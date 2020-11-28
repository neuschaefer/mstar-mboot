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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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


#ifndef _MSBOARD_H_
#define _MSBOARD_H_

// KENYA_TODO // refine the pad/gpio
#define BOARD_NAME                  "BD_MST188B_D01A_S"


//------Function to PIN mapping (PAD_MUX) --------------------------------------
#define PIN_SPI_CZ1                 0
#define PIN_SPI_CZ2                 0
#define PIN_SPI_CZ3                 0
#define PIN_FLASH_WP0               0
#define PIN_FLASH_WP1               0

#define Unknown_pads                0
#define PADS_PM5_IS_IRIN            0
#define PADS_SM0_OPEN               Unknown_pads
#define PADS_SM0_C48                Unknown_pads
#define PADS_SM0_EN                 PAD_SM0_CD
#define PADS_SM1_OPEN               Unknown_pads
#define PADS_SM1_C48                Unknown_pads
#define PADS_SM1_EN                 Unknown_pads
#define PADS_I2CM0_MODE             Unknown_pads
#define PADS_I2CM1_MODE             Unknown_pads
#define PADS_TS0_MODE               PAD_TS0_CLK
#define PADS_TS1_MODE               Unknown_pads //PAD_TS1_D7
#define PADS_TS2_MODE               Unknown_pads
#define PADS_NAND_MODE              PAD_S_GPIO4
#define PADS_CI_MODE                Unknown_pads
#define PADS_CCIR_OUT_MODE          Unknown_pads
#define PADS_CCIR_IN_MODE           Unknown_pads
#define PADS_PANEL_IF_MODE          Unknown_pads
#define PADS_SPDIF_OUT_MODE         PAD_SM0_SWITCH
#define PADS_SPDIF_IN_MODE          Unknown_pads
#define PADS_I2S_IN_MODE            Unknown_pads
#define PADS_I2S_OUT_MUTE_MODE      Unknown_pads
#define PADS_SDIO_MODE              Unknown_pads
#define PADS_ET_MODE                Unknown_pads
#define PADS_RF_AGC_EN              Unknown_pads
#define PADS_IF_AGC_EN              Unknown_pads
#define PADS_SECOND_UART_MODE       Unknown_pads
#define PADS_THIRD_UART_MODE        Unknown_pads
#define PADS_FOURTH_UART_MODE       Unknown_pads
#define PADS_MODEM_MODE             Unknown_pads
#define PADS_PWM_MODE               Unknown_pads
#define PADS_PF_CS1_EN              Unknown_pads
#define PADS_HSYNC_EN               Unknown_pads
#define PADS_VSYNC_EN               Unknown_pads
//------GPIO setting(default GPIO pin level)------------------------------------
#define PIN_72_IS_GPIO              GPIO_OUT_HIGH   // SPI WP0
#define PIN_77_IS_GPIO              GPIO_OUT_HIGH   // Frontend RST
#define PIN_128_IS_GPIO             GPIO_OUT_HIGH   // SPDIF from optical
#define PIN_62_IS_GPIO              GPIO_IN         // PWM0 for Power consumption
#define PIN_63_IS_GPIO              GPIO_IN         // PWM1 for Power consumption
#define PIN_64_IS_GPIO              GPIO_IN         // PWM2 for Power consumption

//------Chip Type---------------------------------------------------------------
#include "chip/MSD7C51H.h"

//------I2C devices-------------------------------------------------------------
#if USE_SW_I2C
#undef USE_SW_I2C
#define USE_SW_I2C 1
#define USE_SW_I2C_HIGHSPEED        0
#endif

#define I2C_DEV_DATABASE            ((E_I2C_BUS_SYS << 8) | 0xA4)
#define I2C_DEV_HDCPKEY             ((E_I2C_BUS_SYS << 8) | 0xA8)
#define I2C_DEV_EDID_A0             ((E_I2C_BUS_DDCA0 << 8) | 0xA0)
#define I2C_DEV_EDID_D0             ((E_I2C_BUS_DDCD0 << 8) | 0xA0)
#define I2C_DEV_EDID_D1             ((E_I2C_BUS_DDCD1 << 8) | 0xA0)
#define I2C_DEV_EDID_D2             ((E_I2C_BUS_DDCD2 << 8) | 0xA0)

//----------------------------------------------------
#define TUNER_IIC_BUS               E_I2C_BUS_DDCD0
#define DEMOD_IIC_BUS               E_I2C_BUS_DDCD0

#define RM_DEVICE_ADR               I2C_DEV_DATABASE
#define RM_HDCP_ADR                 I2C_DEV_HDCPKEY

//------Peripheral Device Setting-----------------------------------------------
#define PANEL_TYPE_SEL                  g_PNL_TypeSel//PNL_AU37_T370HW01_HD //PNL_AU20_T200XW02_WXGA//PNL_LG32_WXGA //PNL_AU19PW01_WXGA//PNL_AU20_T200XW02_WXGA //PNL_LG19_SXGA  //PNL_CMO22_WSXGA  //PNL_AU20_T200XW02_WXGA  // PNL_CMO22_WSXGA  // PNL_AU20_T200XW02_WXGA // PNL_AU17_EN05_SXGA
#define SATURN_FLASH_TYPE               FLASH_TYPE_SERIAL
#define SATURN_FLASH_IC                 FLASH_IC_MX25L3205D

#define RM_EEPROM_TYPE                  RM_TYPE_24C512          // RM_TYPE_24C32
#define INPUT_AV_VIDEO_COUNT            0
#define INPUT_SV_VIDEO_COUNT            0
#define INPUT_YPBPR_VIDEO_COUNT         0
#define INPUT_SCART_VIDEO_COUNT         0
#define INPUT_HDMI_VIDEO_COUNT          0
#define ENABLE_SCART_VIDEO              0

//------Input Source Mux--------------------------------------------------------
#define INPUT_VGA_MUX               INPUT_PORT_ANALOG0
#define INPUT_VGA_SYNC_MUX          INPUT_PORT_ANALOG0_SYNC //SYNC port of VGA. There is a case which data and sync use different port.
#define INPUT_YPBPR_MUX             INPUT_PORT_ANALOG2
#define INPUT_TV_YMUX               INPUT_PORT_YMUX_CVBS4
#define INPUT_AV_YMUX               INPUT_PORT_YMUX_CVBS0
#define INPUT_AV2_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_AV3_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_SV_YMUX               INPUT_PORT_YMUX_CVBS1
#define INPUT_SV_CMUX               INPUT_PORT_CMUX_CVBS2
#define INPUT_SV2_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_SV2_CMUX              INPUT_PORT_NONE_PORT
#define INPUT_SCART_YMUX            INPUT_PORT_YMUX_CVBS5
#define INPUT_SCART_RGBMUX          INPUT_PORT_ANALOG1
#define INPUT_SCART_FB_MUX          SCART_FB1
#define INPUT_SCART2_YMUX           INPUT_PORT_NONE_PORT
#define INPUT_SCART2_RGBMUX         INPUT_PORT_NONE_PORT
#define INPUT_SCART2_FB_MUX         SCART_FB_NONE



//============================================
// Use ATSC code base audio path setting
//============================================
#define AUDIO_SOURCE_DTV            AUDIO_DSP1_DVB_INPUT
#define AUDIO_SOURCE_DTV2           AUDIO_DSP3_DVB_INPUT
#define AUDIO_SOURCE_ATV            AUDIO_DSP4_SIF_INPUT
#define AUDIO_SOURCE_PC             AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_YPBPR          AUDIO_AUIN1_INPUT
#define AUDIO_SOURCE_YPBPR2         AUDIO_AUIN1_INPUT
#define AUDIO_SOURCE_AV             AUDIO_AUIN3_INPUT//AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_AV2            AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_AV3            AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_SV             AUDIO_AUIN3_INPUT//AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_SV2            AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_SCART          AUDIO_AUIN2_INPUT
#define AUDIO_SOURCE_SCART2         AUDIO_AUIN2_INPUT//AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_HDMI           AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI2          AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI3          AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_DVI            AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_DVI2           AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_DVI3           AUDIO_AUIN0_INPUT

#define AUDIO_PATH_MAIN_SPEAKER     AUDIO_T3_PATH_I2S
#define AUDIO_PATH_HP               AUDIO_T3_PATH_AUOUT1
#define AUDIO_PATH_LINEOUT          AUDIO_T3_PATH_AUOUT2
#define AUDIO_PATH_SIFOUT           AUDIO_T3_PATH_AUOUT3
#define AUDIO_PATH_SCART1           AUDIO_PATH_SIFOUT
#define AUDIO_PATH_SCART2           AUDIO_PATH_LINEOUT
#define AUDIO_PATH_SPDIF            AUDIO_T3_PATH_SPDIF

#define AUDIO_OUTPUT_MAIN_SPEAKER  AUDIO_I2S_OUTPUT
#define AUDIO_OUTPUT_HP            AUDIO_AUOUT1_OUTPUT
#define AUDIO_OUTPUT_LINEOUT       AUDIO_AUOUT2_OUTPUT
#define AUDIO_OUTPUT_SIFOUT        AUDIO_AUOUT3_OUTPUT
#define AUDIO_OUTPUT_SCART1        AUDIO_OUTPUT_SIFOUT
#define AUDIO_OUTPUT_SCART2        AUDIO_OUTPUT_LINEOUT

//-----------------------Add GPIO switch setting -------------------------
#define Switch_PC()        _FUNC_NOT_USED()
#define Switch_YPBPR()     _FUNC_NOT_USED()
#define Switch_YPBPR2()    _FUNC_NOT_USED()
#define Switch_AV()        _FUNC_NOT_USED()
#define Switch_AV2()       _FUNC_NOT_USED()
#define Switch_AV3()       _FUNC_NOT_USED()
#define Switch_SV()        _FUNC_NOT_USED()
#define Switch_SV2()       _FUNC_NOT_USED()
#define Switch_SCART()     _FUNC_NOT_USED()
#define Switch_SCART2()    _FUNC_NOT_USED()
#define Switch_DVI()       MApi_XC_DVI_SwitchSrc(INPUT_PORT_DVI0)
#define Switch_DVI2()      MApi_XC_DVI_SwitchSrc(INPUT_PORT_DVI1)
#define Switch_DVI3()      MApi_XC_DVI_SwitchSrc(INPUT_PORT_DVI2)
#define Switch_DVI4()      _FUNC_NOT_USED()
#define Switch_DEFAULT()   _FUNC_NOT_USED()

//===============================================================
//------Tuner Setting-----------------------------------------------------------
#ifdef ATSC_SYSTEM
#define TS_CLK_INV                      0
#define TS_PARALLEL_OUTPUT              1
#define FRONTEND_DEMOD_TYPE             EMBEDDED_ATSC_DEMOD  //EMBEDDED_ATSC_DEMOD//TOSHIBA_TC90512XBG_DEMOD
#define FRONTEND_TUNER_TYPE             SAMSUNG_DVTA50_TUNER//SAMSUNG_S203FH201B_TUNER //SAMSUNG_S205_TUNER////SHARP_VA1G5BF2009_TUNERPHILIPS_TDA1316_TUNER //PHILIPS_FQD1216_TUNER

#define FRONTEND_IF_MIXER_TYPE          XUGUANG_T126CWADC //PHILIPS_FQD1216_TUNER
#define FRONTEND_IF_DEMODE_TYPE         MSTAR_INTERN_VIF  //PHILIPS_TDA9886 //MSTAR_VIF_MSB1210   //MSTAR_VIF //PHILIPS_TDA9886

#else
#define TS_CLK_INV                      0
#define TS_PARALLEL_OUTPUT              1
#define FRONTEND_DEMOD_TYPE             EMBEDDED_DVBC_DEMOD //EMBEDDED_DVBT_DEMOD //ZARLINK_ZL10353_DEMODE
#define FRONTEND_TUNER_TYPE             NXP_TDA18250A_TUNER //LG_TDTC_G311D_TUNER//PHILIPS_TDA1316_TUNER //PHILIPS_FQD1216_TUNER
#define FRONTEND_DEMOD_IQ_SWAP          0
#define FRONTEND_DEMOD_IQ_TYPE          1
#define FRONTEND_IF_MIXER_TYPE          XUGUANG_T126CWADC //PHILIPS_FQD1216_TUNER
#define FRONTEND_IF_DEMODE_TYPE         MSTAR_VIF_MSB1210  //PHILIPS_TDA9886 //MSTAR_VIF_MSB1210
#endif


#define MSB1210_TS_SERIAL_INVERSION          0
#define MSB1210_TS_PARALLEL_INVERSION      1
#define MSB1210_DTV_DRIVING_LEVEL             1 //0 or 1
#define MSB1210_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE  1

#define INTERN_DVBT_TS_SERIAL_INVERSION       0
#define INTERN_DVBT_TS_PARALLEL_INVERSION     1
#define INTERN_DVBT_DTV_DRIVING_LEVEL          1
#define INTERN_DVBT_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE  1

#define SECAM_L_PRIME_ON()              _FUNC_NOT_USED() //GPIO60_SET(1)//_FUNC_NOT_USED()
#define SECAM_L_PRIME_OFF()             _FUNC_NOT_USED() //GPIO60_SET(0)//_FUNC_NOT_USED()
#define EXT_RF_AGC_ON()                 _FUNC_NOT_USED() // ATV mode: external RF AGC
#define EXT_RF_AGC_OFF()                _FUNC_NOT_USED()  // DTV mode: internal RF AGC


//------IR & Key Setting--------------------------------------------------------
#define IR_TYPE_SEL                     IR_TYPE_MSTAR_DTV   // IR_TYPE_MSTAR_DTV // IR_TYPE_CUS03_DTV // IR_TYPE_NEW
#define KEYPAD_TYPE_SEL                 KEYPAD_TYPE_ORIG    // KEYPAD_TYPE_DEMO
#define POWER_KEY_SEL                   POWER_KEY_PAD_INT

//------Power Setting-----------------------------------------------------------
#define ENABLE_POWER_SAVING             0
#define POWER_DOWN_SEQ                  1
#define POWER_SAVING_T                  0
#define SCREENSAVER_ENABLE              1
#define NO_SIGNAL_AUTO_SHUTDOWN         1
#define STANDBY_MODE                    POWERMODE_S3
#define POWERUP_MODE                    PUMODE_WORK
#define ENABLE_POWER_GOOD_DETECT        1
#define ENABLE_POWER_SAVING_SIF            1
#define ENABLE_POWER_SAVING_VDMVD        0
#define ENABLE_POWER_SAVING_DPMS        0


//------Memory Setting----------------------------------------------------------
#define BOOTUP_MIU_BIST                 1
#ifndef MEMORY_MAP
#define MEMORY_MAP                      MMAP_256MB  // 1024 1024  ??TBC
#endif
#define  MIU_INTERFACE                  DDR3_INTERFACE_QFP_156

//------Analog Function Setting-------------------------------------------------
#define MOD_LVDS_GPIO                   0x820

#define ENABLE_SSC                      DISABLE
#define ENABLE_LVDSTORGB_CONVERTER      DISABLE
#if ENABLE_SSC
#define MIU_SSC_SPAN_DEFAULT            350
#define MIU_SSC_STEP_DEFAULT            200
#define MIU_SSC_SPAN_MAX                500
#define MIU_SSC_STEP_MAX                300
#define LVDS_SSC_SPAN_DEFAULT           350
#define LVDS_SSC_STEP_DEFAULT           200
#define LVDS_SSC_SPAN_MAX               500
#define LVDS_SSC_STEP_MAX               300
#endif

//------ETHNET PHY_TYPE---------------------------------------------------------
#define ETHNET_PHY_LAN8700              0x0f
#define ETHNET_PHY_IP101ALF             0x01
#define ETHNET_PHY_TYPE                 ETHNET_PHY_IP101ALF

//------DRAM Config---------------------------------------------------------------
#define DRAM_TYPE                       DDR_II
#define DRAM_BUS                        DRAM_BUS_16
#define DDRPLL_FREQ                     DDRLLL_FREQ_400
#define DDRII_ODT

#define MIU_0_02                        0x0C45
#define MIU_0_1A                        0x5151
#define MIU_0_36                        0x0244
#define MIU_0_38                        0x0070

//------MCU use Scaler internal MPLL clock-------------------
#define MCU_CLOCK_SEL                   MCUCLK_144MHZ

#define MST_XTAL_CLOCK_HZ               FREQ_12MHZ
#define MST_XTAL_CLOCK_KHZ              (MST_XTAL_CLOCK_HZ/1000UL)
#define MST_XTAL_CLOCK_MHZ              (MST_XTAL_CLOCK_KHZ/1000UL)

//------MCU Code----------------------------------------------------------------
#define ENABLE_HKMCU_ICACHE_BYPASS      0
#define ENABLE_HKMCU_CODE_ECC           0

//------Extra-------------------------------------------------------------------
#define POWER_DOWN_INFORM_EXTERNALMCU   0

#if POWER_DOWN_INFORM_EXTERNALMCU
#define EXMCU_SLAVE_ADDR        0xA8
#define EXMCU_SUBADDRESS        0x04
#define EXMCU_SLEEP_MODE        0x00
#endif

#define IIC_BY_HW                       0 //
#define IIC_BY_SW                       1 //
#define _EEPROM_ACCESS                  IIC_BY_SW//IIC_BY_HW
#define EEPROM_CLK_SEL                  EEPROM_CLK_100KHZ

//------MST I/O control definition----------------------------------------------
#define ENABLE_DPWM_FUNCTION            0

//-------------------------------------------------
#define SCART_OUT_ON()                  _FUNC_NOT_USED()
#define SCART_OUT_OFF()                 _FUNC_NOT_USED())

// Video switch Setting
#define Switch_YPbPr1()                 _FUNC_NOT_USED()
#define Switch_YPbPr2()                 _FUNC_NOT_USED()

#define SwitchRGBToSCART()              _FUNC_NOT_USED()
#define SwitchRGBToDSUB()               _FUNC_NOT_USED()

#define MDrv_Sys_GetUsbOcdN()           _FUNC_NOT_USED
#define MDrv_Sys_GetRgbSw()

// Audio Amplifier
#define Audio_Amplifier_ON()            _FUNC_NOT_USED()
#define Audio_Amplifier_OFF()           _FUNC_NOT_USED()

#define Adj_Volume_Off()                _FUNC_NOT_USED()
#define Adj_Volume_On()                 _FUNC_NOT_USED()

#define Panel_VCC_ON()                  _FUNC_NOT_USED()
#define Panel_VCC_OFF()                 _FUNC_NOT_USED()
#define Panel_Backlight_VCC_ON()        _FUNC_NOT_USED()
#define Panel_Backlight_VCC_OFF()       _FUNC_NOT_USED()

#define Panel_Backlight_PWM_ADJ(x)      _FUNC_NOT_USED()
#define Panel_Backlight_Max_Current(x)  _FUNC_NOT_USED()

#define Panel_VG_HL_CTL_ON()            _FUNC_NOT_USED()
#define Panel_VG_HL_CTL_OFF()           _FUNC_NOT_USED()
#define PANEL_CONNECTOR_SWAP_LVDS_CH    0
#define PANEL_CONNECTOR_SWAP_LVDS_POL   0
#define PANEL_CONNECTOR_SWAP_PORT       1

#define PANEL_SWAP_LVDS_POL    1

// Power Saving
#define Power_On()                      _FUNC_NOT_USED()
#define Power_Off()                     _FUNC_NOT_USED()
#define MDrv_Sys_GetSvideoSw()          _FUNC_NOT_USED()

#define Peripheral_Device_Reset_ON()    _FUNC_NOT_USED()
#define Peripheral_Device_Reset_OFF()   _FUNC_NOT_USED()
#define Tuner_ON()                      _FUNC_NOT_USED()
#define Tuner_OFF()                     _FUNC_NOT_USED()
#define Demodulator_ON()                _FUNC_NOT_USED()
#define Demodulator_OFF()               _FUNC_NOT_USED()
#define LAN_ON()                        _FUNC_NOT_USED()
#define LAN_OFF()                       _FUNC_NOT_USED()

#define TunerOffPCMCIA()                _FUNC_NOT_USED()
#define TunerOnPCMCIA()                 _FUNC_NOT_USED()

// LED Control
#define LED_RED_ON()                    _FUNC_NOT_USED()
#define LED_RED_OFF()                   _FUNC_NOT_USED()
#define LED_GREEN_ON()                  _FUNC_NOT_USED()
#define LED_GREEN_OFF()                 _FUNC_NOT_USED()

#define ST_DET_Read()                   0
#define ANT_5V_MNT_Read()               0
#define TU_ERROR_N_Read()               0
#define HDMI_5V_Read()                  0
#define COMP_SW_Read()                  1
#define PANEL_CTL_Off()                 Panel_VCC_OFF()
#define PANEL_CTL_On()                  Panel_VCC_ON()
#define INV_CTL_Off()                   Panel_Backlight_VCC_OFF()
#define INV_CTL_On()                    Panel_Backlight_VCC_ON()
#define POWER_ON_OFF1_On()              Power_On()
#define POWER_ON_OFF1_Off()             Power_Off()
#define MUTE_On()                       Adj_Volume_Off()//(XBYTE[0x1e63] |= BIT7)
#define MUTE_Off()                      Adj_Volume_On()//(XBYTE[0x1e63] &= ~BIT7)
#define EEPROM_WP_On()                  _FUNC_NOT_USED()
#define EEPROM_WP_Off()                 _FUNC_NOT_USED()
#define LED_GRN_Off()                   LED_GREEN_OFF()
#define LED_GRN_On()                    LED_GREEN_ON()
#define LED_RED_Off()                   LED_GRN_On()
#define LED_RED_On()                    LED_GRN_Off()
#define ANT_5V_CTL_Off()                _FUNC_NOT_USED()
#define ANT_5V_CTL_On()                 _FUNC_NOT_USED()
#define BOOSTER_Off()                   _FUNC_NOT_USED()
#define BOOSTER_On()                    _FUNC_NOT_USED()
#define RGB_SW_On()                     _FUNC_NOT_USED()
#define RGB_SW_Off()                    _FUNC_NOT_USED()
#define SC_RE1_On()                     _FUNC_NOT_USED()
#define SC_RE1_Off()                    _FUNC_NOT_USED()
#define SC_RE2_On()                     _FUNC_NOT_USED()
#define SC_RE2_Off()                    _FUNC_NOT_USED()
#define TU_RESET_N_On()                 _FUNC_NOT_USED()//mdrv_gpio_set_high( BALL_P4 )
#define TU_RESET_N_Off()                _FUNC_NOT_USED()//mdrv_gpio_set_low( BALL_P4 )
#define DeactivateScartRecord1()        //SetGPIOHigh(SC_RE1)
#define ActivateScartRecord1()            //SetGPIOLow(SC_RE1)
#define DeactivateScartRecord2()        //SetGPIOHigh(SC_RE2)
#define ActivateScartRecord2()            //SetGPIOLow(SC_RE2)
//------MST Keypad definition---------------------------------------------------
#define KEYPAD_CHANNEL_SUPPORT          4 //Maximun supported keypad channels
#define ADC_KEY_CHANNEL_NUM             2 //Real supported keypad channels
#define ADC_KEY_LAST_CHANNEL            ADC_KEY_CHANNEL_NUM - 1
//config which keypad channel enabled
#define ENABLE_KPDCHAN_1                ENABLE
#define ENABLE_KPDCHAN_2                DISABLE
#define ENABLE_KPDCHAN_3                DISABLE
#define ENABLE_KPDCHAN_4                ENABLE

#define KEYPAD_KEY_VALIDATION           3
#define KEYPAD_REPEAT_KEY_CHECK         KEYPAD_KEY_VALIDATION + 2
#define KEYPAD_REPEAT_KEY_CHECK_1       KEYPAD_KEY_VALIDATION + 3
#define KEYPAD_STABLE_NUM               10
#define KEYPAD_STABLE_NUM_MIN           9
#define KEYPAD_REPEAT_PERIOD            2 // 6
#define KEYPAD_REPEAT_PERIOD_1          KEYPAD_REPEAT_PERIOD/2

#define KEYPAD_CH1_UB                   0xFF
#define KEYPAD_CH1_LB                   0x84
#define KEYPAD_CH2_UB                   0xFF
#define KEYPAD_CH2_LB                   0x84
#define KEYPAD_CH3_UB                   0xFF
#define KEYPAD_CH3_LB                   0x84
#define KEYPAD_CH4_UB                   0xFF
#define KEYPAD_CH4_LB                   0x84

#define ADC_KEY_LEVEL                   4
#define ADC_KEY_L0                      0x27
#define ADC_KEY_L1                      0x47
#define ADC_KEY_L2                      0x63
#define ADC_KEY_L3                      0x7B

#if (KEYPAD_TYPE_SEL == KEYPAD_TYPE_CUSTMOER)   // CUSTMOER keypad
#define ADC_KEY_1_L0_FLAG               IRKEY_UP
#define ADC_KEY_1_L1_FLAG               IRKEY_MENU
#define ADC_KEY_1_L2_FLAG               IRKEY_LEFT
#define ADC_KEY_1_L3_FLAG               IRKEY_MUTE

#define ADC_KEY_2_L0_FLAG               IRKEY_POWER
#define ADC_KEY_2_L1_FLAG               IRKEY_INPUT_SOURCE
#define ADC_KEY_2_L2_FLAG               IRKEY_RIGHT
#define ADC_KEY_2_L3_FLAG               IRKEY_DOWN
#elif (KEYPAD_TYPE_SEL == KEYPAD_TYPE_ORIG)   // MStar normal keypad
#define ADC_KEY_1_L0_FLAG               IRKEY_UP
#define ADC_KEY_1_L1_FLAG               IRKEY_MENU
#define ADC_KEY_1_L2_FLAG               IRKEY_LEFT
#define ADC_KEY_1_L3_FLAG               IRKEY_MUTE

#define ADC_KEY_2_L0_FLAG               IRKEY_POWER
#define ADC_KEY_2_L1_FLAG               IRKEY_INPUT_SOURCE
#define ADC_KEY_2_L2_FLAG               IRKEY_RIGHT
#define ADC_KEY_2_L3_FLAG               IRKEY_DOWN
#elif (KEYPAD_TYPE_SEL == KEYPAD_TYPE_DEMO) // MStar demo set keypad
#define ADC_KEY_1_L0_FLAG               IRKEY_MUTE
#define ADC_KEY_1_L1_FLAG               IRKEY_VOLUME_MINUS
#define ADC_KEY_1_L2_FLAG               IRKEY_VOLUME_PLUS
#define ADC_KEY_1_L3_FLAG               IRKEY_DOWN

#define ADC_KEY_2_L0_FLAG               IRKEY_POWER
#define ADC_KEY_2_L1_FLAG               IRKEY_UP
#define ADC_KEY_2_L2_FLAG               IRKEY_MENU
#define ADC_KEY_2_L3_FLAG               IRKEY_INPUT_SOURCE
#endif

//------------------------------------------------------------------------------
// SAR boundary define
//------------------------------------------------------------------------------
#define LK_KEYPAD_CH1_UB                0x3F
#define LK_KEYPAD_CH1_LB                0x1A
#define LK_KEYPAD_CH2_UB                0x3F
#define LK_KEYPAD_CH2_LB                0x1A
#define LK_KEYPAD_CH3_UB                0x3F
#define LK_KEYPAD_CH3_LB                0x00
#define LK_KEYPAD_CH4_UB                0x3F
#define LK_KEYPAD_CH4_LB                0x00

#define LK_CH_MINUS_UB                  0x11
#define LK_CH_MINUS_LB                  0x0D
#define LK_CH_PLUS_UB                   0x11
#define LK_CH_PLUS_LB                   0x0D
#define LK_INPUT_UB                     0x09
#define LK_INPUT_LB                     0x05
#define LK_MENU_UB                      0x09
#define LK_MENU_LB                      0x05
#define LK_OK_UB                        0x18
#define LK_OK_LB                        0x14
#define LK_POWER_UB                     0x03
#define LK_POWER_LB                     0x00
#define LK_VOL_MINUS_UB                 0x18
#define LK_VOL_MINUS_LB                 0x14
#define LK_VOL_PLUS_UB                   0x03
#define LK_VOL_PLUS_LB                   0x00

//-----PIN_OUT_SELECT------------------------------------------------------------------------

//#define PWM0_PERIOD                     0xff
//#define PWM1_PERIOD                     0xff
#define PWM2_PERIOD                     0xFF    //PWM2 Period=( PWM2_PERIOD+1 ) *( 1/ Xtal)
//#define PWM3_PERIOD                     0xFf

//#define INIT_PWM0_DUTY                  0x7e
//#define INIT_PWM1_DUTY                  0x7e
#define INIT_PWM2_DUTY                  0x7e    //PWM2_duty= (Init_Pwm2_DUTY +1 ) * (1/XTAL)
//#define INIT_PWM3_DUTY                  0x7e

#define BACKLITE_INIT_SETTING           ENABLE

#define PWM2_MUX_SEL                    0x00

//------8051 Serial Port Setting------------------------------------------------
#if OBA2
//----------------------------------------------------------------------------
// UART_SRC_SEL
//----------------------------------------------------------------------------
#define UART0_SRC_SEL                   (UART_SEL_PIU_UART0)
#define UART1_SRC_SEL                   (UART_SEL_MHEG5)
#endif

#if(ENABLE_UART1_DEBUG)
#define ENABLE_UART0                    DISABLE
#define ENABLE_UART0_INTERRUPT          DISABLE
#define ENABLE_UART1                    ENABLE
#define ENABLE_UART1_INTERRUPT          ENABLE
//------STDIO device setting----------------------------------------------------
#define STDIN_DEVICE                    IO_DEV_UART1
#define STDOUT_DEVICE                   IO_DEV_UART1
#else
#define ENABLE_UART0                    ENABLE
#define ENABLE_UART0_INTERRUPT          ENABLE
#define ENABLE_UART1                    DISABLE
#define ENABLE_UART1_INTERRUPT          DISABLE
//------STDIO device setting----------------------------------------------------
#define STDIN_DEVICE                    IO_DEV_UART0
#define STDOUT_DEVICE                   IO_DEV_UART0
#endif

#define ENABLE_PIU_UART0                DISABLE
#define ENABLE_PIU_UART0_INTERRUPT      DISABLE

//------ PANEL RELATED ---------------------------------------------------------
#define PANEL_PDP_10BIT                 1
#define PANEL_SWAP_PORT                 0

//------ HDMI RELATED ---------------------------------------------------------
#define HDCP_HPD_INVERSE                DISABLE

// ----- HDMITX HPD pin --------------------------------------------------------
#define HDMITX_HPD_PM_GPIO          PAD_HDMI_HPD // GPIO 0 ~ 12

#endif // _MSBOARD_H_
