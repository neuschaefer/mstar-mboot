//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (“MStar Software”) are intellectual property of MStar Semiconductor, Inc. (“MStar”) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar.
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (“Terms”) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party’s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party’s software.
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar’s confidential information and you agree to keep MStar’s confidential information in strictest confidence and not disclose to any third party.
//4. MStar Software is provided on an “AS IS” basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.
//   In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer’s product (“Services”).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an “AS IS” basis and the warranty disclaimer set forth in Section 4 above shall apply.
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.
//   The arbitration award shall be final and binding to both parties.
//
//本處所有軟體、韌體及相關文檔(下稱「MStar Software」)均為MStar Semiconductor, Inc. (下稱「MStar」)之智慧財產權並為相關法律(包括但不限於著作權法及國際條約)所保護，任何未經MStar事前書面野i之使用、修改、重製、傳送或公開均為禁止的。
//一旦您進入、瀏覽或使用MStar Software，您即聲明您已詳讀、了解並同意為下列條款（下稱「本條款」）所拘束並將遵守相關法規之規定：
//
//1.	MStar仍保有MStar Software及其修改物／衍生物之任何與全部的權利、所有權及利益，您並未因本條款而取得關於MStar Software及其修改物／衍生物之任何與全部的權利、所有權及利益。
//2.	您了解MStar Software可能含有或結合有屬於第三人之軟體或係與第三人之軟體一併提供，而使用MStar Software可能需另行向第三人取得授權，因此您同意您將自行負責向此等第三人取得授權以合法使用MStar Software。
//3.	MStar Software及其修改物／衍生物應被視為MStar的機密資訊，您同意將以最機密保存MStar的機密資訊且不將之揭露予任何第三人。
//4.	MStar Software係「依現狀」所提供而無任何擔保。MStar於此否認對MStar Software提供任何擔保，包括但不限於可商品化、不侵權、符合特定使用目的、無瑕疵及符合任何國際標準之擔保。您同意將不會對MStar主張您因使用MStar Software所生之任何損失、損害、費用或支出。於任何情況下，MStar對於直接的、間接的、附帶的或必然的損害均不負責任，包括但不限於利潤營收損失、資料之毀損遺失及系統被未經授權使用。您並同意，除雙方另有書面協議外，即使MStar曾依您的要求或指示而修改MStar Software，本第4條之規定仍繼續適用而不受影響。
//5.	如經要求，MStar不時將提供技術支援或服務予您，以利您的產品可以與MStar Software一同使用(下稱「服務」)，您了解並同意，除雙方另有書面協議外，所有服務均係「以現狀」提供，第4條之不提供擔保相關規定亦應適用之。
//6.	本條款之任何條款不得被解釋為(無論依默示、禁反言原則或其它)：(a) 授予任何權利以使用MStar之名稱、商標、服務標章、符號或其它識別圖像；(b)課予MStar或其關係企業提供予任何人(包括但不限於您及您的客戶)任何形式的協助或資訊的義務；或(c) 授予任何智慧財產權。
//7.	本條款應依中華民國法律為準據法(不含其衝突法則)。任何基於本條款所生或與本條款相關之爭議最終應依中華民國仲裁法及該協會之仲裁規則解決，仲裁應由3名仲裁人以英文在台灣台北進行，仲裁人應依中華民國仲裁協會之仲裁規則選出，仲裁判斷應為終局的且對雙方均有拘束力。
//***********************************************************************************
//<MStar Software>
#ifndef __UNFD_K2_LINUX_H__
#define __UNFD_K2_LINUX_H__

#include <asm/io.h>
#include <linux/string.h>
#include <common.h>
#include <jffs2/load_kernel.h>

#define REG_BANK_CLKGEN                     (0x580)
#define REG_BANK_CHIPTOP                    (0xF00)
#define REG_BANK_FCIE0                      (0x8980)
#define REG_BANK_FCIE2                      (0x8A00)
#define REG_BANK_TIMER0                     (0x1800)

#define RIU_PM_BASE                         0xBF000000
#define RIU_BASE                            0xBF200000

#define MPLL_CLK_REG_BASE_ADDR        (RIU_BASE+(REG_BANK_CLKGEN<<REG_OFFSET_SHIFT_BITS))
#define CHIPTOP_REG_BASE_ADDR       (RIU_BASE+(REG_BANK_CHIPTOP<<REG_OFFSET_SHIFT_BITS))
#define FCIE_REG_BASE_ADDR          (RIU_BASE+(REG_BANK_FCIE0<<REG_OFFSET_SHIFT_BITS))
#define FCIE_NC_CIFD_BASE         (RIU_BASE+(REG_BANK_FCIE2<<REG_OFFSET_SHIFT_BITS))
#define TIMER0_REG_BASE_ADDR        (RIU_PM_BASE+(REG_BANK_TIMER0<<REG_OFFSET_SHIFT_BITS))

#define REG(Reg_Addr)                       (*(volatile U16*)(Reg_Addr))
#define REG_OFFSET_SHIFT_BITS               2
#define GET_REG_ADDR(x, y)                  (x+((y)<<REG_OFFSET_SHIFT_BITS))

#define REG_WRITE_UINT16(reg_addr, val)     REG(reg_addr) = val
#define REG_READ_UINT16(reg_addr, val)      val = REG(reg_addr)
#define HAL_WRITE_UINT16(reg_addr, val)     (REG(reg_addr) = val)
#define HAL_READ_UINT16(reg_addr, val)      val = REG(reg_addr)
#define REG_SET_BITS_UINT16(reg_addr, val)  REG(reg_addr) |= (val)
#define REG_CLR_BITS_UINT16(reg_addr, val)  REG(reg_addr) &= ~(val)
#define REG_W1C_BITS_UINT16(reg_addr, val)  REG_WRITE_UINT16(reg_addr, REG(reg_addr)&(val))

#define REG50_ECC_CTRL_INIT_VALUE           0

#define UNFD_ST_PLAT                        0x80000000
#define IF_IP_VERIFY                        0 // [CAUTION]: to verify IP and HAL code, defaut 0

#define NAND_PAD_BYPASS_MODE	            1

// debug
#define FCIE3_DUMP_DEBUG_BUS                1

#define SPARE640B_CIFD512B_PATCH    		1

#if (defined(FCIE4_DDR) && FCIE4_DDR)
#define NC_SET_DDR_MODE()                   REG_WRITE_UINT16(NC_DDR_CTRL, pNandDrv->u16_Reg58_DDRCtrl);
#define NC_CLR_DDR_MODE()                   REG_CLR_BITS_UINT16(NC_DDR_CTRL, BIT_DDR_MASM);
#else
#define NC_SET_DDR_MODE()
#define NC_CLR_DDR_MODE()
#endif

#define NC_SEL_FCIE3                        1
#if NC_SEL_FCIE3
#include "drvNAND_reg_v3.h"
#else
#error "Error! no FCIE registers selected."
#endif

#define IF_FCIE_SHARE_PINS                  1 // 1: need to nand_pads_switch at HAL's functions.
#define IF_FCIE_SHARE_CLK                   0 // 1: need to nand_clock_setting at HAL's functions.
#define IF_FCIE_SHARE_IP                    0

#define ENABLE_NAND_INTERRUPT_MODE          0

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
#ifdef __FPGA_MODE__  // currently G1 don't care this macro, even in ROM code
#define NAND_DRIVER_ENV                     NAND_ENV_FPGA
#else
#define NAND_DRIVER_ENV                     NAND_ENV_ASIC
#endif

#define UNFD_CACHE_LINE                     0x80
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
#define NAND_DEBUG_MSG                      1
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
#define nand_print_tmt            //msPrintfFunc
#define nand_printf            printf
#define nand_debug(dbg_lv, tag, str, ...)       \
  do {                        \
    if (dbg_lv > UNFD_DEBUG_LEVEL)        \
      break;                  \
    else {                    \
      if (tag)                  \
      {                                       \
        nand_printf(__func__);        \
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

#define nand_die()                              \
  do {                                          \
    nand_printf(__func__);                      \
    nand_printf("\nUNFD Assert(%d)", __LINE__); \
    nand_assert(0);                             \
  } while(0);

#define nand_stop() \
  while(1)  nand_reset_WatchDog();

//=====================================================
// HW Timer for Delay
//=====================================================
#define TIMER0_ENABLE                       GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x10)
#define TIMER0_HIT                          GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x11)
#define TIMER0_MAX_LOW                      GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x12)
#define TIMER0_MAX_HIGH                     GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x13)
#define TIMER0_CAP_LOW                      GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x14)
#define TIMER0_CAP_HIGH                     GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x15)

#define TIMER1_ENABLE                       GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x20)
#define TIMER1_HIT                          GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x21)
#define TIMER1_MAX_LOW                      GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x22)
#define TIMER1_MAX_HIGH                     GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x23)
#define TIMER1_CAP_LOW                      GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x24)
#define TIMER1_CAP_HIGH                     GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x25)

#define NAND_SPEED_TEST                     0

#define HW_TIMER_DELAY_1us                  1
#define HW_TIMER_DELAY_10us                 10
#define HW_TIMER_DELAY_100us                100
#define HW_TIMER_DELAY_1ms                  (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms                  (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms                 (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms                (100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms                (500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s                   (1000 * HW_TIMER_DELAY_1ms)

extern void delay_us( unsigned us );
extern U32  nand_hw_timer_delay(U32 u32usTick);

//=====================================================
// Pads Switch
//=====================================================
#define reg_allpad_in                       GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x50)
#define reg_nf_en             GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x06)
#define reg_ts1_mode            GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x02)
#define reg_boot_from_pf          GET_REG_ADDR(CHIPTOP_REG_BASE_ADDR, 0x01)

extern U32 nand_pads_switch(U32 u32EnableFCIE);

//=====================================================
// set FCIE clock
//=====================================================
#define NFIE_CLK_MASK                       (BIT5|BIT4|BIT3|BIT2)
#define NFIE_CLK_300K            (0)
#define NFIE_CLK_750K            (BIT2)
#define NFIE_CLK_5_4M           (BIT3)
#define NFIE_CLK_13_5M            (BIT3|BIT2)
#define NFIE_CLK_18M            (BIT4)
#define NFIE_CLK_22_7M            (BIT4|BIT2)
#define NFIE_CLK_27M            (BIT4|BIT3)
#define NFIE_CLK_32M            (BIT4|BIT3|BIT2)
#define NFIE_CLK_43M            (BIT5)
#define NFIE_CLK_54M            (BIT5|BIT2)
#define NFIE_CLK_72M            (BIT5|BIT3)
#define NFIE_CLK_86M                        (BIT5|BIT3|BIT2)
#define NFIE_CLK_SSC            (BIT5|BIT4)
#define NFIE_CLK_XTAL           (BIT5|BIT4|BIT2)
#define NFIE_CLK_62M            (BIT5|BIT4|BIT3)

#define DUTY_CYCLE_PATCH                    0 // 1: to enlarge low width for tREA's worst case of 25ns
#if DUTY_CYCLE_PATCH
#define FCIE3_SW_DEFAULT_CLK                NFIE_CLK_86M
#define FCIE_REG41_VAL                      ((2<<9)|(2<<3)) // RE,WR pulse, Low:High=3:1
#define REG57_ECO_FIX_INIT_VALUE            0
#else
#define FCIE3_SW_DEFAULT_CLK                NFIE_CLK_54M
#define FCIE_REG41_VAL                      0               // RE,WR pulse, Low:High=1:1
#define REG57_ECO_FIX_INIT_VALUE            BIT_NC_LATCH_DATA_1_0_T // delay 1.0T
#define FCIE_EXTEND_tWW			1
#endif
#define FCIE3_SW_SLOWEST_CLK                NFIE_CLK_5_4M

#define NAND_SEQ_ACC_TIME_TOL               10 //in unit of ns

#define reg_ckg_fcie                        GET_REG_ADDR(MPLL_CLK_REG_BASE_ADDR, 0x64)

extern U32  nand_clock_setting(U32 u32ClkParam);
extern void nand_DumpPadClk(void);

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
  U8 *pu8_PageSpareBuf;
  U8 *pu8_PageDataBuf;
  U32 u32_DMAAddrOffset;
  U32 u32_RAMBufferOffset;
  U32 u32_RAMBufferLen;

}NAND_DRIVER_PLAT_CTX, *P_NAND_DRIVER_PLAT;


#define NC_REG_MIU_LAST_DONE                NC_MIE_EVENT

extern void flush_cache(U32 start_addr, U32 size);
extern void Chip_Flush_Memory(void);
extern void Chip_Read_Memory(void);

extern int memcmp(const void *,const void *, unsigned int);
extern void *malloc(unsigned int);
extern void free(void*);

int printf(const char *format, ...);

#define NANDINFO_ECC_TYPE ECC_TYPE_24BIT1KB

#endif
