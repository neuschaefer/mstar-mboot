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
#include <config.h>
#include <configs/uboot_board_config.h>
#include <MsTypes.h>

#include <MsCommon.h>
#include <MsVersion.h>
#if (ENABLE_MSTAR_KAISER==1) //K3
#include <apiPNL_EX.h>
#endif
#include <apiPNL.h>
#include <drvPWM.h>

#include <panel/MsDrvPanel.h>
#include <panel/Gamma12BIT_256.inc>
#include <MsApiPM.h>
#include <MsSystem.h>

#include <MsMmap.h>
#if(CONFIG_HDMITX_MSTAR_ROCKET ==1)
#include <apiHDMITx.h>
#endif

#if(ENABLE_URSA_6M30 == 1)
#include <ursa/ursa_6m30.h>
#endif
#if(ENABLE_URSA_8 == 1)
#include <ursa/ursa_8.h>
#endif
#if(ENABLE_URSA6_VB1 == 1 || ENABLE_NOVA_KS2 == 1)
#include <ursa/ursa_6m38.h>
#endif
#if(ENABLE_URSA7_VB1 == 1)
#include <ursa/ursa_7.h>
#endif
#include <mstarstr.h>

#define PWM_DUTY   "u32PWMDuty"
#define PWM_PERIOD "u32PWMPeriod"
#define PWM_DIVPWM "u16DivPWM"
#define MIRROR_ON "MIRROR_ON"
#define PWM_POLPWM "bPolPWM"
#define PWM_MAXPWM "u16MaxPWMvalue"
#define PWM_MINPWM "u16MinPWMvalue"
#define PWM_CH "pnl_pwmch"
#include <bootlogo/MsPoolDB.h>
#include <MsDebug.h>
//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
unsigned long lPanleTimer =0;
unsigned long lPanelOnTiming=0;
MS_BOOL bMst6m40Installed = FALSE;
#define URSA_DBG(x)   // x
#define MFC5_ONEBIN_DBG(x) // x
//--------------------------------------------------------------------------------------------------
// Local Variables
//--------------------------------------------------------------------------------------------------
static unsigned char PanelLinkExtType=10;


#if (CONFIG_XC_FRC_VB1)

#include <apiXC.h>

#endif

#if defined(CONFIG_A3_STB)
#include <drvTVEncoder.h>
#include <drvXC_IOPort.h>
#include <apiXC.h>
#include <apiXC_Adc.h>
#include <drvGPIO.h>
#include <apiGOP.h>



MS_BOOL mvideo_sc_is_interlace(void)
{
    return 0;
}

void verDispCvbs_Main(void)
{
    MS_Switch_VE_Dest_Info SwitchOutputDest;
    MS_VE_Output_Ctrl OutputCtrl;
    MS_VE_Set_Mode_Type SetModeType;
    //XC_INITDATA XC_InitData;
	MS_U16 u16OutputVfreq;
    U32 u32Addr;
	XC_INITDATA XC_InitData;
	GOP_InitInfo pGopInit;
	//xc init
	UBOOT_TRACE("IN\n");
	memset((void *)&XC_InitData, 0, sizeof(XC_InitData));
    MApi_XC_Init(&XC_InitData, 0);
	MApi_XC_SetDispWindowColor(0x82,MAIN_WINDOW);
	memset((void *)&pGopInit, 0, sizeof(pGopInit));
	MApi_GOP_RegisterXCIsInterlaceCB(mvideo_sc_is_interlace);
	MApi_GOP_Init(&pGopInit);
	MApi_GOP_GWIN_OutputColor(GOPOUT_YUV);

    MApi_GOP_SetGOPHStart(0, g_IPanel.HStart());
    MApi_GOP_SetGOPHStart(1, g_IPanel.HStart());
    if(get_addr_from_mmap("E_MMAP_ID_VE", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_MMAP_ID_VE fail\n");
        return -1;
    }
	MDrv_VE_Init(u32Addr);//MDrv_VE_Init(VE_BUFFER_ADDR);
	MApi_XC_SetOutputCapture(ENABLE, E_XC_OP2);     // Enable op2 to ve path

	u16OutputVfreq = MApi_XC_GetOutputVFreqX100()/10;
    if(u16OutputVfreq > 550)
    {
        //60 hz for NTSC
        MDrv_VE_SetOutputVideoStd(MS_VE_NTSC);
		SetModeType.u16InputVFreq = (3000 * 2) / 10;
    }
    else
    {
        //50 hz for PAL
        MDrv_VE_SetOutputVideoStd(MS_VE_PAL);
		SetModeType.u16InputVFreq = (2500 * 2) / 10;
    }


    MS_Switch_VE_Src_Info SwitchInputSrc;
    SwitchInputSrc.InputSrcType = MS_VE_SRC_SCALER;
    MDrv_VE_SwitchInputSource(&SwitchInputSrc);
	MDrv_VE_SetRGBIn(false);

    SwitchOutputDest.OutputDstType = MS_VE_DEST_CVBS;
    MDrv_VE_SwitchOuputDest(&SwitchOutputDest);

    SetModeType.u16H_CapSize     = g_IPanel.Width();
    SetModeType.u16V_CapSize     = g_IPanel.Height();
    SetModeType.u16H_CapStart    = g_IPanel.HStart();
    SetModeType.u16V_CapStart    = g_IPanel.VStart();
    SetModeType.u16H_SC_CapSize  = g_IPanel.Width();
    SetModeType.u16V_SC_CapSize  = g_IPanel.Height();
    SetModeType.u16H_SC_CapStart = g_IPanel.HStart();
    SetModeType.u16V_SC_CapStart = g_IPanel.VStart();

	SetModeType.bHDuplicate = FALSE;
	SetModeType.bSrcInterlace = FALSE;

    MDrv_VE_SetMode(&SetModeType);

    OutputCtrl.bEnable = TRUE;
    OutputCtrl.OutputType = MS_VE_OUT_TVENCODER;

    MDrv_VE_SetOutputCtrl(&OutputCtrl);
	MDrv_VE_SetBlackScreen(FALSE);
	MApi_XC_ADC_SetCVBSOut(ENABLE, OUTPUT_CVBS1, INPUT_SOURCE_DTV, TRUE);

    UBOOT_TRACE("OUT\n");

}
#endif

#define LVDS_OUTPUT_USER          4
#if(ENABLE_URSA_6M30 == 1)
#define PANEL_4K2K_ENABLE         0
#endif
#if (CONFIG_PANEL_INIT)

void SetPWM(U16 Period,U16 Duty,U16 PwmDiv,PWM_ChNum PWMPort)
{
    PWM_Result result = E_PWM_FAIL;

    U16 bPolPWM = 0;
    char *p_str=NULL;
#if ( CONFIG_VESTEL_MB97 == 1 )
    MS_BOOL bfEnvUpdate=FALSE;
#endif
    result = MDrv_PWM_Init(E_PWM_DBGLV_NONE);
    if(result == E_PWM_FAIL)
    {
        UBOOT_DEBUG("Sorry , init failed!~\n");
        return ;
    }
	p_str = getenv(PWM_POLPWM);
		if(p_str == NULL)
		{
			UBOOT_DEBUG("PWM_POLPWM in env is NULL,so use default value 0x1\n");
			setenv(PWM_POLPWM,"0x1");
#if ( CONFIG_VESTEL_MB97 == 1 )
			bfEnvUpdate = TRUE;
#endif
		}
		else
		{
			bPolPWM = simple_strtol(p_str, NULL, 16);
		}
		UBOOT_DEBUG("\nbPolPWM_T = %d\n",bPolPWM);
#if ( CONFIG_VESTEL_MB97 == 1 )
    if ( bfEnvUpdate == TRUE )
    {
        saveenv();
        bfEnvUpdate = FALSE;
    }
#else
        saveenv();
#endif
    //MDrv_PWM_UnitDiv(0); //duplicate  MDrv_PWM_Div
    MDrv_PWM_Oen(PWMPort, 0);    /* Set 0 for output enable */
    MDrv_PWM_Period(PWMPort, Period);
    MDrv_PWM_DutyCycle(PWMPort, Duty);
    MDrv_PWM_Div(PWMPort, PwmDiv);
	if(bPolPWM==1)
    MDrv_PWM_Polarity(PWMPort, TRUE);
	else
    MDrv_PWM_Polarity(PWMPort, FALSE);
    MDrv_PWM_Vdben(PWMPort, FALSE);
    MDrv_PWM_Dben(PWMPort,FALSE);
}

int PWM_init(void)
{
    U16 u32PWMDuty = 0;
    U16 u32PWMPeriod = 0;
    U16 u32PWMDIV = 0;
	U16 u16maxPWM = 5000; //give default max and min PWM value
	U16 u16minPWM = 5000;
	PWM_ChNum PWMPort = 0;
    char *p_str=NULL;
#if ( CONFIG_VESTEL_MB97 == 1 )
    MS_BOOL bfEnvUpdate=FALSE;
#endif
    // printf("getenv duty[%s]\n",getenv(PWM_DUTY));
    // printf("getenv period[%s]\n",getenv(PWM_PERIOD));
    p_str = getenv(PWM_DIVPWM);
    if(p_str == NULL)
    {
        UBOOT_DEBUG("PWM_DIVPWM in env is NULL,so use default value 0x1FF\n");
        setenv(PWM_DIVPWM,"0x1FF");
#if ( CONFIG_VESTEL_MB97 == 1 )
        bfEnvUpdate = TRUE;
#endif
    }
    else
    {
        u32PWMDIV = simple_strtol(p_str, NULL, 16);
    }

    p_str = getenv(PWM_PERIOD);
    if(p_str == NULL)
    {
        UBOOT_DEBUG("PWM_PERIOD in env is NULL,so use default value 0xC350\n");
        setenv(PWM_PERIOD,"0xC350");
#if ( CONFIG_VESTEL_MB97 == 1 )
        bfEnvUpdate = TRUE;
#endif
    }
    else
    {
        u32PWMPeriod = simple_strtol(p_str, NULL, 16);
    }

	p_str = getenv(PWM_MAXPWM);
	if(p_str == NULL)
	{
		UBOOT_DEBUG("PWM_MAXPWM in env is NULL,so use default value 0xC350\n");
		setenv(PWM_MAXPWM,"0xC350");
#if ( CONFIG_VESTEL_MB97 == 1 )
		bfEnvUpdate = TRUE;
#endif
	}
	else
	{
		u16maxPWM = simple_strtol(p_str, NULL, 16);
	}
	p_str = getenv(PWM_MINPWM);
	if(p_str == NULL)
	{
		UBOOT_DEBUG("PWM_MINPWM in env is NULL,so use default value 0xC350\n");
		setenv(PWM_MINPWM,"0xC350");
#if ( CONFIG_VESTEL_MB97 == 1 )
		bfEnvUpdate = TRUE;
#endif
	}
	else
	{
		u16minPWM = simple_strtol(p_str, NULL, 16);
	}

	p_str = getenv(PWM_CH);
	if( p_str == NULL )
	{
      UBOOT_DEBUG("PWM CH not specified ,So use default CH2\n");
      PWMPort = (PWM_ChNum)E_PWM_CH2;
	}
	else
	{
      PWMPort = (PWM_ChNum)simple_strtol(p_str, NULL, 16);
      if(PWMPort < 0 || PWMPort >9)
      {
        UBOOT_DEBUG("PWM CH out of range ,So use default CH2\n");
        PWMPort = (PWM_ChNum)E_PWM_CH2;
      }
	}
#if ( CONFIG_VESTEL_MB97 == 1 )
    if (bfEnvUpdate == TRUE )
    {
        saveenv();
        bfEnvUpdate = FALSE;
    }
#else
        saveenv();
#endif
    u32PWMDuty = (u16maxPWM+u16minPWM)/2;

    UBOOT_DEBUG("u32PWMPeriod_T = %d\n",u32PWMPeriod);
    UBOOT_DEBUG("u32PWMDuty_T = %d\n",u32PWMDuty);
    UBOOT_DEBUG("u32PWMDIV_T = %d\n",u32PWMDIV);
    UBOOT_DEBUG("u16maxPWM_T = %d\n",u16maxPWM);
    UBOOT_DEBUG("u16minPWM_T = %d\n",u16minPWM);

    SetPWM(u32PWMPeriod,u32PWMDuty, u32PWMDIV,PWMPort);
    return 0;
}


#if (ENABLE_TCON_PANEL == 1)
#include <MsOS.h>
#include <drvXC_IOPort.h>
#include <apiXC.h>
#include <panel/pnl_tcon_tbl.h>
#include <panel/pnl_tcon_tbl.c>


E_TCON_TAB_TYPE eTCONPNL_TypeSel = TCON_TABTYPE_GENERAL;
static void _MApi_TCon_Tab_DumpPSRegTab(MS_U8* pu8TconTab)
{
    #define TCON_DUMP_TIMEOUT_TIME  1000
    MS_U32 u32tabIdx = 0;
    MS_U32 u32Addr;
    MS_U16 u16Mask;
    MS_U16 u16Value;
    MS_U8 u8NeedDelay;
    MS_U8 u8DelayTime;
    MS_U32 u32StartTime = MsOS_GetSystemTime();
    UBOOT_TRACE("IN\n");


    if (pu8TconTab == NULL)
    {
        UBOOT_ERROR("pu8TconTab is NULL! at %s %u \n", __FUNCTION__, __LINE__);
        return;
    }

    while(1)
    {
        if( (MsOS_GetSystemTime() - u32StartTime) > TCON_DUMP_TIMEOUT_TIME )
        {
            UBOOT_ERROR("Dump tcon tab timeout! at %s %u \n", __FUNCTION__, __LINE__);
            return;
        }

        u32Addr     = ((pu8TconTab[u32tabIdx]<<8) + pu8TconTab[(u32tabIdx +1)]) & 0xFFFF;
        u16Mask     = pu8TconTab[(u32tabIdx +2)] & 0xFF;
        u16Value    = pu8TconTab[(u32tabIdx +3)] & 0xFF;
        u8NeedDelay = pu8TconTab[(u32tabIdx +4)] & 0xFF;
        u8DelayTime = pu8TconTab[(u32tabIdx +5)] & 0xFF;

        if (u32Addr == REG_TABLE_END) // check end of table
            break;

        u32Addr = (u32Addr | 0x100000);

        if( u32Addr == REG_TCON_BASE )
        {
            UBOOT_DEBUG("Wait V sync \n");
            MApi_XC_WaitOutputVSync(1, 50, MAIN_WINDOW);
        }

        if (u32Addr & 0x1)
        {
            u32Addr --;
            //temp_mask, need check!! MApi_PNL_Write2ByteMask(u32Addr, (u16Value << 8), (u16Mask << 8));//MApi_XC_Write2ByteMask
            MApi_XC_Write2ByteMask(u32Addr, (u16Value << 8), (u16Mask << 8));
            UBOOT_DEBUG("[Odd .addr=%04lx, msk=%02x, val=%02x] \n", u32Addr, (u16Mask << 8), (u16Value << 8));
        }
        else
        {
            MApi_XC_Write2ByteMask(u32Addr, u16Value, u16Mask);
            //temp_mask, need check!! MApi_PNL_Write2ByteMask(u32Addr, u16Value, u16Mask);//MApi_XC_Write2ByteMask
            UBOOT_DEBUG("[Even.addr=%04lx, msk=%02x, val=%02x] \n", u32Addr, u16Mask, u16Value);
        }
        // Check need delay?
        if( u8NeedDelay && u8DelayTime )
        {
            mdelay(u8DelayTime);
        }
        u32tabIdx = u32tabIdx + 7;
    }
    UBOOT_TRACE("OK\n");
}


static void _MApi_XC_Sys_Init_TCON_Panel(TCON_TAB_INFO* pTcontab)
{
    // TCON init
    MApi_PNL_TCON_Init();

    // dump TCON general register tab
    MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInitTab, E_APIPNL_TCON_TAB_TYPE_GENERAL);

    // dump TCON mod register tab
    MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInit_MODTab, E_APIPNL_TCON_TAB_TYPE_MOD);

    // dump TCON GPIO register tab
    MApi_PNL_TCONMAP_DumpTable(pTcontab->pTConInit_GPIOTab, E_APIPNL_TCON_TAB_TYPE_GPIO);

    // dump TCON gamma register tab
    #if 0
    {
        _MApi_XC_Sys_Init_TCON_GAMMA(pTcontab->pTConGammaTab);
    }
    #endif

    _MApi_TCon_Tab_DumpPSRegTab(pTcontab->pTConPower_Sequence_OnTab);

}

static void Init_TCON_Panel(void)
{
    UBOOT_TRACE("IN\n");
    TCON_TAB_INFO* pTcontab = &(TConMAP_Main[eTCONPNL_TypeSel]);
    _MApi_XC_Sys_Init_TCON_Panel(pTcontab);
    UBOOT_TRACE("OK\n");
}

#endif

#if defined(PCB_WITH_MFC)//MB100_BRINGUP
#include <apiSWI2C.h>

void MDrv_Ursa_6M40_I2CCheck(void)
{
    MS_BOOL bResult = FALSE;
    MS_U8 pBuffer[7] = { 0x00,  0x00,  0x00, 0x00, 0x00, 0x00, 0x00};
    SWI2C_BusCfg Ursa_6m40_I2cBusCfg[1]=
    {
        {PAD_DDCR_CK, PAD_DDCR_DA, 400}
    };

    MApi_SWI2C_Init(Ursa_6m40_I2cBusCfg, 1);

    bResult = MApi_SWI2C_ReadBytes (0x40, 0, NULL, 7, pBuffer);

    if(bResult)
    {
        UBOOT_DEBUG("[mboot]MFC I2C OK\n");
        bMst6m40Installed = TRUE;
    }
    else
    {
        UBOOT_DEBUG("[mboot]MFC I2C NOK\n");
        bMst6m40Installed = FALSE;
    }
}

#endif
#if (CONFIG_3D_HWLVDSLRFLAG)
static void PNL_Set3D_HWLVDSLRFlag(void)
{
    MS_PNL_HW_LVDSResInfo lvdsresinfo;
    lvdsresinfo.bEnable = 1;
    lvdsresinfo.u16channel = 0x03; // channel A: BIT0, channel B: BIT1,
    lvdsresinfo.u32pair = 0x18; // pair 0: BIT0, pair 1: BIT1, pair 2: BIT2, pair 3: BIT3, pair 4: BIT4, etc ...

    MApi_PNL_HWLVDSReservedtoLRFlag(lvdsresinfo);
}
#endif

MS_BOOL MsDrv_PNL_Init(PanelType*  panel_data)
{
	MS_BOOL ret=TRUE;
	char* s=NULL;
	MS_U16 u16PanelDCLK=0;
    UBOOT_TRACE("IN\n");

    UNUSED(s);
    UNUSED(u16PanelDCLK);

#if defined(PCB_WITH_MFC) //MB100_BRINGUP
    MDrv_Ursa_6M40_I2CCheck();
#endif

    #if (CONFIG_VESTEL_MB97 == 1)
	MApi_PNL_PreInit(E_PNL_CLK_ONLY);
    #else
	MApi_PNL_PreInit(E_PNL_NO_OUTPUT);
    #endif

	MApi_PNL_SkipTimingChange(FALSE);

    if (panel_data->m_ePanelLinkType == LINK_TTL)
    {
        UBOOT_DEBUG("Panle Link Type=LINK_TTL \n");
        MApi_BD_LVDS_Output_Type(LVDS_OUTPUT_USER);
        MApi_PNL_MOD_OutputConfig_User(0, 0, 0);
    }
    else if(panel_data->m_ePanelLinkType == LINK_LVDS)
    {
        #if (CONFIG_VESTEL_MB97 == 1)
        MApi_PNL_MOD_OutputConfig_User(0x0000, 0x0555, 0x0000);
        #else
        MApi_PNL_MOD_OutputConfig_User(0x5555, 0x0555, 0x0000);
        #endif
        MApi_BD_LVDS_Output_Type(panel_data->m_bPanelDualPort ? 0 : 4); // LVDS_SINGLE_OUTPUT_B
        UBOOT_DEBUG("Panle Link Type=LINK_LVDS \n");
    }
    else if(panel_data->m_ePanelLinkType == LINK_EXT)
    {
        UBOOT_DEBUG("Panle Link Type=LINK_EXT \n");
        UBOOT_DEBUG("Link Ext Type=%u \n", getLinkExtType());

        MApi_PNL_SetLPLLTypeExt(getLinkExtType());
#if(ENABLE_MSTAR_NAPOLI==1 || ENABLE_MSTAR_NIKE==1)
        if((LINK_VBY1_8BIT_8LANE<getLinkExtType()) || (LINK_VBY1_10BIT_4LANE>getLinkExtType()))
        {
            MApi_PNL_PreInit(E_PNL_CLK_DATA);
        }
#endif
#if ((CONFIG_XC_FRC_VB1==1||CONFIG_URSA6_VB1 ==1 || CONFIG_URSA9_VB1 == 1 || CONFIG_URSA7_VB1 == 1))&&(!defined(CONFIG_MSTAR_MONACO))
        if(LINK_VBY1_10BIT_8LANE==getLinkExtType())
        {
            MApi_PNL_MOD_OutputConfig_User(0x5500, 0x0055, 0x0000);
            MApi_BD_LVDS_Output_Type(4); // LVDS_SINGLE_OUTPUT_B
            MApi_PNL_ForceSetPanelDCLK((panel_data->m_dwPanelDCLK *2),TRUE); //4k2k
            MApi_PNL_Init_MISC(E_APIPNL_MISC_4K2K_ENABLE_60HZ);
            UBOOT_DEBUG("VB1 Link Type=LINK_VBY1_10BIT_8LANE \n");

        }
        else if(LINK_VBY1_10BIT_2LANE==getLinkExtType())
        {
            MApi_PNL_MOD_OutputConfig_User(0x0500, 0x0000, 0x0000);
            MApi_BD_LVDS_Output_Type(4); // LVDS_SINGLE_OUTPUT_B
            UBOOT_DEBUG("VB1 Link Type=LINK_VBY1_10BIT_2LANE \n");

        }
        else if(LINK_VBY1_10BIT_4LANE==getLinkExtType())
        {
            MApi_PNL_MOD_OutputConfig_User(0x5500, 0x0000, 0x0000);
            MApi_BD_LVDS_Output_Type(4); // LVDS_SINGLE_OUTPUT_B
            MApi_PNL_ForceSetPanelDCLK((panel_data->m_dwPanelDCLK *2),TRUE); //4k2k

            UBOOT_DEBUG("VB1 Link Type=LINK_VBY1_10BIT_4LANE \n");
        }
#elif (ENABLE_MSTAR_MONACO) || (ENABLE_MSTAR_MUJI) || (ENABLE_MSTAR_CELTICS)
        if(LINK_VBY1_10BIT_8LANE==getLinkExtType())
        {
            #if(MS_BOARD_TYPE_SEL == BD_MST205A_D01A_S_MONACO) //MB100_BRINGUP
            MApi_PNL_MOD_OutputConfig_User(0x5555, 0x0000, 0x0000); //for G6 direct output 8 via ch0-ch7
            UBOOT_DEBUG("[mboot]G6 output is Vx1 on demo board\n");
            #elif(MS_BOARD_TYPE_SEL == BD_MB100_120814R1)
            if(bMst6m40Installed==0)
            {
                MApi_PNL_MOD_OutputConfig_User(0x5550, 0x0005, 0x0000); //for G6 direct output 8 via ch2-ch9
                UBOOT_DEBUG("[mboot]G6 output is Vx1\n");
            }
            else
            {
                MApi_PNL_MOD_OutputConfig_User(0x5555, 0x0055, 0x0000); //for G6 output 8v+4o to MFC9 via ch0-ch7 ch8-ch11
                UBOOT_DEBUG("[mboot]G6 output is Vx1 w/MFC9\n");
            }
            #else
            MApi_PNL_MOD_OutputConfig_User(0x5555, 0x0055, 0x0000);
            #endif
            MApi_BD_LVDS_Output_Type(4); // LVDS_SINGLE_OUTPUT_B
            MApi_PNL_ForceSetPanelDCLK((panel_data->m_dwPanelDCLK *2),TRUE); //4k2k
            MApi_PNL_Init_MISC(E_APIPNL_MISC_4K2K_ENABLE_60HZ);
            UBOOT_DEBUG("VB1 Link Type=LINK_VBY1_10BIT_8LANE \n");
        }
#endif
    }

#if (ENABLE_HDMITX_MSTAR_ROCKET==1)
    char * p_str = NULL;
    int u8ResolutionEnv = -1;
    MApi_BD_LVDS_Output_Type(4); // LVDS_SINGLE_OUTPUT_B
    MApi_PNL_MOD_OutputConfig_User(0x1550, 0x0155, 0x0000);
    MApi_PNL_Init_MISC(E_APIPNL_MISC_SKIP_T3D_CONTROL|E_APIPNL_MISC_ENABLE_MANUAL_VSYNC_CTRL);
    p_str = getenv ("resolution");
    if(NULL != p_str)
    {
        u8ResolutionEnv = (int)simple_strtol(p_str, NULL, 10);
        UBOOT_DEBUG("ROCKET Link Type=%d \n",u8ResolutionEnv);

        if(u8ResolutionEnv==HDMITX_RES_4K2Kp_30Hz || u8ResolutionEnv==HDMITX_RES_4K2Kp_25Hz)
        {
            MApi_PNL_SetLPLLTypeExt(getLinkExtType());
            MApi_PNL_PreInit(E_PNL_CLK_DATA);
            MApi_PNL_ForceSetPanelDCLK((panel_data->m_dwPanelDCLK *2),TRUE);
            UBOOT_DEBUG("ROCKET Link Type=E_HAL_LTH_OUTPUT_4K2K \n");
        }
    }

#endif

#if (ENABLE_MSTAR_KAISER==0 && ENABLE_MSTAR_KAISERIN ==0 && ENABLE_MSTAR_KENYA == 0 && ENABLE_MSTAR_KERES==0 && ENABLE_MSTAR_KRITI==0 && ENABLE_MSTAR_CLIPPERS==0 && CONFIG_VESTEL_MB100==0 && CONFIG_VESTEL_MB97==0 )
    MApi_PNL_On(panel_data->m_wPanelOnTiming1);//Power on TCON and Delay Timming1
#endif

	MApi_PNL_Init(panel_data);

#if(MS_BOARD_TYPE_SEL == BD_MB100_120814R1) //MB100_BRINGUP
    if(panel_data->m_ePanelLinkType==LINK_EXT)
    {
        if(bMst6m40Installed==0)
        {
            //MApi_PNL_Init() will overwrite those setting
            //for G6 direct output 8 via ch2-ch9
            if(panel_data->m_bPanelDualPort )
            { // 2 division (VES480QNSS)
//                MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER,
//                                                                             0x4000, 0x5162, 0x0073, 0x0000);
                HAL_SYS_Write2Byte(0x103210, 0x4000);
                HAL_SYS_Write2Byte(0x103212, 0x5162);
                HAL_SYS_Write2Byte(0x103214, 0x0073);
            }
            else
            { // 1 divition
//                MApi_PNL_MOD_OutputChannelOrder(APIPNL_OUTPUT_CHANNEL_ORDER_USER,
//                                                                             0x1000, 0x3254, 0x0076, 0x0000);
                HAL_SYS_Write2Byte(0x103210, 0x1000);
                HAL_SYS_Write2Byte(0x103212, 0x3254);
                HAL_SYS_Write2Byte(0x103214, 0x0076);
            }
            HAL_SYS_Write2Byte(0x111E74, (HAL_SYS_Read2Byte(0x111E74)&0x0FFF)); //bit15:12=0
        }
    }
#endif

#if ((CONFIG_XC_FRC_VB1==1||CONFIG_URSA6_VB1 ==1 || CONFIG_URSA9_VB1 == 1 || CONFIG_URSA7_VB1 == 1))&&(!defined(CONFIG_MSTAR_MONACO))
     MApi_PNL_Control_Out_Swing(600);
#endif

        g_IPanel.Dump();
        g_IPanel.SetGammaTbl(E_APIPNL_GAMMA_12BIT, tAllGammaTab, GAMMA_MAPPING_MODE);
#if(ENABLE_URSA_6M30 == 1)
        if(PANEL_4K2K_ENABLE == 1)
        {
            MDrv_WriteByte(0x1032B5, 0xF0);  //LR Flag Send From LVDS Dummy Pixel
        }

        if(bMst6m30Installed)
        {
            ret=MApi_PNL_PreInit(E_PNL_CLK_DATA);
            MApi_PNL_SetOutput(E_APIPNL_OUTPUT_CLK_DATA);
            g_IPanel.Enable(TRUE);
            MApi_PNL_On(panel_data->m_wPanelOnTiming1);//Power on TCON and Delay Timming1
            MDrv_Ursa_6M30_LVDS_Enalbe(TRUE);//run_command("ursa_lvds_on", 0);
            PWM_init();
            MApi_PNL_On(panel_data->m_wPanelOnTiming2);//Delay Timming2
            lPanelOnTiming=panel_data->m_wPanelOnTiming2;
            lPanleTimer=MsSystemGetBootTime();
        }
        else
#endif
        {
            #if (ENABLE_MSTAR_KAISER==0 && ENABLE_MSTAR_KAISERIN ==0 && ENABLE_MSTAR_KENYA == 0 && ENABLE_MSTAR_KERES==0 && ENABLE_MSTAR_KRITI==0 && ENABLE_MSTAR_CLIPPERS==0)

            #if defined (CONFIG_URSA9_VB1) && (CONFIG_URSA9_VB1 == 1)
                if (LINK_VBY1_10BIT_2LANE == getLinkExtType())
                    MDrv_Ursa_9_Set_Lane_VB1_per_init(2, 2);
                else if (LINK_VBY1_10BIT_4LANE == getLinkExtType())
                    MDrv_Ursa_9_Set_Lane_VB1_per_init(4, 4);
            #elif defined (CONFIG_URSA7_VB1) && (CONFIG_URSA7_VB1 == 1)
                MDrv_Ursa_7_Set_2_lane_VB1_per_init();
            #endif

            ret=MApi_PNL_PreInit(E_PNL_CLK_DATA);
            #if defined(CONFIG_NOVA_KS2)
            MDrv_KS2_Panel_Unlock();
            if(panel_data->m_wPanelWidth == 3840 && panel_data->m_wPanelHeight == 2160)
            {
                MDrv_KS2_Panel_Bootlogo(1);
            }
            else
            {
                MDrv_KS2_Panel_Bootlogo(0);
                MDrv_KS2_Panel_AutoMuteMode();
            }
            #endif

            #if (ENABLE_MSTAR_AMBER1 == 1) || (ENABLE_MSTAR_MACAW12 == 1)
            MApi_PNL_SetOutput(E_APIPNL_OUTPUT_CLK_DATA);
            #endif
            PWM_init();
          #if defined(PCB_WITH_MFC) //for MB100 and MB98
            if(bMst6m40Installed == TRUE)
            {
                 if(IsBootLogoValid() == TRUE) //bootlogo exist
                    g_IPanel.Enable(TRUE);
            }
            else
          #endif
            {
                if(IsBootLogoValid() == TRUE) //bootlogo exist //MB97, MB100 no ursa case
                    MApi_PNL_En(TRUE, panel_data->m_wPanelOnTiming2);//Delay Timming2
            }
          #if(MS_BOARD_TYPE_SEL == BD_MB100_120814R1)
            if(IsBootLogoValid() == FALSE)
                MApi_LPLL_On(TRUE);
          #endif
            lPanelOnTiming=panel_data->m_wPanelOnTiming2;
            lPanleTimer=MsSystemGetBootTime();
		#endif

        #if (ENABLE_TCON_PANEL == 1)
            if(MApi_XC_Init(NULL, 0) == TRUE)
            {
                //Fix back porch for TCON
                XC_PANEL_INFO_EX stPanelInfoEx;
                memset(&stPanelInfoEx, 0, sizeof(XC_PANEL_INFO_EX));
                stPanelInfoEx.u32PanelInfoEx_Version = PANEL_INFO_EX_VERSION;
                stPanelInfoEx.u16PanelInfoEX_Length = sizeof(XC_PANEL_INFO_EX);
                stPanelInfoEx.bVSyncBackPorchValid = TRUE;
                stPanelInfoEx.u16VSyncBackPorch = panel_data->m_ucPanelVBackPorch; //set back porch value
                stPanelInfoEx.u16VFreq = 500; //this step setting info is only for 50hz
                if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
                    UBOOT_DEBUG("---%s:%d Set ExPanel Info OK\n", __FUNCTION__, __LINE__);
                else
                    UBOOT_ERROR("---%s:%d Set ExPanel Info Fail\n", __FUNCTION__, __LINE__);

                stPanelInfoEx.u16VFreq = 600; //set same setting for 60hz
                if(MApi_XC_SetExPanelInfo(TRUE, &stPanelInfoEx))//Check the set is accepted or not
                    UBOOT_DEBUG("---%s:%d Set ExPanel Info OK\n", __FUNCTION__, __LINE__);
                else
                    UBOOT_ERROR("---%s:%d Set ExPanel Info Fail\n", __FUNCTION__, __LINE__);

                Init_TCON_Panel();
            }
            else
            {
                UBOOT_DEBUG("xc Init failed....\n");
            }
    	#endif


        }

#if (defined(CONFIG_A3_STB))
    verDispCvbs_Main();
#endif

    #if (CONFIG_3D_HWLVDSLRFLAG)
    PNL_Set3D_HWLVDSLRFlag();
    #endif
    UBOOT_TRACE("OK\n");

#if (ENABLE_MSTAR_KAISER==1) //K3
	PNL_DeviceId stPNL_DeviceId = {0, 1}; // SC1 PNL device ID
	MApi_PNL_EX_SkipTimingChange(&stPNL_DeviceId, FALSE);
	MApi_PNL_EX_Init(&stPNL_DeviceId, (PNL_EX_PanelType*)panel_data);
#endif
#if (CONFIG_XC_FRC_VB1==1)
        MDrv_XC_Sys_Init_XC();
#endif
#if defined (CONFIG_URSA9_VB1) && (CONFIG_URSA9_VB1 == 1)
    if (LINK_VBY1_10BIT_2LANE == getLinkExtType())
        MDrv_Ursa_9_Set_Lane_VB1(1920, panel_data->m_wPanelWidth);
    else if (LINK_VBY1_10BIT_4LANE == getLinkExtType())
        MDrv_Ursa_9_Set_Lane_VB1(3840, panel_data->m_wPanelWidth);
#elif defined (CONFIG_URSA7_VB1) && (CONFIG_URSA7_VB1 == 1)
    MDrv_Ursa_7_Set_2_lane_VB1();
#endif

#if defined(PCB_WITH_MFC) && (MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S)
    ursa5_cmd_table cmd_table={0};
    if(Read_Ursa5ParaFromflash(&cmd_table)==0)
        MDrv_Ursa_6M30_Init(&cmd_table);
#endif

	return ret;

}

void MsDrv_PNL_BackLigth_On(void)
{
	UBOOT_TRACE("IN\n");
    unsigned long lpanelDelayTime=0;
	unsigned long ltotalTime=MsSystemGetBootTime();
#if ((CONFIG_VESTEL_MB100 == 1) || (CONFIG_VESTEL_MB97 == 1))
    if ((IsBootLogoValid() == TRUE) && (bMst6m40Installed == FALSE))
    {//if no Ursa and there is bootlogo
    #if (CONFIG_VESTEL_MB100 == 1)
        if(ltotalTime > lPanleTimer)
        {
            unsigned long ltimeDiff = 0;
            ltimeDiff = ltotalTime-lPanleTimer;
            if(lPanelOnTiming > ltimeDiff)
            {
                lpanelDelayTime=(lPanelOnTiming-(ltimeDiff));
                MApi_PNL_Delay(lpanelDelayTime);
            }
        }

    #endif

        MApi_PNL_SetBackLight(BACKLITE_INIT_SETTING);//Power on backlight
    }
#else
	if(lPanelOnTiming>(ltotalTime-lPanleTimer))
	{
		lpanelDelayTime=(lPanelOnTiming-(ltotalTime-lPanleTimer));

		mdelay(lpanelDelayTime);
		printf("\n---%s:%d Set MsDrv_PNL_BackLigth_On DelayTask %lu \n", __FUNCTION__, __LINE__,lpanelDelayTime);
	}
	else
	{
		UBOOT_DEBUG("\n---%s:%d Set MsDrv_PNL_BackLigth_On No Delay \n", __FUNCTION__, __LINE__);

	}
	if(FALSE == pm_check_back_ground_active())
	{
		MApi_PNL_SetBackLight(BACKLITE_INIT_SETTING);//Power on backlight
	}
	else
	{
		MApi_PNL_SetBackLight(DISABLE);
	}
    #endif
	UBOOT_TRACE("OK\n");

}

void setLinkExtType(APIPNL_LINK_EXT_TYPE linkExtType)
{
    PanelLinkExtType=linkExtType;
}
APIPNL_LINK_EXT_TYPE getLinkExtType(void)
{
    return PanelLinkExtType;
}


#if (CONFIG_XC_FRC_VB1==1)

int MDrv_XC_Sys_Init_XC(void)
{
    XC_INITDATA sXC_InitData;
    XC_INITDATA *pstXC_InitData= &sXC_InitData;
    XC_INITMISC sXC_Init_Misc;
    U32 u32Addr=0,u32Size=0;


    // reset to zero

    memset(&sXC_InitData, 0, sizeof(sXC_InitData));
    memset(&sXC_Init_Misc, 0, sizeof(XC_INITMISC));

    // Init XC
#if 1// (OBA2!=1) // remove when XC driver update
    // Check library version. Do not modify this statement please.
    pstXC_InitData->u32XC_version = XC_INITDATA_VERSION;
#endif
    pstXC_InitData->u32XTAL_Clock = MST_XTAL_CLOCK_HZ;
#if 1


	if(get_addr_from_mmap("E_MMAP_ID_XC_MAIN_FB", &u32Addr)!=0)
	{
		UBOOT_ERROR("get E_MMAP_ID_XC_MAIN_FB mmap fail\n");
	}
	if(u32Addr==0xFFFF)
	{
		UBOOT_ERROR("get E_MMAP_ID_XC_MAIN_FB mmap fail\n");
		return -1;
	}
    get_length_from_mmap("E_MMAP_ID_XC_MAIN_FB", (U32 *)&u32Size);

#if 0

    /* E_MMAP_ID_XC_MAIN_FB   */
    //co_buffer L0
#define E_MMAP_ID_XC_MAIN_FB_AVAILABLE                         0x000C380000
#define E_MMAP_ID_XC_MAIN_FB_ADR                               0x000C380000  //Alignment 0
#define E_MMAP_ID_XC_MAIN_FB_GAP_CHK                           0x0000000000
#define E_MMAP_ID_XC_MAIN_FB_LEN                               0x0003000000
#define E_MMAP_ID_XC_MAIN_FB_MEMORY_TYPE                       (MIU1 | TYPE_NONE | UNCACHE

#endif
    pstXC_InitData->u32Main_FB_Size = u32Size; //SCALER_DNR_BUF_LEN;
    pstXC_InitData->u32Main_FB_Start_Addr = u32Addr;//((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));

    // Init DNR Address in Main & Sub channel. Keep the same. If project support FB PIP mode, set Sub DNR Address in AP layer (eg. mapp_init).
    pstXC_InitData->u32Sub_FB_Size = pstXC_InitData->u32Main_FB_Size;
    pstXC_InitData->u32Sub_FB_Start_Addr = pstXC_InitData->u32Main_FB_Start_Addr;

    // Chip related.
    pstXC_InitData->bIsShareGround = ENABLE;
#endif

#if 1 // (OBA2!=1) // remove when XC driver update
    // Board related
    pstXC_InitData->eScartIDPort_Sel = SCART_ID_SEL;//SCART_ID_SEL | SCART2_ID_SEL ;
#endif
    pstXC_InitData->bCEC_Use_Interrupt = FALSE;

    pstXC_InitData->bEnableIPAutoCoast = 0;

    pstXC_InitData->bMirror = FALSE;


    // panel info
    pstXC_InitData->stPanelInfo.u16HStart = g_IPanel.HStart();      // DE H start
    pstXC_InitData->stPanelInfo.u16VStart = g_IPanel.VStart();
    pstXC_InitData->stPanelInfo.u16Width  = g_IPanel.Width();
    pstXC_InitData->stPanelInfo.u16Height = g_IPanel.Height();
    pstXC_InitData->stPanelInfo.u16HTotal = g_IPanel.HTotal();
    pstXC_InitData->stPanelInfo.u16VTotal = g_IPanel.VTotal();

    pstXC_InitData->stPanelInfo.u16DefaultVFreq = g_IPanel.DefaultVFreq();

    pstXC_InitData->stPanelInfo.u8LPLL_Mode = g_IPanel.LPLL_Mode();
    pstXC_InitData->stPanelInfo.enPnl_Out_Timing_Mode = (E_XC_PNL_OUT_TIMING_MODE)(g_IPanel.OutTimingMode());

    pstXC_InitData->stPanelInfo.u16DefaultHTotal = g_IPanel.HTotal();
    pstXC_InitData->stPanelInfo.u16DefaultVTotal = g_IPanel.VTotal();
    pstXC_InitData->stPanelInfo.u32MinSET = g_IPanel.MinSET();
    pstXC_InitData->stPanelInfo.u32MaxSET = g_IPanel.MaxSET();
    pstXC_InitData->stPanelInfo.eLPLL_Type = (E_XC_PNL_LPLL_TYPE) g_IPanel.LPLL_Type();
    //printf("%s, %d, pstXC_InitData->stPanelInfo.eLPLL_Type=%u\n", __FUNCTION__, __LINE__, pstXC_InitData->stPanelInfo.eLPLL_Type);
    pstXC_InitData->bDLC_Histogram_From_VBlank = FALSE;

    if (  MApi_XC_GetCapability(E_XC_SUPPORT_IMMESWITCH)  )
    {
        sXC_Init_Misc.u32MISC_A |= E_XC_INIT_MISC_A_IMMESWITCH;
    }

    if ( MApi_XC_GetCapability(E_XC_SUPPORT_FRC_INSIDE) && 1 )
    {
        sXC_Init_Misc.u32MISC_A |= E_XC_INIT_MISC_A_FRC_INSIDE;
    }
// TODO: =====Start Temp function=====//After Interface/Struct definition are fixed, remove these!!

    if(sXC_Init_Misc.u32MISC_A & E_XC_INIT_MISC_A_FRC_INSIDE)
    {
        XC_PREINIT_INFO_t stXC_PANEL_INFO_ADV;
        memset(&stXC_PANEL_INFO_ADV, 0, sizeof(XC_PREINIT_INFO_t));

        stXC_PANEL_INFO_ADV.u8PanelHSyncWidth      = g_IPanel.HSynWidth();
        stXC_PANEL_INFO_ADV.u8PanelHSyncBackPorch  = g_IPanel.HSynBackPorch();
        stXC_PANEL_INFO_ADV.u8PanelVSyncWidth      = MApi_XC_GetPanelSpec(MApi_PNL_GetPnlTypeSetting())->m_ucPanelVSyncWidth;
        stXC_PANEL_INFO_ADV.u8PanelVSyncBackPorch  = g_IPanel.VSynBackPorch();
        stXC_PANEL_INFO_ADV.u16VTrigX              = 0x82F;
            stXC_PANEL_INFO_ADV.u16VTrigY              = (g_IPanel.VStart()+g_IPanel.Height()+12)%(MApi_XC_GetPanelSpec(MApi_PNL_GetPnlTypeSetting())->m_wPanelVTotal);//0x45B;

        // �ڧ�Memory�������ª�code����, �s�����u�ݭn�@��memory
        #if 0

        /* E_MMAP_ID_FRC_4K2K   */
        //co_buffer L0
        #define E_MMAP_ID_FRC_4K2K_AVAILABLE                           0x000FE00000
        #define E_MMAP_ID_FRC_4K2K_ADR                                 0x000FE00000  //Alignment 0x100000
        #define E_MMAP_ID_FRC_4K2K_GAP_CHK                             0x0000000000
        #define E_MMAP_ID_FRC_4K2K_LEN                                 0x0002800000
        #define E_MMAP_ID_FRC_4K2K_MEMORY_TYPE                         (MIU1 | TYPE_NONE | UNCACHE)


        #endif
        if(get_addr_from_mmap("E_MMAP_ID_FRC_4K2K", &u32Addr)!=0)
	    {
		    UBOOT_ERROR("get E_MMAP_ID_FRC_4K2K mmap fail\n");
	    }
	    if(u32Addr==0xFFFF)
	    {
		    UBOOT_ERROR("get E_MMAP_ID_FRC_4K2K mmap fail\n");
		    return -1;
	    }
        get_length_from_mmap("E_MMAP_ID_FRC_4K2K", (U32 *)&u32Size);
        stXC_PANEL_INFO_ADV.FRCInfo.u32FRC_MEMC_MemAddr    = u32Addr;  //?�o�O��FRC�һݪ�memory
        stXC_PANEL_INFO_ADV.FRCInfo.u32FRC_MEMC_MemSize    = u32Size;


        stXC_PANEL_INFO_ADV.FRCInfo.u16FB_YcountLinePitch  = 0x00;
        stXC_PANEL_INFO_ADV.FRCInfo.u16PanelWidth          = g_IPanel.Width();
        stXC_PANEL_INFO_ADV.FRCInfo.u16PanelHeigh          = g_IPanel.Height();
        stXC_PANEL_INFO_ADV.FRCInfo.u8FRC3DPanelType       = E_XC_3D_PANEL_NONE;

        stXC_PANEL_INFO_ADV.FRCInfo.bFRC                   = TRUE; // TRUE: Normal; FALSE: Bypass
        stXC_PANEL_INFO_ADV.FRCInfo.u83Dmode               = 0x00;
        stXC_PANEL_INFO_ADV.FRCInfo.u8IpMode               = 0x00;
        stXC_PANEL_INFO_ADV.FRCInfo.u8MirrorMode           = 0x00;
        stXC_PANEL_INFO_ADV.FRCInfo.u32FRC_FrameSize       = 0;
        stXC_PANEL_INFO_ADV.FRCInfo.u83D_FI_out            = 0;

        MApi_XC_PreInit( E_XC_PREINIT_FRC, &stXC_PANEL_INFO_ADV, sizeof(XC_PREINIT_INFO_t) );
        pstXC_InitData->stPanelInfo.u8LPLL_Mode = 2; // Quad mode

    }
// TODO: =====End of Temp Function=====


        if(MApi_XC_Init(pstXC_InitData, sizeof(XC_INITDATA)) == FALSE)
    {
        printf("L:%d, XC_Init failed because of InitData wrong, please update header file and compile again\n", __LINE__);
    }

#if 1

    if (is_str_resume() == 1)
    {
       MApi_XC_FRC_Mute(TRUE);
    }

        if(MApi_XC_Init_MISC(&sXC_Init_Misc, sizeof(XC_INITMISC)) == FALSE)
    {
        printf("L:%d, XC Init MISC failed because of InitData wrong, please update header file and compile again\n", __LINE__);
    }

    // Init Gamma table
#endif
    return 1;

}
#endif

#endif

#if defined(PCB_WITH_MFC)
#define URSA_6M40_CMD_DATA_SUM          (7)
#define URSA_6M40_I2C_BUS_NUM           (2)
#define URSA_6M40_DDC2BI_MODE_ADDR		(0x40)
#define URSA_6M40_I2C_SUB_ADDR          (0)
#define URSA_6M40_CMD_RETRY_TIMES       (3)
#define URSA_6M40_CMD_INTERVAL_TIME     (50)
#define URSA_6M40_CMD_Delay(x)          udelay(x*1000)
typedef enum
{
    CMD_6M40_OSD_MUTE,
    CMD_6M40_OSD_ON,
    CMD_6M40_OSD_OFF,
    CMD_6M40_OSD_UNMUTE,
    CMD_6M40_LVDS_ON,
    CMD_6M40_LVDS_OFF,
    CMD_6M40_2K_MODE_ON,
    CMD_6M40_4K_MODE_ON,
    //sword add
    CMD_6M40_OSD_PROTECT_OFF,
    CMD_6M40_OSD_PROTECT_ON,
    CMD_6M40_OSD_PROTECT_ON_EMMC
}URSA_6M40_CMD_TYPE;
MS_BOOL MDrv_Ursa_6M40_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_WriteBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}
MS_BOOL MDrv_Ursa_6M40_Write_Cmd(MS_U8 *pu8CmdData)
{
    MS_U16 u16BusNumSlaveID = URSA_6M40_DDC2BI_MODE_ADDR;
    MS_U8 u8SubAddr = URSA_6M40_I2C_SUB_ADDR;
    MS_U8 uRetryCnt = URSA_6M40_CMD_RETRY_TIMES;
    MS_BOOL bRet = FALSE;
    MS_U8 u8ChkSum = 0x00;
    //printf("[6m40]Write cmd:%x,%x,%x,%x,%x,%x,%x\n", pu8CmdData[0], pu8CmdData[1], pu8CmdData[2], pu8CmdData[3], pu8CmdData[4], pu8CmdData[5], pu8CmdData[6]);

    if(pu8CmdData==NULL) return FALSE;

    //DDC need checksum
    u8ChkSum = (pu8CmdData[1] + pu8CmdData[2] + pu8CmdData[3] + pu8CmdData[4] + pu8CmdData[5] + pu8CmdData[6]) & 0x0F;
    pu8CmdData[0] |= (u8ChkSum << 4);

    while(uRetryCnt--)
    {
        bRet = MDrv_Ursa_6M40_SWI2C_WriteBytes(u16BusNumSlaveID, u8SubAddr, NULL, URSA_6M40_CMD_DATA_SUM, pu8CmdData);
        URSA_6M40_CMD_Delay(URSA_6M40_CMD_INTERVAL_TIME);
        if(bRet)
        {
            break;
        }
    }
    return bRet;
}

MS_BOOL MDrv_Ursa_6M40_SendCmd(URSA_6M40_CMD_TYPE eCmdType)
{
    MS_U8 pCmdData[URSA_6M40_CMD_DATA_SUM] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    MS_BOOL bUnkown = FALSE;
    MS_BOOL bRet = FALSE;

    switch(eCmdType)
    {
        case CMD_6M40_OSD_MUTE:
            {
            //0x43, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x43;
                pCmdData[1] = 0x03;
                pCmdData[2] = 0x01;
            }
            break;

        case CMD_6M40_OSD_ON:
            {
            //0x51,  0x04,  0x01,  0x00,  0x00,  0x00,  0x00
                pCmdData[0] = 0x51;
                pCmdData[1] = 0x04;
                pCmdData[2] = 0x01;
            }
            break;

        case CMD_6M40_OSD_OFF:
            {
            //0x41,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00
                pCmdData[0] = 0x41;
                pCmdData[1] = 0x04;
            }
            break;

        case CMD_6M40_OSD_UNMUTE:
            {
            //0x33, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x33;
                pCmdData[1] = 0x03;
            }
            break;

        case CMD_6M40_LVDS_ON:
            {
            //0x93, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x93;
                pCmdData[1] = 0x08;
                pCmdData[2] = 0x01;
            }
            break;

        case CMD_6M40_LVDS_OFF:
            {
            //0x83, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x83;
                pCmdData[1] = 0x08;
            }
            break;
		case CMD_6M40_2K_MODE_ON:
			{
				//0x81,0x05,0x07,0x80,0x04,0x38,0x00
				pCmdData[0] = 0x81;
                pCmdData[1] = 0x05;
				pCmdData[2] = 0x07;
				pCmdData[3] = 0x80;
				pCmdData[4] = 0x04;
				pCmdData[5] = 0x38;

			}
			break;
	    case CMD_6M40_OSD_PROTECT_OFF:
			{
			//  95 09 00 00 00 00 00
                pCmdData[0] = 0x95;
                pCmdData[1] = 0x09;
			}
			break;
		case CMD_6M40_OSD_PROTECT_ON:
			{
			//  A5 09 01 00 00 00 00
                pCmdData[0] = 0xA5;
                pCmdData[1] = 0x09;
		pCmdData[2] = 0x01;
			}
			break;
		case CMD_6M40_OSD_PROTECT_ON_EMMC:
			{
			//  B5 09 02 00 00 00 00
                pCmdData[0] = 0xB5;
                pCmdData[1] = 0x09;
		pCmdData[2] = 0x02;
			}
			break;
        default:
            bUnkown = TRUE;
            break;
    }

    if(!bUnkown)
    {
        bRet  = MDrv_Ursa_6M40_Write_Cmd(pCmdData);
        printf("[6m40]Send cmd:%d, return:%d\n", eCmdType, bRet);
    }
    else
    {
        bRet = FALSE;
        printf("[6m40]Can not find the command, please check!\n");
    }

    return bRet;
}
MS_BOOL MDrv_Ursa_Set_Lvds_On(void)
{
    return MDrv_Ursa_6M40_SendCmd(CMD_6M40_LVDS_ON);
}

MS_BOOL MDrv_Ursa_Set_Lvds_Off(void)
{
    return MDrv_Ursa_6M40_SendCmd(CMD_6M40_LVDS_OFF);
}
MS_BOOL MDrv_Ursa_Set_Osd_Off(void)
{
    return MDrv_Ursa_6M40_SendCmd(CMD_6M40_OSD_OFF);
}
#if (MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S)
#define STATIC_URSA_PAR 0//bootlogo for test
void MDrv_Ursa_Init(ursa5_cmd_table * u5cmd)
{
    MS_U8 ucData[7], i;
    MS_BOOL bRet = FALSE;
    //////////////////////////////////////////////
    //           UC_INIT_RX_ALL 0x001           //
    //////////////////////////////////////////////
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x00; ucData[1] = 0x01;
    ucData[2] = (((((u5cmd->URSA5_LVDS_RX_CHCONNECT&0x03) == 0x03)?0:1) << 7)|
                (u5cmd->URSA5_LVDS_RX_TI_MODE << 6) |
                (u5cmd->URSA5_LVDS_RX_BIT_NUM << 4) |
                (u5cmd->URSA5_LVDS_RX_SWAP_ODD_EVEN << 3) |
                (u5cmd->URSA5_CUS_LVDS_RX_SWAP_P_N << 2) |
                (u5cmd->URSA5_CUS_LVDS_RX_SWAP_MSB_LSB << 1));
    #if STATIC_URSA_PAR
    ucData[0] = 0x00; ucData[1] = 0x01;
    ucData[2] = 0x60;
    #endif
    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_RX_CHCONNECT = %u\n",u5cmd->URSA5_LVDS_RX_CHCONNECT));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_RX_TI_MODE = %u\n",u5cmd->URSA5_LVDS_RX_TI_MODE));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_RX_BIT_NUM = %u\n",u5cmd->URSA5_LVDS_RX_BIT_NUM));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_RX_SWAP_ODD_EVEN = %u\n",u5cmd->URSA5_LVDS_RX_SWAP_ODD_EVEN));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_CUS_LVDS_RX_SWAP_P_N = %u\n",u5cmd->URSA5_CUS_LVDS_RX_SWAP_P_N));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_CUS_LVDS_RX_SWAP_MSB_LSB = %u\n",u5cmd->URSA5_CUS_LVDS_RX_SWAP_MSB_LSB));


    //////////////////////////////////////////////
    //         UC_INIT_OUT_ALL_1 0x010          //
    //////////////////////////////////////////////

    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x00; ucData[1] = 0x10;
    ucData[2] =(((u5cmd->URSA5_LVDS_TX_CHANNEL_NUMBER&0x07) << 5) |
                    (u5cmd->URSA5_LVDS_TX_PANEL_TYPE&0x0F));
    ucData[3] =((u5cmd->URSA5_MASK_HS << 7) |
                (u5cmd->URSA5_MASK_VS << 6) |
                (u5cmd->URSA5_MASK_DE << 5) |
                (u5cmd->URSA5_PANEL_INV_HSYNC << 4) |
                (u5cmd->URSA5_PANEL_INV_VSYNC << 3) |
                (u5cmd->URSA5_PANEL_INV_DE << 2) |
                (u5cmd->URSA5_DITHER_8BITS << 1) |
                (u5cmd->URSA5_DITHER_EN));
    ucData[4] = (((u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_A)&0x03) |
                 ((u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_B << 2)&0x0C) |
                 ((u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_C << 4)&0x30) |
                 ((u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_D << 6)&0xC0));
    ucData[5] = 0x00;//reserved
    ucData[6] =((u5cmd->URSA5_LVDS_TX_INCREASE_VTOTAL_FOR_50HZ << 7) |
                (u5cmd->URSA5_DITHER_TAIL_CUT << 6) |
                (u5cmd->URSA5_CUS_PANEL_SWING_DATA&0x3F));
    #if STATIC_URSA_PAR
    ucData[0] = 0x00; ucData[1] = 0x10;
    ucData[2] = 0x43; ucData[3] = 0x02; ucData[4] = 0x72; ucData[5] = 0x00; ucData[6] = 0x80;
    #endif
    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_CHANNEL_NUMBER = %u\n",u5cmd->URSA5_LVDS_TX_CHANNEL_NUMBER));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_PANEL_TYPE = %u\n",u5cmd->URSA5_LVDS_TX_PANEL_TYPE));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_MASK_HS = %u\n",u5cmd->URSA5_MASK_HS));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_MASK_VS = %u\n",u5cmd->URSA5_MASK_VS));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_MASK_DE = %u\n",u5cmd->URSA5_MASK_DE));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_PANEL_INV_HSYNC = %u\n",u5cmd->URSA5_PANEL_INV_HSYNC));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_PANEL_INV_VSYNC = %u\n",u5cmd->URSA5_PANEL_INV_VSYNC));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_PANEL_INV_DE = %u\n",u5cmd->URSA5_PANEL_INV_DE));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_DITHER_8BITS = %u\n",u5cmd->URSA5_DITHER_8BITS));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_DITHER_EN = %u\n",u5cmd->URSA5_DITHER_EN));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_D = %u\n",u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_D));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_C = %u\n",u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_C));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_B = %u\n",u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_B));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_A = %u\n",u5cmd->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_A));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_INCREASE_VTOTAL_FOR_50HZ = %u\n",u5cmd->URSA5_LVDS_TX_INCREASE_VTOTAL_FOR_50HZ));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_DITHER_TAIL_CUT = %u\n",u5cmd->URSA5_DITHER_TAIL_CUT));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_CUS_PANEL_SWING_DATA = %u\n",u5cmd->URSA5_CUS_PANEL_SWING_DATA));


    //////////////////////////////////////////////
    //         UC_INIT_OUT_ALL_2 0x011          //
    //////////////////////////////////////////////

    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x00; ucData[1] = 0x11;
    ucData[2] = (u5cmd->URSA5_LVDS_TX_HTOTAL >> 8);//H-Total
    ucData[3] = u5cmd->URSA5_LVDS_TX_HTOTAL&0xFF;
    ucData[4] = (((u5cmd->URSA5_LVDS_TX_HSTART >> 8) << 4) |
                  (u5cmd->URSA5_LVDS_TX_VTOTAL >> 8));//V-Total
    ucData[5] = u5cmd->URSA5_LVDS_TX_VTOTAL&0xFF;
    ucData[6] = u5cmd->URSA5_LVDS_TX_HSTART&0xFF;//LVDS TX DE HStart

    #if STATIC_URSA_PAR
    ucData[0] = 0x00; ucData[1] = 0x11;
    ucData[2] = 0x08; ucData[3] = 0x98; ucData[4] = 0x04; ucData[5] = 0x65; ucData[6] = 0xa0;
    #endif
    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_HTOTAL = %u\n",u5cmd->URSA5_LVDS_TX_HTOTAL));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_HSTART = %u\n",u5cmd->URSA5_LVDS_TX_HSTART));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_VTOTAL = %u\n",u5cmd->URSA5_LVDS_TX_VTOTAL));


    //////////////////////////////////////////////
    //         UC_INIT_OUT_ALL_3 0x012          //
    //////////////////////////////////////////////
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x00; ucData[1] = 0x12;
    ucData[2] = (u5cmd->URSA5_LVDS_TX_WIDTH >> 8);//LVDS TX Width ex:1920 (FULL HD)
    ucData[3] = u5cmd->URSA5_LVDS_TX_WIDTH&0xFF;
    ucData[4] = (((u5cmd->URSA5_LVDS_TX_VSTART >> 8) << 4) |
                  (u5cmd->URSA5_LVDS_TX_HEIGHT >> 8));//LVDS TX Height ex:1080 (FULL HD)
    ucData[5] = u5cmd->URSA5_LVDS_TX_HEIGHT&0xFF;
    ucData[6] = u5cmd->URSA5_LVDS_TX_VSTART&0xFF;//LVDS TX DE VStart ex:20 (FULL HD)

    #if STATIC_URSA_PAR
    ucData[0] = 0x00; ucData[1] = 0x12;
    ucData[2] = 0x07; ucData[3] = 0x80; ucData[4] = 0x04; ucData[5] = 0x38; ucData[6] = 0x14;
    #endif
    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_WIDTH = %u\n",u5cmd->URSA5_LVDS_TX_WIDTH));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_HEIGHT = %u\n",u5cmd->URSA5_LVDS_TX_HEIGHT));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_VSTART = %u\n",u5cmd->URSA5_LVDS_TX_VSTART));


    //////////////////////////////////////////////
    //        UC_SET_OUT_LVDS_MODE 0x201        //
    //////////////////////////////////////////////
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x02; ucData[1] = 0x01;
    ucData[2] = u5cmd->URSA5_LVDS_TX_TI_MODE;//E_MFCLVDS_TX_TIMode; //gTxModInfo.lvds.tiMode
    ucData[3] = u5cmd->URSA5_LVDS_TX_SHIFT_PAIR;//E_MFCLVDS_TX_ShiftPair; //gTxModInfo.lvds.lvdsShiftPair
    ucData[4] = u5cmd->URSA5_LVDS_TX_SWAP_POL;//E_MFCLVDS_TX_SwapPolarity; //gTxModInfo.lvds.lvdsSwapPol
    ucData[5] = u5cmd->URSA5_LVDS_TX_SWAP_PAIR;//E_MFCLVDS_TX_SwapPair; //gTxModInfo.lvds.lvdsSwapPair
    ucData[6] = u5cmd->URSA5_LVDS_TX_BIT_NUMBER;//E_MFCLVDS_TX_BitNumber; //gTxModInfo.lvds.panelBitNums

    #if STATIC_URSA_PAR
    ucData[0] = 0x02; ucData[1] = 0x01;
    ucData[2] = 0x00; ucData[3] = 0x00; ucData[4] = 0x00; ucData[5] = 0x00; ucData[6] = 0x02;
    #endif
    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_TI_MODE = %u\n",u5cmd->URSA5_LVDS_TX_TI_MODE));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_SHIFT_PAIR = %u\n",u5cmd->URSA5_LVDS_TX_SHIFT_PAIR));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_SWAP_POL = %u\n",u5cmd->URSA5_LVDS_TX_SWAP_POL));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_SWAP_PAIR = %u\n",u5cmd->URSA5_LVDS_TX_SWAP_PAIR));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_LVDS_TX_BIT_NUMBER = %u\n",u5cmd->URSA5_LVDS_TX_BIT_NUMBER));


    //////////////////////////////////////////////
    //       UC_SET_MIRRORMODE 0x30C            //
    //////////////////////////////////////////////
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x03; ucData[1] = 0x0C;
    ucData[2] = u5cmd->URSA5_ENABLE_MST_MIRROR_FUNC;//the value need to be check, since ursa9 osd/video mirror is seperate

    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
    MFC5_ONEBIN_DBG(printf("E_MFC_ONEBIN_ENABLE_MST_MIRROR_FUNC = %u\n",u5cmd->URSA5_ENABLE_MST_MIRROR_FUNC));
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x01; ucData[1] = 0x00;
    bRet = MDrv_Ursa_6M40_Write_Cmd(ucData);
    URSA_DBG(printf("\n\033[33mMFC DDC Cmd %u: %x %x %x %x %x %x %x\033[m\n",bRet,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6]));
}
void MDrv_Ursa_6M30_Init(ursa5_cmd_table * u5cmd)
{
    if(IsBootLogoValid() && (bMst6m40Installed == TRUE))
        MDrv_Ursa_Init(u5cmd);
}
#endif

#if(MS_BOARD_TYPE_SEL == BD_MB100_120814R1)
void MDrv_Ursa_PWM_SLOW_START(void)
{
    MS_U8 ucData[7], i;
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x0D; ucData[1] = 0x1C; //UC_VESTEL_SET_PWM_SLOW_START
    MDrv_Ursa_6M40_Write_Cmd(ucData);
}

void MDrv_Ursa_PWM_DELAY_START(void)
{
    MS_U8 ucData[7], i;
    for(i=0; i<7; i++)
        ucData[i] = 0x00;
    ucData[0] = 0x0D; ucData[1] = 0x1E; //UC_VESTEL_SET_PWM_DELAY_START
    MDrv_Ursa_6M40_Write_Cmd(ucData);
}
#endif

void MDrv_Ursa_PNL_ON(void)
{
	if(IsBootLogoValid() && (bMst6m40Installed == TRUE))
	{
        #if(MS_BOARD_TYPE_SEL == BD_MB100_120814R1)
        MDrv_Ursa_PWM_DELAY_START(); //before BL_ON/OFF
        #endif
	    MApi_PNL_VCC_On();
        MDrv_Ursa_Set_Lvds_On();
        MApi_PNL_SetBackLight(TRUE);
        #if(MS_BOARD_TYPE_SEL == BD_MB100_120814R1)
        MDrv_Ursa_PWM_SLOW_START(); //after BL_ON/OFF GPIO, send DDC to MFC9 do PWM SLOW START
        #endif
        printf("MDrv_Ursa_PNL_ON...\n");
	}
}

#endif
