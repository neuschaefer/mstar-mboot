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

#include "drvFCIE_reg.h"
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

typedef union _CMD_RSP
{
    U8 Command[16];
    U8 Response[16];
} CMD_RSP;

typedef enum
{
    CMD_TYPE_BC     = 0, // broadcast command
    CMD_TYPE_BCR    = 1, // broadcast command with response
    CMD_TYPE_AC     = 2, // addressed command
    CMD_TYPE_ADTC   = 3, // addressed data transfer command
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
    DAT_READ     = 0,
    DAT_WRITE    = 1,
} E_DAT_DIR;

typedef struct _CMD_RSP_INFO
{
    U32         CardClock;
    CMD_RSP     CmdRsp;
    U8          CmdSize;
    U8          RspSize;
    E_DAT_DIR   Dir;
    E_CMD_TYPE  CmdType;
    E_RSP_TYPE  RspType;
    U16         DataLength;
} CMD_RSP_INFO;

typedef enum
{
    DIR_R = 0,
    DIR_W = 1,
} E_RWDIR;

typedef enum
{
    DEST_MIU    = 0,
    DEST_CIFD   = 1,
} E_DEST;

typedef struct _RW_INFO
{
    U32     CardClock;
    CMD_RSP CmdRsp;
    U32     MiuAddr;
    U16     JobCount;
    E_RWDIR RwDir;
    E_DEST  Dest;
} RW_INFO;

typedef enum
{
    BUS_1_BIT   = 0,
    BUS_4_BITS  = 1,
    BUS_8_BITS  = 2,
} E_DATA_BUS;

U8 halFCIE_CheckRsp(void);
void halFCIE_Init(void);
void halFCIE_DumpRegister(void);
void halFCIE_OpenClock(U8 On_off);
void halFCIE_EnableCardInf(U8 u8MIE_PATH);

void halFCIE_Platform_Reset_Fcie(void);

E_IO_STS halFCIE_SDWaitD0High(U32);
E_IO_STS halFCIE_SendCmdEx(CMD_RSP_INFO * pCmdRspInfo, U8 *rsp);
E_IO_STS halFCIE_TransferData(E_DAT_DIR eDir);
E_IO_STS halFCIE_SetBusWidth(U8 * pu8BusWidth, E_DATA_BUS DataBus);

void halFCIE_Disable_Stop_Clock(void);
void halFCIE_Reset_Toggle_Count(void);
void halFCIE_Set_Read_Toggle_Count(void);
void halFCIE_Set_Write_Toggle_Count(void);
void halFCIE_Config_DDR_Mode(void);

#endif
