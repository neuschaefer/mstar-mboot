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

#ifndef __DRVFCIE_ERR_H__
#define __DRVFCIE_ERR_H__

typedef enum
{
    EC_NO_ERROR = 0,
    EC_CRC_ERROR,
    EC_CMD_TIME_OUT,
    EC_DMA_TIME_OUT,
    EC_CMD_NO_RSP,

} ERR_CODE_SD;

typedef enum
{
    IO_SUCCESS              = 0x00,
    IO_TIME_OUT             = 0x01,
    IO_CARD_REMOVED         = 0x02,
    IO_ERROR                = 0x03,
    IO_ERROR_DETECT         = 0x04,

    IO_VOLTAGE_NOT_ACCEPT   = 0x05,
    IO_MISS_CHECK_PATTERN   = 0x06,

    IO_CMD_NO_RSP           = 0x16,
    IO_RSP_CRC_ERROR        = 0x17,
    IO_RSP_ERROR            = 0x18,

    IO_R_DATA_CRC_ERROR     = 0x20,
    IO_W_DATA_STS_ERROR     = 0x21,
    IO_W_DATA_STS_NEGATIVE  = 0x22,

    IO_STILL_POWERING_UP    = 0x30,

    IO_CARD_CHANGED         = 0x40,

} E_IO_STS;

#endif
