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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (ߡMStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#define MAPP_WAKEUP_C

#include <stdio.h>
#include "datatype.h"
#include "drvGlobal.h"
#include "hwreg.h"
#include "MsCommon.h"
#include "MApp_Wakeup.h"
#include "drvUART.h"
#include "uartdebug.h"
#include "MApp_IR.h"
#include "uartdebug.h"
#include "apiCEC.h"
#include "msAPI_CEC.h"
#include "xcSys.h"
#include "drvXC_HDMI_if.h"

//***********************************************************
//              Debug Definition
//***********************************************************
#define WKDBG(x)    //x


//***********************************************************
//              Global Functions Definition
//***********************************************************
#define MAX_IR_WAKEUP_KEYS      4
extern void SystemWholeChipReset(void);

static U16 wPM_WakeUpDevice = 0;
static U8 UartIdx = 0;
static U8 UsbStatus = 0;
// store wakeup IR keys : max 4 keys (1 byte per key)
static U8 g_u8IRWakeupKey[MAX_IR_WAKEUP_KEYS];

//***********************************************************

void MDrv_UART_ChckWakeupEvent(int c)
{
    if( c == 'w' )
    {
        UartIdx=1;
    }
    else
    {
        if( c == 'a' && UartIdx == 1 )
        {
            UartIdx++;
        }
        else
        {
            if( c == 'k' && UartIdx == 2)
            {
                UartIdx++;
            }
            else
            {
                if( c == 'e' && UartIdx == 3)
                {
                    UartIdx = 0;
                    SystemWholeChipReset();
                }
            }
        }
    }
}

//***********************************************************

void msAPI_Power_NotifyWakeupDeviceForAP(U16 u16WakeUpDEvice)
{
    MDrv_Write2Byte(PM_SLEEP_NOTIFY_WAKEUP_DEVICE_FLAG, u16WakeUpDEvice);
}

//***********************************************************

void MDrv_RTC_Isr(void)
{
    msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_RTC);
    SystemWholeChipReset();

    //enable interrupt again
    //MsOS_EnableInterrupt(E_INT_IRQ_RTC);
}

//***********************************************************

U8 MDrv_CheckUsbStatus(void)
{
    U8 temp=0;
    // switch USB port
    MDrv_WriteRegBit(0x103ab8, 0, BIT2);
    temp = MDrv_ReadByte(0x100708);
    temp &= BIT6;
    if(temp != 0)
    {
        return TRUE;
    }

    temp = 0;
    // check USB status
    MDrv_WriteRegBit(0x103ab8, 1, BIT2);
    temp = MDrv_ReadByte(0x100708);
    temp &= BIT6;
    if(temp != 0)
    {
        return TRUE;
    }

    return FALSE;
}

void MDrv_USBPrecheck(void)
{
    U8 temp=0;

    temp = MDrv_CheckUsbStatus();
    if(temp == TRUE)
        UsbStatus = 1; // USB plug-in before system into PM
    else
        UsbStatus = 2; // USB plug-out before system into PM
}

void MDrv_ProcessUSBWakeup(void)
{
    U8 temp = 0;

    temp = MDrv_CheckUsbStatus();
    if(temp == TRUE) // low -> high
    {
        if(UsbStatus == 2)
        {
            msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_USB);
            SystemWholeChipReset();
        }
    }
    else
    {
        if(UsbStatus == 1)  // high -> low
            UsbStatus = 2;
    }
}

void MDrv_ProcessMHLWakeup(void)
{
    if( ((MDrv_Read2Byte(0x002F30) & BIT(7))>>7) == 1 )  //mobile phone plug in, from low to high
    {
        msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_MHL);
        SystemWholeChipReset();
    }
}

//***********************************************************

#if 0
void MDrv_RTC_ConfigWakeup(void)
{
    MDrv_WriteByte(REG_RTC_CTRL_REG, MDrv_Read2Byte(REG_RTC_CTRL_REG)&(~RTC_SOFT_RSTZ_BIT));
    MDrv_WriteByte(REG_RTC_CTRL_REG, MDrv_Read2Byte(REG_RTC_CTRL_REG)|(RTC_SOFT_RSTZ_BIT));
    MDrv_Write2Byte(REG_RTC_FREQ_CW_L, 0x1B00);
    MDrv_Write2Byte(REG_RTC_FREQ_CW_H, 0x00B7);
    MDrv_Write2Byte(REG_RTC_MATCH_VAL_L, 0x000A);
    MDrv_Write2Byte(REG_RTC_MATCH_VAL_H, 0x0000);

    MDrv_WriteByte(REG_RTC_CTRL_REG, MDrv_Read2Byte(REG_RTC_CTRL_REG)&(~RTC_INT_MASK_BIT));
    MDrv_WriteByte(REG_RTC_CTRL_REG, MDrv_Read2Byte(REG_RTC_CTRL_REG)&(~RTC_INT_CLEAR_BIT));

    MsOS_AttachInterrupt(E_INT_IRQ_RTC, (InterruptCb)MDrv_RTC_Isr);
    MsOS_EnableInterrupt(E_INT_IRQ_RTC);

    MDrv_WriteByte(REG_RTC_CTRL_REG, MDrv_Read2Byte(REG_RTC_CTRL_REG)|(RTC_WRAP_EN_BIT));
    MDrv_WriteByte(REG_RTC_CTRL_REG, MDrv_Read2Byte(REG_RTC_CTRL_REG)|(RTC_CNT_EN_BIT));

}
#endif

//***********************************************************
void MDrv_SYNC_ClearINT(void)
{
    MDrv_WriteByte(REG_PM_SD_IRQ_CLR, (MDrv_ReadByte(REG_PM_SD_IRQ_CLR))|(BIT5|BIT4|BIT3|BIT2|BIT1|BIT0));
    MDrv_WriteByte(REG_PM_SD_IRQ_CLR, (MDrv_ReadByte(REG_PM_SD_IRQ_CLR))&(~(BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)));
}

void MDrv_SYNC_Isr(void)
{
    WKDBG(printf("\n\rMDrv_SYNC_Isr\n\r");)

    #if ENABLE_SC_BLOCK_SYNC_WAKEUP
    //(1) power up SC block
    MDrv_WriteRegBit(0x101e1e, 1, BIT4);
    MDrv_WriteRegBit(0x101e1e, 1, BIT0);
    MDrv_WriteRegBit(0x101e3a, 0, BIT2);
    //(2) must generate 3T clock to let reset signal feeded into scaler
    //generate 3T clock
    MDrv_WriteByte(0x100baa, 0x00);
    MDrv_WriteRegBit(0x100baa, 1, BIT1);
    MDrv_WriteByte(0x100baa, 0x00);
    MDrv_WriteRegBit(0x100baa, 1, BIT1);
    MDrv_WriteByte(0x100baa, 0x00);
    MDrv_WriteRegBit(0x100baa, 1, BIT1);
    //recovery back to value after standby
    MDrv_WriteByte(0x100baa, 0x01);
    //(3) set ipmux as ADC A, and select IP1 input source as analog1(for VGA)
    XC_Recovery_VGA();
    #endif
    //(4) set sync detect flag
    gSyncDetect = TRUE;

}

void MDrv_SYNC_KeepStandby(void)
{
    WKDBG(printf("\n\nMDrv_SYNC_KeepStandby\n\r");)

    #if ENABLE_SC_BLOCK_SYNC_WAKEUP
    //(1) power down SC block
    MDrv_WriteRegBit(0x101e3a, 1, BIT2);
    MDrv_WriteRegBit(0x101e1e, 0, BIT0);
    MDrv_WriteRegBit(0x101e1e, 0, BIT4);
    #endif
    //(2) clear interrupt status & disable interrupt
    MDrv_SYNC_ClearINT();
    MsOS_EnableInterrupt(E_INT_IRQ_SYNC_DET);
}

void MDrv_SYNC_ProcessWakeup(void)
{
    //clear interrupt status & disable interrupt
    MDrv_SYNC_ClearINT();
    MsOS_DisableInterrupt(E_INT_IRQ_SYNC_DET);
    //set wakeup event source
    msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_SYNC);
    //do chip global reset
    SystemWholeChipReset();
}

void MDrv_SYNC_ConfigWakeup(void)
{
    // from Zen_T8 code base T12 register setting
    //Interrupt setting
    // {vsync2,hsync2,vsync1,hsync1:FAIL,vsync0:OK,hsync0:FAIL}
    MDrv_Write2Byte(REG_PM_SD_POL, MDrv_Read2Byte(REG_PM_SD_POL)|(BIT6));  //1: active low
    MDrv_WriteByte(REG_PM_SD_IRQ_MASK, MDrv_ReadByte(REG_PM_SD_IRQ_MASK)&(~(BIT1))); //unmask vsync0
    MDrv_Write2Byte(REG_PM_SD_IRQ_FORCE, MDrv_Read2Byte(REG_PM_SD_IRQ_FORCE)&(~(BIT6)));

    MDrv_SYNC_ClearINT();
    MsOS_AttachInterrupt(E_INT_IRQ_SYNC_DET, (InterruptCb)MDrv_SYNC_Isr);
    MsOS_EnableInterrupt(E_INT_IRQ_SYNC_DET);
    gSyncDetect = FALSE;
}

//***********************************************************

void MDrv_DVI_Isr(void)
{
    WKDBG(printf("\n\rMDrv_DVI_Isr\n\r");)
    gDviClockDetect = TRUE;
    //MsOS_DisableInterrupt(E_INT_FIQ_DVI_DET);
}

void MDrv_DVI_ProcessWakeup(void)
{
    MsOS_DisableInterrupt(E_INT_FIQ_DVI_DET);
    msAPI_Power_NotifyWakeupDeviceForAP(WakeUp_by_DVI);
    SystemWholeChipReset();
}

void MDrv_DVI_ConfigWakeup(void)
{
    MDrv_Write2Byte(REG_PM_DM_SEL_IB, 0x0000);
    MDrv_Write2Byte(REG_PM_GCR_SWCK, 0x0100 | BIT3);
    MDrv_Write2Byte(REG_PM_DVI_HW_SW_CNT, 0x00FF);// reg_dvi_hw_sw_cnt
    // reg_dvi_ctrl_sw_rst
    MDrv_Write2Byte(REG_PM_DVI_CTRL_SW_RST, (MDrv_Read2Byte(REG_PM_DVI_CTRL_SW_RST)|BIT9));
    MDrv_Write2Byte(REG_PM_DVI_CTRL_SW_RST, (MDrv_Read2Byte(REG_PM_DVI_CTRL_SW_RST)&~BIT9));
    //set interrupt condition for port 0
    MDrv_WriteByte(REG_PM_DVI_DET_CMP_P0, (MDrv_ReadByte(REG_PM_DVI_DET_CMP_P0)&(~0xFF))|0xF2);// reg_dvi_det_cmp
    MDrv_Write2Byte(REG_PM_CMPVALUE1_P0, 0x0006);// reg_cmpvalue   //for sleep
    MDrv_Write2Byte(REG_PM_CMPVALUE2_P0, 0x0064);// reg_cmpvalue2 //for sleep
    //set interrupt condition for port 1
    MDrv_WriteByte(REG_PM_DVI_DET_CMP_P1, (MDrv_ReadByte(REG_PM_DVI_DET_CMP_P1)&(~0xFF))|0xF2);// reg_dvi_det_cmp
    MDrv_Write2Byte(REG_PM_CMPVALUE1_P1, 0x0006);// reg_cmpvalue_1   //for sleep
    MDrv_Write2Byte(REG_PM_CMPVALUE2_P1, 0x0064);// reg_cmpvalue2_1 //for sleep

    MsOS_AttachInterrupt(E_INT_FIQ_DVI_DET, (InterruptCb)MDrv_DVI_Isr);
    MsOS_EnableInterrupt(E_INT_FIQ_DVI_DET);
    gDviClockDetect = FALSE;
}

void MDrv_DVI_ManualSwitchPort(void)
{
    //#define DELAY_TIME_MS   500 //>=500 :OK, <500:with risk of failure
    if(wPM_WakeUpDevice & PM_WAKEUP_BY_DVI)
    {
        //switch to port 0
        if( 25 == u8HDMIWakeUpDelayCount )
        {
            MDrv_WriteRegBit(REG_PM_GCR_SWCK, 0, BIT3);
        }
        if( u8HDMIWakeUpDelayCount > 0 )
        {
            u8HDMIWakeUpDelayCount--;
            msDelayTime(20);
        }
        if(0 == u8HDMIWakeUpDelayCount )
        {
            u8HDMIWakeUpDelayCount = 25;
            msDelayTime(20);
            MDrv_WriteRegBit(REG_PM_GCR_SWCK, 1, BIT3);
        }
    }
    else if(wPM_WakeUpDevice & PM_WAKEUP_BY_DVI1)
    {
        //switch to port 1
        if( 25 == u8HDMIWakeUpDelayCount )
        {
            MDrv_WriteRegBit(REG_PM_GCR_SWCK, 0, BIT4);
        }
        if( u8HDMIWakeUpDelayCount > 0 )
        {
            u8HDMIWakeUpDelayCount--;
            msDelayTime(20);
        }
        if( 0 == u8HDMIWakeUpDelayCount )
        {
            u8HDMIWakeUpDelayCount = 25;
            msDelayTime(20);
            MDrv_WriteRegBit(REG_PM_GCR_SWCK, 1, BIT4);
        }
    }
    else
    {
        //switch to port 2
        if( 25 == u8HDMIWakeUpDelayCount )
        {
            MDrv_WriteRegBit(REG_PM_GCR_SWCK, 0, BIT5);
        }
        if( u8HDMIWakeUpDelayCount > 0 )
        {
            u8HDMIWakeUpDelayCount--;
            msDelayTime(20);
        }
        if( 0 == u8HDMIWakeUpDelayCount )
        {
            u8HDMIWakeUpDelayCount = 25;
            msDelayTime(20);
            MDrv_WriteRegBit(REG_PM_GCR_SWCK, 1, BIT5);
        }
    }
}
static void MDrv_DVI_PowerDown(void) //OK
{
    MDrv_WriteRegBit( 0x000e94, 1, 0xFF);
    MDrv_WriteRegBit( 0x000e96, 1, 0x7F);
    MDrv_WriteRegBit( 0x000e97, 1, 0x38);
    MDrv_WriteRegBit( 0x000e98, 1, 0x02);
}
//***********************************************************
static void MDrv_IR_ConfigWakeup(void)
{
    // store IR wakeup keys
    g_u8IRWakeupKey[0] = MDrv_ReadByte(STNADBY_WAKEUP_IR_KEY0);
    g_u8IRWakeupKey[1] = MDrv_ReadByte(STNADBY_WAKEUP_IR_KEY1);
    g_u8IRWakeupKey[2] = MDrv_ReadByte(STNADBY_WAKEUP_IR_KEY2);
    g_u8IRWakeupKey[3] = MDrv_ReadByte(STNADBY_WAKEUP_IR_KEY3);

}

BOOL MDrv_IR_IsWakeup(U8 u8Key)
{
    U8 i;

    for(i=0;i<MAX_IR_WAKEUP_KEYS;i++)
    {
        if(u8Key==g_u8IRWakeupKey[i])
            return TRUE;
    }
    return FALSE;
}


//***********************************************************
extern void Hal_HDMI_POWER_OFF(void);
void MDrv_CheckWakeupDeviceFromAP(void)
{
    wPM_WakeUpDevice = MDrv_Read2Byte(PM_SLEEP_WAKEUP_DEVICE_FLAG);
    WKDBG(printf("wPM_WakeUpDevice = 0x%x \r\n", wPM_WakeUpDevice);)

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_KEYPAD)
    {
        // init Keypad by default
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_IR)
    {
        // init IR by default
        MDrv_IR_ConfigWakeup();
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_CEC)
    {
        MApi_CEC_ConfigWakeUp();
        msAPI_CEC_Init();
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_RTC)
    {
        // RTC wakeup is set by AP,
        // if RTC wakeup is set, PM only needs to enable ISR.
        if ( MDrv_Read4Byte(REG_RTC_MATCH_VAL_L) != RTC_DISABLE_VALUE)
        {
            MsOS_AttachInterrupt(E_INT_IRQ_RTC, (InterruptCb)MDrv_RTC_Isr);
            MsOS_EnableInterrupt(E_INT_IRQ_RTC);
        }
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_DDC)
    {
        // to be implemented
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_VGA)
    {
        MDrv_WriteRegBit(0x10250b, 1, _BIT0); //adc_atop::reg_pdn_hsync[0], 1 : power down, 0 : power up
        msDelayTime(10);
        _MApi_XC_Sys_Init_XC();
        MDrv_SYNC_ConfigWakeup();
    }
    else
    {
       // power down SC block
       MDrv_WriteRegBit(0x101e3a, 1, BIT2);
       MDrv_WriteRegBit(0x101e1e, 0, BIT0);
       MDrv_WriteRegBit(0x101e1e, 0, BIT4);
    }

    if ((wPM_WakeUpDevice & PM_WAKEUP_BY_DVI)||(wPM_WakeUpDevice & PM_WAKEUP_BY_DVI1)||(wPM_WakeUpDevice & PM_WAKEUP_BY_DVI2))
    {
        MDrv_DVI_ConfigWakeup();
    }
    else
    {
        Hal_HDMI_POWER_OFF();
        MDrv_DVI_PowerDown();
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_GPI)
    {
        // to be implemented
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_UART)
    {
        ;
    }

    if (wPM_WakeUpDevice & PM_WAKEUP_BY_USB)
    {
        MDrv_USBPrecheck();
    }

    MDrv_UART_ConfigWakeup();
}

//***********************************************************

void MApp_CheckWakeupEvent(void)
{
    // clear WDT
    // Check GPIO status (GPIO wakeup)
    if (wPM_WakeUpDevice & PM_WAKEUP_BY_VGA)
    {
        if (gSyncDetect)
        {
            U32 BackupReg = MDrv_Read2Byte(0x10250A);
            MDrv_Write2Byte(0x10250A,0); //Set ADC
            gSyncDetect = FALSE;
            msDelayTime(10);
            XC_Get_ModeStatus();
            if ( XC_GetModeParseResult() == XC_MODEPARSE_SUPPORT_MODE )
            {
                WKDBG(printf("\r\nMODE : SUPPORT\r\n"));
                MDrv_SYNC_ProcessWakeup();
            }
            #if ENABLE_VGA_JUST_CHECK_SYNC
            if( XC_Check_HVSync() == TRUE )
            {
                WKDBG(printf("\r\MODE : SYNC\r\n"));
                MDrv_SYNC_ProcessWakeup();
            }
            #endif
            else
            {
                WKDBG(printf("\r\nMODE : NOT SUPPORT\r\n"));
                MDrv_Write2Byte(0x10250A,BackupReg); // Disable ADC
                MDrv_SYNC_KeepStandby();
                #if ENABLE_VGA_JUST_CHECK_SYNC
                msDelayTime(25);
                #endif
            }
        }
        #if ENABLE_VGA_JUST_CHECK_SYNC
        else
        {
            XC_Clear_HVSyncCount();
        }
        #endif
    }

    if ((wPM_WakeUpDevice & PM_WAKEUP_BY_DVI)||(wPM_WakeUpDevice & PM_WAKEUP_BY_DVI1)||(wPM_WakeUpDevice & PM_WAKEUP_BY_DVI2))
    {
        if (gDviClockDetect)
        {
            gDviClockDetect = FALSE;
            msDelayTime(10);
            if(1) //make decision to check dvi clock or not later
                MDrv_DVI_ProcessWakeup();
            else
                MsOS_EnableInterrupt(E_INT_FIQ_DVI_DET);
        }
        else
        {
            MsOS_EnableInterrupt(E_INT_FIQ_DVI_DET);
            MDrv_DVI_ManualSwitchPort();
        }
    }

    // Check MHL
    if (wPM_WakeUpDevice & PM_WAKEUP_BY_MHL)
        MDrv_ProcessMHLWakeup();

    // Check SAR and IR status (keypad wakeup)
    MApp_ProcessUserInput();

    // Check USB
    if (wPM_WakeUpDevice & PM_WAKEUP_BY_USB)
        MDrv_ProcessUSBWakeup();

    // Check CEC
    if (wPM_WakeUpDevice & PM_WAKEUP_BY_CEC)
        msAPI_CEC_Handler();
}

////////////////////////////////////////////////////////////////////////////////
#undef MAPP_WAKEUP_C

