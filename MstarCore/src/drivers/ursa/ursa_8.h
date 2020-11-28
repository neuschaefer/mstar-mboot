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

#ifndef __DRV_URSA_8_H__
#define __DRV_URSA_8_H__

#ifdef __DRV_URSA_8_C__
#define URSA_INTERFACE
#else
#define URSA_INTERFACE extern
#endif

#include <common.h>
#include <MsTypes.h>
#include <apiSWI2C.h>

#include <ShareType.h>
#if(CONFIG_MSTARI2C == 1)
#include <apiSWI2C.h>
#endif

#define  IIC_MODE  EN_IIC_DDC2BI_MODE

#define BOOLEAN MS_BOOL
#define MAPI_BOOL MS_BOOL
#define MAPI_U8 U8
#define MAPI_U16 U16
#define MAPI_TRUE TRUE
#define MAPI_U32 U32







//-------------------------------------------------------------------------------------------------
//  struction define
//-------------------------------------------------------------------------------------------------
typedef enum
{
    URSA_8_CMD_OSD_MUTE,
    URSA_8_CMD_OSD_ON,
    URSA_8_CMD_OSD_OFF,
    URSA_8_CMD_OSD_UNMUTE,
    URSA_8_CMD_LVDS_ON,
    URSA_8_CMD_LVDS_OFF,
    URSA_8_CMD_LVDS_SWING,
    URSA_8_CMD_OSD_PROTECT_OFF,
    URSA_8_CMD_OSD_PROTECT_ON,
    URSA_8_CMD_OSD_PROTECT_ON_EMMC
    
}URSA_8_CMD_TYPE;
typedef enum
{
	URSA_8_OSD_PROTECT_OFF  , 
	URSA_8_OSD_PROTECT_ON  ,
	URSA_8_OSD_PROTECT_ON_EMMC  
}URSA_8_OSD_PROTECT_MODE;

//-------------------------------------------------------------------------------------------------
//  Function declare
//-------------------------------------------------------------------------------------------------
typedef enum
{
    PANEL_3D_MODE_HALF_SIDE_BY_SIDE = 0,
    PANEL_3D_MODE_TOP_AND_BOTTOM,
    PANEL_3D_MODE_FRAME_INTERLEAVED,
    PANEL_3D_MODE_PIXEL_INTERLEAVED,
    PANEL_3D_MODE_LINE_INTERLEAVED,
    PANEL_3D_MODE_CHECKERBOARD,
    PANEL_3D_MODE_NONE,
    PANEL_3D_MODE_LONLY,
    PANEL_3D_MODE_LREXCHANGE,
    PANEL_3D_MODE_MAXNUM
} PANEL_3D_MODE;//command 0x301

typedef enum
{
    PANEL_3D_MODE_2D_TO_3D_ON,
    PANEL_3D_MODE_2D_TO_3D_OFF
} PANEL_2D_TO_3D_MODE;//command 0x30A


typedef enum
{
    CHANNEL_SWAP_MODE1 = 0,
    CHANNEL_SWAP_MODE2,
    CHANNEL_SWAP_MODE3,
    CHANNEL_SWAP_MODE4,
    CHANNEL_SWAP_MODE5,
    CHANNEL_SWAP_MODE6,
    CHANNEL_SWAP_MODE7,
    CHANNEL_SWAP_MODE8,
    CHANNEL_SWAP_MODE9,
    CHANNEL_SWAP_MODE10,
    CHANNEL_SWAP_MODE11,
    CHANNEL_SWAP_MODE12,
    CHANNEL_SWAP_MODE13,
    CHANNEL_SWAP_MODE14,
    CHANNEL_SWAP_MODE15,
    CHANNEL_SWAP_MODE16,
    CHANNEL_SWAP_MODE17,
    CHANNEL_SWAP_MODE18,
    CHANNEL_SWAP_MODE19,
    CHANNEL_SWAP_MODE20,
    CHANNEL_SWAP_MODE21,
    CHANNEL_SWAP_MODE22,
    CHANNEL_SWAP_MODE23,
    CHANNEL_SWAP_MODE24,
    CHANNEL_SWAP_MODEDETAULT = CHANNEL_SWAP_MODE1,
} CHANNEL_SWAP_MODE;//command 0x202

typedef enum
{
    INPUT_DUAL_CHANNEL = 0,
    INPUT_SINGLE_CHANNEL,
    INPUT_JEIDA_MODE,
    INPUT_VESA_MODE,
    INPUT_SIXBITNUMS,
    INPUT_EIGHTBITNUMS,
    INPUT_TENBITNUMS
} SET_INPUT_LVDS_MODE; //command 0x101

typedef enum
{
    INPUT_SWAP_EVENODD_ON = 0,
    INPUT_SWAP_EVENODD_OFF,
    INPUT_SWAP_PN_ON,
    INPUT_SWAP_PN_OFF,
    INPUT_SWAP_MSBLSB_ON,
    INPUT_SWAP_MSBLSB_OFF
} SET_INPUT_LVDS_SWAP; //command 0x102

typedef enum
{
    OUTPUT_SIXBITNUMS = 0,
    OUTPUT_EIGHTBITNUMS,
    OUTPUT_TENBITNUMS,
    OUTPUT_JEIDA_MODE,
    OUTPUT_VESA_MODE,
    OUTPUT_LVDS_SWAPPOL_ON,
    OUTPUT_LVDS_SWAPPOL_OFF,
    OUTPUT_LVDS_SHIFTPAIR_ON,
    OUTPUT_LVDS_SHIFTPAIR_OFF,
    OUTPUT_LVDS_SWAPPAIR_ON,
    OUTPUT_LVDS_SWAPPAIR_OFF
} SET_OUTPUT_LVDS_MODE; //command 0x201

typedef enum
{
    SWING_LEVLE_100 = 0,
    SWING_LEVLE_200,
    SWING_LEVLE_300,
    SWING_LEVLE_400,
    SWING_LEVLE_500,
    SWING_LEVLE_600,
    SWING_LEVLE_700
} SWING_LEVEL; //command 0x204

typedef enum
{
    MFC_OFF = 0,
    MFC_LOW,
    MFC_MIDDLE,
    MFC_HIGH
} MFC_LEVEL_MODE;//command 0x302

typedef enum
{
    VIDEO_OUTPUT_UNMUTE = 0,
    VIDEO_OUTPUT_MUTE,
    VIDEO_OUTPUT_DEFAULT = VIDEO_OUTPUT_UNMUTE,
} VIDEO_OUTPUT_MODE;//command 0x303

typedef enum
{
    VMIRROR_ON = 0,
    VMIRROR_OFF,
    HMIRROR_ON,
    HMIRROR_OFF
} HVMIRROR_MODE;//command 0x30C

typedef enum
{
    FRAMELOCK_OFF = 0,
    FRAMELOCK_ON
} FRAMELOCK_MODE;//command 0x30D

typedef struct
{
    MS_U8    CMDIdx0;    //0st    [3:0]->CmdIdx[11:8],[7:4]->Checksum;
    MS_U8    CMDIdx1;    // 1st    [7:0]->CmdIdx[7:0]
    MS_U8    CMDIdx2;    // 2nd   CMD data
    MS_U8    CMDIdx3;    // 3rd   CMD data
    MS_U8    CMDIdx4;    // 4th   CMD data
    MS_U8    CMDIdx5;    // 5th   CMD data
    MS_U8    CMDIdx6;    // 6th   CMD data
} URSA_CMD_DATA;

typedef struct
{
    MS_U8    bsingleCh: 1;
    MS_U8    bTIMode: 1;
    MS_U8    BitNums: 2;
    MS_U8    bSwap_evenodd: 1;
    MS_U8    bSwap_pn: 1;
    MS_U8    bSwap_msblsb: 1;
    MS_U8    bTTL: 1;
} URSA_CMD_INIT_IN_LVDSALL_DATA;

typedef struct
{
    MS_U8    bTIMode: 1;
    MS_U8    bShiftPair: 1;
    MS_U8    bSwapPol: 1;
    MS_U8    bSwapPair: 1;
    MS_U8    PanelBitNums: 2;
    MS_U8    bDither8Bits: 1;
    MS_U8    bDitherEn: 1;
    MS_U8    SwapCh;
    MS_U8    PanelType: 4;
    MS_U8    PanelChannel: 4;
} URSA_CMD_INIT_OUT_ALL_1_DATA;

typedef struct
{
    MS_U16    VTotal;
    MS_U16    De_XStart_high: 4;
    MS_U16    HTotal: 12;
    MS_U8      De_XStart_low;
} URSA_CMD_INIT_OUT_ALL_2_DATA;

typedef struct
{
    MS_U16    PanelHeight;
    MS_U16    De_YStart_high: 4;
    MS_U16    PanelWidth: 12;
    MS_U8      De_YStart_low;
} URSA_CMD_INIT_OUT_ALL_3_DATA;

typedef struct
{
    MS_U8    Reserve: 3;
    MS_U8    PanelBitNums: 2;
    MS_U8    bTIMode: 1;
    MS_U8    bLvdsSwapPol: 1;
    MS_U8    bLvdsShiftPair: 1;
    MS_U8    bLvdsSwapPair: 1;
} URSA_CMD_OUT_LVDS_MODE_DATA;

typedef struct
{
    MS_U8    LvdsSwapCh;
} URSA_CMD_OUT_LVDS_SWAP_DATA;

typedef struct
{
    MS_U8    Reserve: 4;
    MS_U8    PanelChannel: 4;
} URSA_CMD_OUT_LVDS_CHANNELTYPE_DATA;

typedef struct
{
    MS_U8    Reserve: 1;
    MS_U8    CtrlSwing: 4;
    MS_U8    Reserve1: 3;
} URSA_CMD_SWING_DATA;

typedef struct
{
    MS_U8    Set3Dmode: 4;
    MS_U8    Reserve: 3;
    MS_U8    bL_Only: 1;
    MS_U8    Reserve1: 7;
    MS_U8    bLR_Exchange: 1;
} URSA_CMD_3D_MODE_DATA;

typedef struct
{
    MS_U8    MFClevel;
} URSA_CMD_MFC_LEVEL_DATA;

typedef struct
{
    MS_U8    Reserve: 7;
    MS_U8    bMute: 1;
} URSA_CMD_VIDEO_MUTE_DATA;

typedef struct
{
    MS_U8    AdjustIdx;
    MS_U16  wAdjustValue;
} URSA_CMD_GAIN_OFFSET_DATA;

typedef struct
{
    MS_U8    Reserve: 4;
    MS_U8    WinID: 3;
    MS_U8    bWinEn: 1;
    MS_U16  WinHStart;
    MS_U16  WinHEnd;
} URSA_CMD_OSD_WINDOWS_H_DATA;
typedef struct
{
    MS_U16  protect_mode;
} URSA_CMD_OSD_PROTECT_MOdE;

typedef struct
{
    MS_U8    Reserve: 4;
    MS_U8    WinID: 3;
    MS_U8    bWinEn: 1;
    MS_U16  WinVStart;
    MS_U16  WinVEnd;
} URSA_CMD_OSD_WINDOWS_V_DATA;

typedef struct
{
    MS_U8    Reserve: 3;
    MS_U8    PwmPolarity: 1;
    MS_U8    PwmCH: 4;
    MS_U16  PwmDuty;
    MS_U16  PwmPhase;
} URSA_CMD_DUTY_PHASE_DATA;

typedef struct
{
    MS_U8    Reserve: 3;
    MS_U8    SscSel: 1; // 0 :MIU , 1: LVDS
    MS_U8    Reserve1: 3;
    MS_U8    SscEN: 1; //  0:disable, 1 enable
    MS_U16   SscFreq;
    MS_U16   SscPercent;
} URSA_CMD_FREQ_PERCENT_DATA;


typedef struct
{
    MS_U8    Reserve: 7;
    MS_U8    bOnOff: 1;
} URSA_CMD_MOD_POWER_DATA;

typedef struct
{
    MS_U8    Reserve: 6;
    MS_U8    bConcave: 1;
    MS_U8    bEnable2Dto3D: 1;
    MS_U8    Gain: 4;
    MS_U8    ArtificalGain: 4;
    MS_U8    Offset;
} URSA_CMD_2D_TO_3D_DATA;

typedef struct
{
    MS_U8    Reserve: 6;
    MS_U8    bVMirror: 1;
    MS_U8    bHMirror: 1;
} URSA_CMD_HVMIRROR_DATA;

typedef struct
{
    MS_U8    Reserve: 7;
    MS_U8    bFrameLock: 1;
} URSA_CMD_FRAMELOCK_DATA;


typedef struct
{
    URSA_CMD_INIT_IN_LVDSALL_DATA   g_InitInLvdsAll;
    URSA_CMD_INIT_OUT_ALL_1_DATA   g_InitOutAll1;
    URSA_CMD_INIT_OUT_ALL_2_DATA   g_InitOutAll2;
    URSA_CMD_INIT_OUT_ALL_3_DATA   g_InitOutAll3;
    URSA_CMD_OUT_LVDS_MODE_DATA   g_OutLvdsMode;
    URSA_CMD_OUT_LVDS_SWAP_DATA   g_OutLvdsSwap;
    URSA_CMD_OUT_LVDS_CHANNELTYPE_DATA   g_OutLvdsChannelType;
    URSA_CMD_SWING_DATA    g_CtrlSwing;
    URSA_CMD_3D_MODE_DATA   g_3DMode;
    URSA_CMD_MFC_LEVEL_DATA   g_MFCLevel;
    URSA_CMD_VIDEO_MUTE_DATA   g_VideoMute;
    URSA_CMD_GAIN_OFFSET_DATA   g_GainOffset;
    URSA_CMD_OSD_WINDOWS_H_DATA   g_OSDWinH;
    URSA_CMD_OSD_WINDOWS_V_DATA   g_OSDWinV;
    URSA_CMD_DUTY_PHASE_DATA   g_PwmDutyPhase;
    URSA_CMD_FREQ_PERCENT_DATA   g_SscFreqPercent;
    URSA_CMD_MOD_POWER_DATA   g_ModPower;
    URSA_CMD_2D_TO_3D_DATA   g_2Dto3D;
    URSA_CMD_HVMIRROR_DATA  g_HVMirror;
    URSA_CMD_FRAMELOCK_DATA g_FrameLock;
	URSA_CMD_OSD_PROTECT_MOdE g_OsdMode;

} URSA_CMD_GEN_SETTINGS;

typedef enum
{
    UC_INIT_IN_ALL,//= 0x0001

    UC_INIT_FINISH,//= 0x0100

    UC_SET_IN_LVDS_MODE,//= 0x0101

    UC_SET_IN_LVDS_SWAP,//= 0x0102

    UC_SET_IN_LVDS_TTL,//= 0x0103

    UC_INIT_OUT_ALL_1,//= 0x0010

    UC_INIT_OUT_ALL_2,//= 0x0011

    UC_INIT_OUT_ALL_3,//= 0x0012

    //UC_SET_OUT_TGEN_BASIC_1,//= 0x0110

    //UC_SET_OUT_TGEN_BASIC_2,//= 0x0111

    //UC_SET_OUT_TGEN_ADV,//= 0x0112

    UC_SET_OUT_LVDS_MODE,//= 0x0201

    UC_SET_OUT_LVDS_SWAP,//= 0x0202

    UC_SET_OUT_LVDS_CHANNELTYPE,//= 0x0203

    UC_SET_OUT_SWING_LELVEL,//= 0x0204
    //==3D mode CMD==

    UC_SET_3DMODE,// = 0x3010, //No 3D; MEMC 240H



    //==MFC level CMD ==
    UC_SET_MFC_LEVEL,//  = 0x3020,


    //==video mute/on CMD ==
    UC_SET_VIDEO_MUTE,//= 0x3030,


    UC_SET_GAIN_OFFSET,//= 0x3040,
    UC_SET_OSD_WINDOWS_H,//= 0x3050,
    UC_SET_OSD_WINDOWS_V,//= 0x3060,


    UC_SET_PWM_DUTY_PHASE,//= 0x3070,


    UC_SET_LVDS_OFF,//= 0x3080,
    UC_SET_LVDS_ON, // 0x3081,
    UC_SET_SSC_FREQ_PERCENT, // 0x309,

    UC_SET_2D_TO_3D,//=0x30a0,

    UC_SET_HVMIRROR,//0x30c

    UC_SET_FRAMELOCK,//0x30d

    UC_SET_CMDTYPE_END, // EN_CMD Type index Max
} UC_CMD_TYPE;
URSA_INTERFACE MS_BOOL    bMstUrsa8Installed;

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_3D_Cmd ( UC_CMD_TYPE eCmdIdx ) ;
URSA_INTERFACE MS_BOOL MDrv_Ursa_8_LVDS_Enalbe ( MS_BOOL bEnable ) ;
URSA_INTERFACE URSA_CMD_GEN_SETTINGS g_UrsaCMDGenSetting;

URSA_INTERFACE  MS_BOOL MDrv_Ursa_8_3D_DataWrite ( MS_U8 *u8Buf );

URSA_INTERFACE void MDrv_Ursa_8__Data_Init ( void );

URSA_INTERFACE void MDrv_Ursa_8_CMD_Init ( void );


URSA_INTERFACE void MDrv_Ursa_8_SetInitInLvdsAllData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetInitOutAll1Data ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetInitOutAll2Data ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetInitOutAll3Data ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetOutLvdsModeData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetOutLvdsSwapData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetOutLvdsChannelTypeData ( MS_U8 *u8Buf );

URSA_INTERFACE void MDrv_Ursa_8_SetOutLvdsSwingData ( MS_U8 *u8Buf );


URSA_INTERFACE  void MDrv_Ursa_8_Set3DModeData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetMFClevelData ( MS_U8 *u8Buf );



URSA_INTERFACE void MDrv_Ursa_8_SetVideoMuteData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetGainOffsetData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetOSDWinHData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetOSDWinVData ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetPwmDutyPhaseData ( MS_U8 *u8Buf );
URSA_INTERFACE void MDrv_Ursa_8_SetSSCFreqPercent ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_SetModPowerData ( MS_U8 *u8Buf );

URSA_INTERFACE void MDrv_Ursa_8_Set2Dto3DMode ( MS_U8 *u8Buf );

URSA_INTERFACE void MDrv_Ursa_8_SetHVMirrorMode ( MS_U8 *u8Buf );
URSA_INTERFACE void MDrv_Ursa_8_SetFrameLockMode ( MS_U8 *u8Buf );


URSA_INTERFACE void MDrv_Ursa_8_CalCheckSum ( MS_U8 *pBuf, U8 u8BufLen );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_3D_MODE ( PANEL_3D_MODE ePanel3DMode );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_2DTO3D_MODE ( PANEL_2D_TO_3D_MODE ePanel2DTO3DMode );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_LVDS_IN_MODE ( SET_INPUT_LVDS_MODE eInputLvdsMode );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_LVDS_IN_Swap ( SET_INPUT_LVDS_SWAP eInputLvdsSwap );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_LVDS_OUT_MODE ( SET_OUTPUT_LVDS_MODE eLvdsOutputMode );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_LVDS_OUT_Swing ( SWING_LEVEL eLvdsOutputSwing );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_LVDS_OUT_MFC ( MFC_LEVEL_MODE eLvdsOutputMFC );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_VideoOutput_Mode ( VIDEO_OUTPUT_MODE eVideoOutputMode );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_ChanelSwap_Mode ( CHANNEL_SWAP_MODE eChanelSwap );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_HVMirror_Mode ( HVMIRROR_MODE eHVMirrorMode );

URSA_INTERFACE MS_BOOL MDrv_Ursa_8_SET_FrameLock_Mode ( FRAMELOCK_MODE eFrameLockMode );


void MDrv_Ursa_8_SWI2C_Init(void);
MS_BOOL MDrv_Ursa_8_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL MDrv_Ursa_8_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL MDrv_Ursa_8_SendCmd(URSA_8_CMD_TYPE eCmdType);
MS_BOOL MDrv_Ursa_8_Write_Cmd(MS_U8 *pu8CmdData);

MS_BOOL MDrv_Ursa_8_Set_Osd_On(void);
MS_BOOL MDrv_Ursa_8_Set_Osd_Off(void);
MS_BOOL MDrv_Ursa_8_Set_Osd_Mute(void);
MS_BOOL MDrv_Ursa_8_Set_Osd_Unmute(void);
MS_BOOL MDrv_Ursa_8_Set_Lvds_On(void);
MS_BOOL MDrv_Ursa_8_Set_Lvds_Off(void);
MS_BOOL MDrv_Ursa_8_Set_Lvds_Swing(void);

MS_BOOL MDrv_Ursa_8_Install ( void );
void  MDrv_Ursa_8_Initialize ( void );




#endif //__DRV_URSA_8_H__

