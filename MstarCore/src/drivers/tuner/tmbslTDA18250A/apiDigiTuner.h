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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
///
/// @file   apiDigiTuner.h
/// @brief  Digital Tuner Low-Level API
/// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////

#ifndef _API_DIGI_TUNER_H_
#define _API_DIGI_TUNER_H_

//---------------------------------------------------------------------------
//  Include file
//---------------------------------------------------------------------------
#include "Board.h"
#include "drvDemod.h"
#if MS_DVBS_INUSE
//#include "apiDTVSatTable.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#if MS_DVBS_INUSE
#define MAX_C_LOF_FREQ    6350   //4200+2150

#define SAT_MOVE_TIME           10 // s
#endif


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// Define converlution code rate for DVB-T and DVB-S
typedef enum
{
    CONV_CODE_RATE_1_2,                                                 ///< Code rate = 1/2
    CONV_CODE_RATE_2_3,                                                 ///< Code rate = 2/3
    CONV_CODE_RATE_3_4,                                                 ///< Code rate = 3/4
    CONV_CODE_RATE_5_6,                                                 ///< Code rate = 5/6
    CONV_CODE_RATE_7_8,                                                 ///< Code rate = 7/8
    CONV_CODE_RATE_3_5,                                                 ///< Code rate = 3/5
    CONV_CODE_RATE_4_5,                                                 ///< Code rate = 4/5
} EN_CONV_CODE_RATE_TYPE;

/// Define terrestrial band width
typedef enum
{
    BW_MODE_6MHZ = 0,                                                   ///< 6 MHz
    BW_MODE_7MHZ,                                                       ///< 7 MHz
    BW_MODE_8MHZ                                                        ///< 8 MHz
} EN_TER_BW_MODE;

/// Define terrestrial constellation type
typedef enum
{
    TER_QPSK,                                                           ///< QPSK type
    TER_QAM16,                                                          ///< QAM 16 type
    TER_QAM64,                                                           ///< QAM 64 type
    TER_QAM256                                                          ///< QAM 256 type
} EN_TER_CONSTEL_TYPE;

/// Define terrestrial hierarchy information
typedef enum
{
    TER_HIE_NONE,                                                       ///< Non-hierarchy
    TER_HIE_ALPHA_1,                                                    ///< Hierarchy alpha = 1
    TER_HIE_ALPHA_2,                                                    ///< Hierarchy alpha = 2
    TER_HIE_ALPHA_4                                                     ///< Hierarchy alpha = 4
} EN_TER_HIE_TYPE;

/// Define terrestrial guard interval
typedef enum
{
    TER_GI_1_32,                                                        ///< Guard interval value = 1/32
    TER_GI_1_16,                                                        ///< Guard interval value = 1/16
    TER_GI_1_8,                                                         ///< Guard interval value = 1/8
    TER_GI_1_4,                                                          ///< Guard interval value = 1/4
    TER_GI_1_128,                                                          ///< Guard interval value = 1/128
    TER_GI_19_128,                                                          ///< Guard interval value = 19/128
    TER_GI_19_256                                                          ///< Guard interval value = 19/256
} EN_TER_GI_TYPE;

/// Define terrestrial transmission mode
typedef enum
{
    TER_FFT_2K,                                                         ///< 2k FFT mode
    TER_FFT_8K,                                                          ///< 8k FFT mode
    //T2
    TER_FFT_8K_GI_LONG,                                                  /// 8k with guard interval 1/32, 1/16,1/8,1/4
    TER_FFT_4K,
    TER_FFT_1K,
    TER_FFT_16K,
    TER_FFT_32K_GI_LONG,                                                     /// 32k with guard interval 1/32, 1/16,1/8
    TER_FFT_8K_GI_SHORT,                                                     /// 8k with guard interval 1/128, 19/256,19/128
    TER_FFT_32K_GI_SHORT                                                     /// 32k with guard interval 1/128, 19/256,19/128
} EN_TER_FFT_MODE;

/// Define terrestrial transmission mode
typedef enum
{
    TER_HP_SEL,                                                         ///< High priority level selection
    TER_LP_SEL                                                          ///< Low priority level selection
} EN_TER_LEVEL_SEL;

/// Define DVB-C modulation scheme
typedef enum
{
    CAB_QAM16,                                                          ///< QAM 16
    CAB_QAM32,                                                          ///< QAM 32
    CAB_QAM64,                                                          ///< QAM 64
    CAB_QAM128,                                                         ///< QAM 128
    CAB_QAM256,                                                         ///< QAM256
    CAB_QAMAUTO                                                         ///< QAMAUTO
} EN_CAB_CONSTEL_TYPE;


/// Define DVB-S IQ tuning mode
typedef enum
{
    CAB_IQ_NORMAL,                                                      ///< Normal
    CAB_IQ_INVERT                                                       ///< Inverse
} EN_CAB_IQ_MODE;


/// Define DVB-S modulatiopn scheme
typedef enum
{
    SAT_QPSK,                                                           ///< QPSK
    SAT_8PSK,                                                           ///< 8PSK
    SAT_QAM16                                                           ///< QAM16
} EN_SAT_CONSTEL_TYPE;

/// Define DVB-S Roll-Off factor
typedef enum
{
    SAT_RO_35,                                                          ///< roll-off factor = 0.35
    SAT_RO_25,                                                          ///< roll-off factor = 0.25
    SAT_RO_20                                                           ///< roll-off factor = 0.20
} EN_SAT_ROLL_OFF_TYPE;

/// Define DVB-S IQ tuning mode
typedef enum
{
    SAT_IQ_NORMAL,                                                      ///< Normal
    SAT_IQ_INVERSE                                                      ///< Inverse
} EN_SAT_IQ_MODE;

/// Define Bit Error Rate range measure from signal
typedef enum
{
    BIT_ERR_RATIO_LOW ,                                                 ///< Low BER
    BIT_ERR_RATIO_MEDIUM ,                                              ///< Medium BER
    BIT_ERR_RATIO_HIGH                                                  ///< High BER
} EN_BIT_ERR_RATIO;

/// Define lock status of front end
typedef enum
{
    FE_UNLOCKED = 0,                                                    ///< Frontend is unlocked
    FE_LOCKED                                                           ///< Frontend is locked
} EN_FE_LOCK_STATUS;


/// Define tuning mode
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef enum
{
    FE_TUNE_MANUAL,                                                     ///< Manual tuning to carrier
    FE_TUNE_AUTO,                                                       ///< Auto tuning to carrier
} EN_FE_TUNE_MODE;

/// Define symbol rate for DVB-S, unit in symbol/sec
typedef MS_U32                      FE_SYMBOL_RATE;                     ///< unit in symbol/sec

/// Define the cellule identifier
typedef MS_U16                      FE_CELL_ID;

/// Define tuning paramter of DVB-T front-end
typedef struct
{
    MS_U8                           u8PlpID;
    EN_TER_BW_MODE                  eBandWidth;                         ///< Band width
    EN_TER_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    EN_TER_HIE_TYPE                 eHierarchy;                         ///< Hierarchy
    EN_TER_GI_TYPE                  eGuardInterval;                     ///< Guard interval
    EN_TER_FFT_MODE                 eFFT_Mode;                          ///< Transmission mode
    EN_CONV_CODE_RATE_TYPE          eHPCodeRate;                        ///< HP code rate
    EN_CONV_CODE_RATE_TYPE          eLPCodeRate;                        ///< LP code rate
    EN_TER_LEVEL_SEL                eLevelSel;                          ///< Select HP or LP level
} MS_TER_CARRIER_PARAM;

/// Define tuning paramter of DVB-C front-end
typedef struct
{
    EN_CAB_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    MS_U16                          u16SymbolRate;                      ///< Symbol rate (Ksym/sec)

    EN_CAB_IQ_MODE                  eIQMode;                            ///< IQ Mode
    MS_U8                           u8TapAssign;                        ///< Tap assign
    MS_U32                          u32FreqOffset;                      ///< Carrier frequency offset
    MS_U8                           u8TuneFreqOffset;                       ///< Requeset tuner freq offset
} MS_CAB_CARRIER_PARAM;

/// Define tuning paramter of DVB-S front-end
typedef struct
{
    EN_SAT_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    EN_SAT_ROLL_OFF_TYPE            eRollOff;                           ///< Roll-Off factor
    EN_SAT_IQ_MODE                  eIQ_Mode;                           ///< IQ mode
    EN_CONV_CODE_RATE_TYPE          eCodeRate;                          ///< Converlution code rate
    //FE_SYMBOL_RATE                  SymbolRate;                                      ///< Symbol rate
    MS_U16                          u16SymbolRate;                      ///< Symbol rate
#if MS_DVBS_INUSE
    MS_U8                           u8Polarity; // 0: Horizon; > 0(default 1): Vertical;
    MS_U8                           u8SatID;
#endif

} MS_SAT_CARRIER_PARAM;

/// Define carrier paramter of digital tuner
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef struct
{
    MS_U32                          u32Frequency;                       ///< RF frequency
    union
    {
        MS_TER_CARRIER_PARAM        TerParam;                           ///< Paramters for DVB-T front-end
        MS_CAB_CARRIER_PARAM        CabParam;                           ///< Paramters for DVB-C front-end
        MS_SAT_CARRIER_PARAM        SatParam;                           ///< Paramters for DVB-S front-end
    };
} MS_FE_CARRIER_PARAM;

/// Define the quality report
typedef struct
{
    EN_FE_LOCK_STATUS               eLock;
    EN_BIT_ERR_RATIO                eBER;                               ///< Bit error rate
    MS_U8                           u8SNR;
    MS_U8                           u8Signal;
} MS_FE_CARRIER_STATUS;

/// Define the carrier information
typedef struct
{
    MS_FE_CARRIER_PARAM             Param;                              ///< Carrier parameter
    MS_FE_CARRIER_STATUS            Status;                             ///< Quality report
} MS_FE_CARRIER_INFO;

#if MS_DVBS_INUSE

#define MAX_SATNAME_LEN 32


//diseqc
typedef enum
{
    EN_DISEQC_LVL_OFF,
    EN_DISEQC_LVL_10,
    EN_DISEQC_LVL_11,
    EN_DISEQC_LVL_12,
    EN_DISEQC_LVL_NUM,
    EN_DISEQC_LVL_13,
    EN_DISEQC_LVL_20,
    EN_DISEQC_LVL_MULTI
}MS_EN_DISEQC_LEVEL;

typedef enum
{
    EN_SWT_PORT_OFF,
    EN_SWT_PORT_1,
    EN_SWT_PORT_2,
    EN_SWT_PORT_3,
    EN_SWT_PORT_4,
    EN_SWT_PORT_5,
    EN_SWT_PORT_6,
    EN_SWT_PORT_7,
    EN_SWT_PORT_8,
    EN_SWT_PORT_9,
    EN_SWT_PORT_10,
    EN_SWT_PORT_11,
    EN_SWT_PORT_12,
    EN_SWT_PORT_13,
    EN_SWT_PORT_14,
    EN_SWT_PORT_15,
    EN_SWT_PORT_16,
    EN_SWT_PORT_NUM,
    EN_SWT_DISEQC10_PORT_NUM = EN_SWT_PORT_5,
    EN_SWT_DISEQC11_PORT_NUM = EN_SWT_PORT_NUM,
}MS_EN_SWT_PORT;

typedef enum
{
    EN_TONEBURST_NONE,
    EN_TONEBURST_0,
    EN_TONEBURST_1,
    EN_TONEBURST_TYPE_NUM
}MS_EN_TONEBURST_TYPE;

typedef enum
{
    EN_22K_OFF,
    EN_22K_ON,
    EN_22K_AUTO,
    EN_22K_ONOFF_NUM
}MS_EN_22K_ONOFF;

typedef enum
{
    EN_LNBPWR_OFF,
    EN_LNBPWR_13OR18V,
    EN_LNBPWR_13V,
    EN_LNBPWR_18V,
    EN_LNBPWR_ONOFF_NUM
}MS_EN_LNBPWR_ONOFF;

typedef enum
{
    EN_0V12V_ONOFF_OFF,
    EN_0V12V_ONOFF_ON,
    EN_0V12V_ONOFF_NUM
}MS_EN_0V12V_ONOFF;

typedef enum
{
    EN_LNBTYPE_C,
    EN_LNBTYPE_KU,
    EN_LNBTYPE_2LOF,
    EN_LNBTYPE_NUM
}MS_EN_LNBTYPE;

typedef enum
{
    EN_BWTYPE_HALF,
    EN_BWTYPE_FULL,
    EN_BWTYPE_NUM
}MS_EN_BWTYPE;



typedef struct
{
    MS_U8 aSatName[MAX_SATNAME_LEN+1]; // Sat Name
    MS_U16 u16LoLOF; // low LOF value,unit MHz
    MS_U16 u16HiLOF; // high LOF value,unit MHz
    MS_EN_LNBTYPE eLNBType;// Single LOF or Double LOF
    MS_EN_DISEQC_LEVEL   eDiseqcLevel;
    MS_EN_TONEBURST_TYPE eToneburstType;//
    MS_EN_SWT_PORT  eSwt10Port; //
    MS_EN_SWT_PORT  eSwt11Port; //
    MS_EN_22K_ONOFF e22KOnOff;
    MS_EN_LNBPWR_ONOFF eLNBPwrOnOff;
    MS_EN_0V12V_ONOFF e0V12VOnOff; //@FIXME: is it used?
    MS_U8 u8Position; // Motor position  bit8 1:USALS 0:DISEQC1.2
    MS_U16 u16Angle; // angle
    MS_U8 bPorInvert;
}MS_SAT_PARAM;

#define DISEQC12_USALS_POSITION_NUM   0x40
#define DISEQC12_USALS_POSITION_MASK  0x3F
#define DISEQC_USALS_BIT    _BIT7
#define IsUSALS(x)   (x.u8Position&DISEQC_USALS_BIT)


#endif

typedef enum
{
    DETECT_MODE_NOT_SETTING = 0, 
    AUTO_SCAN   = 1,
    USER_DEFINE = 2,
} EN_FRONTEND_DETECT_MODE;

typedef enum
{
    FE_IN_EX_TERNAL_PATH_NOT_SETTING = 0, 
    FE_INTERNAL = 1, 
    FE_EXTERNAL = 2,
} EN_IN_EX_TERNAL_PATH;

typedef struct drv_frontend_entry
{
    EN_FRONTEND_DETECT_MODE  eDetectMode;
    EN_IN_EX_TERNAL_PATH     eInExTernalPath;
    MS_U32 dvb_type;
    MS_U32 dmx_input_path;
    struct drv_demodtab_entry* demodtab;
    struct drv_tunertab_entry* tunertab;
#if MS_DVBS_INUSE
    struct drv_dishtab_entry* dishtab;
#endif

}DEV_FRONTEND_TYPE;


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_Frontend_SetDemod(MS_U8 drv_frontend_index,MS_U32 u32DemodType);
MS_BOOL MApi_Frontend_SetTuner(MS_U8 drv_frontend_index,MS_U32 u32TunerType);
MS_BOOL MApi_Frontend_SetDetectMode(MS_U8 drv_frontend_index,EN_FRONTEND_DETECT_MODE eDetectMode);
MS_BOOL MApi_Frontend_SetBroadcastType(MS_U8 drv_frontend_index,MS_U32 u32DvbType);
MS_BOOL MApi_Frontend_SetInExteralPath(MS_U8 drv_frontend_index,EN_IN_EX_TERNAL_PATH eInExTernalPath);
void MApi_PrintDemodTypes(void);
void MApi_PrintTunerTypes(void);
MS_U32 MApi_GetDmxInputPath(MS_U8 drv_frontend_index);

extern MS_U32 MApi_DigiTuner_GetFrontendType(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_ReInit(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DeInit(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_Init(MS_U8 drv_frontend_index);
#if MS_DVBS_INUSE
extern MS_BOOL MApi_DigiTuner_Tune2RfCh_DVBS(MS_U8 drv_frontend_index, MS_SAT_PARAM *pSATParam,MS_FE_CARRIER_PARAM *pParam, EN_FE_TUNE_MODE eMode);
#endif

extern MS_BOOL MApi_DigiTuner_Tune2RfCh(MS_U8 drv_frontend_index, MS_FE_CARRIER_PARAM *pParam, EN_FE_TUNE_MODE eMode);

extern MS_BOOL MApi_DigiTuner_GetMaxLockTime(MS_U8 drv_frontend_index, EN_FE_TUNE_MODE eMode, MS_U32 *u32LockTime);
extern MS_BOOL MApi_DigiTuner_PowerOnOff(MS_U8 drv_frontend_index, MS_BOOL bEnPower);
extern MS_BOOL MApi_DigiTuner_GetTPSInfo(MS_U8 drv_frontend_index, MS_FE_CARRIER_PARAM* pParam);
extern MS_BOOL MApi_DigiTuner_SetBW(MS_U8 drv_frontend_index, EN_TER_BW_MODE eBandWidth);
extern MS_BOOL MApi_DigiTuner_GetLock(MS_U8 drv_frontend_index, EN_LOCK_STATUS *peLockStatus);
extern MS_BOOL MApi_DigiTuner_GetSNR(MS_U8 drv_frontend_index, MS_U16 *pu32SNR);
extern MS_BOOL MApi_DigiTuner_GetPWR(MS_U8 drv_frontend_index, MS_S16 *ps16PWR);
extern MS_BOOL MApi_DigiTuner_GetPWRFromTuner(MS_U8 drv_frontend_index, float* pfPWR);
extern MS_BOOL MApi_DigiTuner_GetBER(MS_U8 drv_frontend_index, float *pfltBER);
extern MS_BOOL MApi_DigiTuner_Loop_Through_On(MS_U8 drv_frontend_index, MS_BOOL bOn);
extern MS_BOOL MApi_DigiTuner_Stand_By(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_Wake_Up(MS_U8 drv_frontend_index);

#if (MS_DVBT2_INUSE == 1)
extern MS_U8 MApi_DigiTuner_GetCurrentDemodType(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_SetCurrentDemodType(MS_U8 drv_frontend_index, MS_U8 type);
extern MS_BOOL MApi_DigiTuner_SetPlpGroupID(MS_U8 drv_frontend_index, MS_U8 u8PlpID, MS_U8 u8GroupID);
extern MS_BOOL MApi_DigiTuner_GetPlpGroupID(MS_U8 drv_frontend_index, MS_U8 u8PlpID, MS_U8* u8GroupID);
extern MS_BOOL MApi_DigiTuner_GetPlpBitMap(MS_U8 drv_frontend_index, MS_U8* u8PlpBitMap);
#endif

#if MS_DVBS_INUSE
extern void MApi_DigiTuner_ForceRetune(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_GetSatInfo(MS_SAT_PARAM* pSatInfo);
extern MS_BOOL MApi_DigiTuner_GetCurrentLOF(MS_U8 drv_frontend_index, MS_U16* pLOF);
extern MS_U16 MApi_DigiTuner_getCurRFSignalSNR_Persent(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_GetRollOff(MS_U8 drv_frontend_index, EN_SAT_ROLL_OFF_TYPE *pRollOff);
extern MS_BOOL MApi_DigiTuner_GetRFOffset(MS_U8 drv_frontend_index, MS_S16 *ps16RFOffset);

extern MS_BOOL MApi_DigiTuner_Satellite_Set22K(MS_U8 drv_frontend_index, MS_BOOL b22KOn);
extern MS_BOOL MApi_DigiTuner_Satellite_SetLNBPower(MS_U8 drv_frontend_index, MS_EN_LNBPWR_ONOFF enLNBPowe,MS_U8 u8Polarity,MS_BOOL bPorInvert);

extern MS_BOOL MApi_DigiTuner_BlindScan_Start(MS_U8 drv_frontend_index, MS_SAT_PARAM *pSATParam,MS_U8 u8Polarity,MS_BOOL bIsHiLOF);
extern MS_BOOL MApi_DigiTuner_BlindScan_NextFreq(MS_U8 drv_frontend_index, MS_BOOL* bBlindScanEnd);
extern MS_BOOL MApi_DigiTuner_BlindScan_WaitCurFeqFinished(MS_U8 drv_frontend_index, MS_U8* u8Progress,MS_U8* u8FindNum);
extern MS_BOOL MApi_DigiTuner_BlindScan_GetChannel(MS_U8 drv_frontend_index, MS_U16 u16ReadStart,MS_U16* u16TPNum,MS_FE_CARRIER_PARAM *pTPTable);
extern MS_BOOL MApi_DigiTuner_BlindScan_Cancel(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_BlindScan_End(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_BlindScan_GetCurrentFreq(MS_U8 drv_frontend_index, MS_U32 *u32Freq);
//------------------------------------------------------
// DiSEqC
//------------------------------------------------------
MS_BOOL MApi_DigiTuner_DiSEqC_SwitchPort(MS_U8 drv_frontend_index, MS_U8 u8Port,MS_BOOL bUnCommited);
extern MS_BOOL MApi_DigiTuner_DiSEqC_Reset(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_SetEastLimit(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_SetWestLimit(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_DisableLimit(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_GoReferencePoint(MS_U8 drv_frontend_index);
#if   DISEQC13_ONLY_GOTOX
extern MS_BOOL MApi_DigiTuner_DiSEqC_GoSatPos(MS_U8 drv_frontend_index, MS_SAT_PARAM *pSATParam);
#else
extern MS_BOOL MApi_DigiTuner_DiSEqC_GoSatPos(MS_U8 drv_frontend_index, MS_U8 u8SatPos);
#endif
extern MS_BOOL MApi_DigiTuner_DiSEqC_SaveSatPos(MS_U8 drv_frontend_index, MS_U8 u8SatPos);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorConinuteEast(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorConinuteWest(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorStepEast(MS_U8 drv_frontend_index, MS_U8 u8Step);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorStepWest(MS_U8 drv_frontend_index, MS_U8 u8Step);
extern MS_BOOL MApi_DigiTuner_DiSEqC_HaltMotor(MS_U8 drv_frontend_index);
extern MS_BOOL MApi_DigiTuner_DiSEqC_GotoX(MS_U8 drv_frontend_index, MS_U16 u16SatLongitude,MS_S16 s16MyLongitude,MS_S16 s16MyLatitude);
extern MS_BOOL MApi_DigiTuner_IsNeedCheckCurrent(void);
#endif


#endif // _API_DIGI_TUNER_H_

