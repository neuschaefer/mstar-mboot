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

#if !defined(__TUNER_H__)
#define __TUNER_H__
//#include <drvVIF.h>
#if 1//((CONFIG_COMMANDS&(CFG_CMD_TUNER | CFG_CMD_DEMOD)) == (CFG_CMD_TUNER | CFG_CMD_DEMOD))

#define FREQ_STEP_31_25KHz      0x00
#define FREQ_STEP_50KHz         0x01
#define FREQ_STEP_62_5KHz       0x02
#define FREQ_STEP_166_67KHz     0x03
#define FREQ_STEP_125KHz        0x04
#define FREQ_STEP_142_86KHz     0x05


#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
#define IF_FREQ_45_75                               0x01//IF_FREQ_MN
#define IF_FREQ_38_90                               0x02//IF_FREQ_B
#define IF_FREQ_38_00                               0x03//IF_FREQ_PAL_38
#elif (FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
#define IF_FREQ_45_75                               0x01//IF_FREQ_MN
#define IF_FREQ_38_90                               0x02//IF_FREQ_B
#define IF_FREQ_38_00                               0x03//IF_FREQ_PAL_38
#elif (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
#define IF_FREQ_45_75          0x01//IF_FREQ_MN
#define IF_FREQ_38_90          0x02//IF_FREQ_B
#define IF_FREQ_38_00          0x03//IF_FREQ_PAL_38
#define IF_BASE_FREQ           IF_FREQ_38_90  //IF_FREQ_38_00  // IF_FREQ_38_90
#define VIF_VGA_MAXIMUM        0x3000
#define GAIN_DISTRIBUTION_THR  0x2000
#endif

typedef enum
{
    E_RFBAND_VHF_LOW,
    E_RFBAND_VHF_HIGH,
    E_RFBAND_UHF
} RFBAND;

typedef enum
{
    FREQSTEP_62_5KHz,
    FREQSTEP_50KHz,
    FREQSTEP_31_25KHz,
    FREQSTEP_166_67KHz
} FREQSTEP;

/// RF Channel bandwidth
typedef enum
{
    E_RF_CH_BAND_6MHz = 0x01,       ///< 6MHz
    E_RF_CH_BAND_7MHz = 0x02,       ///< 7MHz
    E_RF_CH_BAND_8MHz = 0x03,       ///< 8MHz
    E_RF_CH_BAND_INVALID            ///< Invalid
} RF_CHANNEL_BANDWIDTH;


typedef enum
{
    E_RF_CH_HP = 0x00,
    E_RF_CH_LP = 0x01
} RF_CHANNEL_HP_LP;
typedef enum
{
    IF_FREQ_INVALID,
    IF_FREQ_B,              // 38.90 MHz
    IF_FREQ_G,              // 38.90 MHz
    IF_FREQ_I,              // 38.90 MHz
    IF_FREQ_DK,             // 38.90 MHz
    IF_FREQ_L,              // 38.90 MHz
    IF_FREQ_L_PRIME,        // 33.90 MHz
    IF_FREQ_MN,             // 45.75 MHz
    IF_FREQ_J,              // 58.75 MHz
    IF_FREQ_PAL_38,         // 38.00 MHz
    IF_FREQ_MAX_IF_FREQ,
    IF_DIGITAL_MODE
} IF_FREQ;

#if (FRONTEND_TUNER_TYPE == NUTUNE_FT2125_TUNER)
#include <tuner/drvTuner_NuTune_FT2125.h>
#elif (FRONTEND_TUNER_TYPE == NUTUNE_FJ2207_TUNER)
#include <tuner/drvTuner_NuTune_FJ2207.h>
#elif(FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
#include "SILAB_2158_A20.h"
#include "SILAB_2158_A20/Si2158_L1_API.h"
#elif(FRONTEND_TUNER_TYPE == NXP_TDA18275_TUNER)
#include "NXP_TDA18275.h"
#elif (FRONTEND_TUNER_TYPE == NXP_TDA18250A_TUNER)
#include "tmbslTDA18250A/tmNxTypes.h"
#include "tmbslTDA18250A/tmCompId.h"
#include "tmbslTDA18250A/tmFlags.h"
#include "tmbslTDA18250A/tmFrontEnd.h"
#include "tmbslTDA18250A/tmbslFrontEndTypes.h"
#include "tmbslTDA18250A/tmbslFrontEndCfgItem.h"
#include "tmbslTDA18250A/tmsysFrontEndTypes.h"
#include "tmbslTDA18250A/tmUnitParams.h"
#include "tmbslTDA18250A/tmbslTDA18250A.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Advanced.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Config_Common.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Config_ATSC.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Config_DTMB.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Config_DVBC.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Config_DVBT.h"
#include "tmbslTDA18250A/tmbslTDA18250A_Config_ISDBT.h"
//#include "tmbslTDA18250A/tmbslTDA18250A_Local.h"
#elif (FRONTEND_TUNER_TYPE == TUNER_MXL603)
#include "MxL603/MaxLinearDataTypes.h"
#include "MxL603/MxL603_Features.h"
#include "MxL603/MxL603_OEM_Drv.h"
#include "MxL603/MxL603_TunerApi.h"
#include "MxL603/MxL603_TunerCfg.h"
#include "MxL603/MxL603_TunerSpurTable.h"
#include "MxL603/MxL_Debug.h"
#elif (FRONTEND_TUNER_TYPE == TUNER_MXL608)
#include "MxL608/MaxLinearDataTypes.h"
#include "MxL608/MxL608_Features.h"
#include "MxL608/MxL608_OEM_Drv.h"
#include "MxL608/MxL608_TunerApi.h"
#include "MxL608/MxL608_TunerCfg.h"
#include "MxL608/MxL608_TunerSpurTable.h"
#include "MxL608/MxL_Debug.h"
#endif

#ifndef TN_FREQ_STEP
  #if((FRONTEND_TUNER_TYPE ==SHARP_VA1G5BF2009_TUNER) || (FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER))
    #define TN_FREQ_STEP                FREQ_STEP_50KHz
  #else
    #define TN_FREQ_STEP                FREQ_STEP_62_5KHz//FREQ_STEP_50KHz//FREQ_STEP_31_25KHz
  #endif
#endif


#ifdef ATSC_SYSTEM
    #define TUNER_IF_FREQ_KHz 45750L
    #define IF_BASE_FREQ                                 IF_FREQ_45_75
#else
 #if ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
  #if (TUNER_IF_FREQ_KHz == 38000L)
    #define IF_BASE_FREQ                                 IF_FREQ_38_00
  #elif (TUNER_IF_FREQ_KHz == 45750L)
    #define IF_BASE_FREQ                                 IF_FREQ_45_75
  #else  // for (TUNER_IF_FREQ_KHz == 38900L)
    #define IF_BASE_FREQ                                 IF_FREQ_38_90
  #endif
 #endif
#endif


void devDigitalTuner_Init(void);
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth);

#endif

#endif // #if !defined(__TUNER_H__)

