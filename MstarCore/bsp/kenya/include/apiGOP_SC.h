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
/// @file   apiGOP_SC.h
/// @brief  MStar Graphics Output Path API
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _API_GOP_SC_H_
#define _API_GOP_SC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define MSIF_GOP_SC_LIBVER              {'0','0'}            //LIB version
#define MSIF_GOP_SC_BUILDNUM            {'1','1'}            //Build Number
#define MSIF_GOP_SC_CHANGELIST          {'0','0','3','9','1','8','8','7'} //P4 ChangeList Number

typedef enum
{
    EN_GOP_ARGB =0,
    EN_SC_RGB
}EN_GOP_SC_MUX_SEL;

typedef enum
{
    EN_GOP_SC_NTSC =0,
    EN_GOP_SC_PAL,
    EN_GOP_SC_PAL_M,
    EN_GOP_SC_TVSYS_NUM
} EN_GOP_SC_TVSYS;

typedef enum
{
    EN_GOP_SC_DST_FB=0,
    EN_GOP_SC_DST_FBL=1,
    EN_GOP_SC_DST_NUM,

}MAPI_GOP_SC_Dst;

typedef struct
{
    //op to ve timing
    MS_U16 u16VTotal;   //VttIn for GOP_SC
    MS_U16 u16HTotal;   //HttIn for GOP_SC
    MS_U16 u16Width;    //HdeIn for GOP_SC
    MS_U16 u16Hight;    //VdeIn for GOP_SC

    MS_U16 u16Vde_St;
    MS_U16 u16Hde_St;

}MAPI_GOP_SC_InCfg;

typedef struct
{
    EN_GOP_SC_MUX_SEL  enSrcSel;

    MAPI_GOP_SC_InCfg stInputCfg;
    EN_GOP_SC_TVSYS u8TVSys;
    MAPI_GOP_SC_Dst stDst;

}MAPI_GOP_SC_INFO;

void MApi_GOP_SC_SkipInit(MS_BOOL bEnable);
MS_BOOL MApi_GOP_SC_Init(void);
MS_BOOL MApi_GOP_SC_SetCfg(MAPI_GOP_SC_INFO *pGopSC_Info);
MS_BOOL MApi_GOP_SC_MuxSel(EN_GOP_SC_MUX_SEL u8Sel);
MS_BOOL MApi_GOP_SC_SetFPLL_Enable(MS_BOOL bEnable);

#ifdef __cplusplus
}
#endif

#endif
