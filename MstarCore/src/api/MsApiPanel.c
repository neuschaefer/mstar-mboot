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
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <command.h>
#include <MsTypes.h>
#include <apiPNL.h>
#include <MsDebug.h>
#include <MsBoot.h>
#include <bootlogo/MsPoolDB.h>
#include <panel/MsDrvPanel.h>
#include <MsApiPanel.h>
#if(ENABLE_URSA_6M30 == 1)
#include <ursa/ursa_6m30.h>
#endif
#if (ENABLE_MSTAR_CLEANBOOT) ||(ENABLE_MSTAR_PUMABOOT)
#include <MsSystem.h>
#include <drvMBX.h>
#include <MsOS.h>
#endif

#if(ENABLE_URSA_6M40 == 1)
#include <ursa/ursa_6m40.h>
#endif

#if(ENABLE_URSA_8 == 1)
#include <ursa/ursa_8.h>
#endif

#if defined(CONFIG_URSA6_VB1) && (!defined(CONFIG_MSTAR_MONACO))
#include <ursa/ursa_6m38.h>
#endif

#include <MsMmap.h>
#include <MsSystem.h>
#include <mstarstr.h>
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------
void cmp(PanelType *p1, PanelType *p2);

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define PANEL_DEBUG 0

//-------------------------------------------------------------------------------------------------
//  External Functions
//-------------------------------------------------------------------------------------------------
#if (ENABLE_MSTAR_PUMABOOT)
extern MS_BOOL MApi_PBMBX_SendMsgPanel(U32 u32Addr, U16 u16Level, U16 u16Type);
#endif

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static MS_BOOL bPanleReady=FALSE;
static GetPnlTypeSet_cb fpCusGetPnlTypeSet = NULL;

#if (ENABLE_HDMI_RESOLUTION_RESET==1)
#if (ENABLE_HDMI_TX_RESOLUTION == 0)
static char* DacPanelIndexTbl[] = {
    "DACOUT_480P_60",
    "DACOUT_576P_50",
    "DACOUT_720P_50",
    "DACOUT_720P_60",
    "DACOUT_1080P_50",
    "DACOUT_1080P_60",
    "DACOUT_480I_60",
    "DACOUT_576I_50",
    "DACOUT_1080I_50",
    "DACOUT_1080I_60",
    "DACOUT_4K2KP_25",
    "DACOUT_4K2KP_30",
    "DACOUT_4K2KP_60",
};

typedef enum{
    DACOUT_RES_480P_60              = 0,
    DACOUT_RES_576P_50              = 1,
    DACOUT_RES_720P_50              = 2,
    DACOUT_RES_720P_60              = 3,
    DACOUT_RES_1080P_50             = 4,
    DACOUT_RES_1080P_60             = 5,
    DACOUT_RES_480I_60              = 6,
    DACOUT_RES_576I_50              = 7,
    DACOUT_RES_1080I_50             = 8,
    DACOUT_RES_1080I_60             = 9,
    DACOUT_RES_4k2kP_25 			= 10,
    DACOUT_RES_4k2kP_30             = 11,
    DACOUT_RES_4k2kP_60             = 12,
}DACOUT_VIDEO_TIMING;

#else
#include <apiHDMITx.h>
static char* HdmiTxPanelIndexTable[] = {
    "",
    "HDMITX_480_60I",
    "HDMITX_576_50I",
    "HDMITX_480_60P",
    "HDMITX_576_50P",
    "HDMITX_720_50P",
    "HDMITX_720_60P",
    "HDMITX_1080_50I",
    "HDMITX_1080_60I",
    "HDMITX_1080_24P",
    "HDMITX_1080_25P",
    "HDMITX_1080_30P",
    "HDMITX_1080_50P",
    "HDMITX_1080_60P",
    "HDMITX_4K2K_30P",
    "HDMITX_1470_50P",
    "HDMITX_1470_60P",
    "HDMITX_1470_24P",
    "HDMITX_1470_30P",
    "HDMITX_2205_24P",
    "HDMITX_2205_30P",
    "HDMITX_4K2K_25P",
};

static char* HdmiTxTimingIndexTable[] = {
    "HDMITX_RES_640x480p",
    "HDMITX_RES_720x480i",
    "HDMITX_RES_720x576i",
    "HDMITX_RES_720x480p",
    "HDMITX_RES_720x576p",
    "HDMITX_RES_1280x720p_50Hz",
    "HDMITX_RES_1280x720p_60Hz",
    "HDMITX_RES_1920x1080i_50Hz",
    "HDMITX_RES_1920x1080i_60Hz",
    "HDMITX_RES_1920x1080p_24Hz",
    "HDMITX_RES_1920x1080p_25Hz",
    "HDMITX_RES_1920x1080p_30Hz",
    "HDMITX_RES_1920x1080p_50Hz",
    "HDMITX_RES_1920x1080p_60Hz",
    "HDMITX_RES_4K2Kp_30Hz",
    "HDMITX_RES_1280x1470p_50Hz",
    "HDMITX_RES_1280x1470p_60Hz",
    "HDMITX_RES_1280x1470p_24Hz",
    "HDMITX_RES_1280x1470p_30Hz",
    "HDMITX_RES_1920x2205p_24Hz",
    "HDMITX_RES_1920x2205p_30Hz",
    "HDMITX_RES_4K2Kp_25Hz",
};
#endif
#endif

#if (ENABLE_MSTAR_KENYA==1 ||ENABLE_MSTAR_KERES==1 ||ENABLE_MSTAR_CLIPPERS==1 || ENABLE_MSTAR_KRITI==1)
typedef struct
{
    MS_U8                   u8ResolutionEnv;
    PANEL_RESOLUTION_TYPE   enResolutionType;
}RESOLUTION_DAC_MAP;

static RESOLUTION_DAC_MAP stMapTypeIndex[] = {
    {0, DACOUT_480P},
    {1, DACOUT_576P},
    {2, DACOUT_720P_50},
    {3, DACOUT_720P_60},
    {4, DACOUT_1080P_50},
    {5, DACOUT_1080P_60},
    {6, DACOUT_480I},
    {7, DACOUT_576I},
    {8, DACOUT_1080I_50},
    {9, DACOUT_1080I_60}
};
#endif

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
int panel_sinit(void);
int panel_dinit(void);
static PANEL_RESOLUTION_TYPE _GetPnlTypeSetting(void);

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
int IsPanelReady(void)
{
    if(bPanleReady==TRUE)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

APIPNL_LINK_EXT_TYPE GetPanelLinkExtType(void)
{
    APIPNL_LINK_EXT_TYPE eType = LINK_EPI34_8P;
    char *s = getenv("panel_ext_type");
    if(s != NULL)
    {
        eType = (APIPNL_LINK_EXT_TYPE)simple_strtol(s, NULL, 10);
    }
    return eType;
}

#if (ENABLE_MSTAR_CLEANBOOT==1)
#define PNL_MBX_QUEUESIZE      8
#define PNL_MBX_TIMEOUT          5000

MS_BOOL MApi_PNL_MailBox_Init(void)
{
    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_CB_PNL_NOWAIT, PNL_MBX_QUEUESIZE))
    {
        printf("MApi_PNL_MailBox_Init - MBX register msg error\n");
        return FALSE;
    }
    return TRUE;
}

MS_BOOL MApi_PNL_MailBox_Deinit(void)
{
    if( E_MBX_SUCCESS != MDrv_MBX_UnRegisterMSG(E_MBX_CLASS_CB_PNL_NOWAIT, TRUE))
    {
        printf("@@ E_MBX_CLASS_SECURE_WAIT - MBX unregister msg error\n");
    }
    return TRUE;
}

MS_BOOL MApi_PNL_MailBox_SendParameters(U32 u32Addr, U16 u16Level, U16 u16Type)
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
//    printf("MApi_PNL_MailBox_SendParameters - MDrv_MBX_SendMsg u32Addr:0x%x,u16Level:0x%x,u16Type:0x%x\n",u32Addr,u16Level,u16Type);

    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_CB_PNL_NOWAIT;
    stMB_Command.u8Index = 0;
    stMB_Command.u8ParameterCount = 9;
    stMB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    stMB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    stMB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    stMB_Command.u8Parameters[3] =  (U8)(u32Addr&0xFF);
    stMB_Command.u8Parameters[4] =  (U8)(u16Level>>8);
    stMB_Command.u8Parameters[5] =  (U8)(u16Level&0xFF);
    stMB_Command.u8Parameters[6] =  (U8)(u16Type>>8);
    stMB_Command.u8Parameters[7] =  (U8)(u16Type&0xFF);
    stMB_Command.u8Parameters[8] =  0;//panel init order
//    printf(" -MDrv_MBX_SendMsg u8Parameters[0]:0x%x, MDrv_MBX_SendMsg u8Parameters[1]:0x%x\n",stMB_Command.u8Parameters[0],stMB_Command.u8Parameters[1]);
//    printf(" -MDrv_MBX_SendMsg u8Parameters[2]:0x%x, MDrv_MBX_SendMsg u8Parameters[3]:0x%x\n",stMB_Command.u8Parameters[2],stMB_Command.u8Parameters[3]);
//    printf(" -MDrv_MBX_SendMsg u8Parameters[4]:0x%x, MDrv_MBX_SendMsg u8Parameters[5]:0x%x\n",stMB_Command.u8Parameters[4],stMB_Command.u8Parameters[5]);
//    printf(" -MDrv_MBX_SendMsg u8Parameters[6]:0x%x, MDrv_MBX_SendMsg u8Parameters[7]:0x%x\n",stMB_Command.u8Parameters[6],stMB_Command.u8Parameters[7]);
    MDrv_MBX_SendMsg(&stMB_Command);
//    printf("MApi_PNL_MailBox_SendParameters - MDrv_MBX_SendMsg \n");

    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_CB_PNL_NOWAIT, &stMB_Command, PNL_MBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("MApi_PNL_MailBox_SendParameters Fail\n");
    }
    return enMbxResult;
}

#endif //(ENABLE_MSTAR_CLEANBOOT==1)


void RegisterCBGetPnlTypeSetting(GetPnlTypeSet_cb cb)
{
    UBOOT_TRACE("IN\n");
    fpCusGetPnlTypeSet=cb;
    UBOOT_TRACE("OK\n");
}

#if (ENABLE_MSTAR_KENYA==1 ||ENABLE_MSTAR_KERES==1 ||ENABLE_MSTAR_CLIPPERS==1 || ENABLE_MSTAR_KRITI==1)
static PANEL_RESOLUTION_TYPE _GetPnlTypeSettingFromEnv(void)
{
    int resolution_index = 0;
    PANEL_RESOLUTION_TYPE PanelType = DACOUT_1080I_50;
    char * p_str;
    p_str = getenv ("resolution");

    if(p_str != NULL)
    {
        resolution_index = (int)simple_strtol(p_str, NULL, 10);
        if(resolution_index < sizeof(stMapTypeIndex)/sizeof(RESOLUTION_DAC_MAP))
        {
            return stMapTypeIndex[resolution_index].enResolutionType;
        }
    }

    return PanelType;
}
#endif
static PANEL_RESOLUTION_TYPE _GetPnlTypeSetting(void)
{
    PANEL_RESOLUTION_TYPE PanelType = 0;
    UBOOT_TRACE("IN\n");
    if(fpCusGetPnlTypeSet!=NULL)
    {
        PanelType = fpCusGetPnlTypeSet();
    }
    else
    {
        PanelType = MApi_PNL_GetPnlTypeSetting();
    }
    UBOOT_TRACE("OK\n");
    return PanelType;
}


int panel_sinit(void)
{
    PanelType* panel_data = NULL;
    PANEL_RESOLUTION_TYPE enPanelType;
    UBOOT_TRACE("IN\n");

#if (ENABLE_MSTAR_KENYA==1 ||ENABLE_MSTAR_KERES==1 ||ENABLE_MSTAR_CLIPPERS==1 || ENABLE_MSTAR_KRITI==1)
    RegisterCBGetPnlTypeSetting(_GetPnlTypeSettingFromEnv);
#endif

    enPanelType = _GetPnlTypeSetting();
    if(MApi_PNL_PreInit(E_PNL_NO_OUTPUT)!=TRUE)
    {
        bPanleReady=FALSE;
        return -1;
    }

    panel_data=MApi_XC_GetPanelSpec(enPanelType);
    if(panel_data==NULL)
    {
        bPanleReady=FALSE;
        return -1;
    }
#if (ENABLE_MSTAR_MONACO == 1 || ENABLE_MSTAR_MUJI == 1) || (ENABLE_MSTAR_CELTICS)
    if(panel_data->m_wPanelWidth == 3840 && panel_data->m_wPanelHeight == 2160)
    {
        UBOOT_DEBUG(">> m_ePanelLinkExtType = 51 <<<\n");
        setLinkExtType(51);
    }
#endif
    //pane init
    #ifdef BD_LVDS_CONNECT_TYPE
	MApi_BD_LVDS_Output_Type(BD_LVDS_CONNECT_TYPE);
    #endif
    if(MsDrv_PNL_Init(panel_data)==FALSE)
    {
        bPanleReady=FALSE;
        return -1;
    }
    bPanleReady=TRUE;
    UBOOT_TRACE("OK\n");
    return 0;
}

#if (ENABLE_HDMI_RESOLUTION_RESET==1)
static int BootArgs_reset(void)
{
    int resolution_index = 5;
    char p_str[] = "\0";
    char *p;  
    char as8PanelFilePath[50] = "\0";
    #if (ENABLE_HDMI_TX_RESOLUTION == 1)
    HDMITX_VIDEO_TIMING eHDMITimgType = HDMITX_RES_1280x720p_50Hz;
    #else
    DACOUT_VIDEO_TIMING ePANELType = DACOUT_RES_720P_50;
    #endif
    if (isBootToRecovery())
    {
        // if boot to Recovery mode,set resolution 720P
        if(getenv("resolution") != NULL)
        {
            #if (ENABLE_HDMI_TX_RESOLUTION == 1)
            snprintf(p_str,sizeof(p_str),"%ld",eHDMITimgType);
            #else
            snprintf(p_str,sizeof(p_str),"%ld",ePANELType);
            #endif
            if (0 == strcmp(getenv("resolution"), p_str))
                return 0;
            setenv("resolution", p_str);
        }
    }
    else
    {
        if (getenv ("resolution_reset") == NULL)
        {
            setenv("resolution_reset", getenv ("resolution"));
        }
        else
        {
            if (0 == strcmp(getenv("resolution"), getenv ("resolution_reset")))
                return 0;
            setenv("resolution", getenv ("resolution_reset"));
        }
    }

    p = getenv ("resolution");
    if(p != NULL)
    {
        resolution_index = (int)simple_strtol(p, NULL, 10);
        #if (ENABLE_HDMI_TX_RESOLUTION == 1)
        MApi_SetEnv2BootArgs("resolution=", HdmiTxTimingIndexTable[resolution_index]);
        snprintf(as8PanelFilePath, sizeof(as8PanelFilePath),"/config/panel/%s.ini", HdmiTxPanelIndexTable[resolution_index]);
        setenv("panel_path", as8PanelFilePath);
        setenv("panel_name", HdmiTxPanelIndexTable[resolution_index]);
        #else
        MApi_SetEnv2BootArgs("resolution=", DacPanelIndexTbl[resolution_index]);
        snprintf(as8PanelFilePath, sizeof(as8PanelFilePath),"/config/panel/%s.ini", DacPanelIndexTbl[resolution_index]);
        setenv("panel_path", as8PanelFilePath);
        setenv("panel_name", DacPanelIndexTbl[resolution_index]);
        #endif
        setenv("db_table", "0");
        run_command("dbtable_init", 0);
    }
    else
    {
        //set env normal resolution.
        setenv("resolution", "5");
    }
    saveenv();
    return 0;
}
#endif

int panel_dinit(void)
{
    char *pSwingLevel;
    MS_U16 u16Panel_SwingLevel;
    #if (ENABLE_MSTAR_CLEANBOOT==1)
    static PanelType panelpara;
    #else
    PanelType panelpara;
    #endif //(ENABLE_MSTAR_CLEANBOOT==1)
    st_board_para boardpara;
    UBOOT_TRACE("IN\n");

    memset(&panelpara, 0, sizeof(panelpara));
    memset(&boardpara, 0, sizeof(boardpara));

    #if (ENABLE_HDMI_RESOLUTION_RESET==1)
    BootArgs_reset();
    #endif
    //load panel para
#if (defined(CONFIG_URSA6_VB1) || defined(CONFIG_NOVA_KS2)) && (!defined(CONFIG_MSTAR_MONACO))
	if(is_str_resume())
	{
		U32 u32PanelConfigsAddr;
		if(get_addr_from_mmap("E_MMAP_ID_VDEC_CPU", &u32PanelConfigsAddr)!=0)
		{
			UBOOT_ERROR("get E_MMAP_ID_VDEC_CPU mmap fail\n");
			bPanleReady=FALSE;
			return -1;
		}
		UBOOT_DEBUG("E_MMAP_ID_VDEC_CPU = 0x%x\n", u32PanelConfigsAddr);
		UBOOT_DEBUG("(U32)(PA2NVA(u32PanelConfigsAddr)) = 0x%x\n", (U32)(PA2NVA(u32PanelConfigsAddr)));
		memcpy(&panelpara, (U32*)(PA2NVA(u32PanelConfigsAddr)), sizeof(PanelType));
	}
	else
	{
		if(Read_PanelParaFromflash(&panelpara)!=0)
		{
			bPanleReady=FALSE;
			UBOOT_ERROR("%s: Read_PanelParaFromflash() failed, at %d\n", __func__, __LINE__);
			return -1;
		}	
	}
#else
    if(Read_PanelParaFromflash(&panelpara)!=0)
    {
        bPanleReady=FALSE;
        UBOOT_ERROR("%s: Read_PanelParaFromflash() failed, at %d\n", __func__, __LINE__);
        return -1;
    }
#endif

    //load board para
    if(Read_BoardParaFromflash(&boardpara)!=0)
    {
        bPanleReady=FALSE;
        UBOOT_ERROR("%s: Read_BoardParaFromflash() failed, at %d\n", __func__, __LINE__);
        return -1;
    }

    //panel setting by each board
  #if (CONFIG_VESTEL_MB97 == 0) && (CONFIG_VESTEL_MB100 == 0) 
    panelpara.m_bPanelPDP10BIT = boardpara.m_bPANEL_PDP_10BIT;
    panelpara.m_bPanelSwapLVDS_POL = boardpara.m_bPANEL_SWAP_LVDS_POL;
    panelpara.m_bPanelSwapLVDS_CH = boardpara.m_bPANEL_SWAP_LVDS_CH;
    panelpara.m_bPanelSwapPort ^= boardpara.m_bPANEL_CONNECTOR_SWAP_PORT;
    panelpara.m_u16LVDSTxSwapValue = (boardpara.m_u16LVDS_PN_SWAP_H << 8) + boardpara.m_u16LVDS_PN_SWAP_L;
  #endif
#if defined(CONFIG_URSA6_VB1) && (!defined(CONFIG_MSTAR_MONACO))
	if(is_str_resume())
	{
        MDrv_Ursa_6M38_SWI2C_Init();
		if(panelpara.m_wPanelWidth == 3840 && panelpara.m_wPanelHeight == 2160) 
		{
			UBOOT_DEBUG(">> m_ePanelLinkExtType = 45 <<<\n");
			setLinkExtType(45);
		}
		else if(panelpara.m_wPanelWidth == 1920 && panelpara.m_wPanelHeight == 1080)
		{
			UBOOT_DEBUG(">>> m_ePanelLinkExtType = 46 <<<\n");
			setLinkExtType(46);
		}
		else
		{
			UBOOT_DEBUG(">>> get m_ePanelLinkExtType from env <<<\n");
			setLinkExtType(GetPanelLinkExtType());
		}
	}
	else
	{
		UBOOT_DEBUG(">>> get m_ePanelLinkExtType from env <<<\n");
        MDrv_Ursa_6M38_SWI2C_Init();
		setLinkExtType(GetPanelLinkExtType());
	}
#else
#if (ENABLE_MSTAR_MONACO) || (ENABLE_MSTAR_MUJI) || (ENABLE_MSTAR_CELTICS)
    if(panelpara.m_wPanelWidth == 3840 && panelpara.m_wPanelHeight == 2160)
    {
        UBOOT_DEBUG(">> m_ePanelLinkExtType = 51 <<<\n");
        setLinkExtType(51);
    }
    else
    {
        UBOOT_DEBUG(">>@ m_ePanelLinkExtType = %u <<<\n", GetPanelLinkExtType());
        setLinkExtType(GetPanelLinkExtType());
    }
#else
    setLinkExtType(GetPanelLinkExtType());
#endif
#endif
#if (ENABLE_ENABLE_URSA == 1)
#if (ENABLE_URSA_6M40 == 1)
    MDrv_Ursa_6M40_Set_VB1_Init(GetPanelLinkExtType());
#endif
#if (ENABLE_URSA_8 ==1 )||(ENABLE_URSA_6M40 == 1)
       ursa_cmd_table cmd_table={0};
	   if(Read_Ursa_Para(&cmd_table)==0)
	   {
	   	#if (ENABLE_URSA_8 == 1)
		   Ursa_8_Setting(&cmd_table);
		#else
			Ursa_6M40_Syetting(&cmd_table);
		#endif
	   }
	   else
	   {
		  UBOOT_ERROR("read ursa_8 data fail ...>>>\n");
	   }

#endif

#if (ENABLE_URSA_6M30 == 1)
    MDrv_Ursa_6M30_Initialize();
    if(bMst6m30Installed)
    {
        ursa_6m30_cmd_table cmd_table={0};
        if(Read_Ursa_6m30_Para(&cmd_table)==0)
        {
            Ursa_6M30_Setting(&cmd_table);
        }
        else
        {
           UBOOT_ERROR("read ursa_6m30 data fail ...>>>\n");
        }
    }
    else
    {
           UBOOT_ERROR("ursa_6m30 installed fail ...>>>\n");
    }
#endif
#endif
#if PANEL_DEBUG
    PanelType* panel_data = NULL;
    PANEL_RESOLUTION_TYPE enPanelType;
    enPanelType = MApi_PNL_GetPnlTypeSetting();
    MApi_PNL_PreInit(E_PNL_NO_OUTPUT);
    panel_data=MApi_XC_GetPanelSpec(enPanelType);
    cmp(panel_data,&panelpara);
#endif

    //pane init
#if (ENABLE_MSTAR_CLEANBOOT==1)
    //set swing level
    pSwingLevel = getenv("swing_level");
    u16Panel_SwingLevel = simple_strtoul(pSwingLevel, NULL, 10);
    //printf("do_panel_init  SwingLevel:%d, CONNECT_TYPE:%d\n",u16Panel_SwingLevel,boardpara.m_u16BOARD_LVDS_CONNECT_TYPE);
    MApi_PNL_MailBox_Init();
    flush_cache((MS_U32)(&panelpara), sizeof(panelpara));
    MApi_PNL_MailBox_SendParameters(MsOS_VA2PA((MS_U32)(&panelpara)), u16Panel_SwingLevel,boardpara.m_u16BOARD_LVDS_CONNECT_TYPE);
    //MApi_PNL_MailBox_SendParameters(PANEL_To_R2_ADDRESS, u16Panel_SwingLevel,boardpara.m_u16BOARD_LVDS_CONNECT_TYPE);
#else //(ENABLE_MSTAR_CLEANBOOT==1)
    char* pPanel_LVDS_Connect_Type = getenv("PANEL_LVDS_CONNECT_TYPE");
    if((pPanel_LVDS_Connect_Type != NULL) && (strncmp(pPanel_LVDS_Connect_Type,"0x04",4)==0))
    {
        MApi_BD_LVDS_Output_Type(0x04);//LVDS_OUTPUT_User , use to set MOD channels
        //MApi_PNL_MOD_OutputConfig_User(0x1550, 0x0155, 0x0000); //close Channel7 Channel13 
    }
	else
	{
        MApi_BD_LVDS_Output_Type(boardpara.m_u16BOARD_LVDS_CONNECT_TYPE);
	}
    if(MsDrv_PNL_Init(&panelpara)==FALSE)
    {
        bPanleReady=FALSE;
        return -1;
    }

    //set swing level
    pSwingLevel = getenv("swing_level");
    if(pSwingLevel==NULL)
    {
        bPanleReady=FALSE;
        return -1;
    }
    u16Panel_SwingLevel = simple_strtoul(pSwingLevel, NULL, 10);
#if (ENABLE_MSTAR_KAISER==0 && ENABLE_MSTAR_KAISERIN ==0 && ENABLE_MSTAR_CLIPPERS==0 && ENABLE_HDMITX_MSTAR_ROCKET==0)
    if(MApi_PNL_Control_Out_Swing(u16Panel_SwingLevel)!=TRUE)
    {
        bPanleReady=FALSE;
        return -1;
    }
	#endif
#endif
    bPanleReady=TRUE;

    UBOOT_TRACE("OK\n");
    return 0;
}

int do_panel_pre_init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = 0;
    UBOOT_TRACE("IN\n");
    if (argc < 2)
    {
#if (CONFIG_STATIC_PANEL_PARA)
        ret = panel_sinit();
#else
        ret = panel_dinit();
#endif
    }
    else
    {
#if CONFIG_MINIUBOOT
#else
       if(strncmp(argv[1], "-d", 2) == 0)
       {
            ret = panel_dinit();
       }
       else if (strncmp(argv[1], "-s", 2) == 0)
       {
            ret = panel_sinit();
       }
       else
#endif
       {
           cmd_usage(cmdtp);
       }
    }
    UBOOT_TRACE("OK\n");
    return ret;
}
int do_panel_init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = 0;
    UBOOT_TRACE("IN\n");
    if (argc < 2)
    {
#if (CONFIG_STATIC_PANEL_PARA)
        ret = panel_sinit();
#else
        ret = panel_dinit();
#endif
    }
    else
    {
       if(strncmp(argv[1], "-d", 2) == 0)
       {
            ret = panel_dinit();
       }
       else if (strncmp(argv[1], "-s", 2) == 0)
       {
            ret = panel_sinit();
       }
       else
       {
           cmd_usage(cmdtp);
		   return ret;
       }
    }
	if(bPanleReady)
	{
   		MsDrv_PNL_BackLigth_On();
	}
    UBOOT_TRACE("OK\n");
    return ret;
}

int do_backLigth_on(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = 0;
    UBOOT_TRACE("IN\n");
	if(bPanleReady)
	{
   		MsDrv_PNL_BackLigth_On();
	}
	else
	{
		UBOOT_ERROR("do Panel init first!!\n");
	}
    UBOOT_TRACE("OK\n");
    return ret;
}

#if (ENABLE_MSTAR_PUMABOOT)
int r2_pbpnlinit(void)
{
    char *pSwingLevel;
    MS_U16 u16Panel_SwingLevel;
    static PanelType panelpara;
    st_board_para boardpara;

    UBOOT_TRACE("IN\n");
    memset(&panelpara, 0, sizeof(panelpara));
    memset(&boardpara, 0, sizeof(boardpara));

#if 0//
{
    PanelType* panel_data = NULL;
    printf("\n ============= do_panel_init : start =============\n");
    panel_data=MApi_XC_GetPanelSpec(PNL_FULLHD_CMO216_H1L01);
    memcpy(&panelpara, panel_data, sizeof(PanelType));
    panelpara.m_bPanelPDP10BIT = 1;
    panelpara.m_bPanelSwapLVDS_POL = 0;
    panelpara.m_bPanelSwapLVDS_CH = 0;
    panelpara.m_bPanelSwapPort ^= 0;
    panelpara.m_u16LVDSTxSwapValue = 0;
}
#else
    //load panel para
    if(Read_PanelParaFromflash(&panelpara)!=0)
    {
        bPanleReady=FALSE;
        UBOOT_ERROR("%s: Read_PanelParaFromflash() failed, at %d\n", __func__, __LINE__);
        return -1;
    }

    //load board para
    if(Read_BoardParaFromflash(&boardpara)!=0)
    {
        bPanleReady=FALSE;
        UBOOT_ERROR("%s: Read_BoardParaFromflash() failed, at %d\n", __func__, __LINE__);
        return -1;
    }

    #if (CONFIG_VESTEL_MB97 == 0) && (CONFIG_VESTEL_MB100 == 0) 
    //panel setting by each board
    panelpara.m_bPanelPDP10BIT = boardpara.m_bPANEL_PDP_10BIT;
    panelpara.m_bPanelSwapLVDS_POL = boardpara.m_bPANEL_SWAP_LVDS_POL;
    panelpara.m_bPanelSwapLVDS_CH = boardpara.m_bPANEL_SWAP_LVDS_CH;
    panelpara.m_bPanelSwapPort ^= boardpara.m_bPANEL_CONNECTOR_SWAP_PORT;
    panelpara.m_u16LVDSTxSwapValue = (boardpara.m_u16LVDS_PN_SWAP_H << 8) + boardpara.m_u16LVDS_PN_SWAP_L;
    #endif
#endif

    pSwingLevel = 0;
    u16Panel_SwingLevel = 250;
    boardpara.m_u16BOARD_LVDS_CONNECT_TYPE = 3;
    flush_cache((MS_U32)(&panelpara), sizeof(panelpara));
    //printf("\n====================================  send mbx to R2 for panel init: ==================================== \n");
    MApi_PBMBX_SendMsgPanel(MsOS_VA2PA((MS_U32)(&panelpara)), u16Panel_SwingLevel,boardpara.m_u16BOARD_LVDS_CONNECT_TYPE);
    printf("\n ============= do_panel_init : finish =============\n");
    UBOOT_TRACE("OK\n");
    return 0;
}
#endif

#if PANEL_DEBUG
void cmp(PanelType *p1, PanelType *p2)
{
    if((p1 ==NULL) || (p2==NULL))
    {
        printf("null return\n");
        return;
    }
//    printf("compare: '%s', '%s'\n", p1->m_pPanelName, p2->m_pPanelName);
    if(p1->m_bPanelDither != p2->m_bPanelDither)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelDither, p2->m_bPanelDither, __LINE__);
    }
    if(p1->m_ePanelLinkType != p2->m_ePanelLinkType)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ePanelLinkType, p2->m_ePanelLinkType, __LINE__);
    }
    if(p1->m_bPanelDualPort != p2->m_bPanelDualPort)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelDualPort, p2->m_bPanelDualPort, __LINE__);
    }
    if(p1->m_bPanelSwapPort != p2->m_bPanelSwapPort)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapPort, p2->m_bPanelSwapPort, __LINE__);
    }
    if(p1->m_bPanelSwapOdd_ML != p2->m_bPanelSwapOdd_ML)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapOdd_ML, p2->m_bPanelSwapOdd_ML, __LINE__);
    }
    if(p1->m_bPanelSwapEven_ML != p2->m_bPanelSwapEven_ML)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapEven_ML, p2->m_bPanelSwapEven_ML, __LINE__);
    }
    if(p1->m_bPanelSwapOdd_RB != p2->m_bPanelSwapOdd_RB)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapOdd_RB, p2->m_bPanelSwapOdd_RB, __LINE__);
    }
    if(p1->m_bPanelSwapEven_RB != p2->m_bPanelSwapEven_RB)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapEven_RB, p2->m_bPanelSwapEven_RB, __LINE__);
    }
    if(p1->m_bPanelSwapLVDS_POL != p2->m_bPanelSwapLVDS_POL)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapLVDS_POL, p2->m_bPanelSwapLVDS_POL, __LINE__);
    }
    if(p1->m_bPanelSwapLVDS_CH != p2->m_bPanelSwapLVDS_CH)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapLVDS_CH, p2->m_bPanelSwapLVDS_CH, __LINE__);
    }
    if(p1->m_bPanelPDP10BIT != p2->m_bPanelPDP10BIT)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelPDP10BIT, p2->m_bPanelPDP10BIT, __LINE__);
    }
    if(p1->m_bPanelLVDS_TI_MODE != p2->m_bPanelLVDS_TI_MODE)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelLVDS_TI_MODE, p2->m_bPanelLVDS_TI_MODE, __LINE__);
    }
    if(p1->m_ucPanelDCLKDelay != p2->m_ucPanelDCLKDelay)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelDCLKDelay, p2->m_ucPanelDCLKDelay, __LINE__);
    }
    if(p1->m_bPanelInvDCLK != p2->m_bPanelInvDCLK)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelInvDCLK, p2->m_bPanelInvDCLK, __LINE__);
    }
    if(p1->m_bPanelInvDE != p2->m_bPanelInvDE)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelInvDE, p2->m_bPanelInvDE, __LINE__);
    }
    if(p1->m_bPanelInvHSync != p2->m_bPanelInvHSync)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelInvHSync, p2->m_bPanelInvHSync, __LINE__);
    }
    if(p1->m_bPanelInvVSync != p2->m_bPanelInvVSync)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelInvVSync, p2->m_bPanelInvVSync, __LINE__);
    }
    if(p1->m_ucPanelDCKLCurrent != p2->m_ucPanelDCKLCurrent)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelDCKLCurrent, p2->m_ucPanelDCKLCurrent, __LINE__);
    }
    if(p1->m_ucPanelDECurrent != p2->m_ucPanelDECurrent)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelDECurrent, p2->m_ucPanelDECurrent, __LINE__);
    }
    if(p1->m_ucPanelODDDataCurrent != p2->m_ucPanelODDDataCurrent)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelODDDataCurrent, p2->m_ucPanelODDDataCurrent, __LINE__);
    }
    if(p1->m_ucPanelEvenDataCurrent != p2->m_ucPanelEvenDataCurrent)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelEvenDataCurrent, p2->m_ucPanelEvenDataCurrent, __LINE__);
    }
    if(p1->m_wPanelOnTiming1 != p2->m_wPanelOnTiming1)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelOnTiming1, p2->m_wPanelOnTiming1, __LINE__);
    }
    if(p1->m_wPanelOnTiming2 != p2->m_wPanelOnTiming2)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelOnTiming2, p2->m_wPanelOnTiming2, __LINE__);
    }
    if(p1->m_wPanelOffTiming1 != p2->m_wPanelOffTiming1)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelOffTiming1, p2->m_wPanelOffTiming1, __LINE__);
    }
    if(p1->m_wPanelOffTiming2 != p2->m_wPanelOffTiming2)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelOffTiming2, p2->m_wPanelOffTiming2, __LINE__);
    }
    if(p1->m_ucPanelHSyncWidth != p2->m_ucPanelHSyncWidth)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelHSyncWidth, p2->m_ucPanelHSyncWidth, __LINE__);
    }
    if(p1->m_ucPanelHSyncBackPorch != p2->m_ucPanelHSyncBackPorch)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelHSyncBackPorch, p2->m_ucPanelHSyncBackPorch, __LINE__);
    }
    if(p1->m_ucPanelVSyncWidth != p2->m_ucPanelVSyncWidth)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelVSyncWidth, p2->m_ucPanelVSyncWidth, __LINE__);
    }
    if(p1->m_ucPanelVBackPorch != p2->m_ucPanelVBackPorch)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelVBackPorch, p2->m_ucPanelVBackPorch, __LINE__);
    }
    if(p1->m_wPanelHStart != p2->m_wPanelHStart)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelHStart, p2->m_wPanelHStart, __LINE__);
    }
    if(p1->m_wPanelVStart != p2->m_wPanelVStart)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelVStart, p2->m_wPanelVStart, __LINE__);
    }
    if(p1->m_wPanelWidth != p2->m_wPanelWidth)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelWidth, p2->m_wPanelWidth, __LINE__);
    }
    if(p1->m_wPanelHeight != p2->m_wPanelHeight)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelHeight, p2->m_wPanelHeight, __LINE__);
    }
    if(p1->m_wPanelMaxHTotal != p2->m_wPanelMaxHTotal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelMaxHTotal, p2->m_wPanelMaxHTotal, __LINE__);
    }
    if(p1->m_wPanelHTotal != p2->m_wPanelHTotal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelHTotal, p2->m_wPanelHTotal, __LINE__);
    }
    if(p1->m_wPanelMinHTotal != p2->m_wPanelMinHTotal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelMinHTotal, p2->m_wPanelMinHTotal, __LINE__);
    }
    if(p1->m_wPanelMaxVTotal != p2->m_wPanelMaxVTotal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelMaxVTotal, p2->m_wPanelMaxVTotal, __LINE__);
    }
    if(p1->m_wPanelVTotal != p2->m_wPanelVTotal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelVTotal, p2->m_wPanelVTotal, __LINE__);
    }
    if(p1->m_wPanelMinVTotal != p2->m_wPanelMinVTotal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wPanelMinVTotal, p2->m_wPanelMinVTotal, __LINE__);
    }
    if(p1->m_dwPanelMaxDCLK != p2->m_dwPanelMaxDCLK)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_dwPanelMaxDCLK, p2->m_dwPanelMaxDCLK, __LINE__);
    }
    if(p1->m_dwPanelDCLK != p2->m_dwPanelDCLK)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_dwPanelDCLK, p2->m_dwPanelDCLK, __LINE__);
    }
    if(p1->m_dwPanelMinDCLK != p2->m_dwPanelMinDCLK)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_dwPanelMinDCLK, p2->m_dwPanelMinDCLK, __LINE__);
    }
    if(p1->m_wSpreadSpectrumStep != p2->m_wSpreadSpectrumStep)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wSpreadSpectrumStep, p2->m_wSpreadSpectrumStep, __LINE__);
    }
    if(p1->m_wSpreadSpectrumSpan != p2->m_wSpreadSpectrumSpan)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_wSpreadSpectrumSpan, p2->m_wSpreadSpectrumSpan, __LINE__);
    }
    if(p1->m_ucDimmingCtl != p2->m_ucDimmingCtl)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucDimmingCtl, p2->m_ucDimmingCtl, __LINE__);
    }
    if(p1->m_ucMaxPWMVal != p2->m_ucMaxPWMVal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucMaxPWMVal, p2->m_ucMaxPWMVal, __LINE__);
    }
    if(p1->m_ucMinPWMVal != p2->m_ucMinPWMVal)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucMinPWMVal, p2->m_ucMinPWMVal, __LINE__);
    }
    if(p1->m_bPanelDeinterMode != p2->m_bPanelDeinterMode)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelDeinterMode, p2->m_bPanelDeinterMode, __LINE__);
    }
    if(p1->m_ucPanelAspectRatio != p2->m_ucPanelAspectRatio)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucPanelAspectRatio, p2->m_ucPanelAspectRatio, __LINE__);
    }
    if(p1->m_u16LVDSTxSwapValue != p2->m_u16LVDSTxSwapValue)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_u16LVDSTxSwapValue, p2->m_u16LVDSTxSwapValue, __LINE__);
    }
    if(p1->m_ucTiBitMode != p2->m_ucTiBitMode)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucTiBitMode, p2->m_ucTiBitMode, __LINE__);
    }
    if(p1->m_ucOutputFormatBitMode != p2->m_ucOutputFormatBitMode)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucOutputFormatBitMode, p2->m_ucOutputFormatBitMode, __LINE__);
    }
    if(p1->m_bPanelSwapOdd_RG != p2->m_bPanelSwapOdd_RG)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapOdd_RG, p2->m_bPanelSwapOdd_RG, __LINE__);
    }
    if(p1->m_bPanelSwapEven_RG != p2->m_bPanelSwapEven_RG)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapEven_RG, p2->m_bPanelSwapEven_RG, __LINE__);
    }
    if(p1->m_bPanelSwapOdd_GB != p2->m_bPanelSwapOdd_GB)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapOdd_GB, p2->m_bPanelSwapOdd_GB, __LINE__);
    }
    if(p1->m_bPanelSwapEven_GB != p2->m_bPanelSwapEven_GB)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelSwapEven_GB, p2->m_bPanelSwapEven_GB, __LINE__);
    }
    if(p1->m_bPanelDoubleClk != p2->m_bPanelDoubleClk)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelDoubleClk, p2->m_bPanelDoubleClk, __LINE__);
    }
    if(p1->m_dwPanelMaxSET != p2->m_dwPanelMaxSET)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_dwPanelMaxSET, p2->m_dwPanelMaxSET, __LINE__);
    }
    if(p1->m_dwPanelMinSET != p2->m_dwPanelMinSET)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_dwPanelMinSET, p2->m_dwPanelMinSET, __LINE__);
    }
    if(p1->m_ucOutTimingMode != p2->m_ucOutTimingMode)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_ucOutTimingMode, p2->m_ucOutTimingMode, __LINE__);
    }
    if(p1->m_bPanelNoiseDith != p2->m_bPanelNoiseDith)
    {
        printf("diff: '%u', '%u', at %u\n", p1->m_bPanelNoiseDith, p2->m_bPanelNoiseDith, __LINE__);
    }
}
#endif //PANEL_DEBUG
