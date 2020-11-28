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
#ifndef _API_LTH_H_
#define _API_LTH_H_

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
//              define
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//              Enum
//------------------------------------------------------------------------------
typedef enum
{
    E_LTH_HDMITX_COLOR_RGB444,
    E_LTH_HDMITX_COLOR_YUV422,
    E_LTH_HDMITX_COLOR_YUV444,
}E_LTH_HDMITX_COLOR_TYPE;

typedef enum
{
    E_LTH_HDMITX_CD_8BITS = 0,
    E_LTH_HDMITX_CD_10BITS,
    E_LTH_HDMITX_CD_12BITS,
    E_LTH_HDMITX_CD_16BITS,
}E_LTH_HDMITX_CD_TYPE;

typedef enum
{
    E_LTH_HDMITX_480_60I,
    E_LTH_HDMITX_480_60P,
    E_LTH_HDMITX_576_50I,
    E_LTH_HDMITX_576_50P,
    E_LTH_HDMITX_720_50P,
    E_LTH_HDMITX_720_60P,
    E_LTH_HDMITX_1080_50I,
    E_LTH_HDMITX_1080_50P,
    E_LTH_HDMITX_1080_60I,
    E_LTH_HDMITX_1080_60P,
    E_LTH_HDMITX_1080_30P,
    E_LTH_HDMITX_1080_25P,
    E_LTH_HDMITX_1080_24P,
    E_LTH_HDMITX_4K2K_30P,
    E_LTH_HDMITX_1470_50P,
    E_LTH_HDMITX_1470_60P,
    E_LTH_HDMITX_1470_24P,
    E_LTH_HDMITX_1470_30P,
    E_LTH_HDMITX_2250_24P,
    E_LTH_HDMITX_2250_30P,
    E_LTH_HDMITX_4K2K_25P,
    E_LTH_HDMITX_1024x768_60P,
    E_LTH_HDMITX_1280x800_60P,
    E_LTH_HDMITX_1600x1200_60P,
    E_LTH_HDMITX_1920x1200_60P,
    E_LTH_HDMITX_TIMING_MAX,
}E_LTH_HDMITX_OUTPUT_TIMING_TYPE;


typedef enum
{
    E_LTH_HDMITX_AUDIO_SPDIF,
    E_LTH_HDMITX_AUDIO_I2S,
    E_LTH_HDMITX_AUDIO_NONE,
}E_LTH_HDMITX_AUDIO_TYPE;

typedef enum
{
    E_LTH_HDMITX_DBG_OP_TEST_PAT,
    E_LTH_HDMITX_DBG_OP_FREE_RUN,
    E_LTH_HDMITX_DBG_OP_LPLL_LOCK_MONITOR,
    E_LTH_HDMITX_DBG_OP_HTT_VTT_MONITOR,
    E_LTH_HDMITX_DBG_OP_MAX,
}E_LTH_HDMITX_DBG_OPERATOR_TYPE;

typedef enum
{
    E_LTH_HDMITX_INPUT_6_BITS,
    E_LTH_HDMITX_INPUT_8_BITS,
    E_LTH_HDMITX_INPUT_10_BITS,
}E_LTH_HDMITX_INPUT_DATA_BITS_TYPE;

//------------------------------------------------------------------------------
//              structure
//------------------------------------------------------------------------------

typedef struct
{
    E_LTH_HDMITX_OUTPUT_TIMING_TYPE enOutputTiming;
    E_LTH_HDMITX_CD_TYPE    enOutpuColorDepth;
}LTH_HDMITx_OUTPUTTIMING_CONFIG;


typedef struct
{
    MS_BOOL (*IIC_WriteBytes)(MS_U16 u16SlaveCfg, MS_U32 uAddrCnt, MS_U8 *pRegAddr, MS_U32 uSize, MS_U8 *pData);
    MS_BOOL (*IIC_ReadBytes)(MS_U16 u16SlaveCfg, MS_U32 uAddrCnt, MS_U8 *pRegAddr, MS_U32 uSize, MS_U8 *pData);
}LTH_IIC_CB_CONFIG;

typedef struct
{
    MS_BOOL bUseInternal;
    MS_BOOL (*HWI2C_ReadBytes)(MS_U16 u16SlaveCfg, MS_U32 uAddrCnt, MS_U8 *pRegAddr, MS_U32 uSize, MS_U8 *pData);
    MS_BOOL (*HWI2C_WriteBytes)(MS_U16 u16SlaveCfg, MS_U32 uAddrCnt, MS_U8 *pRegAddr, MS_U32 uSize, MS_U8 *pData);
}LTH_HWIIC_CONFIG;


typedef struct
{
    MS_BOOL bUseInternal;
    MS_BOOL (*HPD_Read)(void);
}LTH_HPD_CONFIG;


//------------------------------------------------------------------------------
//              prototype
//------------------------------------------------------------------------------


#ifdef _API_LTH_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void    MApi_Lth_Write2Byte(MS_U16 u16Addr, MS_U16 u16val);
INTERFACE MS_U16  MApi_Lth_Read2Byte(MS_U16 u16Addr);
INTERFACE void    MApi_Lth_WriteByte(MS_U16 u16Addr, MS_U8 u8val);
INTERFACE MS_U8   MApi_Lth_ReadByte(MS_U16 u16Addr);
INTERFACE MS_BOOL MApi_Lth_Load_OuputTimingSetting(E_LTH_HDMITX_OUTPUT_TIMING_TYPE enTimingType, E_LTH_HDMITX_CD_TYPE enCDType);
INTERFACE MS_BOOL MApi_Lth_Init_IIC_CB(LTH_IIC_CB_CONFIG IIC_CB);
INTERFACE MS_BOOL MApi_Lth_Init_HWIIC(LTH_HWIIC_CONFIG stHWIIC_Cfg);
INTERFACE MS_BOOL MApi_Lth_Init_HPD(LTH_HPD_CONFIG stHPD_Cfg);
INTERFACE MS_BOOL MApi_Lth_Set_IDAC(MS_BOOL bEn);
INTERFACE MS_BOOL MApi_Lth_Set_Audio(E_LTH_HDMITX_AUDIO_TYPE enAudioType);
INTERFACE MS_BOOL MApi_Lth_Set_ColorFormat(E_LTH_HDMITX_COLOR_TYPE enInColor);
INTERFACE MS_BOOL MApi_Lth_Init(void);
INTERFACE MS_BOOL MApi_Lth_Set_LPLL_Lock(MS_BOOL bEn);
INTERFACE void    MApi_Lth_Set_Dbg_Level(MS_U16 u16Level);
INTERFACE MS_BOOL MApi_Lth_GetLibVer(const MSIF_Version **ppVersion);
INTERFACE void    MApi_Lth_Set_Dbg_Mode(MS_BOOL bEn, E_LTH_HDMITX_DBG_OPERATOR_TYPE enOpType);
INTERFACE MS_BOOL MApi_Lth_Suspend_HWIIC(void);
INTERFACE MS_BOOL MApi_Lth_Resume_HWIIC(LTH_HWIIC_CONFIG stHWIIC_Cfg);
INTERFACE void    MApi_Lth_Set_Dump_All_Table_Setting(MS_BOOL bEn);
INTERFACE MS_BOOL MApi_Lth_Set_IDAC_BlackColor(MS_BOOL bEn);
INTERFACE MS_BOOL MApi_Lth_Wait_LPLL_Lock(MS_U32 u32Wait);
INTERFACE void    MApi_Lth_Set_Disable_All_Table_Setting(MS_BOOL bEn);
INTERFACE MS_BOOL MApi_Lth_Set_Input_Data_Bits(E_LTH_HDMITX_INPUT_DATA_BITS_TYPE enBits);
INTERFACE MS_BOOL MApi_Lth_Reset_Audio(MS_BOOL bEn);

#undef INTERFACE

#ifdef __cplusplus
}
#endif

#endif
