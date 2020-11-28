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
