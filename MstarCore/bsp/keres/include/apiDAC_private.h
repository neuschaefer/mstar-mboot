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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DAC_PRIV_H_
#define _DAC_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvBDMA.h
/// @author MStar Semiconductor Inc.
/// @brief Byte DMA control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

typedef APIDAC_Result              (*IOCTL_DAC_GET_LIBVER)                  (const MSIF_Version **);
typedef const DAC_ApiInfo *              (*IOCTL_DAC_GET_INFO)                    (void);
typedef MS_BOOL                    (*IOCTL_DAC_GET_STATUS)                  (DAC_ApiStatus *);
typedef MS_BOOL                    (*IOCTL_DAC_SET_DBG_LEVEL)               (MS_U16);
typedef MS_BOOL                    (*IOCTL_DAC_INIT)                         (void);
typedef void                       (*IOCTL_DAC_ENABLE)                       (MS_BOOL, MS_BOOL);
typedef void                       (*IOCTL_DAC_SET_CLKINV)                  (MS_BOOL, MS_BOOL);
typedef void                       (*IOCTL_DAC_SET_YPBPR_OUTPUTTIMING)     (E_OUTPUT_VIDEO_TIMING_TYPE);
typedef void                       (*IOCTL_DAC_SET_OUTPUT_SOURCE)           (E_DAC_OUTPUT_TYPE, MS_BOOL);
typedef void                       (*IOCTL_DAC_SET_OUTPUT_LEVE)             (E_DAC_MAX_OUTPUT_LEVEL, MS_BOOL);
typedef void                       (*IOCTL_DAC_SET_OUTPUT_SWAPSEL)          (E_DAC_SWAP_SEL, MS_BOOL);
typedef void                       (*IOCTL_DAC_ONOFF_SD)                     (E_DAC_SD_ENABLE_CTRL);
typedef void                       (*IOCTL_DAC_ONOFF_HD)                     (E_DAC_HD_ENABLE_CTRL);
typedef void                       (*IOCTL_DAC_CLKSEL)                       (E_OUTPUT_VIDEO_TIMING_TYPE, E_OUTPUT_BIT_TYPE);
typedef void                       (*IOCTL_DAC_DUMP_TABLE)                   (MS_U8 *, MS_U8);
typedef void                       (*IOCTL_DAC_EXIT)                         (void);
typedef void                       (*IOCTL_DAC_SET_IHALF_OUTPUT)            (MS_BOOL, MS_BOOL);
typedef void                       (*IOCTL_DAC_SET_QUART_OUTPUT)            (MS_BOOL, MS_BOOL);
typedef void                       (*IOCTL_DAC_SET_DAC_STATE)               (MS_BOOL, MS_BOOL);
typedef MS_BOOL                    (*IOCTL_DAC_HOTPLUG_DETECT)              (E_DAC_DETECT, E_DAC_DETECT_TYPE, MS_BOOL *);

typedef enum
{
    E_DAC_POOL_ID_INTERNAL_VARIABLE = 0,
    E_DAC_POOL_ID_MAX,
} E_DAC_POOL_ID;

typedef struct
{
    // flow control related
    DAC_ApiInfo _cstDac_ApiInfo;
    DAC_ApiStatus _stDac_ApiStatus;
    MS_U16 _u16DbgSwitch;
} ST_API_DAC;

typedef struct
{
    // flow control related
    MS_BOOL bResourceRegistered;
    ST_API_DAC stapiDAC;
} DAC_RESOURCE_PRIVATE;

typedef struct _DAC_INSTANT_PRIVATE
{
    IOCTL_DAC_GET_LIBVER                  fpDACGetLibVer;
    IOCTL_DAC_GET_INFO        	          fpDACGetInfo;
    IOCTL_DAC_GET_STATUS  		          fpDACGetStatus;
    IOCTL_DAC_SET_DBG_LEVEL               fpDACSetDbgLevel;
    IOCTL_DAC_INIT        	              fpDACInit;
    IOCTL_DAC_ENABLE  		              fpDACEnable;
    IOCTL_DAC_SET_CLKINV                  fpDACSetClkInv;
    IOCTL_DAC_SET_YPBPR_OUTPUTTIMING      fpDACSetYPbPrOutputTiming;
    IOCTL_DAC_SET_OUTPUT_SOURCE  		  fpDACSetOutputSource;
    IOCTL_DAC_SET_OUTPUT_LEVE             fpDACSetOutputLevel;
    IOCTL_DAC_SET_OUTPUT_SWAPSEL          fpDACSetOutputSwapSel;
    IOCTL_DAC_ONOFF_SD  		          fpDACOnOffSD;
    IOCTL_DAC_ONOFF_HD                    fpDACOnOffHD;
    IOCTL_DAC_CLKSEL  		              fpDACClkSel;
    IOCTL_DAC_DUMP_TABLE                  fpDACDumpTable;
    IOCTL_DAC_EXIT        	              fpDACExit;
    IOCTL_DAC_SET_IHALF_OUTPUT  		  fpDACSetIHalfOutput;
    IOCTL_DAC_SET_QUART_OUTPUT            fpDACSetQuartOutput;
    IOCTL_DAC_SET_DAC_STATE        	      fpDACSetDacState;
    IOCTL_DAC_HOTPLUG_DETECT              fpDACHotPlugDetect;
}DAC_INSTANT_PRIVATE;

APIDAC_Result MApi_DAC_GetLibVer_U2(const MSIF_Version **ppVersion);
const DAC_ApiInfo * MApi_DAC_GetInfo_U2(void);
MS_BOOL MApi_DAC_GetStatus_U2(DAC_ApiStatus *pDacStatus);
MS_BOOL MApi_DAC_SetDbgLevel_U2(MS_U16 u16DbgSwitch);
MS_BOOL MApi_DAC_Init_U2(void);
void MApi_DAC_Enable_U2(MS_BOOL bEnable, MS_BOOL bIsYPbPr);
void MApi_DAC_SetClkInv_U2(MS_BOOL bEnable, MS_BOOL bIsYPbPr);
void MApi_DAC_SetYPbPrOutputTiming_U2(E_OUTPUT_VIDEO_TIMING_TYPE eTiming);
void MApi_DAC_SetOutputSource_U2(E_DAC_OUTPUT_TYPE enOutputType, MS_BOOL bIsYPbPr);
void MApi_DAC_SetOutputLevel_U2(E_DAC_MAX_OUTPUT_LEVEL enLevel, MS_BOOL bIsYPbPr);
void MApi_DAC_SetOutputSwapSel_U2(E_DAC_SWAP_SEL enSwap,MS_BOOL bIsYPbPr);
void MApi_DAC_OnOffSD_U2(E_DAC_SD_ENABLE_CTRL enBit);
void MApi_DAC_OnOffHD_U2(E_DAC_HD_ENABLE_CTRL enBit);
void MApi_DAC_ClkSel_U2(E_OUTPUT_VIDEO_TIMING_TYPE eTiming, E_OUTPUT_BIT_TYPE ebits);
void MApi_DAC_DumpTable_U2(MS_U8 *pDACTable, MS_U8 u8DACtype);
void MApi_DAC_Exit_U2(void);
void MApi_DAC_SetIHalfOutput_U2(MS_BOOL bEnable, MS_BOOL bIsYPbPr);
void MApi_DAC_SetQuartOutput_U2(MS_BOOL bEnable,MS_BOOL bIsYPbPr);
void MApi_DAC_SetDacState_U2(MS_BOOL bEnabled, MS_BOOL bIsYPbPr);
MS_BOOL MApi_DAC_HotPlugDetect_U2(E_DAC_DETECT SelDAC,E_DAC_DETECT_TYPE DetectType, MS_BOOL *State);

void DACRegisterToUtopia(void);
MS_U32 DACOpen(void** ppInstance, const void* const pAttribute);
MS_U32 DACClose(void* pInstance);
MS_U32 DACIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);

#ifdef __cplusplus
}
#endif
#endif // _DRVBDMA_PRIV_H_
