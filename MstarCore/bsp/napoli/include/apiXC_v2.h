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

#ifndef _XC_H_
#define _XC_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "MsTypes.h"

//******** ENUM DEFINITIONS ********//

typedef enum
{
    // APIXC
    E_XC_CMD_NONE = 0,
    E_XC_CMD_GET_LIB_VERSION,
    E_XC_CMD_GET_INFO,
    E_XC_CMD_GET_STATUS,
    E_XC_CMD_GET_STATUS_EX,
    E_XC_CMD_SET_DBG_LEVEL,
    E_XC_CMD_SET_FPLL_CUSTOMERMODE,
    E_XC_CMD_SET_IOMAPBASE,
    E_XC_CMD_INIT,
    E_XC_CMD_INIT_MISC,
    E_XC_CMD_GET_MISC_STATUS,
    E_XC_CMD_GET_CAPABILITY,
    E_XC_CMD_GET_CHIPCAPS,
    E_XC_CMD_EXIT,
    E_XC_CMD_SET_DYNAMIC_SCALING,
    E_XC_CMD_GET_DNR_BASEOFFSET,
    E_XC_CMD_GET_STORE_FRAMENUM,
    E_XC_CMD_GET_FRAMENUM_FACTOR,
    E_XC_CMD_SET_WINDOW,
    E_XC_CMD_SET_DUALWINDOW,
    E_XC_CMD_SET_TRAVELING_WINDOW,
    E_XC_CMD_SET_INPUTSOURCE,
    E_XC_CMD_CHECK_YUVSPACE,
    E_XC_CMD_CHECK_MEMORYFORMAT422,
    E_XC_CMD_SET_FORCE_RGBIN,
    E_XC_CMD_SET_MIRRORMODE_EX,
    E_XC_CMD_GET_MIRRORMODE_TYPEEX,
    E_XC_CMD_GET_SYNC_STATUS,
    E_XC_CMD_SET_WAIT_OUTPUT_VSYNC,
    E_XC_CMD_SET_WAIT_INPUT_VSYNC,
    E_XC_CMD_SET_HDMI_SYNCMODE,
    E_XC_CMD_GET_HDMI_SYNCMODE,
    E_XC_CMD_SET_REPORT_WINDOW,
    E_XC_CMD_SET_SKIP_OPWRITEOFF_IN_SETWINDOW,
    E_XC_CMD_GET_SKIP_OPWRITEOFF_IN_SETWINDOW,
    E_XC_SET_SKIP_DISABLE_OPWRITEOFF_IN_FPLL,
    E_XC_CMD_SET_OPWRITEOFF_ENABLE,
    E_XC_CMD_SET_OPWRITEOFF_ENABLE_TO_REG,
    E_XC_CMD_FORCESET_OPWRITEOFF_ENABLE,
    E_XC_CMD_GET_OPWRITEOFF_ENABLE,
    E_XC_CMD_SET_DISPLAY_WIN_TO_REG,
    E_XC_CMD_GET_DISPLAY_WIN_FROM_REG,
    E_XC_CMD_SET_FREEZEIMG,
    E_XC_CMD_CHECK_FREEZEIMG,
    E_XC_CMD_SET_BOTHWINDOW_BLACKVIDEO,
    E_XC_CMD_SET_BLACKSCREEN,
    E_XC_CMD_SET_BLACKVIDEO,
    E_XC_CMD_CHECK_BLACKVIDEO_ENABLE,
    E_XC_CMD_SET_FRAMEBUFFERLESS,
    E_XC_CMD_CHECK_FRAMEBUFFERLESS,
    E_XC_CMD_SET_REQUEST_FRAMEBUFFERLESS,
    E_XC_CMD_CHECK_REQUEST_FRAMEBUFFERLESS,
    E_XC_CMD_GET_3D_HWVERSION,
    E_XC_CMD_CHECK_3D_SUPPORT_HW2DTO3D,
    E_XC_CMD_SET_3D_MODE,
    E_XC_CMD_SET_3D_MAINWIN_FIRST,
    E_XC_CMD_SET_3D_LR_EXCHANGE,
    E_XC_CMD_CHECK_3D_LR_EXCHANGED,
    E_XC_CMD_GET_3D_INPUT_MODE,
    E_XC_CMD_GET_3D_OUTPUT_MODE,
    E_XC_CMD_GET_3D_PANELTYPE,
    E_XC_CMD_GET_3D_MAINWIN_FIRST,
    E_XC_CMD_CHECK_3D_MAINSUB_IPSYNC,
    E_XC_CMD_SET_3D_VERTICALVIDEO_OFFSET,
    E_XC_CMD_GET_3D_VERTICALVIDEO_OFFSET,
    E_XC_CMD_CHECK_3D_FORMAT_SUPPORTED,
    E_XC_CMD_SET_3D_HORIZONTAL_SHIFT,
    E_XC_CMD_SET_3D_LR_SBS2LINE,
    E_XC_CMD_GET_3D_HORIZONTAL_SHIFT,
    E_XC_CMD_SET_3D_HW2DTO3D_BUFFER,
    E_XC_CMD_SET_3D_HW2DTO3D_PARAMETERS,
    E_XC_CMD_GET_3D_HW2DTO3D_PARAMETERS,
    E_XC_CMD_SET_3D_DETECT_3DFORMAT_PARAMETERS,
    E_XC_CMD_GET_3D_DETECT_3DFORMAT_PARAMETERS,
    E_XC_CMD_GET_3D_FORMAT_DETECTED_BY_CONTENT,
    E_XC_CMD_SET_NINELATTICE,
    E_XC_CMD_SET_3D_POST_PQSETTING,
    E_XC_CMD_SET_3D_FRAMEPACKING_INFO,
    E_XC_CMD_SET_3D_AUTODETECT,
    E_XC_CMD_GET_3D_AUTODETECT_3DFLAG,
    E_XC_CMD_SET_3D_SUBWINCLOCK,
    E_XC_CMD_CHECK_3D_LR_SBS2LINE,
    E_XC_CMD_CHECK_3D_SKIP_DEFAULT_LR_FLAG,
    E_XC_CMD_SET_3D_SKIP_DEFAULT_LR_FLAG,
    E_XC_CMD_SET_MUX_INIT,
    E_XC_CMD_SET_MUX_SOURCE_MONITOR,
    E_XC_CMD_SET_MUX_CREATE_PATH,
    E_XC_CMD_SET_MUX_DELETE_PATH,
    E_XC_CMD_SET_MUX_ENABLE_PATH,
    E_XC_CMD_SET_MUX_TRIGGER_PATH_SYNC_EVENT,
    E_XC_CMD_SET_MUX_TRIGGER_DEST_ONOFF_EVENT,
    E_XC_CMD_SET_MUX_ONOFF_PERIODIC_HANDLER,
    E_XC_CMD_GET_MUX_PATHINFO,
    E_XC_CMD_SET_MUX_SUPPORT_MHL_PATHINFO,
    E_XC_CMD_SET_MUX_MHL_HOTPLUG_INVERSE_INFO,
    E_XC_CMD_GET_MUX_HDMIPORT,
    E_XC_CMD_GET_MUX_INPUTSOURCE2VDYMUXPORT,
    E_XC_CMD_SET_NR,
    E_XC_CMD_SET_FILM_MODE_PATCH,
    E_XC_CMD_CHECK_UC_ENABLED,
    E_XC_CMD_SET_GENERATE_SPECIFIC_TIMING,
    E_XC_CMD_GET_DE_BYPASS_MODE,
    E_XC_CMD_GET_DE_WINDOW,
    E_XC_CMD_GET_DE_WIN_WIDTH_HEIGHT_IN_DE_BYPASS_MODE,
    E_XC_CMD_GET_CAPTURE_WINDOW,
    E_XC_CMD_SET_CAPTURE_WINDOW_VSTART,
    E_XC_CMD_SET_CAPTURE_WINDOW_HSTART,
    E_XC_CMD_SET_CAPTURE_WINDOW_VSIZE,
    E_XC_CMD_SET_CAPTURE_WINDOW_HSIZE,
    E_XC_CMD_SET_SOFTWARE_RESET,
    E_XC_CMD_GET_HFREQX10,
    E_XC_CMD_GET_HFREQX1K,
    E_XC_CMD_GET_VFREQX10,
    E_XC_CMD_GET_VFREQX1K,
    E_XC_CMD_GET_ACCURATE_VFREQX1k,
    E_XC_CMD_SET_INTERRUPT_ATTACH,
    E_XC_CMD_SET_INTERRUPT_DEATTACH,
    E_XC_CMD_SET_DISABLE_INPUTSOURCE,
    E_XC_CMD_CHECK_INPUTSOURCE_DISABLED,
    E_XC_CMD_SET_CHANGE_PANELTYPE,
    E_XC_CMD_GET_CURRENT_READBANK,
    E_XC_CMD_GET_CURRENT_WRITEBANK,
    E_XC_CMD_SET_AUTO_PRESCALING,
    E_XC_CMD_GET_VSYNC_WIDTH,
    E_XC_CMD_SET_GOP_ENABLE,
    E_XC_CMD_SET_SELECT_IP_FOR_GOP,
    E_XC_CMD_SET_VOP_NEW_BLENDING_LEVEL,
    E_XC_CMD_GET_DESTINATION_INFO,
	E_XC_CMD_SET_FDMASK_BYWIN,
	E_XC_CMD_GET_FDMASK_BYWIN,
    E_XC_CMD_SET_IP1_TESTPATTERN,
    E_XC_CMD_SET_INIT_IP_FOR_INTERNAL_TIMING,
    E_XC_CMD_SET_IPMUX,
    E_XC_CMD_CHECK_HSYNC_ACTIVE,
    E_XC_CMD_CHECK_VSYNC_ACTIVE,
    E_XC_CMD_GET_AUTO_POSITION_WINDOW,
    E_XC_CMD_SET_FRAMEBUFFER_ADDRESS,
    E_XC_CMD_CHECK_FRAMEBUFFER_ENOUGH_FOR_CUSSCALING,
    E_XC_CMD_SET_SCALER_MEMORY_REQUEST,
    E_XC_CMD_GET_PIXEL_DATA,
    E_XC_CMD_GET_AVAILABLE_SIZE,
    E_XC_CMD_SET_FRAME_COLOR,
    E_XC_CMD_SET_DISPLAY_WINDOW_COLOR,
    E_XC_CMD_GET_SUPPORT_SOURCE_TO_VE,
    E_XC_CMD_SET_OUTPUT_CAPTURE,
    E_XC_CMD_SET_GAMMA_ONOFF,
    E_XC_CMD_SET_PREGAMMA_GAIN,
    E_XC_CMD_SET_PREGAMMA_OFFSET,
    E_XC_CMD_SET_PANEL_TIMING,
    E_XC_CMD_SET_OUTPUT_TIMING_MODE,
    E_XC_CMD_SET_FREERUN_TIMING,
    E_XC_CMD_SET_CUSTOMER_SYNC_INFO,
    E_XC_CMD_GET_WAIT_FPLL_DONE,
    E_XC_CMD_GET_OUTPUT_VFREQX100,
    E_XC_CMD_GET_OP1_OUTPUT_VFREQX100,
    E_XC_CMD_CHECK_FRAMELOCK,
    E_XC_CMD_SET_CUSTOMIZE_FRC_TABLE,
    E_XC_CMD_SET_OUTPUT_FRAME_CONTROL,
    E_XC_CMD_SET_FPLL_FSM_ENABLE,
    E_XC_CMD_SET_FORCE_FREERUN,
    E_XC_CMD_CHECK_FORCE_FREERUN,
    E_XC_CMD_SET_FREERUN_FREQ,
    E_XC_CMD_SET_EXPANEL_INFO,
    E_XC_CMD_SET_FPLL_THRESHMODE,
    E_XC_CMD_GET_FPLL_THRESHMODE,
    E_XC_CMD_SET_IPAUTONOSIGNAL,
    E_XC_CMD_GET_IPAUTONOSIGNAL,
    E_XC_CMD_SET_IPAUTOCOAST,
    E_XC_CMD_SET_IPCOAST_DEBOUNCE_ENABLE,
    E_XC_CMD_SET_CLEAR_IPCOAST_STATUS,
    E_XC_CMD_SET_FPLL_MANUAL_SETTING_ENABLE,
    E_XC_CMD_SET_FPLL_BOUNDARY_TEST,
    E_XC_CMD_SET_OFFLINE_DETECTION,
    E_XC_CMD_GET_OFFLINE_DETECTION,
    E_XC_CMD_SET_OFFLINE_SOG_THRESHOLD,
    E_XC_CMD_SET_OFFLINE_SOG_BW,
    E_XC_CMD_SET_OFFLINE_INIT,
    E_XC_CMD_SET_EXTRA_FETCH_ADV_LINE,
    E_XC_CMD_SET_VGA_SOG_ENABLE,
    E_XC_CMD_SET_WINDOW_ENABLE,
    E_XC_CMD_CHECK_SUBWINDOW_ENABLE,
    E_XC_CMD_SET_BORDER_FORMAT,
    E_XC_CMD_SET_BORDER_ENABLE,
    E_XC_CMD_SET_ZORDER_MAINWINDOW_FIRST,
    E_XC_CMD_SET_PQ_LOADFUNCTION,
    E_XC_CMD_CHECK_H_NONLINEAR_SCALING,
    E_XC_CMD_SET_EUROHDTV_SUPPORT_ENABLE,
    E_XC_CMD_SET_EUROHDTV_DETECTION_ENABLE,
    E_XC_CMD_READBYTE,
    E_XC_CMD_WRITEBYTE,
    E_XC_CMD_WRITEBYTEMSK,
    E_XC_CMD_WRITE2BYTEMSK,
    E_XC_CMD_W2BYTE,
    E_XC_CMD_R2BYTE,
    E_XC_CMD_W4BYTE,
    E_XC_CMD_R4BYTE,
    E_XC_CMD_R2BYTEMSK,
    E_XC_CMD_W2BYTEMSK,
    E_XC_CMD_MLOAD_INIT,
    E_XC_CMD_MLOAD_ENABLE,
    E_XC_CMD_MLOAD_GETSTATUS,
    E_XC_CMD_MLOAD_WRITE_CMD_AND_FIRE,
    E_XC_CMD_MLOAD_WRITE_CMDS_AND_FIRE,
    E_XC_CMD_MLG_INIT,
    E_XC_CMD_MLG_ENABLE,
    E_XC_CMD_MLG_GET_CAPS,
    E_XC_CMD_MLG_GETSTATUS,
    E_XC_CMD_SET_OSD2VEMODE,
    E_XC_CMD_SET_IP2_PREFILTER_ENABLE,
    E_XC_CMD_GET_PIXELRGB,
    E_XC_CMD_SET_KEEP_PIXELPOINTER_APPEAR,
    E_XC_CMD_SET_MEMORY_FORMAT_EX,
    E_XC_CMD_CHECK_REQUEST_FRAMEBUFFERLESS_MODE,
    E_XC_CMD_SET_SKIP_SWRESET,
    E_XC_CMD_SET_REPORTWINDOW_FOR_FRAMECOLOR,
    E_XC_CMD_SET_OSDLAYER,
    E_XC_CMD_GET_OSDLAYER,
    E_XC_CMD_SET_VIDEO_ALPHA,
    E_XC_CMD_GET_VIDEO_ALPHA,
    E_XC_CMD_SKIP_WAIT_VSYNC,
    E_XC_CMD_SET_OP2VOP_DE_SELECTION,
    E_XC_CMD_SET_FRC_WINDOW,
    E_XC_CMD_SET_2INITFACTOR_ENABLE,
    E_XC_CMD_CHECK_FIELDPACKINGMODE_SUPPORTED,
    E_XC_CMD_PREINIT,
    E_XC_CMD_GET_BUFFERDATA,
    E_XC_CMD_SET_BUFFERDATA,
    E_XC_CMD_SET_MAINWINDOW_ENABLE,
    E_XC_CMD_SET_SUBWINDOW_ENABLE,
    E_XC_CMD_SET_SUBWINDOW_DISABLE,
    E_XC_CMD_SET_PIXEL_SHIFT,
    E_XC_CMD_SET_VIDEO_ON_OSD,
    E_XC_CMD_SET_OSD_LAYER_BLEANDING,
    E_XC_CMD_SET_OSD_LAYER_ALPHA,
    E_XC_CMD_SET_OSD_BLENDING_FORMULA,
    E_XC_CMD_GET_REPORT_PIXEL_INFO,
    E_XC_CMD_SET_SCALING,
    E_XC_CMD_SET_MCDI_BUFFERADDRESS,
    E_XC_CMD_SET_MCDI_ENABLE,
    E_XC_CMD_SEND_CMD2FRC,
    E_XC_CMD_GET_MSG_FROM_FRC,
    E_XC_CMD_SET_AUTO_RWBANK_ENABLE,
    E_XC_CMD_SET_RWBANK_MAPPING_NUM,
    E_XC_CMD_GET_RWBANK_MAPPING_NUM,
    E_XC_CMD_GET_RWBANK_MAPPING_NUM_FOR_ZAP,
    E_XC_CMD_SET_BOBMODE,
    E_XC_CMD_SET_FORCE_READBANK,
    E_XC_CMD_SET_LOCK_POINT,
    E_XC_CMD_LD_INIT,
    E_XC_CMD_SET_LD_MEMORYADDRESS,
    E_XC_CMD_GET_LD_VALUE,
    E_XC_CMD_SET_LD_LEVEL,
    E_XC_CMD_SET_LD_TURNOFF_LDBL,
    E_XC_CMD_SET_NOTUPDATE_SPI_DATA_FLAGS,
    E_XC_CMD_SET_LD_USERMODEFLAGS,
    E_XC_CMD_SET_BL_LEVEL,
    E_XC_CMD_SET_BWS_MODE,
    E_XC_CMD_SET_FRC_COLOR_PATH_CONTROL,
    E_XC_CMD_SET_FRC_OP2_RGBGAIN,
    E_XC_CMD_SET_FRC_OP2_RGBOFFSET,
    E_XC_CMD_SET_FRC_OP2_DITHER,
    E_XC_CMD_FRC_BYPASS,
    E_XC_CMD_FRC_MUTE,
    E_XC_CMD_SET_FORCE_READ_FRAME,
    E_XC_CMD_SET_CSC,
    E_XC_CMD_SET_REGISTER_PQ_FPLL_THRESH_MODE,
    E_XC_CMD_GET_FREERUN_STATUS,
    E_XC_CMD_SET_BYPASS_CSC,
    E_XC_CMD_GET_DS_FORCE_INDEX_SUPPORTED,
    E_XC_CMD_SET_DS_FORCE_INDEX,
    E_XC_CMD_SET_DS_INDEX_SOURCE_SELECT,
    E_XC_CMD_GET_DS_STATUS,
    E_XC_CMD_OSDC_INITSETTING,
    E_XC_CMD_OSDC_SET_OUTPUTVFREQX10,
    E_XC_CMD_OSDC_CONTROL,
    E_XC_CMD_OSDC_GET_DESTINATION_INFO,
    E_XC_CMD_SET_POWERSTATE,
    E_XC_CMD_SET_BYPASS_OSDVSYNC_POS,
    E_XC_CMD_SET_BYPASS_INPUTSRC,
    E_XC_CMD_SET_SEAMLESS_ZAPPING,
    E_XC_CMD_GET_SEAMLESS_ZAPPING_STATUS,
    E_XC_CMD_SET_VTRACK_PAYLOADDATA,
    E_XC_CMD_SET_VTRACK_USERDEFINED_SETTING,
    E_XC_CMD_SET_VTRACK_ENABLE,
    E_XC_CMD_PRESET_PQINFO,
    E_XC_GET_OP1_TESTPATTERN_ENABLED,
    E_XC_SET_OP1_TESTPATTERN,
    E_XC_SET_OP2_TESTPATTERN,
    E_XC_CHECK_WHITEBALANCE_PATTERN_MODE,
    E_XC_SET_HLINEARSCALING,
    E_XC_SET_ENABLE_T3D,
    E_XC_SET_FRC_INPUTTIMING,
    E_XC_GET_FRC_INPUTTIMING,
//** OBSELETE FUNCTION**//
        E_XC_CMD_GET_OUTPUT_VFREQ,
        E_XC_CMD_GET_CURRENT_OUTPUTVFREQX100,
        E_XC_CMD_SET_MEMORY_WRITE_REQUEST,
        E_XC_CMD_SET_MEMORY_FORMAT,
        E_XC_CMD_SET_OUTPUT_ADJUST_SETTING,
        E_XC_CMD_SET_FPLL_FSM,
        E_XC_CMD_SET_MIRROR_MODE_ENABLE,
        E_XC_CMD_SET_MIRROR_MODE2_ENABLE,
        E_XC_CMD_MAX,
//** OBSELETE FUNCTION**//

    // APIXC_ADC
    E_XC_ADC_CMD_NONE,
    E_XC_ADC_CMD_SETCVBSOUT,
    E_XC_ADC_CMD_ISCVBSOUTENABLED,
    E_XC_ADC_CMD_SETPCCLOCK,
    E_XC_ADC_CMD_SETPHASE,
    E_XC_ADC_CMD_SETPHASEEX,
    E_XC_ADC_CMD_GETPHASERANGE,
    E_XC_ADC_CMD_GETPHASE,
    E_XC_ADC_CMD_GETPHASEEX,
    E_XC_ADC_CMD_ISSCARTRGB,
    E_XC_ADC_CMD_GETPCCLOCK,
    E_XC_ADC_CMD_GETSOGLEVELRANGE,
    E_XC_ADC_CMD_SETSOGLEVEL,
    E_XC_ADC_CMD_POWEROFF,
    E_XC_ADC_CMD_GETDEFAULTGAINOFFSET,
    E_XC_ADC_CMD_GETMAXIMALOFFSETVALUE,
    E_XC_ADC_CMD_GETMAXIMALGAINVALUE,
    E_XC_ADC_CMD_GETCENTERGAIN,
    E_XC_ADC_CMD_GETCENTEROFFSET,
    E_XC_ADC_CMD_SETGAIN,
    E_XC_ADC_CMD_SETOFFSET,
    E_XC_ADC_CMD_ADJUSTGAINOFFSET,
    E_XC_ADC_CMD_SOURCE_CALIBRATE,
    E_XC_ADC_CMD_SETSOGCAL,
    E_XC_ADC_CMD_SETRGB_PIPE_DELAY,
    E_XC_ADC_CMD_SCARTRGB_SOG_CLAMPDELAY,
    E_XC_ADC_CMD_SET_YPBPRLOOSELPF,
    E_XC_ADC_CMD_SET_SOGBW,
    E_XC_ADC_CMD_SETCLAMPDURATION,
    E_XC_ADC_CMD_ENABLEHWCALIBRATION,
    E_XC_ADC_CMD_MAX,

    // APIXC_AUTO
    E_XC_AUTO_CMD_NONE,
    E_XC_AUTO_CMD_GEOMETRY,
    E_XC_AUTO_CMD_GEOMETRY_EX,
    E_XC_AUTO_CMD_STOPAUTOGEOMETRY,
    E_XC_AUTO_CMD_GAINOFFSET,
    E_XC_AUTO_CMD_GETHWFIXEDGAINOFFSET,
    E_XC_AUTO_CMD_SETVALIDDATA,
    E_XC_AUTO_CMD_AUTOOFFSET,
    E_XC_AUTO_CMD_DETECTWIDTH,
    E_XC_AUTO_CMD_SETCALIBRATIONMODE,
    E_XC_AUTO_CMD_GETCALIBRATIONMODE,
    E_XC_AUTO_CMD_MAX ,

    // APIXC_MHL
    E_XC_MHL_CMD_NONE,
    E_XC_MHL_CMD_INIT,
    E_XC_MHL_CMD_HANDLER,
    E_XC_MHL_CMD_SETHPD,
    E_XC_MHL_CMD_POWERCTRL,
    E_XC_MHL_CMD_WAKEUPDETECT_HANDLER,
    E_XC_MHL_CMD_MAX,

    // APIXC_MODEPARSE
    E_XC_MODEPARSE_CMD_NONE,
    E_XC_MODEPARSE_CMD_INIT,
    E_XC_MODEPARSE_CMD_MATCHMODE,
    E_XC_MODEPARSE_CMD_MATCHMODEEX,
    E_XC_MODEPARSE_CMD_MAX,

    // APIXC_PCMONITOR
    E_XC_PCMONITOR_CMD_NONE,
    E_XC_PCMONITOR_CMD_INIT,
    E_XC_PCMONITOR_CMD_RESTART,
    E_XC_PCMONITOR_CMD_SETTIMINGCOUNT,
    E_XC_PCMONITOR_CMD,
    E_XC_PCMONITOR_CMD_GETCURRENTSTATE,
    E_XC_PCMONITOR_CMD_GETSYNCSTATUS,
    E_XC_PCMONITOR_CMD_GET_HFREQX10,
    E_XC_PCMONITOR_CMD_GET_HFREQX1K,
    E_XC_PCMONITOR_CMD_GET_VFREQX10,
    E_XC_PCMONITOR_CMD_GET_VFREQX1K,
    E_XC_PCMONITOR_CMD_GET_VTOTAL,
    E_XC_PCMONITOR_CMD_GET_DVI_HDMI_DE_INFO,
    E_XC_PCMONITOR_CMD_SYNCLOSS,
    E_XC_PCMONITOR_CMD_INVALIDTIMINGDETECT,
    E_XC_PCMONITOR_CMD_SETTIMINGCOUNTEX,
    E_XC_PCMONITOR_CMD_MAX,

    // DRVHDMI_IF
    E_XC_HDMI_IF_CMD_NONE,
    E_XC_HDMI_IF_CMD_FUNC_CAPS,
    E_XC_HDMI_IF_CMD_INIT,
    E_XC_HDMI_IF_CMD_EXIT,
    E_XC_HDMI_IF_CMD_PKT_RESET,
    E_XC_HDMI_IF_CMD_PULLHPD,
    E_XC_HDMI_IF_CMD_GC_INFO,
    E_XC_HDMI_IF_CMD_PACKET_RECEIVED,
    E_XC_HDMI_IF_CMD_GET_COLORFORMAT,
    E_XC_HDMI_IF_CMD_GET_COLORRANGE,
    E_XC_HDMI_IF_CMD_SET_EQ,
    E_XC_HDMI_IF_CMD_SET_EQ_TO_PORT,
    E_XC_HDMI_IF_CMD_AUDIO_MUTE_ENABLE,
    E_XC_HDMI_IF_CMD_AUDIO_STATUS_CLEAR,
    E_XC_HDMI_IF_CMD_GET_ASPECTRATIO,
    E_XC_HDMI_IF_CMD_GET_ACTIVEFORMAT_ASPECTRATIO,
    E_XC_HDMI_IF_CMD_GET_AVIINFOFRAMEVER,
    E_XC_HDMI_IF_CMD_ERR_STATUS_UPDATE,
    E_XC_HDMI_IF_CMD_GET_POLLINGSTATUS,
    E_XC_HDMI_IF_CMD_ISHDMI_MODE,
    E_XC_HDMI_IF_CMD_GET_MID_INFO,
    E_XC_HDMI_IF_CMD_GET_PACKET_VALUE,
    E_XC_DVI_IF_CMD_CHANNELPHASESTATUS,
    E_XC_DVI_IF_CMD_SOFTWARERESET,
    E_XC_DVI_IF_CMD_RESET,
    E_XC_HDMI_IF_CMD_AVIINFO_ACTIVEINFOPRESENT,
    E_XC_DVI_IF_CMD_CLKPULLLOW,
    E_XC_DVI_IF_CMD_SWITCHSRC,
    E_XC_HDMI_IF_CMD_SETFORCLOCKLESSTHAN70MHZ,
    E_XC_HDMI_IF_CMD_DVI_ADJUST,
    E_XC_HDMI_IF_CMD_SETUPDATEPHASELINECOUNT,
    E_XC_HDCP_IF_CMD_ENABLE,
    E_XC_HDMI_IF_CMD_SET_HDCP_ENABLE,
    E_XC_HDCP_IF_CMD_CLEARSTATUS,
    E_XC_HDCP_IF_CMD_INITPRODUCTIONKEY,
    E_XC_HDCP_IF_CMD_GETSTATUS,
    E_XC_HDCP_IF_CMD_VSYNC_END_EN,
    E_XC_HDMI_IF_CMD_AUDIO_OUTPUT,
    E_XC_HDMI_IF_CMD_AUDIO_CP_HDR_INFO,
    E_XC_HDMI_IF_CMD_AUDIO_CHANNEL_STATUS,
    E_XC_HDMI_IF_CMD_GETLIBVER,
    E_XC_HDMI_IF_CMD_GETINFO,
    E_XC_HDMI_IF_CMD_GETSTATUS,
    E_XC_HDMI_IF_CMD_READ_DDCRAM,
    E_XC_HDMI_IF_CMD_PROG_DDCRAM,
    E_XC_HDMI_IF_CMD_GET_CONTENT_TYPE,
    E_XC_HDMI_IF_CMD_GET_EXTCOLORIMETRY,
    E_XC_HDMI_IF_CMD_GET_PIXEL_REPETITION,
    E_XC_HDMI_IF_CMD_CHECK_4K2K,
    E_XC_HDMI_IF_CMD_3D_4KX2K_PROCESS,
    E_XC_HDMI_IF_CMD_AVG_SCALERINGDOWN,
    E_XC_HDMI_IF_CMD_CHECK_ADDITIONAL_FORMAT,
    E_XC_HDMI_IF_CMD_GET_3D_STRUCTURE,
    E_XC_HDMI_CMD_GET_3D_EXT_DATA,
    E_XC_HDMI_IF_CMD_GET_3D_META_FIELD,
    E_XC_HDMI_IF_CMD_GET_VIC_CODE,
    E_XC_HDMI_IF_CMD_GET_4KX2K_VIC_CODE,
    E_XC_HDMI_IF_CMD_ARC_PINCONTROL,
    E_XC_HDMI_IF_CMD_DVI_SOFTWARE_RESET,
    E_XC_HDMI_IF_CMD_SET_POWERSTATE,
    E_XC_HDMI_IF_CMD_DVI_HF_ADJUST,
    E_XC_HDMI_IF_CMD_MAX,

    E_XC_CMD_NUM,
} E_XC_IOCTL_CMDS;

typedef struct
{
    const MSIF_Version **ppVersion;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_LIB_VER,*pstXC_GET_LIB_VER;

typedef struct
{
    XC_ApiInfo* stReturnValue;
} stXC_CMD_GET_INFO, *pstXC_CMD_GET_INFO;

typedef struct
{
    XC_ApiStatus* pDrvStatus;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_GET_STATUS,*pstXC_GET_STATUS;

typedef struct
{
    XC_ApiStatusEx* pDrvStatusEx;
    SCALER_WIN eWindow;
    MS_U16 u16ReturnValue;
} stXC_GET_STATUS_EX,*pstXC_GET_STATUS_EX;

typedef struct
{
    MS_U16 u16DbgSwitch;
    MS_BOOL bReturnValue;
} stXC_SET_DBG_LEVEL,*pstXC_SET_DBG_LEVEL;

typedef struct
{
    EN_FPLL_MODE eMode;
    EN_FPLL_FLAG eFlag;
    MS_U32 u32Data;
} stXC_SET_FPLL_CUSTOMERMODE, *pstXC_SET_FPLL_CUSTOMERMODE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CMD_SET_IOMAPBASE, *pstXC_CMD_SET_IOMAPBASE;

typedef struct
{
    XC_INITDATA *pXC_InitData;
    MS_U32 u32InitDataLen;
    MS_BOOL bReturnValue;
} stXC_INIT,*pstXC_INIT;

typedef struct
{
    XC_INITMISC *pXC_Init_Misc;
    MS_U32 u32InitMiscDataLen;
    E_APIXC_ReturnValue eReturnValue;
} stXC_INIT_MISC,*pstXC_INIT_MISC;

typedef struct
{
    XC_INITMISC *pXC_Init_Misc;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_MISC_STATUS, *pstXC_GET_MISC_STATUS;

typedef struct
{
    MS_U32 u32Id;
    MS_U32 u32ReturnValue;
} stXC_GET_CAPABILITY, *pstXC_GET_CAPABILITY;

typedef struct
{
    E_XC_CAPS eCapType;
    MS_U32*   pRet;
    MS_U32    ret_size;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_CHIP_CAPS,*pstXC_GET_CHIP_CAPS;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_EXIT, *pstXC_EXIT;

typedef struct
{
    XC_DynamicScaling_Info *pstDSInfo;
    MS_U32 u32DSInfoLen;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_DYNAMIC_SCALING, *pstXC_SET_DYNAMIC_SCALING;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U32 u32ReturnValue;
} stXC_GET_DNR_BASEOFFSET, *pstXC_GET_DNR_BASEOFFSET;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U8 u8ReturnValue;
} stXC_GET_FRAMENUM_FACTOR, *pstXC_GET_FRAMENUM_FACTOR;

typedef struct
{
    XC_SETWIN_INFO *pstXC_SetWin_Info;
    MS_U32 u32InitDataLen;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_WINDOW, *pstXC_SET_WINDOW;

typedef struct
{
    XC_SETWIN_INFO *pstXC_SetWin_Info_Main;
    XC_SETWIN_INFO *pstXC_SetWin_Info_Sub;
    MS_BOOL bReturnValue;
} stXC_SET_DUALWINDOW, *pstXC_SET_DUALWINDOW;

typedef struct
{
    XC_SETWIN_INFO *pstXC_SetWin_Info;
    MS_U32 u32InitDataLen;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_TRAVELING_WINDOW, *pstXC_SET_TRAVELING_WINDOW;

typedef struct
{
    INPUT_SOURCE_TYPE_t enInputSourceType;
    SCALER_WIN eWindow;
} stXC_SET_INPUTSOURCE, *pstXC_SET_INPUTSOURCE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_YUVSPACE, *pstXC_CHECK_YUVSPACE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_MEMORYFORMAT422, *pstXC_CHECK_MEMORYFORMAT422;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_FORCE_RGBIN, *pstXC_SET_FORCE_RGBIN;

typedef struct
{
    MirrorMode_t eMirrorMode;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_MIRRORMODE_EX, *pstXC_SET_MIRRORMODE_EX;

typedef struct
{
    SCALER_WIN eWindow;
    MirrorMode_t eReturnValue;
} stXC_GET_MIRRORMODE_TYPEEX, *pstXC_GET_MIRRORMODE_TYPEEX;

typedef struct
{
    INPUT_SOURCE_TYPE_t eCurrentSrc;
    XC_IP_SYNC_STATUS *sXC_Sync_Status;
    SCALER_WIN eWindow;
} stXC_GET_SYNC_STATUS, *pstXC_GET_SYNC_STATUS;

typedef struct
{
    MS_U8 u8NumVSyncs;
    MS_U16 u16Timeout;
    SCALER_WIN eWindow;
    MS_U8 u8ReturnValue;
} stXC_SET_WAIT_OUTPUT_VSYNC, *pstXC_SET_WAIT_OUTPUT_VSYNC;

typedef struct
{
    MS_U8 u8NumVSyncs;
    MS_U16 u16Timeout;
    SCALER_WIN eWindow;
    MS_U8 u8ReturnValue;
} stXC_SET_WAIT_INPUT_VSYNC, *pstXC_SET_WAIT_INPUT_VSYNC;

typedef struct
{
    E_HDMI_SYNC_TYPE eSynctype;
} stXC_SET_HDMI_SYNCMODE, *pstXC_SET_HDMI_SYNCMODE;

typedef struct
{
    E_HDMI_SYNC_TYPE eReturnValue;
} stXC_GET_HDMI_SYNCMODE, *pstXC_GET_HDMI_SYNCMODE;

typedef struct
{
    MS_BOOL bEnable;
    MS_WINDOW_TYPE Window;
    MS_U8 u8Color;
} stXC_SET_REPORT_WINDOW, *pstXC_SET_REPORT_WINDOW;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_SKIP_OPWRITEOFF_IN_SETWINDOW, *pstXC_SET_SKIP_OPWRITEOFF_IN_SETWINDOW;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_GET_SKIP_OPWRITEOFF_IN_SETWINDOW, *pstXC_GET_SKIP_OPWRITEOFF_IN_SETWINDOW;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_SKIP_DISABLE_OPWRITEOFF_IN_FPLL, *pstXC_SET_SKIP_DISABLE_OPWRITEOFF_IN_FPLL;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_OPWRITEOFF_ENABLE, *pstXC_SET_OPWRITEOFF_ENABLE;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_OPWRITEOFF_ENABLE_TO_REG, *pstXC_SET_OPWRITEOFF_ENABLE_TO_REG;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_FORCESET_OPWRITEOFF_ENABLE, *pstXC_FORCESET_OPWRITEOFF_ENABLE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_GET_OPWRITEOFF_ENABLE, *pstXC_GET_OPWRITEOFF_ENABLE;

typedef struct
{
    MS_WINDOW_TYPE *pstDspwin;
    SCALER_WIN eWindow;
} stXC_SET_DISPLAY_WIN_TO_REG, *pstXC_SET_DISPLAY_WIN_TO_REG;

typedef struct
{
    MS_WINDOW_TYPE *pstDspwin;
    SCALER_WIN eWindow;
} stXC_GET_DISPLAY_WIN_FROM_REG, *pstXC_GET_DISPLAY_WIN_FROM_REG;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_FREEZEIMG, *pstXC_SET_FREEZEIMG;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_FREEZEIMG, *pstXC_CHECK_FREEZEIMG;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_BOTHWINDOW_BLACKVIDEO, *pstXC_SET_BOTHWINDOW_BLACKVIDEO;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_BLACKSCREEN, *pstXC_SET_BLACKSCREEN;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_BLACKVIDEO, *pstXC_SET_BLACKVIDEO;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_BLACKVIDEO_ENABLE, *pstXC_CHECK_BLACKVIDEO_ENABLE;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_FRAMEBUFFERLESS, *pstXC_SET_FRAMEBUFFERLESS;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_FRAMEBUFFERLESS, *pstXC_CHECK_FRAMEBUFFERLESS;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_REQUEST_FRAMEBUFFERLESS, *pstXC_SET_REQUEST_FRAMEBUFFERLESS;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_REQUEST_FRAMEBUFFERLESS, *pstXC_CHECK_REQUEST_FRAMEBUFFERLESS;

typedef struct
{
    MS_U16 u16ReturnValue;
} stXC_GET_3D_HWVERSION, *pstXC_GET_3D_HWVERSION;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_3D_SUPPORT_HW2DTO3D, *pstXC_CHECK_3D_SUPPORT_HW2DTO3D;

typedef struct
{
    E_XC_3D_INPUT_MODE e3dInputMode;
    E_XC_3D_OUTPUT_MODE e3dOutputMode;
    E_XC_3D_PANEL_TYPE e3dPanelType;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_3D_MODE, *pstXC_SET_3D_MODE;

typedef struct
{
    MS_BOOL bMainFirst;
    MS_BOOL bReturnValue;
} stXC_SET_3D_MAINWIN_FIRST, *pstXC_SET_3D_MAINWIN_FIRST;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_3D_LR_EXCHANGE, *pstXC_SET_3D_LR_EXCHANGE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_3D_LR_EXCHANGED, *pstXC_CHECK_3D_LR_EXCHANGED;

typedef struct
{
    SCALER_WIN eWindow;
    E_XC_3D_INPUT_MODE eReturnValue;
} stXC_GET_3D_INPUT_MODE, *pstXC_GET_3D_INPUT_MODE;

typedef struct
{
    E_XC_3D_OUTPUT_MODE eReturnValue;
} stXC_GET_3D_OUTPUT_MODE, *pstXC_GET_3D_OUTPUT_MODE;

typedef struct
{
    E_XC_3D_PANEL_TYPE eReturnValue;
} stXC_GET_3D_PANELTYPE, *pstXC_GET_3D_PANELTYPE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_GET_3D_MAINWIN_FIRST, *pstXC_GET_3D_MAINWIN_FIRST;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_3D_MAINSUB_IPSYNC, *pstXC_CHECK_3D_MAINSUB_IPSYNC;

typedef struct
{
    MS_U16 u163DVerVideoOffset;
    MS_BOOL bReturnValue;
} stXC_SET_3D_VERTICALVIDEO_OFFSET, *pstXC_SET_3D_VERTICALVIDEO_OFFSET;

typedef struct
{
    MS_U16 u16ReturnValue;
} stXC_GET_3D_VERTICALVIDEO_OFFSET, *pstXC_GET_3D_VERTICALVIDEO_OFFSET;

typedef struct
{
    E_XC_3D_INPUT_MODE e3dInputMode;
    E_XC_3D_OUTPUT_MODE e3dOutputMode;
    MS_BOOL bReturnValue;
} stXC_CHECK_3D_FORMAT_SUPPORTED, *pstXC_CHECK_3D_FORMAT_SUPPORTED;

typedef struct
{
    MS_U16 u16HShift;
    MS_BOOL bReturnValue;
} stXC_SET_3D_HORIZONTAL_SHIFT, *pstXC_SET_3D_HORIZONTAL_SHIFT;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bReturnValue;
} stXC_SET_3D_LR_SBS2LINE, *pstXC_SET_3D_LR_SBS2LINE;

typedef struct
{
    MS_U16 u16ReturnValue;
} stXC_GET_3D_HORIZONTAL_SHIFT, *pstXC_GET_3D_HORIZONTAL_SHIFT;

typedef struct
{
    MS_PHYADDR u32HW2DTO3D_DD_Buf;
    MS_PHYADDR u32HW2DTO3D_DR_Buf;
    MS_BOOL bReturnValue;
} stXC_SET_3D_HW2DTO3D_BUFFER, *pstXC_SET_3D_HW2DTO3D_BUFFER;

typedef struct
{
    MS_XC_3D_HW2DTO3D_PARA st3DHw2DTo3DPara;
    MS_BOOL bReturnValue;
} stXC_SET_3D_HW2DTO3D_PARAMETERS, *pstXC_SET_3D_HW2DTO3D_PARAMETERS;

typedef struct
{
    MS_XC_3D_HW2DTO3D_PARA *pst3DHw2DTo3DPara;
    MS_BOOL bReturnValue;
} stXC_GET_3D_HW2DTO3D_PARAMETERS, *pstXC_GET_3D_HW2DTO3D_PARAMETERS;

typedef struct
{
    MS_XC_3D_DETECT3DFORMAT_PARA *pstDetect3DFormatPara;
    MS_BOOL bReturnValue;
} stXC_SET_3D_DETECT_3DFORMAT_PARAMETERS, *pstXC_SET_3D_DETECT_3DFORMAT_PARAMETERS;

typedef struct
{
    MS_XC_3D_DETECT3DFORMAT_PARA *pstDetect3DFormatPara;
    MS_BOOL bReturnValue;
} stXC_GET_3D_DETECT_3DFORMAT_PARAMETERS, *pstXC_GET_3D_DETECT_3DFORMAT_PARAMETERS;

typedef struct
{
    SCALER_WIN eWindow;
    E_XC_3D_INPUT_MODE eReturnValue;
} stXC_GET_3D_FORMAT_DETECTED_BY_CONTENT, *pstXC_GET_3D_FORMAT_DETECTED_BY_CONTENT;

typedef struct
{
    SCALER_WIN eWindow;
    ST_DETECTNL_PARA* pstDetectNLatticePara;
    MS_BOOL bReturnValue;
} stXC_SET_NINELATTICE, *pstXC_SET_NINELATTICE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_3D_POST_PQSETTING, *pstXC_SET_3D_POST_PQSETTING;

typedef struct
{
    MS_XC_3D_FPINFO_PARA *pstFPInfoPara;
    MS_BOOL bReturnValue;
} stXC_SET_3D_FRAMEPACKING_INFO, *pstXC_SET_3D_FRAMEPACKING_INFO;

typedef struct
{
    MS_BOOL bEnable;
    E_XC_3D_AUTODETECT_METHOD enDetectMethod;
    MS_BOOL bReturnValue;
} stXC_SET_3D_AUTODETECT, *pstXC_SET_3D_AUTODETECT;

typedef struct
{
    E_XC_3D_AUTODETECT_METHOD *penDetectMethod;
    MS_BOOL *pbEnable;
    MS_BOOL bReturnValue;
} stXC_GET_3D_AUTODETECT_3DFLAG, *pstXC_GET_3D_AUTODETECT_3DFLAG;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_SET_3D_SUBWINCLOCK, *pstXC_SET_3D_SUBWINCLOCK;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_3D_LR_SBS2LINE, *pstXC_CHECK_3D_LR_SBS2LINE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_3D_SKIP_DEFAULT_LR_FLAG, *pstXC_CHECK_3D_SKIP_DEFAULT_LR_FLAG;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bReturnValue;
} stXC_SET_3D_SKIP_DEFAULT_LR_FLAG, *pstXC_SET_3D_SKIP_DEFAULT_LR_FLAG;

typedef struct
{
    void (*input_source_to_input_port)(INPUT_SOURCE_TYPE_t src_ids , E_MUX_INPUTPORT* port_ids , MS_U8* u8port_count ) ;
} stXC_SET_MUX_INIT, *pstXC_SET_MUX_INIT;

typedef struct
{
    MS_BOOL bRealTimeMonitorOnly;
} stXC_SET_MUX_SOURCE_MONITOR, *pstXC_SET_MUX_SOURCE_MONITOR;

typedef struct
{
    XC_MUX_PATH_INFO* Path_Info;
    MS_U32 u32InitDataLen;
    MS_S16 s16ReturnValue;
} stXC_SET_MUX_CREATE_PATH, *pstXC_SET_MUX_CREATE_PATH;

typedef struct
{
    INPUT_SOURCE_TYPE_t src;
    E_DEST_TYPE dest;
    MS_S16 s16ReturnValue;
} stXC_SET_MUX_DELETE_PATH, *pstXC_SET_MUX_DELETE_PATH;

typedef struct
{
    MS_U16 PathId;
    MS_S16 s16ReturnValue;
} stXC_SET_MUX_ENABLE_PATH, *pstXC_SET_MUX_ENABLE_PATH;

typedef struct
{
    INPUT_SOURCE_TYPE_t src;
    void* para;
} stXC_SET_MUX_TRIGGER_PATH_SYNC_EVENT, *pstXC_SET_MUX_TRIGGER_PATH_SYNC_EVENT;

typedef struct
{
    INPUT_SOURCE_TYPE_t src;
    void* para;
} stXC_SET_MUX_TRIGGER_DEST_ONOFF_EVENT, *pstXC_SET_MUX_TRIGGER_DEST_ONOFF_EVENT;

typedef struct
{
    INPUT_SOURCE_TYPE_t src;
    MS_BOOL bEnable;
    MS_S16 s16ReturnValue;
} stXC_SET_MUX_ONOFF_PERIODIC_HANDLER, *pstXC_SET_MUX_ONOFF_PERIODIC_HANDLER;

typedef struct
{
    XC_MUX_PATH_INFO* Paths;
    MS_U8 u8ReturnValue;
} stXC_GET_MUX_PATHINFO, *pstXC_GET_MUX_PATHINFO;

typedef struct
{
    MS_U8 u8MhlSupportInfo;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_MUX_SUPPORT_MHL_PATHINFO, *pstXC_SET_MUX_SUPPORT_MHL_PATHINFO;

typedef struct
{
    MS_BOOL bIsMhlHotPlugInverse;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_MUX_MHL_HOTPLUG_INVERSE_INFO, *pstXC_SET_MUX_MHL_HOTPLUG_INVERSE_INFO;

typedef struct
{
    INPUT_SOURCE_TYPE_t src;
    E_MUX_INPUTPORT eReturnValue;
} stXC_GET_MUX_HDMIPORT, *pstXC_GET_MUX_HDMIPORT;

typedef struct
{
    INPUT_SOURCE_TYPE_t u8InputSourceType;
    MS_U8 u8ReturnValue;
} stXC_GET_MUX_INPUTSOURCE2VDYMUXPORT, *pstXC_GET_MUX_INPUTSOURCE2VDYMUXPORT;

typedef struct
{
    MS_BOOL bEn;
    SCALER_WIN eWindow;
} stXC_SET_NR, *pstXC_SET_NR;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_UC_ENABLED, *pstXC_CHECK_UC_ENABLED;

typedef struct
{
    XC_Internal_TimingType timingtype;
} stXC_SET_GENERATE_SPECIFIC_TIMING, *pstXC_SET_GENERATE_SPECIFIC_TIMING;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_GET_DE_BYPASS_MODE, *pstXC_GET_DE_BYPASS_MODE;

typedef struct
{
    MS_WINDOW_TYPE *psWin;
    SCALER_WIN eWindow;
} stXC_GET_DE_WINDOW, *pstXC_GET_DE_WINDOW;

typedef struct
{
    MS_U16* pu16Width;
    MS_U16* pu16Height;
    SCALER_WIN eWindow;
} stXC_GET_DE_WIN_WIDTH_HEIGHT_IN_DE_BYPASS_MODE, *pstXC_GET_DE_WIN_WIDTH_HEIGHT_IN_DE_BYPASS_MODE;

typedef struct
{
    MS_WINDOW_TYPE* capture_win;
    SCALER_WIN eWindow;
} stXC_GET_CAPTURE_WINDOW, *pstXC_GET_CAPTURE_WINDOW;

typedef struct
{
    MS_U16 u16Vstart;
    SCALER_WIN eWindow;
} stXC_SET_CAPTURE_WINDOW_VSTART, *pstXC_SET_CAPTURE_WINDOW_VSTART;

typedef struct
{
    MS_U16 u16Hstart;
    SCALER_WIN eWindow;
} stXC_SET_CAPTURE_WINDOW_HSTART, *pstXC_SET_CAPTURE_WINDOW_HSTART;

typedef struct
{
    MS_U16 u16Vsize;
    SCALER_WIN eWindow;
} stXC_SET_CAPTURE_WINDOW_VSIZE, *pstXC_SET_CAPTURE_WINDOW_VSIZE;

typedef struct
{
    MS_U16 u16Hsize;
    SCALER_WIN eWindow;
} stXC_SET_CAPTURE_WINDOW_HSIZE, *pstXC_SET_CAPTURE_WINDOW_HSIZE;

typedef struct
{
    MS_U8 u8Reset;
    SCALER_WIN eWindow;
} stXC_SET_SOFTWARE_RESET, *pstXC_SET_SOFTWARE_RESET;

typedef struct
{
    MS_U16 u16HPeriod;
    MS_U16 u16ReturnValue;
} stXC_GET_HFREQX10, *pstXC_GET_HFREQX10;

typedef struct
{
    MS_U16 u16HPeriod;
    MS_U32 u32ReturnValue;
} stXC_GET_HFREQX1K, *pstXC_GET_HFREQX1K;

typedef struct
{
    MS_U16 u16HFreq;
    MS_U16 u16VTotal;
    MS_U16 u16ReturnValue;
} stXC_GET_VFREQX10, *pstXC_GET_VFREQX10;

typedef struct
{
    MS_U32 u32HFreqx1K;
    MS_U16 u16VTotal;
    MS_U32 u32ReturnValue;
} stXC_GET_VFREQX1K, *pstXC_GET_VFREQX1K;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U32 u32ReturnValue;
} stXC_GET_ACCURATE_VFREQX1k, *pstXC_GET_ACCURATE_VFREQX1k;

typedef struct
{
    SC_INT_SRC eIntNum;
    SC_InterruptCb pIntCb;
    void * pParam;
    MS_BOOL bReturnValue;
} stXC_SET_INTERRUPT_ATTACH, *pstXC_SET_INTERRUPT_ATTACH;

typedef struct
{
    SC_INT_SRC eIntNum;
    SC_InterruptCb pIntCb;
    void * pParam;
    MS_BOOL bReturnValue;
} stXC_SET_INTERRUPT_DEATTACH, *pstXC_SET_INTERRUPT_DEATTACH;

typedef struct
{
    MS_BOOL bDisable;
    SCALER_WIN eWindow;
} stXC_SET_DISABLE_INPUTSOURCE, *pstXC_SET_DISABLE_INPUTSOURCE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_INPUTSOURCE_DISABLED, *pstXC_CHECK_INPUTSOURCE_DISABLED;

typedef struct
{
    XC_PANEL_INFO *pstPanelInfo;
} stXC_SET_CHANGE_PANELTYPE, *pstXC_SET_CHANGE_PANELTYPE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U16 u16ReturnValue;
} stXC_GET_CURRENT_READBANK, *pstXC_GET_CURRENT_READBANK;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U16 u16ReturnValue;
} stXC_GET_CURRENT_WRITEBANK, *pstXC_GET_CURRENT_WRITEBANK;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_AUTO_PRESCALING, *pstXC_SET_AUTO_PRESCALING;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U8 u8ReturnValue;
} stXC_GET_VSYNC_WIDTH, *pstXC_GET_VSYNC_WIDTH;

typedef struct
{
    MS_U8 MaxGOP;
    MS_U8 UseNum;
    MS_U8 u8MuxNum;
    MS_BOOL bEnable;
    MS_BOOL bReturnValue;
} stXC_SET_GOP_ENABLE, *pstXC_SET_GOP_ENABLE;

typedef struct
{
    MS_U8 u8MuxNum;
    MS_XC_IPSEL_GOP ipSelGop;
} stXC_SET_SELECT_IP_FOR_GOP, *pstXC_SET_SELECT_IP_FOR_GOP;

typedef struct
{
    MS_XC_DST_DispInfo *pDstInfo;
    MS_U32 u32SizeofDstInfo;
    EN_GOP_XCDST_TYPE XCDstType;
    MS_BOOL bReturnValue;
} stXC_GET_DESTINATION_INFO, *pstXC_GET_DESTINATION_INFO;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_FDMASK_BYWIN, *pstXC_SET_FDMASK_BYWIN;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_GET_FDMASK_BYWIN, *pstXC_GET_FDMASK_BYWIN;

typedef struct
{
    MS_U8 u8Enable;
    MS_U16 u6Pattern_type;
    SCALER_WIN eWindow;
} stXC_SET_IP1_TESTPATTERN, *pstXC_SET_IP1_TESTPATTERN;

typedef struct
{
    XC_Internal_TimingType timingtype;
} stXC_SET_INIT_IP_FOR_INTERNAL_TIMING, *pstXC_SET_INIT_IP_FOR_INTERNAL_TIMING;

typedef struct
{
    MS_U8 u8Val;
} stXC_SET_IPMUX, *pstXC_SET_IPMUX;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_HSYNC_ACTIVE, *pstXC_CHECK_HSYNC_ACTIVE;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_VSYNC_ACTIVE, *pstXC_CHECK_VSYNC_ACTIVE;

typedef struct
{
    MS_U8 u8ValidData;
    SCALER_WIN eWindow;
    MS_WINDOW_TYPE *pstAutoPositionWindow;
    MS_BOOL bReturnValue;
} stXC_GET_AUTO_POSITION_WINDOW, *pstXC_GET_AUTO_POSITION_WINDOW;

typedef struct
{
    MS_PHYADDR u32FBAddress;
    MS_PHYADDR u32FBSize;
    SCALER_WIN eWindow;
} stXC_SET_FRAMEBUFFER_ADDRESS, *pstXC_SET_FRAMEBUFFER_ADDRESS;

typedef struct
{
    XC_SETWIN_INFO *pstXC_SetWin_Info;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_CHECK_FRAMEBUFFER_ENOUGH_FOR_CUSSCALING, *pstXC_CHECK_FRAMEBUFFER_ENOUGH_FOR_CUSSCALING;

typedef struct
{
    MS_BOOL bEnable;
    E_XC_MEMORY_REQUEST_TYPE eRequestType;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_SCALER_MEMORY_REQUEST, *pstXC_SET_SCALER_MEMORY_REQUEST;

typedef struct
{
    MS_U16 u16CorX;
    MS_U16 u16CorY;
    MS_PIXEL_32BIT* pixel;
} stXC_GET_PIXEL_DATA, *pstXC_GET_PIXEL_DATA;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U8 u8FBNum;
    MS_U32 u32InputSize;
    MS_U32 u32ReturnValue;
} stXC_GET_AVAILABLE_SIZE, *pstXC_GET_AVAILABLE_SIZE;

typedef struct
{
    MS_U32 u32aRGB;
} stXC_SET_FRAME_COLOR, *pstXC_SET_FRAME_COLOR;

typedef struct
{
    MS_U8 u8Color;
    SCALER_WIN eWindow;
} stXC_SET_DISPLAY_WINDOW_COLOR, *pstXC_SET_DISPLAY_WINDOW_COLOR;

typedef struct
{
    MS_U16* pOutputCapability;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_SUPPORT_SOURCE_TO_VE, *pstXC_GET_SUPPORT_SOURCE_TO_VE;

typedef struct
{
    MS_BOOL bEnable;
    E_XC_SOURCE_TO_VE eSourceToVE;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OUTPUT_CAPTURE, *pstXC_SET_OUTPUT_CAPTURE;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_GAMMA_ONOFF, *pstXC_SET_GAMMA_ONOFF;

typedef struct
{
    SCALER_WIN eWindow;
    MS_XC_VOP_CHANNEL_t eVop_Channel;
    MS_U16 u16Val;
} stXC_SET_PREGAMMA_GAIN, *pstXC_SET_PREGAMMA_GAIN;

typedef struct
{
    SCALER_WIN eWindow;
    MS_XC_VOP_CHANNEL_t eVop_Channel;
    MS_U16 u16Val;
} stXC_SET_PREGAMMA_OFFSET, *pstXC_SET_PREGAMMA_OFFSET;

typedef struct
{
    XC_SetTiming_Info *pTimingInfo;
    SCALER_WIN eWindow;
} stXC_SET_PANEL_TIMING, *pstXC_SET_PANEL_TIMING;

typedef struct
{
    E_XC_PNL_OUT_TIMING_MODE enPnl_Out_Timing_Mode;
} stXC_SET_OUTPUT_TIMING_MODE, *pstXC_SET_OUTPUT_TIMING_MODE;

typedef struct
{
    MS_U16 u16FrontPorch;
    MS_U16 u16SyncWidth;
    MS_U16 u16OutputVfreq;
    MS_BOOL bReturnValue;
} stXC_SET_CUSTOMER_SYNC_INFO, *pstXC_SET_CUSTOMER_SYNC_INFO;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_GET_WAIT_FPLL_DONE, *pstXC_GET_WAIT_FPLL_DONE;

typedef struct
{
    MS_U16 u16ReturnValue;
} stXC_GET_OUTPUT_VFREQX100, *pstXC_GET_OUTPUT_VFREQX100;

typedef struct
{
    MS_U16 u16ReturnValue;
} stXC_GET_OP1_OUTPUT_VFREQX100, *pstXC_GET_OP1_OUTPUT_VFREQX100;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_FRAMELOCK, *pstXC_CHECK_FRAMELOCK;

typedef struct
{
    SC_FRC_SETTING * stFRCTable;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_CUSTOMIZE_FRC_TABLE, *pstXC_SET_CUSTOMIZE_FRC_TABLE;

typedef struct
{
    MS_BOOL bEnable;
    XC_OUTPUTFRAME_Info *pstOutFrameInfo;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OUTPUT_FRAME_CONTROL, *pstXC_SET_OUTPUT_FRAME_CONTROL;

typedef struct
{
    MS_BOOL bTrue;
} stXC_SET_FPLL_FSM_ENABLE, *pstXC_SET_FPLL_FSM_ENABLE;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_FORCE_FREERUN, *pstXC_SET_FORCE_FREERUN;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_FORCE_FREERUN, *pstXC_CHECK_FORCE_FREERUN;

typedef struct
{
    E_VFREQ_SEL VFreq;
} stXC_SET_FREERUN_FREQ, *pstXC_SET_FREERUN_FREQ;

typedef struct
{
    MS_BOOL bEnable;
    XC_PANEL_INFO_EX *pPanelInfoEx;
    MS_BOOL bReturnValue;
} stXC_SET_EXPANEL_INFO, *pstXC_SET_EXPANEL_INFO;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_FPLL_THRESHMODE, *pstXC_SET_FPLL_THRESHMODE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_GET_FPLL_THRESHMODE, *pstXC_GET_FPLL_THRESHMODE;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_IPAUTONOSIGNAL, *pstXC_SET_IPAUTONOSIGNAL;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_GET_IPAUTONOSIGNAL, *pstXC_GET_IPAUTONOSIGNAL;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_IPAUTOCOAST, *pstXC_SET_IPAUTOCOAST;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_FPLL_MANUAL_SETTING_ENABLE, *pstXC_SET_FPLL_MANUAL_SETTING_ENABLE;

typedef struct
{
    MS_U32 u32FpllSetOffset;
    MS_U16 u16TestCnt;
} stXC_SET_FPLL_BOUNDARY_TEST, *pstXC_SET_FPLL_BOUNDARY_TEST;

typedef struct
{
    INPUT_SOURCE_TYPE_t u8InputSourceType;
} stXC_SET_OFFLINE_DETECTION, *pstXC_SET_OFFLINE_DETECTION;

typedef struct
{
    INPUT_SOURCE_TYPE_t u8InputSourceType;
    MS_U8 u8ReturnValue;
} stXC_GET_OFFLINE_DETECTION, *pstXC_GET_OFFLINE_DETECTION;

typedef struct
{
    MS_U8 u8Threshold;
    MS_BOOL bReturnValue;
} stXC_SET_OFFLINE_SOG_THRESHOLD, *pstXC_SET_OFFLINE_SOG_THRESHOLD;

typedef struct
{
    MS_U8 u8BW;
    MS_BOOL bReturnValue;
} stXC_SET_OFFLINE_SOG_BW, *pstXC_SET_OFFLINE_SOG_BW;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_SET_OFFLINE_INIT, *pstXC_SET_OFFLINE_INIT;

typedef struct
{
    MS_U8 u8val;
} stXC_SET_EXTRA_FETCH_ADV_LINE, *pstXC_SET_EXTRA_FETCH_ADV_LINE;

typedef struct
{
    MS_BOOL bVGASogEn;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_VGA_SOG_ENABLE, *pstXC_SET_VGA_SOG_ENABLE;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_WINDOW_ENABLE, *pstXC_SET_WINDOW_ENABLE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_SUBWINDOW_ENABLE, *pstXC_CHECK_SUBWINDOW_ENABLE;

typedef struct
{
    MS_U8 u8Left;
    MS_U8 u8Right;
    MS_U8 u8Up;
    MS_U8 u8Down;
    MS_U8 u8color;
    SCALER_WIN eWindow;
} stXC_SET_BORDER_FORMAT, *pstXC_SET_BORDER_FORMAT;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_BORDER_ENABLE, *pstXC_SET_BORDER_ENABLE;

typedef struct
{
    MS_BOOL bMainFirst;
} stXC_SET_ZORDER_MAINWINDOW_FIRST, *pstXC_SET_ZORDER_MAINWINDOW_FIRST;

typedef struct
{
    PQ_Function_Info* function_Info;
    MS_U32 u32InitDataLen;
} stXC_SET_PQ_LOADFUNCTION, *pstXC_SET_PQ_LOADFUNCTION;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_H_NONLINEAR_SCALING, *pstXC_CHECK_H_NONLINEAR_SCALING;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_EUROHDTV_SUPPORT_ENABLE, *pstXC_SET_EUROHDTV_SUPPORT_ENABLE;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_EUROHDTV_DETECTION_ENABLE, *pstXC_SET_EUROHDTV_DETECTION_ENABLE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U8 u8ReturnValue;
} stXC_READBYTE, *pstXC_READBYTE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U8 u8Val;
} stXC_WRITEBYTE, *pstXC_WRITEBYTE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U8 u8Val;
    MS_U8 u8Msk;
} stXC_WRITEBYTEMSK, *pstXC_WRITEBYTEMSK;

typedef struct
{
    MS_U32 u32Reg;
    MS_U16 u16val;
    MS_U16 u16Mask;
} stXC_WRITE2BYTEMSK, *pstXC_WRITE2BYTEMSK;

typedef struct
{
    MS_U32 u32Reg;
    MS_U16 u16Val;
} stXC_W2BYTE, *pstXC_W2BYTE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U16 u16ReturnValue;
} stXC_R2BYTE, *pstXC_R2BYTE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U32 u32Val;
} stXC_W4BYTE, *pstXC_W4BYTE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U32 u32ReturnValue;
} stXC_R4BYTE, *pstXC_R4BYTE;

typedef struct
{
    MS_U32 u32Reg;
    MS_U16 u16mask;
    MS_U16 u16ReturnValue;
} stXC_R2BYTEMSK, *pstXC_R2BYTEMSK;

typedef struct
{
    MS_U32 u32Reg;
    MS_U16 u16Val;
    MS_U16 u16mask;
} stXC_W2BYTEMSK, *pstXC_W2BYTEMSK;

typedef struct
{
    MS_PHYADDR PhyAddr;
    MS_U32 u32BufByteLen;
} stXC_MLOAD_INIT, *pstXC_MLOAD_INIT;

typedef struct
{
    MS_BOOL bEnable;
} stXC_MLOAD_ENABLE, *pstXC_MLOAD_ENABLE;

typedef struct
{
    MLOAD_TYPE eReturnValue;
} stXC_MLOAD_GETSTATUS, *pstXC_MLOAD_GETSTATUS;

typedef struct
{
    MS_U32 u32Addr;
    MS_U16 u16Data;
    MS_U16 u16Mask;
    MS_BOOL bReturnValue;
} stXC_MLOAD_WRITE_CMD_AND_FIRE, *pstXC_MLOAD_WRITE_CMD_AND_FIRE;

typedef struct
{
    MS_U32 *pu32Addr;
    MS_U16 *pu16Data;
    MS_U16 *pu16Mask;
    MS_U16 u16CmdCnt;
    MS_BOOL bReturnValue;
} stXC_MLOAD_WRITE_CMDS_AND_FIRE, *pstXC_MLOAD_WRITE_CMDS_AND_FIRE;

typedef struct
{
    MS_PHYADDR PhyAddr;
    MS_U32 u32BufByteLen;
} stXC_MLG_INIT, *pstXC_MLG_INIT;

typedef struct
{
    MS_BOOL bEnable;
} stXC_MLG_ENABLE, *pstXC_MLG_ENABLE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_MLG_GET_CAPS, *pstXC_MLG_GET_CAPS;

typedef struct
{
    MLG_TYPE eReturnValue;
} stXC_MLG_GETSTATUS, *pstXC_MLG_GETSTATUS;

typedef struct
{
    EN_VOP_SEL_OSD_XC2VE_MUX  eVOPSelOSD_MUX;
} stXC_SET_OSD2VEMODE, *pstXC_SET_OSD2VEMODE;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_IP2_PREFILTER_ENABLE, *pstXC_SET_IP2_PREFILTER_ENABLE;

typedef struct
{
    XC_Get_Pixel_RGB *pData;
    SCALER_WIN eWindow;
    E_APIXC_GET_PixelRGB_ReturnValue eReturnValue;
} stXC_GET_PIXELRGB, *pstXC_GET_PIXELRGB;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_KEEP_PIXELPOINTER_APPEAR, *pstXC_SET_KEEP_PIXELPOINTER_APPEAR;

typedef struct
{
    MS_XC_MEM_FMT eMemFmt;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_MEMORY_FORMAT_EX, *pstXC_SET_MEMORY_FORMAT_EX;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_REQUEST_FRAMEBUFFERLESS_MODE, *pstXC_CHECK_REQUEST_FRAMEBUFFERLESS_MODE;

typedef struct
{
    MS_BOOL bFlag;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_SKIP_SWRESET, *pstXC_SET_SKIP_SWRESET;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_REPORTWINDOW_FOR_FRAMECOLOR, *pstXC_SET_REPORTWINDOW_FOR_FRAMECOLOR;

typedef struct
{
    E_VOP_OSD_LAYER_SEL eVOPOSDLayer;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OSDLAYER, *pstXC_SET_OSDLAYER;

typedef struct
{
    SCALER_WIN eWindow;
    E_VOP_OSD_LAYER_SEL eReturnValue;
} stXC_GET_OSDLAYER, *pstXC_GET_OSDLAYER;

typedef struct
{
    MS_U8 u8Val;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_VIDEO_ALPHA, *pstXC_SET_VIDEO_ALPHA;

typedef struct
{
    MS_U8 *pu8Val;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_VIDEO_ALPHA, *pstXC_GET_VIDEO_ALPHA;

typedef struct
{
    MS_BOOL eWindow;
    MS_BOOL bIsSkipWaitVsyn;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SKIP_WAIT_VSYNC, *pstXC_SKIP_WAIT_VSYNC;

typedef struct
{
    E_OP2VOP_DE_SEL eVopDESel;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OP2VOP_DE_SELECTION, *pstXC_SET_OP2VOP_DE_SELECTION;

typedef struct
{
    E_XC_3D_INPUT_MODE e3dInputMode;
    E_XC_3D_OUTPUT_MODE e3dOutputMode;
    E_XC_3D_PANEL_TYPE e3dPanelType;
} stXC_SET_FRC_WINDOW, *pstXC_SET_FRC_WINDOW;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_2INITFACTOR_ENABLE, *pstXC_SET_2INITFACTOR_ENABLE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_CHECK_FIELDPACKINGMODE_SUPPORTED, *pstXC_CHECK_FIELDPACKINGMODE_SUPPORTED;

typedef struct
{
    E_XC_PREINIT_t eType;
    void* para;
    MS_U32 u32Length;
    E_APIXC_ReturnValue eReturnValue;
} stXC_PREINIT, *pstXC_PREINIT;

typedef struct
{
    E_XC_OUTPUTDATA_TYPE eBufType;
    MS_WINDOW_TYPE *pRect;
    void *pRectBuf;
    SCALER_WIN eWindow;
} stXC_GET_BUFFERDATA, *pstXC_GET_BUFFERDATA;

typedef struct
{
    E_XC_INPUTDATA_TYPE eBufType;
    MS_WINDOW_TYPE *pDstRect;
    void *pSrcBuf;
    MS_WINDOW_TYPE *pSrcRect;
    SCALER_WIN eWindow;
} stXC_SET_BUFFERDATA, *pstXC_SET_BUFFERDATA;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_MAINWINDOW_ENABLE, *pstXC_SET_MAINWINDOW_ENABLE;

typedef struct
{
    MS_WINDOW_TYPE *pstDispWin;
} stXC_SET_SUBWINDOW_ENABLE, *pstXC_SET_SUBWINDOW_ENABLE;

typedef struct
{
    MS_S8 s8H;
    MS_S8 s8V;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_PIXEL_SHIFT, *pstXC_SET_PIXEL_SHIFT;

typedef struct
{
    E_VIDEO_ON_OSD_LAYER enlayer;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_VIDEO_ON_OSD, *pstXC_SET_VIDEO_ON_OSD;

typedef struct
{
    MS_U8 u8Layer;
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OSD_LAYER_BLENDING, *pstXC_SET_OSD_LAYER_BLENDING;

typedef struct
{
    MS_U8 u8Layer;
    MS_U8 u8Alpha;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OSD_LAYER_ALPHA, *pstXC_SET_OSD_LAYER_ALPHA;

typedef struct
{
    E_XC_OSD_INDEX enOsdIndex;
    E_XC_OSD_BlENDING_TYPE enType;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OSD_BLENDING_FORMULA, *pstXC_SET_OSD_BLENDING_FORMULA;

typedef struct
{
    MS_XC_REPORT_PIXELINFO *pstRepPixInfo;
    MS_BOOL bReturnValue;
} stXC_GET_REPORT_PIXEL_INFO, *pstXC_GET_REPORT_PIXEL_INFO;

typedef struct
{
    MS_BOOL bEnable;
    E_XC_SCALING_TYPE eScaling_type;
    E_XC_VECTOR_TYPE eVector_type;
    SCALER_WIN eWindow;
} stXC_SET_SCALING, *pstXC_SET_SCALING;

typedef struct
{
    MS_PHYADDR u32FBAddress;
    MS_PHYADDR u32FBSize;
    E_XC_MCDI_TYPE eType;
} stXC_SET_MCDI_BUFFERADDRESS, *pstXC_SET_MCDI_BUFFERADDRESS;

typedef struct
{
    MS_BOOL bEnable;
    E_XC_MCDI_TYPE eType;
} stXC_SET_MCDI_ENABLE, *pstXC_SET_MCDI_ENABLE;

typedef struct
{
    MS_U8 u8Cmd;
    MS_U8 count;
    FRC_R2_CMD_PARAMETER_t pFRC_R2_Para;
    MS_BOOL bReturnValue;
} stXC_SEND_CMD2FRC, *pstXC_SEND_CMD2FRC;

typedef struct
{
    MS_U8* pu8Cmd;
    MS_U8* pu8ParaCount;
    MS_U8* pu8Para;
    MS_BOOL bReturnValue;
} stXC_GET_MSG_FROM_FRC, *pstXC_GET_MSG_FROM_FRC;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_AUTO_RWBANK_ENABLE, *pstXC_SET_AUTO_RWBANK_ENABLE;

typedef struct
{
    MS_U8 u8Val;
    SCALER_WIN eWindow;
} stXC_SET_RWBANK_MAPPING_NUM, *pstXC_SET_RWBANK_MAPPING_NUM;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U8 u8ReturnValue;
} stXC_GET_RWBANK_MAPPING_NUM, *pstXC_GET_RWBANK_MAPPING_NUM;

typedef struct
{
    SCALER_WIN eWindow;
    MS_U8 u8ReturnValue;
} stXC_GET_RWBANK_MAPPING_NUM_FOR_ZAP, *pstXC_GET_RWBANK_MAPPING_NUM_FOR_ZAP;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
    MS_BOOL bReturnValue;
} stXC_SET_BOBMODE, *pstXC_SET_BOBMODE;

typedef struct
{
    MS_BOOL bEnable;
    MS_U8 u8Bank;
    SCALER_WIN eWindow;
} stXC_SET_FORCE_READBANK, *pstXC_SET_FORCE_READBANK;

typedef struct
{
    MS_U16 u16LockPoint;
    SCALER_WIN eWindow;
} stXC_SET_LOCK_POINT, *pstXC_SET_LOCK_POINT;

typedef struct
{
    EN_LD_PANEL_TYPE enLDPanelType;
    MS_BOOL bReturnValue;
} stXC_LD_INIT, *pstXC_LD_INIT;

typedef struct
{
    MS_U8 u8MIU;
    MS_U32 u32LDFBase0;
    MS_U32 u32LDFBase1;
    MS_U32 u32LDBBase0;
    MS_U32 u32LDBBase1;
    MS_U32 u32EDGE2DBase;
    MS_U32 u32LEDOffset;
    MS_BOOL bReturnValue;
} stXC_SET_LD_MEMORYADDRESS, *pstXC_SET_LD_MEMORYADDRESS;

typedef struct
{
    MS_U8 *pu8LDValue;
    MS_U8 u8WSize;
    MS_U8 u8HSize;
    MS_BOOL bReturnValue;
} stXC_GET_LD_VALUE, *pstXC_GET_LD_VALUE;

typedef struct
{
    EN_LD_MODE enMode;
    MS_BOOL bReturnValue;
} stXC_SET_LD_LEVEL, *pstXC_SET_LD_LEVEL;

typedef struct
{
    MS_BOOL bTurnoffBL;
    MS_BOOL bReturnValue;
} stXC_SET_LD_TURNOFF_LDBL, *pstXC_SET_LD_TURNOFF_LDBL;

typedef struct
{
    MS_BOOL bRefreshSPIData;
    MS_BOOL bReturnValue;
} stXC_SET_NOTUPDATE_SPI_DATA_FLAGS, *pstXC_SET_NOTUPDATE_SPI_DATA_FLAGS;

typedef struct
{
    MS_BOOL bUserLDFlags;
    MS_BOOL bReturnValue;
} stXC_SET_LD_USERMODEFLAGS, *pstXC_SET_LD_USERMODEFLAGS;

typedef struct
{
    MS_U8 u8BLLevel;
    MS_BOOL bReturnValue;
} stXC_SET_BL_LEVEL, *pstXC_SET_BL_LEVEL;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_BWS_MODE, *pstXC_SET_BWS_MODE;

typedef struct
{
    MS_U16 u16Path_sel;
    MS_BOOL bEnable;
} stXC_SET_FRC_COLOR_PATH_CONTROL, *pstXC_SET_FRC_COLOR_PATH_CONTROL;

typedef struct
{
    MS_U16 u16RedGain;
    MS_U16 u16GreenGain;
    MS_U16 u16BlueGain;
} stXC_SET_FRC_OP2_RGBGAIN, *pstXC_SET_FRC_OP2_RGBGAIN;

typedef struct
{
    MS_U16 u16RedOffset;
    MS_U16 u16GreenOffset;
    MS_U16 u16BlueOffset;
} stXC_SET_FRC_OP2_RGBOFFSET, *pstXC_SET_FRC_OP2_RGBOFFSET;

typedef struct
{
    MS_U16 u16dither;
} stXC_SET_FRC_OP2_DITHER, *pstXC_SET_FRC_OP2_DITHER;

typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bReturnValue;
} stXC_FRC_BYPASS, *pstXC_FRC_BYPASS;

typedef struct
{
    MS_BOOL bEnable;
} stXC_FRC_MUTE, *pstXC_FRC_MUTE;

typedef struct
{
    MS_BOOL bEnable;
    MS_U16 u16FrameIndex;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_FORCE_READ_FRAME, *pstXC_SET_FORCE_READ_FRAME;

typedef struct
{
    MS_BOOL bEnable;
    SCALER_WIN eWindow;
} stXC_SET_CSC, *pstXC_SET_CSC;

typedef struct
{
    void (*fpPQCB)(MS_U8 u8PQWin);
} stXC_SET_REGISTER_PQ_FPLL_THRESH_MODE, *pstXC_SET_REGISTER_PQ_FPLL_THRESH_MODE;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_GET_FREERUN_STATUS, *pstXC_GET_FREERUN_STATUS;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_BYPASS_CSC, *pstXC_SET_BYPASS_CSC;

typedef struct
{
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_DS_FORCE_INDEX_SUPPORTED, *pstXC_GET_DS_FORCE_INDEX_SUPPORTED;

typedef struct
{
    MS_BOOL bEnable;
    MS_U8 u8Index;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_DS_FORCE_INDEX, *pstXC_SET_DS_FORCE_INDEX;

typedef struct
{
    E_XC_DS_INDEX_SOURCE eDSIdxSrc;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_DS_INDEX_SOURCE_SELECT, *pstXC_SET_DS_INDEX_SOURCE_SELECT;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_GET_DS_STATUS, *pstXC_GET_DS_STATUS;

typedef struct
{
    E_XC_OSDC_TGEN_Type e_osdctgen_type;
    MS_XC_OSDC_TGEN_INFO *pstOC_Tgen_Cus;
    MS_XC_OSDC_CTRL_INFO *pstOC_Ctrl;
    E_APIXC_ReturnValue eReturnValue;
} stXC_OSDC_INITSETTING, *pstXC_OSDC_INITSETTING;

typedef struct
{
    MS_U16 u16Vfreq;
} stXC_OSDC_SET_OUTPUTVFREQX10, *pstXC_OSDC_SET_OUTPUTVFREQX10;

typedef struct
{
    MS_U32 eCtrl_type;
    E_APIXC_ReturnValue eReturnValue;
} stXC_OSDC_CONTROL, *pstXC_OSDC_CONTROL;

typedef struct
{
    MS_OSDC_DST_DispInfo *pDstInfo;
    MS_U32 u32SizeofDstInfo;
    E_APIXC_ReturnValue eReturnValue;
} stXC_OSDC_GET_DESTINATION_INFO, *pstXC_OSDC_GET_DESTINATION_INFO;

typedef struct
{
    EN_POWER_MODE enPowerState;
    MS_U32 u32ReturnValue;
} stXC_SET_POWERSTATE, *pstXC_SET_POWERSTATE;

typedef struct
{
    MS_U16 u16VsyncStart;
    MS_U16 u16VsyncEnd;
} stXC_SET_BYPASS_OSDVSYNC_POS, *pstXC_SET_BYPASS_OSDVSYNC_POS;

typedef struct
{
    MS_BOOL bEnable;
    E_XC_BYPASS_InputSource input;
} stXC_SET_BYPASS_INPUTSRC, *pstXC_SET_BYPASS_INPUTSRC;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL bEnable;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_SEAMLESS_ZAPPING, *pstXC_SET_SEAMLESS_ZAPPING;

typedef struct
{
    SCALER_WIN eWindow;
    MS_BOOL* pbEnable;
    E_APIXC_ReturnValue eReturnValue;
} stXC_GET_SEAMLESS_ZAPPING_STATUS, *pstXC_GET_SEAMLESS_ZAPPING_STATUS;


typedef struct
{
    MS_U16 u16Timecode;
    MS_U8 u8OperatorID;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_VTRACK_PAYLOADDATA, *pstXC_SET_VTRACK_PAYLOADDATA;

typedef struct
{
    MS_BOOL bUserDefinded;
    MS_U8* pu8Setting;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_VTRACK_USERDEFINED_SETTING, *pstXC_SET_VTRACK_USERDEFINED_SETTING;

typedef struct
{
    MS_U8 u8FrameRate;
    MS_BOOL bEnable;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_VTRACK_ENABLE, *pstXC_SET_VTRACK_ENABLE;

typedef struct
{
    XC_SETWIN_INFO *pstXC_SetWin_Info;
    SCALER_WIN eWindow;
} stXC_PRESET_PQINFO, *pstXC_PRESET_PQINFO;

typedef struct
{
    MS_BOOL bReturnValue;
} stXC_GET_OP1_TESTPATTERN_ENABLED, *pstXC_GET_OP1_TESTPATTERN_ENABLED;

typedef struct
{
    EN_XC_OP1_PATTERN ePattern;
    EN_XC_OP1_PATGEN_MODE eMode;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OP1_TESTPATTERN, *pstXC_SET_OP1_TESTPATTERN;

typedef struct
{
    EN_XC_WB_PATTERN_MODE eWBPattern;
    MS_BOOL eReturnValue;
} stXC_CHECK_WB_TESTPATTERN, *pstXC_CHECK_WB_TESTPATTERN;


typedef struct
{
    MS_BOOL bEnable;
    MS_U16 u16R_Data;
    MS_U16 u16G_Data;
    MS_U16 u16B_Data;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OP2_TESTPATTERN, *pstXC_SET_OP2_TESTPATTERN;


typedef struct
{
    MS_BOOL bEnable;
    MS_BOOL bSign;
    MS_U16 u16Delta;
    SCALER_WIN eWindow;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_HLINEARSCALING, *pstXC_SET_HLINEARSCALING;

typedef struct
{
    MS_BOOL bEnable;
    E_APIXC_ReturnValue eReturnValue;
} stXC_EnableT3D, *pstXC_EnableT3D;

// OBSOLETE STRUCT **START**, please avoid using these
typedef struct
{
    MS_U16 u16ReturnValue;
} stXC_GET_OUTPUT_VFREQ, *pstXC_GET_OUTPUT_VFREQ;

typedef struct
{
    MS_U32 u32ReturnValue;
} stXC_GET_CURRENT_OUTPUTVFREQX100, *pstXC_GET_CURRENT_OUTPUTVFREQX100;

typedef struct
{
    MS_BOOL bEnable;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_MEMORY_WRITE_REQUEST, *pstXC_SET_MEMORY_WRITE_REQUEST;

typedef struct
{
    MS_XC_MEM_FMT eMemFmt;
    MS_BOOL bReturnValue;
} stXC_SET_MEMORY_FORMAT, *pstXC_SET_MEMORY_FORMAT;

typedef struct
{
    XC_OUTPUT_TIMING_ADJUST_SETTING *stAdjSetting;
    E_APIXC_ReturnValue eReturnValue;
} stXC_SET_OUTPUT_ADJUST_SETTING, *pstXC_SET_OUTPUT_ADJUST_SETTING;

typedef struct
{
    SCALER_WIN eWindow;
} stXC_SET_FPLL_FSM, *pstXC_SET_FPLL_FSM;

typedef struct
{
    MS_BOOL bEnable;
} stXC_SET_MIRROR_MODE_ENABLE, *pstXC_SET_MIRROR_MODE_ENABLE;

typedef struct
{
    MirrorMode_t eMirrorMode;
} stXC_SET_MIRROR_MODE2_ENABLE, *pstXC_SET_MIRROR_MODE2_ENABLE;

typedef struct
{
    MirrorMode_t eReturnValue;
} stXC_GET_MIRROR_MODE_TYPE, *pstXC_GET_MIRROR_MODE_TYPE;
// OBSOLETE STRUCT **END**, please avoid using these

typedef struct
{
    E_XC_FRC_InputTiming enFRC_InputTiming;
    E_APIXC_ReturnValue eReturnValue;
} stXC_Set_FRC_InputTiming, *pstXC_Set_FRC_InputTiming;

typedef struct
{
    E_XC_FRC_InputTiming *penFRC_InputTiming;
    E_APIXC_ReturnValue eReturnValue;
} stXC_Get_FRC_InputTiming, *pstXC_Get_FRC_InputTiming;

#ifdef _XC_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#undef INTERFACE

#ifdef __cplusplus
}
#endif

#endif //_XC_H_
