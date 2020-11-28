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
/// file    msAPI_CEC.c
/// @author MStar Semiconductor Inc.
/// @brief  HDMI CEC API Interface
///////////////////////////////////////////////////////////////////////////////////////////////////

#define MSAPI_CEC_C

#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "drvGlobal.h"
#include "hwreg.h"
#include "MsCommon.h"
#include "apiCEC.h"
#include "msAPI_CEC.h"
#include "MApp_Wakeup.h"

//**************************************************************************

#define CEC_DPRINTF(x)     //x

///////////////////////////////////////////////////////////////////////////////////////////////////

extern void SystemWholeChipReset(void);

///////////////////////////////////////////////////////////////////////////////////////////////////


#define ONE_TOUCH_PLAY_SUPPORT          1
#define ROUTING_CONTROL_SUPPORT         1
#define STANDBY_COMMAND_SUPPORT         1
#define SYSTEM_INFORMATION_SUPPORT      1

extern void MDrv_CEC_Standby_Init(MS_U32 u32XTAL_CLK_Hz);

//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecInit()
//  [Description]
//                  CEC initial sequence
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_Init(void)
{
  #if 0
    MS_CEC_INIT_INFO stCECInfo;

    stCECInfo.u32XTAL_CLK_Hz = FREQ_12MHZ;

    MApi_CEC_Init(&stCECInfo);
  #else
    MDrv_CEC_Standby_Init(FREQ_12MHZ);
  #endif
}

//**************************************************************************
//  [Function Name]:
//                   MsAPI_CECProcessCmd()
//  [Description]
//                   It used to parse CEC command
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_ProcessCmd(void)
{
    U8 header, para0, para1, para2, len;
    MsCEC_MSGLIST opcode;
    MsCEC_DEVICELA enDevice;
    U8 u8Fifoidx;
    BOOLEAN bWakeup = FALSE;

    header = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 0);
    opcode = (MsCEC_MSGLIST)  MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 1);
    para0 =  MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 2);
    para1 =  MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 3);
    para2 =  MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 4);
    len = MApi_CEC_GetCmdLen();
    enDevice = (MsCEC_DEVICELA)( (header & 0xF0) >> 4 );

    if (MApi_CEC_GetMsgCnt() == 0 )
    {
        return;  //no received message to process
    }

    CEC_DPRINTF(printf("[CEC] header = 0x%x \r\n", header));
    CEC_DPRINTF(printf("[CEC] opcode = 0x%x \r\n", opcode));
    CEC_DPRINTF(printf("[CEC] para0  = 0x%x \r\n", para0));
    CEC_DPRINTF(printf("[CEC] para1  = 0x%x \r\n", para1));
    CEC_DPRINTF(printf("[CEC] para2  = 0x%x \r\n", para2));
    CEC_DPRINTF(printf(" len      = %d \r\n", len));
    CEC_DPRINTF(printf(" enDevice = 0x%x \r\n", enDevice));

    switch (opcode)
    {

    //----- One Touch Play ---------------
    #if ONE_TOUCH_PLAY_SUPPORT

        case E_MSG_ACTIVE_SOURCE:             //broadcast, if addressed, ignored
            CEC_DPRINTF(printf("got E_MSG_ACTIVE_SOURCE \r\n"));
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4)==0)   break;

            CEC_DPRINTF(printf("Active Source \r\n"));
            bWakeup = TRUE;
            break;

        case E_MSG_OTP_IMAGE_VIEW_ON:     //if in standby, firstly power on
            CEC_DPRINTF(printf("got E_MSG_OTP_IMAGE_VIEW_ON \r\n"));
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2)==0)  break;

            CEC_DPRINTF(printf("Image View On \r\n"));
            bWakeup = TRUE;
            break;

        case E_MSG_OTP_TEXT_VIEW_ON:     //if in standby, firstly power on
            CEC_DPRINTF(printf("got E_MSG_OTP_TEXT_VIEW_ON \r\n"));
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2)==0)  break;

            CEC_DPRINTF(printf("Text View On \r\n"));
            bWakeup = TRUE;
            break;

    #endif
    //----- One Touch Play end ---------------


    //----- System Information -----------
    #if SYSTEM_INFORMATION_SUPPORT

        case E_MSG_SI_REQUEST_PHY_ADDR:
            CEC_DPRINTF(printf("got E_MSG_SI_REQUEST_PHY_ADDR \r\n"));
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2)==0)  break;

            CEC_DPRINTF(printf("Report Power Status \r\n"));
            MApi_CEC_Msg_ReportPhycalAddress();
            break;

        case E_MSG_SI_REPORT_PHY_ADDR:
        {
            MS_U8 txbuf[2];

            txbuf[0] = para0;
            txbuf[1] = para1;

            CEC_DPRINTF(printf("got E_MSG_SI_REPORT_PHY_ADDR \r\n"));
            if(MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 5) == 0) break;

            MApi_CEC_SetActivePhysicalAddress(para0, para1);
            CEC_DPRINTF(printf(" = SetActivePhysicalAddress 0x%x", para0));
            CEC_DPRINTF(printf(" 0x%x = \r\n", para1));
            MApi_CEC_SetActiveDeviceType((MsCEC_DEVICE_TYPE) para2);
            CEC_DPRINTF(printf(" = SetActiveDeviceType 0x%x = \r\n", para2));

            if (enDevice != E_LA_BROADCAST)
            {
                MApi_CEC_TxSendMsg(MApi_CEC_GetActiveLogicalAddress(), E_MSG_OSDNT_GIVE_OSD_NAME, 0, 0);
            }
        }
            break;
    #endif
    //----- System Information end -----------


        default:
            CEC_DPRINTF(printf("Keep Status \r\n"));
            break;
    }

    if (bWakeup)
    {
        msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_CEC);

        SystemWholeChipReset();
    }

    u8Fifoidx = MApi_CEC_GetFifoIdx();

    if((u8Fifoidx+1)>=CEC_FIFO_CNT)
        MApi_CEC_SetFifoIdx(0);
    else
        MApi_CEC_SetFifoIdx(u8Fifoidx+1);

    MApi_CEC_SetMsgCnt(MApi_CEC_GetMsgCnt() - 1);
}

//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecCecHandler()
//  [Description]
//                   CEC handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_Handler(void)
{
#if(!ENABLE_CEC_INT) // if not enable CEC interrupt, use sw polling to instead of
    MApi_CEC_ChkRxBuf();
#endif

    msAPI_CEC_ProcessCmd();
}



////////////////////////////////////////////////////////////////////////////////
#undef MSAPI_CEC_C

