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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#ifndef XC_ANALOG_REG_H
#define XC_ANALOG_REG_H


/******************************************************************************/
/*                     Macro                                                  */
/******************************************************************************/

#ifndef UNUSED
#define UNUSED(x) ((x)=(x))
#endif

///////////////////////////////////////////////////////
// Scaler Bank
///////////////////////////////////////////////////////

#define REG_BANK_RESET              0x00
#define REG_BANK_GOPINT             0x00
#define REG_BANK_IP1F2              0x01
#define REG_BANK_IP2F2              0x02
#define REG_BANK_IP1F1              0x03
#define REG_BANK_IP2F1              0x04
#define REG_BANK_OPM                0x05
#define REG_BANK_DNR                0x06
#define REG_BANK_OP1                0x07
#define REG_BANK_OP1PIP             0x08
#define REG_BANK_OP1HVSP            0x09
#define REG_BANK_FILM               0x0A    //T2
#define REG_BANK_ELA                0x0B
#define REG_BANK_ACE                0x0C
#define REG_BANK_HD                 0x0E
#define REG_BANK_S_VOP              0x0F
#define REG_BANK_VOP                0x10
#define REG_BANK_TCON               0x11
#define REG_BANK_SCMI               0x12  //T2
#define REG_BANK_OFFLINE            0x13
#define REG_BANK_OD                 0x16
#define REG_BANK_SRAM               0x17
#define REG_BANK_VIP                0x18
#define REG_BANK_VPS                0x19
#define REG_BANK_DLC                0x1A
#define REG_BANK_OP1PIPEXT          0x1B
#define REG_BANK_SmoothFilter       0x1C
#define REG_BANK_MFC                0x1D
#define REG_BANK_PIP                0x20
#define REG_BANK_EODI               0x21
#define REG_BANK_MADI               0x22
#define REG_BANK_HVSP               0x23
#define REG_BANK_DMS                0x26
#define REG_BANK_PRED               0x28

#define BK_SELECT_00                REG_SCALER_BASE

#define HIPART( u32x )              (((u32x) >> 16) & 0xFFFF)
#define LOPART( u32x )              ((u32x) & 0xFFFF)

#define BK_REG_L( x, y )            ((x) | (((y) << 1)))
#define BK_REG_H( x, y )            (((x) | (((y) << 1))) + 1)

/* Scaler */
#define L_BK_GOPINT(x)      BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_GOPINT(x)      BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_SWRESET(x)     BK_REG_L(REG_SCALER_BASE,x)
#define L_BK_IP1F2(x)       BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_IP1F2(x)       BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_IP2F2(x)       BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_IP2F2(x)       BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_IP1F1(x)       BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_IP1F1(x)       BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_IP2F1(x)       BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_IP2F1(x)       BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_OPM(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_OPM(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_DNR(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_DNR(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_OP1(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_OP1(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_OP1HVSP(x)     BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_OP1HVSP(x)     BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_ELA(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_ELA(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_ACE(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_ACE(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_HD(x)          BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_HD(x)          BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_S_VOP(x)       BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_S_VOP(x)       BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_VOP(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_VOP(x)         BK_REG_H(REG_SCALER_BASE,x)

#define L_BK_OFFLINE(x)     BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_OFFLINE(x)     BK_REG_H(REG_SCALER_BASE,x)

#define L_BK_SCMI(x)        BK_REG_L(REG_SCALER_BASE,x)      //SUPPORT_CHIP==T2
#define H_BK_SCMI(x)        BK_REG_H(REG_SCALER_BASE,x)      //SUPPORT_CHIP==T2
#define L_BK_OD(x)          BK_REG_L(REG_SCALER_BASE,x)      //SUPPORT_CHIP==T2
#define H_BK_OD(x)          BK_REG_H(REG_SCALER_BASE,x)      //SUPPORT_CHIP==T2

#define L_BK_OP1ZZ(x)       BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_OP1ZZ(x)       BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_VIP(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_VIP(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_VPS(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_VPS(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_DLC(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_DLC(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_OP1PIPEXT(x)   BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_OP1PIPEXT(x)   BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_SmoothFilter(x)  BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_SmoothFilter(x)  BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_MFC(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_MFC(x)         BK_REG_H(REG_SCALER_BASE,x)

#define L_BK_EODI(x)        BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_EODI(x)        BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_MADI(x)        BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_MADI(x)        BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_PIP(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_PIP(x)         BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_HVSP(x)        BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_HVSP(x)        BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_PRED(x)        BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_PRED(x)        BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_FILM(x)        BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_FILM(x)        BK_REG_H(REG_SCALER_BASE,x)
#define L_BK_DMS(x)         BK_REG_L(REG_SCALER_BASE,x)
#define H_BK_DMS(x)         BK_REG_H(REG_SCALER_BASE,x)

/* VE */
#define L_BK_VE_ENC(x)      BK_REG_L(REG_BASE_VE_ENCODER, x)
#define H_BK_VE_ENC(x)      BK_REG_H(REG_BASE_VE_ENCODER, x)
#define L_BK_VE_SRC(x)      BK_REG_L(REG_BASE_VE_SOURCE, x)
#define H_BK_VE_SRC(x)      BK_REG_H(REG_BASE_VE_SOURCE, x)


/* LPLL */
#define L_BK_LPLL(x)        BK_REG_L(REG_LPLL_BASE, x)
#define H_BK_LPLL(x)        BK_REG_H(REG_LPLL_BASE, x)

/* IP Mux */
#define L_BK_IPMUX(x)       BK_REG_L(REG_IPMUX_BASE, x)
#define H_BK_IPMUX(x)       BK_REG_H(REG_IPMUX_BASE, x)

/* Chip Top */
#define L_BK_CHIPTOP(x)     BK_REG_L(REG_CHIPTOP_BASE, x)
#define H_BK_CHIPTOP(x)     BK_REG_H(REG_CHIPTOP_BASE, x)

/* ADC */
#define L_BK_ADC_ATOP(x)    BK_REG_L(REG_ADC_ATOP_BASE, x)
#define H_BK_ADC_ATOP(x)    BK_REG_H(REG_ADC_ATOP_BASE, x)
#define L_BK_ADC_DTOP(x)    BK_REG_L(REG_ADC_DTOP_BASE, x)
#define H_BK_ADC_DTOP(x)    BK_REG_H(REG_ADC_DTOP_BASE, x)

/* MOD */
#define L_BK_MOD(x)         BK_REG_L(REG_MOD_BASE, x)
#define H_BK_MOD(x)         BK_REG_H(REG_MOD_BASE, x)

/* VD:AFEC */
#define L_BK_AFEC(x)        BK_REG_L(REG_AFEC_BASE, x)
#define H_BK_AFEC(x)        BK_REG_H(REG_AFEC_BASE, x)

//------------------------------------------------------------------------------
// Input source select

// BK_IP1F2_02 [2:0]
#define IP_INSSEL_ANALOG1   0x0000
#define IP_INSSEL_ANALOG2   0x0001
#define IP_INSSEL_ANALOG3   0x0002
#define IP_INSSEL_DVI       0x0003
#define IP_INSSEL_VIDEO     0x0004
#define IP_INSSEL_HDTV      0x0005
#define IP_INSSEL_HDMI      0x0007

#define IP_INSSEL_MASK      BITMASK(2:0)
#define IP_VDOSEL_MASK      BITMASK(1:0)

typedef enum
{
    IP_CCIR656_A,
    IP_MST_VD_A,
    IP_CCIR601,
    IP_MST_VD_B, // Don't use; RD's suggestion.
    IP_CCIR656_B=0x20
} VDOSEL;

typedef enum
{
    VE_IPMUX_ADC_A      = 0,            ///< ADC A
    VE_IPMUX_HDMI_DVI   = 1,            ///< DVI
    VE_IPMUX_VD         = 2,            ///< VD
    VE_IPMUX_MVOP       = 3,            ///< MPEG/DC0
    VE_IPMUX_SC_IP1     = 4,            ///< Scaler IP1 output
    VE_IPMUX_EXT_VD     = 5,            ///< External VD
    VE_IPMUX_ADC_B      = 6,            ///< ADC B
} VE_IPMUX_TYPE;

typedef enum
{
    AUTO_DETECT     =0x00,
    HV_SEPARATED    =0x01,
    COMPOSITE_SYNC  =0x02,
    SYNC_ON_GREEN   =0x03
}STYPE;

typedef enum
{
    CSYNC   = 0,
    SOG     = 1
}COMP;

//------------------------------------------------------------------------------
// ADC

#define ADC_AMUXA_MASK      BITMASK(1:0)
#define ADC_YMUX_MASK       BITMASK(3:0)
#define ADC_CMUX_MASK       BITMASK(7:4)


//------------------------------------------------------------------------------
// MUX

typedef enum
{
    ADC_RGB1,
    ADC_RGB2,
    ADC_RGB3,
}AMUX_SEL;

typedef enum // For PC/YPbPr input mux
{
    ANALOG_RGB0 = ADC_RGB1,
    ANALOG_RGB1 = ADC_RGB2,
    ANALOG_RGB2 = ADC_RGB3,
    ANALOG_RGB_DUMMY,
}ANALOG_RGB;

typedef enum
{
    MSVD_YMUX_CVBS0,
    MSVD_YMUX_CVBS1,
    MSVD_YMUX_CVBS2,
    MSVD_YMUX_CVBS3,

    MSVD_YMUX_Y0,
    MSVD_YMUX_Y1,
    MSVD_YMUX_C0,
    MSVD_YMUX_C1,

    MSVD_YMUX_SOG0 = 8,
    MSVD_YMUX_SOG1,
    MSVD_YMUX_SOG2,

    MSVD_YMUX_G0 = 11,
    MSVD_YMUX_G1 = 12,
    MSVD_YMUX_G2 = 13,
    MSVD_YMUX_CVBS4 = MSVD_YMUX_Y0,
    MSVD_YMUX_CVBS5 = MSVD_YMUX_Y1,
    MSVD_YMUX_CVBS6 = MSVD_YMUX_C0,
    MSVD_YMUX_CVBS7 = MSVD_YMUX_C1,
    MSVD_YMUX_NONE = 0xF,

    MSVD_YMUX_DUMMY,
}MS_VD_YMUX;

typedef enum
{
    MSVD_CMUX_CVBS0,
    MSVD_CMUX_CVBS1,
    MSVD_CMUX_CVBS2,
    MSVD_CMUX_CVBS3,

    MSVD_CMUX_Y0 = 4,
    MSVD_CMUX_Y1,
    MSVD_CMUX_C0,
    MSVD_CMUX_C1,

    MSVD_CMUX_SOG0 = 8,
    MSVD_CMUX_SOG1,
    MSVD_CMUX_SOG2,

    MSVD_CMUX_R0 = 11,
    MSVD_CMUX_R1 = 12,
    MSVD_CMUX_R2 = 13,
    MSVD_CMUX_CVBS4 = MSVD_CMUX_Y0,
    MSVD_CMUX_CVBS5 = MSVD_CMUX_C0,
    MSVD_CMUX_CVBS6 = MSVD_CMUX_Y1,
    MSVD_CMUX_CVBS7 = MSVD_CMUX_C1,
    MSVD_CMUX_NONE = 0xF,

    MSVD_CMUX_DUMMY,
}MS_VD_CMUX;

#endif // ANALOG_REG_H
