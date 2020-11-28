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

#ifndef _API_SWI2C_H_
#define _API_SWI2C_H_

#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// define IR library version
#define MSIF_SWI2C_LIB_CODE             {'S','I','2','C'}
#define MSIF_SWI2C_LIBVER               {'0','5'}
#define MSIF_SWI2C_BUILDNUM             {'0','5' }
#define MSIF_SWI2C_CHANGELIST           {'0','0','4','9','7','5','7','8'}

#define SWI2C_API_VERSION                 /* Character String for DRV/API version */  \
      MSIF_TAG,                           /* 'MSIF' */  \
      MSIF_CLASS,                         /* '00' */  \
      MSIF_CUS,                           /* 0x0000 */  \
      MSIF_MOD,                           /* 0x0000 */  \
      MSIF_CHIP,                                       \
      MSIF_CPU,                                        \
      MSIF_SWI2C_LIB_CODE,                /* IP__ */  \
      MSIF_SWI2C_LIBVER,                  /* 0.0 ~ Z.Z */  \
      MSIF_SWI2C_BUILDNUM,                /* 00 ~ 99 */  \
      MSIF_SWI2C_CHANGELIST,              /* CL# */  \
      MSIF_OS

// Speed Mapping: Base on the Driver loading, maybe you must to use the oscilloscope to measure this Value
// Speed Mapping has been refined, and you can specify the IIC speed X (KHz) driectly by X.
#define SWI2C_SPEED_MAPPING_400K          400
#define SWI2C_SPEED_MAPPING_350K          350
#define SWI2C_SPEED_MAPPING_300K          300
#define SWI2C_SPEED_MAPPING_250K          250
#define SWI2C_SPEED_MAPPING_200K          200
#define SWI2C_SPEED_MAPPING_150K          150
#define SWI2C_SPEED_MAPPING_100K          100
#define SWI2C_SPEED_MAPPING_50K           50

/// emurate SWI2C fucntion return result
typedef enum
{
    /// SWI2C result for failure
    E_SWI2C_FAIL =0,
    /// SWI2C result for OK
    E_SWI2C_OK = 1,

} SWI2C_Result;

///Define SWI2C Bus Configuration
typedef struct
{
    MS_U16 padSCL;
    MS_U16 padSDA;
    MS_U16 defDelay;
} SWI2C_BusCfg;

///Define SWI2C read mode
typedef enum {
    E_SWI2C_READ_MODE_DIRECT,                 ///< first transmit slave address + reg address and then start receive the data */
    E_SWI2C_READ_MODE_DIRECTION_CHANGE,       ///< slave address + reg address in write mode, direction change to read mode, repeat start slave address in read mode, data from device
    E_SWI2C_READ_MODE_DIRECTION_CHANGE_STOP_START,  ///< slave address + reg address in write mode + stop, direction change to read mode, repeat start slave address in read mode, data from device
    E_SWI2C_READ_MODE_MAX
} SWI2C_ReadMode;

///Define SWI2C debug level
typedef enum _SWI2C_DbgLvl
{
    E_SWI2C_DBGLVL_NONE = 0,      /// no debug message
    E_SWI2C_DBGLVL_WARNING,       /// show warning only
    E_SWI2C_DBGLVL_ERROR,         /// show error only
    E_SWI2C_DBGLVL_INFO,          /// show error & informaiton
    E_SWI2C_DBGLVL_ALL,           /// show error, information & funciton name
}SWI2C_DbgLvl;

void MApi_SWI2C_Init(SWI2C_BusCfg SWI2CBusCfg[],MS_U8 u8CfgBusNum);
MS_BOOL MApi_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL MApi_SWI2C_WriteBytesStop(MS_U16 u16BusNumSlaveID, MS_U8 AddrCnt, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pBuf,MS_BOOL bGenStop);
MS_BOOL MApi_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
MS_BOOL MApi_SWI2C_ReadBytes_ThruMode(MS_U16 u16BusNumSlaveID, MS_U8 ucSubAdr, MS_U8* paddr, MS_U16 ucBufLen, MS_U8* pBuf);
MS_BOOL MApi_SWI2C_ReadByte(MS_U16 u16BusNumSlaveID, MS_U8 u8RegAddr, MS_U8 *pu8Data);
MS_BOOL MApi_SWI2C_WriteByte(MS_U16 u16BusNumSlaveID, MS_U8 u8RegAddr, MS_U8 u8Data);
MS_BOOL MApi_SWI2C_Write2Bytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addr, MS_U16 u16data);
MS_U16 MApi_SWI2C_Read2Bytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addr);
MS_BOOL MApi_SWI2C_Write4Bytes(MS_U16 u16BusNumSlaveID, MS_U32 u32Data, MS_U8 u8EndData);
MS_BOOL MApi_SWI2C_ReadByteDirectly(MS_U16 u16BusNumSlaveID, MS_U8 * pu8Data);
MS_BOOL MApi_SWI2C_WriteGroupBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8SubGroup, MS_U16 u16Addr, MS_U16 u16Data);
MS_U16 MApi_SWI2C_ReadGroupBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8SubGroup, MS_U16 u16Addr);
MS_U8 MApi_SWI2C_GetMaxBuses(void);
MS_U32 MApi_SWI2C_Speed_Setting(MS_U8 u8BusNum, MS_U32 u32Speed_K);
MS_BOOL MApi_SWI2C_SetReadMode(SWI2C_ReadMode eReadMode);
MS_BOOL MApi_SWI2C_SetBusReadMode(MS_U8 u8BusNum, SWI2C_ReadMode eReadMode);
MS_BOOL MApi_SWI2C_GetLibVer(const MSIF_Version **ppVersion);
SWI2C_Result MApi_SWI2C_SetDbgLevel(SWI2C_DbgLvl eLevel);
MS_U16 MApi_SWI2C_SetPowerState(EN_POWER_MODE u16PowerState);

/******************************************************************************/
///
/// The following API functions are packed for special usage in ISP programming
///
/******************************************************************************/
void MApi_SWI2C_MutexLock(void);
void MApi_SWI2C_MutexUnlock(void);
void MApi_SWI2C_UseBus( MS_U8 u8BusChn );
void MApi_SWI2C_UnuseBus(void);
MS_BOOL MApi_SWI2C_AccessStart(MS_U8 u8SlaveID, MS_U8 trans_t);
void MApi_SWI2C_Stop(void);
MS_BOOL MApi_SWI2C_Start(void);
MS_BOOL MApi_SWI2C_SendByte(MS_U8 u8date);
MS_U8 MApi_SWI2C_GetByte(MS_U16 u16Ack);

#ifdef __cplusplus
}
#endif

#endif // _API_SWI2C_H_
