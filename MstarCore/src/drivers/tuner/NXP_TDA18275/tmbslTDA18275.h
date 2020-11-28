/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18275.h
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

#ifndef _TMBSL_TDA18275_H
#define _TMBSL_TDA18275_H

#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* TDA18275 Error Codes                                                       */
/*============================================================================*/

#define TDA18275_ERR_BASE                       (CID_COMP_TUNER | CID_LAYER_BSL)
#define TDA18275_ERR_COMP                       (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define TDA18275_ERR_BAD_UNIT_NUMBER            (TDA18275_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define TDA18275_ERR_ERR_NO_INSTANCES           (TDA18275_ERR_BASE + TM_ERR_NO_INSTANCES)
#define TDA18275_ERR_NOT_INITIALIZED            (TDA18275_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define TDA18275_ERR_ALREADY_SETUP              (TDA18275_ERR_BASE + TM_ERR_ALREADY_SETUP)
#define TDA18275_ERR_INIT_FAILED                (TDA18275_ERR_BASE + TM_ERR_INIT_FAILED)
#define TDA18275_ERR_BAD_PARAMETER              (TDA18275_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define TDA18275_ERR_NOT_SUPPORTED              (TDA18275_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define TDA18275_ERR_NULL_CONTROLFUNC           (TDA18275_ERR_BASE + TM_ERR_NULL_CONTROLFUNC)
#define TDA18275_ERR_HW_FAILED                  (TDA18275_ERR_COMP + 0x0001)
#define TDA18275_ERR_NOT_READY                  (TDA18275_ERR_COMP + 0x0002)
#define TDA18275_ERR_BAD_VERSION                (TDA18275_ERR_COMP + 0x0003)
#define TDA18275_ERR_STD_NOT_SET                (TDA18275_ERR_COMP + 0x0004)
#define TDA18275_ERR_RF_NOT_SET                 (TDA18275_ERR_COMP + 0x0005)

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

typedef enum _TDA18275PowerState_t {
    TDA18275_PowerNormalMode = 0,                                 /* Device normal mode */
    TDA18275_PowerStandbyWithXtalOn,                              /* Device standby mode with Xtal Output */
    TDA18275_PowerStandby,                                        /* Device standby mode full( only I2C ) */
    TDA18275_PowerMax
} TDA18275PowerState_t, *pTDA18275PowerState_t;

typedef enum _TDA18275StandardMode_t {
    TDA18275_StandardMode_Unknown = 0,                  /* Unknown standard */
    TDA18275_QAM_6MHz,                                  /* Digital TV QAM 6MHz */
    TDA18275_QAM_8MHz,                                  /* Digital TV QAM 8MHz */
    TDA18275_ATSC_6MHz,                                 /* Digital TV ATSC 6MHz */
    TDA18275_ISDBT_6MHz,                                /* Digital TV ISDBT 6MHz */
    TDA18275_DVBT_1_7MHz,                               /* Digital TV DVB-T/T2 6MHz */
    TDA18275_DVBT_6MHz,                                 /* Digital TV DVB-T/T2 6MHz */
    TDA18275_DVBT_7MHz,                                 /* Digital TV DVB-T/T2 7MHz */
    TDA18275_DVBT_8MHz,                                 /* Digital TV DVB-T/T2 8MHz */
    TDA18275_DVBT_10MHz,                                /* Digital TV DVB-T/T2 10MHz */     
    TDA18275_DMBT_8MHz,                                 /* Digital TV DMB-T 8MHz */
    TDA18275_FM_Radio,                                  /* Analog FM Radio */
    TDA18275_ANLG_MN,                                   /* Analog TV M/N */
    TDA18275_ANLG_B,                                    /* Analog TV B */
    TDA18275_ANLG_GH,                                   /* Analog TV G/H */
    TDA18275_ANLG_I,                                    /* Analog TV I */
    TDA18275_ANLG_DK,                                   /* Analog TV D/K */
    TDA18275_ANLG_L,                                    /* Analog TV L */
    TDA18275_ANLG_LL,                                   /* Analog TV L' */
    TDA18275_StandardMode_Max
} TDA18275StandardMode_t, *pTDA18275StandardMode_t;


#define isTDA18275_DGTL_STD(_CURSTD) ( (((_CURSTD)>=TDA18275_QAM_6MHz) && ((_CURSTD)<=TDA18275_DMBT_8MHz)) || ((_CURSTD)==TDA18275_ScanXpress) )
#define isTDA18275_ANLG_STD(_CURSTD) ( ((_CURSTD)>=TDA18275_FM_Radio) && ((_CURSTD)<=TDA18275_Scanning) )


/* Register Bit-Field Definition */
typedef struct _TDA18275_BitField_t
{
    UInt8   Address;
    UInt8   PositionInBits;
    UInt8   WidthInBits;
    UInt8   Attributes;
}
TDA18275_BitField_t, *pTDA18275_BitField_t;

/*============================================================================*/
/* Exported functions:                                                        */
/*============================================================================*/

tmErrorCode_t
tmbslTDA18275_Open(
    tmUnitSelect_t              tUnit,      /*  I: Unit number */
    tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
);

tmErrorCode_t
tmbslTDA18275_Close(
    tmUnitSelect_t  tUnit   /*  I: Unit number */
);

tmErrorCode_t
tmbslTDA18275_GetSWVersion(
    ptmSWVersion_t  pSWVersion  /*  I: Receives SW Version */
);

tmErrorCode_t
tmbslTDA18275_GetSWSettingsVersion(
    ptmSWSettingsVersion_t pSWSettingsVersion   /* O: Receives SW Settings Version */
);

tmErrorCode_t
tmbslTDA18275_SetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t  powerState  /* I: Power state */
);

tmErrorCode_t
tmbslTDA18275_GetPowerState(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    tmPowerState_t* pPowerState /* O: Power state */
);

tmErrorCode_t
tmbslTDA18275_SetStandardMode(
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    TDA18275StandardMode_t    StandardMode    /*  I: Standard mode of this device */
);

tmErrorCode_t
tmbslTDA18275_GetStandardMode(
    tmUnitSelect_t              tUnit,          /*  I: Unit number */
    TDA18275StandardMode_t    *pStandardMode  /*  O: Standard mode of this device */
);

tmErrorCode_t
tmbslTDA18275_SetRF(
    tmUnitSelect_t  tUnit,  /*  I: Unit number */
    UInt32          uRF     /*  I: RF frequency in hertz */
);

tmErrorCode_t
tmbslTDA18275_GetRF(
    tmUnitSelect_t  tUnit,  /*  I: Unit number */
    UInt32*         pRF     /*  O: RF frequency in hertz */
);

tmErrorCode_t
tmbslTDA18275_HwInit(
    tmUnitSelect_t tUnit    /* I: Unit number */
);

tmErrorCode_t
tmbslTDA18275_GetIF(
    tmUnitSelect_t  tUnit,  /* I: Unit number */
    UInt32*         puIF    /* O: IF Frequency in hertz */
);

tmErrorCode_t
tmbslTDA18275_GetLockStatus(
    tmUnitSelect_t          tUnit,      /* I: Unit number */
    tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
);

tmErrorCode_t
tmbslTDA18275_SetGpio(
    tmUnitSelect_t          tUnit,           /* I: Unit number */
    UInt8                   bNumber,         /* I: Number of the GPIO to set */
    Bool                    bActive          /* I: GPIO enabled/disabled */
);

tmErrorCode_t
tmbslTDA18275_GetPowerLevel(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*          pPowerLevel /* O: Power Level in 1/2 steps dBµV */
);

tmErrorCode_t
tmbslTDA18275_GetThermo(
    tmUnitSelect_t  tUnit,      /* I: Unit number */
    UInt8*          pThermo /* O: temperature in °C */
);

/* You can only add one step (-1 or +1) at a time along -125 KHz <-> -62.5 KHz <-> 0 <-> 62.5 KHz <-> 125 KHz */
/* After calling tmbslTDA18275_SetRF, step is reset at 0 */
tmErrorCode_t
tmbslTDA18275_SetFineRF(
    tmUnitSelect_t tUnit,      /* I: Unit number */
    Int8           step        /* I: step (-1, +1) */
);

tmErrorCode_t
tmbslTDA18275_Write(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    const TDA18275_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8                       uData,      /* I: Data to write */
    tmbslFrontEndBusAccess_t    eBusAccess  /* I: Access to bus */
);

tmErrorCode_t
tmbslTDA18275_Read(
    tmUnitSelect_t              tUnit,      /* I: Unit number */
    const TDA18275_BitField_t*  pBitField,  /* I: Bitfield structure */
    UInt8*                      puData,     /* I: Data to read */
    tmbslFrontEndBusAccess_t    eBusAccess  /* I: Access to bus */
);

/*============================================================================*/
/* Legacy compatibility:                                                      */
/*============================================================================*/

#ifndef tmbslTDA18275Init
 #define tmbslTDA18275Init tmbslTDA18275_Open
#endif

#ifndef tmbslTDA18275DeInit
 #define tmbslTDA18275DeInit tmbslTDA18275_Close
#endif

#ifndef tmbslTDA18275GetSWVersion
 #define tmbslTDA18275GetSWVersion tmbslTDA18275_GetSWVersion
#endif

#ifndef tmbslTDA18275GetSWSettingsVersion
 #define tmbslTDA18275GetSWSettingsVersion tmbslTDA18275_GetSWSettingsVersion
#endif

#ifndef tmbslTDA18275CheckHWVersion
 #define tmbslTDA18275CheckHWVersion tmbslTDA18275_CheckHWVersion
#endif

#ifndef tmbslTDA18275SetPowerState
 #define tmbslTDA18275SetPowerState tmbslTDA18275_SetPowerState
#endif

#ifndef tmbslTDA18275GetPowerState
 #define tmbslTDA18275GetPowerState tmbslTDA18275_GetPowerState
#endif

#ifndef tmbslTDA18275SetStandardMode
 #define tmbslTDA18275SetStandardMode tmbslTDA18275_SetStandardMode
#endif

#ifndef tmbslTDA18275GetStandardMode
 #define tmbslTDA18275GetStandardMode tmbslTDA18275_GetStandardMode
#endif

#ifndef tmbslTDA18275SetRf
 #define tmbslTDA18275SetRf tmbslTDA18275_SetRF
#endif

#ifndef tmbslTDA18275GetRf
 #define tmbslTDA18275GetRf tmbslTDA18275_GetRF
#endif

#ifndef tmbslTDA18275Reset
 #define tmbslTDA18275Reset tmbslTDA18275_HwInit
#endif

#ifndef tmbslTDA18275GetIF
 #define tmbslTDA18275GetIF tmbslTDA18275_GetIF
#endif

#ifndef tmbslTDA18275GetLockStatus
 #define tmbslTDA18275GetLockStatus tmbslTDA18275_GetLockStatus
#endif

#ifndef tmbslTDA18275GetPowerLevel
 #define tmbslTDA18275GetPowerLevel tmbslTDA18275_GetPowerLevel
#endif

#ifndef tmbslTDA18275RFFineTuning
 #define tmbslTDA18275RFFineTuning tmbslTDA18275_SetFineRF
#endif

#ifndef tmbslTDA18275Write
 #define tmbslTDA18275Write tmbslTDA18275_Write
#endif

#ifndef tmbslTDA18275Read
 #define tmbslTDA18275Read tmbslTDA18275_Read
#endif

#define tmTDA18275PowerState_t TDA18275PowerState_t
#define tmTDA18275_PowerNormalMode TDA18275_PowerNormalMode
#define tmTDA18275_PowerStandbyWithXtalOn TDA18275_PowerStandbyWithXtalOn
#define tmTDA18275_PowerStandby TDA18275_PowerStandby
#define tmTDA18275_PowerMax TDA18275_PowerMax

#define tmTDA18275StandardMode_t TDA18275StandardMode_t
#define tmTDA18275_QAM_6MHz TDA18275_QAM_6MHz
#define tmTDA18275_QAM_8MHz TDA18275_QAM_8MHz
#define tmTDA18275_ATSC_6MHz TDA18275_ATSC_6MHz
#define tmTDA18275_ISDBT_6MHz TDA18275_ISDBT_6MHz
#define tmTDA18275_DVBT_1_7MHz TDA18275_DVBT_1_7MHz
#define tmTDA18275_DVBT_6MHz TDA18275_DVBT_6MHz
#define tmTDA18275_DVBT_7MHz TDA18275_DVBT_7MHz
#define tmTDA18275_DVBT_8MHz TDA18275_DVBT_8MHz
#define tmTDA18275_DVBT_10MHz TDA18275_DVBT_10MHz
#define tmTDA18275_DMBT_8MHz TDA18275_DMBT_8MHz
#define tmTDA18275_FM_Radio TDA18275_FM_Radio
#define tmTDA18275_ANLG_MN TDA18275_ANLG_MN
#define tmTDA18275_ANLG_B TDA18275_ANLG_B
#define tmTDA18275_ANLG_GH TDA18275_ANLG_GH
#define tmTDA18275_ANLG_I TDA18275_ANLG_I
#define tmTDA18275_ANLG_DK TDA18275_ANLG_DK
#define tmTDA18275_ANLG_L TDA18275_ANLG_L
#define tmTDA18275_ANLG_LL TDA18275_ANLG_LL
#define tmTDA18275_StandardMode_Max TDA18275_StandardMode_Max



#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18275_H */

