//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (¡§MStar Software¡¨) are intellectual property of MStar Semiconductor, Inc. (¡§MStar¡¨) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar. 
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (¡§Terms¡¨) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party¡¦s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party¡¦s software. 
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar¡¦s confidential information and you agree to keep MStar¡¦s confidential information in strictest confidence and not disclose to any third party.  
//4. MStar Software is provided on an ¡§AS IS¡¨ basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.  
//   In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer¡¦s product (¡§Services¡¨).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an ¡§AS IS¡¨ basis and the warranty disclaimer set forth in Section 4 above shall apply.  
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.  
//   The arbitration award shall be final and binding to both parties.
//***********************************************************************************
//<MStar Software>


////////////////////////////////////////////////////////////////////////////////
//
/// @file apiSecureBoot.h
/// This file includes MStar application interface for Secure Boot
/// @brief API for Secure Boot
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define API_SECUREBOOT_C

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <ShareType.h>
#include <linux/string.h> //for memset()
#include <uboot_mmap.h>
#include <MsSystem.h>
#include <secure/apiSecureBoot.h>
#include <drvMBX.h>
#include <MsDebug.h>
#include <malloc.h>
#include <drvAESDMA.h>
#include <secure/MsSecureCommon.h>

extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Local Compiler Options
//-------------------------------------------------------------------------------------------------
#define SB_API_DBG(x)   x

#if defined (CONFIG_SECURITY_BOOT)
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define SECUREBOOT_MBX_QUEUESIZE        8
#define SECUREBOOT_MBX_TIMEOUT          5000

#define RIU_TMPBASE 0xBF200000  //for test
#define CMEM(addr)         (*((volatile unsigned char*)(addr)))
#define AES_BUF_ALIGNMENT_SIZE 16  //for Secure_R2_SHA256
#define SACTTERGATHER_TABLE_SIZE 16  //for Secure_R2_SHA256
//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
static SECUREBOOT_Result gSecureBootResult;
static SECUREBOOT_AckFlags gSecureBootAckFlags;
static MBX_Result gMBXResult;

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
#if !defined(CONFIG_MSTAR_CLEANBOOT)
static void _SecureBoot_MailBoxHandler(MBX_Class eMsgClass, SECUREBOOT_MbxRetStruct *pSecureBootRetStruct)
{
    MBX_Msg MB_Command;

    if(eMsgClass != E_MBX_CLASS_SECURE_WAIT)
    {
        //printf("Invalid Message Class!\n");
        return;
    }

    gMBXResult = MDrv_MBX_RecvMsg(eMsgClass, &MB_Command, SECUREBOOT_MBX_TIMEOUT/*ms*/, MBX_CHECK_NORMAL_MSG);

    if (gMBXResult == E_MBX_ERR_TIME_OUT)
    {
        printf("Handler Timeout!\n");
        return;
    }

    if (gMBXResult == E_MBX_SUCCESS)
    {
        if ((MB_Command.u8Ctrl != 0) && (MB_Command.u8Ctrl != 1))
        {
            gSecureBootResult = E_SECUREBOOT_FAIL;
            printf("Not Implemented!\n");
            return;
        }

        {
            MS_U8 i;
            //printf("Get SECURE command: 0x%02x, 0x%02x\n", MB_Command.u8Index, MB_Command.u8ParameterCount);
            for(i=0; i<MB_Command.u8ParameterCount; i++)
            {
                printf("Parameter[%d]=0x%02x\n", i, MB_Command.u8Parameters[i]);
            }
        }

       gSecureBootResult = E_SECUREBOOT_FAIL;
        switch (MB_Command.u8Index)
        {
            case E_SECUREENG_51ToCPU_CMD_ACK_GETKEY:
                gSecureBootResult = E_SECUREBOOT_OK;
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_GETKEY);
                //printf("mailbox:E_SECUREENG_51ToCPU_CMD_ACK_GETKEY \n");
                break;
            case E_SECUREENG_51ToCPU_CMD_ACK_AES_ENCODE:
                gSecureBootResult = E_SECUREBOOT_OK;
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_AESENCODE);
                //printf("mailbox:E_SECUREENG_51ToCPU_CMD_ACK_AES_ENCODE \n");
                break;
            case E_SECUREENG_51ToCPU_CMD_ACK_AES_DECODE:
                gSecureBootResult = E_SECUREBOOT_OK;
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_AESDECODE);
                //printf("mailbox:E_SECUREENG_51ToCPU_CMD_ACK_AES_DECODE \n");
                break;
            case E_SECUREENG_51ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION:
                gSecureBootResult = E_SECUREBOOT_OK;
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION);
                //printf("mailbox:E_SECUREENG_51ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION \n");
                break;
            case E_SECUREENG_51ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY:
                gSecureBootResult = E_SECUREBOOT_OK;
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY);
                //printf("mailbox:E_SECUREENG_51ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY \n");
            case E_SECUREENG_51ToCPU_CMD_ACK_GETDID:
                gSecureBootResult = E_SECUREBOOT_OK;
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_GETDID);
                
                break;
            default:
                break;
        }
    }
    return;
}


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
/******************************************************************************/
/// API for Secure Boot init Mailbox:
/// Secure_MailBox_Init
/// @param \b IN:
/// @param \b IN:
/// @return BOOLEAN: Success or not
/// - TRUE: Success
/// - FALSE: Fail
/******************************************************************************/

MS_BOOL Secure_MailBox_Init(void)
{
    UBOOT_TRACE("IN\n");
    if(MsApi_MBX_Init()==TRUE)
    {

        if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_SECURE_WAIT, SECUREBOOT_MBX_QUEUESIZE))
    {
            UBOOT_DEBUG("E_MBX_CLASS_SECURE_WAIT - MBX register msg error\n");
    }
        UBOOT_TRACE("OK\n");
        return TRUE;
    }
    else
    {
        UBOOT_ERROR("fail\n");
        return FALSE;
    }
}

MS_BOOL Secure_MailBox_Deinit(void)
{
    UBOOT_TRACE("IN\n");
    if( E_MBX_SUCCESS != MDrv_MBX_UnRegisterMSG(E_MBX_CLASS_SECURE_WAIT, TRUE))
    {
        UBOOT_DEBUG("@@ E_MBX_CLASS_SECURE_WAIT - MBX unregister msg error\n");
    }
    UBOOT_TRACE("OK\n");
    return TRUE;
}

SECUREBOOT_Result Secure_MailBox_GetKey(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct,U32 u32OutAddr,U8  u8KeyImageIndex,U16  u16LenInKeyImage)
{
    MBX_Msg MB_Command;
    UBOOT_TRACE("IN\n");
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_GETKEY;

    //(1) send to PM51
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_GETKEY;
    MB_Command.u8ParameterCount = 10;
    #if 1
    MB_Command.u8Parameters[0] =  (U8)(u32OutAddr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32OutAddr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32OutAddr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32OutAddr&0x000000FF);
    MB_Command.u8Parameters[4] =   u8KeyImageIndex;
    MB_Command.u8Parameters[5] =  (U8)(u16LenInKeyImage>>8);
    MB_Command.u8Parameters[6] =  (U8)(u16LenInKeyImage&0xFF);
    MB_Command.u8Parameters[7] =  0;
    MB_Command.u8Parameters[8] =  0;
    MB_Command.u8Parameters[9] =  0;
    #endif
    MDrv_MBX_SendMsg(&MB_Command);
    UBOOT_DEBUG("wait mailbx response\n");
    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_SECURE_WAIT, pSecureBootMbxRetStruct);
    }
    while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_GETKEY) && (gMBXResult != E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(gSecureBootResult == E_SECUREBOOT_FAIL)
    {
        UBOOT_ERROR("Fail\n");
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;

}

SECUREBOOT_Result Secure_MailBox_AESEncode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U32 u32Len, U8 u8Mode)
{
    MBX_Msg MB_Command;
    UBOOT_TRACE("IN\n");
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_AESENCODE;

    //(1) send to PM51
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_AES_ENCODE;
    MB_Command.u8ParameterCount = 10;
    MB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32Addr&0x000000FF);

    MB_Command.u8Parameters[4] =  (U8)(u32Len>>24);
    MB_Command.u8Parameters[5] =  (U8)(u32Len>>16);
    MB_Command.u8Parameters[6] =  (U8)(u32Len>>8);
    MB_Command.u8Parameters[7] =  (U8)(u32Len&0x000000FF);

    MB_Command.u8Parameters[8] =  u8Mode;
    MB_Command.u8Parameters[9] =  0;

    MDrv_MBX_SendMsg(&MB_Command);

    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_SECURE_WAIT, pSecureBootMbxRetStruct);
    }
    while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_AESENCODE) && (gMBXResult != E_MBX_ERR_TIME_OUT));


    //(3) check result
    if(gSecureBootResult == E_SECUREBOOT_FAIL)
    {
        UBOOT_ERROR("Secure_MailBox_AESEncode Fail\n");
        //while(1);
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}

SECUREBOOT_Result Secure_MailBox_ASSIGN_DECRYPTED_KEY(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U8  u8KeyImageIndex,U16  u16LenInKeyImage, U8 u8IsNoSwap)
{
    MBX_Msg MB_Command;
    UBOOT_TRACE("IN\n");

    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    //gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_AESDECODE;
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY;

    //(1) send to PM51
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_ASSIGN_DECRYPTED_KEY;
    MB_Command.u8ParameterCount = 10;
    MB_Command.u8Parameters[0] =  u8KeyImageIndex;
    MB_Command.u8Parameters[1] =  (U8)(u16LenInKeyImage>>8);
    MB_Command.u8Parameters[2] =  (U8)(u16LenInKeyImage&0xFF);
    MB_Command.u8Parameters[3] =  u8IsNoSwap;
    MB_Command.u8Parameters[4] =  0;
    MB_Command.u8Parameters[5] =  0;
    MB_Command.u8Parameters[6] =  0;
    MB_Command.u8Parameters[7] =  0;
    MB_Command.u8Parameters[8] =  0;
    MB_Command.u8Parameters[9] =  0;

    MDrv_MBX_SendMsg(&MB_Command);
        //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_SECURE_WAIT, pSecureBootMbxRetStruct);
    }
    //while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_AESDECODE) && (gMBXResult != E_MBX_ERR_TIME_OUT));
    while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY) && (gMBXResult != E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(gSecureBootResult == E_SECUREBOOT_FAIL)
    {
        UBOOT_ERROR("Secure_MailBox_ASSIGN_DECRYPTED_KEY Fail\n");
        //while(1);
    }
    else
    {
         UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;

}

SECUREBOOT_Result Secure_MailBox_SET_KEY_WITH_DECRYPTION(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U16 u16Len, U16 u16KeyOffset,U8 u8Mode)
{
    MBX_Msg MB_Command;
    UBOOT_TRACE("IN\n");

    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    //gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_AESDECODE;
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION;

    //(1) send to PM51
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_SETEKEY_WITH_DECRYPTION;
    MB_Command.u8ParameterCount = 10;

    MB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32Addr&0x000000FF);

    MB_Command.u8Parameters[4] =  (U8)(u16Len>>8);
    MB_Command.u8Parameters[5] =  (U8)(u16Len&0x000000FF);

    MB_Command.u8Parameters[6] =  (U8)(u16KeyOffset>>8);
    MB_Command.u8Parameters[7] =  (U8)(u16KeyOffset&0x000000FF);

    MB_Command.u8Parameters[8] =  (U8)(u8Mode);
    MB_Command.u8Parameters[9] =  0;


    MDrv_MBX_SendMsg(&MB_Command);

    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_SECURE_WAIT, pSecureBootMbxRetStruct);
    }
    //while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_AESDECODE) && (gMBXResult != E_MBX_ERR_TIME_OUT));
    while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION) && (gMBXResult != E_MBX_ERR_TIME_OUT));



    //(3) check result
    if(gSecureBootResult == E_SECUREBOOT_FAIL)
    {
        UBOOT_ERROR("Secure_MailBox_ASSIGN_DECRYPTED_KEY Fail\n");
        //while(1);
    }
    else
    {
       UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;

}



SECUREBOOT_Result Secure_MailBox_AESDecode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U32 u32Len, U8 u8Mode)
{
    MBX_Msg MB_Command;
    UBOOT_TRACE("IN\n");

    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_AESDECODE;


    //(1) send to PM51
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_AES_DECODE;


    MB_Command.u8ParameterCount = 10;
    MB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32Addr&0x000000FF);

    MB_Command.u8Parameters[4] =  (U8)(u32Len>>24);
    MB_Command.u8Parameters[5] =  (U8)(u32Len>>16);
    MB_Command.u8Parameters[6] =  (U8)(u32Len>>8);
    MB_Command.u8Parameters[7] =  (U8)(u32Len&0x000000FF);

    MB_Command.u8Parameters[8] =  (U8)(u8Mode);
    MB_Command.u8Parameters[9] =  0;

    MDrv_MBX_SendMsg(&MB_Command);


    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_SECURE_WAIT, pSecureBootMbxRetStruct);
    }
    while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_AESDECODE) && (gMBXResult != E_MBX_ERR_TIME_OUT));



    //(3) check result
    if(gSecureBootResult == E_SECUREBOOT_FAIL)
    {
        UBOOT_ERROR("Secure_MailBox_AESDecode Fail\n");
        //while(1);
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}


SECUREBOOT_Result Secure_MailBox_GETDID(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U16 u16Len)
{
    MBX_Msg MB_Command;
    UBOOT_TRACE("IN\n");

    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_GETDID;


    //(1) send to PM51
    MB_Command.eRoleID = E_MBX_ROLE_PM;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_GETDID;


    MB_Command.u8ParameterCount = 10;
    MB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32Addr&0x000000FF);

    MB_Command.u8Parameters[4] =  (U8)(u16Len>>8);
    MB_Command.u8Parameters[5] =  (U8)(u16Len&0x000000FF);
    MB_Command.u8Parameters[6] =  0;
    MB_Command.u8Parameters[7] =  0;
    MB_Command.u8Parameters[8] =  0;
    MB_Command.u8Parameters[9] =  0;

    MDrv_MBX_SendMsg(&MB_Command);


    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_SECURE_WAIT, pSecureBootMbxRetStruct);
    }
    while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_GETDID) && (gMBXResult != E_MBX_ERR_TIME_OUT));



    //(3) check result
    if(gSecureBootResult == E_SECUREBOOT_FAIL)
    {
        UBOOT_ERROR("Secure_MailBox_AESDecode Fail\n");
        //while(1);
    }
    else
    {
        //printf("Secure_MailBox_AESDecode OK\n");
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}

#else // CONFIG_MSTAR_CLEANBOOT
#include <secure/crypto_rsa.h>
#include <secure/crypto_sha.h>
static void _SecureBoot_MailBoxHandler(MBX_Class eMsgClass, SECUREBOOT_MbxRetStruct *pSecureBootRetStruct)
{
    MBX_Msg MB_Command;

    memset(&MB_Command,0,sizeof(MB_Command));
    if(E_MBX_CLASS_CB_SECURE_WAIT != eMsgClass)
    {
        UBOOT_DEBUG("Invalid Message Class!\n");
        return;
    }
    gSecureBootResult = E_SECUREBOOT_FAIL;
    gMBXResult = MDrv_MBX_RecvMsg(eMsgClass, &MB_Command, SECUREBOOT_MBX_TIMEOUT/*ms*/, MBX_CHECK_INSTANT_MSG);
    if (E_MBX_ERR_TIME_OUT == gMBXResult)
    {
        UBOOT_DEBUG("Handler Timeout!\n");
        return;
    }

    if (E_MBX_SUCCESS == gMBXResult)
    {
        UBOOT_DEBUG("MB_Command.u8Index:%d\n",MB_Command.u8Index);
        switch (MB_Command.u8Index)
        {
            case E_SECUREENG_R2ToCPU_CMD_ACK_GETKEY:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_GETKEY);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_GETKEY \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_AES_ENCODE:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_AESENCODE);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_AES_ENCODE \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_AES_DECODE:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_AESDECODE);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_AES_DECODE \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_GETDID:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_GETDID);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_GETDID \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_SHA:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_SHA);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_SHA \n");
                break;
            case E_SECUREENG_R2ToCPU_CMD_ACK_RSA_DECODE:
                gSecureBootAckFlags &= (SECUREBOOT_AckFlags)(~E_SECUREBOOT_ACKFLG_WAIT_RSADECODE);
                UBOOT_DEBUG("mailbox:E_SECUREENG_R2ToCPU_CMD_ACK_RSA_DECODE \n");
                break;
            default:
                UBOOT_DEBUG("mailbox:default \n");
                break;
        }

        //check command whether executed success by R2
        gSecureBootResult = MB_Command.u8Parameters[0];
        if(E_SECUREBOOT_FAIL == gSecureBootResult)
        {
            UBOOT_ERROR("R2 execute command Failed\n");
        }
    }
    return;
}

MS_BOOL Secure_MailBox_Init(void)
{
    UBOOT_TRACE("IN\n");

    //MDrv_MBX_SetDbgLevel(MBX_DBG_LEVEL_ALL);
    MsApi_MBX_Init();
    MBX_Result MbxResult = MDrv_MBX_RegisterMSG(E_MBX_CLASS_CB_SECURE_WAIT, SECUREBOOT_MBX_QUEUESIZE);
    if (E_MBX_SUCCESS != MbxResult)
    {
         UBOOT_ERROR("E_MBX_CLASS_CB_SECURE_WAIT - MBX register msg error:%d\n",MbxResult);
         return FALSE;
    }

    MbxResult = MDrv_MBX_RegisterMSG(E_MBX_CLASS_CB_SECURE_NOWAIT, SECUREBOOT_MBX_QUEUESIZE);
    if (E_MBX_SUCCESS != MbxResult)
    {
         UBOOT_ERROR("E_MBX_CLASS_CB_SECURE_NOWAIT - MBX register msg error:%d\n",MbxResult);
         return FALSE;
    }

    //udelay(100000);

    UBOOT_TRACE("OK\n");
    return TRUE;
}

MS_BOOL Secure_MailBox_Deinit(void)
{
    UBOOT_TRACE("IN\n");

    if (E_MBX_SUCCESS != MDrv_MBX_UnRegisterMSG(E_MBX_CLASS_CB_SECURE_WAIT, TRUE))
    {
        UBOOT_DEBUG("@@ E_MBX_CLASS_CB_SECURE_WAIT - MBX unregister msg error\n");
    }

    if (E_MBX_SUCCESS != MDrv_MBX_UnRegisterMSG(E_MBX_CLASS_CB_SECURE_NOWAIT, TRUE))
    {
        UBOOT_DEBUG("@@ E_MBX_CLASS_CB_SECURE_NOWAIT - MBX unregister msg error\n");
    }

    UBOOT_TRACE("OK\n");
    return TRUE;
}

static SECUREBOOT_Result Secure_MailBox_AESEncode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32PAAddr, U32 u32Len,U32 u32PAKeyAddr, U8 u8Mode)
{

    UBOOT_TRACE("IN\n");
    MBX_Msg MB_Command;
    SECUREBOOT_INFO SecurebootInfo;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    memset((void*)&SecurebootInfo, 0, sizeof(SECUREBOOT_INFO));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_AESENCODE;
    SecurebootInfo.u32PAInAddr = u32PAAddr;
    SecurebootInfo.u32InLen = u32Len;
    SecurebootInfo.u32PAAESKeyAddr = u32PAKeyAddr;
    SecurebootInfo.eAESMode = u8Mode;
    MS_U32 u32PASecurebootInfo = VA2PA((MS_U32)&SecurebootInfo);
    flush_cache((MS_U32)&SecurebootInfo,sizeof(SECUREBOOT_INFO));
    //(1) send to R2
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_CB_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_AES_ENCODE;
    MB_Command.u8ParameterCount = 4;
    MB_Command.u8Parameters[0] =  (U8)(u32PASecurebootInfo>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32PASecurebootInfo>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32PASecurebootInfo>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32PASecurebootInfo&0x000000FF);

    MDrv_MBX_SendMsg(&MB_Command);
    UBOOT_DEBUG("wait mailbx response\n");

    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_CB_SECURE_WAIT, pSecureBootMbxRetStruct);
    }while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_AESENCODE) && (E_MBX_ERR_TIME_OUT != gMBXResult));
    UBOOT_DEBUG("_SecureBoot_MailBoxHandle OK\n");
    //(3) check result
    if(E_SECUREBOOT_FAIL == gSecureBootResult)
    {
        UBOOT_ERROR("Fail\n");
        //while(1);
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}

static SECUREBOOT_Result Secure_MailBox_AESDecode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32PAAddr, U32 u32Len,U32 u32PAKeyAddr , U8 u8Mode)
{
    UBOOT_TRACE("IN\n");
    MBX_Msg MB_Command;
    SECUREBOOT_INFO SecurebootInfo;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    memset((void*)&SecurebootInfo, 0, sizeof(SECUREBOOT_INFO));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_AESDECODE;
    SecurebootInfo.u32PAInAddr = u32PAAddr;
    SecurebootInfo.u32InLen = u32Len;
    SecurebootInfo.u32PAAESKeyAddr = u32PAKeyAddr;
    SecurebootInfo.eAESMode = u8Mode;
    MS_U32 u32PASecurebootInfo = VA2PA((MS_U32)&SecurebootInfo);
    flush_cache((MS_U32)&SecurebootInfo,sizeof(SECUREBOOT_INFO));
    //(1) send to R2
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_CB_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_AES_DECODE;
    MB_Command.u8ParameterCount = 4;
    MB_Command.u8Parameters[0] =  (U8)(u32PASecurebootInfo>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32PASecurebootInfo>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32PASecurebootInfo>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32PASecurebootInfo&0x000000FF);

    MDrv_MBX_SendMsg(&MB_Command);
    UBOOT_DEBUG("wait mailbx response\n");

    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_CB_SECURE_WAIT, pSecureBootMbxRetStruct);
    } while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_AESDECODE) && (E_MBX_ERR_TIME_OUT != gMBXResult));

    //(3) check result
    if(E_SECUREBOOT_FAIL == gSecureBootResult)
    {
        UBOOT_ERROR("Fail\n");
        //while(1);
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}

static SECUREBOOT_Result Secure_MailBox_SHA(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32PAInAddr, U32 u32Len, U32 u32PAOutAddr,U8 u8Mode)
{
    UBOOT_TRACE("IN\n");
    MBX_Msg MB_Command;
    SECUREBOOT_INFO SecurebootInfo;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    memset((void*)&SecurebootInfo, 0, sizeof(SECUREBOOT_INFO));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_SHA;
    SecurebootInfo.u32PAInAddr = u32PAInAddr;
    SecurebootInfo.u32PAOutAddr = u32PAOutAddr;
    SecurebootInfo.u32InLen = u32Len;
    SecurebootInfo.eSHAMode = u8Mode;
    MS_U32 u32PASecurebootInfo = VA2PA((MS_U32)&SecurebootInfo);
    flush_cache((MS_U32)&SecurebootInfo,sizeof(SECUREBOOT_INFO));
    //(1) send to R2
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_CB_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_SHA;
    MB_Command.u8ParameterCount = 4;
    MB_Command.u8Parameters[0] =  (U8)(u32PASecurebootInfo>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32PASecurebootInfo>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32PASecurebootInfo>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32PASecurebootInfo&0x000000FF);

    MDrv_MBX_SendMsg(&MB_Command);
    UBOOT_DEBUG("wait mailbx response\n");

    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_CB_SECURE_WAIT, pSecureBootMbxRetStruct);
    }while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_SHA) && (E_MBX_ERR_TIME_OUT != gMBXResult));

    //(3) check result
    if(E_SECUREBOOT_FAIL == gSecureBootResult)
    {
        UBOOT_ERROR("Fail\n");
        //while(1);
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}
static SECUREBOOT_Result Secure_MailBox_RSADecrypt(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32PAInAddr,U32 u32PAKeyNAddr, U32 u32PAKeyEAddr,U32 u32PAOutAddr, U8 u8Mode)
{
    UBOOT_TRACE("IN\n");
    MBX_Msg MB_Command;
    SECUREBOOT_INFO SecurebootInfo;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));
    memset((void*)&SecurebootInfo, 0, sizeof(SECUREBOOT_INFO));
    gSecureBootAckFlags |= E_SECUREBOOT_ACKFLG_WAIT_RSADECODE;
    SecurebootInfo.u32PAInAddr = u32PAInAddr;
    SecurebootInfo.u32PAOutAddr = u32PAOutAddr;
    SecurebootInfo.u32PARSAKeyNAddr = u32PAKeyNAddr;
    SecurebootInfo.u32PARSAKeyEAddr = u32PAKeyEAddr;
    SecurebootInfo.eRSAMode = u8Mode;
    MS_U32 u32PASecurebootInfo = VA2PA((MS_U32)&SecurebootInfo);
    flush_cache((MS_U32)&SecurebootInfo,sizeof(SECUREBOOT_INFO));
    //(1) send to R2
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_CB_SECURE_NOWAIT;
    MB_Command.u8Index = E_CMD_SECUREENG_RSA_DECODE;
    MB_Command.u8ParameterCount = 4;
    MB_Command.u8Parameters[0] =  (U8)(u32PASecurebootInfo>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32PASecurebootInfo>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32PASecurebootInfo>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32PASecurebootInfo&0x000000FF);

    MDrv_MBX_SendMsg(&MB_Command);
    UBOOT_DEBUG("wait mailbx response\n");

    //(2) Waiting for SECURE BOOT message done
    do
    {
        _SecureBoot_MailBoxHandler(E_MBX_CLASS_CB_SECURE_WAIT, pSecureBootMbxRetStruct);
    }while((gSecureBootAckFlags & E_SECUREBOOT_ACKFLG_WAIT_RSADECODE) && (E_MBX_ERR_TIME_OUT != gMBXResult));

    //(3) check result
    if(E_SECUREBOOT_FAIL == gSecureBootResult)
    {
        UBOOT_ERROR("Fail\n");
        //while(1);
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return gSecureBootResult;
}

MS_U32 Secure_R2_AES128Encode(U32 u32Addr, U32 u32Len,  U8 *bKey)

{
    UBOOT_TRACE("IN\n");

    //check u32InLen align 16
    if(0 != u32Len%16)
    {
         UBOOT_ERROR("u32InLen should align 16\n");
         return -1;
    }

    flush_cache(u32Addr,u32Len);
    U32 u32PAKeyAddr = 0;
    //if bKey == NULL ,we use EFuse key
    if(bKey)
    {
        flush_cache((U32)bKey,AES_KEY_LEN);
        u32PAKeyAddr = VA2PA((U32)bKey);
    }
    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
    if(E_SECUREBOOT_OK != Secure_MailBox_AESEncode(&SecureBootMbxRetStruct,VA2PA(u32Addr),u32Len,u32PAKeyAddr,E_DRVAESDMA_CIPHER_ECB))
    {
         UBOOT_ERROR("Secure_MailBox_AESEncode failed\n");
         return -1;
    }

    flush_cache(u32Addr,u32Len);
    UBOOT_TRACE("OK\n");
    return 0;
}

MS_U32 Secure_R2_AES128Decode(U32 u32Addr, U32 u32Len,  U8 *bKey)

{
    UBOOT_TRACE("IN\n");

    //check u32InLen align 16
    if(0 != u32Len%16)
    {
         UBOOT_ERROR("u32InLen should align 16\n");
         return -1;
    }

    flush_cache(u32Addr,u32Len);
    U32 u32PAKeyAddr = 0;
    //if bKey == NULL ,we use EFuse key
    if(bKey)
    {
        flush_cache((U32)bKey,AES_KEY_LEN);
        u32PAKeyAddr = VA2PA((U32)bKey);
    }
    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
    if(E_SECUREBOOT_OK != Secure_MailBox_AESDecode(&SecureBootMbxRetStruct,VA2PA(u32Addr),u32Len,u32PAKeyAddr,E_DRVAESDMA_CIPHER_ECB))
    {
         UBOOT_ERROR("Secure_MailBox_AESDecode failed\n");
         return -1;
    }

    flush_cache(u32Addr,u32Len);
    UBOOT_TRACE("OK\n");
    return 0;
}

MS_U32 Secure_R2_SHA256(U32 u32InBuf, U32 u32OutBuf, U32 u32Len)
{
    int ret = 0;
    unsigned int *pTempInBuf=NULL;
    unsigned int *pInBuf=NULL;
    unsigned int *pTempOutBuf=NULL;
    unsigned int *pOutBuf=NULL;
    SECUREBOOT_Result result = 0;
    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("u32InBuf=0x%x,u32OutBuf=0x%x,u32Len=0x%x\n",(unsigned int)u32InBuf,(unsigned int)u32OutBuf,(unsigned int)u32Len);

    //The input buffer of AESDMA must alignment 16 bytes. So we check the input buffer address first.
    //If the input buffer address doesn't alignment to 16 bytes. We allocate a local memory automatically.
    if((u32InBuf%AES_BUF_ALIGNMENT_SIZE)!=0)
    {
       UBOOT_DEBUG("input buffer doesn't alignment 16bytes\n");
       //The size of input buffer should include the size of scattergather table. This table is used for driver.
       // Now, driver creates a scattergather table after input buffer.
       // So, the input buffer should include the sacattergather table.
       #define INPUT_BUF_LENGTH (u32Len+AES_BUF_ALIGNMENT_SIZE+SACTTERGATHER_TABLE_SIZE)
       pTempInBuf=malloc(INPUT_BUF_LENGTH);
       if(pTempInBuf==NULL)
       {
            UBOOT_ERROR("malloc for tbuf fail\n");
            return -1;
       }
       memset(pTempInBuf,0,INPUT_BUF_LENGTH);
       pInBuf=(unsigned int *)((unsigned int)pTempInBuf+(AES_BUF_ALIGNMENT_SIZE-((unsigned int)pTempInBuf%AES_BUF_ALIGNMENT_SIZE)));
       memcpy((void *)pInBuf,(void *)u32InBuf,u32Len);
       #undef INPUT_BUF_LENGTH
    }
    else
    {
        pInBuf=(unsigned int *)u32InBuf;
    }

    memset((void*)u32OutBuf,0,32);
    //The output buffer of AESDMA must alignment 16 bytes. So we check the output buffer address first.
    //If the output buffer address doesn't alignment to 16 bytes. We allocate a local memory automatically.
    if((u32OutBuf%AES_BUF_ALIGNMENT_SIZE)!=0)
    {
       UBOOT_DEBUG("output buffer doesn't alignment 16bytes\n");
       #define OUTPUT_BUF_LENGTH (SHA256_DIGEST_SIZE+AES_BUF_ALIGNMENT_SIZE)
       pTempOutBuf=malloc(OUTPUT_BUF_LENGTH);
       if(pTempOutBuf==NULL)
       {
            if(pTempInBuf!=NULL)
            {
                free(pTempInBuf);
            }
            UBOOT_ERROR("malloc for tbuf fail\n");
            return -1;
       }
       memset(pTempOutBuf,0,OUTPUT_BUF_LENGTH);
       pOutBuf=(unsigned int *)((unsigned int)pTempOutBuf+(AES_BUF_ALIGNMENT_SIZE-((unsigned int)pTempOutBuf%AES_BUF_ALIGNMENT_SIZE)));
       #undef OUTPUT_BUF_LENGTH
    }
    else
    {
        pOutBuf=(unsigned int *)u32OutBuf;
    }


    flush_cache(pInBuf,u32Len);
    flush_cache(pOutBuf,SHA256_DIGEST_SIZE);
    Chip_Flush_Memory();

    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
    result = Secure_MailBox_SHA(&SecureBootMbxRetStruct,VA2PA(pInBuf),u32Len,VA2PA(pOutBuf),E_DRVAESDMA_SHA256);
    flush_cache(pOutBuf,32);
    if(result != E_SECUREBOOT_OK)
    {
        if(pTempInBuf!=NULL)
        {
            free(pTempInBuf);
        }
        if(pTempOutBuf!=NULL)
        {

            free(pTempOutBuf);
        }
        UBOOT_ERROR("Secure_MailBox_SHA failed\n");
        return -1;
    }
    else
    {
        if(pTempInBuf!=NULL)
        {
            free(pTempInBuf);
        }
        if(pTempOutBuf!=NULL)
        {
            UBOOT_DEBUG("copy data from pOutBuf to u32OutBuf\n");
            memcpy((void *)u32OutBuf,(void *)pOutBuf,SHA256_DIGEST_SIZE);
            free(pTempOutBuf);
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;
}
MS_U32 Secure_R2_RSA2048Decrypt(U8 *Signature, U8 *PublicKey_N, U8 *PublicKey_E, U8 *Sim_SignOut)
{
    UBOOT_TRACE("IN\n");

    flush_cache((U32)Signature,256);
    flush_cache((U32)PublicKey_N,256);
    flush_cache((U32)PublicKey_E,256);
    flush_cache((U32)Sim_SignOut,256);
    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;

    if(E_SECUREBOOT_OK != Secure_MailBox_RSADecrypt(&SecureBootMbxRetStruct,VA2PA((U32)Signature),VA2PA((U32)PublicKey_N),VA2PA((U32)PublicKey_E),VA2PA((U32)Sim_SignOut),E_DRVAESDMA_RSA2048_PUBLIC))
    {
        UBOOT_ERROR("Secure_MailBox_RSADecrypt failed\n");
        return -1;
    }
    flush_cache((U32)Sim_SignOut,256);
    UBOOT_TRACE("OK\n");
    return 0;
}
#endif
#endif
#undef API_SECUREBOOT_C

