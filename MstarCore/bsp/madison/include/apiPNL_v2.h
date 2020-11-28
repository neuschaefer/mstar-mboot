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
// comply with all applicable laws and regulations
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
//    or otherwise
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

#ifndef _API_XC_PANEL_V2_H_
#define _API_XC_PANEL_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
//******** ENUM DEFINITIONS ********//
typedef enum
{
    E_PNL_POOL_ID_INTERNAL = 0,

    E_PNL_POOL_ID_NUM,
    E_PNL_POOL_ID_MAX = E_PNL_POOL_ID_NUM,
} E_PNL_POOL_ID;

typedef enum
{
    E_PNL_CMD_GETLIBVER,
    E_PNL_CMD_GETINFO,
    E_PNL_CMD_GETSTATUS,
    E_PNL_CMD_GETSTATUSEX,
    E_PNL_CMD_SETDBGLEVEL,
    E_PNL_CMD_IOMAPBASEINIT,
    E_PNL_CMD_PREINIT,
    E_PNL_CMD_INIT,
    E_PNL_CMD_INIT_EX,
    E_PNL_CMD_SETOUTPUT,
    E_PNL_CMD_CHANGEPANELTYPE,
    E_PNL_CMD_TCONMAP_DUMPTABLE,
    E_PNL_CMD_TCONMAP_POWER_SEQUENCE,
    E_PNL_CMD_TCON_COUNT_RESET,
    E_PNL_CMD_TCON_INIT,
    E_PNL_CMD_GETDSTINFO,
    E_PNL_CMD_CONTROL_OUT_SWING,
    E_PNL_CMD_SET_OUTPUT_PATTERN,
    E_PNL_CMD_MOD_CALIBRATION_SETTING,
    E_PNL_CMD_MOD_DO_CALIBRATION,
    E_PNL_CMD_BD_LVDS_OUTPUT_TYPE,
    E_PNL_CMD_SETLPLLTYPEEXT,
    E_PNL_CMD_INIT_MISC,
    E_PNL_CMD_GET_MISC_STATUS,
    E_PNL_CMD_MOD_OUTPUTCONFIG_USER,
    E_PNL_CMD_HWLVDSRESERVEDTOLRFLAG,
    E_PNL_CMD_MOD_PVDD_POWER_SETTING,
    E_PNL_CMD_SETSSC_EN,
    E_PNL_CMD_SETSSC_FMODULATION,
    E_PNL_CMD_SETSSC_RDEVIATION,
    E_PNL_CMD_SETOSDSSC_EN,
    E_PNL_CMD_SETOSDSSC_FMODULATION,
    E_PNL_CMD_SETOSDSSC_RDEVIATION,
    E_PNL_CMD_SKIPTIMINGCHANGE,
    E_PNL_CMD_PRE_SET_MODE_ON,
    E_PNL_CMD_OVERDRIVER_INIT,
    E_PNL_CMD_OVERDRIVER_ENABLE,
    E_PNL_CMD_GET_LPLL_TYPE,
    E_PNL_CMD_GET_TCON_CAPABILITY,
    E_PNL_CMD_SETPAIRSWAP,
    E_PNL_CMD_SET_EXT_LPLL_TYPE,
    E_PNL_CMD_CALEXTLPLLSETBYDCLK,
    E_PNL_CMD_SETDIFFSWINGLEVEL,
    E_PNL_CMD_SETPOWERSTATE,
    E_PNL_CMD_FORCESETPANELDCLK,
    E_PNL_CMD_ENABLEINTERNALTERMINATION,
    E_PNL_CMD_OUTPUTDEVICEHANDSHAKE,
    E_PNL_CMD_OUTPUTDEVICEOCHANDSHAKE,
    E_PNL_CMD_SETOUTPUTINTERLACETIMING,
    E_PNL_CMD_NUM,
    E_PNL_CMD_MAX = E_PNL_CMD_NUM,
} E_PNL_IOCTL_CMDS;

typedef struct _stPNL_GetLibVer
{
    const MSIF_Version **ppVersion;
    APIPNL_Result eResult;
} stPNL_GetLibVer, *pstPNL_GetLibVer;

typedef struct _stPNL_GetInfo
{
    const PNL_ApiInfo *pApiInfo;
} stPNL_GetInfo, *pstPNL_GetInfo;

typedef struct _stPNL_GetStatus
{
    PNL_ApiStatus *pPnlStatus;
    MS_BOOL bReturn;
} stPNL_GetStatus, *pstPNL_GetStatus;

typedef struct _stPNL_GetStatusEx
{
    PNL_ApiExtStatus *pPnlExtStatus;
    MS_BOOL bReturn;
} stPNL_GetStatusEx, *pstPNL_GetStatusEx;

typedef struct _stPNL_SetDbgLevel
{
    MS_U16 u16DbgSwitch;
    MS_BOOL bReturn;
} stPNL_SetDbgLevel, *pstPNL_SetDbgLevel;

typedef struct _stPNL_IOMapBaseInit
{
    MS_BOOL bReturn;
} stPNL_IOMapBaseInit, *pstPNL_IOMapBaseInit;

typedef struct _stPNL_PreInit
{
    E_PNL_PREINIT_OPTIONS eInitParam;
    MS_BOOL bReturn;
} stPNL_PreInit, *pstPNL_PreInit;

typedef struct _stPNL_Init
{
    PanelType *pSelPanelType;
    MS_BOOL bReturn;
} stPNL_Init, *pstPNL_Init;

typedef struct _stPNL_Init_Ex
{
    PanelType *pSelPanelType;
    MSIF_Version LIBVER;
    MS_BOOL bReturn;
} stPNL_Init_Ex, *pstPNL_Init_Ex;

typedef struct _stPNL_SetOutput
{
    APIPNL_OUTPUT_MODE eOutputMode;
} stPNL_SetOutput, *pstPNL_SetOutput;

typedef struct _stPNL_ChangePanelType
{
    PanelType *pSelPanelType;
    MS_BOOL bReturn;
} stPNL_ChangePanelType, *pstPNL_ChangePanelType;

typedef struct _stPNL_TCONMAP_DumpTable
{
    MS_U8 *pTCONTable;
    MS_U8 u8Tcontype;
    MS_BOOL bReturn;
} stPNL_TCONMAP_DumpTable, *pstPNL_TCONMAP_DumpTable;

typedef struct _stPNL_TCONMAP_Power_Sequence
{
    MS_U8 *pTCONTable;
    MS_BOOL bEnable;
    MS_BOOL bReturn;
} stPNL_TCONMAP_Power_Sequence, *pstPNL_TCONMAP_Power_Sequence;

typedef struct _stPNL_TCON_Count_Reset
{
    MS_BOOL bEnable;
} stPNL_TCON_Count_Reset, *pstPNL_TCON_Count_Reset;

typedef struct _stPNL_TCON_Init
{
} stPNL_TCON_Init, *pstPNL_TCON_Init;

typedef struct _stPNL_GetDstInfo
{
    MS_PNL_DST_DispInfo *pDstInfo;
    MS_U32 u32SizeofDstInfo;
    MS_BOOL bReturn;
} stPNL_GetDstInfo, *pstPNL_GetDstInfo;

typedef struct _stPNL_Control_Out_Swing
{
    MS_U16 u16Swing_Level;
    MS_BOOL bReturn;
} stPNL_Control_Out_Swing, *pstPNL_Control_Out_Swing;

typedef struct _stPNL_SetOutputPattern
{
    MS_BOOL bEnable;
    MS_U16 u16Red;
    MS_U16 u16Green;
    MS_U16 u16Blue;
} stPNL_SetOutputPattern, *pstPNL_SetOutputPattern;

typedef struct _stPNL_Mod_Calibration_Setting
{
	MS_PNL_ModCaliInfo *pstModCaliInfo;
	MS_BOOL bReturn;
} stPNL_Mod_Calibration_Setting, *pstPNL_Mod_Calibration_Setting;

typedef struct _stPNL_Mod_Do_Calibration
{
    MS_BOOL bReturn;
} stPNL_Mod_Do_Calibration, *pstPNL_Mod_Do_Calibration;

typedef struct _stPNL_BD_LVDS_Output_Type
{
    MS_U16 Type;
} stPNL_BD_LVDS_Output_Type, *pstPNL_BD_LVDS_Output_Type;

typedef struct _stPNL_SetLPLLTypeExt
{
    APIPNL_LINK_EXT_TYPE eLPLL_TypeExt;
} stPNL_SetLPLLTypeExt, *pstPNL_SetLPLLTypeExt;

typedef struct _stPNL_Init_MISC
{
    APIPNL_MISC ePNL_MISC;
} stPNL_Init_MISC, *pstPNL_Init_MISC;

typedef struct _stPNL_Get_MISC_Status
{
    MS_U32 u32Status;
} stPNL_Get_MISC_Status, *pstPNL_Get_MISC_Status;

typedef struct _stPNL_MOD_OutputConfig_User
{
    MS_U32 u32OutputCFG0_7;
    MS_U32 u32OutputCFG8_15;
    MS_U32 u32OutputCFG16_21;
} stPNL_MOD_OutputConfig_User, *pstPNL_MOD_OutputConfig_User;

typedef struct _stPNL_HWLVDSReservedtoLRFlag
{
    MS_PNL_HW_LVDSResInfo lvdsresinfo;
} stPNL_HWLVDSReservedtoLRFlag, *pstPNL_HWLVDSReservedtoLRFlag;

typedef struct _stPNL_MOD_PVDD_Power_Setting
{
    MS_BOOL bIs2p5;
} stPNL_MOD_PVDD_Power_Setting, *pstPNL_MOD_PVDD_Power_Setting;

typedef struct _stPNL_SetSSC_En
{
    MS_BOOL bEnable;
    APIPNL_Result eReturn;
} stPNL_SetSSC_En, *pstPNL_SetSSC_En;

typedef struct _stPNL_SetSSC_Fmodulation
{
    MS_U16 u16Fmodulation;
    APIPNL_Result eReturn;
} stPNL_SetSSC_Fmodulation, *pstPNL_SetSSC_Fmodulation;

typedef struct _stPNL_SetSSC_Rdeviation
{
    MS_U16 u16Rdeviation;
    APIPNL_Result eReturn;
} stPNL_SetSSC_Rdeviation, *pstPNL_SetSSC_Rdeviation;

typedef struct _stPNL_SetOSDSSC_En
{
    MS_BOOL bEnable;
    APIPNL_Result eReturn;
} stPNL_SetOSDSSC_En, *pstPNL_SetOSDSSC_En;

typedef struct _stPNL_SetOSDSSC_Fmodulation
{
    MS_U16 u16Fmodulation;
    APIPNL_Result eReturn;
} stPNL_SetOSDSSC_Fmodulation, *pstPNL_SetOSDSSC_Fmodulation;

typedef struct _stPNL_SetOSDSSC_Rdeviation
{
    MS_U16 u16Rdeviation;
    APIPNL_Result eReturn;
} stPNL_SetOSDSSC_Rdeviation, *pstPNL_SetOSDSSC_Rdeviation;

typedef struct _stPNL_SkipTimingChange
{
    MS_BOOL bFlag;
    APIPNL_Result eResult;
} stPNL_SkipTimingChange, *pstPNL_SkipTimingChange;

typedef struct _stPNL_PreSetModeOn
{
    MS_BOOL bSetMode;
    APIPNL_Result eResult;
} stPNL_PreSetModeOn, *pstPNL_PreSetModeOn;

typedef struct _stPNL_OverDriver_Init
{
    MS_PNL_OD_INITDATA *pPNL_ODInitData;
    MS_U32 u32ODInitDataLen;
    APIPNL_Result eResult;
} stPNL_OverDriver_Init, *pstPNL_OverDriver_Init;

typedef struct _stPNL_OverDriver_Enable
{
    MS_BOOL bEnable;
    APIPNL_Result eResult;
} stPNL_OverDriver_Enable, *pstPNL_OverDriver_Enable;

typedef struct _stPNL_Get_LPLL_Type
{
    MS_U8 u8Return;
} stPNL_Get_LPLL_Type, *pstPNL_Get_LPLL_Type;

typedef struct _stPNL_Get_TCON_Capability
{
    MS_BOOL bReturn;
} stPNL_Get_TCON_Capability, *pstPNL_Get_TCON_Capability;

typedef struct _stPNL_SetPairSwap
{
    MS_U32 u32Polarity;
} stPNL_SetPairSwap, *pstPNL_SetPairSwap;

typedef struct _stPNL_SetExt_LPLL_Type
{
    MS_U16 u16Ext_lpll_type;
} stPNL_SetExt_LPLL_Type, *pstPNL_SetExt_LPLL_Type;

typedef struct _stPNL_CalExtLPLLSETbyDClk
{
    MS_U32 ldHz;
} stPNL_CalExtLPLLSETbyDClk, *pstPNL_CalExtLPLLSETbyDClk;

typedef struct _stPNL_SetDiffSwingLevel
{
    MS_U8 u8Swing_Level;
    MS_BOOL bReturn;
} stPNL_SetDiffSwingLevel, *pstPNL_SetDiffSwingLevel;

typedef struct _stPNL_SetPowerState
{
    EN_POWER_MODE ePowerState;
    MS_U32 u32Return;
} stPNL_SetPowerState, *pstPNL_SetPowerState;

typedef struct _stPNL_ForceSetPanelDCLK
{
    MS_U16 u16PanelDCLK;
    MS_BOOL bSetDCLKEnable;
    MS_BOOL bReturn;
} stPNL_ForceSetPanelDCLK, *pstPNL_ForceSetPanelDCLK;

typedef struct _stPNL_EnableInternalTermination
{
    MS_BOOL bEnable;
    MS_BOOL bReturn;
} stPNL_EnableInternalTermination, *pstPNL_EnableInternalTermination;

typedef struct _stPNL_OutputDeviceHandshake
{
    MS_BOOL bReturn;
} stPNL_OutputDeviceHandshake, *pstPNL_OutputDeviceHandshake;

typedef struct _stPNL_OutputDeviceOCHandshake
{
    MS_BOOL bReturn;
} stPNL_OutputDeviceOCHandshake, *pstPNL_OutputDeviceOCHandshake;

typedef struct _stPNL_SetOutputInterlaceTiming
{
    MS_BOOL bEnable;
    APIPNL_Result eReturn;
} stPNL_SetOutputInterlaceTiming, *pstPNL_SetOutputInterlaceTiming;

#ifdef __cplusplus
}
#endif

#endif
