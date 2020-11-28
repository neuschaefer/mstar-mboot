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
#ifndef __SD_CLIPPERS_UBOOT__
#define __SD_CLIPPERS_UBOOT__

//#include <string.h>

#define BIT00 0x01
#define BIT01 0x02
#define BIT02 0x04
#define BIT03 0x08
#define BIT04 0x10
#define BIT05 0x20
#define BIT06 0x40
#define BIT07 0x80

#define WBIT00 0x0001
#define WBIT01 0x0002
#define WBIT02 0x0004
#define WBIT03 0x0008
#define WBIT04 0x0010
#define WBIT05 0x0020
#define WBIT06 0x0040
#define WBIT07 0x0080
#define WBIT08 0x0100
#define WBIT09 0x0200
#define WBIT10 0x0400
#define WBIT11 0x0800
#define WBIT12 0x1000
#define WBIT13 0x2000
#define WBIT14 0x4000
#define WBIT15 0x8000

#define BY_PASS_MODE  1
//#define _8BIT_MARCO  1
//#define SDR_MODE    0

//=====================================================
// HW registers
//=====================================================
#define REG_OFFSET_SHIFT_BITS           2

#define REG_FCIE_U16(Reg_Addr)          (*(volatile U16*)(Reg_Addr))
#define GET_REG_ADDR(x, y)              ((x)+((y) << REG_OFFSET_SHIFT_BITS))

#define REG_FCIE(reg_addr)              REG_FCIE_U16(reg_addr)
#define REG_FCIE_W(reg_addr, val)       REG_FCIE(reg_addr) = (val)
#define REG_FCIE_R(reg_addr, val)       val = REG_FCIE(reg_addr)
#define REG_FCIE_SETBIT(reg_addr, val)  REG_FCIE(reg_addr) |= (val)
#define REG_FCIE_CLRBIT(reg_addr, val)  REG_FCIE(reg_addr) &= ~(val)
#define REG_FCIE_W1C(reg_addr, val)     REG_FCIE_W(reg_addr, REG_FCIE(reg_addr)&(val))

#define FCIE_RIU_W16(addr,value) *((volatile U16*)(addr)) = (value)
#define FCIE_RIU_R16(addr)       *((volatile U16*)(addr))
// read modify write 16 bits register macro
#define FCIE_RIU_16_ON(addr,value) FCIE_RIU_W16(addr, FCIE_RIU_R16(addr)|(value))
#define FCIE_RIU_16_OF(addr,value) FCIE_RIU_W16(addr, FCIE_RIU_R16(addr)&(~(value)))

//------------------------------
//#define RIU_PM_BASE                     0xFD000000
//#define RIU_BASE                        0xFD200000
#define RIU_PM_BASE             0x1F000000
#define RIU_BASE                0x1F200000

#define REG_BANK_FCIE0                  0x10780 // (120Fh - 1000h) x 80h
#define REG_BANK_FCIE1                  (REG_BANK_FCIE0 + 0x20)
#define REG_BANK_FCIE2                  0x11400 // (1228h - 1000h) x 80h
#define REG_BANK_CRC                    0x8A40
#define REG_BANK_POWER_SAVE             0x11480 // (1229h - 1000h) x 80h

#define FCIE0_BASE                      GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE0)
#define FCIE1_BASE                      GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE1)
#define FCIE2_BASE                      GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2)
#define FCIE_CRC_BASE                   GET_REG_ADDR(RIU_BASE, REG_BANK_CRC)
#define FCIE_POWEER_SAVE_MODE_BASE      GET_REG_ADDR(RIU_BASE, REG_BANK_POWER_SAVE)

#define FCIE_REG_BASE_ADDR              FCIE0_BASE
#define FCIE_CMDFIFO_BASE_ADDR          FCIE1_BASE
#define FCIE_CIFD_BASE_ADDR             FCIE2_BASE
//#define FCIE_CMDFIFO_BASE_ADDR          GET_REG_ADDR(FCIE0_BASE, 0x20)

#define FCIE_NC_WBUF_CIFD_BASE          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2)
#define FCIE_NC_RBUF_CIFD_BASE          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2 + 0x20)
#define FCIE_NC_CRCBUF_CIFD_BASE          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2 + 0x40)

#define SD_USE_FCIE5   1

#include "drvFCIE5_reg.h"

#define	REG_BANK_GPIO 			GET_REG_ADDR(RIU_BASE,0x1580)
#define   SD_GPIO_29                 	GET_REG_ADDR(REG_BANK_GPIO, 0x29)
#define   SD_GPIO_2A                 	GET_REG_ADDR(REG_BANK_GPIO, 0x2A)

//--------------------------------clock gen------------------------------------
#define REG_BANK_CLKGEN0                0x0580	// (0x100B - 0x1000) x 80h
#define CLKGEN0_BASE                    GET_REG_ADDR(RIU_BASE, REG_BANK_CLKGEN0)

//--------------------------------chiptop--------------------------------------
#define REG_BANK_CHIPTOP                0x0F00	// (0x101E - 0x1000) x 80h
#define PAD_CHIPTOP_BASE                GET_REG_ADDR(RIU_BASE, REG_BANK_CHIPTOP)

#define reg_chiptop_0x50                GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x50)
#define BIT_ALL_PAD_IN                  BIT15

#define reg_chiptop_0x6E                GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x6E)

#define FCIE_OffShift           2

#define RIU_BASE_CLKGEN0        (RIU_BASE+(0x0580U<<FCIE_OffShift))
#define RIU_BASE_CHIPTOP        (RIU_BASE+(0x0F00U<<FCIE_OffShift))
#define RIU_BASE_FCIE           (RIU_BASE+(0x10780<<FCIE_OffShift))
#define RIU_BASE_FCIE1          (RIU_BASE+(0x107E0<<FCIE_OffShift))
#define RIU_BASE_FCIE2          (RIU_BASE+(0x11400<<FCIE_OffShift))
#define SDIO_PLL_BASE			(RIU_BASE+(0x11F00<<FCIE_OffShift)) // 23E x 80
#define RIU_CHIPGPIO_BASE		(RIU_BASE+(0x1580<<FCIE_OffShift)) //  2B x 80

#define CHIPGPIO_00				(RIU_CHIPGPIO_BASE+ (0x00 << FCIE_OffShift))
#define CHIPGPIO_01				(RIU_CHIPGPIO_BASE+ (0x01 << FCIE_OffShift))

#define CHIPTOP_0C             (RIU_BASE_CHIPTOP+ (0x0c << FCIE_OffShift))
#define CHIPTOP_42             (RIU_BASE_CHIPTOP+ (0x42 << FCIE_OffShift))
#define CHIPTOP_43             (RIU_BASE_CHIPTOP+ (0x43 << FCIE_OffShift))
#define CHIPTOP_4F             (RIU_BASE_CHIPTOP+ (0x4F << FCIE_OffShift))
#define CHIPTOP_50             (RIU_BASE_CHIPTOP+ (0x50 << FCIE_OffShift))
#define CHIPTOP_5A             (RIU_BASE_CHIPTOP+ (0x5A << FCIE_OffShift))
#define CHIPTOP_5B             (RIU_BASE_CHIPTOP+ (0x5B << FCIE_OffShift))
#define CHIPTOP_7B             (RIU_BASE_CHIPTOP+ (0x7B << FCIE_OffShift))

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                               CLKGEN
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#define REG_CLK_SDIO            (RIU_BASE_CLKGEN0+(0x69<<FCIE_OffShift))

#define BIT_SDIO_CLK_GATING             BIT0
#define BIT_SDIO_CLK_INVERSE            BIT1
#define BIT_CLKGEN_SDIO_MASK            (BIT5|BIT4|BIT3|BIT2)
#define BIT_SDIO_CLK_SRC_SEL            BIT6 // 0: clk_xtal 12M, 1: clk_nfie_p1

//#define REG_CLK_EMMC            (RIU_BASE_CLKGEN0+(0x31<<FCIE_OffShift))
#define REG_CLK_65			(RIU_BASE_CLKGEN0+(0x65<<FCIE_OffShift))
#define REG_CLK_64			(RIU_BASE_CLKGEN0+(0x64<<FCIE_OffShift))
#define REG_CLK_69			(RIU_BASE_CLKGEN0+(0x69<<FCIE_OffShift))

//--------------------------------sdio pll--------------------------------------
//#define REG_BANK_SDIO_PLL               0x11F00	// (0x123E - 0x1000) x 80h
//#define SDIO_PLL_BASE                   GET_REG_ADDR(RIU_BASE, REG_BANK_SDIO_PLL)

#define SDIOPLL_10   	   (SDIO_PLL_BASE+ (0x10 << FCIE_OffShift))
#define SDIOPLL_1D   	   (SDIO_PLL_BASE+ (0x1D << FCIE_OffShift))
#define SDIOPLL_36   	   (SDIO_PLL_BASE+ (0x36 << FCIE_OffShift))

#define R_SDIO_PLL_0x68					GET_REG_ADDR(SDIO_PLL_BASE, 0x68)
#define reg_sdiopll_0x69                GET_REG_ADDR(SDIO_PLL_BASE, 0x69)
#define R_SDIO_PLL_0x6A					GET_REG_ADDR(SDIO_PLL_BASE, 0x6A)
#define R_SDIO_PLL_0x6B					GET_REG_ADDR(SDIO_PLL_BASE, 0x6B)
#define reg_sdiopll_0x6c                GET_REG_ADDR(SDIO_PLL_BASE, 0x6c)
#define reg_sdiopll_0x6d                GET_REG_ADDR(SDIO_PLL_BASE, 0x6d)
#define reg_sdiopll_0x6f                GET_REG_ADDR(SDIO_PLL_BASE, 0x6f)
#define reg_sdiopll_0x70                GET_REG_ADDR(SDIO_PLL_BASE, 0x70)
#define reg_sdiopll_0x71                GET_REG_ADDR(SDIO_PLL_BASE, 0x71)
#define reg_sdiopll_0x73                GET_REG_ADDR(SDIO_PLL_BASE, 0x73)
#define reg_sdiopll_0x74                GET_REG_ADDR(SDIO_PLL_BASE, 0x74)


#define BIT_TUNE_SHOT_OFFSET_MASK       (BIT4|BIT5|BIT6|BIT7)
#define BIT_TUNE_SHOT_OFFSET_SHIFT      4

//--------------------------------macro define---------------------------------
#define ENABLE_8BIT_MACRO               0

#if !(defined(ENABLE_8BIT_MACRO) && ENABLE_8BIT_MACRO)
#define ENABLE_32BIT_MACRO              1
#endif

//--------------------------------clock gen------------------------------------

#define BIT_FCIE_CLK_XTAL			0x00
#define BIT_FCIE_CLK_20M			0x01
#define BIT_FCIE_CLK_32M			0x02
#define BIT_FCIE_CLK_36M			0x03
#define BIT_FCIE_CLK_40M			0x04
#define BIT_FCIE_CLK_43M			0x05
#define BIT_FCIE_CLK_54M			0x06
#define BIT_FCIE_CLK_62M			0x07
#define BIT_FCIE_CLK_72M			0x08
#define BIT_FCIE_CLK_86M			0x09
#define BIT_FCIE_CLK_EMMC_PLL_1X	0x0B // 8 bits macro & 32 bit macro HS200
#define BIT_FCIE_CLK_EMMC_PLL_2X	0x0C // 32 bit macroDDR & HS400
#define BIT_FCIE_CLK_300K			0x0D
#define BIT_FCIE_CLK_XTAL2			0x0E
#define BIT_FCIE_CLK_48M			0x0F

#define BIT_FCIE_CLK_52M                0x10 // emmc pll use only
#define BIT_FCIE_CLK_120M               0x11 // emmc pll use only
#define BIT_FCIE_CLK_140M               0x12 // emmc pll use only
#define BIT_FCIE_CLK_160M               0x13 // emmc pll use only
#define BIT_FCIE_CLK_200M               0x14 // emmc pll use only

#define eMMC_PLL_FLAG                   0x80
#define eMMC_PLL_CLK__20M               (0x01|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__27M               (0x02|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__32M               (0x03|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__36M               (0x04|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__40M               (0x05|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__48M               (0x06|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__52M               (0x07|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__62M               (0x08|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__72M               (0x09|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__80M               (0x0A|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__86M               (0x0B|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_100M               (0x0C|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_120M               (0x0D|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_140M               (0x0E|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_160M               (0x0F|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_200M               (0x10|eMMC_PLL_FLAG)



#define eMMC_FCIE_VALID_CLK_CNT         1// FIXME

#define PLL_SKEW4_CNT               9
#define MIN_OK_SKEW_CNT             5



#define REG_BANK_TIMER1                 0x1800
#define TIMER1_BASE                     GET_REG_ADDR(RIU_PM_BASE, REG_BANK_TIMER1)

#define TIMER1_ENABLE                   GET_REG_ADDR(TIMER1_BASE, 0x20)
#define TIMER1_HIT                      GET_REG_ADDR(TIMER1_BASE, 0x21)
#define TIMER1_MAX_LOW                  GET_REG_ADDR(TIMER1_BASE, 0x22)
#define TIMER1_MAX_HIGH                 GET_REG_ADDR(TIMER1_BASE, 0x23)
#define TIMER1_CAP_LOW                  GET_REG_ADDR(TIMER1_BASE, 0x24)
#define TIMER1_CAP_HIGH                 GET_REG_ADDR(TIMER1_BASE, 0x25)


//=====================================================
// API declarations
//=====================================================
#define eMMC_HW_TIMER_MHZ               12000000//12MHz  [FIXME]

#define FCIE_eMMC_MACRO_8BIT            0
#define FCIE_eMMC_MACRO_32BIT           1

#define FCIE_eMMC_DISABLE               0
#define FCIE_eMMC_DDR                   1
#define FCIE_eMMC_SDR                   2
#define FCIE_eMMC_BYPASS                3 // never use this
#define FCIE_eMMC_TMUX                  4
#define FCIE_eMMC_HS200                 5
#define FCIE_eMMC_HS400                 6
#define FCIE_eMMC_SDR_GPIO              7
#define FCIE_eMMC_HS400_DS              8

#define eMMC_BOOT_PART_W                BIT0
#define eMMC_BOOT_PART_R                BIT1




//=====================================================
// Driver configs
//=====================================================
// [CAUTION]: to verify IP and HAL code, defaut 0
#define IF_IP_VERIFY                    1 // [FIXME] -->

#define FCIE_EMMC_BOOT_MODE             0

#if defined(FCIE_EMMC_BOOT_MODE) && FCIE_EMMC_BOOT_MODE
#define FCIE_EMMC_BOOT_TO_SRAM          0
#endif

#define WRITE_TEST_BOOT_CODE            0

#define DELAY_FOR_DEBUGGING_BUS         0
#define DELAY_FOR_BRIAN                 0

#define FCIE_GPIO_PAD_VERIFY            1
#define FCIE_SDR_FLASH_MACRO_VERIFY     1
#define FCIE_DDR52_VERIFY               1
#define FCIE_HS200_VERIFY               1
#define FCIE_HS400_VERIFY               1
#define FCIE_REGRESSION_TEST            0

// [CAUTION]: to detect DDR timiing parameters, only for DL
#define IF_DETECT_eMMC_DDR_TIMING       1
#define eMMC_IF_DDRT_TUNING()           (g_eMMCDrv.u32_DrvFlag&DRV_FLAG_DDR_TUNING)

// need to eMMC_pads_switch
// need to eMMC_clock_setting
#define IF_FCIE_SHARE_IP                1

//------------------------------
#define FICE_BYTE_MODE_ENABLE           1 // always 1
#define ENABLE_eMMC_INTERRUPT_MODE      0
#define ENABLE_eMMC_RIU_MODE            0 // for debug cache issue
#define ENABLE_eMMC_ATOP                0 // after einstein 2013-JUN-14 might has this feature
#define ENABLE_eMMC_HS200               0 // after einstein 2013-JUN-14 might has this feature
#define ENABLE_eMMC_HS400               1

#if !FCIE_GPIO_PAD_VERIFY
#undef ENABLE_eMMC_RIU_MODE
#define ENABLE_eMMC_RIU_MODE            0
#endif

#if ENABLE_eMMC_RIU_MODE
#undef IF_DETECT_eMMC_DDR_TIMING
#define IF_DETECT_eMMC_DDR_TIMING       0 // RIU mode can NOT use DDR
#endif
// <-- [FIXME]

//------------------------------
#define eMMC_FEATURE_RELIABLE_WRITE     1
#if eMMC_UPDATE_FIRMWARE
#undef  eMMC_FEATURE_RELIABLE_WRITE
#define eMMC_FEATURE_RELIABLE_WRITE     0
#endif

//=====================================================
// unit for HW Timer delay (unit of us)
//=====================================================

#define HW_TIMER_DELAY_1us              1
#define HW_TIMER_DELAY_5us              1
#define HW_TIMER_DELAY_10us             1
#define HW_TIMER_DELAY_100us            1
#define HW_TIMER_DELAY_500us            1
#define HW_TIMER_DELAY_1ms              (1 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms              (5    * HW_TIMER_DELAY_1ms) / 3
#define HW_TIMER_DELAY_10ms             (10   * HW_TIMER_DELAY_1ms) / 3
#define HW_TIMER_DELAY_100ms            (100  * HW_TIMER_DELAY_1ms) / 3
#define HW_TIMER_DELAY_500ms            (500  * HW_TIMER_DELAY_1ms) / 3
#define HW_TIMER_DELAY_1s               (1000 * HW_TIMER_DELAY_1ms) / 3

/*
#define HW_TIMER_DELAY_1us              1
#define HW_TIMER_DELAY_5us              5
#define HW_TIMER_DELAY_10us             10
#define HW_TIMER_DELAY_100us            100
#define HW_TIMER_DELAY_500us            500
#define HW_TIMER_DELAY_1ms              (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms              (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms             (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms            (100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms            (500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s               (1000 * HW_TIMER_DELAY_1ms)
*/

//=====================================================
// set FCIE clock
//=====================================================
// [FIXME] -->
#define FCIE_SLOWEST_CLK                BIT_FCIE_CLK_300K
#define FCIE_SLOW_CLK                   BIT_FCIE_CLK_48M
#define FCIE_DEFAULT_CLK                BIT_FCIE_CLK_48M // BIT_FCIE_CLK_36M
#define FCIE_HS200_CLK                  BIT_FCIE_CLK_200M //BIT_FCIE_CLK_52M
// <-- [FIXME]
//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS              4// 8 bytes width [FIXME]
/*
 * Important:
 * The following buffers should be large enough for a whole eMMC block
 */
// FIXME, this is only for verifing IP
#define DMA_W_ADDR                      0x00300000
#define DMA_R_ADDR                      0x00600000
#define DMA_W_SPARE_ADDR                0x00900000
#define DMA_R_SPARE_ADDR                0x00A80000
#define DMA_BAD_BLK_BUF                 0x00C00000

int printf(const char *format, ...);


//=====================================================
// misc
//=====================================================
//#define BIG_ENDIAN
#define LITTLE_ENDIAN

#define BIT_DQS_MODE_MASK               (BIT0|BIT1|BIT2)
#define BIT_DQS_MODE_SHIFT              0

//--------------------------------sdio pll--------------------------------------

#define REG_EMMC_PLL_RX01               GET_REG_ADDR(SDIO_PLL_BASE, 0x01)
#define reg_sdiopll_0x02                GET_REG_ADDR(SDIO_PLL_BASE, 0x02)
#define reg_sdiopll_0x03                GET_REG_ADDR(SDIO_PLL_BASE, 0x03)

#define BIT_SKEW1_MASK				    (BIT3|BIT2|BIT1|BIT0)
#define BIT_SKEW2_MASK				    (BIT7|BIT6|BIT5|BIT4)
#define BIT_SKEW3_MASK				    (BIT11|BIT10|BIT9|BIT8)
#define BIT_SKEW4_MASK				    (BIT15|BIT14|BIT13|BIT12)

#define reg_sdiopll_fbdiv               GET_REG_ADDR(SDIO_PLL_BASE, 0x04)
#define reg_sdiopll_pdiv                GET_REG_ADDR(SDIO_PLL_BASE, 0x05)
#define reg_emmc_pll_reset              GET_REG_ADDR(SDIO_PLL_BASE, 0x06)
#define reg_emmc_pll_test               GET_REG_ADDR(SDIO_PLL_BASE, 0x07)

#define reg_sdiopll_0x09                GET_REG_ADDR(SDIO_PLL_BASE, 0x09)

#define reg_ddfset_15_00                GET_REG_ADDR(SDIO_PLL_BASE, 0x18)
#define reg_ddfset_23_16                GET_REG_ADDR(SDIO_PLL_BASE, 0x19)
#define reg_emmc_test                   GET_REG_ADDR(SDIO_PLL_BASE, 0x1A)
#define reg_atop_patch                  GET_REG_ADDR(SDIO_PLL_BASE, 0x1C)
#define BIT_HS200_PATCH                 BIT0
#define BIT_HS_RSP_META_PATCH_HW        BIT2
#define BIT_HS_D0_META_PATCH_HW         BIT4
#define BIT_HS_DIN0_PATCH               BIT5
#define BIT_HS_EMMC_DQS_PATCH           BIT6
#define BIT_HS_RSP_MASK_PATCH           BIT7
#define BIT_DDR_RSP_PATCH               BIT8
#define BIT_ATOP_PATCH_MASK            (BIT0|BIT1|BIT2|BIT4|BIT5|BIT6|BIT7|BIT8)

#define reg_sdiopll_0x1a                GET_REG_ADDR(SDIO_PLL_BASE, 0x1a)
#define reg_sdiopll_0x1d                GET_REG_ADDR(SDIO_PLL_BASE, 0x1d)
#define reg_sdiopll_0x1e                GET_REG_ADDR(SDIO_PLL_BASE, 0x1e)
#define reg_sdiopll_0x1f                GET_REG_ADDR(SDIO_PLL_BASE, 0x1f)
#define reg_sdiopll_0x20                GET_REG_ADDR(SDIO_PLL_BASE, 0x20)
#define BIT_TRIG_LEVEL_MASK				0x01FF
#define BIT_TRIG_LEVEL_1				0x0007
#define BIT_TRIG_LEVEL_2				0x0038
#define BIT_TRIG_LEVEL_3				0x003F
#define BIT_TRIG_LEVEL_4				0x01C0
#define BIT_TRIG_LEVEL_5				0x01C7
#define BIT_TRIG_LEVEL_6				0x01F8
#define BIT_TRIG_LEVEL_7				0x01FF

#define REG_EMMC_PLL_RX30               GET_REG_ADDR(SDIO_PLL_BASE, 0x30)
#define REG_EMMC_PLL_RX32               GET_REG_ADDR(SDIO_PLL_BASE, 0x32)
#define REG_EMMC_PLL_RX33               GET_REG_ADDR(SDIO_PLL_BASE, 0x33)
#define REG_EMMC_PLL_RX34               GET_REG_ADDR(SDIO_PLL_BASE, 0x34)
//#define reg_sdiopll_0x03                  GET_REG_ADDR(SDIO_PLL_BASE, 0x3)
#define reg_sdiopll_0x1d                  GET_REG_ADDR(SDIO_PLL_BASE, 0x1d)
#define reg_sdiopll_0x36                GET_REG_ADDR(SDIO_PLL_BASE, 0x36)
#define reg_sdiopll_0x63                GET_REG_ADDR(SDIO_PLL_BASE, 0x63)
#define reg_sdiopll_0x68                GET_REG_ADDR(SDIO_PLL_BASE, 0x68)
#define reg_sdiopll_0x69                GET_REG_ADDR(SDIO_PLL_BASE, 0x69)
#define reg_sdiopll_0x6a                GET_REG_ADDR(SDIO_PLL_BASE, 0x6a)
#define reg_sdiopll_0x6b                GET_REG_ADDR(SDIO_PLL_BASE, 0x6b)
#define reg_sdiopll_0x6c                GET_REG_ADDR(SDIO_PLL_BASE, 0x6c)
#define reg_sdiopll_0x6d                GET_REG_ADDR(SDIO_PLL_BASE, 0x6d)
#define reg_sdiopll_0x6f                GET_REG_ADDR(SDIO_PLL_BASE, 0x6f)
#define reg_sdiopll_0x70                GET_REG_ADDR(SDIO_PLL_BASE, 0x70)
#define reg_sdiopll_0x71                GET_REG_ADDR(SDIO_PLL_BASE, 0x71)
#define reg_sdiopll_0x73                GET_REG_ADDR(SDIO_PLL_BASE, 0x73)
#define reg_sdiopll_0x74                GET_REG_ADDR(SDIO_PLL_BASE, 0x74)

/*
#define eMMC_PLL_FLAG                   	0x80
#define eMMC_PLL_CLK__20M               (0x01|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__27M               (0x02|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__32M               (0x03|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__36M               (0x04|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__40M               (0x05|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__48M               (0x06|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__52M               (0x07|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__62M               (0x08|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__72M               (0x09|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__80M               (0x0A|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK__86M               (0x0B|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_100M               (0x0C|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_120M               (0x0D|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_140M               (0x0E|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_160M               (0x0F|eMMC_PLL_FLAG)
#define eMMC_PLL_CLK_200M               (0x10|eMMC_PLL_FLAG)
*/

typedef struct _SKEWER {

	unsigned int u32LatchOKStart;
	unsigned int u32LatchOKEnd;
	unsigned int u32LatchBest;
	unsigned char u8_edge;

} SKEWER;

#endif /* __SD_CLIPPERS_UBOOT__ */


