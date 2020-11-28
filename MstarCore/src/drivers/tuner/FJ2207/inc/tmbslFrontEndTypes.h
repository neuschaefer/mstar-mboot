/**
  Copyright (C) 2007 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslFrontEndTypes.h
 *                %version: CFR_STB#1.9 %
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
    27-Mar-2008 | B.GUILLOT | 13122 | 23472 | Integrate with tmbslDvbtIp.
   -------------|-----------|-------|-------|-----------------------------------
   \endverbatim
 *
*/

#include <stdarg.h>
#ifndef TMBSLFRONTENDTYPES_H
#define TMBSLFRONTENDTYPES_H

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif



/*============================================================================*/
/*                       MACRO DEFINITION                                     */
/*============================================================================*/



/*============================================================================*/
/*                       ENUM OR TYPE DEFINITION                              */
/*============================================================================*/

    
/* Status of the carrier phase lock loop */
typedef enum _tmbslFrontEndState_t
{
    /** status Unknown */
    tmbslFrontEndStateUnknown = 0,
    /** Channel locked*/
    tmbslFrontEndStateLocked,
    /** Channel not locked */
    tmbslFrontEndStateNotLocked,
    /** Channel lock in process */
    tmbslFrontEndStateSearching,
    tmbslFrontEndStateMax
} tmbslFrontEndState_t, *ptmbslFrontEndState_t;


/* Gpio config */
typedef enum _tmbslFrontEndGpioConfig_t
{
    tmbslFrontEndGpioConfUnknown = 0,
    tmbslFrontEndGpioConfInput,
    tmbslFrontEndGpioConfOutputPushPull,
    tmbslFrontEndGpioConfOutputOpenDrain,
    tmbslFrontEndGpioConfTriState,
    tmbslFrontEndGpioConfMax
} tmbslFrontEndGpioConfig_t, *ptmbslFrontEndGpioConfig_t;

/* Gpio polarity */
typedef enum _tmbslFrontEndGpioPolarity_t
{
    tmbslFrontEndGpioPolUnknown = 0,
    tmbslFrontEndGpioPolNotInverted,
    tmbslFrontEndGpioPolInverted,
    tmbslFrontEndGpioPolMax
} tmbslFrontEndGpioPolarity_t, *ptmbslFrontEndGpioPolarity_t;

/* IT Selection */
typedef enum _tmbslFrontEndITSel_t
{
    tmbslFrontEndITSelUnknown = 0,
    tmbslFrontEndITSelFELGoesUp,
    tmbslFrontEndITSelFELGoesDown,
    tmbslFrontEndITSelDVBSynchroFlag,
    tmbslFrontEndITSelVBERRefreshed,
    tmbslFrontEndITSelBERRefreshed,
    tmbslFrontEndITSelUncor,
    tmbslFrontEndGpioITSelMax
} tmbslFrontEndITSel_t, *ptmbslFrontEndITSel_t;

/* I2C switch */
typedef enum _tmbslFrontEndI2CSwitchState_t
{
    tmbslFrontEndI2CSwitchStateUnknown = 0,
    tmbslFrontEndI2CSwitchStateOpen,
    tmbslFrontEndI2CSwitchStateClosed,
    tmbslFrontEndI2CSwitchStateReset,
    tmbslFrontEndI2CSwitchStateMax
} tmbslFrontEndI2CSwitchState_t, *ptmbslFrontEndI2CSwitchState_t;

/* DVBT2 PLP */
typedef struct _tmbslFrontEndDVBT2PLP_t
{
    UInt32 uId;
    UInt32 uGroupId;
    tmFrontEndDVBT2PLPType_t eType;
    tmFrontEndDVBT2PLPPayloadType_t ePayloadType;
    tmFrontEndCodeRate_t eCodeRate;
    tmFrontEndModulation_t eModulation;
    tmFrontEndRotationState eRotation;
    tmFrontEndDVBT2FECType_t eFECType;
} tmbslFrontEndDVBT2PLP_t;

/******************************************************************************/
/** \brief "Function pointers to hardware access services"
 *
 ******************************************************************************/
typedef struct _tmbslFrontEndIoFunc_t
{
    /** Read hardware function */
    tmErrorCode_t   (*Read)(tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr, UInt32 ReadLen, UInt8* pData);
    /** Write hardware register, 8bit aligned function */
    tmErrorCode_t   (*Write)(tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr, UInt32 WriteLen, UInt8* pData);
} tmbslFrontEndIoFunc_t, *ptmbslFrontEndIoFunc_t;


/******************************************************************************/
/** \brief "Function pointers to Time services"
 *
 ******************************************************************************/
typedef struct _tmbslFrontEndTimeFunc_t
{
    /** Return current time value in ms */
    tmErrorCode_t   (*Get)(UInt32 *ptms); 
    /**  Wait t ms without blocking scheduler; warning this function 
     don't schedule others frontend instance */
    tmErrorCode_t   (*Wait)(tmUnitSelect_t tUnit, UInt32 tms);
} tmbslFrontEndTimeFunc_t, *ptmbslFrontEndTimeFunc_t;
   

/******************************************************************************/
/** \brief "Function pointers to Debug services "
 *
 ******************************************************************************/
typedef struct _tmbslFrontEndDebugFunc_t
{
    /** Print a debug message */
    tmErrorCode_t   (*Print)(UInt32 level, const char* ,tmUnitSelect_t tUnit);//format, ...);
} tmbslFrontEndDebugFunc_t, *ptmbslFrontEndDebugFunc_t;

/* Mutex types */
typedef void *ptmbslFrontEndMutexHandle;
#define TMBSL_FRONTEND_MUTEX_TIMEOUT_INFINITE		(0xFFFFFFFF)

/******************************************************************************/
/** \brief "Function pointers to Mutex services "
 *
 ******************************************************************************/
typedef struct _tmbslFrontEndMutexFunc_t
{
    /* Initialize a mutex object */
    tmErrorCode_t   (*Init)(ptmbslFrontEndMutexHandle *ppMutexHandle);
    /* Deinitialize a mutex object */
    tmErrorCode_t   (*DeInit)(ptmbslFrontEndMutexHandle pMutexHandle);
    /* Acquire a mutex object */
    tmErrorCode_t   (*Acquire)(ptmbslFrontEndMutexHandle pMutexHandle, UInt32 timeOut);
    /* Release a mutex object */
    tmErrorCode_t   (*Release)(ptmbslFrontEndMutexHandle pMutexHandle);
} tmbslFrontEndMutexFunc_t, *ptmbslFrontEndMutexFunc_t;

/******************************************************************************/
/** \brief "This structure contain all the bsl driver external dependencies"
 *
 *  \sa    "all bsl 'init' functions"
 *
 ******************************************************************************/
typedef struct _tmbslFrontEndDependency_t
{
    /** Hardware access to FrontEnd */
    tmbslFrontEndIoFunc_t       sIo;
    /** Time services (wait, getTime, ...) */
    tmbslFrontEndTimeFunc_t     sTime;
    /** Debug services (Print, Store, ...) */
    tmbslFrontEndDebugFunc_t    sDebug;
    /** Mutex services */
    tmbslFrontEndMutexFunc_t		sMutex;
    /** Device Parameters data size */
    UInt32                      dwAdditionalDataSize;
    /** Device Parameters data pointer */
    void*                       pAdditionalData;
} tmbslFrontEndDependency_t, *ptmbslFrontEndDependency_t;

/*============================================================================*/

typedef struct tmSWSettingsVersion
{
    UInt32      customerNr;         /* SW Settings customer number */
    UInt32      projectNr;          /* SW Settings project number */
    UInt32      majorVersionNr;     /* SW Settings major version number */
    UInt32      minorVersionNr;     /* SW Settings minor version number */

}   tmSWSettingsVersion_t, *ptmSWSettingsVersion_t;

/******************************************************************************/
/** \brief "These macros map to trace functions "
* P_DBGPRINTEx macro should be defined in each component
******************************************************************************/

#define DEBUGLVL_BLAB    3
#define DEBUGLVL_VERBOSE 2
#define DEBUGLVL_TERSE   1
#define DEBUGLVL_ERROR   0
//#define TMBSLFRONTEND_DEBUG_TRACE

#ifdef TMBSLFRONTEND_DEBUG_TRACE
#define tmDBGPRINTEx(_level, _format, _instance)                                                        \
{                                                                                                       \
    if(P_DBGPRINTVALID)                                                                                 \
    {                                                                                                   \
        if(_level == DEBUGLVL_ERROR)                                                                    \
        {                                                                                               \
            P_DBGPRINTEx(_level, "Error: In Function %s (Line %d):\n==> ", __LINE__ );				    \
        }                                                                                               \
        P_DBGPRINTEx(_level, _format, _instance);                                                       \
    }                                                                                                   \
}
#else
#define tmDBGPRINTEx(_level, _format, ...)
//#define tmDBGPRINTEx(_level, _format, __VA_ARGS__) //alex 2009Aug21 , __FUNCTION__
#endif

#define tmASSERTExTR(_retVar, _expr, _strings)                                                      \
{                                                                                                   \
    if((_retVar) != (_expr))                                                                        \
    {                                                                                               \
        tmDBGPRINTEx _strings ;                                                                     \
        return _retVar;                                                                             \
    }                                                                                               \
}

#define tmASSERTExT(_retVar, _expr, _strings)                                                       \
{                                                                                                   \
    if((_retVar) != (_expr))                                                                        \
    {                                                                                               \
        tmDBGPRINTEx _strings ;                                                                     \
    }                                                                                               \
}

/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* TMBSLFRONTENDTYPES_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

