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

#ifndef __DRVFCIE_H__
#define __DRVFCIE_H__

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
#define S32  signed int
#endif
#ifndef S16
#define S16  signed short
#endif
#ifndef S8
#define S8   signed char
#endif

#include "drvFCIE5_reg.h"
#include "drvFCIE_err.h"
#include "drvFCIE_config.h"

/**************************************
* Function define
**************************************/
#define SD_TIMEOUT_VALUE      1000 // 1 second
#define SD_DMA_TIMEOUT_VALUE  3000 // 3 second
#define BYTES_8          0
#define BYTES_16         1
#define BYTES_32         2
#define MIU_BURST_LEN    BYTES_8

/**************************************
* Structure define
**************************************/
#define TEST_WRITECRC		0
#define	TEST_READSTOPCLOCK  0
#define	TEST_RESPONSESHIFT	0
#define	TEST_POWERSAVE		0
#define	TEST_CMDNORESPONSE	1
#define TEST_RESPONSECRCERR	0
#define TEST_READCRCERR		0
#define	TEST_WRITECRCERR	0
#define TEST_BIST			0
#define REGRESSION_TEST		1
#define TEST_DMA			0
#define TEST_R2N			0
#define	TEST_ADMA			0

#define DMA_MODE 0
#define ADMA_MODE 1
#define R2N_MODE  2

typedef union _CMD
{
    U8 Array[17];

	struct
	{
		U8 Index;
		U32 Arg;
		U8 Reserve[12];

	} __attribute__((__packed__)) Cmd;

} CMD;

typedef union _RSP
{
    U8 Array[17];

	struct
	{
		U8 Index;
		U32 DeviceStatus;
		U8 Reserve[12];

	} __attribute__((__packed__)) Rsp;

} RSP;

typedef enum
{
    CMD_TYPE_BC     = 0, // broadcast command
    CMD_TYPE_BCR    = 1, // broadcast command with response
    CMD_TYPE_AC     = 2, // addressed command
    CMD_TYPE_ADTC   = 3, // addressed data transfer command
    CMD_TYPE_NDTC   = 4, // no data transfer command

} E_CMD_TYPE;

typedef enum
{
    RSP_TYPE_NO  = 0,
    RSP_TYPE_R1  = 1,
    RSP_TYPE_R1b = 2,
    RSP_TYPE_R2  = 3,
    RSP_TYPE_R3  = 4,
    RSP_TYPE_R6  = 5,
    RSP_TYPE_R7  = 6, // CMD08 send if cond

} E_RSP_TYPE;

typedef enum
{
    DIR_R = 0,
    DIR_W = 1,

} E_RWDIR;

typedef enum
{
    PATH_R2N	= 0, // only GPIO_PAD & 8 bits macro can use R2N
    PATH_DMA	= 1,
    PATH_ADMA	= 2,

} E_PATH;

typedef enum
{
    BUS_1_BIT   = 0,
    BUS_4_BITS  = 1,
    BUS_8_BITS  = 2,

} E_DATA_BUS;

typedef struct _CMD_RSP_INFO
{
	U32				CardClock;
	CMD				Command;
	RSP				Response;

	E_CMD_TYPE		CmdType;
	E_RSP_TYPE		RspType;

	// add for data transfer
	E_RWDIR			ReadWriteDir;
	E_PATH			DataPath; // R2N or DMA
	E_DATA_BUS		BusWidth;

	U32				MiuAddr;	// DMA & ADMA use only, this is a MIU address
	U32 *			pBufferAddr; // R2N use only, this is a data buffer pointer
	U16				BlockSize;
	U16				BlockCount; // ADMA don't care

} CMD_RSP_INFO;

U8 halFCIE_CheckRsp(void);
void halFCIE_Init(void);
void HalFcie_DumpRegister(void);
void halFCIE_OpenClock(U8 On_off);
void halFCIE_EnableCardInf(U8 u8MIE_PATH);

U8 HalFcie_CmdFifoGet(U8 u8addr);
void HalFcie_CmdFifoSet(U8 u8addr, U8 u8value);

void halFCIE_Platform_Reset_Fcie(void);
E_IO_STS HalFcie_WaitGetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt);
E_IO_STS HalFcie_WaitSetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt);

E_IO_STS halFCIE_SDWaitD0High(U32);
//E_IO_STS halFCIE_SendCmdEx(CMD_RSP_INFO * pCmdRspInfo, U8 *rsp);
E_IO_STS HalFcie_SendCommand(CMD_RSP_INFO * pCmdRspInfo);
//E_IO_STS halFCIE_TransferData(E_DAT_DIR eDir);
E_IO_STS halFCIE_SetBusWidth(U8 * pu8BusWidth, E_DATA_BUS DataBus);

void halFCIE_Disable_Stop_Clock(void);
void halFCIE_Reset_Toggle_Count(void);
void halFCIE_Set_Read_Toggle_Count(void);
void halFCIE_Set_Write_Toggle_Count(void);
void halFCIE_Config_DDR_Mode(void);
U32 eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec);
U32 sd_hw_timer_delay(U32 u32us);

#endif
