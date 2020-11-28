/*-----------------------------------------------------------------------------
// $Header:
// (C) Copyright 2008 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of NXP Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of NXP
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than NXP Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmddNT220xInstance.c
//
// DESCRIPTION:  define the static Objects
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:
//-----------------------------------------------------------------------------
*/

#include "../../inc/tmNxTypes.h"
#include "../../inc/tmCompId.h"
#include "../../inc/tmFrontEnd.h"
#include "../../inc/tmUnitParams.h"
#include "../../inc/tmbslFrontEndTypes.h"

#include "../inc/tmddNT220x.h"
#include "tmddNT220xlocal.h"

#include "tmddNT220xInstance.h"

/*-----------------------------------------------------------------------------
// Global data:
//-----------------------------------------------------------------------------
//
*/


/* default instance */
tmddNT220xObject_t gddNT220xInstance[] =
{
    {
        (tmUnitSelect_t)(-1),           /* Unit not set */
        (tmUnitSelect_t)(-1),           /* UnitW not set */
        Null,                           /* pMutex */
        False,                          /* init (instance initialization default) */
        {                               /* sRWFunc */
            Null,
            Null
        },
        {                               /* sTime */
            Null,
            Null
        },
        {                               /* sDebug */
            Null
        },
        {                               /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        tmddNT220x_PowerStandbyWithXtalOn,    /* curPowerState */
        tmddNT220x_Version_Not_Forced,        /* versionForced */
        True,                                   /* bIRQWait */
        False,                                  /* bSoftReset */
        False,                                  /* bRFCAL_SW_Algo_Enable */
        {                                       /* RFCAL_Prog */
            { 0, 0, 0 },
            { 1, 0, 0 },
            { 2, 0, 0 },
            { 3, 0, 0 },
            { 4, 0, 0 },
            { 5, 0, 0 },
            { 6, 0, 0 },
            { 7, 0, 0 },
            { 8, 0, 0 },
            { 9, 0, 0 },
            { 10, 0, 0 },
            { 11, 0, 0 }
        },
        {                                       /* RFCAL_Coeffs */
            { 0, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 2, 3, 0, 0 },
            { 3, 4, 0, 0 },
            { 4, 6, 0, 0 },
            { 5, 7, 0, 0 },
            { 6, 9, 0, 0 },
            { 7, 10, 0, 0 }
        },
        {
            0  /* I2CMap*/
        }
    },
    {
        (tmUnitSelect_t)(-1),           /* Unit not set */
        (tmUnitSelect_t)(-1),           /* UnitW not set */
        Null,                           /* pMutex */
        False,                          /* init (instance initialization default) */
        {                               /* sRWFunc */
            Null,
            Null
        },
        {                               /* sTime */
            Null,
            Null
        },
        {                               /* sDebug */
            Null
        },
        {                               /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        tmddNT220x_PowerStandbyWithXtalOn,    /* curPowerState */
        tmddNT220x_Version_Not_Forced,        /* versionForced */
        True,                                   /* bIRQWait */
        False,                                  /* bSoftReset */
        False,                                  /* bRFCAL_SW_Algo_Enable */
        {                                       /* RFCAL_Prog */
            { 0, 0, 0 },
            { 1, 0, 0 },
            { 2, 0, 0 },
            { 3, 0, 0 },
            { 4, 0, 0 },
            { 5, 0, 0 },
            { 6, 0, 0 },
            { 7, 0, 0 },
            { 8, 0, 0 },
            { 9, 0, 0 },
            { 10, 0, 0 },
            { 11, 0, 0 }
        },
        {                                       /* RFCAL_Coeffs */
            { 0, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 2, 3, 0, 0 },
            { 3, 4, 0, 0 },
            { 4, 6, 0, 0 },
            { 5, 7, 0, 0 },
            { 6, 9, 0, 0 },
            { 7, 10, 0, 0 }
        },
        {
            0  // I2CMap;
        }
    },
    {
        (tmUnitSelect_t)(-1),           /* Unit not set */
        (tmUnitSelect_t)(-1),           /* UnitW not set */
        Null,                           /* pMutex */
        False,                          /* init (instance initialization default) */
        {                               /* sRWFunc */
            Null,
            Null
        },
        {                               /* sTime */
            Null,
            Null
        },
        {                               /* sDebug */
            Null
        },
        {                               /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        tmddNT220x_PowerStandbyWithXtalOn,    /* curPowerState */
        tmddNT220x_Version_Not_Forced,        /* versionForced */
        True,                                   /* bIRQWait */
        False,                                  /* bSoftReset */
        False,                                  /* bRFCAL_SW_Algo_Enable */
        {                                       /* RFCAL_Prog */
            { 0, 0, 0 },
            { 1, 0, 0 },
            { 2, 0, 0 },
            { 3, 0, 0 },
            { 4, 0, 0 },
            { 5, 0, 0 },
            { 6, 0, 0 },
            { 7, 0, 0 },
            { 8, 0, 0 },
            { 9, 0, 0 },
            { 10, 0, 0 },
            { 11, 0, 0 }
        },
        {                                       /* RFCAL_Coeffs */
            { 0, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 2, 3, 0, 0 },
            { 3, 4, 0, 0 },
            { 4, 6, 0, 0 },
            { 5, 7, 0, 0 },
            { 6, 9, 0, 0 },
            { 7, 10, 0, 0 }
        },
        {
            0  // I2CMap;
        }
    },
    {
        (tmUnitSelect_t)(-1),           /* Unit not set */
        (tmUnitSelect_t)(-1),           /* UnitW not set */
        Null,                           /* pMutex */
        False,                          /* init (instance initialization default) */
        {                               /* sRWFunc */
            Null,
            Null
        },
        {                               /* sTime */
            Null,
            Null
        },
        {                               /* sDebug */
            Null
        },
        {                               /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        tmddNT220x_PowerStandbyWithXtalOn,    /* curPowerState */
        tmddNT220x_Version_Not_Forced,        /* versionForced */
        True,                                   /* bIRQWait */
        False,                                  /* bSoftReset */
        False,                                  /* bRFCAL_SW_Algo_Enable */
        {                                       /* RFCAL_Prog */
            { 0, 0, 0 },
            { 1, 0, 0 },
            { 2, 0, 0 },
            { 3, 0, 0 },
            { 4, 0, 0 },
            { 5, 0, 0 },
            { 6, 0, 0 },
            { 7, 0, 0 },
            { 8, 0, 0 },
            { 9, 0, 0 },
            { 10, 0, 0 },
            { 11, 0, 0 }
        },
        {                                       /* RFCAL_Coeffs */
            { 0, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 2, 3, 0, 0 },
            { 3, 4, 0, 0 },
            { 4, 6, 0, 0 },
            { 5, 7, 0, 0 },
            { 6, 9, 0, 0 },
            { 7, 10, 0, 0 }
        },
        {
            0  // I2CMap;
        }
    }
};

/*-----------------------------------------------------------------------------
// FUNCTION:    ddNT220xAllocInstance:
//
// DESCRIPTION: allocate new instance
//
// RETURN:
//
// NOTES:
//-----------------------------------------------------------------------------
*/
tmErrorCode_t
ddNT220xAllocInstance
(
 tmUnitSelect_t          tUnit,      /* I: Unit number */
 pptmddNT220xObject_t    ppDrvObject /* I: Device Object */
 )
{
    tmErrorCode_t       err = ddNT220x_ERR_BAD_UNIT_NUMBER;
    ptmddNT220xObject_t pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Find a free instance */
    for(uLoopCounter = 0; uLoopCounter<NT220x_MAX_UNITS; uLoopCounter++)
    {
        pObj = &gddNT220xInstance[uLoopCounter];
        if(pObj->init == False)
        {
            pObj->tUnit = tUnit;
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    /* return value */
    return err;
}

/*-----------------------------------------------------------------------------
// FUNCTION:    ddNT220xDeAllocInstance:
//
// DESCRIPTION: deallocate instance
//
// RETURN:      always TM_OK
//
// NOTES:
//-----------------------------------------------------------------------------
*/
tmErrorCode_t
ddNT220xDeAllocInstance
(
 tmUnitSelect_t  tUnit   /* I: Unit number */
 )
{
    tmErrorCode_t       err = ddNT220x_ERR_BAD_UNIT_NUMBER;
    ptmddNT220xObject_t pObj = Null;

    /* check input parameters */
    err = ddNT220xGetInstance(tUnit, &pObj);

    /* check driver state */
    if (err == TM_OK)
    {
        if (pObj == Null || pObj->init == False)
        {
            err = ddNT220x_ERR_NOT_INITIALIZED;
        }
    }

    if ((err == TM_OK) && (pObj != Null))
    {
        pObj->init = False;
    }

    /* return value */
    return err;
}

/*-----------------------------------------------------------------------------
// FUNCTION:    ddNT220xGetInstance:
//
// DESCRIPTION: get the instance
//
// RETURN:      always True
//
// NOTES:
//-----------------------------------------------------------------------------
*/
tmErrorCode_t
ddNT220xGetInstance
(
 tmUnitSelect_t          tUnit,      /* I: Unit number */
 pptmddNT220xObject_t    ppDrvObject /* I: Device Object */
 )
{
    tmErrorCode_t           err = ddNT220x_ERR_NOT_INITIALIZED;
    ptmddNT220xObject_t     pObj = Null;
    UInt32                  uLoopCounter = 0;

    /* get instance */
    for(uLoopCounter = 0; uLoopCounter<NT220x_MAX_UNITS; uLoopCounter++)
    {
        pObj = &gddNT220xInstance[uLoopCounter];
        if(pObj->init == True && pObj->tUnit == GET_INDEX_TYPE_TUNIT(tUnit))
        {
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    /* return value */
    return err;
}