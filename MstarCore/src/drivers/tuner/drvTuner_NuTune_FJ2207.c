////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

//////////////////////////////////////////////////////////////////////////////
///
/// file    drvTuner_CD1616.c
/// @brief  PHILIPS CD1616 DVBC Tuner Driver Interface
/// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "MsCommon.h"
//#include "drvIIC.h"
//#include "drvTuner.h"
#include <sys/common/MsIRQ.h>
#include <sys/common/MsOS.h>
#include <device/COFDM_Demodulator.h>
#include "FJ2207/inc/tmNxTypes.h"
#include "FJ2207/inc/tmCompId.h"
#include "FJ2207/inc/tmFrontEnd.h"
#include "FJ2207/inc/tmbslFrontEndTypes.h"
#include "FJ2207/inc/tmsysFrontEndTypes.h"
#include "FJ2207/tmbslNT220x/inc/tmbslNT220HN.h"


//#if (FRONTEND_TUNER_TYPE == TUNER_PHILIPS_CD1616LF_GIH_4)
#if 1
//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------


#define IIC_WRITE(u8SlaveId,  u8AddrSize, pu8Addr, u32BufSize,pu8Buf)   devCOFDM_PassThroughI2C_WriteBytes(u8SlaveId, u8AddrSize, pu8Addr, (MS_U16)u32BufSize, pu8Buf)
#define IIC_READ(u8SlaveId, u8AddrSize, pu8Addr, u32BufSize, pu8Buf)   devCOFDM_PassThroughI2C_ReadBytes(u8SlaveId, u8AddrSize, pu8Addr, (MS_U16)u32BufSize, pu8Buf)


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define TUNERADDR 0xC0
#define UNITSEL 0x0


extern tmErrorCode_t 	UserWrittenI2CRead(tmUnitSelect_t tUnit,UInt32 AddrSize, UInt8* pAddr,UInt32 ReadLen, UInt8* pData);
extern tmErrorCode_t 	UserWrittenI2CWrite (tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,UInt32 WriteLen, UInt8* pData);
extern tmErrorCode_t 	UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms);
extern tmErrorCode_t 	UserWrittenPrint(UInt32 level, const char* ,tmUnitSelect_t tUnit);
extern tmErrorCode_t  	UserWrittenMutexInit(ptmbslFrontEndMutexHandle *ppMutexHandle);
extern tmErrorCode_t  	UserWrittenMutexDeInit( ptmbslFrontEndMutexHandle pMutex);
extern tmErrorCode_t  	UserWrittenMutexAcquire(ptmbslFrontEndMutexHandle pMutex, UInt32 timeOut);
extern tmErrorCode_t  	UserWrittenMutexRelease(ptmbslFrontEndMutexHandle pMutex);


//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------

static MS_S32 stFrontEndSem = -1;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CRead
//* Object              :
//* Input Parameters    : 	tmUnitSelect_t tUnit
//* 						UInt32 AddrSize,
//* 						UInt8* pAddr,
//* 						UInt32 ReadLen,
//* 						UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CRead(tmUnitSelect_t tUnit,	UInt32 AddrSize, UInt8* pAddr,
UInt32 ReadLen, UInt8* pData)
{
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    UInt8 U8TunerAddress = TUNERADDR; //for master tuner
    //printf("UserWrittenI2CRead AddrSize = 0x%x,pAddr = 0x%x,ReadLen = 0x%x,pData addr = 0x%x \n",AddrSize,*pAddr,ReadLen,(UInt32)pData);

    IIC_READ(U8TunerAddress,AddrSize,pAddr,ReadLen,pData);


   return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CWrite
//* Object              :
//* Input Parameters    : 	tmUnitSelect_t tUnit
//* 						UInt32 AddrSize,
//* 						UInt8* pAddr,
//* 						UInt32 WriteLen,
//* 						UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CWrite (tmUnitSelect_t tUnit, 	UInt32 AddrSize, UInt8* pAddr,
UInt32 WriteLen, UInt8* pData)
{
   // UInt32 i;
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    UInt8 U8TunerAddress = TUNERADDR; //for master tuner

    //printf("===============================\n");
    //printf("UserWrittenI2CWrite AddrSize = 0x%x,pAddr = 0x%x,WriteLen = 0x%x,pData addr = 0x%x \n",AddrSize,*pAddr,WriteLen,(UInt32)pData);
    //for(i=0;i<WriteLen;i++)
    //{
    //    printf("pData[%d] = 0x%x \n",i,pData[i]);
    //}
    //printf("===============================\n");
    IIC_WRITE(U8TunerAddress,AddrSize,pAddr,WriteLen,pData);


   return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenWait
//* Object              :
//* Input Parameters    : 	tmUnitSelect_t tUnit
//* 						UInt32 tms
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms)
{
   /* Variable declarations */
   tmErrorCode_t err = TM_OK;
    MsOS_DelayTask(tms);

   return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenPrint
//* Object              :
//* Input Parameters    : 	UInt32 level, const char* format, ...
//*
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenPrint(UInt32 level, const char* pchar,tmUnitSelect_t tUnit)
{
   /* Variable declarations */
   tmErrorCode_t err = TM_OK;



   return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexInit
//* Object              :
//* Input Parameters    : 	ptmbslFrontEndMutexHandle *ppMutexHandle
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t  UserWrittenMutexInit(ptmbslFrontEndMutexHandle *ppMutexHandle)
{
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    //stFrontEndSem = MsOS_CreateMutex (E_MSOS_FIFO, "MUTEX_FrontEnd", MSOS_PROCESS_PRIVATE);
    stFrontEndSem = 1;
    ppMutexHandle = (void *)stFrontEndSem;

   return err;
}


//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexDeInit
//* Object              :
//* Input Parameters    : 	 ptmbslFrontEndMutexHandle pMutex
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t  UserWrittenMutexDeInit( ptmbslFrontEndMutexHandle pMutex)
{
   /* Variable declarations */
   tmErrorCode_t err = TM_OK;
    //MsOS_DeleteMutex(stFrontEndSem);
    stFrontEndSem = 1;

   return err;
}



//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexAcquire
//* Object              :
//* Input Parameters    : 	ptmbslFrontEndMutexHandle pMutex, UInt32 timeOut
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t  UserWrittenMutexAcquire(ptmbslFrontEndMutexHandle pMutex, UInt32 timeOut)
{
   /* Variable declarations */
   tmErrorCode_t err = TM_OK;
   //MsOS_ObtainMutex(stFrontEndSem, MSOS_WAIT_FOREVER);


   return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexRelease
//* Object              :
//* Input Parameters    : 	ptmbslFrontEndMutexHandle pMutex
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t  UserWrittenMutexRelease(ptmbslFrontEndMutexHandle pMutex)
{
   /* Variable declarations */
   tmErrorCode_t err = TM_OK;
     //MsOS_ReleaseMutex(stFrontEndSem);



   return err;
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

#if 1
void devDigitalTuner_Init(void)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndDependency_t sSrvTunerFunc;
    printf("== devDigitalTuner_Init ==\n");
    sSrvTunerFunc.sIo.Write             = UserWrittenI2CWrite;
    sSrvTunerFunc.sIo.Read              = UserWrittenI2CRead;
    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = UserWrittenPrint;
    sSrvTunerFunc.sMutex.Init           = UserWrittenMutexInit;
    sSrvTunerFunc.sMutex.DeInit         = UserWrittenMutexDeInit;
    sSrvTunerFunc.sMutex.Acquire        = UserWrittenMutexAcquire;
    sSrvTunerFunc.sMutex.Release        = UserWrittenMutexRelease;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;
    //printf("tmbslNT220xInit begin \n");
    /* NT220X Master Driver low layer setup */
    err = tmbslNT220xInit(UNITSEL, &sSrvTunerFunc);
    if(err != TM_OK)
        return;

    //printf("tmbslNT220xInit end \n");


    /* NT220X Master Hardware initialization */
    err = tmbslNT220xReset(UNITSEL);
    if(err != TM_OK)
        return;


}
#else
void devDigitalTuner_Init(void)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndDependency_t sSrvTunerFunc;

    tmsysFrontEndState_t  LockStatus;
    tmUnitSelect_t  Tuner_Master = 0;

    sSrvTunerFunc.sIo.Write             = UserWrittenI2CWrite;
    sSrvTunerFunc.sIo.Read              = UserWrittenI2CRead;
    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = UserWrittenPrint;
    sSrvTunerFunc.sMutex.Init           = UserWrittenMutexInit;
    sSrvTunerFunc.sMutex.DeInit         = UserWrittenMutexDeInit;
    sSrvTunerFunc.sMutex.Acquire        = UserWrittenMutexAcquire;
    sSrvTunerFunc.sMutex.Release        = UserWrittenMutexRelease;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;

    /* OM3869 Master Driver low layer setup */
   err = tmsysOM3869Init(Tuner_Master, &sSrvTunerFunc);
   if(err != TM_OK)
       return err;

    /* OM3869 Master Hardware power state */
   err = tmsysOM3869SetPowerState(Tuner_Master, tmPowerOn);

   /* OM3869 Master Hardware initialization */
   err = tmsysOM3869Reset(Tuner_Master);
   if(err != TM_OK)
       return err;



}
#endif

#if 1
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    tmErrorCode_t err;
    tmNT220xStandardMode_t NT220xStdMode;
    tmbslFrontEndState_t PLLLockMaster = tmbslFrontEndStateUnknown;

    UInt32 uRF = Freq * 1000000;


    switch(eBandWidth)
    {
        case E_RF_CH_BAND_6MHz:
            NT220xStdMode = tmNT220x_DVBT_6MHz;
        break;

        case E_RF_CH_BAND_7MHz:
            NT220xStdMode = tmNT220x_DVBT_7MHz;
        break;

        case E_RF_CH_BAND_8MHz:
            NT220xStdMode = tmNT220x_DVBT_8MHz;
        break;

        default:
        printf("error RF_CHANNEL_BANDWIDTH type\n");
        NT220xStdMode = tmNT220x_DVBT_8MHz;
        break;
    }


    /* NT220X Master standard mode */
    err = tmbslNT220xSetStandardMode(UNITSEL, NT220xStdMode);
    if(err != TM_OK)
    return;

    /* NT220X Master RF frequency */
    err = tmbslNT220xSetRf(UNITSEL, uRF);
    if(err != TM_OK)
        return;

#if 1
    while(PLLLockMaster != tmbslFrontEndStateLocked)
    {
     /* Get NT220X Master PLL Lock status */
        err = tmbslNT220xGetLockStatus(0, &PLLLockMaster);
        printf("devDigitalTuner_FJ2207_SetFreq PLLLockMaster = 0x%x\n",PLLLockMaster);

    }
    if(err != TM_OK)
        return;
#endif

}

#else
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    tmErrorCode_t err;
    tmsysFrontEndState_t  LockStatus = tmbslFrontEndStateUnknown;
    tmTunerOnlyRequest_t TuneRequest;
    tmUnitSelect_t  Tuner_Master = 0;

    UInt32 uRF = Freq;

    /* OM3869 Master Send Request 546 MHz standard DVB-T  8 MHz*/
   TuneRequest.dwFrequency = uRF * 1000000;
   TuneRequest.dwStandard = tmNT220x_DVBT_8MHz;
   err = tmsysOM3869SendRequest(Tuner_Master,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
   if(err != TM_OK)
       return err;
   /* OM3869 Master Get locked status */
   err = tmsysOM3869GetLockStatus(Tuner_Master,&LockStatus);
   if(err != TM_OK)
       return err;

}

#endif
//==================================================================================================
//Following function were added for compatible Chakra2 tuner code base.
//==================================================================================================



void devTunerInit(void)
{
}


void devTunerSetFreqStep(FREQSTEP eFreqStep)
{

}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
}

#endif // TUNER_PHILIPS_CD1616LF_GIH_4

