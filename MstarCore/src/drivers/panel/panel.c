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
#include <configs/uboot_panel_config.h>
#include <MsTypes.h>
#include <apiPNL.h>
#include <drvGPIO.h>
#include "panel.h"
#include <malloc.h>
#include <ShareType.h>
#include <MsOS.h>
#include <MsBoot.h>

extern int snprintf(char *str, size_t size, const char *fmt, ...);

extern MS_BOOL bMst6m40Installed;

#if (CONFIG_VESTEL_MB97 == 1)
#define PANEL_VCC_VLOTAGE_DROP_LAG      50 // the lag from panel vcc GPIO set to panel vcc voltage
#else
#define PANEL_VCC_VLOTAGE_DROP_LAG      0
#endif
#define ms_delay(x)        \
        do  \
        {   \
            udelay(x*1000); \
        }while(0);

#define TIMER_LOAD_VAL 0xFFFFFFFF
#define MFC_PROCESSING_TIME 30

#if (CONFIG_VESTEL_MB97 == 1)
#define PIU_TICK_LOW    0xBF006090
#define PIU_TICK_HIGH   0xBF006094
#elif (CONFIG_VESTEL_MB100 == 1)
#define PIU_TICK_LOW    0x1f006090
#define PIU_TICK_HIGH   0x1f006094
#endif

PanelType  tDACOUT480I_60[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_480I_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        62,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        62/*60*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        33/*30*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        62+60,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*6+30*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        857 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        857,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        857 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        524 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        524,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        524 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (857*524*60)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (857*524*60)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (857*524*60)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x2CD3FE,
       0x1ED4C4,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT480P_60[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_480P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,
        //#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A) || ( MS_BOARD_TYPE_SEL== BD_MST087C_D02A_S ) )
        //1,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        //#else
        //0,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        //#endif
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        62,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        62/*60*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        31/*30*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        62+60,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*6+30*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        858 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        857/*858*/,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        858 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        525 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        524/*525*/,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        525 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (858*525*60)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (858*525*60)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (858*525*60)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB

       0,          //   double clock
       0x73FBDE,
       0x3555E9,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT576I_50[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_576I_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
            PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,
        //#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A) || ( MS_BOARD_TYPE_SEL== BD_MST087C_D02A_S ) )
        //1,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        //#else
        //0,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        //#endif
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power
/*
        126,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        138,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        3,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        19,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        126+138,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        3+19,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
*/
        64,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        70/*68*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        42/*39*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        64+68,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+39*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        576,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        864 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        863/*864*/,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        864 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        625 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        624/*625*/,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        625 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (864*625*50)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (864*625*50)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (864*625*50)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB

       0,          //   double clock
       0x2CE213,
       0x1EDB6D,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT576P_50[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_576P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
            PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        //#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A) || ( MS_BOARD_TYPE_SEL== BD_MST087C_D02A_S ) )
        //1,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        //#else
        //0,          //BOOL m_bPanelSwapLVDS_POL :1;     //PANEL_SWAP_LVDS_POL
        //#endif
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        62/*64*/,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        72/*68*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        40/*39*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        64+68,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+39*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        576,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        864 + 100,  //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        863/*864*/,        //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        864 - 100,  //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        625 + 100,  //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        624/*625*/,        //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        625 - 100,  //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (864*625*50)/1000000 + 10,  //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (864*625*50)/1000000,       //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (864*625*50)/1000000 - 10,  //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB

       0,          //   double clock
       0x742B06,
       0x355FE0,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT720P_60[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_720P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        222/*220*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5/*6*/,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        21/*20*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        40+220,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*6+20*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        720,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1650 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1649/*1650*/,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1650 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        750 + 100,      //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        749/*750*/,            //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        750 - 100,      //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (1650*750*60)/1000000 + 10,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (1650*750*60)/1000000,          //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (1650*750*60)/1000000 - 10,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1EBCB1,
       0x1770C0,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT720P_50[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_720P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        222/*220*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        21/*20*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        40+220,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+20*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        720,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1980 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1979/*1980*/,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1980 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        750 + 100,      //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        749/*750*/,            //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        750 - 100,      //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (1980*750*50)/1000000 + 10,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (1980*750*50)/1000000,          //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (1980*750*50)/1000000 - 10,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1EBCB1,
       0x1770C0,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT1080I_50[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_1080I_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        150/*148*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37/*15*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+15*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2640 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2639/*2640*/,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2640 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1124/*1125*/,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2640*1125*50)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2640*1125*50)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2640*1125*50)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT1080I_60[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_1080I_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_I,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        150/*148*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37/*15*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+15*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2200 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2199/*2200*/,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2200 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1124/*1125*/,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2200*1125*60)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2200*1125*60)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2200*1125*60)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT1080P_50[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_1080P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        150/*148*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37/*36*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+36*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2640 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2639/*2640*/,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2640 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1124/*1125*/,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2640*1125*50)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2640*1125*50)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2640*1125*50)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tDACOUT1080P_60[] =
{
    {//Dac Out for U3 bringup
        "DACOUT_1080P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_DAC_P,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

#ifdef PANEL_SWAP_PORT
        PANEL_SWAP_PORT,
#else
        0,          //BOOL m_bPanelSwapPort :1;         //PANEL_SWAP_PORT
#endif

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        150/*148*/,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37/*36*/,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        44+148,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0/*5+36*/,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2200 + 100,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2199/*2200*/,           //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        2200 - 100,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1125 + 100,     //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1124/*1125*/,           //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1125 - 100,     //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (2200*1125*60)/1000000 + 10,    //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (2200*1125*60)/1000000,         //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (2200*1125*60)/1000000 - 10,    //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1C848E,
       0x18EB59,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tPanelSXGA_AU17_EN05[] =
{
   {
        "SXGA_AU17_EN05",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        1,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;        //PANEL_EVEN_DATA_CURRENT    // even data current

        10,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        250,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        100,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        24,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        38,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+24,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH-1)
        2+38,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1024,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1800,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1688,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1664,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2047,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1066,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL
        1035,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        140,        //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        108,        //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        100,        //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,        //m_ucDimmingCtl
        0xFF,        //m_ucMaxPWMVal;
        0x50,         //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_4_3,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x277F44,
       0x1C3655,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};//


PanelType  tPanelWXGA_AU20_T200XW02[] =
{
    {
        "WXGA_AU20_T200XW02",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30, //45,   //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,         //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30, //20,   //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        20,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        4,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        34,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        20+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        4+34,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1366,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        768,        //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1722ul,     //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1560ul,//1430,  //WORD m_wPanelHTotal;          //PANEL_HTOTAL
        1414ul,     //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        822,        //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        806ul,      //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        789,        //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        88, //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        76, //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60, //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x50,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x20ea0e,
       0x167109,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};//!<Panel Data  ü.(Multi Panel   )

PanelType  tPanelWXGAP_CMO_M190A1[] =
{
    {

        "WXGAP_CMO_M190A1",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,            //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        150,            //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        104,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        24,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        3,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        6,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        104+24,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        3+6,            //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1440,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        900,            //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1920,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1760,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1520,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1050,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        950,            //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        910,            //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        112,     //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        100,     //DWORD m_dwPanelDCLK;          //PANEL_DCLK
        80,     //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0000,//0x0010,        //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x0000,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x68,       //m_ucDimmingCtl
        0xDD,                //m_ucMaxPWMVal;
        0x20,//63,        //m_ucMinPWMVal;

        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x315F15,
       0x2343EB,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tPanelWSXGA_AU22_M201EW01[] =
{
    {
        "WSXGA_AU22_M201EW01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        500,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        120,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        40,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        8,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        16+40,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        2+8,        //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1680,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1050,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2000,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1840,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1780,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1195,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1080,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1060,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (150),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (119),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (110),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;            //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0xA0,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x50,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x23E80F,
       0x1A54D8,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};
#if 0 // 4K2K
PanelType  tPanelFullHD_CMO216_H1L01[] =
{
    {
        "FullHD_CMO216_H1L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0, //1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        0, //1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        1, //PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        0, //PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A_HX)||(MS_BOARD_TYPE_SEL==BD_MST087E_D01A_HX))
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
#else
        0, //1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
#endif

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        2,//8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        96,//16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        110,//32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        98,//8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        3840,//1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        2160,//1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        4500,//2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        4400,//2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        4300,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        2360,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        2260,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        2160,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl
        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       0xFF0,//(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A_HX)||(MS_BOARD_TYPE_SEL==BD_MST087E_D01A_HX))
        TI_10BIT_MODE,               //8bit ti bit mode
#else
        TI_8BIT_MODE,               //8bit ti bit mode
#endif
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x20EA0E,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};
#else
PanelType  tPanelFullHD_CMO216_H1L01[] =
{
    {
        "FullHD_CMO216_H1L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A_HX)||(MS_BOARD_TYPE_SEL==BD_MST087E_D01A_HX))
	0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
#else
	1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
#endif

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
#if ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A_HX)||(MS_BOARD_TYPE_SEL==BD_MST087E_D01A_HX))
	TI_10BIT_MODE,               //8bit ti bit mode
#else
	TI_8BIT_MODE,               //8bit ti bit mode
#endif
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x20EA0E,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};
#endif

#if ENABLE_MFC
PanelType  tMFCFullHD120_CMO216_H1L01[] =
{
    {
        "URSA120_CMO216H1_L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MFC,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tMFCFullHD60_CMO216_H1L01[] =
{
    {
        "URSA60_CMO216H1_L01",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MFC,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};
#endif

PanelType  tPanelFULLHD_SEC32_LE32A[] =
{
    {
        "SEC_LE32A",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        0,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,          //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        8+16,            //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1130,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;          //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //0x0010,       //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,   //0x87,     //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,    //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

PanelType  tWUXGA_CMO_260J2[] =
{
    {
        "CMO260J2_WUXGA",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_LVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        1,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT
        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB
        PANEL_SWAP_LVDS_POL,
        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        600,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        300,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        26,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        6+26,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1200,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2159,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2141,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2060,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1245,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1235,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1209,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (170),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (158),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        100,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x015E,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x7D,       //m_ucDimmingCtl

        0xFF,        //m_ucMaxPWMVal;
        0x00,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0x1D0AC1,
       0x173BCE,
       E_PNL_CHG_VTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};

#if ENABLE_TCON
PanelType  tPanelFullHD_TCON[] =
{
    {
        "tPanelFullHD_TCON",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_MINILVDS,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
	    1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE


        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        16,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        32+80,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        16+16,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1135,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (149),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (136),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

	    TI_10BIT_MODE,             //10bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       0,          //   double clock
       0x1D0AC1,
       0x181568,
       E_PNL_CHG_HTOTAL,
       1,///<  PAFRC mixed with noise dither disable
    },
};
#endif

#if defined(CONFIG_A3_STB)


PanelType  tSDACOUT480I_60[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_480I_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

    	62,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
    	62,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

    	6,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
    	33,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

    	122,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
    	0,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

    	720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
    	240,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

    	957,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
    	858,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
    	757,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

    	282,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
    	262,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
    	252,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        37,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        13,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        17,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x002cd3fe,
        0x001ed4c4,
        E_PNL_CHG_VTOTAL,
        1,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT480P_60[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_480P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        16,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        122,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        36,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        138,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0,			//WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        480,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        958,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        858,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        758,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        625,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        525,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        425,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        37,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        27,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        17,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x0073fbde,
        0x003555e9,
        E_PNL_CHG_VTOTAL,
        0,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT576I_50[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_576I_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        64,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        70,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        42,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        132,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        288,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        964,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        864,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        764,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        362,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        312,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        262,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        37,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        13,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        17,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x002ce213,
        0x001edb6d,
        E_PNL_CHG_VTOTAL,
        1,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT576P_50[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_576P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        12,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        132,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        1,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        44,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        144,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        720,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        576,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        964,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        864,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        764,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        725,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        625,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        525,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        37,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        27,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        17,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x00742b06,
        0x00355fe0,
        E_PNL_CHG_DCLK,
        0,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT720P_50[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_720P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

		40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        220,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

		5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        20,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH
#else
		21,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH
#endif
		260,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#if (ENABLE_HDMITX_NXP_TDA19988==1)
		25,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
#else
		26,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
#endif

		1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
		720,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

		2080,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
		1980,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
		1880,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

		850,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
		749,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
		650,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

		84,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
		74,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
		64,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

		25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
		192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

		160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

		255,        //m_ucMaxPWMVal;
		80,			//m_ucMinPWMVal;
		0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
		E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
		0x001ebcb1,
		0x001770c0,
		E_PNL_CHG_DCLK,
		0,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT720P_60[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_720P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        40,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        220,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        20, 		//BYTE m_ucPanelBackPorch;			//PANEL_VSYNC_BACK_PORCH
#else
        5,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH
#endif
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        /*72*/260,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#else
        72,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#endif
        10,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1280,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        720,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        1848,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        1650,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        1400,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        820,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        750,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        730,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        90,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        75,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        60,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x001ebcb1,
        0x001770c0,
        E_PNL_CHG_DCLK,
        0,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT1080I_50[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_1080I_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        150,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        192,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        540,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2740,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2640,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2540,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        580,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        562,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        550,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        158,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        74,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        138,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x001c848e,
        0x0018eb59,
        E_PNL_CHG_VTOTAL,
        1,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT1080I_60[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_1080I_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        150,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        192,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        540,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2300,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2100,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        580,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        562,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        550,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        158,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        74,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        138,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x001c848e,
        0x0018eb59,
        E_PNL_CHG_VTOTAL,
        1,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT1080P_50[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_1080P_50",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        0/*0x08*/,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        1,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC
#else
		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC
#endif
        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        40,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH
#else
        5,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        37,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH
#endif
        192,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0,       //WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)

        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2740,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2640,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2540,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1225,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1025,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        158,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        148,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        138,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        160,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        80,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x001c848e,
        0x0018eb59,
        E_PNL_CHG_DCLK,
        0,///<  PAFRC mixed with noise dither disable
	},
};

PanelType  tSDACOUT1080P_60[] =
{
	{//Dac Out for A3 STB bringup
		"DACOUT_1080P_60",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
		0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
		LINK_TTL,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

		0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

		0,			// shall swap if
					// (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE
        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

		0,

		0,			//BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
		0x01,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
		0x01,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE

#if (ENABLE_HDMITX_NXP_TDA19988==1)
        0/*0x08*/,		 //BYTE m_ucPanelDCLKDelay; 		 //PANEL_DCLK_DELAY
        1,			//BOOL m_bPanelInvDCLK	:1; 		//PANEL_INV_DCLK
        0,			//BOOL m_bPanelInvDE		:1; 	//PANEL_INV_DE
        0,			//BOOL m_bPanelInvHSync :1; 		//PANEL_INV_HSYNC
        0,			//BOOL m_bPanelInvVSync :1; 		//PANEL_INV_VSYNC
#else
		0x08,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
		0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
		0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
		0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
		0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC
#endif

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current


    	30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        400,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        80,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        30,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        44,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        148,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        1,			//BYTE m_ucPanelVSyncWidth; 		//PANEL_VSYNC_WIDTH
        40,		   //BYTE m_ucPanelBackPorch;		   //PANEL_VSYNC_BACK_PORCH
#else
        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        16,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH
#endif
#if (ENABLE_HDMITX_NXP_TDA19988==1)
        192,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#else
        112,      //WORD m_wPanelHStart;              //PANEL_HSTART             (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
#endif
        0,		//WORD m_wPanelVStart;              //PANEL_VSTART             (PANEL_VSYNC_WIDTH + PANEL_VSYNC_BACK_PORCH)
        1920,       //WORD m_wPanelWidth;               //PANEL_WIDTH
        1080,       //WORD m_wPanelHeight;              //PANEL_HEIGHT

        2360,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2200,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2020,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1200,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        164,      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        150,      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        120,      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        25,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        192,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        109,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        255,        //m_ucMaxPWMVal;
        32,			//m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
		(LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue

		TI_8BIT_MODE,               //8bit ti bit mode
		OUTPUT_10BIT_MODE,          //10bit ti bit mode
		0,          //   PANEL_SWAP_ODD_RG
		0,          //   PANEL_SWAP_EVEN_RG
		0,          //   PANEL_SWAP_ODD_GB
		0,          //   PANEL_SWAP_EVEN_GB
		0,          //   double clock
        0x001c848e,
        0x0018eb59,
        E_PNL_CHG_DCLK,
        0,///<  PAFRC mixed with noise dither disable
	},
};

PanelType * tSPanelIndexTbl[] =
{
    tSDACOUT480P_60,             // DAC 720*480 60MHz
    tSDACOUT576P_50,             // DAC 720*576P 50MHz
    tSDACOUT720P_50,             // DAC 1280*720P 50MHz
    tSDACOUT720P_60,             // DAC 1280*720 60MHz
    tSDACOUT1080P_50,            // DAC 1920*1080P 50MHz
    tSDACOUT1080P_60,            // DAC 1920*1080P 60MHz
    tSDACOUT480I_60,             // DAC 720*480I 60MHz
    tSDACOUT576I_50,             // DAC 720*576I 50MHz
    tSDACOUT1080I_50,            // DAC 1920*1080I 50MHz
    tSDACOUT1080I_60,            // DAC 1920*1080I 60MHz
};

#endif


PanelType * tPanelIndexTbl[] =
{
    tPanelFULLHD_SEC32_LE32A,   // LE32A_FULLHD
    tPanelSXGA_AU17_EN05,
    tPanelWXGA_AU20_T200XW02,
    tPanelWXGAP_CMO_M190A1,     // 1440*900  //CHR_060912_1 Resolution ߰
    tPanelWSXGA_AU22_M201EW01,  // 1680*1050
    tPanelFullHD_CMO216_H1L01,  // 1920x1080
    tDACOUT480I_60,             // DAC 720*480
    tDACOUT480P_60,             // DAC 720*480
    tDACOUT576I_50,             // DAC 720*576
    tDACOUT576P_50,             // DAC 720*576
    tDACOUT720P_50,             // DAC 1280*720
    tDACOUT720P_60,             // DAC 1280*720
    tDACOUT1080I_50,            // DAC 1920*1080I 50MHz
    tDACOUT1080I_60,            // DAC 1920*1080I 60MHz
    tDACOUT1080P_50,            // DAC 1920*1080P 50MHz
    tDACOUT1080P_60,            // DAC 1920*1080P 60MHz
    tWUXGA_CMO_260J2,           // CMO_260J2_WUXGA
#if ENABLE_MFC
    tMFCFullHD120_CMO216_H1L01,       // 1920x1080
    tMFCFullHD60_CMO216_H1L01,       // 1920x1080
#endif
#if ENABLE_TCON
    tPanelFullHD_TCON,             // TCON 1920x1080
#endif
};

typedef struct
{
    U16 ucX;
    U16 ucY;
}T_MS_NONLINEAR_POINT_16;//fix me

typedef struct
{
    T_MS_NONLINEAR_POINT_16     stPoint0;
    T_MS_NONLINEAR_POINT_16     stPoint1;
    T_MS_NONLINEAR_POINT_16     stPoint2;
    T_MS_NONLINEAR_POINT_16     stPoint3;
}T_MS_NONLINEAR_CURVE_16;  //fix me

static T_MS_NONLINEAR_CURVE_16 stBacklightCurveTbl =  //fix me
{
    {0,     0 },
    {0,    0 },
    {0,    0 },
    {0,   0 },
};


PanelType * MApi_XC_GetPanelSpec(PANEL_RESOLUTION_TYPE enResolutionType)
{
#if (defined(CONFIG_A3_STB))
    int resolution_index = 5;
    char * p_str;
    if (isBootToRecovery())
    {
        p_str = getenv ("resolution");
        setenv("resolution_reset", p_str);
        p_str = "2";
        setenv("resolution", "2");
    }
    else
    {
        p_str = getenv ("resolution_reset");
        if (p_str == NULL)
        {
            p_str = getenv ("resolution");
        }
        if (NULL != p_str)
        {
            setenv("resolution", p_str);
            setenv("resolution_reset", p_str);
        }
    }
    char str[128];

    if(p_str != NULL)
    {
        resolution_index = (int)simple_strtol(p_str, NULL, 10);

        memset(str, 0, sizeof(str));
        snprintf(str, sizeof(str)-1, "%s", tSPanelIndexTbl[resolution_index]->m_pPanelName);
        MApi_SetEnv2BootArgs("resolution=", str);
        saveenv();
    }
    else
    {
    //set env normal resolution.
        setenv("resolution", "5");
        saveenv();

        resolution_index = 5;
    }

    enResolutionType = resolution_index;
    return tSPanelIndexTbl[(MS_U8)enResolutionType];
#else
    return tPanelIndexTbl[(MS_U8)enResolutionType];
#endif
}

//--------
// panel
//--------
static void _msAPI_Scaler_SetPanelVCC(MS_BOOL bEnable)
{
    if(bEnable)
    {
        PANEL_CTL_On();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus |= PANEL_POWER_VCC;
    }
    else
    {
        PANEL_CTL_Off();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus &= ~PANEL_POWER_VCC;
    }
}

void MApi_PNL_En(MS_BOOL bPanelOn, MS_U16 u16PanelTiming)
{
    //MS_U32 delayTime;

    if(bPanelOn)
    {
        /* enable/disable VCC */
        #if (CONFIG_VESTEL_MB100 == 1) || (CONFIG_VESTEL_MB97 == 1)
        _msAPI_Scaler_SetPanelVCC(bPanelOn);
        MsOS_DelayTask(PANEL_VCC_VLOTAGE_DROP_LAG);
        #endif
        #if defined(CONFIG_MSTAR_BD_MSD062B_10AVV_14033_MADISON) || (CONFIG_VESTEL_MB100 == 1) || (CONFIG_VESTEL_MB97 == 1)
        MS_U32 delayTime  = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_1);//_getPanelOnTiming1();
        MsOS_DelayTask(delayTime);
        #else
        //delayTime = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_1);//_getPanelOnTiming1();
        //MsOS_DelayTask(delayTime);
        #endif

        g_IPanel.Enable(bPanelOn);
        #if (CONFIG_VESTEL_MB97 == 1)
            //Note: Must put OnTiming2 delay here, if put in MApi_PNL_SetBackLight
            //the ms_delay has no effect, and if use MsOS_DelayTask(), the system will stuck at MApi_PNL_SetBackLight
            MS_U32 delayTime2  = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_2);//_getPanelOnTiming1();
            MsOS_DelayTask(delayTime2);
        #endif
/* 		remove for mboot boot time issue jh.huang
        if(u16PanelTiming != 0)
            MsOS_DelayTask(u16PanelTiming);
        else
            MsOS_DelayTask(5);
*/
        // >>> Ken 20090914
        /*
        	#if(MS_BOARD_TYPE_SEL == BD_MST087B_S7M_D01A_S)
        	MDrv_Write2Byte(0x103240, 0x1100);
        	MDrv_WriteByte(0x103264, 0x03);
        	MDrv_Write2Byte(0x1032EE, 0x0000);
        	MDrv_Write2Byte(0x1032F0, 0x0001);
        	MDrv_WriteByte(0x1032EA, 0x01);
        	#endif
       	 */
        // <<< Ken 20090914
    }
    else
    {
        g_IPanel.Enable(bPanelOn);
        //MsOS_DelayTask(20);
        /* enable/disable VCC */
        if(u16PanelTiming != 0)
            MsOS_DelayTask(u16PanelTiming);
        else
            MsOS_DelayTask(5);

        _msAPI_Scaler_SetPanelVCC(bPanelOn);
    }
}

void MApi_PNL_On(MS_U16 u16PanelOnTiming )
{
    _msAPI_Scaler_SetPanelVCC(TRUE);
    //printf("u16PanelOnTiming = %d\n",u16PanelOnTiming);
    //u16PanelOnTiming +=5;		//patch for HW delay 101223
    //MsOS_DelayTask(u16PanelOnTiming);
}

void MApi_PNL_Delay(MS_U32 ms)
{
    unsigned int PiuTick = *(volatile unsigned int *)(PIU_TICK_LOW);
    PiuTick |= (*(volatile unsigned int *)(PIU_TICK_HIGH)) << 16;
    unsigned int PiuTime = PiuTick / 12000;
    MS_U32 timeBase = (MS_U32)PiuTime;
    MS_U32 currentTime = (MS_U32)PiuTime;
    MS_U32 diffTime;
    do
    {
        PiuTick = *(volatile unsigned int *)(PIU_TICK_LOW);
        PiuTick |= (*(volatile unsigned int *)(PIU_TICK_HIGH)) << 16;
        PiuTime = PiuTick / 12000;
        currentTime = (MS_U32)PiuTime;

        if (currentTime >= timeBase)
        {
            diffTime = currentTime - timeBase;
        }
        else
        {
            diffTime = TIMER_LOAD_VAL - currentTime + timeBase;
        }
    } while(diffTime < ms);
}

void MApi_PNL_VCC_On(void)
{
    _msAPI_Scaler_SetPanelVCC(TRUE);
    MS_U32 delayTime  = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_1);//_getPanelOnTiming1();
    #if (CONFIG_VESTEL_MB100 == 1)
    #ifdef PCB_WITH_MFC
    if (delayTime >= MFC_PROCESSING_TIME)
    {
        delayTime -= MFC_PROCESSING_TIME;
    }
    else
    {
        delayTime = 0;
    }
    #endif
    #endif
    MApi_PNL_Delay(delayTime); //MsOS_DelayTask(delayTime); //use ms_delay() to fix crash at do_bootm_linux()
}
void MApi_LPLL_On(MS_BOOL bEnable)
{
    MApi_PNL_PowerDownLPLL(!bEnable);
}
/******************************************************************************/
///Enable/Disable Panel backlight
///@param bEnable \b IN:
///- TRUE: Enable
///- FALSE: Disable
/******************************************************************************/
#define MAX_BACKLIGHT    100
void MApi_PNL_SetInverter(MS_BOOL bEnable)
{
    if(bEnable)
    {
        INV_CTL_On();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus |= PANEL_POWER_LIGHT_ON;
    }
    else
    {
        INV_CTL_Off();
        //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus &= ~PANEL_POWER_LIGHT_ON;
    }
}

U16 msAPI_CalNonLinearCurve_BackLight(unsigned char AdjustValue, T_MS_NONLINEAR_CURVE_16* stNonLinearCurve )
{
    U16 rValue,ucY0,ucY1,ucX0,ucX1,ucIntercept;
    U16 wDistanceOfY, wDistanceOfX;

    if (AdjustValue < stNonLinearCurve->stPoint1.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint0.ucY;
          ucY1 = stNonLinearCurve->stPoint1.ucY;
          ucX0 = stNonLinearCurve->stPoint0.ucX;
          ucX1 = stNonLinearCurve->stPoint1.ucX;
    }
    else if (AdjustValue < stNonLinearCurve->stPoint2.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint1.ucY;
          ucY1 = stNonLinearCurve->stPoint2.ucY;
          ucX0 = stNonLinearCurve->stPoint1.ucX;
          ucX1 = stNonLinearCurve->stPoint2.ucX;
    }
    else //if (AdjustValue < stNonLinearCurve->stPoint3.ucX)
    {
          ucY0 = stNonLinearCurve->stPoint2.ucY;
          ucY1 = stNonLinearCurve->stPoint3.ucY;
          ucX0 = stNonLinearCurve->stPoint2.ucX;
          ucX1 = stNonLinearCurve->stPoint3.ucX;
    }
//    else
//    {
//          ucY0 = stNonLinearCurve->stPoint3.ucY;
//          ucY1 = stNonLinearCurve->stPoint4.ucY;
//          ucX0 = stNonLinearCurve->stPoint3.ucX;
//          ucX1 = stNonLinearCurve->stPoint4.ucX;
//    }

    if (ucY1 > ucY0)
    {
        wDistanceOfY = ucY1 - ucY0;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY0;
        AdjustValue  = AdjustValue - ucX0;
    }
    else
    {
        wDistanceOfY = ucY0 - ucY1;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY1;
        AdjustValue  = ucX1 - AdjustValue;
    }

  //printf("wDistanceOfY %u\n", wDistanceOfY);
  //printf("wDistanceOfX %u\n", wDistanceOfX);
  //printf("ucIntercept %bu\n", ucIntercept);
  //printf("AdjustValue %bu\n", AdjustValue);

    rValue = ((U16)wDistanceOfY*AdjustValue/(wDistanceOfX)) + ucIntercept;
    return rValue;
}

U16 msAPI_Mode_PictureBackLightN100toReallyValue ( U8 u8value )
{
    return msAPI_CalNonLinearCurve_BackLight(u8value, &stBacklightCurveTbl );  //fix me
}

void MApi_PNL_SetBackLight(MS_BOOL bEnable)
{
    //U8 u8TransientBacklight;

    if ( bEnable )
    {
        //ms_delay( g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_2) );
        if(bMst6m40Installed == TRUE)
        {
            MS_U32 delayTime2  = g_IPanel.OnTiming(E_APIPNL_POWER_TIMING_2);//_getPanelOnTiming1();
            #if (CONFIG_VESTEL_MB100 == 1)
            #ifdef PCB_WITH_MFC
            if (delayTime2 >= MFC_PROCESSING_TIME)
            {
                delayTime2 -= MFC_PROCESSING_TIME;
            }
            else
            {
                delayTime2 = 0;
            }
            #endif
            #endif
            MApi_PNL_Delay(delayTime2); //MsOS_DelayTask(delayTime2); //use ms_delay() to fix crash at do_bootm_linux()
        }
        MApi_PNL_SetInverter(ENABLE);
       // u8TransientBacklight = MIN(MAX_BACKLIGHT, MAX_BACKLIGHT);

        //Panel_Backlight_PWM_ADJ(msAPI_Mode_PictureBackLightN100toReallyValue( u8TransientBacklight ));
    #if 0 //desable by jp for reduce boot time
        U8 i;
        i = 0;
        msAPI_Scaler_SetPanelBacklight(ENABLE);
        ms_delay( 10 );
        Panel_Backlight_Max_Current(PANEL_DIMMING_CTL);

        g_bIsSoftStartValid = TRUE;

        while ( g_bIsSoftStartValid == TRUE )
        {
            if ( g_u8TransientBacklight < MAX_BACKLIGHT )
            {
                g_u8TransientBacklight += 5;
            }

            g_u8TransientBacklight = MIN(g_u8TransientBacklight, MAX_BACKLIGHT);

            msAPI_Scaler_SetBacklight( msAPI_Mode_PictureBackLightN100toReallyValue( g_u8TransientBacklight ));

            ms_delay( 10 );
            if ( g_u8TransientBacklight == MAX_BACKLIGHT )
            {
                g_bIsSoftStartValid = FALSE;

            }
        }
    #endif
    }
    else
    {
        //Panel_Backlight_PWM_ADJ(0);

        //ms_delay( 5 );
        MApi_PNL_SetInverter(DISABLE);
    }
}

PANEL_RESOLUTION_TYPE MApi_PNL_GetPnlTypeSetting(void)
{
    if (ENABLE_PNL_FULLHD_SEC_LE32A)
        return PNL_FULLHD_SEC_LE32A;
    else if (ENABLE_PNL_SXGA_AU17_EN05)
        return PNL_SXGA_AU17_EN05;
    else if (ENABLE_PNL_WXGA_AU20_T200XW02)
        return PNL_WXGA_AU20_T200XW02;
    else if (ENABLE_PNL_WXGA_PLUS_CMO190_M190A1)
        return PNL_WXGA_PLUS_CMO190_M190A1;
    else if (ENABLE_PNL_WSXGA_AU22_M201EW01)
        return PNL_WSXGA_AU22_M201EW01;
    else if (ENABLE_PNL_FULLHD_CMO216_H1L01)
        return PNL_FULLHD_CMO216_H1L01;
    else if (ENABLE_PANEL_RES_FULL_HD)
        return PANEL_RES_FULL_HD;
    else if (ENABLE_PNL_WUXGA_CMO260_J2)
        return PNL_WUXGA_CMO260_J2;
#if ENABLE_MFC
    else if (ENABLE_MFC120_FULLHD_CMO216_H1L01)
        return MFC120_FULLHD_CMO216_H1L01;
    else if (ENABLE_MFC60_FULLHD_CMO216_H1L01)
        return MFC60_FULLHD_CMO216_H1L01;
#endif

    else if (ENABLE_PNL_DACOUT_576I)
        return DACOUT_576I;
    else if (ENABLE_PNL_DACOUT_576P)
        return DACOUT_576P;
    else if (ENABLE_PNL_DACOUT_720P_50)
        return DACOUT_720P_50;
    else if (ENABLE_PNL_DACOUT_1080I_50)
        return DACOUT_1080I_50;
    else if (ENABLE_PNL_DACOUT_1080P_50)
        return DACOUT_1080P_50;
    else if (ENABLE_PNL_DACOUT_480I)
        return DACOUT_480I;
    else if (ENABLE_PNL_DACOUT_480P)
        return DACOUT_480P;
    else if (ENABLE_PNL_DACOUT_720P_60)
        return DACOUT_720P_60;
    else if (ENABLE_PNL_DACOUT_1080I_60)
        return DACOUT_1080I_60;
    else if (ENABLE_PNL_DACOUT_1080P_60)
        return DACOUT_1080P_60;

#if ENABLE_TCON
    else if (ENABLE_PNL_FULLHD_TCON)
        return PNL_FULLHD_TCON;
#endif
    else
        return PNL_WXGA_AU20_T200XW02;
}

void MApi_PNL_Dump(void)
{
    printf("PNL name:%s\n",g_IPanel.Name());
    printf("PNL HStart:%d\n",g_IPanel.HStart());
    printf("PNL VStart:%d\n",g_IPanel.VStart());
    printf("PNL Width:%d\n",g_IPanel.Width());
    printf("PNL Height:%d\n",g_IPanel.Height());
    printf("PNL HTotal:%d\n",g_IPanel.HTotal());
    printf("PNL VTotal:%d\n",g_IPanel.VTotal());
    printf("PNL HSynWidth:%d\n",g_IPanel.HSynWidth());
    printf("PNL HSynBackPorch:%d\n",g_IPanel.HSynBackPorch());
    printf("PNL VSynBackPorch:%d\n",g_IPanel.VSynBackPorch());
    printf("PNL DefaultVFreq:%d\n",g_IPanel.DefaultVFreq());
    printf("PNL LPLL_Mode:%d\n",g_IPanel.LPLL_Mode());
    printf("PNL LPLL_Type:%d\n",g_IPanel.LPLL_Type());
    printf("PNL AspectRatio:%d\n",g_IPanel.AspectRatio());
    printf("PNL MinSET:%lu\n",g_IPanel.MinSET());
    printf("PNL MaxSET:%lu\n",g_IPanel.MaxSET());
	//printf("PNL PanelSwapLVDS:%lu\n",g_IPanel);
}

MS_BOOL MApi_SetEnv2BootArgs(const char* name,const char* value)
{
    if(name == NULL || value == NULL)
        return FALSE;

    int reslen=(strlen(name)+strlen(value)+1);
    char* pResolution = (char*)malloc(reslen);

    if(pResolution == NULL)
    {
        printf("%s: Error: ou of memory, at %d\n", __func__, __LINE__);
        return FALSE;
    }

    snprintf(pResolution, reslen, "%s%s", name, value);

    const char *pArgs = getenv("bootargs");

    if (pArgs != NULL )
    {
        int len = strlen(pArgs);
        char* pOldArgs = (char*)malloc(len + 1);
        if(pOldArgs == NULL)
        {
            printf("%s: Error: ou of memory, at %d\n", __func__, __LINE__);
            free(pResolution);
            return FALSE;
        }
        strcpy(pOldArgs, pArgs);

        //if resolution exist, delete it.
        char* pPreEnv = strstr(pOldArgs, name);
        if (pPreEnv != NULL)
        {
            char* pPreEnvEnd = strchr(pPreEnv, ' ');
            if (pPreEnvEnd!=NULL)
            {
                int remain = len - (++pPreEnvEnd - pOldArgs);
                if (remain > 0)
                {
                    char* pRemainBuf = (char*)malloc(remain + 1);
                    if(pRemainBuf == NULL)
                    {
                        printf("%s: Error: ou of memory, at %d\n", __func__, __LINE__);
                        free(pOldArgs);
                        free(pResolution);
                        return false;
                    }
                    strcpy(pRemainBuf, pPreEnvEnd);
                    strcpy(pPreEnv, pRemainBuf);
                    free(pRemainBuf);
                }
                else
                {
                    *pPreEnv = 0;
                }
            }
            else
            {
                *pPreEnv = 0;
            }
        }

        const int NewArgsLen = len + 1+1 + reslen;
        char* pNewArgs = (char*)malloc(NewArgsLen);
        if(pNewArgs == NULL)
        {
            printf("%s: Error: ou of memory, at %d\n", __func__, __LINE__);
            free(pOldArgs);
            free(pResolution);
            return FALSE;
        }
        memset(pNewArgs, 0 , NewArgsLen);
        int templen= strlen(pOldArgs) - 1;
        if( (templen>=1) && (templen<len) )
        {
            if (pOldArgs[templen] != ' ')
            {
                snprintf(pNewArgs, NewArgsLen, "%s %s ", pOldArgs, pResolution);
            }
            else
            {
                snprintf(pNewArgs, NewArgsLen, "%s%s ", pOldArgs, pResolution);
            }
        }
        setenv("bootargs", pNewArgs);
        free(pNewArgs);
        free(pOldArgs);
    }

    free(pResolution);
    return TRUE;
}
MS_BOOL IsBootLogoValid(void)
{
    char* opt_logo = NULL;
    int logo = 0;
    MS_BOOL bRet = FALSE;
    opt_logo = getenv("logo");
    if(opt_logo != NULL)
    {
        logo = (int)simple_strtol(opt_logo, NULL, 10);
        if(logo != 0)
        {
            //printf("\033[0;36m With bootlogo\n\033[m");
            bRet = TRUE;
        }
    }
    else
    {
        //printf("\033[0;36m With bootlogo\n\033[m");
        bRet = TRUE;
    }
    return bRet;
}
