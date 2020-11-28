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

#define _MSKEYPAD_C_

//***********************************************************
//              Header Files
//***********************************************************
#include "Board.h"
#include "datatype.h"
#include "hwreg.h"
#include "drvGlobal.h"
#include "drvISR.h"

#include "msIR.h"
#include "msKeypad.h"
//#include "msAPI_Timer.h"

//*******************
//
//  utopia include files
//
//*******************
#include "MsCommon.h"
//#include "drvPM.h"
//#include "SysInit.h"


//***********************************************************
//              Macro Definitions
//***********************************************************
#define CheckWakeupKeyPad(x) ((x == IRKEY_POWER) ||             \
                              (x == IRKEY_CHANNEL_MINUS) ||     \
                              (x == IRKEY_CHANNEL_PLUS) ||      \
                              (x == IRKEY_INPUT_SOURCE))
#define ADCKeyValueOffest       0x0A

//***********************************************************
//              External Veriables
//***********************************************************
extern U32 volatile g100msTimeCount;
extern U32 volatile g100msTimeCount;


//***********************************************************
//              Local Veriables
//***********************************************************
static U8 KeyPadCheckCount, PreviousCMD, PressKey;
static U32 KeyPadTimePeriod;
#if( POWER_KEY_PAD_BY_INTERRUPT )
static U8 u8PwrKeypadIntFlag;
#endif
//Currently Only Support 2 Channel Keypad
static U8 Keypad_Channel[ADC_KEY_CHANNEL_NUM];
const U8 tADCKeyLevel[ADC_KEY_CHANNEL_NUM][8] = 
{
  {ADC_KEY_1_L0,ADC_KEY_1_L1,ADC_KEY_1_L2,ADC_KEY_1_L3,ADC_KEY_1_L4,ADC_KEY_1_L5,ADC_KEY_1_L6,ADC_KEY_1_L7},
  {ADC_KEY_2_L0,ADC_KEY_2_L1,ADC_KEY_2_L2,ADC_KEY_2_L3,ADC_KEY_2_L4,ADC_KEY_2_L5,ADC_KEY_2_L6,ADC_KEY_2_L7}
};
const U8 tADCKeyFlag[ADC_KEY_CHANNEL_NUM][8] = 
{
  {ADC_KEY_1_L0_FLAG,ADC_KEY_1_L1_FLAG,ADC_KEY_1_L2_FLAG,ADC_KEY_1_L3_FLAG,ADC_KEY_1_L4_FLAG,ADC_KEY_1_L5_FLAG,ADC_KEY_1_L6_FLAG,ADC_KEY_1_L7_FLAG},
  {ADC_KEY_2_L0_FLAG,ADC_KEY_2_L1_FLAG,ADC_KEY_2_L2_FLAG,ADC_KEY_2_L3_FLAG,ADC_KEY_2_L4_FLAG,ADC_KEY_2_L5_FLAG,ADC_KEY_2_L6_FLAG,ADC_KEY_2_L7_FLAG}
};


//***********************************************************
//              Global Veriables
//***********************************************************
U8 KeypadCount, KeypadSamplePeriod;


//***********************************************************
//              External Functions
//***********************************************************


//***********************************************************
//              Global Functions Declaration
//***********************************************************
void *memcpy(void *d, void *s, unsigned int n);


//***********************************************************
//              Local Functions Definition
//***********************************************************
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
            return k;
    }
    return 0xFF;
}

static BOOLEAN msKeypad_CH_GetKey(U8 Channel, U8 *pkey, U8* pflag)
{
        U8 i, j, KEY_LV[ADC_KEY_LEVEL], Key_Value, *Keymapping=NULL;
        U8 u8ChIdx=0;
        U8 u8CHLVLs[KEYPAD_CHANNEL_SUPPORT]={ADC_CH1_LEVELS,ADC_CH2_LEVELS,ADC_CH3_LEVELS,ADC_CH4_LEVELS};
        *pkey = 0xFF;
        *pflag = 0;

#if( POWER_KEY_PAD_BY_INTERRUPT )
        if (u8PwrKeypadIntFlag){
            u8PwrKeypadIntFlag = FALSE;
            *pkey = IRKEY_POWER;
            return MSRET_OK;
        }
#endif


        for(i=0; i<ADC_KEY_LEVEL; i++)
            KEY_LV[i] = 0;
    
        u8ChIdx = msKeypad_GetChanIndex(Channel);
        if(u8ChIdx<ADC_KEY_CHANNEL_NUM)
            Keymapping = (U8*)tADCKeyFlag[u8ChIdx];
        else
            return MSRET_ERROR;
        for ( i = 0; i < KEYPAD_STABLE_NUM; i++ )
        {
            msKeypad_Get_ADC_Channel(Channel,&Key_Value);
            for (j=0;j<u8CHLVLs[Channel];j++)
            {
#if 0//((MS_BOARD_TYPE_SEL == BD_MST004B_20AVS_10306)||(MS_BOARD_TYPE_SEL == BD_MST006B_10AVS_10315) ||(MS_BOARD_TYPE_SEL == BD_MST6M182VL))
                if(abs(Key_Value - tADCKeyLevel[u8ChIdx][j]) < ADCKeyValueOffest)
#else                    
                if (Key_Value < tADCKeyLevel[u8ChIdx][j])
#endif               
                {
                    //printf("Key_Value=%02X\n",Key_Value);
                    KEY_LV[j]++;
                    break;
                }
            }
        }
        
        for(i=0; i<u8CHLVLs[Channel]; i++)
        {
            if(KEY_LV[i] >= KEYPAD_STABLE_NUM_MIN)
            {
                PressKey = TRUE;
                *pkey = *(Keymapping+i);
                //printf("CH[%d]=%02X\n",Channel,*pkey);
                if (PreviousCMD != *pkey)
                {
                    PreviousCMD = *pkey;
                    KeyPadCheckCount = 0;
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
                        KeyPadTimePeriod = g100msTimeCount;
                        return MSRET_OK;
                    }

                    if (KeyPadCheckCount == KEYPAD_REPEAT_KEY_CHECK)    //3+2
                    {
                        if (g100msTimeCount > KeyPadTimePeriod + KEYPAD_REPEAT_PERIOD/3)
                        {
                            KeyPadTimePeriod = g100msTimeCount;
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
                        if (g100msTimeCount > KeyPadTimePeriod)
                        {
                            KeyPadTimePeriod = g100msTimeCount;
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

                    if (g100msTimeCount > KeyPadTimePeriod + KEYPAD_REPEAT_PERIOD)  //if 700ms
                    {
                        KeyPadTimePeriod = g100msTimeCount;
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


//***********************************************************
//              Global Functions Definition
//***********************************************************
void *memcpy(void *d, void *s, unsigned int n)
{
    char *dest = (char*)d;
    char *src = (char*)s;

    while (n-- > 0)
    {
        *dest++ = *src++;
    }
    return d;
}

void msKeypad_Init(void)
{

  #if(ENABLE_KPDCHAN_1==ENABLE)//channel 1
    MDrv_WriteByte(REG_SAR1_UPB, KEYPAD_CH1_UB);
    MDrv_WriteByte(REG_SAR1_LOB, KEYPAD_CH1_LB);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_1);
  #endif
  
  #if(ENABLE_KPDCHAN_2==ENABLE)//channel 2
    MDrv_WriteByte(REG_SAR2_UPB, KEYPAD_CH2_UB);
    MDrv_WriteByte(REG_SAR2_LOB, KEYPAD_CH2_LB);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_2);
  #endif
  
  #if(ENABLE_KPDCHAN_3==ENABLE)//channel 3
    MDrv_WriteByte(REG_SAR3_UPB, KEYPAD_CH3_UB);
    MDrv_WriteByte(REG_SAR3_LOB, KEYPAD_CH3_LB);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_3);
  #endif
  
  #if(ENABLE_KPDCHAN_4==ENABLE)//channel 4
    MDrv_WriteByte(REG_SAR4_UPB, KEYPAD_CH4_UB);
    MDrv_WriteByte(REG_SAR4_LOB, KEYPAD_CH4_LB);
    msKeypad_AllocChan(KEYPAD_ADC_CHANNEL_4);
  #endif

    MDrv_WriteByte(REG_SAR_CTRL0, (SAR_MODE_FREERUN|SAR_SIGNAL_CH));
    MDrv_WriteByte(REG_SAR_CTRL0, MDrv_ReadByte(REG_SAR_CTRL0)&(~SAR_DIGITAL_PWRDN));
    MDrv_WriteByte(REG_SAR_CTRL1, MDrv_ReadByte(REG_SAR_CTRL1)&(~SAR_ADC_PWRDN));
    MDrv_WriteByte(REG_SAR_CTRL1, MDrv_ReadByte(REG_SAR_CTRL1)|(SAR_ADC_FREERUN));
    MDrv_WriteByte(REG_SAR_SELCH, MDrv_ReadByte(REG_SAR_SELCH)|(SAR_NCH_EN));
    MDrv_WriteByte(REG_SAR_CKSAMP_PRD, 0x05);   //sample period

  #if(ENABLE_KPDCHAN_1==ENABLE)//channel 1
    //select pad as analog input
    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH0_MSK));
    //select pad direction as input mode
    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH0_MSK));
  #endif    

  #if(ENABLE_KPDCHAN_2==ENABLE)//channel 2
    //select pad as analog input
    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH1_MSK));
    //select pad direction as input mode
    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH1_MSK));
  #endif    

  #if(ENABLE_KPDCHAN_3==ENABLE)//channel 3
    //select pad as analog input
    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH2_MSK));
    //select pad direction as input mode
    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH2_MSK));
  #endif    

  #if(ENABLE_KPDCHAN_4==ENABLE)//channel 4
    //select pad as analog input
    MDrv_WriteByte(REG_SAR_AISEL, MDrv_ReadByte(REG_SAR_AISEL)|(SAR_AISEL_CH3_MSK));
    //select pad direction as input mode
    MDrv_WriteByte(REG_SAR_GPIOOEN, MDrv_ReadByte(REG_SAR_GPIOOEN)|(SAR_GPIOOEN_CH3_MSK));
  #endif

    //disable sar mask 
    MDrv_WriteByte(REG_SAR_INT_MASK, MDrv_ReadByte(REG_SAR_INT_MASK)|(SAR_INT_MASK));
    
//    printf("sar input test... \r\n");
}

#if( POWER_KEY_PAD_BY_INTERRUPT )
U8 msKeypad_Get_PwrKey_IntFlag(void)
{
    return u8PwrKeypadIntFlag;
}

void msKeypad_Set_PwrKey_IntFlag(U8 u8Val)
{
    u8PwrKeypadIntFlag = u8Val;
}
#endif

/******************************************************************************/
///Keypad get ADC Channel value
///@param pkey \b IN ADC Channel
///@param pflag \b IN Pointer to the ADC Channel value
/******************************************************************************/
U8 msKeypad_Get_ADC_Channel(U8 Channel, U8 *pvalue)
{
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
        case KEYPAD_ADC_CHANNEL_5:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT5) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_6:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT6) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_7:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT7) & MASK_SAR_ADCOUT;
            break;
        case KEYPAD_ADC_CHANNEL_8:
            *pvalue = MDrv_ReadByte(REG_SAR_ADCOUT8) & MASK_SAR_ADCOUT;
             break;
        default:
            u8Status = 1;
            *pvalue = 0xFF;
            break;
    }

    return u8Status;
}

/******************************************************************************/
///Keypad get key value and repeat flag
///@param pkey \b IN return the key value(The same as Irda key value)
///@param pflag \b IN return the repeat flag(1:Repeat)
/******************************************************************************/
BOOLEAN msKeypad_GetKey(U8 *pkey, U8 *pflag)
{
    U8 Channel;

    for (Channel=0; Channel<KEYPAD_CHANNEL_SUPPORT; Channel++)
    {
        if (msKeypad_CH_GetKey(Channel, pkey, pflag))
        {
            return MSRET_OK;
        }
    }
    return MSRET_ERROR;
}

BOOLEAN msKeypad_CheckFactoryModeKey(void)
{
    U8 Channel,u8TwoKeyPressed=0;
    U8 u8Key,u8Flag;
    U8 u8Temp[2];

    for (Channel=0; Channel<ADC_KEY_CHANNEL_NUM; Channel++)
    {
        if (msKeypad_CH_GetKey(Channel, &u8Key, &u8Flag))
        {
            u8TwoKeyPressed++;
            u8Temp[Channel]=u8Key;

        }
    }
    if(u8TwoKeyPressed==2)
    {
        if(u8Temp[0]==IRKEY_UP&&u8Temp[1]==IRKEY_RIGHT)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }

    }
    else
    {
        return FALSE;
    }
}

BOOLEAN MDrv_Power_CheckPowerOnKeyPad(void)
{
    U8 KeypadCHValue;

 #if( POWER_KEY_PAD_BY_INTERRUPT )
    if(msKeypad_Get_PwrKey_IntFlag())
    {
        msKeypad_Set_PwrKey_IntFlag(FALSE);
        return TRUE;
    }
#endif

    KeypadSamplePeriod++;

    if(KeypadSamplePeriod > 20)
    {
        KeypadSamplePeriod = 0;
        KeypadCount = 0;
    }
    KeypadCHValue = MDrv_ReadByte(REG_SAR_ADCOUT1);

    if(CheckWakeupKeyPad(ADC_KEY_1_L0_FLAG))
    {
        if (KeypadCHValue <= ADC_KEY_1_L0)
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L1_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_1_L0) &&
            (KeypadCHValue <= ADC_KEY_1_L1))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L2_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_1_L1) &&
            (KeypadCHValue <= ADC_KEY_1_L2))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_1_L3_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_1_L2) &&
            (KeypadCHValue <= ADC_KEY_1_L3))
            KeypadCount++;
    }

    KeypadCHValue = MDrv_ReadByte(REG_SAR_ADCOUT2);

    if(CheckWakeupKeyPad(ADC_KEY_2_L0_FLAG))
    {
        if (KeypadCHValue <= ADC_KEY_2_L0)
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L1_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_2_L0) &&
            (KeypadCHValue <= ADC_KEY_2_L1))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L2_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_2_L1) &&
            (KeypadCHValue <= ADC_KEY_2_L2))
            KeypadCount++;
    }
    if(CheckWakeupKeyPad(ADC_KEY_2_L3_FLAG))
    {
        if ((KeypadCHValue > ADC_KEY_2_L2) &&
            (KeypadCHValue <= ADC_KEY_2_L3))
            KeypadCount++;
    }

    if(KeypadCount > 10)
        return TRUE;
    else
        return FALSE;
}


#undef _MSKEYPAD_C_

