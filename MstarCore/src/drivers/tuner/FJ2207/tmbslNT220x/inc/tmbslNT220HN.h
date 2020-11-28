/**
Copyright (C) 2008 NXP B.V., All Rights Reserved.
This source code and any compilation or derivative thereof is the proprietary
information of NXP B.V. and is confidential in nature. Under no circumstances
is this software to be  exposed to or placed under an Open Source License of
any type without the expressed written permission of NXP B.V.
*
* \file          tmbslNT220HN.h
*                %version: 15 %
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

#ifndef _TMBSL_NT220HN_H
#define _TMBSL_NT220HN_H

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

    /* SW Error codes */
#define NT220x_ERR_BASE               (CID_COMP_TUNER | CID_LAYER_BSL)
#define NT220x_ERR_COMP               (CID_COMP_TUNER | CID_LAYER_BSL | TM_ERR_COMP_UNIQUE_START)

#define NT220x_ERR_BAD_UNIT_NUMBER    (NT220x_ERR_BASE + TM_ERR_BAD_UNIT_NUMBER)
#define NT220x_ERR_NOT_INITIALIZED    (NT220x_ERR_BASE + TM_ERR_NOT_INITIALIZED)
#define NT220x_ERR_INIT_FAILED        (NT220x_ERR_BASE + TM_ERR_INIT_FAILED)
#define NT220x_ERR_BAD_PARAMETER      (NT220x_ERR_BASE + TM_ERR_BAD_PARAMETER)
#define NT220x_ERR_NOT_SUPPORTED      (NT220x_ERR_BASE + TM_ERR_NOT_SUPPORTED)
#define NT220x_ERR_HW_FAILED          (NT220x_ERR_COMP + 0x0001)
#define NT220x_ERR_NOT_READY          (NT220x_ERR_COMP + 0x0002)
#define NT220x_ERR_BAD_VERSION        (NT220x_ERR_COMP + 0x0003)


    typedef enum _tmNT220xPowerState_t {
        tmNT220x_PowerNormalMode,                                     /* Device normal mode */
        tmNT220x_PowerStandbyWithLNAOnAndWithXtalOnAndSynthe,         /* Device standby mode with LNA and Xtal Output and Synthe */
        tmNT220x_PowerStandbyWithLNAOnAndWithXtalOn,                  /* Device standby mode with LNA and Xtal Output */
        tmNT220x_PowerStandbyWithXtalOn,                              /* Device standby mode with Xtal Output */
        tmNT220x_PowerStandby,                                        /* Device standby mode */
        tmNT220x_PowerMax
    } tmNT220xPowerState_t, *ptmNT220xPowerState_t;

    typedef enum _tmNT220xStandardMode_t {
        tmNT220x_DVBT_6MHz = 0,                       /* Digital TV DVB-T 6MHz */
        tmNT220x_DVBT_7MHz,                           /* Digital TV DVB-T 7MHz */
        tmNT220x_DVBT_8MHz,                           /* Digital TV DVB-T 8MHz */
        tmNT220x_ANLG_MN,                             /* Analog TV M/N */
        tmNT220x_ANLG_B,                              /* Analog TV B */
        tmNT220x_ANLG_GH,                             /* Analog TV G/H */
        tmNT220x_ANLG_I,                              /* Analog TV I */
        tmNT220x_ANLG_DK,                             /* Analog TV D/K */
        tmNT220x_ANLG_L,                              /* Analog TV L */
        tmNT220x_ANLG_LL,                             /* Analog TV L' */
        tmNT220x_FM_Radio,                            /* Analog FM Radio */
        tmNT220x_Scanning,                            /* analog  preset blind Scanning */
        tmNT220x_QAM_6MHz,                            /* Digital TV QAM 6MHz */
        tmNT220x_QAM_8MHz,                            /* Digital TV QAM 8MHz */
        tmNT220x_ISDBT_6MHz,                          /* Digital TV ISDBT 6MHz */
        tmNT220x_ATSC_6MHz,                           /* Digital TV ATSC 6MHz */
        tmNT220x_DMBT_8MHz,                           /* Digital TV DMB-T 8MHz */
        tmNT220x_StandardMode_Max
    } tmNT220xStandardMode_t, *ptmNT220xStandardMode_t;

    typedef enum _tmNT220xLPF_t {
        tmNT220x_LPF_6MHz = 0,                        /* 6MHz LPFc */
        tmNT220x_LPF_7MHz,                            /* 7MHz LPFc */
        tmNT220x_LPF_8MHz,                            /* 8MHz LPFc */
        tmNT220x_LPF_9MHz,                            /* 9MHz LPFc */
        tmNT220x_LPF_1_5MHz,                          /* 1.5MHz LPFc */
        tmNT220x_LPF_Max
    } tmNT220xLPF_t, *ptmNT220xLPF_t;

    typedef enum _tmNT220xLPFOffset_t {
        tmNT220x_LPFOffset_0pc = 0,                   /* LPFc 0% */
        tmNT220x_LPFOffset_min_4pc,                   /* LPFc -4% */
        tmNT220x_LPFOffset_min_8pc,                   /* LPFc -8% */
        tmNT220x_LPFOffset_min_12pc,                  /* LPFc -12% */
        tmNT220x_LPFOffset_Max
    } tmNT220xLPFOffset_t, *ptmNT220xLPFOffset_t;

    typedef enum _tmNT220xIF_AGC_Gain_t {
        tmNT220x_IF_AGC_Gain_2Vpp_0_30dB = 0,         /* 2Vpp       0 - 30dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_1_25Vpp_min_4_26dB,      /* 1.25Vpp   -4 - 26dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_1Vpp_min_6_24dB,         /* 1Vpp      -6 - 24dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_0_8Vpp_min_8_22dB,       /* 0.8Vpp    -8 - 22dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_0_85Vpp_min_7_5_22_5dB,  /* 0.85Vpp   -7.5 - 22.5dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_0_7Vpp_min_9_21dB,       /* 0.7Vpp    -9 - 21dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_0_6Vpp_min_10_3_19_7dB,  /* 0.6Vpp    -10.3 - 19.7dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_0_5Vpp_min_12_18dB,      /* 0.5Vpp    -12 - 18dB IF AGC Gain */
        tmNT220x_IF_AGC_Gain_Max
    } tmNT220xIF_AGC_Gain_t, *ptmNT220xIF_AGC_Gain_t;

    typedef enum _tmNT220xIF_Notch_t {
        tmNT220x_IF_Notch_Disabled = 0,               /* IF Notch Enabled */
        tmNT220x_IF_Notch_Enabled,                    /* IF Notch Disabled */
        tmNT220x_IF_Notch_Max
    } tmNT220xIF_Notch_t, *ptmNT220xIF_Notch_t;

    typedef enum _tmNT220xIF_HPF_t {
        tmNT220x_IF_HPF_Disabled = 0,                 /* IF HPF 0.4MHz */
        tmNT220x_IF_HPF_0_4MHz,                       /* IF HPF 0.4MHz */
        tmNT220x_IF_HPF_0_85MHz,                      /* IF HPF 0.85MHz */
        tmNT220x_IF_HPF_1MHz,                         /* IF HPF 1MHz */
        tmNT220x_IF_HPF_1_5MHz,                       /* IF HPF 1.5MHz */
        tmNT220x_IF_HPF_Max
    } tmNT220xIF_HPF_t, *ptmNT220xIF_HPF_t;

    typedef enum _tmNT220xDC_Notch_t {
        tmNT220x_DC_Notch_Disabled = 0,               /* IF Notch Enabled */
        tmNT220x_DC_Notch_Enabled,                    /* IF Notch Disabled */
        tmNT220x_DC_Notch_Max
    } tmNT220xDC_Notch_t, *ptmNT220xDC_Notch_t;

    typedef enum _tmNT220xAGC1_LNA_TOP_t {
        tmNT220x_AGC1_LNA_TOP_d95_u89dBuV = 0,            /* AGC1 LNA TOP down 95 up 89 dBuV */
        tmNT220x_AGC1_LNA_TOP_d95_u93dBuV_do_not_use,     /* AGC1 LNA TOP down 95 up 93 dBuV */
        tmNT220x_AGC1_LNA_TOP_d95_u94dBuV_do_not_use,     /* AGC1 LNA TOP down 95 up 94 dBuV */
        tmNT220x_AGC1_LNA_TOP_d95_u95dBuV_do_not_use,     /* AGC1 LNA TOP down 95 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_d99_u89dBuV,                /* AGC1 LNA TOP down 99 up 89 dBuV */
        tmNT220x_AGC1_LNA_TOP_d99_u93dBuV,                /* AGC1 LNA TOP down 95 up 93 dBuV */
        tmNT220x_AGC1_LNA_TOP_d99_u94dBuV,                /* AGC1 LNA TOP down 99 up 94 dBuV */
        tmNT220x_AGC1_LNA_TOP_d99_u95dBuV,                /* AGC1 LNA TOP down 99 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_d99_u9SdBuV,                /* AGC1 LNA TOP down 99 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_d100_u93dBuV,               /* AGC1 LNA TOP down 100 up 93 dBuV */
        tmNT220x_AGC1_LNA_TOP_d100_u94dBuV,               /* AGC1 LNA TOP down 100 up 94 dBuV */
        tmNT220x_AGC1_LNA_TOP_d100_u95dBuV,               /* AGC1 LNA TOP down 100 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_d100_u9SdBuV,               /* AGC1 LNA TOP down 100 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_d101_u93dBuV,               /* AGC1 LNA TOP down 101 up 93 dBuV */
        tmNT220x_AGC1_LNA_TOP_d101_u94dBuV,               /* AGC1 LNA TOP down 101 up 94 dBuV */
        tmNT220x_AGC1_LNA_TOP_d101_u95dBuV,               /* AGC1 LNA TOP down 101 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_d101_u9SdBuV,               /* AGC1 LNA TOP down 101 up 95 dBuV */
        tmNT220x_AGC1_LNA_TOP_Max
    } tmNT220xAGC1_LNA_TOP_t, *ptmNT220xAGC1_LNA_TOP_t;

    typedef enum _tmNT220xAGC2_RF_Attenuator_TOP_t {
        tmNT220x_AGC2_RF_Attenuator_TOP_d89_u81dBuV = 0, /* AGC2 RF Attenuator TOP down 89 up 81 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d91_u83dBuV,     /* AGC2 RF Attenuator TOP down 91 up 83 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d93_u85dBuV,     /* AGC2 RF Attenuator TOP down 93 up 85 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d95_u87dBuV,     /* AGC2 RF Attenuator TOP down 95 up 87 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d88_u88dBuV,     /* AGC2 RF Attenuator TOP down 88 up 81 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d89_u82dBuV,     /* AGC2 RF Attenuator TOP down 89 up 82 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d90_u83dBuV,     /* AGC2 RF Attenuator TOP down 90 up 83 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d91_u84dBuV,     /* AGC2 RF Attenuator TOP down 91 up 84 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d92_u85dBuV,     /* AGC2 RF Attenuator TOP down 92 up 85 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d93_u86dBuV,     /* AGC2 RF Attenuator TOP down 93 up 86 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d94_u87dBuV,     /* AGC2 RF Attenuator TOP down 94 up 87 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d95_u88dBuV,     /* AGC2 RF Attenuator TOP down 95 up 88 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d87_u81dBuV,     /* AGC2 RF Attenuator TOP down 87 up 81 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d88_u82dBuV,     /* AGC2 RF Attenuator TOP down 88 up 82 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d89_u83dBuV,     /* AGC2 RF Attenuator TOP down 89 up 83 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d90_u84dBuV,     /* AGC2 RF Attenuator TOP down 90 up 84 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d91_u85dBuV,     /* AGC2 RF Attenuator TOP down 91 up 85 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d92_u86dBuV,     /* AGC2 RF Attenuator TOP down 92 up 86 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d93_u87dBuV,     /* AGC2 RF Attenuator TOP down 93 up 87 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d94_u88dBuV,     /* AGC2 RF Attenuator TOP down 94 up 88 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_d95_u89dBuV,     /* AGC2 RF Attenuator TOP down 95 up 89 dBuV */
        tmNT220x_AGC2_RF_Attenuator_TOP_Max
    } tmNT220xAGC2_RF_Attenuator_TOP_t, *ptmNT220xAGC2_RF_Attenuator_TOP_t;
    
    typedef enum _tmNT220xAGC3_RF_AGC_TOP_t {
        tmNT220x_AGC3_RF_AGC_TOP_94dBuV = 0, /* AGC3 RF AGC TOP 94 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_96dBuV,     /* AGC3 RF AGC TOP 96 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_98dBuV,     /* AGC3 RF AGC TOP 98 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_100dBuV,    /* AGC3 RF AGC TOP 100 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_102dBuV,    /* AGC3 RF AGC TOP 102 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_104dBuV,    /* AGC3 RF AGC TOP 104 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_106dBuV,    /* AGC3 RF AGC TOP 106 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_107dBuV,    /* AGC3 RF AGC TOP 107 dBuV */
        tmNT220x_AGC3_RF_AGC_TOP_Max
    } tmNT220xAGC3_RF_AGC_TOP_t, *ptmNT220xAGC3_RF_AGC_TOP_t;

#define tmNT220x_AGC3_RF_AGC_TOP_FREQ_LIM 291000000

    typedef enum _tmNT220xAGC4_IR_Mixer_TOP_t {
        tmNT220x_AGC4_IR_Mixer_TOP_d105_u99dBuV = 0,     /* AGC4 IR_Mixer TOP down 105 up 99 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d105_u100dBuV,        /* AGC4 IR_Mixer TOP down 105 up 100 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d105_u101dBuV,        /* AGC4 IR_Mixer TOP down 105 up 101 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d107_u101dBuV,        /* AGC4 IR_Mixer TOP down 107 up 101 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d107_u102dBuV,        /* AGC4 IR_Mixer TOP down 107 up 102 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d107_u103dBuV,        /* AGC4 IR_Mixer TOP down 107 up 103 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d108_u103dBuV,        /* AGC4 IR_Mixer TOP down 108 up 103 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d109_u103dBuV,        /* AGC4 IR_Mixer TOP down 109 up 103 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d109_u104dBuV,        /* AGC4 IR_Mixer TOP down 109 up 104 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d109_u105dBuV,        /* AGC4 IR_Mixer TOP down 109 up 105 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d110_u104dBuV,        /* AGC4 IR_Mixer TOP down 110 up 104 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d110_u105dBuV,        /* AGC4 IR_Mixer TOP down 110 up 105 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d110_u106dBuV,        /* AGC4 IR_Mixer TOP down 110 up 106 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d112_u106dBuV,        /* AGC4 IR_Mixer TOP down 112 up 106 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d112_u107dBuV,        /* AGC4 IR_Mixer TOP down 112 up 107 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_d112_u108dBuV,        /* AGC4 IR_Mixer TOP down 112 up 108 dBuV */
        tmNT220x_AGC4_IR_Mixer_TOP_Max
    } tmNT220xAGC4_IR_Mixer_TOP_t, *ptmNT220xAGC4_IR_Mixer_TOP_t;

    typedef enum _tmNT220xAGC5_IF_AGC_TOP_t {
        tmNT220x_AGC5_IF_AGC_TOP_d105_u99dBuV = 0,        /* AGC5 IF AGC TOP down 105 up 99 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d105_u100dBuV,           /* AGC5 IF AGC TOP down 105 up 100 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d105_u101dBuV,           /* AGC5 IF AGC TOP down 105 up 101 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d107_u101dBuV,           /* AGC5 IF AGC TOP down 107 up 101 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d107_u102dBuV,           /* AGC5 IF AGC TOP down 107 up 102 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d107_u103dBuV,           /* AGC5 IF AGC TOP down 107 up 103 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d108_u103dBuV,           /* AGC5 IF AGC TOP down 108 up 103 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d109_u103dBuV,           /* AGC5 IF AGC TOP down 109 up 103 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d109_u104dBuV,           /* AGC5 IF AGC TOP down 109 up 104 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d109_u105dBuV,           /* AGC5 IF AGC TOP down 109 up 105 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d110_u104dBuV,           /* AGC5 IF AGC TOP down 108 up 104 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d110_u105dBuV,           /* AGC5 IF AGC TOP down 108 up 105 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d110_u106dBuV,           /* AGC5 IF AGC TOP down 108 up 106 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d112_u106dBuV,           /* AGC5 IF AGC TOP down 108 up 106 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d112_u107dBuV,           /* AGC5 IF AGC TOP down 108 up 107 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_d112_u108dBuV,           /* AGC5 IF AGC TOP down 108 up 108 dBuV */
        tmNT220x_AGC5_IF_AGC_TOP_Max
    } tmNT220xAGC5_IF_AGC_TOP_t, *ptmNT220xAGC5_IF_AGC_TOP_t;

    typedef enum _tmNT220xAGC5_Detector_HPF_t {
        tmNT220x_AGC5_Detector_HPF_Disabled = 0,          /* AGC5_Detector_HPF Enabled */
        tmNT220x_AGC5_Detector_HPF_Enabled,               /* IF Notch Disabled */
        tmNT220x_AGC5_Detector_HPF_Max
    } tmNT220xAGC5_Detector_HPF_t, *ptmNT220xAGC5_Detector_HPFh_t;

    typedef enum _tmNT220xAGC3_Adapt_t {
        tmNT220x_AGC3_Adapt_Enabled = 0,                  /* AGC3_Adapt Enabled */
        tmNT220x_AGC3_Adapt_Disabled,                     /* AGC3_Adapt Disabled */
        tmNT220x_AGC3_Adapt_Max
    } tmNT220xAGC3_Adapt_t, *ptmNT220xAGC3_Adapt_t;

    typedef enum _tmNT220xAGC3_Adapt_TOP_t {
        tmNT220x_AGC3_Adapt_TOP_102dBuV = 0,              /* AGC3 Adapt TOP 102 dBuV */
        tmNT220x_AGC3_Adapt_TOP_100dBuV,                  /* AGC3 Adapt TOP 100 dBuV */
        tmNT220x_AGC3_Adapt_TOP_98dBuV,                   /* AGC3 Adapt TOP 98 dBuV */
        tmNT220x_AGC3_Adapt_TOP_96dBuV,                   /* AGC3 Adapt TOP 96 dBuV */
    } tmNT220xAGC3_Adapt_TOP_t, *ptmNT220xAGC3_Adapt_TOP_t;

    typedef enum _tmNT220xAGC5_Atten_3dB_t {
        tmNT220x_AGC5_Atten_3dB_Disabled = 0,             /* AGC5_Atten_3dB Disabled */
        tmNT220x_AGC5_Atten_3dB_Enabled,                  /* AGC5_Atten_3dB Enabled */
        tmNT220x_AGC5_Atten_3dB_Max
    } tmNT220xAGC5_Atten_3dB_t, *ptmNT220xAGC5_Atten_3dB_t;

    typedef enum _tmNT220xH3H5_VHF_Filter6_t {
        tmNT220x_H3H5_VHF_Filter6_Disabled = 0,           /* H3H5_VHF_Filter6 Disabled */
        tmNT220x_H3H5_VHF_Filter6_Enabled,                /* H3H5_VHF_Filter6 Enabled */
        tmNT220x_H3H5_VHF_Filter6_Max
    } tmNT220xH3H5_VHF_Filter6_t, *ptmNT220xH3H5_VHF_Filter6_t;

    typedef enum _tmNT220x_LPF_Gain_t {
        tmNT220x_LPF_Gain_Unknown = 0,                    /* LPF_Gain Unknown */
        tmNT220x_LPF_Gain_Frozen,                         /* LPF_Gain Frozen */
        tmNT220x_LPF_Gain_Free                            /* LPF_Gain Free */
    } tmNT220x_LPF_Gain_t, *ptmNT220x_LPF_Gain_t;

    typedef struct _tmNT220xStdCoefficients
    {
        UInt32                              IF;
        Int32                               CF_Offset;
        tmNT220xLPF_t                     LPF;
        tmNT220xLPFOffset_t               LPF_Offset;
        tmNT220xIF_AGC_Gain_t             IF_Gain;
        tmNT220xIF_Notch_t                IF_Notch;
        tmNT220xIF_HPF_t                  IF_HPF;
        tmNT220xDC_Notch_t                DC_Notch;
        tmNT220xAGC1_LNA_TOP_t            AGC1_LNA_TOP;
        tmNT220xAGC2_RF_Attenuator_TOP_t  AGC2_RF_Attenuator_TOP;
        tmNT220xAGC3_RF_AGC_TOP_t         AGC3_RF_AGC_TOP_Low_band;
        tmNT220xAGC3_RF_AGC_TOP_t         AGC3_RF_AGC_TOP_High_band;
        tmNT220xAGC4_IR_Mixer_TOP_t       AGC4_IR_Mixer_TOP;
        tmNT220xAGC5_IF_AGC_TOP_t         AGC5_IF_AGC_TOP;
        tmNT220xAGC5_Detector_HPF_t       AGC5_Detector_HPF;
        tmNT220xAGC3_Adapt_t              AGC3_Adapt;
        tmNT220xAGC3_Adapt_TOP_t          AGC3_Adapt_TOP;
        tmNT220xAGC5_Atten_3dB_t          AGC5_Atten_3dB;
        UInt8                               GSK;
        tmNT220xH3H5_VHF_Filter6_t        H3H5_VHF_Filter6;
        tmNT220x_LPF_Gain_t               LPF_Gain;
    } tmNT220xStdCoefficients, *ptmNT220xStdCoefficients;

    typedef enum _tmNT220xRFFilterRobustness_t {
        tmNT220xRFFilterRobustness_Low = 0,
        tmNT220xRFFilterRobustness_High,
        tmNT220xRFFilterRobustness_Max
    } tmNT220xRFFilterRobustness_t, *ptmNT220xRFFilterRobustness_t;

    typedef struct _tmNT220xRFFilterRating {
        double                               VHFLow_0_Margin;
        double                               VHFLow_1_Margin;
        double                               VHFHigh_0_Margin;
        double                               VHFHigh_1_Margin;
        double                               UHFLow_0_Margin;
        double                               UHFLow_1_Margin;
        double                               UHFHigh_0_Margin;
        double                               UHFHigh_1_Margin;    
        tmNT220xRFFilterRobustness_t      VHFLow_0_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      VHFLow_1_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      VHFHigh_0_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      VHFHigh_1_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      UHFLow_0_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      UHFLow_1_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      UHFHigh_0_RFFilterRobustness;
        tmNT220xRFFilterRobustness_t      UHFHigh_1_RFFilterRobustness;
    } tmNT220xRFFilterRating, *ptmNT220xRFFilterRating;

    tmErrorCode_t
        tmbslNT220xInit(
        tmUnitSelect_t              tUnit,      /*  I: Unit number */
        tmbslFrontEndDependency_t*  psSrvFunc   /*  I: setup parameters */
        );
    tmErrorCode_t 
        tmbslNT220xDeInit (
        tmUnitSelect_t  tUnit   /*  I: Unit number */
        );
    tmErrorCode_t
        tmbslNT220xGetSWVersion (
        ptmSWVersion_t  pSWVersion  /*  I: Receives SW Version */
        );
    tmErrorCode_t
        tmbslNT220xCheckHWVersion (
        tmUnitSelect_t tUnit    /* I: Unit number */
        );
    tmErrorCode_t
        tmbslNT220xSetPowerState (
        tmUnitSelect_t          tUnit,      /*  I: Unit number */
        tmNT220xPowerState_t  powerState  /*  I: Power state of this device */
        );
    tmErrorCode_t
        tmbslNT220xGetPowerState (
        tmUnitSelect_t            tUnit,        /*  I: Unit number */
        tmNT220xPowerState_t    *pPowerState  /*  O: Power state of this device */
        );
    tmErrorCode_t
        tmbslNT220xSetStandardMode (
        tmUnitSelect_t              tUnit,          /*  I: Unit number */
        tmNT220xStandardMode_t    StandardMode    /*  I: Standard mode of this device */
        );
    tmErrorCode_t
        tmbslNT220xGetStandardMode (
        tmUnitSelect_t              tUnit,          /*  I: Unit number */
        tmNT220xStandardMode_t    *pStandardMode  /*  O: Standard mode of this device */
        );
    tmErrorCode_t
        tmbslNT220xSetRf(
        tmUnitSelect_t  tUnit,  /*  I: Unit number */
        UInt32          uRF     /*  I: RF frequency in hertz */
        );
    tmErrorCode_t
        tmbslNT220xGetRf(
        tmUnitSelect_t  tUnit,  /*  I: Unit number */
        UInt32*         pRF     /*  O: RF frequency in hertz */
        );
    tmErrorCode_t
        tmbslNT220xReset(
        tmUnitSelect_t tUnit    /* I: Unit number */
        );
    tmErrorCode_t
        tmbslNT220xGetIF(
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        UInt32*         puIF    /* O: IF Frequency in hertz */
        );
    tmErrorCode_t
        tmbslNT220xGetCF_Offset(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32*         puOffset    /* O: Center frequency offset in hertz */
        );
    tmErrorCode_t
        tmbslNT220xGetLockStatus(
        tmUnitSelect_t          tUnit,      /* I: Unit number */
        tmbslFrontEndState_t*   pLockStatus /* O: PLL Lock status */
        );
    tmErrorCode_t
        tmbslNT220xGetPowerLevel(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32*         pPowerLevel /* O: Power Level in dBµV */
        );
    tmErrorCode_t
        tmbslNT220xSetIRQWait(
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        Bool            bWait   /* I: Determine if we need to wait IRQ in driver functions */
        );
    tmErrorCode_t
        tmbslNT220xGetIRQWait(
        tmUnitSelect_t  tUnit,  /* I: Unit number */
        Bool*           pbWait  /* O: Determine if we need to wait IRQ in driver functions */
        );
    tmErrorCode_t
        tmbslNT220xGetIRQ(
        tmUnitSelect_t  tUnit  /* I: Unit number */,
        Bool*           pbIRQ  /* O: IRQ triggered */
        );
    tmErrorCode_t
        tmbslNT220xWaitIRQ(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          timeOut,    /* I: timeOut for IRQ wait */
        UInt32          waitStep,   /* I: wait step */
        UInt8           irqStatus   /* I: IRQs to wait */
        );
    tmErrorCode_t
        tmbslNT220xGetXtalCal_End(
        tmUnitSelect_t  tUnit           /* I: Unit number */,
        Bool*           pbXtalCal_End   /* O: XtalCal_End triggered */
        );
    tmErrorCode_t
        tmbslNT220xWaitXtalCal_End(
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          timeOut,    /* I: timeOut for IRQ wait */
        UInt32          waitStep    /* I: wait step */
        );
    tmErrorCode_t
        tmbslNT220xSoftReset(
        tmUnitSelect_t  tUnit   /* I: Unit number */
        );
    tmErrorCode_t
        tmbslNT220xCheckRFFilterRobustness
        (
        tmUnitSelect_t                         tUnit,      /* I: Unit number */
        ptmNT220xRFFilterRating              rating      /* O: RF Filter rating */
        );
    tmErrorCode_t
        tmbslNT220xWrite (
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          uIndex,     /* I: Start index to write */
        UInt32          WriteLen,   /* I: Number of bytes to write */
        UInt8*          pData       /* I: Data to write */
        );
    tmErrorCode_t
        tmbslNT220xRead (
        tmUnitSelect_t  tUnit,      /* I: Unit number */
        UInt32          uIndex,     /* I: Start index to read */
        UInt32          ReadLen,    /* I: Number of bytes to read */
        UInt8*          pData       /* I: Data to read */
        );

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_NT220HN_H */
