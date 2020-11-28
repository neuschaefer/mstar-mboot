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

#define U8 MS_U8
#define U16 MS_U16
#define U32 MS_U32
#define S8 MS_S8
#define S16 MS_S16
#define S32 MS_S32


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


typedef enum {
    GPD_STATE_MGIF_TERMINATE,
    GPD_STATE_GIF_ERROR,
    GPD_STATE_MGIF_WAIT_BUFFFER,
    GPD_STATE_GIF_SUCCESS
} gpd_state;



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

#ifdef __cplusplus
}
#endif


#endif

