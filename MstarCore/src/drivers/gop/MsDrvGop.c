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

#include <common.h>
#include <config.h>
#include <MsOS.h>
#if (ENABLE_MSTAR_KAISER==1)
#include <drvXC_IOPort.h>
#include <apiXC.h>
#include <drvTVEncoder.h>
#endif
#include <apiGOP.h>
#include <apiPNL.h>
#include <MsDebug.h>

#include <gop/MsDrvGop.h>
#include <uboot_mmap.h>
#include <ShareType.h>
#include <MsMmap.h>

#include <bootlogo/MsPoolDB.h>

#ifndef UNUSED
#define UNUSED( var )                   ((void)(var))
#endif
U8 u8OsdLayerFbId=0xFF, u8OsdLayerGwinId=0xFF;
U16 u16OsdW = 0,u16OsdH = 0;
U8 g_logoGopIdx = 0;
U8 g_logoMiuIdx = 0;
U8 bDelayLogo = FALSE;
U8 u8OsdLayerFbId_SC=0xFF, u8OsdLayerGwinId_SC=0xFF;
U8 g_logoGopIdx_SC = 1;

MS_BOOL _sc_is_interlace(void)
{
    return 0;
}

MS_U16 _sc_get_h_cap_start(void)
{
    return 0x60;
}
void _Sys_PQ_ReduceBW_ForOSD(MS_U8 PqWin, MS_BOOL bOSD_On)
{
    PqWin=bOSD_On=0;
    UNUSED(PqWin);
    UNUSED(bOSD_On);
}

void MsDrvGOP_SetStretch(GFX_BufferInfo *dst_info, MS_BOOL bHorStretch, MS_BOOL bVerStretch,MS_U16 u16DispX,MS_U16 u16DispY)
{
    U32 u32GWinDispX_Max;
    U32 u32GWinDispY_Max;

    u32GWinDispX_Max = g_IPanel.Width();
    u32GWinDispY_Max = g_IPanel.Height();

    MApi_GOP_GWIN_Set_HSCALE(bHorStretch, dst_info->u32Width, u32GWinDispX_Max);

    MApi_GOP_GWIN_Set_VSCALE(bVerStretch, dst_info->u32Height, u32GWinDispY_Max);

    MApi_GOP_GWIN_Set_STRETCHWIN(g_logoGopIdx, E_GOP_DST_OP0,u16DispX,u16DispY, dst_info->u32Width, dst_info->u32Height);
}


void gop_stretch(U16 graph_pitch, U16 graph_width, U16 graph_height, MS_BOOL bHorStretch, MS_BOOL bVerStretch)
{
    U32 u32GWinDispX_Max;
    U32 u32GWinDispY_Max;


    u32GWinDispX_Max = g_IPanel.Width();
    u32GWinDispY_Max = g_IPanel.Height();

    if (bHorStretch)
        MApi_GOP_GWIN_Set_HSCALE(TRUE, graph_width, u32GWinDispX_Max);
    if (bVerStretch)
        MApi_GOP_GWIN_Set_VSCALE(TRUE, graph_height, u32GWinDispY_Max);

    MApi_GOP_GWIN_Set_STRETCHWIN(g_logoGopIdx, E_GOP_DST_OP0, 0, 0, graph_pitch, graph_height);
}

//GOPSC functions
#if (ENABLE_MSTAR_KAISER==1)

static int _UseOtherGOPShowToVE(void)
{
    U32 u32Addr=0;
    MApi_GOP_GWIN_SetForceWrite(TRUE);
    MApi_GOP_GWIN_SwitchGOP(g_logoGopIdx_SC);

    //Create GOPSC
    VE_DrvStatus DrvStatus;
    MS_VE_Output_Ctrl OutputCtrl;
    GOP_MixerTiming gopMixerTiming;
    //EN_GOP_DST_TYPE GopDest = E_GOP_DST_MIXER2VE;
    EN_GOP_DST_TYPE GopDest = E_GOP_DST_VE;
    MS_BOOL VE_PAL = TRUE;

    MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
    MApi_GOP_GWIN_SetGOPDst(g_logoGopIdx_SC, GopDest);

    MDrv_VE_SetOSD(TRUE);

    //MApi_XC_SetOSD2VEMode(E_VOP_SEL_OSD_BLEND1);
    OutputCtrl.bEnable = TRUE;
    OutputCtrl.OutputType = MS_VE_OUT_TVENCODER;
    MDrv_VE_SetOutputCtrl(&OutputCtrl);
    // disable blackScreen
    MDrv_VE_SetBlackScreen(FALSE);
    //**setconfig
    MDrv_VE_GetStatus(&DrvStatus);
    if(DrvStatus.VideoSystem <= 2)
    {
        VE_PAL = FALSE;
    }
    else
    {
        VE_PAL = TRUE;
    }
    if(GopDest == E_GOP_DST_MIXER2VE)
    {
        MApi_GOP_MIXER_SetOutputTiming((VE_PAL)?GOP_PAL:GOP_NTSC, &gopMixerTiming);
    }
    else
    {
        MApi_GOP_VE_SetOutputTiming((VE_PAL)? GOP_VE_PAL : GOP_VE_NTSC);
    }
    if(VE_PAL == TRUE)
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(g_logoGopIdx_SC, GopDest, 0, 0, 720, 576);
    }
    else
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(g_logoGopIdx_SC, GopDest, 0, 0, 720, 480);
    }
    //**createwin
    u8OsdLayerGwinId_SC = MApi_GOP_GWIN_GetFreeWinID();
    u8OsdLayerFbId_SC = MApi_GOP_GWIN_GetFreeFBID();



    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_DFB_FRAMEBUFFER_ADR mmap fail\n");
    }

    if(u32Addr==0xFFFF)
    {
        UBOOT_ERROR("get GOP mmap fail\n");
        return -1;
    }
    if(VE_PAL == TRUE)
    {
        MApi_GOP_GWIN_CreateFBbyStaticAddr(u8OsdLayerFbId_SC, 0, 0, 720, 576, E_MS_FMT_YUV422, (u32Addr+0xA00000));
    }
    else
    {
        MApi_GOP_GWIN_CreateFBbyStaticAddr(u8OsdLayerFbId_SC, 0, 0, 720, 480, E_MS_FMT_YUV422, (u32Addr+0xA00000));
    }
    MApi_GOP_GWIN_MapFB2Win(u8OsdLayerFbId_SC, u8OsdLayerGwinId_SC);
    MApi_GOP_GWIN_SetBlending(u8OsdLayerGwinId_SC, FALSE, 0xFF);
    //GOP_GwinInfo pinfo;
    //GOP_GwinInfo pinfo;
    //MApi_GOP_GWIN_GetWinInfo(u8OsdLayerGwinId_SC ,&pinfo);
    //pinfo.;
    //pinfo.u16DispHPixelEnd = 720;
    //pinfo.u16DispVPixelEnd = u16Height;
    //MApi_GOP_GWIN_SetWinInfo(u8OsdLayerGwinId_SC ,&pinfo);
    if(GopDest == E_GOP_DST_VE)
    {
        MApi_GOP_GWIN_EnableProgressive(FALSE);
    }
    else
    {
        MApi_GOP_GWIN_EnableProgressive(TRUE); //FIXME
    }
    MApi_GOP_GWIN_OutputColor(GOPOUT_YUV);
    MApi_GOP_GWIN_Enable(u8OsdLayerGwinId_SC, TRUE);
    MApi_GOP_GWIN_SetForceWrite(FALSE);

}
#endif

void MsDrvGFX_Init(void)
{
    GFX_Config tGFXcfg;

    tGFXcfg.bIsCompt = TRUE;
    tGFXcfg.bIsHK = TRUE;
    MApi_GFX_Init(&tGFXcfg);

}
int MsDrvGFX_Blt(GFX_DrawRect *rect,GFX_BufferInfo *src_info, GFX_BufferInfo *dst_info )
{
    GFX_Point gfxPt0 = { rect->dstblk.x, rect->dstblk.y };
    GFX_Point gfxPt1 = { rect->dstblk.x+rect->dstblk.width,rect->dstblk.y+rect->dstblk.height };

    MApi_GFX_SetSrcBufferInfo(src_info, 0);

    MApi_GFX_SetDstBufferInfo(dst_info, 0);

    MApi_GFX_SetClip(&gfxPt0, &gfxPt1);

    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_PC, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);

    if( (rect->srcblk.width!= rect->dstblk.width)||(rect->srcblk.height!= rect->dstblk.height) )
    {
        MApi_GFX_BitBlt(rect, GFXDRAW_FLAG_SCALE);
    }
    else
    {
        MApi_GFX_BitBlt(rect, 0);
    }
    MApi_GFX_FlushQueue();

    //BitBlt to GOP SD Path with hard code
#if (ENABLE_MSTAR_KAISER==1)
    GFX_BufferInfo dst_info_sd;

    U32 u32Addr=0;


    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_DFB_FRAMEBUFFER_ADR mmap fail\n");
    }

    if(u32Addr==0xFFFF)
    {
        UBOOT_ERROR("get GOP mmap fail\n");
        return -1;
    }
    dst_info_sd.u32Addr = (u32Addr+0xA00000);
    //dst_info_sd.u32Addr = GOP1_BUFFER_ADDR;//0x17AD3000;

    //check VE status
    VE_DrvStatus DrvStatus;
    MS_BOOL VE_PAL = TRUE;
    MDrv_VE_GetStatus(&DrvStatus);
    if(DrvStatus.VideoSystem <= 2)
    {
        VE_PAL = FALSE;
    }
    else
    {
        VE_PAL = TRUE;
    }
    dst_info_sd.u32ColorFmt = GFX_FMT_YUV422;
    if(VE_PAL == TRUE)
    {
        dst_info_sd.u32Height = 576;
    }
    else
    {
        dst_info_sd.u32Height = 480;
    }
    dst_info_sd.u32Pitch = 720*2;
    dst_info_sd.u32Width = 720;
    MApi_GFX_SetDstBufferInfo(&dst_info_sd, 0);
    GFX_DrawRect rect_sd;
    rect_sd.srcblk.x = rect->srcblk.x;
    rect_sd.srcblk.y = rect->srcblk.y;
    rect_sd.srcblk.width = rect->srcblk.width;
    rect_sd.srcblk.height = rect->srcblk.height;

    rect_sd.dstblk.x = 0;
    rect_sd.dstblk.y = 0;
    rect_sd.dstblk.width = dst_info_sd.u32Width;
    rect_sd.dstblk.height = dst_info_sd.u32Height;

    GFX_Point gfxPt0_sd = { rect_sd.dstblk.x, rect_sd.dstblk.y };
    GFX_Point gfxPt1_sd = { rect_sd.dstblk.x+rect_sd.dstblk.width,rect_sd.dstblk.y+rect_sd.dstblk.height };

    MApi_GFX_SetClip(&gfxPt0_sd, &gfxPt1_sd);

    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_PC, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);

    if( (rect_sd.srcblk.width!= rect_sd.dstblk.width)||(rect_sd.srcblk.height!= rect_sd.dstblk.height) )
    {
        MApi_GFX_BitBlt(&rect_sd, GFXDRAW_FLAG_SCALE);
    }
    else
    {
        MApi_GFX_BitBlt(&rect_sd, GFXDRAW_FLAG_DEFAULT);
    }
    MApi_GFX_FlushQueue();
#endif
    return 1;
    //BitBlt to GOP SD Path

}
void MsDrvGOP_Init(void)
{
    // MS_U8 u8Idx;
    GOP_InitInfo pGopInit;
    //MApi_GOP_RegisterFBFmtCB(( U32(*)(MS_U16 pitch,U32 addr , MS_U16 fmt ))OSD_RESOURCE_SetFBFmt);
    MApi_GOP_RegisterXCIsInterlaceCB(_sc_is_interlace);
    MApi_GOP_RegisterXCGetCapHStartCB(_sc_get_h_cap_start);
    MApi_GOP_RegisterXCReduceBWForOSDCB(_Sys_PQ_ReduceBW_ForOSD);
    pGopInit.u16PanelWidth = g_IPanel.Width();
    pGopInit.u16PanelHeight = g_IPanel.Height();
    pGopInit.u16PanelHStr = g_IPanel.HStart();
    pGopInit.u32GOPRBAdr = 0x0;//((GOP_GWIN_RB_MEMORY_TYPE & MIU1) ? (GOP_GWIN_RB_ADR | MIU_INTERVAL) : (GOP_GWIN_RB_ADR));
    pGopInit.u32GOPRBLen = 0x0;

    //there is a GOP_REGDMABASE_MIU1_ADR for MIU1
    pGopInit.u32GOPRegdmaAdr = 0;//((GOP_REGDMABASE_MEMORY_TYPE & MIU1) ? (GOP_REGDMABASE_ADR | MIU_INTERVAL) : (GOP_REGDMABASE_ADR));
    pGopInit.u32GOPRegdmaLen = 0;
    pGopInit.bEnableVsyncIntFlip = FALSE;

    if (TRUE == bDelayLogo)
    {
        // initilize the GOP of Subtitle instead of UI;
        // otherwise, then bootlogo will be closed unexpectedly,
        // because UI is initilalized during booting up
        char* p_str = getenv("bootlogo_gopidx");
        g_logoGopIdx = (NULL != p_str) ? simple_strtoul(p_str, NULL, 10) : 0;
    }

#if (ENABLE_MSTAR_KENYA==1||ENABLE_MSTAR_KRITI==1||ENABLE_MSTAR_KERES==1)
    g_logoGopIdx = 3;
#endif

    MApi_GOP_GWIN_SetForceWrite(TRUE);
    MApi_GOP_InitByGOP(&pGopInit, g_logoGopIdx);
    MApi_GOP_GWIN_SwitchGOP(g_logoGopIdx);

#if (ENABLE_HDMITX_MSTAR_ROCKET==1)
    MApi_GOP_GWIN_EnableT3DMode(FALSE);
#endif

    if (TRUE == bDelayLogo)
    {
        // read the MIU in which the bootlogo stored
        MApi_GOP_MIUSel(g_logoGopIdx, g_logoMiuIdx);
    }
    
#if defined(PCB_WITH_MFC) 
		//since the time that ursa go into main loop time is sensitive
		//this should no be marked when ursa exist
    MMapInfo_s mmapinfo = {0};
    if (get_mmap("E_DFB_FRAMEBUFFER", &mmapinfo) == 0) 
    {
        g_logoMiuIdx = mmapinfo.u32miuID;
    }
    MApi_GOP_MIUSel(g_logoGopIdx,g_logoMiuIdx);
#endif

    char * p_str = getenv("GOP_SET_MUX");
    if(p_str != NULL)
    {
        int i = 0;
        int j = 0;
        U8 au8GopMux[4] = {0};
        GOP_MuxConfig stMuxCfg;

        memset(&stMuxCfg, 0, sizeof(GOP_MuxConfig));

        while(p_str[i] != '\0')
        {
            if((p_str[i] != ':') && (p_str[i] >= 0x30) &&(p_str[i] <= 0x39))
            {
                au8GopMux[j] = p_str[i] - 0x30;
                stMuxCfg.GopMux[j].u8GopIndex = au8GopMux[j];
                stMuxCfg.GopMux[j].u8MuxIndex = j;
                stMuxCfg.u8MuxCounts = ++j;
            }

            i++;
        }

        MApi_GOP_GWIN_SetMux(&stMuxCfg, sizeof(GOP_MuxConfig));
    }

#if(ENABLE_HDMI_TX == 1 && CONFIG_MSTAR_NAPOLI_BD_MST051D_20ANV == 0)

    MApi_GOP_GWIN_OutputColor(GOPOUT_YUV);	//for BOX

#else
    MApi_GOP_GWIN_OutputColor(GOPOUT_RGB);  //TV
#endif
    /* avoiding the fail log in getwinfb func while in init stage
    for(u8Idx=0;u8Idx< MApi_GOP_GWIN_GetGwinNum(g_logoGopIdx);u8Idx++)
    {
        MApi_GOP_GWIN_DeleteWin(u8Idx);
    }
    */
    MApi_GOP_GWIN_SetForceWrite(FALSE);

    //Init GOP2
#if (ENABLE_MSTAR_KAISER==1)
    MApi_GOP_GWIN_SetForceWrite(TRUE);
    MApi_GOP_InitByGOP(&pGopInit, g_logoGopIdx_SC);
    MApi_GOP_GWIN_SwitchGOP(g_logoGopIdx_SC);
    /*
    for(u8Idx=0;u8Idx< MApi_GOP_GWIN_GetGwinNum(g_logoGopIdx_SC);u8Idx++)
    {
        MApi_GOP_GWIN_DeleteWin(u8Idx);
    }
    */
    MApi_GOP_GWIN_SetForceWrite(FALSE);
#endif

}

void MsDrvGOP_Show(GFX_BufferInfo *dst_info,MS_BOOL bHorStretch, MS_BOOL bVerStretch,MS_U16 u16DispX,MS_U16 u16DispY)
{
    MApi_GOP_GWIN_SetForceWrite(TRUE);
    MApi_GOP_GWIN_SwitchGOP(g_logoGopIdx);
    MsDrvGOP_SetStretch(dst_info, bHorStretch, bVerStretch,u16DispX,u16DispY);

    MApi_GOP_GWIN_SetGOPDst(g_logoGopIdx, E_GOP_DST_OP0);

    u8OsdLayerFbId = MApi_GOP_GWIN_GetFreeFBID();
    u8OsdLayerGwinId = MApi_GOP_GWIN_GetFreeWinID();

    MApi_GOP_GWIN_CreateFBbyStaticAddr(u8OsdLayerFbId, 0, 0, dst_info->u32Width, dst_info->u32Height, E_MS_FMT_YUV422, dst_info->u32Addr);

    MApi_GOP_GWIN_MapFB2Win(u8OsdLayerFbId, u8OsdLayerGwinId);
    //jh patch for k3 need fix after sn has right dac panel ini
#if(ENABLE_MSTAR_KAISER==1)
    //  MApi_GOP_SetGOPHStart(0,g_IPanel.HStart() +  0x50);
#endif

    MApi_GOP_GWIN_SetBlending(u8OsdLayerGwinId, FALSE, 0xFF);

    MApi_GOP_GWIN_SetForceWrite(FALSE);
    MApi_GOP_GWIN_Enable(u8OsdLayerGwinId, TRUE);

#if (ENABLE_MSTAR_KAISER==1)
    _UseOtherGOPShowToVE();
#endif
}

#if CONFIG_MINIUBOOT
#else
#if (ENABLE_DISPLAY_LOGO) // GEGOP
int do_destroy_logo (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (u8OsdLayerGwinId != 0xFF)
    {
        MApi_GOP_GWIN_Set_HSCALE(FALSE, 0, 0);
        MApi_GOP_GWIN_Set_VSCALE(FALSE, 0, 0);
        MApi_GOP_GWIN_Enable(u8OsdLayerGwinId, FALSE);
        MApi_GOP_GWIN_DestroyWin(u8OsdLayerGwinId);
        u8OsdLayerGwinId = 0xFF;
    }

    if (u8OsdLayerFbId != 0xFF)
    {
        MApi_GOP_GWIN_DestroyFB(u8OsdLayerFbId);
        u8OsdLayerFbId = 0xFF;
    }
    return 0;
}

U_BOOT_CMD(
    destroy_logo,    1,   1,  do_destroy_logo,
    "destroy_logo - Stop logo display \n",
    "Stop logo display\n"
);
#endif
#endif
