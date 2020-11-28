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
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __COFDM_DEMODULATOR_H__
#define __COFDM_DEMODULATOR_H__

#include <MsTypes.h>
#include <ShareType.h>
#include <msAPI_Tuner.h>

#if 1//((CONFIG_COMMANDS&(CFG_CMD_TUNER | CFG_CMD_DEMOD)) == (CFG_CMD_TUNER | CFG_CMD_DEMOD))


typedef enum
{
    E_SERIAL_INTERFACE,
    E_PARALLEL_INTERFACE
} TS_INTERFACE;

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD)
#include <cofdm/MSB123x.h>
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB122x_DEMOD)
#include <cofdm/MSB122x.h>
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD)
#include <cofdm/MSB1233C.h>
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
#if defined(CONFIG_KENYA)
typedef enum
{
	COFDM_FEC_LOCK,
	COFDM_PSYNC_LOCK,
	COFDM_TPS_LOCK,
	COFDM_DCR_LOCK,
	COFDM_AGC_LOCK,
	COFDM_MODE_DET,

} COFDM_LOCK_STATUS;
#endif
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1238_DEMOD)
#if defined(CONFIG_KENYA)
typedef enum
{
	COFDM_FEC_LOCK,
	COFDM_PSYNC_LOCK,
	COFDM_TPS_LOCK,
	COFDM_DCR_LOCK,
	COFDM_AGC_LOCK,
	COFDM_MODE_DET,

} COFDM_LOCK_STATUS;
#endif
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1240_DEMOD)
#if defined(CONFIG_KERES)
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_TPS_LOCK_HISTORY,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
    COFDM_LOCK_STABLE_DVBT,
    COFDM_SYNC_LOCK_DVBT,
    COFDM_FAST_LOCK_DVBT,
    COFDM_P1_LOCK,
    COFDM_P1_LOCK_HISTORY,
    COFDM_L1_CRC_LOCK,
    COFDM_DVBT2_NOCH_FLAG,
    COFDM_DVBT_NOCH_FLAG,
} COFDM_LOCK_STATUS;
#endif
#endif


//******************************************************************************
// Functions prototype
//******************************************************************************

void devCOFDM_Init(void);
void devCOFDM_ControlPowerOnOff(BOOLEAN bPowerOn);
FUNCTION_RESULT devCOFDM_PowerSave(void);
void devCOFDM_SetFreqStep(FREQSTEP eFreqStep);
void devCOFDM_SetFrequency(MS_U32 dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID);
BOOLEAN devCOFDM_GetLockStatus(COFDM_LOCK_STATUS eStatus);
U8 devCOFDM_GetSignalToNoiseRatio(void);
void devCOFDM_PassThroughI2C(BOOLEAN bEnable);
BOOLEAN devCOFDM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
BOOLEAN devCOFDM_PassThroughI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
#if (FRONTEND_DEMOD_TYPE == ZARLINK_CE6355_DEMOD)
void devCOFDM_SwitchTransportSteamInferface(TS_INTERFACE interface, RF_CHANNEL_BANDWIDTH BandWidth);
#else
void devCOFDM_SwitchTransportSteamInferface(TS_INTERFACE interface);
#endif
#if DTV_SCAN_AUTO_FINE_TUNE_ENABLE
BOOLEAN devCOFDM_GetFrequencyOffset(float *pFreqOff, RF_CHANNEL_BANDWIDTH u8BW);
BOOLEAN devCOFDM_SetAfcEnable(BOOLEAN bEnable);
#endif
FUNCTION_RESULT devCOFDM_GetSignal_Vit( MS_U32 *vit );
FUNCTION_RESULT devCOFDM_GetSignalStrength(MS_U16 *strength);
BOOLEAN devCOFDM_Get_CELL_ID(MS_U16 *wCell_id);
FUNCTION_RESULT devCOFDM_GetSignalQuality(MS_U16 *quality);
BOOLEAN devCOFDM_GetBER(float *ber);
BOOLEAN devCOFDM_Get_Modul_Mode(MS_U16 *Modul_Mode);
BOOLEAN devCOFDM_Is_Hierarchy_On(void);
void devCOFDM_TunerProgramming(U8 *cTunerData);

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD || FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD || FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD || FRONTEND_DEMOD_TYPE == TOSHIBA_TC90517FG_DEMOD)
U16 devCOFDM_ReadReg(U16 RegAddr);
BOOLEAN devCOFDM_WriteReg(U16 RegAddr, U16 RegData);
#endif
#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD) || (FRONTEND_DEMOD_TYPE == MSTAR_MSB122x_DEMOD) ||(FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD))
BOOLEAN devCOFDM_SetDemodType(EN_DEVICE_DEMOD_TYPE enDemodType);
EN_DEVICE_DEMOD_TYPE devCOFDM_GetDemodType(void);
#endif

#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD) || (FRONTEND_DEMOD_TYPE == MSTAR_MSB1233c_DEMOD))
BOOLEAN devCOFDM_DTV_Serial_Control(BOOLEAN bEnable);
#endif

#if ((FRONTEND_DEMOD_TYPE == MSTAR_MSB1238_DEMOD)||(FRONTEND_DEMOD_TYPE == MSTAR_MSB1240_DEMOD))
MS_BOOL MDrv_Tuner_Init(void);
MS_U32 MDrv_Tuner_SetTuner(MS_U32 dwFreq /*Khz*/, MS_U8 ucBw /*MHz*/);
#else
void MDrv_Tuner_Init(void);
#endif

#endif
#endif // __COFDM_DEMODULATOR_H__

