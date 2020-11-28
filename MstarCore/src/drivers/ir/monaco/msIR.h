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

#ifndef MS_IR_H
#define MS_IR_H

//------------------------------------------------------------------------------
// IR register define
//------------------------------------------------------------------------------
#define    RIUBASE_IR                           0x003d00    //0x003d00 ~ 0x003dff

#define IR_CTRL                                 ( RIUBASE_IR + 0x80 )  //0x3D80
#define IR_CHECK                                ( RIUBASE_IR + 0x81 )  //0x3D81
#define IR_HDC_UPB_L                            ( RIUBASE_IR + 0x82 )  //0x3D82
#define IR_HDC_UPB_H                            ( RIUBASE_IR + 0x83 )  //0x3D83
#define IR_HDC_LOB_L                            ( RIUBASE_IR + 0x84 )  //0x3D84
#define IR_HDC_LOB_H                            ( RIUBASE_IR + 0x85 )  //0x3D85
#define IR_OFC_UPB_L                            ( RIUBASE_IR + 0x86 )  //0x3D86
#define IR_OFC_UPB_H                            ( RIUBASE_IR + 0x87 )  //0x3D87
#define IR_OFC_LOB_L                            ( RIUBASE_IR + 0x88 )  //0x3D88
#define IR_OFC_LOB_H                            ( RIUBASE_IR + 0x89 )  //0x3D89
#define IR_OFC_RP_UPB_L                         ( RIUBASE_IR + 0x8A )  //0x3D8A
#define IR_OFC_RP_UPB_H                         ( RIUBASE_IR + 0x8B )  //0x3D8B
#define IR_OFC_RP_LOB_L                         ( RIUBASE_IR + 0x8C )  //0x3D8C
#define IR_OFC_RP_LOB_H                         ( RIUBASE_IR + 0x8D )  //0x3D8D
#define IR_LG01H_UPB_L                          ( RIUBASE_IR + 0x8E )  //0x3D8E
#define IR_LG01H_UPB_H                          ( RIUBASE_IR + 0x8F )  //0x3D8F
#define IR_LG01H_LOB_L                          ( RIUBASE_IR + 0x90 )  //0x3D90
#define IR_LG01H_LOB_H                          ( RIUBASE_IR + 0x91 )  //0x3D91
#define IR_LG0_UPB_L                            ( RIUBASE_IR + 0x92 )  //0x3D92
#define IR_LG0_UPB_H                            ( RIUBASE_IR + 0x93 )  //0x3D93
#define IR_LG0_LOB_L                            ( RIUBASE_IR + 0x94 )  //0x3D94
#define IR_LG0_LOB_H                            ( RIUBASE_IR + 0x95 )  //0x3D95
#define IR_LG1_UPB_L                            ( RIUBASE_IR + 0x96 )  //0x3D96
#define IR_LG1_UPB_H                            ( RIUBASE_IR + 0x97 )  //0x3D97
#define IR_LG1_LOB_L                            ( RIUBASE_IR + 0x98 )  //0x3D98
#define IR_LG1_LOB_H                            ( RIUBASE_IR + 0x99 )  //0x3D99
#define IR_SEPR_UPB_L                           ( RIUBASE_IR + 0x9A )  //0x3D9A
#define IR_SEPR_UPB_H                           ( RIUBASE_IR + 0x9B )  //0x3D9B
#define IR_SEPR_LOB_L                           ( RIUBASE_IR + 0x9C )  //0x3D9C
#define IR_SEPR_LOB_H                           ( RIUBASE_IR + 0x9D )  //0x3D9D
#define IR_TIMEOUT_CYC_0                        ( RIUBASE_IR + 0x9E )  //0x3D9E
#define IR_TIMEOUT_CYC_1                        ( RIUBASE_IR + 0x9F )  //0x3D9F
#define IR_TIMEOUT_CYC_2                        ( RIUBASE_IR + 0xA0 )  //0x3DA0
#define IR_CODEBYTE                             ( RIUBASE_IR + 0xA1 )  //0x3DA1
#define IR_SEPR_BIT                             ( RIUBASE_IR + 0xA2 )  //0x3DA2
#define IR_FIFO_CTRL                            ( RIUBASE_IR + 0xA3 )  //0x3DA3  // different location with Saturn
#define IR_CCODE_L                              ( RIUBASE_IR + 0xA4 )  //0x3DA4
#define IR_CCODE_H                              ( RIUBASE_IR + 0xA5 )  //0x3DA5
#define IR_GLHRM_NUM_L                          ( RIUBASE_IR + 0xA6 )  //0x3DA6
#define IR_GLHRM_NUM_H                          ( RIUBASE_IR + 0xA7 )  //0x3DA7
#define IR_CKDIV_NUM_REG                        ( RIUBASE_IR + 0xA8 )  //0x3DA8  // different location with Saturn
#define IR_KEY                                  ( RIUBASE_IR + 0xA9 )  //0x3DA9
#define IR_SHOT_CNT_0                           ( RIUBASE_IR + 0xAA )  //0x3DAA
#define IR_SHOT_CNT_1                           ( RIUBASE_IR + 0xAB )  //0x3DAB
#define IR_SHOT_CNT_2                           ( RIUBASE_IR + 0xAC )  //0x3DAC
#define IR_RPT_FIFOEMPTY                        ( RIUBASE_IR + 0xAD )  //0x3DAD
#define IR_FIFO_READ_PULSE                      ( RIUBASE_IR + 0xB0 )  //0x3DB0  // added in Saturn2

#define IR_TYPE_FULLDECODE_MODE 1
#define IR_TYPE_RAWDATA_MODE    2
#define IR_TYPE_SWDECODE_MODE   3
#define IR_TYPE_SWDECODE_KON_MODE 4
#define IR_TYPE_SWDECODE_RC5HAI_MODE 5
#define IR_TYPE_SWDECODE_SHA_MODE 6
#define IR_TYPE_SWDECODE_MALATA_MODE 7
#define IR_TYPE_SWDECODE_RC5_MODE        8
#define IR_TYPE_TOSHIBA_MODE 9
#define IR_TYPE_SWDECODE_HSS_MODE 10
#define IR_TYPE_SWDECODE_TOSHIBA_MODE 11
#define IR_TYPE_HWDECODE_RC 12
#define IR_TYPE_SWDECODE_RCA_MODE 13
#define IR_TYPE_SWDECODE_SKY_MODE 14

#if(IR_TYPE_SEL==IR_TYPE_CUS08_VL) //MB100_BRINGUP
#include <IR_CUS08_VL.h>
#else
#include <IR_MSTAR_DTV.h>
#endif

#ifndef IR_MODE_SEL
#define IR_MODE_SEL             IR_TYPE_FULLDECODE_MODE
#endif

#if 0//(IR_TYPE_SEL==IR_TYPE_DC_BN59_611 || IR_TYPE_SEL==IR_TYPE_DC_BN59)
#define IR_FILTER_REPEAT_NUM    5
#else
#define IR_FILTER_REPEAT_NUM    4
#endif

#ifdef  MS_IR_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void msIR_Clear_FIFO(void);
INTERFACE U8   msIR_ReadByte( U16 u16RegIndex );
INTERFACE void msIR_WriteByte(U16 u16RegIndex, U8 u8Value);
INTERFACE void msIR_Write2Byte ( U16 u16RegIndex, U16 u16Value );
INTERFACE void msIR_Write3Byte ( U16 u16Regndex, U32 u32Value );
INTERFACE void msIR_Initialize(U8 irclk_mhz);
INTERFACE void msIR_PowerDown_Init(void);
INTERFACE BOOLEAN msIR_GetIRKeyCode(U8 *pkey, U8 *pu8flag);

extern U8 g_ucIrRepeatTimer;
INTERFACE BOOLEAN MDrv_Power_CheckPowerOnSWIRKey(void);
INTERFACE BOOLEAN MDrv_IR_CheckPowerOnKey(void);
#if (IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
INTERFACE BOOLEAN MDrv_CheckSWIRKey(void);
#endif
BOOLEAN MDrv_IR_IsIRkeyEnabled(U8 u8IRkey);

#define IR_CODE                     (g_ucIrCode[2])
INTERFACE U8 g_bIrDetect;//!<IR command detect flag
INTERFACE U8 g_ucIrCode[10];

#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
// Variables and fuctions used in IR SWDECODE MODE for TVLINK-Loader ----------------------------
#define IR_SW_COUNT_BIT_NUM         8
#define IR_SW_REPEAT_TIMEOUT        110//110ms
#define IR_REPEAT_SKIP_COUNT        2
#define IR_MAX_IR_DATA_NUM            10

INTERFACE U16 g_wIrLoaderCnt;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
INTERFACE U8 g_u8IrKonRepeatTimeout;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
// Fixed pulse width format: Start(1.5)+Control(1)+System(5)+Data(6)
#define IR_RC5_DATA_BITS                 26

#define IR_RC5_DETECT_START         BIT0   // start to detect IR int
#define IR_RC5_DETECT_END             BIT1   // end to detect IR int
#define IR_RC5_LAST_BIT                 BIT2    // last bit detect IR int

#define IR_RC5_DECODING                 BIT6   // sw decoding
#define IR_RC5_TOGGLE_BIT              BIT7       // for control bit

INTERFACE U16 volatile data g_u16IrRc5Data;          // for store shift ir data
INTERFACE U8 volatile data g_u8IrRc5Bits;                // for store bit count
INTERFACE U16 volatile data g_u16IrRc5Counter;         // for read counter from register
INTERFACE U8 volatile data g_u8IrRc5Flag;            // for store bit var
INTERFACE U8 volatile data g_u8IrRc5RepeatCount;

#elif (IR_MODE_SEL == IR_TYPE_HWDECODE_RC)
//IR HW_FULL: Time Interval & Timeout
#define HAL_IR_NEC_INTERVAL             108
#define HAL_IR_NEC_TIMEOUT              120
//IR HW_RC5: Time Interval & Timeout
#define HAL_IR_RC5_INTERVAL             29//ms
#define HAL_IR_RC5_TIMEOUT              116//ms
//IR HW_RC6: Time Interval & Timeout
#define HAL_IR_RC6_INTERVAL             26//ms
#define HAL_IR_RC6_TIMEOUT              104//ms
//IR decode mode
#define HAL_IR_DECODE_FULL          0x03//0x00
#define HAL_IR_DECODE_RAW           0x02//0x00
#define HAL_IR_DECODE_SW            0x01//0x00
//IR FIFO
#define HAL_IR_FIFO_DEPTH_MAX       7
#define HAL_IR_RC_FIFO_DEPTH_MAX    7
//IR control
#define HAL_IR_CTRL_0               0
#define HAL_IR_CTRL_1               1
#define HAL_IR_RC_CTRL_0            2
#define HAL_IR_RC_CTRL_1            3
//IR RC Decode Type
#define HAL_IR_RC_RC5               0
#define HAL_IR_RC_RC5X              1
#define HAL_IR_RC_RC6               2
#define HAL_IR_RC_DISABLE           3
//IR RC Wakeup key
#define HAL_IR_RC_WKUP_KEY1         0
#define HAL_IR_RC_WKUP_KEY2         1

typedef struct
{
    U8 u8Valid : 1;
    U8 u8Toggle : 1;
    U8 u8Repeat : 1;
    U8 u8RC6Mode : 3;  //Only for RC6
    U8 u8Reserved : 2;
    U8 u8Address; //system bits: RC5[4:0], RC6[7:0]
    U8 u8Command; //command bits: RC5[5:0], RC5X[6:0], RC6[7:0]
} HAL_IR_RC_KeyData;

//##############################
// For Hardware RC Decode
//##############################
#define IR_REG_BASEMENT                         (0x1E80*2) //(0x1EC0*2)
#define REG_IR_RC_CTRL0                         ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2))
#define REG_IR_RC_RC6_LDPS_THR_L                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2))    //BIT[4:0]
    #define _IR_RC_RC6_LDPS_THR_L_MSK           (0x1F) //BIT[4:0]
    #define _IR_RC_AUTOCONFIG                   (BIT5)
    #define _IR_RC_FIFO_CLR                     (BIT6)
    #define _IR_RC_FIFO_WFST                    (BIT7)
#define REG_IR_RC_CTRL1                         ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2) +1)
#define REG_IR_RC_WKUP_DEBUG_SEL                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2) +1) //BIT[6:4]
    #define _IR_RC_WKUP_DEBUG_SEL_MSK           (BIT6|BIT5|BIT4) //BIT[6:4]
    #define _IR_RC_ENABLE                       (BIT0)
    #define _IR_RC_RC6_EN                       (BIT1)
    #define _IR_RC_RC5X_EN                      (BIT2)
    #define _IR_RC_MODE_MSK                     (_IR_RC_RC5X_EN|_IR_RC_RC6_EN|_IR_RC_ENABLE)
    #define _IR_RC_WKUP_EN                      (BIT3)
    #define _IR_RC_DGB_SEL                      (BIT6|BIT5|BIT4)
    #define _IR_RC_IN_INV                       (BIT7)
#define REG_IR_RC_LGPS_THR_L                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x01*2))    //BIT[7:0]
#define REG_IR_RC_LGPS_THR_H                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x01*2) +1) //BIT[4:0]
    #define _IR_RC_LGPS_THR_L_MSK               (0xFF)
    #define _IR_RC_LGPS_THR_H_MSK               (0x1F)
#define REG_IR_RC_RC6_LGPS_MAR_L                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x02*2))    //BIT[7:0]
#define REG_IR_RC_RC6_LGPS_MAR_H                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x02*2) +1) //BIT[1:0]
    #define _IR_RC_RC6_LGPS_MAR_L_MSK           (0xFF)
    #define _IR_RC_RC6_LGPS_MAR_H_MSK           (0x03)
#define REG_IR_RC_RC6_LDPS_THR_H                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x02*2) +1) //BIT[4:2]
    #define _IR_RC_RC6_LDPS_THR_H_MSK           (BIT4|BIT3|BIT2) //BIT[4:2]
#define REG_IR_RC_RC6_ECO_EN                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x03*2))    //BIT[0]
    #define _IR_RC_RC6_ECO_EN                   (BIT0)
#define REG_IR_RC_INTG_THR                      ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x03*2))    //BIT[7:1]
    #define _IR_RC_INTG_THR_MSK                 (0xFE)
#define REG_IR_RC_CLK_DIV                       ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x03*2) +1) //BIT[4:0]
    #define _IR_RC_CLK_DIV_MSK                  (0x1F)
#define REG_IR_RC_WDOG_COUNT                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x04*2))    //BIT[7:0]
#define REG_IR_RC_TIMEOUT_COUNT                 ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x04*2) +1) //BIT[7:0]
#define REG_IR_RC_COMP_KEY1                     ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x05*2))    //BIT[7:0]
#define REG_IR_RC_COMP_KEY2                     ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x05*2) +1) //BIT[7:0]

//Registers: Read Only
#define REG_IR_RC_KEY_ADDR                      ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x06*2))    //BIT[7:0]
    #define _IR_RC_RC5_KEY_ADDR_MSK             (0x1F) //{[7:6]:2'b00, [5]:toggle, [4:0]:address}
    #define _IR_RC_RC5_KEY_ADDR_TGL             (BIT5)
    #define _IR_RC_RC6_KEY_ADDR_MSK             (0xFF) //[7:0]:address
#define REG_IR_RC_KEY_CMD                       ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x06*2) +1) //BIT[7:0]
    #define _IR_RC_RC5_KEY_CMD_MSK              (0x3F)//{[7]:repeat, [6]:1'b0, [5:0]:command}
    #define _IR_RC_RC5_KEY_CMD_RPT              (BIT7)
    #define _IR_RC_RC5X_KEY_CMD_MSK             (0x7F)//{[7]:repeat, [6:0]:command}
    #define _IR_RC_RC5X_KEY_CMD_RPT             (BIT7)
    #define _IR_RC_RC6_KEY_CMD_MSK              (0xFF)//[7:0]:command
#define REG_IR_RC_RC6_KEY_MISC                  ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x07*2))    //BIT[4:0]
    #define _IR_RC_RC6_KEY_MISC_MOD_MSK         (BIT2|BIT1|BIT0)//{[4]:repeat, [3]:toggle, [2:0]:mode}
    #define _IR_RC_RC6_KEY_MISC_TGL             (BIT3)
    #define _IR_RC_RC6_KEY_MISC_RPT             (BIT4)
#define REG_IR_RC_FIFO_STATUS1                  ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x08*2))
    #define _IR_RC_FIFO_EMPTY                   (BIT0)
    #define _IR_RC_TIMEOUT_FLAG                 (BIT1)
    #define _IR_RC_FIFO_FULL                    (BIT2)
    #define _IR_RC_FIFO_WPTR_MSK                (BIT6|BIT5|BIT4)
#define REG_IR_RC_FIFO_STATUS2                  ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x08*2) +1)
    #define _IR_RC_FIFO_RPTR_MSK                (BIT2|BIT1|BIT0)

//Registers: Write Only
#define REG_IR_RC_FIFO_READ_PULSE               ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x09*2))
    #define _IR_RC_FIFO_RD_PULSE                (BIT0)
#define REG_IR_RC_WKUP_CLR                      ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x09*2) +1)
    #define _IR_RC_WKUP_CLR                     (BIT0)


#define REG_IR_CTRL0                            ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x40*2))
    #define _IR_HWDEC_EN                        (BIT0)
    #define _IR_LDCCHK_EN                       (BIT1)
    #define _IR_CCODE_CHK_EN                    (BIT2)
    #define _IR_DCODE_PCHK_EN                   (BIT3)
    #define _IR_LG01H_CHK_EN                    (BIT4)
    #define _IR_RPCODE_EN                       (BIT5)
    #define _IR_INT_MSK                         (BIT6)
    #define _IR_INV                             (BIT7)

#define REG_IR_CTRL1                            ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x40*2) +1)
    #define _IR_TIMEOUT_CHK_EN                  (BIT0)
    #define _IR_SEP_CODE_CHK_EN                 (BIT1)
    #define _IR_CODE_BIT_LSB_EN                 (BIT2)
    #define _IR_NEC_WKUP_EN                     (BIT3)
    #define _IR_TSTBUS_SEL_MSK                  (BIT5|BIT4)
    #define _IR_RAW_RPT_INT_MSK                 (BIT6)
    #define _IR_INT_CRC_MSK                     (BIT7)

    //#######################################
    //#  For Hardware RC Decode
    //#######################################
    INTERFACE void HAL_IR_CfgSetControl(U32 u32Reg,U8 u8CtrlData,U8 u8Mask);
    INTERFACE void HAL_IR_CfgControl(U8 u8Index, U8 u8CtrlData,U8 u8Mask);
    INTERFACE void HAL_IR_CfgHwDecode(U8 u8Enable);
    INTERFACE void HAL_IR_CfgIntrMask(U8 u8Enable);

    INTERFACE U8 HAL_IR_RC_GetDecode(void);
    INTERFACE void HAL_IR_RC_CfgClkDiv(U8 u8ClkMhz);
    INTERFACE void HAL_IR_RC_CfgAutoConfig(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgFifoClear(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgFifoWFirst(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgDecMode(U8 u8DecMode);
    INTERFACE void HAL_IR_RC_CfgWakeup(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgOutputSelect(U8 u8OutputSel);
    INTERFACE void HAL_IR_RC_CfgInputInvert(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgLgpsThr(void);
    INTERFACE void HAL_IR_RC_CfgIntgThr(void);
    INTERFACE void HAL_IR_RC_CfgWdogCount(void);
    INTERFACE void HAL_IR_RC_CfgTimeoutCount(void);//U16 u16TimeoutUs
    INTERFACE void HAL_IR_RC_CfgLgpsMar(void);//Only for RC6
    INTERFACE void HAL_IR_RC_CfgLdpsThr(void);//Only for RC6
    INTERFACE void HAL_IR_RC_CfgEcoFunc(BOOLEAN bEnable);//Only for RC6
    INTERFACE BOOLEAN HAL_IR_RC_IsTimeout(void);
    INTERFACE BOOLEAN HAL_IR_RC_IsFIFOEmpty(void);
    INTERFACE BOOLEAN HAL_IR_RC_IsFIFOFull(void);
    INTERFACE void HAL_IR_RC_ClearFIFO(void);
    INTERFACE U8 HAL_IR_RC_GetWakeupKey(U8 u8KeyNum);
    INTERFACE void HAL_IR_RC_GetKeyData(HAL_IR_RC_KeyData *pIRRCKeyData);

#endif
INTERFACE void msIR_ResetSoftWareModeVariables(void);

INTERFACE void msIR_SwitchIRMode(U8 mode);
//----------------------------------------------------------------------------
#undef INTERFACE

#endif
