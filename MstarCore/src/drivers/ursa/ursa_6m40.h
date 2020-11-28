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

#ifndef __DRV_URSA_6M40_H__
#define __DRV_URSA_6M40_H__

#include <MsTypes.h>
#include <apiSWI2C.h>
#include <common.h>
#include <apiPNL.h>
//-------------------------------------------------------------------------------------------------
//  struction define
//-------------------------------------------------------------------------------------------------
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

extern URSA_CMD_GEN_SETTINGS g_UrsaCMDGenSetting;

typedef enum
{
    CMD_6M40_OSD_MUTE,
    CMD_6M40_OSD_ON,
    CMD_6M40_OSD_OFF,
    CMD_6M40_OSD_UNMUTE,
    CMD_6M40_LVDS_ON,
    CMD_6M40_LVDS_OFF,
    CMD_6M40_2K_MODE_ON,
    CMD_6M40_4K_MODE_ON,
    //sword add
    CMD_6M40_OSD_PROTECT_OFF,
    CMD_6M40_OSD_PROTECT_ON,
    CMD_6M40_OSD_PROTECT_ON_EMMC
}URSA_6M40_CMD_TYPE;

typedef enum
{
	URSA_6M40_OSD_PROTECT_OFF  , 
	URSA_6M40_OSD_PROTECT_ON  ,
	URSA_6M40_OSD_PROTECT_ON_EMMC  
}URSA_6M40_OSD_PROTECT_MODE;

typedef struct
{
    MS_U8 u8Cmd0;
    MS_U8 u8Cmd1;
    MS_U8 u8Cmd2;
    MS_U8 u8Cmd3;
    MS_U8 u8Cmd4;
    MS_U8 u8Cmd5;
    MS_U8 u8Cmd6;
}URSA_6M40_CMD_DATA;

typedef enum _FlashProgErrorType
{
    FlashEnterIspModeErr,
    FlashBlankingErr,
    FlashVerifyErr,
    FlashIDErr,
    FlashProgOK,
} FlashProgErrorType;

typedef enum _FlashProgStateType
{
    FlashProgStateInit,
    FlashProgStateEnterIsp,
    FlashProgStateErase,
    FlashProgStateBlank,
    FlashProgStateProgram,
    FlashProgStateVerify,
    FlashProgStateExit,
    FlashProgStateIdle,
} FlashProgStateType;

typedef struct
{
    MS_U32 size;				// 1-4
    MS_U8 manufacturer_id;	// 5
    MS_U8 device_id;			// 6

    // command
    MS_U8 WREN;				// 7
    MS_U8 WRDI;				// 8
    MS_U8 RDSR;				// 9
    MS_U8 WRSR;				// 10
    MS_U8 READS;				// 11
    MS_U8 FAST_READ;			// 12
    MS_U8 PG_PROG;			// 13
    MS_U8 SECTOR_ERASE;		// 14
    MS_U8 BLOCK_ERASE;		// 15
    MS_U8 CHIP_ERASE;		// 16
    MS_U8 RDID;				// 17
    MS_U8 LOCK;              // 18
    MS_U16 ChipEraseMaxTime;  // 19-20//Unit:100ms
} SFlashType;


typedef enum _FlashType
{
    Flash_PMC512,//PMC
    Flash_PMC010,
    Flash_PMC020,
    Flash_PMC040,
    Flash_EN25P10,//EON
    Flash_EN25P20,
    Flash_EN25P40,
    Flash_EN25P80,
    Flash_EN25F40,
    Flash_EN25F80,
    Flash_EN25F16,
    Flash_EN25P16,
    Flash_EN25B20,
    Flash_EN25B40,
    Flash_EN25B40T,
    Flash_EN25B16,
    Flash_EN25B16T,
    Flash_EN25B32,
    Flash_S25FL004A,//SPANSION
    Flash_S25FL016A,
    Flash_S25FL040A,
    Flash_NX25P16,//Winbond & NX
    Flash_W25X10,//not test
    Flash_W25X20,//not test
    Flash_W25X40,//not test
    Flash_W25P20,//not test
    Flash_W25P40,
    Flash_W25X16,
    Flash_W25X32,
    Flash_W25X64,
    Flash_SST25VF016B,//SST
    Flash_SST25VF040B,//not test
    Flash_MX25L4005A,//MX
    Flash_MX25L8005,//MX
    Flash_MX25L2005,//not test
    Flash_MX25L1605,
    Flash_MX25L3205,
    Flash_MX25L6405,
    Flash_QB25F160S,//intel QB25F160S33B8
    Flash_QB25F320S,//intel QB25F320S33B8
    Flash_QB25F640S,//intel QB25F640S33B8
    Flash_A25L40P,//AMIC A25L40P
    Flash_GD25Q32,//GD
    Flash_EN25Q32A,//EN
    Flash_NUMS,
} FlashType;

//-------------------------------------------------------------------------------------------------
//  Function declare
//-------------------------------------------------------------------------------------------------
void MDrv_Ursa_6M40_SWI2C_Init(void);
MS_BOOL MDrv_Ursa_6M40_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL MDrv_Ursa_6M40_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrnum, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
void MDrv_Ursa_6M40_Cmd_CheckSum(MS_U8 *pCmd, MS_U8 u8CmdLen);
MS_BOOL MDrv_Ursa_6M40_SendCmd(URSA_6M40_CMD_TYPE eCmdType);
MS_BOOL MDrv_Ursa_6M40_Write_Cmd(MS_U8 *pu8CmdData);
MS_BOOL MDrv_Ursa_6M40_Write_Cmd_Array(URSA_6M40_CMD_DATA *pCmdArray, MS_U8 u8ArraySize);

MS_BOOL MDrv_Ursa_6M40_Set_Osd_On(void);
MS_BOOL MDrv_Ursa_6M40_Set_Osd_Off(void);
MS_BOOL MDrv_Ursa_6M40_Set_Osd_Mute(void);
MS_BOOL MDrv_Ursa_6M40_Set_Osd_Unmute(void);
MS_BOOL MDrv_Ursa_6M40_Set_Lvds_On(void);
MS_BOOL MDrv_Ursa_6M40_Set_Lvds_Off(void);
MS_BOOL MDrv_Ursa_6M40_Set_2K_Mode_On(void);
MS_BOOL MDrv_Ursa_6M40_Set_VB1_Init(APIPNL_LINK_EXT_TYPE eLinkExtType);


MS_U8 MDrv_Ursa_6M40__ReadChipJEDEC_ID(MS_U8 *ReadIDBuf);
MS_U8 MDrv_Ursa_6M40_ReadChipID(void);
MS_U8 MDrv_Ursa_6M40_ReadChipIDBuffer(MS_U8 *ReadIDBuf);
void MDrv_Ursa_6M40_SWI2C_WriteDatas(MS_U8 * paddr, MS_U8 addrSize, MS_U8  * pdatabuf, MS_U8 dataSize);
void MDrv_Ursa_6M40_SWI2C_WriteStop(void);
void MDrv_Ursa_6M40_SWI2C_ReadDatas(MS_U8  * paddr, MS_U8 addrSize, MS_U8 * pdatabuf, MS_U8 dataSize);
void MDrv_Ursa_6M40_SWI2C_CommandRead(void);

MS_BOOL MDrv_Ursa_6M40_EnterIspMode(void);
MS_BOOL MDrv_Ursa_6M40_ExitIspMode(void);
void MDrv_Ursa_6M40_WP_PullHigh(void);

#endif //__DRV_URSA_6M40_H__

