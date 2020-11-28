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
#ifndef _ENUM_DEVICE_H_
#define _ENUM_DEVICE_H_

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define FREQ_12MHZ              (12000000UL)
#define FREQ_14P318MHZ          (14318180UL)
#define FREQ_24MHZ              (24000000UL)
#define FREQ_67P5MHZ            (67500000UL)
#define FREQ_83MHZ              (83000000UL)
#define FREQ_90MHZ              (90000000UL)
#define FREQ_108MHZ             (108000000UL)
#define FREQ_120MHZ             (120000000UL)
#define FREQ_123MHZ             (123428000UL)
#define FREQ_125MHZ             (125000000UL)
#define FREQ_130MHZ             (130000000UL)
#define FREQ_135MHZ             (135000000UL)
#define FREQ_141MHZ             (141000000UL)
#define FREQ_144MHZ             (144000000UL)
#define FREQ_160MHZ             (160000000UL)
#define FREQ_166MHZ             (166000000UL)
#define FREQ_170MHZ             (170000000UL)
#define FREQ_172P8MHZ           (172800000UL)
#define FREQ_180MHZ             (180000000UL)
#define FREQ_195MHZ             (195000000UL)
#define FREQ_200MHZ             (200000000UL)
#define FREQ_210MHZ             (210000000UL)
#define FREQ_220MHZ             (220000000UL)
#define FREQ_230MHZ             (230000000UL)
#define FREQ_250MHZ             (250000000UL)
#define FREQ_312MHZ             (312000000UL)
#define FREQ_336MHZ             (336000000UL)

//------------------------------------------------------------------------------------
//  FRONTEND_DEMOD_TYPE
//------------------------------------------------------------------------------------
#define ZARLINK_ZL10353_DEMODE          0   // DVB COFDM Demodulator
#define MSTAR_MSB1200_DEMOD             1   // DVB COFDM Demodulator
#define LEGEND_8G13_DEMOD               2   // DMB-T COFDM Demodulator
#define MTK_5131_DEMOD                  3   // MTK solution for Samsung DVBT project
#define ZARLINK_CE6355_DEMOD            4   // DVB COFDM Demodulator
#define LEGEND_8G42_DEMOD               5   // LEGEND DMB-T Demodulator
#define LEGEND_8G52_DEMOD               6   // LEGEND DMB-T Demodulator
#define MSTAR_MSB1210_DEMOD             7   // DVB COFDM Demodulator
#define TOSHIBA_TC90512XBG_DEMOD        8   // TOSHIBA ISDB-T Demodulator
#define MONTAGE_M88DC2800_DEMOD         9   // DVB-C COFDM Demodulator
#define MONTAGE_M88DD2000_DEMOD         10  // DMB-T COFDM Demodulator
#define EMBEDDED_DVBT_DEMOD             11  // Internal DVB-T Demodulator
#define EMBEDDED_DVBC_DEMOD             12  // Internal DVB-C Demodulator
#define EMBEDDED_ATSC_DEMOD             13  // Internal ATSC Demodulator
#define LEGEND_8G80_DEMOD               14  // LEGEND DMB-T Demodulator
#define LEGEND_8G75_DEMOD               15  // LEGEND DVB-C+DTMB Demodulator
#define ALTOBEAM_883X                   16  // ALTOBEAM DTMB Demodulator
#define TOSHIBA_TC90517FG_DEMOD         17  // TOSHIBA ISDB-T Demodulator


#define LG_3303_DEMODE                  20    // ATSC 8VSB & XQAM Demodulator
#define SAMSUNG_S5H1409_DEMODE          21    // ATSC 8VSB & XQAM Demodulator
#define PHILIPS_TUV1236D_DEMODE         22    // ATSC 8VSB & XQAM Demodulator
#define OLD_LG_3304_DEMODE              23    // ATSC 8VSB & XQAM Demodulator
#define LG_3304_DEMODE                  24    // ATSC 8VSB & XQAM Demodulator
#define SAMSUNG_S5H1410_DEMODE          26    // ATSC 8VSB & XQAM Demodulator
#define MSTAR_MSB1500_DEMODE            27    // ATSC 8VSB & XQAM Demodulator
#define MSTAR_MSB1501_DEMODE            28

#define MSTAR_NONE_DEMOD                99  // no Demodulator

//------------------------------------------------------------------------------------
//FRONTEND_TUNER_TYPE
//------------------------------------------------------------------------------------
#define MSTAR_MSR1200_TUNER             0x01    // Silicon Tuner for ATSC & DVB
#define MSTAR_MSR1200                   0x02    //Silicon Tuner
#define MSTAR_AVATAR2                   0x09

#define PHILIPS_TDA1316_TUNER           0x10    // DVB RF Tuner
#define PHILIPS_FQD1216_TUNER           0x11    // DVB RF Tuner
#define PHILIPS_FQD1218_TUNER           0x12
#define PHILIPS_FQD1116_TUNER           0x13
#define PHILIPS_TD1318AFLHP_3X_TUNER    0x14
#define PHILIPS_FQD1236_TUNER           0x15

#define THOMSON_FE6640_TUNER            0x20    // DVB RF Tuner
#define THOMSON_DTT75407_TUNER          0x21
#define THOMSON_DTT7630_TUNER           0x22    // ATSC RF Tuner

#define LG_TDTC_G001D_TUNER             0x30
#define LG_TDCC_G031D_TUNER             0x31
#define LG_TDFV_G135D_TUNER             0x32
#define LG_TDVS_H703P_TUNER             0x33
#define LG_TDTC_G501D_TUNER             0x34
#define LG_TDTC_G311D_TUNER             0x35
#define LG_TDTC_G601D_TUNER             0x36
#define LG_TDTC_GX01D_GX71D_TUNER       0x37
#define LG_TDTC_G901D_TUNER             0x38

#define XUGUANG_DDT8A1C_TUNER           0x40
#define XUGUANG_TDQ_6FT_W116H           0x41    // Analog Tuner for ATV only
#define XUGUANG_STM_6F_V236H_TUNER      0x42
#define XUGUANG_HFT_8B1_V116H_TUNER     0x43
#define XUGUANG_HFT_8B_115CW_TUNER      0x44
#define XUGUANG_HFT2_8C_116CW_TUNER     0x45
#define XUGUANG_DVT_8ADC1_W41F2         0x46

#define SHARP_VA1Y1ED_TUNER             0x50
#define SHARP_VA1T1ED_6060              0x51
#define SHARP_VA1G5BF2009_TUNER         0x52    // RF Tuner
#define SHARP_VA1E1CD2403_TUNER         0x53
#define SHARP_VA1E1BF1402_TUNER         0x54
#define SHARP_VA1Y2UR2201_TUNER         0x55    // ATSC RF Tuner

#define NXP_TD1616EF_TUNER              0x60
#define NXP_FQD1136_TUNER               0x61
#define NXP_TD1636ALMK2_TUNER           0x62// ATSC RF Tuner
#define NXP_TD1136_TUNER                0x63
#define NXP_FH2608_TUNER                0x64
#define NXP_FH2603_TUNER                0x65
#define NXP_FH2112_TUNER                0x66
#define NXP_TH2603_TUNER                0x67
#define NXP_FH2122_TUNER                0x68
#define NXP_TT2120_TUNER                0x69
#define NXP_TDA18273                0x6A ////NXP silicon tuner

#define QINGJIA_DAI4W500G_TUNER         0x70
#define QINGJIA_DTZ0W302G_TUNER         0x71
#define QINGJIA_AFT7W006_TUNER          0x72
#define QINGJIA_DTT9W303G_TUNER         0x73
#define QINGJIA_AFT7W023_TUNER         0x74


#define TCL_DTC78WI_3E_TUNER            0x80
#define TCL_DT70WI_3R_TUNER             0x81
#define TCL_F17CT_6N_E_TUNER            0x82
#define TCL_DT61WI_2R_E_TUNER           0x83
#define TCL_F20WT_3DD_E                 0x84    //TCL SAWLESS tuner
#define TCL_DT58WT_3RB_E_TUNER          0x85

#define ALPS_TDHG6_K02A_TUNER           0x90    //always with MTK_5131_DEMOD
#define ALPS_TDQG4602A_TUNER            0x91
#define ALPS_TDQG9_601A_TUNER           0x92
#define ALPS_TDQU4_TUNER                0x93    // ATSC RF Tuner
#define ALPS_TDQU6_TUNER                0x94    // ATSC RF Tuner  //SEC ATSC project

#define SAMSUNG_DTOS40AMH201A_TUNER     0xA0
#define SAMSUNG_S205_TUNER              0xA1    // ATSC RF Tuner
#define SAMSUNG_EH201A_TUNER            0xA2    // ATSC RF Tuner
#define SAMSUNG_DVTA50_TUNER            0xA3
#define SAMSUNG_S203FH201B_TUNER        0xA4
#define SEC_DTOS403LH121A               0xAA
#define SEC_DTOS403IR121B               0xAB

#define CDT_9BT322_40_TUNER             0xB0
#define CDT_SFT338_40_TUNER             0xB1

#define CH_TMI8_C22I1VH_TUNER           0xC0
#define LINGHUA_TDP_1H1_E_TUNER         0xC6    //Analog Tuner For ATV Only 2009-12-22
#define TDQ_3EPD_TUNER                  0xCA
#define CHANGHONG_DTI1_E4I1VH           0xD0    //Changhong tuner
#define XC5200_TUNER                    0xD6
#define DMCT_6A_111_TUNER               0xDA

#define SONY_SUT_RE217_TUNER         0xDB        //SONY silicon tuner

//------------------------------------------------------------------------------------
// FRONTEND_IF_DEMODE_TYPE
//------------------------------------------------------------------------------------
#define MSTAR_VIF                       0x00
#define MSTAR_VIF_MSB1210               0x01    // MSB1210 DVB-T + VIF Demodulator
#define MSTAR_INTERN_VIF                0x02

#define PHILIPS_TDA9886                 0x10   // DVB Domodulator for Analog AV
#define PHILIPS_TDA9881                 0x11

#define TOSHIBA_TC90512XBG_IF           0x20

#define RENESAS_R2A10406NP              0x30

//------------------------------------------------------------------------------------
// IR_TYPE_SEL
//------------------------------------------------------------------------------------
#define IR_TYPE_OLD                 0x00
#define IR_TYPE_NEW                 0x01
#define IR_TYPE_MSTAR_DTV           0x02
#define IR_TYPE_MSTAR_RAW           0x03
#define IR_TYPE_MSTAR_SZ1           0x04
#define IR_TYPE_MSTAR_FANTASY       0x05

#define IR_TYPE_CUS03_DTV           0x10
#define IR_TYPE_CUS4                0x11
#define IR_TYPE_CUS21SH             0x12
#define IR_TYPE_CUS30_BK            0x13
#define IR_TYPE_CUS_KITKING         0x14
#define IR_TYPE_CUS_CVT             0x15
#define IR_TYPE_CUS_DCLWB1          0x16
#define IR_TYPE_CUS_RC260I          0x17
#define IR_TYPE_CUS_WDE             0x18
#define IR_TYPE_CUS_SZ              0x19
#define IR_TYPE_CUS_SK              0x1A
#define IR_TYPE_CUS_RC260D          0x1B
#define IR_TYPE_CUS_NS_RC01G_09     0x1C

#define IR_TYPE_DC_LWB1             0x20
#define IR_TYPE_DC_BN59             0x21
#define IR_TYPE_DC_BN59_611         0x22

#define IR_TYPE_SZ_CTV1             0x31
#define IR_TYPE_SZ_CHO1             0x32
#define IR_TYPE_SZ_ALC1             0x33
#define IR_TYPE_SZ_TON1             0x34
#define IR_TYPE_SZ_KON1             0x35
#define IR_TYPE_SZ_KON2             0x36
#define IR_TYPE_SZ_MTC1             0x37
#define IR_TYPE_SZ_HAI1             0x38
#define IR_TYPE_SZ_PRI1             0x39
#define IR_TYPE_SZ_TEN              0x3A

#define IR_TYPE_HIS_NEC             0x40
#define IR_TYPE_HIS_NEW             0x41
#define IR_TYPE_HIS_NEC_309         0x42
#define IR_TYPE_HISENSE_TEST        0x43

#define IR_TYPE_J_DTV               0x50
#define IR_TYPE_J_RC5               0x51

#define IR_TYPE_P_DTV               0x60
#define IR_TYPE_RC_V16              0x66
#define IR_TYPE_TPV_AOC             0x6A
#define IR_TYPE_JEAN_RC5            0x70
#define IR_TYPE_HYF_51F             0x76
#define IR_TYPE_TCL_RCA             0x7A
#define IR_TYPE_HAIER_TOSHIBA       0x80
#define IR_TYPE_SKY_TOSHIBA         0x86
#define IR_TYPE_CHANGHONG_RP57C     0x8A

#define IR_TYPE_PANASONIC_REMOTE    0x90
#define IR_TYPE_MITSUBISHI_REMOTE   0x91
#define IR_TYPE_SAMSUNG_REMOTE      0x92
#define IR_TYPE_SONY_REMOTE         0x93
#define IR_TYPE_SAMPO_REMOTE        0x94

#define IR_TYPE_RAW_TEST            0xFE
#define IR_TYPE_SW_TEST             0xFF

//------------------------------------------------------------------------------------
// PANEL_TYPE_SEL
//------------------------------------------------------------------------------------
#define PNL_DAC_720X480I                0x00
#define PNL_DAC_720X480P                0x01
#define PNL_DAC_720X576I                0x02
#define PNL_DAC_720X576P                0x03
#define PNL_DAC_720X833I                0x04
#define PNL_DAC_1024X768P               0x05
#define PNL_DAC_1920X1080               0x06
#define PNL_DAC_CRT                     0x0F

#define PNL_AU07_AT                     0x10
#define PNL_AU10_2_DT                   0x11
#define PNL_AU17_EN05_SXGA              0x12
#define PNL_AU17_WXGA                   0x13
#define PNL_AU17_EG01_SXGA              0x14
#define PNL_AU19PW01_WXGA               0x15
#define PNL_AU20_VGA                    0x16
#define PNL_AU20_SVGA                   0x17
#define PNL_AU20_UXGA                   0x18
#define PNL_AU20_T200XW02_WXGA          0x19
#define PNL_AU20_M201EW01_WSXGA         0x1A
#define PNL_AU23_T230XW01_WXGA          0x1B
#define PNL_AU26_T260XW01_WXGA          0x1C
#define PNL_AU26_T260XW02_WXGA          0x1D
#define PNL_AU32_T315HW02_HD            0x1E
#define PNL_AU37_T370XW01_WXGA          0x1F    // 120HZ
#define PNL_AU37_T370HW01_HD            0x20
#define PNL_AU85_AT                     0x21
#define PNL_AU154_WXGA                  0x22

#define PNL_CMO19_SXGA                  0x30
#define PNL_CMO20_VGA                   0x31
#define PNL_CMO27_WXGA                  0x32
#define PNL_CMO29_WXGA                  0x33
#define PNL_CMO32_WXGA                  0x34
#define PNL_CMO37_WUXGA                 0x35
#define PNL_CMO20_WXGA                  0x36
#define PNL_CMO19_M190A1_WXGA           0x37
#define PNL_CMO26_V260B1_WXGA           0x38
#define PNL_CMO22_WSXGA                 0x39
#define PNL_CMO42_WUXGA                 0x3A
#define PNL_CMO16_WXGA                  0x3B
#define PNL_CMO260J2_WUXGA              0x3C
#define PNL_CMO216H1_L01_HD             0x3D
                                        
#define PNL_LG17_SXGA                   0x50
#define PNL_LG19_SXGA                   0x51
#define PNL_LG17_LC171_WXGA             0x52
#define PNL_LG20_UXGA                   0x35
#define PNL_LG23_LC230_WXGA             0x54
#define PNL_LG26_WXGA                   0x55
#define PNL_LG30_LC300_WXGA             0x56
#define PNL_LG32_WXGA                   0x57
#define PNL_LG20_VGA                    0x58
#define PNL_LG15_XGA                    0x59
#define PNL_LG_PDP32F1_WVGA             0x5A
#define PNL_LG42_WXGA                   0x5B    // 120HZ

#define PNL_SAMSUNG24_WUXGA             0x60
#define PNL_SAMSUNG21_WSXGA             0x61
#define PNL_SAMSUNG19M2_WXGAL01         0x62
#define PNL_SAMSUNG23_LTA230W2L1_WXGA   0x63
#define PNL_SEC_LTM170W1_L01            0x6A

#define PNL_CPT15_XGA                   0x70
#define PNL_CPT20_VGA                   0x71
#define PNL_CPT15_XG09_XGA              0x72
#define PNL_CPT320WF01_WXGA             0x73
#define PNL_CPT22_A01_V2                0x74

#define PNL_HAN23_HSD230WX01A           0x80
#define PNL_HANNS96_SVGA                0x81
#define PNL_HANNS12_VGA                 0x82

#define PNL_SH19_LQ197_VGA              0x85
#define PNL_SH32_LQ315T3LZ50Z_WXGA      0x86
#define PNL_SH20_B7B_UXGA               0x87

#define PNL_LPL22_LM220WE1_WSXGA        0x8A
#define PNL_LPL19_LM190WX1_WXGA         0x8B
#define PNL_LPL42_WXGA                  0x8C

#define PNL_TMD133_WXGA                 0x90
#define PNL_TMD12_SVGA                  0x91

#define PNL_HSD260WX11_A                0xA0
#define PNL_QDI17_EL07_SXGA             0xA2
#define PNL_BOE190WG01_WXGA             0xA4
#define PNL_FU17_FLC43_WXGA             0xA6
#define PNL_PVI10_VGA                   0xA8
#define PNL_PANASONIC22_WVGA            0xAA
#define PNL_SHARP08_D                   0xAC
#define PNL_SVSVA150XG04TB_XGA          0xAE

//------------------------------------------------------------------------------------
//KEYPAD_TYPE_SEL
//------------------------------------------------------------------------------------
#define KEYPAD_TYPE_NONE        0   // no keypad
#define KEYPAD_TYPE_ORIG        1   // MStar normal keypad
#define KEYPAD_TYPE_DEMO        2   // MStar demoset keypad
#define KEYPAD_TYPE_CUSTMOER    3   // Customer
#define KEYPAD_TYPE_BOARDDEP    4   // none regular slow ADC keypad
#define KEYPAD_TYPE_HISENSE     5
//------------------------------------------------------------------------------------
//RM_EEPROM_TYPE
//------------------------------------------------------------------------------------
#define RM_TYPE_24C01           0
#define RM_TYPE_24C02           1
#define RM_TYPE_24C04           2
#define RM_TYPE_24C08           3
#define RM_TYPE_24C16           4
#define RM_TYPE_24C32           5
#define RM_TYPE_24C64           6
#define RM_TYPE_24C512          7

//------------------------------------------------------------------------------------
//I2C_IO_EXPANDER_TYPE
//------------------------------------------------------------------------------------
#define I2C_IO_EXPANDER_NONE            0
#define I2C_IO_EXPANDER_PCA9557         1
#define I2C_IO_EXPANDER_PCF8574         2
#define I2C_IO_EXPANDER_MSG1016RC       3

//------------------------------------------------------------------------------------
// SATURN_FLASH_IC
//------------------------------------------------------------------------------------
#define FLASH_IC_INVALID            0x0000
#define FLASH_IC_SST25VF080B        0x0100      // 1M    SST
#define FLASH_IC_SST25VF016B        0x0101      // 2M
#define FLASH_IC_Pm25LV080          0x0200      // 1M    PMC
#define FLASH_IC_Pm25LV016          0x0201      // 2M
#define FLASH_IC_ST25P80_A          0x0300      // 1M    ST
#define FLASH_IC_ST25P16_A          0x0301      // 2M
#define FLASH_IC_STM25P32           0x0302      // 4M
#define FLASH_IC_AT26DF081A         0x0400      // 1M    ATMEL
#define FLASH_IC_AT26DF161          0x0401      // 2M
#define FLASH_IC_AT26DF321          0x0402      // 4M
#define FLASH_IC_MX25L8005          0x0500      // 1M    MXIC
#define FLASH_IC_MX25L1605A         0x0501      // 2M
#define FLASH_IC_MX25L3205D         0x0502      // 4M
#define FLASH_IC_MX25L6405D         0x0503      // 8M
#define FLASH_IC_NX25P80            0x0600      // 1M    NX
#define FLASH_IC_NX25P16            0x0601      // 2M
#define FLASH_IC_W25X80             0x0700      // 1M    WINB
#define FLASH_IC_W25X16             0x0701      // 2M
#define FLASH_IC_W25X32             0x0702      // 4M
#define FLASH_IC_S25FL008A          0x0800      // 1M    SPANSION
#define FLASH_IC_S25FL016A          0x0801      // 2M
#define FLASH_IC_EN25B20T           0x0900      // 2M    EON
#define FLASH_IC_EN25B20B           0x0901      // 2M
#define FLASH_IC_EN25B10T           0x0902      // 1M
#define FLASH_IC_EN25B10B           0x0903      // 1M
#define FLASH_IC_EN25B32B           0x0904      // 4M    (Bottom Boot)
#define FLASH_IC_EN25B64B           0x0905      // 4M
#define FLASH_IC_ESMT_F25L016A      0x0A00      // 2M

// Audio external I2S selection
#define AUDIO_I2S_NONE              0
#define AUDIO_I2S_STA333            1
#define AUDIO_I2S_STA559BW          2
#define AUDIO_I2S_TAS5706           3
#define AUDIO_I2S_TAS5707           4
// HDMI Switch selection
#define HDMI_SWITCH_NONE            0
#define HDMI_SWITCH_PS321           1
#define HDMI_SWITCH_SIL9185         2
#define HDMI_SWITCH_TDA19998        3
#define HDMI_SWITCH_IT6633          4
#endif
