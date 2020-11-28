/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (¡§MStar Confidential Information¡¨) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */

#ifndef _HAL_SPINAND_H_
#define _HAL_SPINAND_H_


#if defined(CONFIG_MCU_ARM)
#define CONFIG_SRAM_SPINAND_OFFSET  0x1FC02800 //512B Reserved for SPINAND Flash Driver
#define CONFIG_SRAM_SPINAND_BUF     (0x1FC02800+0x100)
#define CONFIG_RIU_BASE_ADDRESS     0x1F000000
#define RIU_BASE                    0x1F200000

#elif defined(CONFIG_MCU_MIPS32)
#define CONFIG_RIU_BASE_ADDRESS     0xBF000000
#define RIU_BASE                    0xBF200000
#define CONFIG_SRAM_SPINAND_OFFSET  0xB0007800 //512B Reserved for SPINAND Flash Driver
#define CONFIG_SRAM_SPINAND_BUF     (0xB0007800+0x100)
#else
#error  "Unknown CPU Platform"
#endif
#define CONFIG_XIU_BASE_ADDRESS     0x1F600000
#define TSP_SRAM_BASE_ADDRESS       0xB0004000

#define REG_OFFSET_SHIFT_BITS       2
#define GET_REG_ADDR(x, y)          ((x)+((y) << REG_OFFSET_SHIFT_BITS))

#define REG_BANK_PORTSTATUS         0x0280U
#define PORTSTATUS_BASE             GET_REG_ADDR(RIU_BASE, REG_BANK_PORTSTATUS)
#define BOOTSTAGE_REG               GET_REG_ADDR(PORTSTATUS_BASE, 0x7)

#define DEBUG_REG                   GET_REG_ADDR(PORTSTATUS_BASE, 0x01)
#define DEBUG_REG_SYS_L1            GET_REG_ADDR(PORTSTATUS_BASE, 0x02)
#define DEBUG_REG_SYS_L2            GET_REG_ADDR(PORTSTATUS_BASE, 0x03)

#define REG_READ_UINT16(reg_addr, val)      val = REG((reg_addr))
#define REG_WRITE_UINT16(reg_addr, val)     REG((reg_addr)) = (val)
#define REG_SET_BITS_UINT16(reg_addr, val)  REG((reg_addr)) |= (val)

#define REG_BANK_TIMER0                     0x1800U
#define TIMER0_REG_BASE_ADDR				GET_REG_ADDR(CONFIG_RIU_BASE_ADDRESS, REG_BANK_TIMER0)

#define TIMER0_ENABLE						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x10)
#define TIMER0_HIT							GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x11)
#define TIMER0_MAX_LOW						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x12)
#define TIMER0_MAX_HIGH						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x13)
#define TIMER0_CAP_LOW						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x14)
#define TIMER0_CAP_HIGH						GET_REG_ADDR(TIMER0_REG_BASE_ADDR, 0x15)

#ifndef TRUE
#define TRUE                        1
#endif

#ifndef FALSE
#define FALSE                       0
#endif

#ifndef U32
#define U32  unsigned long
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

#ifndef BOOL
#define BOOL unsigned char
#endif
#define REG(Reg_Addr)           (*(volatile unsigned short *)(Reg_Addr))
#define SECURE_DEBUG(reg_addr, val)      REG((reg_addr)) = (val)
#define SPINAND_DEBUG 0
#define ALIGN_8(_x_)                (((_x_) + 7) & ~7)
#define RIU     ((unsigned short volatile *) CONFIG_RIU_BASE_ADDRESS)
#define RIU8    ((unsigned char  volatile *) CONFIG_RIU_BASE_ADDRESS)
#define XIU     ((unsigned int   volatile *) CONFIG_XIU_BASE_ADDRESS)
#define XIU8    ((unsigned char  volatile *) CONFIG_XIU_BASE_ADDRESS)

#define FSP_BASE_ADDR        (0x000900)
#define QSPI_BASE_ADDR       (0x000A00)
#define BDMA_BASE_ADDR       (0x100900)
#define MBX_BASE_ADDR        (0x103380)
#define CHIP_BASE_ADDR       (0x101E00)   
#define CHK_NUM_WAITDONE     100

// FSP Register 
#define REG_FSP_WRITE_BUFF                      0x60 * 2
    #define REG8_FSP_COMMAND       0x00
    #define REG8_FSP_COMMAND1      0x01
    #define REG8_FSP_RADDR_L       0x03
    #define REG8_FSP_RADRR_M       0x02
    #define REG8_FSP_RADDR_H       0x01
    #define REG8_FSP_WADDR_L       0x04
    #define REG8_FSP_WADDR_M       0x03
    #define REG8_FSP_WADDR_H       0x02

    #define REG8_FSP_WDATA         0x05
    #define REG8_FSP_WDATA10       0x10

#define REG_FSP_READ_BUFF                       0x65 * 2
#define REG_FSP_WRITE_SIZE                      0x6A * 2
#define REG_FSP_READ_SIZE                       0x6B * 2
#define REG_FSP_CTRL                            0x6C * 2
#define REG_FSP_TRIGGER                         0x6D * 2
    #define TRIGGER_FSP            1
#define REG_FSP_DONE                            0x6E * 2
    #define DONE_FSP               1
#define REG_FSP_AUTO_CHECK_ERROR                0x6E * 2
    #define AUTOCHECK_ERROR_FSP    2
#define REG_FSP_CLEAR_DONE                      0x6F * 2
    #define CLEAR_DONE_FSP         1
#define REG_FSP_CTRL2                           0x75 * 2
#define REG_FSP_CTRL3                           0x75 * 2
#define REG_FSP_CTRL4                           0x76 * 2
#define REG_FSP_WDATA           0x00


    #define REG_FSP_RDATA          0x05
#define REG_FSP_WSIZE           0x0A
    #define MAX_WRITE_BUF_CNT    17
    #define SINGLE_WRITE_SIZE    14
#define REG_FSP_RSIZE           0x0B
    #define MAX_READ_BUF_CNT     10
    #define ENABLE_FSP             1
    #define RESET_FSP              2
    #define INT_FSP                4
    #define AUTOCHECK_FSP          8
    #define ENABLE_SEC_CMD         0x8000
    #define ENABLE_THR_CMD         0x4000
    #define ENCMD2_3               0xF000
#define FLASH_BUSY_BIT            1 
#define FLASH_WRITE_ENANLE        2    
#define FLASH_BUSY_BIT_EREASE     3
    // writet protect register 
#define WRITE_PROTECT_ENABLE   0xFC
#define WRITE_PROTECT_DISABLE  0x00

 //QSPI Register 
#define REG_SPI_CS_SET   0x0A
   #define REG_SPI_CS_HIGH         0x3
   #define REG_SPI_CS_LOW          0x2
#define REG_SPI_WRAP_VAL 0x54
   #define REG_SPI_WRAP_BIT_OFFSET 0x8
   #define REG_SPI_WRAP_BIT_MASK   0xF
#define REG_SPI_CKG_SPI  0x70
    #define REG_SPI_USER_DUMMY_EN       0x10
    #define REG_SPI_DUMMY_CYC_SINGAL    0x07
    #define REG_SPI_DUMMY_CYC_DUAL      0x03
    #define REG_SPI_DUMMY_CYC_QUAD      0x01
#define REG_SPI_MODE_SEL 0x72
    #define REG_SPI_NORMAL_MODE         0x00
    #define REG_SPI_FAST_READ           0x01
    #define REG_SPI_CMD_3B              0x02
    #define REG_SPI_CMD_BB              0x03
    #define REG_SPI_CMD_6B              0x0A
    #define REG_SPI_CMD_EB              0x0B
    #define REG_SPI_CMD_0B              0x0C
    #define REG_SPI_CMD_4EB             0x0D
#define REG_SPI_FUNC_SET 0x7D
    #define REG_SPI_ADDR2_EN    0x800
    #define REG_SPI_DUMMY_EN    0x1000
    //only for two plane nand
    #define REG_SPI_WRAP_EN     0x2000


U32 HAL_SPINAND_Read (U32 u32Addr, U32 u32DataSize, U8 *pu8Data);
U8  HAL_SPINAND_ReadID(U32 u32DataSize, U8 *pu8Data);
U32 HAL_SPINAND_RFC(U32 u32Addr, U8 *pu8Data);
BOOL HAL_SPINAND_Init(void);
BOOL HAL_SPINAND_PLANE_HANDLER(U32 u32Addr);
void HAL_SPINAND_SetReadMode(BOOL bRIUFlag);
void HAL_SPINAND_CSCONFIG(void);
BOOL HAL_SPINAND_SetCKG(U8 u8CkgSpi);

#if SPINAND_DEBUG
BOOL HAL_SPINAND_BDMA_CHECK(U32 u32Addr, U32 u32DataSize, U8 *u8pData);
#endif
#endif

