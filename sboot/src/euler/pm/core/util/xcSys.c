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
#define _XC_SYS_C_

////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "datatype.h"
#include "Board.h"
#include "drvGlobal.h"
#include "hwreg.h"
#include "MsCommon.h"
#include "xcSys.h"
#include "drvISR.h"

////////////////////////////////////////////////////////////////////////////////

#define XC_MSG(x)       //x

#if ENABLE_VGA_JUST_CHECK_SYNC
#define VGA_SYNC_COUNT      10
U8 u8HVSyncCount;
#endif

////////////////////////////////////////////////////////////////////////////////
void msDelayTime(U32 u32Delay)
{
    // volatile is necessary to avoid optimization
    U32 volatile u32Dummy = gTimerCount0;
    
    while (1)
    {
        if((gTimerCount0-u32Dummy)>=u32Delay)
        {
            break;
        }
    }
}

/***************************************************************************************/

static void XC_Switch_VGA_Mux(INPUT_SOURCE_TYPE_t eSrcType)
{
#if 0
    XC_MUX_PATH_INFO PathInfo;
    S16 s16PathId;

    PathInfo.Path_Type = PATH_TYPE_SYNCHRONOUS;
    PathInfo.src = eSrcType;
    PathInfo.dest = OUTPUT_SCALER_MAIN_WINDOW;
    PathInfo.path_thread = NULL;
    PathInfo.SyncEventHandler = NULL;
    PathInfo.DestOnOff_Event_Handler = NULL;
    PathInfo.dest_periodic_handler = NULL;

    s16PathId = MApi_XC_Mux_CreatePath( &PathInfo, sizeof(XC_MUX_PATH_INFO) );
printf("s16PathId = 0x%x \r\n", s16PathId);
    if (s16PathId == -1)
    {
        printf("Create path fail src = %d  dest = %d \r\n", PathInfo.src ,PathInfo.dest);
    }
    else
    {
        printf("Create path success src = %d dest = %d \r\n",PathInfo.src ,PathInfo.dest );
        MApi_XC_Mux_EnablePath( (U16)s16PathId );
    }
#else
    UNUSED(eSrcType);
#endif
}

/***************************************************************************************/

void _MApi_XC_Sys_Init_XC(void)
{
    XC_INITDATA sXC_InitData;

    sXC_InitData.u32XC_version = XC_INITDATA_VERSION;
    sXC_InitData.u32XTAL_Clock = MST_XTAL_CLOCK_HZ;
    sXC_InitData.u32Main_FB_Size = 0;
    sXC_InitData.u32Main_FB_Start_Addr = 0;
    sXC_InitData.u32Sub_FB_Size = 0;
    sXC_InitData.u32Sub_FB_Start_Addr = 0;
    sXC_InitData.bIsShareGround = 0;
    sXC_InitData.eScartIDPort_Sel = 0;
    sXC_InitData.bCEC_Use_Interrupt = FALSE;
    sXC_InitData.bEnableIPAutoCoast = ENABLE_IP_AUTO_COAST;
    sXC_InitData.bMirror = 0;
    sXC_InitData.stPanelInfo.u16HStart = 0;      // DE H start
    sXC_InitData.stPanelInfo.u16VStart = 0;
    sXC_InitData.stPanelInfo.u16Width  = 1920;
    sXC_InitData.stPanelInfo.u16Height = 1080;
    sXC_InitData.stPanelInfo.u16HTotal = 2200;
    sXC_InitData.stPanelInfo.u16VTotal = 1130;
    sXC_InitData.stPanelInfo.u16DefaultVFreq = 50;
    sXC_InitData.stPanelInfo.u8LPLL_Mode = 0;
    sXC_InitData.stPanelInfo.enPnl_Out_Timing_Mode = 0;
    sXC_InitData.stPanelInfo.u16DefaultHTotal = 2200;
    sXC_InitData.stPanelInfo.u16DefaultVTotal = 1130;
    sXC_InitData.stPanelInfo.u32MinSET = 0;
    sXC_InitData.stPanelInfo.u32MaxSET = 0;
    sXC_InitData.stPanelInfo.eLPLL_Type = 0;
    sXC_InitData.bDLC_Histogram_From_VBlank = FALSE;

#if 0
    if(MApi_XC_Init(&sXC_InitData, sizeof(XC_INITDATA)) == FALSE)
    {
        printf("XC_Init failed \r\n");
    }
#else
#endif
}

/***************************************************************************************/

static MS_U8 XC_Get_Sync_Status(void)
{
    MS_U8 u8Bank, u8DetectStatus;

    u8Bank = MDrv_ReadByte(0x102F00);

    /* mode detect status */
    MDrv_WriteByte(0x102F00, 0x01);
    u8DetectStatus = MDrv_ReadByte(H_BK_IP1F2(0x1E));

    u8Bank = MDrv_ReadByte(0x102F00);

    return u8DetectStatus;
}

/***************************************************************************************/

static MS_U16 XC_Get_HorizontalPeriod(void)
{
    MS_U8 u8Bank;
    MS_U16 u16HorizontalPeriod;

    u8Bank = MDrv_ReadByte(0x102F00);

    /* mode detect status */
    MDrv_WriteByte(0x102F00, 0x01);

    u16HorizontalPeriod = MDrv_Read2Byte(L_BK_IP1F2(0x20));

    MDrv_WriteByte( 0x102F00, u8Bank );

    return (u16HorizontalPeriod & MST_H_PERIOD_MASK);
}

static MS_U16 XC_Get_VerticalTotal(void)
{
    MS_U8 u8Bank;
    MS_U16 u16VerticalTotal;

    u8Bank = MDrv_ReadByte(0x102F00);

    /* mode detect status */
    MDrv_WriteByte(0x102F00, 0x01);

    u16VerticalTotal = MDrv_Read2Byte(L_BK_IP1F2(0x1F));

    MDrv_WriteByte( 0x102F00, u8Bank );

    return (u16VerticalTotal & MST_V_TOTAL_MASK);
}

//-------------------------------------------------------------------------------------------------
/// This function will calculate and return H Frequency x 10
/// @param  wHPeriod      \b IN: Horizontal period
/// @return MS_U16: H Frequency x 10
//-------------------------------------------------------------------------------------------------
static MS_U16 XC_CalculateHFreqx10(MS_U16 wHPeriod)
{
    MS_U16 u16HFreqx10 = 0;

    if (wHPeriod)
        u16HFreqx10 = ( (((MS_U32)MST_XTAL_CLOCK_HZ + (wHPeriod/2)) / wHPeriod ) / 100 );
    else
        u16HFreqx10 = 1;   // avoid devide by 0 error

    return u16HFreqx10;
}

static MS_U16 XC_Get_HFreqx10(void)
{
    MS_U16 u16HorizontalPeriod, u16HFreqx10;

    u16HorizontalPeriod = XC_Get_HorizontalPeriod();
    u16HFreqx10 = XC_CalculateHFreqx10(u16HorizontalPeriod);

    return u16HFreqx10;
}

//-------------------------------------------------------------------------------------------------
/// This function will calculate and return V Frequency x 10
/// @param  wHFreq      \b IN: Horizontal frequency
/// @param  wVTotal     \b IN: Vertical Total, usually the scan lines counts of a frame
/// @return MS_U16: V Frequency x 10
//-------------------------------------------------------------------------------------------------
static MS_U16 XC_CalculateVFreqx10(MS_U16 wHFreq, MS_U16 wVTotal)
{
    MS_U16 u16VFreqx10;

    if (wHFreq && wVTotal)
        u16VFreqx10 = ( (((MS_U32)wHFreq * 1000 ) + (wVTotal/2)) / wVTotal ); // Hz
    else
        u16VFreqx10 = 0;

    return u16VFreqx10;
}

static MS_U16 XC_Get_VFreqx10(void)
{
    MS_U16 u16VFreqx10;

    u16VFreqx10 = XC_CalculateVFreqx10(XC_Get_HFreqx10(), XC_Get_VerticalTotal());

    if (XC_Get_Sync_Status() & XC_MD_INTERLACE_BIT)
    {
        u16VFreqx10 *= 2;
    }

    return u16VFreqx10;
}

/***************************************************************************************/

static MS_BOOL _MApp_PCMode_Check_OOR(XC_MODEPARSE_INPUT_INFO *psInputInfo)
{
    MS_U16 u16MinHfreq, u16MaxHfreq;
    MS_U16 u16MinVfreq, u16MaxVfreq;
    MS_U16 u16MinVtotal, u16MaxVtotal;

    if(IsSrcTypeVga(psInputInfo->eSrcType))
    {
        u16MinHfreq    = MIN_HFREQ_OF_RGB;
        u16MaxHfreq    = MAX_HFREQ_OF_RGB;
        u16MinVfreq    = MIN_VFREQ_OF_RGB;
        u16MaxVfreq    = MAX_VFREQ_OF_RGB;
        u16MinVtotal   = MIN_VTOTAL_OF_RGB;
        u16MaxVtotal   = MAX_VTOTAL_OF_RGB;
    }
#if (INPUT_HDMI_VIDEO_COUNT > 0)
    else
    {
        u16MinHfreq    = MIN_HFREQ_OF_DVI;
        u16MaxHfreq    = MAX_HFREQ_OF_DVI;
        u16MinVfreq    = MIN_VFREQ_OF_DVI;
        u16MaxVfreq    = MAX_VFREQ_OF_DVI;
        u16MinVtotal   = MIN_VTOTAL_OF_DVI;
        u16MaxVtotal   = MAX_VTOTAL_OF_DVI;
    }
#endif

    if ( (psInputInfo->u16HFreqx10 > u16MaxHfreq) || (psInputInfo->u16HFreqx10 < u16MinHfreq) ||
         (psInputInfo->u16VFreqx10 > u16MaxVfreq) || (psInputInfo->u16VFreqx10 < u16MinVfreq) ||
         (psInputInfo->u16Vtotal > u16MaxVtotal) || (psInputInfo->u16Vtotal < u16MinVtotal)
         ||((IsSrcTypeHDMI(psInputInfo->eSrcType)&&(psInputInfo->sDVI_HDMI_DE_Info.width > MAX_WIDTH_OF_DVI))
         ||(psInputInfo->sDVI_HDMI_DE_Info.height > MAX_HEIGHT_OF_DVI))
        )
    {
        XC_MSG(printf("OOR u16HFreqx10 %d \r\n", psInputInfo->u16HFreqx10));
        XC_MSG(printf("OOR u16VFreqx10 %d \r\n", psInputInfo->u16VFreqx10));
        XC_MSG(printf("OOR u16Vtotal %d \r\n", psInputInfo->u16Vtotal));

        return TRUE;
    }

    return FALSE;
}

/***************************************************************************************/
static BOOLEAN XC_Get_PC_ModeStatus(void)
{
    MS_U8 u8DetectStatus;

    XC_Switch_VGA_Mux(INPUT_SOURCE_VGA);

    u8DetectStatus = XC_Get_Sync_Status();
    msDelayTime(100);
    XC_MSG(printf("################(1)###############\r\n"));
    XC_MSG(printf(" u8DetectStatus     = 0x%x \r\n", u8DetectStatus));

    gXC_PCMode_Info.u16Hperiod = XC_Get_HorizontalPeriod();
    gXC_PCMode_Info.sModeParseInputInfo.eSrcType = INPUT_SOURCE_VGA;
    gXC_PCMode_Info.sModeParseInputInfo.u16HFreqx10 = XC_Get_HFreqx10();
    gXC_PCMode_Info.sModeParseInputInfo.u16VFreqx10 = XC_Get_VFreqx10();
    gXC_PCMode_Info.sModeParseInputInfo.u16Vtotal = XC_Get_VerticalTotal();

    if ( u8DetectStatus & BIT(0) )
    {
        gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus |= XC_MD_VSYNC_POR_BIT;
    }
    if ( u8DetectStatus & BIT(1) )
    {
        gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus |= XC_MD_HSYNC_POR_BIT;
    }
    if ( u8DetectStatus & BIT(3) )
    {
        gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus |= XC_MD_INTERLACE_BIT;
    }

    #if ENABLE_VGA_JUST_CHECK_SYNC
    if( (u8DetectStatus & BIT(0)) || (u8DetectStatus & BIT(1)) )
    {
        u8HVSyncCount++;
        return TRUE;
    }
    #endif

    /* HSync */
    if ( (gXC_PCMode_Info.u16Hperiod == MST_H_PERIOD_MASK)
       ||(gXC_PCMode_Info.u16Hperiod < 10) )
    {
        gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus |= XC_MD_HSYNC_LOSS_BIT;
    }

    /* VSync */
    if ( (gXC_PCMode_Info.sModeParseInputInfo.u16Vtotal == MST_V_TOTAL_MASK)
       ||(gXC_PCMode_Info.sModeParseInputInfo.u16Vtotal < 200) )
    {
        gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus |= XC_MD_VSYNC_LOSS_BIT;
    }

    // Mode Parse... to be implemented.
    if ( _MApp_PCMode_Check_OOR(&(gXC_PCMode_Info.sModeParseInputInfo)) )
    {
        gXC_PCMode_Info.eModeParseResult = XC_MODEPARSE_OUT_OF_RANGE;
        XC_MSG(printf(" OUT_OF_RANGE \r\n"));
    }
    else
    {
        gXC_PCMode_Info.eModeParseResult =
                MApi_XC_ModeParse_MatchMode(MApi_XC_GetModeTable(),
                                            MApi_XC_GetTotalModeCount(),
                                            &(gXC_PCMode_Info.sModeParseInputInfo));
    }

    return TRUE;
}

/***************************************************************************************/

XC_MODEPARSE_RESULT XC_GetModeParseResult(void)
{
    return gXC_PCMode_Info.eModeParseResult;
}


/***************************************************************************************/

void XC_Get_ModeStatus(void)
{
    gXC_PCMode_Info.eModeParseResult = XC_MODEPARSE_NOT_PARSED;
    gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus = 0;

    XC_Get_PC_ModeStatus();
    msDelayTime(100);

    XC_MSG(printf("################(2)###############\r\n"));
    XC_MSG(printf(" eSrcType     = 0x%x \r\n", gXC_PCMode_Info.sModeParseInputInfo.eSrcType));
    XC_MSG(printf(" u8SyncStatus = 0x%x \r\n", gXC_PCMode_Info.sModeParseInputInfo.u8SyncStatus));
    XC_MSG(printf(" u16HFreqx10  = 0x%x \r\n", gXC_PCMode_Info.sModeParseInputInfo.u16HFreqx10));
    XC_MSG(printf(" u16VFreqx10  = 0x%x \r\n", gXC_PCMode_Info.sModeParseInputInfo.u16VFreqx10));
    XC_MSG(printf(" u16Hperiod   = 0x%x \r\n", gXC_PCMode_Info.u16Hperiod));
    XC_MSG(printf(" u16Vtotal    = 0x%x \r\n", gXC_PCMode_Info.sModeParseInputInfo.u16Vtotal));

    XC_MSG(printf("################(3)###############\r\n"));
    XC_MSG(printf(" u8ModeIndex      = 0x%x \r\n", gXC_PCMode_Info.sModeParseInputInfo.u8ModeIndex));
    XC_MSG(printf(" eModeParseResult = 0x%x \r\n", gXC_PCMode_Info.eModeParseResult));
    XC_MSG(printf("##################################\r\n\n\n"));
}

#if ENABLE_VGA_JUST_CHECK_SYNC
BOOLEAN XC_Check_HVSync(void)
{
    if(u8HVSyncCount > VGA_SYNC_COUNT)
        return TRUE;
    else
        return FALSE;
}

void XC_Clear_HVSyncCount(void)
{
    u8HVSyncCount = 0;
}
#endif

#if ENABLE_SC_BLOCK_SYNC_WAKEUP
void XC_Recovery_VGA(void)
{
    MS_U8 u8Bank;

    u8Bank = MDrv_ReadByte(0x102F00);

    //(1) set main ipmux to ADC A
    MDrv_WriteByteMask(0x102E02,0x00,0xF0);

    //(2)set input source select to analog1 (VGA)
    MDrv_WriteByte(0x102F00, 0x01);
    MDrv_WriteByteMask(0x102F04,0x00,0x0F);
    MDrv_WriteByte( 0x102F00, u8Bank );
}
#endif
////////////////////////////////////////////////////////////////////////////////
#undef _XC_SYS_C_

