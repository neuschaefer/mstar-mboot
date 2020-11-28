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
//#ifndef __UNFD_AGATE_LINUX_H__
//#define __UNFD_AGATE_LINUX_H__
#ifndef __UNFD_KAISER_LINUX_H__
#define __UNFD_KAISER_LINUX_H__

//#include <asm/io.h>
#include <linux/string.h>
#include <common.h>
#include <jffs2/load_kernel.h>

#define REG_BANK_CLKGEN               (0x580)
#define REG_BANK_CHIPTOP              (0xF00)
#define REG_BANK_FCIE0                (0x8980)
#define REG_BANK_FCIE2                (0x8A00)
#define REG_BANK_TIMER0               (0x1810)

#define RIU_PM_BASE                   0x1F000000
#define RIU_BASE                      0x1F200000

#define MPLL_CLK_REG_BASE_ADDR        (RIU_BASE+(REG_BANK_CLKGEN<<REG_OFFSET_SHIFT_BITS))
#define CHIPTOP_REG_BASE_ADDR         (RIU_BASE+(REG_BANK_CHIPTOP<<REG_OFFSET_SHIFT_BITS))
#define FCIE_REG_BASE_ADDR            (RIU_BASE+(REG_BANK_FCIE0<<REG_OFFSET_SHIFT_BITS))
#define FCIE_NC_CIFD_BASE             (RIU_BASE+(REG_BANK_FCIE2<<REG_OFFSET_SHIFT_BITS))
#define TIMER0_REG_BASE_ADDR          (RIU_PM_BASE+(REG_BANK_TIMER0<<REG_OFFSET_SHIFT_BITS))

#define REG(Reg_Addr)                 (*(volatile U16*)(Reg_Addr))
#define REG_OFFSET_SHIFT_BITS         2
#define GET_REG_ADDR(x, y)            (x+((y)<<REG_OFFSET_SHIFT_BITS))

#define REG_WRITE_UINT16(reg_addr, val)   REG(reg_addr) = val
#define REG_READ_UINT16(reg_addr, val)    val = REG(reg_addr)
#define HAL_WRITE_UINT16(reg_addr, val)   (REG(reg_addr) = val)
#define HAL_READ_UINT16(reg_addr, val)    val = REG(reg_addr)
#define REG_SET_BITS_UINT16(reg_addr, val)  REG(reg_addr) |= (val)
#define REG_CLR_BITS_UINT16(reg_addr, val)  REG(reg_addr) &= ~(val)
#define REG_W1C_BITS_UINT16(reg_addr, val)  REG_WRITE_UINT16(reg_addr, REG(reg_addr)&(val))

#define REG50_ECC_CTRL_INIT_VALUE     0

#define UNFD_ST_PLAT            0x80000000
#define IF_IP_VERIFY            0 // [CAUTION]: to verify IP and HAL code, defaut 0

// debug
#define FCIE3_DUMP_DEBUG_BUS        1

//FCIE4 DDR Nand
#define FCIE4_DDR                   0

#define SPARE640B_CIFD512B_PATCH    1
//Each Platform, which supports DDR NAND,  Needs to define DQS pull high/low
#define NC_DQS_PULL_H()
#define NC_DQS_PULL_L()

#define NAND_PAD_BYPASS_MODE        1
#define NAND_PAD_TOGGLE_MODE        2
#define NAND_PAD_ONFI_SYNC_MODE     3

#define REG_NAND_CS1_EN                GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x6F)
#define BIT_NAND_CS1_EN                BIT4


#if (defined(FCIE4_DDR) && FCIE4_DDR)
#define NC_SET_DDR_MODE()       REG_WRITE_UINT16(NC_DDR_CTRL, pNandDrv->u16_Reg58_DDRCtrl);
#define NC_CLR_DDR_MODE()       REG_CLR_BITS_UINT16(NC_DDR_CTRL, BIT_DDR_MASM);
#else
#define NC_SET_DDR_MODE()
#define NC_CLR_DDR_MODE()
#endif

#if (defined(FCIE4_DDR) && FCIE4_DDR)
#define DQS_MODE_2P0T        0
#define DQS_MODE_1P5T        1
#define DQS_MODE_2P5T        2
#define DQS_MODE_0P0T        3
#define DQS_MODE_TABLE_CNT    4
#define DQS_MODE_SEARCH_TABLE {DQS_MODE_1P5T, DQS_MODE_0P0T, DQS_MODE_2P0T, DQS_MODE_2P5T}
#define DQS_MODE_TABLE        {DQS_MODE_0P0T, DQS_MODE_1P5T, DQS_MODE_2P0T, DQS_MODE_2P5T}
#endif

#define NC_INST_DELAY    1
#define NC_HWCMD_DELAY    1
#define NC_TRR_TCS        1
#define NC_TWHR_TCLHZ            1
#define NC_TCWAW_TADL            1

// ask IP designer to obtain the following default delay
#define    NC_ONFI_DEFAULT_TRR 12
#define    NC_ONFI_DEFAULT_TCS 7
#define    NC_ONFI_DEFAULT_TWW    8
#define NC_ONFI_DEFAULT_TWHR 5
#define NC_ONFI_DEFAULT_TADL 6
#define NC_ONFI_DEFAULT_TCWAW 4
#define    NC_ONFI_DEFAULT_RX40CMD 4
#define    NC_ONFI_DEFAULT_RX40ADR 7
#define    NC_ONFI_DEFAULT_RX56 10

#define    NC_TOGGLE_DEFAULT_TRR 8
#define    NC_TOGGLE_DEFAULT_TCS 6
#define    NC_TOGGLE_DEFAULT_TWW 7
#define    NC_TOGGLE_DEFAULT_TWHR 5
#define    NC_TOGGLE_DEFAULT_TADL 7
#define    NC_TOGGLE_DEFAULT_TCWAW 2
#define    NC_TOGGLE_DEFAULT_RX40CMD 4
#define    NC_TOGGLE_DEFAULT_RX40ADR 5
#define    NC_TOGGLE_DEFAULT_RX56 15

#define    NC_SDR_DEFAULT_TRR 7
#define    NC_SDR_DEFAULT_TCS 6
#define    NC_SDR_DEFAULT_TWW 5
#define    NC_SDR_DEFAULT_TWHR 4
#define    NC_SDR_DEFAULT_TADL 8
#define    NC_SDR_DEFAULT_TCWAW 2
#define    NC_SDR_DEFAULT_RX40CMD 4
#define    NC_SDR_DEFAULT_RX40ADR 5
#define    NC_SDR_DEFAULT_RX56 5

#define NC_SEL_FCIE3            1
#if NC_SEL_FCIE3
#include "drvNAND_reg_v3.h"

#undef ECC_CODE_BYTECNT_4BIT
#undef ECC_CODE_BYTECNT_8BIT
#undef ECC_CODE_BYTECNT_20BIT
#undef ECC_CODE_BYTECNT_24BIT

#define ECC_CODE_BYTECNT_4BIT               8
#define ECC_CODE_BYTECNT_8BIT               14
#define ECC_CODE_BYTECNT_20BIT              34
#define ECC_CODE_BYTECNT_24BIT              40

#else
#error "Error! no FCIE registers selected."
#endif

#if IF_IP_VERIFY
/* select a default NAND chip for IP_VERIFY or NAND_PROGRAMMER */
//#define K9GAG08U0E                          1
//#define H27UAG8T2M                          1
//#define NAND512W3A2C                        1
//#define K9F1G08X0C                          1
//#define TH58TVG7D2GBA                       1 // <- Toggle
//#define MT29F64G08CBAAB                     1 // <- ONFI
//#define H27UAG8T2A                          1
//#define H27UF081G2A                         1
//#define K511F12ACA                          1
//#define TY8A0A111162KC40                    1
//#define K522H1GACE                          1
//#define TY890A111229KC40                    1
//#define H8ACU0CE0DAR                        1
//#define H9LA25G25HAMBR                      1
//#define TY8A0A111178KC4                     1
//#define HY27UF082G2B                        1
//#define H27UCG8V5M                          1 //4k page
//#define H27U2G8F2CTR                        1
//#define H27U4G8F2DTR                        1
#define MT29F4G08ABAEA											1
#include "../common/drvNAND_device.h"
#endif


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
        nand_printf("NAND Err:");            \
      if (tag)                  \
      {                                       \
        nand_printf("[%s]\t", __func__);        \
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
#define TIMER0_ENABLE             GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x00)
#define TIMER0_HIT                GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x01)
#define TIMER0_MAX_LOW            GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x02)
#define TIMER0_MAX_HIGH           GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x03)
#define TIMER0_CAP_LOW            GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x04)
#define TIMER0_CAP_HIGH           GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x05)

#define HW_TIMER_DELAY_1us          1
#define HW_TIMER_DELAY_10us         10
#define HW_TIMER_DELAY_100us        100
#define HW_TIMER_DELAY_1ms          (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms          (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms         (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms        (100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms        (500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s           (1000 * HW_TIMER_DELAY_1ms)

#define NAND_SPEED_TEST             0

extern void delay_us( unsigned us );
extern U32  nand_hw_timer_delay(U32 u32usTick);

//=====================================================
// Pads Switch
//=====================================================
#define reg_fcie2macro_sd_bypass        GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x35)
#define BIT_SD_USE_BYPASS               BIT7
#define BIT_FCIE2MACRO_SD_BYPASS        BIT6
#define BIT_EMMC_SWRSTZ_EN              BIT5
#define BIT_EMMC_SWRSTZ                 BIT4
#define BIT_PAD_IN_SEL_SD               BIT1
#define BIT_PAD_IN_SEL_SDIO             BIT0

#define reg_allpad_in                   GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x50)
#define BIT_ALL_PAD_IN                  BIT15

#define reg_nf_en                       GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x06)
#define CFG_EMMC_PAD_MASK               (BIT12|BIT13)
#define CFG_SD_PAD_MASK                 (BIT14|BIT15)
#define CFG_NAND_PAD_MASK               (BIT0|BIT1)
#define BIT_NAND_PAD_MODE2               BIT1


extern U32 nand_pads_switch(U32 u32EnableFCIE);
extern U32     nand_check_DDR_pad(void);


//=====================================================
// set FCIE clock
//=====================================================
#define NFIE_CLK_MASK           (BIT5|BIT4|BIT3|BIT2)


#define NFIE_CLK_300K           (0 << 2)
#define NFIE_CLK_750K           (1 << 2)
#define NFIE_CLK_5_4M           (2 << 2)
#define NFIE_CLK_13M            (3 << 2)
#define NFIE_CLK_18M            (4 << 2)
#define NFIE_CLK_22_7M          (5 << 2)
#define NFIE_CLK_27M            (6 << 2)
#define NFIE_CLK_32M            (7 << 2)
#define NFIE_CLK_43_2M          (8 << 2)
#define NFIE_CLK_54M            (9 << 2)
#define NFIE_CLK_72M            (10 << 2)
#define NFIE_CLK_86M            (11 << 2)
#define NFIE_CLK_XTAL           (13 << 2)
#define NFIE_CLK_62M            (14 << 2)

#define DECIDE_CLOCK_BY_NAND    1

#define NFIE_CLK_TABLE_CNT    13
#define NFIE_CLK_TABLE    {NFIE_CLK_300K, NFIE_CLK_750K, NFIE_CLK_5_4M, NFIE_CLK_13M, \
                            NFIE_CLK_18M, NFIE_CLK_22_7M, NFIE_CLK_27M, NFIE_CLK_32M,\
                            NFIE_CLK_43_2M, NFIE_CLK_54M, NFIE_CLK_62M, NFIE_CLK_72M, NFIE_CLK_86M}


#define NFIE_CLK_TABLE_STR    {"300K", "750K", "5.4M", "13M", \
                            "18M", "22.7M", "27M", "32M",\
                            "43.2M", "54M", "62M", "72M", "86M"}

#define NFIE_300K_VALUE          300000
#define NFIE_750K_VALUE          750000
#define NFIE_5_4M_VALUE         5400000
#define NFIE_13M_VALUE        13000000
#define NFIE_18M_VALUE        18000000
#define NFIE_22_7M_VALUE    22700000
#define NFIE_27M_VALUE        27000000
#define NFIE_32M_VALUE        32000000
#define NFIE_43_2M_VALUE    43200000
#define NFIE_54M_VALUE        54000000
#define NFIE_62M_VALUE        62000000
#define NFIE_72M_VALUE        72000000
#define NFIE_86M_VALUE        86000000

#define NFIE_CLK_VALUE_TABLE    {    NFIE_300K_VALUE, NFIE_750K_VALUE, NFIE_5_4M_VALUE, NFIE_13M_VALUE, \
                            NFIE_18M_VALUE, NFIE_22_7M_VALUE, NFIE_27M_VALUE, NFIE_32M_VALUE, \
                            NFIE_43_2M_VALUE, NFIE_54M_VALUE, NFIE_62M_VALUE, NFIE_72M_VALUE, NFIE_86M_VALUE}


/*Define 1 cycle Time for each clock note: define value must be the (real value -1)*/
#define NFIE_1T_300K        3332
#define NFIE_1T_750K        1332
#define NFIE_1T_5_4M        184
#define NFIE_1T_13M            76
#define NFIE_1T_18M            55
#define NFIE_1T_22_7M        43
#define NFIE_1T_27M            37
#define NFIE_1T_32M            31
#define NFIE_1T_43_2M        23
#define NFIE_1T_54M            18
#define NFIE_1T_62M            15
#define NFIE_1T_72M            13
#define NFIE_1T_86M            11

#define NFIE_1T_TABLE    {NFIE_1T_300K, NFIE_1T_750K, NFIE_1T_5_4M, NFIE_1T_13M,    \
                            NFIE_1T_18M, NFIE_1T_22_7M, NFIE_1T_27M, NFIE_1T_32M, \
                            NFIE_1T_43_2M, NFIE_1T_54M, NFIE_1T_62M, NFIE_1T_72M, NFIE_1T_86M}

#if 0
/*====================================for 4 xclock==========================================*/

#define NFIE_4CLK_TABLE_CNT    8
#define NFIE_4CLK_TABLE    {    NFIE_CLK_20M, \
                            NFIE_CLK_27M, NFIE_CLK_36M, NFIE_CLK_40M, \
                            NFIE_CLK_48M, NFIE_CLK_54M, \
                            NFIE_CLK_72M, NFIE_CLK_108M    }

#define NFIE_4CLK_TABLE_STR    {    "20M",\
                            "27M", "36M", "40M", \
                            "48M", "54M",  \
                            "72M", "108M"    }


#define NFIE_4CLK_VALUE_TABLE    { NFIE_20M_VALUE, \
                            NFIE_27M_VALUE, NFIE_36M_VALUE, NFIE_40M_VALUE, \
                            NFIE_48M_VALUE, NFIE_54M_VALUE, \
                            NFIE_72M_VALUE, NFIE_108M_VALUE}


#define NFIE_4CLK_1T_TABLE    {NFIE_1T_20M, \
                            NFIE_1T_27M, NFIE_1T_36M, NFIE_1T_40M, \
                            NFIE_1T_48M, NFIE_1T_54M, \
                            NFIE_1T_72M, NFIE_1T_108M    }
#endif


#define DUTY_CYCLE_PATCH            0 // 1: to enlarge low width for tREA's worst case of 25ns
#if DUTY_CYCLE_PATCH
#define FCIE3_SW_DEFAULT_CLK        NFIE_CLK_86M
#define FCIE_REG41_VAL              ((2<<9)|(2<<3)) // RE,WR pulse, Low:High=3:1
#define REG57_ECO_FIX_INIT_VALUE    0
#else
#define FCIE3_SW_DEFAULT_CLK        NFIE_CLK_54M
#define FCIE_REG41_VAL              0               // RE,WR pulse, Low:High=1:1
#define REG57_ECO_FIX_INIT_VALUE    BIT_NC_LATCH_DATA_1_0_T // delay 1.0T
#endif
#define FCIE3_SW_SLOWEST_CLK        NFIE_CLK_18M

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
#define DMA_W_ADDR              0x20C00000
#define DMA_R_ADDR              0x20D00000
#define DMA_W_SPARE_ADDR          0x20E00000
#define DMA_R_SPARE_ADDR          0x20E80000
#define DMA_BAD_BLK_BUF           0x20F00000

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

