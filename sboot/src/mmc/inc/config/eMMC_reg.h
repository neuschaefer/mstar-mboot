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
#ifndef __eMMC_FCIE_REG_H__
#define __eMMC_FCIE_REG_H__

#ifndef NULL
#define NULL    ((void*)0)
#endif
#ifndef BIT0
#define BIT0    (1<<0)
#endif
#ifndef BIT1
#define BIT1    (1<<1)
#endif
#ifndef BIT2
#define BIT2    (1<<2)
#endif
#ifndef BIT3
#define BIT3    (1<<3)
#endif
#ifndef BIT4
#define BIT4    (1<<4)
#endif
#ifndef BIT5
#define BIT5    (1<<5)
#endif
#ifndef BIT6
#define BIT6    (1<<6)
#endif
#ifndef BIT7
#define BIT7    (1<<7)
#endif
#ifndef BIT8
#define BIT8    (1<<8)
#endif
#ifndef BIT9
#define BIT9    (1<<9)
#endif
#ifndef BIT10
#define BIT10   (1<<10)
#endif
#ifndef BIT11
#define BIT11   (1<<11)
#endif
#ifndef BIT12
#define BIT12   (1<<12)
#endif
#ifndef BIT13
#define BIT13   (1<<13)
#endif
#ifndef BIT14
#define BIT14   (1<<14)
#endif
#ifndef BIT15
#define BIT15   (1<<15)
#endif
#ifndef BIT16
#define BIT16   (1<<16)
#endif
#ifndef BIT17
#define BIT17   (1<<17)
#endif
#ifndef BIT18
#define BIT18   (1<<18)
#endif
#ifndef BIT19
#define BIT19   (1<<19)
#endif
#ifndef BIT20
#define BIT20   (1<<20)
#endif
#ifndef BIT21
#define BIT21   (1<<21)
#endif
#ifndef BIT22
#define BIT22   (1<<22)
#endif
#ifndef BIT23
#define BIT23   (1<<23)
#endif
#ifndef BIT24
#define BIT24   (1<<24)
#endif
#ifndef BIT25
#define BIT25   (1<<25)
#endif
#ifndef BIT26
#define BIT26   (1<<26)
#endif
#ifndef BIT27
#define BIT27   (1<<27)
#endif
#ifndef BIT28
#define BIT28   (1<<28)
#endif
#ifndef BIT29
#define BIT29   (1<<29)
#endif
#ifndef BIT30
#define BIT30   (1<<30)
#endif
#ifndef BIT31
#define BIT31   (1<<31)
#endif

//------------------------------------------------------------------
#define FCIE_MIE_EVENT          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x00)
#define FCIE_MIE_INT_EN         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x01)
#define FCIE_MMA_PRI_REG        GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x02)
#define FCIE_MIU_DMA_26_16      GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x03)
#define FCIE_MIU_DMA_15_0       GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x04)
#define FCIE_CARD_INT_EN		GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x06)
#define FCIE_CARD_POWER         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x08)
#define FCIE_FORCE_INT          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x09)
#define FCIE_PATH_CTRL          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x0A)
#define FCIE_JOB_BL_CNT         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x0B)
#define FCIE_TR_BK_CNT          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x0C)
#define FCIE_RSP_SIZE           GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x0D)
#define FCIE_CMD_SIZE           GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x0E)
#define FCIE_CIFD_WORD_CNT      GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x0F)
#define FCIE_SD_MODE            GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x10)
#define FCIE_SD_CTRL            GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x11)
#define FCIE_SD_STATUS          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x12)
#define FCIE_SDIO_CTRL          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x1B)
#define FCIE_SDIO_ADDR0         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x1C)
#define FCIE_SDIO_ADDR1         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x1D)
#define FCIE_SD_MACRO_REDNT2    GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x2B)
#define FCIE_SM_STS             GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x2C)
#define FCIE_REG_2Dh            GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x2D)
#define FCIE_MIU_OFFSET         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x2E)
#define FCIE_BOOT_CONFIG        GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x2F)
#define FCIE_TEST_MODE          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x30)
#define FCIE_DEBUG_BUS          GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x31)
#define FCIE_MACRO_REDNT        GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x32)
#define FCIE_TOGGLE_CNT         GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x33)
#define FCIE_PWR_SAVE_MODE      GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x35)
#define FCIE_MISC               GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x36)
#define NC_WIDTH                GET_REG_ADDR(FCIE_REG_BASE_ADDR, 0x41)

#define FCIE_CIFC_ADDR(u16_pos)   GET_REG_ADDR(FCIE_CIFC_BASE_ADDR, u16_pos)
#define FCIE_CIFC_BYTE_CNT        0x40 // 32 x 16 bits

#define FCIE_CIFD_ADDR(u16_pos)   GET_REG_ADDR(FCIE_CIFD_BASE_ADDR, u16_pos)
#define FCIE_CIFD_BYTE_CNT        0x200 // 256 x 16 bits

//------------------------------------------------------------------
/* FCIE_MIE_EVENT  0x00 */
/* FCIE_MIE_INT_EN 0x01 */
#define BIT_MMA_DATA_END           BIT0
#define BIT_SD_CMD_END             BIT1
#define BIT_SD_DATA_END            BIT2
#define BIT_CARD_DMA_END           BIT11
#define BIT_MIU_LAST_DONE		   BIT14
#define BIT_CARD_BOOT_DONE		   BIT15
#define BIT_ALL_CARD_INT_EVENTS    (BIT_MMA_DATA_END|BIT_SD_CMD_END|BIT_SD_DATA_END\
	                               |BIT_CARD_DMA_END|BIT_MIU_LAST_DONE |BIT_CARD_BOOT_DONE)
/* FCIE_MMA_PRI_REG 0x02 */
#define BIT_DMA_DIR_W              BIT2
#define BIT_MIU_REQUEST_RST        BIT4 
#define BIT_FIFO_CLKRDY            BIT5 
#define BIT_MIU_BURST_MASK         (BIT8|BIT9|BIT10)
#define BIT_MIU_BURST_CTRL         BIT10
#define BIT_MIU_BURST_8            BIT_MIU_BURST_CTRL
#define BIT_MIU_BURST_16           (BIT8|BIT_MIU_BURST_CTRL)
#define BIT_MIU_BURST_32           (BIT9|BIT_MIU_BURST_CTRL)
#define BIT_MIU_CLK_EN_SW          BIT12
#define BIT_MIU_CLK_EN_HW          BIT13
#define BIT_MIU_CLK_CTRL_SEL_SW    BIT14
#define BIT_MIU_CLK_FREE_RUN       BIT15
/* FCIE_MIU_DMA_26_16 0x03 */
#define BIT_MIU1_SELECT            BIT15
/* FCIE_CARD_POWER 0x08 */
#define BIT_SD_PWR_ON_n            BIT0
#define BIT_SD_PWR_OUT_n           BIT2
/* FCIE_PATH_CTRL 0x0A */
#define BIT_MMA_EN                 BIT0
#define BIT_SD_EN                  BIT1
/* FCIE_JOB_BL_CNT 0x0B */
#define BIT_SD_JOB_BLK_CNT_MASK   (BIT12-1)
/* FCIE_RSP_SIZE 0x0D */
#define BIT_SD_RSP_SIZE_MASK      (BIT7-1)
/* FCIE_SD_MODE 0x10 */
#define BIT_SD_CLK_EN              BIT0
#define BIT_SD_DATA_WIDTH_MASK     (BIT1|BIT2)
#define BIT_SD_DATA_WIDTH_1        0
#define BIT_SD_DATA_WIDTH_4        BIT1
#define BIT_SD_DATA_WIDTH_8        BIT2
#define BIT_SD_IF_LOW              BIT3
#define BIT_SD_CLK_AUTO_STOP       BIT4
#define BIT_SD_DATA_CIFD           BIT5
#define BIT_SD_DATA_SYNC           BIT6 // set for eMMC High Speed Mode
#define BIT_SD_SELECT_SDIO         BIT9
#define BIT_SD_DMA_R_CLK_STOP      BIT11

#define BIT_SD_DEFAULT_MODE_REG    (BIT_SD_CLK_AUTO_STOP|BIT_SD_CLK_EN)
//#define BIT_SD_DEFAULT_MODE_REG    (BIT_SD_CLK_AUTO_STOP|BIT_SD_DATA_SYNC|BIT_SD_CLK_EN)

/* FCIE_SD_CTRL 0x11 */
#define BIT_SD_RSPR2_EN            BIT0
#define BIT_SD_RSP_EN              BIT1
#define BIT_SD_CMD_EN              BIT2
#define BIT_SD_DAT_EN              BIT3
#define BIT_SD_DAT_DIR_W           BIT4
/* FCIE_SD_STATUS 0x12 */
#define BIT_SD_R_CRC_ERR           BIT0
#define BIT_SD_W_FAIL              BIT1
#define BIT_SD_W_CRC_ERR           BIT2
#define BIT_SD_RSP_TIMEOUT         BIT3
#define BIT_SD_RSP_CRC_ERR         BIT4
#define BIT_SD_CARD_WP             BIT5
#define BIT_SD_CARD_BUSY           BIT6
//#define BIT_SD_FCIE_ERR_FLAGS      ((BIT5-1)|BIT_SD_CARD_BUSY)
#define BIT_SD_FCIE_ERR_FLAGS      (BIT5-1)
#define BIT_SD_CARD_D0_ST          BIT8
#define BIT_SD_CARD_D1_ST          BIT9
#define BIT_SD_CARD_D2_ST          BIT10
#define BIT_SD_CARD_D3_ST          BIT11
#define BIT_SD_CARD_D4_ST          BIT12
#define BIT_SD_CARD_D5_ST          BIT13
#define BIT_SD_CARD_D6_ST          BIT14
#define BIT_SD_CARD_D7_ST          BIT15
/* FCIE_SDIO_CTRL 0x1B */
#define BIT_SDIO_BLK_SIZE_MASK    (BIT13-1)
#define BIT_SDIO_BLK_MODE          BIT15
/* FCIE_SM_STS 0x2B */
#define BIT_DDR_TIMING_LATCH       BIT8
/* FCIE_SM_STS 0x2C */
#define BIT_DQS_DELAY_CELL_MASK    (BIT8|BIT9|BIT10|BIT11)
#define BIT_DQS_DELAY_CELL_SHIFT   8
#define BIT_DQS_MODE_MASK          (BIT12|BIT13)
#define BIT_DQS_MDOE_SHIFT         12
#define BIT_DQS_MODE_2T            (0 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_1_5T          (1 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_2_5T          (2 << BIT_DQS_MDOE_SHIFT)
#define BIT_DQS_MODE_1T            (3 << BIT_DQS_MDOE_SHIFT)
/* FCIE_REG_2Dh 0x2D */
#define BIT_ddr_timing_patch        BIT0
#define BIT_NEW_DESIGN_ENn          BIT14
/* FCIE_BOOT_CONFIG 0x2F */
#define BIT_BOOT_STG2_EN            BIT0
#define BIT_BOOT_END_EN             BIT1
#define BIT_EMMC_BOOT_MODE_EN       BIT2
#define BIT_NAND_BOOT_MODE_EN       BIT3
#define BIT_BOOT_SRAM_ACCESS_SEL    BIT4
#define BIT_MACRO_EN                BIT8
#define BIT_SD_DDR_EN               BIT9
#define BIT_SD_BYPASS_MODE_EN       BIT10
#define BIT_SD_SDR_IN_BYPASS        BIT11
#define BIT_SD_FROM_TMUX            BIT12
#define BIT_SD_CLKOE_DELAY_EN       BIT13
/* FCIE_TEST_MODE 0x30 */
#define BIT_FCIE_BIST_FAIL          (BIT0|BIT1|BIT2|BIT3|BIT4)
#define BIT_FCIE_DEBUG_MODE_MASK    (BIT8|BIT9|BIT10)
#define BIT_FCIE_DEBUG_MODE_SHIFT   8
#define BIT_FCIE_SOFT_RST_n         BIT12
#define BIT_FCIE_PPFIFO_CLK         BIT14
/* FCIE_MACRO_REDNT 0x32 */
#define BIT_DQS_DELAY_CELL_SEL_MASK (BIT0|BIT1|BIT2|BIT3)
#define BIT_MACRO_TEST_MODE_MASK    (BIT4|BIT5)
#define BIT_MACRO_DIR               BIT6
#define BIT_TOGGLE_CNT_RST          BIT7
/* FCIE_TOGGLE_CNT */
#define BITS_8_R_TOGGLE_CNT            0x111
#define BITS_4_R_TOGGLE_CNT            0x211
#define BITS_8_W_TOGGLE_CNT            0x11A
#define BITS_4_W_TOGGLE_CNT            0x21A
/* FCIE_PWR_SAVE_MODE 0x35 */
#define BIT_POWER_SAVE_MODE_EN      BIT0      /* Power Save HW enable, high active */
#define BIT_SD_POWER_SAVE_RIU       BIT1      /* SW set register to emulate power lost event, high active */
#define BIT_POWER_SAVE_MODE_INT_EN  BIT2      /* interrupt enable, high active */
#define BIT_SD_POWER_SAVE_RST       BIT3      /* software reset Power Save HW, default is '1', set '0' to reset HW */
#define BIT_RIU_SAVE_EVENT          BIT5      /* RO, RIU emulation power save event */
#define BIT_RST_SAVE_EVENT          BIT6      /* RO, Hardware reset power save event */
#define BIT_BAT_SAVE_EVENT          BIT7      /* RO, Battery lost power save event */

/* NC_WIDTH 0x41 */
#define BIT_NC_DEB_SEL_SHIFT        12
#define BIT_NC_DEB_SEL_MASK         (BIT12|BIT13|BIT14)
#define BIT_NC_BCH_DEB_SEL          BIT15

//------------------------------------------------------------------
/*
 * Power Save FIFO Cmd*
 */
#define PWR_BAT_CLASS    (0x1 << 13)  /* Battery lost class */
#define PWR_RST_CLASS    (0x1 << 12)  /* Reset Class */

/* Command Type */
#define PWR_CMD_WREG     (0x0 << 9)   /* Write data */
#define PWR_CMD_RDCP     (0x1 << 9)   /* Read and cmp data. If mismatch, HW retry */
#define PWR_CMD_WAIT     (0x2 << 9)   /* Wait idle, max. 128T */
#define PWR_CMD_WINT     (0x3 << 9)   /* Wait interrupt */
#define PWR_CMD_STOP     (0x7 << 9)   /* Stop */

/* RIU Bank */
#define PWR_CMD_BK0      (0x0 << 7)
#define PWR_CMD_BK1      (0x1 << 7)
#define PWR_CMD_BK2      (0x2 << 7)
#define PWR_CMD_BK3      (0x3 << 7)

#define PWR_RIU_ADDR     (0x0 << 0)

#endif /* __eMMC_FCIE_REG_H__ */
