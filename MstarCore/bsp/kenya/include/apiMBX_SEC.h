////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#ifndef _API_SECURE_H_
#define _API_SECURE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

#define SECUREBOOT_MBX_QUEUESIZE        8
#define SECUREBOOT_MBX_TIMEOUT          5000

/// emurate SECUREBOOT fucntion return result
typedef enum
{
    /// SECUREBOOT result for failure
    E_SECUREBOOT_FAIL =0,
    /// SECUREBOOT result for OK
    E_SECUREBOOT_OK = 1,

} SECUREBOOT_Result;

///Define SECUREBOOT Acknoledge Flags
typedef enum
{
    E_SECUREBOOT_ACKFLG_WAIT_GETKEY     = (1<<0),
    E_SECUREBOOT_ACKFLG_WAIT_AESENCODE  = (1<<1),
    E_SECUREBOOT_ACKFLG_WAIT_AESDECODE  = (1<<2),
    E_SECUREBOOT_ACKFLG_SETEKEY_WITH_DECRYPTION    = (1<<3),
    E_SECUREBOOT_ACKFLG_ASSIGN_DECRYPTED_KEY    = (1<<4),
    E_SECUREBOOT_ACKFLG_OEM_DECRYPT_ECM    = (1<<5),   
} SECUREBOOT_AckFlags;

/// emurate SECUREBOOT mailbox commands from cpu to mcu51
typedef enum
{
    E_CMD_SECUREENG_GETKEY=0x00,
    E_CMD_SECUREENG_AES_ENCODE,
    E_CMD_SECUREENG_AES_DECODE,
    E_CMD_SECUREENG_SETEKEY_WITH_DECRYPTION,
    E_CMD_SECUREENG_ASSIGN_DECRYPTED_KEY,
    E_CMD_SECUREENG_OEM_DECRYPT_ECM,
}SECUREENG_CPUTo51_CMDIDX;

/// emurate SECUREBOOT mailbox commands ack from mcu51 to cpu
typedef enum
{
    //(1) Ack from 51 to CPU
    E_SECUREENG_51ToCPU_CMD_ACK_GETKEY     = 0x00,
    E_SECUREENG_51ToCPU_CMD_ACK_AES_ENCODE,
    E_SECUREENG_51ToCPU_CMD_ACK_AES_DECODE,
    E_SECUREENG_51ToCPU_CMD_ACK_SETEKEY_WITH_DECRYPTION,
    E_SECUREENG_51ToCPU_CMD_ACK_ASSIGN_DECRYPTED_KEY,
    E_SECUREENG_51ToCPU_CMD_ACK_OEM_DECRYPT_ECM,     
} SECUREENG_51ToCPU_CMDIDX;

typedef struct
{
    MS_U32  u32Pm51ToCpuAddr;
    MS_U32  u32Length;
    MS_U8   u8Status;
} SECUREBOOT_MbxRetStruct;

unsigned char Secure_MailBox_Init(void);
unsigned char Secure_MailBox_DeInit(void);

SECUREBOOT_Result Secure_MailBox_GetKey(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct,MS_U32 u32OutAddr,MS_U8  u8AppIndex,MS_U8  u8KeyImageIndex,MS_U16  u16OffsetInKeyImage,MS_U16  u16LenInKeyImage);
SECUREBOOT_Result Secure_MailBox_AESEncode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, MS_U32 u32Addr, MS_U32 u32Len, MS_U8 u8Mode);
SECUREBOOT_Result Secure_MailBox_AESDecode(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, MS_U32 u32Addr, MS_U32 u32Len, MS_U8 u8Mode);
SECUREBOOT_Result Secure_MailBox_ASSIGN_DECRYPTED_KEY(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, MS_U8  u8AppIndex, MS_U8  u8KeyImageIndex, MS_U16  u16OffsetInKeyImage,MS_U16  u16LenInKeyImage);
SECUREBOOT_Result Secure_MailBox_SET_KEY_WITH_DECRYPTION(SECUREBOOT_MbxRetStruct *pSecureBootMbxRetStruct, MS_U32 u32Addr, MS_U32 u32Len, MS_U8 u8CiphertMode,MS_U8 u8Mode);
SECUREBOOT_Result Secure_MailBox_SET_KEY_WITH_DECRYPT_ECM(SECUREBOOT_MbxRetStruct *SecureBootMbxRetStruct, MS_U32 u32Addr, MS_U32 u32Len, MS_U8 u8CiphertMode, MS_U8 u8Mode);
#ifdef __cplusplus
}
#endif

#endif // _API_SECURE_H_
