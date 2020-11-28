/*
  Copyright (C) 2012 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18275_Instance.c
 *
 * \date          %modify_time%
 *
 * \author        Michael VANNIER
 *                
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18275_Driver_User_Guide.pdf
 *
 *
 * \section info Change Information
 *
*/

/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"
#include "tmUnitParams.h"

/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#include "tmbslTDA18275.h"

#include "tmbslTDA18275_RegDef.h"
#include "tmbslTDA18275_Local.h"
#include "tmbslTDA18275_Instance.h"
#include "tmbslTDA18275_InstanceCustom.h"


/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

/* Driver instance */
TDA18275Object_t gTDA18275Instance[TDA18275_UNITS] = 
{
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA18275_INSTANCE_CUSTOM_0         /* Instance Customizable Settings */
        TDA18275_INSTANCE_REGMAP_DEF
    },
#if TDA18275_UNITS >= 2
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA18275_INSTANCE_CUSTOM_1          /* Instance Customizable Settings */
        TDA18275_INSTANCE_REGMAP_DEF
    },
#endif
#if TDA18275_UNITS >= 3
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA18275_INSTANCE_CUSTOM_2          /* Instance Customizable Settings */
        TDA18275_INSTANCE_REGMAP_DEF
    },
#endif
#if TDA18275_UNITS >= 4
    {
        (tmUnitSelect_t)(-1),               /* Unit not set */
        (tmUnitSelect_t)(-1),               /* UnitW not set */
        Null,                               /* pMutex */
        False,                              /* init (instance initialization default) */
        {                                   /* sIo */
            Null,
            Null
        },
        {                                   /* sTime */
            Null,
            Null
        },
        {                                   /* sDebug */
            Null
        },
        {                                   /* sMutex */
            Null,
            Null,
            Null,
            Null
        },
        TDA18275_INSTANCE_CUSTOM_3          /* Instance Customizable Settings */
        TDA18275_INSTANCE_REGMAP_DEF
    }
#endif
};

/*============================================================================*/
/* Internal functions:                                                        */
/*============================================================================*/

/*============================================================================*/
/* FUNCTION:    iTDA18275_AllocInstance:                                      */
/*                                                                            */
/* DESCRIPTION: Allocates an instance.                                        */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18275_AllocInstance(
    tmUnitSelect_t      tUnit,      /* I: Unit number */
    ppTDA18275Object_t  ppDrvObject /* I: Driver Object */
)
{
    tmErrorCode_t       err = TDA18275_ERR_ERR_NO_INSTANCES;
    pTDA18275Object_t   pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Find a free instance */
    for (uLoopCounter = 0; uLoopCounter<TDA18275_UNITS; uLoopCounter++)
    {
        pObj = &gTDA18275Instance[uLoopCounter];
        if (pObj->init == False)
        {
            err = TM_OK;

            pObj->tUnit = tUnit;
            pObj->tUnitW = tUnit;

            err = iTDA18275_ResetInstance(pObj);

            if(err == TM_OK)
            {
                *ppDrvObject = pObj;
            }
            break;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18275_DeAllocInstance:                                    */
/*                                                                            */
/* DESCRIPTION: Deallocates an instance.                                      */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18275_DeAllocInstance(
    pTDA18275Object_t  pDrvObject  /* I: Driver Object */
)
{
    tmErrorCode_t   err = TM_OK;

    if(pDrvObject != Null)
    {
        pDrvObject->init = False;
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18275_GetInstance:                                        */
/*                                                                            */
/* DESCRIPTION: Gets an instance.                                             */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18275_GetInstance(
    tmUnitSelect_t      tUnit,      /* I: Unit number   */
    ppTDA18275Object_t  ppDrvObject /* I: Driver Object */
)
{
    tmErrorCode_t       err = TDA18275_ERR_ERR_NO_INSTANCES;
    pTDA18275Object_t   pObj = Null;
    UInt32              uLoopCounter = 0;

    /* Get instance */
    for (uLoopCounter = 0; uLoopCounter<TDA18275_UNITS; uLoopCounter++)
    {
        pObj = &gTDA18275Instance[uLoopCounter];
        if (pObj->init == True && pObj->tUnit == GET_INDEX_TYPE_TUNIT(tUnit))
        {
            pObj->tUnitW = tUnit;

            *ppDrvObject = pObj;
            err = TM_OK;
            break;
        }
    }

    return err;
}

/*============================================================================*/
/* FUNCTION:    iTDA18275_ResetInstance:                                      */
/*                                                                            */
/* DESCRIPTION: Resets an instance.                                           */
/*                                                                            */
/* RETURN:      TM_OK if no error                                             */
/*                                                                            */
/* NOTES:                                                                     */
/*============================================================================*/
tmErrorCode_t
iTDA18275_ResetInstance(
    pTDA18275Object_t  pDrvObject  /* I: Driver Object */
)
{
    tmErrorCode_t   err = TM_OK ;

    pDrvObject->curPowerState = TDA18275_INSTANCE_CUSTOM_CURPOWERSTATE_DEF;
    pDrvObject->curLLPowerState = TDA18275_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF;
    pDrvObject->uRF = TDA18275_INSTANCE_CUSTOM_RF_DEF;
    pDrvObject->uLO = TDA18275_INSTANCE_CUSTOM_LO_DEF;

    pDrvObject->StandardMode = TDA18275_INSTANCE_CUSTOM_STANDARDMODE_DEF;

    pDrvObject->eHwState = TDA18275_HwState_InitNotDone;

    return err;
}

