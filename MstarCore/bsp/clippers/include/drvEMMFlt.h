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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVEMMFLT_H_
#define _DRVEMMFLT_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvEMMFlt.h
/// @author MStar Semiconductor Inc.
/// @brief to filter EMM packet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////
#define MSIF_EMMFLT_LIB_CODE	{'E','M','M','F'}    //Lib code
#define MSIF_EMMFLT_LIBVER		{'0','1'}            //LIB version
#define MSIF_EMMFLT_BUILDNUM    {'0','1'}            //Build Number
#define MSIF_EMMFLT_CHANGELIST  {'0','0','3','4','8','0','3','3'} //P4 ChangeList Number

#define EMMFLT_DRV_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_EMMFLT_LIB_CODE,                  /* IP__                                             */  \
    MSIF_EMMFLT_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_EMMFLT_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_EMMFLT_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

typedef MS_U32                         EMMFLT_RESULT;

typedef void (*EMMFLT_Notify)(MS_U32 conn, MS_U32 reason, void *pData);


#define DRV_EMMFLT_OK                   TRUE
#define DRV_EMMFLT_FAIL                 FALSE
#define DRV_EMMFLT_INVALID_REQUEST      3



#define EMM_SRC_FILEIN      0
#define EMM_SRC_LIVEIN      1


typedef enum _EMM_EVENT_
{
    EMM_EVENT_ARRIVE = 0,
    EMM_EVENT_OVERFLOW,
} EMM_EVENT_e;



typedef enum _EMM_SrcType_
{
    EMM_SRC_TS0 = 0,
    EMM_SRC_TS1,
    EMM_SRC_TS2,
    EMM_SRC_TS3,
    EMM_SRC_INTERDEMOD_0,
    EMM_SRC_INTERDEMOD_1,
    EMM_SRC_MEMORY,
}EMM_SRCTYPE_e;

typedef enum
{
    EMM_TIDMODE_INGORE = 0x0,
    EMM_TIDMODE_ACCEPT_ALL,
    EMM_TIDMODE_ACCEPT_ADDRESS,
    EMM_TIDMODE_RESERVED,
} EMMDRV_TIDMODE_e;

typedef enum _EMM_OutType_
{
    EMM_OUT_NORMAL = 0,
    EMM_OUT_184BYTES,
    EMM_OUT_PACKETNUM,
}EMM_OUTTYPE_e;

typedef struct _EMMFLT_Require_
{
    MS_U32 u32DstBufSize;
    MS_U32 u32AlignBytes;
    MS_U8  u8EMMNumber;
} EMMFLT_Require_t;


typedef struct _EMM_FILTER_DEF
{
    MS_U8   filter_type;         //this can be set to LABEL_00, 01, 02, 03
    MS_U8   filter_address[4];   //
    MS_U8   filter_address_mask[4];

} EMM_FILTER_DEF_t;


////////////////////////////////////////////////////////////////////////////////
// Extern Function
////////////////////////////////////////////////////////////////////////////////

EMMFLT_RESULT MDrv_EMMFLT_Init(EMMFLT_Require_t *pRequire);
EMMFLT_RESULT MDrv_EMMFLT_GetHwBufCnt(MS_U32 *pHwBufCnt);
EMMFLT_RESULT MDrv_EMMFLT_SetDbgLevel(MS_U32 u32Level);
EMMFLT_RESULT MDrv_EMMFLT_SetNotify(EMMFLT_Notify Notify);
EMMFLT_RESULT MDrv_EMMFLT_SetEmmPID(MS_U32 connection,MS_U16 u16EmmPID);
EMMFLT_RESULT MDrv_EMMFLT_SetTidMode(MS_U32 connection, MS_U8 u8TidValue, EMMDRV_TIDMODE_e eTIDMODE);
EMMFLT_RESULT MDrv_EMMFLT_EnableEmmTID(MS_U32 connection, MS_BOOL bEnable);
EMMFLT_RESULT MDrv_EMMFLT_SetFilterCfg(MS_U32 connection, MS_U8 FilerIndex, EMM_FILTER_DEF_t *pFilter);
EMMFLT_RESULT MDrv_EMMFLT_Fire(MS_U32 connection);

EMMFLT_RESULT MDrv_EMMFLT_SetDstBufInfo(MS_U32 x_connection, MS_U32 u32BufAddr, MS_U32 u32BufSize);
EMMFLT_RESULT MDrv_EMMFLT_EmmProcessingFinished(MS_U8 *emm_buf/* RPC SIZECONST(256) */);
EMMFLT_RESULT MDrv_EMMFLT_Deinit(void);
EMMFLT_RESULT MDrv_EMMFLT_SrcSelect(MS_U32 x_connection, MS_U32 u32SrcFrom, EMM_SRCTYPE_e eSrcType);
EMMFLT_RESULT MDrv_EMMFLT_StopEmm(MS_U32 x_connection);
EMMFLT_RESULT MDrv_EMMFLT_EmmProcessingFinished(MS_U8 *emm_buf/* RPC SIZECONST(256) */);
EMMFLT_RESULT MDrv_EMMFLT_SetOutputType(MS_U32 x_connection, EMM_OUTTYPE_e eOutType);
EMMFLT_RESULT MDrv_EMMFLT_ConnectCheck(MS_U32 connection);

#ifdef __cplusplus
}
#endif
#endif//_DRVEMMFLT_H_

