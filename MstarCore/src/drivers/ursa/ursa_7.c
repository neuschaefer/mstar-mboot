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

#ifndef __DRV_URSA_7_C__
#define __DRV_URSA_7_C__

//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------
#include "ursa_7.h"

//-------------------------------------------------------------------------------------------------
//  Define
//-------------------------------------------------------------------------------------------------
#define URSA_7_CMD_DATA_SUM             (7)
#define URSA_7_I2C_BUS_NUM              (2)
#define URSA_7_DDC2BI_MODE_ADDR         (0x40)
#define URSA_7_I2C_SUB_ADDR             (0)

static SWI2C_BusCfg Ursa_7_I2cBusCfg[URSA_7_I2C_BUS_NUM]=
{
    // Bus-0
    {PAD_DDCR_CK, PAD_DDCR_DA, 400}, //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Bus-1
    {PAD_TGPIO2, PAD_TGPIO3, 400},   //IS_SW_I2C  /SCL_PAD /SDA_PAD /Delay
    // Others, add other bus here
};

//-------------------------------------------------------------------------------------------------
//  Function define
//-------------------------------------------------------------------------------------------------
void MDrv_Ursa_7_SWI2C_Init(void)
{
	MApi_SWI2C_Init(Ursa_7_I2cBusCfg, URSA_7_I2C_BUS_NUM);
}

MS_BOOL MDrv_Ursa_7_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_WriteBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Ursa_7_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_ReadBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Ursa_7_SendCmd(URSA_7_CMD_TYPE eCmdType)
{
    MS_U8 pCmdData[URSA_7_CMD_DATA_SUM] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    MS_BOOL bUnkown = FALSE;
    MS_BOOL bRet = FALSE;
    
    switch(eCmdType)
    {
         case UC_INIT_RX_ALL_1:
        {
            //0xB0, 0x01, 0x02, 0x03, 0x45, 0x00, 0x00
            pCmdData[0] = 0xB0;
            pCmdData[1] = 0x01;
            pCmdData[2] = 0x02;
            pCmdData[3] = 0x03;
            pCmdData[4] = 0x54;
            pCmdData[5] = 0x00;
            pCmdData[6] = 0x00;
        }
            break;
        
        case UC_INIT_RX_ALL_2:
            {
                //0x40, 0x02, 0x11, 0x00, 0x00, 0x01, 0x00}
                pCmdData[0] = 0x40;
                pCmdData[1] = 0x02;
                pCmdData[2] = 0x11;
                pCmdData[3] = 0x00;
                pCmdData[4] = 0x00;
                pCmdData[5] = 0x01;
                pCmdData[6] = 0x00;
                
            }
            break;
            
        case UC_SET_IN_VIDEO_SIZE:
          {
              //0x81, 0x05, 0x07, 0x80, 0x04, 0x38, 0x00 
              pCmdData[0] = 0x81;
              pCmdData[1] = 0x05;
              pCmdData[2] = 0x07;
              pCmdData[3] = 0x80;
              pCmdData[4] = 0x04;
              pCmdData[5] = 0x38;
              pCmdData[6] = 0x00;
              
          }
          break;

        case UC_SET_LVDS_RX_RECONFIG:
          {
              //0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00
              pCmdData[0] = 0x61;
              pCmdData[1] = 0x06;
              pCmdData[2] = 0x00;
              pCmdData[3] = 0x00;
              pCmdData[4] = 0x00;
              pCmdData[5] = 0x00;
              pCmdData[6] = 0x00;
              
          }
          break;
        case UC_SET_3D_MODE:
        {
            //0x81,0x05,0x07,0x80,0x04,0x38,0x00
            pCmdData[0] = 0x13;
            pCmdData[1] = 0x01;
            pCmdData[2] = 0x00;
            pCmdData[3] = 0x00;
            pCmdData[4] = 0x00;
            pCmdData[5] = 0x00;
            pCmdData[6] = 0x00;
            
        }
        break;
        case UC_WRITE_REGISTER_1:
          {
              //0x23,0x1B,0x10,0x27,0xC2,0xEE,0xD0,
              pCmdData[0] = 0x23;
              pCmdData[1] = 0x1B;
              pCmdData[2] = 0x10;
              pCmdData[3] = 0x27;
              pCmdData[4] = 0xC2;
              pCmdData[5] = 0xEE;
              pCmdData[6] = 0xD0;

          }
          break;
          case UC_WRITE_REGISTER_2:
            {
                //0x23,0x1B,0x10,0x27,0x40,0x40,0xD0
                pCmdData[0] = 0x23;
                pCmdData[1] = 0x1B;
                pCmdData[2] = 0x10;
                pCmdData[3] = 0x27;
                pCmdData[4] = 0x40;
                pCmdData[5] = 0x40;
                pCmdData[6] = 0xD0;

            }
            break;
           case UC_WRITE_REGISTER_3:
          {
              //0x33,0x1B,0x10,0x27,0xC3,0xEE,0xD0
              pCmdData[0] = 0x33;
              pCmdData[1] = 0x1B;
              pCmdData[2] = 0x10;
              pCmdData[3] = 0x27;
              pCmdData[4] = 0xC3;
              pCmdData[5] = 0xEE;
              pCmdData[6] = 0xD0;

          }
          break;
         case UC_WRITE_REGISTER_MASK_1:
          {
              //0x33,0x1C,0x13,0x00,0x04,0x40,0x40
              pCmdData[0] = 0x33;
              pCmdData[1] = 0x1C;
              pCmdData[2] = 0x13;
              pCmdData[3] = 0x00;
              pCmdData[4] = 0x04;
              pCmdData[5] = 0x40;
              pCmdData[6] = 0x40;

          }
          break;
          case UC_WRITE_REGISTER_MASK_2:
            {
                //0x33,0x1C,0x13,0x00,0x04,0x00,0x40
                pCmdData[0] = 0x33;
                pCmdData[1] = 0x1C;
                pCmdData[2] = 0x13;
                pCmdData[3] = 0x00;
                pCmdData[4] = 0x04;
                pCmdData[5] = 0x00;
                pCmdData[6] = 0x40;

            }
            break;

        case UC_URSA_MOD_POWER_ON:
            {
                //URSA MOD Power On command: 0x93, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x93;
                pCmdData[1] = 0x08;
                pCmdData[2] = 0x01;
                pCmdData[3] = 0x00;
                pCmdData[4] = 0x00;
                pCmdData[5] = 0x00;
                pCmdData[6] = 0x00;
        
            }
            break;

        default:
            bUnkown = TRUE;
            break;
    }

    if(!bUnkown)
    {
        bRet  = MDrv_Ursa_7_Write_Cmd(pCmdData);
        printf("[Ursa7]Send cmd:%d, return:%d\n", eCmdType, bRet);
    }
    else
    {
        bRet = FALSE;
        printf("[Ursa7]Can not find the command, please check!\n");
    }
    
    return bRet;
}

MS_BOOL MDrv_Ursa_7_Write_Cmd(MS_U8 *pu8CmdData)
{
    MS_U16 u16BusNumSlaveID = URSA_7_DDC2BI_MODE_ADDR;
    MS_U8 u8SubAddr = URSA_7_I2C_SUB_ADDR;
    
    MDrv_Ursa_7_SWI2C_Init();
    printf("[Ursa7]Write cmd:%x,%x,%x,%x,%x,%x,%x\n", pu8CmdData[0], pu8CmdData[1], pu8CmdData[2], pu8CmdData[3], pu8CmdData[4], pu8CmdData[5], pu8CmdData[6]);
    return MDrv_Ursa_7_SWI2C_WriteBytes(u16BusNumSlaveID, u8SubAddr, NULL, URSA_7_CMD_DATA_SUM, pu8CmdData);
}
//-------------------------------------------------------------------------------------------------
//  Member Function
//-------------------------------------------------------------------------------------------------

MS_BOOL MDrv_Ursa_7_Set_2_lane_VB1(void)
{
        MS_BOOL bRet = FALSE;
        MS_U8 retryCount=0;
        MS_U8 MaxRetry=10;
        do
        {
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
        
            printf("delay Done......\n");
            bRet=MDrv_Ursa_7_SendCmd(UC_SET_IN_VIDEO_SIZE);
            retryCount=retryCount+1;

        }while ( (bRet==FALSE) && ( retryCount<MaxRetry));

            udelay(50);
            MDrv_Ursa_7_SendCmd(UC_SET_3D_MODE);
            udelay(50);
            MDrv_Ursa_7_SendCmd(UC_URSA_MOD_POWER_ON);
            udelay(50);
        return bRet;
}

MS_BOOL MDrv_Ursa_7_Set_2_lane_VB1_per_init(void)
{
        MS_BOOL bRet = FALSE;
        MS_U8 retryCount=0;
        MS_U8 MaxRetry=20;
        do
        {
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay ..........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay...........\n");
            udelay(50000);
            printf("delay Done......\n");
            bRet=MDrv_Ursa_7_SendCmd(UC_INIT_RX_ALL_1);
            retryCount=retryCount+1;

        }while ( (bRet==FALSE) && ( retryCount<MaxRetry));

        udelay(50);
        MDrv_Ursa_7_SendCmd(UC_INIT_RX_ALL_2);
        udelay(50);
        MDrv_Ursa_7_SendCmd(UC_SET_LVDS_RX_RECONFIG);
        udelay(50);
        return bRet;
}

#endif //__DRV_URSA_7_C__

