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

#ifndef __PANEL_INX_VB1_C__
#define __PANEL_INX_VB1_C__

//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------
#include "panel_INX_vb1.h"

//-------------------------------------------------------------------------------------------------
//  Define
//-------------------------------------------------------------------------------------------------
#define PANEL_INX_VB1_CMD_DATA_SUM          (sizeof(PANEL_CMD_DATA) / sizeof(MS_U8))
#define PANEL_INX_VB1_I2C_BUS_NUM           (3)
#define PANEL_INX_VB1_DDC2BI_MODE_ADDR		((E_I2C_BUS_SYS<<8)|0x38)
#define PANEL_INX_VB1_I2C_SUB_ADDR          (0)

#define PANEL_INX_VB1_Delay(x)          udelay(x*1000)
#define PANEL_INX_CMD_INTERVAL_TIME     (240)
#define PANEL_INX_VB1_CMD_RETRY_TIMES   (3)

static MS_BOOL g_Panel_INX_VB1_Init = FALSE;

static SWI2C_BusCfg Panel_INX_VB1_I2cBusCfg[PANEL_INX_VB1_I2C_BUS_NUM]=
{
    // Bus-0
    {PAD_DDCR_CK, PAD_DDCR_DA, 400}, //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-1
    {PAD_TGPIO2, PAD_TGPIO3, 400},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-2
    {PAD_GPIO17, PAD_GPIO18, 400},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Others, add other bus here
};

static PANEL_CMD_DATA g_PanelPreInit[] =
{
    {0x40, 0x01, 0x02, 0x00, 0x00, 0x11, 0x00},
	{0x30, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00},
	{0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x81, 0x05, 0x07, 0x80, 0x04, 0x38, 0x00},
    {0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xFD, 0x0D, 0x02, 0x00, 0x00, 0x00, 0x00},//frame mode change ,disable black screen
};

static PANEL_CMD_DATA g_PanelSetFHD[] =
{
    {0x40, 0x01, 0x02, 0x00, 0x00, 0x11, 0x00},
    {0x30, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00},
    {0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x81, 0x05, 0x07, 0x80, 0x04, 0x38, 0x00},
    {0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
};

static PANEL_CMD_DATA g_PanelSet4K2K[] =
{
#if 0
    {0x80, 0x01, 0x02, 0x00, 0x00, 0x55, 0x00},
    {0x80, 0x02, 0x00, 0x00, 0x02, 0x01, 0x03},
    {0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xC1, 0x05, 0x0F, 0x00, 0x08, 0x70, 0x00},
    {0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
#endif

    {0x20, 0x01, 0x12, 0x00, 0x40, 0xFF, 0x00},
};

static PANEL_CMD_DATA g_PanelSet2D[] =
{
    {0x40, 0x01, 0x02, 0x00, 0x00, 0x11, 0x00},
    {0x30, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00},
    {0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x81, 0x05, 0x07, 0x80, 0x04, 0x38, 0x00},
    {0x13, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
};

static PANEL_CMD_DATA g_PanelSet3D[] =
{
    {0x80, 0x01, 0x02, 0x00, 0x00, 0x55, 0x00},
    {0x80, 0x02, 0x00, 0x00, 0x02, 0x01, 0x03},
    {0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x81, 0x05, 0x07, 0x80, 0x04, 0x38, 0x00},
    {0x13, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00},
};

static PANEL_CMD_DATA g_PanelRxInit[] =
{
    {0x20, 0x01, 0x12, 0x00, 0x40, 0xFF, 0x00},
};

//-------------------------------------------------------------------------------------------------
//  Function define
//-------------------------------------------------------------------------------------------------
void MDrv_Panel_INX_VB1_SWI2C_Init(void)
{
	MApi_SWI2C_Init(Panel_INX_VB1_I2cBusCfg, PANEL_INX_VB1_I2C_BUS_NUM);
    g_Panel_INX_VB1_Init = 1;
}

MS_BOOL MDrv_Panel_INX_VB1_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_WriteBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Panel_INX_VB1_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_ReadBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Panel_INX_VB1_SendCmd(PANEL_INX_VB1_CMD_TYPE eCmdType)
{
    MS_BOOL bUnkown = FALSE;
    MS_BOOL bRet = FALSE;
    PANEL_CMD_DATA *pCmdArray = NULL;
    MS_U8 u8ArraySize = 0;
    switch(eCmdType)
    {
        case CMD_INX_VB1_SET_PRE_INIT:
            {
                 pCmdArray = g_PanelPreInit;
                 u8ArraySize = sizeof(g_PanelPreInit)/sizeof(PANEL_CMD_DATA);
            }
            break;

        case CMD_INX_VB1_SET_FHD:
            {
                pCmdArray = g_PanelSetFHD;
                u8ArraySize = sizeof(g_PanelSetFHD)/sizeof(PANEL_CMD_DATA);
            }
            break;

        case CMD_INX_VB1_SET_4K2K:
            {
                pCmdArray = g_PanelSet4K2K;
                u8ArraySize = sizeof(g_PanelSet4K2K)/sizeof(PANEL_CMD_DATA);
            }
            break;

        case CMD_INX_VB1_SET_2D:
            {
                pCmdArray = g_PanelSet2D;
                u8ArraySize = sizeof(g_PanelSet2D)/sizeof(PANEL_CMD_DATA);
            }
            break;

        case CMD_INX_VB1_SET_3D:
            {
                pCmdArray = g_PanelSet3D;
                u8ArraySize = sizeof(g_PanelSet3D)/sizeof(PANEL_CMD_DATA);
            }
            break;

        case CMD_INX_VB1_RX_INIT:
            {
                pCmdArray = g_PanelRxInit;
                u8ArraySize = sizeof(g_PanelRxInit)/sizeof(PANEL_CMD_DATA);
            }
            break;

        default:
            bUnkown = TRUE;
            break;
    }

    if(bUnkown)
    {
        bRet = FALSE;
        printf("[INX_VB1]Can not find the command, please check!\n");
    }
    else
    {
        MS_U8 u8CmdData[PANEL_INX_VB1_CMD_DATA_SUM] = {0};
        MS_U8 u8Index = 0;

        for(u8Index = 0; u8Index < u8ArraySize; u8Index++)
        {
            memcpy(u8CmdData, &pCmdArray[u8Index], sizeof(PANEL_CMD_DATA));
            bRet  = MDrv_Panel_INX_VB1_Write_Cmd(u8CmdData);
        }
        printf("[INX_VB1]Send cmd:%d, return:%d\n", eCmdType, bRet);
    }

    return bRet;
}

MS_BOOL MDrv_Panel_INX_VB1_Write_Cmd(MS_U8 *pu8CmdData)
{
    MS_U16 u16BusNumSlaveID = PANEL_INX_VB1_DDC2BI_MODE_ADDR;
    MS_U8 u8SubAddr = PANEL_INX_VB1_I2C_SUB_ADDR;
    MS_U8 uRetryCnt = PANEL_INX_VB1_CMD_RETRY_TIMES;
    MS_BOOL bRet = FALSE;

    if(!g_Panel_INX_VB1_Init)
    {
        MDrv_Panel_INX_VB1_SWI2C_Init();
    }

    MDrv_Panel_INX_VB1_Print_Cmd(pu8CmdData);

    while(uRetryCnt--)
    {
        bRet = MDrv_Panel_INX_VB1_SWI2C_WriteBytes(u16BusNumSlaveID, u8SubAddr, NULL, PANEL_INX_VB1_CMD_DATA_SUM, pu8CmdData);
        PANEL_INX_VB1_Delay(PANEL_INX_CMD_INTERVAL_TIME);

        if(bRet)
        {
            break;
        }
    }

    return bRet;
}

MS_BOOL MDrv_Panel_INX_VB1_Print_Cmd(MS_U8 *pu8CmdData)
{
    MS_U8 u8Index = 0;

    printf("[INX_VB1]Write cmd:");
    while(u8Index < PANEL_INX_VB1_CMD_DATA_SUM)
    {
        printf("0x%02x, ", pu8CmdData[u8Index]);
        u8Index++;
    }
    printf("\r\n");

    return TRUE;
}
//-------------------------------------------------------------------------------------------------
//  Member Function
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_Panel_INX_VB1_Set_Pre_Init(void)
{
    return MDrv_Panel_INX_VB1_SendCmd(CMD_INX_VB1_SET_PRE_INIT);
}

MS_BOOL MDrv_Panel_INX_VB1_Set_FHD(void)
{
    return MDrv_Panel_INX_VB1_SendCmd(CMD_INX_VB1_SET_FHD);
}

MS_BOOL MDrv_Panel_INX_VB1_Set_4K2K(void)
{
    return MDrv_Panel_INX_VB1_SendCmd(CMD_INX_VB1_SET_4K2K);
}

MS_BOOL MDrv_Panel_INX_VB1_Set_2D(void)
{
    return MDrv_Panel_INX_VB1_SendCmd(CMD_INX_VB1_SET_2D);
}

MS_BOOL MDrv_Panel_INX_VB1_Set_3D(void)
{
    return MDrv_Panel_INX_VB1_SendCmd(CMD_INX_VB1_SET_3D);
}

MS_BOOL MDrv_Panel_INX_VB1_RX_INIT(void)
{
    return MDrv_Panel_INX_VB1_SendCmd(CMD_INX_VB1_RX_INIT);
}

#endif //__PANEL_INX_VB1_C__

