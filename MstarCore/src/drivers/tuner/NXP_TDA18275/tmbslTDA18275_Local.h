/*
  Copyright (C) 2012 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18275_Local.h
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
 * \par Changelog
 *  -0.0.23 RFT160	 timeout adjustement on VCO_Freq_Meas , VCO_Ampl_Cal, LO_Lock
 *     RFT171	 VCO algo selection correction (VCO_low vs VCO_High )
 *     RFT138	 Exclude SubLO around 16 Mhz in analog PAL & NTSC (AGC toggling)
 *  -0.0.22 RFT37 : reduce PLL_Lock timeout to 10ms
 *     RFT146 : LNA High Pass should not be activated below 250MHz
 *     RFT147 :  ensure multiple software reset/tune sequence robust
 *     RFT148 :  limit RF input to 1002 Mhz
 *     RFT150 :  floating point calculations removed
 *  -0.0.21 RFT124:  VCO current Ctrl above 75° T
 *  -0.0.20 RFT132  IR improvement
 *     RFT122  Calibrated PLD equation creation
 *  -0.0.19 RFT132 : IR improvement
 *  -0.0.18 RFT124 : new ES1' PLL settings for optimum PN when temperature varies
 *     RFT126 : PLL prog - VCO decision margin modification
 *     RFT130: Icp prog for all Analog standarts
 *  -0.0.17 RFT110	 bypass VCO Ampl Cal vs Temperature
 *     RFT116	 new settings for VCO on ES1' ( Swing and ICP )
 *     RFT117	 improve  VCO selection algorithm
 *  -0.0.16 RFT108:   API GetPowerLevel() updated to calculate power at antenna input
 *     RFT108:  PLD_CC_Enable set to 0
 *     RFT112: IRcal setting for ES1'
 *     
 *  -0.0.15 RFT96: Soft Reset at HwInit(); VCO meas check validity; Top_adapt_AGC1& Top_adapt_AGC2 label code update
 *     RFT103:  OVLD UDLD configurations update
 *  -0.0.14 RFT90 :  fix issue on MFT
 *     RFT92:  Disable Fast mode AGC2 ( toggling)
 *  -0.0.13 RFT87 (New settings for Release candidate 1.0)
 *  -0.0.12 RFT60:  change settings Soft IRcal
 *  -0.0.11 RFT81 : fix bug on IR_FreqPtr selection
 *     RFTxx :  NEW MAPPING AMP CAL & NEW MAPPING ICP
 *                   fix bug on cpleak0
 *                  regulo VCO to 3V
 *  -0.0.10 RFT67 : TDA18275 es1 - RC cal offset
 *     RFT71 : PLL ctrl software - VCO swg target ctrl
 *     RFT74 : New setup fine tuned in LG-IT bench
 *  -0.0.9 RFT60 : Setting Soft IRcal
 *     RFT62 : PLL VCO amp CAL mapping v1
 *  -0.0.8 RFT40: VCO low curr  to 0 ( as in POR) 
 *  -0.0.7 new algo HighPass_AGC2
 *  -0.0.7 RFT41 : Software Tda18275 on OM3954 not working
 *     RFT47: PSM IF_LPF for all Analog standard
 *  -0.0.6 AGC2_Highpass to 20 Mhz when not used ( QAM)
 *     new settings PSM groups only  ( Digital / Analog / QAM )
 *  -0.0.5 Add missing LU codes  for RF filter ( index from 98 to 131 )
 *     PSM IFfilters : « 0 mA »  vs « -4.2mA »
 *  -0.0.5 Add missing LU codes  for RF filter ( index from 98 to 131 )
 *     le PSM IFfilters : from « -4.2mA » to « 0 mA »
 *  -0.0.5 Add missing LU codes  for RF filter ( index from 98 to 131 )
 *  -0.0.4 Increase LO lock time to 100ms
 *  -0.0.3 update after review
 *  -0.0.2 update after review
 *  -0.0.1 Initial version
 *
 *
 * \par Version_Definition
 *  VERSION_TAG:TDA18275_COMP_NUM.TDA18275_MAJOR_VER.TDA18275_MINOR_VER
 *
*/

#ifndef _TMBSL_TDA18275_LOCAL_H
#define _TMBSL_TDA18275_LOCAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/


/* Driver version definition */
#define TDA18275_COMP_NUM  0  /* Major protocol change - Specification change required */
#define TDA18275_MAJOR_VER 0  /* Minor protocol change - Specification change required */
#define TDA18275_MINOR_VER 23  /* Software update - No protocol change - No specification change required */

/* Instance macros */
#define P_OBJ_VALID                             (pObj != Null)

/* I/O Functions macros */
#define P_SIO                                   pObj->sIo
#define P_SIO_READ                              P_SIO.Read
#define P_SIO_WRITE                             P_SIO.Write
#define P_SIO_READ_VALID                        (P_OBJ_VALID && (P_SIO_READ != Null))
#define P_SIO_WRITE_VALID                       (P_OBJ_VALID && (P_SIO_WRITE != Null))

/* Time Functions macros */
#define P_STIME                                 pObj->sTime
#define P_STIME_WAIT                            P_STIME.Wait
#define P_STIME_WAIT_VALID                      (P_OBJ_VALID && (P_STIME_WAIT != Null))

/* Debug Functions macros */
#define P_SDEBUG                                pObj->sDebug
#define P_DBGPRINTEx                            P_SDEBUG.Print
#define P_DBGPRINTVALID                         (P_OBJ_VALID && (P_DBGPRINTEx != Null))

/* Mutex Functions macros */
#define P_SMUTEX                                pObj->sMutex
#ifdef _TVFE_SW_ARCH_V4
 #define P_SMUTEX_OPEN                           P_SMUTEX.Open
 #define P_SMUTEX_CLOSE                          P_SMUTEX.Close
#else
 #define P_SMUTEX_OPEN                           P_SMUTEX.Init
 #define P_SMUTEX_CLOSE                          P_SMUTEX.DeInit
#endif
#define P_SMUTEX_ACQUIRE                        P_SMUTEX.Acquire
#define P_SMUTEX_RELEASE                        P_SMUTEX.Release

#define P_SMUTEX_OPEN_VALID                     (P_OBJ_VALID && (P_SMUTEX_OPEN != Null))
#define P_SMUTEX_CLOSE_VALID                    (P_OBJ_VALID && (P_SMUTEX_CLOSE != Null))
#define P_SMUTEX_ACQUIRE_VALID                  (P_OBJ_VALID && (P_SMUTEX_ACQUIRE != Null))
#define P_SMUTEX_RELEASE_VALID                  (P_OBJ_VALID && (P_SMUTEX_RELEASE != Null))

/* Driver Mutex macros */
#define TDA18275_MUTEX_TIMEOUT                  (5000)
#define P_MUTEX                                 pObj->pMutex
#define P_MUTEX_VALID                           (P_MUTEX != Null)

#ifdef _TVFE_IMPLEMENT_MUTEX
 #define _MUTEX_ACQUIRE(_NAME) \
     if(err == TM_OK) \
     { \
         /* Try to acquire driver mutex */ \
         err = i##_NAME##_MutexAcquire(pObj, _NAME##_MUTEX_TIMEOUT); \
     } \
     if(err == TM_OK) \
     {

 #define _MUTEX_RELEASE(_NAME) \
         (void)i##_NAME##_MutexRelease(pObj); \
     }
#else
 #define _MUTEX_ACQUIRE(_NAME) \
     if(err == TM_OK) \
     {

 #define _MUTEX_RELEASE(_NAME) \
     }
#endif

    
#define TDA18275_INSTANCE_REGMAP_DEF \
    { \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0  \
    }
#define TDA18275_Identity 3658
#define TDA18275_VCO_LOW_MIN 5700000
#define TDA18275_VCO_LOW_MAX 7800000
#define TDA18275_VCO_MED_MIN 6400000
#define TDA18275_VCO_MED_MAX 8700000
#define TDA18275_VCO_HIGH_MIN 7100000
#define TDA18275_VCO_HIGH_MAX 9300000

/* TDA18275 Driver State Machine */
typedef enum _TDA18275HwState_t {
    TDA18275_HwState_Unknown = 0,   /* Hw State Unknown */
    TDA18275_HwState_InitNotDone,   /* Hw Init Not Done */
    TDA18275_HwState_InitPending,   /* Hw Init Pending */
    TDA18275_HwState_InitDone,      /* Hw Init Done */
    TDA18275_HwState_SetStdDone,    /* Set Standard Done */
    TDA18275_HwState_SetRFDone,     /* Set RF Done */
    TDA18275_HwState_SetFineRFDone, /* Set Fine RF Done */
    TDA18275_HwState_Max
} TDA18275HwState_t, *pTDA18275HwState_t;

typedef enum _TDA18275HwStateCaller_t {
    TDA18275_HwStateCaller_Unknown = 0, /* Caller Unknown */
    TDA18275_HwStateCaller_SetPower,    /* Caller SetPowerState */
    TDA18275_HwStateCaller_HwInit,      /* Caller HwInit */
    TDA18275_HwStateCaller_SetStd,      /* Caller SetStandardMode */
    TDA18275_HwStateCaller_SetRF,       /* Caller SetRF */
    TDA18275_HwStateCaller_SetFineRF,   /* Caller SetFineRF */
    TDA18275_HwStateCaller_GetRSSI,     /* Caller GetRSSI */
    TDA18275_HwStateCaller_SetRawRF,    /* Caller SetRawRF */
    TDA18275_HwStateCaller_Max
} TDA18275HwStateCaller_t, *pTDA18275HwStateCaller_t;

/* TDA18275 specific  TDA18275 MSM */
typedef enum _TDA18275MSM_t {
    TDA18275_MSM_VCO_Freq_Meas       = 0x01,
    TDA18275_MSM_VCO_Ampl_Cal        = 0x02,  
    TDA18275_MSM_RC_Cal              = 0x04,
    TDA18275_MSM_IR_CAL_Image        = 0x08,
    TDA18275_MSM_IR_Cal_Loop         = 0x10,
    TDA18275_MSM_RSSI_Meas           = 0x20
} TDA18275MSM_t, *pTDA18275MSM_t;

typedef enum _TDA18275PowerSavingMode_t {
    TDA18275PowerSavingMode_Digital_nominal = 0,
    TDA18275PowerSavingMode_Analog_nominal = 1,
    TDA18275PowerSavingMode_QAM_nominal = 2,
    TDA18275PowerSavingMode_ATSC_nominal = 3,
    TDA18275PowerSavingMode_Max
} TDA18275PowerSavingMode_t, *pTDA18275PowerSavingMode_t;

typedef enum _TDA18275_HighPass_AGC2_t {
    TDA18275_HighPass_AGC2_Digital = 0,
    TDA18275_HighPass_AGC2_Analog = 1,
    TDA18275_HighPass_AGC2_Analog_GH = 2,
    TDA18275_HighPass_AGC2_QAM = 3,
    TDA18275_HighPass_AGC2_20MHZ = 4,
    TDA18275_HighPass_AGC2_Max
} TDA18275_HighPass_AGC2_t , *pTDA18275_HighPass_AGC2_t;


typedef struct _TDA18275StdSettings
{
    /****************************************************************/
    /* IF Settings                                                  */
    /****************************************************************/
    UInt32                                      IF;                         /* IF Frequency */
    UInt32                                      Offset_fmax;

    /****************************************************************/
    /* IF SELECTIVITY Settings                                      */
    /****************************************************************/
    TDA18275_LP_Fc_t                               LPF;                        /* LPF Cut off */
    TDA18275_IF_LPF_Offset_t                       LPF_Offset;                 /* LPF offset */
    TDA18275_IF_LPF_sign_t                         LPF_sign;                   /* LPF offset sign */
    TDA18275_DC_Notch_t                            DC_Notch_IF_PPF;            /* DC notch IF PPF */
    TDA18275_IF_HP_Enable_t                        HP_Enable;                  /* Hi Pass Enable */
    TDA18275_IF_HP_Fc_t                            HPF;                        /* Hi Pass */
    TDA18275_IF_HPF_Offset_t                       HPF_Offset;                 /* HPF offset */
    TDA18275_IF_HPF_sign_t                         HPF_sign;                   /* HPF offset sign */
    TDA18275_IF_Notch_Enable_t                     IF_Notch_Enable;            /* IF_Notch_Enable */
    TDA18275_IF_Notch_Freq_t                       IF_Notch_Freq;              /* IF Notch Freq */
    TDA18275_IF_Notch_Offset_t                     IF_Notch_Offset;            /* IF Notch Offset */
    TDA18275_IF_Notch_sign_t                       IF_Notch_sign;              /* IF Notch Offset sign */
    TDA18275_IFnotchToRSSI_t                       IFnotchToRSSI;              /* IFnotchToRSSI */

    /****************************************************************/
    /* AGC  Settings                                                */
    /****************************************************************/
    TDA18275_AGC1_Top_t                            AGC1_TOP_I2C_DN_UP;         /* AGC1 TOP I2C DN/UP */
    TDA18275_AGC1_Top_Strategy_t                   AGC1_TOP_STRATEGY;          /* AGC1 TOP STRATEGY */
    TDA18275_AGC1_Do_step_t                        AGC1_Do_step;               /* AGC1_Do_step */
    TDA18275_AGC2_TOP_t                            AGC2_TOP_I2C_DN_UP;         /* AGC2 TOP I2C DN/UP */
    TDA18275_AGC2_Top_Strategy_t                   AGC2_Top_Strategy;          /* AGC2 TOP STRATEGY */
    TDA18275_AGC2_Do_step_t                        AGC2_Do_step;               /* AGC2_Do_step */
    TDA18275_AGC4_TOP_t                            AGC4_TOP_I2C_DN_UP;         /* AGC4 TOP I2C DN/UP */
    TDA18275_AGC4_Do_step_t                        AGC4_Do_step;               /* AGC4_Do_step */
    TDA18275_AGC5_TOP_t                            AGC5_TOP_I2C_DN_UP;         /* AGC5 TOP I2C DN/UP */
    TDA18275_AGC5_Do_step_t                        AGC5_Do_step;               /* AGC5_Do_step */
    TDA18275_Top_adapt_AGC1_t                      AGC1_Adapt_TOP;             /* AGC1 TOP adapt */
    TDA18275_Top_adapt_AGC2_t                      AGC2_Adapt_TOP;             /* AGC2 TOP adapt */
    TDA18275_IF_level_t                            IF_Output_Level;            /* IF Output Level */
    TDA18275_AGC_Ovld_TOP_t                        AGC_Overload_TOP;           /* AGC Overload TOP */
    TDA18275_AGC2_Gain_Control_Speed_t             AGC2_Gain_Control_Speed;    /* AGC2 Gain Control Speed */
    Bool                                           AGC1_cc_Freeze_Enable;      /* AGC1_cc_Freeze */
    Bool                                           AGC1_cc_Wide_Enable;        /* AGC1_cc_Wide_Enable */
    TDA18275_PD_Vsync_Mgt_t                        PD_Vsync_Mgt;               /* PD_Vsync_Mgt */
    TDA18275_Neg_Modulation_t                      Neg_Modulation;             /* Negative modulation */
    TDA18275_AGCK_Mode_t                           AGCK_Mode;                  /* AGCK Mode */
    TDA18275_AGC5_HP_Fc_t                          AGC5_HP_Fc;                 /* AGC5_HP_Fc */
    TDA18275_RSSI_HP_Fc_t                          RSSI_HP_Fc;                 /* RSSI_HP_Fc */
    TDA18275_Det6_Cap_Val_t                        Det6_Cap_Val;               /* Det6_Cap_Val */
    TDA18275_RSSI_AV_t                             RSSI_AV;                    /* RSSI_AV */
    TDA18275_RSSI_Ck_Speed_t                       RSSI_Ck_Speed;              /* RSSI_Ck_Speed*/
    TDA18275_LNA_Highpass_t                        LNA_Highpass;               /* LNA_Highpass */
    TDA18275_HighPass_AGC2_t                       HighPass_AGC2_algo;         /* HighPass_AGC2 algo  */ 
    UInt8                                          cp_cursel_algo;             /* current charge pump selection algo */
    TDA18275_DIFOUT_En_t                           DIFOUT_En;                  /* DIFOUT_En */
    TDA18275_DVIFAGC_En_t                          DVIFAGC_En;                 /* DVIFAGC_En */
    TDA18275PowerSavingMode_t					PowerSavingMode;            /* normal or low */

} TDA18275StdSettings, *pTDA18275StdSettings;

typedef struct _TDA18275_VCO
{
    UInt32 fmax;
    UInt32 fmin;
} TDA18275_VCO, *pTDA18275_VCO;

typedef struct _TDA18275Object_t
{
    tmUnitSelect_t                  tUnit;
    tmUnitSelect_t                  tUnitW;
    ptmbslFrontEndMutexHandle       pMutex;
    Bool                            init;
    tmbslFrontEndIoFunc_t           sIo;
    tmbslFrontEndTimeFunc_t         sTime;
    tmbslFrontEndDebugFunc_t        sDebug;
    tmbslFrontEndMutexFunc_t        sMutex;
    /* Device specific part: */
    tmPowerState_t                  curPowerState;
    TDA18275PowerState_t            curLLPowerState;
    TDA18275PowerState_t            mapLLPowerState[tmPowerMax];
    TDA18275PowerSavingMode_t       curPowerSavingMode;
    TDA18275_VCO                    VCO[3];
    UInt8                           Temp_Meas;
    UInt32                          uRF;
    UInt32                          uIF;
    UInt32                          uLO;
    UInt32                          uFVCO;
    TDA18275StandardMode_t          StandardMode;
    pTDA18275StdSettings            pStandard;
    /* Settings independant of standard */
    TDA18275HwState_t               eHwState;                /* Indicates HwInit state */
    UInt32                          uLUCodeProgrammed;
    /* Settings dependant of standard */
    TDA18275StdSettings         Std_Array[TDA18275_StandardMode_Max-1];
#ifdef _TDA18275_REGMAP_BITFIELD_DEFINED
    TDA18275_Reg_Map_t              RegMap;
#else
    UInt8                           RegMap[TDA18275_REG_MAP_NB_BYTES];
#endif
} TDA18275Object_t, *pTDA18275Object_t, **ppTDA18275Object_t;


/*============================================================================*/
/* Internal Prototypes:                                                       */
/*============================================================================*/

extern tmErrorCode_t
iTDA18275_CheckCalcPLL(pTDA18275Object_t pObj);

extern tmErrorCode_t
iTDA18275_CheckHwState(pTDA18275Object_t pObj, TDA18275HwStateCaller_t caller);

extern tmErrorCode_t
iTDA18275_SetRF(pTDA18275Object_t pObj);

extern tmErrorCode_t
iTDA18275_SetRF_NoFast(pTDA18275Object_t pObj);

extern tmErrorCode_t
iTDA18275_SetLO(pTDA18275Object_t pObj);

extern tmErrorCode_t
iTDA18275_ProgramLPF(pTDA18275Object_t pObj, UInt32 uIndex);

extern tmErrorCode_t
iTDA18275_SetRF_Dependencies(pTDA18275Object_t pObj);

extern tmErrorCode_t
iTDA18275_SetRF_Freq(pTDA18275Object_t pObj);


extern tmErrorCode_t iTDA18275_SetPLL(pTDA18275Object_t pObj);

extern tmErrorCode_t iTDA18275_Adapt_vco_swingctrl(pTDA18275Object_t pObj, UInt8  adc_vtune, UInt8   VCO_select);

extern tmErrorCode_t iTDA18275_Force_vco_currentctrl(pTDA18275Object_t pObj, UInt8  adc_vtune, UInt8   VCO_select);

extern tmErrorCode_t
iTDA18275_MSMLaunch( pTDA18275Object_t pObj, UInt8 uValue);

extern tmErrorCode_t
iTDA18275_SetLLPowerState(
    pTDA18275Object_t       pObj,       /* I: Driver object */
    TDA18275PowerState_t    powerState  /* I: Power state of TDA18275 */
);
extern tmErrorCode_t
iTDA18275_WaitIRQ(pTDA18275Object_t pObj, UInt32 timeOut, UInt32 waitStep);

 tmErrorCode_t
iTDA18275_Write(pTDA18275Object_t pObj, const TDA18275_BitField_t* pBitField, UInt8 uData, tmbslFrontEndBusAccess_t eBusAccess);

extern tmErrorCode_t
iTDA18275_Read(pTDA18275Object_t pObj, const TDA18275_BitField_t* pBitField, UInt8* puData, tmbslFrontEndBusAccess_t eBusAccess);

extern tmErrorCode_t
iTDA18275_WriteRegMap(pTDA18275Object_t pObj, UInt8 uAddress, UInt32 uWriteLen);

extern tmErrorCode_t
iTDA18275_ReadRegMap(pTDA18275Object_t pObj, UInt8 uAddress, UInt32 uReadLen);

extern tmErrorCode_t
iTDA18275_Wait(pTDA18275Object_t pObj, UInt32 Time);

extern tmErrorCode_t 
iTDA18275_PowerSavingMode( pTDA18275Object_t   pObj, TDA18275PowerSavingMode_t PowerSavingMode);

extern tmErrorCode_t 
iTDA18275_GetIdentity(pTDA18275Object_t   pObj, UInt16*  puIdentity);

#ifdef _TVFE_IMPLEMENT_MUTEX
 extern tmErrorCode_t iTDA18275_MutexAcquire(pTDA18275Object_t pObj, UInt32 timeOut);
 extern tmErrorCode_t iTDA18275_MutexRelease(pTDA18275Object_t pObj);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18275_LOCAL_H */

