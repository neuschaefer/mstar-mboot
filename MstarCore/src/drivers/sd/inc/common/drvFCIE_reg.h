////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#ifndef __DRVFCIE_REG_H__
#define __DRVFCIE_REG_H__

#define REG(addr)                   (*(volatile U16*)(addr))

#define FCIE_RIU_W16(addr,value)    *((volatile U16*)(addr)) = (value)
#define FCIE_RIU_R16(addr)          *((volatile U16*)(addr))
#define FCIE_RIU_16_ON(addr,value)  FCIE_RIU_W16(addr, FCIE_RIU_R16(addr)|(value))
#define FCIE_RIU_16_OF(addr,value)  FCIE_RIU_W16(addr, FCIE_RIU_R16(addr)&(~(value)))

///////////////////////////////////////////////////////////////////////////////////////////////////
// RIU_BASE_FCIE                                                              0x1400 x 4 =  0x5000
///////////////////////////////////////////////////////////////////////////////////////////////////
#define MIE_EVENT               	(RIU_BASE_FCIE+(0x00<<FCIE_OffShift))
#define MIE_INT_EN              	(RIU_BASE_FCIE+(0x01<<FCIE_OffShift))
#define MMA_PRIORITY            	(RIU_BASE_FCIE+(0x02<<FCIE_OffShift))
#define FCIE_MIU_DMA_26_16    	(RIU_BASE_FCIE+(0x03<<FCIE_OffShift))
#define CARD_EVENT              	(RIU_BASE_FCIE+(0x05<<FCIE_OffShift))
#define CARD_INT_EN             	(RIU_BASE_FCIE+(0x06<<FCIE_OffShift))
#define CARD_DET                	(RIU_BASE_FCIE+(0x07<<FCIE_OffShift))
#define CARD_PWR                	(RIU_BASE_FCIE+(0x08<<FCIE_OffShift))
#define MIE_PATH_CTL            	(RIU_BASE_FCIE+(0x0A<<FCIE_OffShift))
#define JOB_BL_CNT              	(RIU_BASE_FCIE+(0x0B<<FCIE_OffShift))
#define TR_BK_CNT               	(RIU_BASE_FCIE+(0x0C<<FCIE_OffShift))
#define RSP_SIZE                	(RIU_BASE_FCIE+(0x0D<<FCIE_OffShift))
#define CMD_SIZE                	(RIU_BASE_FCIE+(0x0E<<FCIE_OffShift))
#define CARD_WD_CNT             	(RIU_BASE_FCIE+(0x0F<<FCIE_OffShift))
#define SD_MODE                 	(RIU_BASE_FCIE+(0x10<<FCIE_OffShift))
#define SD_CTL                  	(RIU_BASE_FCIE+(0x11<<FCIE_OffShift))
#define SD_STS                  	(RIU_BASE_FCIE+(0x12<<FCIE_OffShift))
#define SDIO_CTL                	(RIU_BASE_FCIE+(0x1B<<FCIE_OffShift))
#define SDIO_ADDR0              	(RIU_BASE_FCIE+(0x1C<<FCIE_OffShift))
#define SDIO_ADDR1              	(RIU_BASE_FCIE+(0x1D<<FCIE_OffShift))
#define SDIO_STS		       (RIU_BASE_FCIE+(0x1E<<FCIE_OffShift))
#define SM_STS                      (RIU_BASE_FCIE+(0x2C<<FCIE_OffShift))
#define NC_REORDER                  (RIU_BASE_FCIE+(0x2D<<FCIE_OffShift))
#define EMMC_BOOT_CONFIG            (RIU_BASE_FCIE+(0x2F<<FCIE_OffShift))
#define TEST_MODE               	(RIU_BASE_FCIE+(0x30<<FCIE_OffShift))
#define NC_MISC                     (RIU_BASE_FCIE+(0x31<<FCIE_OffShift))
#define DEBUG_BUS0                  (RIU_BASE_FCIE+(0x31<<FCIE_OffShift))
#define DEBUG_BUS1                  (RIU_BASE_FCIE+(0x32<<FCIE_OffShift))
#define SD_DDR_CNT                  (RIU_BASE_FCIE+(0x33<<FCIE_OffShift))
#define DQS_MODE                    (RIU_BASE_FCIE+(0x36<<FCIE_OffShift))

// fcie register constant
//============================================
//MIE_EVENT:offset 0x00
//============================================
#define R_MMA_DATA_END          	WBIT00
#define R_SD_CMD_END            	WBIT01
#define R_SD_DATA_END           	WBIT02
#define R_CARD_DMA_END          	WBIT11
#define R_MMA_LAST_DONE_Z       	WBIT14

//============================================
//MIE_INT_EN:offset 0x01
//============================================
#define R_MMA_DATA_ENDE         	WBIT00
#define R_SD_CMD_ENDE           	WBIT01
#define R_SD_DATA_ENDE          	WBIT02
#define R_CARD_DMA_END_INT_EN   	WBIT11

//============================================
//MMA_PRIORITY:offset 0x02
//============================================
#define R_MMA_R_PRIORITY        	WBIT00
#define R_MMA_W_PRIORITY        	WBIT01
#define R_JOB_RW_DIR            	WBIT02
#define R_FIFO_CLK_RDY          	WBIT05
#define R_MIU_BUS_TYPE_MSK      	WBIT09+WBIT08
#define R_MIU_BUS_CTRL_EN           WBIT10

// offset 03
#define BIT_MIU1_SELECT            WBIT15

//============================================
//CARD_EVENT:offset 0x05
//============================================
#define R_SD_STS_CHG            	WBIT00

//============================================
//CARD_INT_EN:offset 0x06
//============================================
#define R_SD_STS_EN             	WBIT00
#define R_SD_CD_SRC             	WBIT07 // 0: SD_CDZ, 1: SD_DAT3

//============================================
//CARD_DET:offset 0x07
//============================================
#define R_SD_DET_N              	WBIT00

//============================================
//MIE_PATH_CTL:offset 0x0A
//============================================
#define R_MMA_ENABLE            	WBIT00
#define R_SD_EN                 	WBIT01

//============================================
//JOB_BL_CNT:offset 0x0B
//============================================
#define R_TR_JOB_CNT_SEL        	WBIT14 // 0: card remain block count, 1: miu
#define R_TR_JOB_CNT_MANUAL     	WBIT15

//============================================
//SD_MODE:offset 0x10
//============================================
#define R_SD_CLK_EN             	WBIT00
#define R_SD_4BITS              	WBIT01
#define R_SD_8BITS              	WBIT02
#define R_SDDRL                 	WBIT03
#define R_SD_CS_EN              	WBIT04
#define R_SD_DEST               	WBIT05 // 0: Data FIFO, 1: CIF FIFO
#define R_SD_DATSYNC            	WBIT06
#define R_MMC_BUS_TEST          	WBIT07
#define R_SDIO_RDWAIT           	WBIT08
#define R_SDIO_SD_BUS_SW        	WBIT09

//============================================
//SD_CTL:offset 0x11
//============================================
#define R_SD_RSPR2_EN           	WBIT00 // Response R2 type
#define R_SD_RSP_EN             	WBIT01
#define R_SD_CMD_EN             	WBIT02
#define R_SD_DTRX_EN            	WBIT03
#define R_SD_DTRX_DIR           	WBIT04 // 0: R, 1:W

//============================================
//SD_STS:offset 0x12
//============================================
#define R_SD_DAT_CERR           	WBIT00 // data crc error
#define R_SD_DAT_STSERR         	WBIT01
#define R_SD_DAT_STSNEG         	WBIT02
#define R_SD_CMD_NORSP          	WBIT03 // response time out in 64 clocks
#define R_SD_CMDRSP_CERR        	WBIT04 // response crc error
#define R_SD_WR_PRO_N           	WBIT05
#define R_SD_DAT0               	WBIT08
#define R_SD_DAT1               	WBIT09
#define R_SD_DAT2               	WBIT10
#define R_SD_DAT3               	WBIT11
#define R_SD_DAT4               	WBIT12
#define R_SD_DAT5               	WBIT13
#define R_SD_DAT6               	WBIT14
#define R_SD_DAT7               	WBIT15

#define R_SDIO_DAT0				WBIT00

//============================================
//SDIO_CTL:offset 0x1B
//============================================
#define R_SDIO_BLK_MOD          	WBIT15

//============================================
//EMMC_BOOT_CONFIG:offset 0x2F
//============================================
#define R_BOOT_STG2_EN              WBIT00
#define R_BOOT_END_EN               WBIT01
#if (ENABLE_AMBER3) || (ENABLE_AGATE)
#define R_SD_DDR_MODE               WBIT08
#define R_SD_BYPASS_MODE_DIS        WBIT09
#define R_SD_SDRIN_BYPASS_MODE      WBIT10
#define R_DQS_DELAY_SEL_MASK        (WBIT15|WBIT14|WBIT13|WBIT12)
#endif

#if (ENABLE_EAGLE)
#define R_SD_MACRO_EN               WBIT08
#define R_SD_DDR_MODE               WBIT09
#define R_SD_BYPASS_MODE            WBIT10
#define R_SD_SDRIN_BYPASS_MODE      WBIT11
#define R_SD_FROM_TMUX              WBIT12
#define R_SD_CLKOE_DELAY_EN         WBIT15
#define R_SD_MODE_MASK              (WBIT12|WBIT11|WBIT10|WBIT09|WBIT08)
#endif

#if (ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_MIAMI) || (ENABLE_NADAL)
#define R_SD_MACRO_EN               WBIT08
#define R_SD_DDR_MODE               WBIT09
#define R_SD_BYPASS_MODE            WBIT10
#define R_SD_SDRIN_BYPASS_MODE      WBIT11
#define R_SD_FROM_TMUX              WBIT12
#define R_SD_CLKOE_DELAY_EN         WBIT15
#define R_SD_MODE_MASK              (WBIT12|WBIT11|WBIT10|WBIT09|WBIT08)
#endif

//============================================
//TEST_MODE:offset 0x30
//============================================
#define R_FCIE_SOFT_RST         	WBIT12
#define R_ENDIAN_SEL            	WBIT13

//============================================
//NC_MISC offser 0x31
//============================================
#define R_DDR_DISABLE_CLOCK_STOP    WBIT06
#define R_TOGGLE_COUNT_RESET        WBIT07

//============================================
//DQS_MODE offser 0x36
//============================================
#define R_DQS_DELAY_2T              0
#define R_DQS_DELAY_1_5_T           WBIT10
#define R_DQS_DELAY_2_5_T           WBIT11
#define R_DQS_DELAY_1_T             (WBIT11|WBIT10)

#endif
