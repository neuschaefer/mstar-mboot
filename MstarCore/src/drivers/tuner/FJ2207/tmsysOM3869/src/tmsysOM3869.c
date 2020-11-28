/**
Copyright (C) 2008 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmsysOM3869_63.c
*                %version: 10 %
*
* \date          %date_modified%
*
* \brief         Describe briefly the purpose of this file.
*
* REFERENCE DOCUMENTS :
*
* Detailed description may be added here.
*
* \section info Change Information
*
* \verbatim
Date          Modified by CRPRNr  TASKNr  Maintenance description
-------------|-----------|-------|-------|-----------------------------------
9-JULY-2007  | A.TANT    |       |       | CREATION OF TDA10048 ARCHITECTURE 2.0.0
-------------|-----------|-------|-------|-----------------------------------
|           |       |       |
-------------|-----------|-------|-------|-----------------------------------
\endverbatim
*
*/


/*============================================================================*/
/*                   STANDARD INCLUDE FILES                                   */
/*============================================================================*/


/*============================================================================*/
/*                   PROJECT INCLUDE FILES                                    */
/*============================================================================*/
#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#include "tmsysFrontEndTypes.h"
#include "tmUnitParams.h"

#include "tmbslNT220HN.h"
#include "tmddNT220x.h"

#include "tmsysOM3869.h"
#include "tmsysOM3869local.h"
#include "tmsysOM3869Instance.h"

/*============================================================================*/
/*                   MACRO DEFINITION                                         */
/*============================================================================*/

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(ar)        (sizeof(ar)/sizeof((ar)[0]))
#endif // !defined(SIZEOF_ARRAY)

/*============================================================================*/
/*                   TYPE DEFINITION                                          */
/*============================================================================*/



/*============================================================================*/
/*                   PUBLIC VARIABLES DEFINITION                              */
/*============================================================================*/

/*============================================================================*/
/*                   STATIC VARIABLES DECLARATIONS                            */
/*============================================================================*/

/*============================================================================*/
/*                       EXTERN FUNCTION PROTOTYPES                           */
/*============================================================================*/


/*============================================================================*/
/*                   STATIC FUNCTIONS DECLARATIONS                            */
/*============================================================================*/


/*============================================================================*/
/*                   PUBLIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/



/*============================================================================*/
/*                   PROJECT INCLUDE FILES                                    */
/*============================================================================*/


/*============================================================================*/
/*                   TYPE DEFINITION                                          */
/*============================================================================*/


/*============================================================================*/
/*                   STATIC VARIABLES DECLARATIONS                            */
/*============================================================================*/


/*============================================================================*/
/*                   PUBLIC FUNCTIONS DECLARATIONS                            */
/*============================================================================*/



/*============================================================================*/
/*                   STATIC FUNCTIONS DECLARATIONS                            */
/*============================================================================*/

/*============================================================================*/
/*                   PUBLIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/


/*============================================================================*/
/*============================================================================*/
/* tmsysOM3869GetSWVersion                                                 */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetSWVersion
(
    ptmsysSWVersion_t   pSWVersion  /* O: Receives SW Version  */
)
{
    tmErrorCode_t   err = TM_OK;
    static char     OM3869Name[] = "tmsysOM3869\0";
    static char     NT220xName[] = "tmbslNT220x\0";

    pSWVersion->arrayItemsNumber = 2;
    pSWVersion->swVersionArray[0].pName = (char *)OM3869Name;
    pSWVersion->swVersionArray[0].nameBufSize = sizeof(OM3869Name);
    
    pSWVersion->swVersionArray[0].swVersion.compatibilityNr = OM3869_SYS_COMP_NUM;
    pSWVersion->swVersionArray[0].swVersion.majorVersionNr = OM3869_SYS_MAJOR_VER;
    pSWVersion->swVersionArray[0].swVersion.minorVersionNr = OM3869_SYS_MINOR_VER;
    
    pSWVersion->swVersionArray[1].pName = (char *)NT220xName;
    pSWVersion->swVersionArray[1].nameBufSize = sizeof(NT220xName);
    err = tmbslNT220xGetSWVersion(&pSWVersion->swVersionArray[1].swVersion);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xGetSWVersion failed."));

    return err;
}

/*============================================================================*/
/* tmsysOM3869Init                                                         */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869Init
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    // pObj initialization
    err = OM3869GetInstance(tUnit, &pObj);

    /* check driver state */
    if (err == TM_OK || err == OM3869_ERR_NOT_INITIALIZED)
    {
        if (pObj != Null && pObj->init == True)
        {
            err = OM3869_ERR_NOT_INITIALIZED;
        }
        else 
        {
            /* initialize the Object */
            if (pObj == Null)
            {
                err = OM3869AllocInstance(tUnit, &pObj);
                if (err != TM_OK || pObj == Null)
                {
                    err = OM3869_ERR_NOT_INITIALIZED;        
                }
            }

            if (err == TM_OK)
            {
                // initialize the Object by default values
                pObj->sRWFunc = psSrvFunc->sIo;
                pObj->sTime = psSrvFunc->sTime;
                pObj->sDebug = psSrvFunc->sDebug;

                if(  psSrvFunc->sMutex.Init != Null
                    && psSrvFunc->sMutex.DeInit != Null
                    && psSrvFunc->sMutex.Acquire != Null
                    && psSrvFunc->sMutex.Release != Null)
                {
                    pObj->sMutex = psSrvFunc->sMutex;

                    err = pObj->sMutex.Init(&pObj->pMutex);
                }

                pObj->tUnitNT220x = GET_INDEX_TUNIT(tUnit)|UNIT_PATH_TYPE_VAL(tmOM3869UnitDeviceTypeNT220x);

                pObj->init = True;
                err = TM_OK;

                err = OM3869Init(tUnit);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869Init(0x%08X) failed.", tUnit));
           }
        }
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869DeInit                                                          */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869DeInit
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    /************************************************************************/
    /* DeInitialize NT220x low layer setup                                */
    /************************************************************************/
    if(err == TM_OK)
    {
        if(pObj->sMutex.DeInit != Null)
        {
            if(pObj->pMutex != Null)
            {
                err = pObj->sMutex.DeInit(pObj->pMutex);
            }

            pObj->sMutex.Init = Null;
            pObj->sMutex.DeInit = Null;
            pObj->sMutex.Acquire = Null;
            pObj->sMutex.Release = Null;

            pObj->pMutex = Null;
        }
        
        err = tmbslNT220xDeInit(pObj->tUnitNT220x);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xDeInit(0x%08X) failed.", pObj->tUnitNT220x));
    }

 
    err = OM3869DeAllocInstance(tUnit);

    return err;
}

/*============================================================================*/
/* tmsysOM3869Reset                                                        */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869Reset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = OM3869_ERR_NOT_INITIALIZED;

    /* check input parameters */
    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        err = OM3869Reset(tUnit);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869Reset(0x%08X) failed.", tUnit));

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SetPowerState                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    tmPowerState_t  ePowerState /* I: Power state of the device */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(ePowerState)
        {
        case tmPowerOn:
            if (err == TM_OK)
            {
                pObj->powerState = ePowerState;

                /* Set NT220x power state to Normal Mode */
                err = tmbslNT220xSetPowerState(pObj->tUnitNT220x, tmNT220x_PowerNormalMode);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xSetPowerState(0x%08X, tmPowerOn) failed.", pObj->tUnitNT220x));
            }
            break;

        case tmPowerStandby:
            if (err == TM_OK)
            {
                pObj->powerState = ePowerState;

                /* Set NT220x power state to standby with Xtal and Loop Through*/
                err = tmbslNT220xSetPowerState(pObj->tUnitNT220x, tmNT220x_PowerStandbyWithLNAOnAndWithXtalOn);
                tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xSetPowerState(0x%08X, tmPowerStandby) failed.", pObj->tUnitNT220x));
            }
            break;

        case tmPowerSuspend:
        case tmPowerOff:
        default:
            err = OM3869_ERR_NOT_SUPPORTED;
            break;
        }

        if (err == TM_OK)
        {
            pObj->lastTuneReqType = TRT_UNKNOWN;
        }

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SetPowerState                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetPowerState
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    ptmPowerState_t pPowerState /* O: Power state of the device */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        *pPowerState = pObj->powerState;

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SendRequest                                                  */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SendRequest
(
    tmUnitSelect_t  tUnit,              /* I: FrontEnd unit number */
    pVoid           pTuneRequest,       /* I/O: Tune Request Structure pointer */
    UInt32          dwTuneRequestSize,  /* I: Tune Request Structure size */
    tmTuneReqType_t tTuneReqType        /* I: Tune Request Type */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;

    if(err == TM_OK)
    {
        err = OM3869GetInstance(tUnit, &pObj);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));
    }

    // check pointer
    if( !pTuneRequest )
    {
        tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Invalid Pointer!");
        err = OM3869_ERR_BAD_PARAMETER;
    }

    //if(err == TM_OK  && !pObj->resetDone)
    //{
    //    err = OM3869_ERR_NOT_INITIALIZED;
    //}

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        switch(tTuneReqType)
        {
        case TRT_TUNER_ONLY:
            if( dwTuneRequestSize != sizeof(tmTunerOnlyRequest_t) )
            {
                tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Bad parameter");
                err = OM3869_ERR_BAD_PARAMETER;
            }
            else
            {
                if (err == TM_OK)
                {
                    ptmTunerOnlyRequest_t pTunerOnlyRequest = (ptmTunerOnlyRequest_t)(pTuneRequest);

                    err = OM3869SetFrequency(tUnit, pTunerOnlyRequest);
                    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "Error: OM3869SetFrequency failed"));
                }
            }
            break;

        default:
            tmDBGPRINTEx(DEBUGLVL_ERROR, "Error: Unsupported tune request");
            err = OM3869_ERR_NOT_SUPPORTED;
            break;
        }

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SetI2CSwitchState                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,  /* I: FrontEnd unit number */
    tmsysFrontEndI2CSwitchState_t   eState  /* I: I2C switch state */
)
{
    return OM3869_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869GetI2CSwitchState                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetI2CSwitchState
(
    tmUnitSelect_t                  tUnit,
    tmsysFrontEndI2CSwitchState_t*  peState,
    UInt32*                         puI2CSwitchCounter
)
{
    return OM3869_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869GetLockStatus                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetLockStatus
(
    tmUnitSelect_t          tUnit,      /* I: FrontEnd unit number */
    tmsysFrontEndState_t*   pLockStatus /* O: Lock status */
)
{
    ptmOM3869Object_t    pObj = Null;
    tmErrorCode_t           err = TM_OK;
    tmbslFrontEndState_t    lockStatus = tmbslFrontEndStateUnknown;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        /* Get NT220x PLL Lock status */
        err = tmbslNT220xGetLockStatus(pObj->tUnitNT220x, &lockStatus);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xGetLockStatus(0x%08X) failed.", pObj->tUnitNT220x));

        if(err == TM_OK)
        {
           *pLockStatus = (tmsysFrontEndState_t)lockStatus;
        }

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869GetSignalStrength                                               */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetSignalStrength
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pStrength  /* I/O: Signal Strength pointer */
)
{
    return OM3869_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869GetSignalQuality                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetSignalQuality
(
    tmUnitSelect_t  tUnit,      /* I: FrontEnd unit number */
    UInt32          *pQuality   /* I/O: Signal Quality pointer */
)
{
   return OM3869_ERR_NOT_SUPPORTED;
}

/*============================================================================*/
/* tmsysOM3869GetDeviceUnit                                                */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869GetDeviceUnit
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3869UnitDeviceType_t deviceType, /* I: Device Type  */
    ptmUnitSelect_t             ptUnit      /* O: Device unit number */
)
{
    ptmOM3869Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(ptUnit!=Null)
        {
            switch(deviceType)
            {
            default:
            case tmOM3869UnitDeviceTypeUnknown:
                err = OM3869_ERR_BAD_PARAMETER;
                break;

            case tmOM3869UnitDeviceTypeNT220x:
                *ptUnit = pObj->tUnitNT220x;
                break;
            }
        }
        
        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869SetHwAddress                                                    */
/*============================================================================*/
tmErrorCode_t
tmsysOM3869SetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3869UnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32                      uHwAddress  /* I: Hardware Address */
)
{
    ptmOM3869Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(deviceType>tmOM3869UnitDeviceTypeUnknown && deviceType<tmOM3869UnitDeviceTypeMax)
        {
            pObj->uHwAddress[deviceType] = uHwAddress;
        }
        else
        {
            err = OM3869_ERR_BAD_PARAMETER;
        }

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/* tmsysOM3869GetHwAddress                                                    */
/*============================================================================*/
extern tmErrorCode_t
tmsysOM3869GetHwAddress
(
    tmUnitSelect_t              tUnit,      /* I: FrontEnd unit number */
    tmOM3869UnitDeviceType_t    deviceType, /* I: Device Type  */
    UInt32*                     puHwAddress /* O: Hardware Address */
)
{
    ptmOM3869Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    /* Check incoming pointer */
    if(err == TM_OK && !puHwAddress)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE,("Error: Invalid Pointer!"));
        err = OM3869_ERR_BAD_PARAMETER;
    }

    if(err == TM_OK)
    {
        err = OM3869MutexAcquire(pObj, OM3869_MUTEX_TIMEOUT);
    }

    if(err == TM_OK)
    {
        if(deviceType>tmOM3869UnitDeviceTypeUnknown && deviceType<tmOM3869UnitDeviceTypeMax)
        {
            *puHwAddress = pObj->uHwAddress[deviceType];
        }
        else
        {
            err = OM3869_ERR_BAD_PARAMETER;
        }

        (void)OM3869MutexRelease(pObj);
    }

    return err;
}

/*============================================================================*/
/*                   STATIC FUNCTIONS DEFINITIONS                             */
/*============================================================================*/

/*============================================================================*/
/* OM3869Init                                                                 */
/*============================================================================*/
static tmErrorCode_t
OM3869Init
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869Object_t        pObj = Null;
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndDependency_t   sSrvFunc;   /* setup parameters */

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        /* Fill function pointers structure */
        sSrvFunc.sIo                    = pObj->sRWFunc;
        sSrvFunc.sTime                  = pObj->sTime;
        sSrvFunc.sDebug                 = pObj->sDebug;
        sSrvFunc.sMutex                 = pObj->sMutex;
        sSrvFunc.dwAdditionalDataSize   = 0;
        sSrvFunc.pAdditionalData        = Null;

        /************************************************************************/
        /* NT220x low layer setup                                             */
        /************************************************************************/

        err = tmbslNT220xInit(pObj->tUnitNT220x, &sSrvFunc);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xInit(0x%08X) failed.", pObj->tUnitNT220x));
    }

    return err;
}

/*============================================================================*/
/* OM3869DeInit                                                               */
/*============================================================================*/
static tmErrorCode_t
OM3869DeInit
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));
 
    if(err == TM_OK)
    {
        err = tmbslNT220xDeInit(pObj->tUnitNT220x);
        tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xDeInit(0x%08X) failed.", pObj->tUnitNT220x));
    }

    return err;
}

/*============================================================================*/
/* OM3869Reset                                                                */
/*============================================================================*/
static tmErrorCode_t
OM3869Reset
(
    tmUnitSelect_t  tUnit   /* I: FrontEnd unit number */
)
{
    ptmOM3869Object_t   pObj = Null;
    tmErrorCode_t       err = TM_OK;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        err = tmsysOM3869SetPowerState(pObj->tUnit, tmPowerStandby);
    }

    if(err == TM_OK)
    {
        pObj->resetDone = False;

        /************************************************************************/
        /* NT220x initialization                                              */
        /************************************************************************/
        /* Determine if we need to wait in Reset function */
        err = tmbslNT220xSetIRQWait(pObj->tUnitNT220x, True);

        if(err == TM_OK)
        {
            err = tmbslNT220xSetPowerState(pObj->tUnitNT220x, tmNT220x_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xSetPowerState(0x%08X, tmPowerOn) failed.", pObj->tUnitNT220x));
        }

        if(err == TM_OK)
        {
            err = tmbslNT220xReset(pObj->tUnitNT220x);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xReset(0x%08X) failed.", pObj->tUnitNT220x));
        }
        if (err == TM_OK)
        {
            err = tmbslNT220xSetPowerState(pObj->tUnitNT220x, tmNT220x_PowerStandbyWithLNAOnAndWithXtalOn);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xSetPowerState(0x%08X, tmPowerStandby) failed.", pObj->tUnitNT220x));
        }

        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslNT220xReset(0x%08X) failed.", pObj->tUnitNT220x);
            /* Open I²C switch to stop Tuner access */
            (void)tmsysOM3869SetI2CSwitchState(pObj->tUnit, tmsysFrontEndI2CSwitchStateReset);
        }
    }
    return err;
}

/*============================================================================*/
/* OM3869SetFrequency                                                         */
/*============================================================================*/
static tmErrorCode_t
OM3869SetFrequency
(
    tmUnitSelect_t          tUnit,          /* I: FrontEnd unit number */
    ptmTunerOnlyRequest_t   pTuneRequest    /* I/O: Tuner Tune Request Structure pointer */
)
{
    ptmOM3869Object_t           pObj = Null;
    tmErrorCode_t               err = TM_OK;
    tmbslFrontEndState_t        eTunerPLLLock = tmbslFrontEndStateUnknown;

    err = OM3869GetInstance(tUnit, &pObj);
    tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "OM3869GetInstance(0x%08X) failed.", tUnit));

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "\n\n===========================================================================");
        tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3869SetFrequency(0x%08X) is called with following parameters:", pObj->tUnit);
        tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
        tmDBGPRINTEx(DEBUGLVL_TERSE, "     Frequency:           %d Hz", pTuneRequest->dwFrequency);
        tmDBGPRINTEx(DEBUGLVL_TERSE, "     Standard:            %d",    pTuneRequest->dwStandard);
        tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
    }

    if(err == TM_OK && pObj->lastTuneReqType != TRT_TUNER_ONLY)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE,("Configuring Tuner!"));

        if(err == TM_OK)
        {
            err = tmbslNT220xSetPowerState(pObj->tUnitNT220x, tmNT220x_PowerNormalMode);
            tmASSERTExT(err, TM_OK, (DEBUGLVL_ERROR, "tmbslNT220xSetPowerState(0x%08X, PowerOn) failed.", pObj->tUnitNT220x));
        }

        if(err == TM_OK)
        {
            pObj->powerState = tmPowerOn;
            pObj->lastTuneReqType = TRT_TUNER_ONLY;
        }
    }

    /************************************************************************/
    /* Program Tuner                                                        */
    /************************************************************************/

    if(err == TM_OK)
    {
        /* Set Tuner Standard mode */
        err = tmbslNT220xSetStandardMode(pObj->tUnitNT220x, pTuneRequest->dwStandard);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslNT220xSetStandardMode(0x%08X, %d) failed.", pObj->tUnitNT220x, pTuneRequest->dwStandard);
        }
    }

    if(err == TM_OK)
    {
        /* Set Tuner RF */
        err = tmbslNT220xSetRf(pObj->tUnitNT220x, pTuneRequest->dwFrequency);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslNT220xSetRf(0x%08X, %d) failed.", pObj->tUnitNT220x, pTuneRequest->dwFrequency);
        }
    }
    
    if(err == TM_OK)
    {
        /* Get Tuner PLL Lock status */
        err = tmbslNT220xGetLockStatus(pObj->tUnitNT220x, &eTunerPLLLock);
        if (err != TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "tmbslNT220xGetLockStatus(0x%08X) failed.", pObj->tUnitNT220x);
        }
    }

    if(err == TM_OK)
    {
        tmDBGPRINTEx(DEBUGLVL_TERSE, "NT220x(0x%08X) PLL Lock:%d.", pObj->tUnitNT220x, eTunerPLLLock);
    }
    if(err == TM_OK)
    {
        pTuneRequest->eTunerLock = (tmsysFrontEndState_t)eTunerPLLLock;
    }

    /* Print the result of the Manager function */
    switch(eTunerPLLLock)
    {
    case tmbslFrontEndStateLocked:
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner 0x%08X LOCKED.", pObj->tUnit);
        }
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
            tmDBGPRINTEx(DEBUGLVL_TERSE, " OM3869SetFrequency(0x%08X) found following parameters:", pObj->tUnit);
            tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
            tmDBGPRINTEx(DEBUGLVL_TERSE, "     Frequency:      %d Hz", pTuneRequest->dwFrequency);
            tmDBGPRINTEx(DEBUGLVL_TERSE, "===========================================================================");
        }

        break;

    case tmbslFrontEndStateNotLocked:
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_TERSE, "Tuner 0x%08X NOT LOCKED.", pObj->tUnit);
        }
        break;

    case tmbslFrontEndStateSearching:
    default:
        if(err == TM_OK)
        {
            tmDBGPRINTEx(DEBUGLVL_ERROR, "Tuner 0x%08X TIMEOUT.", pObj->tUnit);
        }
        break;
    }

    return err;
}

/*============================================================================*/
/* OM3869MutexAcquire                                                      */
/*============================================================================*/
extern tmErrorCode_t
OM3869MutexAcquire
(
    ptmOM3869Object_t    pObj,
    UInt32                  timeOut
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Acquire != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Acquire(pObj->pMutex, timeOut);
    }

    return err;
}

/*============================================================================*/
/* OM3869MutexRelease                                                      */
/*============================================================================*/
extern tmErrorCode_t
OM3869MutexRelease
(
    ptmOM3869Object_t    pObj
)
{
    tmErrorCode_t   err = TM_OK;

    if(pObj->sMutex.Release != Null && pObj->pMutex != Null)
    {
        err = pObj->sMutex.Release(pObj->pMutex);
    }

    return err;
}

