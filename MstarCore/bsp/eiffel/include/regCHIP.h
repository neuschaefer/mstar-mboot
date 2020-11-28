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

#ifndef _REG_SYSTEM_H_
#define _REG_SYSTEM_H_

//-------------------------------------------------------------------------------------------------
//  Hardware Capability
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define REG_TOP_BASE                        (0x1F000000 + (0x101E00 << 1))

//=============================================================================
// Register access
#define TOP_READ(addr)                      READ_WORD(REG_TOP_BASE + ((addr) << 2))
#define TOP_WRITE(addr, val)                WRITE_WORD((REG_TOP_BASE + ((addr) << 2)), (val))

//=============================================================================
// Register access utility
#define TOP_OR(addr, val)                   TOP_WRITE(addr, TOP_READ(addr) | (val))
#define TOP_AND(addr, val)                  TOP_WRITE(addr, TOP_READ(addr) & (val))
#define TOP_XOR(addr, val)                  TOP_WRITE(addr, TOP_READ(addr) ^ (val))

//=============================================================================
#define REG_TOP_DEVICE_ID                   0x0066
#define REG_TOP_CHIP_VERSION                0x0067
#define CHIP_VERSION_SHFT                   0
#define CHIP_VERSION_MASK                   BMASK(7:0)
#define CHIP_REVISION_SHFT                  8
#define CHIP_REVISION_MASK                  BMASK(15:8)

//=============================================================================
#ifdef MCU_AEON
    #define REG_IRQ_BASE                    (0xa0000000 + (0x101900 << 1))
    #define REG_INT_BASE_ADDR               0x0060
#else
    #define REG_IRQ_BASE                    (0x1f000000 + (0x101900 << 1))
    #define REG_INT_BASE_ADDR               0x0020
#endif

    #define REG_FIQ_MASK_L                  (REG_INT_BASE_ADDR + 0x0004)
    #define REG_FIQ_MASK_H                  (REG_INT_BASE_ADDR + 0x0005)
    #define REG_FIQEXP_MASK_L               (REG_INT_BASE_ADDR + 0x0006)
    #define REG_FIQEXP_MASK_H               (REG_INT_BASE_ADDR + 0x0007)

    #define REG_FIQ_CLEAR_L                 (REG_INT_BASE_ADDR + 0x000c)
    #define REG_FIQ_CLEAR_H                 (REG_INT_BASE_ADDR + 0x000d)
    #define REG_FIQEXP_CLEAR_L              (REG_INT_BASE_ADDR + 0x000e)
    #define REG_FIQEXP_CLEAR_H              (REG_INT_BASE_ADDR + 0x000f)

    #define REG_FIQ_PENDING_L               (REG_INT_BASE_ADDR + 0x000c)
    #define REG_FIQ_PENDING_H               (REG_INT_BASE_ADDR + 0x000d)
    #define REG_FIQEXP_PENDING_L            (REG_INT_BASE_ADDR + 0x000e)
    #define REG_FIQEXP_PENDING_H            (REG_INT_BASE_ADDR + 0x000f)

    #define REG_IRQ_MASK_L                  (REG_INT_BASE_ADDR + 0x0014)
    #define REG_IRQ_MASK_H                  (REG_INT_BASE_ADDR + 0x0015)
    #define REG_IRQEXP_MASK_L               (REG_INT_BASE_ADDR + 0x0016)
    #define REG_IRQEXP_MASK_H               (REG_INT_BASE_ADDR + 0x0017)

    #define REG_IRQ_PENDING_L               (REG_INT_BASE_ADDR + 0x001c)
    #define REG_IRQ_PENDING_H               (REG_INT_BASE_ADDR + 0x001d)
    #define REG_IRQEXP_PENDING_L            (REG_INT_BASE_ADDR + 0x001e)
    #define REG_IRQEXP_PENDING_H            (REG_INT_BASE_ADDR + 0x001f)

//=============================================================================
    #define IRQ_REG(addr)                   (*((volatile MS_U16*)(REG_IRQ_BASE + ((addr) << 2))))

    // REG_FIQ_MASK_L
    //FIQ Low 16 bits
    #define FIQL_MASK                       0xFFFF
    #define FIQ_EXTIMER0                    (0x01 << (E_FIQ_00 - E_FIQL_START))
    #define FIQ_EXTIMER1                    (0x01 << (E_FIQ_01 - E_FIQL_START))
    #define FIQ_WDT                         (0x01 << (E_FIQ_02 - E_FIQL_START))
//  #define FIQ_RESERVED                    (0x01 << (E_FIQ_03 - E_FIQL_START))
    #define FIQ_R2TOMCU_INT0                (0x01 << (E_FIQ_04 - E_FIQL_START))
    #define FIQ_R2TOMCU_INT1                (0x01 << (E_FIQ_05 - E_FIQL_START))
    #define FIQ_DSPTOMCU_INT0               (0x01 << (E_FIQ_06 - E_FIQL_START))
    #define FIQ_DSPTOMCU_INT1               (0x01 << (E_FIQ_07 - E_FIQL_START))
    #define FIQ_TEMPERATURE_FLAG_FALL       (0x01 << (E_FIQ_08 - E_FIQL_START))
    #define FIQ_TEMPERATURE_FLAG_RISE       (0x01 << (E_FIQ_09 - E_FIQL_START))
//  #define FIQ_RESERVED                    (0x01 << (E_FIQ_10 - E_FIQL_START))
    #define FIQ_HDMI_NON_PCM                (0x01 << (E_FIQ_11 - E_FIQL_START))
    #define FIQ_SPDIF_IN_NON_PCM            (0x01 << (E_FIQ_12 - E_FIQL_START))
    #define FIQ_EMAC                        (0x01 << (E_FIQ_13 - E_FIQL_START))
    #define FIQ_SE_DSP2UP                   (0x01 << (E_FIQ_14 - E_FIQL_START))
    #define FIQ_TSP2AEON                    (0x01 << (E_FIQ_15 - E_FIQL_START))

    // REG_FIQ_MASK_H
    //FIQ High 16 bits
    #define FIQH_MASK                       0xFFFF
    #define FIQ_VIVALDI_STR                 (0x01 << (E_FIQ_16 - E_FIQH_START))
    #define FIQ_VIVALDI_PTS                 (0x01 << (E_FIQ_17 - E_FIQH_START))
    #define FIQ_DSP_MIU_PROT                (0x01 << (E_FIQ_18 - E_FIQH_START))
    #define FIQ_XIU_TIMEOUT                 (0x01 << (E_FIQ_19 - E_FIQH_START))
    #define FIQ_DMDMCU2HK                   (0x01 << (E_FIQ_20 - E_FIQH_START))
    #define FIQ_VSYNC_VE4VBI                (0x01 << (E_FIQ_21 - E_FIQH_START))
    #define FIQ_FIELD_VE4VBI                (0x01 << (E_FIQ_22 - E_FIQH_START))
    #define FIQ_VDMCU2HK                    (0x01 << (E_FIQ_23 - E_FIQH_START))
    #define FIQ_VE_DONE_TT                  (0x01 << (E_FIQ_24 - E_FIQH_START))
    #define FIQ_CMDQ                        (0x01 << (E_FIQ_25 - E_FIQH_START))
//  #define FIQ_RESERVED                    (0x01 << (E_FIQ_26 - E_FIQH_START))
    #define FIQ_IR                          (0x01 << (E_FIQ_27 - E_FIQH_START))
    #define FIQ_AFEC_VSYNC                  (0x01 << (E_FIQ_28 - E_FIQH_START))
    #define FIQ_DEC_DSP2UP                  (0x01 << (E_FIQ_29 - E_FIQH_START))
//  #define FIQ_RESERVED                    (0x01 << (E_FIQ_30 - E_FIQH_START))
    #define FIQ_DSP2MIPS                    (0x01 << (E_FIQ_31 - E_FIQH_START))

    #define FIQEXPL_MASK                    0xFFFF
    #define FIQEXPL_IR_INT_RC               (0x01 << (E_FIQ_32 - E_FIQEXPL_START))
    #define FIQEXPL_AU_DMA_BUF_INT          (0x01 << (E_FIQ_33 - E_FIQEXPL_START))
    #define FIQEXPL_IR_IN                   (0x01 << (E_FIQ_34 - E_FIQEXPL_START))
//  #define FIQEXPL_RESERVED                (0x01 << (E_FIQ_35 - E_FIQH_START))
    #define FIQEXPL_8051_TO_AEON            (0x01 << (E_FIQ_36 - E_FIQEXPL_START))
    #define FIQEXPL_8051_TO_MIPS_VPE1       (0x01 << (E_FIQ_37 - E_FIQEXPL_START))
    #define FIQEXPL_8051_TO_MIPS_VPE0       (0x01 << (E_FIQ_38 - E_FIQEXPL_START))
    #define FIQEXPL_GPIO0                   (0x01 << (E_FIQ_39 - E_FIQEXPL_START))
    #define FIQEXPL_MIPS_VPE0_TO_AEON       (0x01 << (E_FIQ_40 - E_FIQEXPL_START))
    #define FIQEXPL_MIPS_VPE0_TO_MIPS_VPE1  (0x01 << (E_FIQ_41 - E_FIQEXPL_START))
    #define FIQEXPL_MIPS_VPE0_TO_8051       (0x01 << (E_FIQ_42 - E_FIQEXPL_START))
    #define FIQEXPL_GPIO1                   (0x01 << (E_FIQ_43 - E_FIQEXPL_START))
    #define FIQEXPL_MIPS_VPE1_TO_AEON       (0x01 << (E_FIQ_44 - E_FIQEXPL_START))
    #define FIQEXPL_MIPS_VPE1_TO_MIPS_VPE0  (0x01 << (E_FIQ_45 - E_FIQEXPL_START))
    #define FIQEXPL_MIPS_VPE1_TO_8051       (0x01 << (E_FIQ_46 - E_FIQEXPL_START))
    #define FIQEXPL_GPIO2                   (0x01 << (E_FIQ_47 - E_FIQEXPL_START))

    #define FIQEXPH_MASK                    0xFFFF
    #define FIQEXPH_AEON_TO_MIPS_VPE1       (0x01 << (E_FIQ_48 - E_FIQEXPH_START))
    #define FIQEXPH_AEON_TO_MIPS_VPE0       (0x01 << (E_FIQ_49 - E_FIQEXPH_START))
    #define FIQEXPH_AEON_TO_8051            (0x01 << (E_FIQ_50 - E_FIQEXPH_START))
    #define FIQEXPH_AU_SPDIF_TX_CS0         (0x01 << (E_FIQ_51 - E_FIQEXPH_START))
    #define FIQEXPH_AU_SPDIF_TX_CS1         (0x01 << (E_FIQ_52 - E_FIQEXPH_START))
    #define FIQEXPH_PCM_DMA                 (0x01 << (E_FIQ_53 - E_FIQEXPH_START))
    #define FIQEXPH_U3_DPHY                 (0x01 << (E_FIQ_54 - E_FIQEXPH_START))
    #define FIQEXPH_GPIO3                   (0x01 << (E_FIQ_55 - E_FIQEXPH_START))
    #define FIQEXPH_GPIO4                   (0x01 << (E_FIQ_56 - E_FIQEXPH_START))
    #define FIQEXPH_GPIO5                   (0x01 << (E_FIQ_57 - E_FIQEXPH_START))
    #define FIQEXPH_GPIO6                   (0x01 << (E_FIQ_58 - E_FIQEXPH_START))
    #define FIQEXPH_PWM_RP_L                (0x01 << (E_FIQ_59 - E_FIQEXPH_START))
    #define FIQEXPH_PWM_FP_L                (0x01 << (E_FIQ_60 - E_FIQEXPH_START))
    #define FIQEXPH_PWM_RP_R                (0x01 << (E_FIQ_61 - E_FIQEXPH_START))
    #define FIQEXPH_PWM_FP_R                (0x01 << (E_FIQ_62 - E_FIQEXPH_START))
    #define FIQEXPH_GPIO7                   (0x01 << (E_FIQ_63 - E_FIQEXPH_START))

    // #define REG_IRQ_PENDING_L
    #define IRQL_MASK                       0xFFFF
    #define IRQ_UART0                       (0x01 << (E_IRQ_00 - E_IRQL_START))
    #define IRQ_PMSLEEP                     (0x01 << (E_IRQ_01 - E_IRQL_START))
    #define IRQ_UHC3                        (0x01 << (E_IRQ_02 - E_IRQL_START))
    #define IRQ_MVD                         (0x01 << (E_IRQ_03 - E_IRQL_START))
    #define IRQ_PS                          (0x01 << (E_IRQ_04 - E_IRQL_START))
    #define IRQ_NFIE                        (0x01 << (E_IRQ_05 - E_IRQL_START))
    #define IRQ_USB                         (0x01 << (E_IRQ_06 - E_IRQL_START))
    #define IRQ_UHC                         (0x01 << (E_IRQ_07 - E_IRQL_START))
    #define IRQ_AU_DMA                      (0x01 << (E_IRQ_08 - E_IRQL_START))
    #define IRQ_EMAC                        (0x01 << (E_IRQ_09 - E_IRQL_START))
    #define IRQ_DISP                        (0x01 << (E_IRQ_10 - E_IRQL_START))
    #define IRQ_MSPI0                       (0x01 << (E_IRQ_11 - E_IRQL_START))
    #define IRQ_MIIC_DMA_INT3               (0x01 << (E_IRQ_12 - E_IRQL_START))
    #define IRQ_ERROR_RESP                  (0x01 << (E_IRQ_13 - E_IRQL_START))
    #define IRQ_COMB                        (0x01 << (E_IRQ_14 - E_IRQL_START))
    #define IRQ_LDM_DMA0                    (0x01 << (E_IRQ_15 - E_IRQL_START))

    // #define REG_IRQ_PENDING_H
    #define IRQH_MASK                       0xFFFF
    #define IRQ_TSP2HK                      (0x01 << (E_IRQ_16 - E_IRQH_START))
    #define IRQ_VE                          (0x01 << (E_IRQ_17 - E_IRQH_START))
    #define IRQ_CIMAX2MCU                   (0x01 << (E_IRQ_18 - E_IRQH_START))
    #define IRQ_DC                          (0x01 << (E_IRQ_19 - E_IRQH_START))
    #define IRQ_GOP                         (0x01 << (E_IRQ_20 - E_IRQH_START))
    #define IRQ_PCM                         (0x01 << (E_IRQ_21 - E_IRQH_START))
    #define IRQ_LDM_DMA1                    (0x01 << (E_IRQ_22 - E_IRQH_START))
    #define IRQ_SMART                       (0x01 << (E_IRQ_23 - E_IRQH_START))
    #define IRQ_MHL_CBUS_PM                 (0x01 << (E_IRQ_24 - E_IRQH_START))
//  #define IRQ_RESERVED                    (0x01 << (E_IRQ_25 - E_IRQH_START))
    #define IRQ_DDC2BI                      (0x01 << (E_IRQ_26 - E_IRQH_START))
    #define IRQ_SCM                         (0x01 << (E_IRQ_27 - E_IRQH_START))
    #define IRQ_VBI                         (0x01 << (E_IRQ_28 - E_IRQH_START))
    #define IRQ_MVD2MIPS                    (0x01 << (E_IRQ_29 - E_IRQH_START))
    #define IRQ_GPD                         (0x01 << (E_IRQ_30 - E_IRQH_START))
    #define IRQ_ADCDVI2RIU                  (0x01 << (E_IRQ_31 - E_IRQH_START))

    #define IRQEXPL_MASK                    0xFFFF
    #define IRQEXPL_HVD                     (0x01 << (E_IRQ_32 - E_IRQEXPL_START))
    #define IRQEXPL_USB1                    (0x01 << (E_IRQ_33 - E_IRQEXPL_START))
    #define IRQEXPL_UHC1                    (0x01 << (E_IRQ_34 - E_IRQEXPL_START))
    #define IRQEXPL_MIU                     (0x01 << (E_IRQ_35 - E_IRQEXPL_START))
    #define IRQEXPL_USB2                    (0x01 << (E_IRQ_36 - E_IRQEXPL_START))
    #define IRQEXPL_UHC2                    (0x01 << (E_IRQ_37 - E_IRQEXPL_START))
    #define IRQEXPL_AEON2HI                 (0x01 << (E_IRQ_38 - E_IRQEXPL_START))
    #define IRQEXPL_UART1                   (0x01 << (E_IRQ_39 - E_IRQEXPL_START))
    #define IRQEXPL_UART2                   (0x01 << (E_IRQ_40 - E_IRQEXPL_START))
    #define IRQEXPL_MSPI1                   (0x01 << (E_IRQ_41 - E_IRQEXPL_START))
    #define IRQEXPL_MIU_SECURITY            (0x01 << (E_IRQ_42 - E_IRQEXPL_START))
    #define IRQEXPL_MIIC_DMA_INT2           (0x01 << (E_IRQ_43 - E_IRQEXPL_START))
    #define IRQEXPL_MIIC_INT2               (0x01 << (E_IRQ_44 - E_IRQEXPL_START))
    #define IRQEXPL_JPD                     (0x01 << (E_IRQ_45 - E_IRQEXPL_START))
    #define IRQEXPL_PM                      (0x01 << (E_IRQ_46 - E_IRQEXPL_START))
    #define IRQEXPL_MFE                     (0x01 << (E_IRQ_47 - E_IRQEXPL_START))

    #define IRQEXPH_MASK                    0xFFFF
    #define IRQEXPH_BDMA0                   (0x01 << (E_IRQ_48 - E_IRQEXPH_START))
    #define IRQEXPH_BDMA1                   (0x01 << (E_IRQ_49 - E_IRQEXPH_START))
    #define IRQEXPH_UART2MCU                (0x01 << (E_IRQ_50 - E_IRQEXPH_START))
    #define IRQEXPH_URDMA2MCU               (0x01 << (E_IRQ_51 - E_IRQEXPH_START))
    #define IRQEXPH_DVI_HDMI_HDCP           (0x01 << (E_IRQ_52 - E_IRQEXPH_START))
    #define IRQEXPH_G3D2MCU                 (0x01 << (E_IRQ_53 - E_IRQEXPH_START))
    #define IRQEXPH_CEC                     (0x01 << (E_IRQ_54 - E_IRQEXPH_START))
    #define IRQEXPH_HDCP_IIC                (0x01 << (E_IRQ_55 - E_IRQEXPH_START))
    #define IRQEXPH_HDCP_X74                (0x01 << (E_IRQ_56 - E_IRQEXPH_START))
    #define IRQEXPH_WADR_ERR                (0x01 << (E_IRQ_57 - E_IRQEXPH_START))
    #define IRQEXPH_DCSUB                   (0x01 << (E_IRQ_58 - E_IRQEXPH_START))
    #define IRQEXPH_GE                      (0x01 << (E_IRQ_59 - E_IRQEXPH_START))
    #define IRQEXPH_MIIC_DMA1               (0x01 << (E_IRQ_60 - E_IRQEXPH_START))
    #define IRQEXPH_MIIC_INT1               (0x01 << (E_IRQ_61 - E_IRQEXPH_START))
    #define IRQEXPH_MIIC_DMA0               (0x01 << (E_IRQ_62 - E_IRQEXPH_START))
    #define IRQEXPH_MIIC_INT0               (0x01 << (E_IRQ_63 - E_IRQEXPH_START))

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
#define INTERFACE extern

INTERFACE MS_U32    u32_ge0_mmio_base;
//extern MS_U32     u32_bdma_mmio_base;
//extern MS_U32     u32_scaler_mmio_base;

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define     REG_GE0_BASE    u32_ge0_mmio_base
//#define   REG_BDMA_BASE   u32_bdma_mmio_base
//#define   REG_SCALER_BASE u32_scaler_mmio_base

//-------------------------------------------------------------------------------------------------

// Macros

//-------------------------------------------------------------------------------------------------

#define MReg_Write2Byte(u32Base, u32Reg, u16Val)    \
    do {((volatile MS_U16*)(u32Base))[((u32Reg))] = u16Val;} while(0)

#define MReg_Read2Byte(u32Base, u32Reg)     \
    ((volatile MS_U16*)(u32Base))[((u32Reg))]

#define MReg_WriteByte(u32Base, u32Reg, u8Val)  \
    do{((volatile MS_U8*)(u32Base))[((u32Reg) * 2) - ((u32Reg) & 1)] = u8Val;} while(0)

#define MReg_ReadByte(u32Base, u32Reg)  \
    ((volatile MS_U8*)(u32Base))[((u32Reg) * 2) - ((u32Reg) & 1)]

 #define MReg_Write3Byte(u32Base, u32Reg, u32Val)   \
    do {    \
        if ((u32Reg) & 0x01)    \
        {   \
            MReg_WriteByte(u32Base, u32Reg , u32Val);   \
            MReg_Write2Byte(u32Base, (u32Reg + 1), ((u32Val) >> 8));    \
        }   \
        else    \
        {   \
            MReg_Write2Byte(u32Base, (u32Reg), u32Val);     \
            MReg_WriteByte(u32Base, (u32Reg + 2),  ((u32Val) >> 16));   \
        }   \
    } while(0)

#define MReg_Write4Byte(u32Base, u32Reg, u32Val)    \
    do {    \
        if ((u32Reg) & 0x01)    \
        {   \
            MReg_WriteByte(u32Base, u32Reg,  u32Val);   \
            MReg_Write2Byte(u32Base, (u32Reg + 1), ((u32Val) >> 8));    \
            MReg_WriteByte(u32Base, (u32Reg + 3), ((u32Val) >> 24));    \
        }   \
        else    \
        {   \
            MReg_Write2Byte(u32Base, u32Reg, u32Val);   \
            MReg_Write2Byte(u32Base, (u32Reg + 2), ((u32Val) >> 16));   \
        }   \
    } while(0)

#define MReg_WriteByteMask(u32Base, u32Reg, u8Val, u8Msk)   \
    do {    \
        MReg_WriteByte(u32Base, u32Reg, (MReg_ReadByte(u32Base, ((u32Reg))) & ~(u8Msk)) | ((u8Val) & (u8Msk))); \
    } while(0)

#define MReg_Write2ByteMask(u32Base, u32Reg, u16Val, u16Msk)    \
    do {    \
        if (((u32Reg) & 0x01))  \
        {   \
            MReg_WriteByteMask( u32Base, ((u32Reg) + 1) , (((u16Val) & 0xff00) >> 8) , (((u16Msk) & 0xff00) >> 8) );                                                                          \
            MReg_WriteByteMask( u32Base, (u32Reg) , ((u16Val) & 0x00ff) , ((u16Msk) & 0x00ff));                                                                          \
        }   \
        else    \
        {   \
            MReg_Write2Byte(u32Base, u32Reg, (((u16Val) & (u16Msk)) | (MReg_Read2Byte(u32Base, u32Reg) & (~(u16Msk)))));                                                       \
        }   \
    } while(0)

#endif // _REG_SYSTEM_H_

