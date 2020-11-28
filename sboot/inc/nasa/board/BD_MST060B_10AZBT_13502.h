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

#define BOARD_NAME                  "BD_MST060B_10AZBT_13502"

//------MHL Setting-----------------------------------------------------------
#define ENABLE_MHL                  ENABLE
#define MHL_TYPE                    MHL_TYPE_INTERNAL
#define HDMI_PORT_FOR_MHL           UI_INPUT_SOURCE_HDMI

//For Support MHL chip
#if (ENABLE_MHL == ENABLE)
#define INPUT_SUPPORT_MHL_PATH      E_INPUT_SUPPORT_MHL_PORT_DVI0
#else
#define INPUT_SUPPORT_MHL_PATH      E_INPUT_NOT_SUPPORT_MHL
#endif

#define PIN_SPI_CZ1                 0//PIN_129
#define PIN_SPI_CZ2                 0
#define PIN_SPI_CZ3                 0
#define PIN_FLASH_WP0               PIN_120
#define PIN_I2S_IN                  0
#define PIN_I2S_OUT                 0
#define PIN_SPDIF_OUT               0

//------PAD MUX setting-------------------------------------------------------
#define Unknown_pad_mux             0
#define XC3DLR_PATH1                1
#define XC3DLR_PATH2                2
#define XC3DLR_VSYNC_PATH1          3
#define XC3DLR_VSYNC_PATH2          4
#define TTL_8BIT_MODE               1
#define TTL_6BIT_MODE               1
#define MHL_CBUS_MODE1              1 //PAD_HOTPLUG_A
#define MHL_CBUS_MODE2              2 //PAD_HOTPLUG_B
#define MHL_CBUS_MODE3              3 //PAD_HOTPLUG_C
#define MHL_VBUS_MODE1              1 //PAD_GPIO2
#define MHL_VBUS_MODE2              2 //PAD_GPIO0
#define MHL_VBUS_MODE3              3 //PAD_PWM0
#define MHL_VBUS_MODE4              4 //PAD_PWM1
#define DDCDA_ENABLE                1 //PAD_DDCDA_CLK, PAD_DDCDA_DAT
#define DDCDB_ENABLE                1 //PAD_DDCDB_CLK, PAD_DDCDB_DAT
#define DDCDC_ENABLE                1 //PAD_DDCDC_CLK, PAD_DDCDC_DAT
#define I2S_IN_MODE1                1 //PAD_GPIO2, PAD_GPIO3, PAD_GPIO4
#define I2S_OUT_MODE1               1 //PAD_GPIO2, PAD_TCON2, PAD_TCON4, PAD_TCON5
#define I2S_OUT_MODE2               2 //PAD_GPIO2, PAD_TCON1, PAD_TCON2, PAD_TCON4, PAD_TCON5
#define I2S_OUT_MODE3               3 //PAD_GPIO2, PAD_GPIO3, PAD_GPIO4, PAD_GPIO6, PAD_GPIO7
#define I2S_OUT_MODE4               4 //PAD_GPIO3, PAD_GPIO4, PAD_GPIO6, PAD_GPIO17
#define I2S_OUT_MODE5               5 //PAD_GPIO3, PAD_GPIO4, PAD_GPIO6, PAD_GPIO7
#define DDCR_PATH(X)                X // 1 ~ 4
#define IIC_PATH(X)                 X // 1 ~ 4
#define TS_IN_P_MODE(X)             X // 1 ~ 2
#define TS_IN_S_MODE(X)             X // 1 ~ 2
#define TS_OUT_P_MODE(X)            X // 1 ~ 4
#define PAD_TCON_7                  0x7F

//define the following values from 1
#define PADS_CEC_CONFIG             PAD_CEC //Unknown_pad_mux
#define PADS_TCON_CONFIG            Unknown_pad_mux //TCON0~TCON6
#define PADS_UART2_MODE             Unknown_pad_mux //PAD_GPIO0 or PAD_GPIO1
#define PADS_UART3_MODE             Unknown_pad_mux //PAD_GPIO3 or PAD_GPIO4
#define PADS_UART4_MODE             Unknown_pad_mux //PAD_TCON0 or PAD_TCON1
#define PADS_UART5_MODE             Unknown_pad_mux //PAD_TCON2 or PAD_TCON3
#define PADS_FAST_UART_MODE         Unknown_pad_mux //PAD_TCON0 or PAD_TCON1
#define PADS_3DLR_MODE              Unknown_pad_mux
#define PADS_8BIT_TTL               Unknown_pad_mux
#define PADS_6BIT_TTL               Unknown_pad_mux
#define PADS_MHL_CBUS               MHL_CBUS_MODE1
#define PADS_MHL_VBUS               MHL_VBUS_MODE1 //PAD_GPIO2
#define PADS_MHL_DEBUG              Unknown_pad_mux //PAD_GPIO0
#define PADS_MHL_DET                PAD_MHL_DET //PAD_MHL_DET
#define PADS_DDCDA                  DDCDA_ENABLE
#define PADS_DDCDB                  DDCDB_ENABLE
#define PADS_DDCDC                  DDCDC_ENABLE
#define PADS_I2S_IN                 Unknown_pad_mux
#define PADS_I2S_OUT                Unknown_pad_mux
#define PADS_SPDIF_IN               Unknown_pad_mux //PAD_GPIO7
#define PADS_SPDIF_OUT              PAD_PWM1 //PAD_PWM1,PAD_TCON0, PAD_GPIO4, PAD_TCON1
#define PADS_INT_GPIO               Unknown_pad_mux
#define PADS_PWM0_MODE              PAD_PWM0
#define PADS_PWM1_MODE              Unknown_pad_mux //PAD_PWM1
#define PADS_PWM2_MODE              Unknown_pad_mux //PAD_PWM2
#define PADS_PWM3_MODE              Unknown_pad_mux //PAD_PWM3
#define PADS_PWM4_MODE              Unknown_pad_mux //PAD_GPIO7
#define PADS_PWM5_MODE              Unknown_pad_mux //PAD_GPIO6
#define PADS_DDCR_MODE              Unknown_pad_mux
#define PADS_TS_IN_P_CFG            Unknown_pad_mux
#define PADS_TS_IN_S_CFG            Unknown_pad_mux
#define PADS_TS_OUT_P_CFG           Unknown_pad_mux
#define PADS_SPI_NOR_MODE           Unknown_pad_mux
#define PADS_SPI_NAND_MODE          Unknown_pad_mux
#define PADS_NAND_MODE              Unknown_pad_mux


//------GPIO setting(default GPIO pin level)------------------------------------
#define PIN_99_IS_GPIO              GPIO_OUT_LOW//GPIO61: Panel On: High / Off: Low

#define PIN_29_IS_GPIO              GPIO_OUT_LOW//GPIO87: AUDIO-EN (H:Enable)

#define PIN_54_IS_GPIO              GPIO_IN         //GPIO44: Tuner_SDA
#define PIN_55_IS_GPIO              GPIO_IN         //GPIO45: Tuner_SCL

#define PIN_121_IS_GPIO             GPIO_OUT_HIGH   //GPIO89: PreAMP_EN(H:Mute -> set low)
#define PIN_123_IS_GPIO             GPIO_OUT_LOW    //GPIO91: MUTE_S(L:Mute -> set high)

#define PIN_145_IS_GPIO             GPIO_OUT_HIGH   //GPIO54: PWR_ON/OFF

#define PIN_122_IS_GPIO             GPIO_OUT_HIGH   //GPIO90: USB Port 0 Over Current Detect
#define PIN_140_IS_GPIO             GPIO_OUT_LOW

//------Chip Type---------------------------------------------------------------
#include "chip/MSD8311Z1.h"

#define  SHARE_GND               	ENABLE

//------I2C devices-------------------------------------------------------------
#if USE_SW_I2C
#undef USE_SW_I2C
#define USE_SW_I2C                  1
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
#define DEMOD_IIC_BUS               E_I2C_BUS_DDCD1

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
#define INPUT_SV_VIDEO_COUNT        0  //0, if set = 0, code flow can not support
#define INPUT_YPBPR_VIDEO_COUNT     1

#ifdef ATSC_SYSTEM
#define INPUT_SCART_VIDEO_COUNT     0
#else
#define INPUT_SCART_VIDEO_COUNT     0
#endif

#define INPUT_HDMI_VIDEO_COUNT      2

#ifdef ATSC_SYSTEM
#define ENABLE_SCART_VIDEO          0
#else
#define ENABLE_SCART_VIDEO          ENABLE
#endif

//------Input Source Mux--------------------------------------------------------
#define INPUT_VGA_MUX               INPUT_PORT_ANALOG0
#define INPUT_VGA_SYNC_MUX          INPUT_PORT_ANALOG0_SYNC //SYNC port of VGA. There is a case which data and sync use different port.
#define INPUT_YPBPR_MUX             INPUT_PORT_ANALOG1
#define INPUT_YPBPR2_MUX            INPUT_PORT_NONE_PORT
#define INPUT_TV_YMUX               INPUT_PORT_YMUX_CVBS0
#define INPUT_AV_YMUX               INPUT_PORT_YMUX_CVBS0
#define INPUT_AV2_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_AV3_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_SV_YMUX               INPUT_PORT_NONE_PORT
#define INPUT_SV_CMUX               INPUT_PORT_NONE_PORT
#define INPUT_SV2_YMUX              INPUT_PORT_NONE_PORT
#define INPUT_SV2_CMUX              INPUT_PORT_NONE_PORT
#define INPUT_SCART_YMUX            INPUT_PORT_NONE_PORT
#define INPUT_SCART_RGBMUX          INPUT_PORT_NONE_PORT
#define INPUT_SCART_FB_MUX          SCART_FB1
#define INPUT_SCART2_YMUX           INPUT_PORT_NONE_PORT
#define INPUT_SCART2_RGBMUX         INPUT_PORT_NONE_PORT
#define INPUT_SCART2_FB_MUX         INPUT_PORT_NONE_PORT

#define INPUT_HDMI1_MUX             INPUT_PORT_DVI0
#define INPUT_HDMI2_MUX             INPUT_PORT_DVI1
#define INPUT_HDMI3_MUX             INPUT_PORT_DVI2

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
#define AUDIO_SOURCE_DTV2           AUDIO_DSP2_DVB_INPUT
#define AUDIO_SOURCE_ATV            AUDIO_DSP3_SIF_INPUT
#define AUDIO_SOURCE_PC             AUDIO_AUIN4_INPUT
#define AUDIO_SOURCE_YPBPR          AUDIO_AUIN4_INPUT
#define AUDIO_SOURCE_YPBPR2         AUDIO_NULL_INPUT
#define AUDIO_SOURCE_AV             AUDIO_AUIN4_INPUT
#define AUDIO_SOURCE_AV2            AUDIO_NULL_INPUT
#define AUDIO_SOURCE_AV3            AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SV             AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SV2            AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SCART          AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SCART2         AUDIO_NULL_INPUT
#define AUDIO_SOURCE_HDMI           AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI2          AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI3          AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_DVI            AUDIO_SOURCE_PC
#define AUDIO_SOURCE_DVI2           AUDIO_SOURCE_PC
#define AUDIO_SOURCE_DVI3           AUDIO_NULL_INPUT
#define AUDIO_SOURCE_KTV            AUDIO_SOURCE_AV

#define AUDIO_PATH_MAIN_SPEAKER     AUDIO_PATH_MAIN	// AUDIO_T3_PATH_I2S
#define AUDIO_PATH_HP               AUDIO_PATH_NULL
#define AUDIO_PATH_LINEOUT          AUDIO_PATH_1
#define AUDIO_PATH_SIFOUT           AUDIO_PATH_NULL
#define AUDIO_PATH_SCART1           AUDIO_PATH_SIFOUT
#define AUDIO_PATH_SCART2           AUDIO_PATH_LINEOUT
#define AUDIO_PATH_SPDIF             AUDIO_PATH_3

#define AUDIO_OUTPUT_MAIN_SPEAKER   AUDIO_AUOUT0_OUTPUT	// AUDIO_I2S_OUTPUT
#define AUDIO_OUTPUT_HP             AUDIO_NULL_OUTPUT
#define AUDIO_OUTPUT_LINEOUT        AUDIO_AUOUT3_OUTPUT
#define AUDIO_OUTPUT_SIFOUT         AUDIO_NULL_OUTPUT
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

#if (ENABLE_MHL == ENABLE)
//MHL
#define MHL_Reset_High()            _FUNC_NOT_USED()
#define MHL_Reset_Low()             _FUNC_NOT_USED()
#endif
//------HDMI ARC Contrl-------------------------------------------------------
#define ARC_CTRL_ON()               _FUNC_NOT_USED()
#define ARC_CTRL_OFF()              _FUNC_NOT_USED()


// HDMI switch Setting
#define HDMI_SWITCH_SELECT          HDMI_SWITCH_NONE


//------Tuner Setting-----------------------------------------------------------

#ifdef ATSC_SYSTEM

    #define TS_CLK_INV                      0
    #define TS_PARALLEL_OUTPUT              1
    #define FRONTEND_DEMOD_TYPE             EMBEDDED_ATSC_DEMOD
    #define FRONTEND_TUNER_TYPE             SAMSUNG_DVTA50_TUNER

    #define FRONTEND_IF_MIXER_TYPE          XUGUANG_T126CWADC
    #define FRONTEND_IF_DEMODE_TYPE         MSTAR_INTERN_VIF

    #define VIF_TUNER_TYPE                  0       // 0: RF Tuner; 1: Silicon Tuner
    #define VIF_SAW_ARCH                    5       // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF)
#else
    #define USE_UTOPIA                      ENABLE
    #define FRONTEND_DEMOD_TYPE             EMBEDDED_DTMB_DEMOD
    #define FRONTEND_SECOND_DEMOD_TYPE      MSTAR_NONE_DEMOD
    #define FRONTEND_IF_DEMODE_TYPE         MSTAR_INTERN_VIF
 	
    #define TS_CLK_INV                      0
    #define TS_PARALLEL_OUTPUT              1
    #define TS_SERIAL_OUTPUT_IF_CI_REMOVED  1
    #define FRONTEND_TUNER_TYPE             MxL_601SI_TUNER//SILAB_2158_TUNER
    #define FRONTEND_IF_MIXER_TYPE          XUGUANG_T126CWADC
    #define VIF_TUNER_TYPE                  1       // 0: RF Tuner; 1: Silicon Tuner
    #define VIF_SAW_ARCH                    2       // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner(DIF); 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF) ;6:silicon tuner(VIF)
#endif


//------------------------------------------------------------------------------------
//FRONTEND_DEMO_TUNER_IIC_TYPE
//------------------------------------------------------------------------------------
#define TWO_ROAD_SEPARATE  1
#define ONE_ROAD_BUS   2
#define DEMO_TO_TUNER   3

//------Tuner Demo IIC Setting-----------------------------------------------------------
#define DEMO_TUNER_IIC_TYPE  TWO_ROAD_SEPARATE //ONE_ROAD_BUS //DEMO_TO_TUNER

#if (VIF_TUNER_TYPE == 1)
#define DTV_LOW_IF_FREQ ENABLE
#endif

//#define BD_MST072A_D01A_WITH_ONBOARD_TUNER_ATV

#define MSB1210_TS_SERIAL_INVERSION                     0
#define MSB1210_TS_PARALLEL_INVERSION                   1
#define MSB1210_DTV_DRIVING_LEVEL                       1 //0 or 1
#define MSB1210_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE       1

#define INTERN_DVBT_TS_SERIAL_INVERSION                 0
#define INTERN_DVBT_TS_PARALLEL_INVERSION               1
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
#define EXT_RF_AGC_ON()                 _FUNC_NOT_USED()  // ATV mode: external RF AGC
#define EXT_RF_AGC_OFF()                _FUNC_NOT_USED()   // DTV mode: internal RF AGC

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
#define MEMORY_MAP                      MMAP_128MB//MMAP_64MB
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
#define LVDS_SSC_SWING_DEFAULT          250
#define LVDS_SSC_SPAN_MAX               500
#define LVDS_SSC_STEP_MAX               300
#define LVDS_SSC_SWING_MIN              40
#define LVDS_SSC_SWING_MAX              600
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
#define SCART_OUT_OFF()                 _FUNC_NOT_USED()

// Video switch Setting
#define Switch_YPbPr1()                 _FUNC_NOT_USED()
#define Switch_YPbPr2()                 _FUNC_NOT_USED()

#define SwitchRGBToSCART()              _FUNC_NOT_USED()
#define SwitchRGBToDSUB()               _FUNC_NOT_USED()

#define MDrv_Sys_GetUsbOcdN()           _FUNC_NOT_USED()
#define MDrv_Sys_GetRgbSw()             _FUNC_NOT_USED()

// Audio Amplifier
#define Audio_Amplifier_ON()            mdrv_gpio_set_high( PIN_29 )
#define Audio_Amplifier_OFF()           mdrv_gpio_set_low( PIN_29 )

#define Adj_Volume_On()                 mdrv_gpio_set_high( PIN_121 )
#define Adj_Volume_Off()                mdrv_gpio_set_low( PIN_121 )

#define Panel_VCC_ON()                  mdrv_gpio_set_high( PIN_99 )
#define Panel_VCC_OFF()                 mdrv_gpio_set_low( PIN_99 )

#define Panel_Backlight_VCC_ON()        mdrv_gpio_set_high( PIN_140 )
#define Panel_Backlight_VCC_OFF()       mdrv_gpio_set_low( PIN_140 )

#define Panel_Backlight_PWM_ADJ(x)      MDrv_PWM_DutyCycle(E_PWM_CH0, x)
#define Panel_Backlight_Max_Current(x)  MDrv_PWM_DutyCycle(E_PWM_CH0, x)

#define Panel_VG_HL_CTL_ON()            _FUNC_NOT_USED()
#define Panel_VG_HL_CTL_OFF()           _FUNC_NOT_USED()

// PCMCIA power control
#define PCMCIA_VCC_ON()                 _FUNC_NOT_USED()
#define PCMCIA_VCC_OFF()                _FUNC_NOT_USED()

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

#define Tuner_Reset_On()                _FUNC_NOT_USED()
#define Tuner_Reset_OFF()               _FUNC_NOT_USED()

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
#define MUTE_On()                       Adj_Volume_Off()
#define MUTE_Off()                      Adj_Volume_On()
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
#define DeactivateScartRecord1()        _FUNC_NOT_USED()
#define ActivateScartRecord1()            _FUNC_NOT_USED()
#define DeactivateScartRecord2()        _FUNC_NOT_USED()
#define ActivateScartRecord2()            _FUNC_NOT_USED()
#define USBPowerOn()                    _FUNC_NOT_USED()
#define USBPowerOff()                   _FUNC_NOT_USED()

// For samsung tuner only
#define SILICON_TUNER_RESET_ON()        mdrv_gpio_set_high( PAD_GPIO6)
#define SILICON_TUNER_RESET_OFF()       mdrv_gpio_set_low( PAD_GPIO6)

//------MST Keypad definition---------------------------------------------------
#define KEYPAD_CHANNEL_SUPPORT          4 //Maximun supported keypad channels
#define ADC_KEY_CHANNEL_NUM             2 //Real supported keypad channels
#define ADC_KEY_LAST_CHANNEL            ADC_KEY_CHANNEL_NUM - 1
//config which keypad channel enabled
#define ENABLE_KPDCHAN_1                ENABLE
#define ENABLE_KPDCHAN_2                DISABLE
#define ENABLE_KPDCHAN_3                DISABLE
#define ENABLE_KPDCHAN_4                DISABLE

#define KEYPAD_KEY_VALIDATION           3
#define KEYPAD_REPEAT_KEY_CHECK         KEYPAD_KEY_VALIDATION + 2
#define KEYPAD_REPEAT_KEY_CHECK_1       KEYPAD_KEY_VALIDATION + 3
#define KEYPAD_STABLE_NUM               10
#define KEYPAD_STABLE_NUM_MIN           9
#define KEYPAD_REPEAT_PERIOD            2 // 6
#define KEYPAD_REPEAT_PERIOD_1          KEYPAD_REPEAT_PERIOD/2

//------------------------------------------------------------------------------
// SAR boundary define
//------------------------------------------------------------------------------
#define KEYPAD_CH1_UB                   0xFF
#define KEYPAD_CH1_LB                   0x70//0x80
#define KEYPAD_CH2_UB                   0xFF
#define KEYPAD_CH2_LB                   0x70//0x80
#define KEYPAD_CH3_UB                   0xFF
#define KEYPAD_CH3_LB                   0x70//0x80
#define KEYPAD_CH4_UB                   0xFF
#define KEYPAD_CH4_LB                   0x70//0x80

//### MAX support 8 level for each channel
#define ADC_KEY_LEVEL                   8
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

#define ADC_KEY_1_L0                    0x10//0x27
#define ADC_KEY_1_L1                    0x30//0x47
#define ADC_KEY_1_L2                    0x50//0x63
#define ADC_KEY_1_L3                    0x6A//0x7B
#define ADC_KEY_1_L4                    0x00//RFU
#define ADC_KEY_1_L5                    0x00//RFU
#define ADC_KEY_1_L6                    0x00//RFU
#define ADC_KEY_1_L7                    0x00//RFU

#define ADC_KEY_2_L0                    0x10//0x27
#define ADC_KEY_2_L1                    0x30//0x47
#define ADC_KEY_2_L2                    0x50//0x63
#define ADC_KEY_2_L3                    0x6A//0x7B
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
/*
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
*/
#define ADC_KEY_1_L0_FLAG               IRKEY_POWER
#define ADC_KEY_1_L1_FLAG               IRKEY_CHANNEL_PLUS
#define ADC_KEY_1_L2_FLAG               IRKEY_CHANNEL_MINUS//IRKEY_DOWN
#define ADC_KEY_1_L3_FLAG               IRKEY_VOLUME_PLUS//IRKEY_RIGHT
#define ADC_KEY_1_L4_FLAG               IRKEY_VOLUME_MINUS//IRKEY_LEFT
#define ADC_KEY_1_L5_FLAG               IRKEY_SELECT
#define ADC_KEY_1_L6_FLAG               IRKEY_INPUT_SOURCE
#define ADC_KEY_1_L7_FLAG               IRKEY_MENU
	
#define ADC_KEY_2_L0_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L1_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L2_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L3_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L4_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L5_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L6_FLAG               IRKEY_DUMY
#define ADC_KEY_2_L7_FLAG               IRKEY_DUMY

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
//PWMX Period=( PWMX_PERIOD+1 ) *( 1/ Xtal) //X=0~5
//PWMX_duty= (Init_PwmX_DUTY +1 ) * (1/XTAL) //X=0~5
#if (PADS_PWM0_MODE!=Unknown_pad_mux)
#define PWM0_PERIOD                     0xff
#define INIT_PWM0_DUTY                  0x7e
#define PWM0_DIV                        0x00
#endif
#if (PADS_PWM1_MODE!=Unknown_pad_mux)
#define PWM1_PERIOD                     0xff
#define INIT_PWM1_DUTY                  0x7e
#endif
#if (PADS_PWM2_MODE!=Unknown_pad_mux)
#define PWM2_PERIOD                     0xff
#define INIT_PWM2_DUTY                  0x7e
#endif
#if (PADS_PWM3_MODE!=Unknown_pad_mux) //Especially for Tuner+30V Power
#define PWM3_PERIOD                     0x23
#define INIT_PWM3_DUTY                  0x0A
#endif
#if (PADS_PWM4_MODE!=Unknown_pad_mux)
#define PWM4_PERIOD                     0xff
#define INIT_PWM4_DUTY                  0x7e
#endif
#if (PADS_PWM5_MODE!=Unknown_pad_mux)
#define PWM5_PERIOD                     0xff
#define INIT_PWM5_DUTY                  0x7e
#endif

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

#define ENABLE_PIU_UART1                DISABLE
#define ENABLE_PIU_UART1_INTERRUPT      DISABLE

//------ PANEL RELATED ---------------------------------------------------------
#define PANEL_PDP_10BIT                 1
#define PANEL_SWAP_PORT                 0
#define PANEL_CONNECTOR_SWAP_LVDS_CH    0
#define PANEL_CONNECTOR_SWAP_LVDS_POL   0
#define PANEL_CONNECTOR_SWAP_PORT       1

#define PANEL_SWAP_LVDS_POL             0
#define PANEL_SWAP_LVDS_CH              0
#define BD_LVDS_CONNECT_TYPE            0

//------ HDMI RELATED ---------------------------------------------------------
#define HDCP_HPD_INVERSE                ENABLE

#define PANEL_IS_LED_BACKLIGHT          TRUE

#define  MApi_AUDIO_SPDIF_GetMute_Status()     0
#define TV_FREQ_SHIFT_CLOCK DISABLE //ENABLE

#if(FRONTEND_TUNER_TYPE==MxL_301RF_TUNER)
#define D_DMD_IF_DVBT_8M  6000L
#define D_DMD_IF_DVBT_7M  6000L
#define D_DMD_IF_DVBT_6M  6000L
#define D_DMD_IF_DVBC_8M  6000L
#define D_DMD_IF_DVBC_7M  6000L
#define D_DMD_IF_DVBC_6M  6000L
#elif (FRONTEND_TUNER_TYPE == LG_G230D_TUNER)
#define D_DMD_IF_DVBT_8M  5500L
#define D_DMD_IF_DVBT_7M  5500L
#define D_DMD_IF_DVBT_6M  5500L
#define D_DMD_IF_DVBC_8M  5500L
#define D_DMD_IF_DVBC_7M  5500L
#define D_DMD_IF_DVBC_6M  5500L
#else
#define D_DMD_IF_DVBT_8M 4800
#define D_DMD_IF_DVBT_7M 4500
#define D_DMD_IF_DVBT_6M 3500
#define D_DMD_IF_DVBC_8M 5000
#define D_DMD_IF_DVBC_7M 5000
#define D_DMD_IF_DVBC_6M 5000
#endif
#define D_DMD_TUNER_IQSWAP 1

#define D_DMD_SAR_CHANNEL 0xFF
#define D_DMD_SSI_TABLE_RFAGC \
{ \
    {-15.000000,    0x1c}, \
    {-15.500000,    0x1c}, \
    {-16.000000,    0x1c}, \
    {-16.500000,    0x1d}, \
    {-17.000000,    0x1e}, \
    {-17.500000,    0x1e}, \
    {-18.000000,    0x1f}, \
    {-18.500000,    0x20}, \
    {-19.000000,    0x20}, \
    {-19.500000,    0x21}, \
    {-20.000000,    0x22}, \
    {-20.500000,    0x23}, \
    {-21.000000,    0x23}, \
    {-21.500000,    0x25}, \
    {-22.000000,    0x26}, \
    {-22.500000,    0x27}, \
    {-23.000000,    0x28}, \
    {-23.500000,    0x2a}, \
    {-24.000000,    0x2b}, \
    {-24.500000,    0x2d}, \
    {-25.000000,    0x2f}, \
    {-25.500000,    0x31}, \
    {-26.000000,    0x33}, \
    {-26.500000,    0x35}, \
    {-27.000000,    0x38}, \
    {-27.500000,    0x3a}, \
    {-28.000000,    0x3d}, \
    {-28.500000,    0x40}, \
    {-29.000000,    0x42}, \
    {-29.500000,    0x45}, \
    {-30.000000,    0x47}, \
    {-30.500000,    0x49}, \
    {-31.000000,    0x4c}, \
    {-31.500000,    0x4e}, \
    {-32.000000,    0x51}, \
    {-32.500000,    0x52}, \
    {-33.000000,    0x55}, \
    {-33.500000,    0x56}, \
    {-34.000000,    0x59}, \
    {-34.500000,    0x5a}, \
    {-35.000000,    0x5c}, \
    {-35.500000,    0x5e}, \
    {-36.000000,    0x60}, \
    {-36.500000,    0x61}, \
    {-37.000000,    0x63}, \
    {-37.500000,    0x64}, \
    {-38.000000,    0x66}, \
    {-38.500000,    0x67}, \
    {-39.000000,    0x69}, \
    {-39.500000,    0x6b}, \
    {-40.000000,    0x6c}, \
    {-40.500000,    0x6d}, \
    {-41.000000,    0x6e}, \
    {-41.500000,    0x70}, \
    {-42.000000,    0x71}, \
    {-42.500000,    0x72}, \
    {-43.000000,    0x74}, \
    {-43.500000,    0x75}, \
    {-44.000000,    0x76}, \
    {-44.500000,    0x78}, \
    {-45.000000,    0x79}, \
    {-45.500000,    0x7a}, \
    {-46.000000,    0x7b}, \
    {-46.500000,    0x7c}, \
    {-47.000000,    0x7d}, \
    {-47.500000,    0x7e}, \
    {-48.000000,    0x7f}, \
    {-48.500000,    0x81}, \
    {-49.000000,    0x82}, \
    {-49.500000,    0x83}, \
    {-50.000000,    0x84}, \
    {-50.500000,    0x85}, \
    {-51.000000,    0x87}, \
    {-51.500000,    0x88}, \
    {-52.000000,    0x89}, \
    {-52.500000,    0x8b}, \
    {-53.000000,    0x8d}, \
    {-53.500000,    0x8f}, \
    {-54.000000,    0x91}, \
    {-54.500000,    0x94}, \
    {-55.000000,    0x9a}, \
    {-55.500000,    0xae}, \
    {-56.000000,    0xeb}, \
    {-56.500000,    0xef}, \
    {-57.000000,    0xf0}, \
} \

#define D_DMD_SSI_TABLE_IFAGC \
{ \
    {-56.000000,    0xb1}, \
    {-56.500000,    0xb2}, \
    {-57.000000,    0xb2}, \
    {-57.500000,    0xb3}, \
    {-58.000000,    0xb4}, \
    {-58.500000,    0xb4}, \
    {-59.000000,    0xb5}, \
    {-59.500000,    0xb6}, \
    {-60.000000,    0xb6}, \
    {-60.500000,    0xb7}, \
    {-61.000000,    0xb8}, \
    {-61.500000,    0xb9}, \
    {-62.000000,    0xb9}, \
    {-62.500000,    0xba}, \
    {-63.000000,    0xba}, \
    {-63.500000,    0xbb}, \
    {-64.000000,    0xbc}, \
    {-64.500000,    0xbc}, \
    {-65.000000,    0xbd}, \
    {-65.500000,    0xbe}, \
    {-66.000000,    0xbe}, \
    {-66.500000,    0xbf}, \
    {-67.000000,    0xbf}, \
    {-67.500000,    0xc0}, \
    {-68.000000,    0xc0}, \
    {-68.500000,    0xc1}, \
    {-69.000000,    0xc1}, \
    {-69.500000,    0xc1}, \
    {-70.000000,    0xc2}, \
    {-70.500000,    0xc2}, \
    {-71.000000,    0xc3}, \
    {-71.500000,    0xc3}, \
    {-72.000000,    0xc3}, \
    {-72.500000,    0xc4}, \
    {-73.000000,    0xc4}, \
    {-73.500000,    0xc5}, \
    {-74.000000,    0xc5}, \
    {-74.500000,    0xc6}, \
    {-75.000000,    0xc6}, \
    {-75.500000,    0xc6}, \
    {-76.000000,    0xc7}, \
    {-76.500000,    0xc7}, \
    {-77.000000,    0xc8}, \
    {-77.500000,    0xc8}, \
    {-78.000000,    0xc9}, \
    {-78.500000,    0xc9}, \
    {-79.000000,    0xca}, \
    {-79.500000,    0xca}, \
    {-80.000000,    0xcb}, \
    {-80.500000,    0xcc}, \
    {-81.000000,    0xcc}, \
    {-81.500000,    0xcd}, \
    {-82.000000,    0xcd}, \
    {-82.500000,    0xcd}, \
    {-83.000000,    0xce}, \
    {-83.500000,    0xce}, \
    {-84.000000,    0xcf}, \
    {-84.500000,    0xcf}, \
    {-85.000000,    0xd0}, \
    {-85.500000,    0xd0}, \
    {-86.000000,    0xd1}, \
    {-86.500000,    0xd1}, \
    {-87.000000,    0xd2}, \
    {-87.500000,    0xd3}, \
    {-88.000000,    0xee}, \
    {-93.000000,    0xff}, \
} \

#define D_DMD_SSI_TABLE_IFAGC_ERR_LO \
{ \
    {0.00,        0x0A}, \
    {0.00,        0xFF}, \
} \

#define D_DMD_SSI_TABLE_IFAGC_ERR_HI \
{ \
    {0.00,        0x2D}, \
    {0.00,        0xFF}, \
} \

#define D_DMD_SQI_CN_NORDIGP1 \
{ \
    {_QPSK,  _CR1Y2, 5.1 }, \
    {_QPSK,  _CR2Y3, 6.9 }, \
    {_QPSK,  _CR3Y4, 7.9 }, \
    {_QPSK,  _CR5Y6, 8.9 }, \
    {_QPSK,  _CR7Y8, 9.7 }, \
    {_16QAM, _CR1Y2, 10.8}, \
    {_16QAM, _CR2Y3, 13.1}, \
    {_16QAM, _CR3Y4, 12.2}, \
    {_16QAM, _CR5Y6, 15.6}, \
    {_16QAM, _CR7Y8, 16.0}, \
    {_64QAM, _CR1Y2, 16.5}, \
    {_64QAM, _CR2Y3, 16.3}, \
    {_64QAM, _CR3Y4, 17.8}, \
    {_64QAM, _CR3Y4, 21.2}, \
    {_64QAM, _CR5Y6, 21.6}, \
    {_64QAM, _CR7Y8, 22.5}, \
} \

#define D_DMD_DVBT_DSPRegInitExt \
{\
     1,\
     0,\
}
/*
// 0:DUAL_SAW
    3,// version
    0,// reserved
    0xFF,// TS_CLK
    1,// RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
    (MS_U8)(36167>>24),// IF Frequency
    (MS_U8)(36167>>16),
    (MS_U8)(36167>>8),
    (MS_U8)(36167>>0),
    (MS_U8)(45474>>24),// FS Frequency
    (MS_U8)(45474>>16),
    (MS_U8)(45474>>8),
    (MS_U8)(45474>>0),
    0,// IQ Swap
    0,// u8ADCIQMode : 0=I path, 1=Q path, 2=both IQ
    0,// u8PadSel : 0=Normal, 1=analog pad
    0,// bPGAEnable : 0=disable, 1=enable
    5,// u8PGAGain : default 5
*/
#if (VIF_SAW_ARCH==0)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==1)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==2)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    1, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==3)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==4)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    1, \
    1, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==5)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==6)
#define D_DMD_DVBT_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(5500>>24), \
    (MS_U8)(5500>>16), \
    (MS_U8)(5500>>8), \
    (MS_U8)(5500>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    1, \
    1, \
    0, \
    5, \
}
#else
#define D_DMD_DVBT_InitExt NULL
#print "BOARD_SAW_TYPE Error"
#endif

#define D_DMD_DVBC_DSPRegInitExt \
{\
    1,\
    0,\
    E_DMD_DVBC_NO_SIGNAL_NUM_TH,\
    E_DMD_DVBC_NO_SIGNAL_NUM_TH>>8,\
    0xFF,\
    0x14,\
    E_DMD_DVBC_NO_SIGNAL_GAIN_TH_L,\
    E_DMD_DVBC_NO_SIGNAL_GAIN_TH_L>>8,\
    0xFF,\
    0x00,\
    E_DMD_DVBC_NO_SIGNAL_GAIN_TH_H,\
    E_DMD_DVBC_NO_SIGNAL_GAIN_TH_H>>8,\
    0xFF,\
    0x80,\
}//pls ask BY.Tsai why modify this value (from 0x90 to 0x80)can improve scan speed.
/*
// 0:DUAL_SAW
    3,// version
    0,// reserved
    0xFF,// TS_CLK
    1,// RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
    (MS_U8)(36167>>24),// IF Frequency
    (MS_U8)(36167>>16),
    (MS_U8)(36167>>8),
    (MS_U8)(36167>>0),
    (MS_U8)(45474>>24),// FS Frequency
    (MS_U8)(45474>>16),
    (MS_U8)(45474>>8),
    (MS_U8)(45474>>0),
    0,// IQ Swap
    0,// u8ADCIQMode : 0=I path, 1=Q path, 2=both IQ
    0,// u8PadSel : 0=Normal, 1=analog pad
    0,// bPGAEnable : 0=disable, 1=enable
    5,// u8PGAGain : default 5
*/
#if (VIF_SAW_ARCH==0)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==1)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==2)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    1, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==3)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==4)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    1, \
    1, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==5)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(36167>>24), \
    (MS_U8)(36167>>16), \
    (MS_U8)(36167>>8), \
    (MS_U8)(36167>>0), \
    (MS_U8)(45474>>24), \
    (MS_U8)(45474>>16), \
    (MS_U8)(45474>>8), \
    (MS_U8)(45474>>0), \
    0, \
    0, \
    0, \
    0, \
    5, \
}
#elif (VIF_SAW_ARCH==6)
#define D_DMD_DVBC_InitExt \
{ \
    3, \
    0, \
    0xFF, \
    1, \
    (MS_U8)(5000>>24), \
    (MS_U8)(5000>>16), \
    (MS_U8)(5000>>8), \
    (MS_U8)(5000>>0), \
    (MS_U8)(24000>>24), \
    (MS_U8)(24000>>16), \
    (MS_U8)(24000>>8), \
    (MS_U8)(24000>>0), \
    0, \
    1, \
    1, \
    0, \
    5, \
}
#else
#define D_DMD_DVBC_InitExt NULL
#print "BOARD_SAW_TYPE Error"
#endif

#endif // _MSBOARD_H_
