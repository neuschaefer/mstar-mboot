/**
Copyright (C) 2008 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmbslNT220xlocal.h
*                %version: 7 %
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
|            |           |       |
-------------|-----------|-------|-------|-----------------------------------
|            |           |       |
-------------|-----------|-------|-------|-----------------------------------
\endverbatim
*
*/

#ifndef _TMBSL_NT220xLOCAL_H
#define _TMBSL_NT220xLOCAL_H

/*------------------------------------------------------------------------------*/
/* Standard include files:                                                      */
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/* Project include files:                                                       */
/*------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

/*------------------------------------------------------------------------------*/
/* Types and defines:                                                           */
/*------------------------------------------------------------------------------*/

#define NT220x_MUTEX_TIMEOUT  TMBSL_FRONTEND_MUTEX_TIMEOUT_INFINITE

#ifdef TMBSL_NT220HN
 #define TMBSL_NT220x_COMPONENT_NAME_STR "NT220HN"
#else /* TMBSL_NT220HN */
 #define TMBSL_NT220x_COMPONENT_NAME_STR "NT220DN"
#endif /* TMBSL_NT220HN */

#define _SYSTEMFUNC (pObj->SystemFunc)
#define POBJ_SRVFUNC_SIO pObj->sRWFunc
#define POBJ_SRVFUNC_STIME pObj->sTime
#define P_DBGPRINTEx pObj->sDebug.Print
#define P_DBGPRINTVALID ((pObj != Null) && (pObj->sDebug.Print != Null))


/*-------------*/
/* ERROR CODES */
/*-------------*/
//Alex 2009Sept16 - change to 4 in order to support 4 tuners for FJ2215 and FJ2216
//#define NT220x_MAX_UNITS                          2
#define NT220x_MAX_UNITS                          4

    typedef struct _tmNT220xObject_t
    {
        tmUnitSelect_t              tUnit;
        tmUnitSelect_t              tUnitW;
        ptmbslFrontEndMutexHandle   pMutex;
        Bool                        init;
        tmbslFrontEndIoFunc_t       sRWFunc;
        tmbslFrontEndTimeFunc_t     sTime;
        tmbslFrontEndDebugFunc_t    sDebug;
        tmbslFrontEndMutexFunc_t    sMutex;
        tmNT220xPowerState_t      curPowerState;
        UInt32                      uRF;
        tmNT220xStandardMode_t    StandardMode;
        tmNT220xStdCoefficients   Std_Array[tmNT220x_StandardMode_Max];
    } tmNT220xObject_t, *ptmNT220xObject_t, **pptmNT220xObject_t;



//static tmErrorCode_t NT220xInit(tmUnitSelect_t tUnit);
tmErrorCode_t NT220xInit(tmUnitSelect_t tUnit);
#if 0
static tmErrorCode_t NT220xWait(ptmNT220xObject_t pObj, UInt32 Time);
#endif

extern tmErrorCode_t NT220xMutexAcquire(ptmNT220xObject_t   pObj, UInt32 timeOut);
extern tmErrorCode_t NT220xMutexRelease(ptmNT220xObject_t   pObj);

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_NT220xLOCAL_H */
