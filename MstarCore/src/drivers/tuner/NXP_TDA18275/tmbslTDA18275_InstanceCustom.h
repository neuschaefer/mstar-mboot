/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18275_InstanceCustom.h
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
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 * \par Changelog
 *  -0.0.0.14 RFT167	 TOP AGC5 SECAM L prime
 *  -0.0.0.13 RFT137  PD_vsync_management to be disabled
 *     RFT135  ISDBT- LNA_Highpass to "0"
 *     RFT134  ISDBT- 3.683MHz
 *     RFT133  AGC5 block saturation in J83B (LPF 8MHz issue)
 *  -0.0.0.12 RFT118: ATSC N+1 adjustment setting
 *  -0.0.0.11 RFT80 : improve ATSC ACIs N+6/N+7
 *     RFT101:  improve C/N with LPF to 7Mhz 0%
 *  -0.0.0.11 RFT80 : ATSC ACIs N+6/N+7 improve
 *  -0.0.0.10 RFT93 : new settings 1.8 ( Analog changes PAL I, DK,  L )
 *  -0.0.0.9 RFT87 (New settings for Release candidate 1.0)
 *  -0.0.0.8 RFT84: New settings M/N in alpha 8
 *  -0.0.0.7 RFT83 : new analog settings
 *  -0.0.0.6 RFT74 : New setup fine tuned in LG-IT bench
 *  -0.0.0.5 RFT65 : IF shift in PAL B  ( v1.4)
 *  -0.0.0.4 RFT54 ; new settings v1.3
 *  -0.0.0.3 RFT48  : new settnigs V1.2
 *  -0.0.0.3 RFT43: Settings optimization: TOP AGC1
 *     RFT45: DVB-T 7 and 8MHz : IF filter modification for N+-1
 *  -0.0.0.2 new settings
 *  -0.0.0.1 Initial version
 *
 *
 * \par Version_Definition
 *  VERSION_TAG:TDA18275_SETTINGS_CUSTOMER_NUM.TDA18275_SETTINGS_PROJECT_NUM.TDA18275_SETTINGS_MAJOR_VER.TDA18275_SETTINGS_MINOR_VER
 *
*/

#ifndef _TDA18275_INSTANCE_CUSTOM_H
#define _TDA18275_INSTANCE_CUSTOM_H


#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

/* Driver settings version definition */
#define TDA18275_SETTINGS_CUSTOMER_NUM 0                     /* SW Settings Customer Number */
#define TDA18275_SETTINGS_PROJECT_NUM  0                     /* SW Settings Project Number  */
#define TDA18275_SETTINGS_MAJOR_VER    0                     /* SW Settings Major Version   */
#define TDA18275_SETTINGS_MINOR_VER    14                     /* SW Settings Minor Version   */

/*  number of tuner supported by driver */
#define TDA18275_UNITS  1

/* RC Cal Offset  0x00:+4%; 0x01:+2%; 0x02:0%  0x03:-2%  */
#define TDA18275_RC_Cal_Offset 0x01

#define TDA18275_cp_cursel_Analog 0
#define TDA18275_cp_cursel_Digital 1

/* Standard Preset Definitions: */
#define TDA18275_INSTANCE_CUSTOM_STD_QAM_6MHz \
    {                                                       /* QAM 6MHz */ \
        4000000,                                            /* IF */ \
        3000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_7_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_0,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Enabled,                          /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_4,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Negative,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_108_107d5_103d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_110_105_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_107_102_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Slow,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_QAM,                         /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_QAM_nominal,                /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_QAM_8MHz \
    {                                                       /* QAM 6MHz */ \
        5000000,                                            /* IF */ \
        4000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_9_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Negative,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Enabled,                          /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_106_100_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_108_107d5_103d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_110_105_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_110_105_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                          /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Slow,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* HighPass_LNA_algo */ \
        TDA18275_HighPass_AGC2_QAM,                         /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_QAM_nominal,                /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ATSC_6MHz \
    {                                                       /* ATSC */ \
        5250000,                                            /* IF */ \
        3000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_0,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Enabled,                          /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_3d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_8,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Negative,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_8d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_4,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_n6_dB_TOP_Do_for_LNA_gain_sup_13_dB,    /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_111_110d5_106d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_7dB_13dB,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_112_107_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n10d3_to_19d7_dB_0d6_Vpp,         /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                          /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_20MHZ,                       /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_ATSC_nominal,               /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ISdBT_6MHz \
    {                                                       /* ISdBT */ \
        3683000,                                            /* IF */ \
        3000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_7_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_8,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Negative,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Enabled,                          /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_7d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_112_107_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_DVBT_1_7MHz \
    {                                                       /* DVB-T/T2 1.7MHz */ \
        850000,                                             /* IF */ \
        1350000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_1d5_MHz,                             /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_107_102_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_DVBT_6MHz \
    {                                                       /* DVB-T/T2 6MHz */ \
        4000000,                                            /* IF */ \
        3000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_7_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_8,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Negative,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_7d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_107_102_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_DVBT_7MHz \
    {                                                       /* DVB-T/T2 7MHz */ \
        4500000,                                            /* IF */ \
        3500000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Negative,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1d6_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_8,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Negative,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_8d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_107_102_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_DVBT_8MHz \
    {                                                       /* DVB-T/T2 8MHz */ \
        5000000,                                            /* IF */ \
        4000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_8,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_9d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_107_102_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_DVBT_10MHz \
    {                                                       /* DVB-T/T2 10MHz */ \
        6000000,                                            /* IF */ \
        5000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_11d25_MHz,                           /* LPF */ \
        TDA18275_IF_LPF_Offset_8,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Negative,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Enabled,                          /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_11d45_MHz,                   /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_107_102_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_DMBT_8MHz \
    {                                                       /* DMB-T */ \
        5000000,                                            /* IF */ \
        4000000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_9_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_8,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Negative,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_9d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Disabled,                    /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_108_102_dBuVrms,                  /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_0d128_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms,          /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_0d128_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_112_107_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_0d128_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_112_107_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_0d128_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n6_to_24_dB_1_Vpp,                /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_8d192_ms,                        /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Digital,                     /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Digital,                         /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Digital_nominal,             /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_FM_RADIO \
    {                                                       /* FM */ \
        1250000,                                            /* IF */ \
        0100000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_1d5_MHz,                             /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Enabled,                          /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Enabled,                      /* HP Enable */ \
        TDA18275_IF_HP_Fc_1_MHz,                            /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_98_92_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_99_98d5_94d5_dBuVrms,             /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_110_105_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_110_105_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n8_to_22_dB_0d8_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_8d192_ms,          /* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                      /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_32d768_ms,                       /* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_0d3_MHz,                        /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_0d3_MHz,                        /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_3_pF,                         /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_31_25_KHz,                   /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_MN \
    {                                                       /* NTSC M/N */ \
        5400000,                                            /* IF */ \
        4750000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_6_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_98_92_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_99_98d5_94d5_dBuVrms,             /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_110_105_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_110_105_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Enabled,                    /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                       /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_B \
    {                                                       /* PAL B */ \
        6250000,                                            /* IF */ \
        5750000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_7_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_98_92_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_10_dB,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_103_102d5_98d5_dBuVrms,             /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_4dB_10dB,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_105_100_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_105_100_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Enabled,                    /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                       /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_GH \
    {                                                               /* PAL G/H */ \
        6750000,                                                    /* IF */ \
        6750000,                                                    /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_98_92_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_10_dB,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_103_102d5_98d5_dBuVrms,             /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_4dB_10dB,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_105_100_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_105_100_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Enabled,                    /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                        /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog_GH,                   /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_I \
    {                                                               /* PAL I */ \
        7250000,                                                    /* IF */ \
        6750000,                                                    /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_104_98_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_10_dB,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_103_102d5_98d5_dBuVrms,             /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_4dB_10dB,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_105_100_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_105_100_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Enabled,                    /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                       /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_DK \
    {                                                               /* SECAM D/K */ \
        6850000,                                                    /* IF */ \
        5750000,                                                    /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_8d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_100_94_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_13_dB,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_101_100d5_96d5_dBuVrms,            /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_7dB_13dB,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_105_100_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_105_100_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5,                 /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Enabled,                    /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                       /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_L \
    {                                                       /* SECAM L */ \
        6750000,                                            /* IF */ \
        5750000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Enabled,                   /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_8d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_98_92_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_103_102d5_98d5_dBuVrms,            /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_110_105_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_110_105_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p6_n9,                     /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                   /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                       /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

#define TDA18275_INSTANCE_CUSTOM_STD_ANALOG_LL \
    {                                                       /* SECAM L' */ \
        1250000,                                            /* IF */ \
        1250000,                                            /* Offset_fmax */ \
        TDA18275_LP_Fc_8_MHz,                               /* LPF */ \
        TDA18275_IF_LPF_Offset_4,                           /* LPF Offset */ \
        TDA18275_IF_LPF_sign_Positive,                      /* LPF Offset sign */ \
        TDA18275_DC_Notch_Disabled,                         /* DC notch IF PPF */ \
        TDA18275_IF_HP_Enable_Disabled,                     /* HP Enable */ \
        TDA18275_IF_HP_Fc_0d5_MHz,                          /* HPF Fc */ \
        TDA18275_IF_HPF_Offset_0,                           /* HPF Offset */ \
        TDA18275_IF_HPF_sign_Positive,                      /* HPF Offset sign */ \
        TDA18275_IF_Notch_Enable_Disabled,                  /* IF_Notch_Enable */ \
        TDA18275_IF_Notch_Freq_6d25_MHz,                    /* IF _Notch Freq */ \
        TDA18275_IF_Notch_Offset_0,                         /* IF Notch Offset */ \
        TDA18275_IF_Notch_sign_Positive,                    /* IF Notch Offset sign */ \
        TDA18275_IFnotchToRSSI_Enabled,                     /*  IFnotchToRSSI  */ \
        TDA18275_AGC1_Top_98_92_dBuVrms,                    /* AGC1 TOP I2C DN/UP */ \
        TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change,   /* AGC1 TOP STRATEGY */ \
        TDA18275_AGC1_Do_step_1d024_ms,                      /* AGC1_Do_step */ \
        TDA18275_AGC2_TOP_99_98d5_94d5_dBuVrms,             /* AGC2 TOP I2C DN/UP */ \
        TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change,   /* AGC2 TOP STRATEGY */ \
        TDA18275_AGC2_Do_step_1d024_ms,                      /* AGC2_Do_step */ \
        TDA18275_AGC4_TOP_110_105_dBuVrms,                  /* AGC4 TOP I2C DN/UP */ \
        TDA18275_AGC4_Do_step_1d024_ms,                      /* AGC4_Do_step */ \
        TDA18275_AGC5_TOP_105_100_dBuVrms,                  /* AGC5 TOP I2C DN/UP */ \
        TDA18275_AGC5_Do_step_1d024_ms,                      /* AGC5_Do_step */ \
        TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change,      /* AGC1 TOP adapt */ \
        TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change,      /* AGC2 TOP adapt */ \
        TDA18275_IF_level_n9_to_21_dB_0d7_Vpp,              /* IF Output Level */ \
        TDA18275_AGC_Ovld_TOP_p9_p6_n9,                     /* AGC Overload TOP */ \
        TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms,/* AGC2 Gain Control Speed */ \
        False,                                              /* AGC1_cc_Freeze */ \
        False,                                              /* AGC1_cc_Wide_Enable */ \
        TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled,                     /* PD_Vsync_Mgt */ \
        TDA18275_Neg_Modulation_Disabled,                  /* Negative modulation */ \
        TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms,/* AGCK Mode */ \
        TDA18275_AGC5_HP_Fc_2d25_MHz,                       /* AGC5_HP_Fc */ \
        TDA18275_RSSI_HP_Fc_2d25_MHz,                       /* RSSI_HP_Fc */ \
        TDA18275_Det6_Cap_Val_0d5_pF,                       /* Det6_Cap_Val */ \
        TDA18275_RSSI_AV_Fast,                              /* RSSI_AV */ \
        TDA18275_RSSI_Ck_Speed_250_KHz,                     /* RSSI_Ck_Speed*/ \
        TDA18275_LNA_Highpass_Disabled,                     /* LNA_Highpass */ \
        TDA18275_HighPass_AGC2_Analog,                      /* HighPass_AGC2_algo */ \
        TDA18275_cp_cursel_Analog,                          /* current charge pump */ \
        TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled,         /* DIFOUT_En */ \
        TDA18275_DVIFAGC_En_Analog_VIF_AGC,                 /* DVIFAGC_En */ \
        TDA18275PowerSavingMode_Analog_nominal,              /* Normal or Low */ \
    }

/* Default configuration */
#define TDA18275_INSTANCE_CUSTOM_CURPOWERSTATE_DEF tmPowerMax
#define TDA18275_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF TDA18275_PowerMax
#define TDA18275_INSTANCE_CUSTOM_RF_DEF 0
#define TDA18275_INSTANCE_CUSTOM_IF_DEF 0
#define TDA18275_INSTANCE_CUSTOM_LO_DEF 0
#define TDA18275_INSTANCE_CUSTOM_STANDARDMODE_DEF TDA18275_StandardMode_Max
#define TDA18275_INSTANCE_CUSTOM_CURPOWERSAVINGMODE TDA18275PowerSavingMode_Max

/* Power settings */
#define TDA18275_INSTANCE_CUSTOM_POWER_DEF \
    TDA18275_INSTANCE_CUSTOM_CURPOWERSTATE_DEF,                     /* curPowerState */ \
    TDA18275_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF,                   /* curLLPowerState */ \
    {                                                               /* mapLLPowerState */ \
        TDA18275_PowerNormalMode,                                   /* tmPowerOn (D0) */ \
        TDA18275_PowerStandbyWithXtalOn,                            /* tmPowerStandby (D1) */ \
        TDA18275_PowerStandbyWithXtalOn,                            /* tmPowerSuspend (D2) */ \
        TDA18275_PowerStandbyWithXtalOn                             /* tmPowerOff (D3) */ \
    }, \
    TDA18275_INSTANCE_CUSTOM_CURPOWERSAVINGMODE

/* Standard Presets Aggregation: */
#define TDA18275_INSTANCE_CUSTOM_STD_DEF \
    { \
        TDA18275_INSTANCE_CUSTOM_STD_QAM_6MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_QAM_8MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_ATSC_6MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_ISdBT_6MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_DVBT_1_7MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_DVBT_6MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_DVBT_7MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_DVBT_8MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_DVBT_10MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_DMBT_8MHz, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_FM_RADIO, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_MN, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_B, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_GH, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_I, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_DK, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_L, \
        TDA18275_INSTANCE_CUSTOM_STD_ANALOG_LL, \
    }

#define TDA18275_VCO_DEF \
    { \
       {TDA18275_VCO_HIGH_MAX, TDA18275_VCO_HIGH_MIN }, \
       {TDA18275_VCO_MED_MAX, TDA18275_VCO_MED_MIN }, \
       {TDA18275_VCO_LOW_MAX, TDA18275_VCO_LOW_MIN }, \
    }

#define TDA18275_INSTANCE_CUSTOM_MASTER_0 \
    TDA18275_INSTANCE_CUSTOM_POWER_DEF, \
    TDA18275_VCO_DEF, \
    50, /* temp_meas */ \
    TDA18275_INSTANCE_CUSTOM_RF_DEF,                                /* uRF */ \
    TDA18275_INSTANCE_CUSTOM_IF_DEF,                                /* uIF */ \
    TDA18275_INSTANCE_CUSTOM_LO_DEF,                                /* uProgRF */ \
    0,                                                              /* uFVCO */ \
    TDA18275_INSTANCE_CUSTOM_STANDARDMODE_DEF,                      /* StandardMode */ \
    Null,                                                           /* pStandard */ \
    TDA18275_HwState_InitNotDone,                                   /* eHwState */ \
    0,                                                              /* uLUCodeProgrammed */ \
    TDA18275_INSTANCE_CUSTOM_STD_DEF, \

/* Custom Driver Instance Parameters: (Path 0) */
#define TDA18275_INSTANCE_CUSTOM_0 \
    TDA18275_INSTANCE_CUSTOM_MASTER_0

#ifdef __cplusplus
}
#endif

#endif /* _TDA18275_INSTANCE_CUSTOM_H */

