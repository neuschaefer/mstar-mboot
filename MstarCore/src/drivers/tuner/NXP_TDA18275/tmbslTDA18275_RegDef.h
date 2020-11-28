/*
  Copyright (C) 2011 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA18275_RegDef.h
 *
 * \date          %modify_time%
 *
 * \author        TVFE SW Group
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA18275_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template
 *
 * \section info Change Information
 *
*/

/* File generated automatically from register description file */


#pragma once
#ifndef _TMBSL_TDA18275_REGDEF_H
#define _TMBSL_TDA18275_REGDEF_H

#ifdef __cplusplus
extern "C"
{
#endif


/*============================================================================*/
/* Registers definitions:                                                     */
/*============================================================================*/

#define TDA18275_REG_ADD_SZ                             (0x01)
#define TDA18275_REG_DATA_MAX_SZ                        (0x01)
#define TDA18275_REG_MAP_NB_BYTES                       (0x5B)

#define TDA18275_REG_DATA_LEN(_FIRST_REG, _LAST_REG)    ( (_LAST_REG.Address - _FIRST_REG.Address) + 1)

/* TDA18275 Register ID_byte_1 0x00 */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_1;
/* Ident_1 bit(s): type number information (MSB) */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_1__Ident_1;


/* TDA18275 Register ID_byte_2 0x01 */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_2;
/* Ident_2 bit(s): type number information (LSB) */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_2__Ident_2;


typedef enum _TDA18275_Fab_rev_Item_t {
    TDA18275_Fab_rev_SSMC = 0,		/*  SSMC   */
    TDA18275_Fab_rev_ICN8 = 1		/*  ICN8  */
} TDA18275_Fab_rev_t, *pTDA18275_Fab_rev_t;

/* TDA18275 Register ID_byte_3 0x02 */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_3;
/* Major_rev bit(s): device major revision */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_3__Major_rev;
/* Fab_rev bit(s): fabrication unit revision */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_3__Fab_rev;
/* Minor_rev bit(s): device minor revision */
extern const TDA18275_BitField_t gTDA18275_Reg_ID_byte_3__Minor_rev;


/* TDA18275 Register Thermo_byte_1 0x03 */
extern const TDA18275_BitField_t gTDA18275_Reg_Thermo_byte_1;
/* TM_D bit(s): junction temperature measurement */
extern const TDA18275_BitField_t gTDA18275_Reg_Thermo_byte_1__TM_D;


/* TDA18275 Register Thermo_byte_2 0x04 */
extern const TDA18275_BitField_t gTDA18275_Reg_Thermo_byte_2;
/* TM_ON bit(s): temperature sensor ON or OFF */
extern const TDA18275_BitField_t gTDA18275_Reg_Thermo_byte_2__TM_ON;


/* TDA18275 Register Power_state_byte_1 0x05 */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_1;
/* POR bit(s): Power On Reset bit */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_1__POR;
/* AGCs_Max bit(s): maximum gain status indicator */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_1__AGCs_Max;
/* AGCs_Lock bit(s): AGC convergence status indicator */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_1__AGCs_Lock;
/* Vsync_Lock bit(s): Vertical Blanking Interval status indicator */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_1__Vsync_Lock;
/* LO_Lock bit(s): PLL lock status indicator */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_1__LO_Lock;


typedef enum _TDA18275_power_state_mode_Item_t {
    TDA18275_power_state_mode_Normal = 0,		/*  Normal   */
    TDA18275_power_state_mode_Standby_Xtout = 1,		/*  Standby Xtout   */
    TDA18275_power_state_mode_Standby = 2,		/*  Standby   */
    TDA18275_power_state_mode_Image_Rejection_mode = 3		/*  Image Rejection mode  */
} TDA18275_power_state_mode_t, *pTDA18275_power_state_mode_t;

/* TDA18275 Register Power_state_byte_2 0x06 */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_2;
/* power_state_mode bit(s): selects the power state mode */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_state_byte_2__power_state_mode;


/* TDA18275 Register Power_Level_byte_1 0x07 */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_Level_byte_1;
/* Det6_level bit(s): Detector 6 level indicator */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_Level_byte_1__Det6_level;


/* TDA18275 Register IRQ_status 0x08 */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status;
/* IRQ_status bit(s): Interupt Request Status */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__IRQ_status;
/* MSM_IRCAL_End bit(s): Image Rejection Calibration completion */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__MSM_IRCAL_End;
/* XtalCal_End bit(s): Xtal oscillator calibration completion */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__XtalCal_End;
/* MSM_RSSI_End bit(s): RSSI measurement completion */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__MSM_RSSI_End;
/* MSM_RCCal_End bit(s): RC calibration completion */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__MSM_RCCal_End;
/* VCO_Ampl_End bit(s): VCO amplitude calibration completion */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__VCO_Ampl_End;
/* VCO_Freq_End bit(s): VCO frequency calibration completion */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_status__VCO_Freq_End;


/* TDA18275 Register IRQ_clear 0x0A */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear;
/* IRQ_Clear bit(s): Clear IRQ */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__IRQ_Clear;
/* MSM_IRCAL_Clear bit(s): Clear IRCAL */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__MSM_IRCAL_Clear;
/* XtalCal_Clear bit(s): Clear XtalCAL */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__XtalCal_Clear;
/* MSM_RSSI_Clear bit(s): Clear RSSI */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__MSM_RSSI_Clear;
/* MSM_RCCal_Clear bit(s): Clear RCCAL */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__MSM_RCCal_Clear;
/* VCO_Ampl_Clear bit(s): Clear VCO_Amp */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__VCO_Ampl_Clear;
/* VCO_Freq_Clear bit(s): Clear VCO_Freq */
extern const TDA18275_BitField_t gTDA18275_Reg_IRQ_clear__VCO_Freq_Clear;


typedef enum _TDA18275_GPIO2_Item_t {
    TDA18275_GPIO2_Off = 0,		/*  Off   */
    TDA18275_GPIO2_On = 1		/*  On  */
} TDA18275_GPIO2_t, *pTDA18275_GPIO2_t;

typedef enum _TDA18275_GPIO1_Item_t {
    TDA18275_GPIO1_Off = 0,		/*  Off   */
    TDA18275_GPIO1_On = 1		/*  On  */
} TDA18275_GPIO1_t, *pTDA18275_GPIO1_t;

/* TDA18275 Register Gpio_ctrl_byte 0x0C */
extern const TDA18275_BitField_t gTDA18275_Reg_Gpio_ctrl_byte;
/* GPIO2 bit(s): enables / disables GPO2 output */
extern const TDA18275_BitField_t gTDA18275_Reg_Gpio_ctrl_byte__GPIO2;
/* GPIO1 bit(s): enables / disables GPO1 output */
extern const TDA18275_BitField_t gTDA18275_Reg_Gpio_ctrl_byte__GPIO1;


typedef enum _TDA18275_AGC1_Top_Strategy_Item_t {
    TDA18275_AGC1_Top_Strategy_No_dynamic_TOP_change = 0,		/*  No dynamic TOP change   */
    TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_10_dB = 1,		/*  -4 dB TOP Do for LNA gain &gt; 10 dB   */
    TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_13_dB = 2,		/*  -4 dB TOP Do for LNA gain &gt; 13 dB   */
    TDA18275_AGC1_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_16_dB = 3,		/*  -4 dB TOP Do for LNA gain &gt; 16 dB   */
    TDA18275_AGC1_Top_Strategy_n6_dB_TOP_Do_for_LNA_gain_sup_10_dB = 4,		/*  -6 dB TOP Do for LNA gain &gt; 10 dB   */
    TDA18275_AGC1_Top_Strategy_n6_dB_TOP_Do_for_LNA_gain_sup_13_dB = 5,		/*  -6 dB TOP Do for LNA gain &gt; 13 dB   */
    TDA18275_AGC1_Top_Strategy_n6_dB_TOP_Do_for_LNA_gain_sup_16_dB = 6,		/*  -6 dB TOP Do for LNA gain &gt; 16 dB   */
    TDA18275_AGC1_Top_Strategy_n8_dB_TOP_Do_for_LNA_gain_sup_13_dB = 7		/*  -8 dB TOP Do for LNA gain &gt; 13 dB  */
} TDA18275_AGC1_Top_Strategy_t, *pTDA18275_AGC1_Top_Strategy_t;

typedef enum _TDA18275_AGC1_Top_Item_t {
    TDA18275_AGC1_Top_94_88_dBuVrms = 0,		/*  94/88 dBuVrms  */
    TDA18275_AGC1_Top_96_90_dBuVrms = 1,		/*  96/90 dBuVrms  */
    TDA18275_AGC1_Top_98_92_dBuVrms = 2,		/*  98/92 dBuVrms  */
    TDA18275_AGC1_Top_100_94_dBuVrms = 3,		/*  100/94 dBuVrms  */
    TDA18275_AGC1_Top_102_96_dBuVrms = 4,		/*  102/96 dBuVrms  */
    TDA18275_AGC1_Top_104_98_dBuVrms = 5,		/*  104/98 dBuVrms  */
    TDA18275_AGC1_Top_106_100_dBuVrms = 6,		/*  106/100 dBuVrms  */
    TDA18275_AGC1_Top_108_102_dBuVrms = 7		/*  108/102 dBuVrms */
} TDA18275_AGC1_Top_t, *pTDA18275_AGC1_Top_t;

/* TDA18275 Register AGC1_byte_1 0x0D */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_1;
/* LNA_HiZ bit(s): enables / disables the LNA_Hiz control */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_1__LNA_HiZ;
/* AGC1_Top_Strategy bit(s): selects AGC1 TOP strategy algorithm (function of AGC1 gain) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_1__AGC1_Top_Strategy;
/* AGC1_Top bit(s): selects  AGC1 TOP Down / TOP Up (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_1__AGC1_Top;


typedef enum _TDA18275_AGC2_Gain_Control_Speed_Item_t {
    TDA18275_AGC2_Gain_Control_Speed_1_step_each_VSYNC_rising_edge_ms = 0,		/*  1 step each VSYNC rising edge ms  */
    TDA18275_AGC2_Gain_Control_Speed_0d512_ms = 1,		/*  0.512 ms  */
    TDA18275_AGC2_Gain_Control_Speed_8d192_ms = 2,		/*  8.192 ms  */
    TDA18275_AGC2_Gain_Control_Speed_32d768_ms = 3		/*  32.768 ms */
} TDA18275_AGC2_Gain_Control_Speed_t, *pTDA18275_AGC2_Gain_Control_Speed_t;

/* TDA18275 Register AGC1_byte_2 0x0E */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_2;
/* AGC1_cc_Freeze_Enable bit(s): AGC1 Freeze algorithm selection */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_2__AGC1_cc_Freeze_Enable;
/* AGC1_cc_Wide_Enable bit(s): AGC1 Wide algorithm selection */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_2__AGC1_cc_Wide_Enable;
/* AGC2_Gain_Control_Speed bit(s): selects Up transition step duration when AGC2 underload is detected (ms)  */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_2__AGC2_Gain_Control_Speed;


typedef enum _TDA18275_AGC1_Do_step_Item_t {
    TDA18275_AGC1_Do_step_1d024_ms = 0,		/*  1.024 ms  */
    TDA18275_AGC1_Do_step_0d512_ms = 1,		/*  0.512 ms  */
    TDA18275_AGC1_Do_step_0d256_ms = 2,		/*  0.256 ms  */
    TDA18275_AGC1_Do_step_0d128_ms = 3		/*  0.128 ms */
} TDA18275_AGC1_Do_step_t, *pTDA18275_AGC1_Do_step_t;

typedef enum _TDA18275_AGC1_Gain_Item_t {
    TDA18275_AGC1_Gain_n5_dB = 0,		/*  -5 dB  */
    TDA18275_AGC1_Gain_n2_dB = 1,		/*  -2 dB  */
    TDA18275_AGC1_Gain_1_dB = 2,		/*  1 dB  */
    TDA18275_AGC1_Gain_4_dB = 3,		/*  4 dB  */
    TDA18275_AGC1_Gain_7_dB = 4,		/*  7 dB  */
    TDA18275_AGC1_Gain_10_dB = 5,		/*  10 dB  */
    TDA18275_AGC1_Gain_13_dB = 6,		/*  13 dB  */
    TDA18275_AGC1_Gain_16_dB = 7,		/*  16 dB  */
    TDA18275_AGC1_Gain_19_dB = 8,		/*  19 dB  */
    TDA18275_AGC1_Gain_22_dB = 9,		/*  22 dB  */
    TDA18275_AGC1_Gain_25_dB = 10,		/*  25 dB  */
    TDA18275_AGC1_Gain_28_dB = 11		/*  28 dB */
} TDA18275_AGC1_Gain_t, *pTDA18275_AGC1_Gain_t;

/* TDA18275 Register AGC1_byte_3 0x0F */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_3;
/* AGC1_Do_step bit(s): selects AGC1 down time constant (ms) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_3__AGC1_Do_step;
/* Force_AGC1_gain bit(s): enables / disables the manual control on AGC1 control loop */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_3__Force_AGC1_gain;
/* AGC1_Gain bit(s): selects AGC1 gain value if Force_AGC1_gain = 1 (manual .forced. mode) (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_byte_3__AGC1_Gain;


typedef enum _TDA18275_AGC2_Top_Strategy_Item_t {
    TDA18275_AGC2_Top_Strategy_No_dynamic_TOP_change = 0,		/*  No dynamic TOP change   */
    TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_4dB_10dB = 1,		/*  -1dB /-6dB TOP Do for LNA gain &gt; 4dB/10dB   */
    TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_7dB_13dB = 2,		/*  -1dB /-6dB TOP Do for LNA gain &gt; 7dB/13dB   */
    TDA18275_AGC2_Top_Strategy_n1dB_n6dB_TOP_Do_for_LNA_gain_sup_10dB_16dB = 3,		/*  -1dB /-6dB TOP Do for LNA gain &gt; 10dB/16dB   */
    TDA18275_AGC2_Top_Strategy_n4_dB_TOP_Do_for_LNA_gain_sup_13_dB = 4,		/*  -4 dB TOP Do for LNA gain &gt; 13 dB   */
    TDA18275_AGC2_Top_Strategy_n5_dB_TOP_Do_for_LNA_gain_sup_13_dB = 5,		/*  -5 dB TOP Do for LNA gain &gt; 13 dB   */
    TDA18275_AGC2_Top_Strategy_n1dB_n7dB_TOP_Do_for_LNA_gain_sup_7dB_13dB = 6,		/*  -1dB /-7dB TOP Do for LNA gain &gt; 7dB/13dB   */
    TDA18275_AGC2_Top_Strategy_n2dB_n8dB_TOP_Do_for_LNA_gain_sup_7dB_13dB = 7		/*  -2dB /-8dB TOP Do for LNA gain &gt; 7dB/13dB  */
} TDA18275_AGC2_Top_Strategy_t, *pTDA18275_AGC2_Top_Strategy_t;

typedef enum _TDA18275_AGC2_TOP_Item_t {
    TDA18275_AGC2_TOP_93_92d5_88d5_dBuVrms = 0,		/*  93/92.5/88.5 dBuVrms  */
    TDA18275_AGC2_TOP_95_94d5_90d5_dBuVrms = 1,		/*  95/94.5/90.5 dBuVrms  */
    TDA18275_AGC2_TOP_97_96d5_92d5_dBuVrms = 2,		/*  97/96.5/92.5 dBuVrms  */
    TDA18275_AGC2_TOP_99_98d5_94d5_dBuVrms = 3,		/*  99/98.5/94.5 dBuVrms  */
    TDA18275_AGC2_TOP_101_100d5_96d5_dBuVrms = 4,		/*  101/100.5/96.5 dBuVrms  */
    TDA18275_AGC2_TOP_103_102d5_98d5_dBuVrms = 5,		/*  103/102.5/98.5 dBuVrms  */
    TDA18275_AGC2_TOP_104_103d5_99d5_dBuVrms = 6,		/*  104/103.5/99.5 dBuVrms  */
    TDA18275_AGC2_TOP_105_104d5_100d5_dBuVrms = 7,		/*  105/104.5/100.5 dBuVrms  */
    TDA18275_AGC2_TOP_106_105d5_101d5_dBuVrms = 8,		/*  106/105.5/101.5 dBuVrms  */
    TDA18275_AGC2_TOP_107_106d5_102d5_dBuVrms = 9,		/*  107/106.5/102.5 dBuVrms  */
    TDA18275_AGC2_TOP_108_107d5_103d5_dBuVrms = 10,		/*  108/107.5/103.5 dBuVrms  */
    TDA18275_AGC2_TOP_109_108d5_104d5_dBuVrms = 11,		/*  109/108.5/104.5 dBuVrms  */
    TDA18275_AGC2_TOP_110_109d5_105d5_dBuVrms = 12,		/*  110/109.5/105.5 dBuVrms  */
    TDA18275_AGC2_TOP_111_110d5_106d5_dBuVrms = 13,		/*  111/110.5/106.5 dBuVrms  */
    TDA18275_AGC2_TOP_112_111d5_107d5_dBuVrms = 14,		/*  112/111.5/107.5 dBuVrms  */
    TDA18275_AGC2_TOP_113_112d5_108d5_dBuVrms = 15,		/*  113/112.5/108.5 dBuVrms  */
    TDA18275_AGC2_TOP_114_113d5_109d5_dBuVrms = 16,		/*  114/113.5/109.5 dBuVrms  */
    TDA18275_AGC2_TOP_115_114d5_110d5_dBuVrms = 17,		/*  115/114.5/110.5 dBuVrms  */
    TDA18275_AGC2_TOP_116_115d5_111d5_dBuVrms = 18,		/*  116/115.5/111.5 dBuVrms  */
    TDA18275_AGC2_TOP_117_116d5_112d5_dBuVrms = 19,		/*  117/116.5/112.5 dBuVrms  */
    TDA18275_AGC2_TOP_118_117d5_113d5_dBuVrms = 20,		/*  118/117.5/113.5 dBuVrms  */
    TDA18275_AGC2_TOP_119_118d5_114d5_dBuVrms = 21		/*  119/118.5/114.5 dBuVrms */
} TDA18275_AGC2_TOP_t, *pTDA18275_AGC2_TOP_t;

/* TDA18275 Register AGC2_byte_1 0x10 */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_byte_1;
/* AGC2_Top_Strategy bit(s): selects AGC2 TOP strategy algorithm (function of AGC1 gain) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_byte_1__AGC2_Top_Strategy;
/* AGC2_TOP bit(s): selects AGC2 TOP Down / TOP Up / TOP Underload (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_byte_1__AGC2_TOP;


/* TDA18275 Register AGC2_byte_2 0x11 */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_byte_2;
/* AGC2_Gain bit(s): selects AGC2 gain value if Force_AGC2_gain = 1 (manual .forced. mode) (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_byte_2__AGC2_Gain;


typedef enum _TDA18275_AGC2_Do_step_Item_t {
    TDA18275_AGC2_Do_step_1d024_ms = 0,		/*  1.024 ms  */
    TDA18275_AGC2_Do_step_0d512_ms = 1,		/*  0.512 ms  */
    TDA18275_AGC2_Do_step_0d256_ms = 2,		/*  0.256 ms  */
    TDA18275_AGC2_Do_step_0d128_ms = 3		/*  0.128 ms */
} TDA18275_AGC2_Do_step_t, *pTDA18275_AGC2_Do_step_t;

/* TDA18275 Register RF_byte 0x12 */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_byte;
/* PLD_CC_Enable bit(s): Power Level detector configuration */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_byte__PLD_CC_Enable;
/* AGCs_loop_off bit(s): enables / disables all AGC detector clocks */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_byte__AGCs_loop_off;
/* AGC2_Do_step bit(s): selects AGC2 down time constant (ms) */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_byte__AGC2_Do_step;
/* Force_AGC2_gain bit(s): enables / disables the manual control on AGC2 control loop */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_byte__Force_AGC2_gain;


typedef enum _TDA18275_AGCK_Mode_Item_t {
    TDA18275_AGCK_Mode_1_step_each_VSYNC_rising_edge_ms = 0,		/*  1 step each VSYNC rising edge ms  */
    TDA18275_AGCK_Mode_0d512_ms = 1,		/*  0.512 ms  */
    TDA18275_AGCK_Mode_8d192_ms = 2,		/*  8.192 ms  */
    TDA18275_AGCK_Mode_32d768_ms = 3		/*  32.768 ms */
} TDA18275_AGCK_Mode_t, *pTDA18275_AGCK_Mode_t;

/* TDA18275 Register AGCK_byte_1 0x13 */
extern const TDA18275_BitField_t gTDA18275_Reg_AGCK_byte_1;
/* AGC2_Gain_Control_En bit(s): enables / disables AGC2 underload mechanism */
extern const TDA18275_BitField_t gTDA18275_Reg_AGCK_byte_1__AGC2_Gain_Control_En;
/* AGCK_Mode bit(s): selects AGCK clock  (ms) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGCK_byte_1__AGCK_Mode;


typedef enum _TDA18275_AGC4_TOP_Item_t {
    TDA18275_AGC4_TOP_105_100_dBuVrms = 0,		/*  105/100 dBuVrms  */
    TDA18275_AGC4_TOP_107_102_dBuVrms = 1,		/*  107/102 dBuVrms  */
    TDA18275_AGC4_TOP_110_105_dBuVrms = 2,		/*  110/105 dBuVrms  */
    TDA18275_AGC4_TOP_112_107_dBuVrms = 3		/*  112/107 dBuVrms */
} TDA18275_AGC4_TOP_t, *pTDA18275_AGC4_TOP_t;

/* TDA18275 Register IR_Mixer_byte_1 0x14 */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Mixer_byte_1;
/* AGC4_TOP bit(s): selects  AGC4 TOP Down / TOP Up (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Mixer_byte_1__AGC4_TOP;


typedef enum _TDA18275_AGC4_Do_step_Item_t {
    TDA18275_AGC4_Do_step_1d024_ms = 0,		/*  1.024 ms  */
    TDA18275_AGC4_Do_step_0d512_ms = 1,		/*  0.512 ms  */
    TDA18275_AGC4_Do_step_0d256_ms = 2,		/*  0.256 ms  */
    TDA18275_AGC4_Do_step_0d128_ms = 3		/*  0.128 ms */
} TDA18275_AGC4_Do_step_t, *pTDA18275_AGC4_Do_step_t;

typedef enum _TDA18275_AGC4_Gain_Item_t {
    TDA18275_AGC4_Gain_2_dB = 0,		/*  2 dB  */
    TDA18275_AGC4_Gain_5_dB = 1,		/*  5 dB  */
    TDA18275_AGC4_Gain_8_dB = 2,		/*  8 dB  */
    TDA18275_AGC4_Gain_11_dB = 3,		/*  11 dB  */
    TDA18275_AGC4_Gain_14_dB = 4,		/*  14 dB  */
    TDA18275_AGC4_Gain_val_5_Forbidden_dB = 5,		/*  val 5 Forbidden dB  */
    TDA18275_AGC4_Gain_val_6_Forbidden_dB = 6,		/*  val 6 Forbidden dB  */
    TDA18275_AGC4_Gain_val_7_Forbidden_dB = 7		/*  val 7 Forbidden dB */
} TDA18275_AGC4_Gain_t, *pTDA18275_AGC4_Gain_t;

/* TDA18275 Register IR_Mixer_byte_2 0x15 */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Mixer_byte_2;
/* AGC4_Do_step bit(s): selects AGC4 down time constant (ms) */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Mixer_byte_2__AGC4_Do_step;
/* Force_AGC4_gain bit(s): enables / disables the manual control on AGC4 control loop */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Mixer_byte_2__Force_AGC4_gain;
/* AGC4_Gain bit(s): selects AGC4 gain value if Force_AGC4_gain = 1 (manual .forced. mode) (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Mixer_byte_2__AGC4_Gain;


typedef enum _TDA18275_RSSI_HP_Fc_Item_t {
    TDA18275_RSSI_HP_Fc_0d3_MHz = 0,		/*  0.3 MHz  */
    TDA18275_RSSI_HP_Fc_2d25_MHz = 1		/*  2.25 MHz */
} TDA18275_RSSI_HP_Fc_t, *pTDA18275_RSSI_HP_Fc_t;

typedef enum _TDA18275_AGC5_HP_Fc_Item_t {
    TDA18275_AGC5_HP_Fc_0d3_MHz = 0,		/*  0.3 MHz  */
    TDA18275_AGC5_HP_Fc_2d25_MHz = 1		/*  2.25 MHz */
} TDA18275_AGC5_HP_Fc_t, *pTDA18275_AGC5_HP_Fc_t;

typedef enum _TDA18275_AGC5_TOP_Item_t {
    TDA18275_AGC5_TOP_105_100_dBuVrms = 0,		/*  105/100 dBuVrms  */
    TDA18275_AGC5_TOP_107_102_dBuVrms = 1,		/*  107/102 dBuVrms  */
    TDA18275_AGC5_TOP_110_105_dBuVrms = 2,		/*  110/105 dBuVrms  */
    TDA18275_AGC5_TOP_112_107_dBuVrms = 3		/*  112/107 dBuVrms */
} TDA18275_AGC5_TOP_t, *pTDA18275_AGC5_TOP_t;

/* TDA18275 Register AGC5_byte_1 0x16 */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_1;
/* RSSI_HP_Fc bit(s): selects RSSI HPF cut off frequency (MHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_1__RSSI_HP_Fc;
/* AGC5_HP_Fc bit(s): selects AGC5 highpass filter cut off frequency (MHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_1__AGC5_HP_Fc;
/* AGC5_TOP bit(s): selects  AGC5 TOP Down / TOP Up (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_1__AGC5_TOP;


typedef enum _TDA18275_AGC5_Do_step_Item_t {
    TDA18275_AGC5_Do_step_1d024_ms = 0,		/*  1.024 ms  */
    TDA18275_AGC5_Do_step_0d512_ms = 1,		/*  0.512 ms  */
    TDA18275_AGC5_Do_step_0d256_ms = 2,		/*  0.256 ms  */
    TDA18275_AGC5_Do_step_0d128_ms = 3		/*  0.128 ms */
} TDA18275_AGC5_Do_step_t, *pTDA18275_AGC5_Do_step_t;

typedef enum _TDA18275_AGC5_Gain_Item_t {
    TDA18275_AGC5_Gain_n6_or_6d4_dB = 0,		/*  -6  or 6.4  dB  */
    TDA18275_AGC5_Gain_n3_or_9d4_dB = 1,		/*  -3 or 9.4  dB  */
    TDA18275_AGC5_Gain_0_or_12d4_dB = 2,		/*  0  or 12.4  dB  */
    TDA18275_AGC5_Gain_3_or_15d4_dB = 3,		/*  3  or 15.4  dB  */
    TDA18275_AGC5_Gain_6_or_18d4_dB = 4,		/*  6  or 18.4  dB  */
    TDA18275_AGC5_Gain_9_or_21d4_dB = 5,		/*  9  or 21.4  dB  */
    TDA18275_AGC5_Gain_12_or_24d4_dB = 6,		/*  12  or 24.4  dB  */
    TDA18275_AGC5_Gain_15_or_27d4_dB = 7		/*  15  or 27.4  dB */
} TDA18275_AGC5_Gain_t, *pTDA18275_AGC5_Gain_t;

/* TDA18275 Register AGC5_byte_2 0x17 */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_2;
/* AGC5_Do_step bit(s): selects AGC5 down time constant (ms) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_2__AGC5_Do_step;
/* Force_AGC5_gain bit(s): enables / disables the manual control on AGC5 control loop */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_2__Force_AGC5_gain;
/* AGC5_Gain bit(s): selects AGC5 gain value if Force_AGC5_gain = 1 (manual .forced. mode) (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC5_byte_2__AGC5_Gain;


typedef enum _TDA18275_Top_adapt_AGC2_Item_t {
    TDA18275_Top_adapt_AGC2_No_dynamic_TOP_change = 0,		/*  No dynamic TOP change   */
    TDA18275_Top_adapt_AGC2_n3_dB_TOP_for_IFLPF_gain_inf_9dB_12dB = 1,		/*  -3 dB TOP for IFLPF gain &lt; 9dB / 12dB   */
    TDA18275_Top_adapt_AGC2_n5_dB_TOP_for_IFLPF_gain_inf_9dB_12dB = 2,		/*  -5 dB TOP for IFLPF gain &lt; 9dB / 12dB   */
    TDA18275_Top_adapt_AGC2_n7_dB_TOP_for_IFLPF_gain_inf_9dB_12dB = 3		/*  -7 dB TOP for IFLPF gain &lt; 9dB / 12dB  */
} TDA18275_Top_adapt_AGC2_t, *pTDA18275_Top_adapt_AGC2_t;

typedef enum _TDA18275_Top_adapt_AGC1_Item_t {
    TDA18275_Top_adapt_AGC1_No_dynamic_TOP_change = 0,		/*  No dynamic TOP change   */
    TDA18275_Top_adapt_AGC1_n4_dB_TOP_for_IFLPF_gain_inf_9dB_12dB = 1,		/*  -4 dB TOP for IFLPF gain &lt; 9dB / 12dB   */
    TDA18275_Top_adapt_AGC1_n6_dB_TOP_for_IFLPF_gain_inf_9dB_12dB = 2,		/*  -6 dB TOP for IFLPF gain &lt; 9dB / 12dB   */
    TDA18275_Top_adapt_AGC1_n8_dB_TOP_for_IFLPF_gain_inf_9dB_12dB = 3		/*  -8 dB TOP for IFLPF gain &lt; 9dB / 12dB  */
} TDA18275_Top_adapt_AGC1_t, *pTDA18275_Top_adapt_AGC1_t;

/* TDA18275 Register Adapt_Top_byte 0x18 */
extern const TDA18275_BitField_t gTDA18275_Reg_Adapt_Top_byte;
/* Top_adapt_AGC2 bit(s): selects AGC2 TOP adapt algorithm (function of AGC5 gain) */
extern const TDA18275_BitField_t gTDA18275_Reg_Adapt_Top_byte__Top_adapt_AGC2;
/* Top_adapt_AGC1 bit(s): selects AGC1 TOP adapt algorithm (function of AGC5 gain) */
extern const TDA18275_BitField_t gTDA18275_Reg_Adapt_Top_byte__Top_adapt_AGC1;


typedef enum _TDA18275_PD_Vsync_Mgt_Item_t {
    TDA18275_PD_Vsync_Mgt_Vsync_Management_enabled = 0,		/*  Vsync Management enabled   */
    TDA18275_PD_Vsync_Mgt_Vsync_Management_disabled = 1		/*  Vsync Management disabled  */
} TDA18275_PD_Vsync_Mgt_t, *pTDA18275_PD_Vsync_Mgt_t;

typedef enum _TDA18275_Neg_Modulation_Item_t {
    TDA18275_Neg_Modulation_Disabled = 0,		/*  Disabled   */
    TDA18275_Neg_Modulation_Enabled = 1		/*  Enabled  */
} TDA18275_Neg_Modulation_t, *pTDA18275_Neg_Modulation_t;

/* TDA18275 Register Vsync_byte 0x19 */
extern const TDA18275_BitField_t gTDA18275_Reg_Vsync_byte;
/* PD_Vsync_Mgt bit(s): enables / disables the automatic management of AGC clocking in ATV reception mode */
extern const TDA18275_BitField_t gTDA18275_Reg_Vsync_byte__PD_Vsync_Mgt;
/* Neg_Modulation bit(s): selects whether the received analog TV channel uses negative or positive modulation */
extern const TDA18275_BitField_t gTDA18275_Reg_Vsync_byte__Neg_Modulation;


typedef enum _TDA18275_AGC_Ovld_TOP_Item_t {
    TDA18275_AGC_Ovld_TOP_p9_p3d5_n3d5 = 0,		/*  +9/+3.5/-3.5   */
    TDA18275_AGC_Ovld_TOP_p9_p4d5_n4d5 = 1,		/*  +9/+4.5/-4.5   */
    TDA18275_AGC_Ovld_TOP_p9_p4d5_n3d5 = 2,		/*  +9/+4.5/-3.5   */
    TDA18275_AGC_Ovld_TOP_p9_p6_n4d5 = 3,		/*  +9/+6/-4.5   */
    TDA18275_AGC_Ovld_TOP_p9_p6_n6 = 4,		/*  +9/+6/-6   */
    TDA18275_AGC_Ovld_TOP_p9_p6_n9 = 5,		/*  +9/+6/-9   */
    TDA18275_AGC_Ovld_TOP_p9_p7d5_n9 = 6,		/*  +9/+7.5/-9   */
    TDA18275_AGC_Ovld_TOP_p12_p7d5_n9 = 7		/*  +12/+7.5/-9  */
} TDA18275_AGC_Ovld_TOP_t, *pTDA18275_AGC_Ovld_TOP_t;

/* TDA18275 Register Ovld_Udld_byte 0x1A */
extern const TDA18275_BitField_t gTDA18275_Reg_Ovld_Udld_byte;
/* Ovld_Disable bit(s): enables / disables the IF overload detection */
extern const TDA18275_BitField_t gTDA18275_Reg_Ovld_Udld_byte__Ovld_Disable;
/* Ovld_RF_Disable bit(s): enables / disables the RF overload detection */
extern const TDA18275_BitField_t gTDA18275_Reg_Ovld_Udld_byte__Ovld_RF_Disable;
/* Udld_Disable bit(s): enables/ disabled the IF underload mechanism */
extern const TDA18275_BitField_t gTDA18275_Reg_Ovld_Udld_byte__Udld_Disable;
/* AGC_Ovld_TOP bit(s): selects RF overload / IF overload / IF underload ranges (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_Ovld_Udld_byte__AGC_Ovld_TOP;


typedef enum _TDA18275_IF_LPF_Offset_Item_t {
    TDA18275_IF_LPF_Offset_0 = 0,		/*  0   */
    TDA18275_IF_LPF_Offset_4 = 1,		/*  4   */
    TDA18275_IF_LPF_Offset_8 = 2,		/*  8   */
    TDA18275_IF_LPF_Offset_12 = 3		/*  12  */
} TDA18275_IF_LPF_Offset_t, *pTDA18275_IF_LPF_Offset_t;

typedef enum _TDA18275_IF_LPF_sign_Item_t {
    TDA18275_IF_LPF_sign_Positive = 0,		/*  Positive   */
    TDA18275_IF_LPF_sign_Negative = 1		/*  Negative  */
} TDA18275_IF_LPF_sign_t, *pTDA18275_IF_LPF_sign_t;

typedef enum _TDA18275_DC_Notch_Item_t {
    TDA18275_DC_Notch_Disabled = 0,		/*  Disabled   */
    TDA18275_DC_Notch_Enabled = 1		/*  Enabled  */
} TDA18275_DC_Notch_t, *pTDA18275_DC_Notch_t;

typedef enum _TDA18275_LP_Fc_Item_t {
    TDA18275_LP_Fc_6_MHz = 0,		/*  6 MHz  */
    TDA18275_LP_Fc_7_MHz = 1,		/*  7 MHz  */
    TDA18275_LP_Fc_8_MHz = 2,		/*  8 MHz  */
    TDA18275_LP_Fc_9_MHz = 3,		/*  9 MHz  */
    TDA18275_LP_Fc_10_MHz = 4,		/*  10 MHz  */
    TDA18275_LP_Fc_11d25_MHz = 5,		/*  11.25 MHz  */
    TDA18275_LP_Fc_1d5_MHz = 6		/*  1.5 MHz */
} TDA18275_LP_Fc_t, *pTDA18275_LP_Fc_t;

/* TDA18275 Register IF_Byte_1 0x1B */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_1;
/* IF_LPF_Offset bit(s): selects the IF LPF cut-off frequency correction factor (%) */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_1__IF_LPF_Offset;
/* IF_LPF_sign bit(s): selects the IF LPF cut-off frequency correction sign */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_1__IF_LPF_sign;
/* DC_Notch bit(s): enables / disables the DC Notch in the IF polyphase filter */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_1__DC_Notch;
/* LP_Fc bit(s): selects the IF LPF cut-off frequency (MHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_1__LP_Fc;


typedef enum _TDA18275_IF_HPF_Offset_Item_t {
    TDA18275_IF_HPF_Offset_0 = 0,		/*  0   */
    TDA18275_IF_HPF_Offset_4 = 1,		/*  4   */
    TDA18275_IF_HPF_Offset_8 = 2,		/*  8   */
    TDA18275_IF_HPF_Offset_12 = 3		/*  12  */
} TDA18275_IF_HPF_Offset_t, *pTDA18275_IF_HPF_Offset_t;

typedef enum _TDA18275_IF_HPF_sign_Item_t {
    TDA18275_IF_HPF_sign_Positive = 0,		/*  Positive   */
    TDA18275_IF_HPF_sign_Negative = 1		/*  Negative  */
} TDA18275_IF_HPF_sign_t, *pTDA18275_IF_HPF_sign_t;

typedef enum _TDA18275_IF_HP_Fc_Item_t {
    TDA18275_IF_HP_Fc_0d5_MHz = 0,		/*  0.5 MHz  */
    TDA18275_IF_HP_Fc_1_MHz = 1,		/*  1 MHz  */
    TDA18275_IF_HP_Fc_1d6_MHz = 2,		/*  1.6 MHz  */
    TDA18275_IF_HP_Fc_2d3_MHz = 3,		/*  2.3 MHz  */
    TDA18275_IF_HP_Fc_3d5_MHz = 4		/*  3.5 MHz */
} TDA18275_IF_HP_Fc_t, *pTDA18275_IF_HP_Fc_t;

typedef enum _TDA18275_IF_HP_Enable_Item_t {
    TDA18275_IF_HP_Enable_Disabled = 0,		/*  Disabled   */
    TDA18275_IF_HP_Enable_Enabled = 1		/*  Enabled  */
} TDA18275_IF_HP_Enable_t, *pTDA18275_IF_HP_Enable_t;

/* TDA18275 Register IF_Byte_2 0x1C */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_2;
/* IF_HPF_Offset bit(s): selects the IF HPF cut-off frequency correction factor (%) */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_2__IF_HPF_Offset;
/* IF_HPF_sign bit(s): selects the IF HPF cut-off frequency correction sign */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_2__IF_HPF_sign;
/* IF_HP_Fc bit(s): selects the IF HPF cut-off frequency (MHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_2__IF_HP_Fc;
/* IF_HP_Enable bit(s): enables / disables the IF highpass filter */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_2__IF_HP_Enable;


typedef enum _TDA18275_IF_Notch_Offset_Item_t {
    TDA18275_IF_Notch_Offset_0 = 0,		/*  0   */
    TDA18275_IF_Notch_Offset_4 = 1,		/*  4   */
    TDA18275_IF_Notch_Offset_8 = 2,		/*  8   */
    TDA18275_IF_Notch_Offset_12 = 3		/*  12  */
} TDA18275_IF_Notch_Offset_t, *pTDA18275_IF_Notch_Offset_t;

typedef enum _TDA18275_IF_Notch_sign_Item_t {
    TDA18275_IF_Notch_sign_Positive = 0,		/*  Positive   */
    TDA18275_IF_Notch_sign_Negative = 1		/*  Negative  */
} TDA18275_IF_Notch_sign_t, *pTDA18275_IF_Notch_sign_t;

typedef enum _TDA18275_IF_Notch_Freq_Item_t {
    TDA18275_IF_Notch_Freq_6d25_MHz = 0,		/*  6.25 MHz  */
    TDA18275_IF_Notch_Freq_7d25_MHz = 1,		/*  7.25 MHz  */
    TDA18275_IF_Notch_Freq_8d25_MHz = 2,		/*  8.25 MHz  */
    TDA18275_IF_Notch_Freq_9d25_MHz = 3,		/*  9.25 MHz  */
    TDA18275_IF_Notch_Freq_10d25_MHz = 4,		/*  10.25 MHz  */
    TDA18275_IF_Notch_Freq_11d45_MHz = 5		/*  11.45 MHz */
} TDA18275_IF_Notch_Freq_t, *pTDA18275_IF_Notch_Freq_t;

typedef enum _TDA18275_IF_Notch_Enable_Item_t {
    TDA18275_IF_Notch_Enable_Disabled = 0,		/*  Disabled   */
    TDA18275_IF_Notch_Enable_Enabled = 1		/*  Enabled  */
} TDA18275_IF_Notch_Enable_t, *pTDA18275_IF_Notch_Enable_t;

/* TDA18275 Register IF_Byte_3 0x1D */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_3;
/* IF_Notch_Offset bit(s): selects the IF notch center frequency correction factor (%) */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_3__IF_Notch_Offset;
/* IF_Notch_sign bit(s): selects the IF notch center frequency correction sign */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_3__IF_Notch_sign;
/* IF_Notch_Freq bit(s): selects the IF notch center frequency (MHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_3__IF_Notch_Freq;
/* IF_Notch_Enable bit(s): enables / disables the IF notch filter */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_Byte_3__IF_Notch_Enable;


typedef enum _TDA18275_Dig_Clock_Item_t {
    TDA18275_Dig_Clock_16MHz = 0,		/*  16MHz   */
    TDA18275_Dig_Clock_SubLO = 1		/*  SubLO  */
} TDA18275_Dig_Clock_t, *pTDA18275_Dig_Clock_t;

typedef enum _TDA18275_Xtout_Amp_Item_t {
    TDA18275_Xtout_Amp_200_mVpp_diff = 0,		/*  200 mVpp diff  */
    TDA18275_Xtout_Amp_400_mVpp_diff = 1		/*  400 mVpp diff */
} TDA18275_Xtout_Amp_t, *pTDA18275_Xtout_Amp_t;

typedef enum _TDA18275_XTout_Item_t {
    TDA18275_XTout_No_signal = 0,		/*  No signal   */
    TDA18275_XTout_Fdiv_PLL_2 = 1,		/*  Fdiv PLL /2   */
    TDA18275_XTout_DigClock = 2,		/*  DigClock   */
    TDA18275_XTout_16Mhz = 3		/*  16Mhz  */
} TDA18275_XTout_t, *pTDA18275_XTout_t;

/* TDA18275 Register Reference_Byte 0x1E */
extern const TDA18275_BitField_t gTDA18275_Reg_Reference_Byte;
/* Dig_Clock bit(s): selects the clock of the digital core */
extern const TDA18275_BitField_t gTDA18275_Reg_Reference_Byte__Dig_Clock;
/* Xtout_Amp bit(s): selects XTOUT amplitude (mVpp) */
extern const TDA18275_BitField_t gTDA18275_Reg_Reference_Byte__Xtout_Amp;
/* XTout bit(s): enables / disables the reference clock output XTOUT  */
extern const TDA18275_BitField_t gTDA18275_Reg_Reference_Byte__XTout;


typedef enum _TDA18275_IFnotchToRSSI_Item_t {
    TDA18275_IFnotchToRSSI_Disabled = 0,		/*  Disabled   */
    TDA18275_IFnotchToRSSI_Enabled = 1		/*  Enabled  */
} TDA18275_IFnotchToRSSI_t, *pTDA18275_IFnotchToRSSI_t;

typedef enum _TDA18275_DIFOUT_En_Item_t {
    TDA18275_DIFOUT_En_Digital_IF_OUT_Disabled = 0,		/*  Digital IF OUT Disabled   */
    TDA18275_DIFOUT_En_Digital_IF_OUT_Enabled = 1		/*  Digital IF OUT Enabled  */
} TDA18275_DIFOUT_En_t, *pTDA18275_DIFOUT_En_t;

typedef enum _TDA18275_DVIFAGC_En_Item_t {
    TDA18275_DVIFAGC_En_Analog_VIF_AGC = 0,		/*  Analog VIF AGC   */
    TDA18275_DVIFAGC_En_Digital_VIF_AGC = 1		/*  Digital VIF AGC  */
} TDA18275_DVIFAGC_En_t, *pTDA18275_DVIFAGC_En_t;

typedef enum _TDA18275_IF_level_Item_t {
    TDA18275_IF_level_0_to_30_dB_2_Vpp = 0,		/*  0 to 30 dB (2 Vpp)   */
    TDA18275_IF_level_n4_to_26_dB_1d25_Vpp = 1,		/*  -4 to 26 dB (1.25 Vpp)   */
    TDA18275_IF_level_n6_to_24_dB_1_Vpp = 2,		/*  -6 to 24 dB (1 Vpp)   */
    TDA18275_IF_level_n8_to_22_dB_0d8_Vpp = 3,		/*  -8 to 22 dB (0.8 Vpp)   */
    TDA18275_IF_level_n7d5_to_22d5_dB_0d85_Vpp = 4,		/*  -7.5 to 22.5 dB (0.85 Vpp)   */
    TDA18275_IF_level_n9_to_21_dB_0d7_Vpp = 5,		/*  -9 to 21 dB (0.7 Vpp)   */
    TDA18275_IF_level_n10d3_to_19d7_dB_0d6_Vpp = 6,		/*  -10.3 to 19.7 dB (0.6 Vpp)   */
    TDA18275_IF_level_n12_to_18_dB_0d5_Vpp = 7		/*  -12 to 18 dB (0.5 Vpp)  */
} TDA18275_IF_level_t, *pTDA18275_IF_level_t;

/* TDA18275 Register IF_AGC_byte 0x1F */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_AGC_byte;
/* IFnotchToRSSI bit(s): enables / disables the IF notch to RSSI control */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_AGC_byte__IFnotchToRSSI;
/* DIFOUT_En bit(s): enables / disables the IFOUT_D outputs */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_AGC_byte__DIFOUT_En;
/* DVIFAGC_En bit(s): selects IFAGC control path */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_AGC_byte__DVIFAGC_En;
/* IF_level bit(s): selects the IF amplifier gain range */
extern const TDA18275_BitField_t gTDA18275_Reg_IF_AGC_byte__IF_level;


/* TDA18275 Register MSM_byte_1 0x20 */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_1;
/* IR_CAL_Loop bit(s): Image rejection calibration selection */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_1__IR_CAL_Loop;
/* IR_Cal_Image bit(s): Image rejection calibration selection */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_1__IR_Cal_Image;
/* RC_Cal bit(s): RC calibration selection */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_1__RC_Cal;
/* VCO_Ampl_Cal bit(s): VCO amplitude calibration selection */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_1__VCO_Ampl_Cal;
/* VCO_Freq_Meas bit(s): VCO frequency calibration selection */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_1__VCO_Freq_Meas;


/* TDA18275 Register MSM_byte_2 0x21 */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_2;
/* AGC_CC_Fast_Launch bit(s): Fast Mode trigger */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_2__AGC_CC_Fast_Launch;
/* MSM_Launch bit(s): Main State Machine execution */
extern const TDA18275_BitField_t gTDA18275_Reg_MSM_byte_2__MSM_Launch;


typedef enum _TDA18275_PSM_LNA_Item_t {
    TDA18275_PSM_LNA_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_LNA_n3d5_mA = 1,		/*  -3.5  mA  */
    TDA18275_PSM_LNA_n7_mA = 2,		/*  -7 mA  */
    TDA18275_PSM_LNA_n10_mA = 3		/*  -10 mA */
} TDA18275_PSM_LNA_t, *pTDA18275_PSM_LNA_t;

typedef enum _TDA18275_PSM_LoMixer_Item_t {
    TDA18275_PSM_LoMixer_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_LoMixer_1_mA = 1,		/*  1 mA  */
    TDA18275_PSM_LoMixer_2_mA = 2,		/*  2 mA  */
    TDA18275_PSM_LoMixer_3_mA = 3		/*  3 mA */
} TDA18275_PSM_LoMixer_t, *pTDA18275_PSM_LoMixer_t;

typedef enum _TDA18275_PSM_AGC2_Item_t {
    TDA18275_PSM_AGC2_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_AGC2_n3d4_mA = 1,		/*  -3.4  mA  */
    TDA18275_PSM_AGC2_n8_mA = 2,		/*  -8  mA  */
    TDA18275_PSM_AGC2_n11_mA = 3		/*  -11  mA */
} TDA18275_PSM_AGC2_t, *pTDA18275_PSM_AGC2_t;

typedef enum _TDA18275_PSM_Det2_Item_t {
    TDA18275_PSM_Det2_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_Det2_n1_mA = 1,		/*  -1  mA  */
    TDA18275_PSM_Det2_n2_mA = 2,		/*  -2  mA  */
    TDA18275_PSM_Det2_n3_mA = 3		/*  -3  mA */
} TDA18275_PSM_Det2_t, *pTDA18275_PSM_Det2_t;

/* TDA18275 Register PowerSavingMode_byte_1 0x22 */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_1;
/* PSM_LNA bit(s): adjusts the current in LNA amplifier (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_1__PSM_LNA;
/* PSM_LoMixer bit(s): adjusts the current in LO/mixer section (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_1__PSM_LoMixer;
/* PSM_AGC2 bit(s): adjusts the current in AGC2 amplifier (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_1__PSM_AGC2;
/* PSM_Det2 bit(s): adjusts the current in AGC2 detector (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_1__PSM_Det2;


typedef enum _TDA18275_Loch_curr_boost_Item_t {
    TDA18275_Loch_curr_boost_0 = 0,		/*  0   */
    TDA18275_Loch_curr_boost_1 = 1,		/*  1   */
    TDA18275_Loch_curr_boost_2 = 2,		/*  2   */
    TDA18275_Loch_curr_boost_3 = 3		/*  3  */
} TDA18275_Loch_curr_boost_t, *pTDA18275_Loch_curr_boost_t;

typedef enum _TDA18275_PSM_IFfilter_Item_t {
    TDA18275_PSM_IFfilter_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_IFfilter_n4d2_mA = 1,		/*  -4.2 mA  */
    TDA18275_PSM_IFfilter_n7_mA = 2,		/*  -7 mA  */
    TDA18275_PSM_IFfilter_n8d9_mA = 3		/*  -8.9  mA */
} TDA18275_PSM_IFfilter_t, *pTDA18275_PSM_IFfilter_t;

typedef enum _TDA18275_PSM_IFLPF_Item_t {
    TDA18275_PSM_IFLPF_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_IFLPF_n2d3_mA = 1,		/*  -2.3 mA  */
    TDA18275_PSM_IFLPF_n3d8_mA = 2,		/*  -3.8 mA  */
    TDA18275_PSM_IFLPF_n4d9_mA = 3		/*  -4.9 mA */
} TDA18275_PSM_IFLPF_t, *pTDA18275_PSM_IFLPF_t;

typedef enum _TDA18275_PSM_RF_LPF_Item_t {
    TDA18275_PSM_RF_LPF_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_RF_LPF_n7_mA = 1,		/*  -7 mA  */
    TDA18275_PSM_RF_LPF_n15_mA = 2,		/*  -15 mA  */
    TDA18275_PSM_RF_LPF_n23_mA = 3		/*  -23 mA */
} TDA18275_PSM_RF_LPF_t, *pTDA18275_PSM_RF_LPF_t;

/* TDA18275 Register PowerSavingMode_byte_2 0x23 */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_2;
/* Loch_curr_boost bit(s): adjusts the current in LO chain (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_2__Loch_curr_boost;
/* PSM_IFfilter bit(s): adjusts the current in IF filter (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_2__PSM_IFfilter;
/* PSM_IFLPF bit(s): adjusts the current in IF LPF (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_2__PSM_IFLPF;
/* PSM_RF_LPF bit(s): adjusts the current in the harmonic filter (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_2__PSM_RF_LPF;


typedef enum _TDA18275_LOdiv4_Boost_Item_t {
    TDA18275_LOdiv4_Boost_0_mA = 0,		/*  0 mA  */
    TDA18275_LOdiv4_Boost_1d8_mA = 1		/*  1.8 mA */
} TDA18275_LOdiv4_Boost_t, *pTDA18275_LOdiv4_Boost_t;

typedef enum _TDA18275_PSM_Mixer_Item_t {
    TDA18275_PSM_Mixer_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_Mixer_n0d65_mA = 1,		/*  -0.65  mA  */
    TDA18275_PSM_Mixer_n1d4_mA = 2,		/*  -1.4  mA  */
    TDA18275_PSM_Mixer_n3_mA = 3		/*  -3  mA */
} TDA18275_PSM_Mixer_t, *pTDA18275_PSM_Mixer_t;

typedef enum _TDA18275_PSM_Ifpoly_Item_t {
    TDA18275_PSM_Ifpoly_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_Ifpoly_n1d8_mA = 1,		/*  -1.8 mA  */
    TDA18275_PSM_Ifpoly_n3d2_mA = 2,		/*  -3.2 mA  */
    TDA18275_PSM_Ifpoly_n4d1_mA = 3		/*  -4.1 mA */
} TDA18275_PSM_Ifpoly_t, *pTDA18275_PSM_Ifpoly_t;

typedef enum _TDA18275_PSM_Lodriver_Item_t {
    TDA18275_PSM_Lodriver_0_mA = 0,		/*  0 mA  */
    TDA18275_PSM_Lodriver_n3_mA = 1,		/*  -3 mA  */
    TDA18275_PSM_Lodriver_n4d5_mA = 2,		/*  -4.5 mA  */
    TDA18275_PSM_Lodriver_n6_mA = 3		/*  -6 mA */
} TDA18275_PSM_Lodriver_t, *pTDA18275_PSM_Lodriver_t;

/* TDA18275 Register PowerSavingMode_byte_3 0x24 */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_3;
/* LOdiv4_Boost bit(s): adjusts the current of the divider by 4 in the LO section */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_3__LOdiv4_Boost;
/* PSM_Mixer bit(s): adjusts the current in the mixer (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_3__PSM_Mixer;
/* PSM_Ifpoly bit(s): adjusts the current in IF polyphase filter (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_3__PSM_Ifpoly;
/* PSM_Lodriver bit(s): adjusts the current in LO driver (mA) */
extern const TDA18275_BitField_t gTDA18275_Reg_PowerSavingMode_byte_3__PSM_Lodriver;


typedef enum _TDA18275_LNA_Highpass_Item_t {
    TDA18275_LNA_Highpass_Disabled = 0,		/*  Disabled   */
    TDA18275_LNA_Highpass_Enabled = 1		/*  Enabled  */
} TDA18275_LNA_Highpass_t, *pTDA18275_LNA_Highpass_t;

typedef enum _TDA18275_AGC2_Highpass_Item_t {
    TDA18275_AGC2_Highpass_766_MHz = 0,		/*  766 MHz  */
    TDA18275_AGC2_Highpass_600_MHz = 1,		/*  600 MHz  */
    TDA18275_AGC2_Highpass_470_MHz = 2,		/*  470 MHz  */
    TDA18275_AGC2_Highpass_180_MHz = 3,		/*  180 MHz  */
    TDA18275_AGC2_Highpass_20_MHz = 4		/*  20 MHz */
} TDA18275_AGC2_Highpass_t, *pTDA18275_AGC2_Highpass_t;

/* TDA18275 Register RF_Filters_byte_1 0x25 */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Filters_byte_1;
/* LNA_Highpass bit(s): enables / disables the LNA highpass filter */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Filters_byte_1__LNA_Highpass;
/* AGC2_Highpass bit(s): selects AGC2 highpass filter cut off frequency (MHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Filters_byte_1__AGC2_Highpass;


/* TDA18275 Register RF_Low_Pass_Filter_byte_1 0x26 */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_1;
/* RF_LPF_1 bit(s): selects harmonic filter RF_LPF coefficients */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_1__RF_LPF_1;


/* TDA18275 Register RF_Low_Pass_Filter_byte_2 0x27 */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_2;
/* RF_LPF_2 bit(s): selects harmonic filter RF_LPF coefficients */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_2__RF_LPF_2;
/* RF_LPF_f_1 bit(s): selects harmonic filter RF_LPF_f coefficients */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_2__RF_LPF_f_1;


/* TDA18275 Register RF_Low_Pass_Filter_byte_3 0x28 */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_3;
/* RF_LPF_f_2 bit(s): selects harmonic filter RF_LPF_f coefficients */
extern const TDA18275_BitField_t gTDA18275_Reg_RF_Low_Pass_Filter_byte_3__RF_LPF_f_2;


typedef enum _TDA18275_AGC1_Top_Do_Read_Item_t {
    TDA18275_AGC1_Top_Do_Read_94_dBuVrms = 0,		/*  94 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_96_dBuVrms = 1,		/*  96 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_98_dBuVrms = 2,		/*  98 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_100_dBuVrms = 3,		/*  100 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_102_dBuVrms = 4,		/*  102 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_104_dBuVrms = 5,		/*  104 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_106_dBuVrms = 6,		/*  106 dBuVrms  */
    TDA18275_AGC1_Top_Do_Read_108_dBuVrms = 7		/*  108 dBuVrms */
} TDA18275_AGC1_Top_Do_Read_t, *pTDA18275_AGC1_Top_Do_Read_t;

typedef enum _TDA18275_AGC1_Top_Up_Read_Item_t {
    TDA18275_AGC1_Top_Up_Read_88_dBuVrms = 0,		/*  88 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_90_dBuVrms = 1,		/*  90 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_92_dBuVrms = 2,		/*  92 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_94_dBuVrms = 3,		/*  94 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_96_dBuVrms = 4,		/*  96 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_98_dBuVrms = 5,		/*  98 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_100_dBuVrms = 6,		/*  100 dBuVrms  */
    TDA18275_AGC1_Top_Up_Read_102_dBuVrms = 7		/*  102 dBuVrms */
} TDA18275_AGC1_Top_Up_Read_t, *pTDA18275_AGC1_Top_Up_Read_t;

/* TDA18275 Register AGC1_Top_byte 0x2A */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_Top_byte;
/* AGC1_Top_Do_Read bit(s): reads current AGC1 TOP Down (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_Top_byte__AGC1_Top_Do_Read;
/* AGC1_Top_Up_Read bit(s): reads current AGC1 TOP Up (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_Top_byte__AGC1_Top_Up_Read;


typedef enum _TDA18275_AGC2_Top_Do_Read_Item_t {
    TDA18275_AGC2_Top_Do_Read_93_dBuVrms = 0,		/*  93 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_95_dBuVrms = 1,		/*  95 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_97_dBuVrms = 2,		/*  97 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_99_dBuVrms = 3,		/*  99 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_101_dBuVrms = 4,		/*  101 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_103_dBuVrms = 5,		/*  103 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_104_dBuVrms = 6,		/*  104 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_105_dBuVrms = 7,		/*  105 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_106_dBuVrms = 8,		/*  106 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_107_dBuVrms = 9,		/*  107 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_108_dBuVrms = 10,		/*  108 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_109_dBuVrms = 11,		/*  109 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_110_dBuVrms = 12,		/*  110 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_111_dBuVrms = 13,		/*  111 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_112_dBuVrms = 14,		/*  112 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_113_dBuVrms = 15,		/*  113 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_114_dBuVrms = 16,		/*  114 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_115_dBuVrms = 17,		/*  115 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_116_dBuVrms = 18,		/*  116 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_117_dBuVrms = 19,		/*  117 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_118_dBuVrms = 20,		/*  118 dBuVrms  */
    TDA18275_AGC2_Top_Do_Read_119_dBuVrms = 21		/*  119 dBuVrms */
} TDA18275_AGC2_Top_Do_Read_t, *pTDA18275_AGC2_Top_Do_Read_t;

/* TDA18275 Register AGC2_Top_byte 0x2B */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_Top_byte;
/* AGC2_Top_Do_Read bit(s): reads current AGC2 TOP Down (dBuV) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_Top_byte__AGC2_Top_Do_Read;


typedef enum _TDA18275_AGC1_Gain_Read_Item_t {
    TDA18275_AGC1_Gain_Read_n5_dB = 0,		/*  -5 dB  */
    TDA18275_AGC1_Gain_Read_n2_dB = 1,		/*  -2 dB  */
    TDA18275_AGC1_Gain_Read_1_dB = 2,		/*  1 dB  */
    TDA18275_AGC1_Gain_Read_4_dB = 3,		/*  4 dB  */
    TDA18275_AGC1_Gain_Read_7_dB = 4,		/*  7 dB  */
    TDA18275_AGC1_Gain_Read_10_dB = 5,		/*  10 dB  */
    TDA18275_AGC1_Gain_Read_13_dB = 6,		/*  13 dB  */
    TDA18275_AGC1_Gain_Read_16_dB = 7,		/*  16 dB  */
    TDA18275_AGC1_Gain_Read_19_dB = 8,		/*  19 dB  */
    TDA18275_AGC1_Gain_Read_22_dB = 9,		/*  22 dB  */
    TDA18275_AGC1_Gain_Read_25_dB = 10,		/*  25 dB  */
    TDA18275_AGC1_Gain_Read_28_dB = 11		/*  28 dB */
} TDA18275_AGC1_Gain_Read_t, *pTDA18275_AGC1_Gain_Read_t;

/* TDA18275 Register AGC1_Gain_byte 0x2C */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_Gain_byte;
/* AGC1_Gain_Read bit(s): reads current AGC1 gain value (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC1_Gain_byte__AGC1_Gain_Read;


/* TDA18275 Register AGC2_Gain_byte 0x2D */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_Gain_byte;
/* AGC2_Gain_Read bit(s): reads current AGC2 gain value (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_AGC2_Gain_byte__AGC2_Gain_Read;


typedef enum _TDA18275_AGC5_Gain_Read_Item_t {
    TDA18275_AGC5_Gain_Read_n6_or_6d4_dB = 0,		/*  -6  or 6.4  dB  */
    TDA18275_AGC5_Gain_Read_n3_or_9d4_dB = 1,		/*  -3 or 9.4  dB  */
    TDA18275_AGC5_Gain_Read_0_or_12d4_dB = 2,		/*  0  or 12.4  dB  */
    TDA18275_AGC5_Gain_Read_3_or_15d4_dB = 3,		/*  3  or 15.4  dB  */
    TDA18275_AGC5_Gain_Read_6_or_18d4_dB = 4,		/*  6  or 18.4  dB  */
    TDA18275_AGC5_Gain_Read_9_or_21d4_dB = 5,		/*  9  or 21.4  dB  */
    TDA18275_AGC5_Gain_Read_12_or_24d4_dB = 6,		/*  12  or 24.4  dB  */
    TDA18275_AGC5_Gain_Read_15_or_27d4_dB = 7		/*  15  or 27.4  dB */
} TDA18275_AGC5_Gain_Read_t, *pTDA18275_AGC5_Gain_Read_t;

typedef enum _TDA18275_AGC4_Gain_Read_Item_t {
    TDA18275_AGC4_Gain_Read_2 = 0,		/*  2   */
    TDA18275_AGC4_Gain_Read_5 = 1,		/*  5   */
    TDA18275_AGC4_Gain_Read_8 = 2,		/*  8   */
    TDA18275_AGC4_Gain_Read_11 = 3,		/*  11   */
    TDA18275_AGC4_Gain_Read_14 = 4,		/*  14   */
    TDA18275_AGC4_Gain_Read_val_5_NOT_USED = 5,		/*  val 5 NOT USED   */
    TDA18275_AGC4_Gain_Read_val_6_NOT_USED = 6,		/*  val 6 NOT USED   */
    TDA18275_AGC4_Gain_Read_val_7_NOT_USED = 7		/*  val 7 NOT USED  */
} TDA18275_AGC4_Gain_Read_t, *pTDA18275_AGC4_Gain_Read_t;

/* TDA18275 Register IFAGCs_Gain_byte 0x2E */
extern const TDA18275_BitField_t gTDA18275_Reg_IFAGCs_Gain_byte;
/* AGC5_Gain_Read bit(s): reads current AGC5 gain value (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_IFAGCs_Gain_byte__AGC5_Gain_Read;
/* AGC4_Gain_Read bit(s): reads current AGC4 gain value (dB) */
extern const TDA18275_BitField_t gTDA18275_Reg_IFAGCs_Gain_byte__AGC4_Gain_Read;


typedef enum _TDA18275_RSSI_AV_Item_t {
    TDA18275_RSSI_AV_Slow = 0,		/*  Slow   */
    TDA18275_RSSI_AV_Fast = 1		/*  Fast  */
} TDA18275_RSSI_AV_t, *pTDA18275_RSSI_AV_t;

typedef enum _TDA18275_Det6_Cap_Val_Item_t {
    TDA18275_Det6_Cap_Val_0d5_pF = 0,		/*  0.5 pF  */
    TDA18275_Det6_Cap_Val_3_pF = 1		/*  3 pF */
} TDA18275_Det6_Cap_Val_t, *pTDA18275_Det6_Cap_Val_t;

typedef enum _TDA18275_RSSI_Ck_Speed_Item_t {
    TDA18275_RSSI_Ck_Speed_31_25_KHz = 0,		/*  31,25 KHz  */
    TDA18275_RSSI_Ck_Speed_250_KHz = 1		/*  250 KHz */
} TDA18275_RSSI_Ck_Speed_t, *pTDA18275_RSSI_Ck_Speed_t;

/* TDA18275 Register RSSI_byte_2 0x30 */
extern const TDA18275_BitField_t gTDA18275_Reg_RSSI_byte_2;
/* RSSI_AV bit(s): RSSI average mode */
extern const TDA18275_BitField_t gTDA18275_Reg_RSSI_byte_2__RSSI_AV;
/* Det6_Cap_Val bit(s): selects Detector 6 integration capacitor value (pF) */
extern const TDA18275_BitField_t gTDA18275_Reg_RSSI_byte_2__Det6_Cap_Val;
/* RSSI_Ck_Speed bit(s): RSSI clock selection (kHz) */
extern const TDA18275_BitField_t gTDA18275_Reg_RSSI_byte_2__RSSI_Ck_Speed;


/* TDA18275 Register Sublo_byte 0x33 */
extern const TDA18275_BitField_t gTDA18275_Reg_Sublo_byte;
/* SUBLO_prog bit(s): SubLO divider ratio */
extern const TDA18275_BitField_t gTDA18275_Reg_Sublo_byte__SUBLO_prog;


typedef enum _TDA18275_LoChain_ratio_Item_t {
    TDA18275_LoChain_ratio_2 = 0,		/*  2   */
    TDA18275_LoChain_ratio_3 = 1,		/*  3   */
    TDA18275_LoChain_ratio_4 = 2,		/*  4   */
    TDA18275_LoChain_ratio_6 = 3,		/*  6   */
    TDA18275_LoChain_ratio_8 = 8,		/*  8   */
    TDA18275_LoChain_ratio_12 = 9,		/*  12   */
    TDA18275_LoChain_ratio_16 = 10,		/*  16   */
    TDA18275_LoChain_ratio_24 = 11,		/*  24   */
    TDA18275_LoChain_ratio_32 = 12		/*  32  */
} TDA18275_LoChain_ratio_t, *pTDA18275_LoChain_ratio_t;

/* TDA18275 Register LoChain_byte 0x34 */
extern const TDA18275_BitField_t gTDA18275_Reg_LoChain_byte;
/* PLL_Div2_Highfreq bit(s): PLL Div2 biasing */
extern const TDA18275_BitField_t gTDA18275_Reg_LoChain_byte__PLL_Div2_Highfreq;
/* LoChain_ratio bit(s): selects LO divider ratio */
extern const TDA18275_BitField_t gTDA18275_Reg_LoChain_byte__LoChain_ratio;


/* TDA18275 Register Sigma_delta_byte_1 0x35 */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_delta_byte_1;
/* LO_Int bit(s): selects sigma delta integer ratio */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_delta_byte_1__LO_Int;


/* TDA18275 Register Sigma_delta_byte_2 0x36 */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_delta_byte_2;
/* LO_Frac_2 bit(s): selects sigma delta fractional ratio (MSB) */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_delta_byte_2__LO_Frac_2;


/* TDA18275 Register Sigma_delta_byte_3 0x37 */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_delta_byte_3;
/* LO_Frac_1 bit(s): selects sigma delta fractional ratio (LSB) */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_delta_byte_3__LO_Frac_1;


/* TDA18275 Register Sigma_prog_byte 0x38 */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_prog_byte;
/* Update_prg bit(s): PLL divider ratios synchronisation */
extern const TDA18275_BitField_t gTDA18275_Reg_Sigma_prog_byte__Update_prg;


typedef enum _TDA18275_cp_cursel_Item_t {
    TDA18275_cp_cursel_20_uA = 0,		/*  20 uA  */
    TDA18275_cp_cursel_150_uA = 1,		/*  150 uA  */
    TDA18275_cp_cursel_210_uA = 2,		/*  210 uA  */
    TDA18275_cp_cursel_300_uA = 3,		/*  300 uA  */
    TDA18275_cp_cursel_420_uA = 4,		/*  420 uA  */
    TDA18275_cp_cursel_580_uA = 5,		/*  580 uA  */
    TDA18275_cp_cursel_800_uA = 6,		/*  800 uA  */
    TDA18275_cp_cursel_1100_uA = 7		/*  1100 uA */
} TDA18275_cp_cursel_t, *pTDA18275_cp_cursel_t;

/* TDA18275 Register Charge_pump_byte 0x3A */
extern const TDA18275_BitField_t gTDA18275_Reg_Charge_pump_byte;
/* ICP_Force_Sink bit(s): enables / disables the manual control on sinking charge pump */
extern const TDA18275_BitField_t gTDA18275_Reg_Charge_pump_byte__ICP_Force_Sink;
/* ICP_Force_Src bit(s): enables / disables the manual control on sourcing charge pump */
extern const TDA18275_BitField_t gTDA18275_Reg_Charge_pump_byte__ICP_Force_Src;
/* cpleak0 bit(s): enables / disables charge pump current offset */
extern const TDA18275_BitField_t gTDA18275_Reg_Charge_pump_byte__cpleak0;
/* cp_cursel bit(s): selects the charge pump current (uA) */
extern const TDA18275_BitField_t gTDA18275_Reg_Charge_pump_byte__cp_cursel;


/* TDA18275 Register SigmaDelta_Test_byte 0x3B */
extern const TDA18275_BitField_t gTDA18275_Reg_SigmaDelta_Test_byte;
/* LOSD_Static_N bit(s): Sigma Delta modulator ON / OFF */
extern const TDA18275_BitField_t gTDA18275_Reg_SigmaDelta_Test_byte__LOSD_Static_N;


typedef enum _TDA18275_VCO_Reg_Item_t {
    TDA18275_VCO_Reg_2d6_V = 0,		/*  2.6 V  */
    TDA18275_VCO_Reg_2d8_nom_V = 1,		/*  2.8  nom V  */
    TDA18275_VCO_Reg_3_V = 2,		/*  3 V  */
    TDA18275_VCO_Reg_val_3_Forbidden_V = 3		/*  val 3 Forbidden V */
} TDA18275_VCO_Reg_t, *pTDA18275_VCO_Reg_t;

/* TDA18275 Register Regulators_byte 0x3D */
extern const TDA18275_BitField_t gTDA18275_Reg_Regulators_byte;
/* VCO_Reg bit(s): selects VCO regulator voltage */
extern const TDA18275_BitField_t gTDA18275_Reg_Regulators_byte__VCO_Reg;


typedef enum _TDA18275_VCO_Select_Item_t {
    TDA18275_VCO_Select_VCO_High = 0,		/*  VCO_High   */
    TDA18275_VCO_Select_VCO_Medium = 1,		/*  VCO_Medium   */
    TDA18275_VCO_Select_VCO_Low = 2,		/*  VCO_Low   */
    TDA18275_VCO_Select_val_3_Forbidden = 3		/*  val 3 Forbidden  */
} TDA18275_VCO_Select_t, *pTDA18275_VCO_Select_t;

/* TDA18275 Register VCO_byte 0x3E */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_byte;
/* VCO_Select bit(s): selects VCO frequency band */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_byte__VCO_Select;


typedef enum _TDA18275_VCO_currentctrl_Item_t {
    TDA18275_VCO_currentctrl_0 = 0,		/*  0   */
    TDA18275_VCO_currentctrl_1 = 1,		/*  1   */
    TDA18275_VCO_currentctrl_2 = 2,		/*  2   */
    TDA18275_VCO_currentctrl_3 = 3,		/*  3   */
    TDA18275_VCO_currentctrl_4 = 4,		/*  4   */
    TDA18275_VCO_currentctrl_5 = 5,		/*  5   */
    TDA18275_VCO_currentctrl_6 = 6,		/*  6   */
    TDA18275_VCO_currentctrl_7 = 7,		/*  7   */
    TDA18275_VCO_currentctrl_8 = 8,		/*  8   */
    TDA18275_VCO_currentctrl_9 = 9,		/*  9   */
    TDA18275_VCO_currentctrl_10 = 10,		/*  10   */
    TDA18275_VCO_currentctrl_11 = 11,		/*  11   */
    TDA18275_VCO_currentctrl_12 = 12,		/*  12   */
    TDA18275_VCO_currentctrl_13 = 13,		/*  13   */
    TDA18275_VCO_currentctrl_14 = 14,		/*  14   */
    TDA18275_VCO_currentctrl_15 = 15		/*  15  */
} TDA18275_VCO_currentctrl_t, *pTDA18275_VCO_currentctrl_t;

/* TDA18275 Register VCO_cal_byte_1 0x3F */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_cal_byte_1;
/* VCOampl_force_cur bit(s): Forces a manual VCO amplitude */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_cal_byte_1__VCOampl_force_cur;
/* VCO_currentctrl bit(s): Reads the index returned by the VCO amplitude calibration or set the index value in case of a manual control */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_cal_byte_1__VCO_currentctrl;


typedef enum _TDA18275_VCO_swingctrl_Item_t {
    TDA18275_VCO_swingctrl_680_mV = 0,		/*  680 mV  */
    TDA18275_VCO_swingctrl_640_mV = 1,		/*  640 mV  */
    TDA18275_VCO_swingctrl_600_mV = 2,		/*  600 mV  */
    TDA18275_VCO_swingctrl_560_mV = 3,		/*  560 mV  */
    TDA18275_VCO_swingctrl_520_mV = 4,		/*  520 mV  */
    TDA18275_VCO_swingctrl_480_mV = 5,		/*  480 mV  */
    TDA18275_VCO_swingctrl_460_mV = 6,		/*  460 mV  */
    TDA18275_VCO_swingctrl_420_mV = 7,		/*  420 mV  */
    TDA18275_VCO_swingctrl_400_mV = 8,		/*  400 mV  */
    TDA18275_VCO_swingctrl_380_mV = 9,		/*  380 mV  */
    TDA18275_VCO_swingctrl_360_mV = 10,		/*  360 mV  */
    TDA18275_VCO_swingctrl_320_mV = 11,		/*  320 mV  */
    TDA18275_VCO_swingctrl_280_mV = 12,		/*  280 mV  */
    TDA18275_VCO_swingctrl_240_mV = 13,		/*  240 mV  */
    TDA18275_VCO_swingctrl_200_mV = 14,		/*  200 mV  */
    TDA18275_VCO_swingctrl_160_mV = 15		/*  160 mV */
} TDA18275_VCO_swingctrl_t, *pTDA18275_VCO_swingctrl_t;

/* TDA18275 Register VCO_cal_byte_2 0x40 */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_cal_byte_2;
/* VCO_swingctrl bit(s): VCO amplitude calibration target */
extern const TDA18275_BitField_t gTDA18275_Reg_VCO_cal_byte_2__VCO_swingctrl;


typedef enum _TDA18275_adc_vtune_Item_t {
    TDA18275_adc_vtune_0_to_0d33_V = 0,		/*  0 to 0.33 V  */
    TDA18275_adc_vtune_0d33_to_0d45_V = 1,		/*  0.33 to 0.45 V  */
    TDA18275_adc_vtune_0d45_to_0d58_V = 2,		/*  0.45 to 0.58 V  */
    TDA18275_adc_vtune_0d58_to_1d05_V = 3,		/*  0.58 to 1.05 V  */
    TDA18275_adc_vtune_1d05_to_1d62_V = 4,		/*  1.05 to 1.62 V  */
    TDA18275_adc_vtune_1d62_to_1d84_V = 5,		/*  1.62 to 1.84 V  */
    TDA18275_adc_vtune_1d84_to_2d1_V = 6,		/*  1.84 to 2.1 V  */
    TDA18275_adc_vtune_2d1_upper_V = 7		/*  2.1 upper V */
} TDA18275_adc_vtune_t, *pTDA18275_adc_vtune_t;

/* TDA18275 Register vco_log 0x41 */
extern const TDA18275_BitField_t gTDA18275_Reg_vco_log;
/* adc_vtune bit(s): vtune voltage measurement value (V) */
extern const TDA18275_BitField_t gTDA18275_Reg_vco_log__adc_vtune;


/* TDA18275 Register FVCO_MAX_BYTE_1 0x42 */
extern const TDA18275_BitField_t gTDA18275_Reg_FVCO_MAX_BYTE_1;
/* FVCO_max_1 bit(s): Current VCO frequency calibration result (MSB) */
extern const TDA18275_BitField_t gTDA18275_Reg_FVCO_MAX_BYTE_1__FVCO_max_1;


/* TDA18275 Register FVCO_MAX_BYTE_2 0x43 */
extern const TDA18275_BitField_t gTDA18275_Reg_FVCO_MAX_BYTE_2;
/* FVCO_max_2 bit(s): Current VCO frequency calibration result (medium byte) */
extern const TDA18275_BitField_t gTDA18275_Reg_FVCO_MAX_BYTE_2__FVCO_max_2;


/* TDA18275 Register FVCO_MAX_BYTE_3 0x44 */
extern const TDA18275_BitField_t gTDA18275_Reg_FVCO_MAX_BYTE_3;
/* FVCO_max_3 bit(s): Current VCO frequency calibration result (LSB) */
extern const TDA18275_BitField_t gTDA18275_Reg_FVCO_MAX_BYTE_3__FVCO_max_3;


typedef enum _TDA18275_RC_Cal_Offset_Item_t {
    TDA18275_RC_Cal_Offset_0 = 0,		/*  0   */
    TDA18275_RC_Cal_Offset_1 = 1,		/*  1   */
    TDA18275_RC_Cal_Offset_2 = 2,		/*  2   */
    TDA18275_RC_Cal_Offset_3 = 3		/*  3  */
} TDA18275_RC_Cal_Offset_t, *pTDA18275_RC_Cal_Offset_t;

/* TDA18275 Register RC_Cal_byte_1 0x45 */
extern const TDA18275_BitField_t gTDA18275_Reg_RC_Cal_byte_1;
/* RC_Cal_Offset bit(s): Index offset applied to the RC calibration */
extern const TDA18275_BitField_t gTDA18275_Reg_RC_Cal_byte_1__RC_Cal_Offset;


/* TDA18275 Register RC_Cal_byte_2 0x46 */
extern const TDA18275_BitField_t gTDA18275_Reg_RC_Cal_byte_2;
/* RCcal bit(s): RC calibration index result (including RC_Cal_Offset) */
extern const TDA18275_BitField_t gTDA18275_Reg_RC_Cal_byte_2__RCcal;


typedef enum _TDA18275_IR_ROM_offset_Item_t {
    TDA18275_IR_ROM_offset_0 = 0,		/*  0   */
    TDA18275_IR_ROM_offset_1 = 1,		/*  1   */
    TDA18275_IR_ROM_offset_2 = 2,		/*  2   */
    TDA18275_IR_ROM_offset_3 = 3		/*  3  */
} TDA18275_IR_ROM_offset_t, *pTDA18275_IR_ROM_offset_t;

typedef enum _TDA18275_IR_FreqPtr_Item_t {
    TDA18275_IR_FreqPtr_NOT_USED = 0,		/*  NOT USED   */
    TDA18275_IR_FreqPtr_Low = 1,		/*  Low   */
    TDA18275_IR_FreqPtr_Mid = 2,		/*  Mid   */
    TDA18275_IR_FreqPtr_high = 3		/*  high  */
} TDA18275_IR_FreqPtr_t, *pTDA18275_IR_FreqPtr_t;

/* TDA18275 Register IR_Cal_byte_3 0x47 */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Cal_byte_3;
/* IR_ROM_offset bit(s): Image Rejection calibration factor */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Cal_byte_3__IR_ROM_offset;
/* IR_FreqPtr bit(s): Pointer to Image Rejection calibration results */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Cal_byte_3__IR_FreqPtr;


typedef enum _TDA18275_ircal_boost_Item_t {
    TDA18275_ircal_boost_0 = 0,		/*  0   */
    TDA18275_ircal_boost_1 = 1,		/*  1   */
    TDA18275_ircal_boost_2 = 2,		/*  2   */
    TDA18275_ircal_boost_3 = 3		/*  3  */
} TDA18275_ircal_boost_t, *pTDA18275_ircal_boost_t;

/* TDA18275 Register IR_Cal_byte_4 0x48 */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Cal_byte_4;
/* ircal_boost bit(s): Image Rejection calibration generator amplitude index */
extern const TDA18275_BitField_t gTDA18275_Reg_IR_Cal_byte_4__ircal_boost;


/* TDA18275 Register Power_Down_byte_1 0x4A */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_Down_byte_1;
/* PD_adc_vtune bit(s): enables / disables the ADC connected on vtune */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_Down_byte_1__PD_adc_vtune;
/* PD_SUBLO bit(s):  */
extern const TDA18275_BitField_t gTDA18275_Reg_Power_Down_byte_1__PD_SUBLO;


/* TDA18275 Register Powerdown 0x4C */
extern const TDA18275_BitField_t gTDA18275_Reg_Powerdown;
/* force_soft_reset bit(s): enables / disables the software reset */
extern const TDA18275_BitField_t gTDA18275_Reg_Powerdown__force_soft_reset;
/* Soft_reset bit(s): Requests a software reset */
extern const TDA18275_BitField_t gTDA18275_Reg_Powerdown__Soft_reset;


/* TDA18275 Register Test_byte 0x4D */
extern const TDA18275_BitField_t gTDA18275_Reg_Test_byte;
/* reset_i2c_dis bit(s): Defines if I2C core is reset or not when performing a Soft_reset operation */
extern const TDA18275_BitField_t gTDA18275_Reg_Test_byte__reset_i2c_dis;



#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA18275_REGDEF_H */
