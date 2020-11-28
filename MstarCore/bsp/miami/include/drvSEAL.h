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

//////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvSEAL.h
/// @brief  SEAL Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_SEAL_H_
#define _DRV_SEAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsCommon.h"
#include "utopia.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0x0020
#define BIT6  0x0040
#define BIT7  0x0080
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define SEAL_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    {'S','E','A','L'},                  /* IP__                                             */  \
    {'0','0'},                          /* 0.0 ~ Z.Z                                        */  \
    {'0','0'},                          /* 00 ~ 99                                          */  \
    {'0','0','2','6','4','8','8','5'},  /* CL#                                              */  \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_SEAL_MIU_DEV0,
    E_SEAL_MIU_DEV1,
    E_SEAL_MIU_DEV2,
    E_SEAL_MIU_DEV3,
    E_SEAL_MIU_NUM,
}eSeal_MiuDev;

typedef enum
{
    E_SEAL_SECURE_WRITE    = BIT0,
    E_SEAL_SECURE_READ     = BIT1,
    E_SEAL_NONSECURE_WRITE = BIT2,
    E_SEAL_NONSECURE_READ  = BIT3,
}eSeal_SecureAttribute;

typedef enum
{
    E_SEAL_SECURE_RANGE_ID0,
    E_SEAL_SECURE_RANGE_ID1,
    E_SEAL_SECURE_RANGE_ID2,
    E_SEAL_SECURE_RANGE_ID3,
    E_SEAL_SECURE_RANGE_ID4,
    E_SEAL_SECURE_RANGE_ID5,
    E_SEAL_SECURE_RANGE_ID6,
    E_SEAL_SECURE_RANGE_ID7,
    E_SEAL_SECURE_RANGE_NUM,
}eSeal_SecureRangeId;

typedef enum
{
    E_SEAL_DBBUS,
    E_SEAL_MCU51,
    E_SEAL_CPU2,
    E_SEAL_VD_R2,
    E_SEAL_SECURE_R2,
    E_SEAL_SC,
    E_SEAL_CMDQ,
    E_SEAL_HEMCU,
    E_SEAL_PROCESSOR_NUM,
}eSeal_ProcessorId ;

typedef enum
{
    E_SEAL_NONE                                =0,
    E_SEAL_DUMMY                               =1,
    E_SEAL_RIU_DBG_PROT_NONPM                  =2,
    E_SEAL_MSPI0_PROT_NONPM                    =3,
    E_SEAL_MSPI1_PROT_NONPM                    =4,
    E_SEAL_VD_MHEG5_PROT_NONPM                 =5,
    E_SEAL_MAU1_PROT_NONPM                     =6,
    E_SEAL_HIREG_PROT_NONPM                    =7,
    E_SEAL_POR_STATUS_PROT_NONPM               =8,
    E_SEAL_INTR_CPUINT_PROT_NONPM              =9,
    E_SEAL_MIU2_PROT_NONPM                     =10,
    E_SEAL_USB0_PROT_NONPM                     =11,
    E_SEAL_USB1_PROT_NONPM                     =12,
    E_SEAL_BDMA_CH0_PROT_NONPM                 =13,
    E_SEAL_BDMA_CH1_PROT_NONPM                 =14,
    E_SEAL_UART0_PROT_NONPM                    =15,
    E_SEAL_CLKGEN0_PROT_NONPM                  =16,
    E_SEAL_DSCRMB_PROT_NONPM                   =17,
    E_SEAL_UHC1_PROT_NONPM                     =18,
    E_SEAL_MHEG5_PROT_NONPM                    =19,
    E_SEAL_MVD_PROT_NONPM                      =20,
    E_SEAL_MIU_PROT_NONPM                      =21,
    E_SEAL_MVOPSUB_PROT_NONPM                  =22,
    E_SEAL_MVOP_PROT_NONPM                     =23,
    E_SEAL_TSP0_PROT_NONPM                     =24,
    E_SEAL_TSP1_PROT_NONPM                     =25,
    E_SEAL_JPD_PROT_NONPM                      =26,
    E_SEAL_SEMAPH_PROT_NONPM                   =27,
    E_SEAL_MAU0_PROT_NONPM                     =28,
    E_SEAL_ECBRIDGE_PROT_NONPM                 =29,
    E_SEAL_INTR_CTRL_PROT_NONPM                =30,
    E_SEAL_HDMI2_PROT_NONPM                    =31,
    E_SEAL_HVD_PROT_NONPM                      =32,
    E_SEAL_TSP2_PROT_NONPM                     =33,
    E_SEAL_MIPS_PROT_NONPM                     =34,
    E_SEAL_CHIP_PROT_NONPM                     =35,
    E_SEAL_GOP_PROT_NONPM                      =36,
    E_SEAL_EMAC0_PROT_NONPM                    =37,
    E_SEAL_EMAC1_PROT_NONPM                    =38,
    E_SEAL_EMAC2_PROT_NONPM                    =39,
    E_SEAL_EMAC3_PROT_NONPM                    =40,
    E_SEAL_UHC0_PROT_NONPM                     =41,
    E_SEAL_ADC_ATOP_PROT_NONPM                 =42,
    E_SEAL_ADC_DTOP_PROT_NONPM                 =43,
    E_SEAL_HDMI_PROT_NONPM                     =44,
    E_SEAL_GE0_PROT_NONPM                      =45,
    E_SEAL_SMART_PROT_NONPM                    =46,
    E_SEAL_CI_PROT_NONPM                       =47,
    E_SEAL_CHIPGPIO_PROT_NONPM                 =48,
    E_SEAL_VP6_PROT_NONPM                      =49,
    E_SEAL_LDM_DMA0_PROT_NONPM                 =50,
    E_SEAL_LDM_DMA1_PROT_NONPM                 =51,
    E_SEAL_SC0_PROT_NONPM                      =52,
    E_SEAL_SC1_PROT_NONPM                      =53,
    E_SEAL_SC2_PROT_NONPM                      =54,
    E_SEAL_SC3_PROT_NONPM                      =55,
    E_SEAL_SC4_PROT_NONPM                      =56,
    E_SEAL_CLKGEN1_PROT_NONPM                  =57,
    E_SEAL_MAILBOX_PROT_NONPM                  =58,
    E_SEAL_MIIC_PROT_NONPM                     =59,
    E_SEAL_PCM_PROT_NONPM                      =60,
    E_SEAL_VDMCU51_IF_PROT_NONPM               =61,
    E_SEAL_DMDMCU51_IF_PROT_NONPM              =62,
    E_SEAL_URDMA_PROT_NONPM                    =63,
    E_SEAL_AFEC_PROT_NONPM                     =64,
    E_SEAL_COMB_PROT_NONPM                     =65,
    E_SEAL_VBI_PROT_NONPM                      =66,
    E_SEAL_SCM_PROT_NONPM                      =67,
    E_SEAL_UTMI2_PROT_NONPM                    =68,
    E_SEAL_PATGEN_PROT_NONPM                   =69,
    E_SEAL_UTMI1_PROT_NONPM                    =70,
    E_SEAL_UTMI_PROT_NONPM                     =71,
    E_SEAL_VE_0_PROT_NONPM                     =72,
    E_SEAL_REG_PIU_NONPM_PROT_NONPM            =73,
    E_SEAL_VE_1_PROT_NONPM                     =74,
    E_SEAL_VE_2_PROT_NONPM                     =75,
    E_SEAL_MPIF_PROT_NONPM                     =76,
    E_SEAL_GPD_PROT_NONPM                      =77,
    E_SEAL_UART1_PROT_NONPM                    =78,
    E_SEAL_UART2_PROT_NONPM                    =79,
    E_SEAL_FUART_PROT_NONPM                    =80,
    E_SEAL_GE1_PROT_NONPM                      =81,
    E_SEAL_G3D_PROT_NONPM                      =82,
    E_SEAL_DVI_ATOP_PROT_NONPM                 =83,
    E_SEAL_DVI_DTOP_PROT_NONPM                 =84,
    E_SEAL_DVIEQ_PROT_NONPM                    =85,
    E_SEAL_HDCP_PROT_NONPM                     =86,
    E_SEAL_NR_HSD_PROT_NONPM                   =87,
    E_SEAL_ANA_MISC_PROT_NONPM                 =88,
    E_SEAL_MIU_ATOP_PROT_NONPM                 =89,
    E_SEAL_NR_PROT_NONPM                       =90,
    E_SEAL_DI_PROT_NONPM                       =91,
    E_SEAL_MFE0_PROT_NONPM                     =92,
    E_SEAL_MFE1_PROT_NONPM                     =93,
    E_SEAL_ADC_DTOPB_PROT_NONPM                =94,
    E_SEAL_NFIE0_PROT_NONPM                    =95,
    E_SEAL_NFIE1_PROT_NONPM                    =96,
    E_SEAL_NFIE2_PROT_NONPM                    =97,
    E_SEAL_ON0_PROT_NONPM                      =98,
    E_SEAL_ON1_PROT_NONPM                      =99,
    E_SEAL_MIIC0_PROT_NONPM                    =100,
    E_SEAL_MIIC1_PROT_NONPM                    =101,
    E_SEAL_MIIC2_PROT_NONPM                    =102,
    E_SEAL_MIIC3_PROT_NONPM                    =103,
    E_SEAL_CLKGEN_DMD_PROT_NONPM               =104,
    E_SEAL_DEMOD_0_PROT_NONPM                  =105,
    E_SEAL_DEMOD_1_PROT_NONPM                  =106,
    E_SEAL_DEMOD_2_PROT_NONPM                  =107,
    E_SEAL_DEMOD_3_PROT_NONPM                  =108,
    E_SEAL_DEMOD_4_PROT_NONPM                  =109,
    E_SEAL_DEMOD_5_PROT_NONPM                  =110,
    E_SEAL_DEMOD_6_PROT_NONPM                  =111,
    E_SEAL_DEMOD_7_PROT_NONPM                  =112,
    E_SEAL_DMD_ANA_MISC_PROT_NONPM             =113,
    E_SEAL_AUR20_PROT_NONPM                    =114,
    E_SEAL_VIVALDI0_PROT_NONPM                 =115,
    E_SEAL_VIVALDI1_PROT_NONPM                 =116,
    E_SEAL_VIVALDI2_PROT_NONPM                 =117,
    E_SEAL_VIVALDI3_PROT_NONPM                 =118,
    E_SEAL_VIVALDI4_PROT_NONPM                 =119,
    E_SEAL_VIVALDI5_PROT_NONPM                 =120,
    E_SEAL_AUR21_PROT_NONPM                    =121,
    E_SEAL_AUR22_PROT_NONPM                    =122,
    E_SEAL_DVI_ATOP_1_PROT_NONPM               =123,
    E_SEAL_DVI_DTOP_1_PROT_NONPM               =124,
    E_SEAL_DVIEQ_1_PROT_NONPM                  =125,
    E_SEAL_HDCP_1_PROT_NONPM                   =126,
    E_SEAL_DVI_ATOP_2_PROT_NONPM               =127,
    E_SEAL_DVI_DTOP_2_PROT_NONPM               =128,
    E_SEAL_DVIEQ_2_PROT_NONPM                  =129,
    E_SEAL_HDCP_2_PROT_NONPM                   =130,
    E_SEAL_DVI_PS_PROT_NONPM                   =131,
    E_SEAL_DVI_DTOP_3_PROT_NONPM               =132,
    E_SEAL_DVIEQ_3_PROT_NONPM                  =133,
    E_SEAL_HDCP_3_PROT_NONPM                   =134,
    E_SEAL_USB2_PROT_NONPM                     =135,
    E_SEAL_UHC2_PROT_NONPM                     =136,
    E_SEAL_DRM_SECURE_PROT_NONPM               =137,
    E_SEAL_DSCRMB2_PROT_NONPM                  =138,
    E_SEAL_DSCRMB3_PROT_NONPM                  =139,
    E_SEAL_GPD0_PROT_NONPM                     =140,
    E_SEAL_GPD1_PROT_NONPM                     =141,
    E_SEAL_GOP4G_0_PROT_NONPM                  =142,
    E_SEAL_GOP4G_1_PROT_NONPM                  =143,
    E_SEAL_GOP4G_ST_PROT_NONPM                 =144,
    E_SEAL_GOP2G_0_PROT_NONPM                  =145,
    E_SEAL_GOP2G_1_PROT_NONPM                  =146,
    E_SEAL_GOP2G_ST_PROT_NONPM                 =147,
    E_SEAL_GOP1G_0_PROT_NONPM                  =148,
    E_SEAL_GOP1G_1_PROT_NONPM                  =149,
    E_SEAL_GOP1G_ST_PROT_NONPM                 =150,
    E_SEAL_GOP1GX_0_PROT_NONPM                 =151,
    E_SEAL_GOP1GX_1_PROT_NONPM                 =152,
    E_SEAL_GOP1GX_ST_PROT_NONPM                =153,
    E_SEAL_GOPD_PROT_NONPM                     =154,
    E_SEAL_SPARE0_PROT_NONPM                   =155,
    E_SEAL_SPARE1_PROT_NONPM                   =156,
    E_SEAL_CA9PAT_PROT_NONPM                   =157,
    E_SEAL_USB30PHY_DTOP_PROT_NONPM            =158,
    E_SEAL_USB30PHY_ATOP_PROT_NONPM            =159,
    E_SEAL_UTMI3_PROT_NONPM                    =160,
    E_SEAL_USB3INDCTL_PROT_NONPM               =161,
    E_SEAL_USB3TOP_PROT_NONPM                  =162,
    E_SEAL_ALBANY0_PROT_NONPM                  =163,
    E_SEAL_ALBANY1_PROT_NONPM                  =164,
    E_SEAL_SEC_R2_PROT_NONPM                   =165,
    E_SEAL_SEC_MAU0_PROT_NONPM                 =166,
    E_SEAL_MOBF_PROT_NONPM                     =167,
    E_SEAL_DC_SCL_PROT_NONPM                   =168,
    E_SEAL_JPD1_PROT_NONPM                     =169,
    E_SEAL_JPD2_PROT_NONPM                     =170,
    E_SEAL_JPD3_PROT_NONPM                     =171,
    E_SEAL_CMDQ_PROT_NONPM                     =172,
    E_SEAL_MSC_PROT_NONPM                      =173,
    E_SEAL_GPUAPB_PROT_NONPM                   =174,
    E_SEAL_X32_USB3XHCI_PROT_NONPM             =175,
    E_SEAL_USBBC0_PROT_NONPM                   =176,
    E_SEAL_USBBC1_PROT_NONPM                   =177,
    E_SEAL_USBBC2_PROT_NONPM                   =178,
    E_SEAL_USB3_BC0_PROT_NONPM                 =179,
    E_SEAL_MHL_TMDS_PROT_NONPM                 =180,
    E_SEAL_HDCPKEY_PROT_NONPM                  =181,
    E_SEAL_ACP_PROT_NONPM                      =182,
    E_SEAL_SPARE2_PROT_NONPM                   =183,
    E_SEAL_SPARE3_PROT_NONPM                   =184,
    E_SEAL_TSP_DUMMY_PROT_NONPM                =185,
    E_SEAL_CODEC_DUMMY_PROT_NONPM              =186,
    E_SEAL_MHEG5_DUMMY_PROT_NONPM              =187,
    E_SEAL_DSCRMB4_PROT_NONPM                  =188,
    E_SEAL_MENULOAD_PROT_PM                    =189,
    E_SEAL_GDMA_PROT_PM                        =190,
    E_SEAL_DDC_PROT_PM                         =191,        
    E_SEAL_ISP_PROT_PM                         =192,
    E_SEAL_FSP_PROT_PM                         =193,
    E_SEAL_QSPI_PROT_PM                        =194,
    E_SEAL_PM_SLEEP_PROT_PM                    =195,
    E_SEAL_PM_GPIO_PROT_PM                     =196,
    E_SEAL_MCU_PROT_PM                         =197,        
    E_SEAL_PM_CEC_PROT_PM                      =198,
    E_SEAL_PM_RTC_PROT_PM                      =199,
    E_SEAL_PM_RTC2_PROT_PM                     =200,
    E_SEAL_PM_SAR_PROT_PM                      =201,
    E_SEAL_PM_AV_LINK_PROT_PM                  =202,
    E_SEAL_PM_TOP_PROT_PM                      =203,        
    E_SEAL_MHL_CBUS_PROT_PM                    =204,
    E_SEAL_EFUSE_PROT_PM                       =205,
    E_SEAL_IRQ_PROT_PM                         =206,
    E_SEAL_CACHE_PROT_PM                       =207,
    E_SEAL_XDMIU_PROT_PM                       =208,
    E_SEAL_PM_MISC_PROT_PM                     =209,        
    E_SEAL_PM_MHL_CBUS_PROT_PM                 =210,
    E_SEAL_WDT_PROT_PM                         =211,
    E_SEAL_TIMER0_PROT_PM                      =212,
    E_SEAL_TIMER1_PROT_PM                      =213,
    E_SEAL_SEC_KEY_PROT_PM                     =214,
    E_SEAL_DID_KEY_PROT_PM                     =215,        
    E_SEAL_REG_PIU_MISC_0_PROT_PM              =216,
    E_SEAL_IR_PROT_PM                          =217,
    E_SEAL_PM_SPARE0_PROT_PM                   =218, 
    E_SEAL_PM_SPARE1_PROT_PM                   =219,
    E_SEAL_FUART1_PROT_NONPM                   =220,
    E_SEAL_URDMA1_PROT_NONPM                   =221,
    E_SEAL_UPLL0_PROT_NONPM                    =222,
    E_SEAL_UPLL1_PROT_NONPM                    =223,
    E_SEAL_UART3_PROT_NONPM                    =224,
    E_SEAL_CLKGEN2_PROT_NONPM                  =225,
    E_SEAL_VDMCU51_1_IF_PROT_NONPM             =226,
    E_SEAL_ADC_ATOPB_PROT_NONPM                =227,
    E_SEAL_UART4_PROT_NONPM                    =228,
    E_SEAL_ANA_MISC_GMAC_PROT_NONPM            =229,
    E_SEAL_USB30PHY_DTOP_M_0_PROT_NONPM        =230,
    E_SEAL_USB30PHY_DTOP_M_1_PROT_NONPM        =231,
    E_SEAL_USB3_PROT_NONPM                     =232,
    E_SEAL_TSO_PROT_NONPM                      =233,
    E_SEAL_SDIO0_PROT_NONPM                    =234,
    E_SEAL_MIU_ARB256_PROT_NONPM               =235,
    E_SEAL_HDMITX_MISC_PROT_NONPM              =236,
    E_SEAL_MIIC4_PROT_NONPM                    =237,
    E_SEAL_MIIC5_PROT_NONPM                    =238,
    E_SEAL_HDMITX_VIDEO_PROT_NONPM             =239,
    E_SEAL_HDMITX_AUDIO_PROT_NONPM             =240,
    E_SEAL_USB30PHY_ATOP_M_0_PROT_NONPM        =241,
    E_SEAL_USB30PHY_ATOP_M_1_PROT_NONPM        =242,
    E_SEAL_UTMISS0_PROT_NONPM                  =243,
    E_SEAL_UTMISS1_PROT_NONPM                  =244,
    E_SEAL_UHC3_PROT_NONPM                     =245,
    E_SEAL_SDIO1_PROT_NONPM                    =246,
    E_SEAL_SDIO2_PROT_NONPM                    =247,
    E_SEAL_USBBC3_PROT_NONPM                   =248,
    E_SEAL_USB3_BC1_PROT_NONPM                 =249,
    E_SEAL_SECURERANGE0_PROT_NONPM             =250,
    E_SEAL_SECURERANGE1_PROT_NONPM             =251,
    E_SEAL_TZPC_NONPM_PROT_NONPM               =252,
    E_SEAL_NFIE3_PROT_NONPM                    =253,
    E_SEAL_DSCRMB5_PROT_NONPM                  =254,
    E_SEAL_EMMC_PLL_PROT_NONPM                 =255,
    E_SEAL_VIVALDI6_PROT_NONPM                 =256,
    E_SEAL_VIVALDI7_PROT_NONPM                 =257,
    E_SEAL_GMAC0_PROT_NONPM                    =258,
    E_SEAL_GMAC1_PROT_NONPM                    =259,
    E_SEAL_GMAC2_PROT_NONPM                    =260,
    E_SEAL_GMAC3_PROT_NONPM                    =261,
    E_SEAL_GMAC4_PROT_NONPM                    =262,
    E_SEAL_PCM2_PROT_NONPM                     =263,
    E_SEAL_TSP3_PROT_NONPM                     =264,
    E_SEAL_HEVC0_PROT_NONPM                    =265,
    E_SEAL_HEVC1_PROT_NONPM                    =266,
    E_SEAL_DYN_SCL_PROT_NONPM                  =267,
    E_SEAL_X32_MVD1_PROT_NONPM                 =268,
    E_SEAL_X32_MVD2_PROT_NONPM                 =269,
    E_SEAL_X32_MVD3_PROT_NONPM                 =270,
    E_SEAL_X32_MVD4_PROT_NONPM                 =271,
    E_SEAL_CODEC_MRQ_PROT_NONPM                =272,
    E_SEAL_MIU3_PROT_NONPM                     =273,
    E_SEAL_MIU_ATOP2_PROT_NONPM                =274,
    E_SEAL_X32_HVD0_PROT_NONPM                 =275,
    E_SEAL_X32_HVD1_PROT_NONPM                 =276,
    E_SEAL_X32_HVD2_PROT_NONPM                 =277,
    E_SEAL_X32_HVD3_PROT_NONPM                 =278,
    E_SEAL_X32_HVD4_PROT_NONPM                 =279,
    E_SEAL_X32_HVD5_PROT_NONPM                 =280,
    E_SEAL_X32_HVD6_PROT_NONPM                 =281,
    E_SEAL_X32_HVD7_PROT_NONPM                 =282,
    E_SEAL_X32_EVD0_PROT_NONPM                 =283,
    E_SEAL_X32_EVD1_PROT_NONPM                 =284,
    E_SEAL_X32_EVD2_PROT_NONPM                 =285,
    E_SEAL_X32_EVD3_PROT_NONPM                 =286,
    E_SEAL_X32_EVD4_PROT_NONPM                 =287,
    E_SEAL_X32_EVD5_PROT_NONPM                 =288,
    E_SEAL_X32_EVD6_PROT_NONPM                 =289,
    E_SEAL_X32_EVD7_PROT_NONPM                 =290,
    E_SEAL_X32_EVD8_PROT_NONPM                 =291,
    E_SEAL_X32_GPUAPB0_PROT_NONPM              =292,
    E_SEAL_X32_GPUAPB1_PROT_NONPM              =293,
    E_SEAL_X32_GPUAPB2_PROT_NONPM              =294,
    E_SEAL_TIMER2_PROT_PM                      =295, 
    E_SEAL_ALBANY0_PROT_PM                     =296, 
    E_SEAL_ALBANY1_PROT_PM                     =297, 
    E_SEAL_ALBANY2_PROT_PM                     =298, 
    E_SEAL_NORPF_PROT_NONPM                    =299,
    E_SEAL_PM_PROT_NONPM                       =300,
    E_SEAL_ON_PROT_NONPM                       =301,
    E_SEAL_SWCD_PROT_NONPM                     =302,
    E_SEAL_ALBANY2_PROT_NONPM                  =303,
    E_SEAL_TZPC_PROT_PM                        =304, 
    E_SEAL_SPARE4_PROT_NONPM                   =305,
    E_SEAL_SPARE5_PROT_NONPM                   =306,
    E_SEAL_JPD4_PROT_NONPM                     =307,
    E_SEAL_RIU_DBG_PROT_PM                     =308, 
    E_SEAL_UHC4_PROT_NONPM                     =309,
    E_SEAL_USB4_PROT_NONPM                     =310,
    E_SEAL_UTMI4_PROT_NONPM                    =311,
    E_SEAL_USBBC4_PROT_NONPM                   =312,
    E_SEAL_UTMISS_PROT_NONPM                   =313,
    E_SEAL_VDR2_PROT_NONPM                     =314,
    E_SEAL_INTR_CTRL1_PROT_NONPM               =315,
    E_SEAL_L3_AXI_PROT_NONPM                   =316,
    E_SEAL_MCU_ARM_PROT_NONPM                  =317,
    E_SEAL_VDMCU51_1_IF_NONPM                  =318,
    E_SEAL_SC_GP1_NONPM                        =319,
    E_SEAL_CHIPGPIO1_NONPM                     =320,
    E_SEAL_GPU_NONPM                           =321,
    E_SEAL_ANA_MISC2_NONPM                     =322,
    E_SEAL_AU_MAU_NONPM                        =323,
    E_SEAL_AU_GDMA_NONPM                       =324,
    E_SEAL_USB3_NONPM                          =325,
    E_SEAL_OTG0_NONPM                          =326,
    E_SEAL_OTG1_NONPM                          =327,
    E_SEAL_OTG2_NONPM                          =328,
    E_SEAL_OTG3_NONPM                          =329,
    E_SEAL_SECURERANGE2_NONPM                  =330,
    E_SEAL_TZPC_NONPM2_NONPM                   =331,
    E_SEAL_TSO1_NONPM                          =332,
    E_SEAL_MSC1_NONPM                          =333,
    E_SEAL_EVD_NONPM                           =334,
    E_SEAL_MIU_ARB_NONPM                       =335,
    E_SEAL_TSP4_NONPM                          =336,
    E_SEAL_DVI_ATOP3_NONPM                     =337,
    E_SEAL_HDMI_P4_NONPM                       =338,
    E_SEAL_HDMI2_P4_NONPM                      =339,
    E_SEAL_DVI_ATOP_P4_NONPM                   =340,
    E_SEAL_DVI_DTOP_P4_NONPM                   =341,
    E_SEAL_DVI_EQ_P4_NONPM                     =342,
    E_SEAL_HDCP_P4_NONPM                       =343,
    E_SEAL_DVI_POWERSAVE_P4_NONPM              =344,
    E_SEAL_MIU3_NONPM                          =345,
    E_SEAL_MIU_ATOP3_NONPM                     =346,
    E_SEAL_MIU_ARB2_NONPM                      =347,
    E_SEAL_MIU_ARB3_NONPM                      =348,
    E_SEAL_MIU4_NONPM                          =349,
    E_SEAL_MIU_ATOP4_NONPM                     =350,
    E_SEAL_MIU_ARB4_NONPM                      =351,
    E_SEAL_GE2_NONPM                           =352,
    E_SEAL_GE3_NONPM                           =353,
    E_SEAL_HDCP22_P0_NONPM                     =354,
    E_SEAL_HDCP22_P1_NONPM                     =355,
    E_SEAL_HDCP22_P2_NONPM                     =356,
    E_SEAL_HDCP22_P3_NONPM                     =357,
    E_SEAL_HDCP22_P4_NONPM                     =358,
    E_SEAL_AU_R2_1_NONPM                       =359,
    E_SEAL_AU_MAU_1_NONPM                      =360,
    E_SEAL_AU_GDMA_1_NONPM                     =361,
    E_SEAL_VD_EVD_R2_NONPM                     =362,
    E_SEAL_MAU_EVD_NONPM                       =363,
    E_SEAL_MAU1_LV2_0_NONPM                    =364,
    E_SEAL_MAU1_LV2_1_NONPM                    =365,
    E_SEAL_MAU_EVD_LV2_0_NONPM                 =366,
    E_SEAL_MAU_EVD_LV2_1_NONPM                 =367,
    E_SEAL_SEC_MAU_LV2_0_NONPM                 =368,
    E_SEAL_SEC_MAU_LV2_1_NONPM                 =369,
    E_SEAL_TSP5_NONPM                          =370,
    E_SEAL_X32_USB3XHCI_NONPM                  =371,
    E_SEAL_X32_GPUAPB0_NONPM                   =372,
    E_SEAL_X32_GPUAPB1_NONPM                   =373,
    E_SEAL_X32_GPUAPB2_NONPM                   =374,
    E_SEAL_SECURERANGE3_PROT_NONPM             =375,
    E_SEAL_HIREG_EVD_PROT_NONPM                =376,
    E_SEAL_PM_RTC0_PROT_PM                     =377,
    E_SEAL_PM_RTC1_PROT_PM                     =378,
    E_SEAL_PM_CEC1_PROT_PM                     =379,
    E_SEAL_PM_CEC2_PROT_PM                     =380,
    E_SEAL_PM_CEC3_PROT_PM                     =381,
    E_SEAL_IP_NUM                              =382
}eSeal_IP;

typedef enum
{
    E_SEAL_LOCK_NONE                           =0,
    E_SEAL_LOCK_DUMMY                          =1,
    E_SEAL_VD_R2_INST_BUF                      =2,
    E_SEAL_HK_R2_INST_BUF                      =3,
    E_SEAL_AUDIO_DEC_R2_INST_BUF               =4,
    E_SEAL_AUDIO_DEC_ES_BUF                    =5,
    E_SEAL_AUDIO_ENC_R2_INST_BUF               =6,
    E_SEAL_AUDIO_ENC_ES_BUF                    =7,
    E_SEAL_HVD_ES0_BUF                         =8,
    E_SEAL_HVD_ES1_BUF                         =9,
    E_SEAL_HVD_ES2_BUF                         =10,
    E_SEAL_MFE0_ES_BUF                         =11,
    E_SEAL_MFE1_ES_BUF                         =12,
    E_SEAL_TSP_AEON_INS_BUF                    =13,
    E_SEAL_PVR_BUF                             =14,
    E_SEAL_SECURE_RANGE                        =15,
    E_SEAL_SC_BUF                              =16,
    E_SEAL_GE_BUF                              =17,
    E_SEAL_SC_WP_DIPW                          =18,
    E_SEAL_SC_RP_DIPW                          =19,
    E_SEAL_SC_WP_DIPR                          =20,
    E_SEAL_SC_RP_DIPR                          =21,
    E_SEAL_CIPHERENG_WP_SYSKEY                 =22,
    E_SEAL_CIPHERENG_RP_SYSKEY                 =23,
    E_SEAL_DSCRMB_WP_RIV0                      =24,
    E_SEAL_DSCRMB_RP_RIV0                      =25,
    E_SEAL_DSCRMB_WP_RIV1                      =26,
    E_SEAL_DSCRMB_RP_RIV1                      =27,
    E_SEAL_DSCRMB_WP_WDATA                     =28,
    E_SEAL_DSCRMB_RP_WDATA                     =29,
    E_SEAL_DSCRMB_RP_RDATA                     =30,
    E_SEAL_RNG_PROTECT                         =31,
    E_SEAL_RSA_PROTECT                         =32,
    E_SEAL_SHA_PROTECT                         =33,
    E_SEAL_MVD_WR_PROTN_0                      =34,
    E_SEAL_MVD_WR_PROTN_1                      =35,
    E_SEAL_MVD_WR_PROTN_2                      =36,
    E_SEAL_EVD_0_WR_PROTN_0                    =37,
    E_SEAL_EVD_1_WR_PROTN_0                    =38,
    E_SEAL_MHEG5_WR_PROTN_0                    =39,
    E_SEAL_TSO_WP_TSOFI                        =40,
    E_SEAL_TSO_RP_TSOFI                        =41,
    E_SEAL_MMFI_WP_MMFI0                       =42,
    E_SEAL_MMFI_RP_MMFI0                       =43,
    E_SEAL_MMFI_WP_MMFI1                       =44,
    E_SEAL_MMFI_RP_MMFI1                       =45,
    E_SEAL_TSP0_WP_PVR                         =46,
    E_SEAL_TSP0_RP_PVR                         =47,
    E_SEAL_TSP0_WP_PVR1                        =48,
    E_SEAL_TSP0_RP_PVR1                        =49,
    E_SEAL_TSP0_WP_FILEIN                      =50,
    E_SEAL_TSP0_RP_FILEIN                      =51,
    E_SEAL_TSP0_WP_QMEM                        =52,
    E_SEAL_TSP0_RP_QMEM                        =53,
    E_SEAL_TSP0_WP_FW                          =54,
    E_SEAL_TSP0_RP_FW                          =55,
    E_SEAL_VE_WP                               =56,
    E_SEAL_VE_RP                               =57,
    E_SEAL_SC_WP_OD                            =58,
    E_SEAL_SC_RP_OD                            =59,
    E_SEAL_SC_WP_SCM_M                         =60,
    E_SEAL_SC_RP_SCM_M                         =61,
    E_SEAL_SC_WP_SCM_S                         =62,
    E_SEAL_SC_RP_SCM_S                         =63,
    E_SEAL_SC_WP_PDW0                          =64,
    E_SEAL_SC_RP_PDW0                          =65,
    E_SEAL_SC_WP_PDW1                          =66,
    E_SEAL_SC_RP_PDW1                          =67,
    E_SEAL_SC_WP_OPW                           =68,
    E_SEAL_SC_RP_OPW                           =69,
    E_SEAL_GOPD_PROTN                          =70,
    E_SEAL_GE0_SB_PROTN                        =71,
    E_SEAL_GE0_DB_PROTN                        =72,
    E_SEAL_GE1_SB_PROTN                        =73,
    E_SEAL_GE1_DB_PROTN                        =74,
    E_SEAL_AUDIO_LCL_R2_WR_PROTN_0             =75,
    E_SEAL_AUDIO_LCL_R2_WR_PROTN_1             =76,
    E_SEAL_AUDIO_LCL_R2_WR_PROTN_2             =77,
    E_SEAL_AUDIO_LCL_R2_WR_PROTN_3             =78,
    E_SEAL_AUDIO_SCL_R2_WR_PROTN_0             =79,
    E_SEAL_AUDIO_SCL_R2_WR_PROTN_1             =80,
    E_SEAL_AUDIO_SCL_R2_WR_PROTN_2             =81,
    E_SEAL_AUDIO_SCL_R2_WR_PROTN_3             =82,
    E_SEAL_SECURE_R2_WR_PROTN_0                =83,
    E_SEAL_SECURE_R2_WR_PROTN_1                =84,
    E_SEAL_SECURE_R2_WR_PROTN_2                =85,
    E_SEAL_SECURE_R2_WR_PROTN_3                =86,
    E_SEAL_EVD_R2_WR_PROTN_0                   =87,
    E_SEAL_EVD_R2_WR_PROTN_1                   =88,
    E_SEAL_EVD_R2_WR_PROTN_2                   =89,
    E_SEAL_EVD_R2_WR_PROTN_3                   =90,
    E_SEAL_HVD_R2_WR_PROTN_0                   =91,
    E_SEAL_HVD_R2_WR_PROTN_1                   =92,
    E_SEAL_HVD_R2_WR_PROTN_2                   =93,
    E_SEAL_HVD_R2_WR_PROTN_3                   =94,
    E_SEAL_AUDIO_DSP_ES_PROTN                  =95,
    E_SEAL_AUDIO_DSP_CACHE_PROTN               =96,
    E_SEAL_EVD_0_WR_PROTN_1                    =97,
    E_SEAL_EVD_1_WR_PROTN_1                    =98,
    E_SEAL_LOCK_NUM                            =99
}eSeal_Lock;

typedef struct
{
    MS_BOOL bIsHit;
    MS_U8   u8MiuDev;
    MS_U8   u8SecureRangeId;
    MS_U8   u8ClientId;
    MS_BOOL bIsSecure;
    MS_BOOL bIsWrite;
    MS_U64  u64HitAddr;
}Seal_PortectInfo;

typedef struct
{
    MS_U8   u8MiuDev;
    MS_U8   u8SecureRangeId;
    MS_U64  u64StartAddr;
    MS_U64  u64EndAddr;
    MS_U32  u32Attribute;
}Seal_SecureRangeInfo;

typedef void (*SEAL_CB_FUNC)(InterruptNum eIntNum);
//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_SEAL_Init(void);
MS_BOOL MDrv_Seal_SecureRangeSet(MS_U8 u8SecureRangeId ,MS_U64 u64StartAddr, MS_U64 u64EndAddr, MS_U32 u32Attribute);
MS_BOOL MDrv_Seal_SecureRangeQuery(MS_U8 u8MiuDev, MS_U8 u8SecureRangeId, Seal_SecureRangeInfo *pSecureRangeInfo);
MS_BOOL MDrv_Seal_IMI_RangeSet(MS_U32 u32StartAddr, MS_U32 u32EndAddr, MS_BOOL bEnable);
MS_BOOL MDrv_Seal_GetHittedInfo(MS_U8 u8MiuDev, Seal_PortectInfo *pInfo);
MS_BOOL MDrv_Seal_SecureRangeLock(MS_U8 u8MiuDev, MS_U8 u8SecureRangeId);
MS_BOOL MDrv_Seal_NonSecureProcessorSet(MS_U8 u8ProcessorId, MS_BOOL bNonEnable);
MS_BOOL MDrv_Seal_NonSecureProcessorQuery(MS_U8 u8ProcessorId, MS_BOOL *bNonSecure);
MS_BOOL MDrv_Seal_SecureSlaveSet(MS_U32 u32SlaveId, MS_BOOL bSecure);
MS_BOOL MDrv_Seal_SecureSlaveQuery(MS_U32 u32SlaveId, MS_BOOL *pSecure);
MS_BOOL MDrv_Seal_SecureMasterSet(MS_U32 u32MasterId, MS_BOOL bSecure);
MS_BOOL MDrv_Seal_SecureMasterQuery(MS_U32 u32MasterId, MS_BOOL *pSecure);
MS_U32 MDrv_Seal_SetPowerState(EN_POWER_MODE u16PowerState);
MS_BOOL MDrv_Seal_BufferLock(MS_U8 u8BufferLockId, MS_BOOL bLock);
MS_BOOL MDrv_Seal_ENInterrupt(MS_BOOL bEnable);
MS_BOOL MDrv_Seal_AttachCallbackFunc(SEAL_CB_FUNC pSEALCBFunc);
MS_BOOL MDrv_Seal_DispatchCallbackFunc(void);
#ifdef __cplusplus
}
#endif

#endif // _DRV_SEAL_H_
