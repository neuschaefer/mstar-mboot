//-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2007 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of NXP Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of NXP
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than NXP Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmddNT220xlocal.h
//
// DESCRIPTION:  define the Object for the NT220x
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:        
//-----------------------------------------------------------------------------
//
#ifndef _TMDD_NT220xLOCAL_H //-----------------
#define _TMDD_NT220xLOCAL_H

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------

#include "../inc/tmddNT220x.h"

/*------------------------------------------------------------------------------*/
/* Project include files:                                                       */
/*------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

    //-----------------------------------------------------------------------------
    // Types and defines:
    //-----------------------------------------------------------------------------
    //

#define ddNT220x_MUTEX_TIMEOUT       TMBSL_FRONTEND_MUTEX_TIMEOUT_INFINITE

#define _SYSTEMFUNC (pObj->SystemFunc)

#define POBJ_SRVFUNC_SIO pObj->sRWFunc
#define POBJ_SRVFUNC_STIME pObj->sTime
#define P_DBGPRINTEx pObj->sDebug.Print
#define P_DBGPRINTVALID ((pObj != Null) && (pObj->sDebug.Print != Null))

#define NT220x_DD_COMP_NUM    2 // Major protocol change - Specification change required
#define NT220x_DD_MAJOR_VER   3 // Minor protocol change - Specification change required
#define NT220x_DD_MINOR_VER   1001 // Software update - No protocol change - No specification change required

#define NT220x_POWER_LEVEL_MIN  40
#define NT220x_POWER_LEVEL_MAX  110

//Alex 2009Sept16 - change to 4 due to 4 tuner needed for combine FJ2215 and FJ2216
//#define NT220x_MAX_UNITS                  2
#define NT220x_MAX_UNITS                  4
#define NT220x_I2C_MAP_NB_BYTES           68

#define NT220x_DEVICE_ID_MASTER  1
#define NT220x_DEVICE_ID_SLAVE   0

    typedef struct _NT220x_I2C_Map_t
    {
        union
        {
            UInt8 ID_byte_1;
            struct       
            {
                UInt8 Ident_1:7;
                UInt8 MS:1;
            }bF;
        }uBx00;

        union
        {
            UInt8 ID_byte_2;
            struct
            {
                UInt8 Ident_2:8;
            }bF;
        }uBx01;

        union
        {
            UInt8 ID_byte_3;
            struct
            {
                UInt8 Minor_rev:4;
                UInt8 Major_rev:4;
            }bF;
        }uBx02;

        union
        {
            UInt8 Thermo_byte_1;
            struct
            {
                UInt8 TM_D:7;
                UInt8 UNUSED_I0_D0:1;
            }bF;
        }uBx03;

        union
        {
            UInt8 Thermo_byte_2;
            struct
            {
                UInt8 TM_ON:1;
                UInt8 UNUSED_I0_D0:7;
            }bF;
        }uBx04;

        union
        {
            UInt8 Power_state_byte_1;
            struct
            {
                UInt8 LO_Lock:1;
                UInt8 POR:1;
                UInt8 UNUSED_I0_D0:6;
            }bF;
        }uBx05;

        union
        {
            UInt8 Power_state_byte_2;
            struct
            {
                UInt8 SM_XT:1;
                UInt8 SM_LT:1;
                UInt8 SM_Synthe:1;
                UInt8 SM:1;
                UInt8 UNUSED_I0_D0:4;
            }bF;
        }uBx06;

        union
        {
            UInt8 Input_Power_Level_byte;
            struct
            {
                UInt8 Power_Level:7;
                UInt8 UNUSED_I0_D0:1;
            }bF;
        }uBx07;

        union
        {
            UInt8 IRQ_status;
            struct
            {
                UInt8 MSM_RCCal_End:1;
                UInt8 MSM_IRCAL_End:1;
                UInt8 MSM_RFCal_End:1;
                UInt8 MSM_LOCalc_End:1;
                UInt8 MSM_RSSI_End:1;
                UInt8 MSM_XtalCal_End:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_status:1;
            }bF;
        }uBx08;

        union
        {
            UInt8 IRQ_enable;
            struct
            {
                UInt8 MSM_RCCal_Enable:1;
                UInt8 MSM_IRCAL_Enable:1;
                UInt8 MSM_RFCAL_Enable:1;
                UInt8 MSM_LOCalc_Enable:1;
                UInt8 MSM_RSSI_Enable:1;
                UInt8 XtalCal_Enable:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_Enable:1;
            }bF;
        }uBx09;

        union
        {
            UInt8 IRQ_clear;
            struct
            {
                UInt8 MSM_RCCal_Clear:1;
                UInt8 MSM_IRCAL_Clear:1;
                UInt8 MSM_RFCal_Clear:1;
                UInt8 MSM_LOCalc_Clear:1;
                UInt8 MSM_RSSI_Clear:1;
                UInt8 XtalCal_Clear:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_Clear:1;
            }bF;
        }uBx0A;

        union
        {
            UInt8 IRQ_set;
            struct
            {
                UInt8 MSM_RCCal_Set:1;
                UInt8 MSM_IRCAL_Set:1;
                UInt8 MSM_RFCal_Set:1;
                UInt8 MSM_LOCalc_Set:1;
                UInt8 MSM_RSSI_Set:1;
                UInt8 XtalCal_Set:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_Set:1;
            }bF;
        }uBx0B;

        union
        {
            UInt8 AGC1_byte_1;
            struct
            {
                UInt8 AGC1_TOP:4;
                UInt8 UNUSED_I0_D0:2;
                UInt8 AGC1_6_15dB:1;
                UInt8 LT_Enable:1;
            }bF;
        }uBx0C;

        union
        {
            UInt8 AGC2_byte_1;
            struct
            {
                UInt8 AGC2_TOP:5;
                UInt8 UNUSED_I0_D0:3;
            }bF;
        }uBx0D;

        union
        {
            UInt8 AGCK_byte_1;
            struct
            {
                UInt8 AGCK_Mode:2;
                UInt8 AGCK_Step:2;
                UInt8 Pulse_Shaper_Disable:1;
                UInt8 AGCs_Up_Step:1;
                UInt8 AGCs_Up_Step_assym:2;
            }bF;
        }uBx0E;

        union
        {
            UInt8 RF_AGC_byte;
            struct
            {
                UInt8 RFAGC_Top:3;
                UInt8 RF_Atten_3dB:1;
                UInt8 RFAGC_Low_BW:1;
                UInt8 RFAGC_Adapt_TOP:2;
                UInt8 PD_RFAGC_Adapt:1;
            }bF;
        }uBx0F;

        union
        {
            UInt8 IR_Mixer_byte_1;
            struct
            {
                UInt8 IR_Mixer_Top:4;
                UInt8 UNUSED_I0_D0:4;
            }bF;
        }uBx10;

        union
        {
            UInt8 AGC5_byte_1;
            struct
            {
                UInt8 AGC5_TOP:4;
                UInt8 AGC5_Ana:1;
                UInt8 AGCs_Do_Step_assym:2;
                UInt8 UNUSED_I0_D0:1;
            }bF;
        }uBx11;

        union
        {
            UInt8 IF_AGC_byte;
            struct
            {
                UInt8 IF_level:3;
                UInt8 UNUSED_I0_D0:5;
            }bF;
        }uBx12;

        union
        {
            UInt8 IF_Byte_1;
            struct
            {
                UInt8 LP_Fc:3;
                UInt8 LP_FC_Offset:2;
                UInt8 IF_ATSC_Notch:1;
                UInt8 IF_HP_Fc:2;
            }bF;
        }uBx13;

        union
        {
            UInt8 Reference_Byte;
            struct
            {
                UInt8 XTout:2;
                UInt8 UNUSED_I0_D0:2;
                UInt8 XtalOsc_AnaReg_En:1;
                UInt8 UNUSED_I1_D0:1;
                UInt8 Digital_Clock_Mode:1;
                UInt8 I2C_Clock_Mode:1;
            }bF;
        }uBx14;

        union
        {
            UInt8 IF_Frequency_byte;
            struct
            {
                UInt8 IF_Freq:8;
            }bF;
        }uBx15;

        union
        {
            UInt8 RF_Frequency_byte_1;
            struct
            {
                UInt8 RF_Freq_1:4;
                UInt8 UNUSED_I0_D0:4;
            }bF;
        }uBx16;

        union
        {
            UInt8 RF_Frequency_byte_3;
            struct
            {
                UInt8 RF_Freq_3:8;
            }bF;
        }uBx18;

        union
        {
            UInt8 RF_Frequency_byte_2;
            struct
            {
                UInt8 RF_Freq_2:8;
            }bF;
        }uBx17;

        union
        {
            UInt8 MSM_byte_1;
            struct
            {
                UInt8 Calc_PLL:1;
                UInt8 RC_Cal:1;
                UInt8 IR_CAL_Wanted:1;
                UInt8 IR_Cal_Image:1;
                UInt8 IR_CAL_Loop:1;
                UInt8 RF_CAL:1;
                UInt8 RF_CAL_AV:1;
                UInt8 RSSI_Meas:1;
            }bF;
        }uBx19;

        union
        {
            UInt8 MSM_byte_2;
            struct
            {
                UInt8 MSM_Launch:1;
                UInt8 XtalCal_Launch:1;
                UInt8 UNUSED_I0_D0:6;
            }bF;
        }uBx1A;

        union
        {
            UInt8 PowerSavingMode;
            struct
            {
                UInt8 PSM_Lodriver:2;
                UInt8 PSM_Ifpoly:1;
                UInt8 PSM_Mixer:1;
                UInt8 PSMRFpoly:1;
                UInt8 PSM_StoB:1;
                UInt8 PSM_AGC1:2;
            }bF;
        }uBx1B;

        union
        {
            UInt8 DCC_byte;
            struct
            {
                UInt8 UNUSED_I0_D0:5;
                UInt8 DCC_psm:1;
                UInt8 DCC_Slow:1;
                UInt8 DCC_Bypass:1;
            }bF;
        }uBx1C;

        union
        {
            UInt8 FLO_max_byte;
            struct
            {
                UInt8 Fmax_Lo:6;
                UInt8 UNUSED_I0_D0:2;
            }bF;
        }uBx1D;

        union
        {
            UInt8 IR_Cal_byte_1;
            struct
            {
                UInt8 IR_GStep:3;
                UInt8 IR_Target:3;
                UInt8 IR_Loop:2;  
            }bF;
        }uBx1E;

        union
        {
            UInt8 IR_Cal_byte_2;
            struct
            {
                UInt8 IR_FreqLow:5;
                UInt8 IR_mode_ram_store:1;
                UInt8 IR_FreqLow_Sel:1;
                UInt8 IR_Corr_Boost:1;
            }bF;
        }uBx1F;

        union
        {
            UInt8 IR_Cal_byte_3;
            struct
            {
                UInt8 IR_FreqMid:5;
                UInt8 UNUSED_I0_D0:3;
            }bF;
        }uBx20;

        union
        {
            UInt8 IR_Cal_byte_4;
            struct
            {
                UInt8 IR_FreqHigh:5;
                UInt8 Coarse_IR_FreqHigh:1;
                UInt8 UNUSED_I0_D0:2;
            }bF;
        }uBx21;

        union
        {
            UInt8 Vsync_Mgt_byte;
            struct
            {
                UInt8 AGC_Ovld_Timer:2;
                UInt8 AGC_Ovld_TOP:3;
                UInt8 PD_Udld:1;
                UInt8 PD_Ovld:1;
                UInt8 PD_Vsync_Mgt:1;
            }bF;
        }uBx22;

        union
        {
            UInt8 IR_Mixer_byte_2;
            struct
            {
                UInt8 IF_Notch:1;
                UInt8 Hi_Pass:1;
                UInt8 UNUSED_I0_D0:3;
                UInt8 IR_Mixer_Do_step:2;
                UInt8 IR_Mixer_loop_off:1;
            }bF;
        }uBx23;

        union
        {
            UInt8 AGC1_byte_2;
            struct
            {
                UInt8 AGC1_Gain:4;
                UInt8 Force_AGC1_gain:1;
                UInt8 AGC1_Do_step:2;
                UInt8 AGC1_loop_off:1;
            }bF;
        }uBx24;

        union
        {
            UInt8 AGC5_byte_2;
            struct
            {
                UInt8 AGC5_Gain:2;
                UInt8 UNUSED_I0_D0:1;
                UInt8 Force_AGC5_gain:1;
                UInt8 UNUSED_I1_D0:1;
                UInt8 AGC5_Do_step:2;
                UInt8 AGC5_loop_off:1;
            }bF;
        }uBx25;

        union
        {
            UInt8 RF_Cal_byte_1;
            struct
            {
                UInt8 RFCAL_Freq1:2;
                UInt8 RFCAL_Offset_Cprog1:2;
                UInt8 RFCAL_Freq0:2;
                UInt8 RFCAL_Offset_Cprog0:2;
            }bF;
        }uBx26;

        union
        {
            UInt8 RF_Cal_byte_2;
            struct
            {
                UInt8 RFCAL_Freq3:2;
                UInt8 RFCAL_Offset_Cprog3:2;
                UInt8 RFCAL_Freq2:2;
                UInt8 RFCAL_Offset_Cprog2:2;
            }bF;
        }uBx27;

        union
        {
            UInt8 RF_Cal_byte_3;
            struct
            {
                UInt8 RFCAL_Freq5:2;
                UInt8 RFCAL_Offset_Cprog5:2;
                UInt8 RFCAL_Freq4:2;
                UInt8 RFCAL_Offset_Cprog4:2;
            }bF;
        }uBx28;

        union
        {
            UInt8 RF_Cal_byte_4;
            struct
            {
                UInt8 RFCAL_Freq7:2;
                UInt8 RFCAL_Offset_Cprog7:2;
                UInt8 RFCAL_Freq6:2;
                UInt8 RFCAL_Offset_Cprog6:2;
            }bF;
        }uBx29;

        union
        {
            UInt8 RF_Cal_byte_5;
            struct
            {
                UInt8 RFCAL_Freq9:2;
                UInt8 RFCAL_Offset_Cprog9:2;
                UInt8 RFCAL_Freq8:2;
                UInt8 RFCAL_Offset_Cprog8:2;
            }bF;
        }uBx2A;

        union
        {
            UInt8 RF_Cal_byte_6;
            struct
            {
                UInt8 RFCAL_Freq11:2;
                UInt8 RFCAL_Offset_Cprog11:2;
                UInt8 RFCAL_Freq10:2;
                UInt8 RFCAL_Offset_Cprog10:2;
            }bF;
        }uBx2B;

        union
        {
            UInt8 RF_Filters_byte_1;
            struct
            {
                UInt8 RF_Filter_Band:2;
                UInt8 RF_Filter_Gv:2;
                UInt8 Force_AGC2_gain:1;
                UInt8 AGC2_loop_off:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 RF_Filter_Bypass:1;
            }bF;
        }uBx2C;

        union
        {
            UInt8 RF_Filters_byte_2;
            struct
            {
                UInt8 RF_Filter_Cap:8;
            }bF;
        }uBx2D;

        union
        {
            UInt8 RF_Filters_byte_3;
            struct
            {
                UInt8 Gain_Taper:6;
                UInt8 AGC2_Do_step:2;
            }bF;
        }uBx2E;

        union
        {
            UInt8 RF_Band_Pass_Filter_byte;
            struct
            {
                UInt8 RF_BPF:3;
                UInt8 UNUSED_I0_D0:4;
                UInt8 RF_BPF_Bypass:1;
            }bF;
        }uBx2F;

        union
        {
            UInt8 CP_Current_byte;
            struct
            {
                UInt8 N_CP_Current:7;
                UInt8 UNUSED_I0_D0:1;
            }bF;
        }uBx30;

        union
        {
            UInt8 AGCs_DetOut_byte;
            struct
            {
                UInt8 Do_AGC1:1;
                UInt8 Up_AGC1:1;
                UInt8 Do_AGC2:1;
                UInt8 Up_AGC2:1;
                UInt8 Do_AGC4:1;
                UInt8 Up_AGC4:1;
                UInt8 Do_AGC5:1;
                UInt8 Up_AGC5:1;
            }bF;
        }uBx31;

        union
        {
            UInt8 RFAGCs_Gain_byte_1;
            struct
            {
                UInt8 AGC1_Gain_Read:4;
                UInt8 AGC2_Gain_Read:2;
                UInt8 UNUSED_I0_D0:2;
            }bF;
        }uBx32;

        union
        {
            UInt8 RFAGCs_Gain_byte_2;
            struct
            {
                UInt8 TOP_AGC3_Read:3;
                UInt8 UNUSED_I0_D0:5;
            }bF;
        }uBx33;

        union
        {
            UInt8 IFAGCs_Gain_byte;
            struct
            {
                UInt8 AGC4_Gain_Read:3;
                UInt8 AGC5_Gain_Read:2;
                UInt8 UNUSED_I0_D0:3;
            }bF;
        }uBx34;

        union
        {
            UInt8 RSSI_byte_1;
            UInt8 RSSI;
        }uBx35;

        union
        {
            UInt8 RSSI_byte_2;
            struct
            {
                UInt8 RSSI_Dicho_not:1;
                UInt8 RSSI_Ck_Speed:1;
                UInt8 RSSI_Cap_Val:1;
                UInt8 RSSI_Cap_Reset_En:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 RSSI_AV:1;
                UInt8 UNUSED_I1_D0:2;
            }bF;
        }uBx36;

        union
        {
            UInt8 Misc_byte;
            struct
            {
                UInt8 IRQ_Polarity:1;
                UInt8 RFCAL_DeltaGain:4;
                UInt8 DDS_Polarity:1;
                UInt8 RFCAL_Phi2:2;
            }bF;
        }uBx37;

        union
        {
            UInt8 rfcal_log_0;
            struct       
            {
                UInt8 rfcal_log_0:8;
            }bF;
        }uBx38;

        union
        {
            UInt8 rfcal_log_1;
            struct       
            {
                UInt8 rfcal_log_1:8;
            }bF;
        }uBx39;

        union
        {
            UInt8 rfcal_log_2;
            struct       
            {
                UInt8 rfcal_log_2:8;
            }bF;
        }uBx3A;

        union
        {
            UInt8 rfcal_log_3;
            struct       
            {
                UInt8 rfcal_log_3:8;
            }bF;
        }uBx3B;

        union
        {
            UInt8 rfcal_log_4;
            struct       
            {
                UInt8 rfcal_log_4:8;
            }bF;
        }uBx3C;

        union
        {
            UInt8 rfcal_log_5;
            struct       
            {
                UInt8 rfcal_log_5:8;
            }bF;
        }uBx3D;

        union
        {
            UInt8 rfcal_log_6;
            struct       
            {
                UInt8 rfcal_log_6:8;
            }bF;
        }uBx3E;

        union
        {
            UInt8 rfcal_log_7;
            struct       
            {
                UInt8 rfcal_log_7:8;
            }bF;
        }uBx3F;

        union
        {
            UInt8 rfcal_log_8;
            struct       
            {
                UInt8 rfcal_log_8:8;
            }bF;
        }uBx40;

        union
        {
            UInt8 rfcal_log_9;
            struct       
            {
                UInt8 rfcal_log_9:8;
            }bF;
        }uBx41;

        union
        {
            UInt8 rfcal_log_10;
            struct       
            {
                UInt8 rfcal_log_10:8;
            }bF;
        }uBx42;

        union
        {
            UInt8 rfcal_log_11;
            struct       
            {
                UInt8 rfcal_log_11:8;
            }bF;
        }uBx43;

    } NT220x_I2C_Map_t, *pNT220x_I2C_Map_t;

    typedef struct _tmNT220x_RFCalProg_t {
        UInt8   Cal_number;
        Int8    DeltaCprog;
        Int8    CprogOffset;
    } tmNT220x_RFCalProg_t, *ptmNT220x_RFCalProg_t;

    typedef struct _tmNT220x_RFCalCoeffs_t {
        UInt8   Sub_band;
        UInt8   Cal_number;
        Int32   RF_A1;
        Int32   RF_B1;
    } tmNT220x_RFCalCoeffs_t, *ptmNT220x_RFCalCoeffs_t;

#define NT220x_RFCAL_PROG_ROW (12)
#define NT220x_RFCAL_COEFFS_ROW (8)

    typedef struct _tmddNT220xObject_t {
        tmUnitSelect_t              tUnit;
        tmUnitSelect_t              tUnitW;
        ptmbslFrontEndMutexHandle   pMutex;
        Bool                        init;
        tmbslFrontEndIoFunc_t       sRWFunc;
        tmbslFrontEndTimeFunc_t     sTime;
        tmbslFrontEndDebugFunc_t    sDebug;
        tmbslFrontEndMutexFunc_t    sMutex;
        tmddNT220xPowerState_t    curPowerState;
        UInt8                       versionForced;
        Bool                        bIRQWait;
        Bool                        bSoftReset;
        Bool                        bRFCAL_SW_Algo_Enable;
        tmNT220x_RFCalProg_t      RFCAL_Prog[NT220x_RFCAL_PROG_ROW];
        tmNT220x_RFCalCoeffs_t    RFCAL_Coeffs[NT220x_RFCAL_COEFFS_ROW];
        NT220x_I2C_Map_t          I2CMap;
    } tmddNT220xObject_t, *ptmddNT220xObject_t, **pptmddNT220xObject_t;


    extern tmErrorCode_t ddNT220xGetIRQ_status(ptmddNT220xObject_t pObj, UInt8* puValue);
    extern tmErrorCode_t ddNT220xGetMSM_XtalCal_End(ptmddNT220xObject_t pObj, UInt8* puValue);

    extern tmErrorCode_t ddNT220xWaitIRQ(ptmddNT220xObject_t pObj, UInt32 timeOut, UInt32 waitStep, UInt8 irqStatus);
    extern tmErrorCode_t ddNT220xWaitXtalCal_End(ptmddNT220xObject_t pObj, UInt32 timeOut, UInt32 waitStep);

    extern tmErrorCode_t ddNT220xWrite(ptmddNT220xObject_t pObj, UInt8 uSubAddress, UInt8 uNbData);
    extern tmErrorCode_t ddNT220xRead(ptmddNT220xObject_t pObj, UInt8 uSubAddress, UInt8 uNbData);
    extern tmErrorCode_t ddNT220xWait(ptmddNT220xObject_t pObj, UInt32 Time);

    extern tmErrorCode_t ddNT220xMutexAcquire(ptmddNT220xObject_t   pObj, UInt32 timeOut);
    extern tmErrorCode_t ddNT220xMutexRelease(ptmddNT220xObject_t   pObj);

#ifdef __cplusplus
}
#endif

#endif // _TMDD_NT220xLOCAL_H //---------------
