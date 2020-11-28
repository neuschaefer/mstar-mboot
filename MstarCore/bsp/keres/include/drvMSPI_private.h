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

#ifndef _DRVMSPI_PRIV_H_
#define _DRVMSPI_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvMSPI_private.h
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

#include "MsTypes.h"
#include "drvMSPI.h"


typedef MSPI_ErrorNo (*IOCTL_MSPI_Init_Ext)(MS_U8);
typedef MSPI_ErrorNo (*IOCTL_MSPI_Init)(MSPI_config*, MS_U8);
typedef MSPI_ErrorNo (*IOCTL_MSPI_Read)(MS_U8*, MS_U16);
typedef MSPI_ErrorNo (*IOCTL_MSPI_Write)(MS_U8*, MS_U16);
typedef MSPI_ErrorNo (*IOCTL_MSPI_DCConfig)(MSPI_DCConfig*);
typedef MSPI_ErrorNo (*IOCTL_MSPI_CLKConfig)(MSPI_CLKConfig*);
typedef MSPI_ErrorNo (*IOCTL_MSPI_FRAMEConfig)(MSPI_FrameConfig*);
typedef void (*IOCTL_MSPI_SlaveEnable)(MS_BOOL);
typedef MS_U32 (*IOCTL_MSPI_SetPowerState)(EN_POWER_MODE); 
typedef MS_BOOL (*IOCTL_MSPI_SetDbgLevel)(MS_U8);
//==============================================================================
//   NEW API for MSPI
//===============================================================================
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_Init)(MSPI_config*, MS_U8);
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_Read)(MS_U32, MS_U8*, MS_U16);
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_Write)(MS_U32, MS_U8*, MS_U16);
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_DCConfig)(MS_U32, MSPI_DCConfig*);
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_CLKConfig)(MS_U32, MSPI_CLKConfig*);
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_FRAMEConfig)(MS_U32, MSPI_FrameConfig*);
typedef MSPI_ErrorNo (*IOCTL_MasterSPI_SlaveEnable)(MS_U32, MS_BOOL);
typedef MS_BOOL (*IOCTL_MasterSPI_CSPadConfig)(MS_U32, MS_U32);
typedef MS_BOOL (*IOCTL_MasterSPI_MaxClkConfig)(MS_U32, MS_U32);

typedef struct _MSPI_RESOURCE_PRIVATE
{
    MS_U32 Dummy;
}MSPI_RESOURCE_PRIVATE;

typedef struct _MSPI_INSTANT_PRIVATE
{
    IOCTL_MSPI_Init_Ext                                 fpMSPI_Init_Ext;
    IOCTL_MSPI_Init                                     fpMSPI_Init;
    IOCTL_MSPI_Read                                     fpMSPI_Read;
    IOCTL_MSPI_Write                                    fpMSPI_Write;
    IOCTL_MSPI_DCConfig                                 fpMSPI_DCConfig;
    IOCTL_MSPI_CLKConfig                                fpMSPI_CLKConfig;
    IOCTL_MSPI_FRAMEConfig                              fpMSPI_FRAMEConfig;
    IOCTL_MSPI_SlaveEnable                              fpMSPI_SlaveEnable;
    IOCTL_MSPI_SetPowerState                            fpMSPI_SetPowerState; 
    IOCTL_MSPI_SetDbgLevel                              fpMSPI_SetDbgLevel;
    IOCTL_MasterSPI_Init                                fpMasterSPI_Init;
    IOCTL_MasterSPI_Read                                fpMasterSPI_Read;
    IOCTL_MasterSPI_Write                               fpMasterSPI_Write;
    IOCTL_MasterSPI_DCConfig                            fpMasterSPI_DCConfig;
    IOCTL_MasterSPI_CLKConfig                           fpMasterSPI_CLKConfig;
    IOCTL_MasterSPI_FRAMEConfig                         fpMasterSPI_FrameConfig;
    IOCTL_MasterSPI_SlaveEnable                         fpMasterSPI_SlaveEnable;
    IOCTL_MasterSPI_CSPadConfig                         fpMasterSPI_CsPadConfig;
    IOCTL_MasterSPI_MaxClkConfig                        fpMasterSPI_MaxClkConfig;
}MSPI_INSTANT_PRIVATE;

void MSPIRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 MSPIOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 MSPIClose(void* pInstance);
MS_U32 MSPIIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);
#if (MSPI_UTOPIA20)
//------------------------------------------------------------------------------
/// Description : Set detailed level of Parallel Flash driver debug message
/// @param u8DbgLevel    \b IN  debug level for Serial Flash driver
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//------------------------------------------------------------------------------
MS_BOOL _MDrv_MSPI_SetDbgLevel(MS_U8 u8DbgLevel);

//------------------------------------------------------------------------------
/// Description : MSPI Init
/// @param u8HwNum
/// @return TRUE : succeed
/// @return FALSE : failed to set the WP pin info
//------------------------------------------------------------------------------
MSPI_ErrorNo  _MDrv_MSPI_Init_Ext(MS_U8 u8HWNum);

//------------------------------------------------------------------------------
/// Description : MSPI read data
/// @param pData
/// @param u16Size
/// @return TRUE : succeed
/// @return NULL :
//------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MSPI_Read(MS_U8 *pData, MS_U16 u16Size);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI write data
/// @param pData
/// @param u16Size
/// @return TRUE : succeed
/// @return FALSE : unknown flash type
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MSPI_Write(MS_U8 *pData, MS_U16 u16Size);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI timing config
/// @param  ptDCConfig \b IN: config MSPI timing
/// @return TRUE : succeed
/// @return FALSE : unknown flash size
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MSPI_DCConfig(MSPI_DCConfig *ptDCConfig);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI clock config
/// @param  ptCLKConfig    \b IN: clock config
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   Please ref. sprc. to confirm Flash support or not
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MSPI_CLKConfig(MSPI_CLKConfig *ptCLKConfig);

//-------------------------------------------------------------------------------------------------
/// Description : Config MSPI frame size
/// @param  ptFrameConfig
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   Please ref. sprc. to confirm Flash support or not. It is safty to run at 43M (Default).
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MSPI_FRAMEConfig(MSPI_FrameConfig *ptFrameConfig);
//-------------------------------------------------------------------------------------------------
/// Description : set CS of MSPI
/// @param  bEnable  \b IN: set CS HIGH/LOW
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note
//-------------------------------------------------------------------------------------------------
void _MDrv_MSPI_SlaveEnable(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI power state
/// @param  enPowerState \b IN: power state of MSPI
/// @return TRUE : succeed
/// @return FALSE : not succeed
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_MSPI_SetPowerState(EN_POWER_MODE enPowerState); 

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI debug message level
/// @param  u8DbgLevel /b IN: debug message level
/// @return TRUE : succeed
/// @return FALSE : illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_MSPI_SetDbgLevel(MS_U8 u8DbgLevevl);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI Init
/// @param  ptMSPIConfig \b IN: slave device config of mspi
/// @param  u8HWNum      \b IN: mspi ip number
/// @return error numbero of driver E_MSPI_OK : success \others fail
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_Init(MSPI_config *ptMSPIConfig, MS_U8 u8HWNum);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI READ DATA
/// @param  u32DevID    \b IN: device id of slave device
/// @param  *pu8Data      \b IN: pointer of buffer to get data
/// @param  u16Size     \b IN: size of read data
/// @return E_MSPI_OK : succeed
/// @return others: fail 
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_Read(MS_U32 u32DevID, MS_U8 *pu8Data, MS_U16 u16Size);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI write data
/// @param  u32DevID    \b IN: device id of slave device
/// @param  *pu8Data    \b IN: pointer of buffer to send data
/// @param  u16Size     \b IN: size of write data
/// @return E_MSPI_OK : succeed
/// @return others : fail
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_Write(MS_U32 u32DevID, MS_U8 *pu8Data, MS_U16 u16Size);

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI timming
/// @param  u32DevID      \b IN: device id of slave device
/// @param  ptDCConfig    \b IN: poniter of struct config slave timming
/// @return E_MSPI_OK : succeed
/// @return others: fail 
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_DCConfig(MS_U32 u32DevID, MSPI_DCConfig *ptDCConfig);

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI clock
/// @param u32DevID    \b IN: device id of slave device
/// @param ptCLKConfig \b IN: pointer of struct to config mspi clock
/// @return E_MSPI_OK : success 
/// @return others : fail
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_CLKConfig(MS_U32 u32DevID, MSPI_CLKConfig *ptCLKConfig);

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI fram size
/// @param  u32DevID         \b IN: device id of slave device
/// @param  ptFrameConfig    \b IN: pointer of frame size 
/// @return E_MSPI_OK : succeed
/// @return others: fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_FRAMEConfig(MS_U32 u32DevID, MSPI_FrameConfig *ptFrameConfig);

//-------------------------------------------------------------------------------------------------
/// Description : MSPI slave enable/disable
/// @param  u32DevID    \b IN: device id of slave id
/// @param  bEnable     \b IN: set CS high /low to enable /disable slave device
/// @return NONE
/// @note   Not allowed in interrupt context
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo _MDrv_MasterSPI_SlaveEnable(MS_U32 u32DevID, MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI CS PAD number
/// @param u32DevID \b IN: slave device id of slave device
/// @param u32CsPad \b IN: pad number of cs pin
/// @return TRUE : succeed
/// @return FALSE : fail
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_MasterSPI_CsPadConfig(MS_U32 u32DevID, MS_U32 u32CsPad);

//-------------------------------------------------------------------------------------------------
/// Description : Set MSPI Slave Device Support Max Clock
/// @param u32DevID  \b IN: slave device id of slave device
/// @param u32MaxCLk \b IN: max clock of slave device support
/// @return TRUE : succeed
/// @return FALSE : fail
/// @note   Not allowed in interrupt contextb//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_MasterSPI_MaxClkConfig(MS_U32 u32DevID, MS_U32 u32MaxClk);

#endif

#ifdef __cplusplus
}
#endif
#endif // _DRVBDMA_PRIV_H_
