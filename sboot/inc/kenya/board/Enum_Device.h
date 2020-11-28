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
#define TOSHIBA_TC90512XBG_DEMOD        8   // DVB COFDM Demodulator
#define MONTAGE_M88DC2800_DEMOD         9   // DVB-C COFDM Demodulator
#define MONTAGE_M88DD2000_DEMOD         10  // DMB-T COFDM Demodulator
#define EMBEDDED_DVBT_DEMOD             11  // Internal DVB-T Demodulator
#define EMBEDDED_DVBC_DEMOD             12  // Internal DVB-C Demodulator
#define EMBEDDED_ATSC_DEMOD             13  // Internal ATSC Demodulator

#define LG_3303_DEMODE          20    // ATSC 8VSB & XQAM Demodulator
#define SAMSUNG_S5H1409_DEMODE  21    // ATSC 8VSB & XQAM Demodulator
#define PHILIPS_TUV1236D_DEMODE 22    // ATSC 8VSB & XQAM Demodulator
#define OLD_LG_3304_DEMODE      23    // ATSC 8VSB & XQAM Demodulator
#define LG_3304_DEMODE          24    // ATSC 8VSB & XQAM Demodulator
#define SAMSUNG_S5H1410_DEMODE  26    // ATSC 8VSB & XQAM Demodulator
#define MSTAR_MSB1500_DEMODE    27    // ATSC 8VSB & XQAM Demodulator
#define MSTAR_MSB1501_DEMODE    28
#define MSTAR_MSB123x_DEMOD     29
#define DIBCOM_DIB8096_DEMOD	30
#define MSTAR_MSB122x_DEMOD     31
#define MSTAR_MSB1238_DEMOD     32    //DTMB Demodulator

//------------------------------------------------------------------------------------
//FRONTEND_TUNER_TYPE
//------------------------------------------------------------------------------------
#define PHILIPS_TDA1316_TUNER           0   // DVB RF Tuner
#define THOMSON_FE6640_TUNER            1   // DVB RF Tuner
#define PHILIPS_FQD1216_TUNER           2   // DVB RF Tuner
#define MSTAR_MSR1200_TUNER             3   // Silicon Tuner for ATSC & DVB
#define LG_TDTC_G001D_TUNER             4
#define XUGUANG_DDT8A1C_TUNER           5
#define PHILIPS_FQD1218_TUNER           6
#define SHARP_VA1Y1ED_TUNER             7
#define NXP_TD1616EF_TUNER              8
#define QINGJIA_DAI4W500G_TUNER         9
#define LG_TDCC_G031D_TUNER             10
#define ALPS_TDHG6_K02A_TUNER           11 //always with MTK_5131_DEMOD
#define PHILIPS_FQD1116_TUNER           12
#define NXP_FQD1136_TUNER               13
#define LG_TDFV_G135D_TUNER             14
#define SHARP_VA1T1ED_6060              15
#define PHILIPS_TD1318AFLHP_3X_TUNER    17
#define XUGUANG_TDQ_6FT_W116H           18  // Analog Tuner for ATV only
#define SAMSUNG_DTOS40AMH201A_TUNER     19
#define ALPS_TDQG4602A_TUNER            20
#define THOMSON_DTT75407_TUNER          21
#define SHARP_VA1G5BF2009_TUNER         22 // RF Tuner
#define CH_TMI8_C22I1VH_TUNER           23
#define ALPS_TDQG9_601A_TUNER           24
#define QINGJIA_DTZ0W302G_TUNER         25
#define NXP_TDA18250A_TUNER             26

#define PHILIPS_FQD1236_TUNER   48
#define THOMSON_DTT7630_TUNER   49    // ATSC RF Tuner
#define SAMSUNG_S205_TUNER      50    // ATSC RF Tuner
#define ALPS_TDQU4_TUNER        51    // ATSC RF Tuner
#define SHARP_VA1Y2UR2201_TUNER 52    // ATSC RF Tuner
#define LG_TDVS_H703P_TUNER     53
#define NXP_TD1636ALMK2_TUNER   54    // ATSC RF Tuner
#define NXP_TD1136_TUNER        55
#define MSTAR_MSR1200           56       //Silicon Tuner
#define ALPS_TDQU6_TUNER        57    // ATSC RF Tuner  //SEC ATSC project
#define SAMSUNG_EH201A_TUNER    58    // ATSC RF Tuner
#define SAMSUNG_DVTA50_TUNER    59
#define LG_TDTC_G501D_TUNER     60
#define LG_TDTC_G311D_TUNER     61
#define SEC_DTOS403LH121A 62
#define XUGUANG_DVT_8ADC1_W41F2 63
#define SAMSUNG_S203FH201B_TUNER 64
#define XC5200_TUNER            65
#define DMCT_6A_111_TUNER       66
#define SEC_DTOS403IR121B 67
#define LG_TDTC_G601D_TUNER     68
#define MSTAR_AVATAR2 69

#define NXP_FH2608_TUNER            70
#define NXP_FH2603_TUNER            71
#define NXP_FH2112_TUNER            72
#define NXP_TH2603_TUNER            73

#define LG_TDTC_GX01D_GX71D_TUNER   75
#define CDT_SFT338_40_TUNER         76
#define TCL_F17CT_6N_E_TUNER        77
#define TCL_DT61WI_2R_E_TUNER       78
#define NUTUNE_FT2125_TUNER         79
#define NUTUNE_FJ2207_TUNER         80
#define DIBCOM_DIB8096_TUNER        81
#define NXP_CD1616LF_TUNER          82
#define NXP_TD1611ALF_TUNER         83
#define TUNER_MXL603	            84


//------------------------------------------------------------------------------------
// FRONTEND_IF_DEMODE_TYPE
//------------------------------------------------------------------------------------
#define PHILIPS_TDA9886                 0   // DVB Domodulator for Analog AV
#define PHILIPS_TDA9881                 1
#define RENESAS_R2A10406NP              2
#define MSTAR_VIF                       3
#define MSTAR_VIF_MSB1210               4    // MSB1210 DVB-T + VIF Demodulator
#define TOSHIBA_TC90512XBG_IF           5
#define MSTAR_INTERN_VIF                6

//------------------------------------------------------------------------------------
// IR_TYPE_SEL
//------------------------------------------------------------------------------------
#define IR_TYPE_OLD             0
#define IR_TYPE_NEW                1
#define IR_TYPE_MSTAR_DTV       2
#define IR_TYPE_MSTAR_RAW       3
#define IR_TYPE_MSTAR_SZ1       4
#define IR_TYPE_RC_V16          5
#define IR_TYPE_CUS03_DTV       6
#define IR_TYPE_CUS4            7
#define IR_TYPE_DC_LWB1         8
#define IR_TYPE_DC_BN59         9
#define IR_TYPE_P_DTV           10
#define IR_TYPE_SZ_CTV1         11
#define IR_TYPE_SZ_CHO1         12
#define IR_TYPE_SZ_ALC1            13
#define IR_TYPE_SZ_TON1         14
#define IR_TYPE_SZ_KON1         15
#define IR_TYPE_SZ_KON2         16
#define IR_TYPE_SZ_MTC1         17
#define IR_TYPE_SZ_HAI1         18
#define IR_TYPE_SZ_PRI1         19
#define IR_TYPE_SZ_TEN          20
#define IR_TYPE_CUS21SH         21
#define IR_TYPE_DC_BN59_611     22
#define IR_TYPE_CUS30_BK        23
#define IR_TYPE_TPV_AOC         24
#define IR_TYPE_JEAN_RC5         25
#define IR_TYPE_HYF_51F         26
#define IR_TYPE_HIS_NEC         27
#define IR_TYPE_MSTAR_FANTASY   28


#define IR_TYPE_CUS_DCLWB1       40
#define IR_TYPE_CUS_RC260I       41
#define IR_TYPE_CUS_WDE          42
#define IR_TYPE_CUS_SZ         43
#define IR_TYPE_CUS_SK         44
#define IR_TYPE_J_DTV            45
#define IR_TYPE_CUS_RC260D      46
#define IR_TYPE_J_RC5           47
#define IR_TYPE_CUS_NS_RC01G_09 48

//------------------------------------------------------------------------------------
// PANEL_TYPE_SEL
//------------------------------------------------------------------------------------
#define PNL_DAC_720X480I        0
#define PNL_DAC_720X480P        1
#define PNL_DAC_720X576I        2
#define PNL_DAC_720X576P        3
#define PNL_DAC_720X833I        4
#define PNL_DAC_1024X768P       5
#define PNL_DAC_1920X1080       6
#define PNL_AU17_EN05_SXGA      7
#define PNL_AU20_VGA            8
#define PNL_AU20_SVGA           9
#define PNL_AU20_UXGA           10
#define PNL_CMO19_SXGA          11
#define PNL_CMO20_VGA           12
#define PNL_CMO27_WXGA          13
#define PNL_CMO29_WXGA          14
#define PNL_CMO32_WXGA          15
#define PNL_FU17_FLC43_WXGA     16
#define PNL_HAN23_HSD230WX01A   17
#define PNL_LG17_SXGA           18
#define PNL_LG19_SXGA           19
#define PNL_LG17_LC171_WXGA     20
#define PNL_LG20_UXGA           21
#define PNL_LG23_LC230_WXGA     22
#define PNL_LG26_WXGA           23
#define PNL_LG30_LC300_WXGA     24
#define PNL_QDI17_EL07_SXGA     25
#define PNL_SEC_LTM170W1_L01    26
#define PNL_SH19_LQ197_VGA      27
#define PNL_SH20_B7B_UXGA       28
#define PNL_SAMSUNG24_WUXGA     29
#define PNL_CMO37_WUXGA         30
#define PNL_AU26_T260XW01_WXGA  31
#define PNL_AU20_M201EW01_WSXGA 32
#define PNL_LG32_WXGA           33
#define PNL_SAMSUNG21_WSXGA     34
#define PNL_LG20_VGA            35
#define PNL_HSD260WX11_A        36
#define PNL_AU10_2_DT           37
#define PNL_CPT20_VGA           38
#define PNL_PVI10_VGA           39
#define PNL_CMO20_WXGA          40
#define PNL_CPT15_XGA           41
#define PNL_PANASONIC22_WVGA    42
#define PNL_TMD133_WXGA         43
#define PNL_HANNS96_SVGA        44
#define PNL_HANNS12_VGA         45
#define PNL_LG15_XGA            46
#define PNL_SHARP08_D           47
#define PNL_TMD12_SVGA          48
#define PNL_AU17_WXGA           49
#define PNL_AU17_EG01_SXGA      50
#define PNL_CMO19_M190A1_WXGA   51
#define PNL_CPT15_XG09_XGA      52
#define PNL_AU26_T260XW02_WXGA  53
#define PNL_AU19PW01_WXGA       54
#define PNL_SAMSUNG19M2_WXGAL01 55
#define PNL_AU07_AT             56
#define PNL_AU20_T200XW02_WXGA  57
#define PNL_CMO26_V260B1_WXGA   58
#define PNL_AU85_AT             59
#define PNL_CMO22_WSXGA         60
#define PNL_AU23_T230XW01_WXGA  61
#define PNL_CMO42_WUXGA         62
#define PNL_LPL22_LM220WE1_WSXGA 63
#define PNL_LPL19_LM190WX1_WXGA 64
#define PNL_SAMSUNG23_LTA230W2L1_WXGA 65
#define PNL_LPL42_WXGA          66
#define PNL_LG_PDP32F1_WVGA        67
#define PNL_AU37_T370HW01_HD    68
#define PNL_BOE190WG01_WXGA     69
#define PNL_CPT320WF01_WXGA     70
#define PNL_AU154_WXGA           71
#define PNL_SH32_LQ315T3LZ50Z_WXGA 72
#define PNL_SVSVA150XG04TB_XGA  73

#define PNL_CMO16_WXGA          74
#define PNL_CPT22_A01_V2        75
#define PNL_AU37_T370XW01_WXGA  76 // 120HZ
#define PNL_LG42_WXGA           77 // 120HZ
#define PNL_CMO260J2_WUXGA      78
#define PNL_CMO216H1_L01_HD     79
#define PNL_AU32_T315HW02_HD    80

//
#define PNL_DAC_CRT             99

//------------------------------------------------------------------------------------
//KEYPAD_TYPE_SEL
//------------------------------------------------------------------------------------
#define KEYPAD_TYPE_NONE        0   // no keypad
#define KEYPAD_TYPE_ORIG        1   // MStar normal keypad
#define KEYPAD_TYPE_DEMO        2   // MStar demoset keypad
#define KEYPAD_TYPE_CUSTMOER    3   // Customer
#define KEYPAD_TYPE_BOARDDEP    4   // none regular slow ADC keypad

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
#define FLASH_IC_INVALID        0x0000
#define FLASH_IC_SST25VF080B    0x0100      // 1M    SST
#define FLASH_IC_SST25VF016B    0x0101      // 2M
#define FLASH_IC_Pm25LV080      0x0200      // 1M    PMC
#define FLASH_IC_Pm25LV016      0x0201      // 2M
#define FLASH_IC_ST25P80_A      0x0300      // 1M    ST
#define FLASH_IC_ST25P16_A      0x0301      // 2M
#define FLASH_IC_STM25P32       0x0302      // 4M
#define FLASH_IC_AT26DF081A     0x0400      // 1M    ATMEL
#define FLASH_IC_AT26DF161      0x0401      // 2M
#define FLASH_IC_AT26DF321      0x0402      // 4M
#define FLASH_IC_MX25L8005      0x0500      // 1M    MXIC
#define FLASH_IC_MX25L1605A     0x0501      // 2M
#define FLASH_IC_MX25L3205D     0x0502      // 4M
#define FLASH_IC_MX25L6405D     0x0503      // 8M
#define FLASH_IC_NX25P80        0x0600      // 1M    NX
#define FLASH_IC_NX25P16        0x0601      // 2M
#define FLASH_IC_W25X80         0x0700      // 1M    WINB
#define FLASH_IC_W25X16         0x0701      // 2M
#define FLASH_IC_W25X32         0x0702      // 4M
#define FLASH_IC_S25FL008A      0x0800      // 1M    SPANSION
#define FLASH_IC_S25FL016A      0x0801      // 2M
#define FLASH_IC_EN25B20T       0x0900      // 2M    EON
#define FLASH_IC_EN25B20B       0x0901      // 2M
#define FLASH_IC_EN25B10T       0x0902      // 1M
#define FLASH_IC_EN25B10B       0x0903      // 1M
#define FLASH_IC_EN25B32B       0x0904      // 4M    (Bottom Boot)
#define FLASH_IC_EN25B64B       0x0905      // 4M
#define FLASH_IC_ESMT_F25L016A  0x0A00      // 2M

#endif
