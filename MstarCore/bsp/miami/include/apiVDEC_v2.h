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

#ifndef _VDEC_V2_H_
#define _VDEC_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif



typedef enum
{
    //E_VDEC_V2_CMD_GET_FREE_STREAM_ID,
    
    E_VDEC_V2_CMD_GETLIBVER = 0,
    E_VDEC_V2_CMD_GETINFO,
    E_VDEC_V2_CMD_GETSTATUS,
    E_VDEC_V2_CMD_CHECKCAPS,
    E_VDEC_V2_CMD_ENABLETUEBOMODE,
    E_VDEC_V2_CMD_INIT,
    E_VDEC_V2_CMD_INIT_EX,
    E_VDEC_V2_CMD_SET_CONTROL,
    E_VDEC_V2_CMD_GET_CONTROL,
    E_VDEC_V2_CMD_PRE_SET_CONTROL,
    E_VDEC_V2_CMD_POST_SET_CONTROL,
    E_VDEC_V2_CMD_RST,
    E_VDEC_V2_CMD_EXIT,
    E_VDEC_V2_CMD_CHECK_DISP_INFO_RDY,
    E_VDEC_V2_CMD_SET_FRC_MODE,
    E_VDEC_V2_CMD_SET_DYNSCALING_PARAMS,
    E_VDEC_V2_CMD_PLAY,
    E_VDEC_V2_CMD_PAUSE,
    E_VDEC_V2_CMD_RESUME,
    E_VDEC_V2_CMD_STEP_DISP,
    E_VDEC_V2_CMD_IS_STEP_DISP_DONE,
    E_VDEC_V2_CMD_SEEK_TO_PTS,
    E_VDEC_V2_CMD_SKIP_TO_PTS,
    E_VDEC_V2_CMD_STEP_DECODE,
    E_VDEC_V2_CMD_IS_STEP_DECODE_DONE,
    E_VDEC_V2_CMD_SET_TRICK_MODE,
    E_VDEC_V2_CMD_PUSH_DECQ,
    E_VDEC_V2_CMD_FIRE_DEC_CMD,
    E_VDEC_V2_CMD_GET_DECQ_VACANCY,
    E_VDEC_V2_CMD_IS_CC_AVAILABLE,
    E_VDEC_V2_CMD_GET_CC_INFO,
    E_VDEC_V2_CMD_FLUSH,
    E_VDEC_V2_CMD_GET_ES_WRITE_PTR,
    E_VDEC_V2_CMD_GET_ES_READ_PTR,
    E_VDEC_V2_CMD_ENABLE_LAST_FRAME_SHOW,
    E_VDEC_V2_CMD_IS_DISP_FINISH,
    E_VDEC_V2_CMD_SET_SPEED,
    E_VDEC_V2_CMD_IS_FRAME_RDY,
    E_VDEC_V2_CMD_SET_FREEZE_DISP,
    E_VDEC_V2_CMD_SET_BLUE_SCREEN,
    E_VDEC_V2_CMD_RESET_PTS,
    E_VDEC_V2_CMD_AVSYNC_ON,
    E_VDEC_V2_CMD_SET_AVSYNC_FREERUN_THRESHOLD,
    E_VDEC_V2_CMD_IS_AVSYNC_ON,
    E_VDEC_V2_CMD_GET_PTS,
    E_VDEC_V2_CMD_GET_NEXT_PTS,
    E_VDEC_V2_CMD_IS_START_SYNC,
    E_VDEC_V2_CMD_IS_REACH_SYNC,
    E_VDEC_V2_CMD_IS_FREERUN,
    E_VDEC_V2_CMD_MHEG_DECODE_I_FRAME,
    E_VDEC_V2_CMD_MHEG_IS_I_FRAME_DECODING,
    E_VDEC_V2_CMD_MHEG_RST_I_FRAME_DEC,
    E_VDEC_V2_CMD_GET_ERR_CODE,
    E_VDEC_V2_CMD_GET_ERR_CNT,
    E_VDEC_V2_CMD_GET_ACTIVE_CODEC_TYPE,
    E_VDEC_V2_CMD_GET_BITS_RATE,
    E_VDEC_V2_CMD_IS_32PULLDOWN,
    E_VDEC_V2_CMD_IS_ALIVE,
    E_VDEC_V2_CMD_GET_VIDEO_PTS_STC_DELTA,
    E_VDEC_V2_CMD_IS_WITH_VALID_STREAM,
    E_VDEC_V2_CMD_IS_I_FRAME_FOUND,
    E_VDEC_V2_CMD_IS_WITH_LOW_DELAY,
    E_VDEC_V2_CMD_IS_ALL_BUFFER_EMPTY,
    E_VDEC_V2_CMD_GET_GOP_CNT,
    E_VDEC_V2_CMD_GET_FRAME_CNT,
    E_VDEC_V2_CMD_GET_SKIP_CNT,
    E_VDEC_V2_CMD_GET_DROP_CNT,
    E_VDEC_V2_CMD_GET_DISP_INFO,
    E_VDEC_V2_CMD_GET_TRICK_MODE,
    E_VDEC_V2_CMD_GET_ACTIVE_FORMAT,
    E_VDEC_V2_CMD_GET_COLOUR_PRIMARIES,
    E_VDEC_V2_CMD_GET_HW_KEY,
    E_VDEC_V2_CMD_IS_SEQ_CHG,
    E_VDEC_V2_CMD_SET_DBG_LEVEL,
    E_VDEC_V2_CMD_GET_DEC_FRAME_INFO,
    E_VDEC_V2_CMD_GET_DISP_FRAME_INFO,
    E_VDEC_V2_CMD_GET_EXT_DISP_INFO,
    E_VDEC_V2_CMD_GET_DEC_TIME_CODE,
    E_VDEC_V2_CMD_GET_DISP_TIME_CODE,
    E_VDEC_V2_CMD_CC_STARTPARSING,
    E_VDEC_V2_CMD_CC_STOPPARSING,
    E_VDEC_V2_CMD_CC_GETWRITEPTR,
    E_VDEC_V2_CMD_CC_GETREADPTR,
    E_VDEC_V2_CMD_CC_UPDATEREADPTR,
    E_VDEC_V2_CMD_CC_GETISOVERFLOW,
    E_VDEC_V2_CMD_SETEVENT,
    E_VDEC_V2_CMD_UNSETEVENT,
    E_VDEC_V2_CMD_SETENVENT_EX,
    E_VDEC_V2_CMD_UNSETEVENT_EX,
    E_VDEC_V2_CMD_GETEVENTINFO,
    E_VDEC_V2_CMD_GENPATTERN,
    E_VDEC_V2_CMD_GENPATTERNLEASTLENGTH,
    E_VDEC_V2_CMD_DISABLEDEBLOCKING,
    E_VDEC_V2_CMD_DISABLEQUARTERPIXEL,
    E_VDEC_V2_CMD_SETAUTORMLSTZEROBYTE,
    E_VDEC_V2_CMD_SETBALANCEBW,
    E_VDEC_V2_CMD_DBGDUMPSTATUS,
    E_VDEC_V2_CMD_SETCONTROL,
    E_VDEC_V2_CMD_GETCONTROL,
    E_VDEC_V2_CMD_GETDISPCNT,
    E_VDEC_V2_CMD_GETFWVERSION,
    E_VDEC_V2_CMD_SETBLOCKDISPLAY,
    E_VDEC_V2_CMD_ENABLEESBUFFMALLOC,
    E_VDEC_V2_CMD_GETESBUFFVACANCY,
    E_VDEC_V2_CMD_GETESBUFF,
    E_VDEC_V2_CMD_GETNEXTDISPFRAME,
    E_VDEC_V2_CMD_DISPLAYFRAME,
    E_VDEC_V2_CMD_RELEASEFRAME,
    E_VDEC_V2_CMD_FLUSHPTSBUF,
    E_VDEC_V2_CMD_CAPTUREFRAME,
    E_VDEC_V2_CMD_CC_INIT,
    E_VDEC_V2_CMD_CC_SETCFG,
    E_VDEC_V2_CMD_CC_SETBUFFSTARTADD,
    E_VDEC_V2_CMD_CC_UPDATEWRITEADD,
    E_VDEC_V2_CMD_CC_UPDATEREADADD,
    E_VDEC_V2_CMD_CC_DISABLEPARSING,
    E_VDEC_V2_CMD_CC_GETINFO,
    E_VDEC_V2_CMD_CC_GETISRSTDONE,
    E_VDEC_V2_CMD_CC_GETISBUFFOVERFLOW,
    E_VDEC_V2_CMD_CC_GETWRITEADD,
    E_VDEC_V2_CMD_CC_GETREADADD,
    E_VDEC_V2_CMD_SYSTEMPRESETCONTROL,
    E_VDEC_V2_CMD_PRESETCONTROL,

    E_VDEC_V2_CMD_NUM,
    E_VDEC_V2_CMD_MAX = E_VDEC_V2_CMD_NUM,
} E_VDEC_V2_IOCTL_CMD;


//-------------------------------------------------------------------------------------------------
//  API for Upper layer
//-------------------------------------------------------------------------------------------------

void VDEC_V2_RegisterToUtopia(void);
MS_U32 VDEC_V2_Open(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 VDEC_V2_Close(void* pInstance);
MS_U32 VDEC_V2_Ioctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);

typedef struct
{
    VDEC_User_Cmd eUserCmd;
    void* param[8];  // at most 8 param
    void* pRet;//johnny.ko
}VDEC_V2_IO_Param;

#ifdef __cplusplus
}
#endif

#undef _VDEC_V2_H_
#endif //_VDEC_V2_H_
