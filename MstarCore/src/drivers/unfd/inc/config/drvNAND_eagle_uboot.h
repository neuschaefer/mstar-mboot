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
#ifndef __UNFD_EAGLE_LINUX_H__
#define __UNFD_EAGLE_LINUX_H__

//#include <asm/io.h>
#include <linux/string.h>
#include <common.h>
#include <jffs2/load_kernel.h>

#define REG_BANK_CLKGEN				(0x580)
#define REG_BANK_CHIPTOP			(0xF00)
#define REG_BANK_FCIE0				(0x8980)
#define REG_BANK_FCIE2				(0x8A00)
#define REG_BANK_TIMER0				(0x1800)

#define RIU_PM_BASE					0x1F000000
#define RIU_BASE					0x1F200000

#define MPLL_CLK_REG_BASE_ADDR		(RIU_BASE+(REG_BANK_CLKGEN<<REG_OFFSET_SHIFT_BITS))
#define CHIPTOP_REG_BASE_ADDR		(RIU_BASE+(REG_BANK_CHIPTOP<<REG_OFFSET_SHIFT_BITS))
#define FCIE_REG_BASE_ADDR			(RIU_BASE+(REG_BANK_FCIE0<<REG_OFFSET_SHIFT_BITS))
#define FCIE_NC_CIFD_BASE			(RIU_BASE+(REG_BANK_FCIE2<<REG_OFFSET_SHIFT_BITS))
#define TIMER0_REG_BASE_ADDR        (RIU_PM_BASE+(REG_BANK_TIMER0<<REG_OFFSET_SHIFT_BITS))

#define REG(Reg_Addr)				(*(volatile U16*)(Reg_Addr))
#define REG_OFFSET_SHIFT_BITS		2
#define GET_REG_ADDR(x, y)			(x+((y)<<REG_OFFSET_SHIFT_BITS))

#define REG_WRITE_UINT16(reg_addr, val)		REG(reg_addr) = val
#define REG_READ_UINT16(reg_addr, val)		val = REG(reg_addr)
#define HAL_WRITE_UINT16(reg_addr, val)		(REG(reg_addr) = val)
#define HAL_READ_UINT16(reg_addr, val)		val = REG(reg_addr)
#define REG_SET_BITS_UINT16(reg_addr, val)	REG(reg_addr) |= (val)
#define REG_CLR_BITS_UINT16(reg_addr, val)	REG(reg_addr) &= ~(val)
#define REG_W1C_BITS_UINT16(reg_addr, val)	REG_WRITE_UINT16(reg_addr, REG(reg_addr)&(val))

#define REG50_ECC_CTRL_INIT_VALUE	0

#define UNFD_ST_PLAT				0x80000000
#define IF_IP_VERIFY				0 // [CAUTION]: to verify IP and HAL code, defaut 0

// debug
#define FCIE3_DUMP_DEBUG_BUS		1

//FCIE4 DDR Nand
#define FCIE4_DDR					1

#define FCIE_LFSR					1

#define SPARE640B_CIFD512B_PATCH    1

#define REG_SDR_BYPASS_MODE			GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x43)

#define BIT_SD_USE_BYPASS			(BIT0)
#define BIT_FCIE2MACRO_SD_BYPASS	(BIT1)

#define GPIO_CTL_BASE				GET_REG_ADDR(RIU_BASE, REG_BANK_CHIPTOP) /*0x101E*/
#define REG_GPIO_DQS_EN             GET_REG_ADDR(GPIO_CTL_BASE, 0x6B)         /* 0x101E */
#define REG_GPIO_DQS_UL             GET_REG_ADDR(GPIO_CTL_BASE, 0x6C)         /* 0x101E */

#define REG_PCM_D_PE				GET_REG_ADDR(GPIO_CTL_BASE, 0x0C)
#define REG_PCM_A_PE				GET_REG_ADDR(GPIO_CTL_BASE, 0x41)
#define REG_PCM2_CD_N				GET_REG_ADDR(GPIO_CTL_BASE, 0x42)

#define REG_NAND_CS1_EN				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x50)
#define BIT_NAND_CS1_EN				BIT10


#define BIT_DQS_PULL_H              BIT8

#define NC_DQS_PULL_H()             REG_SET_BITS_UINT16(REG_GPIO_DQS_UL, BIT_DQS_PULL_H)
#define NC_DQS_PULL_L()             REG_CLR_BITS_UINT16(REG_GPIO_DQS_UL, BIT_DQS_PULL_H)

#define NAND_PAD_BYPASS_MODE	    1
#define NAND_PAD_TOGGLE_MODE	    2
#define NAND_PAD_ONFI_SYNC_MODE		3

#if (defined(FCIE4_DDR) && FCIE4_DDR)
#define NC_SET_DDR_MODE()           REG_WRITE_UINT16(NC_DDR_CTRL, pNandDrv->u16_Reg58_DDRCtrl);
#define NC_CLR_DDR_MODE()           REG_CLR_BITS_UINT16(NC_DDR_CTRL, BIT_DDR_MASM);
#else
#define NC_SET_DDR_MODE()
#define NC_CLR_DDR_MODE()
#endif

#if (defined(FCIE4_DDR) && FCIE4_DDR)
#define DQS_MODE_2P0T		0
#define DQS_MODE_1P5T		1
#define DQS_MODE_2P5T		2
#define DQS_MODE_0P0T		3
#define DQS_MODE_TABLE_CNT	4
#define DQS_MODE_SEARCH_TABLE {DQS_MODE_1P5T, DQS_MODE_0P0T, DQS_MODE_2P0T, DQS_MODE_2P5T}
#define DQS_MODE_TABLE		{DQS_MODE_0P0T, DQS_MODE_1P5T, DQS_MODE_2P0T, DQS_MODE_2P5T}

#define NC_INST_DELAY	1
#define NC_HWCMD_DELAY	1
#define NC_TRR_TCS		1
#define NC_TWHR_TCLHZ			1
#define NC_TCWAW_TADL			1

#define	NC_ONFI_DEFAULT_TRR 		12
#define	NC_ONFI_DEFAULT_TCS 		7
#define NC_ONFI_DEFAULT_TWW			8
#define NC_ONFI_DEFAULT_TWHR 		5
#define NC_ONFI_DEFAULT_TADL 		6
#define NC_ONFI_DEFAULT_TCWAW 		4
#define	NC_ONFI_DEFAULT_RX40CMD 	4
#define	NC_ONFI_DEFAULT_RX40ADR 	7
#define	NC_ONFI_DEFAULT_RX56 		10

#define	NC_TOGGLE_DEFAULT_TRR 		8
#define	NC_TOGGLE_DEFAULT_TCS 		6
#define NC_TOGGLE_DEFAULT_TWW 		7
#define	NC_TOGGLE_DEFAULT_TWHR 		5
#define	NC_TOGGLE_DEFAULT_TADL 		7
#define	NC_TOGGLE_DEFAULT_TCWAW 	2
#define	NC_TOGGLE_DEFAULT_RX40CMD 	4
#define	NC_TOGGLE_DEFAULT_RX40ADR 	5
#define	NC_TOGGLE_DEFAULT_RX56 		15

#define	NC_SDR_DEFAULT_TRR 			7
#define	NC_SDR_DEFAULT_TCS 			6
#define NC_SDR_DEFAULT_TWW			5
#define	NC_SDR_DEFAULT_TWHR 		4
#define	NC_SDR_DEFAULT_TADL 		8
#define	NC_SDR_DEFAULT_TCWAW 		2
#define	NC_SDR_DEFAULT_RX40CMD 		4
#define	NC_SDR_DEFAULT_RX40ADR 		5
#define	NC_SDR_DEFAULT_RX56 		5
#endif




#define NC_SEL_FCIE3            1
#if NC_SEL_FCIE3
#include "drvNAND_reg_v3.h"
#else
#error "Error! no FCIE registers selected."
#endif

#define IF_SPARE_AREA_DMA          1 // [CAUTION] 

#define IF_FCIE_SHARE_PINS          1 // 1: need to nand_pads_switch at HAL's functions.
#define IF_FCIE_SHARE_CLK         0 // 1: need to nand_clock_setting at HAL's functions.
#define IF_FCIE_SHARE_IP          0

#define ENABLE_NAND_INTERRUPT_MODE      0

#define NAND_DRIVER_ROM_VERSION       0 // to save code size
#define AUTO_FORMAT_FTL           0

#define ENABLE_CUS_READ_ENHANCEMENT     0

#define __VER_UNFD_FTL__          0
//=====================================================
// Nand Driver configs
//=====================================================
#define NAND_BUF_USE_STACK          0
#define NAND_ENV_FPGA           1
#define NAND_ENV_ASIC           2
#ifdef __FPGA_MODE__  // currently G1 don't care this macro, even in ROM code
#define NAND_DRIVER_ENV           NAND_ENV_FPGA
#else
#define NAND_DRIVER_ENV           NAND_ENV_ASIC
#endif

#define UNFD_CACHE_LINE           0x80
//=====================================================
// tool-chain attributes
//=====================================================
#define UNFD_PACK0
#define UNFD_PACK1              __attribute__((__packed__))
#define UNFD_ALIGN0
#define UNFD_ALIGN1             __attribute__((aligned(UNFD_CACHE_LINE)))

//=====================================================
// debug option
//=====================================================
#define NAND_TEST_IN_DESIGN         0      /* [CAUTION] */

#ifndef NAND_DEBUG_MSG
#define NAND_DEBUG_MSG            1
#endif

/* Define trace levels. */
#define UNFD_DEBUG_LEVEL_ERROR        (1)    /* Error condition debug messages. */
#define UNFD_DEBUG_LEVEL_WARNING      (2)    /* Warning condition debug messages. */
#define UNFD_DEBUG_LEVEL_HIGH       (3)    /* Debug messages (high debugging). */
#define UNFD_DEBUG_LEVEL_MEDIUM       (4)    /* Debug messages. */
#define UNFD_DEBUG_LEVEL_LOW        (5)    /* Debug messages (low debugging). */

/* Higer debug level means more verbose */
#ifndef UNFD_DEBUG_LEVEL
#define UNFD_DEBUG_LEVEL          UNFD_DEBUG_LEVEL_WARNING
#endif

extern int Disable_Err_log;
#if defined(NAND_DEBUG_MSG) && NAND_DEBUG_MSG
#define nand_print_tmt            //msPrintfFunc
#define nand_printf            printf
#define nand_debug(dbg_lv, tag, str, ...)       \
  do {                        \
    if (dbg_lv > UNFD_DEBUG_LEVEL || Disable_Err_log == 1)        \
      break;                  \
    else {                    \
	  if (dbg_lv == UNFD_DEBUG_LEVEL_ERROR) \
		nand_printf("NAND Err:");			\
      if (tag)                  \
      {                                       \
        nand_printf("[%s]\t",__func__);        \
        /*nand_print_tmt(__func__);*/       \
      }                                       \
                          \
      nand_printf(str, ##__VA_ARGS__);      \
      /*nand_print_tmt(str, ##__VA_ARGS__);*/     \
    }                     \
  } while(0)
#else /* NAND_DEBUG_MSG */
#define nand_printf(...)
#define nand_debug(enable, tag, str, ...) {}
#endif /* NAND_DEBUG_MSG */

static __inline void nand_assert(int condition)
{
  if (!condition) {

  }
}

#define nand_die() \
  do { \
    nand_printf(__func__); \
    nand_printf("\nUNFD Assert(%d)", __LINE__); \
    nand_assert(0); \
  } while(0);

#define nand_stop() \
  while(1)  nand_reset_WatchDog();

//=====================================================
// HW Timer for Delay
//=====================================================
#define TIMER0_ENABLE           GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x10)
#define TIMER0_HIT              GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x11)
#define TIMER0_MAX_LOW            GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x12)
#define TIMER0_MAX_HIGH           GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x13)
#define TIMER0_CAP_LOW            GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x14)
#define TIMER0_CAP_HIGH           GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x15)

#define HW_TIMER_DELAY_1us          1
#define HW_TIMER_DELAY_10us         10
#define HW_TIMER_DELAY_100us        100
#define HW_TIMER_DELAY_1ms          (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms          (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms         (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms        (100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms        (500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s         (1000 * HW_TIMER_DELAY_1ms)

#define NAND_SPEED_TEST             0

extern void delay_us( unsigned us );
extern U32  nand_hw_timer_delay(U32 u32usTick);

//=====================================================
// Pads Switch
//=====================================================
#define reg_allpad_in           GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x50)
#define reg_nf_en             	GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x0B)
#define REG_EMMC_CONFIG				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x5D)
#define REG_SD_CONFIG				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x0B)
#define REG_PCM_CONFIG				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x4F)

#define REG_LD_SPI_CONFIG			GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x5A)
#define REG_CIAD_CONFIG				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x64)
#define REG_MCUJTAGMODE				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x03)
#define REG_TS0_CONFIG				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x51)
#define REG_BT656_CTRL				GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x6F)

#define REG_SD_MODE_MASK			(BIT9|BIT8|BIT7|BIT6|BIT5|BIT4|BIT3|BIT2)
#define REG_PCM_CONFIG_MASK			(BIT14|BIT13)
#define REG_NAND_MODE_MASK		    (BIT14|BIT13|BIT12)
#define NAND_MODE1				    (BIT12)
#define NAND_MODE2				    (BIT13)
#define NAND_MODE3				    (BIT13|BIT12)
#define NAND_MODE4				    (BIT14)
#define NAND_MODE5				    (BIT14|BIT12)

extern U32 nand_pads_switch(U32 u32EnableFCIE);
extern U32 	nand_check_DDR_pad(void);

//=====================================================
// Analog Delay Cell
//=====================================================
//#define REG_ANALOG_DELAY_CELL			GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x61)
//#define BIT_ANALOG_DELAY_CELL_MASK		(BIT8|BIT7|BIT6|BIT5|BIT4)

//=====================================================
// Data and Control Strength 
//=====================================================

#define reg_fcie_data_strength  		GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x08)
#define reg_fcie_control_strength1  	GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x0C)
#define reg_fcie_control_strength2  	GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x0D)

//=====================================================
// set FCIE clock
//=====================================================
#define EMMC_CLK_MASK			(BIT12|BIT11|BIT10)
#define REG_CLK_EMMC			GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x31)

#define NFIE_CLK_MASK           (BIT6|BIT5|BIT4|BIT3|BIT2)
#define NFIE_CLK_GLITCH_FREE_EN (BIT6)
#define NFIE_CLK_XTAL           (0)
#define NFIE_CLK_20M            (BIT6|BIT2)
#define NFIE_CLK_27M            (BIT6|BIT3)
#define NFIE_CLK_32M            (BIT6|BIT3|BIT2)
#define NFIE_CLK_36M            (BIT6|BIT4)
#define NFIE_CLK_40M            (BIT6|BIT4|BIT2)
#define NFIE_CLK_43M            (BIT6|BIT4|BIT3)
#define NFIE_CLK_54M            (BIT6|BIT4|BIT3|BIT2)
#define NFIE_CLK_62M            (BIT6|BIT5)
#define NFIE_CLK_72M            (BIT6|BIT5|BIT2)
#define NFIE_CLK_80M            (BIT6|BIT5|BIT3)
#define NFIE_CLK_86M            (BIT6|BIT5|BIT3|BIT2)
#define NFIE_CLK_SSC            (BIT6|BIT5|BIT4)
#define NFIE_CLK_300K           (BIT6|BIT5|BIT4|BIT2)
#define NFIE_CLK_48M            (BIT6|BIT5|BIT4|BIT3|BIT2)


//=====================================================
// set EMMC clock
//=====================================================

#define EMMC_CLK_80M			(BIT10)
#define EMMC_CLK_108M			(BIT11)
#define EMMC_CLK_144M			(BIT11|BIT10)
#define EMMC_CLK_160M			(BIT12)
#define EMMC_CLK_192M			(BIT12|BIT10)

#define DECIDE_CLOCK_BY_NAND	1

#define NFIE_CLK_TABLE_CNT	14
#define NFIE_CLK_TABLE	{	NFIE_CLK_300K, NFIE_CLK_XTAL, NFIE_CLK_20M, \
							NFIE_CLK_27M, NFIE_CLK_32M, NFIE_CLK_36M, NFIE_CLK_40M, \
							NFIE_CLK_43M, NFIE_CLK_48M, NFIE_CLK_54M, NFIE_CLK_62M, \
							NFIE_CLK_72M, NFIE_CLK_80M, NFIE_CLK_86M }

#define NFIE_CLK_TABLE_STR	{	"300K", "XTAL", "20M",\
							"27M", "32", "36M", "40M", \
							"43M", "48M", "54M", "62M", \
							"72M", "80M", "86M"	}

#define NFIE_300K_VALUE		300000
#define NFIE_XTAL_VALUE		12000000
#define NFIE_20M_VALUE		20000000
#define NFIE_27M_VALUE		27000000
#define NFIE_32M_VALUE		32000000
#define NFIE_36M_VALUE		36000000
#define NFIE_40M_VALUE		40000000
#define NFIE_43M_VALUE		43000000
#define NFIE_48M_VALUE		48000000
#define NFIE_54M_VALUE		54000000
#define NFIE_62M_VALUE		62000000
#define NFIE_72M_VALUE		72000000
#define NFIE_80M_VALUE		80000000
#define NFIE_86M_VALUE		86000000


#define NFIE_CLK_VALUE_TABLE	{	NFIE_300K_VALUE, NFIE_XTAL_VALUE, NFIE_20M_VALUE, \
							NFIE_27M_VALUE, NFIE_32M_VALUE, NFIE_36M_VALUE, NFIE_40M_VALUE, \
							NFIE_43M_VALUE, NFIE_48M_VALUE, NFIE_54M_VALUE, NFIE_62M_VALUE, \
							NFIE_72M_VALUE, NFIE_80M_VALUE, NFIE_86M_VALUE}


/*Define 1 cycle Time for each clock note: define value must be the (real value -1)*/
#define NFIE_1T_300K		332
#define NFIE_1T_XTAL		83
#define NFIE_1T_20M			49
#define NFIE_1T_27M			37
#define NFIE_1T_32M			31
#define NFIE_1T_36M			27
#define NFIE_1T_40M			25
#define NFIE_1T_43M			23
#define NFIE_1T_48M			20
#define NFIE_1T_54M			18
#define NFIE_1T_62M			16
#define NFIE_1T_72M			13
#define NFIE_1T_80M			12
#define NFIE_1T_86M			11

#define NFIE_1T_TABLE	{	NFIE_1T_300K, NFIE_1T_XTAL, NFIE_1T_20M, \
							NFIE_1T_27M, NFIE_1T_32M, NFIE_1T_36M, NFIE_1T_40M, \
							NFIE_1T_43M, NFIE_1T_48M, NFIE_1T_54M, NFIE_1T_62M, \
							NFIE_1T_72M, NFIE_1T_80M, NFIE_1T_86M }

/*====================================for 4 xclock==========================================*/

#define NFIE_4CLK_TABLE_CNT	5
#define NFIE_4CLK_TABLE	{	NFIE_CLK_20M, NFIE_CLK_27M, NFIE_CLK_36M, \
							NFIE_CLK_40M, NFIE_CLK_48M	}

#define NFIE_4CLK_TABLE_STR	{	"20M", "27M", "36M", \
							"40M", "48M"}

#define NFIE_4CLK_VALUE_TABLE	{ 	NFIE_20M_VALUE, NFIE_27M_VALUE, NFIE_36M_VALUE,\
								 	NFIE_40M_VALUE, NFIE_48M_VALUE}

#define NFIE_4CLK_1T_TABLE	{	NFIE_1T_20M, NFIE_1T_27M, NFIE_1T_36M, \
								NFIE_1T_40M, NFIE_1T_48M}

#define DUTY_CYCLE_PATCH          0 // 1: to enlarge low width for tREA's worst case of 25ns
#if DUTY_CYCLE_PATCH
#define FCIE3_SW_DEFAULT_CLK        NFIE_CLK_86M
#define FCIE_REG41_VAL            ((2<<9)|(2<<3)) // RE,WR pulse, Low:High=3:1
#define REG57_ECO_FIX_INIT_VALUE      0
#else
#define FCIE3_SW_DEFAULT_CLK        NFIE_CLK_54M
#define FCIE_REG41_VAL            0               // RE,WR pulse, Low:High=1:1
#define REG57_ECO_FIX_INIT_VALUE      BIT_NC_LATCH_DATA_1_0_T // delay 1.0T
#endif
#define FCIE3_SW_SLOWEST_CLK        NFIE_CLK_20M

#define NAND_SEQ_ACC_TIME_TOL       16 //in unit of ns

#define reg_ckg_fcie            GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x64)

extern U32  nand_clock_setting(U32 u32ClkParam);

extern void nand_DumpPadClk(void);
//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS          3 // Need to confirm
/*
 * Important:
 * The following buffers should be large enough for a whole NAND block
 */
// FIXME, this is only for verifing IP
#define DMA_W_ADDR              0x80C00000
#define DMA_R_ADDR              0x80D00000
#define DMA_W_SPARE_ADDR          0x80E00000
#define DMA_R_SPARE_ADDR          0x80E80000
#define DMA_BAD_BLK_BUF           0x80F00000

#define MIU_CHECK_LAST_DONE         1

//=====================================================
// misc
//=====================================================
//#define BIG_ENDIAN
#define LITTLE_ENDIAN

typedef struct NAND_DRIVER_PLATFORM_DEPENDENT
{
  U8 *pu8_PageSpareBuf;
  U8 *pu8_PageDataBuf;
  U32 u32_DMAAddrOffset;
  U32 u32_RAMBufferOffset;
  U32 u32_RAMBufferLen;

}NAND_DRIVER_PLAT_CTX, *P_NAND_DRIVER_PLAT;

#define NC_REG_MIU_LAST_DONE        NC_MIE_EVENT

extern void flush_cache(U32 start_addr, U32 size);
extern void Chip_Flush_Memory(void);
extern void Chip_Read_Memory(void);

extern int memcmp(const void *,const void *, unsigned int);
extern void *malloc(unsigned int);
extern void free(void*);

int printf(const char *format, ...);

#define NANDINFO_ECC_TYPE ECC_TYPE_40BIT1KB

#endif

