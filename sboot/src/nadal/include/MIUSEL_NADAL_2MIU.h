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

#ifndef _MIUSEL_NADAL_2MIU_H_
#define _MIUSEL_NADAL_2MIU_H_

//----------------------------------------------------------
//priority setting: 0:highest priority, 3:lowest priority
//----------------------------------------------------------
//MIU group priority
//----------------------------------------------------------

#define GROUP_0                         0
#define GROUP_1                         1
#define GROUP_2                         2
#define GROUP_3                         3

#define MIU0_1ST_PRIORITY               GROUP_2
#define MIU0_2ND_PRIORITY               GROUP_0
#define MIU0_3RD_PRIORITY               GROUP_1
#define MIU0_4TH_PRIORITY               GROUP_3

#define MIU1_1ST_PRIORITY               GROUP_1
#define MIU1_2ND_PRIORITY               GROUP_2
#define MIU1_3RD_PRIORITY               GROUP_3
#define MIU1_4TH_PRIORITY               GROUP_0

#define MIU0_GROUP_PRIORITY             ((MIU0_4TH_PRIORITY << 6) | (MIU0_3RD_PRIORITY << 4) | (MIU0_2ND_PRIORITY << 2) | (MIU0_1ST_PRIORITY) )
#define MIU1_GROUP_PRIORITY             ((MIU1_4TH_PRIORITY << 6) | (MIU1_3RD_PRIORITY << 4) | (MIU1_2ND_PRIORITY << 2) | (MIU1_1ST_PRIORITY) )

////////////////////////////////////////////////////////////////////////////////
// MIU assignment   0: MIU0, 1: MIU1  2:IP_
////////////////////////////////////////////////////////////////////////////////

//Group 0
#define _MIU_CLIENT_NONE_G00            0   //g00
#define _MIU_CLIENT_VIVALDI9_DECODER_R  0   //g01
#define _MIU_CLIENT_NONE_G02            0   //g02
#define _MIU_CLIENT_ARM_RW              0   //g03
#define _MIU_CLIENT_SECURE_R2_RW        0   //g04
#define _MIU_CLIENT_MAU1_RW             1   //g05
#define _MIU_CLIENT_USB3_RW             0   //g06
#define _MIU_CLIENT_PM51_RW             0   //g07
#define _MIU_CLIENT_MHEG5_ICACHE_RW     1   //g08
#define _MIU_CLIENT_USB_UHC0_RW         0   //g09
#define _MIU_CLIENT_USB_UHC1_RW         0   //g0a
#define _MIU_CLIENT_USB_UHC2_RW         0   //g0b
#define _MIU_CLIENT_MVD_BBU_RW          1   //g0c
#define _MIU_CLIENT_EMAC_RW             0   //g0d
#define _MIU_CLIENT_BDMA_RW             2   //g0e
#define _MIU_CLIENT_SC_2D3D_RW          0   //g0f

//Software selection enable: 0: MIU0 / 1: MIU1
    #define  ClientGruop0_in_MIU1       (((_MIU_CLIENT_NONE_G00             == 1) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_VIVALDI9_DECODER_R   == 1) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G02             == 1) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_ARM_RW               == 1) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_SECURE_R2_RW         == 1) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_MAU1_RW              == 1) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_USB3_RW              == 1) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_PM51_RW              == 1) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_MHEG5_ICACHE_RW      == 1) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_USB_UHC0_RW          == 1) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_USB_UHC1_RW          == 1) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_USB_UHC2_RW          == 1) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_MVD_BBU_RW           == 1) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_EMAC_RW              == 1) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_BDMA_RW              == 1) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_SC_2D3D_RW           == 1) ? (0x01 << 15) : 0))

//Hardware selection enable: 0: MIU0 / 1: depend on IP (software selection is invaild)
    #define  ClientGruop0_in_IP         (((_MIU_CLIENT_NONE_G00             == 2) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_VIVALDI9_DECODER_R   == 2) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G02             == 2) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_ARM_RW               == 2) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_SECURE_R2_RW         == 2) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_MAU1_RW              == 2) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_USB3_RW              == 2) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_PM51_RW              == 2) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_MHEG5_ICACHE_RW      == 2) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_USB_UHC0_RW          == 2) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_USB_UHC1_RW          == 2) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_USB_UHC2_RW          == 2) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_MVD_BBU_RW           == 2) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_EMAC_RW              == 2) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_BDMA_RW              == 2) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_SC_2D3D_RW           == 2) ? (0x01 << 15) : 0))

//Group 1
#define _MIU_CLIENT_VIVALDI9_MAD_RW     0   //g10
#define _MIU_CLIENT_NONE_G11            0   //g11
#define _MIU_CLIENT_NONE_G12            0   //g12
#define _MIU_CLIENT_MVOP_R              1   //g13
#define _MIU_CLIENT_GOP_W               0   //g14
#define _MIU_CLIENT_GOP0_R              0   //g15
#define _MIU_CLIENT_GOP1_R              0   //g16
#define _MIU_CLIENT_GOP2_R              0   //g17
#define _MIU_CLIENT_SC_OP_W             0   //g18
#define _MIU_CLIENT_SC_OP_R             0   //g19
#define _MIU_CLIENT_SC_IP_W             0   //g1a
#define _MIU_CLIENT_SC_IP_R             0   //g1b
#define _MIU_CLIENT_VD_COMB_W           0   //g1c
#define _MIU_CLIENT_VD_COMB_R           0   //g1d
#define _MIU_CLIENT_VE_W                0   //g1e
#define _MIU_CLIENT_VE_R                0   //g1f

//Software selection enable: 0: MIU0 / 1: MIU1
    #define  ClientGruop1_in_MIU1       (((_MIU_CLIENT_VIVALDI9_MAD_RW      == 1) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G11             == 1) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G12             == 1) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_MVOP_R               == 1) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_GOP_W                == 1) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_GOP0_R               == 1) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_GOP1_R               == 1) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_GOP2_R               == 1) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_SC_OP_W              == 1) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_SC_OP_R              == 1) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_SC_IP_W              == 1) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_SC_IP_R              == 1) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_VD_COMB_W            == 1) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_VD_COMB_R            == 1) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_VE_W                 == 1) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_VE_R                 == 1) ? (0x01 << 15) : 0))

//Hardware selection enable: 0: MIU0  / 1: depend on IP (software selection is invaild)
    #define  ClientGruop1_in_IP         (((_MIU_CLIENT_VIVALDI9_MAD_RW      == 2) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G11             == 2) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G12             == 2) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_MVOP_R               == 2) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_GOP_W                == 2) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_GOP0_R               == 2) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_GOP1_R               == 2) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_GOP2_R               == 2) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_SC_OP_W              == 2) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_SC_OP_R              == 2) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_SC_IP_W              == 2) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_SC_IP_R              == 2) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_VD_COMB_W            == 2) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_VD_COMB_R            == 2) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_VE_W                 == 2) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_VE_R                 == 2) ? (0x01 << 15) : 0))
//Group 2
#define _MIU_CLIENT_SC_OD_W             0   //g20
#define _MIU_CLIENT_SC_OD_R             0   //g21
#define _MIU_CLIENT_SC_LDM_W            0   //g22
#define _MIU_CLIENT_SC_LDM_R            0   //g23
#define _MIU_CLIENT_SC_IPSUB_W          0   //g24
#define _MIU_CLIENT_SC_IPSUB_R          0   //g25
#define _MIU_CLIENT_SC_T3D_W            0   //g26
#define _MIU_CLIENT_SC_T3D_R            0   //g27
#define _MIU_CLIENT_GPD_RW              0   //g28
#define _MIU_CLIENT_SC_DIP_RW           1   //g29
#define _MIU_CLIENT_TSP_W               0   //g2a
#define _MIU_CLIENT_TSP_R               0   //g2b
#define _MIU_CLIENT_VD_TTX_RW           0   //g2c
#define _MIU_CLIENT_VD_TTXSL_W          0   //g2d
#define _MIU_CLIENT_TSP_ORZ_RW          0   //g2e
#define _MIU_CLIENT_TSP_ORZ_W           0   //g2f

//Software selection enable: 0: MIU0 / 1: MIU1
    #define  ClientGruop2_in_MIU1       (((_MIU_CLIENT_SC_OD_W              == 1) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_SC_OD_R              == 1) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_SC_LDM_W             == 1) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_SC_LDM_R             == 1) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_SC_IPSUB_W           == 1) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_SC_IPSUB_R           == 1) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_SC_T3D_W             == 1) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_SC_T3D_R             == 1) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_GPD_RW               == 1) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_SC_DIP_RW            == 1) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_TSP_W                == 1) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_TSP_R                == 1) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_VD_TTX_RW            == 1) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_VD_TTXSL_W           == 1) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_TSP_ORZ_RW           == 1) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_TSP_ORZ_W            == 1) ? (0x01 << 15) : 0))

//Hardware selection enable: 0: MIU0 / 1: depend on IP (software selection is invaild)
    #define  ClientGruop2_in_IP         (((_MIU_CLIENT_SC_OD_W              == 2) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_SC_OD_R              == 2) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_SC_LDM_W             == 2) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_SC_LDM_R             == 2) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_SC_IPSUB_W           == 2) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_SC_IPSUB_R           == 2) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_SC_T3D_W             == 2) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_SC_T3D_R             == 2) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_GPD_RW               == 2) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_SC_DIP_RW            == 2) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_TSP_W                == 2) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_TSP_R                == 2) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_VD_TTX_RW            == 2) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_VD_TTXSL_W           == 2) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_TSP_ORZ_RW           == 2) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_TSP_ORZ_W            == 2) ? (0x01 << 15) : 0))

//Group 3
#define _MIU_CLIENT_GE_RW               0   //g30
#define _MIU_CLIENT_HVD_BBU_R           1   //g31
#define _MIU_CLIENT_HVD_RW              1   //g32
#define _MIU_CLIENT_JPD_RW              1   //g33
#define _MIU_CLIENT_MVD_RW              1   //g34
#define _MIU_CLIENT_GPU_RW              0   //g35
#define _MIU_CLIENT_MFE0_W              0   //g36
#define _MIU_CLIENT_MFE1_R              0   //g37
#define _MIU_CLIENT_NAND_RW             0   //g38
#define _MIU_CLIENT_NONE_G39            0   //g39
#define _MIU_CLIENT_DSCRMB_RW           0   //g3a
#define _MIU_CLIENT_JPD720P_RW          1   //g3b
#define _MIU_CLIENT_UDMA_RW             0   //g3c
#define _MIU_CLIENT_MIIC_RW             0   //g3d
#define _MIU_CLIENT_SDIO_RW             0   //g3e
#define _MIU_CLIENT_USB3_PHY_W          0   //g3f

//Software selection enable: 0: MIU0 / 1: MIU1
    #define  ClientGruop3_in_MIU1       (((_MIU_CLIENT_GE_RW                == 1) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_HVD_BBU_R            == 1) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_HVD_RW               == 1) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_JPD_RW               == 1) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_MVD_RW               == 1) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_GPU_RW               == 1) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_MFE0_W               == 1) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_MFE1_R               == 1) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_NAND_RW              == 1) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G39             == 1) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_DSCRMB_RW            == 1) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_JPD720P_RW           == 1) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_UDMA_RW              == 1) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_MIIC_RW              == 1) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_SDIO_RW              == 1) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_USB3_PHY_W           == 1) ? (0x01 << 15) : 0))

//Hardware selection enable: 0: MIU0 / 1: depend on IP (software selection is invaild)
    #define  ClientGruop3_in_IP         (((_MIU_CLIENT_GE_RW                == 2) ? (0x01 << 0)  : 0) | \
                                         ((_MIU_CLIENT_HVD_BBU_R            == 2) ? (0x01 << 1)  : 0) | \
                                         ((_MIU_CLIENT_HVD_RW               == 2) ? (0x01 << 2)  : 0) | \
                                         ((_MIU_CLIENT_JPD_RW               == 2) ? (0x01 << 3)  : 0) | \
                                         ((_MIU_CLIENT_MVD_RW               == 2) ? (0x01 << 4)  : 0) | \
                                         ((_MIU_CLIENT_GPU_RW               == 2) ? (0x01 << 5)  : 0) | \
                                         ((_MIU_CLIENT_MFE0_W               == 2) ? (0x01 << 6)  : 0) | \
                                         ((_MIU_CLIENT_MFE1_R               == 2) ? (0x01 << 7)  : 0) | \
                                         ((_MIU_CLIENT_NAND_RW              == 2) ? (0x01 << 8)  : 0) | \
                                         ((_MIU_CLIENT_NONE_G39             == 2) ? (0x01 << 9)  : 0) | \
                                         ((_MIU_CLIENT_DSCRMB_RW            == 2) ? (0x01 << 10) : 0) | \
                                         ((_MIU_CLIENT_JPD720P_RW           == 2) ? (0x01 << 11) : 0) | \
                                         ((_MIU_CLIENT_UDMA_RW              == 2) ? (0x01 << 12) : 0) | \
                                         ((_MIU_CLIENT_MIIC_RW              == 2) ? (0x01 << 13) : 0) | \
                                         ((_MIU_CLIENT_SDIO_RW              == 2) ? (0x01 << 14) : 0) | \
                                         ((_MIU_CLIENT_USB3_PHY_W           == 2) ? (0x01 << 15) : 0))

#define   MIUSEL_FLAG_DNRB_R            _MIU_CLIENT_SC_IP_R
#define   MIUSEL_FLAG_DNRB_RW           (_MIU_CLIENT_SC_IP_R | _MIU_CLIENT_SC_IP_W)

//-----------------------------------------------------------------------------

#endif  //_MIUSEL_NADAL_2MIU_H_

