////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvCA.h
/// @brief  CA Driver Interface
/// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_CA_H__
#define __DRV_CA_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define MSIF_CA_LIB_CODE              {'C','A', '_', '_'}               //Lib code
#define MSIF_CA_LIBVER                {'0','1'}                         //LIB version
#define MSIF_CA_BUILDNUM              {'1','1'}                         //Build Number
#define MSIF_CA_CHANGELIST            {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define CA_DRV_VERSION               /* Character String for DRV/API version             */  \
    MSIF_TAG,                        /* 'MSIF'                                           */  \
    MSIF_CLASS,                      /* '00'                                             */  \
    MSIF_CUS,                        /* 0x0000                                           */  \
    MSIF_MOD,                        /* 0x0000                                           */  \
    MSIF_CHIP,                                                                               \
    MSIF_CPU,                                                                                \
    MSIF_CA_LIB_CODE,                /* IP__                                             */  \
    MSIF_CA_LIBVER,                  /* 0.0 ~ Z.Z                                        */  \
    MSIF_CA_BUILDNUM,                /* 00 ~ 99                                          */  \
    MSIF_CA_CHANGELIST,              /* CL#                                              */  \
    MSIF_OS


typedef enum
{
    E_CA_BOOT_SPI0,     // Boot from SPI0 flash
    E_CA_BOOT_SPI1,     // Boot from SPI1 flash
    E_CA_BOOT_PARALLEL, // Boot from Parallel NOR flash
    E_CA_BOOT_OTP       // Boot from OTP
} CA_BOOT_MODE;

typedef enum
{
    E_CA_DEBUG_PORT_I2C,
    E_CA_DEBUG_PORT_JTAG,
    E_CA_DEBUG_PORT_SCAN,
} CA_DEBUG_PORT;

typedef enum
{
    E_CA_DEBUG_PORT_OPEN,
    E_CA_DEBUG_PORT_PASSWD,
    E_CA_DEBUG_PORT_CLOSE
} CA_DEBUG_PORT_MODE;

typedef enum
{
    E_CA_LOCK_DeviceID, // Lock bank 1 ~ 4
    E_CA_LOCK_BootArea,
    E_CA_LOCK_SecretArea,
    E_CA_LOCK_BANK_0,
    E_CA_LOCK_BANK_1,
    E_CA_LOCK_BANK_2,
    E_CA_LOCK_BANK_3,
    E_CA_LOCK_BANK_4,
    E_CA_LOCK_BANK_5,
    E_CA_LOCK_BANK_6,
    E_CA_LOCK_BANK_7,
    E_CA_LOCK_BANK_8,
    E_CA_LOCK_BANK_9,
    E_CA_LOCK_BANK_A,
    E_CA_LOCK_BANK_B,
} CA_OTP_LOCK;

#define E_CA_DEBUG_PORT_PASSWORD_PROTECTED E_CA_DEBUG_PORT_PASSWD

MS_BOOL MDrv_CA_Init(void);

//-------------------------------------------------------------------------------------------------
// The functions will read from the OTP_CONFIG registers
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_CA_DeviceId(MS_U8 *pu8Did, MS_U32 u32Size);
MS_U32 MDrv_CA_MaxDeviceIdSize(void);

CA_BOOT_MODE MDrv_CA_BootMode(void);
MS_BOOL MDrv_CA_SecureBoot(void);

MS_BOOL MDrv_CA_DebugPortMode(CA_DEBUG_PORT eDebugPort, CA_DEBUG_PORT_MODE *eMode);

MS_BOOL MDrv_CA_Locked(CA_OTP_LOCK eLock);

MS_BOOL MDrv_CA_SecureCWMode(void);

//-------------------------------------------------------------------------------------------------
// The functions will write to OTP
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_CA_OTP_SetDeviceId(const MS_U8 *pu8Did, MS_U32 u32Size);
MS_BOOL MDrv_CA_OTP_GetDeviceId(MS_U8 *pu8Did, MS_U32 u32Size);

MS_BOOL MDrv_CA_OTP_SetBootMode(CA_BOOT_MODE eMode);
MS_BOOL MDrv_CA_OTP_EnableSecureBoot(void);

MS_BOOL MDrv_CA_OTP_SetDebugPortMode(CA_DEBUG_PORT eDebugPort, CA_DEBUG_PORT_MODE eMode);

MS_BOOL MDrv_CA_OTP_SetCAVendor(MS_U32 u32Value);
MS_U32 MDrv_CA_OTP_GetCAVendor(void);

MS_BOOL MDrv_CA_OTP_EnableSecureCWMode(void);

MS_BOOL MDrv_CA_OTP_Lock(CA_OTP_LOCK eLock);

//-------------------------------------------------------------------------------------------------
// The OTP read/write
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_CA_OTP_IsBlank(MS_U32 addr);
MS_U32 MDrv_CA_OTP_Read(MS_U32 addr);
MS_BOOL MDrv_CA_OTP_Write(MS_U32 addr, MS_U32 value);

//-------------------------------------------------------------------------------------------------
// Hardware 16-bits Random number generator
//-------------------------------------------------------------------------------------------------
MS_U32 MDrv_CA_Random(void);

//-------------------------------------------------------------------------------------------------
// HASH1 Version
//-------------------------------------------------------------------------------------------------
MS_U32 MDrv_CA_HASH1_VersionAddrress(void);

#ifdef __cplusplus
}
#endif

#endif
