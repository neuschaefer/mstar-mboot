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
/// @file   drvSYS_priv.h
/// @brief  System Control Interface
/// @author MStar Semiconductor,Inc.
///
////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef _DRVSYS_PRIV_H_
#define _DRVSYS_PRIV_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
// driver version
#define SYS_VERSION            0x00000001

enum {
    // Do not need to check resource
    MDrv_CMD_SYS_GetChipRev,
    MDrv_CMD_SYS_GetChipID,
    MDrv_CMD_SYS_GetInfo,
    MDrv_CMD_SYS_GetLibVer,
    MDrv_CMD_SYS_GetStatus,
    MDrv_CMD_SYS_GetSoftwareVersion,
    MDrv_CMD_SYS_DisableDebugPort,
    MDrv_CMD_SYS_EnableDebugPort,
    MDrv_CMD_SYS_SetDbgLevel,
    MDrv_CMD_SYS_VIFWriteByteByVDMbox,
    MDrv_CMD_SYS_VIFWriteByteMaskByVDMbox,
    MDrv_CMD_SYS_VIFWriteRegBitByVDMbox,
    MDrv_CMD_SYS_VIFReadByteByVDMbox,
    MDrv_CMD_SYS_VIFRead2ByteByVDMbox,


    // check if resource left
    MDrv_CMD_SYS_WDTEnable,
    MDrv_CMD_SYS_WDTClear,
    MDrv_CMD_SYS_WDTLastStatus,
    MDrv_CMD_SYS_WDTSetTime,
    MDrv_CMD_SYS_ResetChip,
    MDrv_CMD_SYS_ResetCPU,
    MDrv_CMD_SYS_SetAGCPadMux,
    MDrv_CMD_SYS_SetPCMCardDetectMode,
    MDrv_CMD_SYS_SetPadMux,
    MDrv_CMD_SYS_SetTSOutClockPhase,
    MDrv_CMD_SYS_Query,
#ifdef _SYS_DAC_GAIN_CTRL    
    MDrv_CMD_SYS_EnhanceDACGain,
#endif    
    MDrv_CMD_SYS_Init,
    MDrv_CMD_SYS_GlobalInit,       
} eSYSIoctlOpt;

//ioctl function pointer type
typedef MS_U8 (*IOCTL_SYS_GETCHIPREV)(void);
typedef MS_U16 (*IOCTL_SYS_GETCHIPID)(void);
typedef const SYS_Info* (*IOCTL_SYS_GETINFO)(void);
typedef const MSIF_Version* (*IOCTL_SYS_GETLIBVER)(void);
typedef MS_BOOL (*IOCTL_SYS_GETSTATUS)(SYS_Status *);
typedef void (*IOCTL_SYS_GETSOFTWAREVERSION)(MS_SW_VERSION_INFO *);
typedef MS_BOOL (*IOCTL_SYS_DISABLEDEBUGPORT)(void);
typedef MS_BOOL (*IOCTL_SYS_ENABLEDEBUGPORT)(void);
typedef void (*IOCTL_SYS_SETDBGLEVEL)(SYS_DbgLv);
typedef void (*IOCTL_SYS_VIFWRITEBYTEBYVDMBOX)(MS_U32, MS_U8);
typedef void (*IOCTL_SYS_VIFWRITEBYTEMASKBYVDMBOX)(MS_U32, MS_U8, MS_U8);
typedef void (*IOCTL_SYS_VIFWRITEREGBITBYVDMBOX)(MS_U32, MS_U8, MS_U8);
typedef MS_U8 (*IOCTL_SYS_VIFREADBYTEBYVDMBOX)(MS_U32);
typedef MS_U16 (*IOCTL_SYS_VIFREAD2BYTEBYVDMBOX)(MS_U32);
typedef void (*IOCTL_SYS_WDTENABLE)(MS_BOOL);
typedef void (*IOCTL_SYS_WDTCLEAR)(void);
typedef MS_BOOL (*IOCTL_SYS_WDTLASTSTATUS)(void);
typedef void (*IOCTL_SYS_WDTSETTIME)(MS_U32);
typedef void (*IOCTL_SYS_RESETCHIP)(void);
typedef void (*IOCTL_SYS_RESETCPU)(void);
typedef void (*IOCTL_SYS_SETAGCPADMUX)(SYS_AGC_PAD_SET);
typedef MS_BOOL (*IOCTL_SYS_SETPCMCARDDETECTMODE)(SYS_PCM_CD_MODE);
typedef MS_BOOL (*IOCTL_SYS_SETPADMUX)(SYS_PAD_MUX_SET, SYS_PAD_SEL);
typedef MS_BOOL (*IOCTL_SYS_SETTSOUTCLOCKPHASE)(MS_U16);
typedef MS_BOOL (*IOCTL_SYS_QUERY)(E_SYS_QUERY);
#ifdef _SYS_DAC_GAIN_CTRL
typedef void (*IOCTL_SYS_ENHANCEDACGAIN)(MS_U8, MS_BOOL);
#endif
typedef MS_BOOL (*IOCTL_SYS_INIT)(void);
typedef void (*IOCTL_SYS_GLOBALINIT)(void);

// INSTANCE Private(ioctl function pointer)
typedef struct _SYS_INSTANT_PRIVATE
{
    IOCTL_SYS_GETCHIPREV                    fpSYS_GetChipRev;
    IOCTL_SYS_GETCHIPID                     fpSYS_GetChipID;
    IOCTL_SYS_GETINFO                       fpSYS_GetInfo;
    IOCTL_SYS_GETLIBVER                     fpSYS_GetLibVer;
    IOCTL_SYS_GETSTATUS                     fpSYS_GetStatus;
    IOCTL_SYS_GETSOFTWAREVERSION            fpSYS_GetSoftwareVersion;
    IOCTL_SYS_DISABLEDEBUGPORT              fpSYS_DisableDebugPort;
    IOCTL_SYS_ENABLEDEBUGPORT               fpSYS_EnableDebugPort;
    IOCTL_SYS_SETDBGLEVEL                   fpSYS_SetDbgLevel;
    IOCTL_SYS_VIFWRITEBYTEBYVDMBOX          fpSYS_VIFWriteByteByVDMbox;
    IOCTL_SYS_VIFWRITEBYTEMASKBYVDMBOX      fpSYS_VIFWriteByteMaskByVDMbox;
    IOCTL_SYS_VIFWRITEREGBITBYVDMBOX        fpSYS_VIFWriteRegBitByVDMbox;
    IOCTL_SYS_VIFREADBYTEBYVDMBOX           fpSYS_VIFReadByteByVDMbox;
    IOCTL_SYS_VIFREAD2BYTEBYVDMBOX          fpSYS_VIFRead2ByteByVDMbox;
    IOCTL_SYS_WDTENABLE                     fpSYS_WDTEnable;
    IOCTL_SYS_WDTCLEAR                      fpSYS_WDTClear;
    IOCTL_SYS_WDTLASTSTATUS                 fpSYS_WDTLastStatus;
    IOCTL_SYS_WDTSETTIME                    fpSYS_WDTSetTime;
    IOCTL_SYS_RESETCHIP                     fpSYS_ResetChip;
    IOCTL_SYS_RESETCPU                      fpSYS_ResetCPU;
    IOCTL_SYS_SETAGCPADMUX                  fpSYS_SetAGCPadMux;
    IOCTL_SYS_SETPCMCARDDETECTMODE          fpSYS_SetPCMCardDetectMode;
    IOCTL_SYS_SETPADMUX                     fpSYS_SetPadMux;
    IOCTL_SYS_SETTSOUTCLOCKPHASE            fpSYS_SetTSOutClockPhase;
    IOCTL_SYS_QUERY                         fpSYS_Query;
#ifdef _SYS_DAC_GAIN_CTRL    
    IOCTL_SYS_ENHANCEDACGAIN                fpSYS_EnhanceDACGain;
#endif
    IOCTL_SYS_INIT                          fpSYS_Init;
    IOCTL_SYS_GLOBALINIT                    fpSYS_GlobalInit;
}SYS_INSTANT_PRIVATE;

//////////////////////////////////////
// function parameter structure //////
//////////////////////////////////////
// for cmd MDrv_SYS_GetStatus
typedef struct _SYS_GETSTATUS_PARAM
{
    SYS_Status *pStatus;
}SYS_GETSTATUS_PARAM, *PSYS_GETSTATUS_PARAM;

// for cmd MDrv_SYS_GetSoftwareVersion
typedef struct _SYS_GETSOFTWAREVERSION_PARAM
{
    MS_SW_VERSION_INFO *pSoftwareVersionInfo;
}SYS_GETSOFTWAREVERSION_PARAM, *PSYS_GETSOFTWAREVERSION_PARAM;

// for cmd MDrv_SYS_SetDbgLevel
typedef struct _SYS_SETDBGLEVEL_PARAM
{
    SYS_DbgLv eLevel;
}SYS_SETDBGLEVEL_PARAM, *PSYS_SETDBGLEVEL_PARAM;

// for cmd MDrv_SYS_VIFWriteByteByVDMbox
typedef struct _SYS_VIFWRITEBYTEBYVDMBOX_PARAM
{
    MS_U32 u32Reg;
    MS_U8 u8Val;
}SYS_VIFWRITEBYTEBYVDMBOX_PARAM, *PSYS_VIFWRITEBYTEBYVDMBOX_PARAM;

// for cmd MDrv_SYS_VIFWriteByteMaskByVDMbox
typedef struct _SYS_VIFWRITEBYTEMASKBYVDMBOX_PARAM
{
    MS_U32 u32Reg;
    MS_U8 u8Val;
    MS_U8 u8Mask;
}SYS_VIFWRITEBYTEMASKBYVDMBOX_PARAM, *PSYS_VIFWRITEBYTEMASKBYVDMBOX_PARAM;

// for cmd MDrv_SYS_VIFWriteRegBitByVDMbox
typedef struct _SYS_VIFWRITEREGBITBYVDMBOX_PARAM
{
    MS_U32 u32Reg;
    MS_U8 bEnable;
    MS_U8 u8Mask;
}SYS_VIFWRITEREGBITBYVDMBOX_PARAM, *PSYS_VIFWRITEREGBITBYVDMBOX_PARAM;

// for cmd MDrv_SYS_VIFReadByteByVDMbox
typedef struct _SYS_VIFREADBYTEBYVDMBOX_PARAM
{
    MS_U32 u32Reg;
}SYS_VIFREADBYTEBYVDMBOX_PARAM, *PSYS_VIFREADBYTEBYVDMBOX_PARAM;

// for cmd MDrv_SYS_VIFRead2ByteByVDMbox
typedef struct _SYS_VIFREAD2BYTEBYVDMBOX_PARAM
{
    MS_U32 u32Reg;
}SYS_VIFREAD2BYTEBYVDMBOX_PARAM, *PSYS_VIFREAD2BYTEBYVDMBOX_PARAM;

// for cmd MDrv_SYS_WDTEnable
typedef struct _SYS_WDTENABLE_PARAM
{
    MS_BOOL bEnable;
}SYS_WDTENABLE_PARAM, *PSYS_WDTENABLE_PARAM;

// for cmd MDrv_SYS_WDTSetTime
typedef struct _SYS_WDTSETTIME_PARAM
{
    MS_U32 u32Ms;
}SYS_WDTSETTIME_PARAM, *PSYS_WDTSETTIME_PARAM;

// for cmd MDrv_SYS_SetAGCPadMux
typedef struct _SYS_SETAGCPADMUX_PARAM
{
    SYS_AGC_PAD_SET eAgcPadMux;
}SYS_SETAGCPADMUX_PARAM, *PSYS_SETAGCPADMUX_PARAM;

// for cmd MDrv_SYS_SetPCMCardDetectMode
typedef struct _SYS_SETPCMCARDDETECT_PARAM
{
    SYS_PCM_CD_MODE ePCMCDMode;
}SYS_SETPCMCARDDETECT_PARAM, *PSYS_SETPCMCARDDETECT_PARAM;

// for cmd MDrv_SYS_SetPadMux
typedef struct _SYS_SETPADMUX_PARAM
{
    SYS_PAD_MUX_SET ePadMuxType;
    SYS_PAD_SEL ePadSel;
}SYS_SETPADMUX_PARAM, *PSYS_SETPADMUX_PARAM;

// for cmd MDrv_SYS_SetTSOutClockPhase
typedef struct _SYS_SETTSOUTCLOCKPHASE_PARAM
{
    MS_U16 u16Val;
}SYS_SETTSOUTCLOCKPHASE_PARAM, *PSYS_SETTSOUTCLOCKPHASE_PARAM;

// for cmd MDrv_SYS_Query
typedef struct _SYS_QUERY_PARAM
{
    E_SYS_QUERY id;
}SYS_QUERY_PARAM, *PSYS_QUERY_PARAM;

#ifdef _SYS_DAC_GAIN_CTRL
// for cmd MDrv_SYS_EnhanceDACGain
typedef struct _SYS_ENHANCEDACGAIN_PARAM
{
    MS_U8 u8DAC_ID;
    MS_BOOL bEnable;
}SYS_ENHANCEDACGAIN_PARAM, *PSYS_ENHANCEDACGAIN_PARAM;
#endif

//////////////////////////////////////
// function for utopia2.0 ////////////
//////////////////////////////////////
void SYSRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 SYSOpen(void** pInstance, void* pAttribute);
MS_U32 SYSClose(void* pInstance);
MS_U32 SYSIoctl(void* pInstance, MS_U32 u32Cmd, void *pArgs);

// Resource_Private
typedef struct _SYS_RESOURCE_PRIVATE
{
    MS_U32 Dummy;
}SYS_RESOURCE_PRIVATE;

#ifdef __cplusplus
}
#endif

#endif // _DRVSYS_PRIV_H_
