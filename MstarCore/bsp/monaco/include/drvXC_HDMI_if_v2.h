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

#ifndef _XC_HDMI_IF_H_
#define _XC_HDMI_IF_H_

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
    MS_U16 u16ReturnValue;
} stHDMI_FUNC_CAPS, *pstHDMI_FUNC_CAPS;

typedef struct
{
    HDMI_REST_t breset;
} stHDMI_PKT_RESET, *pstHDMI_PKT_RESET;

typedef struct
{
    MS_BOOL bHighLow;
    E_MUX_INPUTPORT enInputPortType;
    MS_BOOL bInverse;
} stHDMI_PULLHPD, *pstHDMI_PULLHPD;

typedef struct
{
    HDMI_GControl_INFO_t gcontrol;
    MS_U16 u16ReturnValue;
} stHDMI_GC_INFO, *pstHDMI_GC_INFO;

typedef struct
{
    MS_BOOL bEnable;
    MS_HDMI_PACKET_VALUE_t stReturnValue;
} stHDMI_PACKET_RECEIVED, *pstHDMI_PACKET_RECEIVED;

typedef struct
{
    MS_HDMI_COLOR_FORMAT eReturnValue;
} stHDMI_GET_COLORFORMAT, *pstHDMI_GET_COLORFORMAT;

typedef struct
{
    EN_HDMI_COLOR_RANGE eReturnValue;
} stHDMI_GET_COLORRANGE, *pstHDMI_GET_COLORRANGE;

typedef struct
{
    MS_HDMI_EQ enEq;
    MS_U8 u8EQValue;
} stHDMI_SET_EQ, *pstHDMI_SET_EQ;

typedef struct
{
    MS_HDMI_EQ enEq;
    MS_U8 u8EQValue;
    E_MUX_INPUTPORT enInputPortType;
    MS_BOOL bReturnValue;
} stHDMI_SET_EQ_TO_PORT, *pstHDMI_SET_EQ_TO_PORT;

typedef struct
{
    MS_U16 u16MuteEvent;
    MS_U16 u16MuteMask;
} stHDMI_AUDIO_MUTE_ENABLE, *pstHDMI_AUDIO_MUTE_ENABLE;

typedef struct
{
    MS_BOOL bEn_PAR;
    MS_BOOL bEn_AFAR;
    MS_HDMI_AR_TYPE eReturnValue;
} stHDMI_GET_ASPECTRATIO, *pstHDMI_GET_ASPECTRATIO;

typedef struct
{
    MS_BOOL bEn_AFAR;
    MS_HDMI_AR_TYPE eReturnValue;
} stHDMI_GET_ACTIVEFORMAT_ASPECTRATIO, *pstHDMI_GET_ACTIVEFORMAT_ASPECTRATIO;

typedef struct
{
    EN_AVI_INFOFRAME_VERSION eReturnValue;
} stHDMI_GET_AVIINFOFRAMEVER, *pstHDMI_GET_AVIINFOFRAMEVER;

typedef struct
{
    MS_U8 u8value;
    MS_BOOL bread;
    MS_U8 u8ReturnValue;
} stHDMI_ERR_STATUS_UPDATE, *pstHDMI_ERR_STATUS_UPDATE;

typedef struct
{
    MS_U16 u8ReturnValue;
} stHDMI_GET_TMDS_FREQ, *pstHDMI_GET_TMDS_FREQ;

typedef struct
{
    HDMI_POLLING_STATUS_t **pStatus;
} stHDMI_GET_POLLINGSTATUS, *pstHDMI_GET_POLLINGSTATUS;

typedef struct
{
    MS_BOOL bReturnValue;
} stHDMI_ISHDMI_MODE, *pstHDMI_ISHDMI_MODE;

typedef struct
{
    MS_U8 * pu8ManufactorData;
} stHDMI_GET_MID_INFO, *pstHDMI_GET_MID_INFO;

typedef struct
{
    MS_HDMI_PACKET_STATE_t u8state;
    MS_U8 u8byte_idx;
    MS_U8 *pValue;
    MS_BOOL bReturnValue;
} stHDMI_GET_PACKET_VALUE, *pstHDMI_GET_PACKET_VALUE;

typedef struct
{
    MS_DVI_CHANNEL_TYPE u8Channel;
    MS_U16 u16ReturnValue;
} stDVI_CHANNELPHASESTATUS, *pstDVI_CHANNELPHASESTATUS;

typedef struct
{
    MS_U16 u16Reset;
} stDVI_SOFTWARERESET, *pstDVI_SOFTWARERESET;

typedef struct
{
    MS_BOOL bReturnValue;
} stHDMI_GET_AVIIINFO_ACTIVEINFOPRESENT, *pstHDMI_GET_AVIIINFO_ACTIVEINFOPRESENT;

typedef struct
{
    MS_BOOL bPullLow;
    E_MUX_INPUTPORT enInputPortType;
} stDVI_CLKPULLLOW, *pstDVI_CLKPULLLOW;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
} stDVI_SWITCHSRC, *pstDVI_SWITCHSRC;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
    MS_BOOL bReturnValue;
} stHDMI_SETFORCLOCKLESSTHAN70MHZ, *pstHDMI_SETFORCLOCKLESSTHAN70MHZ;

typedef struct
{
    MS_BOOL bClockLessThan70MHz;
} stHDMI_DVI_ADJUST, *pstHDMI_DVI_ADJUST;

typedef struct
{
    INPUT_SOURCE_TYPE_t enInputSourceType;
} stHDMI_SETUPDATEPHASELINECOUNT, *pstHDMI_SETUPDATEPHASELINECOUNT;

typedef struct
{
    MS_BOOL bEnable;
} stHDCP_ENABLE, *pstHDCP_ENABLE;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
    MS_BOOL bEnable;
    MS_BOOL bReturnValue;
} stHDMI_SET_HDCPENABLE, *pstHDMI_SET_HDCPENABLE;

typedef struct
{
    MS_U8 * pu8HdcpKeyData;
} stHDCP_INITPRODUCTIONKEY, *pstHDCP_INITPRODUCTIONKEY;

typedef struct
{
    MS_HDCP_STATUS_INFO_t* stReturnValue;
} stHDCP_GETSTATUS, *pstHDCP_GETSTATUS;

typedef struct
{
    MS_BOOL bStable;
} stHDCP_VSYNC_END_EN, *pstHDCP_VSYNC_END_EN;

typedef struct
{
    MS_BOOL bEnable;
} stHDMI_AUDIO_OUTPUT, *pstHDMI_AUDIO_OUTPUT;

typedef struct
{
    MS_U8 u8ReturnValue;
} stHDMI_AUDIO_CP_HDR_INFO, *pstHDMI_AUDIO_CP_HDR_INFO;

typedef struct
{
    MS_U8 u8byte;
    MS_U8 u8ReturnValue;
} stHDMI_AUDIO_CHANNEL_STATUS, *pstHDMI_AUDIO_CHANNEL_STATUS;

typedef struct
{
    const MSIF_Version **ppVersion;
    HDMI_Ret_Value eReturnValue;
} stHDMI_GETLIBVER, *pstHDMI_GETLIBVER;

typedef struct
{
    MS_HDMI_INFO *pInfo;
    HDMI_Ret_Value eReturnValue;
} stHDMI_GETINFO, *pstHDMI_GETINFO;

typedef struct
{
    MS_HDMI_Status *pStatus;
    HDMI_Ret_Value eReturnValue;
} stHDMI_GETSTATUS, *pstHDMI_GETSTATUS;

typedef struct
{
    XC_DDCRAM_PROG_INFO *pstDDCRam_Info;
    MS_U32 u32SizeOfInfo;
} stHDMI_READ_DDCRAM, *pstHDMI_READ_DDCRAM;

typedef struct
{
    XC_DDCRAM_PROG_INFO *pstDDCRam_Info;
    MS_U32 u32SizeOfInfo;
} stHDMI_PROG_DDCRAM, *pstHDMI_PROG_DDCRAM;

typedef struct
{
    MS_HDMI_CONTENT_TYPE enReturnValue;
} stHDMI_GET_CONTENT_TYPE, *pstHDMI_GET_CONTENT_TYPE;

typedef struct
{
    MS_HDMI_EXT_COLORIMETRY_FORMAT enReturnValue;
} stHDMI_GET_EXT_COLORIMETRY, *pstHDMI_GET_EXT_COLORIMETRY;

typedef struct
{
    MS_U8 u8ReturnValue;
} stHDMI_GET_PIXEL_REPETITION, *pstHDMI_GET_PIXEL_REPETITION;

typedef struct
{
    MS_BOOL bReturnValue;
} stHDMI_CHECK_4K2K, *pstHDMI_CHECK_4K2K;

typedef struct
{
    MS_BOOL bTrue;
} stHDMI_AVG_SCALERINGDOWN, *pstHDMI_AVG_SCALERINGDOWN;

typedef struct
{
    E_HDMI_ADDITIONAL_VIDEO_FORMAT eReturnValue;
} stHDMI_CHECK_ADDITIONAL_FORMAT, *pstHDMI_CHECK_ADDITIONAL_FORMAT;

typedef struct
{
    E_XC_3D_INPUT_MODE eReturnValue;
} stHDMI_GET_3D_STRUCTURE, *pstHDMI_GET_3D_STRUCTURE;

typedef struct
{
    E_HDMI_3D_EXT_DATA_T eReturnValue;
} stHDMI_GET_3D_EXT_DATA, *pstHDMI_GET_3D_EXT_DATA;

typedef struct
{
    sHDMI_3D_META_FIELD *pdata;
} stHDMI_GET_3D_META_FIELD, *pstHDMI_GET_3D_META_FIELD;

typedef struct
{
    MS_U8 u8ReturnValue;
} stHDMI_GET_VIC_CODE, *pstHDMI_GET_VIC_CODE;

typedef struct
{
    E_HDMI_VIC_4Kx2K_CODE eReturnValue;
} stHDMI_GET_4KX2K_VIC_CODE, *pstHDMI_GET_4KX2K_VIC_CODE;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
    MS_BOOL bEnable;
    MS_BOOL bDrivingHigh;
} stHDMI_ARC_PINCONTROL, *pstHDMI_ARC_PINCONTROL;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
    MS_U16 u16Reset;
} stDVI_SOFTWARE_RESET, *pstDVI_SOFTWARE_RESET;

typedef struct
{
    EN_POWER_MODE enPowerState;
    MS_U32 u32ReturnValue;
} stHDMI_SET_POWERSTATE, *pstHDMI_SET_POWERSTATE;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
    MS_BOOL bReturnValue;
} stHDMI_CheckHDMI20_Setting, *pstHDMI_CheckHDMI20_Setting;

typedef struct
{
    E_MUX_INPUTPORT enInputPortType;
    MS_U8 ucSourceVersion;
} stHDMI_Get_Source_Version, *pstHDMI_Get_Source_Version;

/*************************** HDCP22 ***************************/
typedef struct
{
	HDCP22_Recv_CBF pCBFunc;
	void* pContext;
} stHDCP22_InitCBFunc, *pstHDCP22_InitCBFunc;

typedef struct
{
	MS_U8	ucPortIdx;
} stHDCP22_PortInit, *pstHDCP22_PortInit;

typedef struct
{
	MS_U8	ucPortIdx;
	MS_BOOL bReturnValue;
} stHDCP22_PollingReadDone, *pstHDCP22_PollingReadDone;

typedef struct
{
	MS_U8	ucPortType;
	MS_U8	ucPortIdx;
	MS_BOOL bIsEnable;
} stHDCP22_EnableCipher, *pstHDCP22_EnableCipher;

typedef struct
{
	MS_U8	ucPortType;
	MS_U8	ucPortIdx;
	MS_U8*	pucData;
	MS_U32	dwDataLen;
	void*	pDummy;
} stHDCP22_SendMsg, *pstHDCP22_SendMsg;

typedef struct
{
	MS_U8	ucPortIdx;
} stHDCP22_Handler, *pstHDCP22_Handler;


/*************************** HDCP22 ***************************/

#ifdef __cplusplus
}
#endif

#endif //_XC_HDMI_IF_H_
