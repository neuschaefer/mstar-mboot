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
#ifndef __UNFD_EMERALD_SBOOT_H__
#define __UNFD_EMERALD_SBOOT_H__

#define REG(Reg_Addr)                       (*(volatile U16*)(Reg_Addr))
#define REG_OFFSET_SHIFT_BITS               2
#define GET_REG_ADDR(x, y)                  ((x)+((y) << REG_OFFSET_SHIFT_BITS))

#define REG_WRITE_UINT16(reg_addr, val)     REG((reg_addr)) = (val)
#define REG_READ_UINT16(reg_addr, val)      val = REG((reg_addr))
#define REG_SET_BITS_UINT16(reg_addr, val)  REG((reg_addr)) |= (val)
#define REG_CLR_BITS_UINT16(reg_addr, val)  REG((reg_addr)) &= ~(val)
#define REG_W1C_BITS_UINT16(reg_addr, val)  REG_WRITE_UINT16((reg_addr), REG((reg_addr))&(val))

#define REG_BANK_CLKGEN                     0x0580U
#define REG_BANK_CHIPTOP                    0x0F00U
#define REG_BANK_MAILBOX                    0x19C0U
#define REG_BANK_FCIE0                      0x8980U
#define REG_BANK_FCIE2                      0x8A00U

#define REG_BANK_TIMER0                     0x1800U

#define RIU_PM_BASE                         0xBF000000U
#define RIU_BASE                            0xBF200000U
#define CONFIG_RIU_BASE_ADDRESS             0xBF000000

#define MPLL_CLK_REG_BASE_ADDR              GET_REG_ADDR(RIU_BASE, REG_BANK_CLKGEN)
#define CHIPTOP_REG_BASE_ADDR               GET_REG_ADDR(RIU_BASE, REG_BANK_CHIPTOP)
#define MAILBOX_REG_BASE_ADDR               GET_REG_ADDR(RIU_BASE, REG_BANK_MAILBOX)
#define FCIE_REG_BASE_ADDR                  GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE0)
#define FCIE_NC_CIFD_BASE                   GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2)

#define TIMER0_REG_BASE_ADDR				GET_REG_ADDR(RIU_PM_BASE, REG_BANK_TIMER0)

#define CONFIG_SRAM_BASE_ADDRESS            0xBF600000
#define CONFIG_SRAM_FCIE_OFFSET             0x2800

#define DEBUG_REG                           (CONFIG_RIU_BASE_ADDRESS + (0x103380 << 1))
#define DEBUG_REG_SYS_L1                    (CONFIG_RIU_BASE_ADDRESS + (0x103392 << 1))
#define DEBUG_REG_SYS_L2                    (CONFIG_RIU_BASE_ADDRESS + (0x103394 << 1))
#define DEBUG_REG_SYS_L3                    (CONFIG_RIU_BASE_ADDRESS + (0x103396 << 1))

#define ROM_PPM_ADDR						0x0										//emerald does not need to reference this

#define FCIE4_DDR                           1
#define SPARE640B_CIFD512B_PATCH            1

#define NAND_PAD_BYPASS_MODE                1

#define BOOT_NONSECURE                      0x00
#define BOOT_HASH0                          0x80
#define BOOT_HASH1                          0x81
#define BOOT_HASH2                          0x82

#define NC_SET_DDR_MODE()
#define NC_CLR_DDR_MODE()

#define NC_CLR_SRAM_SEL()                   //REG_CLR_BITS_UINT16(NC_REG_PAD_SWITCH, BIT_BOOTSRAM_ACCESS)
#define NC_SET_SRAM_SEL()                   //REG_SET_BITS_UINT16(NC_REG_PAD_SWITCH, BIT_BOOTSRAM_ACCESS)

//-------------------------------

#define REG50_ECC_CTRL_INIT_VALUE           0

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

#define ENABLE_NAND_RIU_MODE                0
#if defined(ENABLE_NAND_RIU_MODE) && ENABLE_NAND_RIU_MODE
#undef ENABLE_NAND_INTERRUPT_MODE
#define ENABLE_NAND_INTERRUPT_MODE          0
#endif

#define IF_SPARE_AREA_DMA                   0 // [CAUTION]

#define NAND_DRIVER_ROM_VERSION             0 // to save code size
#define AUTO_FORMAT_FTL                     0

#define ENABLE_CUS_READ_ENHANCEMENT         0

#define __VER_UNFD_FTL__                    0
//=====================================================
// Nand Driver configs
//=====================================================
#define NAND_BUF_USE_STACK                  0
#define NAND_ENV_FPGA                       1
#define NAND_ENV_ASIC                       2
#ifdef __FPGA_MODE__	// currently G1 don't care this macro, even in ROM code
#define NAND_DRIVER_ENV                     NAND_ENV_FPGA
#else
#define NAND_DRIVER_ENV                     NAND_ENV_ASIC
#endif

#if defined(__ASIC_SIM__)// && __ASIC_SIM__
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
#define nand_debug(enable, tag, str, ...)	{}
#endif /* NAND_DEBUG_MSG */

extern void nand_reset_WatchDog(void);

#define nand_die(msg)                           \
    REG_WRITE_UINT16(DEBUG_REG_SYS_L3, 0xDEAD); \
    while(1);

#define nand_stop()
	//while(1)  nand_reset_WatchDog();

//=====================================================
// HW Timer for Delay
//=====================================================
#define TIMER0_ENABLE						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x20)
#define TIMER0_HIT							GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x21)
#define TIMER0_MAX_LOW						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x22)
#define TIMER0_MAX_HIGH						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x23)
#define TIMER0_CAP_LOW						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x24)
#define TIMER0_CAP_HIGH						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x25)

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


//=====================================================
// set FCIE clock
//=====================================================
#define NFIE_CLK_MASK                       (BIT5|BIT4|BIT3|BIT2)
#define NFIE_CLK_XTAL                       (0)
#define NFIE_CLK_5_4M                       (BIT2)
#define NFIE_CLK_27M                        (BIT3)
#define NFIE_CLK_32M                        (BIT3|BIT2)
#define NFIE_CLK_36M                        (BIT4)
#define NFIE_CLK_40M                        (BIT4|BIT2)
#define NFIE_CLK_43M                        (BIT4|BIT3)
#define NFIE_CLK_54M                        (BIT4|BIT3|BIT2)
#define NFIE_CLK_62M                        (BIT5)
#define NFIE_CLK_72M                        (BIT5|BIT2)
#define NFIE_CLK_80M                        (BIT5|BIT3)
#define NFIE_CLK_86M                        (BIT5|BIT3|BIT2)
#define NFIE_CLK_300K                       (BIT5|BIT4|BIT2)
#define NFIE_CLK_48M                        (BIT5|BIT4|BIT3|BIT2)

#define DUTY_CYCLE_PATCH					0 // 1: to enlarge low width for tREA's worst case of 25ns
#if DUTY_CYCLE_PATCH
#define FCIE3_SW_DEFAULT_CLK				NFIE_CLK_86M
#define FCIE_REG41_VAL						((2<<9)|(2<<3)) // RE,WR pulse, Low:High=3:1
#define REG57_ECO_FIX_INIT_VALUE			0
#else
#define FCIE3_SW_DEFAULT_CLK				NFIE_CLK_54M
#define FCIE_REG41_VAL						0               // RE,WR pulse, Low:High=1:1
#define REG57_ECO_FIX_INIT_VALUE			BIT_NC_LATCH_DATA_1_0_T	// delay 1.0T
#endif
#define FCIE3_SW_SLOWEST_CLK				NFIE_CLK_5_4M

#define NAND_SEQ_ACC_TIME_TOL				10 //in unit of ns

#define reg_ckg_fcie						GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x64)

extern U32  nand_clock_setting(U32 u32ClkParam);


//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS                  3 // Need to confirm

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

#endif /* __UNFD_G2_LINUX_H__ */
