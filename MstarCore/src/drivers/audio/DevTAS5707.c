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

#define DRV_TAS5707_C
#include <display_logo/DevTAS5707.h>
#include <linux/types.h>
#include <apiSWI2C.h>
#define code
//INTERFACE U8 iu8Loop_i,iu8Loop_j;
U8 iu8Loop_i,iu8Loop_j;
U8 gU8EarPhoneInserted;

//#include "chip/MST6990JX.h"
#ifdef HISENSE_SMART_BORAD
#define I2S_Reset_High()                 mdrv_gpio_set_high(148 )
#define I2S_Reset_Low()                  mdrv_gpio_set_low( 148 )
#else //new hisense borad
#define I2S_Reset_High()                 mdrv_gpio_set_high(144 )
#define I2S_Reset_Low()                  mdrv_gpio_set_low( 144 )
#endif

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "Board.h"
//#include "hwreg.h"
//#include "datatype.h"
//#include "drvIIC.h"
//#include "GPIO.h"

//#include "MApp_GlobalVar.h"
//#include "msAPI_Timer.h"

#if  (DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5707)

#define TAS5707_ADDR     0x36
#define TAS5707_BUSID     (((U16) E_I2C_BUS_SYS << 8) | TAS5707_ADDR)

static TAS5707_REGMAP				sm_sRegImage;
#define __ENDTBL__         0xFF


#ifdef TAS_DEBUG
    #define TAS_MSG(x)      x
#else
    #define TAS_MSG(x)
#endif


static BOOLEAN si_dvTAS5707RegsRead(void)
{
    U8* pu8Buf;
    U8  cSubAddr[1];
    cSubAddr[0] = sm_sRegImage.ucAddr;
    pu8Buf = sm_sRegImage.sDatas;
    return MApi_SWI2C_ReadBytes(TAS5707_BUSID, 1, cSubAddr, sm_sRegImage.ucNumber, pu8Buf);
}



static BOOLEAN si_dvTAS5707RegsWrite(void)
{
    U8 *pu8Buf;
    U8  cSubAddr[1];
    cSubAddr[0] = sm_sRegImage.ucAddr;
    pu8Buf = sm_sRegImage.sDatas;
    return MApi_SWI2C_WriteBytes(TAS5707_BUSID,1,cSubAddr,sm_sRegImage.ucNumber,pu8Buf);
    /*while(sm_sRegImage.ucNumber>0)
    {
        sm_sRegImage.ucNumber--;
        pu8Buf[0] = sm_sRegImage.sDatas[i];
        result=MApi_SWI2C_WriteBytes(TAS5707_BUSID,1,
                                    cSubAddr,
                                    1,
                                    pu8Buf);
        i++;
    }
    return result;*/
}



code TAS5707_REGMAP DrvTas5707InitTbl1[] =
{
	// Addr  Count   DataArrary
//wait 50ms here to let part acquiring lock
//01	(Below) 	DRC energy time(2ms)
{0x3A,  0x08,    {0x00, 0x01, 0x53,0x8F, 0x00, 0x7D, 0x2F ,0xD2}},
//01	(Below) 	DRC attack time(1ms)
{0x3B,  0x08,    {0x00, 0x02, 0xA3, 0x9A, 0x00, 0x7D, 0x2F, 0xD2}},
//01	(Below) 	DRC decay time(100ms)
{0x3C,  0x08,    {0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B}},
//01	(Below) 	DRC threshold 1(-9.5dB��8.8W,THD+N=8.747%)
{0x40,  0x04,    {0xFD, 0xB5, 0x36, 0xF2}},
//01	(Below) 	DRC compression ratio��100��
{0x41,  0x04,    {0x03, 0x81, 0x47, 0xAF}},
//01	(Below) 	DRC offset��0��
{0x42,  0x04,    {0x00, 0x08, 0x42, 0x10}},
//01	(Below) 	DRC control
{0x46,  0x04,    {0x00, 0x00, 0x00, 0x01}},
//01	(Below) 	Bank switch control ��no automatic bank switching)
{0x50,  0x04,    {0x0F, 0x70, 0x80, 0x00}},
//01	(Below) 	Input Mux Register(BD mode)
{0x20,  0x04,    {0x00, 0x89, 0x77, 0x7A}},
//01	(Below)	PWM Output MUX Register (Note: Writes to this register affect Inter-Channel Delay)
{0x25,  0x04,    {0x01, 0x13, 0x02, 0x45}},
{0x07,  0x01,   {0x10}},	//Master Volume Register (0xFF = Mute)
{0x08,  0x01,   {0x30}},	//Channel 1 Volume
{0x09,  0x01,   {0x30}},	//Channel 2 Volume
{0x06,  0x01,   {0x00}},	//Soft Mute Register (mute off)
{0x03,  0x01,   {0xA0}},	//System Control Register 1(opt.)
{0x04,  0x01,   {0x05}},	//Serial Data Interface Register
{0x05,  0x01,   {0x00}},	//System Control Register 2(exit hard mute)
{0x0E,  0x01,   {0x91}},	//Micro Register(opt.)
{0x10,  0x01,   {0x02}},	//Modulation Limit(opt.)
{0x1A,  0x01,   {0x0A}},	//Split Capacitor Charge Period(opt.)
{0x1C,  0x01,   {0x02}},	//Back-end Error Register(opt.)
{0x11,  0x01,   {0xB8}},	//Inter-Channel Delay Channel 1
{0x12,  0x01,   {0x60}},	//Inter-Channel Delay Channel 2
{0x13,  0x01,   {0xA0}},	//Inter-Channel Delay Channel 3
{0x14,  0x01,   {0x48}},	//Inter-Channel Delay Channel 4
{__ENDTBL__,  0x00,   {0x00}},

};


BOOLEAN Drv_TAS5707_WRITE_DATAS(U8 ucSubAddr, U8 ucCnt, U8* pBufs )
{
    //U8* pu8Data;
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = ucSubAddr;
    sm_sRegImage.ucNumber = ucCnt;

    memcpy((U8*)&sm_sRegImage.sDatas[0],pBufs,ucCnt);

    bResult = si_dvTAS5707RegsWrite();

    if(bResult)
	{
        TAS_MSG(printf("\r \n Write 5707 Success!"));
	}
    else
	{
        TAS_MSG(printf("\r \n Write 5707 Fail!"));
	}

    return bResult;
}

BOOLEAN Drv_TAS5707_READ_DATAS(U8 ucSubAddr, U8 ucCnt, U8* pBufs )
{
    //U8* pu8Data;
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = ucSubAddr;
    sm_sRegImage.ucNumber = ucCnt;

    bResult = si_dvTAS5707RegsRead();

    memcpy(pBufs,(U8*)&sm_sRegImage.sDatas[0],ucCnt);

    if(bResult)
    {
        if(ucCnt == 1)
            printf("\r \n READ Data = %x",(U16)sm_sRegImage.sDatas[0]);
        else if(ucCnt == 4)
            printf("\r \n READ Data = %x, %x, %x, %x",(U16)sm_sRegImage.sDatas[0],
            (U16)sm_sRegImage.sDatas[1],(U16)sm_sRegImage.sDatas[2],(U16)sm_sRegImage.sDatas[3]);
        else if(ucCnt == 20){
            printf("\r \n READ Data = ");
            for(iu8Loop_i=0;iu8Loop_i<20;iu8Loop_i++)
            {
                 printf(" %x",(U16)sm_sRegImage.sDatas[iu8Loop_i]);
            }
        }
    }
    else
        printf("\r \n READ 5707 Fail!");

    return bResult;
}
/*void drvTAS5707_MuteSubwoof(BOOLEAN bMute)
{
    U8* pu8Buf;
    U8 u8Temp;

    MDrv_TAS5707_IIC_ReadBytes(TAS5707_BUSID,0x06,1,pu8Buf);
    u8Temp = *pu8Buf;
    sm_sRegImage.ucAddr=0x06;
    sm_sRegImage.ucNumber=1;

    if(bMute)
    {
	    sm_sRegImage.sDatas[0]= u8Temp|BIT5;
    }
    else
    {
    	sm_sRegImage.sDatas[0]= u8Temp&(~BIT5);
    }
    printf("\r\n[sDatas_Value]: %x",(U16)sm_sRegImage.sDatas[0]);
	si_dvTAS5707RegsWrite();
}
*/
void drvTAS5707_HWInit(void)
{

        Audio_Amplifier_ON();
        msAPI_Timer_Delayms(1);
       	I2S_Reset_High();
        msAPI_Timer_Delayms(10);
        I2S_Reset_Low();
        msAPI_Timer_Delayms(10);
        I2S_Reset_High();
}

BOOL drvTAS5707_Is_PowerOn(void)//test if 5707 is poweron
{
    sm_sRegImage.ucAddr=0x1b;
    sm_sRegImage.ucNumber=1;
    sm_sRegImage.sDatas[0]=0;
    return si_dvTAS5707RegsWrite();

}
void drvTAS5707_RegInit(void)
{
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr=0x1b;
    sm_sRegImage.ucNumber=1;
    sm_sRegImage.sDatas[0]=0;
    si_dvTAS5707RegsWrite();
    msAPI_Timer_Delayms(50);

    iu8Loop_i = 0;
    while(1)
	{
    	if(DrvTas5707InitTbl1[iu8Loop_i].ucAddr == __ENDTBL__)
		break;
        sm_sRegImage.ucAddr = DrvTas5707InitTbl1[iu8Loop_i].ucAddr;
        sm_sRegImage.ucNumber = DrvTas5707InitTbl1[iu8Loop_i].ucNumber;
        memcpy((U8*)&sm_sRegImage.sDatas[0],
            (U8*)(&DrvTas5707InitTbl1[iu8Loop_i].sDatas[0]),
            sm_sRegImage.ucNumber);
        bResult=si_dvTAS5707RegsWrite();
	    if(bResult)
		{
	        TAS_MSG(printf("\r \n dai Write 5707 Success!\n"));
		}
	    else
    	{
	        TAS_MSG(printf("\r \n dai Write 5707 Fail!\n"));
    	}
		++iu8Loop_i;
	}
    //drvTAS5707_Subwoof();
    if(bResult)
	{
        printf("\ndrvTAS5707_RegInit-> Success!\n");
		gU8EarPhoneInserted= FALSE;

	}
    else
	{
        printf("\ndrvTAS5707_RegInit->Fail!\n");
		gU8EarPhoneInserted= TRUE;
	}
}

void drvTAS5707_Shutdown(void)
{
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = 0x05;
    sm_sRegImage.ucNumber = 1;
    sm_sRegImage.sDatas[0] = 0x40;

    bResult = si_dvTAS5707RegsWrite();

    if(bResult)
        printf("\ndrvTAS5707_Shutdown-> Success!");
    else
        printf("\ndrvTAS5707_Shutdown-> Fail!");

    msAPI_Timer_Delayms(700);
}
void drvTAS5707_Mute(BOOLEAN bmute)
{
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = 0x05;
    sm_sRegImage.ucNumber = 1;
    if(bmute)
    {
        Audio_Amplifier_OFF();
    	msAPI_Timer_Delayms(20);
        sm_sRegImage.sDatas[0] = 0x60;
    }
    else
    {
        sm_sRegImage.sDatas[0] = 0x00;
    	msAPI_Timer_Delayms(20);
        Audio_Amplifier_ON();
    }
    bResult = si_dvTAS5707RegsWrite();
}

void drvTAS5707_SW_Init(void)
{
#if (MS_BOARD_TYPE_SEL == BD_MST119A_D01A_S_HISENSE)
    U8 * Pstr = NULL;
    U8 DataLength = 0;
    U8 g_ucTas5707RegAddr = 0;
    U8 AmpInitTbl[] =
    {
        //DataLength        Address     DataN       DataN+1...
        // I2C Configuration file for TAS5700x
        1, 0x1B, 0x00,
        // Biquads
        4, 0x50, 0x0F, 0x70, 0x80, 0x00,
        4, 0x20, 0x00, 0x89, 0x77, 0x72,
        4, 0x25, 0x01, 0x13, 0x20, 0x45,

 		20, 0x29, 0x00, 0x7E, 0x82, 0x70, 0x0F, 0x81, 0x7D, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7D, 0x04, 0xE0, 0x00, 0x00, 0x00, 0x00,
		20, 0x2A, 0x00, 0x7E, 0x39, 0xA9, 0x0F, 0x05, 0x88, 0xEA, 0x00, 0x7C, 0x95, 0x6B, 0x00, 0xFA, 0x77, 0x16, 0x0F, 0x85, 0x30, 0xEB,
 		20, 0x2B, 0x00, 0x92, 0x0D, 0x64, 0x0F, 0x51, 0xAE, 0x7F, 0x00, 0x49, 0xAB, 0xD2, 0x00, 0xAE, 0x51, 0x81, 0x0F, 0xA4, 0x46, 0xC9,
 		20, 0x2C, 0x00, 0xBA, 0x7D, 0x1C, 0x0F, 0xB2, 0xBC, 0x64, 0x00, 0x0F, 0x69, 0x81, 0x00, 0x4D, 0x43, 0x9C, 0x0F, 0xB6, 0x19, 0x63,
        20, 0x2D, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        20, 0x2E, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        20, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        20, 0x30, 0x00, 0x7E, 0x82, 0x70, 0x0F, 0x81, 0x7D, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7D, 0x04, 0xE0, 0x00, 0x00, 0x00, 0x00,
		20, 0x31, 0x00, 0x7E, 0x39, 0xA9, 0x0F, 0x05, 0x88, 0xEA, 0x00, 0x7C, 0x95, 0x6B, 0x00, 0xFA, 0x77, 0x16, 0x0F, 0x85, 0x30, 0xEB,
		20, 0x32, 0x00, 0x92, 0x0D, 0x64, 0x0F, 0x51, 0xAE, 0x7F, 0x00, 0x49, 0xAB, 0xD2, 0x00, 0xAE, 0x51, 0x81, 0x0F, 0xA4, 0x46, 0xC9,
		20, 0x33, 0x00, 0xBA, 0x7D, 0x1C, 0x0F, 0xB2, 0xBC, 0x64, 0x00, 0x0F, 0x69, 0x81, 0x00, 0x4D, 0x43, 0x9C, 0x0F, 0xB6, 0x19, 0x63,

        20, 0x34, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        20, 0x35, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        20, 0x36, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // DRCs
        8, 0x3A, 0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B,
        8, 0x3B, 0x00, 0x02, 0xA3, 0x9A, 0x00, 0x7D, 0x2F, 0xD2,
        8, 0x3C, 0x00, 0x00, 0x06, 0xd3, 0x00, 0x7f, 0xf9, 0x2B,
        4, 0x40, 0xFD, 0x97, 0x73, 0x3D,
		4, 0x41, 0x03, 0x81, 0x47, 0xAF,
		4, 0x42, 0x00, 0x08, 0x42, 0x10,
		4, 0x46, 0x00, 0x00, 0x00, 0x01,
        1, 0x07, 0x10,
        1, 0x05, 0x00,
		1, 0x08, 0x30,	//Channel 1 Volume
		1, 0x09, 0x30,	//Channel 2 Volume
		1, 0x06, 0x00,	//Soft Mute Register (mute off)
		1, 0x03, 0xA0,	//System Control Register 1(opt.)
		1, 0x04, 0x05,	//Serial Data Interface Register
		1, 0x0E, 0x91,	//Micro Register(opt.)
		1, 0x10, 0x02,	//Modulation Limit(opt.)
		1, 0x1A, 0x0A,	//Split Capacitor Charge Period(opt.)
		1, 0x1C, 0x02,	//Back-end Error Register(opt.)
		1, 0x11, 0xB8,	//Inter-Channel Delay Channel 1
		1, 0x12, 0x60,	//Inter-Channel Delay Channel 2
		1, 0x13, 0xA0,	//Inter-Channel Delay Channel 3
		1, 0x14, 0x48,	//Inter-Channel Delay Channel 4
        0x00,
    };


    printf("********Amplifier_Init\n");
    //===========================================
    mdrv_gpio_init();

    mdrv_gpio_set_low(BALL_W20);
    udelay(1000);

    mdrv_gpio_set_low(BALL_Y20);
    udelay(1000);

    mdrv_gpio_set_high(BALL_W20);
    udelay(20*1000);

    Pstr = AmpInitTbl;
    do
    {
        DataLength = *Pstr;
        if (DataLength > 20)
        {
            printf("5707 set command error!!\n");
            break;
        }
        g_ucTas5707RegAddr = *(++Pstr);
        Pstr++;
        if (MApi_SWI2C_WriteBytes(((U16)((E_I2C_BUS_SYS << 8) | 0x36)), 1,&g_ucTas5707RegAddr, DataLength, Pstr) == FALSE)
            printf("5707write fail = %d\n", g_ucTas5707RegAddr);
        if (g_ucTas5707RegAddr == 0x1B)
        {
            udelay(50*1000);
        }
        else// if (i<=5)
        {
            udelay(1*1000);
        }
        Pstr = Pstr + DataLength;
    } while (*Pstr != 0);
#elif (ENABLE_MSTAR_TITANIA_BD_MSTCUS23_6A801_A3)
{
    U8 * Pstr = NULL;
    U8 DataLength = 0;
    U8 g_ucTas5707RegAddr = 0;

    U8 AmpInitTbl[] =
    {
        //DataLength        Address     DataN       DataN+1...
        // I2C Configuration file for TAS5700x
        //i2c writes
        0x01, 0x1B, 0x00,//Os`cillator Trim(place a 50ms delay after writing this register)

        //(Below)      DRC energy time(100ms)
        0x08, 0x3A, 0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B,

        //(Below)      DRC attack time(1ms)
        0x08, 0x3B, 0x00, 0x02, 0xA3, 0x9A, 0x00, 0x7D, 0x2F, 0xD2,

        //(Below)      DRC decay time(100ms)
        0x08, 0x3C, 0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B,


        0x04, 0x40, 0xFD, 0xAC, 0xB5, 0xE3,//0xFD, 0x9F, 0xF4, 0x4C,

        //(Below)      DRC compression ratio(100)
        0x04, 0x41, 0x03, 0x81, 0x47, 0xAF,

        //(Below)      DRC offset(0)
        0x04, 0x42, 0x00, 0x08, 0x42, 0x10,

        //(Below)      DRC control(DRC enable)
        0x04, 0x46, 0x00, 0x00, 0x00, 0x01,

        //(Below)      Bank switch control (no automatic bank switching)
        0x04, 0x50, 0x0F, 0x70, 0x80, 0x00,


        0x04, 0x20, 0x00, 0x98, 0x77, 0x72,    //
        //0x04, 0x20, 0x00, 0x89, 0x77, 0x72,  //change vol balance lmy 110714
        //(Below)       PWM Output MUX Register (Note: Writes to this register affect Inter-Channel Delay,R:A+,B-,L:C+,D-)
        0x04, 0x25, 0x01, 0x02, 0x13, 0x45,

        0x01, 0x07, 0x15,//0x16, //Master Volume Register (0xFF = Mute,16dB)
        0x01, 0x08, 0x30, //Channel 1 Volume
        0x01, 0x09, 0x30, //Channel 2 Volume
        0x01, 0x06, 0x00, //Soft Mute Register (mute off)
        0x01, 0x03, 0xA0, //System Control Register 1(opt.)
        0x01, 0x04, 0x05, //Serial Data Interface Register
        0x01, 0x05, 0x00, //System Control Register 2(exit hard mute)
        0x01, 0x0E, 0x91, //Micro Register(opt.)
        0x01, 0x10, 0x02, //Modulation Limit(opt.)
        0x01, 0x1A, 0x0A, //Split Capacitor Charge Period(opt.)
        0x01, 0x1C, 0x02, //Back-end Error Register(opt.)
        0x01, 0x11, 0xB8, //Inter-Channel Delay Channel 1
        0x01, 0x12, 0x60, //Inter-Channel Delay Channel 2
        0x01, 0x13, 0xA0, //Inter-Channel Delay Channel 3
        0x01, 0x14, 0x48, //Inter-Channel Delay Channel 4
        0x00
    };


     U8 Amp5707A_InitTbl[] =
     {
     //i2c writes
     0x01, 0x1B, 0x00,//Os`cillator Trim(place a 50ms delay after writing this register)

     //(Below)      DRC energy time(100ms)
     0x08, 0x3A, 0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B,

     //(Below)      DRC attack time(1ms)
     0x08, 0x3B, 0x00, 0x02, 0xA3, 0x9A, 0x00, 0x7D, 0x2F, 0xD2,

     //(Below)      DRC decay time(100ms)
     0x08, 0x3C, 0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B,

     //(Below)      DRC thresh
     0x04, 0x40, 0xFD, 0x9F, 0xF4, 0x4C, //same as 5707

     //(Below)      DRC compression ratio(100)
     0x04, 0x41, 0x03, 0x81, 0x47, 0xAF,

     //(Below)      DRC offset(0)
     0x04, 0x42, 0x00, 0x08, 0x42, 0x10,

     //(Below)      DRC control(DRC enable)
     0x04, 0x46, 0x00, 0x00, 0x00, 0x01,

     0x14, 0x29, 0x00, 0x00, 0x40, 0x8D, 0x00, 0x00, 0x81, 0x1B, 0x00, 0x00, 0x40, 0x8D, 0x00, 0xEF, 0x6E, 0x9F, 0x0F, 0x8F, 0x8F, 0x29,//45Hz
     0x14, 0x30, 0x00, 0x00, 0x40, 0x8D, 0x00, 0x00, 0x81, 0x1B, 0x00, 0x00, 0x40, 0x8D, 0x00, 0xEF, 0x6E, 0x9F, 0x0F, 0x8F, 0x8F, 0x29,//45Hz

     0x14, 0x2A, 0x00, 0x82, 0x80, 0x27, 0x0F, 0x03, 0x5D, 0x04, 0x00, 0x7A, 0x31, 0x04, 0x00, 0xFC, 0xA2, 0xFC, 0x0F, 0x83, 0x4E, 0xD4,//700MHz
     0x14, 0x31, 0x00, 0x82, 0x80, 0x27, 0x0F, 0x03, 0x5D, 0x04, 0x00, 0x7A, 0x31, 0x04, 0x00, 0xFC, 0xA2, 0xFC, 0x0F, 0x83, 0x4E, 0xD4,//700MHz


     0x14, 0x2B, 0x00, 0x7F, 0x2C, 0x58, 0x0F, 0x01, 0xA7, 0x50, 0x00, 0x7F, 0x2C, 0x58, 0x00, 0xFE, 0x57, 0x52, 0x0F, 0x81, 0xA5, 0xF2,//45Hz
     0x14, 0x32, 0x00, 0x7F, 0x2C, 0x58, 0x0F, 0x01, 0xA7, 0x50, 0x00, 0x7F, 0x2C, 0x58, 0x00, 0xFE, 0x57, 0x52, 0x0F, 0x81, 0xA5, 0xF2,//45Hz

     0x14, 0x2C, 0x00, 0x75, 0x76, 0x29, 0x0F, 0x19, 0x61, 0xFB, 0x00, 0x72, 0x6D, 0x0E, 0x00, 0xE6, 0x9E, 0x05, 0x0F, 0x98, 0x1C, 0xC8,//700MHz
     0x14, 0x33, 0x00, 0x75, 0x76, 0x29, 0x0F, 0x19, 0x61, 0xFB, 0x00, 0x72, 0x6D, 0x0E, 0x00, 0xE6, 0x9E, 0x05, 0x0F, 0x98, 0x1C, 0xC8,//700MHz

     0x14, 0x2D, 0x00, 0x80, 0x6A, 0x60, 0x0F, 0x00, 0xDB, 0x5E, 0x00, 0x7E, 0xBF, 0xDB, 0x00, 0xFF, 0x24, 0xA2, 0x0F, 0x80, 0xD5, 0xC5,//700MHz
     0x14, 0x34, 0x00, 0x80, 0x6A, 0x60, 0x0F, 0x00, 0xDB, 0x5E, 0x00, 0x7E, 0xBF, 0xDB, 0x00, 0xFF, 0x24, 0xA2, 0x0F, 0x80, 0xD5, 0xC5,//700MHz
     //(Below)   ch1 Biquad1 Coeff(low pass butterworth 2 200Hz)
    // 0x14, 0x2B, 0x00, 0x81, 0x49, 0x88, 0x0F, 0x03, 0x92, 0xB6, 0x00, 0x7B, 0x67, 0xA3, 0x00, 0xFC, 0x6D, 0x4A, 0x0F, 0x83, 0x4E, 0xD4,
     //00, 0x80, 0x52, 0x7D, 0x0F, 0x02, 0xC1, 0x44, 0x00, 0x7D, 0x30, 0x59, 0x00, 0xFD, 0x3E, 0xBC, 0x0F, 0x82, 0x7D, 0x2A,
         //00,0x80,0x52,0x7D,0x0F,0x02,0xC1,0x44,0x00,0x7D,0x30,0x59,0x00,0xFD,0x3E,0xBC,0x0F,0x82,0x7D,0x2A,
    // 00, 0x00, 0x05, 0x83, 0x00, 0x00, 0x0B, 0x06, 0x00, 0x00, 0x05, 0x83, 0x00, 0xFB, 0x42, 0xC1, 0x0F, 0x84, 0xA7, 0x33,

     //(Below)   ch1 Biquad2 Coeff(high pass butterworth 2 45Hz)
     //0x14, 0x2C, 0x00, 0x7F, 0x77, 0xC7, 0x0F, 0x01, 0x10, 0x72, 0x00, 0x7F, 0x77, 0xC7, 0x00, 0xFE, 0xEE, 0xFD, 0x0F, 0x81, 0x0F, 0xE1,



     //(Below)   ch2 Biquad1 Coeff(low pass butterworth 2 200Hz)
     //0x14, 0x32, 0x00, 0x81, 0x49, 0x88, 0x0F, 0x03, 0x92, 0xB6, 0x00, 0x7B, 0x67, 0xA3, 0x00, 0xFC, 0x6D, 0x4A, 0x0F, 0x83, 0x4E, 0xD4,
     //00, 0x80, 0x52, 0x7D, 0x0F, 0x02, 0xC1, 0x44, 0x00, 0x7D, 0x30, 0x59, 0x00, 0xFD, 0x3E, 0xBC, 0x0F, 0x82, 0x7D, 0x2A,//350hZ
     //00, 0x00, 0x05, 0x83, 0x00, 0x00, 0x0B, 0x06, 0x00, 0x00, 0x05, 0x83, 0x00, 0xFB, 0x42, 0xC1, 0x0F, 0x84, 0xA7, 0x33,

     //(Below)   ch2 Biquad2 Coeff(high pass butterworth 2 45Hz)
     //0x14, 0x33, 0x00, 0x7F, 0x77, 0xC7, 0x0F, 0x01, 0x10, 0x72, 0x00, 0x7F, 0x77, 0xC7, 0x00, 0xFE, 0xEE, 0xFD, 0x0F, 0x81, 0x0F, 0xE1,

     //(Below)      Bank switch control (no automatic bank switching)
     0x04, 0x50, 0x0F, 0x70, 0x80, 0x00,


     0x04, 0x20, 0x00, 0x80, 0x77, 0x72,
     //0x04, 0x20, 0x00, 0x89, 0x77, 0x72,
     //(Below)       PWM Output MUX Register (Note: Writes to this register affect Inter-Channel Delay,R:A+,B-,L:C+,D-)
     0x04, 0x25, 0x01, 0x20, 0x31, 0x45,

     0x01, 0x07, 0x16, //Master Volume Register (0xFF = Mute,16dB)   //same as 5707
     0x01, 0x08, 0x30, //Channel 1 Volume
     0x01, 0x09, 0x30, //Channel 2 Volume
     0x01, 0x06, 0x00, //Soft Mute Register (mute off)
     0x01, 0x03, 0xA0, //System Control Register 1(opt.)
     0x01, 0x04, 0x05, //Serial Data Interface Register
     0x01, 0x05, 0x00, //System Control Register 2(exit hard mute)
     0x01, 0x0E, 0x91, //Micro Register(opt.)
     0x01, 0x10, 0x02, //Modulation Limit(opt.)
     0x01, 0x1A, 0x0A, //Split Capacitor Charge Period(opt.)
     0x01, 0x1C, 0x02, //Back-end Error Register(opt.)
     0x01, 0x11, 0xB8, //Inter-Channel Delay Channel 1
     0x01, 0x12, 0x60, //Inter-Channel Delay Channel 2
     0x01, 0x13, 0xA0, //Inter-Channel Delay Channel 3
     0x01, 0x14, 0x48, //Inter-Channel Delay Channel 4
     0x00
     };


    printf("********Amplifier_Init\n");
    //===========================================
    mdrv_gpio_init();
    Audio_Amplifier_OFF();
    msAPI_Timer_Delayms(1);
    Audio_Amplifier_ON();
    msAPI_Timer_Delayms(20);//must added

    Pstr = AmpInitTbl;
    do
    {
        DataLength = *Pstr;
        if (DataLength > 20)
        {
            printf("5707 set command error!!\n");
            break;
        }
        g_ucTas5707RegAddr = *(++Pstr);
        Pstr++;
        if (MApi_SWI2C_WriteBytes(((U16)((E_I2C_BUS_SYS << 8) | 0x36)), 1,&g_ucTas5707RegAddr, DataLength, Pstr) == FALSE)
            printf("5707write fail = 0x%x\n", g_ucTas5707RegAddr);

        if (g_ucTas5707RegAddr == 0x1B)
        {
            msAPI_Timer_Delayms(50);
        }
        else// if (i<=5)
        {
            msAPI_Timer_Delayms(1);
        }
        Pstr = Pstr + DataLength;
    } while (*Pstr != 0);


    Pstr = Amp5707A_InitTbl;
    do
    {
        DataLength = *Pstr;
        if (DataLength > 20)
        {
            printf("5707A set command error!!\n");
            break;
        }
        g_ucTas5707RegAddr = *(++Pstr);
        Pstr++;
        if (MApi_SWI2C_WriteBytes(((U16)((E_I2C_BUS_SYS << 8) | 0x3A)), 1,&g_ucTas5707RegAddr, DataLength, Pstr) == FALSE)
            printf("5707Awrite fail = %d\n", g_ucTas5707RegAddr);

        if (g_ucTas5707RegAddr == 0x1B)
        {
            msAPI_Timer_Delayms(50);
        }
        else// if (i<=5)
        {
            msAPI_Timer_Delayms(1);
        }
        Pstr = Pstr + DataLength;
    } while (*Pstr != 0);
}
#else
    drvTAS5707_Shutdown();
    drvTAS5707_HWInit();
    msAPI_Timer_Delayms(50);
    drvTAS5707_RegInit();
#endif
}
#endif
#undef DRV_TAS5707_C


