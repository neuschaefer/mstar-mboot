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
// Copyright (c) 2011-2013 MStar Semiconductor, Inc.
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
/// file    drvTSO.h
/// @brief  TS I/O Driver Interface
/// @author MStar Semiconductor,Inc.
/// @attention
/// All TSO DDI are not allowed to use in any interrupt context other than TSO ISR and Callback
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_TSO_H_
#define _DRV_TSO_H_



#ifdef __cplusplus
extern "C"
{
#endif


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

/// TSP byte address alignment unit
#define DRVTSO_ALIGN_UNIT           16

/// TSP byte address alignment macro
#define DRVTSO_ALIGN(_x)            ALIGN_16((MS_U32)_x)

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Transport stream null PID
#define DRVTSO_PID_NULL             0x1FFF

#define MSIF_TSO_LIB_CODE           {'T','S','O'}                                               // Lib code
#define MSIF_TSO_LIBVER             {'0','1'}                                                       // LIB version
#define MSIF_TSO_BUILDNUM           {'0','2'}                                                       // Build Number
#define MSIF_TSO_CHANGELIST         {'0','0','5','6','3','2','4','9'}                               // P4 ChangeList Number

#define TSO_DRV_VERSION             /* Character String for DRV/API version             */  \
    MSIF_TAG,                       /* 'MSIF'                                           */  \
    MSIF_CLASS,                     /* '00'                                             */  \
    MSIF_CUS,                       /* 0x0000                                           */  \
    MSIF_MOD,                       /* 0x0000                                           */  \
    MSIF_CHIP,                                                                              \
    MSIF_CPU,                                                                               \
    MSIF_TSO_LIB_CODE,              /* IP__                                             */  \
    MSIF_TSO_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_TSO_BUILDNUM,              /* 00 ~ 99                                          */  \
    MSIF_TSO_CHANGELIST,            /* CL#                                              */  \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
/// TSO DDI return value

/// @name TSO_Result
/// @ref TSO_Result
/// return value
/// @{
typedef enum
{
    DRVTSO_FAIL                      = 0,
    DRVTSO_OK					     = 1,
    DRVTSO_INVALID_PARAM 			 = 2,
    DRVTSO_FUNC_ERROR                = 3,
}TSO_Result;
/// @}

typedef enum //_DrvTSO_DbgLevel
{
    E_DRVTSO_DBG_Release = 0,
    E_DRVTSO_DBG_ERR, // display error msg
    E_DRVTSO_DBG_INFO, 
} DrvTSO_DbgLevel;

typedef enum
{
    E_DRVTSO_CAP_FILTER_NUM = 0,                 // Get filter number
} DrvTSO_Cap;

typedef enum
{
    /// Command Queue is Idle
    E_DRVTSO_STATE_IDLE        = 0x00,
    /// Command Queue is Busy
    E_DRVTSO_STATE_BUSY        = 0x01,    

	E_DRVTSO_STATE_UNKNOWN     = 0xFF,    
} DrvTSO_FileinState;

typedef enum
{    	
	E_DRVTSO_STATUS_UNKNOWN	   		= 0,	
    E_DRVTSO_STATUS_FILEINDONE    	= 0x01,    //bit 0
    E_DRVTSO_STATUS_PKTERR        	= 0x02,    //bit 1
} DrvTSO_Status;

typedef enum
{    
    E_DRVTSO_CTRL_MODE_TS0           = 0x0,
    E_DRVTSO_CTRL_MODE_TS1           = 0x1,
    E_DRVTSO_CTRL_MODE_TS2           = 0x2,
    E_DRVTSO_CTRL_MODE_TSCB          = 0x6,
    E_DRVTSO_CTRL_MODE_DEMOD         = 0x7,
    E_DRVTSO_CTRL_MODE_MEM           = 0x8,
} DrvTSO_CtrlMode;

/// TSP file in Packet mode
typedef enum //_DrvTSP_PacketMode
{
    E_DRVTSO_PKTMODE_188              = 0x00000000,
    E_DRVTSO_PKTMODE_192              = 0x00000001,
    E_DRVTSO_PKTMODE_204              = 0x00000002,
} DrvTSO_PacketMode;


TSO_Result MDrv_TSO_Init(void);
TSO_Result MDrv_TSO_Exit(void);
TSO_Result MDrv_TSO_Get_HWIntStatus(MS_U32* pu16status);
TSO_Result MDrv_TSO_SetDbgLevel(DrvTSO_DbgLevel DbgLevel);
TSO_Result MDrv_TSO_SetOperateMode(DrvTSO_CtrlMode TSOCtrlMode, MS_BOOL bClkInv, MS_BOOL bParallel);
TSO_Result MDrv_TSO_Filein_Rate(MS_U16 u16timer);

// PIDFlt API
TSO_Result MDrv_TSO_PidFlt_Alloc(MS_U8 *pu8PidFltId);
TSO_Result MDrv_TSO_PidFlt_Free(MS_U8 u8PidFltId);
TSO_Result MDrv_TSO_PidFlt_SetPid(MS_U8 u8PidFltId, MS_U16 u16Pid);

TSO_Result MDrv_TSO_Filein_CmdQ_Reset(void);
TSO_Result MDrv_TSO_Filein_CmdQFifo_Status(MS_U8 *pu8FifoLevel);
TSO_Result MDrv_TSO_Filein_CmdQ_GetSlot(MS_U32 *pu32EmptySlot);

TSO_Result MDrv_TSO_SetPlaybackTimeStamp(MS_U32 u32timestamp);
TSO_Result MDrv_TSO_GetPlaybackTimeStamp(MS_U32 *pu32timestamp);
TSO_Result MDrv_TSO_GetFileInTimeStamp(MS_U32* pu32Timestamp);
TSO_Result MDrv_TSO_File_GetReadAddr(MS_PHYADDR *pu32ReadAddr);

TSO_Result MDrv_TSO_Filein_SetAddr(MS_PHYADDR u32StreamAddr);
TSO_Result MDrv_TSO_Filein_SetSize(MS_U32 u32StreamSize);
TSO_Result MDrv_TSO_SetPacketMode(DrvTSO_PacketMode ePktMode);
TSO_Result MDrv_TSO_SetPacketSize(MS_BOOL bFileinMode, MS_U16 u16InPktSize, MS_U16 u16OutPktSize);
TSO_Result MDrv_TSO_Filein_192Mode_En(MS_BOOL bEnable);
TSO_Result MDrv_TSO_Filein_192BlockScheme_En(MS_BOOL bEnable);

TSO_Result MDrv_TSO_TEI_SkipPkt(MS_BOOL bEnable);
TSO_Result MDrv_TSO_Clr_Pidflt_ByteCnt(void);
TSO_Result MDrv_TSO_GetCap(DrvTSO_Cap eCap, void* pOutput);

TSO_Result MDrv_TSO_Filein_GetState(DrvTSO_FileinState *peFileinState);
TSO_Result MDrv_TSO_Filein_ChkStatus(DrvTSO_Status* pStatus);
TSO_Result MDrv_TSO_Filein_ClearHWInt(MS_U16 u16int);

TSO_Result MDrv_TSO_Filein_Start(void);
TSO_Result MDrv_TSO_Filein_Abort(void);

TSO_Result MDrv_TSO_ResetAll(void);

#ifdef __cplusplus
} // closing brace for extern "C"
#endif

#endif // _DRV_TSO_H_


