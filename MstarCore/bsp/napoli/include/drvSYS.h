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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvSYS.h
/// @brief  System Control Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_SYS_H_
#define _DRV_SYS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "MsDevice.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Version string.
    #define MSIF_SYS_LIB_CODE               {'S','Y','S','_'} //Lib code
    #define MSIF_SYS_LIBVER                 {'0','1'}      //LIB version
    #define MSIF_SYS_BUILDNUM               {'0','9' }    //Build Number
    #define MSIF_SYS_CHANGELIST             {'0','0','6','3','0','6','5','2'} //P4 ChangeList Number

#define SYS_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_SYS_LIB_CODE,                  /* IP__                                             */  \
    MSIF_SYS_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_SYS_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_SYS_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

#define SYS_LIB_NAME_MAX            16      ///< Maximum length of library name
#define SYS_LIB_TIME_MAX            16      ///< Maximum length of time
#define SYS_LIB_DATE_MAX            16      ///< Maximum length of date
#define SYS_BOARD_MODEL_MAX         32      ///< Maximum length of board name
#define SYS_PLATFORM_CHIP_MAX       32      ///< Maximum length of playform name
#define SYS_EFUSE_DID_LENGTH         4      ///< efuse device ID length


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// System information
typedef struct _SYS_Info
{
    struct
    {
        MS_U16  DeviceId;                           ///< Device ID
        MS_U8   Version;                            ///< Version
        MS_U8   Revision;                           ///< Revision
        MS_U32  MIU1Base;                           ///< MIU1Base
        MS_U32  MIU1BusBase;                        ///< MIU1Base
        MS_U32  MIU2Base;                           ///< MIU2Base
        MS_U32  MIU2BusBase;                        ///< MIU3Base
        MS_U32  MIU3Base;                           ///< MIU2Base
        MS_U32  MIU3BusBase;                        ///< MIU3Base
    } Chip;                                         ///< Chip information

    struct
    {
        MS_U8   Time[SYS_LIB_TIME_MAX];             ///< Library Built Time
        MS_U8   Date[SYS_LIB_DATE_MAX];             ///< Library Built Date
    } SWLib;                                        ///< Software Library Information

} SYS_Info;


typedef struct _SYS_Status
{
    MS_BOOL     WDT_Active;                         ///< Watchdog Timer

} SYS_Status;

typedef enum _SYS_DbgLv
{
    E_SYS_DBGLV_NONE           //no debug message
    ,E_SYS_DBGLV_ERR_ONLY      //show error only
    ,E_SYS_DBGLV_REG_DUMP      //show error & reg dump
    ,E_SYS_DBGLV_INFO          //show error & informaiton
    ,E_SYS_DBGLV_ALL           //show error, information & funciton name
}SYS_DbgLv;

typedef enum
{
    E_SYS_QUERY_H264_SUPPORTED = 0x00,
    E_SYS_QUERY_DVBC_SUPPORTED = 0x10,
    E_SYS_QUERY_MM_SUPPORTED = 0x11,
    E_SYS_QUERY_TTXNICAM_SUPPORTED = 0x12,
    E_SYS_QUERY_TCON_SUPPORTED = 0x13,
    E_SYS_QUERY_DTV_SUPPORTED = 0x14,
    E_SYS_QUERY_DTVCC_SUPPORTED = 0x15,
    E_SYS_QUERY_GINGA_NCL_SUPPORTED = 0x16,
    E_SYS_QUERY_GINGA_JAVA_SUPPORTED = 0x17,
    E_SYS_QUERT_HD_SUPPORTED = 0x18,
    E_SYS_QUERY_MHL_SUPPORTED = 0x19,
    E_SYS_QUERY_DVBT_SUPPORTED = 0x1A,
    E_SYS_QUERY_ISDBT_SUPPORTED = 0x1B,
} E_SYS_QUERY;

typedef enum
{
    E_SYS_ATV_AGC_PAD_SET,
    E_SYS_DTV_AGC_PAD_SET,
    E_SYS_DTV_AGC_PAD_SET_ALL_OFF,
}SYS_AGC_PAD_SET;

typedef enum
{
    E_TS0_PAD_SET,
    E_TS1_PAD_SET,
    E_TS2_PAD_SET,
    E_TS3_PAD_SET,
    E_CA_CI_PAD_SET,
    E_SC_PAD_SET,
    E_MSPI_PAD_SET,
    E_PAD_SET_MAX
}SYS_PAD_MUX_SET;

typedef enum
{
    E_PARALLEL_IN,
    E_SERIAL_IN,
    E_PARALLEL_IN_2nd_PORT,
    E_PARALLEL_OUT,
    E_CA_CI_PAD_CA,
    E_CA_CI_PAD_CI,
    E_CA_CI_PAD_NONE,    
    E_TRI_STATE_ON,
    E_TRI_STATE_OFF,
    E_SC_PAD_PCM,    
    E_SC_PAD_TS1,
    E_MSPI_PAD_ON,
    E_MSPI_PAD_GPIO,
    E_PAD_SEL_MAX
}SYS_PAD_SEL;

typedef enum
{
    E_PCM_CD_SINGLE,
    E_PCM_CD_OR,
    E_PCM_CD_MAX
}SYS_PCM_CD_MODE;

typedef enum
{
    E_SYS_DOLBY_VERSION = 0x00,
    E_SYS_DOLBY_CONTROL_BIT = 0x01,
    E_SYS_DOLBY_REVERSE_BIT = 0x02,

} E_SYS_DOLBY_HASH_INFO;

typedef enum
{
    E_SYS_CHIP_TV,
    E_SYS_CHIP_STB,
    E_SYS_CHIP_MAX,
} E_SYS_CHIP_TYPE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL         MDrv_SYS_Init(void);
void            MDrv_SYS_GlobalInit(void);
const SYS_Info* MDrv_SYS_GetInfo(void);
MS_U8           MDrv_SYS_GetChipRev(void);
MS_U16          MDrv_SYS_GetChipID(void);
void            MDrv_SYS_WDTEnable(MS_BOOL bEnable);
void            MDrv_SYS_WDTClear(void);
MS_BOOL         MDrv_SYS_WDTLastStatus(void);
void            MDrv_SYS_WDTSetTime(MS_U32 u32Ms);
void            MDrv_SYS_ResetChip(void);
void            MDrv_SYS_ResetCPU(void);
void            MDrv_SYS_SetDbgLevel(SYS_DbgLv eLevel);
void            MDrv_SYS_FlushMemory(void);
void            MDrv_SYS_ReadMemory(void);
void            MDrv_SYS_VIFWriteByteByVDMbox(MS_U32 u32Reg, MS_U8 u8Val);
void            MDrv_SYS_VIFWriteByteMaskByVDMbox(MS_U32 u32Reg, MS_U8 u8Val, MS_U8 u8Mask);
void            MDrv_SYS_VIFWriteRegBitByVDMbox(MS_U32 u32Reg, MS_U8 bEnable, MS_U8 u8Mask);
MS_U8           MDrv_SYS_VIFReadByteByVDMbox(MS_U32 u32Reg);
MS_U16          MDrv_SYS_VIFRead2ByteByVDMbox(MS_U32 u32Reg);

MS_BOOL         MDrv_SYS_Query(E_SYS_QUERY id);

#ifdef _SYS_DAC_GAIN_CTRL_
void MDrv_SYS_EnhanceDACGain(MS_U8 u8DAC_ID, MS_BOOL bEnable);
#endif

void            MDrv_SYS_GetSoftwareVersion(MS_SW_VERSION_INFO *pSoftwareVersionInfo);
void            MDrv_SYS_SetAGCPadMux(SYS_AGC_PAD_SET eAgcPadMux);
MS_BOOL         MDrv_SYS_SetPadMux(SYS_PAD_MUX_SET ePadMuxType,SYS_PAD_SEL ePadSel);
MS_BOOL         MDrv_SYS_SetPCMCardDetectMode(SYS_PCM_CD_MODE ePCMCDMode);
MS_BOOL         MDrv_SYS_DisableDebugPort(void);
MS_BOOL         MDrv_SYS_EnableDebugPort(void);
MS_BOOL         MDrv_SYS_SetTSOutClockPhase(MS_U16 u16Val);
MS_U32          MDrv_SYS_SetPowerState(EN_POWER_MODE u16PowerState);
MS_U32          MDrv_SYS_QueryDolbyHashInfo(E_SYS_DOLBY_HASH_INFO index);
E_SYS_CHIP_TYPE MDrv_SYS_GetChipType(void);
void MDrv_SYS_GetDolbyKeyCustomer(MS_U8 * u8pkey);
MS_U16          MDrv_SYS_ReadBrickTerminatorStatus(void);
void            MDrv_SYS_WriteBrickTerminatorStatus(MS_U16 u16Status);
MS_BOOL         MDrv_SYS_GetEfuseDid(MS_U16 *u16efuse_did);
MS_BOOL         MDrv_SYS_ReadEfuseHDCPKey(MS_U16 u16ReadAddr, MS_U32 *u32HDCPKey);

#ifdef __cplusplus
}
#endif


#endif // _DRV_SYS_H_

