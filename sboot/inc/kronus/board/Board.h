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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _BOARD_H_
#define _BOARD_H_

//------------------------------BOOTLOADER--------------------------------------


//------------------------------PUMODE_WORK-------------------------------------
#define PUMODE_WORK             0
#define PUMODE_STANDBY          1

//------------------------------PIU_TYPE-----------------
#define PIU_UART_0                  0x0000          // SM1
#define PIU_UART_1                  0x0001
#define PIU_UART_2                  0x0002          // SM2
#define PIU_UART_3                  0x0003
#define PIU_UART_NONE               0x000F
#define PIU_IIC_0                   0x0010
#define PIU_IIC_1                   0x0020
#define PIU_IIC_2                   0x0030
#define PIU_IIC_GPIO                0x00E0
#define PIU_IIC_NONE                0x00F0
//------------------------------DEMOD_IQ-----------------
#define DEMOD_IQ_I_IN               0
#define DEMOD_IQ_Q_IN               1

//------------------------------TV_SYSTEM---------------------------------------
#define TV_NTSC                 0
#define TV_PAL                  1
#define TV_CHINA                2

//------------------------------AUDIO_SYSTEM_SEL--------------------------------
#define AUDIO_SYSTEM_BTSC                       0
#define AUDIO_SYSTEM_A2         1
#define AUDIO_SYSTEM_EIAJ                        2

//Eddie added at 20071231
#define HDCPKEY_USE_CODE    0
#define HDCPKEY_USE_24C04    1
#define HDCPKEY_USE_24C08   2
#define HDCPKEY_USE_24C16   3
#define HDCPKEY_USE_24C32   4
//End of Eddie

//------------------------------DRAM type---------------------------------------
#define SDRAM_32                0
#define DDRAM_32                1
#define DDRAM_16                2

// new style for S4...
#define SDR                     0x10
#define DDR_I                   0x11
#define DDR_II                  0x12

//------------------------------DRAM Bus---------------------------------------
#define DRAM_BUS_16             0
#define DRAM_BUS_32             1

//------------------------------DDRPLL Freq--------------------------------------
#define DDRLLL_FREQ_166         166
#define DDRLLL_FREQ_200         200
#define DDRLLL_FREQ_333         333
#define DDRLLL_FREQ_380         380
#define DDRLLL_FREQ_400         400
#define DDRLLL_FREQ_450         450

//------------------------------DRAM Chip---------------------------------------
#define DRAM_ETRON              0
#define DRAM_NANYA              1

//------------------------------DRAM Size---------------------------------------
#define DDRAM16_32M             0
#define DDRAM16_64M             1

#define EEPROM_CLK_100KHZ       0
#define EEPROM_CLK_200KHZ       1
#define EEPROM_CLK_400KHZ       2

#define EEPROM_BLK_CPY_SIZE     MSAPI_DMX_SECTION_4K

//------------------------------POWER_KEY_SEL------------
#define POWER_KEY_PAD_WAKEUP    0   // power key is connected to PAD_WAKEUP
#define POWER_KEY_PAD_INT       1   // power key is connected to PAD_INT

//------------------------------VIDEO_FIRMWARE_CODE_SEL-------------------------
#define VIDEO_FIRMWARE_CODE_SD  0x00
#define VIDEO_FIRMWARE_CODE_HD  0x10

//------------------------------IO_DEVICE_SEL-----------------------------------
#define IO_DEV_NULL             -1
#define IO_DEV_UART0            0
#define IO_DEV_UART1            1
#define IO_DEV_PIU_UART0        2

//------------------------------EXT_SUBMCU_TYPE---------------------------------
#define EXT_SUBMCU_NONE         0
#define EXT_SUBMCU_MSTAR_UA01   1   // UART, chip A, protocol 01

//------------------------------MEMORY_MAP--------------------------------------
#define MMAP_24MB               0
#define MMAP_16MB               1
#define MMAP_8MB                2
#define MMAP_4MB                3
#define MMAP_4MB_FLASH          4
#define MMAP_32MB               5
#define MMAP_64MB               6
#define MMAP_64_32MB            7
#define MMAP_64_64MB            8
#define MMAP_64MB_SD            9
#define MMAP_128MB              10
#define MMAP_128_128MB          11



#define  DDR2_INTERFACE_QFP               0
#define  DDR2_INTERFACE_QFP_216           DDR2_INTERFACE_QFP
#define  DDR2_INTERFACE_BGA               1
#define  DDR3_INTERFACE_BGA               2
#define  DDR2_INTERFACE_BGA_4X_MODE       3
#define  DDR3_INTERFACE_QFP               4
#define  DDR3_INTERFACE_QFP_8BIT_MODE     5
#define  DDR2_INTERFACE_QFP_128           6
#define  DDR3_INTERFACE_QFP_128           7
#define  DDR3_INTERFACE_QFP_128_8BIT_MODE 8
#define  DDR3_INTERFACE_QFP_156           9
#define  DDR3_INTERFACE_QFP_156_8BIT_MODE 10


//------------------------------FLASH_SIZE--------------------------------------
#define FLASH_SIZE_1MB          0x100000
#define FLASH_SIZE_2MB          0x200000
#define FLASH_SIZE_4MB          0x400000
#define FLASH_SIZE_8MB          0x800000
#define FLASH_SIZE_16MB         0x1000000

//------------------------------MS_FONT_SIZE_TYPE-------------------------------
#define MS_FONT_SMALL           0
#define MS_FONT_LARGE           1
#define MS_FONT_NORMAL          2

//------------------------------UNUSED MACROS-----------------------------------
#define _FUNC_NOT_USED()        do {} while ( 0 )

//------------------------------MS_BOARD_TYPE_SEL-------------------------------
// Demo board made in Taiwan

#define BD_FPGA                 0x00FF

// S2, S3
#define BD_MST037A_D01A         0x0020
#define BD_MST037B_D01A         0x0021
#define BD_MST037C_D01A         0x0022

#define BD_MST037E_D01A         0x0023
#define BD_MST037F_C01A         0x0024
#define BD_MST037G_C01A         0x0025
#define BD_MST037H_D01A         0x0026
#define BD_MST037I_C01A         0x0027
#define BD_MST037J_D01A         0x0028
#define BD_MST037K_D01A         0x0029
#define BD_MST037L_D01A         0x003A
#define BD_MST037N_C01A         0x003B

// S3+
#define BD_MST042A_D01A         0x0040
#define BD_MST042B_D01A         0x0041
#define BD_MST042C_D01A         0x0042
#define BD_MST042D_D01A         0x0043
#define BD_MST042F_D01A_S       0x0044  // socket board
#define BD_MST042F_D01A         0x0045  // demo board
#define BD_MST042H_D01A         0x0046
#define BD_MST042H_D02A         0x0047
#define BD_MST042H_D02B         0x0048
#define BD_MST042K_D01A_S       0x0049
#define BD_MST042K_D01A         0x0050
#define BD_MST042K_D02A         0x0051
#define BD_MST042Q_D01A         0x0052
#define BD_MST058B_D02A         0x0053
// S4 Eris
#define BD_MST035B_D01D_S4      0x0060
#define BD_MST042F_D01A_S_S4    0x0061
#define BD_MST052A_D01A_S       0x0062
#define BD_MST052B_D01A_S       0x0063
#define BD_MST052B_D01A         0x0064
#define BD_MST052D_D01A_S       0x0065
#define BD_MST052D_D01A         0x0066
#define BD_MST052D_D01A_CH      0x0067  //CHANGHONG board  goldie
#define BD_MST052F_D01A         0x0068
#define BD_MST052E_D01A         0x0069
#define BD_MST052G_D01A_S       0x006A
#define BD_MST052G_D01A         0x006B
#define BD_MST052I_D01A         0x006C
#define BD_MST052H_D01A_S       0x006D

// S4Lite
#define BD_MST055A_D01A_S       0x0080
#define BD_MST055B_D01A_S       0x0081
#define BD_MST055C_D01A_S       0x0082
#define BD_MST055D_D01A_S       0x0083
#define BD_MST055D_D01A         0x0084
#define BD_MST055D_C01A         0x0085

// S4Lite + Triton
#define BD_MST056B_D01A_S       0x0090
#define BD_MST_S5_DEMO_01       0x0091
#define BD_MST055E_D01A_S       0x0092
#define BD_MST_S6_DEMO_01       0x0093

#define BD_MST064A_D01A_S       0x0094      // H6 USBx1
#define BD_MST064A_D01C_S       0x0095      // H6 USB x2
#define BD_MST064B_D01B_S       0x0096
#define BD_MST064C_D01A_S       0x0097      // TCON BGA27x27
#define BD_MST064D_D01A_S       0x0098
#define BD_MST064E_D01A         0x0099
#define BD_MST064F_D01A         0x009A

#define BD_MST072A_D01A_S       0x00A0
#define BD_MST072A_D01A         0x00A1
#define BD_MST072B_D01B_S       0x00A2

//S7M,...
#define BD_T3_FPGA_001          0x0701
#define BD_MST087A_D01A_S       0x0702   // 256p QFP
#define BD_MST087B_S7M_D01A_S   0x0703   // S7M - support URSA3
#define BD_MST087B_S7_D01A_S    0x0704   // S7
#define BD_MST087C_D02A_S       0x0705   // SEC X1
#define BD_MST087D_D01A_S       0x0706   // S7
#define BD_MST087C_D01A_S       0x0707   //
#define BD_MST087E_D01A_S       0x0708   //
#define BD_MST087E_D01A         0x0709
#define BD_MST087F_D01A         0x070A

//S7LD
#define BD_MST090A_D01A_S       0x0750
#define BD_MST090B_D01A_S       0x0751
#define BD_MST090C_D01A_S       0x0752

//S7LA
#define BD_MST087B_S7LA_D01A_S  0x0780

//U3
#define BD_MST072C_D01A         0x0A00      // QFP296p
#define BD_MST072D_D01A_S       0x0A01      // BGA(MSD3A10HX)
#define BD_MST072F_D01A_S       0x0A02      // MM Box

//U4
#define BD_MST098A_D01A_S       0x0A50
#define BD_MST098B_D01A_S       0x0A51
#define BD_MST098C_D01A_S       0x0A52
#define BD_MST098D_D01A_S       0x0A53
#define BD_MST098E_D01A         0x0A54
#define BD_MST098B_D01A         0x0A55
#define BD_ZDT300_V01           0x0A56
#define BD_MST098E_D01B         0x0A57
#define BD_MST098B_D01B         0x0A58

#define BD_CUS75_MBQ213A        0x0A60

// K1
#define BD_MST124A_D01A_S       0x0A70
#define BD_MST124A_D02A_S       0x0A71
#define BD_MST124A_D03A_S       0x0A72
#define BD_MST124B_D01A_S       0x0A80
#define BD_MST124B_D02A_S       0x0A81
#define BD_MST124B_D03A_S       0x0A82
#define BD_MST124SZ             0x0A83
#define BD_MST124B_D02A         0x0A84
#define BD_MST124C_D01A_S       0x0A85
#define BD_MST124D_D02A_S       0x0A86
#define BD_MST124E_D01A_S       0x0A87 // U02 156 Pin
#define BD_MST124E_D01A_SZ      0x0A88
#define BD_MST124D_D01A         0x0A89

// SZ board
#define BD_SHENZHEN_01          0x0120
#define BD_MSD109CL_11C         0x0121
#define BD_MSD109CL_20A         0x0122
#define BD_MSD109CL_30A         0x0123
#define BD_MSD109CL_CTV         0x0124
#define BD_MSD109CL_MTC         0x0125
#define BD_MSD109CL_HAI         0x0126
#define BD_MSD109CL_KON         0x0127
#define BD_MSD109CL_PRI         0x0128
#define BD_MSD189CL_KON         0x0129
#define BD_MSD189CL_10A         0x012A
#define BD_MSD106CL_12A         0x012B
#define BD_MSD119CL_PRI         0x012C
#define BD_MSD109CL_ALC         0x012D // base on BD_MSD109CL_11C
#define BD_MSD119CL_ALC         0x012E // base on BD_MSD189CL_10A
#define BD_MSD189CL_HIS         0x012F
#define BD_MSD119CL_CTV         0x0130
#define BD_MSD189CL_TCL         0x0131
#define BD_MSD106CL_PRI         0x0132
#define BD_MSD119CL_PRI_AU      0x0133
#define BD_MSD109CL_HAI2        0x0134
#define BD_MSD109CL_HAI2_HF     0x0135
#define BD_MSD209_HAI           0x0136
#define BD_MSD209_HIS           0x0137 // base on BD_MST052E_D01A
#define BD_MST064D_D01A_S_SBTVD_SZ  0x0138
#define BD_MST256A_TT2_10A      0x0139
#define BD_MST064F_D01B_SZ      0x013A
#define BD_MST256A_TT2_20A      0x013B
#define BD_MSD256_T2_10A        0x013C
#define BD_MST556A_T2_10A       0x013D
#define BD_MST556A_T2_10A_HX    0x013E
#define BD_SHENZHEN_END         0x01FF

// Others
#define BD_P_001A               0x0200
#define BD_CP_001A              0x0210
#define BD_CUS05KS_01           0x0300
#define BD_CUS05KS_02           0x0301

#define BD_CUS21SH_01           0x0400
#define BD_CUS22T_01            0x0500

#define BD_JC_328               0x0600
#define BD_CUS09JN_JC168MS      0x0601
#define BD_CUS16TA_01           0x0700

#define BD_CUS30BK_190R         0x0800

#define BD_UNKNOWN              0xFFFF

//------------------------------MS_PROJECT_TYPE_SEL-------------------------------
#define PRJ_CUS21SH_GEN             0x2100 // customer code: 0x21 (CUS21SH), project code: 0x00 (General)

#define PRJ_CUS22T_GEN              0x2200 // customer code: 0x22 (CUS22T), project code: 0x00 (General)
#define PRJ_CUS22T_DVBT             0x2201 // customer code: 0x22 (CUS22T), project code: 0x01 (DVBT)

#define PRJ_CUS24QSD_GEN            0x2400 // customer code: 0x24 (CUS24QSD), project code: 0x00 (General)

#define PRJ_UNKNOWN                 0xFFFF

#define PRJ_CUS_CODE_MASK           0xFF00
#define IS_CUS_CODE(x)              ( (MS_PROJECT_TYPE_SEL & PRJ_CUS_CODE_MASK) == ((x) & PRJ_CUS_CODE_MASK) )

//===============================================
#define EVENT_DV                0
#define EVENT_PV                1
#define EVENT_PQ                2
#define EVENT_MP                3

#define BOOT_VER_EVENT          EVENT_DV
#define BOOT_VER_NUM            1

#define SW_VER_EVENT            EVENT_DV
#define SW_VER_NUM              0
#define HW_VER                  0
//===============================================

#define ENABLE_OD      0

#define ENABLE_MLINK   0

#define MS_PROJECT_TYPE_SEL     PRJ_UNKNOWN

#define MODEL_NAME              "DVBT-----"     // Used in imginfo.c. 9 characters.

////////////////////////////////////////////////////////////////////////////////
#define ENABLE_UART1_DEBUG    0

#if defined (CONFIG_KRONUS_AEON_51_MAU_128MB)
#define AEON_51_MAU_64MB           1
#else
#define AEON_51_MAU_64MB           0
#endif

#ifndef MS_BOARD_TYPE_SEL
#if defined (CONFIG_MSTAR_TITANIA_BD_MST087B_S7_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST087B_S7_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087B_S7M_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST087B_S7M_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087C_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST087C_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087C_D02A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST087C_D02A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087E_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST087E_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087E_D01A)
    #define MS_BOARD_TYPE_SEL       BD_MST087E_D01A
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087F_D01A)
    #define MS_BOARD_TYPE_SEL       BD_MST087F_D01A
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST090A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST090A_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST090B_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST090B_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST090C_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST090C_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_GP2_DEMO1)
    #define MS_BOARD_TYPE_SEL       BD_GP2_DEMO1
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST098A_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098B_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST098B_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098B_D01A)
    #define MS_BOARD_TYPE_SEL       BD_MST098B_D01A
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098B_D01B)
    #define MS_BOARD_TYPE_SEL       BD_MST098B_D01B
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098C_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST098C_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098D_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST098D_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098E_D01A)
    #define MS_BOARD_TYPE_SEL       BD_MST098E_D01A
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST098E_D01B)
    #define MS_BOARD_TYPE_SEL       BD_MST098E_D01B
#elif defined (CONFIG_MSTAR_TITANIA_BD_ZDT300_V01)
    #define MS_BOARD_TYPE_SEL       BD_ZDT300_V01
#elif defined (CONFIG_MSTAR_TITANIA_BD_CUS75_MBQ213A)
    #define MS_BOARD_TYPE_SEL       BD_CUS75_MBQ213A
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124A_D01A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124A_D02A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124A_D02A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124B_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124B_D01A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124B_D02A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124B_D02A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124B_D02A)
    #define MS_BOARD_TYPE_SEL       BD_MST124B_D02A
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124C_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124C_D01A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124D_D01A)
    #define MS_BOARD_TYPE_SEL       BD_MST124D_D01A
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124D_D02A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124D_D02A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124SZ)
    #define MS_BOARD_TYPE_SEL       BD_MST124SZ
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124E_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST124E_D01A_S
#elif defined (CONFIG_MSTAR_KRONUS_BD_MST124E_D01A_SZ)
    #define MS_BOARD_TYPE_SEL       BD_MST124E_D01A_SZ
#else
    #error "BOARD define not found"
#endif
#endif
//-------------------------------------------------------

#include "Enum_Device.h"

//------------------------------------------------------------------------------
// For build only
#define USE_SW_I2C      1
#define ENABLE          1
#define DISABLE         0
#define OBA2            0
#define _TEMP_PM_       0

//------------------------------------------------------------------------------
// SW feature configure header file

#if ( MS_BOARD_TYPE_SEL ==  BD_T3_FPGA_001 )
    #include "BD_T3_FPGA_001.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037A_D01A )
    #include "BD_MST037A_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037B_D01A )
    #include "bd_mst037b_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037C_D01A )
    #include "bd_mst037c_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037E_D01A )
    #include "bd_mst037e_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037F_C01A )
    #include "bd_mst037f_c01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037G_C01A )
    #include "bd_mst037G_c01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037H_D01A )
    #include "bd_mst037h_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037I_C01A )
    #include "bd_mst037I_C01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST037L_D01A )
    #include "bd_mst037L_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042A_D01A )
    #include "bd_mst042a_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042B_D01A )
    #include "bd_mst042b_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042F_D01A_S )
    #include "bd_mst042F_d01a_s.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042F_D01A )
    #include "bd_mst042F_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042H_D01A )
    #include "bd_mst042H_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042H_D02A )
    #include "bd_mst042H_d02a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042H_D02B )
    #include "bd_mst042H_d02b.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042K_D01A_S )
    #include "bd_mst042K_d01a_s.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042K_D01A )
    #include "bd_mst042K_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042K_D02A)
    #include "bd_mst042K_d02a.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042Q_D01A)
    #include "bd_mst042Q_d01a.h"
#elif (MS_BOARD_TYPE_SEL == BD_FPGA)
    #include "bd_fpga.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_CTV)
    #include "BD_MSD109CL_CTV.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_11C)
    #include "BD_MSD109CL_11C.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_ALC)
    #include "BD_MSD109CL_ALC.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_HAI)
    #include "BD_MSD109CL_HAI.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_MTC)
    #include "BD_MSD109CL_MTC.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_20A)
    #include "BD_MSD109CL_20A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_30A)
    #include "BD_MSD109CL_30A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD106CL_12A)
    #include "BD_MSD106CL_12A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_PRI)
    #include "BD_MSD109CL_PRI.h"
#elif (MS_BOARD_TYPE_SEL == BD_P_001A)
    #include "BD_P_001A.h"
#elif (MS_BOARD_TYPE_SEL == BD_CUS05KS_01)
    #include "BD_CUS05KS_01.h"
#elif (MS_BOARD_TYPE_SEL == BD_CUS05KS_02)
    #include "BD_CUS05KS_02.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD109CL_KON)
    #include "BD_MSD109CL_KON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD189CL_KON)
    #include "BD_MSD189CL_KON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD189CL_10A)
    #include "BD_MSD189CL_10A.h"
#elif (MS_BOARD_TYPE_SEL == BD_CUS21SH_01)
    #include "BD_CUS21SH_01.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042F_D01A_S_S4)
    #include "BD_MST042F_D01A_S_S4.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD119CL_PRI)
    #include "BD_MSD119CL_PRI.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052A_D01A_S)
    #include "BD_MST052A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052B_D01A_S)
    #include "BD_MST052B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052B_D01A)
    #include "BD_MST052B_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052D_D01A_S)
    #include "BD_MST052D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052D_D01A)
    #include "BD_MST052D_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052D_D01A_CH)
    #include "BD_MST052D_D01A_CH.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052F_D01A)
    #include "BD_MST052F_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052E_D01A)
    #include "BD_MST052E_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052I_D01A)
    #include "BD_MST052I_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055A_D01A_S)
    #include "BD_MST055A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055B_D01A_S)
    #include "BD_MST055B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055C_D01A_S)
    #include "BD_MST055C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055D_D01A_S)
    #include "BD_MST055D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055D_D01A)
    #include "BD_MST055D_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055D_C01A)
    #include "BD_MST055D_C01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST055E_D01A_S)
    #include "BD_MST055E_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST056B_D01A_S)
    #include "BD_MST056B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST_S5_DEMO_01)
    #include "BD_MST_S5_DEMO_01.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST_S6_DEMO_01)
    #include "BD_MST_S6_DEMO_01.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST035B_D01D_S4)
    #include "BD_MST035B_D01D.h"
#elif (MS_BOARD_TYPE_SEL ==BD_MST064A_D01A_S)
    #include "BD_MST064A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL ==BD_MST064A_D01C_S)
    #include "BD_MST064A_D01C_S.h"
#elif(MS_BOARD_TYPE_SEL == BD_JC_328)
    #include "BD_JC_328.h"
#elif(MS_BOARD_TYPE_SEL == BD_CUS09JN_JC168MS)
    #include "BD_CUS09JN_JC168MS.h"
#elif(MS_BOARD_TYPE_SEL == BD_CUS16TA_01)
    #include "BD_CUS16TA_01.h"
#elif(MS_BOARD_TYPE_SEL == BD_MST042C_D01A)
    #include "BD_MST042C_D01A.h"
#elif(MS_BOARD_TYPE_SEL == BD_MST052G_D01A_S)
    #include "BD_MST052G_D01A_S.h"
#elif(MS_BOARD_TYPE_SEL == BD_MST052G_D01A)
    #include "BD_MST052G_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD209_HAI)
    #include "BD_MSD209_HAI.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD209_HIS)
    #include "BD_MSD209_HIS.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST064B_D01B_S)
    #include "BD_MST064B_D01B_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST058B_D02A)
    #include "BD_MST058B_D02A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST052H_D01A_S)
    #include "BD_MST052H_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST064C_D01A_S)
    #include "BD_MST064C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST064D_D01A_S)
    #include "BD_MST064D_D01A_S.h"
#elif(MS_BOARD_TYPE_SEL == BD_MST064D_D01A_S_SBTVD_SZ)
    #include "BD_MST064D_D01A_S_SBTVD_SZ.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST064E_D01A)
    #include "BD_MST064E_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST064F_D01A)
    #include "BD_MST064F_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST072A_D01A_S)
    #include "BD_MST072A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST072A_D01A)
    #include "BD_MST072A_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST072B_D01B_S)
    #include "BD_MST072B_D01B_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST256A_TT2_10A)
    #include "BD_MST256A_TT2_10A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST256A_TT2_20A)
    #include "BD_MST256A_TT2_20A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST064F_D01B_SZ)
    #include "BD_MST064F_D01B_SZ.h"
#elif (MS_BOARD_TYPE_SEL == BD_MSD256_T2_10A)
    #include "BD_MSD256_T2_10A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST072C_D01A)
    #include "BD_MST072C_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST072D_D01A_S)
    #include "BD_MST072D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST072F_D01A_S)
    #include "BD_MST072F_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087A_D01A_S)
    #include "BD_MST087A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087B_S7M_D01A_S)
    #include "BD_MST087B_S7M_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087B_S7_D01A_S)
    #include "BD_MST087B_S7_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087C_D02A_S)
    #include "BD_MST087C_D02A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087C_D01A_S)
    #include "BD_MST087C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087D_D01A_S)
    #include "BD_MST087D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087E_D01A_S)
    #include "BD_MST087E_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087E_D01A)
    #include "BD_MST087E_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087F_D01A)
    #include "BD_MST087F_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST556A_T2_10A)
    #include "BD_MST556A_T2_10A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST556A_T2_10A_HX)
    #include "BD_MST556A_T2_10A_HX.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST090A_D01A_S)
    #include "BD_MST090A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST090B_D01A_S)
    #include "BD_MST090B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST090C_D01A_S)
    #include "BD_MST090C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098A_D01A_S)
    #include "BD_MST098A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098B_D01A_S)
    #include "BD_MST098B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098B_D01A)
    #include "BD_MST098B_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098B_D01B)
    #include "BD_MST098B_D01B.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098C_D01A_S)
    #include "BD_MST098C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098D_D01A_S)
    #include "BD_MST098D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098E_D01A)
    #include "BD_MST098E_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST098E_D01B)
    #include "BD_MST098E_D01B.h"
#elif (MS_BOARD_TYPE_SEL == BD_ZDT300_V01)
    #include "BD_ZDT300_V01.h"
#elif (MS_BOARD_TYPE_SEL == BD_CUS75_MBQ213A)
    #include "BD_CUS75_MBQ213A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124A_D01A_S)
    #include "BD_MST124A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124A_D02A_S)
    #include "BD_MST124A_D02A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124B_D01A_S)
    #include "BD_MST124B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124B_D02A_S)
    #include "BD_MST124B_D02A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124B_D02A)
    #include "BD_MST124B_D02A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124C_D01A_S)
    #include "BD_MST124C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124D_D01A)
    #include "BD_MST124D_D01A.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124D_D02A_S)
    #include "BD_MST124D_D02A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124SZ)
    #include "BD_MST124SZ.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124E_D01A_S)
    #include "BD_MST124E_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST124E_D01A_SZ)
    #include "BD_MST124E_D01A_SZ.h"
#else
    #error Unknow board type
#endif

//------ SYSTEM MEMORY MAP ---------------------------------------------------------
#include "mmap/MMap.h"

//------------------------------------------------------------------------------
// The file can fix compile error if some board definition didn't define

// TODO:

    // should always place in the end of Board.h; no move!
    #define XMODEM_DWNLD_ENABLE      0
    #define XMODEM_1K                0

//------PCI_PORT_FUNCTION---------------------------------------------------------
#define NO_PCI_PORT                 0x00
#define PCI_PORT_IS_GPIO            0x01
#define PCI_PORT_IS_CARDREADER      0x02
#define ATCON_PORT                  0x03

#define IS_GPIO_PIN                 0x00
#define IS_PWM_PIN                  0x01

//PWM0~3 mode
#define NORMAL_MODE                 0
#define ENHANCE_MODE                1

//------DMA TYPE------------------------------------------------------------------
#define DRAM_GE_DMA                 0
#define DRAM_W1_DMA                 1
#define DRAM_BYTEDMA                2
#define DRAM_DMATYPE                DRAM_BYTEDMA//DRAM_W1_DMA

//------Sub Micro-----------------------------------------------------------------
#ifndef EXT_SUBMCU_TYPE
#define EXT_SUBMCU_TYPE             EXT_SUBMCU_NONE
#endif

//------------------------------ Board Default -----------------------------------
#ifndef I2C_IO_EXPANDER_TYPE
#define I2C_IO_EXPANDER_TYPE        I2C_IO_EXPANDER_NONE
#endif

#ifndef USE_SW_I2C
#define USE_SW_I2C                  1
#endif

#define ENABLE_TWO_FLASH_BAK        0

#endif // _BOARD_H_

