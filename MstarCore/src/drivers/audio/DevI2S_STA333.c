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

#define _DEVAUDIO_I2S_
#include <common.h>
#include <audio/DevI2S_STA333.h>

#define CHANNEL1_CFG_VAL  0x08
#define CHANNEL2_CFG_VAL  0x48
#define CHANNEL3_CFG_VAL  0x80
#define MAIN_VOLUME_VAL   0x04 //lcf 80203 0x1C


#define BOOL MS_BOOL

void DevI2s_STA333_Init(void)
{
	MS_U8 I2C_buf1;
    BOOLEAN bResult = FALSE;
/* the master clock select 0x62 = 384fs,0x63 = 256fs,0x64 = 128fs fault detect enable */
	I2C_buf1=0x63;//0x64;
/* the first parameter is the number that how many registers will be written
   the second parameter is the address that the variable
   the third parameter is the DDX chip address
   the fourth parameter is the begining register address */
    bResult=  MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_A,I2C_buf1);
    if(bResult)
        printf("\r \n Write 5333 Success!\n");
    else
        printf("\r \n Write 5333 Fail!\n");
/* the serial input format select, I2s format, MSB first*/
	I2C_buf1=0x40;//0x80;   // Johnny+ swap L/R
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_B,I2C_buf1);

/* Use default output mode*/
	I2C_buf1=0x07;//0x22;//c2;//0x42;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_C,I2C_buf1);

/* High pass enbale, No De-emphasis, No DSP by pass, Anti-Clipping Mode*/
	I2C_buf1=0x64;//0x50; //0x40;//0x00;58
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_D,I2C_buf1);

/* Use standard MPC, AM mode disable, normal output speed*/
	I2C_buf1=0xc2;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_E,I2C_buf1);

/*	let the EAPD high, 2 DDX channel, invalid detect disable, Auto EAPD on disable*/
	I2C_buf1=0xc9;//0x5D;//0xDC;//0xC0;//MODIFIED_BY_HHH 071206
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_F,I2C_buf1);

/*	main and channel mute*/
	I2C_buf1=0x00;//0x46;//0x06;//0x10;//0x11;//0x06:mute ch1,ch2     0x00:clear mute	//MODIFIED_BY_HHH 071206
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE,I2C_buf1);

/* Preset EQ, user defined pre-scale*/
	I2C_buf1=0x80;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_AUTO1,I2C_buf1);

/* Switching frequency determined by AMAM setting*/

	I2C_buf1=0xF0;//0xA0;

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_AUTO2,I2C_buf1);

/* flat mode EQ*/
	I2C_buf1=0x00;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_AUTO3,I2C_buf1);

/* channel1 mapped to limiter 1, tone and treble control bypass*/

       I2C_buf1=CHANNEL1_CFG_VAL;//0x08;

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG,I2C_buf1);

/* channel2 mapped to limiter 1, tone and treble control bypass*/

I2C_buf1=CHANNEL2_CFG_VAL;

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG,I2C_buf1);

/* channel3 mapped to limiter 2, tone and treble control enable*/
	I2C_buf1=0x77;//0x20;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_TONEBASS,I2C_buf1);
/* tone and treble are 0 dB*/

	I2C_buf1=CHANNEL3_CFG_VAL;

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG,I2C_buf1);

/* Limiter1 attack and rease rate*/
	I2C_buf1=0x6a;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L1AR_RATE,I2C_buf1);

/* Limiter1 attack and rease threshold*/
	I2C_buf1=0x69;//0x8c;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L1AR_THRESHOLD,I2C_buf1);

/* Limiter2 attack and rease rate*/
	I2C_buf1=0x6a;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L2AR_RATE,I2C_buf1);

/* Limiter2 attack and rease threshold*/
	I2C_buf1=0x69;//0x9d;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L2AR_THRESHOLD,I2C_buf1);

/*	initiate the volume, volume = 20 */
	I2C_buf1= MAIN_VOLUME_VAL;//0x30;//0x10;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME,I2C_buf1);
#if 0//(STRUCT_TYPE == STRUCT_H78)
	I2C_buf1=0x30;//lcf 80203 0x2a; //0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_VOL,I2C_buf1);
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_VOL,I2C_buf1);
	I2C_buf1= 0x2a;//lcf 80203 0x26;////0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_VOL,I2C_buf1);
#elif 1//(STRUCT_TYPE == STRUCT_E9)
	I2C_buf1=0x30;//lcf 80203 0x2a; //0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_VOL,I2C_buf1);
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_VOL,I2C_buf1);
	I2C_buf1= 0x2a;//lcf 80203 0x26;////0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_VOL,I2C_buf1);
#elif 0//(STRUCT_TYPE == STRUCT_M9)
	I2C_buf1=0x30;//lcf 80203 0x2a; //0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_VOL,I2C_buf1);
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_VOL,I2C_buf1);
	I2C_buf1= 0x2a;//lcf 80203 0x26;////0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_VOL,I2C_buf1);

#else
	I2C_buf1=0x30;//lcf 80203 0x2a; //0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_VOL,I2C_buf1);
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_VOL,I2C_buf1);
	I2C_buf1= 0x2a;//lcf 80203 0x26;////0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_VOL,I2C_buf1);
#endif
//	I2C_buf1=0x60;
//    MDrv_IIC_WriteByte(STA333_ADDR,DDX_LEFT_VOL,I2C_buf1);
//	I2C_buf1=0x60;
//    MDrv_IIC_WriteByte(STA333_ADDR,DDX_RIGHT_VOL,I2C_buf1);
/* alrough there is not the subwoofer channel for some configuration,
	I still have its source code for the reference*/
//	I2C_buf1=0x48;
//    MDrv_IIC_WriteByte(STA333_ADDR,DDX_SUBWOOFER_VOL,I2C_buf1);

//    DevI2S_STA333_SetCFTable();//jazzy 071130 update for TCL

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE,0x40);//clear mute

}


#define WA_OK       _BIT1
MS_U8 tEQAddrtable[] = {0x00, 0x05, 0x0A, 0x0F};

MS_U8 tCFtable[][3]=
{
#if 0//(STRUCT_TYPE == STRUCT_H78)
//f1
    {0x80, 0x87, 0xa8},//b1/2
    {0x7F, 0x3f, 0xcb},//b2
    {0x7F, 0x78, 0x58},//a1/2
    {0x80, 0xf6, 0x0d},//a2
    {0x3F, 0xE5, 0x14},//b0/2
    //f2
    {0x85, 0x79, 0x3c},//b1/2
    {0x78, 0x4a, 0x57},//b2
    {0x7a, 0x86, 0xc4},//a1/2
    {0x89, 0x07, 0x27},//a2
    {0x3f, 0x57, 0x41},//b0/2
    //f3
    {0x8e, 0x21, 0xb0},//b1/2
    {0x6f, 0xcd, 0xba},//b2
    {0x71, 0xde, 0x50},//a1/2
    {0x96, 0x64, 0x1c},//a2
    {0x3c, 0xe7, 0x15},//b0/2
    //f4
    {0x90, 0xfb, 0x57},//b1/2
    {0x6b, 0x09, 0x6a},//b2
    {0x6f, 0x04, 0xa9},//a1/2
    {0x8f, 0x17, 0x3e},//a2
    {0x42, 0xef, 0xab},//b0/2

#elif 0//(STRUCT_TYPE== STRUCT_E77_SMALL_SPEAKER)
//f1
    {0x80, 0x83, 0x1b},//b1/2
    {0x7F, 0x7c, 0xe5},//b2
    {0x7F, 0x7c, 0x93},//a1/2
    {0x81, 0x05, 0x90},//a2
    {0x3F, 0xbe, 0x72},//b0/2
    //f2
    {0x85, 0x3e, 0xd5},//b1/2
    {0x79, 0x48, 0x1e},//b2
    {0x7a, 0xc1, 0x2b},//a1/2
    {0x88, 0xf3, 0x5d},//a2
    {0x3e, 0xe2, 0x42},//b0/2
    //f3
    {0x90, 0x3e, 0x36},//b1/2
    {0x6e, 0x09, 0x31},//b2
    {0x6f, 0xc1, 0xca},//a1/2
    {0x97, 0xee, 0xe5},//a2
    {0x3d, 0x03, 0xf4},//b0/2
    //f4
    {0x06, 0x9a, 0x03},//b1/2
    {0x06, 0x9a, 0x03},//b2
    {0x65, 0x71, 0x75},//a1/2
    {0x9a, 0xb5, 0x07},//a2
    {0x03, 0x4d, 0x01},//b0/2
#elif 0//(STRUCT_TYPE== STRUCT_E77_BIG_SPEAKER)
//f1
    {0x80, 0x4E, 0xC7},//b1/2
    {0x7F, 0xB1, 0x39},//b2
    {0x7F, 0xB1, 0x21},//a1/2
    {0x80, 0x9D, 0x5d},//a2
    {0x3F, 0xD8, 0x9C},//b0/2
    //f2
    {0x8A, 0x8B, 0x8E},//b1/2
    {0x74, 0x6C, 0xE0},//b2
    {0x75, 0x74, 0x72},//a1/2
    {0x91, 0x16, 0x38},//a2
    {0x3D, 0x3E, 0x74},//b0/2
    //f3
    {0x9D, 0x01, 0x7F},//b1/2
    {0x4F, 0x98, 0x89},//b2
    {0x62, 0xFE, 0x81},//a1/2
    {0xA2, 0xD8, 0x3F},//a2
    {0x46, 0xC7, 0x9C},//b0/2
    //f4
    {0x09, 0xFC, 0x40},//b1/2
    {0x09, 0xFC, 0x40},//b2
    {0x44, 0x72, 0x41},//a1/2
    {0xCF, 0x2A, 0x7A},//a2
    {0x04, 0xFE, 0x20},//b0/2
#elif 0//(STRUCT_TYPE== STRUCT_M9_20CHANNEL)
//f1
    {0x80, 0x4D, 0xFE},//b1/2
    {0x7F, 0xB2, 0x02},//b2
    {0x7F, 0xB1, 0xE5},//a1/2
    {0x80, 0x9B, 0xC1},//a2
    {0x3F, 0xD9, 0x01},//b0/2
    //f2
    {0x8C, 0x57, 0xA8},//b1/2
    {0x6F, 0x1D, 0x17},//b2
    {0x73, 0xA8, 0x58},//a1/2
    {0x96, 0x7F, 0x52},//a2
    {0x3D, 0x31, 0xCB},//b0/2
    //f3
    {0x88, 0x4A, 0x20},//b1/2
    {0x6E, 0x59, 0xAB},//b2
    {0x77, 0xB5, 0xE0},//a1/2
    {0x8A, 0x0D, 0x2A},//a2
    {0x43, 0xCC, 0x95},//b0/2
    //f4
    {0x92, 0xA9, 0x4B},//b1/2
    {0x59, 0xAD, 0xD8},//b2
    {0x6D, 0x56, 0xB5},//a1/2
    {0x94, 0x12, 0x62},//a2
    {0x49, 0x1F, 0x42},//b0/2
    #elif 1//(STRUCT_TYPE== STRUCT_E9)
//f1
    {0x80, 0x4D, 0xFE},//b1/2
    {0x7F, 0xB2, 0x02},//b2
    {0x7F, 0xB1, 0xE5},//a1/2
    {0x80, 0x9B, 0xC1},//a2
    {0x3F, 0xD9, 0x01},//b0/2
    //f2
    {0x8C, 0x57, 0xA8},//b1/2
    {0x6F, 0x1D, 0x17},//b2
    {0x73, 0xA8, 0x58},//a1/2
    {0x96, 0x7F, 0x52},//a2
    {0x3D, 0x31, 0xCB},//b0/2
    //f3
    {0x88, 0x4A, 0x20},//b1/2
    {0x6E, 0x59, 0xAB},//b2
    {0x77, 0xB5, 0xE0},//a1/2
    {0x8A, 0x0D, 0x2A},//a2
    {0x43, 0xCC, 0x95},//b0/2
    //f4
    {0x92, 0xA9, 0x4B},//b1/2
    {0x59, 0xAD, 0xD8},//b2
    {0x6D, 0x56, 0xB5},//a1/2
    {0x94, 0x12, 0x62},//a2
    {0x49, 0x1F, 0x42},//b0/2
   #elif 0//(STRUCT_TYPE== STRUCT_X9)
    {0x80, 0x9a, 0x58},//b1/2
    {0x7F, 0x65, 0xa8},//b2
    {0x7F, 0x65, 0x4b},//a1/2
    {0x81, 0x33, 0xf6},//a2
    {0x3F, 0xb2, 0xd4},//b0/2
    //f2
    {0x89, 0x8c, 0x2a},//b1/2
    {0x74, 0x87, 0x3e},//b2
    {0x76, 0x73, 0xd6},//a1/2
    {0x8f, 0xdb, 0xfd},//a2
    {0x3d, 0xce, 0x62},//b0/2
    //f3
    {0x9a, 0x8e, 0xe6},//b1/2
    {0x55, 0x2b, 0xc9},//b2
    {0x65, 0x71, 0x1a},//a1/2
    {0xa3, 0x81, 0x5d},//a2
    {0x43, 0xa9, 0x6c},//b0/2
    //f4
    {0x06, 0xc8, 0xa6},//b1/2
    {0x06, 0xc8, 0xa6},//b2
    {0x5c, 0x7e, 0xcb},//a1/2
    {0xab, 0xdf, 0xd2},//a2
    {0x03, 0x64, 0x53},//b0/2
    #elif 0//(STRUCT_TYPE==STRUCT_M11_20CHANNEL)
    {0x80, 0x3e, 0x43},//b1/2
    {0x7F, 0xc1, 0xbd},//b2
    {0x7F, 0xc1, 0xa5},//a1/2
    {0x80, 0x7c, 0x57},//a2
    {0x3F, 0xe0, 0xde},//b0/2
    //f2
    {0x80, 0xc7, 0xf8},//b1/2
    {0x7e, 0xcf, 0x3d},//b2
    {0x7f, 0x38, 0x08},//a1/2
    {0x81, 0x86, 0x22},//a2
    {0x3f, 0xd5, 0x50},//b0/2
    //f3
    {0x8a, 0x1f, 0x8a},//b1/2
    {0x6c, 0x5a, 0xc4},//b2
    {0x75, 0xe0, 0x76},//a1/2
    {0x8e, 0x24, 0x66},//a2
    {0x42, 0xc0, 0x6b},//b0/2
    //f4
    {0x97, 0x32, 0x3f},//b1/2
    {0x56, 0x78, 0xf1},//b2
    {0x68, 0xcd, 0xc1},//a1/2
    {0x95, 0xc0, 0x5b},//a2
    {0x49, 0xe3, 0x59},//b0/2
#endif
};
        static unsigned char STA333BW_WOOFER_VOLUME_TABLE[101]=
        {//0x46=70,smaller,the sound larger
            20,21,22,23,24,25,26,27,28,29,//0~9
            30,31,32,33,34,35,36,37,38,39,//10~19
            40,41,42,43,44,45,46,47,48,49,//20~29
            50,51,52,53,54,55,56,57,58,59,//30~39
            60,61,62,63,64,65,66,67,68,69,//40~49
            70,//50
            71,72,73,74,75,76,77,78,79,80,//51~60
            81,82,83,84,85,86,87,88,89,90,//61~70
            91,92,93,94,95,96,97,98,99,100,//71~80
            101,102,103,104,105,106,107,108,109,110,//81~90
            111,112,113,114,115,116,117,118,119,0xff//91~100 //last force to mute
        };
void DevI2S_STA333_SubwoofValue(U8 Subwoof)
{
//    UINT8 Subwooffl;
    MS_U8 I2C_buf1;
//    Subwooffl = 0;                  //by tao test ,is error .
//    if(Subwoof)
    {

	I2C_buf1=STA333BW_WOOFER_VOLUME_TABLE[100-Subwoof];
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_VOL,I2C_buf1);
        }
}
void DevI2S_STA333_SetCFTable(void )
{
    MS_U8 i,j,ucIndex;
    MS_U8 u8Temp;

    ucIndex = MDrv_IIC_ReadByte(STA333_ADDR,DDX_CONFIGURE_D,&u8Temp );
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_D ,(ucIndex |_BIT4));//channel1,channel2 use same filter coefficient

    for(ucIndex = 0;ucIndex< sizeof(tEQAddrtable);ucIndex++)
    {
        MDrv_IIC_WriteByte(STA333_ADDR,REG_CFADDR1,tEQAddrtable[ucIndex]);
        for(j = 0;j<5;j++)
        {
            for(i = 0;i<3;i++)
                MDrv_IIC_WriteByte(STA333_ADDR, (MS_U8)(REG_B1CF1 + i+ 3*j), tCFtable[(j+5*ucIndex)][i]);
        }
        MDrv_IIC_WriteByte(STA333_ADDR,REG_CFUD ,WA_OK);
    }

}

void DecI2S_STA333_Patch(MS_U8 ucCtl)
{
    MS_U8 ucTmp;
    MS_U8 u8Temp;
    printf("\r\nDecI2SPatch(%d)",ucCtl);
     if(ucCtl)
     {
        //ClrPinAudioMute();
        //Delay1ms(5);
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR,DDX_MUTE,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE ,(ucTmp |_BIT0));
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME, 0xFE);
        //SetPinAudioMute();
     }
     else
     {
        //ClrPinAudioMute();
        //Delay1ms(5);
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL1_CFG,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,(ucTmp&(~_BIT4)&(~_BIT5)));
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL2_CFG,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,(ucTmp&(~_BIT4)&(~_BIT5)));
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL3_CFG,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,(ucTmp&(~_BIT4)&(~_BIT5)));

        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,CHANNEL1_CFG_VAL);
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,CHANNEL2_CFG_VAL);
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,CHANNEL3_CFG_VAL);
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME, MAIN_VOLUME_VAL);

        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR,DDX_MUTE,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE ,(ucTmp &(~_BIT0)));
        //SetPinAudioMute();
     }
}

BOOL STA333_GetPowerDNStatus(void)  //+zch for headphone
{
	MS_U8 Temp[3];
       MS_U8 u8Temp;
	Temp[0] = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CONFIGURE_A,&u8Temp );
	Temp[1] = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CONFIGURE_B,&u8Temp );
	Temp[2] = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CONFIGURE_C,&u8Temp );
    if((Temp[0]==63)&&(Temp[0]==80)&&(Temp[0]==97))
        return TRUE;
    else
        return FALSE;
}

