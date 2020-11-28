//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (��MStar Software��) are intellectual property of MStar Semiconductor, Inc. (��MStar��) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar. 
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (��Terms��) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party��s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party��s software. 
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar��s confidential information and you agree to keep MStar��s confidential information in strictest confidence and not disclose to any third party.  
//4. MStar Software is provided on an ��AS IS�� basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.  
//   In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer��s product (��Services��).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an ��AS IS�� basis and the warranty disclaimer set forth in Section 4 above shall apply.  
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.  
//   The arbitration award shall be final and binding to both parties.
//
//���B�Ҧ��n��B����ά�������(�U�١uMStar Software�v)����MStar Semiconductor, Inc. (�U�١uMStar�v)�����z�]���v�ì������k��(�]�A��������ۧ@�v�k�ΰ�ڱ���)�ҫO�@�A���󥼸gMStar�ƫe�ѭ���i���ϥΡB�ק�B���s�B�ǰe�Τ��}�����T��C
//�@���z�i�J�B�s���Ψϥ�MStar Software�A�z�Y�n���z�w��Ū�B�F�ѨæP�N���U�C���ڡ]�U�١u�����ڡv�^�ҩ���ñN��u�����k�W���W�w�G
//
//1.	MStar���O��MStar Software�Ψ�ק磌���l�ͪ�������P�������v�Q�B�Ҧ��v�ΧQ�q�A�z�å��]�����ڦӨ��o����MStar Software�Ψ�ק磌���l�ͪ�������P�������v�Q�B�Ҧ��v�ΧQ�q�C
//2.	�z�F��MStar Software�i��t���ε��X���ݩ�ĤT�H���n��ΫY�P�ĤT�H���n��@�ִ��ѡA�Өϥ�MStar Software�i��ݥt��V�ĤT�H���o���v�A�]���z�P�N�z�N�ۦ�t�d�V�����ĤT�H���o���v�H�X�k�ϥ�MStar Software�C
//3.	MStar Software�Ψ�ק磌���l�ͪ����Q����MStar�����K��T�A�z�P�N�N�H�̾��K�O�sMStar�����K��T�B���N�����S������ĤT�H�C
//4.	MStar Software�Y�u�̲{���v�Ҵ��ѦӵL�����O�CMStar�󦹧_�{��MStar Software���ѥ����O�A�]�A��������i�ӫ~�ơB���I�v�B�ŦX�S�w�ϥΥت��B�L�岫�βŦX�����ڼзǤ���O�C�z�P�N�N���|��MStar�D�i�z�]�ϥ�MStar Software�ҥͤ�����l���B�l�`�B�O�ΩΤ�X�C����󱡪p�U�AMStar��󪽱����B�������B���a���Υ��M���l�`�����t�d���A�]�A��������Q���禬�l���B��Ƥ����l�򥢤Ψt�γQ���g���v�ϥΡC�z�æP�N�A������t���ѭ���ĳ�~�A�Y��MStar���̱z���n�D�Ϋ��ܦӭק�MStar Software�A����4�����W�w���~��A�ΦӤ����v�T�C
//5.	�p�g�n�D�AMStar���ɱN���ѧ޳N�䴩�ΪA�Ȥ��z�A�H�Q�z�����~�i�H�PMStar Software�@�P�ϥ�(�U�١u�A�ȡv)�A�z�F�ѨæP�N�A������t���ѭ���ĳ�~�A�Ҧ��A�ȧ��Y�u�H�{���v���ѡA��4���������Ѿ�O�����W�w�����A�Τ��C
//6.	�����ڤ�������ڤ��o�Q������(�L�ר��q�ܡB�T�Ϩ���h�Ψ䥦)�G(a) �¤������v�Q�H�ϥ�MStar���W�١B�ӼСB�A�ȼг��B�Ÿ��Ψ䥦�ѧO�Ϲ��F(b)�Ҥ�MStar�Ψ����Y���~���Ѥ�����H(�]�A��������z�αz���Ȥ�)����Φ�����U�θ�T���q�ȡF��(c) �¤����󴼼z�]���v�C
//7.	���������̤��إ���k�߬��Ǿڪk(���t��Ĭ�k�h)�C�����󥻱��کҥͩλP�����ڬ�������ĳ�̲����̤��إ������k�θӨ�|������W�h�ѨM�A�������3�W����H�H�^��b�x�W�x�_�i��A����H���̤��إ�������|������W�h��X�A����P�_�����ק����B�����觡������O�C
//***********************************************************************************
//<MStar Software>


///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   apiSecureBoot.h
/// @brief  Secure Boot Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_SECUREBOOT_H_
#define _API_SECUREBOOT_H_

#ifdef API_SECUREBOOT_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include <MsTypes.h>
#include <drvAESDMA.h>
#include <ShareType.h>
#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define SECUREBOOT_MBX_QUEUESIZE        8

#define MBX_CTRL_FIRE            BIT(0)
#define MBX_CTRL_READBACK        BIT(1)
#define MBX_CTRL_INSTANT         BIT(2)
#define MBX_STATE1_OVERFLOW      BIT(13)
#define MBX_STATE1_ERROR         BIT(14)
#define MBX_STATE1_BUSY          BIT(15)

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// emurate SECUREBOOT fucntion return result
typedef enum
{
    /// SECUREBOOT result for failure
    E_SECUREBOOT_FAIL =0,
    /// SECUREBOOT result for OK
    E_SECUREBOOT_OK = 1,

} SECUREBOOT_Result;

#if !defined(CONFIG_MSTAR_CLEANBOOT)
///Define SECUREBOOT Acknoledge Flags
typedef enum
{
    E_SECUREBOOT_ACKFLG_WAIT_GETKEY     = (1<<0),      
    E_SECUREBOOT_ACKFLG_WAIT_AESENCODE  = (1<<1),      
    E_SECUREBOOT_ACKFLG_WAIT_AESDECODE  = (1<<2),      
    E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION    = (1<<3),
    E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY    = (1<<4),   
    E_SECUREBOOT_ACKFLG_GETDID    = (1<<5), 

} SECUREBOOT_AckFlags;

typedef enum
{
	E_CMD_SECUREENG_GETKEY=0x00,
	E_CMD_SECUREENG_AES_ENCODE,
    E_CMD_SECUREENG_AES_DECODE,
    E_CMD_SECUREENG_SETEKEY_WITH_DECRYPTION,    
    E_CMD_SECUREENG_ASSIGN_DECRYPTED_KEY,    
    E_CMD_SECUREENG_GETDID,
}SECUREENG_CPUTo51_CMDIDX;

typedef enum
{
    //(1) Ack from 51 to CPU
    E_SECUREENG_51ToCPU_CMD_ACK_GETKEY     = 0x00,
    E_SECUREENG_51ToCPU_CMD_ACK_AES_ENCODE,
    E_SECUREENG_51ToCPU_CMD_ACK_AES_DECODE,
    E_SECUREENG_51ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION,
    E_SECUREENG_51ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY,    
    E_SECUREENG_51ToCPU_CMD_ACK_GETDID,        
} SECUREENG_51ToCPU_CMDIDX;

typedef struct
{
    MS_U32  u32Pm51ToCpuAddr;
    MS_U32  u32Length;
    MS_U8   u8Status;
} SECUREBOOT_MbxRetStruct;

#else  //#if !defined(CONFIG_MSTAR_CLEANBOOT)
 ///Define SECUREBOOT Acknoledge Flags
 typedef enum
 {
     E_SECUREBOOT_ACKFLG_WAIT_GETKEY     = (1<<0),
     E_SECUREBOOT_ACKFLG_WAIT_AESENCODE  = (1<<1),
     E_SECUREBOOT_ACKFLG_WAIT_AESDECODE  = (1<<2),
     E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION    = (1<<3),
     E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY    = (1<<4),
     E_SECUREBOOT_ACKFLG_GETDID    = (1<<5),
     E_SECUREBOOT_ACKFLG_WAIT_SHA = (1<<6),
     E_SECUREBOOT_ACKFLG_WAIT_RSADECODE = (1<<8),
 } SECUREBOOT_AckFlags;
 //ARM to R2
 typedef enum
{
	E_CMD_SECUREENG_GETKEY=0x00,
	E_CMD_SECUREENG_AES_ENCODE,
    E_CMD_SECUREENG_AES_DECODE,
    E_CMD_SECUREENG_SETEKEY_WITH_DECRYPTION,
    E_CMD_SECUREENG_ASSIGN_DECRYPTED_KEY,
    E_CMD_SECUREENG_GETDID,
    E_CMD_SECUREENG_SHA,
    E_CMD_SECUREENG_RSA_DECODE,
}SECUREENG_CPUToR2_CMDIDX;
//R2 to ARM
typedef enum
{
    //(1) Ack from R2 to CPU
    E_SECUREENG_R2ToCPU_CMD_ACK_GETKEY     = 0x00,
    E_SECUREENG_R2ToCPU_CMD_ACK_AES_ENCODE,
    E_SECUREENG_R2ToCPU_CMD_ACK_AES_DECODE,
    E_SECUREENG_R2ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION,
    E_SECUREENG_R2ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY,
    E_SECUREENG_R2ToCPU_CMD_ACK_GETDID,
    E_SECUREENG_R2ToCPU_CMD_ACK_SHA,
    E_SECUREENG_R2ToCPU_CMD_ACK_RSA_DECODE,
} SECUREENG_R2ToCPU_CMDIDX;

typedef struct
{
    MS_U32  u32PAInAddr;
    MS_U32  u32PAOutAddr;
    MS_U32  u32InLen;
    MS_U32  u32PAAESKeyAddr;
    MS_U32  u32PARSAKeyNAddr;
    MS_U32  u32PARSAKeyEAddr;
    DrvAESDMA_CipherMode eAESMode;
    DrvAESDMA_SHAMode eSHAMode;
    DrvAESDMA_RSAMode eRSAMode;
} SECUREBOOT_INFO;

typedef struct
{
    MS_U32  u32R2ToCpuAddr;
    MS_U32  u32Length;
    MS_U8   u8Status;
} SECUREBOOT_MbxRetStruct;
#endif //#if !defined(CONFIG_MSTAR_CLEANBOOT)

#if 0
/// Callback function which is called in SECUREBOOT send MAILBOX ISR.
typedef void ( *SECUREBOOT_Callback ) (void* pData);
#endif

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
INTERFACE MS_BOOL Secure_MailBox_Init(void);
#if !defined(CONFIG_MSTAR_CLEANBOOT)
INTERFACE SECUREBOOT_Result Secure_MailBox_GetKey(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct,U32 u32OutAddr,U8  u8KeyImageIndex,U16  u16LenInKeyImage);
INTERFACE SECUREBOOT_Result Secure_MailBox_AESEncode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U32 u32Len, U8 u8Mode);
INTERFACE SECUREBOOT_Result Secure_MailBox_AESDecode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U32 u32Len, U8 u8Mode);
INTERFACE SECUREBOOT_Result Secure_MailBox_ASSIGN_DECRYPTED_KEY(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U8  u8KeyImageIndex,U16  u16LenInKeyImage, U8 u8IsNoSwap);
INTERFACE SECUREBOOT_Result Secure_MailBox_SET_KEY_WITH_DECRYPTION(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U16 u16Len, U16 u16KeyOffset,U8 u8Mode);
INTERFACE SECUREBOOT_Result Secure_MailBox_GETDID(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, U32 u32Addr, U16 u16Len);
#else //#if !defined(CONFIG_MSTAR_CLEANBOOT)
MS_U32 Secure_R2_AES128Encode(U32 u32Addr, U32 u32Len,  U8 *bKey);
MS_U32 Secure_R2_AES128Decode(U32 u32Addr, U32 u32Len,  U8 *bKey);
MS_U32 Secure_R2_SHA256(U32 u32InBuf, U32 u32OutBuf, U32 u32Len);
MS_U32 Secure_R2_RSA2048Decrypt(U8 *Signature, U8 *PublicKey_N, U8 *PublicKey_E, U8 *Sim_SignOut);
#endif //#if !defined(CONFIG_MSTAR_CLEANBOOT)

#ifdef __cplusplus
}
#endif

#undef INTERFACE
#endif // _API_SECUREBOOT_H_

