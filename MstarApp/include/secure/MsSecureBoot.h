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

#ifndef __CMD_MS_SECURE_BOOT_H__
#define __CMD_MS_SECURE_BOOT_H__
#include <secure/MsSecureCommon.h>

typedef struct
{
    _SUB_SECURE_INFO customer;
    U8 u8RSABootPublicKey[RSA_PUBLIC_KEY_LEN];   
    U8 u8RSAUpgradePublicKey[RSA_PUBLIC_KEY_LEN];       
    U8 u8RSAImagePublicKey[RSA_PUBLIC_KEY_LEN];      
    U8 u8AESBootKey[AES_KEY_LEN];   
    U8 u8AESUpgradeKey[AES_KEY_LEN];       
    U8 u8MagicID[16];
    U8 crc[4];
}CUSTOMER_KEY_BANK;

//-------------------------------------------------------------------------------------------------
/// Decrypt and authenticate RawData image
/// @param KLName                \b IN: RawData image name
/// @param u32kernelAddr             \b IN: RawData image adderss
/// @return  int                               \b OUT: 0: successful. -1: fail
//-------------------------------------------------------------------------------------------------
int RawData_Authentication(char *KLName,unsigned int u32kernelAddr);

//-------------------------------------------------------------------------------------------------    
/// Authenticate rootfs.ubifs, mslib.ubifs and application.ubifs
/// @return  int                              \b OUT: 0: successful. -1: fail
//-------------------------------------------------------------------------------------------------
int FileSystem_Authentication(void);

//-------------------------------------------------------------------------------------------------    
/// get RSA N Public Key according different KEY_INDEX.     
/// @param  enKey                 \b IN: select the enum key you need.
/// @param  buffer                \b IN: The dram address of RSA Key   
/// @param  len                   \b IN: RSA Key Length
/// @return  int                              \b OUT: 0: successful. -1: fail
//-------------------------------------------------------------------------------------------------
int GetPublicKeyN(KEY_INDEX enKey, U8 *buffer, U32 len);

//-------------------------------------------------------------------------------------------------    
/// get RSA E Public Key according different KEY_INDEX.     
/// @param  enKey                 \b IN: select the enum key you need.
/// @param  buffer                \b IN: The dram address of RSA Key   
/// @param  len                   \b IN: RSA Key Length
/// @return  int                              \b OUT: 0: successful. -1: fail
//-------------------------------------------------------------------------------------------------
int GetPublicKeyE(KEY_INDEX enKey, U8 *buffer, U32 len);

//-------------------------------------------------------------------------------------------------    
/// get AES Key according different KEY_INDEX.     
/// @param  enKey                 \b IN: select the enum key you need.
/// @param  keyBuf                \b IN: The dram address of AES Key   
/// @return  int                              \b OUT: 0: successful. -1: fail
//-------------------------------------------------------------------------------------------------
int GetAESKey(KEY_INDEX enKey,U8 *keyBuf);

int do_SecureBootCmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_verify_sha256(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_sha256(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_rsa(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_Secure_Init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_DoSecureEngUnitTestCase1(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_DoSecureEngUnitTestCase2(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_DoSecureEngUnitTestCase3(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_DoSecureEngUnitTestCase4(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_DoSecureEngUnitTestCase5(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_Authenticate(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_DumpSignature(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_performance_test (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_AN_Authenticate(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
void Secure_HaltCPU(void);

int CopyCustomerKeyBank(U32 u32DramAddr);
int DecryptKernelImage(char *dataBuf, unsigned int len);
int GetPublicKeyN(KEY_INDEX enKey, U8 *buffer, U32 len);
int GetPublicKeyE(KEY_INDEX enKey, U8 *buffer, U32 len);
int GetSignature(char *volume, U8 num, U8 *buffer, U32 len);
int GetImageSize(char *volume, U8 num, U32 *size);
#if defined (CONFIG_Securestorage)
int Chunk_Authentication(char* KLName, unsigned u32kernelAddr);
int do_write_rsa_key(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif


#endif

