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

* Class : device_tuner
* File  : device_tuner_tdtc_g311d.cpp
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/


/*@ <Include> @*/
/*
#include "device_tuner.h"
#include "device_tuner_NXP_TD1611ALF.h"
#include "mapi_i2c_devTable.h"

//#include "apiSWI2C.h"
#include "mapi_i2c.h"
#include "mapi_interface.h" */
#include <cofdm/COFDM_Demodulator.h>
#include <MsOS.h>


#define tuner_I2c 0xC0

#define NXP_TD1611ALF_INT_AGC 1
#define TUNER_IF_FREQ                   36160

#define DBG_TUNER(x)  // x

#if 0
U8 u8DeviceBusy=0;

MAPI_BOOL DeviceTunerCreate()
{
    mapi_tuner *pMapiTuner;

    pMapiTuner = mapi_interface::Get_mapi_tuner();

    pMapiTuner->stMapiTunerFun.Connect = Connect;

    pMapiTuner->stMapiTunerFun.Disconnect = Disconnect;

    pMapiTuner->stMapiTunerFun.ATV_SetTune = ATV_SetTune;

    pMapiTuner->stMapiTunerFun.DTV_SetTune = DTV_SetTune;

    pMapiTuner->stMapiTunerFun.ExtendCommand = ExtendCommand;

    return TRUE;

}

BOOL Connect(void)
{
    DBG_TUNER(printf("device_tuner_CD1616LF_GIGH_4: Connect\n"));
    if (u8DeviceBusy==1)
        return FALSE;

    u8DeviceBusy=1;

    return TRUE;
}

BOOL Disconnect()
{
    DBG_TUNER(printf("device_tuner_CD1616LF_GIGH_4: Disconnect\n"));

    u8DeviceBusy=0;
    return TRUE;
}

BOOL ATV_SetTune( U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode)
{
    u32FreqKHz = u32FreqKHz;
    eBand = eBand;
    eMode = eMode;

    return TRUE;
}

BOOL DTV_SetTune( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    U8 CONFIG[5];
    U8 CB0,CB1;
    BOOL dwError = FALSE;
    U8    ucfreq[2];
    U16    wFrequency;
    U8    ucDividerRatio = 6;
    eMode = eMode;
    // Use critical section to protect Tuner frequency setting
    //SysEnterCriticalSection();

    CB0 = 0xC8;
    CB1 = 0;
    //P5 P4
    if(eBandWidth == E_RF_CH_BAND_8MHz)
    {
          CB0 |= 0x01;
          CB1 |= 0x08;//according to -4 spec only.
          ucDividerRatio = 7;
    }
    else
    {
         CB0 |= 0x02; //R2R1R0
         ucDividerRatio = 6;
    }
    Freq*=1000;
    DBG_TUNER(printf("sttest tune %d ,%d \n",(int)Freq,(int)eBandWidth));

    wFrequency = (U16)(((Freq + TUNER_IF_FREQ) * ucDividerRatio + 500) / 1000);
    ucfreq[1] = (U8)((wFrequency >> 8) & 0x00FF);
    ucfreq[0] = (U8)(wFrequency & 0x00FF);

    //P3 P2 P1
    if ( Freq <= 174000 ) // VHF low
    {
        CB1 |= 0x00;
    }
    else if ( Freq  <= 470000 ) // VHF high
    {
        CB1 |= 0x02;
    }
    else  // UHF
    {
        CB1 |= 0x04;
    }

    //Charge Pump  CP2 CP1 CP0
    Freq += TUNER_IF_FREQ;
    if(Freq<=200000)
        CB1|= 0x60;// not used
    else if(Freq<=290000)
        CB1|= 0x60;
    else if(Freq<=420000)
        CB1|= 0xA0;
    else if(Freq<=480000)
        CB1|= 0xC0;
    else if(Freq<=620000)
        CB1|= 0x60;
    else if(Freq<=830000)
        CB1|= 0xA0;
    else
        CB1|= 0xE0;

    CONFIG[0]  = ucfreq[1];
    CONFIG[1]  = ucfreq[0];
    CONFIG[2]  = CB0;
    CONFIG[3]  = CB1;
    mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(TUNER_DEV_I2C_1);
    dwError = iptr->WriteBytes(0, NULL, 4, CONFIG);

    if (dwError)
    {
        MsOS_DelayTaskUs(150);
        #if (NXP_TD1611ALF_INT_AGC)
           CONFIG[2]  = 0x8C;
        #else
           CONFIG[2]  = 0x8E;
        #endif
        dwError = iptr->WriteBytes(0, NULL, 4, CONFIG);

    #if 1
        if (dwError)
        {
            U8 n=0;
            while(n<20)
            {
                MsOS_DelayTaskUs(100);
                dwError=iptr->ReadBytes(0,NULL,1, CONFIG);
                n++;
                /*if((CONFIG[0]&0x08)==0x08)
                    printf("Internal RF AGC!\n");
                else
                   printf("external RF AGC\n");*/
                if((CONFIG[0]==0xFF)||(dwError==FALSE)) // not by pass
                {
                    dwError=FALSE;
                    break;
                }
                else if((CONFIG[0]&0x40)==0x40)
                {
                    //printf("Tuner locked %d!\n",n);
                    break;
                }
                else
                {
                    //printf("tuner lock failed\n");
                }

            }

            if((n>=20)||(dwError==FALSE))
            {
                printf("tuner config fail; status:%x\n",CONFIG[0]);
                dwError=FALSE;
            }
        }
    #else
        MsOS_DelayTaskUs(100);
    #endif

    }

    // Release ownership of the critical section
    //SysLeaveCriticalSection();
    return (dwError);
}


BOOL ExtendCommand( U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3)
{
    u8SubCmd=u8SubCmd;
    u32Param1=u32Param1;
    u32Param2=u32Param2;
    pvoidParam3=pvoidParam3;
    return TRUE;
}

#else

#include <Tuner.h>
#include <MsIRQ.h>
#include <MsOS.h>

#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB123x_DEMOD)
#include <cofdm/MSB123x.h>
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB122x_DEMOD)
#include <cofdm/MSB122x.h>
#endif


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

//-----------------------------------------------------
	MS_U8 CONFIG[5];
    MS_U8 CB0,CB1;
    MS_BOOL dwError = FALSE;
    MS_U8    ucfreq[2];
    MS_U16    wFrequency;
    MS_U8    ucDividerRatio = 6;
    // Use critical section to protect Tuner frequency setting
    //SysEnterCriticalSection();

    CB0 = 0xC8;
    CB1 = 0;
    //P5 P4
    if(eBandWidth == E_RF_CH_BAND_8MHz)
    {
          CB0 |= 0x01;
          CB1 |= 0x08;//according to -4 spec only.
          ucDividerRatio = 7;
    }
    else
    {
         CB0 |= 0x02; //R2R1R0
         ucDividerRatio = 6;
    }
    Freq*=1000;
    DBG_TUNER(printf("sttest tune %d ,%d \n",(int)Freq,(int)eBandWidth));

    wFrequency = (U16)(((Freq + TUNER_IF_FREQ) * ucDividerRatio + 500) / 1000);
    ucfreq[1] = (U8)((wFrequency >> 8) & 0x00FF);
    ucfreq[0] = (U8)(wFrequency & 0x00FF);

    //P3 P2 P1
    if ( Freq <= 174000 ) // VHF low
    {
        CB1 |= 0x00;
    }
    else if ( Freq  <= 470000 ) // VHF high
    {
        CB1 |= 0x02;
    }
    else  // UHF
    {
        CB1 |= 0x04;
    }

    //Charge Pump  CP2 CP1 CP0
    Freq += TUNER_IF_FREQ;
    if(Freq<=200000)
        CB1|= 0x60;// not used
    else if(Freq<=290000)
        CB1|= 0x60;
    else if(Freq<=420000)
        CB1|= 0xA0;
    else if(Freq<=480000)
        CB1|= 0xC0;
    else if(Freq<=620000)
        CB1|= 0x60;
    else if(Freq<=830000)
        CB1|= 0xA0;
    else
        CB1|= 0xE0;

    CONFIG[0]  = ucfreq[1];
    CONFIG[1]  = ucfreq[0];
    CONFIG[2]  = CB0;
    CONFIG[3]  = CB1;
 /*   mapi_i2c *iptr = mapi_i2c::GetI2C_Dev(TUNER_DEV_I2C_1);
    dwError = iptr->WriteBytes(0, NULL, 4, CONFIG); */

 dwError = devCOFDM_PassThroughI2C_WriteBytes(tuner_I2c, 0, NULL, 4, CONFIG);

    if (dwError)
    {
        MsOS_DelayTaskUs(150);
        #if (NXP_TD1611ALF_INT_AGC)
           CONFIG[2]  = 0x8C;
        #else
           CONFIG[2]  = 0x8E;
        #endif
       // dwError = iptr->WriteBytes(0, NULL, 4, CONFIG);
		dwError = devCOFDM_PassThroughI2C_WriteBytes(tuner_I2c, 0, NULL, 4, CONFIG);

    #if 1
        if (dwError)
        {
            U8 n=0;
            while(n<200)
            {
                MsOS_DelayTaskUs(100);
               // dwError=iptr->ReadBytes(0,NULL,1, CONFIG);
				dwError = devCOFDM_PassThroughI2C_ReadBytes(tuner_I2c, 0, NULL, 1, CONFIG);

                n++;
                /*if((CONFIG[0]&0x08)==0x08)
                    printf("Internal RF AGC!\n");
                else
                   printf("external RF AGC\n");*/
                if((CONFIG[0]==0xFF)||(dwError==FALSE)) // not by pass
                {
                    dwError=FALSE;
                    break;
                }
                else if((CONFIG[0]&0x40)==0x40)
                {
                    //printf("Tuner locked %d!\n",n);
                    break;
                }
                else
                {
                    //printf("tuner lock failed\n");
                }

            }

            if((n>=200)||(dwError==FALSE))
            {
                printf("tuner config fail; status:%x\n",CONFIG[0]);
                dwError=FALSE;
            }
        }
    #else
        MsOS_DelayTaskUs(100);
    #endif

    }

    // Release ownership of the critical section
    //SysLeaveCriticalSection();
    // return (dwError);

}


#endif

