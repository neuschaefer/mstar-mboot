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

#ifndef __PANEL_INX_NOVA_VB1_C__
#define __PANEL_INX_NOVA_VB1_C__

//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------
#include "panel_INX_NOVA_vb1.h"

//-------------------------------------------------------------------------------------------------
//  Define
//-------------------------------------------------------------------------------------------------
#define PANEL_INX_NOVA_VB1_I2C_BUS_NUM          (3)
#define PANEL_INX_NOVA_VB1_I2C_BUS_SELECT		(E_I2C_BUS_SYS)
#define PANEL_INX_NOVA_VB1_I2C_ADDR		        ((PANEL_INX_NOVA_VB1_I2C_BUS_SELECT<<8)|0x34)
#define PANEL_INX_NOVA_VB1_I2C_SUB_ADDR         (0)

#define PANEL_INX_NOVA_VB1_CMD_LEN              (sizeof(PANEL_INX_NOVA_VB1_CMD_DATA)/sizeof(MS_U8))
#define PANEL_INX_NOVA_VB1_READ_DATA_LEN        (4)
#define PANEL_INX_NOVA_VB1_Delay(x)             MsOS_DelayTask(x)
#define PANEL_INX_NOVA_VB1_CMD_INTERVAL_TIME    (200)//(ms) the time is not exactly
#define PANEL_INX_NOVA_VB1_CMD_RETRY_TIMES      (5)

static MS_BOOL g_Panel_I2C_Init = FALSE;
static MS_BOOL g_AHB_Bridge_Unlock = FALSE;

static SWI2C_BusCfg Panel_INX_NOVA_VB1_I2cBusCfg[PANEL_INX_NOVA_VB1_I2C_BUS_NUM]=
{
    // Bus-0
    {PAD_DDCR_CK, PAD_DDCR_DA, 200}, //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-1
    {PAD_TGPIO2, PAD_TGPIO3, 200},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-2
    {PAD_GPIO36, PAD_GPIO37, 200}    //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
};

static PANEL_INX_NOVA_VB1_CMD_DATA UHDDivisonCmd[] =
{
    {0x00, 0x00, 0x01, 0x0A, 0x9F, 0x00, 0x00, 0x15, 0x04},
    {0x00, 0x00, 0x01, 0x0A, 0x9F, 0x01, 0x00, 0x50, 0x04},
};

static PANEL_INX_NOVA_VB1_CMD_DATA InputModeCmd[] =
{
    {0x00, 0x00, 0x01, 0x0A, 0x9F, 0x00, 0x00, 0x00, 0x0F}, //CMD_INX_NOVA_VB1_SET_INPUT_MODE
};

static PANEL_INX_NOVA_VB1_CMD_DATA Set3DModeCmd[] =
{
    {0x00, 0x00, 0x01, 0x0A, 0x9F, 0x00, 0x00, 0x01, 0x02}, //CMD_INX_NOVA_VB1_SET_3D_MODE
};

//-------------------------------------------------------------------------------------------------
//  Function define
//-------------------------------------------------------------------------------------------------
void MDrv_Panel_INX_NOVA_VB1_SWI2C_Init(void)
{
	MApi_SWI2C_Init(Panel_INX_NOVA_VB1_I2cBusCfg, PANEL_INX_NOVA_VB1_I2C_BUS_NUM);
    g_Panel_I2C_Init = 1;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_WriteBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_ReadBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_SendCmd(PANEL_INX_NOVA_VB1_CMD_TYPE eCmdType, MS_U8 u8Data)
{
    PANEL_INX_NOVA_VB1_CMD_DATA *pCmdArray = NULL;
    MS_U8 u8ArraySize = 0;
    MS_BOOL bUnkown = FALSE;
    MS_BOOL bRet = FALSE;

    switch(eCmdType)
    {
        case CMD_INX_NOVA_VB1_UNLOCK_AHB:  //it is need set I2C cmd directly
            {
                MS_U8 u8Cmd1[] = {0xFE, 0x31};
                MS_U8 u8Cmd2[] = {0xFF, 0x72};
                MS_U8 u8Len = sizeof(u8Cmd1)/sizeof(MS_U8);
                bRet = MDrv_Panel_INX_NOVA_VB1_Write_Cmd(u8Cmd1, u8Len);
                bRet = MDrv_Panel_INX_NOVA_VB1_Write_Cmd(u8Cmd2, u8Len);
            }
            break;

        case CMD_INX_NOVA_VB1_SET_UHD_DIVISION_MODE:
            {
                pCmdArray = UHDDivisonCmd;
                u8ArraySize = sizeof(UHDDivisonCmd)/sizeof(PANEL_INX_NOVA_VB1_CMD_DATA);
                pCmdArray[0].Idx5 = u8Data; //set 0,1 ro 2 division
            }
            break;

        case CMD_INX_NOVA_VB1_SET_INPUT_MODE:
            {
                pCmdArray = InputModeCmd;
                u8ArraySize = sizeof(InputModeCmd)/sizeof(PANEL_INX_NOVA_VB1_CMD_DATA);
                pCmdArray[0].Idx5 = u8Data; //set INPUT_TIMMING_TYPE
            }
            break;

        case CMD_INX_NOVA_VB1_SET_3D_MODE:
            {
                pCmdArray = Set3DModeCmd;
                u8ArraySize = sizeof(Set3DModeCmd)/sizeof(PANEL_INX_NOVA_VB1_CMD_DATA);
                pCmdArray[0].Idx5 = u8Data; //set INPUT_3D_TYPE
            }
            break;

        default:
            bUnkown = TRUE;
            break;
    }

    if(bUnkown)
    {
        printf("[INX_NOVA_VB1]Can not find the command, please check!\n");
        return FALSE;
    }
    else if(pCmdArray != NULL) //it is only for array cmd
    {
        bRet = MDrv_Panel_INX_NOVA_VB1_Run_Cmd(pCmdArray, u8ArraySize);
    }
    printf("[INX_NOVA_VB1]send cmd:%d, return:%d\n", eCmdType, bRet);
    return bRet;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Run_Cmd(PANEL_INX_NOVA_VB1_CMD_DATA *pCmdArray, MS_U8 u8ArraySize)
{
    MS_BOOL bCmdPass = FALSE;
    MS_BOOL bStatusPass = FALSE;

    //1. make sure that unlock AHB bridge
    MDrv_Panel_INX_NOVA_VB1_Unlock_AHB();
    while(!bStatusPass)
    {
        //2.write command register
        MS_U8 u8CmdData[PANEL_INX_NOVA_VB1_CMD_LEN] = {0};
        MS_U8 u8Index = 0;
        MS_BOOL bRet = FALSE;
        for(u8Index = 0; u8Index < u8ArraySize; u8Index++)
        {
            memcpy(u8CmdData, &pCmdArray[u8Index], sizeof(PANEL_INX_NOVA_VB1_CMD_DATA));
            bRet = MDrv_Panel_INX_NOVA_VB1_Write_Cmd(u8CmdData, PANEL_INX_NOVA_VB1_CMD_LEN);
        }
        //3.read command register
        while(!bCmdPass)
        {
            bCmdPass = MDrv_Panel_INX_NOVA_VB1_Check_Cmd();
        }
        //4.read status register
        bStatusPass = MDrv_Panel_INX_NOVA_VB1_Check_Status();
    }
    return TRUE;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Check_Cmd(void)
{
    MS_U8 pCmd[5] = {0x08, 0x00, 0x01, 0x0A, 0x9F}; //cmd to read command register
    MS_U8 pReturn[PANEL_INX_NOVA_VB1_READ_DATA_LEN] = {0};
    MS_BOOL bRet = FALSE;
    MDrv_Panel_INX_NOVA_VB1_Write_Cmd(pCmd, sizeof(pCmd));
    MDrv_Panel_INX_NOVA_VB1_Read_Data(pReturn, PANEL_INX_NOVA_VB1_READ_DATA_LEN);
    if((pReturn[0]==0xFF)&&(pReturn[1]==0xFF)&&(pReturn[2]==0xFF)&&(pReturn[3]==0xFF))
    {
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
    }
    return bRet;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Check_Status(void)
{
    MS_U8 pCmd[5] = {0x08, 0x04, 0x01, 0x0A, 0x9F}; //cmd to read status register
    MS_U8 pReturn[PANEL_INX_NOVA_VB1_READ_DATA_LEN] = {0};
    MS_BOOL bRet = FALSE;

    memset(pReturn, 0xAB, PANEL_INX_NOVA_VB1_READ_DATA_LEN);
    MDrv_Panel_INX_NOVA_VB1_Write_Cmd(pCmd, sizeof(pCmd));
    MDrv_Panel_INX_NOVA_VB1_Read_Data(pReturn, PANEL_INX_NOVA_VB1_READ_DATA_LEN);
    if((pReturn[0]==0x00)&&(pReturn[1]==0x00)&&(pReturn[2]==0x00)&&(pReturn[3]==0x00))
    {
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
    }
    return bRet;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Write_Cmd(MS_U8 *pu8CmdData, MS_U8 u8CmdLen)
{
    MS_U16 u16BusNumSlaveID = PANEL_INX_NOVA_VB1_I2C_ADDR;
    MS_U8 u8SubAddr = PANEL_INX_NOVA_VB1_I2C_SUB_ADDR;
    MS_U8 uRetryCnt = PANEL_INX_NOVA_VB1_CMD_RETRY_TIMES;
    MS_BOOL bRet = FALSE;

    if(!g_Panel_I2C_Init)
    {
        MDrv_Panel_INX_NOVA_VB1_SWI2C_Init();
    }

    MDrv_Panel_INX_NOVA_VB1_Print_Cmd(TRUE, pu8CmdData, u8CmdLen);

    while(uRetryCnt--)
    {
        bRet = MDrv_Panel_INX_NOVA_VB1_SWI2C_WriteBytes(u16BusNumSlaveID, u8SubAddr, NULL, u8CmdLen, pu8CmdData);
        PANEL_INX_NOVA_VB1_Delay(PANEL_INX_NOVA_VB1_CMD_INTERVAL_TIME);

        if(bRet)
        {
            break;
        }
    }

    return bRet;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Read_Data(MS_U8 *pu8CmdData, MS_U8 u8DataLen)
{
    MS_U16 u16BusNumSlaveID = PANEL_INX_NOVA_VB1_I2C_ADDR;
    MS_U8 u8SubAddr[1] = {0x0C};
    MS_U8 u8SubAddrNum = sizeof(u8SubAddr);
    MS_BOOL bRet = FALSE;

    if(!g_Panel_I2C_Init)
    {
        MDrv_Panel_INX_NOVA_VB1_SWI2C_Init();
    }

    bRet = MDrv_Panel_INX_NOVA_VB1_SWI2C_ReadBytes(u16BusNumSlaveID, u8SubAddrNum, u8SubAddr, u8DataLen, pu8CmdData);
    MDrv_Panel_INX_NOVA_VB1_Print_Cmd(FALSE, pu8CmdData, u8DataLen);
    return bRet;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Print_Cmd(MS_BOOL bWrite, MS_U8 *pu8CmdData, MS_U8 u8CmdLen)
{
    MS_U8 u8Index = 0;

    if(bWrite)
    {
        printf("[INX_NOVA_VB1]Write cmd:");
    }
    else
    {
        printf("[INX_NOVA_VB1]Read cmd:");
    }
    while(u8Index < u8CmdLen)
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
MS_BOOL MDrv_Panel_INX_NOVA_VB1_Unlock_AHB(void)
{
    MS_BOOL bRet = FALSE;
    if(!g_AHB_Bridge_Unlock)
    {
        bRet = MDrv_Panel_INX_NOVA_VB1_SendCmd(CMD_INX_NOVA_VB1_UNLOCK_AHB, 0);
        g_AHB_Bridge_Unlock = bRet;
    }
    return bRet;
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Set_UHD_DIVISION(UHD_DIVISION_TYPE eDivisionType)
{
    MDrv_Panel_INX_NOVA_VB1_Unlock_AHB();
    return MDrv_Panel_INX_NOVA_VB1_SendCmd(CMD_INX_NOVA_VB1_SET_UHD_DIVISION_MODE, (MS_U8)eDivisionType);
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Set_INPUT_MODE(INPUT_TIMMING_TYPE eTimmingType)
{
    return MDrv_Panel_INX_NOVA_VB1_SendCmd(CMD_INX_NOVA_VB1_SET_INPUT_MODE, (MS_U8)eTimmingType);
}

MS_BOOL MDrv_Panel_INX_NOVA_VB1_Set_3D_MODE(INPUT_3D_TYPE e3DType)
{
    return MDrv_Panel_INX_NOVA_VB1_SendCmd(CMD_INX_NOVA_VB1_SET_3D_MODE, (MS_U8)e3DType);
}
#endif //__PANEL_INX_NOVA_VB1_C__

