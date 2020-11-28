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
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    drvMMFilein.h
/// @brief  Multimedia File In (MMFILEIN) Driver Interface
/// @author MStar Semiconductor,Inc.
/// @attention
/// All MMFILEIN DDI are not allowed to use in any interrupt context other than MMFILEIN ISR and Callback
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MMFILEIN_H_
#define _DRV_MMFILEIN_H_

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

/// TSP byte address alignment unit
#define DRVMMFI_ALIGN_UNIT           16

/// TSP byte address alignment macro
#define DRVMMFI_ALIGN(_x)            ALIGN_16((MS_U32)_x)


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Transport stream null PID
#define DRVMMFI_PID_NULL             0x1FFF
#define MSIF_MMFI_LIB_CODE           {'M','M','F','I'}                                               // Lib code
#define MSIF_MMFI_LIBVER             {'0','3'}                                                       // LIB version
#define MSIF_MMFI_BUILDNUM           {'0','0'}                                                       // Build Number
#define MSIF_MMFI_CHANGELIST         {'0','0','5','1','1','4','7','0'}                               // P4 ChangeList Number

#define MMFI_DRV_VERSION             /* Character String for DRV/API version             */  \
    MSIF_TAG,                       /* 'MSIF'                                           */  \
    MSIF_CLASS,                     /* '00'                                             */  \
    MSIF_CUS,                       /* 0x0000                                           */  \
    MSIF_MOD,                       /* 0x0000                                           */  \
    MSIF_CHIP,                                                                              \
    MSIF_CPU,                                                                               \
    MSIF_MMFI_LIB_CODE,              /* IP__                                             */  \
    MSIF_MMFI_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_MMFI_BUILDNUM,              /* 00 ~ 99                                          */  \
    MSIF_MMFI_CHANGELIST,            /* CL#                                              */  \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// MMFILEIN DDI return value

/// @name MMFI_Result
/// @ref MMFI_Result
/// return value
/// @{
typedef enum
{
    DRVMMFI_FAIL                     = 0,
    DRVMMFI_OK                       = 1,
    DRVMMFI_INVALID_PARAM            = 2,
    DRVMMFI_FUNC_ERROR               = 3,
} MMFI_Result;
/// @}

typedef enum
{
    E_DRVMMFI_PTH_AUDIO   = 0x00,
    E_DRVMMFI_PATH_VD3D   = 0x01,

}DrvMMFI_Path;

typedef enum
{
    E_DRVMMFI_MODE_NO_BYPASS_AU     = 0x0000,

    E_DRVMMFI_MODE_PS_AU            = 0x0001,

    E_DRVMMFI_MODE_PS_AUB           = 0x0002,

    E_DRVMMFI_MODE_APID_BYPASS      = 0x0004,

    E_DRVMMFI_MODE_APIDB_BYPASS     = 0x0008,

    E_DRVMMFI_MODE_NO_BYPASS_V3D    = 0x0010,
    E_DRVMMFI_MODE_PS_V3D           = 0x0020,
    E_DRVMMFI_MODE_V3DPID_BYPASS    = 0x0040,

    E_DRVMMFI_MODE_NO_BYPASS_VD     = 0x0080,
    E_DRVMMFI_MODE_VPID_BYPASS      = 0x0100,
    E_DRVMMFI_MODE_NO_BYPASS_TS     = 0x0200,
} DrvMMFI_FileinMode;

typedef enum
{
    /// Command Queue is Idle
    E_DRVMMFI_STATE_IDLE        = 0x00,
    /// Command Queue is Busy
    E_DRVMMFI_STATE_BUSY        = 0x01,

    E_DRVMMFI_STATE_UNKNOWN     = 0xFF,
} DrvMMFI_FileinState;

typedef enum
{
    E_DRVMMFI_STATUS_UNKNOWN            = 0,
    E_DRVMMFI_STATUS_AU_FILEINDONE      = 0x01,    //bit 0
    E_DRVMMFI_STATUS_AU_PKTERR          = 0x02,    //bit 1
    E_DRVMMFI_STATUS_VD_FILEINDONE      = 0x04,    //bit 2
    E_DRVMMFI_STATUS_VD_PKTERR          = 0x08,    //bit 3
} DrvMMFI_Status;


/// MMFI file in Packet mode
typedef enum //_DrvMMFI_PacketMode
{
    E_DRVMMFI_PKTMODE_188              = 0x0000,
    E_DRVMMFI_PKTMODE_192              = 0x0001,
    E_DRVMMFI_PKTMODE_204              = 0x0002,
} DrvMMFI_PacketMode;

/// TSP TS Input Source
typedef enum
{
    E_DRVMMFI_FLTTYPE_NONE = 0,
    E_DRVMMFI_FLTTYPE_AUD  = 1,
    E_DRVMMFI_FLTTYPE_AUDB = 2,
    E_DRVMMFI_FLTTYPE_VD3D = 3,
} DrvMMFI_FltType;

typedef enum //_DrvMMFI_DbgLevel
{
    E_DRVMMFI_DBG_Release = 0,
    E_DRVMMFI_DBG_ERR, // display error msg
    E_DRVMMFI_DBG_INFO,
} DrvMMFI_DbgLevel;

typedef enum
{
    E_DRVMMFI_CAP_FILTER_AU_NUM = 0,                // Get filter number
    E_DRVMMFI_CAP_FILTER_VD_NUM,                    // Get pvr filter number
    E_DRVMMFI_CAP_FILTER_ALL_NUM,

    E_DRVMMFI_CAP_RESOURCE_SIZE,                    // Get the data structure size of private resource (share resource)

    E_DRVMMFI_CAP_NULL,
} DrvMMFI_Cap;


typedef struct _DrvPIDFLT_HEADER
{
    MS_U32      CCounter        : 4;
    MS_U32      Adp_Ctrl        : 2;
    MS_U32      Scramble        : 2;
    MS_U32      PID             : 13;
    MS_U32      TS_Priority     : 1;
    MS_U32      Payload_Start   : 1;
    MS_U32      Err_Flag        : 1;
    MS_U32      reserved        : 8;
}DrvPIDFLT_HEADER;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MMFI_Result MDrv_MMFI_InitLibResource(void* pResMemAddr);
MMFI_Result MDrv_MMFI_Init(void);
MMFI_Result MDrv_MMFI_Exit(void);
MMFI_Result MDrv_MMFI_Get_HWIntStatus(MS_U32* pu32status);
MMFI_Result MDrv_MMFI_SetDbgLevel(DrvMMFI_DbgLevel DbgLevel);
MMFI_Result MDrv_MMFI_AudPath_Enable(MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_File_SetTimer(DrvMMFI_Path epath, MS_U8 u8timer);
MMFI_Result MDrv_MMFI_File_ByteTimer_En(DrvMMFI_Path epath, MS_BOOL bEnable);

// PIDFlt API
MMFI_Result MDrv_MMFI_PidFlt_Alloc(DrvMMFI_FltType eFilterType, MS_U8 *pu8PidFltId);
MMFI_Result MDrv_MMFI_PidFlt_Free(MS_U8 u8PidFltId);
MMFI_Result MDrv_MMFI_PidFlt_Enable(MS_U8 u8PidFltId, MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_PidFlt_SetPid(MS_U8 u8PidFltId, MS_U16 u16Pid);

MMFI_Result MDrv_MMFI_File_CmdQ_Reset(DrvMMFI_Path epath);
MMFI_Result MDrv_MMFI_File_CmdQFifo_Status(DrvMMFI_Path epath, MS_U8 *pu8FifoLevel);
MMFI_Result MDrv_MMFI_File_CmdQ_GetSlot(DrvMMFI_Path epath, MS_U32 *pu32EmptySlot);

MMFI_Result MDrv_MMFI_SetPlaybackTimeStamp(DrvMMFI_Path epath, MS_U32 u32lpcr2);
MMFI_Result MDrv_MMFI_GetPlaybackTimeStamp(DrvMMFI_Path epath, MS_U32 *pu32lpcr2);
MMFI_Result MDrv_MMFI_GetFileInTimeStamp(DrvMMFI_Path epath, MS_U32* pu32TSLen);

MMFI_Result MDrv_MMFI_File_SetAddr(DrvMMFI_Path epath, MS_PHYADDR u32StreamAddr);
MMFI_Result MDrv_MMFI_File_SetSize(DrvMMFI_Path epath, MS_U32 u32StreamSize);
MMFI_Result MDrv_MMFI_File_SetPacketMode(DrvMMFI_Path epath, DrvMMFI_PacketMode PacketMode);
MMFI_Result MDrv_MMFI_File_192Mode_En(DrvMMFI_Path epath, MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_File_192BlockScheme_En(DrvMMFI_Path epath, MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_File_SetPacketMode(DrvMMFI_Path epath, DrvMMFI_PacketMode PacketMode);
MMFI_Result MDrv_MMFI_File_SetTimeStampClk(DrvMMFI_Path ePath, MS_U32 u32ClkSrc);
MMFI_Result MDrv_MMFI_File_GetReadAddr(DrvMMFI_Path epath, MS_PHYADDR* pu32ReadAddr);

MMFI_Result MDrv_MMFI_DupPktSkip(DrvMMFI_Path epath, MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_TEI_SkipPktf(DrvMMFI_Path epath, MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_Clr_Pidflt_ByteCnt(DrvMMFI_Path epath);
MMFI_Result MDrv_MMFI_TSDataEndian_Swap(DrvMMFI_Path epath, MS_BOOL bEnable);
MMFI_Result MDrv_MMFI_TSOrder_Swap(DrvMMFI_Path epath, MS_BOOL bEnable);

MMFI_Result MDrv_MMFI_File_GetState(DrvMMFI_Path epath, DrvMMFI_FileinState *peFileinState);
MMFI_Result MDrv_MMFI_File_ChkStatus(DrvMMFI_Status* pStatus);
MMFI_Result MDrv_MMFI_File_ClearHWInt(MS_U32 u32int);
MMFI_Result MDrv_MMFI_Get_TsHeader(DrvMMFI_Path epath, DrvPIDFLT_HEADER *pheader);

MMFI_Result MDrv_MMFI_File_Start(DrvMMFI_Path epath);
MMFI_Result MDrv_MMFI_File_Abort(DrvMMFI_Path epath);
MMFI_Result MDrv_MMFI_File_ModeEnable(DrvMMFI_FileinMode fileinmode, MS_BOOL bEnable);

MMFI_Result MDrv_MMFI_ResetAll(void);
MMFI_Result MDrv_MMFI_GetCap(DrvMMFI_Cap eCap, void* pOutput);
MMFI_Result MDrv_MMFI_RemoveDupAVPkt(MS_BOOL bEnable);

MMFI_Result MDrv_MMFI_VD3DPath_Enable(MS_BOOL bEnable);

MMFI_Result MDrv_MMFI_Set_MOBF_FileinKey(DrvMMFI_Path epath, MS_U32 u32Key);
MMFI_Result MDrv_MMFI_MOBF_FileIn_Enable(DrvMMFI_Path epath, MS_BOOL benable);
MMFI_Result MDrv_MMFI_MOBF_FileIn_SetLevel(DrvMMFI_Path epath, MS_U8 u8level);


#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif // _DRV_MMFILEIN_H_
