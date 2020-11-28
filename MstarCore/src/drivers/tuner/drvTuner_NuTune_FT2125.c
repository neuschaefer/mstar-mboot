/**********************************************************************
 Copyright (c) 2006-2009 MStar Semiconductor, Inc.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 MStar Semiconductor Inc. and be kept in strict confidence
 (MStar Confidential Information) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of MStar Confidential
 Information is unlawful and strictly prohibited. MStar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.

**********************************************************************/


#ifndef drvTuner_NuTune_FT2125_C
#define drvTuner_NuTune_FT2125_C


#include <cofdm/COFDM_Demodulator.h>
#include <MsIRQ.h>
#include <MsOS.h>


void devDigitalTuner_Init()
{

}

void devTunerInit(void)
{
}


void devTunerSetFreqStep(FREQSTEP eFreqStep)
{

}

void devTunerSetPLLData(MS_U16 wPLLData, RFBAND eBand)
{
}


void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    MS_BOOL dwError = FALSE;
    MS_U8 config[4];

    MS_U16 divider = (Freq + 36.0) * 6.0;
    MS_U8 u8Control, u8BandSwitch;

    if (Freq <= 228.5)
    {
        u8Control = 0xBC;
        u8BandSwitch = (eBandWidth != E_RF_CH_BAND_8MHz) ? 0x02 : 0x12;
    }
    else if (Freq <= 500.0)
    {
        u8Control = 0xBC;
        u8BandSwitch = (eBandWidth != E_RF_CH_BAND_8MHz) ? 0x04 : 0x14;
    }
    else if (Freq <= 800.0)
    {
        u8Control = 0xF4;
        u8BandSwitch = (eBandWidth != E_RF_CH_BAND_8MHz) ? 0x04 : 0x14;
    }
    else
    {
        u8Control = 0xFC;
        u8BandSwitch = (eBandWidth != E_RF_CH_BAND_8MHz) ? 0x04 : 0x14;
    }

    config[0] = (divider >> 8) & 0xff;
    config[1] = divider & 0xff;
    config[2] = u8Control;
    config[3] = u8BandSwitch;
    //fprintf(stderr, "\033[1;36m[%s:%s][%d] Freq=%lf config=%x %x %x %x\033[0m\n",
    //            __FILE__, __FUNCTION__, __LINE__, Freq, config[0], config[1], config[2], config[3]);
    dwError = devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, config);
    MsOS_DelayTask(100);
    //usleep(100*1000);

}


#endif
