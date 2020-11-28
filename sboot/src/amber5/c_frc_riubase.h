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
    //************************************************************
    //***             RIU Base address of each IP              ***
    //***                (Byte address [23:0])                 ***
    //************************************************************

#define    RIUBASE_FRC_RIU_DBG         0x300100    //0x300100 ~ 0x3001ff
#define    RIUBASE_FRC_INTR_CPUINT     0x300580    //0x300580 ~ 0x30059f
#define    RIUBASE_FRC_REG_HW_SEMAPH   0x300600    //0x300600 ~ 0x3006ff
#define    RIUBASE_LDM_DMA0            0x300900    //0x300900 ~ 0x3009ff
#define    RIUBASE_LDM_DMA1            0x300a00    //0x300a00 ~ 0x300aff
#define    RIUBASE_LDM_DMA2            0x300b00    //0x300b00 ~ 0x300bff
#define    RIUBASE_LDM_DMA3            0x300c00    //0x300c00 ~ 0x300cff
#define    RIUBASE_FRC_MAU0            0x300d00    //0x300d00 ~ 0x300d7f
#define    RIUBASE_FRC_R2              0x301000    //0x301000 ~ 0x3010ff
#define    RIUBASE_FRC_INTR_CTRL       0x301100    //0x301100 ~ 0x3011ff
#define    RIUBASE_FRC_MIU             0x301200    //0x301200 ~ 0x3012ff
#define    RIUBASE_PRAM                0x301500    //0x301500 ~ 0x3015ff
#define    RIUBASE_SC24_2D3D           0x301600    //0x301600 ~ 0x3016ff
#define    RIUBASE_ECC                 0x301800    //0x301800 ~ 0x3018ff
#define    RIUBASE_MSPI0               0x301900    //0x301900 ~ 0x3019ff
#define    RIUBASE_MSPI1               0x301a00    //0x301a00 ~ 0x301aff
#define    RIUBASE_MSPI2               0x301b00    //0x301b00 ~ 0x301bff
#define    RIUBASE_MSPI3               0x301c00    //0x301c00 ~ 0x301cff
#define    RIUBASE_FRC_CHIP            0x301e00    //0x301e00 ~ 0x301eff
#define    RIUBASE_FRC_VD_IRQ          0x301f00    //0x301f00 ~ 0x301fff
#define    RIUBASE_SC0_IP              0x302000    //0x302000 ~ 0x3020ff
#define    RIUBASE_SC1_VBI             0x302100    //0x302100 ~ 0x3021ff
#define    RIUBASE_SC2_LVDSRX          0x302200    //0x302200 ~ 0x3022ff
#define    RIUBASE_SC3_TCON            0x302300    //0x302300 ~ 0x3023ff
#define    RIUBASE_SC4_SCTOP           0x302400    //0x302400 ~ 0x3024ff
#define    RIUBASE_SC5_PWM             0x302500    //0x302500 ~ 0x3025ff
#define    RIUBASE_SC6_MCPLUS          0x302600    //0x302600 ~ 0x3026ff
#define    RIUBASE_SC7_MC_3FRAME       0x302700    //0x302700 ~ 0x3027ff
#define    RIUBASE_SC8_OD              0x302800    //0x302800 ~ 0x3028ff
#define    RIUBASE_SC9_MC2D            0x302900    //0x302900 ~ 0x3029ff
#define    RIUBASE_SC10_DISP_LPLL      0x302a00    //0x302a00 ~ 0x302aff
#define    RIUBASE_SC16_MC2D           0x302c00    //0x302c00 ~ 0x302cff
#define    RIUBASE_SC17_IP             0x302d00    //0x302d00 ~ 0x302dff
#define    RIUBASE_SC11_SNR            0x302e00    //0x302e00 ~ 0x302eff
#define    RIUBASE_SC12_DISP_TGEN      0x302f00    //0x302f00 ~ 0x302fff
#define    RIUBASE_SC13_VOP2           0x303000    //0x303000 ~ 0x3030ff
#define    RIUBASE_SC14_MFT            0x303100    //0x303100 ~ 0x3031ff
#define    RIUBASE_SC15_MISC           0x303200    //0x303200 ~ 0x3032ff
#define    RIUBASE_SC18_LD             0x303300    //0x303300 ~ 0x3033ff
#define    RIUBASE_SC19_OD_LOCAL_GAIN  0x303800    //0x303800 ~ 0x3038ff
#define    RIUBASE_SC20_MC2D           0x303a00    //0x303a00 ~ 0x303aff
#define    RIUBASE_SC21_NEW_FILM       0x303b00    //0x303b00 ~ 0x303bff
#define    RIUBASE_SC22_ADL            0x303d00    //0x303d00 ~ 0x303dff
#define    RIUBASE_SC25_HVSP           0x303e00    //0x303e00 ~ 0x303eff
#define    RIUBASE_FRC_EFUSE           0x303f00    //0x303f00 ~ 0x303fff
#define    RIUBASE_LGD_IP1             0x312000    //0x312000 ~ 0x3120ff
#define    RIUBASE_SC26_3DD            0x313000    //0x313000 ~ 0x3130ff
