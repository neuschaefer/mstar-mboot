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
/// file    drvTuner_TDA18250A.c
/// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "Board.h"

#include "drvIIC.h"
#include "drvTuner.h"
#include "drvTunerNull.h"

#if 1//IF_THIS_TUNER_INUSE(TUNER_TDA18250A)||IF_THIS_TUNER_INUSE(TUNER_TDA18250B)

#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#include "apiDigiTuner.h"


//*--------------------------------------------------------------------------------------
//* Include Driver files
//*--------------------------------------------------------------------------------------
#include "tmbslTDA18250A.h"
#include "tmbslTDA18250A_Advanced.h"
//#include "tmbslTDA18250A_Config.h"
//#include "tmbslTDA18250A_Local.h"

#define TDA18250A_ADDR             0xC0



//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------
static tmErrorCode_t     UserWrittenI2CRead(tmUnitSelect_t tUnit,UInt32 AddrSize, UInt8* pAddr,UInt32 ReadLen, UInt8* pData);
static tmErrorCode_t     UserWrittenI2CWrite (tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,UInt32 WriteLen, UInt8* pData);
static tmErrorCode_t     UserWrittenI2C1Read(tmUnitSelect_t tUnit,UInt32 AddrSize, UInt8* pAddr,UInt32 ReadLen, UInt8* pData);
static tmErrorCode_t     UserWrittenI2C1Write (tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,UInt32 WriteLen, UInt8* pData);
static tmErrorCode_t     UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms);
static tmErrorCode_t     UserWrittenPrint(UInt32 level, const char* format, ...);
#if 0
static tmErrorCode_t     UserWrittenMutexInit(ptmbslFrontEndMutexHandle *ppMutexHandle);
static tmErrorCode_t     UserWrittenMutexDeInit( ptmbslFrontEndMutexHandle pMutex);
static tmErrorCode_t     UserWrittenMutexAcquire(ptmbslFrontEndMutexHandle pMutex, UInt32 timeOut);
static tmErrorCode_t     UserWrittenMutexRelease(ptmbslFrontEndMutexHandle pMutex);
#endif

//#define IIC_WRITE(u8SlaveId, pu8Addr, u8AddrSize, pu8Buf, u32BufSize)   MDrv_IIC_WriteBytes(u8SlaveId, u8AddrSize, pu8Addr, (MS_U16)u32BufSize, pu8Buf)
//#define IIC_READ(u8SlaveId, pu8Addr, u8AddrSize, pu8Buf, u32BufSize)   MDrv_IIC_ReadBytes(u8SlaveId, u8AddrSize, pu8Addr, (MS_U16)u32BufSize, pu8Buf)

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
/*
#if   (FRONTEND_TUNER_CTRL == PIU_IIC_0)
#define IIC_WRITE                   MDrv_IIC_Write
#define IIC_READ                    MDrv_IIC_Read
#elif (FRONTEND_TUNER_CTRL == PIU_IIC_1)
#define IIC_WRITE                   MDrv_IIC1_Write
#define IIC_READ                    MDrv_IIC1_Read
#elif (FRONTEND_TUNER_CTRL == PIU_IIC_NONE)
#define REG(addr)                   (*(volatile MS_U8*)(addr))
#else
#error "FRONTEND_TUNER_CTRL"
#endif
*/
#define IIC_WRITE                   MDrv_IIC_Write
#define IIC_READ                    MDrv_IIC_Read
#define IIC1_WRITE                  MDrv_IIC1_Write
#define IIC1_READ                   MDrv_IIC1_Read
#define MAX_FRONTEND_NUM            1



//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
/*MS_U8 dmdConfig[] =

{
    // SZ 5015 board TDA18250HN internal RFAGC
    // Rev.: [0x3f] 0x82, [0x20] 0x72, [0x29] 0xff, [0x2a] 0x7f, [0x30] 0xd3
    0x01, 0x08, 0x84, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x73, 0x00, 0xb3, 0x33, 0x03, 0x05, 0x52, 0x52, 0x73, 0x73, 0x73, 0x31, 0x52, 0x73, 0x73, 0x73,
    0x72, 0xc0, 0x24, 0x00, 0x80, 0xff, 0x7f, 0x00, 0x80, 0xff, 0x7f, 0x0e, 0x2b, 0x0b, 0x47, 0x40,
    0xd3, 0x9a, 0xde, 0x11, 0xa4, 0x60, 0x08, 0x08, 0x00, 0x10, 0x02, 0x0b, 0x03, 0x05, 0x03, 0x82,
    0x52, 0x52, 0x55,
};

MS_U8 dmdConfig[] =
{
      0x01, 0x22, 0x8d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x73, 0x00, 0xb3, 0x33, 0x03, 0x05, 0x52, 0x52, 0x73, 0x73, 0x73, 0x31, 0x52, 0x73, 0x73, 0x73,
      0x72, 0xc0, 0x24, 0x00, 0x80, 0xff, 0x7f, 0x00, 0x80, 0xff, 0x7f, 0x0e, 0x2b, 0x0b, 0x47, 0x40,
      0xd3, 0x9a, 0xde, 0x11, 0xa4, 0x60, 0x08, 0x08, 0x00, 0x10, 0x02, 0x0b, 0x03, 0x05, 0x03, 0x82,
      0x52, 0x52, 0x55,
};*/

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
extern DEV_FRONTEND_TYPE frontendtab[MAX_FRONTEND_NUM]; // <= not good

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_Tuner_TDA18250A_SetFreq(MS_U8 u8TunerIndex, MS_U32 u32Freq)
{
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndState_t PLLLockMaster = tmbslFrontEndStateUnknown;
    UInt32 uIFMaster = 0;



    err = tmbslTDA18250A_SetRF(u8TunerIndex,0, u32Freq*1000);
    if(err != TM_OK)
        return err;

    err = tmbslTDA18250A_GetPLLState(u8TunerIndex,0, &PLLLockMaster);
    //printf("===================== Lock status=%d, result[0x%X].\n", PLLLockMaster, err);
    if(err != TM_OK)
        return err;

    /* Get TDA18250A IF */
    err = tmbslTDA18250A_GetIF(u8TunerIndex,0, &uIFMaster);
    //printf("===================== uIFMaster=%d, result[0x%X].\n",(int)uIFMaster, err);


    if(err == TM_OK)
        return TRUE;
    else
        return FALSE;
}


MS_BOOL MDrv_Tuner_TDA18250A_SetTuner(MS_U8 u8TunerIndex, MS_U32 u32Freq, MS_U8 u8Bw)
{
    TDA18250AStandardMode_t standard_mode;

    switch(u8Bw)
    {
       case 0x01://J83B
            printf("=== TDA18250A_QAM_6MHz\n");
            standard_mode = TDA18250A_QAM_6MHz;
            break;
       case 0x03:
            printf("=== TDA18250A_QAM_8MHz\n");
            standard_mode = TDA18250A_QAM_8MHz;
            break;
       default:
            printf("=== TDA18250A_QAM_8MHz\n");
            standard_mode = TDA18250A_QAM_8MHz;
            break;
    }

    if(TM_OK != tmbslTDA18250A_SetStandardMode(u8TunerIndex, 0, standard_mode))
        printf("!!!!! standard_mode error\n");

    return MDrv_Tuner_TDA18250A_SetFreq(u8TunerIndex,u32Freq);
}


MS_BOOL MDrv_Tuner_TDA18250A_PowerOnOff(MS_U8 u8TunerIndex, MS_BOOL bPowerOn)
{
    return TRUE;
}
MS_BOOL MDrv_Tuner_TDA18250B_Init(MS_U8 u8TunerIndex)
{
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndDependency_t   sSrvTunerFunc;
    UInt32                      TunerUnit = 0;
    TDA18250AStandardMode_t     TDA18250AStdMode = TDA18250A_QAM_8MHz;
    //UInt32                      uRF = 0;
    //tmbslFrontEndState_t        PLLLock = tmbslFrontEndStateUnknown;
    HWI2C_PORT hwi2c_port;
    hwi2c_port = getI2CPort(u8TunerIndex);
    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        sSrvTunerFunc.sIo.Write = UserWrittenI2CWrite;
        sSrvTunerFunc.sIo.Read = UserWrittenI2CRead;
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        sSrvTunerFunc.sIo.Write = UserWrittenI2C1Write;
        sSrvTunerFunc.sIo.Read = UserWrittenI2C1Read;
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }

    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = UserWrittenPrint;
    sSrvTunerFunc.sMutex.Init           = Null;
    sSrvTunerFunc.sMutex.DeInit         = Null;
    sSrvTunerFunc.sMutex.Acquire        = Null;
    sSrvTunerFunc.sMutex.Release        = Null;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;

    // Reset the XTAL CLK to 18250B Only
    tmbslTDA18250B_ResetConfig(u8TunerIndex);

    /* Open TDA18250A driver instance */
    err = tmbslTDA18250A_Open(u8TunerIndex,TunerUnit, &sSrvTunerFunc);
    printf("\n=== TDA18250B open, result[0x%lX]. \n", err);
    if(err == TM_OK)
    {
        /* TDA18250A Power On */
        err = tmbslTDA18250A_SetPowerState(u8TunerIndex,TunerUnit, tmPowerOn);
        printf("\n=== TDA18250B SetPowerState, result[0x%lX]. \n", err);

        /* TDA18250A Hardware initialization */
        err = tmbslTDA18250A_HwInit(u8TunerIndex,TunerUnit);
        printf("\n=== TDA18250B HW init status, result[0x%lX]. \n", err);

        /* TDA18250A Power On */
        err = tmbslTDA18250A_SetPowerState(u8TunerIndex,TunerUnit, tmPowerOn);
        printf("\n=== TDA18250B Set2ndPowerState, result[0x%lX]. \n", err);

        if(err == TM_OK)
        {
          /* TDA18250A standard mode if changed */
          err = tmbslTDA18250A_SetStandardMode(u8TunerIndex, TunerUnit, TDA18250AStdMode);
          printf("\n=== TDA18250B init SetStandardMode status[0x%lX]. \n", err);
        }

    }
    else
    {
        printf("\n=== TDA18250B open fail[%ld]. \n", err);
    }

    #if 0   //temp
    if(err == TM_OK)
    {
      /* Get TDA18250A PLL Lock status */
      err = tmbslTDA18250A_GetLockStatus(TunerUnit, &PLLLock);
    }
    #endif
    if(err == TM_OK)
    {
        return TRUE;
    }
    else
    {
        printf("\n=== TDA18250B init fail, status[%ld]. \n", err);
        return FALSE;
    }

}

MS_BOOL MDrv_Tuner_TDA18250A_Init(MS_U8 u8TunerIndex)
{
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndDependency_t   sSrvTunerFunc;
    UInt32                      TunerUnit = 0;
    TDA18250AStandardMode_t     TDA18250AStdMode = TDA18250A_QAM_8MHz;
    //UInt32                      uRF = 0;
    //tmbslFrontEndState_t        PLLLock = tmbslFrontEndStateUnknown;
    HWI2C_PORT hwi2c_port;
    hwi2c_port = getI2CPort(u8TunerIndex);
    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        sSrvTunerFunc.sIo.Write = UserWrittenI2CWrite;
        sSrvTunerFunc.sIo.Read = UserWrittenI2CRead;
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        sSrvTunerFunc.sIo.Write = UserWrittenI2C1Write;
        sSrvTunerFunc.sIo.Read = UserWrittenI2C1Read;
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }

    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = UserWrittenPrint;
    sSrvTunerFunc.sMutex.Init           = Null;
    sSrvTunerFunc.sMutex.DeInit         = Null;
    sSrvTunerFunc.sMutex.Acquire        = Null;
    sSrvTunerFunc.sMutex.Release        = Null;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;

    /* Open TDA18250A driver instance */
    err = tmbslTDA18250A_Open(u8TunerIndex,TunerUnit, &sSrvTunerFunc);
    printf("\n=== TDA18250A open, result[0x%lX]. \n", err);
    if(err == TM_OK)
    {
        /* TDA18250A Power On */
        err = tmbslTDA18250A_SetPowerState(u8TunerIndex,TunerUnit, tmPowerOn);
        printf("\n=== TDA18250A SetPowerState, result[0x%lX]. \n", err);

        /* TDA18250A Hardware initialization */
        err = tmbslTDA18250A_HwInit(u8TunerIndex,TunerUnit);
        printf("\n=== TDA18250A HW init status, result[0x%lX]. \n", err);

        /* TDA18250A Power On */
        err = tmbslTDA18250A_SetPowerState(u8TunerIndex,TunerUnit, tmPowerOn);
        printf("\n=== TDA18250A Set2ndPowerState, result[0x%lX]. \n", err);

        if(err == TM_OK)
        {
          /* TDA18250A standard mode if changed */
          err = tmbslTDA18250A_SetStandardMode(u8TunerIndex, TunerUnit, TDA18250AStdMode);
          printf("\n=== TDA18250A init SetStandardMode status[0x%lX]. \n", err);
        }

    }
    else
    {
        printf("\n=== TDA18250A open fail[%ld]. \n", err);
    }

    #if 0   //temp
    if(err == TM_OK)
    {
      /* Get TDA18250A PLL Lock status */
      err = tmbslTDA18250A_GetLockStatus(TunerUnit, &PLLLock);
    }
    #endif
    if(err == TM_OK)
    {
        return TRUE;
    }
    else
    {
        printf("\n=== TDA18250A init fail, status[%ld]. \n", err);
        return FALSE;
    }

}

MS_U32 MDrv_Tuner_Loop_Through_On(MS_U8 u8TunerIndex, MS_BOOL bOn)
{
    return TRUE;
}


MS_U32 MDrv_Tuner_Stand_By(MS_U8 u8TunerIndex)
{
    return TRUE;
}


MS_U32 MDrv_Tuner_Wake_Up(MS_U8 u8TunerIndex)
{
    return TRUE;
}
//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CRead
//* Object              :
//* Input Parameters    :   tmUnitSelect_t tUnit
//*                         UInt32 AddrSize,
//*                         UInt8* pAddr,
//*                         UInt32 ReadLen,
//*                         UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2C1Read(tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,
UInt32 ReadLen, UInt8* pData)
{
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;

    if(IIC1_READ(TDA18250A_ADDR, pAddr, (MS_U8)AddrSize,  pData, (MS_U16)ReadLen)!=TRUE)
    {
        err = TDA18250A_ERR_HW_FAILED;
        printf("[%s][%d] \n",__FUNCTION__,__LINE__);
    }
    return err;
}
//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CWrite
//* Object              :
//* Input Parameters    :   tmUnitSelect_t tUnit
//*                         UInt32 AddrSize,
//*                         UInt8* pAddr,
//*                         UInt32 WriteLen,
//*                         UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2C1Write (tmUnitSelect_t tUnit,   UInt32 AddrSize, UInt8* pAddr,
UInt32 WriteLen, UInt8* pData)
{
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;

    if(IIC1_WRITE(TDA18250A_ADDR, pAddr, (MS_U8)AddrSize, pData, (MS_U16)WriteLen)!=TRUE)
    {
        err = TDA18250A_ERR_HW_FAILED;
        printf("[%s][%d] \n",__FUNCTION__,__LINE__);
    }

    return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CRead
//* Object              :
//* Input Parameters    :     tmUnitSelect_t tUnit
//*                         UInt32 AddrSize,
//*                         UInt8* pAddr,
//*                         UInt32 ReadLen,
//*                         UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CRead(tmUnitSelect_t tUnit,    UInt32 AddrSize, UInt8* pAddr,
UInt32 ReadLen, UInt8* pData)
{
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;

    if(IIC_READ(TDA18250A_ADDR, pAddr, (MS_U8)AddrSize, pData, (MS_U16)ReadLen)!= TRUE)
        err = TDA18250A_ERR_HW_FAILED;

    //printf("\n=== TDA18250A UserWrittenI2CRead, result[0x%X]. \n", err);
    return err;
}
//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CWrite
//* Object              :
//* Input Parameters    :     tmUnitSelect_t tUnit
//*                         UInt32 AddrSize,
//*                         UInt8* pAddr,
//*                         UInt32 WriteLen,
//*                         UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CWrite (tmUnitSelect_t tUnit,     UInt32 AddrSize, UInt8* pAddr,
UInt32 WriteLen, UInt8* pData)
{
   /* Variable declarations */
    tmErrorCode_t err = TM_OK;

    if(IIC_WRITE(TDA18250A_ADDR, pAddr, (MS_U8)AddrSize, pData, (MS_U16)WriteLen)!= TRUE)
    {
        err = TDA18250A_ERR_HW_FAILED;
    }

    //printf("\n=== TDA18250A UserWrittenI2CWrite, result[0x%X]. \n", err);
    return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenWait
//* Object              :
//* Input Parameters    :     tmUnitSelect_t tUnit
//*                         UInt32 tms
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
//* Input Parameters    :     UInt32 level, const char* format, ...
//*
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t             UserWrittenPrint(UInt32 level, const char* format, ...)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;

    /* Customer code here */
    /* ...*/

    /* ...*/
    /* End of Customer code here */

    return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexInit
//* Object              :
//* Input Parameters    :     ptmbslFrontEndMutexHandle *ppMutexHandle
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
//tmErrorCode_t  UserWrittenMutexInit(ptmbslFrontEndMutexHandle *ppMutexHandle)
//{
    /* Variable declarations */
  //  tmErrorCode_t err = TM_OK;

    /* Customer code here */
    /* ...*/

    /* ...*/
    /* End of Customer code here */

    //return err;
//}


//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexDeInit
//* Object              :
//* Input Parameters    :      ptmbslFrontEndMutexHandle pMutex
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
//tmErrorCode_t  UserWrittenMutexDeInit( ptmbslFrontEndMutexHandle pMutex)
//{
    /* Variable declarations */
    //tmErrorCode_t err = TM_OK;

    /* Customer code here */
    /* ...*/

    /* ...*/
    /* End of Customer code here */

    //return err;
//}



//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexAcquire
//* Object              :
//* Input Parameters    :     ptmbslFrontEndMutexHandle pMutex, UInt32 timeOut
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
//tmErrorCode_t  UserWrittenMutexAcquire(ptmbslFrontEndMutexHandle pMutex, UInt32 timeOut)
//{
    /* Variable declarations */
    //tmErrorCode_t err = TM_OK;

    /* Customer code here */
    /* ...*/

    /* ...*/
    /* End of Customer code here */

    //return err;
//}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenMutexRelease
//* Object              :
//* Input Parameters    :     ptmbslFrontEndMutexHandle pMutex
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
//tmErrorCode_t  UserWrittenMutexRelease(ptmbslFrontEndMutexHandle pMutex)
//{
    /* Variable declarations */
    //tmErrorCode_t err = TM_OK;

    /* Customer code here */
    /* ...*/

    /* ...*/
    /* End of Customer code here */

    //return err;
//}

#define TDA18250A_CHIP_ID_1 0x4a
#define TDA18250A_CHIP_ID_0 0xc7
#define TDA18250A_REVISION_0 0x20
#define TDA18250B_REVISION_0 0x21


MS_BOOL TDA18250A_CheckExist(MS_U8 u8TunerIndex)
{
    MS_U8 Addr = 0x00;
    MS_U8 Data[3] = {0};

    HWI2C_PORT hwi2c_port;
    hwi2c_port = getI2CPort(u8TunerIndex);

    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        IIC_READ(TDA18250A_ADDR, &Addr,1, &Data[0],1);
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        IIC1_READ(TDA18250A_ADDR, &Addr,1, &Data[0],1);
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }
    Addr = 0x01;
    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        IIC_READ(TDA18250A_ADDR, &Addr,1, &Data[1],1);
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        IIC1_READ(TDA18250A_ADDR, &Addr,1, &Data[1],1);
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }
    Addr = 0x02;
    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        IIC_READ(TDA18250A_ADDR, &Addr,1, &Data[2],1);
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        IIC1_READ(TDA18250A_ADDR, &Addr,1, &Data[2],1);
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }



    printf("[18250a] read id =0x%x 0x%x , 0x%x\n",Data[0],Data[1],Data[2]);

    return (Data[0] == TDA18250A_CHIP_ID_0) && (Data[1] == TDA18250A_CHIP_ID_1) ;
}

MS_BOOL TDA18250B_CheckExist(MS_U8 u8TunerIndex)
{
    MS_U8 Addr = 0x00;
    MS_U8 Data[3] = {0};

    HWI2C_PORT hwi2c_port;
    hwi2c_port = getI2CPort(u8TunerIndex);

    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        IIC_READ(TDA18250A_ADDR, &Addr,1, &Data[0],1);
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        IIC1_READ(TDA18250A_ADDR, &Addr,1, &Data[0],1);
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }
    Addr = 0x01;
    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        IIC_READ(TDA18250A_ADDR, &Addr,1, &Data[1],1);
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        IIC1_READ(TDA18250A_ADDR, &Addr,1, &Data[1],1);
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }
    Addr = 0x02;
    if (hwi2c_port < E_HWI2C_PORT_1)
    {
        IIC_READ(TDA18250A_ADDR, &Addr,1, &Data[2],1);
    }
    else if (hwi2c_port < E_HWI2C_PORT_2)
    {
        IIC1_READ(TDA18250A_ADDR, &Addr,1, &Data[2],1);
    }
    else
    {
        printf("hwi2c_port number exceeds limitation\n");
        return FALSE;
    }



    printf("[18250b] read id =0x%x 0x%x , 0x%x\n",Data[0],Data[1],Data[2]);

    return (Data[0] == TDA18250A_CHIP_ID_0) && (Data[1] == TDA18250A_CHIP_ID_1) ;

}

MS_BOOL TDA18250A_Extension_Function(MS_U8 u8TunerIndex, TUNER_EXT_FUNCTION_TYPE fuction_type, void *data)
{
    return TRUE;
}
DRV_TUNER_TABLE_TYPE GET_TUNER_ENTRY_NODE(1) DDI_DRV_TUNER_TABLE_ENTRY(tunertab) =
{
    .name               = "TUNER_TDA18250A",          // demod system name
    .data               = 1,            // private data value
    .Init               = MDrv_Tuner_TDA18250A_Init,
    .SetFreq            = MDrv_Tuner_TDA18250A_SetFreq,
    .SetFreqS2          = MDrv_Tuner_Null_SetFreq_S2,
    .GetLock            = MDrv_Tuner_Null_GetLock,
    .SetTuner           = MDrv_Tuner_TDA18250A_SetTuner,
    .CheckExist         = TDA18250A_CheckExist,
    .Extension_Function = TDA18250A_Extension_Function
};

#endif // TUNER_PHILIPS_TDA18250A

void devDigitalTuner_Init(void)
{
    MDrv_Tuner_TDA18250A_Init(0);
    return;
}

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    MS_BOOL bOK = MDrv_Tuner_TDA18250A_SetTuner(0, (MS_U32)Freq*1000, eBandWidth);
    if(bOK == TRUE)
    {
        printf("Tuner LOCK OK!!!!\n");
    }
    else
    {
        printf("Tuner LOCK FAIL!!!!\n");
    }
}