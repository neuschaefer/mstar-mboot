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
// Description: Interrupt Service Routines
//
////////////////////////////////////////////////////////////////////////////////

#define _DRV_ISR_C_

#include <stdio.h>
#include <string.h>
#include "risc32_spr.h"
#include "hwreg.h"
#include "drvGlobal.h"
#include "drvISR.h"
#include "uartdebug.h"


//###########
//
// ISR Functions
//
//##########
static void ProcessCPU0toCPU2Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    MsOS_EnableInterrupt(E_INT_FIQ_8051_TO_BEON);
}

static void ProcessCPU1toCPU2Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

	MsOS_EnableInterrupt(E_INT_FIQ_AEON_TO_BEON);
}

static void MDrv_Sys_DisableWatchDog(void)
{
    MDrv_Write2Byte(0x3008, 0x0000);
    MDrv_Write2Byte(0x300A, 0x0000);
}

static void TimerISR(void)
{
    gTimerCount0++;
    gu8100msTH++;

    // Use a threshold to check the 100 ms. If the threshold
    // is greater or equal than the 100 ms. Increase the 100 ms
    // counter.
    if (gu8100msTH >= 100)
    {
        g100msTimeCount++;
        gu8100msTH = 0;
    }

    //--------------------------------

    if (gTimerCount0%1000==0)
    {
        gSystemTimeCount++;
    }

    //--------------------------------
    //down time counter:
    if ( gTimerDownCount0 > 0 )
        gTimerDownCount0--;

    if ( gTimerDownCount1 > 0 )
        gTimerDownCount1--;
    //-------------------------------

#if (ENABLE_MSTV_UART_DEBUG )
    if (g_Uart0CheckTick)
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            g_bUart0Detected = FALSE;
            g_UartCommand.Index = 0;
        }
    }
#endif

#if(ENABLE_UART2) 
    if (g_Uart2CheckTick)
    {
        --g_Uart2CheckTick;
        if ( g_Uart2CheckTick == 0 )
        {
            g_bUart2Detected = FALSE;
            g_Uart2Command.Index = 0;
        }
    }
#endif
}

//################
//
//  Global API Functions
//
//################
void ProcessSysTrap(MHAL_SavedRegisters *pHalReg, U32 vector)
{
   printf("system trap");

   UNUSED(pHalReg);
   UNUSED(vector);

   MDrv_Sys_DisableWatchDog();
   while(1);
}

void MDrv_ISR_Init(void)
{
    MsOS_AttachInterrupt(E_INT_FIQ_8051_TO_BEON, (InterruptCb)ProcessCPU0toCPU2Isr);
    MsOS_AttachInterrupt(E_INT_FIQ_AEON_TO_BEON, (InterruptCb)ProcessCPU1toCPU2Isr);
}

void MDrv_Timer_ISR_Register(void)
{
    MS_U32 check_timer_status;
    check_timer_status = MsOS_CreateTimer( (TimerCb)TimerISR,
                                                  0,
                                                  1,
                                                  TRUE,
                                                  (char*)"Check timer");
}

void MDrv_Timer_Init(void) // Now support mode 1
{
    gTimerCount0 = 0;
    gTimerDownCount0 = 0;
    gTimerDownCount1 = 0;
    gu8100msTH = 0;
    g_u16ElapsedTimeSecond = 0;
}

void MDrv_Interrupt_Init(void)
{
    MsOS_CPU_UnMaskInterrupt( E_INTERRUPT_FIQ );
    MsOS_CPU_UnMaskInterrupt( E_INTERRUPT_IRQ );
    MsOS_CPU_EnableInterrupt();
}

