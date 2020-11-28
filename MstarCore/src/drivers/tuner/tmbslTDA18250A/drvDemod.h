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
#ifndef __DRV_DEMOD_H__
#define __DRV_DEMOD_H__

#include "Board.h"

#define MAX_TPS_LPF            10  //DVBS_STYLE

#if 0
/// Demodulator tune parameter
typedef struct
{
    // Channel setting
    MS_U32                          u32SymRate;                         ///< Symbol rate (Ksym/sec)
    // Channel characteristic
    DMD_QAMType                     eQamType;                           ///< QAM type
    DMD_IQType                      eIQSwap;                            ///< IQ type
    DMD_TapAssign                   eTapAssign;                         ///< Tap assign
    MS_U32                          u32FreqOffset;                      ///< Carrier frequency offset
    MS_U8                           u8TuneFreqOffset;                   ///< Request Tuner offset
    MS_U32                          u32TunerFreq;                       ///< Request Tuner offset
} DMD_Param;
#endif

typedef enum
{
    E_DEMOD_LOCK = 0,
    E_DEMOD_CHECKING,
    E_DEMOD_CHECKEND,
    E_DEMOD_UNLOCK,
    E_DEMOD_NULL,
} EN_LOCK_STATUS;

/// Define extension function types
typedef enum
{
    DEMOD_EXT_FUNC_OPEN,
    DEMOD_EXT_FUNC_CLOSE,
    DEMOD_EXT_FUNC_RESET,
    DEMOD_EXT_FUNC_TS_OUT,
    DEMOD_EXT_FUNC_POWER_ON_OFF,
    DEMOD_EXT_FUNC_SET_BW,
    DEMOD_EXT_FUNC_GET_BW,
    DEMOD_EXT_FUNC_SET_MODE,
    DEMOD_EXT_FUNC_CONFIG,
    DEMOD_EXT_FUNC_GET_ROLL_OFF,
    DEMOD_EXT_FUNC_GET_RF_OFFSET,
    DEMOD_EXT_FUNC_SET_TS_SERIAL,
    DEMOD_EXT_FUNC_FINALIZE,
    DEMOD_EXT_FUNC_EXISTED
} DEMOD_EXT_FUNCTION_TYPE;


/// Define converlution code rate for DVB-T and DVB-S
typedef enum
{
    DEMOD_CONV_CODE_RATE_1_2=0,                                                 ///< Code rate = 1/2
    DEMOD_CONV_CODE_RATE_2_3,                                                 ///< Code rate = 2/3
    DEMOD_CONV_CODE_RATE_3_4,                                                 ///< Code rate = 3/4
    DEMOD_CONV_CODE_RATE_5_6,                                                 ///< Code rate = 5/6
    DEMOD_CONV_CODE_RATE_7_8,                                                 ///< Code rate = 7/8
    DEMOD_CONV_CODE_RATE_3_5,                                                 ///< Code rate = 3/5
    DEMOD_CONV_CODE_RATE_4_5,                                                 ///< Code rate = 4/5
} DEMOD_EN_CONV_CODE_RATE_TYPE;

/// Define terrestrial band width
typedef enum
{
    DEMOD_BW_MODE_6MHZ = 0,                                                   ///< 6 MHz
    DEMOD_BW_MODE_7MHZ,                                                       ///< 7 MHz
    DEMOD_BW_MODE_8MHZ,                                                       ///< 8 MHz
    DEMOD_BW_MODE_1_7MHZ
} DEMOD_EN_TER_BW_MODE;

/// Define terrestrial constellation type
typedef enum
{
    DEMOD_TER_QPSK,                                                           ///< QPSK type
    DEMOD_TER_QAM16,                                                          ///< QAM 16 type
    DEMOD_TER_QAM64,                                                           ///< QAM 64 type
    DEMOD_TER_QAM256                                                           ///< QAM 256 type
} DEMOD_EN_TER_CONSTEL_TYPE;

/// Define terrestrial hierarchy information
typedef enum
{
    DEMOD_TER_HIE_NONE,                                                       ///< Non-hierarchy
    DEMOD_TER_HIE_ALPHA_1,                                                    ///< Hierarchy alpha = 1
    DEMOD_TER_HIE_ALPHA_2,                                                    ///< Hierarchy alpha = 2
    DEMOD_TER_HIE_ALPHA_4                                                     ///< Hierarchy alpha = 4
} DEMOD_EN_TER_HIE_TYPE;

/// Define terrestrial guard interval
typedef enum
{
    DEMOD_TER_GI_1_32,                                                        ///< Guard interval value = 1/32
    DEMOD_TER_GI_1_16,                                                        ///< Guard interval value = 1/16
    DEMOD_TER_GI_1_8,                                                         ///< Guard interval value = 1/8
    DEMOD_TER_GI_1_4,                                                          ///< Guard interval value = 1/4
    DEMOD_TER_GI_1_128,                                                          ///< Guard interval value = 1/128
    DEMOD_TER_GI_19_128,                                                          ///< Guard interval value = 19/128
    DEMOD_TER_GI_19_256                                                          ///< Guard interval value = 19/256
} DEMOD_EN_TER_GI_TYPE;

/// Define terrestrial transmission mode
typedef enum
{
    DEMOD_TER_FFT_2K,                                                         ///< 2k FFT mode
    DEMOD_TER_FFT_8K,                                                          ///< 8k FFT mode
    //T2
    DEMOD_TER_FFT_8K_GI_LONG,                                                  /// 8k with guard interval 1/32, 1/16,1/8,1/4
    DEMOD_TER_FFT_4K,
    DEMOD_TER_FFT_1K,
    DEMOD_TER_FFT_16K,
    DEMOD_TER_FFT_32K_GI_LONG,                                                     /// 32k with guard interval 1/32, 1/16,1/8
    DEMOD_TER_FFT_8K_GI_SHORT,                                                     /// 8k with guard interval 1/128, 19/256,19/128
    DEMOD_TER_FFT_32K_GI_SHORT                                                     /// 32k with guard interval 1/128, 19/256,19/128
} DEMOD_EN_TER_FFT_MODE;

/// Define terrestrial transmission mode
typedef enum
{
    DEMOD_TER_HP_SEL,                                                         ///< High priority level selection
    DEMOD_TER_LP_SEL                                                          ///< Low priority level selection
} DEMOD_EN_TER_LEVEL_SEL;

/// Define DVB-C modulation scheme
typedef enum
{
    DEMOD_CAB_QAM16,                                                          ///< QAM 16
    DEMOD_CAB_QAM32,                                                          ///< QAM 32
    DEMOD_CAB_QAM64,                                                          ///< QAM 64
    DEMOD_CAB_QAM128,                                                         ///< QAM 128
    DEMOD_CAB_QAM256,
    DEMOD_CAB_QAMAUTO

} DEMOD_EN_CAB_CONSTEL_TYPE;


/// Define DVB-S IQ tuning mode
typedef enum
{
    DEMOD_CAB_IQ_NORMAL,                                                      ///< Normal
    DEMOD_CAB_IQ_INVERT                                                       ///< Inverse
} DEMOD_EN_CAB_IQ_MODE;

/// Define DVB-S modulatiopn scheme
typedef enum
{
    DEMOD_SAT_DVBS2,                                                          ///< DVBS2
    DEMOD_SAT_DVBS                                                            ///< DVBS
} DEMOD_EN_SAT_MOD_TYPE;


/// Define DVB-S modulatiopn scheme
typedef enum
{
    DEMOD_SAT_QPSK,                                                           ///< QPSK
    DEMOD_SAT_8PSK,                                                           ///< 8PSK
    DEMOD_SAT_QAM16                                                           ///< QAM16
} DEMOD_EN_SAT_CONSTEL_TYPE;

/// Define DVB-S Roll-Off factor
typedef enum
{
    DEMOD_SAT_RO_35,                                                          ///< roll-off factor = 0.35
    DEMOD_SAT_RO_25,                                                          ///< roll-off factor = 0.25
    DEMOD_SAT_RO_20                                                           ///< roll-off factor = 0.20
} DEMOD_EN_SAT_ROLL_OFF_TYPE;

/// Define DVB-S IQ tuning mode
typedef enum
{
    DEMOD_SAT_IQ_NORMAL,                                                      ///< Normal
    DEMOD_SAT_IQ_INVERSE                                                      ///< Inverse
} DEMOD_EN_SAT_IQ_MODE;

/// Define Bit Error Rate range measure from signal
typedef enum
{
    DEMOD_BIT_ERR_RATIO_LOW ,                                                 ///< Low BER
    DEMOD_BIT_ERR_RATIO_MEDIUM ,                                              ///< Medium BER
    DEMOD_BIT_ERR_RATIO_HIGH                                                  ///< High BER
} DEMOD_EN_BIT_ERR_RATIO;

/// Define lock status of front end
typedef enum
{
    DEMOD_FE_UNLOCKED = 0,                                                    ///< Frontend is unlocked
    DEMOD_FE_LOCKED                                                           ///< Frontend is locked
} DEMOD_EN_FE_LOCK_STATUS;


/// Define tuning mode
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef enum
{
    DEMOD_FE_TUNE_MANUAL,                                                     ///< Manual tuning to carrier
    DEMOD_FE_TUNE_AUTO,                                                       ///< Auto tuning to carrier
} DEMOD_EN_FE_TUNE_MODE;

/// Define output mode
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef enum
{
    DEMOD_INTERFACE_SERIAL = 0,                                                   ///< Serial interface
    DEMOD_INTERFACE_PARALLEL                                                  ///< Parallel interface
} DEMOD_INTERFACE_MODE;

typedef enum
{
     E_DEMOD_TYPE_T =0,
     E_DEMOD_TYPE_T2,
}EN_DEMOD_TYPE;


#if ((MS_DVB_TYPE_SEL == ATSC))
typedef enum
{
	DEMOD_MODE_NTSC,
	DEMOD_MODE_256QAM,
	DEMOD_MODE_64QAM,
	DEMOD_MODE_8VSB,
	DEMOD_MODE_NUM
} DEMOD_EN_DEMOD_MODE;
#endif


/// Define tuning paramter of DVB-T front-end
typedef struct
{
//#if ((MS_DVB_TYPE_SEL == DVBT2))
    MS_U8                                 u8PlpID;
//#endif
    DEMOD_EN_TER_BW_MODE                  eBandWidth;                         ///< Band width
    DEMOD_EN_TER_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    DEMOD_EN_TER_HIE_TYPE                 eHierarchy;                         ///< Hierarchy
    DEMOD_EN_TER_GI_TYPE                  eGuardInterval;                     ///< Guard interval
    DEMOD_EN_TER_FFT_MODE                 eFFT_Mode;                          ///< Transmission mode
    DEMOD_EN_CONV_CODE_RATE_TYPE          eHPCodeRate;                        ///< HP code rate
    DEMOD_EN_CONV_CODE_RATE_TYPE          eLPCodeRate;                        ///< LP code rate
    DEMOD_EN_TER_LEVEL_SEL                eLevelSel;                          ///< Select HP or LP level
} DEMOD_MS_TER_CARRIER_PARAM;

/// Define tuning paramter of DVB-C front-end
typedef struct
{
    DEMOD_EN_CAB_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    MS_U16                          u16SymbolRate;                      ///< Symbol rate (Ksym/sec)

    DEMOD_EN_CAB_IQ_MODE                  eIQMode;                            ///< IQ Mode
    MS_U8                           u8TapAssign;                        ///< Tap assign
    MS_U32                          u32FreqOffset;                      ///< Carrier frequency offset
    MS_U8                           u8TuneFreqOffset;                       ///< Requeset tuner freq offset
} DEMOD_MS_CAB_CARRIER_PARAM;

/// Define tuning paramter of DVB-S front-end
typedef struct
{
    DEMOD_EN_SAT_CONSTEL_TYPE             eConstellation;                     ///< Constellation type
    DEMOD_EN_SAT_ROLL_OFF_TYPE            eRollOff;                           ///< Roll-Off factor
    DEMOD_EN_SAT_IQ_MODE                  eIQ_Mode;                           ///< IQ mode
    DEMOD_EN_CONV_CODE_RATE_TYPE          eCodeRate;                          ///< Converlution code rate
    MS_U32                                u32SymbolRate;
#if MS_DVBS_INUSE
    MS_U8                                 u8Polarity;                         // 0: Horizon; > 0(default 1): Vertical;
#endif
} DEMOD_MS_SAT_CARRIER_PARAM;

/// Define carrier paramter of digital tuner
/// NOTE: When this typedef is modified, the apiChScan should be rebuild.
typedef struct
{
    MS_U32                          u32Frequency;                       ///< RF frequency
    union
    {
        DEMOD_MS_TER_CARRIER_PARAM        TerParam;                           ///< Paramters for DVB-T front-end
        DEMOD_MS_CAB_CARRIER_PARAM        CabParam;                           ///< Paramters for DVB-C front-end
        DEMOD_MS_SAT_CARRIER_PARAM        SatParam;                           ///< Paramters for DVB-S front-end
    };
} DEMOD_MS_FE_CARRIER_PARAM;

/// Define the quality report
typedef struct
{
    DEMOD_EN_FE_LOCK_STATUS               eLock;
    DEMOD_EN_BIT_ERR_RATIO                eBER;                               ///< Bit error rate
    MS_U8                           u8SNR;
    MS_U8                           u8Signal;
} DEMOD_MS_FE_CARRIER_STATUS;

/// Define the carrier information
typedef struct
{
    DEMOD_MS_FE_CARRIER_PARAM             Param;                              ///< Carrier parameter
    DEMOD_MS_FE_CARRIER_STATUS            Status;                             ///< Quality report
} DEMOD_MS_FE_CARRIER_INFO;

typedef struct
{
    // Demodulator option
    MS_BOOL                         bX4CFE_en;                          ///< Carrier frequency estimation
    MS_BOOL                         bPPD_en;                            ///< Tap assign estimation
    MS_BOOL                         bIQAutoSwap_en;                     ///< IQ mode auto swap
    MS_BOOL                         bQAMScan_en;                        ///< QAM type auto scan
    MS_BOOL                         bFHO_en;                            ///< FHO
    MS_BOOL                         (*fptTunerSet)(MS_U32);             ///< Tuner set freq function pointer
// } DMD_Mode;
} Demod_Mode;

#define _GET_DEMOD_ENTRY_NODE(var, Name) var##Name
#define GET_DEMOD_ENTRY_NODE(Name) _GET_DEMOD_ENTRY_NODE(demod_entry_,Name) 

#define DDIBLD_ATTRIB_SECTION(__sect__) __attribute__((section (__sect__)))

#define __string(_x) #_x
#define __xstring(_x) __string(_x)

#ifndef DDI_DRV_TABLE_ENTRY
#define DDI_DRV_TABLE_ENTRY( _name ) \
        DDIBLD_ATTRIB_SECTION(".ecos.demod." __xstring(_name) ".data")
#endif

typedef MS_BOOL     drv_demodop_init(MS_U8 u8DemodIndex);
typedef MS_BOOL     drv_demodop_Reset(MS_U8 u8DemodIndex);
typedef MS_BOOL     drv_demodop_GetLock(MS_U8 u8DemodIndex,EN_LOCK_STATUS *pbLock);
typedef MS_BOOL     drv_demodop_GetSNR(MS_U8 u8DemodIndex,MS_U32 *pu32SNR);
typedef MS_BOOL     drv_demodop_GetBER(MS_U8 u8DemodIndex,float *pfBER);
typedef MS_BOOL     drv_demodop_GetPWR(MS_U8 u8DemodIndex,MS_S32 *ps32Signal);
typedef MS_BOOL     drv_demodop_GetParam(MS_U8 u8DemodIndex,DEMOD_MS_FE_CARRIER_PARAM* pParam); // MS_BOOL MDrv_Demod_GetParam(DMD_Param *pParam);
typedef MS_BOOL     drv_demodop_Restart(MS_U8 u8DemodIndex,DEMOD_MS_FE_CARRIER_PARAM* pParam); // MS_BOOL MDrv_Demod_Restart(DMD_Param *pParam);
typedef MS_BOOL     drv_demodop_I2C_ByPass(MS_U8 u8DemodIndex,MS_BOOL bOn);
typedef MS_BOOL     drv_demodop_CheckExist(MS_U8 u8DemodIndex);
typedef MS_BOOL     drv_demodop_Extension_Function(MS_U8 u8DemodIndex, DEMOD_EXT_FUNCTION_TYPE fuction_type, void *data);

#if MS_DVBT2_INUSE
typedef MS_BOOL     drv_demodop_SetCurrentDemodType(MS_U8 u8DemodIndex, MS_U8 type);
typedef MS_U8       drv_demodop_GetCurrentDemodType(MS_U8 u8DemodIndex);
typedef MS_BOOL     drv_demodop_GetPlpBitMap(MS_U8 u8DemodIndex, MS_U8* u8PlpBitMap);
typedef MS_BOOL     drv_demodop_GetPlpGroupID(MS_U8 u8DemodIndex, MS_U8 u8PlpID, MS_U8* u8GroupID);
typedef MS_BOOL     drv_demodop_SetPlpGroupID(MS_U8 u8DemodIndex, MS_U8 u8PlpID, MS_U8 u8GroupID);
#endif

#if MS_DVBS_INUSE
typedef MS_BOOL     drv_demodop_BlindScan_Start(MS_U8 u8DemodIndex,MS_U16 u16StartFreq,MS_U16 u16EndFreq);
typedef MS_BOOL     drv_demodop_BlindScan_NextFreq(MS_U8 u8DemodIndex,MS_BOOL* bBlindScanEnd);
typedef MS_BOOL     drv_demodop_BlindScan_WaitCurFreqFinished(MS_U8 u8DemodIndex,MS_U8* u8Progress,MS_U8 *u8FindNum);
typedef MS_BOOL     drv_demodop_BlindScan_Cancel(MS_U8 u8DemodIndex);
typedef MS_BOOL     drv_demodop_BlindScan_End(MS_U8 u8DemodIndex);
typedef MS_BOOL     drv_demodop_BlindScan_GetChannel(MS_U8 u8DemodIndex, MS_U16 u16ReadStart,MS_U16* u16TPNum,DEMOD_MS_FE_CARRIER_PARAM *pTable);
typedef MS_BOOL     drv_demodop_BlindScan_GetCurrentFreq(MS_U8 u8DemodIndex, MS_U32 *u32CurrentFeq);
typedef MS_BOOL     drv_demodop_DiSEqC_SetTone(MS_U8 u8DemodIndex, MS_BOOL bTone1);
typedef MS_BOOL     drv_demodop_DiSEqC_SetLNBOut(MS_U8 u8DemodIndex, MS_BOOL bLow);
typedef MS_BOOL     drv_demodop_DiSEqC_GetLNBOut(MS_U8 u8DemodIndex, MS_BOOL* bLNBOutLow);
typedef MS_BOOL     drv_demodop_DiSEqC_Set22kOnOff(MS_U8 u8DemodIndex, MS_BOOL b22kOn);
typedef MS_BOOL     drv_demodop_DiSEqC_Get22kOnOff(MS_U8 u8DemodIndex, MS_BOOL* b22kOn);
typedef MS_BOOL     drv_demodop_DiSEqC_SendCmd(MS_U8 u8DemodIndex, MS_U8* pCmd,MS_U8 u8CmdSize);
#endif

typedef struct drv_demodtab_entry
{
    const char              *name;          // demod system name
    MS_U32                  data;            // private data value
    drv_demodop_init        *init;
    drv_demodop_GetLock     *GetLock;
    drv_demodop_GetSNR      *GetSNR;
    drv_demodop_GetBER      *GetBER;
    drv_demodop_GetPWR      *GetPWR;
    drv_demodop_GetParam    *GetParam;
    drv_demodop_Restart     *Restart;
    drv_demodop_I2C_ByPass  *I2CByPass;
    drv_demodop_Extension_Function  *Extension_Function;
    drv_demodop_CheckExist  *CheckExist;
    #if MS_DVBT2_INUSE
    drv_demodop_SetCurrentDemodType *SetCurrentDemodType;
    drv_demodop_GetCurrentDemodType *GetCurrentDemodType;
    drv_demodop_GetPlpBitMap *GetPlpBitMap;
    drv_demodop_GetPlpGroupID *GetPlpGroupID;
    drv_demodop_SetPlpGroupID *SetPlpGroupID;
    #endif
    #if MS_DVBS_INUSE
    drv_demodop_BlindScan_Start *BlindScanStart;
    drv_demodop_BlindScan_NextFreq  *BlindScanNextFreq;
    drv_demodop_BlindScan_WaitCurFreqFinished   *BlindScanWaitCurFreqFinished;
    drv_demodop_BlindScan_Cancel    *BlindScanCancel;
    drv_demodop_BlindScan_End   *BlindScanEnd;
    drv_demodop_BlindScan_GetChannel    *BlindScanGetChannel;
    drv_demodop_BlindScan_GetCurrentFreq    *BlindScanGetCurrentFreq;
    drv_demodop_DiSEqC_SetTone  *DiSEqCSetTone;
    drv_demodop_DiSEqC_SetLNBOut    *DiSEqCSetLNBOut;
    drv_demodop_DiSEqC_GetLNBOut    *DiSEqCGetLNBOut;
    drv_demodop_DiSEqC_Set22kOnOff  *DiSEqCSet22kOnOff;
    drv_demodop_DiSEqC_Get22kOnOff  *DiSEqCGet22kOnOff;
    drv_demodop_DiSEqC_SendCmd  *DiSEqC_SendCmd;
    #endif
} DRV_DEMOD_TABLE_TYPE;


#ifdef FE_AUTO_TEST
MS_U16  MDrv_Demod_ReadReg(MS_U16 RegAddr);
MS_BOOL MDrv_Demod_WriteReg(MS_U16 RegAddr, MS_U16 RegData);
MS_BOOL MDrv_Demod_Get_Packet_Error(MS_U16 *u16_data);
#endif

#endif // #define __DRV_DEMOD_H__
