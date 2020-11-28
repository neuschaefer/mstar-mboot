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
///
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _API_GPD_H_
#define _API_GPD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MSIF_GPD_LIB_CODE      {'G','P','D','_'}
#define MSIF_GPD_LIBVER        {'0','1'}
#define MSIF_GPD_BUILDNUM      {'0','3'}
#define MSIF_GPD_CHANGELIST    {'0','0','6','1','4','5','9','5'}

/// Version string.
#define GPD_API_VERSION                /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_GPD_LIB_CODE,                 /* IP__                                             */  \
    MSIF_GPD_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_GPD_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_GPD_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS



#define U8 MS_U8
#define U16 MS_U16
#define U32 MS_U32
#define S8 MS_S8
#define S16 MS_S16
#define S32 MS_S32


#define TRUE 1
#define FALSE 0

#define ARGB8888 0
#define YUV422   1
#define RGB565   2
#define YVYU422  3
#define GRAY     4
#define GRAY_ALPHA 5

#ifndef GPD_SUPPORT_MGIF
#define GPD_SUPPORT_MGIF 1
#endif

#ifndef GPD_NO_SUPPORT_MGIF
#define GPD_NO_SUPPORT_MGIF 0
#endif

#define GPD_VERSION 0x12062516
#define WORDALIGN  0x3
#define GPD_CLOCK_OFFSET (0x50 << 1)

typedef struct
{
    U32    u32PA_ReadBufferAddr;
    U32    u32VA_ReadBufferAddr;
    U32    u32ReadBufferSize;
    U32    u32PA_WriteBufferAddr;
    U32    u32VA_WriteBufferAddr;
    U32    u32WriteBufferSize;
    U32	   u32PA_DepthBufferAddr;
    U32    u32VA_DepthBufferAddr;
    U32	   u32PA_ColorBufferAddr;
    U32	   u32VA_ColorBufferAddr;
    U32    RegBaseAddr;
    U32    ReadBitBaseAddr;
} gpd_addr_info;


typedef struct
{
    char   *filename;
    U32    u32Width;
    U32    u32Height;
    U8     u8BitPP;
    U8     u8Interlace;
    S32    enGPDStatus;    //Error Code
    U8     u8MGIF;
} gpd_pic_info;


typedef struct
{
    U32    hstart;
    U32    vstart;
    U32    width;
    U32    height;

} gpd_roi_info;

typedef struct
{
    U32    u32PA_StartAddr;
    U32    u32PA_EndAddr;

} gpd_access_region;


typedef enum {
    GPD_STATE_MGIF_TERMINATE,
    GPD_STATE_GIF_ERROR,
    GPD_STATE_MGIF_WAIT_BUFFFER,
    GPD_STATE_GIF_SUCCESS
} gpd_state;


typedef enum
{
    E_GPD_USER_CMD_SET_ACCESS_REGION = 0,
    E_GPD_USER_CMD_SET_CACHEABLE,

} gpd_user_cmd;

typedef enum
{
    E_GPD_SCALE_ONE_TO_TWO,
    E_GPD_SCALE_ONE_TO_FOUR,
    E_GPD_SCALE_ONE_TO_EIGHT,
    E_GPD_SCALE_ONE_TO_SIXTEEN,
} gpd_scale_mode;

#if 1

void *MApi_GPD_Init(U32 SrcBuf);
S32 MApi_GPD_InputSource(gpd_pic_info* param, U32 InputBuf, U32 Size);
S32 MApi_GPD_OutputDecode(U32 DecodeBuf, U32 ocolor, U32 Size);
S32 MApi_GPD_OutputDecodeROI(U32 DecodeBuf, U32 ocolor, U32 Size, gpd_roi_info *roi);
S32 MApi_GPD_OutputDecodeMGIF(U32 DecodeBuf, U32 ocolor, U32 Size);
S32 MApi_GPD_GetDuration(void);
void MApi_GPD_SetGIFMode(int mode);


#else

S32 MAdp_GPD_Init(void);
S32 MAdp_GPD_Play(gpd_pic_info* param, U32 ocolor, U8 *srcbuffer, U32 size);
S32 MAdp_GPD_Compare(U32 ocolor_typ);
#endif

void MApi_GPD_ScalingEnable(U32 mode);
void MApi_GPD_ScalingDisable(void);
U32 MApi_GPD_SetControl(gpd_user_cmd cmd_id, U32 param);
U32 MApi_GPD_GetControl(gpd_user_cmd cmd_id, U32 param);
U32 MApi_GPD_GetCRCResult(const MS_U8 *pu8Data, MS_U32 u32Size, MS_U32 u32Width, unsigned int ocolor);

#ifdef __cplusplus
}
#endif


#endif

