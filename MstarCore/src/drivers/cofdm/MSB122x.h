/*@ <FileComment ID=1246257763790> @*/
/**********************************************************************
 Copyright (c) 2006-2009 MStar Semiconductor, Inc.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 MStar Semiconductor Inc. and be kept in strict confidence
 (MStar Confidential Information) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of MStar Confidential
 Information is unlawful and strictly prohibited. MStar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.

* Class : mapi_demodulator_msb122x
* File  : mapi_demodulator_msb122x.h
**********************************************************************/

/*@ </FileComment ID=1246257763790> @*/


/*@ <IncludeGuard> @*/
#ifndef _MSB122x_H_
#define _MSB122x_H_

/*@ </IncludeGuard> @*/

#include <msAPI_Tuner.h>

/*@ </Include> @*/


/*@ <Definitions> @*/

#ifndef usleep
#define usleep MsOS_DelayTaskUs
#endif

#ifndef MAPI_BOOL
#define MAPI_BOOL BOOLEAN
#endif
#ifndef MAPI_U8
#define MAPI_U8 U8
#endif
#ifndef MAPI_U16
#define MAPI_U16 U16
#endif
#ifndef MAPI_U32
#define MAPI_U32 U32
#endif
#ifndef MAPI_TRUE
#define MAPI_TRUE TRUE
#endif
#ifndef MAPI_FALSE
#define MAPI_FALSE FALSE
#endif
#ifndef MAPI_S8
#define MAPI_S8 S8
#endif


	typedef enum
	{
		COFDM_FEC_LOCK,
		COFDM_PSYNC_LOCK,
		COFDM_TPS_LOCK,
		COFDM_DCR_LOCK,
		COFDM_AGC_LOCK,
		COFDM_MODE_DET,

	} COFDM_LOCK_STATUS;

	typedef struct
	{
		U8		cmd_code;
		U8		param[64];
	} S_CMDPKTREG;

	typedef enum
	{
		CMD_SYSTEM_INIT = 0,
		CMD_DAC_CALI,
		CMD_DVBT_CONFIG,
		CMD_DVBC_CONFIG,
		CMD_VIF_CTRL,
		CMD_FSM_CTRL,
		CMD_INDIR_RREG,
		CMD_INDIR_WREG,
		CMD_GET_INFO,
		CMD_TS_CTRL,
		CMD_TUNED_VALUE,
		CMD_MAX_NUM
	}E_CMD_CODE;

typedef enum
{
    E_FE_SIGNAL_NO = 0,
    E_FE_SIGNAL_WEAK,
    E_FE_SIGNAL_MODERATE,
    E_FE_SIGNAL_STRONG,
    E_FE_SIGNAL_VERY_STRONG,
} EN_FRONTEND_SIGNAL_CONDITION;
/*
typedef enum
{
	E_DEMOD_LOCK,
	E_DEMOD_CHECKING,
	E_DEMOD_CHECKEND,
	E_DEMOD_UNLOCK,
	E_DEMOD_NULL,
} EN_LOCK_STATUS;
*/


#define     DEMOD_SLAVE_ID          0x32

    // ------------------------------------------------------------
    // Other Define
    // -----------------------------------------------------------

    #define E_AFC_GOOD_MINUS_VALUE      E_AFC_MINUS_37p5KHz
    #define E_AFC_GOOD_PLUS_VALUE       E_AFC_PLUS_12p5KHz

    #define SAW_FILTER_SECAML_MODE      1
    #define SAW_FILTER_OTHERS_MODE      2

    #define AGC_MEAN16_UPBOUND          0x0119     // 1.256*0xE0
    #define AGC_MEAN16_LOWBOUND         0x0026     // (1/4)*0x9A
    #define AGC_MEAN16_UPBOUND_SECAM    0x0050     // 1.256*0x40
    #define AGC_MEAN16_LOWBOUND_SECAM   0x0010     // (1/4)*0x40
    #define AAGC_MEAN_UPBOUND           0x30
    #define AAGC_MEAN_LOWBOUND          0x16
    #define DAGC_ENABLE_RATIO           (3/32)
    #define DAGC_DISABLE_RATIO          (1/16)
    #define ADC_REG_BASE            0x8100
    #define RF_REG_BASE             0x9000
    #define DBB1_REG_BASE           0x9100
    #define DBB2_REG_BASE           0x9200
    #define DBB3_REG_BASE           0x9300
    #define VIF_PWR                 0x8100
    #define VIF_VCO_PWR             0x8100
    #define VIF_VCOREG_PWR          0x8100
    #define VIF_PLL_PWR             0x8100
    #define VIF_CBC_PWR             0x8100
    #define VIF_CBC_PWRS            0x8100
    #define VIF_TAGC_PWR            0x8100
    #define VIF_PWR_PGA2S           0x8101
    #define VIF_PWR_LPFS            0x8101
    #define VIF_MXPWRS              0x8101
    #define VIF_PGPWRS              0x8101
    #define VIF_PWR_PGA2V           0x8101
    #define VIF_PWR_LPFV            0x8101
    #define VIF_MXPWRV              0x8101
    #define VIF_PGPWRV              0x8101
    #define VIF_PLL_R               0x8102
    #define VIF_CBC_BGR0            0x8102
    #define VIF_CBC_BGR1            0x8102
    #define VIF_PLL_RSTZ            0x8102
    #define VIF_PLLTPEN             0x8102
    #define VIF_PLL_TEST            0x8103
    #define VIF_PLL_ICPSW           0x8103
    #define VIF_PLL_ENLCKDET        0x8103
    #define VIF_PLL_M               0x8104
    #define VIF_PLL_MTEST           0x8104
    #define VIF_PLL_MSEL            0x8104
    #define VIF_TAGC_ODMODE         0x8104
    #define VIF_PLL_N               0x8105
    #define VIF_PLL_RDIV            0x8105
    #define VIF_PLL_RSEL            0x8105
    #define VIF_PLL_ICTRL           0x8106
    #define VIF_PLL_LPEX            0x8106
    #define VIF_PLL_ADD128U         0x8106
    #define VIF_PLL_PBYP            0x8106
    #define VIF_PLL_PSEL            0x8106
    #define VIF_PLL_FBBYP           0x8106
    #define VIF_VCO_R               0x8107
    #define VIF_VCOREG_SBIAS        0x8107
    #define VIF_VCO_REF             0x8107
    #define VIF_PLL_SBIAS           0x8107
    #define VIF_VCO_LP              0x8108
    #define VIF_VCO_LK              0x8108
    #define VIF_FCODE_EXT           0x810B
    #define VIF_RN_TUNE             0x810B
    #define VIF_FORCE_TUNE          0x810B
    #define VIF_CALIB_TUNE          0x810B
    #define VIF_MXCR                0x810C
    #define VIF_MXLOR               0x810C
    #define VIF_PGCR                0x810D
    #define VIF_TINENS              0x810D
    #define VIF_TINENV              0x810D
    #define VIF_ISW_PGA2            0x810E
    #define VIF_ISW_LPF             0x810E
    #define VIF_ISW_TUNE            0x810E
    #define VIF_IFTPENS             0x810F
    #define VIF_IFTPENV             0x810F
    #define VIF_MXTPENS             0x810F
    #define VIF_MXTPENV             0x810F
    #define VIF_PGTPENS             0x810F
    #define VIF_PGTPENV             0x810F
    #define VIF_MXTPS               0x8110
    #define VIF_PGTPA               0x8110
    #define VIF_TAGC_TAFC_NRZDATA   0x8110
    #define VIF_TESTENBS            0x8111
    #define VIF_TESTENBV            0x8111
    #define VIF_TEN_LPFS            0x8111
    #define VIF_TEN_LPFV            0x8111
    #define VIF_XTAL_BYP            0x8111
    #define TAGC_EN_KEY             0x8114
    #define TAGC_INVCLK             0x8116
    #define TAGC_TAFC_OUTR          0x8116
    #define VIF_BYPASS              0x8119
    #define SIF_BYPASS              0x8119
    #define VIF_LOCK                0x811A
    #define VIF_VCTRL_UNDER         0x811A
    #define VIF_VCTRL_OVER          0x811A
    #define VIF_FCODE_OUT           0x811D
    #define VIF_STOPCAL_TUNE        0x811D
    #define VIF_TB                  0x8122
    #define VIF_TESTPGA1ENBS        0x8123
    #define VIF_TESTPGA1ENBV        0x8123
    #define VIF_VREF                0x8124
    #define VIF_CBCTPEN             0x8126
    #define VIF_LPFS_BW             0x812A
    #define VIF_LPFTUNE_XSEL        0x812A
    #define VIF_PGA1GAINS_SRC       0x812A
    #define VIF_PGA2S_HG            0x812A
    #define VIF_FCAL_DIV            0x812C
    #define VIF_TUNEC               0x812D
    #define ADC0_TSTX               0x813E
    #define ADC1_TSTX               0x813F
    #define PWDNA0                  0x8140
    #define PWDNA1                  0x8140
    #define PWDN_ADC0REF            0x8140
    #define PWDN_ADC1REF            0x8140
    #define PWDN_CORE               0x8140
    #define ADC0_ICTRL              0x8142
    #define ADC1_ICTRL              0x8144
    #define ADC0_VCTRL              0x8146
    #define ADC1_VCTRL              0x8146
    #define BP0                     0x8148
    #define BMA0                    0x8148
    #define BP1                     0x8149
    #define BMA1                    0x8149
    #define RDAC_ICTRL0             0x814A
    #define RDAC_ICTRL1             0x814A
    #define ADCREF0                 0x814C
    #define ADCREF1                 0x814E
    #define TST0                    0x8150
    #define TST1                    0x8151
    #define TST_REF                 0x8152
    #define ADC_OFFSET_I            0x8154
    #define ADC_OFFSET_Q            0x8156
    #define ADCIN_I                 0x8158
    #define ADCIN_Q                 0x815A
    #define ADCIN_SIGN              0x815C
    #define EXT_ADC                 0x815C
    #define ADC_IQ_SWAP             0x815C
    #define ADCD_FRZ                0x815D
    #define ADC_RDSEL               0x815D
    #define ADC_PLL_DEBUG_SEL       0x815D
    #define ADC0_DEC                0x815E
    #define ADC1_DEC                0x815E
    #define GC_MPLLIN_ADCLKSEL      0x8160
    #define GC_MPLLIN_ENHALFVCO     0x8160
    #define GC_MPLLIN_ICTRL         0x8160
    #define GC_MPLLIN_INDIV1ST      0x8162
    #define GC_MPLLIN_INDIV2ND      0x8163
    #define GC_MPLLIN_LOOPDIV1ST    0x8164
    #define GC_MPLLIN_LOOPDIV2ND    0x8165
    #define GC_MPLLIN_OUTDIV1ST     0x8166
    #define GC_MPLLIN_OUTDIV2ND     0x8167
    #define GC_MPLLIN_PORST         0x8168
    #define GC_MPLLIN_RESET         0x8168
    #define GC_MPLLIN_VCOOFSET      0x8168
    #define GC_MPLLXTAL_EN          0x8168
    #define GC_MPLLXTAL_GAIN        0x8168
    #define PD_MPLLIN               0x816A
    #define PD_MPLLDIV5             0x816A
    #define TEST_MPLLIN             0x816C
    #define GC_MPLLXTAL_AMP         0x816D
    #define RO_MPLLHIGHIN           0x816E
    #define RO_MPLLLOCKIN           0x816E
    #define RO_BOND_MODE            0x816E
    #define AAMUX                   0x8170
    #define AMUXTST                 0x8171
    #define VAMUX                   0x8172
    #define VCLP_D                  0x8173
    #define VIF_ENZ_AUD             0x8174
    #define VIF_ENZ_VD              0x8174
    #define VMUXTST                 0x8175
    #define PADTST                  0x8176

    ///////////////////////////////////////////////////////
    // [RF bank register]
    ///////////////////////////////////////////////////////
    #define VIF_VCO_BANK_W          0x9008
    #define VIF_PLL_CPINIT_W        0x9008
    #define VIF_CAL_START           0x9008
    #define VIF_PGA1GAINS_W         0x9009
    #define VIF_PGA1GAINV_W         0x9009
    #define VIF_GAIN_PGA2S_W        0x900A
    #define VIF_GAIN_PGA2V_W        0x900A
    #define TAGC_W_L                0x9012
    #define TAGC_W_H                0x9013
    #define TAGC_TEST_EN            0x9016
    #define TAGC_POLARITY           0x9016
    #define TAGC_SEL_DECIMATE_NUM   0x9017
    #define TAGC_DITHER_SHIFT       0x9017
    #define TAGC_SEL_SECONDER       0x9017
    #define TAGC_DITHER_EN          0x9017
    #define OREN_PGA2_S             0x9019
    #define OREN_PGA1_S             0x9019
    #define OREN_PGA2_V             0x9019
    #define OREN_PGA1_V             0x9019
    #define OREN_VCO_BANK           0x9019
    #define OREN_TAGC               0x9019
    #define VIF_VCO_BANK            0x901A
    #define VIF_PLL_CPINIT          0x901A
    #define VIF_VCOCAL_FAIL         0x901A
    #define VIF_PGA1GAINS           0x901B
    #define VIF_PGA1GAINV           0x901B
    #define VIF_GAIN_PGA2S          0x901C
    #define VIF_GAIN_PGA2V          0x901C
    #define VIF_CAL_FINISH          0x901D
    #define VIF_CAL_GAP             0x901E
    #define VSYNC_VD_MASK           0x9020
    #define VSYNC_VD_POLARITY       0x9020
    #define VSYNC_OVERRIDE          0x9021
    #define TAGC_DAC_TES_IN         0x9028
    #define VIF_PGA2V_HG_OV         0x902D
    #define VIF_PGA2S_HG_OV         0x902D
    #define CLAMPGAIN_RSTZ                  0x9040
    #define CLAMPGAIN_BYPASS                0x9040
    #define CLAMPGAIN_EN                    0x9040
    #define CLAMPGAIN_SEL                   0x9040
    #define CLAMPGAIN_STATUS_FREEZE         0x9040
    #define CLAMPGAIN_SYNCBOTT_REF          0x9042
    #define CLAMPGAIN_SYNCHEIGHT_REF        0x9043
    #define CLAMPGAIN_KC                    0x9044
    #define CLAMPGAIN_KG                    0x9044
    #define CLAMPGAIN_CLAMP_OREN            0x9045
    #define CLAMPGAIN_GAIN_OREN             0x9045
    #define CLAMPGAIN_CLAMP_OVERWRITE       0x9046
    #define CLAMPGAIN_GAIN_OVERWRITE        0x9048
    #define CLAMPGAIN_CLAMP_MIN             0x904A
    #define CLAMPGAIN_CLAMP_MAX             0x904B
    #define CLAMPGAIN_GAIN_MIN              0x904C
    #define CLAMPGAIN_GAIN_MAX              0x904D
    #define CLAMPGAIN_SYNCBOTTOM_OFFSET     0x904E
    #define CLAMPGAIN_RATIO                 0x904F
    #define CLAMPGAIN_SYNCBOTTOM_CNT        0x9050
    #define CLAMPGAIN_PORCH_CNT             0x9052
    #define CLAMPGAIN_PEAK_MEAN             0x9054
    #define CLAMPGAIN_SYNCBOTTOM_MEAN       0x9056
    #define CLAMPGAIN_PORCH_MEAN            0x9058
    #define CLAMPGAIN_CLAMP                 0x905A
    #define CLAMPGAIN_GAIN                  0x905C
    #define VSYNC_RSTZ                      0x9080
    #define VSYNC_ENABLE                    0x9080
    #define VSYNC_LPF_SEL                   0x9080
    #define VSYNC_DET_DATAIN_SEL            0x9080
    #define VSYNC_EXT                       0x9080
    #define VSYNC_OFFSET                    0x9082
    #define VSYNC_CNT                       0x9083
    #define VSYNC_VSYNC_CNT                 0x9084
    #define VSYNC_BYPASS_CNT                0x9085
    #define VSYNC_MIN_CNT                   0x9086
    #define VIF_VADC_DEC                    0x90AA
    #define VIF_AADC_DEC                    0x90AA
    #define VIF_VDAC_OUT_SEL                0x90C0
    #define VIF_VDAC_ENABLE                 0x90C0
    #define VIF_VDAC_MSB_INV                0x90C0
    #define VIF_VDAC_CLK_INV                0x90C0
    #define VIF_VDAC_TESTBUS_SWAP           0x90C0
    #define VIF_VDAC_RAMP_OUT_MAX_L         0x90C2
    #define VIF_VDAC_RAMP_OUT_MAX_H         0x90C3
    #define VIF_VDAC_RAMP_OUT_MIN_L         0x90C4
    #define VIF_VDAC_RAMP_OUT_MIN_H         0x90C5
    #define VIF_VDAC_FORCE_DATA_L           0x90C6
    #define VIF_VDAC_FORCE_DATA_H           0x90C7
    #define VIF_ADAC_OUT_SEL                0x90C8
    #define VIF_ADAC_ENABLE                 0x90C8
    #define VIF_ADAC_MSB_INV                0x90C8
    #define VIF_ADAC_CLK_INV                0x90C8
    #define VIF_ADAC_TESTBUS_SWAP           0x90C8
    #define VIF_ADAC_RAMP_OUT_MAX_L         0x90CA
    #define VIF_ADAC_RAMP_OUT_MAX_H         0x90CB
    #define VIF_ADAC_RAMP_OUT_MIN_L         0x90CC
    #define VIF_ADAC_RAMP_OUT_MIN_H         0x90CD
    #define VIF_ADAC_FORCE_DATA_L           0x90CE
    #define VIF_ADAC_FORCE_DATA_H           0x90CF
    #define TIMER_MAX                       0x90E0
    #define TIMER                           0x90E2
    #define DCXO_RSTZ                       0x90EA
    #define DCXO_MODE                       0x90EA
    #define DCXO_DIT_SEL                    0x90EA
    #define DCXO_SYNC_LOAD                  0x90EB
    #define DCXO_TRI_ANG_MIN                0x90EC
    #define DCXO_TRI_ANG_MAX                0x90ED
    #define DCXO_FORCE                      0x90EE
    #define DCXO_STEP_CNT                   0x90F0
    #define DCXO_CODE                       0x90F4

    ///////////////////////////////////////////////////////
    // [DBB1 bank register]
    ///////////////////////////////////////////////////////
    #define VIF_SOFT_RSTZ           0x9100
    #define AFC_SOFT_RSTZ           0x9100
    #define FILTER_SOFT_RSTZ        0x9100
    #define AGC_SOFT_RSTZ           0x9100
    #define DAGC1_SOFT_RSTZ         0x9100
    #define DAGC2_SOFT_RSTZ         0x9100
    #define AAGC_SOFT_RSTZ          0x9100
    #define ADAGC_SOFT_RSTZ         0x9100
    #define MODULATION_TYPE         0x9102
    #define DEBUG_CLK_FINAL_SEL     0x9102
    #define BYPASS_N_A4             0x9102
    #define BYPASS_CR_NOTCH2        0x9102
    #define AUDIO_BYPASS            0x9104
    #define LOCK_LEAKY_FF_SEL       0x9106
    #define VNCO_INV_OREN           0x9106
    #define VNCO_INV_OV             0x9106
    #define INT_EN                  0x9107
    #define CR_CODIC_TH_L           0x9108
    #define CR_CODIC_TH_H           0x9109
    #define BYPASS_SOS11            0x910A
    #define BYPASS_SOS12            0x910A
    #define BYPASS_CO_A_REJ         0x910A
    #define CO_A_REJ_NTSC           0x910A
    #define BYPASS_SOS21            0x910A
    #define BYPASS_SOS22            0x910A
    #define BYPASS_SOS31            0x910B
    #define BYPASS_SOS32            0x910B
    #define BYPASS_2ND_A_BP         0x910B
    #define A_BP_NTSC               0x910B
    #define BYPASS_A_SOS1           0x910B
    #define BYPASS_A_LPF_BG         0x910B
    #define ADAGC_IN_SEL            0x910B
    #define BYPASS_NYQUIST_ACI      0x910B

    #define CR_DL_A                 0x9114
    #define CR_DL_A_BYPASS          0x9114
    #define CR_F_OFFSET             0x9115
    #define CR_PD_ERR_MAX_L         0x9116
    #define CR_PD_ERR_MAX_H         0x9117
    #define CR_KL_L                 0x9118
    #define CR_KL_H                 0x9119
    #define CR_NOTCH_A1_L           0x911A
    #define CR_NOTCH_A1_H           0x911B
    #define CR_NOTCH_A2_L           0x911C
    #define CR_NOTCH_A2_H           0x911D
    #define CR_NOTCH_B1_L           0x911E
    #define CR_NOTCH_B1_H           0x911F
    #define CR_ANCO_SEL             0x9120
    #define CR_PD_MODE              0x9120
    #define CR_PD_X2                0x9120
    #define CR_INV                  0x9120
    #define CR_LPF_SEL              0x9120
    #define CR_LF_FF_RSTZ           0x9120
    #define CR_K_SEL                0x9120
    #define CR_PD_LIMITER           0x9120
    #define CR_KP_SW                0x9122
    #define CR_KI_SW                0x9122
    #define CR_KF_SW                0x9123
    #define CR_RATE                 0x9124
    #define CR_KP1_HW               0x9128
    #define CR_KI1_HW               0x9128
    #define CR_KF1_HW               0x9129
    #define CR_KP2_HW               0x912A
    #define CR_KI2_HW               0x912A
    #define CR_KF2_HW               0x912B
    #define CR_LOCK_TH_L            0x912C
    #define CR_LOCK_TH_H            0x912D
    #define CR_FOE_SCAL_FACTOR_L    0x912E
    #define CR_FOE_SCAL_FACTOR_H    0x912F
    #define CR_LOCK_NUM             0x9130
    #define CR_UNLOCK_NUM           0x9134
    #define CR_FOE                  0x9138
    #define CR_LOCK_STATUS          0x9139
    #define CR_LOCK_LEAKY_FF_I      0x913A
    #define CR_LOCK_LEAKY_FF_Q      0x913C
    #define CR_NOTCH2_A1_L          0x913E
    #define CR_NOTCH2_A1_H          0x913F
    #define CR_NOTCH2_A2_L          0x9140
    #define CR_NOTCH2_A2_H          0x9141
    #define CR_NOTCH2_B1_L          0x9142
    #define CR_NOTCH2_B1_H          0x9143
    #define CR_LF_FF_RPT            0x9144

    #define ADC_43M                 0x9180
    #define BYPASS_DC               0x9180
    #define BYPASS_N_A1             0x9180
    #define BYPASS_N_A2             0x9180
    #define NYQUIST_ACI_REJ_EN      0x9180
    #define BYPASS_IMAGE_REJ        0x9180
    #define ACI_REJ_NTSC            0x9180
    #define A_BP_OUT_X2             0x9180
    #define BYPASS_A_DC             0x9181
    #define BYPASS_1ST_A_BP         0x9181
    #define BYPASS_A_NOTCH          0x9181
    #define AD_SIGNED_UNSIGNED      0x9181
    #define VD_SIGNED_UNSIGNED      0x9181
    #define BYPASS_N_A3             0x9181
    #define DC_C                    0x9182
    #define A_DC_C                  0x9183
    #define N_A1_C0_L               0x9184
    #define N_A1_C0_H               0x9185
    #define N_A1_C1_L               0x9186
    #define N_A1_C1_H               0x9187
    #define N_A1_C2_L               0x9188
    #define N_A1_C2_H               0x9189
    #define N_A2_C0_L               0x918A
    #define N_A2_C0_H               0x918B
    #define N_A2_C1_L               0x918C
    #define N_A2_C1_H               0x918D
    #define N_A2_C2_L               0x918E
    #define N_A2_C2_H               0x918F
    #define AN_C0_L                 0x9190
    #define AN_C0_H                 0x9191
    #define AN_C1_L                 0x9192
    #define AN_C1_H                 0x9193
    #define AN_C2_L                 0x9194
    #define AN_C2_H                 0x9195
    #define SOS11_C0_L              0x9196
    #define SOS11_C0_H              0x9197
    #define SOS11_C1_L              0x9198
    #define SOS11_C1_H              0x9199
    #define SOS11_C2_L              0x919A
    #define SOS11_C2_H              0x919B
    #define SOS11_C3_L              0x919C
    #define SOS11_C3_H              0x919D
    #define SOS11_C4_L              0x919E
    #define SOS11_C4_H              0x919F
    #define SOS12_C0_L              0x91A0
    #define SOS12_C0_H              0x91A1
    #define SOS12_C1_L              0x91A2
    #define SOS12_C1_H              0x91A3
    #define SOS12_C2_L              0x91A4
    #define SOS12_C2_H              0x91A5
    #define N_A3_C0_L               0x91A6
    #define N_A3_C0_H               0x91A7
    #define N_A3_C1_L               0x91A8
    #define N_A3_C1_H               0x91A9
    #define N_A3_C2_L               0x91AA
    #define N_A3_C2_H               0x91AB
    #define N_A4_C0_L               0x91AC
    #define N_A4_C0_H               0x91AD
    #define N_A4_C1_L               0x91AE
    #define N_A4_C1_H               0x91AF
    #define N_A4_C2_L               0x91B0
    #define N_A4_C2_H               0x91B1
    #define SOS12_C3_L              0x91B2
    #define SOS12_C3_H              0x91B3
    #define SOS12_C4_L              0x91B4
    #define SOS12_C4_H              0x91B5
    #define SOS21_C0_L              0x91B6
    #define SOS21_C0_H              0x91B7
    #define SOS21_C1_L              0x91B8
    #define SOS21_C1_H              0x91B9
    #define SOS21_C2_L              0x91BA
    #define SOS21_C2_H              0x91BB
    #define SOS21_C3_L              0x91BC
    #define SOS21_C3_H              0x91BD
    #define SOS21_C4_L              0x91BE
    #define SOS21_C4_H              0x91BF
    #define SOS22_C0_L              0x91C0
    #define SOS22_C0_H              0x91C1
    #define SOS22_C1_L              0x91C2
    #define SOS22_C1_H              0x91C3
    #define SOS22_C2_L              0x91C4
    #define SOS22_C2_H              0x91C5
    #define SOS22_C3_L              0x91C6
    #define SOS22_C3_H              0x91C7
    #define SOS22_C4_L              0x91C8
    #define SOS22_C4_H              0x91C9
    #define SOS31_C0_L              0x91CA
    #define SOS31_C0_H              0x91CB
    #define SOS31_C1_L              0x91CC
    #define SOS31_C1_H              0x91CD
    #define SOS31_C2_L              0x91CE
    #define SOS31_C2_H              0x91CF
    #define SOS31_C3_L              0x91D0
    #define SOS31_C3_H              0x91D1
    #define SOS31_C4_L              0x91D2
    #define SOS31_C4_H              0x91D3
    #define SOS32_C0_L              0x91D4
    #define SOS32_C0_H              0x91D5
    #define SOS32_C1_L              0x91D6
    #define SOS32_C1_H              0x91D7
    #define SOS32_C2_L              0x91D8
    #define SOS32_C2_H              0x91D9
    #define SOS32_C3_L              0x91DA
    #define SOS32_C3_H              0x91DB
    #define SOS32_C4_L              0x91DC
    #define SOS32_C4_H              0x91DD
    #define A_SOS1_C0_L             0x91DE
    #define A_SOS1_C0_H             0x91DF
    #define A_SOS1_C1_L             0x91E0
    #define A_SOS1_C1_H             0x91E1
    #define A_SOS1_C2_L             0x91E2
    #define A_SOS1_C2_H             0x91E3
    #define A_SOS1_C3_L             0x91E4
    #define A_SOS1_C3_H             0x91E5
    #define A_SOS1_C4_L             0x91E6
    #define A_SOS1_C4_H             0x91E7
    #define A_SOS2_C0_L             0x91E8
    #define A_SOS2_C0_H             0x91E9
    #define A_SOS2_C1_L             0x91EA
    #define A_SOS2_C1_H             0x91EB
    #define A_SOS2_C2_L             0x91EC
    #define A_SOS2_C2_H             0x91ED
    #define A_SOS2_C3_L             0x91EE
    #define A_SOS2_C3_H             0x91EF
    #define A_SOS2_C4_L             0x91F0
    #define A_SOS2_C4_H             0x91F1
    #define A_SOS3_C0_L             0x91F2
    #define A_SOS3_C0_H             0x91F3
    #define A_SOS3_C1_L             0x91F4
    #define A_SOS3_C1_H             0x91F5
    #define A_SOS3_C2_L             0x91F6
    #define A_SOS3_C2_H             0x91F7
    #define A_SOS3_C3_L             0x91F8
    #define A_SOS3_C3_H             0x91F9
    #define A_SOS3_C4_L             0x91FA
    #define A_SOS3_C4_H             0x91FB
    #define FIRMWARE_VERSION_L      0x91FE
    #define FIRMWARE_VERSION_H      0x91FF

    ///////////////////////////////////////////////////////
    // [DBB2 bank register]
    ///////////////////////////////////////////////////////
    #define AGC_ENABLE              0x9200
    #define AGC_MODE                0x9200
    #define AGC_MEAN_SEL            0x9200
    #define AGC_GAIN_SLOPE          0x9200
    #define AGC_VSYNC_ENA           0x9200
    #define AGC_VSYNC_ENB           0x9200
    #define AGC_VSYNC_SEL           0x9200
    #define AGC_VSYNC_POL           0x9201
    #define AGC_IN_SEL              0x9201
    #define AGC_ABS_DATA_IN_SEL     0x9201
    #define AGC_DBB_VVGA_SEL        0x9201
    #define AGC_DBB_AVGA_SEL        0x9201
    #define AGC_VSYNC_PULSE         0x9201
    #define AGC_LINE_CNT_L          0x9202
    #define AGC_LINE_CNT_H          0x9203
    #define AGC_PORCH_CNT_L         0x9204
    #define AGC_PORCH_CNT_H         0x9205
    #define AGC_PEAK_CNT_L          0x9206
    #define AGC_PEAK_CNT_H          0x9207
    #define AGC_REF                 0x9208
    #define AGC_K                   0x920A
    #define AGC_OFFSET              0x920B
    #define AGC_GAIN_OREN           0x920C
    #define AGC_DBB_VVGA_OREN       0x920C
    #define AAGC_DBB_VVGA_OREN      0x920C
    #define AGC_PGA1_OV             0x920E
    #define AGC_PGA2_OV             0x920F
    #define AGC_VGA_OV_L            0x9210
    #define AGC_VGA_OV_H            0x9211
    #define AGC_PGA1_MIN            0x9212
    #define AGC_PGA1_MAX            0x9213
    #define AGC_PGA2_MIN            0x9214
    #define AGC_PGA2_MAX            0x9215
    #define AGC_VGA_MIN_L           0x9216
    #define AGC_VGA_MIN_H           0x9217
    #define AGC_VGA_MAX_L           0x9218
    #define AGC_VGA_MAX_H           0x9219
    #define AGC_DBB_VVGA_OV_L       0x921A
    #define AGC_DBB_VVGA_OV_H       0x921B
    #define AAGC_DBB_VVGA_OV_L      0x921C
    #define AAGC_DBB_VVGA_OV_H      0x921D
    #define AGC_MEAN0               0x9220
    #define AGC_MEAN16              0x9222
    #define AGC_MEAN256             0x9224
    #define AGC_DIFF                0x9226
    #define AGC_VGA                 0x9228
    #define AGC_PGA1A               0x922A
    #define AGC_PGA2A               0x922B
    #define AGC_PGA1B               0x922C
    #define AGC_PGA2B               0x922D
    #define AGC_PGA1C               0x922E
    #define AGC_PGA2C               0x922F
    #define AGC_VSYNC_IN            0x9230
    #define AGC_HS_FOUND            0x9230

    #define AAGC_ENABLE             0x92A0
    #define AAGC_LINE_CNT           0x92A2
    #define AAGC_GAIN_OREN          0x92A4
    #define AAGC_VPGA_OREN          0x92A4
    #define AAGC_DEC                0x92A5
    #define AAGC_PGA1_OV            0x92A6
    #define AAGC_PGA2_OV            0x92A7
    #define AAGC_PGA1_MIN           0x92A8
    #define AAGC_PGA1_MAX           0x92A9
    #define AAGC_PGA2_MIN           0x92AA
    #define AAGC_PGA2_MAX           0x92AB
    #define AAGC_MEAN_MIN           0x92AC
    #define AAGC_MEAN_MAX           0x92AD
    #define AAGC_MEAN               0x92AE
    #define AAGC_PEAKMEAN           0x92B0
    #define AAGC_PGA1               0x92B2
    #define AAGC_PGA2               0x92B3
    #define AAGC_CNT                0x92B4

    #define DEBUG_PORT              0x92E0
    #define DEBUG_CLK_SEL           0x92E0
    #define DEBUG_CLK_INV           0x92E0
    #define DEBUG_SIGNED_UNSIGNED   0x92E0
    #define DEBUG_MODULE            0x92E1
    #define DEBUG_SWITCH            0x92E1
    #define DEBUG_V_A               0x92E1
    #define DEBUG_FREQ_L            0x92E2
    #define DEBUG_FREQ_H            0x92E3


    #if 1
    #define IF_FREQ_45_75           0x01//IF_FREQ_MN
    #define IF_FREQ_38_90           0x02//IF_FREQ_B
    #define IF_FREQ_38_00           0x03//IF_FREQ_PAL_38
    #define IF_BASE_FREQ            IF_FREQ_38_90  //IF_FREQ_38_00  // IF_FREQ_38_90
    #ifndef VIF_TOP
    #define VIF_TOP                 5  // TOP range 0~6
    #endif
    #define VIF_VGA_MAXIMUM         0x4000
    #define GAIN_DISTRIBUTION_THR   0x3000
    #endif

    ///////////////////////////////////////////////////////
    // [DBB3 bank register]
    ///////////////////////////////////////////////////////
    #define DAGC1_ENABLE                0x9300
    #define DAGC1_BYPASS                0x9300
    #define DAGC1_GAIN0_FB_EN           0x9300
    #define DAGC2_ENABLE                0x9301
    #define DAGC2_BYPASS                0x9301
    #define DAGC2_GAIN0_FB_EN           0x9301
    #define DAGC1_GAIN_OVERWRITE_L      0x9302
    #define DAGC1_GAIN_OVERWRITE_H      0x9303
    #define DAGC1_OREN                  0x9303
    #define DAGC2_GAIN_OVERWRITE_L      0x9304
    #define DAGC2_GAIN_OVERWRITE_H      0x9305
    #define DAGC2_OREN                  0x9305
    #define DAGC1_REF                   0x9306
    #define DAGC2_REF                   0x9307
    #define DAGC1_LEVEL_SHIFT           0x9308
    #define DAGC2_LEVEL_SHIFT           0x9309
    #define DAGC1_RATIO                 0x930A
    #define DAGC2_RATIO                 0x930B
    #define DAGC1_PEAK_CNT_L            0x930C
    #define DAGC1_PEAK_CNT_H            0x930D
    #define DAGC2_PEAK_CNT_L            0x930E
    #define DAGC2_PEAK_CNT_H            0x930F
    #define DAGC1_PORCH_CNT_L           0x9310
    #define DAGC1_PORCH_CNT_H           0x9311
    #define DAGC2_PORCH_CNT_L           0x9312
    #define DAGC2_PORCH_CNT_H           0x9313
    #define DAGC1_MEAN                  0x9314
    #define DAGC1_VAR                   0x9316
    #define DAGC2_MEAN                  0x9318
    #define DAGC2_VAR                   0x931A
    #define DAGC1_GAIN                  0x931C
    #define DAGC2_GAIN                  0x931E
    #define DAGC1_SYNCHEIGHT            0x9320
    #define DAGC1_VSYNC                 0x9321
    #define DAGC2_SYNCHEIGHT            0x9322
    #define DAGC2_VSYNC                 0x9323
    #define DAGC1_LPF_DELAY_0           0x9324
    #define DAGC2_LPF_DELAY_0           0x9326
    #define DAGC1_OFFSET                0x9328
    #define DAGC2_OFFSET                0x9329

    #define ADAGC_ENABLE                0x9380
    #define ADAGC_BYPASS                0x9380
    #define ADAGC_PEAK_MEAN_SEL         0x9380
    #define ADAGC_K                     0x9381
    #define ADAGC_CNT                   0x9382
    #define ADAGC_DEC                   0x9386
    #define ADAGC_LINE_CNT              0x9387
    #define ADAGC_REF                   0x9388
    #define ADAGC_GAIN_OREN             0x938A
    #define ADAGC_GAIN_OV               0x938C
    #define ADAGC_MEAN                  0x93A0
    #define ADAGC_PEAK                  0x93A1
    #define ADAGC_GAIN                  0x93A2

    //--------------------------------------------------------------------
    //-------------------------MSB122x.h jeff.chu ------------------------
    //--------------------------------------------------------------------
#define     DEMOD_SLAVE_ID2          0x32

    //#define DEMOD_DYNAMIC_SLAVE_ID    0x32
    //#define DEMOD_DYNAMIC_SLAVE_ID_2    0x72
    //#define DEMOD_DYNAMIC_SLAVE_ID_3    0xB2
    //#define DEMOD_DYNAMIC_SLAVE_ID_4    0xF2
    #define DEMOD_ADDR_H                0x00
    #define DEMOD_ADDR_L                0x01
    #define DEMOD_WRITE_REG             0x02
    #define DEMOD_WRITE_REG_EX          0x03
    #define DEMOD_READ_REG              0x04
    #define DEMOD_RAM_CONTROL           0x05
    #define MSB122x_IIC_CONTROL         0x8400
    #define MSB122x_IIC_SCL_CLK         0x8401
    #define MSB122x_IIC_READ_DATA       0x8402
    #define MSB122x_IIC_STATUS          0x8403
    #define MSB122x_IIC_WRITE_DATA      0x8404
    //#define COFDM_DEM_I2C_ID            DEMOD_DYNAMIC_SLAVE_ID_1
    //#define COFDM_DEM_I2C_ID_2          DEMOD_DYNAMIC_SLAVE_ID_2
    //#define COFDM_DEM_I2C_ID_3          DEMOD_DYNAMIC_SLAVE_ID_3
    //#define COFDM_DEM_I2C_ID_4          DEMOD_DYNAMIC_SLAVE_ID_4
    #define MSB122x_REG_INVERSION       0x8024

#define DTV_SCAN_AUTO_FINE_TUNE_ENABLE 0 //jeff temp 0729
#if  DTV_SCAN_AUTO_FINE_TUNE_ENABLE
    #define DEMOD_CAPTURE_RANGE_500_K   500
    #define DEMOD_CAPTURE_RANGE_SIZE    DEMOD_CAPTURE_RANGE_500_K
#endif

    #define REG_CMD_CTRL                0x809C
    #define REG_DTA_CTRL                0x809D
    #define REG_CMD_ADDR                0x809E
    #define REG_CMD_DATA                0x809F
    #define _REG_START                  REG_CMD_CTRL
    #define _REG_END                    REG_CMD_CTRL
    #define _REG_DRQ                    REG_DTA_CTRL
    #define _REG_FSM                    REG_CMD_CTRL
    #define _REG_ERR                    REG_DTA_CTRL
    #define _BIT_START                  0x02
    #define _BIT_END                    0x01
    #define _BIT_DRQ                    0x01
    #define _BIT_FSM                    0x08
    #define _BIT_ERR                    0x80
    #define MSVIF_0702_ENABLE           1
   // #define _IF_DEM_I2C_ID              0x32

/*@ </Definitions> @*/

typedef enum
{
    VIF_SOUND_BG,
    VIF_SOUND_I,
    VIF_SOUND_DK1,
    VIF_SOUND_DK2,
    VIF_SOUND_DK3,
    VIF_SOUND_L,
    VIF_SOUND_LL,
    VIF_SOUND_MN,
    VIF_SOUND_NUMS
}VIFSoundSystem;

typedef enum
{
    IF_FREQ_3395, // SECAM-L'
    IF_FREQ_3800, // PAL
    IF_FREQ_3890, // PAL
    IF_FREQ_3950, // only for PAL-I
    IF_FREQ_4575, // NTSC-M/N
    IF_FREQ_5875, // NTSC-M/N
    IF_FREQ_NUMS
}IfFrequencyType;

typedef enum
{
    dac_op_code = 0,
    dac_idac_ch0,
    dac_idac_ch1,

    DAC_PARAM_MAX_NUM
}
E_DAC_PARAM;

typedef enum
{
    DAC_RUN_CALI = 0,
    DAC_IDAC_ASSIGN,

    DAC_CMD_MAX_NUM
}
E_DAC_CMD;

typedef enum
{
    SET_IF_FREQ = 0,
    SET_SOUND_SYS,
    VIF_INIT,
    SET_VIF_HANDLER,
    VIF_TOP_ADJUST,

    VIF_CMD_MAX_NUM
}E_VIF_CMD;

typedef enum
{
    pc_op_code = 0,
    pc_if_freq,
    pc_sound_sys,
    pc_vif_vga_maximum_l,
    pc_vif_vga_maximum_h,
    pc_scan_mode,
    pc_vif_top,
    pc_gain_distribution_thr_l,
    pc_gain_distribution_thr_h,

    VIF_PARAM_MAX_NUM
}E_VIF_PARAM;

typedef enum
{
    // OP Mode Settings
    p_opmode_rfagc_en = 0,
    p_opmode_humdet_en,
    p_opmode_dcr_en,
    p_opmode_iqb_en,
    p_opmode_auto_iq_swap,
    p_opmode_auto_fsa_left,
    p_opmode_auto_rfmax,
    p_opmode_mode_forced,
    p_opmode_cp_forced,

    // Config Params
    pc_config_rssi,
    pc_config_zif,
    pc_config_fc_l,
    pc_config_fc_h,
    pc_config_fs_l,
    pc_config_fs_h,
    pc_config_bw,
    pc_config_fsa_left,
    pc_config_rfmax,
    pc_config_lp_sel,
    pc_config_cp,
    pc_config_mode,
    pc_config_iq_swap,
    pc_config_atv_system,
    pc_config_serial_ts,
    pc_config_ts_out_inv,
    pc_config_ts_data_swap,
    pc_config_icfo_range,
    // pc_config_ts_serial_clk,

    DVBT_PARAM_LEN,
} DVBT_Param;

typedef enum
{
    agc_ref_small = 0,
    agc_ref_large,
    agc_ref_aci,
    ripple_switch_th_l,
    ripple_switch_th_h,

    TUNED_PARAM_MAX_NUM
}E_TUNED_PARAM;

typedef enum
{
    TS_SERIAL_CLK_57p6M = 0,
    TS_SERIAL_CLK_72M = 2,

    TS_CLK_SEL_MAX_NUM,
}E_TS_CLK_SEL;

typedef enum
{
    _QPSK       = 0x0,
    _16QAM      = 0x1,
    _64QAM      = 0x2,
}E_CONSTEL;

typedef enum
{
    _CR1Y2      = 0x0,
    _CR2Y3      = 0x1,
    _CR3Y4      = 0x2,
    _CR5Y6      = 0x3,
    _CR7Y8      = 0x4,
}E_CODERATE;


typedef struct
{
    float    power_db;
    MAPI_U8        agc_val;
}S_IFAGC_SSI;

typedef struct
{
    float    attn_db;
    MAPI_U8        agc_err;
}S_IFAGC_ERR;

typedef struct
{
    float    power_db;
    MAPI_U8        sar3_val;
}S_RFAGC_SSI;

typedef struct
{
    MAPI_U8        constel;
    MAPI_U8        code_rate;
    float    p_ref;
}S_SSI_PREF;


/*@ <IncludeGuardEnd> @*/
#endif // #ifndef _MSB122x_H_
/*@ </IncludeGuardEnd> @*/
