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


#ifndef _DRVTUNER_NUTUNE_FJ2207_H_
#define _DRVTUNER_NUTUNE_FJ2207_H_
#include <sys/common/MsTypes.h>

#define INTERFACE extern

#define VHF_LOWMIN_FREQ        48250L    // KHz
#define VHF_LOWMAX_FREQ        158000L    // KHz
#define VHF_HIGHMIN_FREQ    160000L    // KHz
#define VHF_HIGHMAX_FREQ    442000L    // KHz
#define UHF_MIN_FREQ_UK        470000L//470000L    // KHz for UK
#define UHF_MIN_FREQ        442000L    // KHz
#define UHF_MAX_FREQ        863250L    // KHz

#define TUNER_IF_FREQ_KHz            38000L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz    33950L    // KHz


INTERFACE void devDigitalTuner_Init(void);
INTERFACE void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth);
INTERFACE void devTunerInit(void);
INTERFACE void devTunerSetFreqStep(FREQSTEP eFreqStep);
INTERFACE void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);

#undef INTERFACE
#endif
