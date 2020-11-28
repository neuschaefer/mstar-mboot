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
#define FORCE_MY_GPIO_MODE 1
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#define _IIC_C_

#include <linux/string.h>
#include "Board.h"
#include "drvIIC.h"
#include "drvGPIO.h"
#include "drvMMIO.h"
#include "drvHWI2C.h"




void MDrv_IIC_InitPort0(HWI2C_PORT ePort)
{
    MS_BOOL bResult = FALSE;
    HWI2C_UnitCfg hwI2CCfg;
    memset(&hwI2CCfg, 0x00, sizeof(HWI2C_UnitCfg));
#ifdef BD_CUS75_MBQ213A
#if (MS_BOARD_TYPE_SEL == BD_CUS75_MBQ213A) // To improve tuner and demod lock time
    hwI2CCfg.eSpeed = E_HWI2C_HIGH;
#else
    hwI2CCfg.eSpeed = E_HWI2C_SLOW;//E_HWI2C_NORMAL
#endif
#else
    hwI2CCfg.eSpeed = E_HWI2C_SLOW;//E_HWI2C_NORMAL
#endif

    hwI2CCfg.sI2CPin.u32Reg = 0;
    hwI2CCfg.sI2CPin.u8BitPos = 0;
    hwI2CCfg.sI2CPin.bEnable = 0;
    hwI2CCfg.ePort = ePort;
    bResult = MDrv_HWI2C_Init(&hwI2CCfg);
    if(bResult)
    {
        printf("MDrv_IIC_InitPort0: OK\n");
    }
    else
    {
        printf("MDrv_IIC_InitPort0: FAIL\n");
        return;
    }

    MDrv_HWI2C_SelectPort(hwI2CCfg.ePort);
    MDrv_HWI2C_SetClk(hwI2CCfg.eSpeed);
    MDrv_HWI2C_SetReadMode(E_HWI2C_READ_MODE_DIRECTION_CHANGE);

}

void MDrv_IIC_InitPort1(HWI2C_PORT ePort)
{
    MS_BOOL bResult;
    HWI2C_UnitCfg hwI2CCfg;
    memset(&hwI2CCfg, 0x00, sizeof(HWI2C_UnitCfg));
#ifdef BD_CUS75_MBQ213A
#if (MS_BOARD_TYPE_SEL == BD_CUS75_MBQ213A) // To improve tuner and demod lock time
    hwI2CCfg.eSpeed = E_HWI2C_HIGH;
#else
    hwI2CCfg.eSpeed = E_HWI2C_SLOW;//E_HWI2C_NORMAL
#endif
#endif
    hwI2CCfg.sI2CPin.u32Reg = 0;
    hwI2CCfg.sI2CPin.u8BitPos = 0;
    hwI2CCfg.sI2CPin.bEnable = 0;
    hwI2CCfg.ePort = ePort;
    bResult = MDrv_HWI2C_Init(&hwI2CCfg);
    if(bResult)
    {
        printf("MDrv_IIC_InitPort1: OK\n");
    }
    else
    {
        printf("MDrv_IIC_InitPort1: FAIL\n");
        return;
    }

    MDrv_HWI2C_SelectPort1(hwI2CCfg.ePort);
    MDrv_HWI2C_SetClkP1(hwI2CCfg.eSpeed);
    MDrv_HWI2C_SetReadModeP1(E_HWI2C_READ_MODE_DIRECTION_CHANGE);

}

void MDrv_IIC_Init(HWI2C_PORT ePort)
{
    printf("MDrv_IIC_Init  PORT  %d \n", ePort);

    if (E_HWI2C_PORT_NOSUP == ePort)
    {
        return;
    }

    if(ePort >= E_HWI2C_PORT_1)
    {
         MDrv_IIC_InitPort1(ePort);
    }
    else
    {
         MDrv_IIC_InitPort0(ePort);
    }

}



MS_BOOL MDrv_IIC_ReadBytesPort0(MS_U16 u16BusNumSlaveID, MS_U8 ucSubAdr, MS_U8* paddr, MS_U16 ucBufLen, MS_U8* pBuf)
{
    return MDrv_HWI2C_ReadBytes(u16BusNumSlaveID, (MS_U32)ucSubAdr, paddr, (MS_U32)ucBufLen, pBuf);
}


MS_BOOL MDrv_IIC_ReadBytesPort1(MS_U16 u16BusNumSlaveID, MS_U8 ucSubAdr, MS_U8* paddr, MS_U16 ucBufLen, MS_U8* pBuf)
{
    return MDrv_HWI2C_ReadBytesP1(u16BusNumSlaveID, (MS_U32)ucSubAdr, paddr, (MS_U32)ucBufLen, pBuf);
}

MS_BOOL MDrv_IIC_ReadBytes(HWI2C_PORT ePort, MS_U16 u16BusNumSlaveID, MS_U8 ucSubAdr, MS_U8* paddr, MS_U16 ucBufLen, MS_U8* pBuf)
{
    //HB_printf("MDrv_IIC_ReadBytes  PORT  %d \n", ePort);
    if(ePort >= E_HWI2C_PORT_1)
    {
        return MDrv_IIC_ReadBytesPort1(u16BusNumSlaveID,ucSubAdr, paddr,ucBufLen, pBuf);
    }
    else
    {
        return MDrv_IIC_ReadBytesPort0(u16BusNumSlaveID,ucSubAdr, paddr,ucBufLen, pBuf);
    }
}


MS_BOOL MDrv_IIC_WriteBytesPort0(MS_U16 u16BusNumSlaveID, MS_U8 AddrCnt, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pBuf)
{
    return MDrv_HWI2C_WriteBytes(u16BusNumSlaveID, (MS_U32)AddrCnt, pu8addr, (MS_U32)u16size, pBuf);
}

MS_BOOL MDrv_IIC_WriteBytesPort1(MS_U16 u16BusNumSlaveID, MS_U8 AddrCnt, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pBuf)
{
    return MDrv_HWI2C_WriteBytesP1(u16BusNumSlaveID, (MS_U32)AddrCnt, pu8addr, (MS_U32)u16size, pBuf);
}

MS_BOOL MDrv_IIC_WriteBytes(HWI2C_PORT ePort, MS_U16 u16BusNumSlaveID, MS_U8 AddrCnt, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pBuf)
{
    //HB_printf("MDrv_IIC_WriteBytes  PORT  %d \n", ePort);
    if(ePort >= E_HWI2C_PORT_1)
    {
        return MDrv_IIC_WriteBytesPort1(u16BusNumSlaveID,AddrCnt, pu8addr,u16size, pBuf);
    }
    else
    {
        return MDrv_IIC_WriteBytesPort0(u16BusNumSlaveID,AddrCnt, pu8addr,u16size, pBuf);
    }
}



MS_BOOL MDrv_IIC_Read(MS_U16 u16BusNumSlaveID, MS_U8* pu8addr, MS_U8 AddrCnt, MS_U8* pBuf,  MS_U16 u16size)
{
    MS_BOOL ret;
    ret = MDrv_HWI2C_ReadBytes(u16BusNumSlaveID, (MS_U32)AddrCnt, pu8addr, (MS_U32)u16size, pBuf);
    return ret;
}

MS_BOOL MDrv_IIC1_Read(MS_U16 u16BusNumSlaveID, MS_U8* pu8addr, MS_U8 AddrCnt, MS_U8* pBuf,  MS_U16 u16size)
{
    return MDrv_HWI2C_ReadBytesP1(u16BusNumSlaveID, (MS_U32)AddrCnt, pu8addr, (MS_U32)u16size, pBuf);
}

MS_BOOL MDrv_IIC_Write(MS_U16 u16BusNumSlaveID, MS_U8* pu8addr, MS_U8 AddrCnt, MS_U8* pBuf,  MS_U16 u16size)
{
    MS_BOOL ret;
    ret = MDrv_IIC_WriteBytesPort0(u16BusNumSlaveID,AddrCnt, pu8addr,u16size, pBuf);
    return ret;

}

MS_BOOL MDrv_IIC1_Write(MS_U16 u16BusNumSlaveID, MS_U8* pu8addr, MS_U8 AddrCnt, MS_U8* pBuf,  MS_U16 u16size)
{
    return MDrv_IIC_WriteBytesPort1(u16BusNumSlaveID,AddrCnt, pu8addr,u16size, pBuf);
}


MS_BOOL MDrv_IIC_SelectCLK(HWI2C_PORT ePort, HWI2C_CLKSEL eSpeed)
{
    if(ePort >= E_HWI2C_PORT_1)
    {
        return MDrv_HWI2C_SetClkP1(eSpeed);

    }
    else
    {
        return MDrv_HWI2C_SetClk(eSpeed);
    }
}


void IIC_Stop(void)
{
    printf("IIC_N");
}

MS_BOOL IIC_Start(void)
{
    printf("IIC_N");
    return 0;
}

MS_BOOL IIC_SendByte(MS_U8 u8dat)
{
    printf("IIC_N");
    return 0;
}

HWI2C_PORT getI2CPort(MS_U8 drv_frontend_index)
{
    HWI2C_PORT ePort;
    switch(drv_frontend_index)
    {
        case 0:
            ePort = FRONTEND_TUNER_PORT0;
        break;
        case 1:
            ePort = FRONTEND_TUNER_PORT1;
        break;
        case 2:
            ePort = FRONTEND_TUNER_PORT2;
        break;
        case 3:
            ePort = FRONTEND_TUNER_PORT3;
        break;
        default:
            ePort = FRONTEND_TUNER_PORT0;
            break;
    }
    return ePort;
}


#undef _IIC_C_

