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
// Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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

#ifndef _MIUSEL_EIFFEL_2MIU_H_
#define _MIUSEL_EIFFEL_2MIU_H_

//----------------------------------------------------------
//priority setting: 0:highest priority, 3:lowest priority
//----------------------------------------------------------
//MIU group priority
//----------------------------------------------------------

#define GROUP_0                     0
#define GROUP_1                     1
#define GROUP_2                     2
#define GROUP_3                     3

#define MIU0_1ST_PRIORITY           GROUP_3
#define MIU0_2ND_PRIORITY           GROUP_0
#define MIU0_3RD_PRIORITY           GROUP_1
#define MIU0_4TH_PRIORITY           GROUP_2

#define MIU1_1ST_PRIORITY           GROUP_3
#define MIU1_2ND_PRIORITY           GROUP_1
#define MIU1_3RD_PRIORITY           GROUP_0
#define MIU1_4TH_PRIORITY           GROUP_2

#define MIU0_GROUP_PRIORITY         ((MIU0_4TH_PRIORITY << 6) | (MIU0_3RD_PRIORITY << 4) | (MIU0_2ND_PRIORITY << 2) | (MIU0_1ST_PRIORITY) )
#define MIU1_GROUP_PRIORITY         ((MIU1_4TH_PRIORITY << 6) | (MIU1_3RD_PRIORITY << 4) | (MIU1_2ND_PRIORITY << 2) | (MIU1_1ST_PRIORITY) )

////////////////////////////////////////////////////////////////////////////////
// MIU assignment   0: MIU0, 1: MIU1  2:IP_
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------
//
//----------------------------------------
//Group 0
#define  MIU_CLIENT_NONE                0
#define  MIU_CLIENT_VIVALDI9_DECODER_R  0
#define  MIU_CLIENT_VIVALDI9_SE_R       0
#define  MIU_CLIENT_USB3_RW             0
#define  MIU_CLIENT_SECURE_R2_RW        0
#define  MIU_CLIENT_AU_R2_RW            0
#define  MIU_CLIENT_MAU_RW              1
#define  MIU_CLIENT_PM51_RW             0
#define  MIU_CLIENT_MHEG5_ICACHE_RW     1
#define  MIU_CLIENT_USB_UHC0_RW         0
#define  MIU_CLIENT_USB_UHC1_RW         0
#define  MIU_CLIENT_USB_UHC2_RW         0
#define  MIU_CLIENT_MVD_BBU_RW          1
#define  MIU_CLIENT_EMAC_RW             0
#define  MIU_CLIENT_BDMA_RW             2
#define  MIU_CLIENT_SC_2D3D_RW          0

// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop0_in_MIU1       (((MIU_CLIENT_VIVALDI9_DECODER_R    == 1) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_VIVALDI9_SE_R         == 1) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_USB3_RW               == 1) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_SECURE_R2_RW          == 1) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_AU_R2_RW              == 1) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_MAU_RW                == 1) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_PM51_RW               == 1) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_MHEG5_ICACHE_RW       == 1) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_USB_UHC0_RW           == 1) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_USB_UHC1_RW           == 1) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_USB_UHC2_RW           == 1) ? (0x01 << 11) : 0) | \
                                     ((MIU_CLIENT_MVD_BBU_RW            == 1) ? (0x01 << 12) : 0) | \
                                     ((MIU_CLIENT_EMAC_RW               == 1) ? (0x01 << 13) : 0) | \
                                     ((MIU_CLIENT_BDMA_RW               == 1) ? (0x01 << 14) : 0) | \
                                     ((MIU_CLIENT_SC_2D3D_RW            == 1) ? (0x01 << 15) : 0))

// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop0_in_IP         (((MIU_CLIENT_VIVALDI9_DECODER_R    == 2) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_VIVALDI9_SE_R         == 2) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_USB3_RW               == 2) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_SECURE_R2_RW          == 2) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_AU_R2_RW              == 2) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_MAU_RW                == 2) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_PM51_RW               == 2) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_MHEG5_ICACHE_RW       == 2) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_USB_UHC0_RW           == 2) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_USB_UHC1_RW           == 2) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_USB_UHC2_RW           == 2) ? (0x01 << 11) : 0) | \
                                     ((MIU_CLIENT_MVD_BBU_RW            == 2) ? (0x01 << 12) : 0) | \
                                     ((MIU_CLIENT_EMAC_RW               == 2) ? (0x01 << 13) : 0) | \
                                     ((MIU_CLIENT_BDMA_RW               == 2) ? (0x01 << 14) : 0) | \
                                     ((MIU_CLIENT_SC_2D3D_RW            == 2) ? (0x01 << 15) : 0))

//Group 1
#define  MIU_CLIENT_VIVALDI9_MAD_RW     0
#define  MIU_CLIENT_VIVALDI9_DMA_RW     0
#define  MIU_CLIENT_VIVALDI9_AUDMA_RW   0
#define  MIU_CLIENT_MVOP_128BIT_R       1
#define  MIU_CLIENT_MVOP1_R             1
#define  MIU_CLIENT_SC_DIPW_RW          1
#define  MIU_CLIENT_SC_LOCALDIMING_RW   0
#define  MIU_CLIENT_CMD_QUEUE_RW        0
#define  MIU_CLIENT_TSP_W               0
#define  MIU_CLIENT_TSP_R               0
#define  MIU_CLIENT_VD_TTX_RW           0
#define  MIU_CLIENT_VD_TTXSL_W          0
#define  MIU_CLIENT_VD_COMB_W           0
#define  MIU_CLIENT_VD_COMB_R           0
#define  MIU_CLIENT_VE_W                0
#define  MIU_CLIENT_VE_R                0

// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop1_in_MIU1       (((MIU_CLIENT_VIVALDI9_MAD_RW       == 1) ? (0x01 << 0)  : 0) | \
                                     ((MIU_CLIENT_VIVALDI9_DMA_RW       == 1) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_VIVALDI9_AUDMA_RW     == 1) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_MVOP_128BIT_R         == 1) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_MVOP1_R               == 1) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_SC_DIPW_RW            == 1) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_SC_LOCALDIMING_RW     == 1) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_CMD_QUEUE_RW          == 1) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_TSP_W                 == 1) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_TSP_R                 == 1) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_VD_TTX_RW             == 1) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_VD_TTXSL_W            == 1) ? (0x01 << 11) : 0) | \
                                     ((MIU_CLIENT_VD_COMB_W             == 1) ? (0x01 << 12) : 0) | \
                                     ((MIU_CLIENT_VD_COMB_R             == 1) ? (0x01 << 13) : 0) | \
                                     ((MIU_CLIENT_VE_W                  == 1) ? (0x01 << 14) : 0) | \
                                     ((MIU_CLIENT_VE_R                  == 1) ? (0x01 << 15) : 0))

// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop1_in_IP         (((MIU_CLIENT_VIVALDI9_MAD_RW       == 2) ? (0x01 << 0)  : 0) | \
                                     ((MIU_CLIENT_VIVALDI9_DMA_RW       == 2) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_VIVALDI9_AUDMA_RW     == 2) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_MVOP_128BIT_R         == 2) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_MVOP1_R               == 2) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_SC_DIPW_RW            == 2) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_SC_LOCALDIMING_RW     == 2) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_CMD_QUEUE_RW          == 2) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_TSP_W                 == 2) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_TSP_R                 == 2) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_VD_TTX_RW             == 2) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_VD_TTXSL_W            == 2) ? (0x01 << 11) : 0) | \
                                     ((MIU_CLIENT_VD_COMB_W             == 2) ? (0x01 << 12) : 0) | \
                                     ((MIU_CLIENT_VD_COMB_R             == 2) ? (0x01 << 13) : 0) | \
                                     ((MIU_CLIENT_VE_W                  == 2) ? (0x01 << 14) : 0) | \
                                     ((MIU_CLIENT_VE_R                  == 2) ? (0x01 << 15) : 0))
//group_2
#define  MIU_CLIENT_GE_RW               0
#define  MIU_CLIENT_HVD_BBU_R           1
#define  MIU_CLIENT_HVD_RW              1
#define  MIU_CLIENT_MIIC0_RW            0
#define  MIU_CLIENT_MVD_RW              1
#define  MIU_CLIENT_G3D_RW              0
#define  MIU_CLIENT_GPD_RW              0
#define  MIU_CLIENT_MFE0_W              0
#define  MIU_CLIENT_MFE1_R              0
#define  MIU_CLIENT_NAND_RW             0
#define  MIU_CLIENT_JPD720P_RW          1
#define  MIU_CLIENT_DSCRMB_RW           0
#define  MIU_CLIENT_JPD_RW              1
#define  MIU_CLIENT_TSP_ORZ_RW          0
#define  MIU_CLIENT_TSP_ORZ_W           0
#define  MIU_CLIENT_HISPEED_UART_RW     0

// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop2_in_MIU1       (((MIU_CLIENT_GE_RW                 == 1) ? (0x01 << 0)  : 0) | \
                                     ((MIU_CLIENT_HVD_BBU_R             == 1) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_HVD_RW                == 1) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_MIIC0_RW              == 1) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_MVD_RW                == 1) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_G3D_RW                == 1) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_GPD_RW                == 1) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_MFE0_W                == 1) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_MFE1_R                == 1) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_NAND_RW               == 1) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_JPD720P_RW            == 1) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_DSCRMB_RW             == 1) ? (0x01 << 11) : 0) | \
                                     ((MIU_CLIENT_JPD_RW                == 1) ? (0x01 << 12) : 0) | \
                                     ((MIU_CLIENT_TSP_ORZ_RW            == 1) ? (0x01 << 13) : 0) | \
                                     ((MIU_CLIENT_TSP_ORZ_W             == 1) ? (0x01 << 14) : 0) | \
                                     ((MIU_CLIENT_HISPEED_UART_RW       == 1) ? (0x01 << 15) : 0))

// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop2_in_IP         (((MIU_CLIENT_GE_RW                 == 2) ? (0x01 << 0)  : 0) | \
                                     ((MIU_CLIENT_HVD_BBU_R             == 2) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_HVD_RW                == 2) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_MIIC0_RW              == 2) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_MVD_RW                == 2) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_G3D_RW                == 2) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_GPD_RW                == 2) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_MFE0_W                == 2) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_MFE1_R                == 2) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_NAND_RW               == 2) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_JPD720P_RW            == 2) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_DSCRMB_RW             == 2) ? (0x01 << 11) : 0) | \
                                     ((MIU_CLIENT_JPD_RW                == 2) ? (0x01 << 12) : 0) | \
                                     ((MIU_CLIENT_TSP_ORZ_RW            == 2) ? (0x01 << 13) : 0) | \
                                     ((MIU_CLIENT_TSP_ORZ_W             == 2) ? (0x01 << 14) : 0) | \
                                     ((MIU_CLIENT_HISPEED_UART_RW       == 2) ? (0x01 << 15) : 0))

//group_3
#define  MIU_CLIENT_MIPS_RW             0
#define  MIU_CLIENT_GOP_W               0
#define  MIU_CLIENT_GOP0_R              0
#define  MIU_CLIENT_GOP1_R              0
#define  MIU_CLIENT_GOP2_R              0
#define  MIU_CLIENT_GOP3_R              0
#define  MIU_CLIENT_SC_OPMAIN_RW        0
#define  MIU_CLIENT_SC_IPMAIN_RW        0
#define  MIU_CLIENT_SC_IPSUB_RW         0
#define  MIU_CLIENT_SC_OD_W             0
#define  MIU_CLIENT_SC_OD_R             0
#define  MIU_CLIENT_SC_IPM2_R           0

// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop3_in_MIU1       (((MIU_CLIENT_MIPS_RW               == 1) ? (0x01 << 0)  : 0) | \
                                     ((MIU_CLIENT_GOP_W                 == 1) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_GOP0_R                == 1) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_GOP1_R                == 1) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_GOP2_R                == 1) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_GOP3_R                == 1) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_SC_OPMAIN_RW          == 1) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_SC_IPMAIN_RW          == 1) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_SC_IPSUB_RW           == 1) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_SC_OD_W               == 1) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_SC_OD_R               == 1) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_SC_IPM2_R             == 1) ? (0x01 << 11) : 0))

// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop3_in_IP         (((MIU_CLIENT_MIPS_RW               == 2) ? (0x01 << 0)  : 0) | \
                                     ((MIU_CLIENT_GOP_W                 == 2) ? (0x01 << 1)  : 0) | \
                                     ((MIU_CLIENT_GOP0_R                == 2) ? (0x01 << 2)  : 0) | \
                                     ((MIU_CLIENT_GOP1_R                == 2) ? (0x01 << 3)  : 0) | \
                                     ((MIU_CLIENT_GOP2_R                == 2) ? (0x01 << 4)  : 0) | \
                                     ((MIU_CLIENT_GOP3_R                == 2) ? (0x01 << 5)  : 0) | \
                                     ((MIU_CLIENT_SC_OPMAIN_RW          == 2) ? (0x01 << 6)  : 0) | \
                                     ((MIU_CLIENT_SC_IPMAIN_RW          == 2) ? (0x01 << 7)  : 0) | \
                                     ((MIU_CLIENT_SC_IPSUB_RW           == 2) ? (0x01 << 8)  : 0) | \
                                     ((MIU_CLIENT_SC_OD_W               == 2) ? (0x01 << 9)  : 0) | \
                                     ((MIU_CLIENT_SC_OD_R               == 2) ? (0x01 << 10) : 0) | \
                                     ((MIU_CLIENT_SC_IPM2_R             == 2) ? (0x01 << 11) : 0))

//backward competiable
#define   MIUSEL_FLAG_DNRB_R        SC_IP_MAIN_R
#define   MIUSEL_FLAG_DNRB_RW       (SC_IP_MAIN_R | SC_IP_MAIN_W)

//-----------------------------------------------------------------------------

#endif  //_MIUSEL_EIFFEL_2MIU_H_

