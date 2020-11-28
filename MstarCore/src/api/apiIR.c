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
#include <common.h>
#include <MsTypes.h>
#include <MsIRQ.h>
#include <MsOS.h>
#include <drvIR.h>
#include <drvSAR.h>
#if(ENABLE_MSTAR_BD_MST036B_EDISON_CUS18_ATSC)
#include "IR_HISENSE.h"
#else
#include <IR_MSTAR_DTV.h>
#endif
#include <ShareType.h>
#include <MsDebug.h>

/// MS Return Error
#ifndef MSRET_ERROR
#define MSRET_ERROR     0
#endif
/// MS Return OK
#ifndef MSRET_OK
#define MSRET_OK        1
#endif

#define MAX_ADC_KEY_CHANNEL_NUM 4

#define _PA2VA(x) (MS_U32)MsOS_PA2KSEG1((x))
#define _VA2PA(x) (MS_U32)MsOS_VA2PA((x))

BOOLEAN msAPI_IR_Initialize(void)
{
    UBOOT_TRACE("IN\n");
    static IR_RegCfg tIRRegCfg =
    {
        .u8Ctrl0        = IR_LEADER_CODE_CHECKING_OPTION,
        .u8Ctrl1        = 0x01,
        .u8Clk_mhz      = MST_XTAL_CLOCK_MHZ,
        .u8HdrCode0     = IR_HEADER_CODE0,
        .u8HdrCode1     = IR_HEADER_CODE1,
        .u8CCodeBytes   = 2,
        .u8CodeBits     = 32,  //(32bits==4bytes)
    };
    char* s = getenv(IR_HEADER_CODE0_NAME);
    if (s)
    {
        tIRRegCfg.u8HdrCode0 = simple_strtoul(s, NULL, 16);
    }

    s = getenv(IR_HEADER_CODE1_NAME);
    if (s)
    {
        tIRRegCfg.u8HdrCode1 = simple_strtoul(s, NULL, 16);
    }

    static IR_TimeBnd tIRTimeBnd =
    {
        .tHdr={
            .s16Time = IR_HEADER_CODE_TIME,
            .s8UpBnd = IR_HEADER_CODE_TIME_UB,
            .s8LoBnd = IR_HEADER_CODE_TIME_LB},
        .tOff={
            .s16Time = IR_OFF_CODE_TIME,
            .s8UpBnd = IR_OFF_CODE_TIME_UB,
            .s8LoBnd = IR_OFF_CODE_TIME_LB},
        .tOffRpt={
            .s16Time = IR_OFF_CODE_RP_TIME,
            .s8UpBnd = IR_OFF_CODE_RP_TIME_UB,
            .s8LoBnd = IR_OFF_CODE_RP_TIME_LB},
        .tLg01Hg={
            .s16Time = IR_LOGI_01H_TIME,
            .s8UpBnd = IR_LOGI_01H_TIME_UB,
            .s8LoBnd = IR_LOGI_01H_TIME_LB},
        .tLg0={
            .s16Time = IR_LOGI_0_TIME,
            .s8UpBnd = IR_LOGI_0_TIME_UB,
            .s8LoBnd = IR_LOGI_0_TIME_LB},
        .tLg1={
            .s16Time = IR_LOGI_1_TIME,
            .s8UpBnd = IR_LOGI_1_TIME_UB,
            .s8LoBnd = IR_LOGI_1_TIME_LB}
    };

    IR_RegCfg* pirRegCfg=&tIRRegCfg;
    IR_TimeBnd* pirTimeBnd=&tIRTimeBnd;

    //(0) For debugging
    //printf("MailBox: MDrv_IR_SetDbgLevel\n");
    //MDrv_IR_SetDbgLevel(E_IR_DBGLVL_INFO);
    //(1) Initialization
    flush_cache((MS_U32)pirRegCfg, sizeof(IR_RegCfg));
//    printf("pirRegCfg = 0x%lx \n",pirRegCfg);
//    printf("_VA2PA((MS_U32)pirRegCfg) = 0x%lx \n",_VA2PA((MS_U32)pirRegCfg));
    if(MDrv_IR_Init((IR_RegCfg*)_VA2PA((MS_U32)pirRegCfg))==E_IR_FAIL)
    {
        UBOOT_ERROR("MDrv_IR_Init fails...\n");
        return MSRET_ERROR;
    }
//    printf("msAPI_IR_Initialize3333355555555555543\n");
    //(2) Configure Time Bounds
    flush_cache((MS_U32)pirTimeBnd, sizeof(IR_TimeBnd));
 //       printf("msAPI_IR_Initialize3336663444444444443\n");

    if(MDrv_IR_Config(pirTimeBnd)==E_IR_FAIL)
    {
        UBOOT_ERROR("MDrv_IR_Config fails...\n");
        return MSRET_ERROR;
    }
//    printf("$$$$$[eric] IR Init Finished!\n");
    UBOOT_TRACE("OK\n");

    return MSRET_OK;
}

BOOLEAN msAPI_KeyPad_Initialize(void)
{
    UBOOT_TRACE("IN\n");
    static SAR_RegCfg sarRegCfgCh;
    SAR_RegCfg* psarRegCfgCh=&sarRegCfgCh;

    MS_U8 u8ChEnb[KEYPAD_CHANNEL_SUPPORT]={ENABLE_KPDCHAN_1,ENABLE_KPDCHAN_2,ENABLE_KPDCHAN_3,ENABLE_KPDCHAN_4};
    MS_U8 u8UpBnd[KEYPAD_CHANNEL_SUPPORT]={KEYPAD_CH1_UB,KEYPAD_CH2_UB,KEYPAD_CH3_UB,KEYPAD_CH4_UB};
    MS_U8 u8LoBnd[KEYPAD_CHANNEL_SUPPORT]={KEYPAD_CH1_LB,KEYPAD_CH2_LB,KEYPAD_CH3_LB,KEYPAD_CH4_LB};
    MS_U8 u8ChKey[MAX_ADC_KEY_CHANNEL_NUM][4]={
        {ADC_KEY_1_L0_FLAG,ADC_KEY_1_L1_FLAG,ADC_KEY_1_L2_FLAG,ADC_KEY_1_L3_FLAG}, //mapping keys
        {ADC_KEY_2_L0_FLAG,ADC_KEY_2_L1_FLAG,ADC_KEY_2_L2_FLAG,ADC_KEY_2_L3_FLAG},
        /*{ADC_KEY_2_L0_FLAG,ADC_KEY_2_L1_FLAG,ADC_KEY_2_L2_FLAG,ADC_KEY_2_L3_FLAG} //mapping keys*/
    };
    MS_U8 k,u8Idx,i;

    if(MDrv_SAR_Init()==E_SAR_FAIL)
    {
        UBOOT_ERROR("MDrv_SAR_Init fails\n");
        return MSRET_ERROR;
    }

    char* s = getenv(POWER_KEY_NAME);
    MS_U8 u8PowerKey = (NULL != s) ? simple_strtoul(s, NULL, 16) : IRKEY_DUMY;
    //MS_U8 u8PowerKey = simple_strtoul(s, NULL, 16);
    for(u8Idx=0,k=0;k<KEYPAD_CHANNEL_SUPPORT;k++)
    {
        if(u8ChEnb[k]==ENABLE)
        {
            psarRegCfgCh->u8SARChID = k;
            psarRegCfgCh->u8UpBnd = u8UpBnd[k];
            psarRegCfgCh->u8LoBnd = u8LoBnd[k];
            psarRegCfgCh->u8KeyLevelNum = ADC_KEY_LEVEL;
            psarRegCfgCh->u8KeyThreshold[0] = ADC_KEY_L0;
            psarRegCfgCh->u8KeyThreshold[1] = ADC_KEY_L1;
            psarRegCfgCh->u8KeyThreshold[2] = ADC_KEY_L2;
            psarRegCfgCh->u8KeyThreshold[3] = ADC_KEY_L3;
            psarRegCfgCh->u8KeyCode[0] = u8ChKey[u8Idx][0];
            psarRegCfgCh->u8KeyCode[1] = u8ChKey[u8Idx][1];
            psarRegCfgCh->u8KeyCode[2] = u8ChKey[u8Idx][2];
            psarRegCfgCh->u8KeyCode[3] = u8ChKey[u8Idx][3];

            if (IRKEY_DUMY != u8PowerKey)
            {
                for (i = 0; i < 4; ++i)
                {
                    if (IRKEY_POWER == psarRegCfgCh->u8KeyCode[i])
                    {
                        psarRegCfgCh->u8KeyCode[i] = u8PowerKey;
                    }
                }
            }

            // configure keypad channel
            //MsOS_Dcache_Flush((MS_U32)psarRegCfgCh, sizeof(SAR_RegCfg));
            //MsOS_FlushMemory();
            flush_cache((MS_U32)psarRegCfgCh, sizeof(SAR_RegCfg));
            Chip_Flush_Memory();

            if(MDrv_SAR_Config((SAR_RegCfg*)_VA2PA((MS_U32)psarRegCfgCh))==E_SAR_FAIL)
            {
                UBOOT_ERROR("MDrv_SAR_Config: CH_%d fails\n",u8Idx);
                return MSRET_ERROR;
            }

            if((++u8Idx)>=MAX_ADC_KEY_CHANNEL_NUM)
                break;
        }
    }

    if(MDrv_SAR_Enable(TRUE)==E_SAR_FAIL)
    {
        UBOOT_ERROR("MDrv_SAR_Enable fails\n");
        return MSRET_ERROR;
    }
    UBOOT_TRACE("OK\n");
    return MSRET_OK;
}
