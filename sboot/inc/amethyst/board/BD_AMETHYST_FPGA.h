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

#define BOARD_NAME                  "BD_AMETHYST_FPGA"

#define PIN_SPI_CZ1                 BALL_C1
#define PIN_SPI_CZ2                 BALL_D3
#define PIN_SPI_CZ3                 0
#define PIN_FLASH_WP0               BALL_G4
#define PIN_FLASH_WP1               BALL_M6

//------PAD MUX setting-------------------------------------------------------
#define Unknown_pad_mux             0
//define the following values from 1
#define PARALLEL_IN                 1
#define SERIAL_IN                   2
#define PARALLEL_2nd_PORT           3
#define PARALLEL_OUT                4
#define PCM_A                       1
#define PCM_D                       2
#define SINGLE_CH_I2S_OUT           1
#define MULTI_CH_I2S_OUT            2
#define ONE_BIT_MODE                1
#define TWO_BIT_MODE                2
#define FOUR_BIT_MODE               3
#define TS1_PADs                    1
#define PCM_PADs                    2
#define GPIO_PADs                   3
#define DDCR_PADs                   1
#define IIC_PADs                    2

#define PADS_VSYNC_VIF_OUT_EN       Unknown_pad_mux
#define PADS_TS0_CONFIG             PARALLEL_IN
#define PADS_TS1_CONFIG             PARALLEL_OUT
#define PADS_TS_OUT                 Unknown_pad_mux
#define PADS_NAND_MODE              PCM_D
#define PADS_PCM1_CTRL              ENABLE
#define PADS_PCM1_AD                ENABLE
#define PADS_CI_CTRL                Unknown_pad_mux
#define PADS_CI_AD                  Unknown_pad_mux
#define PADS_PCM2_CTRL              Unknown_pad_mux
#define PADS_SPDIF_OUT              PAD_SPDIF_OUT
#define PADS_SPDIF_IN               PAD_SPDIF_IN
#define PADS_I2S_IN                 ENABLE
#define PADS_I2S_MUTE               Unknown_pad_mux
#define PADS_I2S_OUT                MULTI_CH_I2S_OUT
#define PADS_MPIF_MODE              Unknown_pad_mux
#define PADS_ET_MODE                ENABLE
#define PADS_3D_FLAG_CONFIG         Unknown_pad_mux
#define PADS_UART2_MODE             PAD_UART_TX2
#define PADS_UART3_MODE             Unknown_pad_mux
#define PADS_UART4_MODE             Unknown_pad_mux
#define PADS_FAST_UART_MODE         Unknown_pad_mux
#define PADS_PWM0_MODE              Unknown_pad_mux
#define PADS_PWM1_MODE              Unknown_pad_mux
#define PADS_PWM2_MODE              PAD_PWM2
#define PADS_PWM3_MODE              Unknown_pad_mux
#define PADS_PWM4_MODE              Unknown_pad_mux
#define PADS_NAND_CS1_EN            Unknown_pad_mux
#define PADS_TSERR_OUT              Unknown_pad_mux
#define PADS_BT656_CTRL             Unknown_pad_mux
#define PADS_DDCR_MODE              Unknown_pad_mux
#define PADS_MIIC_MODE0             Unknown_pad_mux
#define PADS_MIIC_MODE1             Unknown_pad_mux
#define PADS_MIIC_MODE2             Unknown_pad_mux
#define PADS_P1_ENABLE              Unknown_pad_mux

//------GPIO setting(default GPIO pin level) ??? ------------------------------------
#define BALL_V21_IS_GPIO            GPIO_OUT_LOW	//Panel On: Low / Off: High
#define BALL_T20_IS_GPIO            GPIO_OUT_LOW	//Backlight On: Low / Off: High
#define BALL_AB2_IS_GPIO            GPIO_OUT_LOW    //SIF_CTL
#define BALL_AC2_IS_GPIO            GPIO_OUT_HIGH	//RFAGC_CTRL (High: ATV  Low: DTV)
#define BALL_P23_IS_GPIO            GPIO_IN			//DDCR_CK : EEPROM I2C_SCL
#define BALL_P24_IS_GPIO            GPIO_IN			//DDCR_DA : EEPROM I2C_SDA
#define BALL_AE6_IS_GPIO            GPIO_IN			//TGPIO2 : Tuner I2C_SCL
#define BALL_AD6_IS_GPIO            GPIO_IN			//TGPIO3 : Tuner I2C_SDA
#define BALL_AB3_IS_GPIO            GPIO_OUT_LOW    //Pre-AMP On: Low / Off: High
#define BALL_F4_IS_GPIO             GPIO_OUT_LOW    //Audio On: Low / Off: High
#define BALL_F7_IS_GPIO             GPIO_OUT_HIGH   //Mute On: Low / Off: High

#define BALL_K5_IS_GPIO             GPIO_IN         //USB_OCD
#define BALL_D4_IS_GPIO             GPIO_OUT_HIGH   //USB_CTL
#define BALL_A8_IS_GPIO             GPIO_IN         //USB1_OCD
#define BALL_B8_IS_GPIO             GPIO_OUT_HIGH   //USB1_CTL
#define BALL_G4_IS_GPIO             GPIO_OUT_HIGH   //BOOT-FLASH_WPN (SPI_FLASH1 Write Protect)
#define BALL_M6_IS_GPIO             GPIO_OUT_HIGH   //BACKUP_WP (SPI_FLASH2 Write Protect)
#define BALL_M5_IS_GPIO             GPIO_OUT_LOW    //EDID_WP (VGA EEPROM Write Protect)
#define BALL_M4_IS_GPIO             GPIO_OUT_HIGH   //LED_ON (System power LED on/off)
#define BALL_AB5_IS_GPIO            GPIO_OUT_HIGH   //PCM_5V_CTL (PCM power control)
#define BALL_AB1_IS_GPIO            GPIO_OUT_LOW    //TUNER_RESET (Tuner Reset)
#define BALL_N6_IS_GPIO             GPIO_OUT_LOW    //ETH-RST (ETH Reset)

//------Chip Type---------------------------------------------------------------
#include "chip/MSD804KBX.h"

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
#define PANEL_TYPE_SEL              g_PNL_TypeSel   //PNL_AU37_T370HW01_HD //PNL_AU20_T200XW02_WXGA//PNL_LG32_WXGA //PNL_AU19PW01_WXGA//PNL_AU20_T200XW02_WXGA //PNL_LG19_SXGA  //PNL_CMO22_WSXGA  //PNL_AU20_T200XW02_WXGA  // PNL_CMO22_WSXGA  // PNL_AU20_T200XW02_WXGA // PNL_AU17_EN05_SXGA
#define SATURN_FLASH_TYPE           FLASH_TYPE_SERIAL
#define SATURN_FLASH_IC             FLASH_IC_MX25L6405D

#define ENABLE_DDC_RAM              DISABLE
#define RM_EEPROM_TYPE              RM_TYPE_24C512         // RM_TYPE_24C64
#define DIGITAL_I2S_SELECT          AUDIO_I2S_NONE
#define INPUT_AV_VIDEO_COUNT        1
#define INPUT_SV_VIDEO_COUNT        1  //0, if set = 0, code flow can not support
#define INPUT_YPBPR_VIDEO_COUNT     1
#ifdef ATSC_SYSTEM
#define INPUT_SCART_VIDEO_COUNT     0
#else
#define INPUT_SCART_VIDEO_COUNT     1
#endif
#define INPUT_HDMI_VIDEO_COUNT      3
#ifdef ATSC_SYSTEM
#define ENABLE_SCART_VIDEO          0
#else
#define ENABLE_SCART_VIDEO          ENABLE
#endif

//------Input Source Mux--------------------------------------------------------
#define INPUT_VGA_MUX               INPUT_PORT_ANALOG0
#define INPUT_VGA_SYNC_MUX          INPUT_PORT_ANALOG0_SYNC //SYNC port of VGA. There is a case which data and sync use different port.
#define INPUT_YPBPR_MUX             INPUT_PORT_ANALOG2
#define INPUT_YPBPR2_MUX            INPUT_PORT_NONE_PORT
#define INPUT_TV_YMUX               INPUT_PORT_YMUX_CVBS5 //INPUT_PORT_YMUX_CVBS2
#define INPUT_AV_YMUX               INPUT_PORT_YMUX_CVBS3
#define INPUT_AV2_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_AV3_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_SV_YMUX               INPUT_PORT_YMUX_CVBS4   //INPUT_PORT_NONE_PORT
#define INPUT_SV_CMUX               INPUT_PORT_CMUX_CVBS1   //INPUT_PORT_NONE_PORT
#define INPUT_SV2_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_SV2_CMUX              INPUT_PORT_NONE_PORT
#define INPUT_SCART_YMUX            INPUT_PORT_YMUX_CVBS2
#define INPUT_SCART_RGBMUX          INPUT_PORT_ANALOG1
#define INPUT_SCART_FB_MUX          SCART_FB1
#define INPUT_SCART2_YMUX           INPUT_PORT_NONE_PORT
#define INPUT_SCART2_RGBMUX         INPUT_PORT_NONE_PORT
#define INPUT_SCART2_FB_MUX         SCART_FB2

#define INPUT_HDMI1_MUX             INPUT_PORT_DVI0
#define INPUT_HDMI2_MUX             INPUT_PORT_DVI2
#define INPUT_HDMI3_MUX             INPUT_PORT_DVI3

/// for PWS path mapping
#define PWS_INPUT_HDMI1_PATH        _HDMI1_
#define PWS_INPUT_HDMI2_PATH        _HDMI3_
#define PWS_INPUT_HDMI3_PATH        _HDMI4_


#define SCART_ID_SEL                0x02   // HSYNC1
#define SCART2_ID_SEL               0x04   // HSYNC2
//============================================
// Use ATSC code base audio path setting
//============================================
#define AUDIO_SOURCE_DTV            AUDIO_DSP1_DVB_INPUT
#define AUDIO_SOURCE_DTV2           AUDIO_DSP3_DVB_INPUT
#define AUDIO_SOURCE_ATV            AUDIO_DSP4_SIF_INPUT
#define AUDIO_SOURCE_PC             AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_YPBPR          AUDIO_AUIN4_INPUT
#define AUDIO_SOURCE_YPBPR2         AUDIO_AUIN4_INPUT
#define AUDIO_SOURCE_AV             AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_AV2            AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_AV3            AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_SV             AUDIO_SOURCE_AV
#define AUDIO_SOURCE_SV2            AUDIO_SOURCE_AV
#define AUDIO_SOURCE_SCART          AUDIO_AUIN2_INPUT
#define AUDIO_SOURCE_SCART2         AUDIO_AUIN2_INPUT
#define AUDIO_SOURCE_HDMI           AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI2          AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI3          AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_DVI            AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_DVI2           AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_DVI3           AUDIO_AUIN3_INPUT
#define AUDIO_SOURCE_KTV            AUDIO_AUMIC_INPUT

#define AUDIO_PATH_MAIN_SPEAKER     AUDIO_T3_PATH_I2S
#define AUDIO_PATH_HP               AUDIO_T3_PATH_AUOUT1
#define AUDIO_PATH_LINEOUT          AUDIO_T3_PATH_AUOUT2
#define AUDIO_PATH_SIFOUT           AUDIO_T3_PATH_AUOUT3
#define AUDIO_PATH_SCART1           AUDIO_PATH_SIFOUT
#define AUDIO_PATH_SCART2           AUDIO_PATH_LINEOUT
#define AUDIO_PATH_SPDIF            AUDIO_T3_PATH_SPDIF

#define AUDIO_OUTPUT_MAIN_SPEAKER   AUDIO_I2S_OUTPUT
#define AUDIO_OUTPUT_HP             AUDIO_HP_OUTPUT
#define AUDIO_OUTPUT_LINEOUT        AUDIO_AUOUT2_OUTPUT
#define AUDIO_OUTPUT_SIFOUT         AUDIO_AUOUT3_OUTPUT
#define AUDIO_OUTPUT_SCART1         AUDIO_OUTPUT_SIFOUT
#define AUDIO_OUTPUT_SCART2         AUDIO_OUTPUT_LINEOUT

//-----------------------Add GPIO switch setting -------------------------
#define Switch_PC()                 _FUNC_NOT_USED()
#define Switch_YPBPR()              _FUNC_NOT_USED()
#define Switch_YPBPR2()             _FUNC_NOT_USED()
#define Switch_AV()                 _FUNC_NOT_USED()
#define Switch_AV2()                _FUNC_NOT_USED()
#define Switch_AV3()                _FUNC_NOT_USED()
#define Switch_SV()                 _FUNC_NOT_USED()
#define Switch_SV2()                _FUNC_NOT_USED()
#define Switch_SCART()              _FUNC_NOT_USED()
#define Switch_SCART2()             _FUNC_NOT_USED()
#define Switch_DVI()                MApi_XC_DVI_SwitchSrc(INPUT_HDMI1_MUX)
#define Switch_DVI2()               MApi_XC_DVI_SwitchSrc(INPUT_HDMI2_MUX)
#define Switch_DVI3()               MApi_XC_DVI_SwitchSrc(INPUT_HDMI3_MUX)
#define Switch_DVI4()               _FUNC_NOT_USED()
#define Switch_DEFAULT()            _FUNC_NOT_USED()

// HDMI switch Setting
#define HDMI_SWITCH_SELECT	HDMI_SWITCH_NONE
//===============================================================
//------Tuner Setting-----------------------------------------------------------
#ifdef ATSC_SYSTEM
#define TS_CLK_INV                      0
#define TS_PARALLEL_OUTPUT              1
#define FRONTEND_DEMOD_TYPE             EMBEDDED_ATSC_DEMOD  //EMBEDDED_ATSC_DEMOD//TOSHIBA_TC90512XBG_DEMOD
#define FRONTEND_TUNER_TYPE             TCL_DA91WT_13_E_TUNER //SAMSUNG_DVTA50_TUNER //SAMSUNG_S205_TUNER////SHARP_VA1G5BF2009_TUNERPHILIPS_TDA1316_TUNER //PHILIPS_FQD1216_TUNER

#define FRONTEND_IF_MIXER_TYPE          XUGUANG_T126CWADC //PHILIPS_FQD1216_TUNER
#define FRONTEND_IF_DEMODE_TYPE         MSTAR_INTERN_VIF  //MSTAR_INTERN_VIF  //PHILIPS_TDA9886 //MSTAR_VIF_MSB1210   //MSTAR_VIF //PHILIPS_TDA9886

#define VIF_TUNER_TYPE                  0                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_SAW_ARCH                    3                   // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF)

#else
#define TS_CLK_INV                      0
#define TS_PARALLEL_OUTPUT              1
#define TS_SERIAL_OUTPUT_IF_CI_REMOVED  0
#define FRONTEND_DEMOD_TYPE             EMBEDDED_DVBT_DEMOD //EMBEDDED_DVBT_DEMOD //ZARLINK_ZL10353_DEMODE
#define FRONTEND_TUNER_TYPE             LG_TDTC_G311D_TUNER//PHILIPS_TDA1316_TUNER //PHILIPS_FQD1216_TUNER

#define FRONTEND_IF_MIXER_TYPE          XUGUANG_T126CWADC //PHILIPS_FQD1216_TUNER
#define FRONTEND_IF_DEMODE_TYPE         MSTAR_INTERN_VIF  //MSTAR_INTERN_VIF  //PHILIPS_TDA9886 //MSTAR_VIF_MSB1210   //MSTAR_VIF //PHILIPS_TDA9886

#define VIF_TUNER_TYPE                  0                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_SAW_ARCH                    1                   // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF)

#endif
#define FRONTEND_SECOND_DEMOD_TYPE      MSTAR_NONE_DEMOD

//#define BD_MST072A_D01A_WITH_ONBOARD_TUNER_ATV

#define MSB1210_TS_SERIAL_INVERSION                     0
#define MSB1210_TS_PARALLEL_INVERSION                   0
#define MSB1210_DTV_DRIVING_LEVEL                       1 //0 or 1
#define MSB1210_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE       1

#define INTERN_DVBT_TS_SERIAL_INVERSION                 0
#define INTERN_DVBT_TS_PARALLEL_INVERSION               0
#define INTERN_DVBT_DTV_DRIVING_LEVEL                   1
#define INTERN_DVBT_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE   1

//#if (I2C_IO_EXPANDER_TYPE == I2C_IO_EXPANDER_MSG1016RC)
//#define SECAM_L_PRIME_ON()                      MDrv_ExGPIO3_Set(BIT3, 1) //For SECAM-L PRIME
//#define SECAM_L_PRIME_OFF()                     MDrv_ExGPIO3_Set(BIT3, 0) //For Not SECAM-L PRIME
//#define EXT_RF_AGC_ON()                           MDrv_ExGPIO3_Set(BIT2, 1) // ATV mode: external RF AGC
//#define EXT_RF_AGC_OFF()                      MDrv_ExGPIO3_Set(BIT2, 0) // DTV mode: internal RF AGC

//#else
#define SECAM_L_PRIME_ON()              //mdrv_gpio_set_high( BALL_F4 ) //GPIO60_SET(1)//_FUNC_NOT_USED()
#define SECAM_L_PRIME_OFF()             //mdrv_gpio_set_low( BALL_F4 ) //GPIO60_SET(0)//_FUNC_NOT_USED()
#define EXT_RF_AGC_ON()                 mdrv_gpio_set_high(BALL_AC2) // ATV mode: external RF AGC
#define EXT_RF_AGC_OFF()                mdrv_gpio_set_low(BALL_AC2)  // DTV mode: internal RF AGC

//#endif

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
#define ENABLE_POWER_SAVING_SIF         1
#define ENABLE_POWER_SAVING_VDMVD       0
#define ENABLE_POWER_SAVING_DPMS        0

#define ENABLE_PWS 1 // Analog IP PWS, for U3 and T3
#define ENABLE_DIP_PWS 0  //Digital IP PWS, for U3 only now
#define ENABLE_DIP_MONITOR 0//For U3 oly now


//------Memory Setting----------------------------------------------------------
#define BOOTUP_MIU_BIST                 1
#ifndef MEMORY_MAP
#define MEMORY_MAP                      MMAP_128_128MB//MMAP_64MB
#endif
#define MIU_INTERFACE                   DDR3_INTERFACE_BGA   //DDR3_INTERFACE_BGA / DDR2_INTERFACE_BGA
#define MIU_DRAM_FREQ                   1333 //800 / 1066 / 1333 / 1666

#define MIU1_INTERFACE                  DDR3_INTERFACE_BGA   //DDR3_INTERFACE_BGA / DDR2_INTERFACE_BGA
#define MIU1_DRAM_FREQ                  1333 //800 / 1066 / 1333 / 1666

//------Analog Function Setting-------------------------------------------------
#define MOD_LVDS_GPIO                   0x820

#define LVDS_PN_SWAP_L                  0x00
#define LVDS_PN_SWAP_H                  0x00

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
#define EXMCU_SLAVE_ADDR                0xA8
#define EXMCU_SUBADDRESS                0x04
#define EXMCU_SLEEP_MODE                0x00
#endif

// ??? This board support HW IIC (TBC)
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
#define Audio_Amplifier_ON()            mdrv_gpio_set_high( BALL_F4 )
#define Audio_Amplifier_OFF()           mdrv_gpio_set_low( BALL_F4 )

#define Adj_Volume_Off()                mdrv_gpio_set_high( BALL_F7 )
#define Adj_Volume_On()                 mdrv_gpio_set_low( BALL_F7 )

#define Panel_VCC_ON()                  mdrv_gpio_set_low( BALL_V21 )   // Y9->Y10
#define Panel_VCC_OFF()                 mdrv_gpio_set_high( BALL_V21 )  // Y9->Y10
#define Panel_Backlight_VCC_ON()        mdrv_gpio_set_low( BALL_T20 )
#define Panel_Backlight_VCC_OFF()       mdrv_gpio_set_high( BALL_T20 )

//#define Panel_Backlight_PWM_ADJ(x)      msPWM2_DutyCycle( x )
//#define Panel_Backlight_Max_Current(x)  msPWM2_DutyCycle( x )
#define Panel_Backlight_PWM_ADJ(x)      MDrv_PWM_DutyCycle(E_PWM_CH2, x)
#define Panel_Backlight_Max_Current(x)  MDrv_PWM_DutyCycle(E_PWM_CH2, x)

#define Panel_VG_HL_CTL_ON()            _FUNC_NOT_USED()
#define Panel_VG_HL_CTL_OFF()           _FUNC_NOT_USED()
#define PANEL_CONNECTOR_SWAP_LVDS_CH    0
#define PANEL_CONNECTOR_SWAP_LVDS_POL   0 // need to check
#define PANEL_CONNECTOR_SWAP_PORT       1

#define PANEL_SWAP_LVDS_POL             1

// PCMCIA power control
#define PCMCIA_VCC_ON()                 mdrv_gpio_set_high( BALL_AB5 )
#define PCMCIA_VCC_OFF()                mdrv_gpio_set_low( BALL_AB5 )

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

#define TunerOffPCMCIA()                PCMCIA_VCC_OFF()
#define TunerOnPCMCIA()                 PCMCIA_VCC_ON()


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
#define ENABLE_KPDCHAN_2                ENABLE
#define ENABLE_KPDCHAN_3                DISABLE
#define ENABLE_KPDCHAN_4                DISABLE

#define KEYPAD_KEY_VALIDATION           3
#define KEYPAD_REPEAT_KEY_CHECK         KEYPAD_KEY_VALIDATION + 2
#define KEYPAD_REPEAT_KEY_CHECK_1       KEYPAD_KEY_VALIDATION + 3
#define KEYPAD_STABLE_NUM               10
#define KEYPAD_STABLE_NUM_MIN           9
#define KEYPAD_REPEAT_PERIOD            2 // 6
#define KEYPAD_REPEAT_PERIOD_1          KEYPAD_REPEAT_PERIOD/2

#define KEYPAD_CH1_UB                   0xFF
#define KEYPAD_CH1_LB                   0x80
#define KEYPAD_CH2_UB                   0xFF
#define KEYPAD_CH2_LB                   0x80
#define KEYPAD_CH3_UB                   0xFF
#define KEYPAD_CH3_LB                   0x80
#define KEYPAD_CH4_UB                   0xFF
#define KEYPAD_CH4_LB                   0x80

#define ADC_KEY_LEVEL                   4
#define ADC_KEY_L0                      0x12
#define ADC_KEY_L1                      0x36
#define ADC_KEY_L2                      0x56
#define ADC_KEY_L3                      0x7B
#define ADC_KEY_LEVEL_MAX               ADC_KEY_L3

//### Currently Only Support 2 keypad Channels
//### Support un-balanced levels for each channel by spec. requirement
#define ADC_CH1_LEVELS                  4 //### must be <= ADC_KEY_LEVEL
#define ADC_CH2_LEVELS                  4 //### must be <= ADC_KEY_LEVEL
#define ADC_CH3_LEVELS                  4 //### must be <= ADC_KEY_LEVEL
#define ADC_CH4_LEVELS                  4 //### must be <= ADC_KEY_LEVEL

#define ADC_KEY_1_L0                    0x27//0x27
#define ADC_KEY_1_L1                    0x46//0x47
#define ADC_KEY_1_L2                    0x63//0x63
#define ADC_KEY_1_L3                    0x7A//0x7B
#define ADC_KEY_1_L4                    0x00//RFU
#define ADC_KEY_1_L5                    0x00//RFU
#define ADC_KEY_1_L6                    0x00//RFU
#define ADC_KEY_1_L7                    0x00//RFU

#define ADC_KEY_2_L0                    0x27//0x27
#define ADC_KEY_2_L1                    0x46//0x47
#define ADC_KEY_2_L2                    0x63//0x63
#define ADC_KEY_2_L3                    0x7A//0x7B
#define ADC_KEY_2_L4                    0x00//RFU
#define ADC_KEY_2_L5                    0x00//RFU
#define ADC_KEY_2_L6                    0x00//RFU
#define ADC_KEY_2_L7                    0x00//RFU

#if (KEYPAD_TYPE_SEL == KEYPAD_TYPE_CUSTMOER)   // CUSTMOER keypad
#define ADC_KEY_1_L0_FLAG               IRKEY_UP
#define ADC_KEY_1_L1_FLAG               IRKEY_MENU
#define ADC_KEY_1_L2_FLAG               IRKEY_LEFT
#define ADC_KEY_1_L3_FLAG               IRKEY_MUTE
#define ADC_KEY_1_L4_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L5_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L6_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L7_FLAG               IRKEY_DUMY//RFU

#define ADC_KEY_2_L0_FLAG               IRKEY_POWER
#define ADC_KEY_2_L1_FLAG               IRKEY_INPUT_SOURCE
#define ADC_KEY_2_L2_FLAG               IRKEY_RIGHT
#define ADC_KEY_2_L3_FLAG               IRKEY_DOWN
#define ADC_KEY_2_L4_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L5_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L6_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L7_FLAG               IRKEY_DUMY//RFU
#elif (KEYPAD_TYPE_SEL == KEYPAD_TYPE_ORIG)   // MStar normal keypad
#define ADC_KEY_1_L0_FLAG               IRKEY_UP
#define ADC_KEY_1_L1_FLAG               IRKEY_MENU
#define ADC_KEY_1_L2_FLAG               IRKEY_LEFT
#define ADC_KEY_1_L3_FLAG               IRKEY_MUTE
#define ADC_KEY_1_L4_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L5_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L6_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L7_FLAG               IRKEY_DUMY//RFU

#define ADC_KEY_2_L0_FLAG               IRKEY_POWER
#define ADC_KEY_2_L1_FLAG               IRKEY_INPUT_SOURCE
#define ADC_KEY_2_L2_FLAG               IRKEY_RIGHT
#define ADC_KEY_2_L3_FLAG               IRKEY_DOWN
#define ADC_KEY_2_L4_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L5_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L6_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L7_FLAG               IRKEY_DUMY//RFU
#elif (KEYPAD_TYPE_SEL == KEYPAD_TYPE_DEMO) // MStar demo set keypad
#define ADC_KEY_1_L0_FLAG               IRKEY_MUTE
#define ADC_KEY_1_L1_FLAG               IRKEY_VOLUME_MINUS
#define ADC_KEY_1_L2_FLAG               IRKEY_VOLUME_PLUS
#define ADC_KEY_1_L3_FLAG               IRKEY_DOWN
#define ADC_KEY_1_L4_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L5_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L6_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_1_L7_FLAG               IRKEY_DUMY//RFU

#define ADC_KEY_2_L0_FLAG               IRKEY_POWER
#define ADC_KEY_2_L1_FLAG               IRKEY_UP
#define ADC_KEY_2_L2_FLAG               IRKEY_MENU
#define ADC_KEY_2_L3_FLAG               IRKEY_INPUT_SOURCE
#define ADC_KEY_2_L4_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L5_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L6_FLAG               IRKEY_DUMY//RFU
#define ADC_KEY_2_L7_FLAG               IRKEY_DUMY//RFU
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
#define PANEL_PDP_10BIT             1

//------ HDMI RELATED ---------------------------------------------------------
#define HDCP_HPD_INVERSE                ENABLE

#define ENABLE_FACTORY_POWER_ON_MODE    ENABLE

#endif // _MSBOARD_H_
