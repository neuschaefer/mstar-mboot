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
#ifndef __UNFD_NAPOLI_SBOOT_H__
#define __UNFD_NAPOLI_SBOOT_H__

#include <string.h>

#define TV_ROM

#define REG_OFFSET_SHIFT_BITS               2

#define REG(Reg_Addr)                       (*(volatile U16*)(Reg_Addr))
#define GET_REG_ADDR(x, y)                  ((x)+((y) << REG_OFFSET_SHIFT_BITS))

#define REG_WRITE_UINT16(reg_addr, val)     REG((reg_addr)) = (val)
#define REG_READ_UINT16(reg_addr, val)      val = REG((reg_addr))
#define REG_SET_BITS_UINT16(reg_addr, val)  REG((reg_addr)) |= (val)
#define REG_CLR_BITS_UINT16(reg_addr, val)  REG((reg_addr)) &= ~(val)
#define REG_W1C_BITS_UINT16(reg_addr, val)  REG_WRITE_UINT16((reg_addr), REG((reg_addr))&(val))


#define RIU_PM_BASE                         0x1F000000U
#define RIU_BASE                            0x1F200000U
#define CONFIG_RIU_BASE_ADDRESS             0x1F000000

#ifdef CONFIG_ASIC_EMULATION
#define CONFIG_SRAM_BASE_ADDRESS            0x41000000
#else
#define CONFIG_SRAM_BASE_ADDRESS            0x1FC00000
#endif

#define CONFIG_SRAM_FCIE_OFFSET             0x2800


#define REG_BANK_CLKGEN                     0x0580U
#define REG_BANK_CHIPTOP                    0x0F00U
#define REG_BANK_FCIE0                      0x8980U
#define REG_BANK_FCIE1                      0x89E0U
#define REG_BANK_FCIE2                      0x8A00U
#define REG_BANK_FCIE3                      0x8A80U
#define REG_BANK_TIMER0                     0x1800U
#define REG_BANK_MIU                        0x0900U //owen
#define REG_BANK_MAILBOX                    0x19C0U

#define REG_BANK_PORTSTATUS                 0x0280U
//#define REG_BANK_PMSLEEP                    0x0700U

#define CHIPTOP_BASE                        GET_REG_ADDR(RIU_BASE, REG_BANK_CHIPTOP)
#define CLKGEN_BASE                         GET_REG_ADDR(RIU_BASE, REG_BANK_CLKGEN)
#define FCIE0_BASE                          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE0)
#define FCIE1_BASE                          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE1)
#define FCIE2_BASE                          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2)
#define FCIE3_BASE                          GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE3)
#define MAILBOX_BASE                        GET_REG_ADDR(RIU_BASE, REG_BANK_MAILBOX)

#define PORTSTATUS_BASE                     GET_REG_ADDR(RIU_BASE, REG_BANK_PORTSTATUS)
//#define PMSLEEP_BASE                        GET_REG_ADDR(RIU_PM_BASE, REG_BANK_PMSLEEP)

#define TIMER0_REG_BASE_ADDR				GET_REG_ADDR(CONFIG_RIU_BASE_ADDRESS, REG_BANK_TIMER0)

#define FCIE_REG_BASE_ADDR                  FCIE0_BASE
#define FCIE_REG_BASE1_ADDR                 FCIE1_BASE
#define FCIE_NC_CIFD_BASE                   FCIE2_BASE

#define DEBUG_REG                           (CONFIG_RIU_BASE_ADDRESS + (0x103380 << 1))
#define DEBUG_REG_SYS_L1                    (CONFIG_RIU_BASE_ADDRESS + (0x103392 << 1))
#define DEBUG_REG_SYS_L2                    (CONFIG_RIU_BASE_ADDRESS + (0x103394 << 1))
#define DEBUG_REG_SYS_L3                    (CONFIG_RIU_BASE_ADDRESS + (0x103396 << 1))

#define DUMMY_REG1                          (CONFIG_RIU_BASE_ADDRESS + (0x103382 << 1))
#define DUMMY_REG2                          (CONFIG_RIU_BASE_ADDRESS + (0x103384 << 1))
#define DUMMY_REG3                          (CONFIG_RIU_BASE_ADDRESS + (0x103386 << 1))
#define DUMMY_REG4                          (CONFIG_RIU_BASE_ADDRESS + (0x103388 << 1))

#define EFUSE_REG                           (CONFIG_RIU_BASE_ADDRESS + (0x002000 << 1))
#define REG_EFUSE_OUTA_OUTE_15_0            GET_REG_ADDR(EFUSE_REG, 0x4)
#define REG_SEL_READ_256                    GET_REG_ADDR(EFUSE_REG, 0x25)

#define ROM_PPM_ADDR						0x1fc02a44 // TBD							//check the elf.map for rom code binary

#define BOOTSTAGE_REG                       GET_REG_ADDR(PORTSTATUS_BASE, 0x7)

#define BOOT_NONSECURE                      0x00
#define BOOT_HASH0                          0x80
#define BOOT_HASH1                          0x81
#define BOOT_HASH2                          0x82

#define REG_ALL_PAD_IN                      0x50
#define REG_SDR_BYPASS_MODE                 0x10

#ifndef CONFIG_ASIC_EMULATION

#define REG_NAND_MODE                       0x6F
#define REG_NAND_MODE_MASK                  (BIT6|BIT7)
#define NAND_MODE1                          (BIT6) // obsolete
#define NAND_MODE2                          (BIT7)
#else

#define REG_NAND_MODE                       0x6F
#define REG_NAND_MODE_MASK                  (BIT6|BIT7)
#define NAND_MODE1                          (BIT6) // obsolete
#define NAND_MODE2                          (BIT7)
#endif

#define REG_NAND_DQS_EN                     GET_REG_ADDR(CHIPTOP_BASE, 0x0D)           /* 0x101E */
#define REG_NAND_DQS_UL                     GET_REG_ADDR(CHIPTOP_BASE, 0x0F)           /* 0x101E */

#define REG_PCM_D_PE                        GET_REG_ADDR(CHIPTOP_BASE, 0x09)
#define REG_PCM_A_PE                        GET_REG_ADDR(CHIPTOP_BASE, 0x0A)
#define REG_EMMC_PE                         GET_REG_ADDR(CHIPTOP_BASE, 0x0D)
#define REG_EMMC_PS                         GET_REG_ADDR(CHIPTOP_BASE, 0x0F)
#define REG_TS2_D0                          GET_REG_ADDR(CHIPTOP_BASE, 0x0C)

#define REG_SD_USE_BYPASS                   GET_REG_ADDR(CHIPTOP_BASE, 0x40)

#define EMMC_PLL_ADDR                   	GET_REG_ADDR(CONFIG_RIU_BASE_ADDRESS+0x247E00, 0x1B) //0x123F

#define BIT_NAND_BOOT_EN                    (BIT3)
#define BIT_BOOTSRAM_ACCESS                 (BIT4)

#define BIT_FCIE2MACRO_SD_BYPASS            (BIT8)

#define BIT_SD_USE_BYPASS                   (BIT0)

#define FCIE4_DDR                           1
#define SPARE640B_CIFD512B_PATCH            1

#if defined(FCIE4_DDR) && FCIE4_DDR
#define ENABLE_TOGGLE_MODE_SUPPORT          1
#endif

#define BIT_DQS_PULL_H                      BIT11

#define NC_DQS_PULL_H()                     REG_SET_BITS_UINT16(REG_NAND_DQS_UL, BIT_DQS_PULL_H)
#define NC_DQS_PULL_L()                     REG_CLR_BITS_UINT16(REG_NAND_DQS_UL, BIT_DQS_PULL_H)

#define NAND_PAD_BYPASS_MODE                1
#define NAND_PAD_TOGGLE_MODE                2

#if defined(ENABLE_TOGGLE_MODE_SUPPORT) && ENABLE_TOGGLE_MODE_SUPPORT
#define NC_SET_DDR_MODE()                   REG_WRITE_UINT16(NC_DDR_CTRL, pNandDrv->u16_Reg58_DDRCtrl);
#define NC_CLR_DDR_MODE()                   REG_CLR_BITS_UINT16(NC_DDR_CTRL, BIT_DDR_MASM);
#else
#define NC_SET_DDR_MODE()
#define NC_CLR_DDR_MODE()
#endif

#define NC_CLR_SRAM_SEL()                   REG_CLR_BITS_UINT16(NC_REG_PAD_SWITCH, BIT_BOOTSRAM_ACCESS)
#define NC_SET_SRAM_SEL()                   REG_SET_BITS_UINT16(NC_REG_PAD_SWITCH, BIT_BOOTSRAM_ACCESS)

#define DQS_MODE_0P0T		0
#define DQS_MODE_0P5T		1
#define DQS_MODE_1P0T		2
#define DQS_MODE_1P5T		3
#define DQS_MODE_2P0T		4
#define DQS_MODE_2P5T		5
#define DQS_MODE_3P0T		6
#define DQS_MODE_3P5T		7
#define DQS_MODE_TABLE_CNT	8
#define DQS_MODE_SEARCH_TABLE	{DQS_MODE_1P5T, DQS_MODE_2P0T, DQS_MODE_2P5T, DQS_MODE_3P0T, \
								 DQS_MODE_3P5T, DQS_MODE_0P0T, DQS_MODE_0P5T, DQS_MODE_1P0T} // dqs mode searching sequence

//-------------------------------

#define REG50_ECC_CTRL_INIT_VALUE           0 //(BIT_NC_SHARE_PAD_EN)

#define UNFD_ST_PLAT                        0x80000000
#define IF_IP_VERIFY                        0 // [CAUTION]: to verify IP and HAL code, defaut 0

// debug
#define FCIE3_DUMP_DEBUG_BUS                1

#define NC_SEL_FCIE3                        1
#if NC_SEL_FCIE3
#include "drvNAND_reg_v3.h"
#else
#error "Error! no FCIE registers selected."
#endif

#define IF_FCIE_SHARE_PINS                  0 // 1: need to nand_pads_switch at HAL's functions.
#define IF_FCIE_SHARE_CLK                   0 // 1: need to nand_clock_setting at HAL's functions.
#define IF_FCIE_SHARE_IP                    0

#define ENABLE_NAND_INTERRUPT_MODE          0

#define ENABLE_NAND_RIU_MODE                1
#if defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE
#undef ENABLE_NAND_INTERRUPT_MODE
#define ENABLE_NAND_INTERRUPT_MODE          0
#endif

#define IF_SPARE_AREA_DMA                   0 // [CAUTION]

#define NAND_DRIVER_ROM_VERSION             0 // to save code size
#define AUTO_FORMAT_FTL                     0

#define ENABLE_CUS_READ_ENHANCEMENT         0

//=====================================================
#define ENABLE_BLANK_CHECK_SUPPORT          1

#define ENABLE_READ_DISTURBANCE_SUPPORT     1
#define DEBUG_REG_ECC_STATUS                NC_CF_SSO_CTL // choose dummy reg from FCIE or CHIPTOP

// 2 bits ECC status
#define ECC_STATUS_NORMAL                   0
#define ECC_STATUS_BITFLIP                  1
#define ECC_STATUS_ERROR                    2

//---------------------------------------------------------------------
//         RESERVED          |   BL   | UBOOT | HASH2 | HASH1 | HASH0 |
//---------------------------------------------------------------------
#define BIT_ECC_STATUS_HASH0_SHIFT          0
#define BIT_ECC_STATUS_HASH1_SHIFT          2
#define BIT_ECC_STATUS_HASH2_SHIFT          4
#define BIT_ECC_STATUS_UBOOT_SHIFT          6
#define BIT_ECC_STATUS_BL_SHIFT             8
//=====================================================

#define __VER_UNFD_FTL__                    0
//=====================================================
// Nand Driver configs
//=====================================================
#define NAND_BUF_USE_STACK                  0
#define NAND_ENV_FPGA                       1
#define NAND_ENV_ASIC                       2
#ifdef __FPGA_MODE__        // currently G1 don't care this macro, even in ROM code
#define NAND_DRIVER_ENV                     NAND_ENV_FPGA
#else
#define NAND_DRIVER_ENV                     NAND_ENV_ASIC
#endif

#if defined(__ASIC_SIM__)   // && __ASIC_SIM__
#define NAND_DRIVER_FOR_ROM_SIM             1
#else
#define NAND_DRIVER_FOR_ROM_SIM             0
#endif

#define UNFD_CACHE_LINE                     0x20
//=====================================================
// tool-chain attributes
//=====================================================
#define UNFD_PACK0
#define UNFD_PACK1                          __attribute__((__packed__))
#define UNFD_ALIGN0
#define UNFD_ALIGN1                         __attribute__((aligned(UNFD_CACHE_LINE)))

//=====================================================
// debug option
//=====================================================
#define NAND_TEST_IN_DESIGN                 0      /* [CAUTION] */

#ifndef NAND_DEBUG_MSG
#define NAND_DEBUG_MSG                      0
#endif

/* Define trace levels. */
#define UNFD_DEBUG_LEVEL_ERROR              (1)    /* Error condition debug messages. */
#define UNFD_DEBUG_LEVEL_WARNING            (2)    /* Warning condition debug messages. */
#define UNFD_DEBUG_LEVEL_HIGH               (3)    /* Debug messages (high debugging). */
#define UNFD_DEBUG_LEVEL_MEDIUM             (4)    /* Debug messages. */
#define UNFD_DEBUG_LEVEL_LOW                (5)    /* Debug messages (low debugging). */

/* Higer debug level means more verbose */
#ifndef UNFD_DEBUG_LEVEL
#define UNFD_DEBUG_LEVEL                    UNFD_DEBUG_LEVEL_WARNING
#endif

#if defined(NAND_DEBUG_MSG) && NAND_DEBUG_MSG
#define nand_printf    printf
#define nand_debug(dbg_lv, tag, str, ...)           \
	do {                                            \
		if (dbg_lv > UNFD_DEBUG_LEVEL)              \
			break;                                  \
		else {                                      \
			if (tag)                                \
				nand_printf("[ %s() ] ", __func__); \
                                                    \
			nand_printf(str, ##__VA_ARGS__);        \
		}                                           \
	} while(0)
#else /* NAND_DEBUG_MSG */
#define nand_printf(...)
#define nand_debug(enable, tag, str, ...)   {}
#endif /* NAND_DEBUG_MSG */

extern void nand_reset_WatchDog(void);

#define nand_die(msg)                           \
    REG_WRITE_UINT16(DEBUG_REG_SYS_L3, 0xDEAD); \
    while(1);

#define nand_stop() \
	while(1)  nand_reset_WatchDog();

//=====================================================
// HW Timer for Delay
//=====================================================
#define TIMER0_ENABLE						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x10)
#define TIMER0_HIT							GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x11)
#define TIMER0_MAX_LOW						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x12)
#define TIMER0_MAX_HIGH						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x13)
#define TIMER0_CAP_LOW						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x14)
#define TIMER0_CAP_HIGH						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x15)


#define HW_TIMER_DELAY_1us                  (1)
#define HW_TIMER_DELAY_10us                 (10 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_100us                (100 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_1ms                  (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms                  (5 * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms                 (10 * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms                (100 * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms                (500 * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s                   (1000 * HW_TIMER_DELAY_1ms)

extern void delay_us( unsigned us );
extern U32  nand_hw_timer_delay(U32 u32usTick);

//=====================================================
// Pads Switch
//=====================================================
extern U32 nand_pads_switch(U32 u32EnableFCIE);
extern U32 NC_ReadOneID(void);
extern U32 nand_pad_detect(void);

#define REG_CLK_NFIE                        GET_REG_ADDR(CLKGEN_BASE, 0x64)
#define BIT_CLK_ENABLE                      BIT6
#define REG_CLK_EMMC                        GET_REG_ADDR(CLKGEN_BASE, 0x64)

//=====================================================
// set FCIE clock
//=====================================================
#define EMMC_CLK_MASK                       (BIT5|BIT4|BIT3|BIT2)

#define NFIE_CLK_MASK                       ((BIT4-1)<<2)
#define NFIE_CLK_XTAL                       (0<<2)
#define NFIE_CLK_20M                        (1<<2)
#define NFIE_CLK_27M                        (2<<2)
#define NFIE_CLK_32M                        (3<<2)
#define NFIE_CLK_36M                        (4<<2)
#define NFIE_CLK_40M                        (5<<2)
#define NFIE_CLK_43_2M                      (6<<2)
#define NFIE_CLK_54M                        (7<<2)
#define NFIE_CLK_62M                        (8<<2)
#define NFIE_CLK_72M                        (9<<2)
#define NFIE_CLK_EMMC_PLL                   (10<<2)
#define NFIE_CLK_86M                        (11<<2)
#define NFIE_CLK_300K                       (13<<2)
#define NFIE_CLK_XTAL2                      (14<<2)
#define NFIE_CLK_48M                        (15<<2)

/*
#define NFIE_CLK4X_24M                      (0<<2)
#define NFIE_CLK4X_108M                     (1<<2)
#define NFIE_CLK4X_144M                     (2<<2)
#define NFIE_CLK4X_160M                     (3<<2)
#define NFIE_CLK4X_192M                     (4<<2)
#define NFIE_CLK4X_216M                     (5<<2)
#define NFIE_CLK4X_240M                     (6<<2)
#define NFIE_CLK4X_300M                     (7<<2)
*/
#define DUTY_CYCLE_PATCH                    0 // 1: to enlarge low width for tREA's worst case of 25ns
#if DUTY_CYCLE_PATCH
#define FCIE3_SW_DEFAULT_CLK                NFIE_CLK_86M
#define FCIE_REG41_VAL                      ((2<<9)|(2<<3)) // RE,WR pulse, Low:High=3:1
#else
#define FCIE3_SW_DEFAULT_CLK                NFIE_CLK_32M
#define FCIE_REG41_VAL                      0               // RE,WR pulse, Low:High=1:1
#endif
#define FCIE3_SW_SLOWEST_CLK                NFIE_CLK_XTAL

#define NAND_SEQ_ACC_TIME_TOL               10 //in unit of ns

extern void drvTimer_Enable(unsigned int dwMicroSecondNumber, unsigned char bNeedWaitComplete);
extern U32  nand_clock_setting(U32 u32ClkParam);

#define usleep(TimerCount, WaitComplete)    drvTimer_Enable(TimerCount, WaitComplete)

//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS                  3 // Need to confirm
/*
 * Important:
 * The following buffers should be large enough for a whole NAND block
 */
// FIXME, this is only for verifing IP
#define DMA_W_ADDR                          0x80C00000
#define DMA_R_ADDR                          0x80D00000
#define DMA_W_SPARE_ADDR                    0x80E00000
#define DMA_R_SPARE_ADDR                    0x80E80000
#define DMA_BAD_BLK_BUF                     0x80F00000

#define MIU_CHECK_LAST_DONE                 1

//=====================================================
// misc
//=====================================================
//#define BIG_ENDIAN
#define LITTLE_ENDIAN

typedef struct NAND_DRIVER_PLATFORM_DEPENDENT
{
	U8 		*pu8_PageSpareBuf;
	U8		*pu8_PageDataBuf;
	U32		u32_DMAAddrOffset;
	U32		u32_RAMBufferOffset;
	U32		u32_RAMBufferLen;

}NAND_DRIVER_PLAT_CTX, *P_NAND_DRIVER_PLAT;

#define NC_REG_MIU_LAST_DONE                NC_MIE_EVENT

// locate API to DRAM area
#define __ATTR_DRAM_CODE__	__attribute__((section ("NANDCODE"))) 

#endif /* __UNFD_NAPOLI_SBOOT_H__ */
