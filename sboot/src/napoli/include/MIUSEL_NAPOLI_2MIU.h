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

#ifndef _MIUSEL_NAPOLI_2MIU_H_
#define _MIUSEL_NAPOLI_2MIU_H_

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
#define MIU1_2ND_PRIORITY           GROUP_0
#define MIU1_3RD_PRIORITY           GROUP_1
#define MIU1_4TH_PRIORITY           GROUP_2

#define MIU0_GROUP_PRIORITY         ((MIU0_4TH_PRIORITY << 6) | (MIU0_3RD_PRIORITY << 4) | (MIU0_2ND_PRIORITY << 2) | (MIU0_1ST_PRIORITY) )
#define MIU1_GROUP_PRIORITY         ((MIU1_4TH_PRIORITY << 6) | (MIU1_3RD_PRIORITY << 4) | (MIU1_2ND_PRIORITY << 2) | (MIU1_1ST_PRIORITY) )

////////////////////////////////////////////////////////////////////////////////
// MIU assignment   0: MIU0, 1: MIU1  2:IP_
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------
//
//----------------------------------------
//group_0
#define  RESERVED_for_MIU_SELF      0
#define  VIVALDI9_DSP_DECODER       0
#define  GIGAMAC_RW                 0
#define  USB30_RW                   0
#define  SECURE_R2_RW               0
#define  AU_R2_RW                   0
#define  MAU1_RW                    0
#define  PM51_RW                    0
#define  VD_MHEG5_I_RW              0
#define  UHC0_RW                    0
#define  UHC1_RW                    0
#define  UHC2_RW                    0
#define  MVD_BBU_RW                 1
#define  EMAC_RW                    0
#define  PIU_BDMA_RW                2
#define  UHC3_RW                    0
// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop0_in_MIU1       (((VIVALDI9_DSP_DECODER == 1) ? 0x0002 : 0) | \
                                     ((GIGAMAC_RW           == 1) ? 0x0004 : 0) | \
                                     ((USB30_RW             == 1) ? 0x0008 : 0) | \
                                     ((SECURE_R2_RW         == 1) ? 0x0010 : 0) | \
                                     ((AU_R2_RW             == 1) ? 0x0020 : 0) | \
                                     ((MAU1_RW              == 1) ? 0x0040 : 0) | \
                                     ((PM51_RW              == 1) ? 0x0080 : 0) | \
                                     ((VD_MHEG5_I_RW        == 1) ? 0x0100 : 0) | \
                                     ((UHC0_RW              == 1) ? 0x0200 : 0) | \
                                     ((UHC1_RW              == 1) ? 0x0400 : 0) | \
                                     ((UHC2_RW              == 1) ? 0x0800 : 0) | \
                                     ((MVD_BBU_RW           == 1) ? 0x1000 : 0) | \
                                     ((EMAC_RW              == 1) ? 0x2000 : 0) | \
                                     ((PIU_BDMA_RW          == 1) ? 0x4000 : 0) | \
                                     ((UHC3_RW              == 1) ? 0x8000 : 0))

// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop0_in_IP         (((VIVALDI9_DSP_DECODER == 2) ? 0x0002 : 0) | \
                                     ((GIGAMAC_RW           == 2) ? 0x0004 : 0) | \
                                     ((USB30_RW             == 2) ? 0x0008 : 0) | \
                                     ((SECURE_R2_RW         == 2) ? 0x0010 : 0) | \
                                     ((AU_R2_RW             == 2) ? 0x0020 : 0) | \
                                     ((MAU1_RW              == 2) ? 0x0040 : 0) | \
                                     ((PM51_RW              == 2) ? 0x0080 : 0) | \
                                     ((VD_MHEG5_I_RW        == 2) ? 0x0100 : 0) | \
                                     ((UHC0_RW              == 2) ? 0x0200 : 0) | \
                                     ((UHC1_RW              == 2) ? 0x0400 : 0) | \
                                     ((UHC2_RW              == 2) ? 0x0800 : 0) | \
                                     ((MVD_BBU_RW           == 2) ? 0x1000 : 0) | \
                                     ((EMAC_RW              == 2) ? 0x2000 : 0) | \
                                     ((PIU_BDMA_RW          == 2) ? 0x4000 : 0) | \
                                     ((UHC3_RW              == 2) ? 0x8000 : 0))
//group_1
#define  VIVALDI9_MAD_RW            0
#define  DEMOD0_W                   0
#define  DEMOD0_R                   0
#define  MVOP_R                     1
#define  MVOP1_SUB_R                0
#define  SC_DIPW_W                  0
#define  SC_LD_RW                   0
#define  CMDQ_R                     0
#define  TSP_W                      0 // check with MIU
#define  TSP1_W                     0 // check with MIU
#define  SDIO_RW                    0
#define  VD_VBI_RW                  0
#define  VD_COMB_W                  0
#define  VD_COMB_R                  0
#define  VE_RW                      0
#define  SC_MRQ_MC2D_T3D_VIFADC     0
// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop1_in_MIU1       (((VIVALDI9_MAD_RW          == 1) ? 0x0001 : 0) | \
                                     ((DEMOD0_W                 == 1) ? 0x0002 : 0) | \
                                     ((DEMOD0_R                 == 1) ? 0x0004 : 0) | \
                                     ((MVOP_R                   == 1) ? 0x0008 : 0) | \
                                     ((MVOP1_SUB_R              == 1) ? 0x0010 : 0) | \
                                     ((SC_DIPW_W                == 1) ? 0x0020 : 0) | \
                                     ((SC_LD_RW                 == 1) ? 0x0040 : 0) | \
                                     ((CMDQ_R                   == 1) ? 0x0080 : 0) | \
                                     ((TSP_W                    == 1) ? 0x0100 : 0) | \
                                     ((TSP1_W                    == 1) ? 0x0200 : 0) | \
                                     ((SDIO_RW                  == 1) ? 0x0400 : 0) | \
                                     ((VD_VBI_RW                == 1) ? 0x0800 : 0) | \
                                     ((VD_COMB_W                == 1) ? 0x1000 : 0) | \
                                     ((VD_COMB_R                == 1) ? 0x2000 : 0) | \
                                     ((VE_RW                    == 1) ? 0x4000 : 0) | \
                                     ((SC_MRQ_MC2D_T3D_VIFADC   == 1) ? 0x8000 : 0))
// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop1_in_IP         (((VIVALDI9_MAD_RW          == 2) ? 0x0001 : 0) | \
                                     ((DEMOD0_W                 == 2) ? 0x0002 : 0) | \
                                     ((DEMOD0_R                 == 2) ? 0x0004 : 0) | \
                                     ((MVOP_R                   == 2) ? 0x0008 : 0) | \
                                     ((MVOP1_SUB_R              == 2) ? 0x0010 : 0) | \
                                     ((SC_DIPW_W                == 2) ? 0x0020 : 0) | \
                                     ((SC_LD_RW                 == 2) ? 0x0040 : 0) | \
                                     ((CMDQ_R                   == 2) ? 0x0080 : 0) | \
                                     ((TSP_W                    == 2) ? 0x0100 : 0) | \
                                     ((TSP1_W                    == 2) ? 0x0200 : 0) | \
                                     ((SDIO_RW                  == 2) ? 0x0400 : 0) | \
                                     ((VD_VBI_RW                == 2) ? 0x0800 : 0) | \
                                     ((VD_COMB_W                == 2) ? 0x1000 : 0) | \
                                     ((VD_COMB_R                == 2) ? 0x2000 : 0) | \
                                     ((VE_RW                    == 2) ? 0x4000 : 0) | \
                                     ((SC_MRQ_MC2D_T3D_VIFADC   == 2) ? 0x8000 : 0))
//group_2
#define  GE_RW                      0
#define  HVD_BBU_R                  1
#define  HVD_RW                     1
#define  PIU_UARTDMA_RW             0
#define  MVD_RW                     1
#define  GPU_WR                     1
#define  GPD_WR                     1
#define  MFE0_W                     0
#define  MFE1_R                     0
#define  NAND_RW                    0
#define  JPD_720P_RW                2   // MIU assignment   0: MIU0, 1: MIU1  2:IP_ASSIGN
#define  DSCRMB_RW                  0
#define  JPD1_720P_RW                0
#define  TSP_ORZ_RW                 0
#define  TSP1_ORZ_RW                 0
#define  PIU_MIIC_RW                0
// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop2_in_MIU1       (((GE_RW                   == 1) ? 0x0001 : 0) | \
                                     ((HVD_BBU_R               == 1) ? 0x0002 : 0) | \
                                     ((HVD_RW                  == 1) ? 0x0004 : 0) | \
                                     ((PIU_UARTDMA_RW          == 1) ? 0x0008 : 0) | \
                                     ((MVD_RW                  == 1) ? 0x0010 : 0) | \
                                     ((GPU_WR                  == 1) ? 0x0020 : 0) | \
                                     ((GPD_WR                  == 1) ? 0x0040 : 0) | \
                                     ((MFE0_W                  == 1) ? 0x0080 : 0) | \
                                     ((MFE1_R                  == 1) ? 0x0100 : 0) | \
                                     ((NAND_RW                 == 1) ? 0x0200 : 0) | \
                                     ((JPD_720P_RW             == 1) ? 0x0400 : 0) | \
                                     ((DSCRMB_RW               == 1) ? 0x0800 : 0) | \
                                     ((JPD1_720P_RW              == 1) ? 0x1000 : 0) | \
                                     ((TSP_ORZ_RW              == 1) ? 0x2000 : 0) | \
                                     ((TSP1_ORZ_RW              == 1) ? 0x4000 : 0) | \
                                     ((PIU_MIIC_RW             == 1) ? 0x8000 : 0))
// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop2_in_IP         (((GE_RW                   == 2) ? 0x0001 : 0) | \
                                     ((HVD_BBU_R               == 2) ? 0x0002 : 0) | \
                                     ((HVD_RW                  == 2) ? 0x0004 : 0) | \
                                     ((PIU_UARTDMA_RW          == 2) ? 0x0008 : 0) | \
                                     ((MVD_RW                  == 2) ? 0x0010 : 0) | \
                                     ((GPU_WR                  == 2) ? 0x0020 : 0) | \
                                     ((GPD_WR                  == 2) ? 0x0040 : 0) | \
                                     ((MFE0_W                  == 2) ? 0x0080 : 0) | \
                                     ((MFE1_R                  == 2) ? 0x0100 : 0) | \
                                     ((NAND_RW                 == 2) ? 0x0200 : 0) | \
                                     ((JPD_720P_RW             == 2) ? 0x0400 : 0) | \
                                     ((DSCRMB_RW               == 2) ? 0x0800 : 0) | \
                                     ((JPD1_720P_RW             == 2) ? 0x1000 : 0) | \
                                     ((TSP_ORZ_RW              == 2) ? 0x2000 : 0) | \
                                     ((TSP1_ORZ_RW              == 2) ? 0x4000 : 0) | \
                                     ((PIU_MIIC_RW             == 2) ? 0x8000 : 0))

//group_3
#define  HEMCU_RW                   0
#define  PDW1_RW                    1
#define  GOP0_PDW0_RW               1
#define  GOP1_R                     0
#define  GOP2_R                     1
#define  GOP3_R                     1
#define  SC_OP_MAIN_RW              1
#define  SC_IP_MAIN_RW              0
#define  SC_OP_SUB_RW               0
#define  SC_OD_R                    0
#define  SC_OD_FRCW_W               2   // MIU assignment   0: MIU0, 1: MIU1  2:IP_ASSIGN
#define  SC_IPM2                    0
#define  EVD_BBU_R                  0
#define  EVD_RW                     0
#define  SC_FRCL_RW                 0
#define  SC_FRCR_RW                 0
// software selection enable 0: MIU0 1: MIU1
#define  ClientGruop3_in_MIU1       (((HEMCU_RW               == 1) ? 0x0001 : 0) | \
                                     ((PDW1_RW                == 1) ? 0x0002 : 0) | \
                                     ((GOP0_PDW0_RW           == 1) ? 0x0004 : 0) | \
                                     ((GOP1_R                 == 1) ? 0x0008 : 0) | \
                                     ((GOP2_R                 == 1) ? 0x0010 : 0) | \
                                     ((GOP3_R                 == 1) ? 0x0020 : 0) | \
                                     ((SC_OP_MAIN_RW          == 1) ? 0x0040 : 0) | \
                                     ((SC_IP_MAIN_RW          == 1) ? 0x0080 : 0) | \
                                     ((SC_OP_SUB_RW           == 1) ? 0x0100 : 0) | \
                                     ((SC_OD_R                == 1) ? 0x0200 : 0) | \
                                     ((SC_OD_FRCW_W           == 1) ? 0x0400 : 0) | \
                                     ((SC_IPM2                == 1) ? 0x0800 : 0) | \
                                     ((EVD_BBU_R              == 1) ? 0x1000 : 0) | \
                                     ((EVD_RW                 == 1) ? 0x2000 : 0) | \
                                     ((SC_FRCL_RW             == 1) ? 0x4000 : 0) | \
                                     ((SC_FRCR_RW             == 1) ? 0x8000 : 0))
// Hardware selection enable 0: MIU0 1: depend on IP (software selection is invaild)
#define  ClientGruop3_in_IP         (((HEMCU_RW               == 2) ? 0x0001 : 0) | \
                                     ((PDW1_RW                == 2) ? 0x0002 : 0) | \
                                     ((GOP0_PDW0_RW           == 2) ? 0x0004 : 0) | \
                                     ((GOP1_R                 == 2) ? 0x0008 : 0) | \
                                     ((GOP2_R                 == 2) ? 0x0010 : 0) | \
                                     ((GOP3_R                 == 2) ? 0x0020 : 0) | \
                                     ((SC_OP_MAIN_RW          == 2) ? 0x0040 : 0) | \
                                     ((SC_IP_MAIN_RW          == 2) ? 0x0080 : 0) | \
                                     ((SC_OP_SUB_RW           == 2) ? 0x0100 : 0) | \
                                     ((SC_OD_R                == 2) ? 0x0200 : 0) | \
                                     ((SC_OD_FRCW_W           == 2) ? 0x0400 : 0) | \
                                     ((SC_IPM2                == 2) ? 0x0800 : 0) | \
                                     ((EVD_BBU_R              == 2) ? 0x1000 : 0) | \
                                     ((EVD_RW                 == 2) ? 0x2000 : 0) | \
                                     ((SC_FRCL_RW             == 2) ? 0x4000 : 0) | \
                                     ((SC_FRCR_RW             == 2) ? 0x8000 : 0))


//backward competiable
#define   MIUSEL_FLAG_DNRB_R        SC_IP_MAIN_R
#define   MIUSEL_FLAG_DNRB_RW       (SC_IP_MAIN_R | SC_IP_MAIN_W)

//-----------------------------------------------------------------------------

#endif  //_MIUSEL_NAPOLI_2MIU_H_

