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
#ifndef __eMMC_NADAL_UBOOT__
#define __eMMC_NADAL_UBOOT__

#include <common.h>
#include <malloc.h>
#include <linux/string.h>

#include <config.h>
#include <command.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <asm/errno.h>

#include "drvWDT.h"
#include "MsCommon.h"
#include <watchdog.h>


//=====================================================
// HW registers
//=====================================================
#define REG_OFFSET_SHIFT_BITS    2

#define REG_FCIE_U16(Reg_Addr)  (*(volatile U16*)(Reg_Addr))
#define GET_REG_ADDR(x, y)      ((x)+((y) << REG_OFFSET_SHIFT_BITS))

#define REG_FCIE(reg_addr)              REG_FCIE_U16(reg_addr)
#define REG_FCIE_W(reg_addr, val)       REG_FCIE(reg_addr) = (val)
#define REG_FCIE_R(reg_addr, val)       val = REG_FCIE(reg_addr)
#define REG_FCIE_SETBIT(reg_addr, val)  REG_FCIE(reg_addr) |= (val)
#define REG_FCIE_CLRBIT(reg_addr, val)  REG_FCIE(reg_addr) &= ~(val)
#define REG_FCIE_W1C(reg_addr, val)     REG_FCIE_W(reg_addr, REG_FCIE(reg_addr)&(val))

//------------------------------
#define RIU_PM_BASE             0x1F000000
#define RIU_BASE                0x1F200000

#define REG_BANK_FCIE0          0x8980
#define REG_BANK_FCIE1          0x89E0
#define REG_BANK_FCIE2          0x8A00

#define FCIE0_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE0)
#define FCIE1_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE1)
#define FCIE2_BASE              GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2)

#define FCIE_REG_BASE_ADDR      FCIE0_BASE
#define FCIE_CIFC_BASE_ADDR     FCIE1_BASE
#define FCIE_CIFD_BASE_ADDR     FCIE2_BASE

#include "eMMC_reg.h"

//------------------------------ [FIXME]: refer to Bring-up Note -->
// Mobile CMU = TV CLKGEN
// TV CNM don't touch
#define REG_BANK_CLKGEN         0x580
#define CLKGEN_BASE             GET_REG_ADDR(RIU_BASE, REG_BANK_CLKGEN)
#define reg_ckg_nfie_div4_en    GET_REG_ADDR(CLKGEN_BASE, 0x65)
#define BIT_FCIE_CLK_DIV4_EN    BIT14

#define reg_ckg_fcie            GET_REG_ADDR(CLKGEN_BASE, 0x31)
#define BIT_FCIE_CLK_Gate       BIT8
#define BIT_FCIE_CLK_Inverse    BIT9
#define BIT_FCIE_CLK_MASK       (BIT10|BIT11|BIT12|BIT13)
#define BIT_FCIE_CLK_SHIFT      10

#define BIT_FCIE_CLK_12M        1
#define BIT_FCIE_CLK_18M        3
#define BIT_FCIE_CLK_27M        5
#define BIT_FCIE_CLK_36M        6
#define BIT_FCIE_CLK_40M        7
#define BIT_FCIE_CLK_48M        8
#define BIT_FCIE_CLK_300K       12

#define BIT_FCIE_CLK4X_12M      1
#define BIT_FCIE_CLK4X_18M      3
#define BIT_FCIE_CLK4X_27M      5
#define BIT_FCIE_CLK4X_36M      6
#define BIT_FCIE_CLK4X_40M      7
#define BIT_FCIE_CLK4X_48M      8


#define eMMC_FCIE_VALID_CLK_CNT 5 // FIXME
extern  U8 gau8_FCIEClkSel[];

//------------------------------
#define REG_BANK_CHIPTOP        0xF00
#define PAD_CHIPTOP_BASE        GET_REG_ADDR(RIU_BASE, REG_BANK_CHIPTOP)

#define reg_chiptop_0x0C    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x0C)
#define reg_chiptop_0x42    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x42)
#define reg_chiptop_0x5B    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x5B)
#define reg_chiptop_0x12    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x12)
#define reg_chiptop_0x4F    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x4F)
#define reg_chiptop_0x64    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x64)
#define reg_chiptop_0x5B    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x5B)
#define reg_chiptop_0x51    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x51)
#define reg_chiptop_0x1F    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x1F)
#define reg_chiptop_0x77    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x77)

#define reg_chiptop_0x43        GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x43)
#define BIT_PAD_BYPASS_MACRO    BIT1
#define BIT_eMMC_RSTPIN_EN      BIT3
#define BIT_eMMC_RSTPIN_VAL     BIT4

#define reg_chiptop_0x50        GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x50)
#define BIT_ALL_PAD_IN          BIT15

#define reg_chiptop_0x0B        GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x0B)
#define BIT_NAND_CS2_EN         BIT0
#define BIT_NAND_CS3_EN         BIT1
#define BIT_NAND_CFG_MASK       (BIT12|BIT13|BIT14)

#define reg_chiptop_0x5D        GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x5D)
#define BIT_eMMC_CFG_MASK       (BIT14|BIT15)
#define BIT_eMMC_CFG_MODE1      (BIT14)

#define reg_emmc_drv            GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x59)
#define CFG_EMMC_CMD_STRENGTH   BIT12
#define CFG_EMMC_CLK_STRENGTH   BIT13

#define reg_nand_drv            GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x0C)
#define CFG_NAND_DRV_STRENGTH   (BIT8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15)

#define reg_chip_dummy1         GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x1D)
#define BIT_DDR_TIMING_PATCH    BIT0

#define eMMC_RST_L()    {REG_FCIE_SETBIT(reg_chiptop_0x43, BIT_eMMC_RSTPIN_EN);\
                         REG_FCIE_CLRBIT(reg_chiptop_0x43, BIT_eMMC_RSTPIN_VAL);}
#define eMMC_RST_H()     REG_FCIE_SETBIT(reg_chiptop_0x43, BIT_eMMC_RSTPIN_EN|BIT_eMMC_RSTPIN_VAL)

#define REG_BANK_TIMER1         0x1800
#define TIMER1_BASE             GET_REG_ADDR(RIU_PM_BASE, REG_BANK_TIMER1)

#define TIMER1_ENABLE           GET_REG_ADDR(TIMER1_BASE, 0x20)
#define TIMER1_HIT              GET_REG_ADDR(TIMER1_BASE, 0x21)
#define TIMER1_MAX_LOW          GET_REG_ADDR(TIMER1_BASE, 0x22)
#define TIMER1_MAX_HIGH         GET_REG_ADDR(TIMER1_BASE, 0x23)
#define TIMER1_CAP_LOW          GET_REG_ADDR(TIMER1_BASE, 0x24)
#define TIMER1_CAP_HIGH         GET_REG_ADDR(TIMER1_BASE, 0x25)

//--------------------------------power saving mode----------------------------
#define reg_vplug_in_pwrgd              GET_REG_ADDR(RIU_PM_BASE+0x1C00, 0x62)
#define REG_BANK_PM_SLEEP               (0x700)
#define PM_SLEEP_REG_BASE_ADDR          GET_REG_ADDR(RIU_PM_BASE, REG_BANK_PM_SLEEP)
#define reg_pwrgd_int_glirm             GET_REG_ADDR(PM_SLEEP_REG_BASE_ADDR, 0x61)
#define BIT_PWRGD_INT_GLIRM_EN          BIT9
#define BIT_PWEGD_INT_GLIRM_MASK        (BIT15|BIT14|BIT13|BIT12|BIT11|BIT10)

//=====================================================
// API declarations
//=====================================================
extern  U32 eMMC_hw_timer_delay(U32 u32us);
extern  U32 eMMC_hw_timer_sleep(U32 u32ms);
#define eMMC_HW_TIMER_HZ    12000000//12MHz  [FIXME]
#define FCIE_eMMC_DISABLE    0
#define FCIE_eMMC_DDR        1
#define FCIE_eMMC_SDR        2
#define FCIE_eMMC_BYPASS     3
#define FCIE_tSD_BYPASS     4
#define FCIE_tSD_SDR        5
#define FCIE_DEFAULT_PAD     FCIE_eMMC_BYPASS // [FIXME]

extern  U32 eMMC_pads_switch(U32 u32_FCIE_IF_Type);
extern  U32 eMMC_clock_setting(U16 u16_ClkParam);
extern void eMMC_set_WatchDog(U8 u8_IfEnable);
extern void eMMC_reset_WatchDog(void);
extern  U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void eMMC_flush_data_cache_buffer(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void eMMC_Invalidate_data_cache_buffer(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void eMMC_flush_miu_pipe(void);
extern  U32 eMMC_PlatformResetPre(void);
extern  U32 eMMC_PlatformResetPost(void);
extern  U32 eMMC_PlatformInit(void);
extern  U32 eMMC_CheckIfMemCorrupt(void);
extern void eMMC_DumpPadClk(void);
#define eMMC_BOOT_PART_W   BIT0
#define eMMC_BOOT_PART_R   BIT1
extern  U32 eMMC_BootPartitionHandler_WR(U8 *pDataBuf, U16 u16_PartType, U32 u32_StartSector, U32 u32_SectorCnt, U8 u8_OP);
extern  U32 eMMC_BootPartitionHandler_E(U16 u16_PartType);
extern  U32 eMMC_hw_timer_start(void);
extern  U32 eMMC_hw_timer_tick(void);


//=====================================================
// partitions config
//=====================================================
// every blk is 512 bytes (reserve 2MB-64KB for internal use)
#define eMMC_DRV_RESERVED_BLK_CNT       ((0x200000-0x10000)/0x200)

#define eMMC_CIS_NNI_BLK_CNT            2
#define eMMC_CIS_PNI_BLK_CNT            2
#define eMMC_TEST_BLK_CNT               (0x100000/0x200) // 1MB

#define eMMC_CIS_BLK_0                  (64*1024/512) // from 64KB
#define eMMC_NNI_BLK_0                  (eMMC_CIS_BLK_0+0)
#define eMMC_NNI_BLK_1                  (eMMC_CIS_BLK_0+1)
#define eMMC_PNI_BLK_0                  (eMMC_CIS_BLK_0+2)
#define eMMC_PNI_BLK_1                  (eMMC_CIS_BLK_0+3)
#define eMMC_DDRTABLE_BLK_0             (eMMC_CIS_BLK_0+4)
#define eMMC_DDRTABLE_BLK_1             (eMMC_CIS_BLK_0+5)
#define eMMC_DrvContext_BLK_0           (eMMC_CIS_BLK_0+6)
#define eMMC_DrvContext_BLK_1           (eMMC_CIS_BLK_0+7)
#define eMMC_ALLRSP_BLK_0               (eMMC_CIS_BLK_0+8)
#define eMMC_ALLRSP_BLK_1               (eMMC_CIS_BLK_0+9)
#define eMMC_BURST_LEN_BLK_0            (eMMC_CIS_BLK_0+10)
#define eMMC_LIFE_TEST_BYTE_CNT_BLK     (eMMC_CIS_BLK_0+11)

#define eMMC_CIS_BLK_END                eMMC_LIFE_TEST_BYTE_CNT_BLK
// last 1MB in reserved area, use for eMMC test
#define eMMC_TEST_BLK_0                 (eMMC_CIS_BLK_END+1)
#define eMMC_TOTAL_RESERVED_BLK_CNT     (eMMC_DRV_RESERVED_BLK_CNT+eMMC_CIS_BLK_0)

//=====================================================
// Driver configs
//=====================================================
#define eMMC_UPDATE_FIRMWARE                0

#define eMMC_ST_PLAT                        0x80000000
// [CAUTION]: to verify IP and HAL code, defaut 0
#define IF_IP_VERIFY                        1 // [FIXME] -->
// [CAUTION]: to detect DDR timiing parameters, only for DL
#define IF_DETECT_eMMC_DDR_TIMING           1
#define eMMC_IF_TUNING_TTABLE()               (g_eMMCDrv.u32_DrvFlag&DRV_FLAG_TUNING_TTABLE)

// need to eMMC_pads_switch
// need to eMMC_clock_setting
#define IF_FCIE_SHARE_IP                    1

//------------------------------
#define FICE_BYTE_MODE_ENABLE               1 // always 1
#define ENABLE_eMMC_INTERRUPT_MODE          0
#define ENABLE_eMMC_RIU_MODE                0 // for debug cache issue

#if ENABLE_eMMC_RIU_MODE
#undef IF_DETECT_eMMC_DDR_TIMING
#define IF_DETECT_eMMC_DDR_TIMING           0 // RIU mode can NOT use DDR
#endif
// <-- [FIXME]

//------------------------------
#define eMMC_FEATURE_RELIABLE_WRITE         1
#if eMMC_UPDATE_FIRMWARE
#undef  eMMC_FEATURE_RELIABLE_WRITE
#define eMMC_FEATURE_RELIABLE_WRITE         0
#endif

//------------------------------
#define eMMC_RSP_FROM_RAM                   0
#define eMMC_BURST_LEN_AUTOCFG              1

//------------------------------
#define eMMC_SECTOR_BUF_BYTECTN             eMMC_SECTOR_BUF_16KB
extern U8 gau8_eMMC_SectorBuf[];
extern U8 gau8_eMMC_PartInfoBuf[];

//------------------------------
#ifdef CONFIG_TSD
    #define USE_SD_PAD_2_DEVELOP_TSD    0 // develop with SD card use only

    #if defined USE_SD_PAD_2_DEVELOP_TSD && USE_SD_PAD_2_DEVELOP_TSD
        #undef  FCIE_DEFAULT_PAD
        #define FCIE_DEFAULT_PAD    FCIE_tSD_BYPASS
    #endif
#endif

//=====================================================
// parameter for ROM code (mobile legacy)
//=====================================================
//------------------------------
// Boot Partition:
//   [FIXME]: if platform has ROM code like G2P
//------------------------------
//  No Need in A3
#define BL_BLK_OFFSET          0
#define BL_BLK_CNT            (0xF200/0x200)
#define OTP_BLK_OFFSET         BL_BLK_CNT
#define OTP_BLK_CNT           (0x8000/0x200)
#define SecInfo_BLK_OFFSET    (BL_BLK_CNT+OTP_BLK_CNT)
#define SecInfo_BLK_CNT       (0x1000/0x200)
#define BOOT_PART_TOTAL_CNT   (BL_BLK_CNT+OTP_BLK_CNT+SecInfo_BLK_CNT)
// <-- [FIXME]

#define eMMC_CACHE_LINE        0x20 // [FIXME]

//=====================================================
// tool-chain attributes
//===================================================== [FIXME] -->
#define eMMC_PACK0
#define eMMC_PACK1                  __attribute__((__packed__))
#define eMMC_ALIGN0
#define eMMC_ALIGN1                 __attribute__((aligned(eMMC_CACHE_LINE)))
// <-- [FIXME]

//=====================================================
// debug option
//=====================================================
#define eMMC_TEST_IN_DESIGN                 0 // [FIXME]: set 1 to verify HW timer

#ifndef eMMC_DEBUG_MSG
#define eMMC_DEBUG_MSG                      1
#endif

/* Define trace levels. */
#define eMMC_DEBUG_LEVEL_ERROR              (1)    /* Error condition debug messages. */
#define eMMC_DEBUG_LEVEL_WARNING            (2)    /* Warning condition debug messages. */
#define eMMC_DEBUG_LEVEL_HIGH               (3)    /* Debug messages (high debugging). */
#define eMMC_DEBUG_LEVEL_MEDIUM             (4)    /* Debug messages. */
#define eMMC_DEBUG_LEVEL_LOW                (5)    /* Debug messages (low debugging). */

/* Higer debug level means more verbose */
#ifndef eMMC_DEBUG_LEVEL
#define eMMC_DEBUG_LEVEL                    eMMC_DEBUG_LEVEL_WARNING
#endif

#if defined(eMMC_DEBUG_MSG) && eMMC_DEBUG_MSG
#define eMMC_printf    printf                       // <-- [FIXME]
#define eMMC_debug(dbg_lv, tag, str, ...)            \
    do {                                             \
        if (dbg_lv > eMMC_DEBUG_LEVEL)               \
            break;                                   \
        else if(eMMC_IF_TUNING_TTABLE())             \
            break;                                   \
        else if(eMMC_IF_DISABLE_LOG())               \
			break;                                   \
		else {                                       \
            if (tag)                                 \
                eMMC_printf("[ %s() ] ", __func__);\
                                                     \
            eMMC_printf(str, ##__VA_ARGS__);         \
        } \
    } while(0)
#else /* eMMC_DEBUG_MSG */
#define eMMC_printf(...)
#define eMMC_debug(enable, tag, str, ...)   do{}while(0)
#endif /* eMMC_DEBUG_MSG */

#define eMMC_die(msg) while(1);//SYS_FAIL(""msg);

#define eMMC_stop() \
    while(1)  eMMC_reset_WatchDog();

//=====================================================
// unit for HW Timer delay (unit of us)
//=====================================================
#define HW_TIMER_DELAY_1us      1
#define HW_TIMER_DELAY_5us      5
#define HW_TIMER_DELAY_10us     10
#define HW_TIMER_DELAY_100us    100
#define HW_TIMER_DELAY_500us    500
#define HW_TIMER_DELAY_1ms      (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms      (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms     (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms    (100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms    (500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s       (1000 * HW_TIMER_DELAY_1ms)

//=====================================================
// set FCIE clock
//=====================================================
// [FIXME] -->
#define FCIE_SLOWEST_CLK                BIT_FCIE_CLK_300K
#define FCIE_SLOW_CLK                   BIT_FCIE_CLK_18M
#if (FCIE_DEFAULT_PAD == FCIE_eMMC_BYPASS)
#define FCIE_DEFAULT_CLK                BIT_FCIE_CLK_27M
#else
#define FCIE_DEFAULT_CLK                BIT_FCIE_CLK_48M
#endif

// <-- [FIXME]
//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS                  3 // 8 bytes width [FIXME]
/*
 * Important:
 * The following buffers should be large enough for a whole eMMC block
 */
// FIXME, this is only for verifing IP
#define DMA_W_ADDR                          0x80C00000
#define DMA_R_ADDR                          0x80D00000
#define DMA_W_SPARE_ADDR                    0x80E00000
#define DMA_R_SPARE_ADDR                    0x80E80000
#define DMA_BAD_BLK_BUF                     0x80F00000


//=====================================================
// misc
//=====================================================
//#define BIG_ENDIAN
#define LITTLE_ENDIAN

#if (defined(BIT_DQS_MODE_MASK) && (BIT_DQS_MODE_MASK != (BIT12|BIT13|BIT14)))

#undef BIT_DQS_MODE_MASK
#undef BIT_DQS_MODE_2T
#undef BIT_DQS_MODE_1_5T
#undef BIT_DQS_MODE_2_5T
#undef BIT_DQS_MODE_1T

#define BIT_DQS_MODE_MASK               (BIT12|BIT13|BIT14)
#define BIT_DQS_MODE_0T                 (0 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_0_5T               (1 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_1T                 (2 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_1_5T               (3 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_2T                 (4 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_2_5T               (5 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_3T                 (6 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_3_5T               (7 << BIT_DQS_MDOE_SHIFT)

#endif


#endif /* __eMMC_G2P_UBOOT__ */
