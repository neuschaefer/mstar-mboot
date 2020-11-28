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

#ifndef __DRV_URSA_8_C__
#define __DRV_URSA_8_C__

#ifdef __DRV_URSA_8_C__
#define URSA_INTERFACE
#else
#define URSA_INTERFACE extern
#endif


//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------
#include "ursa_8.h"
#include <apiPNL.h>


//-------------------------------------------------------------------------------------------------
//  Define
//-------------------------------------------------------------------------------------------------
#define URSA_8_CMD_DATA_SUM         (7)
#define URSA_8_I2C_BUS_NUM          (3)
#define URSA_8_I2C_SUB_ADDR         (0)
#define URSA_IIC_BUS                E_I2C_BUS_DDCA1
#define URSA_8_DDC2BI_MODE_ADDR	    (0x40)
#define URSA_8_BUSID     (((MS_U16) URSA_IIC_BUS << 8) | URSA_8_DDC2BI_MODE_ADDR)



#define BIT0                            0x0001
#define BIT1                            0x0002
#define BIT2                            0x0004
#define BIT3                            0x0008
#define BIT4                            0x0010
#define BIT5                            0x0020
#define BIT6                            0x0040
#define BIT7                            0x0080
#define BIT8                            0x0100
#define BIT9                            0x0200
#define BIT10                           0x0400
#define BIT11                           0x0800
#define BIT12                           0x1000
#define BIT13                           0x2000
#define BIT14                           0x4000
#define BIT15                           0x8000
#define BIT16                           0x00010000
#define BIT17                           0x00020000
#define BIT18                           0x00040000
#define BIT19                           0x00080000
#define BIT20                           0x00100000
#define BIT21                           0x00200000
#define BIT22                           0x00400000
#define BIT23                           0x00800000
#define BIT24                           0x01000000
#define BIT25                           0x02000000
#define BIT26                           0x04000000
#define BIT27                           0x08000000
#define BIT28                           0x10000000
#define BIT29                           0x20000000
#define BIT30                           0x40000000
#define BIT31                           0x80000000


#define code

static code URSA_CMD_DATA m_UrsaCmdData[] =
{
    { 0x00,  0x01,  0x00, 0x00, 0x00, 0x00, 0x00}, // UC_INIT_IN_ALL= 0x0001,
    { 0x01,  0x00,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_INIT_FINISH= 0x0100,
    { 0x01,  0x01, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_MODE= 0x0101,
    { 0x01,  0x02, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_SWAP= 0x0102,
    { 0x01,  0x03, 0x01, 0x00, 0x00, 0x00, 0x00}, //UC_SET_IN_LVDS_TTL= 0x0103,
    { 0x00,  0x10, 0x01,  0x01,  0x01, 0x00, 0x00}, //UC_INIT_OUT_ALL_1= 0x0010,
    { 0x00,  0x11, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_INIT_OUT_ALL_2= 0x0011,
    { 0x00,  0x12, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_INIT_OUT_ALL_3= 0x0012,
    //{ 0x01,  0x10, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OUT_TGEN_BASIC_1= 0x0110,
    //{ 0x01,  0x11, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OUT_TGEN_BASIC_2= 0x0111,
    //{ 0x01,  0x12, 0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OUT_TGEN_ADV= 0x0112,
    { 0x02,  0x01,  0x00,  0x00,  0x00,  0x00, 0x00}, //UC_SET_OUT_LVDS_MODE= 0x0201,
    { 0x02,  0x02,  0x00,  0x00,  0x00, 0x00, 0x00}, //UC_SET_OUT_LVDS_SWAP= 0x0202,
    { 0x02,  0x03,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_OUT_LVDS_CHANNELTYPE= 0x0203,
    { 0x02,  0x04,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_OUT_SWING_LELVEL= 0x0204,
    //==3D mode CMD===
    { 0x03,  0x01,  0x00, 0x00, 0x00, 0x00, 0x00}, //UC_SET_3DMODE = 0x0301, //No 3D; MEMC 240Hz

    //==MFC level CMD ==
    { 0x03,  0x02,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_MFC_LEVEL  = 0x0302,

    //==video mute/on CMD ==
    { 0x03,  0x03,  0x01,  0x00,  0x00,  0x00,  0x00}, //UC_SET_VIDEO_MUTE= 0x3030,

    { 0x03,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_GAIN_OFFSET= 0x0304,
    { 0x03,  0x05,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OSD_WINDOWS_H= 0x0305,
    { 0x03,  0x06,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_OSD_WINDOWS_V= 0x0306,

    { 0x03,  0x07,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_PWM_DUTY_PHASE,//= 0x3070,

    { 0x03,  0x08,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_LVDS_OFF,//= 0x3080,
    { 0x03,  0x08,  0x01,  0x00,  0x00,  0x00,  0x00},//EN_MFC_UC_SET_LVDS_ON

    { 0x03,  0x09,	0x00,  0x00,  0x00,  0x00,	0x00},//EN_MFC_UC_SET_LVDS_ON

    { 0x03,  0x0A,  0x01,  0x00,  0x00,  0x00,  0x00}, //UC_SET_2D_TO_3D,//= 0x30A0,

    { 0x03,  0x0c,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_HVMIRROR,//= 0x30C0,

    { 0x03,  0x0d,  0x00,  0x00,  0x00,  0x00,  0x00}, //UC_SET_FRAMELOCK,//= 0x30D0,

    { 0xFF,  0xFF, 0x00,  0x00, 0x00, 0x00, 0x00}, //EN_CMD type index Max
};


static SWI2C_BusCfg Ursa_8_I2cBusCfg[URSA_8_I2C_BUS_NUM]=
{

  
   //Example for SW I2C => { 1, PAD_DDCR_CK, PAD_DDCR_DA, 60, }, //SW_I2C	/SCL_PAD /SDA_PAD /Delay
   // Bus-0
   {PAD_DDCR_CK, PAD_DDCR_DA, 400},    //IS_SW_I2C	/SCL_PAD /SDA_PAD /Delay
   // Bus-1
   {PAD_TGPIO2, PAD_TGPIO3, 400},	   //IS_SW_I2C	/SCL_PAD /SDA_PAD /Delay
   // Bus-2
   {PAD_GPIO17, PAD_GPIO18, 400},
   // Others, add other bus here
};


//-------------------------------------------------------------------------------------------------
//  Function define
//-------------------------------------------------------------------------------------------------
void MDrv_Ursa_8_SWI2C_Init(void)
{
	MApi_SWI2C_Init(Ursa_8_I2cBusCfg, URSA_8_I2C_BUS_NUM);
}

MS_BOOL MDrv_Ursa_8_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_WriteBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Ursa_8_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data)
{
    return MApi_SWI2C_ReadBytes(u16BusNumSlaveID, u8addrnum, pu8addr, u16size, pu8data);
}

MS_BOOL MDrv_Ursa_8_SendCmd(URSA_8_CMD_TYPE eCmdType)
{
    MS_U8 pCmdData[URSA_8_CMD_DATA_SUM] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    MS_BOOL bUnkown = FALSE;
    MS_BOOL bRet = FALSE;
    
    switch(eCmdType)
    {
        case URSA_8_CMD_OSD_MUTE:
            {
            //0x43, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x43;
                pCmdData[1] = 0x03;
                pCmdData[2] = 0x01;
            }
            break;

        case URSA_8_CMD_OSD_ON:
            {
            //0x51,  0x04,  0x01,  0x00,  0x00,  0x00,  0x00
                pCmdData[0] = 0x51;
                pCmdData[1] = 0x04;
                pCmdData[2] = 0x01;
            }
            break;
            
        case URSA_8_CMD_OSD_OFF:
            {
            //0x41,  0x04,  0x00,  0x00,  0x00,  0x00,  0x00
                pCmdData[0] = 0x41;
                pCmdData[1] = 0x04;
            }
            break;
            
        case URSA_8_CMD_OSD_UNMUTE:
            {
            //0x33, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x33;
                pCmdData[1] = 0x03;
            }
            break;

        case URSA_8_CMD_LVDS_ON:
            {
            //0x93, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x93;
                pCmdData[1] = 0x08;
                pCmdData[2] = 0x01;
            }
            break;

        case URSA_8_CMD_LVDS_OFF:
            {
            //0x83, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00
                pCmdData[0] = 0x83;
                pCmdData[1] = 0x08;
            }
            break;
		case URSA_8_CMD_LVDS_SWING:
            {
            //0x32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x2F
                pCmdData[0] = 0x32;
                pCmdData[1] = 0x04;
                pCmdData[6] = 0x2F;
            }
            break; 
		case URSA_8_CMD_OSD_PROTECT_OFF:
			{
			//  95 09 00 00 00 00 00 
                pCmdData[0] = 0x95;
                pCmdData[1] = 0x09;							
			}
			break;
		case URSA_8_CMD_OSD_PROTECT_ON:
			{
			//  A5 09 01 00 00 00 00 
                pCmdData[0] = 0xA5;
                pCmdData[1] = 0x09;		
		pCmdData[2] = 0x01;						
			}
			break;
		case URSA_8_CMD_OSD_PROTECT_ON_EMMC:
			{
			//  B5 09 02 00 00 00 00 
                pCmdData[0] = 0xB5;
                pCmdData[1] = 0x09;		
		pCmdData[2] = 0x02;						
			}
			break;
        default:
            bUnkown = TRUE;
            break;
    }

    if(!bUnkown)
    {
        bRet  = MDrv_Ursa_8_Write_Cmd(pCmdData);
        printf("[Ursa_8]Send cmd:%d, return:%d\n", eCmdType, bRet);
    }
    else
    {
        bRet = FALSE;
        printf("[Ursa_8]Can not find the command, please check!\n");
    }
    
    return bRet;
}

MS_BOOL MDrv_Ursa_8_Write_Cmd(MS_U8 *pu8CmdData)
{
    MS_U16 u16BusNumSlaveID = URSA_8_BUSID;
    MS_U8 u8SubAddr = URSA_8_I2C_SUB_ADDR;
    
    MDrv_Ursa_8_SWI2C_Init();
    printf("[URSA_8]Write cmd:%x,%x,%x,%x,%x,%x,%x\n", pu8CmdData[0], pu8CmdData[1], pu8CmdData[2], pu8CmdData[3], pu8CmdData[4], pu8CmdData[5], pu8CmdData[6]);
    return MDrv_Ursa_8_SWI2C_WriteBytes(u16BusNumSlaveID, u8SubAddr, NULL, URSA_8_CMD_DATA_SUM, pu8CmdData);
}
//-------------------------------------------------------------------------------------------------
//  Member Function
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_Ursa_8_Set_Osd_On(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_ON);
}

MS_BOOL MDrv_Ursa_8_Set_Osd_Off(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_OFF);
}

MS_BOOL MDrv_Ursa_8_Set_Osd_Mute(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_MUTE);
}

MS_BOOL MDrv_Ursa_8_Set_Osd_Unmute(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_OSD_UNMUTE);
}

MS_BOOL MDrv_Ursa_8_Set_Lvds_On(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_LVDS_ON);
}

MS_BOOL MDrv_Ursa_8_Set_Lvds_Off(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_LVDS_OFF);
}
MS_BOOL MDrv_Ursa_8_Set_Lvds_Swing(void)
{
    return MDrv_Ursa_8_SendCmd(URSA_8_CMD_LVDS_SWING);
}

MS_BOOL MDrv_Ursa_8_Install ( void )
{
    MS_BOOL bResult = FALSE;
	//MDrv_Ursa_8_SWI2C_Init();
    MS_U8 pBuffer[7] = { 0x00,  0x00,  0x00, 0x00, 0x00, 0x00, 0x00};
    bResult = MApi_SWI2C_ReadBytes(URSA_8_BUSID, 0, NULL, URSA_8_CMD_DATA_SUM, pBuffer);

    if (bResult == FALSE)
    {
        printf ( "\nUrsa_8_not_install\n" );
        return FALSE;
    }

    printf ( "\nUrsa_8 installed\n" );
    return TRUE;
}

void  MDrv_Ursa_8_Initialize ( void )
{
     bMstUrsa8Installed = 0;
    bMstUrsa8Installed = MDrv_Ursa_8_Install();

    if ( !bMstUrsa8Installed )
    {
        bMstUrsa8Installed = MDrv_Ursa_8_Install();//check again

        if ( !bMstUrsa8Installed )
            return;
    }
}


MS_BOOL MDrv_Ursa_8_3D_DataWrite ( MS_U8 *u8Buf )
{
    MS_BOOL bRet = FALSE;
    MDrv_Ursa_8_SWI2C_Init();
    bRet = MApi_SWI2C_WriteBytes ( URSA_8_BUSID, 0, NULL, URSA_8_CMD_DATA_SUM, u8Buf );
    return bRet;
}


void MDrv_Ursa_8_CalCheckSum ( MS_U8 *pBuf, MS_U8 u8BufLen )
{
    MS_U8 u8CheckSum = 0;

    while ( u8BufLen > 1 ) //calculate pBuf[1]~pBuf[End] do not count pBuf[0],it is checksum
    {
        -- u8BufLen;
        u8CheckSum += pBuf[u8BufLen] & 0x0F;
    }

    u8CheckSum &= 0x0F;
    pBuf[0] &= 0x0F;
    pBuf[0] |= ( ( u8CheckSum ) << 4 );
}

MS_BOOL MDrv_Ursa_8_3D_Cmd ( UC_CMD_TYPE eCmdIdx )
{
    MS_BOOL bResult = FALSE;//TRUE;
    MS_U8 pBuffer[7] = {0, 0, 0, 0, 0, 0, 0};

    if ( eCmdIdx >= UC_SET_CMDTYPE_END )
        return FALSE;

    memcpy ( pBuffer, & ( m_UrsaCmdData[eCmdIdx] ), URSA_8_CMD_DATA_SUM );

    if ( ( pBuffer[0] == 0xFF ) && ( pBuffer[1] == 0xFF ) )
        return FALSE;

    switch ( eCmdIdx )
    {
    case UC_INIT_IN_ALL://= 0x0001,
        MDrv_Ursa_8_SetInitInLvdsAllData ( pBuffer );
        break;
    case UC_INIT_FINISH://= 0x0100,
        break;
    case UC_SET_IN_LVDS_MODE://= 0x0101,
        MDrv_Ursa_8_SetInitInLvdsAllData ( pBuffer );
        break;
    case UC_SET_IN_LVDS_SWAP://= 0x0102,
        MDrv_Ursa_8_SetInitInLvdsAllData ( pBuffer );
        break;
    case UC_SET_IN_LVDS_TTL://= 0x0103,
        MDrv_Ursa_8_SetInitInLvdsAllData ( pBuffer );
        break;
    case UC_INIT_OUT_ALL_1://= 0x0010,
        MDrv_Ursa_8_SetInitOutAll1Data ( pBuffer );
        break;
    case UC_INIT_OUT_ALL_2://= 0x0011,
        MDrv_Ursa_8_SetInitOutAll2Data ( pBuffer );
        break;
    case UC_INIT_OUT_ALL_3://= 0x0012,
        MDrv_Ursa_8_SetInitOutAll3Data ( pBuffer );
        break;
        //    case UC_SET_OUT_TGEN_BASIC_1://= 0x0110,
        //    case UC_SET_OUT_TGEN_BASIC_2://= 0x0111,
        //    case UC_SET_OUT_TGEN_ADV://= 0x0112,
        break;
    case UC_SET_OUT_LVDS_MODE://= 0x0201,
        MDrv_Ursa_8_SetOutLvdsModeData ( pBuffer );
        break;
    case UC_SET_OUT_LVDS_SWAP://= 0x0202,
        MDrv_Ursa_8_SetOutLvdsSwapData ( pBuffer );
        break;
    case UC_SET_OUT_LVDS_CHANNELTYPE://= 0x0203,
        MDrv_Ursa_8_SetOutLvdsChannelTypeData ( pBuffer );
        break;

    case UC_SET_OUT_SWING_LELVEL://= 0x0204,
        MDrv_Ursa_8_SetOutLvdsSwingData ( pBuffer );
        break;
        //==3D mode CMD===
    case UC_SET_3DMODE:// = 0x3010, //No 3D; MEMC 240Hz
        MDrv_Ursa_8_Set3DModeData ( pBuffer );
        break;

        //==MFC level CMD ==
    case UC_SET_MFC_LEVEL://  = 0x3020,
        MDrv_Ursa_8_SetMFClevelData ( pBuffer );
        break;

        //==video mute/on CMD ==
    case UC_SET_VIDEO_MUTE://= 0x3030,
        MDrv_Ursa_8_SetVideoMuteData ( pBuffer );
        break;

    case UC_SET_GAIN_OFFSET://= 0x3040,
        MDrv_Ursa_8_SetGainOffsetData ( pBuffer );
        break;
    case UC_SET_OSD_WINDOWS_H://= 0x3050,
        MDrv_Ursa_8_SetOSDWinHData ( pBuffer );
        break;
    case UC_SET_OSD_WINDOWS_V://= 0x3060,
        MDrv_Ursa_8_SetOSDWinVData ( pBuffer );
        break;

    case UC_SET_PWM_DUTY_PHASE://= 0x3070,
        MDrv_Ursa_8_SetPwmDutyPhaseData ( pBuffer );
        break;
    case  UC_SET_SSC_FREQ_PERCENT:
        MDrv_Ursa_8_SetSSCFreqPercent ( pBuffer );
        break;
        /*
        		case UC_SET_LVDS_OFF://= 0x3080,
        			MDrv_Ursa_8_SetModPowerData(pBuffer);
        		break;

        		case UC_SET_LVDS_ON:// 0x3081,
        			MDrv_Ursa_8_SetModPowerData(pBuffer);
        		break;
        */
        /*
            case UC_SET_MOD_POWER://= 0x3070,
                  MDrv_Ursa_8_SetModPowerData(pBuffer);
        	break;
        */

    case UC_SET_2D_TO_3D://= 0x30a0,
        MDrv_Ursa_8_Set2Dto3DMode ( pBuffer );
        break;

    case UC_SET_HVMIRROR://= 0x30c0,
        MDrv_Ursa_8_SetHVMirrorMode ( pBuffer );
        break;

    case UC_SET_FRAMELOCK://= 0x30D0,
        MDrv_Ursa_8_SetFrameLockMode ( pBuffer );
        break;

    default:
        break;
    }

    MDrv_Ursa_8_CalCheckSum ( pBuffer, URSA_8_CMD_DATA_SUM);
    printf ( ">>CMD:%x,%x,%x,%x,%x,%x,%x\n", pBuffer[0], pBuffer[1], pBuffer[2],//xyy
             pBuffer[3], pBuffer[4], pBuffer[5], pBuffer[6] );//xyy
    bResult = MDrv_Ursa_8_3D_DataWrite (pBuffer );

    if ( bResult )
        printf ( "\nMDrv_Ursa_8_3D_Cmd write data success.....\n" );
    else
        printf ( "\nMDrv_Ursa_8_3D_Cmd write data fail.....\n" );

    return bResult;
}


MS_BOOL MDrv_Ursa_8_LVDS_Enalbe ( MS_BOOL bEnable )
{
    MS_BOOL bResult = FALSE;

    if ( bEnable )
    {
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_LVDS_ON );
    }
    else
    {
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_LVDS_OFF );
    }

    if ( bResult )
    {
        printf ( "sellect lvds on/off ok!!!\n" );
    }
    else
    {
        printf ( "sellect lvds on/off error!!!\n" );
    }

    return bResult;
}



void MDrv_Ursa_8_Data_Init ( void )
{
    MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
    MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
}


void MDrv_Ursa_8_CMD_Init ( void )
{
    g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = 0;//register 0x2328
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bsingleCh = FALSE;
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_evenodd = FALSE;
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_msblsb = FALSE;
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_pn = FALSE;
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode = FALSE;
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bTTL = FALSE;

    g_UrsaCMDGenSetting.g_InitOutAll1.bTIMode = FALSE;
    g_UrsaCMDGenSetting.g_InitOutAll1.bShiftPair = FALSE;
    g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPol = FALSE;
    g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPair = FALSE ;
    g_UrsaCMDGenSetting.g_InitOutAll1.PanelBitNums = 0;
    g_UrsaCMDGenSetting.g_InitOutAll1.bDither8Bits = FALSE;
    g_UrsaCMDGenSetting.g_InitOutAll1.bDitherEn = FALSE;
    g_UrsaCMDGenSetting.g_InitOutAll1.SwapCh = 0;
    g_UrsaCMDGenSetting.g_InitOutAll1.PanelType = 0;
    g_UrsaCMDGenSetting.g_InitOutAll1.PanelChannel = 0;

    g_UrsaCMDGenSetting.g_InitOutAll2.VTotal = 0;
    g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_high = 0;
    g_UrsaCMDGenSetting.g_InitOutAll2.HTotal = 0;
    g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_low = 0;

    g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight = 0;
    g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_high = 0;
    g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth = 0;
    g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_low = 0;

    g_UrsaCMDGenSetting.g_OutLvdsMode.Reserve = 0;
    g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = 0;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode = FALSE;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol = FALSE;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsShiftPair = FALSE;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPair = FALSE;

    g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0;//register 0x321F

    g_UrsaCMDGenSetting.g_OutLvdsChannelType.Reserve = 0;
    g_UrsaCMDGenSetting.g_OutLvdsChannelType.PanelChannel = 0;

    g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 0;//= 0x0202

    g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0;
    g_UrsaCMDGenSetting.g_3DMode.Reserve = 0;
    g_UrsaCMDGenSetting.g_3DMode.bL_Only = FALSE;
    g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = FALSE;//D3 BIT0

    g_UrsaCMDGenSetting.g_MFCLevel.MFClevel = 0;

    g_UrsaCMDGenSetting.g_VideoMute.Reserve = 0;
    g_UrsaCMDGenSetting.g_VideoMute.bMute = FALSE;

    g_UrsaCMDGenSetting.g_GainOffset.AdjustIdx = 0;
    g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue = 0;

    g_UrsaCMDGenSetting.g_OSDWinH.Reserve = 0;
    g_UrsaCMDGenSetting.g_OSDWinH.WinID = 0;
    g_UrsaCMDGenSetting.g_OSDWinH.bWinEn = FALSE;
    g_UrsaCMDGenSetting.g_OSDWinH.WinHStart = 0;
    g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd = 0;

    g_UrsaCMDGenSetting.g_OSDWinV.Reserve = 0;
    g_UrsaCMDGenSetting.g_OSDWinV.WinID = 0;
    g_UrsaCMDGenSetting.g_OSDWinV.bWinEn = FALSE;
    g_UrsaCMDGenSetting.g_OSDWinV.WinVStart = 0;
    g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd = 0;

    g_UrsaCMDGenSetting.g_PwmDutyPhase.Reserve = 0;
    g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPolarity = 1;
    g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH = 1;
    g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty = 0;
    g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase = 0;

    g_UrsaCMDGenSetting.g_SscFreqPercent.Reserve = 0;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscSel = 1;
    g_UrsaCMDGenSetting.g_SscFreqPercent.Reserve1 = 0;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscEN = 0;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscFreq = 0;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscPercent = 0;


    g_UrsaCMDGenSetting.g_ModPower.Reserve = 0;
    g_UrsaCMDGenSetting.g_ModPower.bOnOff = FALSE;

    g_UrsaCMDGenSetting.g_2Dto3D.Reserve = 0;
    g_UrsaCMDGenSetting.g_2Dto3D.bConcave = 1;
    g_UrsaCMDGenSetting.g_2Dto3D.bEnable2Dto3D = 0;
    g_UrsaCMDGenSetting.g_2Dto3D.Gain = 0;
    g_UrsaCMDGenSetting.g_2Dto3D.ArtificalGain = 0;
    g_UrsaCMDGenSetting.g_2Dto3D.Offset = 0;

    g_UrsaCMDGenSetting.g_HVMirror.Reserve = 0;
    g_UrsaCMDGenSetting.g_HVMirror.bVMirror = 0;
    g_UrsaCMDGenSetting.g_HVMirror.bHMirror = 0;

    g_UrsaCMDGenSetting.g_FrameLock.bFrameLock = 0;
}

void MDrv_Ursa_8_SetInitInLvdsAllData ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_InitInLvdsAll.bsingleCh )
        u8Buf[2] |= BIT7;

    if ( g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode )
        u8Buf[2] |= BIT6;

    u8Buf[2] |= ( ( U8 ) ( g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums ) << 4 );

    if ( g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_evenodd )
        u8Buf[2] |= BIT3;

    if ( g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_pn )
        u8Buf[2] |= BIT2;

    if ( g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_msblsb )
        u8Buf[2] |= BIT1;

    if ( g_UrsaCMDGenSetting.g_InitInLvdsAll.bTTL )
        u8Buf[2] |= BIT0;
}

void MDrv_Ursa_8_SetInitOutAll1Data ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_InitOutAll1.bTIMode )
        u8Buf[2] |= BIT7;

    if ( g_UrsaCMDGenSetting.g_InitOutAll1.bShiftPair )
        u8Buf[2] |= BIT6;

    if ( g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPol )
        u8Buf[2] |= BIT5;

    if ( g_UrsaCMDGenSetting.g_InitOutAll1.bSwapPair )
        u8Buf[2] |= BIT4;

    if ( g_UrsaCMDGenSetting.g_InitOutAll1.bDither8Bits )
        u8Buf[2] |= BIT1;

    if ( g_UrsaCMDGenSetting.g_InitOutAll1.bDitherEn )
        u8Buf[2] |= BIT0;

    u8Buf[2] |= ( ( MS_U8 ) ( g_UrsaCMDGenSetting.g_InitOutAll1.PanelBitNums ) << 4 );

    u8Buf[3] = g_UrsaCMDGenSetting.g_InitOutAll1.SwapCh;

    u8Buf[4] |= ( ( MS_U8) ( g_UrsaCMDGenSetting.g_InitOutAll1.PanelType ) << 4 );
    u8Buf[4] |= ( MS_U8 ) g_UrsaCMDGenSetting.g_InitOutAll1.PanelChannel;
}

void MDrv_Ursa_8_SetInitOutAll2Data ( MS_U8 *u8Buf )
{
    u8Buf[2] = ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_InitOutAll2.VTotal ) >> 8 );
    u8Buf[3] = ( MS_U8 ) g_UrsaCMDGenSetting.g_InitOutAll2.VTotal;

    u8Buf[4] |= ( ( MS_U8 ) ( g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_high ) << 4 );
    u8Buf[4] |= ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_InitOutAll2.HTotal ) >> 8 );

    u8Buf[5] = ( MS_U8 ) g_UrsaCMDGenSetting.g_InitOutAll2.HTotal;

    u8Buf[6] = g_UrsaCMDGenSetting.g_InitOutAll2.De_XStart_low;
}

void MDrv_Ursa_8_SetInitOutAll3Data ( MS_U8 *u8Buf )
{
    u8Buf[2] = ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight ) >> 8 );
    u8Buf[3] = ( MS_U8 ) g_UrsaCMDGenSetting.g_InitOutAll3.PanelHeight;

    u8Buf[4] |= ( ( MS_U8 ) ( g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_high ) << 4 );
    u8Buf[4] |= ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth ) >> 8 );

    u8Buf[5] = ( MS_U8 ) g_UrsaCMDGenSetting.g_InitOutAll3.PanelWidth;

    u8Buf[6] = g_UrsaCMDGenSetting.g_InitOutAll3.De_YStart_low;
}

void MDrv_Ursa_8_SetOutLvdsModeData ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode )
        u8Buf[5] |= BIT3;

    if ( g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol )
        u8Buf[5] |= BIT2;

    if ( g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsShiftPair )
        u8Buf[5] |= BIT1;

    if ( g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPair )
        u8Buf[5] |= BIT0;
    u8Buf[5] |= ( ( MS_U8 ) ( g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums ) << 4 );
}
void MDrv_Ursa_8_SetOutLvdsSwapData ( MS_U8 *u8Buf )
{
    u8Buf[4] = g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh;
}

void MDrv_Ursa_8_SetOutLvdsChannelTypeData ( MS_U8 *u8Buf )
{
    u8Buf[2] = g_UrsaCMDGenSetting.g_OutLvdsChannelType.PanelChannel;
}

void MDrv_Ursa_8_SetOutLvdsSwingData ( MS_U8 *u8Buf )
{
    u8Buf[6] = g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing;
}

void MDrv_Ursa_8_Set3DModeData ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_3DMode.bL_Only )
        u8Buf[2] |= BIT0;
    else
        u8Buf[2] &= 0xfe;

    u8Buf[2] |= ( ( U8 ) ( g_UrsaCMDGenSetting.g_3DMode.Set3Dmode ) << 4 );

    if ( g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange )
        u8Buf[3] |= BIT0;
    else
        u8Buf[3] &= 0xfe;
}

void MDrv_Ursa_8_SetMFClevelData ( MS_U8 *u8Buf )
{
    u8Buf[2] = g_UrsaCMDGenSetting.g_MFCLevel.MFClevel;
}


void MDrv_Ursa_8_SetVideoMuteData ( MS_U8 *u8Buf )
{
    u8Buf[2] = ( U8 ) g_UrsaCMDGenSetting.g_VideoMute.bMute;
}

void MDrv_Ursa_8_SetGainOffsetData ( MS_U8 *u8Buf )
{
    //	u8Buf[0] = u8Buf[0] ;
    //	u8Buf[1] = u8Buf[1] ;
    u8Buf[2] = g_UrsaCMDGenSetting.g_GainOffset.AdjustIdx;
    u8Buf[3] = ( U8 ) ( ( g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue ) >> 8 );
    u8Buf[4] = ( U8 ) ( g_UrsaCMDGenSetting.g_GainOffset.wAdjustValue );
}

void MDrv_Ursa_8_SetOSDWinHData ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_OSDWinH.bWinEn )
        u8Buf[2] |= BIT0;

    u8Buf[2] |= ( ( U8 ) ( g_UrsaCMDGenSetting.g_OSDWinH.WinID ) << 1 );
    u8Buf[3] = ( U8 ) ( ( g_UrsaCMDGenSetting.g_OSDWinH.WinHStart ) >> 8 );
    u8Buf[4] = ( U8 ) ( g_UrsaCMDGenSetting.g_OSDWinH.WinHStart );
    u8Buf[5] = ( U8 ) ( ( g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd ) >> 8 );
    u8Buf[6] = ( U8 ) ( g_UrsaCMDGenSetting.g_OSDWinH.WinHEnd );
}

void MDrv_Ursa_8_SetOSDWinVData ( MS_U8  *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_OSDWinH.bWinEn )
        u8Buf[2] |= BIT0;

    u8Buf[2] |= ( ( U8 ) ( g_UrsaCMDGenSetting.g_OSDWinV.WinID ) << 1 );
    u8Buf[3] = ( U8 ) ( ( g_UrsaCMDGenSetting.g_OSDWinV.WinVStart ) >> 8 );
    u8Buf[4] = ( U8 ) ( g_UrsaCMDGenSetting.g_OSDWinV.WinVStart );
    u8Buf[5] = ( U8 ) ( ( g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd ) >> 8 );
    u8Buf[6] = ( U8 ) ( g_UrsaCMDGenSetting.g_OSDWinV.WinVEnd );
}

void MDrv_Ursa_8_SetPwmDutyPhaseData ( MS_U8 *u8Buf )
{
    u8Buf[2] = g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPolarity << 4;
    u8Buf[2] = g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmCH = 1;
    u8Buf[3] = ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty ) >> 8 );
    u8Buf[4] = ( MS_U8) ( g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmDuty );
    u8Buf[5] = ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase ) >> 8 );
    u8Buf[6] = ( MS_U8 ) ( g_UrsaCMDGenSetting.g_PwmDutyPhase.PwmPhase );
}

void MDrv_Ursa_8_SetSSCFreqPercent ( MS_U8 *u8Buf )
{
    u8Buf[2] = g_UrsaCMDGenSetting.g_SscFreqPercent.SscSel << 4;
    u8Buf[2] |= g_UrsaCMDGenSetting.g_SscFreqPercent.SscEN;
    u8Buf[3] = ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_SscFreqPercent.SscFreq ) >> 8 );
    u8Buf[4] = ( MS_U8 ) ( g_UrsaCMDGenSetting.g_SscFreqPercent.SscFreq );
    u8Buf[5] = ( MS_U8 ) ( ( g_UrsaCMDGenSetting.g_SscFreqPercent.SscPercent ) >> 8 );
    u8Buf[6] = ( MS_U8 ) ( g_UrsaCMDGenSetting.g_SscFreqPercent.SscPercent );
}

void MDrv_Ursa_8_SetModPowerData ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_ModPower.bOnOff )
        u8Buf[2] |= BIT0;
}

void MDrv_Ursa_8_Set2Dto3DMode ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_2Dto3D.bConcave )
        u8Buf[2] |= BIT1;
    else
        u8Buf[2] &= 0xfd;

    if ( g_UrsaCMDGenSetting.g_2Dto3D.bEnable2Dto3D )
        u8Buf[2] |= BIT0;
    else
        u8Buf[2] &= 0xfe;

    u8Buf[3] |= g_UrsaCMDGenSetting.g_2Dto3D.Gain << 4;
    u8Buf[3] |= g_UrsaCMDGenSetting.g_2Dto3D.ArtificalGain;
    u8Buf[4] = g_UrsaCMDGenSetting.g_2Dto3D.Offset;

}

void MDrv_Ursa_8_SetHVMirrorMode ( MS_U8 *u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_HVMirror.bVMirror )
        u8Buf[2] |= BIT1;
    else
        u8Buf[2] &= 0xfd;

    if ( g_UrsaCMDGenSetting.g_HVMirror.bHMirror )
        u8Buf[2] |= BIT0;
    else
        u8Buf[2] &= 0xfe;
}

void MDrv_Ursa_8_SetFrameLockMode ( MS_U8 * u8Buf )
{
    if ( g_UrsaCMDGenSetting.g_FrameLock.bFrameLock )
        u8Buf[2] |= BIT0;
    else
        u8Buf[2] &= 0xfe;
}
// 3D OR 2D FORMAT
// buffer foramt:0x13,0x01,3D FOMART,0x00,0x00,0x00,0x00
// 2D:0x00
// 3D side bye side:0x10
// 3D Top and Bottom:0x20
// 3D frame alternative:0x30
MS_BOOL MDrv_Ursa_8_3D_MODE ( PANEL_3D_MODE ePanel3DMode )
{
    MS_BOOL bResult = FALSE;

    //if ( !bMstUrsa8Installed ) return bResult;

    // U8 buffer[7]={0,0,0,0,0,0,0} ;
    switch ( ePanel3DMode )
    {
    case PANEL_3D_MODE_HALF_SIDE_BY_SIDE:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 1;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_TOP_AND_BOTTOM:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 2;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_CHECKERBOARD:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 3;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_FRAME_INTERLEAVED:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 4;//3;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_LINE_INTERLEAVED:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 5;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_NONE:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_LONLY:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 1;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_LREXCHANGE:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    case PANEL_3D_MODE_PIXEL_INTERLEAVED:
    case PANEL_3D_MODE_MAXNUM:
        g_UrsaCMDGenSetting.g_3DMode.Set3Dmode = 0;
        g_UrsaCMDGenSetting.g_3DMode.bL_Only = 0;
        g_UrsaCMDGenSetting.g_3DMode.bLR_Exchange = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_3DMODE );
        break;

    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect 3d mode ok!!!\n" );
    }
    else
    {
        printf ( "sellect 3d mode error!!!\n" );
    }

    return bResult;
}

MS_BOOL MDrv_Ursa_8_2DTO3D_MODE ( PANEL_2D_TO_3D_MODE ePanel2DTO3DMode )
{
    MS_BOOL bResult = FALSE;

    // U8 buffer[7]={0,0,0,0,0,0,0} ;
   // if ( !bMstUrsa8Installed ) return bResult;

    switch ( ePanel2DTO3DMode )
    {

    case PANEL_3D_MODE_2D_TO_3D_ON:
        g_UrsaCMDGenSetting.g_2Dto3D.bConcave = 1;
        g_UrsaCMDGenSetting.g_2Dto3D.bEnable2Dto3D = 1;
        g_UrsaCMDGenSetting.g_2Dto3D.ArtificalGain = 0x0f;
        g_UrsaCMDGenSetting.g_2Dto3D.Offset = 0xd0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_2D_TO_3D );
        break;
    case PANEL_3D_MODE_2D_TO_3D_OFF:
        g_UrsaCMDGenSetting.g_2Dto3D.bConcave = 0;
        g_UrsaCMDGenSetting.g_2Dto3D.bEnable2Dto3D = 0;
        g_UrsaCMDGenSetting.g_2Dto3D.Gain = 0;
        g_UrsaCMDGenSetting.g_2Dto3D.ArtificalGain = 0;
        g_UrsaCMDGenSetting.g_2Dto3D.Offset = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_2D_TO_3D );
        break;

    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect 2d to 3d mode ok!!!\n" );
    }
    else
    {
        printf ( "sellect 2d to 3d mode error!!!\n" );
    }

    return bResult;
}

MS_BOOL MDrv_Ursa_8_SET_LVDS_IN_MODE ( SET_INPUT_LVDS_MODE eInputLvdsMode )
{
    MS_BOOL bResult = FALSE;
    // MS_U8 buffer[7]={0,0,0,0,0,0,0} ;

    //if ( !bMstUrsa8Installed ) return bResult;

    switch ( eInputLvdsMode )
    {

    case INPUT_DUAL_CHANNEL:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bsingleCh = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_SINGLE_CHANNEL:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bsingleCh = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_JEIDA_MODE:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_VESA_MODE:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;

    case INPUT_SIXBITNUMS:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_EIGHTBITNUMS:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_TENBITNUMS:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = 2;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;

    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect input lvds mode ok!!!\n" );
    }
    else
    {
        printf ( "sellect input lvds mode error!!!\n" );
    }

    return bResult;
}

MS_BOOL MDrv_Ursa_8_SET_LVDS_IN_Swap ( SET_INPUT_LVDS_SWAP eInputLvdsSwap )
{
    MS_BOOL bResult = FALSE;
    // MS_U8 buffer[7]={0,0,0,0,0,0,0} ;

    //if ( !bMstUrsa8Installed ) return bResult;

    switch ( eInputLvdsSwap )
    {
    case INPUT_SWAP_EVENODD_ON:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_evenodd = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_SWAP_EVENODD_OFF:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_evenodd = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_SWAP_PN_ON:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_pn = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_SWAP_PN_OFF:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_pn = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;

    case INPUT_SWAP_MSBLSB_ON:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_msblsb = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;
    case INPUT_SWAP_MSBLSB_OFF:
        g_UrsaCMDGenSetting.g_InitInLvdsAll.bSwap_msblsb = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_IN_LVDS_MODE );
        break;

    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect input lvds swap ok!!!\n" );
    }
    else
    {
        printf ( "sellect input lvds swap error!!!\n" );
    }

    return bResult;
}

MS_BOOL MDrv_Ursa_8_SET_LVDS_OUT_MODE ( SET_OUTPUT_LVDS_MODE eLvdsOutputMode )
{
    MS_BOOL bResult = FALSE;

    // MS_U8 buffer[7]={0,0,0,0,0,0,0} ;
    switch ( eLvdsOutputMode )
    {
    case OUTPUT_SIXBITNUMS:
        g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_EIGHTBITNUMS:
        g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_TENBITNUMS:
        g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = 2;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_JEIDA_MODE:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;

    case OUTPUT_VESA_MODE:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_LVDS_SWAPPOL_ON:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_LVDS_SWAPPOL_OFF:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_LVDS_SHIFTPAIR_ON:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsShiftPair = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_LVDS_SHIFTPAIR_OFF:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsShiftPair = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;

    case OUTPUT_LVDS_SWAPPAIR_ON:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPair = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    case OUTPUT_LVDS_SWAPPAIR_OFF:
        g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPair = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE );
        break;
    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect output lvds ok!!!\n" );
    }
    else
    {
        printf ( "sellect output lvds error!!!\n" );
    }

    return bResult;

}

MS_BOOL MDrv_Ursa_8_SET_LVDS_OUT_Swing ( SWING_LEVEL eLvdsOutputSwing )
{
    MS_BOOL bResult = FALSE;

    // MS_U8 buffer[7]={0,0,0,0,0,0,0} ;
   // if ( !bMstUrsa8Installed ) return bResult;

    switch ( eLvdsOutputSwing )
    {
    case SWING_LEVLE_100:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;
    case SWING_LEVLE_200:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;
    case SWING_LEVLE_300:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 2;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;
    case SWING_LEVLE_400:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 3;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;

    case SWING_LEVLE_500:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 4;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;
    case SWING_LEVLE_600:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 5;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;
    case SWING_LEVLE_700:
        g_UrsaCMDGenSetting.g_CtrlSwing.CtrlSwing = 6;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_SWING_LELVEL );
        break;
    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect output lvds swing ok!!!\n" );
    }
    else
    {
        printf ( "sellect output lvds swing error!!!\n" );
    }

    return bResult;

}

MS_BOOL MDrv_Ursa_8_SET_LVDS_OUT_MFC ( MFC_LEVEL_MODE eLvdsOutputMFC )
{
    MS_BOOL bResult = FALSE;

    // MS_U8 buffer[7]={0,0,0,0,0,0,0} ;
    if ( !bMstUrsa8Installed ) return bResult;

    switch ( eLvdsOutputMFC )
    {
    case MFC_OFF:
        g_UrsaCMDGenSetting.g_MFCLevel.MFClevel = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_MFC_LEVEL );
        break;
    case MFC_LOW:
        g_UrsaCMDGenSetting.g_MFCLevel.MFClevel = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_MFC_LEVEL );
        break;
    case MFC_MIDDLE:
        g_UrsaCMDGenSetting.g_MFCLevel.MFClevel = 2;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_MFC_LEVEL );
        break;
    case MFC_HIGH:
        g_UrsaCMDGenSetting.g_MFCLevel.MFClevel = 3;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_MFC_LEVEL );
        break;
    default:
        break;
    }

    if ( bResult )
    {
        printf ( "sellect output lvds mfc ok!!!\n" );
    }
    else
    {
        printf ( "sellect output lvds mfc error!!!\n" );
    }

    return bResult;

}

MS_BOOL MDrv_Ursa_8_VideoOutput_Mode ( VIDEO_OUTPUT_MODE eVideoOutputMode )
{
    MS_BOOL bResult = FALSE;

    //if ( !bMstUrsa8Installed ) return bResult;

    switch ( eVideoOutputMode )
    {
    case VIDEO_OUTPUT_UNMUTE:
        g_UrsaCMDGenSetting.g_VideoMute.bMute = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_VIDEO_MUTE );
        break;
    case VIDEO_OUTPUT_MUTE:
        g_UrsaCMDGenSetting.g_VideoMute.bMute = TRUE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_VIDEO_MUTE );
        break;
    default:
        g_UrsaCMDGenSetting.g_VideoMute.bMute = FALSE;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_VIDEO_MUTE );
    }

    if ( bResult )
    {
        printf ( "sellect video output mode ok!!!\n" );
    }
    else
    {
        printf ( "sellect video output mode error!!!\n" );
    }

    return bResult;
}


MS_BOOL MDrv_Ursa_8_ChanelSwap_Mode ( CHANNEL_SWAP_MODE eChanelSwap )
{
    MS_BOOL  bResult = FALSE;

    //if ( !bMstUrsa8Installed ) return bResult;

    switch ( eChanelSwap )
    {
    case CHANNEL_SWAP_MODE1://DCBA
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xE4;// SANSUNG SG
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE2://DCAB
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xE1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE3://DBCA
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xd8;//LG PANNEL PR
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE4://DBAC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xD2;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE5://DABC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xC6;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE6://DACB
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xC9;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE7://CDAB
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xB1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE8://CDBA
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xB4;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE9://CBAC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x92;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE10://CBCA
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x98;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE11://CABD
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x87;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE12://CADB
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x8D;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE13://BDAC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x72;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE14://BDCA
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x78;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE15://BCAD
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x63;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE16://BCDA
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x6C;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE17://BADC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x4E;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE18://BACD
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x4B;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE19://ADCB
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x39;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE20://ADBC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x36;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE21://ACBD
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x27;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE22://ACDB
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x2D;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE23://ABCD
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x1B;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case CHANNEL_SWAP_MODE24://ABDC
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0x1B;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;


    default :
        g_UrsaCMDGenSetting.g_OutLvdsSwap.LvdsSwapCh = 0xd8;//LG PANNEL PR
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;
    }

    if ( bResult )
    {
        printf ( "sellect channel swap mode ok!!!\n" );
    }
    else
    {
        printf ( "sellect video swap mode error!!!\n" );
    }

    return bResult;
}

MS_BOOL MDrv_Ursa_8_SET_HVMirror_Mode ( HVMIRROR_MODE eHVMirrorMode )
{
    MS_BOOL bResult = FALSE;

   // if ( !bMstUrsa8Installed ) return bResult;

    switch ( eHVMirrorMode )
    {
    case VMIRROR_ON:
        g_UrsaCMDGenSetting.g_HVMirror.bVMirror = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case VMIRROR_OFF:
        g_UrsaCMDGenSetting.g_HVMirror.bVMirror = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case HMIRROR_ON:
        g_UrsaCMDGenSetting.g_HVMirror.bHMirror = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_SWAP );
        break;

    case HMIRROR_OFF:
        g_UrsaCMDGenSetting.g_HVMirror.bHMirror = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_HVMIRROR );
        break;

    default :
        break;
    }

    if ( bResult )
    {
        printf ( "set hvmirror mode ok!!!\n" );
    }
    else
    {
        printf ( "set hvmirror mode error!!!\n" );
    }

    return bResult;
}

MS_BOOL MDrv_Ursa_8_SET_FrameLock_Mode ( FRAMELOCK_MODE eFrameLockMode )
{
    MS_BOOL bResult = FALSE;

    //if ( !bMstUrsa8Installed ) return bResult;

    switch ( eFrameLockMode )
    {
    case FRAMELOCK_ON:
        g_UrsaCMDGenSetting.g_FrameLock.bFrameLock = 1;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_FRAMELOCK );
        break;

    case FRAMELOCK_OFF:
        g_UrsaCMDGenSetting.g_FrameLock.bFrameLock = 0;
        bResult = MDrv_Ursa_8_3D_Cmd ( UC_SET_FRAMELOCK );
        break;

    default :
        break;
    }

    if ( bResult )
    {
        printf ( "set framelock mode ok!!!\n" );
    }
    else
    {
        printf ( "set framelock mode error!!!\n" );
    }

    return bResult;
}

#endif //__DRV_URSA_8_C__

