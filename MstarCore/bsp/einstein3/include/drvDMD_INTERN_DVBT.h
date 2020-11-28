//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDMD_DVBT_INTERN.h
/// @brief  DVBT Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_DVBT_H_
#define _DRV_DVBT_H_

#include "MsCommon.h"
#include "drvDMD_common.h"
#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_DMD_DVBT_INTERN_LIB_CODE           {'D','V', 'B','T'} //Lib code
#define MSIF_DMD_DVBT_INTERN_LIBVER             {'0','1'}      //LIB version
#define MSIF_DMD_DVBT_INTERN_BUILDNUM           {'2','1' }    //Build Number
#define MSIF_DMD_DVBT_INTERN_CHANGELIST         {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define DMD_DVBT_INTERN_VER                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DMD_DVBT_INTERN_LIB_CODE,      /* IP__                                             */  \
    MSIF_DMD_DVBT_INTERN_LIBVER,        /* 0.0 ~ Z.Z                                        */  \
    MSIF_DMD_DVBT_INTERN_BUILDNUM,      /* 00 ~ 99                                          */  \
    MSIF_DMD_DVBT_INTERN_CHANGELIST,    /* CL#                                              */  \
    MSIF_OS

#define IS_BITS_SET(val, bits)                  (((val)&(bits)) == (bits))

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    DMD_DBGLV_NONE,    // disable all the debug message
    DMD_DBGLV_INFO,    // information
    DMD_DBGLV_NOTICE,  // normal but significant condition
    DMD_DBGLV_WARNING, // warning conditions
    DMD_DBGLV_ERR,     // error conditions
    DMD_DBGLV_CRIT,    // critical conditions
    DMD_DBGLV_ALERT,   // action must be taken immediately
    DMD_DBGLV_EMERG,   // system is unusable
    DMD_DBGLV_DEBUG,   // debug-level messages
} DMD_DbgLv;

typedef enum
{
    E_DMD_LOCK,
    E_DMD_CHECKING,
    E_DMD_CHECKEND,
    E_DMD_UNLOCK,
    E_DMD_NULL,
} DMD_LOCK_STATUS;

typedef enum
{
    E_DMD_DMD_DVBT_GETLOCK,
    E_DMD_COFDM_FEC_LOCK,
    E_DMD_COFDM_PSYNC_LOCK,
    E_DMD_COFDM_TPS_LOCK,
    E_DMD_COFDM_DCR_LOCK,
    E_DMD_COFDM_AGC_LOCK,
    E_DMD_COFDM_MODE_DET,
    E_DMD_COFDM_TPS_EVER_LOCK,
    E_DMD_COFDM_NO_CHANNEL,
    E_DMD_COFDM_NO_CHANNEL_IFAGC,
    E_DMD_COFDM_ATV_DETECT,
    E_DMD_COFDM_BER_LOCK,
    E_DMD_COFDM_SNR_LOCK,
    E_DMD_COFDM_TR_LOCK,
} DMD_DVBT_GETLOCK_TYPE;

typedef enum
{
    E_DMD_RF_CH_BAND_6MHz = 0x01,
    E_DMD_RF_CH_BAND_7MHz = 0x02,
    E_DMD_RF_CH_BAND_8MHz = 0x03,
    E_DMD_RF_CH_BAND_INVALID
} DMD_RF_CHANNEL_BANDWIDTH;

typedef enum
{
    E_DMD_DVBT_N_PARAM_VERSION = 0x00,    //0x00
    E_DMD_DVBT_N_OP_RFAGC_EN,
    E_DMD_DVBT_N_OP_HUMDET_EN,
    E_DMD_DVBT_N_OP_DCR_EN,
    E_DMD_DVBT_N_OP_IIS_EN,
    E_DMD_DVBT_N_OP_CCI_EN,
    E_DMD_DVBT_N_OP_ACI_EN,
    E_DMD_DVBT_N_OP_IQB_EN,
    E_DMD_DVBT_N_OP_AUTO_IQ_SWAP_EN,      //0x08
    E_DMD_DVBT_N_OP_AUTO_RF_MAX_EN,
    E_DMD_DVBT_N_OP_FORCE_ACI_EN,
    E_DMD_DVBT_N_OP_FIX_MODE_CP_EN,
    E_DMD_DVBT_N_OP_FIX_TPS_EN,
    E_DMD_DVBT_N_OP_AUTO_SCAN_MODE_EN,
    E_DMD_DVBT_N_CFG_RSSI,
    E_DMD_DVBT_N_CFG_ZIF,                 //0x0F

    E_DMD_DVBT_N_CFG_NIF,                 //0x10
    E_DMD_DVBT_N_CFG_LIF,
    E_DMD_DVBT_N_CFG_SAWLESS,
    E_DMD_DVBT_N_CFG_FS_L,
    E_DMD_DVBT_N_CFG_FS_H,
    E_DMD_DVBT_N_CFG_FIF_L,
    E_DMD_DVBT_N_CFG_FIF_H,
    E_DMD_DVBT_N_CFG_FC_L,
    E_DMD_DVBT_N_CFG_FC_H,                //0x18
    E_DMD_DVBT_N_CFG_BW,
    E_DMD_DVBT_N_CFG_MODE,
    E_DMD_DVBT_N_CFG_CP,
    E_DMD_DVBT_N_CFG_LP_SEL,
    E_DMD_DVBT_N_CFG_CSTL,
    E_DMD_DVBT_N_CFG_HIER,
    E_DMD_DVBT_N_CFG_HPCR,                //0x1F

    E_DMD_DVBT_N_CFG_LPCR,                //0x20
    E_DMD_DVBT_N_CFG_IQ_SWAP,
    E_DMD_DVBT_N_CFG_RFMAX,
    E_DMD_DVBT_N_CFG_CCI,
    E_DMD_DVBT_N_CFG_ICFO_RANGE,
    E_DMD_DVBT_N_CFG_RFAGC_REF,
    E_DMD_DVBT_N_CFG_IFAGC_REF_2K,
    E_DMD_DVBT_N_CFG_IFAGC_REF_8K,
    E_DMD_DVBT_N_CFG_IFAGC_REF_ACI,       //0x28
    E_DMD_DVBT_N_CFG_IFAGC_REF_IIS,
    E_DMD_DVBT_N_CFG_IFAGC_REF_2K_H,
    E_DMD_DVBT_N_CFG_IFAGC_REF_8K_H,
    E_DMD_DVBT_N_CFG_IFAGC_REF_ACI_H,
    E_DMD_DVBT_N_CFG_IFAGC_REF_IIS_H,
    E_DMD_DVBT_N_CFG_TS_SERIAL,
    E_DMD_DVBT_N_CFG_TS_CLK_INV,          //0x2F

    E_DMD_DVBT_N_CFG_TS_DATA_SWAP,        //0x30
    E_DMD_DVBT_N_CFG_8M_DACI_DET_TH_L,
    E_DMD_DVBT_N_CFG_8M_DACI_DET_TH_H,
    E_DMD_DVBT_N_CFG_8M_ANM1_DET_TH_L,
    E_DMD_DVBT_N_CFG_8M_ANM1_DET_TH_H,
    E_DMD_DVBT_N_CFG_8M_ANP1_DET_TH_L,
    E_DMD_DVBT_N_CFG_8M_ANP1_DET_TH_H,
    E_DMD_DVBT_N_CFG_7M_DACI_DET_TH_L,
    E_DMD_DVBT_N_CFG_7M_DACI_DET_TH_H,    //0x38
    E_DMD_DVBT_N_CFG_7M_ANM1_DET_TH_L,
    E_DMD_DVBT_N_CFG_7M_ANM1_DET_TH_H,
    E_DMD_DVBT_N_CFG_7M_ANP1_DET_TH_L,
    E_DMD_DVBT_N_CFG_7M_ANP1_DET_TH_H,
    E_DMD_DVBT_N_IFAGC_REF_READ,
    E_DMD_DVBT_N_IFAGC_K,
    E_DMD_DVBT_N_AGC_IF_GAIN_MIN,         //0x3F

    E_DMD_DVBT_N_AGC_IF_GAIN_MAX,         //0x40
    E_DMD_DVBT_N_AGC_LOCK_TH,
    E_DMD_DVBT_N_AGC_LOCK_NUM,
    E_DMD_DVBT_N_ADC_PGA_GAIN_I,
    E_DMD_DVBT_N_ADC_PGA_GAIN_Q,
    E_DMD_DVBT_N_PWDN_ADCI,
    E_DMD_DVBT_N_PWDN_ADCQ,
    E_DMD_DVBT_N_MPLL_ADC_DIV_SEL,
    E_DMD_DVBT_N_DCR_LOCK,                //0x48
    E_DMD_DVBT_N_MIXER_IQ_SWAP_MODE,
    E_DMD_DVBT_N_CCI_BYPASS,
    E_DMD_DVBT_N_CCI_LOCK_DET,
    E_DMD_DVBT_N_CCI_FSWEEP_L,
    E_DMD_DVBT_N_CCI_FSWEEP_H,
    E_DMD_DVBT_N_CCI_KPKI,
    E_DMD_DVBT_N_INTP_RATEM1_0,           //0x4F

    E_DMD_DVBT_N_INTP_RATEM1_1,           //0x50
    E_DMD_DVBT_N_INTP_RATEM1_2,
    E_DMD_DVBT_N_INTP_RATEM1_3,
    E_DMD_DVBT_N_8K_MC_MODE,
    E_DMD_DVBT_N_8K_MC_CP,
    E_DMD_DVBT_N_8K_MC_CPOBS_NUM,
    E_DMD_DVBT_N_8K_MODECP_DET,
    E_DMD_DVBT_N_2K_MC_MODE,
    E_DMD_DVBT_N_2K_MC_CP,                //0x58
    E_DMD_DVBT_N_2K_MC_CPOBS_NUM,
    E_DMD_DVBT_N_2K_MODECP_DET,
    E_DMD_DVBT_N_ICFO_SCAN_WINDOW_L,
    E_DMD_DVBT_N_ICFO_SCAN_WINDOW_H,
    E_DMD_DVBT_N_ICFO_MAX_OFFSET_L,
    E_DMD_DVBT_N_ICFO_MAX_OFFSET_H,
    E_DMD_DVBT_N_ICFO_DONE,               //0x5F

    E_DMD_DVBT_N_TPS_SYNC_LOCK,           //0x60
    E_DMD_DVBT_N_CONSTELLATION,
    E_DMD_DVBT_N_HIERARCHY,
    E_DMD_DVBT_N_HP_CODE_RATE,
    E_DMD_DVBT_N_LP_CODE_RATE,
    E_DMD_DVBT_N_GUARD_INTERVAL,
    E_DMD_DVBT_N_TRANSMISSION_MODE,
    E_DMD_DVBT_N_OFDM_SYMBOL_NUMBER,
    E_DMD_DVBT_N_LENGTH_INDICATOR,        //0x68
    E_DMD_DVBT_N_FRAME_NUMBER,
    E_DMD_DVBT_N_CELL_IDENTIFIER,
    E_DMD_DVBT_N_DVBH_SIGNALLING,
    E_DMD_DVBT_N_SNR_2K_ALPHA,
    E_DMD_DVBT_N_SNR_8K_ALPHA,
    E_DMD_DVBT_N_TS_EN,
    E_DMD_DVBT_N_2K_DAGC1_REF,            //0x6F

    E_DMD_DVBT_N_8K_DAGC1_REF,            //0x70
    E_DMD_DVBT_N_2K_8K_DAGC2_REF,
    E_DMD_DVBT_N_IF_INV_PWM_OUT_EN,
    E_DMD_DVBT_N_RESERVE_0,
    E_DMD_DVBT_N_RESERVE_1,
    E_DMD_DVBT_N_RESERVE_2,
    E_DMD_DVBT_N_RESERVE_3,
    E_DMD_DVBT_N_RESERVE_4,
    E_DMD_DVBT_N_RESERVE_5,               //0x78
    E_DMD_DVBT_N_RESERVE_6,
    E_DMD_DVBT_N_RESERVE_7,
    E_DMD_DVBT_N_RESERVE_8,
    E_DMD_DVBT_N_RESERVE_9,
    E_DMD_DVBT_N_RESERVE_10,
    E_DMD_DVBT_N_RESERVE_11,              //0x7E
}DVBT_N_Param;

typedef enum
{
//Parameter version
E_DMD_DVBT_PARAM_VERSION	= 0x00,//	0x00
//System
E_DMD_DVBT_OP_AUTO_SCAN_MODE_EN,//
E_DMD_DVBT_CFG_FREQ,//
E_DMD_DVBT_CFG_BW,//
E_DMD_DVBT_CFG_MODE,//
E_DMD_DVBT_CFG_CP,//
E_DMD_DVBT_CFG_LP_SEL,//
E_DMD_DVBT_CFG_CSTL,//
E_DMD_DVBT_CFG_HIER,	//0x08
E_DMD_DVBT_CFG_HPCR,//
E_DMD_DVBT_CFG_LPCR,//

//AGC
E_DMD_DVBT_OP_RFAGC_EN,//
E_DMD_DVBT_OP_HUMDET_EN,//
E_DMD_DVBT_OP_AUTO_RF_MAX_EN,//
E_DMD_DVBT_CFG_RFMAX,//
E_DMD_DVBT_CFG_ZIF,//
E_DMD_DVBT_CFG_RSSI,	//0x10
E_DMD_DVBT_CFG_RFAGC_REF,//
E_DMD_DVBT_AGC_K,//
E_DMD_DVBT_CFG_IFAGC_REF_2K,//
E_DMD_DVBT_CFG_IFAGC_REF_8K,//
E_DMD_DVBT_CFG_IFAGC_REF_ACI,//
E_DMD_DVBT_CFG_IFAGC_REF_IIS,//
E_DMD_DVBT_AGC_REF,
E_DMD_DVBT_AGC_LOCK_TH,	//0x18
E_DMD_DVBT_AGC_LOCK_NUM,	//
E_DMD_DVBT_AGC_GAIN_LOCK,//

//ADC
E_DMD_DVBT_PWDN_ADCI,//
E_DMD_DVBT_PWDN_ADCQ,//
E_DMD_DVBT_MPLL_ADC_DIV_SEL,//

//DCR
E_DMD_DVBT_OP_DCR_EN,//
E_DMD_DVBT_DCR_LOCK,//
E_DMD_DVBT_DCR_LEAKY_I_FF_0,//0x20
E_DMD_DVBT_DCR_LEAKY_I_FF_1,//0x20
E_DMD_DVBT_DCR_LEAKY_I_FF_2,//0x20
E_DMD_DVBT_DCR_LEAKY_Q_FF_0,	//
E_DMD_DVBT_DCR_LEAKY_Q_FF_1,	//
E_DMD_DVBT_DCR_LEAKY_Q_FF_2,	//

//IIS
E_DMD_DVBT_OP_IIS_EN,//

//Mixer
E_DMD_DVBT_CFG_FC_L,//
E_DMD_DVBT_CFG_FC_H,//
E_DMD_DVBT_CFG_FS_L,//
E_DMD_DVBT_CFG_FS_H,//
E_DMD_DVBT_MIXER_IQ_SWAP_MODE,//
E_DMD_DVBT_MIXER_IQ_SWAP_OUT_0,//0x28
E_DMD_DVBT_MIXER_IQ_SWAP_OUT_1,
E_DMD_DVBT_MIXER_IQ_SWAP_OUT_2,
E_DMD_DVBT_MIXER_IQ_SWAP_OUT_3,
E_DMD_DVBT_MIXER_IQ_DBG_SEL,//

//IQ Swap
E_DMD_DVBT_OP_IQB_EN,//
E_DMD_DVBT_OP_AUTO_IQ_SWAP_EN,//
E_DMD_DVBT_CFG_IQ_SWAP,//
E_DMD_DVBT_IQB_PHASE_COARSE_0,//
E_DMD_DVBT_IQB_PHASE_COARSE_1,//
E_DMD_DVBT_IQB_GAIN_COARSE_0,//
E_DMD_DVBT_IQB_GAIN_COARSE_1,//

//ACI
E_DMD_DVBT_OP_ACI_EN,//0x30
E_DMD_DVBT_OP_AUTO_ACI_EN,	//
E_DMD_DVBT_CFG_ACI_DET_TH_L,//
E_DMD_DVBT_CFG_ACI_DET_TH_H,//

//CCI
E_DMD_DVBT_OP_CCI_EN,//
E_DMD_DVBT_CFG_CCI,//
E_DMD_DVBT_CCI_BYPASS,//
E_DMD_DVBT_CCI_TRACK_SW_RST,//
E_DMD_DVBT_CCI_LOCK_DET,//0x38
E_DMD_DVBT_CCI_FREQN_OUT_0,	//
E_DMD_DVBT_CCI_FREQN_OUT_1, //

//Interpolator
E_DMD_DVBT_CFG_2K_SFO_DELAY_TIME_H,//
E_DMD_DVBT_CFG_2K_SFO_DELAY_TIME_L,//
E_DMD_DVBT_CFG_8K_SFO_DELAY_TIME_H,//
E_DMD_DVBT_CFG_8K_SFO_DELAY_TIME_L,//
E_DMD_DVBT_INTP_RATEM1_0,//
E_DMD_DVBT_INTP_RATEM1_1,//
E_DMD_DVBT_INTP_RATEM1_2,//
E_DMD_DVBT_INTP_RATEM1_3,//

//ModeCP
E_DMD_DVBT_OP_FIX_MODE_CP_EN,//
E_DMD_DVBT_8K_MC_MODE,//
E_DMD_DVBT_8K_MC_CP,//
E_DMD_DVBT_8K_MC_CPOBS_NUM,//
E_DMD_DVBT_8K_MODECP_DET, //
E_DMD_DVBT_2K_MC_MODE, //
E_DMD_DVBT_2K_MC_CP, //
E_DMD_DVBT_2K_MC_CPOBS_NUM, //
E_DMD_DVBT_2K_MODECP_DET, //

//ICFO
E_DMD_DVBT_CFG_ICFO_RANGE,//
//E_DMD_DVBT_ICFO_RANGE,//0x40
E_DMD_DVBT_ICFO_SCAN_WINDOW_0,	//
E_DMD_DVBT_ICFO_SCAN_WINDOW_1,	//
E_DMD_DVBT_ICFO_MAX_OFFSET_0,//
E_DMD_DVBT_ICFO_MAX_OFFSET_1,//
E_DMD_DVBT_ICFO_DONE,//

//TPS
E_DMD_DVBT_OP_FIX_TPS_EN,//
E_DMD_DVBT_TPS_SYNC_LOCK,//
E_DMD_DVBT_CONSTELLATION,//
E_DMD_DVBT_HIERARCHY,//
E_DMD_DVBT_HP_CODE_RATE,//0x48
E_DMD_DVBT_LP_CODE_RATE,	//
E_DMD_DVBT_GUARD_INTERVAL,//
E_DMD_DVBT_TRANSMISSION_MODE,//
E_DMD_DVBT_OFDM_SYMBOL_NUMBER,//
E_DMD_DVBT_LENGTH_INDICATOR,//
E_DMD_DVBT_FRAME_NUMBER,//
E_DMD_DVBT_CELL_IDENTIFIER,//
E_DMD_DVBT_DVBH_SIGNALLING,//0x50

//SNR
E_DMD_DVBT_SNR_ACCU_0,	//
E_DMD_DVBT_SNR_ACCU_1,	//
E_DMD_DVBT_SNR_ACCU_2,	//
E_DMD_DVBT_SNR_ACCU_3,	//
E_DMD_DVBT_BIT_ERR_NUM_7_0,//
E_DMD_DVBT_BIT_ERR_NUM_15_8,//
E_DMD_DVBT_BIT_ERR_NUM_23_16,//
E_DMD_DVBT_BIT_ERR_NUM_31_24,//
E_DMD_DVBT_UNCRT_PKT_NUM_7_0,//
E_DMD_DVBT_UNCRT_PKT_NUM_15_8,//

//TS
E_DMD_DVBT_CFG_TS_SERIAL,//0x58
E_DMD_DVBT_CFG_TS_CLK_RATE,//
E_DMD_DVBT_CFG_TS_CLK_INV,//
E_DMD_DVBT_CFG_TS_DATA_SWAP,//
E_DMD_DVBT_TS_EN,//
E_DMD_DVBT_TS_SOURCE_SEL,//
E_DMD_DVBT_DVBTM_TS_CLK_POL,//
E_DMD_DVBT_DVBTM_TS_CLK_DIVNUM,//0x60
E_DMD_DVBT_EN_TS_PAD,	//
E_DMD_DVBT_IF_INV_PWM_OUT_EN,

//Reserve
E_DMD_DVBT_RESERVE_1,
E_DMD_DVBT_RESERVE_2,
E_DMD_DVBT_RESERVE_3,
E_DMD_DVBT_RESERVE_4,

//Debug
E_DMD_DVBT_CHECKSUM,//0x62
} DVBT_Param;

/// For demod init
typedef struct
{
    // tuner parameter
    MS_U8 u8SarChannel;
    DMD_RFAGC_SSI *pTuner_RfagcSsi;
    MS_U16 u16Tuner_RfagcSsi_Size;
    DMD_IFAGC_SSI *pTuner_IfagcSsi_LoRef;
    MS_U16 u16Tuner_IfagcSsi_LoRef_Size;
    DMD_IFAGC_SSI *pTuner_IfagcSsi_HiRef;
    MS_U16 u16Tuner_IfagcSsi_HiRef_Size;
    DMD_IFAGC_ERR *pTuner_IfagcErr_LoRef;
    MS_U16 u16Tuner_IfagcErr_LoRef_Size;
    DMD_IFAGC_ERR *pTuner_IfagcErr_HiRef;
    MS_U16 u16Tuner_IfagcErr_HiRef_Size;
    DMD_SQI_CN_NORDIGP1 *pSqiCnNordigP1;
    MS_U16 u16SqiCnNordigP1_Size;

    // register init
    MS_U8 *u8DMD_DVBT_DSPRegInitExt; // TODO use system variable type
    MS_U8 u8DMD_DVBT_DSPRegInitSize;
    MS_U8 *u8DMD_DVBT_InitExt; // TODO use system variable type
} DMD_DVBT_InitData;

typedef enum
{
    E_DMD_DVBT_FAIL=0,
    E_DMD_DVBT_OK=1
} DMD_DVBT_Result;


typedef enum
{
    E_DMD_DVBT_MODULATION_INFO,
    E_DMD_DVBT_DEMOD_INFO,
    E_DMD_DVBT_LOCK_INFO,
    E_DMD_DVBT_PRESFO_INFO,
    E_DMD_DVBT_LOCK_TIME_INFO,
    E_DMD_DVBT_BER_INFO,
    E_DMD_DVBT_AGC_INFO,
} DMD_DVBT_INFO_TYPE;

typedef struct
{
    MS_U16 u16Version;
    MS_U8 u16DemodState;	//
	float SfoValue; //
	float TotalCfo; //
    MS_U16 u16ChannelLength; //	
	MS_U8 u8Fft; //
	MS_U8 u8Constel; //
	MS_U8 u8Gi; //
	MS_U8 u8HpCr; //
	MS_U8 u8LpCr; //	
	MS_U8 u8Hiearchy; //	
	MS_U8 u8Fd; //
	MS_U8 u8ChLen; //
	MS_U8 u8SnrSel;	//
	MS_U8 u8PertoneNum; //	
	MS_U8 u8DigAci; //
	MS_U8 u8FlagCi;	// 
	MS_U8 u8TdCoef;	//		
} DMD_DVBT_Info;

//typedef void(*P_DMD_ISR_Proc)(MS_U8 u8DMDID);


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Init
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_Init(DMD_DVBT_InitData *pDMD_DVBT_InitData, MS_U32 u32InitDataLen);
////////////////////////////////////////////////////////////////////////////////
/// Should be called when exit VD input source
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_Exit(void);
//------------------------------------------------------------------------------
/// Set detailed level of DVBT driver debug message
/// u8DbgLevel : debug level for Parallel Flash driver\n
/// AVD_DBGLV_NONE,    ///< disable all the debug message\n
/// AVD_DBGLV_INFO,    ///< information\n
/// AVD_DBGLV_NOTICE,  ///< normal but significant condition\n
/// AVD_DBGLV_WARNING, ///< warning conditions\n
/// AVD_DBGLV_ERR,     ///< error conditions\n
/// AVD_DBGLV_CRIT,    ///< critical conditions\n
/// AVD_DBGLV_ALERT,   ///< action must be taken immediately\n
/// AVD_DBGLV_EMERG,   ///< system is unusable\n
/// AVD_DBGLV_DEBUG,   ///< debug-level messages\n
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_DVBT_SetDbgLevel(DMD_DbgLv u8DbgLevel);
//-------------------------------------------------------------------------------------------------
/// Get the information of DVBT driver\n
/// @return the pointer to the driver information
//-------------------------------------------------------------------------------------------------
extern DMD_DVBT_Info* MDrv_DMD_DVBT_GetInfo(DMD_DVBT_INFO_TYPE eInfoType);
//-------------------------------------------------------------------------------------------------
/// Get DVBT driver version
/// when get ok, return the pointer to the driver version
//-------------------------------------------------------------------------------------------------
extern MS_BOOL MDrv_DMD_DVBT_GetLibVer(const MSIF_Version **ppVersion);
////////////////////////////////////////////////////////////////////////////////
/// To get DVBT's register  value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// return the value of AFEC's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetReg(MS_U16 u16Addr, MS_U8 *pu8Data);
////////////////////////////////////////////////////////////////////////////////
/// To set DVBT's register value, only for special purpose.\n
/// u16Addr       : the address of DVBT's register\n
/// u8Value        : the value to be set\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBTGetFWVer(MS_U16 *ver);
////////////////////////////////////////////////////////////////////////////////
/// Get DVBT FW version
/// u16Addr       : the address of DVBT's register\n
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_SetReg(MS_U16 u16Addr, MS_U8 u8Data);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetSerialControl
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_SetSerialControl(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfig
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_SetConfig(DMD_RF_CHANNEL_BANDWIDTH BW, MS_BOOL bSerialTS, MS_BOOL bPalBG);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfigHPLP
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_SetConfigHPLP(DMD_RF_CHANNEL_BANDWIDTH BW, MS_BOOL bSerialTS, MS_BOOL bPalBG, MS_BOOL bLPSel);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetConfigHPLPSetIF
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_SetConfigHPLPSetIF(DMD_RF_CHANNEL_BANDWIDTH BW, MS_BOOL bSerialTS, MS_BOOL bPalBG, MS_BOOL bLPSel, MS_U32 u32IFFreq, MS_U32 u32FSFreq, MS_U8 u8IQSwap);
///////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_SetActive
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_SetActive(MS_BOOL bEnable);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_Get_Lock
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetLock(DMD_DVBT_GETLOCK_TYPE eType, DMD_LOCK_STATUS *eLockStatus);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalStrength
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetSignalStrength(MS_U16 *u16Strength);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalStrengthWithRFPower
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetSignalStrengthWithRFPower(MS_U16 *u16Strength, float fRFPowerDbm);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalQuality
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetSignalQuality(MS_U16 *u16Quality);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSignalQualityWithRFPower
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetSignalQualityWithRFPower(MS_U16 *u16Quality, float fRFPowerDbm);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetSNR
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetSNR(float *fSNR);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetPostViterbiBer
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetPostViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetPreViterbiBer
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetPreViterbiBer(float *ber);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetPacketErr
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetPacketErr(MS_U16 *pktErr);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetTPSInfo
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetTPSInfo(MS_U16 *u16Info);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetCellID
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetCellID(MS_U16 *u16CellID);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_GetFreqOffset
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_GetFreqOffset(float *pFreqOff);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_NORDIG_SSI_Table_Write
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_NORDIG_SSI_Table_Write(DMD_CONSTEL constel, DMD_CODERATE code_rate, float write_value);
////////////////////////////////////////////////////////////////////////////////
/// MDrv_DMD_DVBT_NORDIG_SSI_Table_Read
////////////////////////////////////////////////////////////////////////////////
extern MS_BOOL MDrv_DMD_DVBT_NORDIG_SSI_Table_Read(DMD_CONSTEL constel, DMD_CODERATE code_rate, float *read_value);

extern MS_U32 MDrv_DMD_DVBT_SetPowerState(EN_POWER_MODE u16PowerState);
#ifdef __cplusplus
}
#endif


#endif // _DRV_DVBT_H_

