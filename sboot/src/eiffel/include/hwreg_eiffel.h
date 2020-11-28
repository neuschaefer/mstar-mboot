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

#ifndef _HWREG_EIFFEL_H
#define _HWREG_EIFFEL_H

#ifndef _C_RIUBASE_H_
#include "c_riubase.h"
#endif

#ifndef _C_PM_RIUBASE_H_
#include "c_pm_riubase.h"
#endif

#ifndef _C_VDMCU_RIUBASE_H_
#include "c_vdmcu_riubase.h"
#endif

// PM_REGISRTER for backward compatiable
#define WDT_RST                                 RIUBASE_WDT         //0x003000 ~ 0x00301f
#define PM_SLEEP_REG_BASE                       RIUBASE_PM_SLEEP    //0x000E00 - 0x000E7F
#define ISP_REG_BASE                            RIUBASE_ISP         //0x000800 ~ 0x0008bf

//NON_PM_REGISRTER for backward compatiable
#define MIU2_REG_BASE                           RIUBASE_MIU2        //0x100600 ~ 0x1006ff
#define BDMA_REG_BASE                           RIUBASE_BDMA        //0x100900 ~ 0x10097F
#define MIU_REG_BASE                            RIUBASE_MIU         //0x101200 ~ 0x1012FF
#define SVD_REG_BASE                            RIUBASE_HVD         //0x101B00 ~ 0x101BFF
#define CHIP_REG_BASE                           RIUBASE_CHIP        //0x101e00 ~ 0x101eff
#define ADC_ATOP_REG_BASE                       RIUBASE_ADC_ATOP    //0x102500 ~ 0x1025ff
#define ADC_DTOP_REG_BASE                       RIUBASE_ADC_DTOP    //0x102600 ~ 0x1026ff
#define HDMI_REG_BASE                           RIUBASE_HDMI        //0x102700 ~ 0x1027ff
#define SC0_REG_BASE                            RIUBASE_SC0         //0x102e00 ~ 0x102eff
#define SC1_REG_BASE                            RIUBASE_SC1         //0x102f00 ~ 0x102fff
#define MAILBOX_REG_BASE                        RIUBASE_MAILBOX     //0x103380 ~ 0x1033FF

#define REG_RESET_CPU_8051_GO                   (RIUBASE_PM_SLEEP + 0x53)
#define REG_RESET_CPU_8051                      (RIUBASE_PM_SLEEP + 0x54)

#define WDT_INT_TIMER_0                         (RIUBASE_WDT + 0x06)
#define WDT_TIMER_0                             (RIUBASE_WDT + 0x08)

#define REG_SVD_SW_RST                          (SVD_REG_BASE + 0X0A * 2)
    #define REG_SVD_RESET_SWRST                 BIT0
    #define REG_SVD_RESET_CPURST                BIT1
    #define REG_SVD_RESET_SWRST_FIN             BIT2
    #define REG_SVD_RESET_CPURST_FIN            BIT3

//PM_TOP (0x001E)
#define REG_CHIP_ID_MAJOR                       (RIUBASE_PM_TOP + 0xCC)
#define REG_CHIP_ID_MINOR                       (RIUBASE_PM_TOP + 0xCD)
#define REG_CHIP_VERSION                        (RIUBASE_PM_TOP + 0xCE)
#define REG_CHIP_REVISION                       (RIUBASE_PM_TOP + 0xCF)

//CHIPTOP (0x101E)
#define REG_MUX_UART_JTAG                       (CHIP_REG_BASE + 0xA6)
    #define UART_SEL_MHEG5                      0x01
    #define UART_SEL_VD_MHEG5                   0x02
    #define UART_SEL_TSP                        0x03
    #define UART_SEL_PIU_UART0                  0x04
    #define UART_SEL_PIU_UART1                  0x05
    #define UART_SEL_PIU_FAST_UART              0x07
    #define UART_SEL_VD_MCU51_TXD0              0x0A
    #define UART_SEL_VD_MCU51_TXD1              0x0B
    
//MVD
#define MVD_CTRL                                (RIUBASE_MVD + 0x00)
#define MVD_STATUS                              (RIUBASE_MVD + 0x01)    //0x1101
#define MVD_COMMAND                             (RIUBASE_MVD + 0x02)    //0x1102
#define MVD_ARG0                                (RIUBASE_MVD + 0x04)    //0x1104
#define MVD_ARG1                                (RIUBASE_MVD + 0x05)    //0x1105
#define MVD_ARG2                                (RIUBASE_MVD + 0x06)    //0x1106
#define MVD_ARG3                                (RIUBASE_MVD + 0x07)    //0x1107

//------------------------------------------------------------------------------
// Byte DMA controller
//------------------------------------------------------------------------------
#define REG_BDMA_INT_STATE                      (BDMA_REG_BASE + 0x00)
#define REG_BDMA_QUEUE_STATUS                   (BDMA_REG_BASE + 0x02)
#define REG_BDMA_HOST0_INT_EN                   (BDMA_REG_BASE + 0x04)
#define REG_BDMA_HOST1_INT_EN                   (BDMA_REG_BASE + 0x08)

#define REG_BDMA_CHCTRL_OFFSET                  (0x20)
#define REG_BDMA_CH0_CTRL                       (BDMA_REG_BASE + 0x20)
#define REG_BDMA_CH0_MISC                       (BDMA_REG_BASE + 0x21)
#define REG_BDMA_CH0_STATUS                     (BDMA_REG_BASE + 0x22)
#define REG_BDMA_CH0_SIZE_0                     (BDMA_REG_BASE + 0x24)
#define REG_BDMA_CH0_SIZE_1                     (BDMA_REG_BASE + 0x25)
#define REG_BDMA_CH0_SIZE_2                     (BDMA_REG_BASE + 0x26)
#define REG_BDMA_CH0_SIZE_3                     (BDMA_REG_BASE + 0x27)
#define REG_BDMA_CH0_SRC_ADDR_0                 (BDMA_REG_BASE + 0x28)
#define REG_BDMA_CH0_SRC_ADDR_1                 (BDMA_REG_BASE + 0x29)
#define REG_BDMA_CH0_SRC_ADDR_2                 (BDMA_REG_BASE + 0x2A)
#define REG_BDMA_CH0_SRC_ADDR_3                 (BDMA_REG_BASE + 0x2B)
#define REG_BDMA_CH0_DST_ADDR_0                 (BDMA_REG_BASE + 0x2C)
#define REG_BDMA_CH0_DST_ADDR_1                 (BDMA_REG_BASE + 0x2D)
#define REG_BDMA_CH0_DST_ADDR_2                 (BDMA_REG_BASE + 0x2E)
#define REG_BDMA_CH0_DST_ADDR_3                 (BDMA_REG_BASE + 0x2F)
#define REG_BDMA_CH0_EXTBITS_0                  (BDMA_REG_BASE + 0x30)
#define REG_BDMA_CH0_EXTBITS_1                  (BDMA_REG_BASE + 0x31)
#define REG_BDMA_CH0_EXTBITS_2                  (BDMA_REG_BASE + 0x32)
#define REG_BDMA_CH0_EXTBITS_3                  (BDMA_REG_BASE + 0x33)
#define REG_BDMA_CH0_MATCHADDR_0                (BDMA_REG_BASE + 0x34)
#define REG_BDMA_CH0_MATCHADDR_1                (BDMA_REG_BASE + 0x35)
#define REG_BDMA_CH0_MATCHADDR_2                (BDMA_REG_BASE + 0x36)
#define REG_BDMA_CH0_MATCHADDR_3                (BDMA_REG_BASE + 0x37)
#define REG_BDMA_CH0_CRC_CTRL                   (BDMA_REG_BASE + 0x38)
#define REG_BDMA_CH0_CRC_RESULT0                (BDMA_REG_BASE + 0x3A)
#define REG_BDMA_CH0_CRC_RESULT1                (BDMA_REG_BASE + 0x3B)
#define REG_BDMA_CH0_CRC_RESULT2                (BDMA_REG_BASE + 0x3C)
#define REG_BDMA_CH0_CRC_RESULT3                (BDMA_REG_BASE + 0x3D)

#define REG_BDMA_CH1_CTRL                       (BDMA_REG_BASE + 0x40)
#define REG_BDMA_CH1_MISC                       (BDMA_REG_BASE + 0x41)
#define REG_BDMA_CH1_STATUS                     (BDMA_REG_BASE + 0x42)
#define REG_BDMA_CH1_SIZE_0                     (BDMA_REG_BASE + 0x44)
#define REG_BDMA_CH1_SIZE_1                     (BDMA_REG_BASE + 0x45)
#define REG_BDMA_CH1_SIZE_2                     (BDMA_REG_BASE + 0x46)
#define REG_BDMA_CH1_SIZE_3                     (BDMA_REG_BASE + 0x47)
#define REG_BDMA_CH1_SRC_ADDR_0                 (BDMA_REG_BASE + 0x48)
#define REG_BDMA_CH1_SRC_ADDR_1                 (BDMA_REG_BASE + 0x49)
#define REG_BDMA_CH1_SRC_ADDR_2                 (BDMA_REG_BASE + 0x4A)
#define REG_BDMA_CH1_SRC_ADDR_3                 (BDMA_REG_BASE + 0x4B)
#define REG_BDMA_CH1_DST_ADDR_0                 (BDMA_REG_BASE + 0x4C)
#define REG_BDMA_CH1_DST_ADDR_1                 (BDMA_REG_BASE + 0x4D)
#define REG_BDMA_CH1_DST_ADDR_2                 (BDMA_REG_BASE + 0x4E)
#define REG_BDMA_CH1_DST_ADDR_3                 (BDMA_REG_BASE + 0x4F)
#define REG_BDMA_CH1_EXTBITS_0                  (BDMA_REG_BASE + 0x50)
#define REG_BDMA_CH1_EXTBITS_1                  (BDMA_REG_BASE + 0x51)
#define REG_BDMA_CH1_EXTBITS_2                  (BDMA_REG_BASE + 0x52)
#define REG_BDMA_CH1_EXTBITS_3                  (BDMA_REG_BASE + 0x53)
#define REG_BDMA_CH1_MATCHADDR_0                (BDMA_REG_BASE + 0x54)
#define REG_BDMA_CH1_MATCHADDR_1                (BDMA_REG_BASE + 0x55)
#define REG_BDMA_CH1_MATCHADDR_2                (BDMA_REG_BASE + 0x56)
#define REG_BDMA_CH1_MATCHADDR_3                (BDMA_REG_BASE + 0x57)
#define REG_BDMA_CH1_CRC_CTRL                   (BDMA_REG_BASE + 0x58)
#define REG_BDMA_CH1_CRC_RESULT0                (BDMA_REG_BASE + 0x5A)
#define REG_BDMA_CH1_CRC_RESULT1                (BDMA_REG_BASE + 0x5B)
#define REG_BDMA_CH1_CRC_RESULT2                (BDMA_REG_BASE + 0x5C)
#define REG_BDMA_CH1_CRC_RESULT3                (BDMA_REG_BASE + 0x5D)

    //---------------------------------------------
    // definition for REG_BDMA_CH0_CTRL/REG_BDMA_CH1_CTRL
    #define BDMA_TRIGGER                        BIT0
    #define BDMA_STOP                           BIT1
    #define BDMA_PATTERN_SEARCH_TRIGGER         BIT4
    #define BDMA_RESTART_SEARCH                 BIT6
    #define BDMA_DISABLE_PATTERN_SEARCH         BIT7
    //---------------------------------------------
    // definition for REG_BDMA_CH0_MISC/REG_BDMA_CH1_MISC
    #define BDMA_SRC_MIU                        BIT0
    #define BDMA_DST_MIU                        BIT2
    #define BDMA_ADDR_DIRECTION                 BIT4
    #define BDMA_DMA_DONE_INT_EN                BIT5
    #define BDMA_DMA_ERR_INT_EN                 BIT6
    #define BDMA_PATTERN_SEARCH_DONE            BIT7
    //---------------------------------------------
    // definition for REG_BDMA_CH0_STATUS/REG_BDMA_CH1_STATUS
    #define BDMA_CH_QUEUED                      BIT0
    #define BDMA_CH_BUSY                        BIT1
    #define BDMA_CH_DONE                        BIT2
    #define BDMA_CH_ERR                         BIT3
    #define BDMA_CH_SEARCH_DONE                 BIT4
    #define BDMA_CH_SEARCH_MATCH                BIT5
    //---------------------------------------------
    // definition for REG_BDMA_CH0_STATUS/REG_BDMA_CH1_STATUS
    #define BDMA_CRC_TRIGGER                    BIT0
    #define BDMA_CRC_RETRIGGER                  BIT1
    #define BDMA_CRC_RETRIGGERINIT              BIT2
    #define BDMA_CRC_DONE                       BIT4
    #define BDMA_CRC_CLEARSTATUS                BIT4
    #define BDMA_CRC_INT_EN                     BIT5
    #define BDMA_CRC_REFLECTION                 BIT6

//------------------------------------------------------------------------------
// MCU and PIU Reg (0x1000)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// chip top
//------------------------------------------------------------------------------

//PM
#define PM_ADC_RGB                              0x2508
#define PM_ADC_Y                                0x2509
#define PM_GMC                                  0x250A
#define PM_ADC_FBLANK                           0x2580
#define PM_DAC_CVBS                             0x2590
#define PM_DAC_CVBS2                            0x2592
#define PM_CVBS_BUF_OUT                         0x25A0
#define PM_CVBS2_BUF_OUT                        0x25A4
//<< End

// MISC
//------------------------------------------------------------------------------
// definition for REG_CT_MISC0      //reg[0x1e22]
#define MISC_MCU_CLKSEL_MASK                    0x01    // MASK
#define MISC_MCU_CLKSEL_DFT                     0x00
#define MISC_MCU_CLKSEL_EX                      0x01
#define MISC_VD_CLKSEL_MASK                     0x02    // MASK
#define MISC_VD_CLKSEL_VDADC                    0x00
#define MISC_VD_CLKSEL_ADC                      0x02
#define MISC_DE_ONLY_F1                         0x04
#define MISC_DE_ONLY_F2_SCTOP                   0x08
#define MISC_USBSYN_RST                         0x10
#define MISC_STC0SYN_RST                        0x20
#define MISC_STC0CWSEL_MASK                     0x80    // MASK
#define MISC_STC0CWSEL_HKMCU                    0x00
#define MISC_STC0CWSEL_TSP                      0x80
//--------------------------------------------------

// definition for REG_CT_MISC1      //reg[0x1e23]
#define MISC_UPDATE_STC0CW                      0x02
#define MISC_UPDATE_DC0CW_FRUN                  0x08
#define MISC_UPDATE_DC0CW_SYNC                  0x40

//---------------------------------------------
// definition for REG_CKG_MCU   //reg[0x1e45]
// MPLL   = XTAL * 36
// USBCLK = XTAL * 40
#define MCU_CLK_ENABLE                          0x00
#define MCU_CLK_DISABLE                         0x01
#define MCU_CLK_NONINVERT                       0x00
#define MCU_CLK_INVERT                          0x02
#define MCU_CLK_MASK                            0x1C
#define MCU_CLK_172P8MHZ                        0x00    // MPLL   / 2.5
#define MCU_CLK_160MHZ                          0x04    // USBCLK / 3
#define MCU_CLK_144MHZ                          0x08    // MPLL
#define MCU_CLK_123MHZ                          0x0C    // No function
#define MCU_CLK_108MHZ                          0x10    // No function
#define MCU_CLK_MEM                             0x14    // MIUCLK
#define MCU_CLK_MEMD2                           0x18    // MIUCLK / 2
#define MCU_CLK_0                               0x1C

//------------------------------------------------------------------------------
// IR register define
//------------------------------------------------------------------------------

#define IR_CTRL                                 (RIUBASE_IR + 0x80)  //0x3D80
#define IR_CHECK                                (RIUBASE_IR + 0x81)  //0x3D81
#define IR_HDC_UPB_L                            (RIUBASE_IR + 0x82)  //0x3D82
#define IR_HDC_UPB_H                            (RIUBASE_IR + 0x83)  //0x3D83
#define IR_HDC_LOB_L                            (RIUBASE_IR + 0x84)  //0x3D84
#define IR_HDC_LOB_H                            (RIUBASE_IR + 0x85)  //0x3D85
#define IR_OFC_UPB_L                            (RIUBASE_IR + 0x86)  //0x3D86
#define IR_OFC_UPB_H                            (RIUBASE_IR + 0x87)  //0x3D87
#define IR_OFC_LOB_L                            (RIUBASE_IR + 0x88)  //0x3D88
#define IR_OFC_LOB_H                            (RIUBASE_IR + 0x89)  //0x3D89
#define IR_OFC_RP_UPB_L                         (RIUBASE_IR + 0x8A)  //0x3D8A
#define IR_OFC_RP_UPB_H                         (RIUBASE_IR + 0x8B)  //0x3D8B
#define IR_OFC_RP_LOB_L                         (RIUBASE_IR + 0x8C)  //0x3D8C
#define IR_OFC_RP_LOB_H                         (RIUBASE_IR + 0x8D)  //0x3D8D
#define IR_LG01H_UPB_L                          (RIUBASE_IR + 0x8E)  //0x3D8E
#define IR_LG01H_UPB_H                          (RIUBASE_IR + 0x8F)  //0x3D8F
#define IR_LG01H_LOB_L                          (RIUBASE_IR + 0x90)  //0x3D90
#define IR_LG01H_LOB_H                          (RIUBASE_IR + 0x91)  //0x3D91
#define IR_LG0_UPB_L                            (RIUBASE_IR + 0x92)  //0x3D92
#define IR_LG0_UPB_H                            (RIUBASE_IR + 0x93)  //0x3D93
#define IR_LG0_LOB_L                            (RIUBASE_IR + 0x94)  //0x3D94
#define IR_LG0_LOB_H                            (RIUBASE_IR + 0x95)  //0x3D95
#define IR_LG1_UPB_L                            (RIUBASE_IR + 0x96)  //0x3D96
#define IR_LG1_UPB_H                            (RIUBASE_IR + 0x97)  //0x3D97
#define IR_LG1_LOB_L                            (RIUBASE_IR + 0x98)  //0x3D98
#define IR_LG1_LOB_H                            (RIUBASE_IR + 0x99)  //0x3D99
#define IR_SEPR_UPB_L                           (RIUBASE_IR + 0x9A)  //0x3D9A
#define IR_SEPR_UPB_H                           (RIUBASE_IR + 0x9B)  //0x3D9B
#define IR_SEPR_LOB_L                           (RIUBASE_IR + 0x9C)  //0x3D9C
#define IR_SEPR_LOB_H                           (RIUBASE_IR + 0x9D)  //0x3D9D
#define IR_TIMEOUT_CYC_0                        (RIUBASE_IR + 0x9E)  //0x3D9E
#define IR_TIMEOUT_CYC_1                        (RIUBASE_IR + 0x9F)  //0x3D9F
#define IR_TIMEOUT_CYC_2                        (RIUBASE_IR + 0xA0)  //0x3DA0
#define IR_CODEBYTE                             (RIUBASE_IR + 0xA1)  //0x3DA1
#define IR_SEPR_BIT                             (RIUBASE_IR + 0xA2)  //0x3DA2
#define IR_FIFO_CTRL                            (RIUBASE_IR + 0xA3)  //0x3DA3  // different location with Saturn
#define IR_CCODE_L                              (RIUBASE_IR + 0xA4)  //0x3DA4
#define IR_CCODE_H                              (RIUBASE_IR + 0xA5)  //0x3DA5
#define IR_GLHRM_NUM_L                          (RIUBASE_IR + 0xA6)  //0x3DA6
#define IR_GLHRM_NUM_H                          (RIUBASE_IR + 0xA7)  //0x3DA7
#define IR_CKDIV_NUM_REG                        (RIUBASE_IR + 0xA8)  //0x3DA8  // different location with Saturn
#define IR_KEY                                  (RIUBASE_IR + 0xA9)  //0x3DA9
#define IR_SHOT_CNT_0                           (RIUBASE_IR + 0xAA)  //0x3DAA
#define IR_SHOT_CNT_1                           (RIUBASE_IR + 0xAB)  //0x3DAB
#define IR_SHOT_CNT_2                           (RIUBASE_IR + 0xAC)  //0x3DAC
#define IR_RPT_FIFOEMPTY                        (RIUBASE_IR + 0xAD)  //0x3DAD
#define IR_FIFO_READ_PULSE                      (RIUBASE_IR + 0xB0)  //0x3DB0  // added in Saturn2

#define PM_OFF_FLAG                             (RIUBASE_PM_SLEEP + 0x68)  //0x0E68//0x0E54

#define PM_SYS_PD                               (0x01)
#define PM_GPIO_ACT_LEVEL                       (0x02)
#define PM_IR_ACT_LEVEL                         (0x04)
#define PM_IR_PD                                (0x08)
#define PM_TEST_MODE                            (0x10)
#define PM_CHK_IR_NOISE                         (0x20)

#define PM_XTL_PWD0_VAL                         (0x8E)
#define PM_XTL_PWD1_VAL                         (0x9F)
#define PM_SB_PWD0_VAL                          (0xB4)
#define PM_SB_PWD1_VAL                          (0xA5)
#define PM_TH0_VAL                              (0xBA)
#define PM_TH1_VAL                              (0x0D)

#define PM_FIRST_BOOTUP                         (0x01)
#define PM_MODE_MASK                            (0x06)

#if ( 1 )  //POWERUP_MODE == PUMODE_WORK )
    #define PM_MODE_ON                          (0x00)
    #define PM_MODE_OFF_EXEC                    (0x02)
    #define PM_MODE_OFF                         (0x04)
    #define PM_MODE_ON_EXEC                     (0x06)
#else
    #define PM_MODE_ON                          (0x02)
    #define PM_MODE_OFF_EXEC                    (0x00)
    #define PM_MODE_OFF                         (0x04)
    #define PM_MODE_ON_EXEC                     (0x06)
#endif

#define PM_P3_RESET_FLAG                        (0x08)
#define PM_PDMODE_MASK                          (0x30)
#define PM_PDMODE_S1                            (0x00)
#define PM_PDMODE_S2                            (0x10)
#define PM_PDMODE_S3                            (0x20)
#define PM_PDMODE_S4                            (0x30)

#define VGA_POWERSAVING                         (0x40)

//------------------------------------------------------------------------------
// 2. - MIU Reg
//------------------------------------------------------------------------------
//#define DDR_FREQ_SET_0                        0x1220
//#define DDR_FREQ_SET_1                        0x1221
//#define DDR_FREQ_STEP                         0x1224
//#define DDR_FREQ_DIV_1                        0x1225
//#define DDR_FREQ_INPUT_DIV_2                  0x1226
//#define DDR_FREQ_LOOP_DIV_2                   0x1227
//#define DDR_CLK_SELECT                        0x123E
//#define DDR_FREQ_STATUS                       0x123F

//#define MIU_RQ0L_MASK                         (MIU_REG_BASE+0x46)//Reg[0x1246]
//#define MIU_RQ0H_MASK                         (MIU_REG_BASE+0x47)
//#define MIU_RQ1L_MASK                         (MIU_REG_BASE+0x66)
//#define MIU_RQ1H_MASK                         (MIU_REG_BASE+0x67)
//#define MIU_RQ2L_MASK                         (MIU_REG_BASE+0x86)
//#define MIU_RQ2H_MASK                         (MIU_REG_BASE+0x87)

#define MIU_PROTECT_EN                          (MIU_REG_BASE + 0xC0)
#define MIU_PROTECT_SDR_LIKE                    (MIU_REG_BASE + 0xC1)

#define MIU_PROTECT0_ID0                        (MIU_REG_BASE + 0xC2)
#define MIU_PROTECT0_ID1                        (MIU_REG_BASE + 0xC3)
#define MIU_PROTECT0_ID2                        (MIU_REG_BASE + 0xC4)
#define MIU_PROTECT0_ID3                        (MIU_REG_BASE + 0xC5)
#define MIU_PROTECT0_START_ADDR_H               (MIU_REG_BASE + 0xC6)
#define MIU_PROTECT0_START_ADDR_L               (MIU_REG_BASE + 0xC7)
#define MIU_PROTECT0_END_ADDR_H                 (MIU_REG_BASE + 0xC8)
#define MIU_PROTECT0_END_ADDR_L                 (MIU_REG_BASE + 0xC9)

#define MIU_PROTECT1_ID0                        (MIU_REG_BASE + 0xCA)
#define MIU_PROTECT1_ID1                        (MIU_REG_BASE + 0xCB)
#define MIU_PROTECT1_START_ADDR_H               (MIU_REG_BASE + 0xCC)
#define MIU_PROTECT1_START_ADDR_L               (MIU_REG_BASE + 0xCD)
#define MIU_PROTECT1_END_ADDR_H                 (MIU_REG_BASE + 0xCE)
#define MIU_PROTECT1_END_ADDR_L                 (MIU_REG_BASE + 0xCF)

#define MIU_PROTECT2_ID0                        (MIU_REG_BASE + 0xD0)
#define MIU_PROTECT2_ID1                        (MIU_REG_BASE + 0xD1)
#define MIU_PROTECT2_START_ADDR_H               (MIU_REG_BASE + 0xD2)
#define MIU_PROTECT2_START_ADDR_L               (MIU_REG_BASE + 0xD3)
#define MIU_PROTECT2_END_ADDR_H                 (MIU_REG_BASE + 0xD4)
#define MIU_PROTECT2_END_ADDR_L                 (MIU_REG_BASE + 0xD5)

#define MIU_PROTECT3_ID0                        (MIU_REG_BASE + 0xD6)
#define MIU_PROTECT3_ID1                        (MIU_REG_BASE + 0xD7)
#define MIU_PROTECT3_START_ADDR_H               (MIU_REG_BASE + 0xD8)
#define MIU_PROTECT3_START_ADDR_L               (MIU_REG_BASE + 0xD9)
#define MIU_PROTECT3_END_ADDR_H                 (MIU_REG_BASE + 0xDA)
#define MIU_PROTECT3_END_ADDR_L                 (MIU_REG_BASE + 0xDB)

#define MIU_PROTECT_LOG_CLEAR                   (MIU_REG_BASE + 0xDE)

//#define MIU_DDFSET                            0x1220
//#define MIU_DDFSPAN                           0x1222
//#define MIU_DDFSTEP                           0x1224
//#define MIU_PLLCTRL                           0x1225

//#define MIU_RQ1_CTRL0                         0x1260
//#define MIU_RQ2_CTRL0                         0x1280
//#define MIU_RQ2_CTRL1                         0x1281
//#define MIU_RQ2_HPRIORITY                     0x1288
//#define MIU_GE_FLOW_CTRL_TIME                 0x1294
//#define MIU_PROTECT_LOG_CLEAR                 0x12DE

// MIU selection registers
//#define REG_MIU_SEL0                          0x12F0
//#define REG_MIU_SEL1                          0x12F1
//#define REG_MIU_SEL2                          0x12F2
//#define REG_MIU_SEL3                          0x12F3
//#define REG_MIU_SEL4                          0x12F4
//#define REG_MIU_SEL5                          0x12F5
//#define REG_MIU_SEL6                          0x12F6
//#define REG_MIU_SEL7                          0x12F7

//----------------------------------------------------------------------------
// 5. DEMUX Reg
//----------------------------------------------------------------------------
//#define NIM_HWCONFIG0                         0x1558
//#define NIM_HWCONFIG1                         0x155A
//#define NIM_HWCONFIG2                         0x1584
//#define NIM_HWCONFIG3                         0x1586
//#define NIM_HWINPORT                          0x155E

//#define PCR_L0                                0x1560
//#define PCR_L1                                0x1561
//#define PCR_L2                                0x1562
//#define PCR_L3                                0x1563
//#define PCR_H                                 0x1564

#define SECISR_INTCODE0                         0x1570
#define SECISR_INTCODE1                         0x1571
#define SECISR_INTCODE2                         0x1572
#define SECISR_INTCODE3                         0x1573
#define SECISR_ACKCODE0                         0x1580
#define SECISR_ACKCODE1                         0x1581
#define SECISR_ACKCODE2                         0x1582
#define SECISR_ACKCODE3                         0x1583

#define TSP_DMA_RADDR0                          0x15F0
#define TSP_DMA_RADDR1                          0x15F1
#define TSP_DMA_RNUM0                           0x15F2
#define TSP_DMA_RNUM1                           0x15F3
#define TSP_CTRL                                0x15F4

//----------------------------------------------------------------------------
// 11. GOP Reg
//----------------------------------------------------------------------------
#define GOP_REG_VAL(x)                          (1<<x)

#define __ERIS_GOP_REG(bk, reg)                 (((U16)(bk)<<8) + (reg) * 2)
#define __GOP_REG(reg)                          ((reg) * 2)

#define GOP_4G_CTRL0                            __ERIS_GOP_REG(0, 0x00)
#define GOP_4G_CTRL1                            __ERIS_GOP_REG(0, 0x01)
#define GOP_4G_RATE                             __ERIS_GOP_REG(0, 0x02)
#define GOP_4G_PALDATA_L                        __ERIS_GOP_REG(0, 0x03)
#define GOP_4G_PALDATA_H                        __ERIS_GOP_REG(0, 0x04)
#define GOP_4G_PALCTRL                          __ERIS_GOP_REG(0, 0x05)
#define GOP_4G_REGDMA_END                       __ERIS_GOP_REG(0, 0x06)
#define GOP_4G_REGDMA_STR                       __ERIS_GOP_REG(0, 0x07)
#define GOP_4G_INT                              __ERIS_GOP_REG(0, 0x08)
#define GOP_4G_HWSTATE                          __ERIS_GOP_REG(0, 0x09)
#define GOP_4G_SVM_HSTR                         __ERIS_GOP_REG(0, 0x0a)
#define GOP_4G_SVM_HEND                         __ERIS_GOP_REG(0, 0x0b)
#define GOP_4G_SVM_VSTR                         __ERIS_GOP_REG(0, 0x0c)
#define GOP_4G_SVM_VEND                         __ERIS_GOP_REG(0, 0x0d)
#define GOP_4G_RDMA_HT                          __ERIS_GOP_REG(0, 0x0e)
#define GOP_4G_HS_PIPE                          __ERIS_GOP_REG(0, 0x0f) //new
#define GOP_4G_SLOW                             __ERIS_GOP_REG(0, 0x10) //new
#define GOP_4G_BRI                              __ERIS_GOP_REG(0, 0x11) //new
#define GOP_4G_CON                              __ERIS_GOP_REG(0, 0x12) //new
#define GOP_4G_PRI0                             __ERIS_GOP_REG(0, 0x20)
#define GOP_4G_TRSCLR_L                         __ERIS_GOP_REG(0, 0x24)
#define GOP_4G_TRSCLR_H                         __ERIS_GOP_REG(0, 0x25)
#define GOP_4G_STRCH_HSZ                        __ERIS_GOP_REG(0, 0x30)
#define GOP_4G_STRCH_VSZ                        __ERIS_GOP_REG(0, 0x31)
#define GOP_4G_STRCH_HSTR                       __ERIS_GOP_REG(0, 0x32)
#define GOP_4G_STRCH_VSTR                       __ERIS_GOP_REG(0, 0x34)
#define GOP_4G_HSTRCH                           __ERIS_GOP_REG(0, 0x35)
#define GOP_4G_VSTRCH                           __ERIS_GOP_REG(0, 0x36)
#define GOP_4G_HSTRCH_INI                       __ERIS_GOP_REG(0, 0x38)
#define GOP_4G_VSTRCH_INI                       __ERIS_GOP_REG(0, 0x39)
#define GOP_4G_HVSTRCHMD                        __ERIS_GOP_REG(0, 0x3a)
#define GOP_4G_RBLK0_VOFFL                      __ERIS_GOP_REG(0, 0x60)
#define GOP_4G_RBLK0_VOFFH                      __ERIS_GOP_REG(0, 0x61)
#define GOP_4G_RBLK1_VOFFL                      __ERIS_GOP_REG(0, 0x62)
#define GOP_4G_RBLK1_VOFFH                      __ERIS_GOP_REG(0, 0x63)
#define GOP_4G_RBLK2_VOFFL                      __ERIS_GOP_REG(0, 0x64)
#define GOP_4G_RBLK2_VOFFH                      __ERIS_GOP_REG(0, 0x65)
#define GOP_4G_RBLK3_VOFFL                      __ERIS_GOP_REG(0, 0x66)
#define GOP_4G_RBLK3_VOFFH                      __ERIS_GOP_REG(0, 0x67)
#define GOP_4G_RBLK0_HOFF                       __ERIS_GOP_REG(0, 0x70)
#define GOP_4G_RBLK1_HOFF                       __ERIS_GOP_REG(0, 0x71)
#define GOP_4G_RBLK2_HOFF                       __ERIS_GOP_REG(0, 0x72)
#define GOP_4G_RBLK3_HOFF                       __ERIS_GOP_REG(0, 0x73)
#define GOP_4G_REGDMA_EN                        __ERIS_GOP_REG(0, 0x78)
#define GOP_MUX                                 __GOP_REG(0x7e)
#define GOP_BAK_SEL                             __GOP_REG(0x7f)
#define GOP_OFFSET_WR                           8
#define GOP_VAL_WR                              GOP_REG_VAL(GOP_OFFSET_WR)
#define GOP_OFFSET_FWR                          9
#define GOP_VAL_FWR                             GOP_REG_VAL(GOP_OFFSET_FWR)
#define GOP_OFFSET_FCLR                         11
#define GOP_VAL_FCL                             GOP_REG_VAL(GOP_OFFSET_FCLR)
#define GOP4G_OFFSET_WR_ACK                     12
#define GOP4G_VAL_WR_ACK                        GOP_REG_VAL(GOP4G_OFFSET_WR_ACK)
#define GOP2G_OFFSET_WR_ACK                     13
#define GOP2G_VAL_WR_ACK                        GOP_REG_VAL(GOP2G_OFFSET_WR_ACK)
#define GOPD_OFFSET_WR_ACK                      14
#define GOPD_VAL_WR_ACK                         GOP_REG_VAL(GOPD_OFFSET_WR_ACK)
#define GOP1G_OFFSET_WR_ACK                     15
#define GOP1G_VAL_WR_ACK                        GOP_REG_VAL(GOPD_OFFSET_WR_ACK)
#define GOP_VAL_ACK(x)                          GOP_REG_VAL(GOP4G_OFFSET_WR_ACK+x)

#define GOP_4G_GWIN0_CTRL(id)                   __ERIS_GOP_REG(1, 0x00 + (0x20*((id)%4)))
#define GOP_4G_DRAM_RBLK_L(id)                  __ERIS_GOP_REG(1, 0x01 + (0x20*((id)%4)))
#define GOP_4G_DRAM_RBLK_H(id)                  __ERIS_GOP_REG(1, 0x02 + (0x20*((id)%4)))
#define GOP_4G_HSTR(id)                         __ERIS_GOP_REG(1, 0x04 + (0x20*((id)%4)))
#define GOP_4G_HEND(id)                         __ERIS_GOP_REG(1, 0x05 + (0x20*((id)%4)))
#define GOP_4G_VSTR(id)                         __ERIS_GOP_REG(1, 0x06 + (0x20*((id)%4)))
#define GOP_4G_VEND(id)                         __ERIS_GOP_REG(1, 0x08 + (0x20*((id)%4)))
#define GOP_4G_DRAM_RBLK_HSIZE(id)              __ERIS_GOP_REG(1, 0x09 + (0x20*((id)%4)))
#define GOP_4G_DRAM_VSTR_L(id)                  __ERIS_GOP_REG(1, 0x0C + (0x20*((id)%4)))
#define GOP_4G_DRAM_VSTR_H(id)                  __ERIS_GOP_REG(1, 0x0D + (0x20*((id)%4)))
#define GOP_4G_DRAM_HSTR(id)                    __ERIS_GOP_REG(1, 0x0E + (0x20*((id)%4)))
#define GOP_4G_DRAM_RBLK_SIZE_L(id)             __ERIS_GOP_REG(1, 0x10 + (0x20*((id)%4)))
#define GOP_4G_DRAM_RBLK_SIZE_H(id)             __ERIS_GOP_REG(1, 0x11 + (0x20*((id)%4)))
#define GOP_4G_DRAM_RLEN(id)                    __ERIS_GOP_REG(1, 0x12 + (0x20*((id)%4)))
#define GOP_4G_DRAM_HVSTOP_L(id)                __ERIS_GOP_REG(1, 0x14 + (0x20*((id)%4)))
#define GOP_4G_DRAM_HVSTOP_H(id)                __ERIS_GOP_REG(1, 0x15 + (0x20*((id)%4)))
#define GOP_4G_DRAM_FADE(id)                    __ERIS_GOP_REG(1, 0x16 + (0x20*((id)%4)))
#define GOP_4G_BG_CLR(id)                       __ERIS_GOP_REG(1, 0x18 + (0x20*((id)%4)))
#define GOP_4G_BG_HSTR(id)                      __ERIS_GOP_REG(1, 0x19 + (0x20*((id)%4)))
#define GOP_4G_BG_HEND(id)                      __ERIS_GOP_REG(1, 0x1a + (0x20*((id)%4)))
#define GOP_4G_BG_VSTR(id)                      __ERIS_GOP_REG(1, 0x1C + (0x20*((id)%4)))
#define GOP_4G_BG_VEND(id)                      __ERIS_GOP_REG(1, 0x1D + (0x20*((id)%4)))


#define GOP_2G_CTRL0                            __ERIS_GOP_REG(3, 0x00)
#define GOP_2G_CTRL1                            __ERIS_GOP_REG(3, 0x01)
#define GOP_2G_RATE                             __ERIS_GOP_REG(3, 0x02)
#define GOP_2G_PALDATA_L                        __ERIS_GOP_REG(3, 0x03)
#define GOP_2G_PALDATA_H                        __ERIS_GOP_REG(3, 0x04)
#define GOP_2G_PALCTRL                          __ERIS_GOP_REG(3, 0x05)
#define GOP_2G_REGDMA_END                       __ERIS_GOP_REG(3, 0x06)
#define GOP_2G_REGDMA_STR                       __ERIS_GOP_REG(3, 0x07)
#define GOP_2G_INT                              __ERIS_GOP_REG(3, 0x08)
#define GOP_2G_HWSTATE                          __ERIS_GOP_REG(3, 0x09)
//#define GOP_2G_SVM_HSTR                       __ERIS_GOP_REG(3, 0x0a)
//#define GOP_2G_SVM_HEND                       __ERIS_GOP_REG(3, 0x0b)
//#define GOP_2G_SVM_VSTR                       __ERIS_GOP_REG(3, 0x0c)
//#define GOP_2G_SVM_VEND                       __ERIS_GOP_REG(3, 0x0d)
#define GOP_2G_RDMA_HT                          __ERIS_GOP_REG(3, 0x0e)
#define GOP_2G_HS_PIPE                          __ERIS_GOP_REG(3, 0x0f) //new
#define GOP_2G_SLOW                             __ERIS_GOP_REG(3, 0x10) //new
#define GOP_2G_BRI                              __ERIS_GOP_REG(3, 0x11) //new
#define GOP_2G_CON                              __ERIS_GOP_REG(3, 0x12) //new
#define GOP_2G_PRI0                             __ERIS_GOP_REG(3, 0x20) //new
#define GOP_2G_TRSCLR_L                         __ERIS_GOP_REG(3, 0x24) //new
#define GOP_2G_TRSCLR_H                         __ERIS_GOP_REG(3, 0x25) //new
#define GOP_2G_STRCH_HSZ                        __ERIS_GOP_REG(3, 0x30)
#define GOP_2G_STRCH_VSZ                        __ERIS_GOP_REG(3, 0x31)
#define GOP_2G_STRCH_HSTR                       __ERIS_GOP_REG(3, 0x32)
#define GOP_2G_STRCH_VSTR                       __ERIS_GOP_REG(3, 0x34)
#define GOP_2G_HSTRCH                           __ERIS_GOP_REG(3, 0x35)
#define GOP_2G_VSTRCH                           __ERIS_GOP_REG(3, 0x36)
#define GOP_2G_HSTRCH_INI                       __ERIS_GOP_REG(3, 0x38)
#define GOP_2G_VSTRCH_INI                       __ERIS_GOP_REG(3, 0x39)
#define GOP_2G_HVStrch_MD                       __ERIS_GOP_REG(3, 0x3a)
//#define GOP_2G_RBLK0_VOFFL                    __ERIS_GOP_REG(3, 0x60)
//#define GOP_2G_RBLK0_VOFFH                    __ERIS_GOP_REG(3, 0x61)
//#define GOP_2G_RBLK1_VOFFL                    __ERIS_GOP_REG(3, 0x62)
//#define GOP_2G_RBLK1_VOFFH                    __ERIS_GOP_REG(3, 0x63)
//#define GOP_2G_RBLK2_VOFFL                    __ERIS_GOP_REG(3, 0x64)
//#define GOP_2G_RBLK2_VOFFH                    __ERIS_GOP_REG(3, 0x65)
//#define GOP_2G_RBLK3_VOFFL                    __ERIS_GOP_REG(3, 0x66)
//#define GOP_2G_RBLK3_VOFFH                    __ERIS_GOP_REG(3, 0x67)
//#define GOP_2G_RBLK0_HOFF                     __ERIS_GOP_REG(3, 0x70)
//#define GOP_2G_RBLK1_HOFF                     __ERIS_GOP_REG(3, 0x71)
//#define GOP_2G_RBLK2_HOFF                     __ERIS_GOP_REG(3, 0x72)
//#define GOP_2G_RBLK3_HOFF                     __ERIS_GOP_REG(3, 0x73)
#define GOP_2G_REGDMA_EN                        __ERIS_GOP_REG(3, 0x78)


#define GOP_2G_GWIN0_CTRL(id)                   __ERIS_GOP_REG(4, 0x00 + (0x20*((id)%2)))
#define GOP_2G_GWIN_CTRL(id)                    __ERIS_GOP_REG(4, 0x00 + (0x20*((id)%2)))
#define GOP_2G_DRAM_RBLK_L(id)                  __ERIS_GOP_REG(4, 0x01 + (0x20*((id)%2)))
#define GOP_2G_DRAM_RBLK_H(id)                  __ERIS_GOP_REG(4, 0x02 + (0x20*((id)%2)))
#define GOP_2G_HSTR(id)                         __ERIS_GOP_REG(4, 0x04 + (0x20*((id)%2)))
#define GOP_2G_HEND(id)                         __ERIS_GOP_REG(4, 0x05 + (0x20*((id)%2)))
#define GOP_2G_VSTR(id)                         __ERIS_GOP_REG(4, 0x06 + (0x20*((id)%2)))
#define GOP_2G_VEND(id)                         __ERIS_GOP_REG(4, 0x08 + (0x20*((id)%2)))
#define GOP_2G_DRAM_RBLK_HSIZE(id)              __ERIS_GOP_REG(4, 0x09 + (0x20*((id)%2)))
//#define GOP_2G_DRAM_VSTR_L(id)                __ERIS_GOP_REG(4, 0x0c + (0x20*((id)%2)))
//#define GOP_2G_DRAM_VSTR_H(id)                __ERIS_GOP_REG(4, 0x0d + (0x20*((id)%2)))
//#define GOP_2G_DRAM_HSTR(id)                  __ERIS_GOP_REG(4, 0x0E + (0x20*((id)%2)))
//#define GOP_2G_DRAM_RBLK_SIZE_L(id)           __ERIS_GOP_REG(4, 0x10 + (0x20*((id)%2)))
//#define GOP_2G_DRAM_RBLK_SIZE_H(id)           __ERIS_GOP_REG(4, 0x11 + (0x20*((id)%2)))
//#define GOP_2G_DRAM_RLEN(id)                  __ERIS_GOP_REG(4, 0x12 + (0x20*((id)%2)))
//#define GOP_2G_DRAM_HVSTOP_L(id)              __ERIS_GOP_REG(4, 0x14 + (0x20*((id)%2)))
//#define GOP_2G_DRAM_HVSTOP_H(id)              __ERIS_GOP_REG(4, 0x15 + (0x20*((id)%2)))
#define GOP_2G_DRAM_FADE(id)                    __ERIS_GOP_REG(4, 0x16 + (0x20*((id)%2)))
//#define GOP_2G_BG_CLR(id)                     __ERIS_GOP_REG(4, 0x18 + (0x20*((id)%2)))
//#define GOP_2G_BG_HSTR(id)                    __ERIS_GOP_REG(4, 0x19 + (0x20*((id)%2)))
//#define GOP_2G_BG_HEND(id)                    __ERIS_GOP_REG(4, 0x1a + (0x20*((id)%2)))
//#define GOP_2G_BG_VSTR(id)                    __ERIS_GOP_REG(4, 0x1c + (0x20*((id)%2)))
//#define GOP_2G_BG_VEND(id)                    __ERIS_GOP_REG(4, 0x1d + (0x20*((id)%2)))

// DWIN reg
#define GOP_DW_CTL0_EN                          __ERIS_GOP_REG(6, 0x00)
#define GOP_DWIN_EN                             (0x00)
#define GOP_DWIN_EN_VAL                         GOP_REG_VAL(GOP_DWIN_EN)
#define GOP_DWIN_SHOT                           (0x07)
#define GOP_DWIN_SHOT_VAL                       GOP_REG_VAL(GOP_DWIN_SHOT)

#define GOP_DW_LSTR_WBE                         __ERIS_GOP_REG(6, 0x01)
#define GOP_DW_INT_MASK                         __ERIS_GOP_REG(6, 0x02)
#define GOP_DW_DEBUG                            __ERIS_GOP_REG(6, 0x03)
#define GOP_DW_ALPHA                            __ERIS_GOP_REG(6, 0x04)

#define GOP_DW_VSTR                             __ERIS_GOP_REG(6, 0x10)
#define GOP_DW_HSTR                             __ERIS_GOP_REG(6, 0x11)
#define GOP_DW_VEND                             __ERIS_GOP_REG(6, 0x12)
#define GOP_DW_HEND                             __ERIS_GOP_REG(6, 0x13)
#define GOP_DW_HSIZE                            __ERIS_GOP_REG(6, 0x14)
#define GOP_DW_JMPLEN                           __ERIS_GOP_REG(6, 0x15)
#define GOP_DW_DSTR_L                           __ERIS_GOP_REG(6, 0x16)
#define GOP_DW_DSTR_H                           __ERIS_GOP_REG(6, 0x17)
#define GOP_DW_UB_L                             __ERIS_GOP_REG(6, 0x18)
#define GOP_DW_UB_H                             __ERIS_GOP_REG(6, 0x19)

#define GOP_DW_PON_DSTR_L                       __ERIS_GOP_REG(6, 0x1a)
#define GOP_DW_PON_DSTR_H                       __ERIS_GOP_REG(6, 0x1b)
#define GOP_DW_PON_UB_L                         __ERIS_GOP_REG(6, 0x1c)
#define GOP_DW_PON_UB_H                         __ERIS_GOP_REG(6, 0x1d)



#define GOP_1G_CTRL0                            __ERIS_GOP_REG(7, 0x00)
#define GOP_1G_CTRL1                            __ERIS_GOP_REG(7, 0x01)
//#define GOP_1G_RATE                           __ERIS_GOP_REG(7, 0x02)
//#define GOP_1G_PALDATA_L                      __ERIS_GOP_REG(7, 0x03)
//#define GOP_1G_PALDATA_H                      __ERIS_GOP_REG(7, 0x04)
//#define GOP_1G_PALCTRL                        __ERIS_GOP_REG(7, 0x05)
//#define GOP_1G_REGDMA_END                     __ERIS_GOP_REG(7, 0x06)
//#define GOP_1G_REGDMA_STR                     __ERIS_GOP_REG(7, 0x07)
#define GOP_1G_INT                              __ERIS_GOP_REG(7, 0x08)
#define GOP_1G_HWSTATE                          __ERIS_GOP_REG(7, 0x09)
//#define GOP_1G_SVM_HSTR                       __ERIS_GOP_REG(7, 0x0a)
//#define GOP_1G_SVM_HEND                       __ERIS_GOP_REG(7, 0x0b)
//#define GOP_1G_SVM_VSTR                       __ERIS_GOP_REG(7, 0x0c)
//#define GOP_1G_SVM_VEND                       __ERIS_GOP_REG(7, 0x0d)
#define GOP_1G_RDMA_HT                          __ERIS_GOP_REG(7, 0x0e)
#define GOP_1G_HS_PIPE                          __ERIS_GOP_REG(7, 0x0f) //new
//#define GOP_1G_SLOW                           __ERIS_GOP_REG(7, 0x10) //new
#define GOP_1G_BRI                              __ERIS_GOP_REG(7, 0x11) //new
#define GOP_1G_CON                              __ERIS_GOP_REG(7, 0x12) //new
//#define GOP_1G_PRI0                           __ERIS_GOP_REG(7, 0x20)
#define GOP_1G_TRSCLR_L                         __ERIS_GOP_REG(7, 0x24)
#define GOP_1G_TRSCLR_H                         __ERIS_GOP_REG(7, 0x25)
#define GOP_1G_STRCH_HSZ                        __ERIS_GOP_REG(7, 0x30)
#define GOP_1G_STRCH_VSZ                        __ERIS_GOP_REG(7, 0x31)
#define GOP_1G_STRCH_HSTR                       __ERIS_GOP_REG(7, 0x32)
#define GOP_1G_STRCH_VSTR                       __ERIS_GOP_REG(7, 0x34)
#define GOP_1G_HSTRCH                           __ERIS_GOP_REG(7, 0x35)
//#define GOP_1G_VSTRCH                         __ERIS_GOP_REG(7, 0x36)
#define GOP_1G_HSTRCH_INI                       __ERIS_GOP_REG(7, 0x38)


#define GOP_1G_GWIN0_CTRL(id)                   __ERIS_GOP_REG(7, 0x40)// 1+((id)/4), 0x00+(0x20*((id)%4)))
#define GOP_1G_DRAM_RBLK_L(id)                  __ERIS_GOP_REG(7, 0x41)// 1+((id)/4), 0x01+(0x20*((id)%4)))
#define GOP_1G_DRAM_RBLK_H(id)                  __ERIS_GOP_REG(7, 0x42)// 1+((id)/4), 0x02+(0x20*((id)%4)))
#define GOP_1G_HSTR(id)                         __ERIS_GOP_REG(7, 0x44)// 1+((id)/4), 0x04+(0x20*((id)%4)))
#define GOP_1G_HEND(id)                         __ERIS_GOP_REG(7, 0x45)// 1+((id)/4), 0x05+(0x20*((id)%4)))
#define GOP_1G_VSTR(id)                         __ERIS_GOP_REG(7, 0x46)// 1+((id)/4), 0x06+(0x20*((id)%4)))
#define GOP_1G_VEND(id)                         __ERIS_GOP_REG(7, 0x48// 1+((id)/4), 0x08+(0x20*((id)%4)))
#define GOP_1G_DRAM_RBLK_HSIZE(id)              __ERIS_GOP_REG(7, 0x49)// 1+((id)/4), 0x09+(0x20*((id)%4)))
#define GOP_1G_DRAM_FADE(id)                    __ERIS_GOP_REG(7, 0x56// 1+((id)/4), 0x16+(0x20*((id)%4)))

//----------------------------------------------------------------------------
// 13. GE Reg (GE core use 16-bit registers)
//----------------------------------------------------------------------------
#define __GE_REG(reg)                           ((reg) * 2)
#define PE_REG_EN                               __GE_REG(0x00)  //==0x0000
#define PE_REG_EN1                              __GE_REG(0x01)
#define PE_REG_STATUS                           __GE_REG(0x07)
#define PE_REG_ABL_COEF                         __GE_REG(0x11)
#define PE_REG_DB_ABL                           __GE_REG(0x12)
#define PE_REG_ABL_CONST                        __GE_REG(0x13)
#define PE_REG_SCK_HTH0                         __GE_REG(0x14)
#define PE_REG_SCK_HTH1                         __GE_REG(0x15)
#define PE_REG_SCK_LTH0                         __GE_REG(0x16)
#define PE_REG_SCK_LTH1                         __GE_REG(0x17)
#define PE_REG_DCK_HTH0                         __GE_REG(0x18)
#define PE_REG_DCK_HTH1                         __GE_REG(0x19)
#define PE_REG_DCK_LTH0                         __GE_REG(0x1A)
#define PE_REG_DCK_LTH1                         __GE_REG(0x1B)
#define PE_REG_KEY_OP                           __GE_REG(0x1C)
#define PE_REG_SB_BASE0                         __GE_REG(0x20)
#define PE_REG_SB_BASE1                         __GE_REG(0x21)
#define PE_REG_DB_BASE0                         __GE_REG(0x26)
#define PE_REG_DB_BASE1                         __GE_REG(0x27)
#define PE_REG_DB_PIT                           __GE_REG(0x33)
#define PE_REG_FM                               __GE_REG(0x34)
#define PE_REG_CMD                              __GE_REG(0x60)

// GE_REG_EN
#define REG_EN_PE                               0x0001
#define REG_EN_PE_DITHER                        0x0002
#define REG_EN_PE_ABL                           0x0004
#define REG_EN_PE_ROP                           0x0020
#define REG_EN_PE_SCK                           0x0040
#define REG_EN_PE_DCK                           0x0080

// GE_REG_EN1
#define REG_EN_PE_CMQ                           0x0001
#define REG_EN_PE_RPRIORITY                     0x0002
#define REG_EN_PE_WPRIORITY                     0x0004
#define REG_EN_PE_STBB                          0x0010
#define REG_EN_PE_ITC                           0x0040

// GE_REG_STATUS
#define REG_CMD_FIFO_STATUS                     0x0080
#define REG_PE_STATUS                           0x0001
#define REG_BLT_STATUS                          0x0002
#define REG_PE_CMD_RDY_MASK                     (REG_CMD_FIFO_STATUS + REG_PE_STATUS)

// PE_REG_DB_ABL
#define REG_PE_MSK_ABL_COEF                     0x0007

// PE_REG_DB_ABL
#define REG_PE_MSK_DB_ABL_H                     0x03
#define REG_PE_MSK_DB_ABL                       0x0300

// GE_REG_FM
#define REG_PE_SB_FM_I1                         0x0000  // 1 bit Intesity 1
#define REG_PE_SB_FM_I2                         0x0001  // 2 bits, Intesity 2
#define REG_PE_SB_FM_I4                         0x0002  // 4 bits, Intesity 4
#define REG_PE_SB_FM_I8                         0x0004  // 8 bits, Pallette 8
#define REG_PE_SB_FM_RESERVED                   0x0007  // RESERVED
#define REG_PE_SB_FM_RGB565                     0x0008  // 16 bits, RGB565[15:0]
#define REG_PE_SB_FM_ARGB1555                   0x0009  // 16 bits, ARGB1555[15:0]
#define REG_PE_SB_FM_ARGB4444                   0x000A  // 16 bits, ARGB4444[15:0]
#define REG_PE_SB_FM_1BAAFgBg123433             0x000B  // 16 bits, 1BAAFgBg123433[15:0]
#define REG_PE_SB_FM_RGB888                     0x000C  // 24 bits, RGB888[23:0]
#define REG_PE_SB_FM_ARGB6666                   0x000D  // 24 bits, ARGB6666[23:0]
#define REG_PE_SB_FM_Y1V1Y0U0_422               0x000E  // 32 bits, Y1V1Y0U0 Packer 422[31:0]
#define REG_PE_DB_FM_I8                         0x0400  // 8 bits Pallette 8
#define REG_PE_DB_FM_RGB565                     0x0800  // 16 bits, RGB565[15:0]
#define REG_PE_DB_FM_0RGB1555                   0x0900  // 16 bits, 0RGB1555[15:0]
#define REG_PE_DB_FM_ARGB4444                   0x0A00  // 16 bits, ARGB4444[15:0]
#define REG_PE_DB_FM_1BA1A2FgBg123433           0x0B00  // 16 bits, 1BA1A2FgBg123433[15:0
#define REG_PE_DB_FM_ARGB8888                   0x0F00  // 32 bits, ARGB8888[31:0]
#define REG_PE_SB_FM_ARGB8888                   0x0F00  // 32 bits, ARGB8888[31:0]

// GE_REG_KEY_OP
#define REG_BLT_SCK_OP_MASK                     0x0001
#define REG_BLT_DCK_OP_MASK                     0x0002

#define GE_REG_EN0                              __GE_REG(0x00)
#define GE_REG_EN1                              __GE_REG(0x01)
#define GE_REG_DBG                              __GE_REG(0x02)
#define GE_REG_STBB                             __GE_REG(0x03)

#define GE_REG_STATUS                           __GE_REG(0x07)
#define GE_REG_ROP2                             __GE_REG(0x10)

#define GE_REG_ABL_COEF                         __GE_REG(0x11)
#define GE_REG_DB_ABL                           __GE_REG(0x12)
#define GE_REG_ABL_CONST                        __GE_REG(0x13)
#define GE_REG_SCK_HTH0                         __GE_REG(0x14)
#define GE_REG_SCK_HTH1                         __GE_REG(0x15)
#define GE_REG_SCK_LTH0                         __GE_REG(0x16)
#define GE_REG_SCK_LTH1                         __GE_REG(0x17)
#define GE_REG_DCK_HTH0                         __GE_REG(0x18)
#define GE_REG_DCK_HTH1                         __GE_REG(0x19)
#define GE_REG_DCK_LTH0                         __GE_REG(0x1a)
#define GE_REG_DCK_LTH1                         __GE_REG(0x1b)

#define GE_REG_BLT_CK_OP_MODE                   __GE_REG(0x1c)
#define GE_REG_DC_CSC_FM                        __GE_REG(0x1f)
#define GE_REG_SB_BASE0                         __GE_REG(0x20)
#define GE_REG_SB_BASE1                         __GE_REG(0x21)
#define GE_REG_DB_BASE0                         __GE_REG(0x26)
#define GE_REG_DB_BASE1                         __GE_REG(0x27)

#define GE_REG_VCMQ_BASE0                       __GE_REG(0x28)
#define GE_REG_VCMQ_BASE1                       __GE_REG(0x29)
#define GE_REG_VCMQ_SZ                          __GE_REG(0x2a)
#define GE_REG_P256_0                           __GE_REG(0x2d)
#define GE_REG_P256_1                           __GE_REG(0x2e)
#define GE_REG_P256_IDX                         __GE_REG(0x2f)

#define GE_REG_SB_PIT                           __GE_REG(0x30)
#define GE_REG_DB_PIT                           __GE_REG(0x33)
#define GE_REG_B_FM                             __GE_REG(0x34)

#define GE_REG_I0_C0                            __GE_REG(0x35)
#define GE_REG_I0_C1                            __GE_REG(0x36)
#define GE_REG_I1_C0                            __GE_REG(0x37)
#define GE_REG_I1_C1                            __GE_REG(0x38)
#define GE_REG_I2_C0                            __GE_REG(0x39)
#define GE_REG_I2_C1                            __GE_REG(0x3a)
#define GE_REG_I3_C0                            __GE_REG(0x3b)
#define GE_REG_I3_C1                            __GE_REG(0x3c)
#define GE_REG_I4_C0                            __GE_REG(0x3d)
#define GE_REG_I4_C1                            __GE_REG(0x3e)
#define GE_REG_I5_C0                            __GE_REG(0x3f)
#define GE_REG_I5_C1                            __GE_REG(0x40)
#define GE_REG_I6_C0                            __GE_REG(0x41)
#define GE_REG_I6_C1                            __GE_REG(0x42)
#define GE_REG_I7_C0                            __GE_REG(0x43)
#define GE_REG_I7_C1                            __GE_REG(0x44)
#define GE_REG_I8_C0                            __GE_REG(0x45)
#define GE_REG_I8_C1                            __GE_REG(0x46)
#define GE_REG_I9_C0                            __GE_REG(0x47)
#define GE_REG_I9_C1                            __GE_REG(0x48)
#define GE_REG_I10_C0                           __GE_REG(0x49)
#define GE_REG_I10_C1                           __GE_REG(0x4a)
#define GE_REG_I11_C0                           __GE_REG(0x4b)
#define GE_REG_I11_C1                           __GE_REG(0x4c)
#define GE_REG_I12_C0                           __GE_REG(0x4d)
#define GE_REG_I12_C1                           __GE_REG(0x4e)
#define GE_REG_I13_C0                           __GE_REG(0x4f)
#define GE_REG_I13_C1                           __GE_REG(0x50)
#define GE_REG_I14_C0                           __GE_REG(0x51)
#define GE_REG_I14_C1                           __GE_REG(0x52)
#define GE_REG_I15_C0                           __GE_REG(0x53)
#define GE_REG_I15_C1                           __GE_REG(0x54)

#define GE_REG_CLIP_LEFT                        __GE_REG(0x55)
#define GE_REG_CLIP_RIGHT                       __GE_REG(0x56)
#define GE_REG_CLIP_TOP                         __GE_REG(0x57)
#define GE_REG_CLIP_BOTTOM                      __GE_REG(0x58)

#define GE_REG_ROT                              __GE_REG(0x59)

#define GE_REG_STBB_SCK_TYPE                    __GE_REG(0x5b)
#define GE_REG_STBB_SCK_BG                      __GE_REG(0x5c)
#define GE_REG_STBB_SCK_AR                      __GE_REG(0x5d)

#define GE_REG_STBB_INI_DX                      __GE_REG(0x5e)
#define GE_REG_STBB_INI_DY                      __GE_REG(0x5f)
#define GE_REG_CMD                              __GE_REG(0x60)
#define GE_REG_LINE                             __GE_REG(0x61)
#define GE_REG_LPT                              __GE_REG(0x62)
#define GE_REG_LINE_LEN                         __GE_REG(0x63)
#define GE_REG_STBB_DX                          __GE_REG(0x64)
#define GE_REG_STBB_DY                          __GE_REG(0x65)
#define GE_REG_ITC0                             __GE_REG(0x66)
#define GE_REG_ITC1                             __GE_REG(0x67)
#define GE_REG_PRI_V0_X                         __GE_REG(0x68)
#define GE_REG_PRI_V0_Y                         __GE_REG(0x69)
#define GE_REG_PRI_V1_X                         __GE_REG(0x6a)
#define GE_REG_PRI_V1_Y                         __GE_REG(0x6b)
#define GE_REG_PRI_V2_X                         __GE_REG(0x6c)
#define GE_REG_PRI_V2_Y                         __GE_REG(0x6d)
#define GE_REG_STBB_S_W                         __GE_REG(0x6e)
#define GE_REG_STBB_S_H                         __GE_REG(0x6f)

#define GE_REG_PRI_GB_ST                        __GE_REG(0x70)
#define GE_REG_PRI_AR_ST                        __GE_REG(0x71)

#define GE_REG_PRI_R_DX0                        __GE_REG(0x72)
#define GE_REG_PRI_R_DX1                        __GE_REG(0x73)
#define GE_REG_PRI_R_DY0                        __GE_REG(0x74)
#define GE_REG_PRI_R_DY1                        __GE_REG(0x75)
#define GE_REG_PRI_G_DX0                        __GE_REG(0x76)
#define GE_REG_PRI_G_DX1                        __GE_REG(0x77)
#define GE_REG_PRI_G_DY0                        __GE_REG(0x78)
#define GE_REG_PRI_G_DY1                        __GE_REG(0x79)
#define GE_REG_PRI_B_DX0                        __GE_REG(0x7a)
#define GE_REG_PRI_B_DX1                        __GE_REG(0x7b)
#define GE_REG_PRI_B_DY0                        __GE_REG(0x7c)
#define GE_REG_PRI_B_DY1                        __GE_REG(0x7d)
#define GE_REG_PRI_A_DX0                        __GE_REG(0x7e)
#define GE_REG_PRI_A_DY0                        __GE_REG(0x7f)

#define PE_VAL_EN_CMDQ                          (1 << 0)
#define PE_VAL_EN_VCMDQ                         (1 << 1)
#define PE_VAL_EN_Read_Prio                    (1 << 2)
#define PE_VAL_EN_Write_Prio                    (1 << 3)
#define PE_VAL_EN_STRETCH_BITBLT                (1 << 4)
#define PE_VAL_EN_ITALIC_FONT                   (1 << 6)

//#define PE_REG_EN                             0x00
#define PE_VAL_EN_PE                            (1 << 0)
#define PE_VAL_EN_DITHER                        (1 << 1)
#define PE_VAL_EN_GY_ABL                        (1 << 2)
#define PE_VAL_EN_ROP                           (1 << 5)
#define PE_VAL_EN_SCK                           (1 << 6)
#define PE_VAL_EN_DCK                           (1 << 7)
#define PE_VAL_EN_LPT                           (1 << 8)

#define PE_MSK_PRIM_TYPE                        (0xF << 4)
#define PE_VAL_PRIM_LINE                        (0x1 << 4)
#define PE_VAL_PRIM_RECTANGLE                   (0x3 << 4)
#define PE_VAL_PRIM_BITBLT                      (0x4 << 4)
#define PE_MSK_CLEAR_FLAG                       (0x1FF << 7)
#define PE_VAL_DRAW_SRC_DIR_X_NEG               (1 << 7)
#define PE_VAL_DRAW_SRC_DIR_Y_NEG               (1 << 8)
#define PE_VAL_DRAW_DST_DIR_X_NEG               (1 << 9)
#define PE_VAL_DRAW_DST_DIR_Y_NEG               (1 << 10)
#define PE_VAL_LINE_GRADIENT                    (1 << 11)
#define PE_VAL_RECT_GRADIENT_H                  (1 << 12)
#define PE_VAL_RECT_GRADIENT_V                  (1 << 13)
#define PE_VAL_STBB_NEAREST                     (1 << 14)
#define PE_VAL_STBB_PATCH                       (1 << 15)

#define PE_MSK_LP                               0x3F
#define PE_MSK_LPT_FACTOR                       (0x3<<6)
#define PE_VAL_LPT_F1                           (0<<6)
#define PE_VAL_LPT_F2                           (1<<6)
#define PE_VAL_LPT_F3                           (2<<6)
#define PE_VAL_LPT_F4                           (3<<6)
#define PE_VAL_LPT_RESET                        (1<<8)
#define PE_VAL_LINE_LAST                        (1<<9)

//------------------------------------------------------------------------------
// CACHE : Base 0x2B80
//------------------------------------------------------------------------------
#define REG_CACHE_BYPASS                        0x2BA0

    #define CACHE_BYPASS_EN                         0x01

//----------------------------------------------------------------------------
// Bank9 - DSP
//----------------------------------------------------------------------------
#define DSP_DSPCTRLPORT                         0x80
#define DSP_DSPBRGDATA                          0x81
#define DSP_IDMAOVALAPH                         0x82
#define DSP_IDMAOVALAPL                         0x83
#define DSP_IDMABASEADDRH                       0x84
#define DSP_IDMABASEADDRL                       0x85
#define DSP_IDMATRSIZEH                         0x86
#define DSP_IDMATRSIZEL                         0x87
#define DSP_CH2_IDMABASEADDRH                   0x88
#define DSP_CH2_IDMABASEADDRL                   0x89
#define DSP_CH2_IDMATRSIZEH                     0x8A
#define DSP_CH2_IDMATRSIZEL                     0x8B
#define DSP_RDDATAH                             0x8C
#define DSP_RDDATAL                             0x8D
#define DSP_RDBASEADDRH                         0x8E
#define DSP_RDBASEADDRL                         0x8F

#define DSP_AUD_CTRL                            0xF0
#define DSP_STR_TYPE                            0xF1
#define DSP_MAD_BASE                            0xF2
#define DSP_ES_MBASE_H                          0xF3
#define DSP_ES_MEND_H                           0xF4
#define DSP_PCM_MBASE_H                         0xF5
#define DSP_PCM_MEND_H                          0xF6
#define DSP_P_AUD_MODE                          0xF7

/*****************************************************************************/
//MCU reg
/*****************************************************************************/
#define REG_CSZ_SPI_FLASH                       (RIUBASE_REG_PIU_MISC_0 + 0x1c )  //0x003c1c


#define GPIO_BASE_ADDRESS                       0x1048
#define GPIO_P0_CTRL                            0x1048
#define GPIO_P0_OE                              0x1049
#define GPIO_P0_IN                              0x104A
#define GPIO_P1_CTRL                            0x104B
#define GPIO_P1_OE                              0x104C
#define GPIO_P1_IN                              0x104D
#define GPIO_P2_CTRL                            0x104E
#define GPIO_P2_OE                              0x104F
#define GPIO_P2_IN                              0x1050
#define GPIO_P3_CTRL                            0x1051
#define GPIO_P3_OE                              0x1052
#define GPIO_P3_IN                              0x1053
#define GPIO_P4_CTRL                            0x1054
#define GPIO_P4_OE                              0x1055
#define GPIO_P4_IN                              0x1056
    #define _OFF                                0
    #define _ON                                 1
    #define _HIGH                               1
    #define _LOW                                0
    #define _OUTPUT                             0
    #define _INPUT                              1

//----------------------------------------------------------------------------
// XDMIU Reg :: 0x2BC0
//----------------------------------------------------------------------------
#define XDMIU_RESET                             0x2BC0
    #define XDMIU_SW_RESET                      0x01

#define XDMIU_MISC                              0x2BC4
    #define XDMIU_R_PRI                         0x01
    #define XDMIU_W_PRI                         0x02
    #define XDMIU_MEM_MAP_EN                    0x04

#define XDMIU_MCUXD_W0_S1K                      0x2BC6
#define XDMIU_MCUXD_W0_E1K                      0x2BC7
#define XDMIU_MEMMAP_W0_64K                     0x2BC8
#define XDMIU_MEMMAP_W0_64K_1                   0x2BC9
#define XDMIU_MCUXD_W1_S1K                      0x2BCA
#define XDMIU_MCUXD_W1_E2K                      0x2BCB
#define XDMIU_MEMMAP_W1_4K                      0x2BCC
#define XDMIU_MEMMAP_W1_4K_1                    0x2BCD

//------------------------------------------------------------------------------
// Mail Box Reg
//------------------------------------------------------------------------------
#define REG_51_MB_CMD_BASE                      MAILBOX_REG_BASE
#define REG_AEON_MB_CMD_BASE                    (MAILBOX_REG_BASE + 0x10)

#define MB_51_REG_CTRL_REG                      0x3380
#define MB_51_REG_CMD_CLASS                     0x3381
#define MB_51_REG_CMD_IDX                       0x3382
#define MB_51_REG_PARAM_CNT                     0x3383
#define MB_51_REG_PARAM_00                      0x3384
#define MB_51_REG_PARAM_01                      0x3385
#define MB_51_REG_PARAM_02                      0x3386
#define MB_51_REG_PARAM_03                      0x3387
#define MB_51_REG_PARAM_04                      0x3388
#define MB_51_REG_PARAM_05                      0x3389
#define MB_51_REG_PARAM_06                      0x338A
#define MB_51_REG_PARAM_07                      0x338B
#define MB_51_REG_PARAM_08                      0x338C
#define MB_51_REG_PARAM_09                      0x338D
#define MB_51_REG_Status_0                      0x338E
#define MB_51_REG_Status_1                      0x338F

#define MB_AEON_REG_CTRL_REG                    0x3390
#define MB_AEON_REG_CMD_CLASS                   0x3391
#define MB_AEON_REG_CMD_IDX                     0x3392
#define MB_AEON_REG_PARAM_CNT                   0x3393
#define MB_AEON_REG_PARAM_00                    0x3394
#define MB_AEON_REG_PARAM_01                    0x3395
#define MB_AEON_REG_PARAM_02                    0x3396
#define MB_AEON_REG_PARAM_03                    0x3397
#define MB_AEON_REG_PARAM_04                    0x3398
#define MB_AEON_REG_PARAM_05                    0x3399
#define MB_AEON_REG_PARAM_06                    0x339A
#define MB_AEON_REG_PARAM_07                    0x339B
#define MB_AEON_REG_PARAM_08                    0x339C
#define MB_AEON_REG_PARAM_09                    0x339D
#define MB_AEON_REG_Status_0                    0x339E
#define MB_AEON_REG_Status_1                    0x339F

// AEON Index
#define MB_AEON_IDX_HK51_STATUS                 0x80
#define MB_AEON_IDX_PANEL_INFO                  0x81
#define MB_AEON_IDX_QUERY_SYSINFO               0x82
#define MB_AEON_IDX_AEON_HEARTBEAT              0x83

//------------------------------------------------------------------------------
// DDC Reg
//------------------------------------------------------------------------------
//DDC2BI for ADC
#define DDC2BI_ADC_ID                           0x040A
#define DDC2BI_ADC_INT_MASK                     0x0414
#define DDC2BI_ADC_INT_FLAG                     0x0410
#define DDC2BI_ADC_INT_CLR                      0x041C
#define DDC2BI_ADC_WB_RP                        0x0400
#define DDC2BI_ADC_RB_WP                        0x0401

//DDC2BI for DVI0
#define DDC2BI_DVI0_ID                          0x040C
#define DDC2BI_DVI0_INT_MASK                    0x0416
#define DDC2BI_DVI0_INT_FLAG                    0x0412
#define DDC2BI_DVI0_INT_CLR                     0x041E
#define DDC2BI_DVI0_WB_RP                       0x0404
#define DDC2BI_DVI0_RB_WP                       0x0405

//DDC2BI for DVI1
#define DDC2BI_DVI1_ID                          0x040D
#define DDC2BI_DVI1_INT_MASK                    0x0417
#define DDC2BI_DVI1_INT_FLAG                    0x0413
#define DDC2BI_DVI1_INT_CLR                     0x041F
#define DDC2BI_DVI1_WB_RP                       0x0406
#define DDC2BI_DVI1_RB_WP                       0x0407

//DDC2BI for DVI2
#define DDC2BI_DVI2_ID                          0x0452
#define DDC2BI_DVI2_INT_MASK                    0x0455
#define DDC2BI_DVI2_INT_FLAG                    0x0454
#define DDC2BI_DVI2_INT_CLR                     0x0457
#define DDC2BI_DVI2_WB_RP                       0x0450
#define DDC2BI_DVI2_RB_WP                       0x0451

#define DDC2BI_DVI_INT_FLAG                     0x0412
#define DDC2BI_DVI_INT_CLR                      0x041E
#define DDC2BI_DVI_WB_RP                        0x0404
#define DDC2BI_DVI_RB_WP                        0x0405
#define DDC2BI_CTRL                             0x0409

#endif // _HWREG_EIFFEL_H

