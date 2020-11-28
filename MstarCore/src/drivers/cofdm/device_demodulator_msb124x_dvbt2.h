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

**********************************************************************/



#ifndef _MSB124X_H
#define _MSB124X_H


/*@ <Include> @*/
//#include "MsBoard.h"
//#include "MsCommon.h"
//#include "MsOS.h"
//#include "Tuner.h"
/*@ </Include> @*/

typedef enum
{
    ICE_network_dvbt2 = 0,
    ICE_network_dvbt,
    ICE_network_analog,
    ICE_network_num
} E_ICE_NETWORK_TYPE;

typedef struct
{
    MS_U32 channel_frequency_khz;
    E_ICE_NETWORK_TYPE  network_type;
} ICE_TuneToParams;

typedef struct
{
    MS_U8        cmd_code;
    MS_U8        param[64];
} S_CMDPKTREG;

/// define SAW Type Configuration
typedef enum
{
    /// 0: dual saw
    DUAL_SAW = 0,
    /// 1: external single saw
    EXTERNAL_SINGLE_SAW,
    /// 2: silicon tuner, need tri-state
    SILICON_TUNER,
    /// 2: internal single saw DIF, need tri-state
    INTERNAL_SINGLE_SAW_DIF = SILICON_TUNER,
    /// 3: no saw
    NO_SAW,
    /// 4: internal single saw VIF
    INTERNAL_SINGLE_SAW_VIF,
    /// 5: no saw (DIF)
    NO_SAW_DIF,
    SAW_NUMS
} SawArchitecture;

/// the signal strength
typedef enum
{
    /// no signal
    E_FE_SIGNAL_NO = 0,
    /// weak signal
    E_FE_SIGNAL_WEAK,
    /// moderate signal
    E_FE_SIGNAL_MODERATE,
    /// strong signal
    E_FE_SIGNAL_STRONG,
    /// very strong signal
    E_FE_SIGNAL_VERY_STRONG,
} EN_FRONTEND_SIGNAL_CONDITION;


/// DVB-T modulation mode
typedef enum
{
    /// QPSK
    E_DVBT_QPSK     = 0,
    /// 16QAM
    E_DVBT_16_QAM   = 1,
    /// 64QAM
    E_DVBT_64_QAM   = 2,
    /// 256QAM
    E_DVBT_256_QAM  = 3,
    /// invalid indicator
    E_DVBT_INVALID
} EN_DVBT_CONSTEL_TYPE;

/// DVB-T code rate
typedef enum
{
    /// 1/2
    E_DVBT_CODERATE_1_2 = 0,
    /// 2/3
    E_DVBT_CODERATE_2_3 = 1,
    /// 3/4
    E_DVBT_CODERATE_3_4 = 2,
    /// 5/6
    E_DVBT_CODERATE_5_6 = 3,
    /// 7/8
    E_DVBT_CODERATE_7_8 = 4,
    /// 4/5
    E_DVBT_CODERATE_4_5 = 5,
    /// 6/7
    E_DVBT_CODERATE_6_7 = 6,
    /// 8/9
    E_DVBT_CODERATE_8_9 = 7,
    /// invalid indicator
    E_DVBT_CODERATE_INVALID,
} EN_DVBT_CODE_RATE;

/// guard interval enum
typedef enum
{
    /// 1/32
    E_DVBT_GUARD_INTERVAL_1_32  = 0,
    /// 1/16
    E_DVBT_GUARD_INTERVAL_1_16  = 1,
    /// 1/8
    E_DVBT_GUARD_INTERVAL_1_8   = 2,
    /// 1/4
    E_DVBT_GUARD_INTERVAL_1_4   = 3,
    /// 1/28
    E_DVBT_GUARD_INTERVAL_1_128 = 4,
    /// 19/128
    E_DVBT_GUARD_INTERVAL_19_128 = 5,
    /// 19/256
    E_DVBT_GUARD_INTERVAL_19_256 = 6,
    /// invalid indicator
    E_DVBT_GUARD_INTERVAL_INVALID,
} EN_DVBT_GUARD_INTERVAL;

/// FFT Ext-Bitmask
#define MSB_FLAG_FFT_EXT_DATA   0x08
/// DVB-T FFT enum
typedef enum
{
    /// 2K
    E_DVBT_FFT_2K = 0x00,
    /// 8k
    E_DVBT_FFT_8K = 0x01,
    /// 4k
    E_DVBT_FFT_4K = 0x02,
    /// 1k
    E_DVBT_FFT_1K = 0x03,
    /// 16k
    E_DVBT_FFT_16K = 0x04,
    /// 32k
    E_DVBT_FFT_32K = 0x05,
    /// 8K ext
    E_DVBT_FFT_8K_EXT = (E_DVBT_FFT_8K | MSB_FLAG_FFT_EXT_DATA),
    /// 16k ext
    E_DVBT_FFT_16K_EXT = (E_DVBT_FFT_16K | MSB_FLAG_FFT_EXT_DATA),
    /// 32k ext
    E_DVBT_FFT_32K_EXT = (E_DVBT_FFT_32K | MSB_FLAG_FFT_EXT_DATA),
    /// invalid indicator
    E_DVBT_FFT_INVALID,
} EN_DVBT_FFT_VAL;

typedef enum
{
    T2_MODUL_MODE,
    T2_FFT_VALUE,
    T2_GUARD_INTERVAL,
    T2_CODE_RATE,
    T2_PREAMBLE,
    T2_S1_SIGNALLING,
    T2_PILOT_PATTERN,
    T2_BW_EXT,
    T2_PAPR_REDUCTION,
    T2_OFDM_SYMBOLS_PER_FRAME
} E_SIGNAL_TYPE;

/*@ <Definitions> @*/
// ------------------------------------------------------------
// Other Define
// -----------------------------------------------------------

//#define     DEMOD_SLAVE_ID          DEMOD_DYNAMIC_SLAVE_ID_1
//#define     IIC_CH_MSB1233C         TUNER_IIC_BUS
#define MCP_MSB124X 1
#if MCP_MSB124X
#define DEMOD_DYNAMIC_SLAVE_ID_1    0xF2  // 0x32 //CMD
#else
#define DEMOD_DYNAMIC_SLAVE_ID_1    0xD2  // 0x32 //CMD
#endif
#define DEMOD_DYNAMIC_SLAVE_ID_2    0xA2 // 0x72 //ISP   
//    #define DEMOD_DYNAMIC_SLAVE_ID_3    0xB2
//    #define DEMOD_DYNAMIC_SLAVE_ID_4    0xF2
#define DEMOD_ADDR_H                0x00
#define DEMOD_ADDR_L                0x01
#define DEMOD_WRITE_REG             0x02
#define DEMOD_WRITE_REG_EX          0x03
#define DEMOD_READ_REG              0x04
#define DEMOD_RAM_CONTROL           0x05

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
#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0x0020
#define BIT6  0x0040
#define BIT7  0x0080
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000

/*@ </Definitions> @*/

#ifndef USE_UTOPIA
//mick
typedef enum
{
    // Operation Mode Settings,Address Start at 0x20
    C_opmode_rfagc_en = 0x20,
    C_opmode_humdet_en,
    C_opmode_dcr_en,
    C_opmode_iqb_en,
    C_opmode_auto_iq,
    C_opmode_auto_rfmax,
    C_opmode_auto_aci,
    C_opmode_auto_scan,
    C_opmode_auto_scan_sym_rate,  //0x28
    C_opmode_auto_scan_qam,
    C_opmode_atv_detector_en,
    C_if_inv_pwm_out_en,
    C_opmode_rsv_0x0C,
    C_opmode_rsv_0x0D,
    C_opmode_rsv_0x0E,
    C_opmode_rsv_0x0F,

    // Config Params
    C_config_rssi,    //0x30
    C_config_zif,
    C_config_freq,
    C_config_fc_l,
    C_config_fc_h,
    C_config_fs_l,
    C_config_fs_h,
    C_config_bw_l,
    C_config_bw_h,
    C_config_bw1_l,
    C_config_bw1_h,
    C_config_bw2_l,
    C_config_bw2_h,
    C_config_bw3_l,
    C_config_bw3_h,
    C_config_rsv_0x1F,
    C_config_rfmax,   //0x40
    C_config_qam,
    C_config_iq_swap,
    C_config_cci,
    C_config_ts_serial,
    C_config_ts_clk_rate,
    C_config_ts_out_inv,
    C_config_ts_data_swap,

    MSB124X_DVBC_PARAM_LEN,
} MSB124X_DVBC_Param;

typedef enum
{
    // operation mode settings
    T_OPMODE_RFAGC_EN  = 0x20,   // 0x20
    T_OPMODE_HUMDET_EN,
    T_OPMODE_DCR_EN,
    T_OPMODE_IIS_EN,
    T_OPMODE_CCI_EN,
    T_OPMODE_ACI_EN,
    T_OPMODE_IQB_EN,
    T_OPMODE_AUTO_IQ,
    T_OPMODE_AUTO_RFMAX,    // 0x28
    T_OPMODE_AUTO_ACI,
    T_OPMODE_FIX_MODE_CP,
    T_OPMODE_FIX_TPS,
    T_OPMODE_AUTO_SCAN,
    T_OPMODE_RSV_0X2D,
    T_OPMODE_RSV_0X2E,
    T_OPMODE_RSV_0X2F,

    // channel config param
    T_CONFIG_RSSI,    // 0x30
    T_CONFIG_ZIF,
    T_CONFIG_FREQ,
    T_CONFIG_FC_L,
    T_CONFIG_FC_H,
    T_CONFIG_FS_L,
    T_CONFIG_FS_H,
    T_CONFIG_BW,
    T_CONFIG_MODE,    // 0x38
    T_CONFIG_CP,
    T_CONFIG_LP_SEL,
    T_CONFIG_CSTL,
    T_CONFIG_HIER,
    T_CONFIG_HPCR,
    T_CONFIG_LPCR,
    T_CONFIG_IQ_SWAP,
    T_CONFIG_RFMAX,    // 0x40
    T_CONFIG_CCI,
    T_CONFIG_ICFO_RANGE,
    T_CONFIG_RFAGC_REF,
    T_CONFIG_IFAGC_REF_2K,
    T_CONFIG_IFAGC_REF_8K,
    T_CONFIG_IFAGC_REF_ACI,
    T_CONFIG_IFAGC_REF_IIS_2K,
    T_CONFIG_IFAGC_REF_IIS_8K,    // 0x48
    T_CONFIG_ACI_DET_TH_L,
    T_CONFIG_ACI_DET_TH_H,
    T_CONFIG_TS_SERIAL,
    T_CONFIG_TS_CLK_RATE,
    T_CONFIG_TS_OUT_INV,
    T_CONFIG_TS_DATA_SWAP,
    T_CONFIG_2K_SFO_H,
    T_CONFIG_2K_SFO_L,    // 0x50
    T_CONFIG_8K_SFO_H,
    T_CONFIG_8K_SFO_L,
    T_CONFIG_CHECK_CHANNEL,
    T_CONFIG_SLICER_SNR_POS,
    T_CONFIG_TDP_CCI_KP,
    T_CONFIG_CCI_FSWEEP,
    T_CONFIG_TS_CLK_RATE_AUTO,
    T_CONFIG_IF_INV_PWM_OUT_EN,
    /**********************
     * crc =
     *    ~(T_OPMODE_RFAGC_EN^T_OPMODE_HUMDET_EN^....^T_CONFIG_TS_CLK_RATE_AUTO)
     ************************/
    T_PARAM_CHECK_SUM,

    MSB124X_DVBT_PARAM_LEN,
} MSB124X_DVBT_Param;

typedef enum
{
    // fw version, check sum
    E_T2_CHECK_SUM_L      = 0x00,
    E_T2_CHECK_SUM_H,
    E_T2_FW_VER_0,
    E_T2_FW_VER_1,
    E_T2_FW_VER_2,

    // operation mode
    E_T2_ZIF_EN           = 0x20,
    E_T2_RF_AGC_EN,
    E_T2_HUM_DET_EN,
    E_T2_DCR_EN,
    E_T2_IQB_EN,
    E_T2_IIS_EN,
    E_T2_CCI_EN,
    E_T2_LOW_PWR_DET_EN,
    E_T2_ACI_DET_EN,
    E_T2_TD_MOTION_EN,
    E_T2_FD_MOTION_EN,

    // channel tuning param
    E_T2_BW               = 0x40,
    E_T2_FC_L             = 0x41,
    E_T2_FC_H             = 0x42,
    E_T2_FS_L,
    E_T2_FS_H,
    E_T2_ZIF,
    E_T2_GI,
    E_T2_ACI_DET_TYPE,
    E_T2_AGC_REF,         //0x48
    E_T2_RSSI_REF,
    E_T2_SNR_TIME_L,
    E_T2_SNR_TIME_H,
    E_T2_BER_CMP_TIME_L,
    E_T2_BER_CMP_TIME_H,
    E_T2_SFO_CFO_NUM,
    E_T2_CCI,
    E_T2_ACI_DET_TH_L,    //0x50
    E_T2_ACI_DET_TH_H,
    E_T2_TS_SERIAL     = 0x52,
    E_T2_TS_CLK_RATE   = 0x53,
    E_T2_TS_OUT_INV    = 0x54,
    E_T2_TS_DATA_SWAP  = 0x55,
    E_T2_TDP_CCI_KP,
    E_T2_CCI_FSWEEP,      //0x57
    E_T2_TS_ERR_POL,      //0x58
    E_T2_IF_AGC_INV_PWM_EN,
    E_T2_CCI_TYPE,             //0x5A
    E_T2_LITE,                       //0x5B

    // dvbt2 lock history
    E_T2_DVBT2_LOCK_HIS   = 0xF0,
    E_T2_FEF_DET_IND,
    E_T2_MPLP_NO_COMMON_IND,

    // splp, mplp releted
    E_T2_PLP_ID_ARR       = 0x100,
    E_T2_L1_FLAG          = 0x120,
    E_T2_PLP_ID,
    E_T2_GROUP_ID,
    E_T2_PARAM_NUM,
} E_DVBT2_PARAM;
#endif

typedef enum
{
    TS_SERIAL_CLK_57p6M = 0,
    TS_SERIAL_CLK_72M = 2,

    TS_CLK_SEL_MAX_NUM,
} E_TS_CLK_SEL;

typedef struct
{
    float    power_db;
    MS_U8  agc_val;
} S_IFAGC_SSI;

typedef struct
{
    float    power_db;
    MS_U8  sar3_val;
} S_RFAGC_SSI;

typedef struct
{
    MS_U8     constel;
    MS_U8     code_rate;
    float  p_ref;
} S_SSI_PREF;

typedef struct
{
    MS_U8       constel;
    MS_U8       code_rate;
    float    cn_ref;
} S_SQI_CN_NORDIGP1;

typedef enum
{
    _QPSK_1     = 0x0,
    _16QAM_1    = 0x1,
    _64QAM_1    = 0x2,
} E_T_CONSTEL;

typedef enum
{
    _CR1Y2_1    = 0x0,
    _CR2Y3_1    = 0x1,
    _CR3Y4_1    = 0x2,
    _CR5Y6_1    = 0x3,
    _CR7Y8_1    = 0x4,
} E_T_CODERATE;


//Bit 0~2:        code rate (0 => 1/2, 1 => 3/5, 2 => 2/3, 3 =>3/4, 4 => 4/5, 5 => 5/6)
typedef enum
{
    _T2_CR1Y2   = 0x0,
    _T2_CR3Y5   = 0x1,
    _T2_CR2Y3   = 0x2,
    _T2_CR3Y4   = 0x3,
    _T2_CR4Y5   = 0x4,
    _T2_CR5Y6   = 0x5,
    _T2_CR_UNKNOWN     = 0xFF,
} E_T2_CODERATE;

//Bit 4~6:        constellation ( 0x000 => QPSK, 0x001 => 16QAM, 0x0010 => 64QAM, 0x0011=> 256QAM)
typedef enum
{
    _T2_QPSK    = 0x0,
    _T2_16QAM   = 0x1,
    _T2_64QAM   = 0x2,
    _T2_256QAM    = 0x3,
    _T2_QAM_UNKNOWN     = 0xFF,
} E_T2_CONSTEL;

typedef enum              // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
{
    E_DEMOD_BW_17M    = 0x0,
    E_DEMOD_BW_5M      = 0x1,
    E_DEMOD_BW_6M      = 0x2,
    E_DEMOD_BW_7M      = 0x3,
    E_DEMOD_BW_8M      = 0x4,
    E_DEMOD_BW_10M    = 0x5,
} E_DEMOD_CHANNEL_BANDWIDTH;

typedef struct
{
    E_T2_CONSTEL           constel;
    E_T2_CODERATE          code_rate;
    float                  cn_ref;
} S_DVBT2_SQI_CN_NORDIGP1;


/////////////// CONSTANT /////////////////


#endif
