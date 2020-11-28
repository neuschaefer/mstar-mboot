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
#ifndef __eMMC_KAISER_UBOOT__
#define __eMMC_KAISER_UBOOT__

#include <common.h>
#include <malloc.h>
#include <linux/string.h>

#include <config.h>
#include <command.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <asm/errno.h>
#include <watchdog.h>


#ifndef U32
#define U32  unsigned int
#endif
#ifndef U16
#define U16  unsigned short
#endif
#ifndef U8
#define U8   unsigned char
#endif
#ifndef S32
#define S32  signed long
#endif
#ifndef S16
#define S16  signed short
#endif
#ifndef S8
#define S8   signed char
#endif


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

//------------------------------
#define RIU_PM_BASE                     0x1F000000
#define RIU_BASE                        0x1F200000

#define REG_BANK_FCIE0                  0x8980
#define REG_BANK_FCIE1                  0x89E0
#define REG_BANK_FCIE2                  0x8A00

#define FCIE0_BASE                      GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE0)
#define FCIE1_BASE                      GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE1)
#define FCIE2_BASE                      GET_REG_ADDR(RIU_BASE, REG_BANK_FCIE2)

#define FCIE_REG_BASE_ADDR              FCIE0_BASE
#define FCIE_CIFC_BASE_ADDR             FCIE1_BASE
#define FCIE_CIFD_BASE_ADDR             FCIE2_BASE

#include "eMMC_reg.h"

//------------------------------
#define REG_BANK_CLKGEN                 0x580
#define CLKGEN_BASE                     GET_REG_ADDR(RIU_BASE, REG_BANK_CLKGEN)
#define reg_ckg_fcie_1X                 GET_REG_ADDR(CLKGEN_BASE, 0x64)
#define reg_ckg_fcie_4X                 GET_REG_ADDR(CLKGEN_BASE, 0x64)
#define BIT_FCIE_CLK_Gate               BIT0
#define BIT_FCIE_CLK_Inverse            BIT1
#define BIT_FCIE_CLK_MASK               (BIT2|BIT3|BIT4|BIT5)
#define BIT_FCIE_CLK_SHIFT              2
#define BIT_FCIE_CLK_SEL                BIT6 // 1: NFIE, 0: 12MHz
#define BIT_FCIE_CLK4X_Gate             BIT8
#define BIT_FCIE_CLK4X_Inverse          BIT9
#define BIT_FCIE_CLK4X_MASK             (BIT10|BIT11|BIT12|BIT13)
#define BIT_FCIE_CLK4X_SHIFT            10

#define reg_ckg_MCU                     GET_REG_ADDR(CLKGEN_BASE, 0x10)
#define reg_ckg_MIU                     GET_REG_ADDR(CLKGEN_BASE, 0x1D)

#define BIT_FCIE_CLK_300K               0
#define BIT_FCIE_CLK_18M                1
#define BIT_FCIE_CLK_27M                3
#define BIT_FCIE_CLK_36M                5
#define BIT_FCIE_CLK_40M                6
#define BIT_FCIE_CLK_43M                8
#define BIT_FCIE_CLK_48M                9


#define BIT_FCIE_CLK4X_18M              1
#define BIT_FCIE_CLK4X_27M              3
#define BIT_FCIE_CLK4X_36M              5
#define BIT_FCIE_CLK4X_40M              6
#define BIT_FCIE_CLK4X_43M              8
#define BIT_FCIE_CLK4X_48M              9


#define BIT_FCIE_CLK4X_DIV4             15 

#define eMMC_FCIE_VALID_CLK_CNT         6
extern  U8 gau8_FCIEClkSel[];

//--------------------------sd/eMMC/nand Mode
#define REG_BANK_CHIPTOP                0x0F00
#define PAD_CHIPTOP_BASE                GET_REG_ADDR(RIU_BASE, REG_BANK_CHIPTOP)

#define reg_fcie2macro_sd_bypass        GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x35)
#define BIT_SD_USE_BYPASS               BIT7
#define BIT_FCIE2MACRO_SD_BYPASS        BIT6
#define BIT_reg_emmc_rstn_en            BIT5
#define BIT_reg_emmc_rstn               BIT4
#define BIT_PAD_IN_SEL_SD               BIT1
#define BIT_PAD_IN_SEL_SDIO             BIT0

#define reg_all_pad_in                  GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x50)
#define BIT_ALL_PAD_IN                  BIT15

#define reg_emmc_pad                    GET_REG_ADDR(PAD_CHIPTOP_BASE, 0x06)
#define CFG_EMMC_PAD_MASK               (BIT12|BIT13)
#define CFG_SD_PAD_MASK                 (BIT14|BIT15)
#define CFG_NAND_PAD_MASK               (BIT0|BIT1)
#define BIT_EMMC_PAD_MODE1               BIT12


#define eMMC_DBUS_WIDTH                 8

#define eMMC_RST_L()     {REG_FCIE_SETBIT(reg_fcie2macro_sd_bypass, BIT_reg_emmc_rstn_en);\
	                         REG_FCIE_CLRBIT(reg_fcie2macro_sd_bypass, BIT_reg_emmc_rstn);}
#define eMMC_RST_H()     REG_FCIE_SETBIT(reg_fcie2macro_sd_bypass,BIT_reg_emmc_rstn_en|BIT_reg_emmc_rstn)

#define REG_BANK_TIMER1                 0x1820
#define TIMER1_BASE                     GET_REG_ADDR(RIU_PM_BASE, REG_BANK_TIMER1)

#define TIMER1_ENABLE                   GET_REG_ADDR(TIMER1_BASE, 0x00)
#define TIMER1_HIT                      GET_REG_ADDR(TIMER1_BASE, 0x01)
#define TIMER1_MAX_LOW                  GET_REG_ADDR(TIMER1_BASE, 0x02)
#define TIMER1_MAX_HIGH                 GET_REG_ADDR(TIMER1_BASE, 0x03)
#define TIMER1_CAP_LOW                  GET_REG_ADDR(TIMER1_BASE, 0x04)
#define TIMER1_CAP_HIGH                 GET_REG_ADDR(TIMER1_BASE, 0x05)

//=====================================================
// API declarations
//=====================================================
extern  U32 eMMC_hw_timer_delay(U32 u32us);
extern  U32 eMMC_hw_timer_sleep(U32 u32ms);

#define eMMC_HW_TIMER_HZ               12000000//(384*100*1000)  // [FIXME]
#define FCIE_eMMC_DISABLE               0
#define FCIE_eMMC_DDR                   1
#define FCIE_eMMC_SDR                   2
#define FCIE_eMMC_BYPASS                3

extern  U32 eMMC_pads_switch(U32 u32_FCIE_IF_Type);
extern  U32 eMMC_clock_setting(U16 u16_ClkParam);
extern void eMMC_set_WatchDog(U8 u8_IfEnable);
extern void eMMC_reset_WatchDog(void);
extern  U32 eMMC_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void eMMC_Invalidate_data_cache_buffer(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void eMMC_flush_miu_pipe(void);
extern  U32 eMMC_PlatformResetPre(void);
extern  U32 eMMC_PlatformResetPost(void);
extern  U32 eMMC_PlatformInit(void);
extern  U32 eMMC_CheckIfMemCorrupt(void);
extern void eMMC_DumpPadClk(void);
extern void eMMC_flush_data_cache_buffer(U32 u32_DMAAddr, U32 u32_ByteCnt);
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
#define eMMC_TEST_BLK_CNT               (0x100000/0x200)

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
#define eMMC_TOTAL_RESERVED_BLK_CNT     (eMMC_DRV_RESERVED_BLK_CNT+eMMC_CIS_BLK_0)

// last 1MB in reserved area, use for eMMC test
#define eMMC_TEST_BLK_0                 (eMMC_DRV_RESERVED_BLK_CNT-eMMC_CIS_BLK_END)


//=====================================================
// Driver configs
//=====================================================
#define eMMC_UPDATE_FIRMWARE            0

#define eMMC_ST_PLAT                    0x80000000
// [CAUTION]: to verify IP and HAL code, defaut 0
#define IF_IP_VERIFY                    1 // [FIXME] -->
// [CAUTION]: to detect DDR timiing parameters, only for DL
#define IF_DETECT_eMMC_DDR_TIMING       1
#define eMMC_IF_TUNING_TTABLE()           (g_eMMCDrv.u32_DrvFlag&DRV_FLAG_TUNING_TTABLE)

// need to eMMC_pads_switch
// need to eMMC_clock_setting
#define IF_FCIE_SHARE_IP                1

//------------------------------
#define FICE_BYTE_MODE_ENABLE           1 // always 1
#define ENABLE_eMMC_INTERRUPT_MODE      0
#define ENABLE_eMMC_RIU_MODE            0 // for debug cache issue

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

//------------------------------
#define eMMC_RSP_FROM_RAM               0
#define eMMC_BURST_LEN_AUTOCFG          1

//------------------------------
#define eMMC_SECTOR_BUF_BYTECTN         eMMC_SECTOR_BUF_16KB
extern U8 gau8_eMMC_SectorBuf[];
extern U8 gau8_eMMC_PartInfoBuf[];

//------------------------------
// Boot Partition:
//   [FIXME]: if platform has ROM code like G2P
//------------------------------
//	No Need in A3
#define BL_BLK_OFFSET                   0
#define BL_BLK_CNT                      (0xF200/0x200)
#define OTP_BLK_OFFSET                  BL_BLK_CNT
#define OTP_BLK_CNT                     (0x8000/0x200)
#define SecInfo_BLK_OFFSET              (BL_BLK_CNT+OTP_BLK_CNT)
#define SecInfo_BLK_CNT                 (0x1000/0x200)
#define BOOT_PART_TOTAL_CNT             (BL_BLK_CNT+OTP_BLK_CNT+SecInfo_BLK_CNT)
// <-- [FIXME]

#define eMMC_CACHE_LINE                 0x20 // [FIXME]

//=====================================================
// tool-chain attributes
//===================================================== [FIXME] -->
#define eMMC_PACK0
#define eMMC_PACK1                      __attribute__((__packed__))
#define eMMC_ALIGN0
#define eMMC_ALIGN1                     __attribute__((aligned(eMMC_CACHE_LINE)))
// <-- [FIXME]

//=====================================================
// debug option
//=====================================================
#define eMMC_TEST_IN_DESIGN             0 // [FIXME]: set 1 to verify HW timer

#ifndef eMMC_DEBUG_MSG
#define eMMC_DEBUG_MSG                  1
#endif

/* Define trace levels. */
#define eMMC_DEBUG_LEVEL_ERROR          (1)    /* Error condition debug messages. */
#define eMMC_DEBUG_LEVEL_WARNING        (2)    /* Warning condition debug messages. */
#define eMMC_DEBUG_LEVEL_HIGH           (3)    /* Debug messages (high debugging). */
#define eMMC_DEBUG_LEVEL_MEDIUM         (4)    /* Debug messages. */
#define eMMC_DEBUG_LEVEL_LOW            (5)    /* Debug messages (low debugging). */

/* Higer debug level means more verbose */
#ifndef eMMC_DEBUG_LEVEL
#define eMMC_DEBUG_LEVEL                eMMC_DEBUG_LEVEL_WARNING
#endif

#if defined(eMMC_DEBUG_MSG) && eMMC_DEBUG_MSG
#define eMMC_printf    printf                       // <-- [FIXME]
#define eMMC_debug(dbg_lv, tag, str, ...)	         \
	do {	                                         \
		if (dbg_lv > eMMC_DEBUG_LEVEL)				 \
			break;									 \
		else if(eMMC_IF_TUNING_TTABLE())             \
			break;                                   \
		else if(eMMC_IF_DISABLE_LOG())               \
			break;                                   \
		else {										 \
			if (tag)								 \
				eMMC_printf("[ %s() ] ", __func__);\
													 \
			eMMC_printf(str, ##__VA_ARGS__);		 \
		} \
	} while(0)	
#else /* eMMC_DEBUG_MSG */
#define eMMC_printf(...)
#define eMMC_debug(enable, tag, str, ...)	do{}while(0)
#endif /* eMMC_DEBUG_MSG */

#define eMMC_die(msg) while(1);//SYS_FAIL(""msg);

#define eMMC_stop() \
	while(1)  eMMC_reset_WatchDog();

//=====================================================
// unit for HW Timer delay (unit of us)
//=====================================================
#define HW_TIMER_DELAY_1us              1
#define HW_TIMER_DELAY_5us              5
#define HW_TIMER_DELAY_10us             10
#define HW_TIMER_DELAY_100us            100
#define HW_TIMER_DELAY_1ms              (1000 * HW_TIMER_DELAY_1us)
#define HW_TIMER_DELAY_5ms              (5    * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_10ms             (10   * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_100ms            (100  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_500ms            (500  * HW_TIMER_DELAY_1ms)
#define HW_TIMER_DELAY_1s               (1000 * HW_TIMER_DELAY_1ms)

//=====================================================
// set FCIE clock
//=====================================================
#define FCIE_SLOWEST_CLK                BIT_FCIE_CLK_300K
#define FCIE_SLOW_CLK                   BIT_FCIE_CLK_18M 
#define FCIE_DEFAULT_CLK                BIT_FCIE_CLK_48M

//=====================================================
// transfer DMA Address
//=====================================================
#define MIU_BUS_WIDTH_BITS              3 // 8 bytes width [FIXME]
/*
 * Important:
 * The following buffers should be large enough for a whole eMMC block
 */
// FIXME, this is only for verifing IP
#define DMA_W_ADDR                      0x40C00000
#define DMA_R_ADDR                      0x40D00000
#define DMA_W_SPARE_ADDR                0x40E00000
#define DMA_R_SPARE_ADDR                0x40E80000
#define DMA_BAD_BLK_BUF                 0x40F00000


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
