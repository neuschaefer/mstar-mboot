/**
  Copyright (C) 2007 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslFrontEndTypes.h
 *                %version: 9 %
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


#ifndef TMSYSFRONTENDTYPES_H
#define TMSYSFRONTENDTYPES_H

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

    /* Status of the Front-End */
    typedef enum _tmsysFrontEndState_t
    {
        /** status Unknown */
        tmsysFrontEndStateUnknown = 0,
        /** Channel locked*/
        tmsysFrontEndStateLocked,
        /** Channel not locked */
        tmsysFrontEndStateNotLocked,
        /** Channel lock in process */
        tmsysFrontEndStateSearching,
        tmsysFrontEndStateMax
    } tmsysFrontEndState_t, *ptmsysFrontEndState_t;

    /* I2C switch */
    typedef enum _tmsysFrontEndI2CSwitchState_t
    {
        tmsysFrontEndI2CSwitchStateUnknown = 0,
        tmsysFrontEndI2CSwitchStateOpen,
        tmsysFrontEndI2CSwitchStateClosed,
        tmsysFrontEndI2CSwitchStateReset,
        tmsysFrontEndI2CSwitchStateMax
    } tmsysFrontEndI2CSwitchState_t, *ptmsysFrontEndI2CSwitchState_t;

    /* Block Type: Shaed, Stream A/B */
    typedef enum _tmsysFrontEndBlockType_t
    {
        tmsysFrontEndBlockShared = 0,
        tmsysFrontEndBlockStream,
        tmsysFrontEndBlockMax
    } tmsysFrontEndBlockType_t, *ptmsysFrontEndBlockType_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*                                                                      */
    /*  Describes the possible tune request types.                          */
    /*                                                                      */
    /*  TRT_ATSC        - Digital ATSC type.                                */
    /*  TRT_DVBT        - Digital terrestrial type.                         */
    /*  TRT_DVBC        - Digital cable type.                               */
    /*  TRT_DVBS        - Digital satellite type.                           */
    /*  TRT_ANALOG_FM   - Analog FM radio type.                             */
    /*  TRT_ANALOG_TV   - Analog TV type.                                   */
    /*  TRT_DCABLE      - Digital cable ( ATSC / QAM ) type.                */
    /*  TRT_ISDBT       - ISDB terrestrial type.                            */
    /*  TRT_ISDBC       - ISDB cable type.                                  */
    /*  TRT_ISDBS       - ISDB satellite type.                              */
    /*  TRT_TUNER_ONLY  - ISDB satellite type.                              */
    /*  TRT_UNKNOWN     - Unknown type.                                     */
    /*                                                                      */
    /************************************************************************/
    typedef enum
    {
        TRT_NONE        = 0x00000000,
        TRT_ATSC        = 0x00000001,
        TRT_DVBT        = 0x00000002,
        TRT_DVBC        = 0x00000004,
        TRT_DVBS        = 0x00000008,
        TRT_ANALOG_FM   = 0x00000010,
        TRT_ANALOG_TV   = 0x00000020,
        TRT_DCABLE      = 0x00000040,
        TRT_ISDBT       = 0x00000080,
        TRT_ISDBC       = 0x00000100,
        TRT_ISDBS       = 0x00000200,
        TRT_TUNER_ONLY  = 0x00000400,
        TRT_DVBS2       = 0x00000800,
        TRT_DVBT2       = 0x00001000,
        TRT_DEMOD_ONLY  = 0x00002000,
        TRT_UNKNOWN     = 0xFFFFFFFF
    } tmTuneReqType_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the possible formats of an analog television signal.      */
    /*                                                                      */
    /* Settings:                                                            */
    /*  ANALOG_NONE     - No analog video standard available.               */
    /*  ANALOG_NTSC_M   - NTSC (M) standard, 7.5 IRE black.                 */
    /*  ANALOG_NTSC_M_J - NTSC (M) standard, 0 IRE black (Japan).           */
    /*  ANALOG_NTSC_433 - NTSC 433.                                         */
    /*  ANALOG_PAL_B    - PAL B standard.                                   */
    /*  ANALOG_PAL_D    - PAL (D) standard.                                 */
    /*  ANALOG_PAL_G    - PAL (G) standard.                                 */
    /*  ANALOG_PAL_H    - PAL (H) standard.                                 */
    /*  ANALOG_PAL_I    - PAL (I) standard.                                 */
    /*  ANALOG_PAL_M    - PAL (M) standard.                                 */
    /*  ANALOG_PAL_N    - PAL (N) standard.                                 */
    /*  ANALOG_PAL_60   - PAL 60 standard.                                  */
    /*  ANALOG_SECAM_B  - SECAM (B) standard                                */
    /*  ANALOG_SECAM_D  - SECAM (D) standard.                               */
    /*  ANALOG_SECAM_G  - SECAM (G) standard.                               */
    /*  ANALOG_SECAM_H  - SECAM (H) standard.                               */
    /*  ANALOG_SECAM_K  - SECAM (K) standard.                               */
    /*  ANALOG_SECAM_K1 - SECAM (K1) standard.                              */
    /*  ANALOG_SECAM_L  - SECAM (L) standard.                               */
    /*  ANALOG_SECAM_L1 - SECAM (L1) standard.                              */
    /************************************************************************/
    typedef enum
    {
        ANALOG_NONE     = 0x00000000,
        ANALOG_NTSC_M   = 0x00000001,
        ANALOG_NTSC_M_J = 0x00000002,
        ANALOG_NTSC_433 = 0x00000004,
        ANALOG_PAL_B    = 0x00000010,
        ANALOG_PAL_D    = 0x00000020,
        ANALOG_PAL_G    = 0x00000040,
        ANALOG_PAL_H    = 0x00000080,
        ANALOG_PAL_I    = 0x00000100,
        ANALOG_PAL_M    = 0x00000200,
        ANALOG_PAL_N    = 0x00000400,
        ANALOG_PAL_60   = 0x00000800,
        ANALOG_SECAM_B  = 0x00001000,
        ANALOG_SECAM_D  = 0x00002000,
        ANALOG_SECAM_G  = 0x00004000,
        ANALOG_SECAM_H  = 0x00008000,
        ANALOG_SECAM_K  = 0x00010000,
        ANALOG_SECAM_K1 = 0x00020000,
        ANALOG_SECAM_L  = 0x00040000,
        ANALOG_SECAM_L1 = 0x00080000,
        ANALOG_PAL_N_C  = 0x00100000
    } tmTVStandard_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the DVBT tune request structure.                          */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwOffset              - DVB signal offset frequency.                */
    /*  dwBandwidth           - Bandwidth of the DVB signal.                */
    /*  dwSpectralInversion   - Used spectral inversion.                    */
    /*  dwGuardInterval       - Used guard interval.                        */
    /*  dwTransmissionMode    - Used transmission mode.                     */
    /*  dwPriority            - Low/High Priority channel.                  */
    /*  dwHierarchyAlpha      - Hierarchy Alpha.                            */
    /*  dwModulationType      - Modulation type of the DVB signal.          */
    /*  dwVRateLowPriority    - Viterbi Rate Low Priority.                  */
    /*  dwVRateHighPriority   - Viterbi Rate High Priority.                 */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmDVBTRequest_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwOffset;
        UInt32                  dwBandwidth;
        UInt32                  dwSpectralInversion;
        UInt32                  dwGuardInterval;
        UInt32                  dwTransmissionMode;
        UInt32                  dwPriority;
        UInt32                  dwHierarchyAlpha;
        UInt32                  dwModulationType;
        UInt32                  dwVRateLowPriority;
        UInt32                  dwVRateHighPriority;
    } tmDVBTRequest_t, *ptmDVBTRequest_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the DVBT2 tune request structure.                         */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwBandwidth           - Bandwidth of the DVB signal.                */
    /*  dwSpectralInversion   - Used spectral inversion.                    */
    /*  dwGuardInterval       - Used guard interval.                        */
    /*  dwFFT                 - Used FFT.                                   */
    /*  dwInputType           - Used input type                             */
    /*  dwPLPId               - Used PLP Id                                 */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmDVBT2Request_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwBandwidth;
        UInt32                  dwSpectralInversion;
        UInt32                  dwGuardInterval;
        UInt32                  dwFFT;
        UInt32                  dwInputType;
        UInt32                  dwPLPId;
    } tmDVBT2Request_t, *ptmDVBT2Request_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the DVBT tune request structure.                          */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwModulationType      - Modulation type of the DVB signal.          */
    /*  dwSymbolRate          - Used symbol rate.                           */
    /*  dwSpectralInversion   - Used spectral inversion.                    */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmDVBCRequest_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwModulationType;
        UInt32                  dwSymbolRate;
        UInt32                  dwSpectralInversion;
    } tmDVBCRequest_t, *ptmDVBCRequest_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the DVBS2 tune request structure.                         */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwModulationType      - Modulation type of the DVB signal.          */
    /*  dwSymbolRate          - Used symbol rate.                           */
    /*  dwSpectralInversion   - Used spectral inversion.                    */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmDVBS2Request_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwModulationType;
        UInt32                  dwSymbolRate;
        UInt32                  dwCodeRate;
        UInt32                  dwRollOff;
        UInt32                  dwSpectralInversion;
        UInt32                  dwLNBPolarity;
        UInt32                  dwContinuousTone;
    } tmDVBS2Request_t, *ptmDVBS2Request_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the DVBS2 tune request structure.                         */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwModulationType      - Modulation type of the DVB signal.          */
    /*  dwSymbolRate          - Used symbol rate.                           */
    /*  dwSpectralInversion   - Used spectral inversion.                    */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmDVBSRequest_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwModulationType;
        UInt32                  dwSymbolRate;
        UInt32                  dwCodeRate;
        UInt32                  dwRollOff;
        UInt32                  dwSpectralInversion;
        UInt32                  dwLNBPolarity;
        UInt32                  dwContinuousTone;
    } tmDVBSRequest_t, *ptmDVBSRequest_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the ATSC tune request structure.                          */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwModulationType      - Modulation type of the ATSC signal.         */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmATSCRequest_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwModulationType;
    } tmATSCRequest_t, *ptmATSCRequest_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the DCABLE tune request structure.                        */
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency           - The frequency for a tune request.           */
    /*  dwModulationType      - Modulation type of the ATSC signal.         */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmDCABLERequest_t
    {
        tmsysFrontEndState_t    eFrontEndLock;
        UInt32                  dwFrequency;
        UInt32                  dwModulationType;
    } tmDCABLERequest_t, *ptmDCABLERequest_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the analog tune request structure                         */  
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency     - The frequency.                                    */
    /*  dwCountry       - The current country code.                         */
    /*  tAnalogStandard - The standard of the analog signal.It is a member  */
    /*                    of the tmTVStandard_t enumeration.                */
    /*  bAutoStdDet     - Auto standard detection mode (en/disabled).       */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmAnalogTVRequest_t
    {
        tmsysFrontEndState_t    eFrontEndHLock;
        tmsysFrontEndState_t    eFrontEndVLock;
        UInt32                  dwFrequency;
        UInt32                  dwLastFrequency;
        UInt32                  dwCountry;
        tmTVStandard_t          tAnalogStandard;
        UInt32                  dwKSAnalogStandard;
        Bool                    bAutoStdDet;
        UInt32                  dwChannel;
        UInt32                  dwTuningFlags;
    } tmAnalogTVRequest_t, *ptmAnalogTVRequest_t;

    /************************************************************************/
    /*                                                                      */
    /* Description:                                                         */
    /*  Describes the Tuner Only tune request structure                     */  
    /*                                                                      */
    /* Settings:                                                            */
    /*  dwFrequency     - The frequency.                                    */
    /*  dwStandard      - The standard                                      */
    /*                                                                      */
    /************************************************************************/
    typedef struct _tmTunerOnlyRequest_t
    {
        tmsysFrontEndState_t    eTunerLock;
        UInt32                  dwFrequency;
        UInt32                  dwStandard;
    } tmTunerOnlyRequest_t, *ptmTunerOnlyRequest_t;

/*============================================================================*/

//-----------------------------------------------------------------------------
// Software Version Structure
//
typedef struct _tmbslSWVersion
{
    char*                   pName;
    UInt32                  nameBufSize;
    tmSWVersion_t           swVersion;
    tmSWSettingsVersion_t   swSettingsVersion;
} tmbslSWVersion_t, *ptmbslSWVersion_t;

typedef struct _tmsysSWVersion
{
    UInt32              arrayItemsNumber;
    tmbslSWVersion_t    swVersionArray[32];
} tmsysSWVersion_t, *ptmsysSWVersion_t;


#ifdef __cplusplus
}
#endif

#endif /* TMSYSFRONTENDTYPES_H */
/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

