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
#include <stdio.h>
#include "assert.h"
#include "risc32.h"//#include "mhal_arch.h"
#include "datatype.h"

typedef unsigned long               MS_U32;
typedef unsigned char               MS_U8;
typedef signed long               MS_S32;
typedef unsigned char               MS_BOOL;
typedef void (*TimerCb)(MS_U32 u32Vector);

volatile static TimerCb timer_isr[2] = {0, 0};
volatile static MS_U32 timer_period[2]={0, 0};
volatile static MS_BOOL gStartTimer[2]={0, 0};
volatile static MS_U32 firsttimer_interval[2]={0, 0};
volatile static MS_U32 firsttimer_interval_old[2]={0, 0};
volatile static MS_BOOL firsttimer_interval_flag[2]={0, 0};
volatile static MS_U32 gsystem_ip_time_ms[2]={0, 0};
extern volatile MS_U32 gsystem_time_ms;
//MS_U8 gtimer_cb_number;
void Timer_firsttime_interval(MS_U32 firsttime_interval, MS_S32 s32TimerId_set);
void Timer_Start_set(MS_BOOL bStartTimer_set, MS_S32 s32TimerId_set);
void Timer_Period_Register(MS_U32 periodCb, MS_S32 s32TimerId_set);
MS_S32 Timer_IRQ_Register(void *ptCb);
void Timer_IRQ_Delete(MS_S32 timer_ld);
void  ProcessTimer0Isr( MHAL_SavedRegisters *pHalReg, U32 vector );

void Timer_firsttime_interval(MS_U32 firsttime_interval, MS_S32 s32TimerId_set)
{
    firsttimer_interval_flag[s32TimerId_set]=0;
    firsttimer_interval_old[s32TimerId_set]=0;
    gsystem_ip_time_ms[s32TimerId_set]=0;
    firsttimer_interval[s32TimerId_set]=firsttime_interval;

}
void Timer_Start_set(MS_BOOL bStartTimer_set, MS_S32 s32TimerId_set)
{
    gStartTimer[s32TimerId_set]=bStartTimer_set;
}
void Timer_Period_Register(MS_U32 periodCb, MS_S32 s32TimerId_set)
{

    //printf("Timer size of = %lx\n",sizeof(timer_period));
    if(s32TimerId_set>=2)
    {
        printf("Not enough buffer to set period!!!!!\n");
    }
    if(periodCb==0)
    {
        periodCb=1;
    }
    timer_period[s32TimerId_set]=periodCb;

}
MS_S32 Timer_IRQ_Register(void *ptCb)
{
    int i;
    //printf("Timer size of = %lx\n",sizeof(timer_isr));

    for(i=0;i<=(sizeof(timer_isr)>>2);i++)
    {
        if(i==((sizeof(timer_isr))>>2))
        {
            printf("Not enough buffer to attach timerCB!!!!!\n");
            ASSERT(0);
        }
        if(timer_isr[i]==0)
        {
            timer_isr[i]=(TimerCb)ptCb;
            break;
        }
        timer_period[i] = 1; //set default value
    }
    return i;
}

void Timer_IRQ_Delete(MS_S32 timer_ld)
{
    if(timer_isr[timer_ld]!=0)
    {
        timer_isr[timer_ld]=0;
        gsystem_ip_time_ms[timer_ld]=0;
        timer_period[timer_ld] = 1; //set default value
    }
}

void  ProcessTimer0Isr( MHAL_SavedRegisters *pHalReg, U32 vector )
{
    int i;
    UNUSED(pHalReg);
    UNUSED(vector);

    gsystem_time_ms++;
    for(i=0;i<2;i++)
        {
        if (timer_isr[i])
            {
             if((firsttimer_interval_flag[i]==0)&&(gStartTimer[i]==1))
                {
                if(firsttimer_interval_old[i]==0)
                    {
                        firsttimer_interval_old[i]=gsystem_time_ms;
                    }
                if(((gsystem_time_ms<firsttimer_interval_old[i])&&((0xFFFFFFFF-firsttimer_interval_old[i]+gsystem_time_ms)>=firsttimer_interval[i]))||((gsystem_time_ms>firsttimer_interval_old[i])&&((gsystem_time_ms-firsttimer_interval_old[i])>=firsttimer_interval[i])))
                    {
                        firsttimer_interval_flag[i]=1;
                    }
                if(firsttimer_interval[i]==0)
                    {
                        firsttimer_interval_flag[i]=1;
                    }
                }
                if(((gsystem_ip_time_ms[i]%timer_period[i])==0)&&(gStartTimer[i]==1)&&(firsttimer_interval_flag[i]==1))
                    {
                        timer_isr[i](0);
                    }
                if((gStartTimer[i]==1)&&(firsttimer_interval_flag[i]==1))
                    {
                        gsystem_ip_time_ms[i]++;
                    }
            }
        }
}
