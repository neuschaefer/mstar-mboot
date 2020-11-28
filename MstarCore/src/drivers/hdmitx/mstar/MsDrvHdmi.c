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
#include <command.h>
#include <MsCommon.h>
#include <MsTypes.h>
#include <apiPNL.h>
#include <MsDebug.h>
#include <MsMmap.h>
#include <panel/MsDrvPanel.h>
#include <apiHDMITx.h>
#include <apiDAC.h>
#include <drvTVEncoder.h>
#if (ENABLE_MSTAR_KENYA == 1 ||ENABLE_MSTAR_KERES == 1 ||ENABLE_MSTAR_KRITI == 1 ||ENABLE_MSTAR_CLIPPERS==1)
#include <drvSYS.h>
#include <drvXC_IOPort.h>
#include <apiXC.h>
#endif

#if(ENABLE_MSTAR_KAISER==1)
#include "k3/mdrv_dac_tbl.h"
#include "k3/mdrv_dac_tbl.c"
#elif(ENABLE_MSTAR_KENYA == 1)
#include "kenya/mdrv_dac_tbl.h"
#include "kenya/mdrv_dac_tbl.c"
#elif(ENABLE_MSTAR_KERES == 1)
#include "keres/mdrv_dac_tbl.h"
#include "keres/mdrv_dac_tbl.c"
#elif(ENABLE_MSTAR_KRITI == 1)
#include "kriti/mdrv_dac_tbl.h"
#include "kriti/mdrv_dac_tbl.c"
#elif(ENABLE_MSTAR_CLIPPERS == 1)
#include "clippers/mdrv_dac_tbl.h"
#include "clippers/mdrv_dac_tbl.c"
#else
#include "k2/mdrv_dac_tbl.h"
#include "k2/mdrv_dac_tbl.c"
#endif

#if (ENABLE_MSTAR_KENYA == 1 ||ENABLE_MSTAR_KERES==1 ||ENABLE_MSTAR_KRITI==1 ||ENABLE_MSTAR_CLIPPERS ==1)
#define VE_FRAMEBUFFER_OFFSET       (16)
#define VE_WRITE_ADDR_ADJUSTMENT    (-8)
#define VE_READ_ADDR_ADJUSTMENT     (0)

typedef enum
{
    E_HDMITX_VIDEO_SI_NoData       = 0,
    E_HDMITX_VIDEO_SI_Overscanned  = 1,
    E_HDMITX_VIDEO_SI_Underscanned = 2,
    E_HDMITX_VIDEO_SI_Reserved     = 3,
} MsHDMITX_VIDEO_SCAN_INFO;

typedef enum
{
    E_HDMITX_VIDEO_AFD_SameAsPictureAR    = 8, // 1000
    E_HDMITX_VIDEO_AFD_4_3_Center         = 9, // 1001
    E_HDMITX_VIDEO_AFD_16_9_Center        = 10, // 1010
    E_HDMITX_VIDEO_AFD_14_9_Center        = 11, // 1011
    E_HDMITx_VIDEO_AFD_Others = 15, // 0000~ 0111, 1100 ~ 1111
} MsHDMITX_VIDEO_AFD_RATIO;
#endif //(ENABLE_MSTAR_KENYA == 1)

typedef struct
{
    MS_U8                   u8ResolutionEnv;
    PANEL_RESOLUTION_TYPE   enResolutionType;
    E_DAC_PANEL_INDEX       enDACIndex;
}HDMI_RESOLUTION_DAC_MAP;

#if(ENABLE_MSTAR_CLIPPERS == 1)
#define RESOLUTION_COUNTER 27
#else
#define RESOLUTION_COUNTER 10
#endif

#define HDMITX_INFO_SIZE    3


static HDMITX_ANALOG_TUNING astHdmiAnalogCfg[HDMITX_INFO_SIZE] =
{
    // sd
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    // HD color depth 24bit, 30bit
    {0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
    // DEEP_HD color depth 36bit
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x07},
};

/* display resolution
DACOUT_1080P_50 -> 4//resolution env via SN
DACOUT_1080P_60 -> 5
DACOUT_720P_50 -> 2
DACOUT_720P_60 -> 3
DACOUT_576P_60 -> 1
DACOUT_480P_60 -> 0
*/
static HDMI_RESOLUTION_DAC_MAP staMapTypeIndex[RESOLUTION_COUNTER] = {
    {0, DACOUT_480P,       DAC_PANEL_480P_60},
    {1, DACOUT_576P,       DAC_PANEL_576P_50},
    {2, DACOUT_720P_50,    DAC_PANEL_720P_50},
    {3, DACOUT_720P_60,    DAC_PANEL_720P_60},
    {4, DACOUT_1080P_50,   DAC_PANEL_1080P_50},

    {5, DACOUT_1080P_60,   DAC_PANEL_1080P_60},
    {6, DACOUT_480I,       DAC_PANEL_480I_60},
    {7, DACOUT_576I,       DAC_PANEL_576I_50},
    {8, DACOUT_1080I_50,   DAC_PANEL_1080I_50},
    {9, DACOUT_1080I_60,   DAC_PANEL_1080I_60},
#if(ENABLE_MSTAR_CLIPPERS == 1)

    {10, DACOUT_1080P_30,   DAC_PANEL_1080P_30},
    {11, DACOUT_1080P_25,   DAC_PANEL_1080P_25},
    {12, DACOUT_1080P_24,   DAC_PANEL_1080P_24},
    {13, DACOUT_640x480_60,   DAC_PANEL_640x480_60},
    {14, DACOUT_1920x2205P_24,   DAC_PANEL_1920x2205P_24},

    {15, DACOUT_1280x1470P_50,   DAC_PANEL_1280x1470P_50},
    {16, DACOUT_1280x1470P_60,   DAC_PANEL_1280x1470P_60},
    {17, DACOUT_3840x2160P_24,   DAC_PANEL_3840x2160P_24},
    {18, DACOUT_3840x2160P_25,   DAC_PANEL_3840x2160P_25},
    {19, DACOUT_3840x2160P_30,   DAC_PANEL_3840x2160P_30},

    {20, DACOUT_3840x2160P_50,   DAC_PANEL_3840x2160P_50},
    {21, DACOUT_3840x2160P_60,   DAC_PANEL_3840x2160P_60},
    {22, DACOUT_4096x2160P_24,   DAC_PANEL_4096x2160P_24},
    {23, DACOUT_4096x2160P_25,   DAC_PANEL_4096x2160P_25},
    {24, DACOUT_4096x2160P_30,   DAC_PANEL_4096x2160P_30},
    {25, DACOUT_4096x2160P_50,   DAC_PANEL_4096x2160P_50},

    {26, DACOUT_4096x2160P_60,   DAC_PANEL_4096x2160P_60},

#endif

};



static MS_BOOL getResolutionTypeAndDACIndex(MS_U16 *pPanelType, MS_U16 *pDACIndex)
{
    int u8ResolutionEnv = -1;
    char * p_str = NULL;

    if((NULL == pPanelType) || (NULL == pDACIndex))
    {
        printf("error, paremetre is invalid!\n");
        return FALSE;
    }

    p_str = getenv ("resolution");
    if(NULL != p_str)
    {
        u8ResolutionEnv = (int)simple_strtol(p_str, NULL, 10);
    }
     else
    {
        //set env normal resolution.
        setenv("resolution", "5");
        saveenv();
    }
    //printf("getResolutionTypeAndDACIndex,line:%d£¬ u8ResolutionEnv:%d\n",__LINE__,u8ResolutionEnv);

    if((RESOLUTION_COUNTER <= u8ResolutionEnv) || (0 > u8ResolutionEnv))
    {
        printf("error, resolution env is out of [0--9]!\n");
        return FALSE;
    }

    *pPanelType = staMapTypeIndex[u8ResolutionEnv].enResolutionType;
    *pDACIndex  = staMapTypeIndex[u8ResolutionEnv].enDACIndex;
    //printf("getResolutionTypeAndDACIndex,line:%d£¬ enResolutionType:%d, enDACIndex:%d\n",__LINE__,*pPanelType,*pDACIndex);

    return TRUE;
}

MS_BOOL setHDMITxAnalogTuning(PANEL_RESOLUTION_TYPE enResolutionType)
{
    MS_BOOL bRet = FALSE;
    HDMITX_VIDEO_COLORDEPTH_VAL Val = 0;
    HDMITX_ANALOG_TUNING stHDMITxTun;
    memset(&stHDMITxTun, 0x00 , sizeof(HDMITX_ANALOG_TUNING));

    bRet = MApi_HDMITx_GetRxDCInfoFromEDID(&Val);
    if(FALSE == bRet)
    {
        printf("%s: Error: MApi_HDMITx_GetRxDCInfoFromEDID EDID is not ready, at %d\n", __func__, __LINE__);
        return FALSE;
    }

    //HD:1080P50/60£¬deep HD:1080P50/60&36 bit£¬others SD
/*    if(DACOUT_1080P_50 > enResolutionType)
    {
        memcpy(&stHDMITxTun, (HDMITX_ANALOG_TUNING*)&(astHdmiAnalogCfg[0]), sizeof(HDMITX_ANALOG_TUNING));
    }
    else */if(((DACOUT_1080P_50 == enResolutionType) || (DACOUT_1080P_60 == enResolutionType)) &&
        (HDMITX_VIDEO_CD_36Bits == Val))
    {
        memcpy(&stHDMITxTun, (HDMITX_ANALOG_TUNING*)&(astHdmiAnalogCfg[2]), sizeof(HDMITX_ANALOG_TUNING));
    }
    else if((DACOUT_1080P_50 == enResolutionType) || (DACOUT_1080P_60 == enResolutionType))
    {
        memcpy(&stHDMITxTun, (HDMITX_ANALOG_TUNING*)&(astHdmiAnalogCfg[1]), sizeof(HDMITX_ANALOG_TUNING));
    }
    else
    {
       // printf("%s: warning: setHDMITxAnalogTuning params are out of scope now, at %d\n", __func__, __LINE__);
        memcpy(&stHDMITxTun, (HDMITX_ANALOG_TUNING*)&(astHdmiAnalogCfg[0]), sizeof(HDMITX_ANALOG_TUNING));
    }

    MApi_HDMITx_AnalogTuning(&stHDMITxTun);
    return TRUE;
}

static MS_VE_VIDEOSYS getVEVideoSys(PANEL_RESOLUTION_TYPE enPanelType)
{
    switch (enPanelType)
    {
        case DACOUT_480I:
        case DACOUT_480P:
        case DACOUT_720P_60:
        case DACOUT_1080I_60:
        case DACOUT_1080P_60:
        case DACOUT_1080P_30:
        case DACOUT_1080P_24:
        case DACOUT_640x480_60:
        case DACOUT_1920x2205P_24:
        case DACOUT_1280x1470P_60:
        case DACOUT_3840x2160P_24:
        case DACOUT_3840x2160P_30:
#if(ENABLE_MSTAR_CLIPPERS == 1)
        case DACOUT_3840x2160P_60:
        case DACOUT_4096x2160P_24:
        case DACOUT_4096x2160P_30:
        case DACOUT_4096x2160P_60:
#endif

            return MS_VE_NTSC;
        case DACOUT_576I:
        case DACOUT_576P:
        case DACOUT_720P_50:
        case DACOUT_1080I_50:
        case DACOUT_1080P_50:
        case DACOUT_1080P_25:
        case DACOUT_1280x1470P_50:
#if(ENABLE_MSTAR_CLIPPERS == 1)
        case DACOUT_3840x2160P_50:
        case DACOUT_4096x2160P_25:
        case DACOUT_4096x2160P_50:
#endif
            return MS_VE_PAL;
        default:
            UBOOT_ERROR("ERROR: Not support current panel resolution!\n");
            while(1);
            break;
    }

    return MS_VE_VIDEOSYS_NUM;
}

static MS_U16 getFrameRates(PANEL_RESOLUTION_TYPE enPanelType)
{
    switch (enPanelType)
    {
        case DACOUT_480I:
        case DACOUT_480P:
        case DACOUT_720P_60:
        case DACOUT_1080I_60:
        case DACOUT_1080P_60:
        case DACOUT_640x480_60:
        case DACOUT_1920x2205P_24:
        case DACOUT_1280x1470P_60:
        case DACOUT_3840x2160P_24:
        case DACOUT_3840x2160P_30:
#if(ENABLE_MSTAR_CLIPPERS == 1)
        case DACOUT_3840x2160P_60:
        case DACOUT_4096x2160P_24:
        case DACOUT_4096x2160P_30:
        case DACOUT_4096x2160P_60:
#endif
            return 6000 / 2;
        case DACOUT_576I:
        case DACOUT_576P:
        case DACOUT_720P_50:
        case DACOUT_1080I_50:
        case DACOUT_1080P_50:
        case DACOUT_1080P_25:
        case DACOUT_1280x1470P_50:
#if(ENABLE_MSTAR_CLIPPERS == 1)
        case DACOUT_3840x2160P_50:
        case DACOUT_4096x2160P_25:
        case DACOUT_4096x2160P_50:
#endif
        default:
            break;
    }

    return 5000 / 2;
}

static HDMITX_VIDEO_TIMING getHDMITxVideoTiming(PANEL_RESOLUTION_TYPE enPanelType)
{
    switch (enPanelType)
    {
        case DACOUT_480I:
            return HDMITX_RES_720x480i;
        case DACOUT_480P:
            return HDMITX_RES_720x480p;
        case DACOUT_576I:
            return HDMITX_RES_720x576i;
        case DACOUT_576P:
            return HDMITX_RES_720x576p;
       	case DACOUT_720P_50:
			return HDMITX_RES_1280x720p_50Hz;
        case DACOUT_720P_60:
            return HDMITX_RES_1280x720p_60Hz;
        case DACOUT_1080I_50:
            return HDMITX_RES_1920x1080i_50Hz;
        case DACOUT_1080I_60:
            return HDMITX_RES_1920x1080i_60Hz;
        case DACOUT_1080P_50:
            return HDMITX_RES_1920x1080p_50Hz;
        case DACOUT_1080P_60:
            return HDMITX_RES_1920x1080p_60Hz;
#if(ENABLE_MSTAR_CLIPPERS == 1)

        case DACOUT_1080P_30:
            return HDMITX_RES_1920x1080p_30Hz;

        case DACOUT_1080P_25:
            return HDMITX_RES_1920x1080p_25Hz;

        case DACOUT_1080P_24:
            return HDMITX_RES_1920x1080p_24Hz;

        case DACOUT_1280x1470P_50:
            return HDMITX_RES_1280X1470p_50Hz;

        case DACOUT_1280x1470P_60:
            return HDMITX_RES_1280X1470p_60Hz;

        case DACOUT_3840x2160P_24:
            return HDMITX_RES_3840x2160p_24Hz;

        case DACOUT_3840x2160P_25:
            return HDMITX_RES_3840x2160p_25Hz;

        case DACOUT_3840x2160P_30:
            return HDMITX_RES_3840x2160p_30Hz;

        case DACOUT_3840x2160P_50:
            return HDMITX_RES_3840x2160p_50Hz;

        case DACOUT_3840x2160P_60:
            return HDMITX_RES_3840x2160p_60Hz;

        case DACOUT_4096x2160P_24:
            return HDMITX_RES_4096x2160p_24Hz;

        case DACOUT_4096x2160P_25:
            return HDMITX_RES_4096x2160p_25Hz;

        case DACOUT_4096x2160P_30:
            return HDMITX_RES_4096x2160p_30Hz;

        case DACOUT_4096x2160P_50:
            return HDMITX_RES_4096x2160p_50Hz;

        case DACOUT_4096x2160P_60:
            return HDMITX_RES_4096x2160p_60Hz;


#endif
        default:
            break;
    }

    return HDMITX_RES_1280x720p_50Hz;
}

static MS_BOOL IsReciverSupportYPbPr(void)
{
    #define BLOCK_INDEX1    1

    MS_U8 u8BlockData[128] = {0};
    MApi_HDMITx_GetEDIDData(u8BlockData, BLOCK_INDEX1);

    if ( ( u8BlockData[0x03]& 0x30) == 0x00)
    {
        UBOOT_TRACE("Rx Not Support YCbCr\n");
        return FALSE;
    }
    else
    {
        UBOOT_TRACE("Rx Support YUV444 or YUV422 \n");
        return TRUE;
    }
}


#if (ENABLE_MSTAR_KENYA == 1 || ENABLE_MSTAR_KERES == 1 || ENABLE_MSTAR_KRITI == 1 ||ENABLE_MSTAR_CLIPPERS ==1)
int msHdmitx_Disp_Init(void)
{
    MS_BOOL _bModeNTSC = FALSE;
    MS_BOOL bRet = FALSE;
    PANEL_RESOLUTION_TYPE enPanelType = PANEL_RES_MIN;
    E_DAC_PANEL_INDEX enDACIndex      = DAC_PANEL_480I_60;
    MS_VE_VIDEOSYS eVEStd = MS_VE_PAL;
    MS_VE_WINDOW_TYPE stVEWin = {0, 0, 720, 576};
    XC_INITDATA sXC_InitData;

    printf("msHdmitx_Disp_Init\n");


    bRet = getResolutionTypeAndDACIndex((MS_U16 *)&enPanelType, (MS_U16 *)&enDACIndex);
    //printf("msHdmitx_Init,line:%d£¬bRet:%d, enPanelType:%d,enDACIndex:%d \n",__LINE__,bRet,enPanelType,enDACIndex);
    if(FALSE == bRet)
    {
        printf("%s: Error: getResolutionTypeAndDACIndex FAILE! use 1080p default, at %d\n", __func__, __LINE__);
        enPanelType = DACOUT_1080P_60;
        enDACIndex  = DAC_PANEL_1080P_60;
    }
    UBOOT_DEBUG("[%s %d] (%u, %u)\n",__FUNCTION__,__LINE__,enPanelType,enDACIndex);

    //2. Initialization - DAC and HDMI initialization
    memset(&sXC_InitData, 0, sizeof(XC_INITDATA));
    MApi_XC_Init(&sXC_InitData, sizeof(XC_INITDATA));
    MDrv_SYS_Init();
    //case E_VOP_SEL_OSD_BLEND2:
    //    SC_W2BYTEMSK(REG_SC_BK2F_28_L, 0x0000, 0x0001);
    //    SC_W2BYTEMSK(REG_SC_BK0F_46_L, 0x0020, 0x00F0);
    //    SC_W2BYTEMSK(REG_SC_BK0F_57_L, 0x0800, 0x0800);
#if defined(__ARM__)
        *(volatile unsigned int*)0x1F205E00 = 0x000F;
        *(volatile unsigned int*)0x1F205F18 = 0x0020;
#else
        *(volatile unsigned int*)0xBF205E00 = 0x000F;
        *(volatile unsigned int*)0xBF205F18 = 0x0020;
#endif


    //2. Initialization - DAC and HDMI initialization
    //UBOOT_DEBUG(printf("verDispTx_Main - step1\n"));
    MApi_DAC_Init();
    MApi_DAC_Enable(TRUE, TRUE);
    MApi_DAC_Enable(TRUE, FALSE);
    MApi_DAC_SetClkInv(TRUE, TRUE);

#if (ENABLE_MSTAR_KENYA == 1)
    MApi_DAC_SetOutputSource(E_DAC_TO_HDGEN, TRUE);
    MApi_DAC_SetOutputSwapSel(E_DAC_R_G_B, TRUE);
    MApi_DAC_SetOutputLevel(E_DAC_OUTPUT_LEVEL_LOW, TRUE);
    MApi_DAC_SetIHalfOutput(FALSE,TRUE);
#endif

    MApi_HDMITx_SetDbgLevel(0);
    MApi_HDMITx_SetHPDGpioPin(HDMITX_HPD_PM_GPIO);
    MApi_HDMITx_Init();
    MApi_HDMITx_TurnOnOff(TRUE);
    MApi_HDMITx_SetVideoOnOff(TRUE);

    MS_U32 u32StartTime = 0;
    MS_BOOL bHDMISupport = FALSE;
    HDMITX_VIDEO_COLOR_FORMAT eOutColorFmt = HDMITX_VIDEO_COLOR_YUV444;
    HDMITX_OUTPUT_MODE  eOutMode = HDMITX_HDMI;
    HDMITX_VIDEO_COLORDEPTH_VAL eEDIDColorDepth = HDMITX_VIDEO_CD_NoID;

    MApi_HDMITx_EdidChecking();
    u32StartTime = MsOS_GetSystemTime();
    while((MApi_HDMITx_EDID_HDMISupport(&bHDMISupport) != TRUE) && (MsOS_Timer_DiffTimeFromNow(u32StartTime) < 10))
    {
        printf("EDID NOT READY! \n");
    }

    MApi_HDMITx_GetRxDCInfoFromEDID(&eEDIDColorDepth);
    if(eEDIDColorDepth <= HDMITX_VIDEO_CD_24Bits)
    {
        //To pass simplay lab HDMI test, Item 7-19
        eEDIDColorDepth = HDMITX_VIDEO_CD_NoID;
    }
    else
    {
        //Only Support HDMI 8 bit mode in Mboot
        eEDIDColorDepth = HDMITX_VIDEO_CD_24Bits;
    }

    if(bHDMISupport)
    {
        if (IsReciverSupportYPbPr() == TRUE)
        {
            eOutColorFmt = HDMITX_VIDEO_COLOR_YUV444;
        }
        else
        {
            eOutColorFmt = HDMITX_VIDEO_COLOR_RGB444;
        }

        eOutMode = HDMITX_HDMI;
        printf("Rx Support HDMI mode! \n");
    }
    else
    {
        eOutMode = HDMITX_DVI;
        eOutColorFmt = HDMITX_VIDEO_COLOR_RGB444;
        printf("Rx Support DVI mode only! \n");
    }

    MApi_HDMITx_SetHDMITxMode_CD(eOutMode, eEDIDColorDepth);

#if(ENABLE_MSTAR_CLIPPERS ==1)
    if(enPanelType==DACOUT_3840x2160P_50 ||
        enPanelType==DACOUT_3840x2160P_60 ||
        enPanelType==DACOUT_4096x2160P_50 ||
        enPanelType==DACOUT_3840x2160P_60 )
    {
        MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_YUV420, HDMITX_VIDEO_COLOR_YUV420);
    }
    else
    {
        MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_YUV444, eOutColorFmt);
    }
#else
    MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_YUV444, eOutColorFmt);
#endif

#if(ENABLE_POWER_MUSIC==1)
        MApi_HDMITx_SetAudioOnOff(TRUE);
        MApi_HDMITx_SetAudioConfiguration(HDMITX_AUDIO_48K, HDMITX_AUDIO_CH_2, HDMITX_AUDIO_PCM);
#endif

    //MApi_HDMITx_SetAudioConfiguration(HDMITX_AUDIO_48K, HDMITX_AUDIO_CH_2, HDMITX_AUDIO_PCM);

    //3.
    //UBOOT_DEBUG(printf("verDispTx_Main - step2\n"));
    DAC_TAB_INFO DacTbl;
    DacTbl = DACMAP_Main[enDACIndex];
    // dump DAC general/scaler/HDGEN register tables
    MApi_DAC_DumpTable(DacTbl.pDacINITTab, DacTbl.eINITtype);
    MApi_DAC_DumpTable(DacTbl.pDacINIT_SCTab, DacTbl.eINIT_SCtype);
    MApi_DAC_DumpTable(DacTbl.pDacINIT_HDGENTab, DacTbl.eINIT_HDGENtype);

#if (ENABLE_MSTAR_KENYA==1 ||ENABLE_MSTAR_KERES==1 ||ENABLE_MSTAR_KRITI==1 ||ENABLE_MSTAR_CLIPPERS ==1)
    //Default HDMI TX color depth : 8-bits mode
    MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BIT_DividerTab, DacTbl.eINIT_HDMITX_8BIT_Dividertype);
    MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BITTab, DacTbl.eINIT_HDMITX_8BITtype);
#else
    /*
     * force read EDID for HDMITx Auto Color Depth Mode
     */
    static HDMITX_VIDEO_COLORDEPTH_VAL _eCurColorDepth;
    MApi_HDMITx_GetRxDCInfoFromEDID(&_eCurColorDepth);
    printf("SetHDMIOutputMode_CD: g_eCurColorDepth = %d \n", _eCurColorDepth);

    switch(_eCurColorDepth)
    {
        case HDMITX_VIDEO_CD_NoID:
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BIT_DividerTab, DacTbl.eINIT_HDMITX_8BIT_Dividertype);
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BITTab, DacTbl.eINIT_HDMITX_8BITtype);
            break;

        default:
        case HDMITX_VIDEO_CD_24Bits:
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BIT_DividerTab, DacTbl.eINIT_HDMITX_8BIT_Dividertype);
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BITTab, DacTbl.eINIT_HDMITX_8BITtype);
            break;

        case HDMITX_VIDEO_CD_30Bits:
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_10BIT_DividerTab, DacTbl.eINIT_HDMITX_10BIT_Dividertype);
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_10BITTab, DacTbl.eINIT_HDMITX_10BITtype);
            break;

        case HDMITX_VIDEO_CD_36Bits:
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_12BIT_DividerTab, DacTbl.eINIT_HDMITX_12BIT_Dividertype);
            MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_12BITTab, DacTbl.eINIT_HDMITX_12BITtype);
            break;
    }

    //4.
    //UBOOT_DEBUG(printf("verDispTx_Main - step3\n"));
    MApi_HDMITx_SetHDMITxMode_CD(HDMITX_HDMI, _eCurColorDepth);
#endif

    MApi_HDMITx_SetVideoOutputTiming(getHDMITxVideoTiming(enPanelType));
    setHDMITxAnalogTuning(enPanelType);

    // MApi_HDMITx_Exhibit();
    if(getHDMITxVideoTiming(enPanelType) <= HDMITX_RES_720x576p)
    {
        MApi_HDMITx_SetVideoOutputOverscan_AFD(ENABLE, E_HDMITX_VIDEO_SI_NoData, E_HDMITX_VIDEO_AFD_4_3_Center);
    }
    else
    {
        MApi_HDMITx_SetVideoOutputOverscan_AFD(ENABLE, E_HDMITX_VIDEO_SI_NoData, E_HDMITX_VIDEO_AFD_16_9_Center);
    }
    //udelay(500000);
    MApi_HDMITx_SetTMDSOnOff(TRUE);

    switch(enPanelType)
    {
        case DACOUT_480I:
        case DACOUT_480P:
        case DACOUT_720P_60:
        case DACOUT_1080I_60:
        case DACOUT_1080P_60:
            {
                eVEStd = MS_VE_NTSC;
                _bModeNTSC = TRUE;
            }
            break;
        default:
            {
                eVEStd = MS_VE_PAL;
                _bModeNTSC = FALSE;
            }
            break;
    }

    //VE initialization
    //UBOOT_DEBUG(printf("verDispTx_Main - step4\n"));
    if(eVEStd >= MS_VE_PAL_N)
    {
        //shift 8 pixels in PAL mode
        printf("shift %d pixels in PAL mode \n", VE_WRITE_ADDR_ADJUSTMENT);
        MDrv_VE_AdjustPositionBase(VE_WRITE_ADDR_ADJUSTMENT, VE_READ_ADDR_ADJUSTMENT);
    }
    else
    {
        //shift 0 pixels in NTSC mode
        printf("shift 0 pixels in NTSC mode \n");
        MDrv_VE_AdjustPositionBase(0, VE_READ_ADDR_ADJUSTMENT);
    }

#if (defined(CONFIG_URANUS4))
    MApi_GOP_SC_Init();
#endif

#if (CONFIG_DISPLAY_LOGO && (!ENABLE_BOOT_SPI_ECOS))
    MMapInfo_s mmapinfo;
    if(get_mmap("E_MMAP_ID_VE", &mmapinfo)!=0)
    {
        UBOOT_ERROR("get E_MMAP_ID_VE fail\n");
        MDrv_VE_Init(VE_BUFFER_ADDR + VE_FRAMEBUFFER_OFFSET);
    }
    else
    {
        MDrv_VE_Init(mmapinfo.u32Addr + VE_FRAMEBUFFER_OFFSET);
    }
#else
    MDrv_VE_Init(VE_BUFFER_ADDR + VE_FRAMEBUFFER_OFFSET);
#endif

    MDrv_VE_SetOSD(TRUE);

    MDrv_VE_SetOutputVideoStd(eVEStd);
    MDrv_VE_set_display_window(stVEWin);

    //1. VE configuration
    MS_Switch_VE_Src_Info SwitchInputSrc;
    SwitchInputSrc.InputSrcType = MS_VE_SRC_SCALER;
    MDrv_VE_SwitchInputSource(&SwitchInputSrc);

    MS_Switch_VE_Dest_Info SwitchOutputDest;
    SwitchOutputDest.OutputDstType = MS_VE_DEST_CVBS;
    MDrv_VE_SwitchOuputDest(&SwitchOutputDest);

    MS_VE_Set_Mode_Type SetModeType;
    SetModeType.u16H_CapSize     = g_IPanel.Width();
    SetModeType.u16V_CapSize     = g_IPanel.Height();
    SetModeType.u16H_CapStart    = g_IPanel.HStart();
    SetModeType.u16V_CapStart    = g_IPanel.VStart();
    SetModeType.u16H_SC_CapSize  = g_IPanel.Width();
    SetModeType.u16V_SC_CapSize  = g_IPanel.Height();
    SetModeType.u16H_SC_CapStart = g_IPanel.HStart();
    SetModeType.u16V_SC_CapStart = g_IPanel.VStart();
    SetModeType.u16InputVFreq = 2500*2/10;
    SetModeType.bSrcInterlace = FALSE;
    MDrv_VE_SetMode(&SetModeType);

    MS_VE_Output_Ctrl OutputCtrl;
    OutputCtrl.bEnable    = TRUE;
    OutputCtrl.OutputType = MS_VE_OUT_TVENCODER;
    MDrv_VE_SetOutputCtrl(&OutputCtrl);

    return 0;
}
#endif

int msHdmitx_Init(void)
{
    PANEL_RESOLUTION_TYPE enPanelType = 0;
 //   enPanelType = MApi_PNL_GetPnlTypeSetting();
    E_DAC_PANEL_INDEX   enDACIndex = 0;
    MS_BOOL bRet = FALSE;
    U32 u32Addr=0;

    UBOOT_TRACE("IN\n");
    MApi_HDMITx_SetHPDGpioPin(HDMITX_HPD_PM_GPIO);
    bRet = getResolutionTypeAndDACIndex((MS_U16 *)&enPanelType, (MS_U16 *)&enDACIndex);
    //printf("msHdmitx_Init,line:%d£¬bRet:%d, enPanelType:%d,enDACIndex:%d \n",__LINE__,bRet,enPanelType,enDACIndex);
    if(FALSE == bRet)
    {
        printf("%s: Error: getResolutionTypeAndDACIndex FAILE! use 1080p default, at %d\n", __func__, __LINE__);
        enPanelType = DACOUT_1080P_60;
        enDACIndex = DAC_PANEL_1080P_60;
    }

    //0. VE initialization
    if(get_addr_from_mmap("E_MMAP_ID_VE", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_MMAP_ID_VE fail\n");
        return -1;
    }
    MDrv_VE_Init(u32Addr); //MDrv_VE_Init(VE_BUFFER_ADDR);
    MDrv_VE_SetOSD(FALSE);
    MDrv_VE_SetOutputVideoStd(getVEVideoSys(enPanelType));
    setHDMITxAnalogTuning(enPanelType);    //set bank21_0x2e(16bit mode)
    //1. VE configuration
    MS_Switch_VE_Src_Info SwitchInputSrc;
    SwitchInputSrc.InputSrcType = MS_VE_SRC_SCALER;
    MDrv_VE_SwitchInputSource(&SwitchInputSrc);

    MS_Switch_VE_Dest_Info SwitchOutputDest;
#if 0
#if defined(CONFIG_BOOTLOGO_OUT_CVBS)
    SwitchOutputDest.OutputDstType = MS_VE_DEST_CVBS;
#elif defined(CONFIG_BOOTLOGO_OUT_SCART_HD_DAC) || defined(CONFIG_BOOTLOGO_OUT_SCART_SD_DAC)
    SwitchOutputDest.OutputDstType = MS_VE_DEST_SCART;
#endif
#endif
	SwitchOutputDest.OutputDstType = MS_VE_DEST_SCART;
    MDrv_VE_SwitchOuputDest(&SwitchOutputDest);

    MS_VE_Set_Mode_Type SetModeType;
    SetModeType.u16H_CapSize     = g_IPanel.Width();
    SetModeType.u16V_CapSize     = g_IPanel.Height();
    SetModeType.u16H_CapStart    = g_IPanel.HStart();
    SetModeType.u16V_CapStart    = g_IPanel.VStart();
    SetModeType.u16H_SC_CapSize  = g_IPanel.Width();
    SetModeType.u16V_SC_CapSize  = g_IPanel.Height();
    SetModeType.u16H_SC_CapStart = g_IPanel.HStart();
    SetModeType.u16V_SC_CapStart = g_IPanel.VStart();
    SetModeType.u16InputVFreq = getFrameRates(enPanelType)*2/10;
    SetModeType.bSrcInterlace = FALSE;
    SetModeType.bHDuplicate   = FALSE;
    MDrv_VE_SetMode(&SetModeType);

    MS_VE_Output_Ctrl OutputCtrl;
    OutputCtrl.bEnable = TRUE;
    OutputCtrl.OutputType = MS_VE_OUT_TVENCODER;
    MDrv_VE_SetOutputCtrl(&OutputCtrl);

#if defined(__ARM__)
    *(volatile unsigned int*)0x1F205E00 = 0x000F;
    *(volatile unsigned int*)0x1F205F18 = 0x0020;
#else
    *(volatile unsigned int*)0xBF205E00 = 0x000F;
    *(volatile unsigned int*)0xBF205F18 = 0x0020;
#endif

    //2. Initialization - DAC and HDMI initialization
    //MApi_HDMITx_SetDbgLevel(0xff);
    MApi_DAC_Init();
    MApi_HDMITx_Init();
    MApi_DAC_Enable(TRUE, TRUE);
    MApi_HDMITx_TurnOnOff(TRUE);
    MApi_HDMITx_SetVideoOnOff(TRUE);

    //2.1 set HDMITx mode by checking EDID
    MS_U32 u32StartTime = 0;
    MS_BOOL bHDMISupport = FALSE;
    MS_BOOL bChipSupportDVI = TRUE;
    MS_U32 u32HDMITxCap = FALSE;
    HDMITX_VIDEO_COLOR_FORMAT eOutColorFmt = HDMITX_VIDEO_COLOR_YUV444;
    HDMITX_OUTPUT_MODE  eOutMode = HDMITX_HDMI;
    HDMITX_VIDEO_COLORDEPTH_VAL eEDIDColorDepth = HDMITX_VIDEO_CD_NoID;

    MApi_HDMITx_EdidChecking();
    u32StartTime = MsOS_GetSystemTime();
    while((MApi_HDMITx_EDID_HDMISupport(&bHDMISupport) != TRUE) && (MsOS_Timer_DiffTimeFromNow(u32StartTime) < 10))
    {
        UBOOT_TRACE("EDID NOT READY! \n");
    }
    printf("set MsOS_Timer_DiffTimeFromNow >10 end \n");
    MApi_HDMITx_GetRxDCInfoFromEDID(&eEDIDColorDepth);
    if(eEDIDColorDepth <= HDMITX_VIDEO_CD_24Bits)
    {
        //To pass simplay lab HDMI test, Item 7-19
        eEDIDColorDepth = HDMITX_VIDEO_CD_NoID;
    }
    else
    {
        //Only Support HDMI 8 bit mode in Mboot
        eEDIDColorDepth = HDMITX_VIDEO_CD_24Bits;
    }

#if (ENABLE_MSTAR_KENYA == 0 && ENABLE_MSTAR_KERES==0 && ENABLE_MSTAR_KRITI==0 && ENABLE_MSTAR_CLIPPERS==0)
    MApi_HDMITx_GetChipCaps(E_HDMITX_CAP_SUPPORT_DVI, &u32HDMITxCap, sizeof(MS_BOOL));
#endif
    bChipSupportDVI = (MS_BOOL)u32HDMITxCap;

    if( (bHDMISupport) || (!bChipSupportDVI) )
    {

        if (IsReciverSupportYPbPr() == TRUE)
        {
            eOutColorFmt = HDMITX_VIDEO_COLOR_YUV444;
        }
        else
        {
            if (bChipSupportDVI)
            {
            eOutColorFmt = HDMITX_VIDEO_COLOR_RGB444;
            }
            else
            {
                eOutColorFmt = HDMITX_VIDEO_COLOR_YUV444;
                printf("[%s][%d]This CHIP ONLY support YUV out! \n", __FUNCTION__, __LINE__);
            }
        }

        eOutMode = HDMITX_HDMI;
        UBOOT_TRACE("Rx Support HDMI mode! \n");
    }
    else
    {
        eOutMode = HDMITX_DVI;
        eOutColorFmt = HDMITX_VIDEO_COLOR_RGB444;
        UBOOT_TRACE("Rx Support DVI mode only! \n");
    }


    MApi_HDMITx_SetHDMITxMode_CD(eOutMode, eEDIDColorDepth);
    MApi_HDMITx_SetColorFormat(HDMITX_VIDEO_COLOR_YUV444, eOutColorFmt);


#if(ENABLE_POWER_MUSIC==1)
	MApi_HDMITx_SetAudioOnOff(TRUE);
    MApi_HDMITx_SetAudioConfiguration(HDMITX_AUDIO_48K, HDMITX_AUDIO_CH_2, HDMITX_AUDIO_PCM);
#endif

    //3. jh. set DAC_PANEL_1080P_60 as default
    //DAC_TAB_INFO DacTbl;//DAC_PANEL_1080P_60
    //DacTbl = DACMAP_Main[getDacPanelIdx(enPanelType)];
	//DacTbl = DACMAP_Main[DAC_PANEL_1080P_60];
    DAC_TAB_INFO DacTbl = DACMAP_Main[enDACIndex];
    MApi_DAC_SetClkInv(TRUE, TRUE);

    // dump DAC divider register table
    MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BIT_DividerTab, DacTbl.eINIT_HDMITX_8BIT_Dividertype);

    // dump DAC general/scaler/HDGEN register tables
    MApi_DAC_DumpTable(DacTbl.pDacINITTab, DacTbl.eINITtype);
    MApi_DAC_DumpTable(DacTbl.pDacINIT_SCTab, DacTbl.eINIT_SCtype);
    MApi_DAC_DumpTable(DacTbl.pDacINIT_MODTab, DacTbl.eINIT_MODtype);
    MApi_DAC_DumpTable(DacTbl.pDacINIT_HDGENTab, DacTbl.eINIT_HDGENtype);

#if (ENABLE_MSTAR_KAISER==1) // K3
	E_DAC_PANEL_INDEX enSC1DACIndex = DAC_PANEL_576I_50;

	if(MS_VE_NTSC == getVEVideoSys(enPanelType))
	{
        enSC1DACIndex = DAC_PANEL_480I_60;
	}
	else
	{
        enSC1DACIndex = DAC_PANEL_576I_50;
	}

	DAC_TAB_INFO SC1DacTbl = DACMAP_Main[enSC1DACIndex];
	MApi_DAC_DumpTable(SC1DacTbl.pDacSC1_INITTab, SC1DacTbl.eSC1_INITtype);
    MApi_DAC_DumpTable(SC1DacTbl.pDacSC1_INIT_SCTab, SC1DacTbl.eSC1_INIT_SCtype);
#endif

    MApi_DAC_Enable(TRUE, TRUE);
    MApi_DAC_Enable(TRUE, FALSE);

#if defined(CONFIG_BOOTLOGO_OUT_SCART_HD_DAC)
    MApi_DAC_SetOutputSource(E_DAC_TO_VE_YPBPR, TRUE);
    MApi_DAC_SetOutputSwapSel(E_DAC_R_G_B, TRUE);
    MApi_DAC_SetOutputLevel(E_DAC_OUTPUT_LEVEL_HIGH, TRUE);
#elif defined(CONFIG_BOOTLOGO_OUT_SCART_SD_DAC)
    MApi_DAC_SetOutputSource(E_DAC_TO_VE, FALSE);
    MApi_DAC_SetOutputSwapSel(E_DAC_R_R_R, FALSE);
    MApi_DAC_SetOutputLevel(E_DAC_OUTPUT_LEVEL_HIGH, FALSE);
#endif

#if defined(SDDAC_YPBPR_HALF_CURRENT_ENABLE)
	MApi_DAC_SetIHalfOutput(TRUE, TRUE);
#endif

#if defined(SDDAC_CVBS_HALF_CURRENT_ENABLE)
	MApi_DAC_SetIHalfOutput(TRUE, FALSE);
#endif

	// dump DAC HDMITx register table
    MApi_DAC_DumpTable(DacTbl.pDacINIT_HDMITX_8BITTab, DacTbl.eINIT_HDMITX_8BITtype);

    //4.
    MApi_HDMITx_SetVideoOutputTiming(getHDMITxVideoTiming(enPanelType));
    //udelay(500000);
    MApi_HDMITx_SetTMDSOnOff(TRUE);
    UBOOT_TRACE("OK\n");
    return 0;
}
#if 0
int hdmiExit(void)
{
    VE_Result res;
    VE_DrvStatus status;
    memset(&status, 0, sizeof(status));
    res = MDrv_VE_GetStatus(&status);
    if(res != E_VE_OK)
        return -1;
    if((MS_U8)status.u16H_CapSize == 0 && (MS_U8)status.u16V_CapSize == 0) //check if not init, if no init, return
        return -1;
    MApi_DAC_Enable(FALSE, TRUE);
    MApi_DAC_Enable(FALSE, FALSE);
    MApi_DAC_Exit();
    MDrv_VE_Exit();
    return 0;
}
#endif
