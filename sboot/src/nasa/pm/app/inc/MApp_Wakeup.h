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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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

#ifndef MAPP_WAKEUP_H
#define MAPP_WAKEUP_H

////////////////////////////////////////////////////////////////////////////////

#ifdef  MAPP_WAKEUP_C
#define WAKEUP_INTERFACE
#else
#define WAKEUP_INTERFACE extern
#endif

////////////////////////////////////////////////////////////////////////////////

WAKEUP_INTERFACE BOOLEAN gSyncDetect;
WAKEUP_INTERFACE BOOLEAN gDviClockDetect;
WAKEUP_INTERFACE U8 u8HDMIWakeUpDelayCount;

//***********************************************************
//              Macro Definitions
//***********************************************************
#define BLOCK_POWER_FUNC                        1
#define ENABLE_SC_BLOCK_SYNC_WAKEUP             0//default set to disable

//SYNC register
#define PMSLEEP_REG_BASE                        (0x0700*2)
#define REG_PM_WK_IRQ_MASK                      ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x08*2))
#define REG_PM_WK_IRQ_FORCE                     ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x08*2))

#define REG_PM_SD_IRQ_MASK                      ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x16*2))
#define REG_PM_SD_IRQ_FORCE                     ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x16*2))
#define REG_PM_SD_IRQ_CLR                       ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x17*2))
#define REG_PM_SD_POL                           ((0x00*0x10000) + (PMSLEEP_REG_BASE + 0x17*2))

#define REG_RTC_BASE_0                          (0x1280)

//RTC register
#define RTC_SOFT_RSTZ_BIT                       0x0001
#define RTC_CNT_EN_BIT                          0x0002
#define RTC_WRAP_EN_BIT                         0x0004
#define RTC_LOAD_EN_BIT                         0x0008
#define RTC_READ_EN_BIT                         0x0010
#define RTC_INT_MASK_BIT                        0x0020
#define RTC_INT_FORCE_BIT                       0x0040
#define RTC_INT_CLEAR_BIT                       0x0080

#define REG_RTC_CTRL_REG                        ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x00*2))
#define REG_RTC_FREQ_CW_L                       ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x01*2))
#define REG_RTC_FREQ_CW_H                       ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x02*2))

#define REG_RTC_LOAD_VAL                        ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x03*2))

#define REG_RTC_MATCH_VAL_L                     ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x05*2))
#define REG_RTC_MATCH_VAL_H                     ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x06*2))
    #define RTC_DISABLE_VALUE                   0xFFFFFFFF

#define REG_RTC_INT                             ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x07*2))
#define REG_RTC_CNT                             ((0x00*0x10000) + (REG_RTC_BASE_0 + 0x08*2))


#define REG_PM_DVI_DET_CMP_P0                   ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x2F*2))
#define REG_PM_DVI_DET_CMP_P1                   ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x2F*2 + 1))
#define REG_PM_DVI_CTRL_SW_RST                  ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x31*2))

#define REG_PM_CMPVALUE1_P0                     ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x40*2))
#define REG_PM_CMPVALUE2_P0                     ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x41*2))
#define REG_PM_K_RPT_P0                         ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x42*2))

#define REG_PM_CMPVALUE1_P1                     ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x44*2))
#define REG_PM_CMPVALUE2_P1                     ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x45*2))
#define REG_PM_K_RPT_P1                         ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x46*2))

#define REG_PM_DM_SEL_IB                        ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))
#define REG_PM_DM_SEL_IB_ONEPORT                ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))
#define REG_PM_DM_CLKSEL                        ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))
#define REG_PM_DM_CLKSEL_ONEPORT                ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))
#define REG_PM_PD_IBGREX                        ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))
#define REG_PM_PD_IBGREX_ONEPORT                ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))

#define REG_PM_GCR_SWCK                         ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_GCR_SWCK_OFFL                    ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_GCR_SWCK_ONEPORT                 ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_PD_CLKIN                         ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_PD_CLKIN_OFFL                    ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4A*2))
#define REG_PM_PD_CLKIN_ONEPORT                 ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_PD_RCK                           ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_PD_RCK_ONEPORT                   ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))
#define REG_PM_DVI_SWCK_HW_EN                   ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4B*2))

#define REG_PM_PD_BG                            ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4C*2))
#define REG_PM_PD_BG_ONEPORT                    ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4C*2))
#define REG_PM_DVI_HW_SW_CNT                    ((0x00*0x10000)+ (PMSLEEP_REG_BASE + 0x4D*2))


////////////////////////////////////////////////////////////////////////////////

void MDrv_UART_ChckWakeupEvent(int c);
void MDrv_UART_ConfigWakeup(void);

void MDrv_RTC_Isr(void);
void MDrv_RTC_ConfigWakeup(void);

void MDrv_SYNC_ClearINT(void);
void MDrv_SYNC_Isr(void);
void MDrv_SYNC_KeepStandby(void);
void MDrv_SYNC_ProcessWakeup(void);
void MDrv_SYNC_ConfigWakeup(void);

void MDrv_DVI_Isr(void);
void MDrv_DVI_ProcessWakeup(void);
void MDrv_DVI_ConfigWakeup(void);
void MDrv_DVI_ManualSwitchPort(void);

void MDrv_ProcessMHLWakeup(void);

void MDrv_ProcessUSBWakeup(void);
void MDrv_USBPrecheck(void);
U8 MDrv_CheckUsbStatus(void);

BOOL MDrv_IR_IsWakeup(U8 u8Key);

void MApi_InitCEC(void);
void MApp_CEC_Handler(void);


void MApp_CheckWakeupEvent(void);


// please sync with AP source file: msAPI_Power.h
#define WakeUp_by_IR        0
#define WakeUp_by_CEC       BIT0
#define WakeUp_by_GPIO      BIT1
#define WakeUp_by_RTC       BIT2
#define WakeUp_by_SAR       BIT3
#define WakeUp_by_DDCD      BIT4
#define WakeUp_by_DVI       BIT5
#define WakeUp_by_SYNC      BIT6
#define WakeUp_by_USB       BIT7
#define WakeUp_by_MHL       BIT8
#define WakeUp_by_None      0xFF
WAKEUP_INTERFACE void msAPI_Power_NotifyWakeupDeviceForAP(U16 u16WakeUpDEvice);


// Wake-up device
// please sync with AP source file: msAPI_Power.h
enum
{
    PM_WAKEUP_BY_KEYPAD         = (1 << 0),
    PM_WAKEUP_BY_CEC            = (1 << 1),
    PM_WAKEUP_BY_RTC            = (1 << 2),
    PM_WAKEUP_BY_DDC            = (1 << 3),

    PM_WAKEUP_BY_VGA            = (1 << 4),
    PM_WAKEUP_BY_DVI            = (1 << 5),
    PM_WAKEUP_BY_GPI            = (1 << 6),
    PM_WAKEUP_BY_IR             = (1 << 7),

    PM_WAKEUP_BY_UART           = (1 << 8),
    PM_WAKEUP_BY_USB            = (1 << 9),
    PM_WAKEUP_BY_MHL            = (1 << 10),
    PM_WAKEUP_BY_DVI1           = (1 << 11),
    PM_WAKEUP_BY_DVI2           = (1 << 12),
    
    PM_WAKEUP_BY_ALL            = PM_WAKEUP_BY_KEYPAD
                                | PM_WAKEUP_BY_CEC
                                | PM_WAKEUP_BY_RTC
                                | PM_WAKEUP_BY_DDC
                                | PM_WAKEUP_BY_VGA
                                | PM_WAKEUP_BY_DVI
                                | PM_WAKEUP_BY_GPI
                                | PM_WAKEUP_BY_IR
                                | PM_WAKEUP_BY_UART
                                | PM_WAKEUP_BY_USB
                                | PM_WAKEUP_BY_MHL
                                | PM_WAKEUP_BY_DVI1
                                | PM_WAKEUP_BY_DVI2,
};

void MDrv_CheckWakeupDeviceFromAP(void);






////////////////////////////////////////////////////////////////////////////////

#undef WAKEUP_INTERFACE

#endif // MAPP_WAKEUP_H

