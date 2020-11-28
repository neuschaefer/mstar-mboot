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

#define _MSKEYPAD_C_

#include <common.h>
#include <MsTypes.h>
#include <ShareType.h>

#include <MsUboot.h>
#include "msKeypad.h"
#include "drvSAR.h"

#include <bootlogo/MsPoolDB.h>
#include <stdlib.h>
#include "keypad_type.h"

#if (CONFIG_BINARY_RELEASE == 1)
#include <MsMBootConfig.h>
#endif

static SAR_KpdRegCfg_t m_KpdConfig[MAXKEYPADCH] = {
#include "keypad.h"
};

#if 1//(CONFIG_COMMANDS & CFG_KEYPAD)
#define ONE_MS_TIME_VALUE     ((1000 * CONFIG_SYS_HZ) / 1000000)

static U8 KeyPadCheckCount, PreviousCMD, PressKey;
static U32 KeyPadTimePeriod, g100msTimeCount,g1msTimeCount;
static U32 _gKeypadTimeTick;

static U8 Keypad_Channel[ADC_KEY_CHANNEL_NUM];

#ifndef ADC_KEY_LEVEL_TOLERANCE
#define ADC_KEY_LEVEL_TOLERANCE        0xFF
#endif

/*
#ifndef ADC_KEY_L4
#define ADC_KEY_L4 0xFF
#endif
#ifndef ADC_KEY_L5
#define ADC_KEY_L5 0xFF
#endif
#ifndef ADC_KEY_L6
#define ADC_KEY_L6 0xFF
#endif
#ifndef ADC_KEY_L7
#define ADC_KEY_L7 0xFF
#endif

#ifndef ADC_KEY_3_L0
#define ADC_KEY_3_L0 0x00
#endif
#ifndef ADC_KEY_3_L1
#define ADC_KEY_3_L1 0x00
#endif
#ifndef ADC_KEY_3_L2
#define ADC_KEY_3_L2 0x00
#endif
#ifndef ADC_KEY_3_L3
#define ADC_KEY_3_L3 0x00
#endif
#ifndef ADC_KEY_3_L4
#define ADC_KEY_3_L4 0x00
#endif
#ifndef ADC_KEY_3_L5
#define ADC_KEY_3_L5 0x00
#endif
#ifndef ADC_KEY_3_L6
#define ADC_KEY_3_L6 0x00
#endif
#ifndef ADC_KEY_3_L7
#define ADC_KEY_3_L7 0x00
#endif

#ifndef ADC_KEY_4_L0
#define ADC_KEY_4_L0 0x00
#endif
#ifndef ADC_KEY_4_L1
#define ADC_KEY_4_L1 0x00
#endif
#ifndef ADC_KEY_4_L2
#define ADC_KEY_4_L2 0x00
#endif
#ifndef ADC_KEY_4_L3
#define ADC_KEY_4_L3 0x00
#endif
#ifndef ADC_KEY_4_L4
#define ADC_KEY_4_L4 0x00
#endif
#ifndef ADC_KEY_4_L5
#define ADC_KEY_4_L5 0x00
#endif
#ifndef ADC_KEY_4_L6
#define ADC_KEY_4_L6 0x00
#endif
#ifndef ADC_KEY_4_L7
#define ADC_KEY_4_L7 0x00
#endif

#ifndef ADC_KEY_1_L3_FLAG
#define ADC_KEY_1_L3_FLAG 0x00
#endif
#ifndef ADC_KEY_1_L4_FLAG
#define ADC_KEY_1_L4_FLAG 0x00
#endif
#ifndef ADC_KEY_1_L5_FLAG
#define ADC_KEY_1_L5_FLAG 0x00
#endif
#ifndef ADC_KEY_1_L6_FLAG
#define ADC_KEY_1_L6_FLAG 0x00
#endif
#ifndef ADC_KEY_1_L7_FLAG
#define ADC_KEY_1_L7_FLAG 0x00
#endif

#ifndef ADC_KEY_2_L3_FLAG
#define ADC_KEY_2_L3_FLAG 0x00
#endif
#ifndef ADC_KEY_2_L4_FLAG
#define ADC_KEY_2_L4_FLAG 0x00
#endif
#ifndef ADC_KEY_2_L5_FLAG
#define ADC_KEY_2_L5_FLAG 0x00
#endif
#ifndef ADC_KEY_2_L6_FLAG
#define ADC_KEY_2_L6_FLAG 0x00
#endif
#ifndef ADC_KEY_2_L7_FLAG
#define ADC_KEY_2_L7_FLAG 0x00
#endif

#ifndef ADC_KEY_3_L0_FLAG
#define ADC_KEY_3_L0_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L1_FLAG
#define ADC_KEY_3_L1_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L2_FLAG
#define ADC_KEY_3_L2_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L3_FLAG
#define ADC_KEY_3_L3_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L4_FLAG
#define ADC_KEY_3_L4_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L5_FLAG
#define ADC_KEY_3_L5_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L6_FLAG
#define ADC_KEY_3_L6_FLAG 0x00
#endif
#ifndef ADC_KEY_3_L7_FLAG
#define ADC_KEY_3_L7_FLAG 0x00
#endif

#ifndef ADC_KEY_4_L0_FLAG
#define ADC_KEY_4_L0_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L1_FLAG
#define ADC_KEY_4_L1_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L2_FLAG
#define ADC_KEY_4_L2_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L3_FLAG
#define ADC_KEY_4_L3_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L4_FLAG
#define ADC_KEY_4_L4_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L5_FLAG
#define ADC_KEY_4_L5_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L6_FLAG
#define ADC_KEY_4_L6_FLAG 0x00
#endif
#ifndef ADC_KEY_4_L7_FLAG
#define ADC_KEY_4_L7_FLAG 0x00
#endif
*/

#if !defined(CONFIG_BINARY_RELEASE)
static U8 tADCKeyLevel[MAXKEYPADCH][8];
#endif

static U8 tADCKeyFlag[MAXKEYPADCH][8];

/*
#if !defined(CONFIG_BINARY_RELEASE)
static U8 tADCKeyLevel[KEYPAD_CHANNEL_SUPPORT][8] = 
{
  {ADC_KEY_1_L0,ADC_KEY_1_L1,ADC_KEY_1_L2,ADC_KEY_1_L3,ADC_KEY_1_L4,ADC_KEY_1_L5,ADC_KEY_1_L6,ADC_KEY_1_L7},
  {ADC_KEY_2_L0,ADC_KEY_2_L1,ADC_KEY_2_L2,ADC_KEY_2_L3,ADC_KEY_2_L4,ADC_KEY_2_L5,ADC_KEY_2_L6,ADC_KEY_2_L7},
  {ADC_KEY_3_L0,ADC_KEY_3_L1,ADC_KEY_3_L2,ADC_KEY_3_L3,ADC_KEY_3_L4,ADC_KEY_3_L5,ADC_KEY_3_L6,ADC_KEY_3_L7},
  {ADC_KEY_4_L0,ADC_KEY_4_L1,ADC_KEY_4_L2,ADC_KEY_4_L3,ADC_KEY_4_L4,ADC_KEY_4_L5,ADC_KEY_4_L6,ADC_KEY_4_L7},
};
#endif

static U8 tADCKeyFlag[KEYPAD_CHANNEL_SUPPORT][8] = 
{
  {ADC_KEY_1_L0_FLAG,ADC_KEY_1_L1_FLAG,ADC_KEY_1_L2_FLAG,ADC_KEY_1_L3_FLAG,ADC_KEY_1_L4_FLAG,ADC_KEY_1_L5_FLAG,ADC_KEY_1_L6_FLAG,ADC_KEY_1_L7_FLAG},
  {ADC_KEY_2_L0_FLAG,ADC_KEY_2_L1_FLAG,ADC_KEY_2_L2_FLAG,ADC_KEY_2_L3_FLAG,ADC_KEY_2_L4_FLAG,ADC_KEY_2_L5_FLAG,ADC_KEY_2_L6_FLAG,ADC_KEY_2_L7_FLAG},
  {ADC_KEY_3_L0_FLAG,ADC_KEY_3_L1_FLAG,ADC_KEY_3_L2_FLAG,ADC_KEY_3_L3_FLAG,ADC_KEY_3_L4_FLAG,ADC_KEY_3_L5_FLAG,ADC_KEY_3_L6_FLAG,ADC_KEY_3_L7_FLAG},
  {ADC_KEY_4_L0_FLAG,ADC_KEY_4_L1_FLAG,ADC_KEY_4_L2_FLAG,ADC_KEY_4_L3_FLAG,ADC_KEY_4_L4_FLAG,ADC_KEY_4_L5_FLAG,ADC_KEY_4_L6_FLAG,ADC_KEY_4_L7_FLAG},
};
*/
static void msKeypad_Config_Struct(void);
static void msKeypad_Reset100msTimeCount(void);
static void msKeypad_Update100msTimeCount(void);
static U32 msKeypad_Get100msTimeCount(void);
static BOOLEAN msKeypad_AllocChan(U8 u8KpdCh);
static U8 msKeypad_GetChanIndex(U8 u8KpdCh);
static BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag);

static void msKeypad_Config_Struct(void)
{
   memset (tADCKeyFlag, 0x00, sizeof(char)*32);
   int i = 0;
   int j = 0;

   for (i = 0; i < MAXKEYPADCH; i++)
   {
       for (j = 0; j < 8; j++)
       {

           tADCKeyFlag[i][j] = m_KpdConfig[i].u8KeyCode[j];
       }
   }

#if !defined(CONFIG_BINARY_RELEASE)
   memset (tADCKeyLevel, 0x00, sizeof(char)*32);
   for (i = 0; i < MAXKEYPADCH; i++)
   {
       for (j = 0; j < 8; j++)
       {

           tADCKeyLevel[i][j] = m_KpdConfig[i].u8KeyThreshold[j];
       }
   }
#endif
}

static void msKeypad_Reset100msTimeCount(void)
{
    g100msTimeCount = 0;
    g1msTimeCount = 0;
    _gKeypadTimeTick = get_ticks();
}

static void msKeypad_Update100msTimeCount(void)
{
    U32 u32CurTicks = get_ticks();
    if ((u32CurTicks - _gKeypadTimeTick)>=ONE_MS_TIME_VALUE)
    {
        g1msTimeCount += ((u32CurTicks - _gKeypadTimeTick)/ONE_MS_TIME_VALUE);

        _gKeypadTimeTick = get_ticks();
        if (g1msTimeCount>=100)
        {
            U32 u32Temp = g1msTimeCount;
            g1msTimeCount = (u32Temp%100);
            g100msTimeCount+=(u32Temp/100);
        }
    }
}

static U32 msKeypad_Get100msTimeCount(void)
{
    return g100msTimeCount;
}

static BOOLEAN msKeypad_AllocChan(U8 u8KpdCh)
{
    static U8 u8KpdChIdx=0;

    if(u8KpdChIdx>=ADC_KEY_CHANNEL_NUM)
    {
        printf("[msKeypad_Init]: Allocated channel number > %d !!!\n",ADC_KEY_CHANNEL_NUM);
        return MSRET_ERROR;
    }
    Keypad_Channel[u8KpdChIdx++]=u8KpdCh;
    return MSRET_OK;
}

static U8 msKeypad_GetChanIndex(U8 u8KpdCh)
{
    U8 k;

    for(k=0;k<ADC_KEY_CHANNEL_NUM;k++)
    {
        if(Keypad_Channel[k]==u8KpdCh)
            return Keypad_Channel[k];
    }
    return 0xFF;
}

/******************************************************************************/
///Keypad get ADC Channel value
///@param pkey \b IN ADC Channel
///@param pflag \b IN Pointer to the ADC Channel value
/******************************************************************************/
U8 msKeypad_Get_ADC_Channel(U8 Channel, U8 *pvalue)
{
#if 1
	*pvalue=MDrv_SAR_Adc_GetValue(Channel);
	return 0;
#else
    U8 u8Status = 0;

    switch ( Channel )
    {
        case KEYPAD_ADC_CHANNEL_1:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT1) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_2:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT2) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_3:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT3) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_4:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT4) & MASK_SAR_ADCOUT;
             break;
        default:
            u8Status = 1;
            *pvalue = 0xFF;
            break;
    }

    return u8Status;
#endif
}

static BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag)
{
#if (CONFIG_BINARY_RELEASE == 1)
	U8 tADCKeyLevel[KEYPAD_CHANNEL_SUPPORT][8] = 
	{
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		},
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		},
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		},
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		}
	};
#ifdef ADC_KEY_LEVEL
#undef ADC_KEY_LEVEL
#endif
	U8 ADC_KEY_LEVEL = mboot_config.adc_key_level_num;
#endif
    U8 i, j, KEY_LV[ADC_KEY_LEVEL], Key_Value, *Keymapping=NULL;
    U8 u8ChIdx=0;

    *pkey = 0xFF;
    *pflag = 0;

    for(i=0; i<ADC_KEY_LEVEL; i++)
        KEY_LV[i] = 0;

    u8ChIdx = msKeypad_GetChanIndex(Channel);
    
    if(u8ChIdx == 0xFF)
        return MSRET_ERROR; 
    
    Keymapping = (U8*) tADCKeyFlag[u8ChIdx];

    for ( i = 0; i < KEYPAD_STABLE_NUM; i++ )
    {
        msKeypad_Get_ADC_Channel(u8ChIdx,&Key_Value);
        for (j=0;j<ADC_KEY_LEVEL;j++)
        {
            if (Key_Value < tADCKeyLevel[u8ChIdx][j])
            {
            	if((tADCKeyLevel[u8ChIdx][j]-Key_Value)<=ADC_KEY_LEVEL_TOLERANCE)
        		{
	                KEY_LV[j]++;
	                break;
        		}
            }
        }
    }

    for(i=0; i<ADC_KEY_LEVEL; i++)
    {
        if(KEY_LV[i] > KEYPAD_STABLE_NUM_MIN)
        {
            PressKey = TRUE;
            *pkey = *(Keymapping+i);
            if (PreviousCMD != *pkey)
            {
                PreviousCMD = *pkey;
                KeyPadCheckCount = 0;
                return MSRET_OK;
            }
            else
            {
                if (KeyPadCheckCount < KEYPAD_KEY_VALIDATION)
                {
                   KeyPadCheckCount++;
                    return MSRET_ERROR;
                }
                else if (KeyPadCheckCount == KEYPAD_KEY_VALIDATION)
                {
                    KeyPadCheckCount++;
                    msKeypad_Reset100msTimeCount();
                    KeyPadTimePeriod = msKeypad_Get100msTimeCount();
                    return MSRET_OK;
                }

                msKeypad_Update100msTimeCount();
                if (KeyPadCheckCount == KEYPAD_REPEAT_KEY_CHECK)    //3+2
                {
                    if (msKeypad_Get100msTimeCount() > KeyPadTimePeriod + KEYPAD_REPEAT_PERIOD/3)
                    {
                        KeyPadTimePeriod = msKeypad_Get100msTimeCount();
                        KeyPadCheckCount = KEYPAD_REPEAT_KEY_CHECK_1;
                        *pflag = 0x01;
                    }
                    else
                    {
                        *pkey = 0xFF;
                        *pflag = 0x01;
                    }
                    return MSRET_OK;
                }
                else if (KeyPadCheckCount == KEYPAD_REPEAT_KEY_CHECK_1) //3+3
                {
                    if (msKeypad_Get100msTimeCount() > KeyPadTimePeriod)
                    {
                        KeyPadTimePeriod = msKeypad_Get100msTimeCount();
                        KeyPadCheckCount = KEYPAD_REPEAT_KEY_CHECK_1;
                        *pflag = 0x01;
                    }
                    else
                    {
                        *pkey = 0xFF;
                        *pflag = 0x01;
                    }
                    return MSRET_OK;
                }

                if (msKeypad_Get100msTimeCount() > KeyPadTimePeriod + KEYPAD_REPEAT_PERIOD)  //if 200ms
                {
                    KeyPadTimePeriod = msKeypad_Get100msTimeCount();
                    KeyPadCheckCount = KEYPAD_REPEAT_KEY_CHECK; //3+2
                    *pflag = 0x01;
                    return MSRET_OK;
                }
                else
                {
                    return MSRET_ERROR;
                }
            }
        }
    }

    if(u8ChIdx == ADC_KEY_LAST_CHANNEL)
    {
        if (PressKey)
            PressKey = FALSE;

        else
            PreviousCMD = 0xFF;
    }
    return MSRET_ERROR;

}

void msKeypad_Init(void)
{
    msKeypad_Config_Struct();

#if ENABLE_KEYPAD_CUST
#if (CONFIG_BINARY_RELEASE == 1)
	U8 tADCKeyLevel[KEYPAD_CHANNEL_SUPPORT][8] = 
	{
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		},
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		},
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		},
		{
			mboot_config.adc_key_level[0],
			mboot_config.adc_key_level[1],
			mboot_config.adc_key_level[2],
			mboot_config.adc_key_level[3],
			mboot_config.adc_key_level[4],
			mboot_config.adc_key_level[5],
			mboot_config.adc_key_level[6],
			mboot_config.adc_key_level[7]
		}
	};
#ifdef ADC_KEY_LEVEL
#undef ADC_KEY_LEVEL
#endif
	U8 ADC_KEY_LEVEL = mboot_config.adc_key_level_num;
#endif
#endif

//    MS_U8 u8ChEnb[KEYPAD_CHANNEL_SUPPORT]={ENABLE_KPDCHAN_1,ENABLE_KPDCHAN_2,ENABLE_KPDCHAN_3,ENABLE_KPDCHAN_4};
//    MS_U8 u8UpBnd[KEYPAD_CHANNEL_SUPPORT]={KEYPAD_CH1_UB,KEYPAD_CH2_UB,KEYPAD_CH3_UB,KEYPAD_CH4_UB};
//    MS_U8 u8LoBnd[KEYPAD_CHANNEL_SUPPORT]={KEYPAD_CH1_LB,KEYPAD_CH2_LB,KEYPAD_CH3_LB,KEYPAD_CH4_LB};


    MS_U8 u8ChEnb[MAXKEYPADCH]={m_KpdConfig[KEYPADCH1].bEnable,
                                m_KpdConfig[KEYPADCH2].bEnable,
                                m_KpdConfig[KEYPADCH3].bEnable,
                                m_KpdConfig[KEYPADCH4].bEnable};

    MS_U8 u8UpBnd[MAXKEYPADCH]={m_KpdConfig[KEYPADCH1].tSARChBnd.u8UpBnd,
                                m_KpdConfig[KEYPADCH2].tSARChBnd.u8UpBnd,
                                m_KpdConfig[KEYPADCH3].tSARChBnd.u8UpBnd,
                                m_KpdConfig[KEYPADCH4].tSARChBnd.u8UpBnd};

    MS_U8 u8LoBnd[MAXKEYPADCH]={m_KpdConfig[KEYPADCH1].tSARChBnd.u8LoBnd,
                                m_KpdConfig[KEYPADCH2].tSARChBnd.u8LoBnd,
                                m_KpdConfig[KEYPADCH3].tSARChBnd.u8LoBnd,
                                m_KpdConfig[KEYPADCH4].tSARChBnd.u8LoBnd};

    MS_U8 u8Idx;

#if ENABLE_KEYPAD_CUST
    //judge if using Customer setting
    MS_U8 u8KeyLevel[KEYPAD_CHANNEL_SUPPORT]={ADC_KEY_LEVEL,ADC_KEY_LEVEL,ADC_KEY_LEVEL,ADC_KEY_LEVEL};
    MS_U8 k,i;
    st_keypad_para kpadPara;    
    U8 u8KpdSelect = 0;
	int ret = 0;

    ret = Read_KeypadParaFromflash(&kpadPara);
    
    u8KpdSelect = kpadPara.u8KeypadSelect;
    
    SAR_RegCfg *kpdCfg = kpadPara.kpdCfg;
    //u8KpdSelect = 0 --> use default setting
    if (u8KpdSelect > 0 && ret > 0)
    { 
        for (i = 0 ; i < MAXKEYPADCH; i++)
        {
            int KpdCusCHID = kpdCfg[i].u8SARChID;

            if (KpdCusCHID >= Kpd_ChID_Offset) //KpadCusCHID > 0 --> enable
            {
                KpdCusCHID = KpdCusCHID - Kpd_ChID_Offset;
                u8ChEnb[KpdCusCHID] = DISABLE;
            } 
            else
            {
                u8ChEnb[KpdCusCHID] = ENABLE;
            }

            u8UpBnd[KpdCusCHID] = kpdCfg[i].u8UpBnd;
            u8LoBnd[KpdCusCHID] = kpdCfg[i].u8LoBnd;
            u8KeyLevel[KpdCusCHID] = kpdCfg[i].u8KeyLevelNum;

            for (k = 0; k < 4; k++)
            {
                tADCKeyLevel[KpdCusCHID][k] = kpdCfg[i].u8KeyThreshold[k];
                tADCKeyFlag[KpdCusCHID][k] = kpdCfg[i].u8KeyCode[k];
            }
            
        }
        
    }
#endif
	//for utopia driver for sar mmio base init
	MDrv_SAR_Kpd_MMIO_Init();

    memset(Keypad_Channel, 0xFF, ADC_KEY_CHANNEL_NUM);

    for(u8Idx=0; u8Idx < MAXKEYPADCH; u8Idx++)
    {
        if(u8ChEnb[u8Idx]==ENABLE)
        {

			MDrv_SAR_Kpd_CfgChannelBound(u8Idx, u8UpBnd[u8Idx], u8LoBnd[u8Idx]);
            switch (u8Idx)
            {
                case 0:
                   // MDrv_WriteByte(REG_SAR1_UPB, u8UpBnd[u8Idx]);
                   // MDrv_WriteByte(REG_SAR1_LOB, u8LoBnd[u8Idx]);
                    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_1);
                    break;

                case 1:
                   // MDrv_WriteByte(REG_SAR2_UPB, u8UpBnd[u8Idx]);
                   // MDrv_WriteByte(REG_SAR2_LOB, u8LoBnd[u8Idx]);
                    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_2);
                    break;

                case 2:
                   // MDrv_WriteByte(REG_SAR3_UPB, u8UpBnd[u8Idx]);
                   // MDrv_WriteByte(REG_SAR3_LOB, u8LoBnd[u8Idx]);
                    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_3);
                    break;
                    
                case 3:
                   // MDrv_WriteByte(REG_SAR4_UPB, u8UpBnd[u8Idx]);
                   // MDrv_WriteByte(REG_SAR4_LOB, u8LoBnd[u8Idx]);
                    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_4);
                    break;
                
            }
        }
    }

    MDrv_WriteByte(REG_SAR_CTRL0, (SAR_MODE_FREERUN|SAR_SIGNAL_CH));
    MDrv_WriteByte(REG_SAR_CTRL1, MDrv_ReadByte(REG_SAR_CTRL1)&(~SAR_ADC_PWRDN));
    MDrv_WriteByte(REG_SAR_CTRL1, MDrv_ReadByte(REG_SAR_CTRL1)|(SAR_ADC_FREERUN));
    MDrv_WriteByte(REG_SAR_SELCH, MDrv_ReadByte(REG_SAR_SELCH)&(~SAR_NCH_EN));
    MDrv_WriteByte(REG_SAR_CKSAMP_PRD, 0x05);   //sample period
#if defined(CONFIG_MSTAR_BD_MST176A_D01A_S_NIKE)
    MDrv_WriteByte(REG_SAR_TEST0, MDrv_ReadByte(REG_SAR_TEST0)|(BIT6));   //Full scale=3.3V
#elif defined(CONFIG_MSTAR_BD_MST049B_10AQV_NIKE) || defined(CONFIG_MSTAR_BD_MST049B_10AQV_NIKE_U)
    MDrv_WriteByte(REG_SAR_TEST0, MDrv_ReadByte(REG_SAR_TEST0)|(BIT6));   //Full scale=3.3V
#else
    //do nothing
#endif

    for(u8Idx=0; u8Idx < MAXKEYPADCH; u8Idx++)
    {
        if(u8ChEnb[u8Idx]==ENABLE)
        {
            switch (u8Idx)
            {
                case 0:
                    //select pad as analog input
                    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH0_MSK));
                    //select pad direction as input mode
                    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH0_MSK));
                    break;

                case 1:
                    //select pad as analog input
                    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH1_MSK));
                    //select pad direction as input mode
                    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH1_MSK));
                    break;
                    
                case 2:
                    //select pad as analog input
                    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH2_MSK));
                    //select pad direction as input mode
                    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH2_MSK));
                    break;
                    
                case 3:
                    //select pad as analog input
                    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH3_MSK));
                    //select pad direction as input mode
                    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH3_MSK));
                    break;
                
            }
        }
    }

    //disable sar mask
    MDrv_WriteByte(REG_SAR_INT_MASK, MDrv_ReadByte(REG_SAR_INT_MASK)|(SAR_INT_MASK));
}

/******************************************************************************/
///Keypad get key value and repeat flag
///@param pkey \b IN return the key value(The same as Irda key value)
///@param pflag \b IN return the repeat flag(1:Repeat)
/******************************************************************************/
BOOLEAN msKeypad_GetKey(U8 *pkey, U8 *pflag)
{
    U8 Channel;

    for (Channel=0; Channel<MAXKEYPADCH; Channel++)
    {
        if (msKeypad_CH_GetKey(Channel, pkey, pflag))
        {
            return MSRET_OK;
        }
    }
    return MSRET_ERROR;
}

#undef _MSKEYPAD_C_
#endif

