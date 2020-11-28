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



#define  DDR2_INTERFACE_QFP          0
#define  DDR2_INTERFACE_BGA          1
#define  DDR3_INTERFACE_BGA          2
#define  DDR2_INTERFACE_BGA_4X_MODE  3

#define DDR3_MIU0_16_MIU1_16    0
#define DDR3_MIU0_32_MIU1_16    1
#define DDR3_MIU0_32_MIU1_16_By_8BIT    2

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

//S7LD
#define BD_MST090A_D01A_S       0x0750
#define BD_MST090B_D01A_S       0x0751
#define BD_MST090C_D01A_S       0x0752
#define BD_MSD380B_D01A         0x0753
#define BD_MST090D_D01A_S       0x0754
#define BD_MST090E_D01A_S       0x0755
#define BD_MST090F_C01A         0x0756
//S8
#define BD_MST093A_D01A_S       0x0757
#define BD_MST087F_D01A_T8      0x0758
#define BD_MST105A_D01A_S       0x0759
#define BD_MST105B_D01A_S       0x075A
#define BD_MST105C_D01A_S       0x075B
#define BD_MST105D_D01A_S       0x075C
#define BD_MST116A_D01A_S       0x075D

// A2
#define BD_MST105C_D01A_A2      0x075F
#define BD_AMBER2_FPGA          0x0760

// A5
#define BD_MST105C_D01A_A5      0x0761
#define BD_AMBER5_FPGA          0x0762
#define BD_MST127A_D01A_S_A5    0x0763
#define BD_MST129A_D01A_S       0x0764
#define BD_MST129B_D01A_S       0x0765
#define BD_MST129C_D01A_S       0x0766
#define BD_MST129D_D01A_S       0x0767
#define BD_MST129E_D01A_S       0x0768
#define BD_MST016B_10AA5_11165  0x769

#define BD_UNKNOWN              0xFFFF

//------------------------------MS_PROJECT_TYPE_SEL-------------------------------
#define PRJ_CUS21SH_GEN         0x2100 // customer code: 0x21 (CUS21SH), project code: 0x00 (General)

#define PRJ_CUS22T_GEN          0x2200 // customer code: 0x22 (CUS22T), project code: 0x00 (General)
#define PRJ_CUS22T_DVBT         0x2201 // customer code: 0x22 (CUS22T), project code: 0x01 (DVBT)

#define PRJ_CUS24QSD_GEN        0x2400 // customer code: 0x24 (CUS24QSD), project code: 0x00 (General)

#define PRJ_UNKNOWN             0xFFFF

#define PRJ_CUS_CODE_MASK       0xFF00
#define IS_CUS_CODE(x)          ( (MS_PROJECT_TYPE_SEL & PRJ_CUS_CODE_MASK) == ((x) & PRJ_CUS_CODE_MASK) )

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

#if defined (CONFIG_TITANIA4_AEON_51_MAU_64MB)
#define AEON_51_MAU_64MB           1
#else
#define AEON_51_MAU_64MB           0
#endif

#ifndef MS_BOARD_TYPE_SEL
#if defined (CONFIG_MSTAR_TITANIA_BD_MST093A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST093A_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST087F_D01A_T8)
    #define MS_BOARD_TYPE_SEL       BD_MST087F_D01A_T8
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST105A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST105A_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST105B_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST105B_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST105C_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST105C_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST105D_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST105D_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST116A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST116A_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST105C_D01A_A2)
    #define MS_BOARD_TYPE_SEL       BD_MST105C_D01A_A2
#elif defined (CONFIG_MSTAR_TITANIA_BD_FPGA)
    #define MS_BOARD_TYPE_SEL       BD_AMBER5_FPGA
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST105C_D01A_A5)
    #define MS_BOARD_TYPE_SEL       BD_MST105C_D01A_A5
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST127A_D01A_S_A5)
    #define MS_BOARD_TYPE_SEL       BD_MST127A_D01A_S_A5
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST129A_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST129A_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST129B_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST129B_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST129C_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST129C_D01A_S
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST129D_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST129D_D01A_S    
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST129E_D01A_S)
    #define MS_BOARD_TYPE_SEL       BD_MST129E_D01A_S    
#elif defined (CONFIG_MSTAR_TITANIA_BD_MST016B_10AA5_11165)
    #define MS_BOARD_TYPE_SEL       BD_MST016B_10AA5_11165
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

#if (MS_BOARD_TYPE_SEL == BD_MST093A_D01A_S)
    #include "BD_MST093A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST087F_D01A_T8)
    #include "BD_MST087F_D01A_T8.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST105A_D01A_S)
    #include "BD_MST105A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST105B_D01A_S)
    #include "BD_MST105B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST105C_D01A_S)
    #include "BD_MST105C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST105D_D01A_S)
    #include "BD_MST105D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST116A_D01A_S)
    #include "BD_MST116A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST105C_D01A_A2)
    #include "BD_MST105C_D01A_A2.h"
#elif (MS_BOARD_TYPE_SEL == BD_AMBER2_FPGA)
    #include "BD_AMBER2_FPGA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST105C_D01A_A5)
    #include "BD_MST105C_D01A_A5.h"
#elif (MS_BOARD_TYPE_SEL == BD_AMBER5_FPGA)
    #include "BD_AMBER5_FPGA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST127A_D01A_S_A5)
    #include "BD_MST127A_D01A_S_A5.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST129A_D01A_S)
    #include "BD_MST129A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST129B_D01A_S)
    #include "BD_MST129B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST129C_D01A_S)
    #include "BD_MST129C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST129D_D01A_S)
    #include "BD_MST129D_D01A_S.h"    
#elif (MS_BOARD_TYPE_SEL == BD_MST129E_D01A_S)
    #include "BD_MST129E_D01A_S.h"    
#elif (MS_BOARD_TYPE_SEL == BD_MST016B_10AA5_11165)
    #include "BD_MST016B_10AA5_11165.h"
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


#ifndef BD_LVDS_CONNECT_TYPE
#define BD_LVDS_CONNECT_TYPE                0x00
#endif

#endif // _BOARD_H_
