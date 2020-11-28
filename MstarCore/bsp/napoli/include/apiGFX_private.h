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

#ifndef _DRVGOP_PRIV_H_
#define _DRVGOP_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvBDMA.h
/// @author MStar Semiconductor Inc.
/// @brief Byte DMA control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "apiGFX_v2.h"
#include "apiGFX.h"
#include "drvGE.h"


typedef struct
{
MS_U32 u32dbglvl;
MS_U32 (*fpGetBMP)(MS_S16, GFX_BitmapInfo*);
MS_U32 (*fpGetFont)(MS_S8, GFX_FontInfo*);
GFX_BlendCoef           _blendcoef;
MS_U8                   _angle;
MS_BOOL                 _bNearest;
MS_BOOL                 _bPatchMode;
MS_BOOL                 _bMirrorH;
MS_BOOL                 _bMirrorV;
MS_BOOL                 _bDstMirrorH;
MS_BOOL                 _bDstMirrorV;
MS_BOOL                 _bItalic;
MS_BOOL                 _line_enable;
MS_U8                   _line_pattern;
MS_U8                   _line_factor;
MS_BOOL                 bDither;               

#ifdef DBGLOG
//debug use only
MS_BOOL _bOutFileLog;
MS_U16  *_pu16OutLogAddr;
MS_U16  _u16LogCount;
#endif
GE_Context *g_pGEContext ;
GE_CHIP_PROPERTY *pGeChipProperty;
MS_U32 u32LockStatus;
MS_BOOL  _bInit;
} GFX_API_LOCAL;

typedef struct 
{
    GFX_Set_Colorkey*           pColorKey;              //////////ColorKey
    GFX_Set_ROP*                pROP;                   //////////ROP
}GFX_Function;

typedef struct _GFX_SetConfig
{            
    MS_BOOL                     bOnePixelMode;          //////////OnePixelMode
    MS_BOOL                     bDither;                //////////Dither
    MS_BOOL                     bVQEnable;              //////////Virual Cmd Queue
    MS_BOOL                     bABLEnable;             //////////Alpha Blending Enable
    GFX_RotateAngle             eRotate;                //////////Rotate
    GFX_Set_Mirror*             pMirror;                //////////Mirror      
    MS_U32                      u32TagID;               //////////TagID
    GFX_Set_Clip_Property*      pClip;                  //////////Clip
}GFX_SetConfig;

typedef struct _GFX_Resource_PRIVATE
{
    //GFX_API_LOCAL Eg_apiGFXLocal;
    MS_U32                      u32InstantID;
}GFX_Resource_PRIVATE;

typedef struct _GFX_INSTANT_PRIVATE
{
    /*Resource*/
    GFX_Resource_PRIVATE*       pResource;

    GFX_BitBltInfo*             pGFXBufferInfo;
    GFX_Function*               pGFXFunction;
    GFX_SetConfig*              pGFXSetConfig;
}GFX_INSTANT_PRIVATE;


void            GFXRegisterToUtopia             (FUtopiaOpen ModuleType);
MS_U32          GFXOpen                         (void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32          GFXClose                        (void* pInstance);
MS_U32          GFXIoctl                        (void* pInstance, MS_U32 u32Cmd, void* pArgs);

/*/////////////////
    GetInfo
*//////////////////
GFX_Result      _MApi_GFX_GetBufferInfo         (void* pInstance, PGFX_BufferInfo srcbufInfo, PGFX_BufferInfo dstbufInfo);
GFX_Result      _MApi_GFX_GetClip               (void* pInstance, GFX_Point* v0, GFX_Point* v1);
GFX_Result      _MApi_GFX_GetGECaps             (void* pInstance, EN_GFX_CAPS eCapType, MS_U32* pRet, MS_U32 ret_size);
GFX_Result      _MApi_GFX_GetInfo               (void* pInstance, GFX_DbgInfo *dbg);

GFX_Result      _MApi_GFX_DrawLine              (void* pInstance, GFX_DrawLineInfo *pline);
GFX_Result      _MApi_GFX_RectFill              (void* pInstance, GFX_RectFillInfo *pfillblock);
GFX_Result      _MApi_GFX_BitBlt                (void* pInstance, GFX_DrawRect *drawbuf,MS_U32 drawflag);
GFX_Result      _MApi_GFX_BitBltEx              (void* pInstance, GFX_DrawRect * drawbuf, MS_U32 drawflag, GFX_ScaleInfo * ScaleInfo);

/*/////////////////
    Function
*//////////////////
GFX_Result      _MApi_GFX_SetAlpha              (void* pInstance, MS_BOOL enable, GFX_BlendCoef coef, GFX_AlphaSrcFrom db_abl, MS_U8 abl_const);
GFX_Result      _MApi_GFX_SetSrcColorKey        (void* pInstance, MS_BOOL enable, GFX_ColorKeyMode opMode, GFX_Buffer_Format fmt, void *ps_color, void *pe_color);
GFX_Result      _MApi_GFX_SetDstColorKey        (void* pInstance, MS_BOOL enable, GFX_ColorKeyMode opMode, GFX_Buffer_Format fmt, void *ps_color, void *pe_color);
GFX_Result      _MApi_GFX_SetROP2               (void* pInstance, MS_BOOL enable, GFX_ROP2_Op eRopMode);
GFX_Result      _MApi_GFX_SetIntensity          (void* pInstance, MS_U32 id, GFX_Buffer_Format fmt, MS_U32 *pColor);
GFX_Result      _MApi_GFX_SetDFBBldOP           (void* pInstance, GFX_DFBBldOP gfxSrcBldOP, GFX_DFBBldOP gfxDstBldOP);
GFX_Result      _MApi_GFX_SetDFBBldConstColor   (void* pInstance, GFX_RgbColor gfxRgbColor);
GFX_Result      _MApi_GFX_SetDFBBldFlags        (void* pInstance, MS_U16 u16DFBBldFlags);

/*/////////////////
    SetConfig
*//////////////////
GFX_Result      _MApi_GFX_EnableAlphaBlending   (void* pInstance, MS_BOOL enable);
GFX_Result      _MApi_GFX_SetClip               (void* pInstance, GFX_Point* v0, GFX_Point* v1);
GFX_Result      _MApi_GFX_SetPaletteOpt         (void* pInstance, GFX_PaletteEntry *pPalArray, MS_U16 u32PalStart, MS_U16 u32PalEnd);
GFX_Result      _MApi_GFX_SetVCmdBuffer         (void* pInstance, MS_PHYADDR u32Addr, GFX_VcmqBufSize enBufSize);

/*////////////////
    BitMap
*////////////////
GFX_Result      _MApi_GFX_DrawBitmap            (void* pInstance, MS_S32 handle, GFX_DrawBmpInfo *pbmpfmt);
GFX_Result      _MApi_GFX_TextOut               (void* pInstance, MS_S32 fhandle, MS_U8* pindex, MS_U32 strwidth, GFX_TextOutInfo *pfmt);
GFX_Result      _MApi_GFX_CharacterOut          (void* pInstance, GFX_CharInfo*  pChar, GFX_TextOutInfo *pfmt);


#ifdef __cplusplus
}
#endif
#endif // _DRVBDMA_PRIV_H_
