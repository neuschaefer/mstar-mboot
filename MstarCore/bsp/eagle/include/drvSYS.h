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
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvSYS.h
/// @brief  System Control Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_SYS_H_
#define _DRV_SYS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
/// Version string.
    #define MSIF_SYS_LIB_CODE               {'S','Y','S','_'} //Lib code
    #define MSIF_SYS_LIBVER                 {'0','1'}      //LIB version
    #define MSIF_SYS_BUILDNUM               {'0','6' }    //Build Number
    #define MSIF_SYS_CHANGELIST             {'0','0','4','1','5','8','7','6'} //P4 ChangeList Number

#define SYS_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_SYS_LIB_CODE,                  /* IP__                                             */  \
    MSIF_SYS_LIBVER,                    /* 0.0 ~ Z.Z                                        */  \
    MSIF_SYS_BUILDNUM,                  /* 00 ~ 99                                          */  \
    MSIF_SYS_CHANGELIST,                /* CL#                                              */  \
    MSIF_OS

#define SYS_LIB_NAME_MAX            16      ///< Maximum length of library name
#define SYS_LIB_TIME_MAX            16      ///< Maximum length of time
#define SYS_LIB_DATE_MAX            16      ///< Maximum length of date
#define SYS_BOARD_MODEL_MAX         32      ///< Maximum length of board name
#define SYS_PLATFORM_CHIP_MAX       32      ///< Maximum length of playform name


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// System information
typedef struct _SYS_Info
{
    struct
    {
        MS_U16  DeviceId;                           ///< Device ID
        MS_U8   Version;                            ///< Version
        MS_U8   Revision;                           ///< Revision
        MS_U32  MIU1Base;                           ///< MIU1Base
        MS_U32  MIU1BusBase;                        ///< MIU1Base
    } Chip;                                         ///< Chip information

    struct
    {
        MS_U8   Time[SYS_LIB_TIME_MAX];             ///< Library Built Time
        MS_U8   Date[SYS_LIB_DATE_MAX];             ///< Library Built Date
    } SWLib;                                        ///< Software Library Information

} SYS_Info;


typedef struct _SYS_Status
{
    MS_BOOL     WDT_Active;                         ///< Watchdog Timer

} SYS_Status;

typedef enum _SYS_DbgLv
{
    E_SYS_DBGLV_NONE           //no debug message
    ,E_SYS_DBGLV_ERR_ONLY      //show error only
    ,E_SYS_DBGLV_REG_DUMP      //show error & reg dump
    ,E_SYS_DBGLV_INFO          //show error & informaiton
    ,E_SYS_DBGLV_ALL           //show error, information & funciton name
}SYS_DbgLv;

typedef enum
{
    E_SYS_QUERY_H264_SUPPORTED = 0x00,
    E_SYS_QUERY_DVBC_SUPPORTED = 0x10,
    E_SYS_QUERY_MM_SUPPORTED = 0x11,
} E_SYS_QUERY;

typedef enum
{
    E_SYS_ATV_AGC_PAD_SET,
    E_SYS_DTV_AGC_PAD_SET,
    E_SYS_DTV_AGC_PAD_SET_ALL_OFF,
}SYS_AGC_PAD_SET;

typedef enum
{
    E_TS0_PAD_SET,
    E_TS1_PAD_SET,
    E_TS2_PAD_SET,
    E_PAD_SET_MAX
}SYS_PAD_MUX_SET;

typedef enum
{
    E_PARALLEL_IN,
    E_SERIAL_IN,
    E_PARALLEL_IN_2nd_PORT,
    E_PARALLEL_OUT,
    E_PAD_SEL_MAX
}SYS_PAD_SEL;

typedef enum
{
    E_PCM_CD_SINGLE,
    E_PCM_CD_OR,
    E_PCM_CD_MAX
}SYS_PCM_CD_MODE;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL         MDrv_SYS_Init(void);
const SYS_Info* MDrv_SYS_GetInfo(void);
MS_U8           MDrv_SYS_GetChipRev(void);
MS_U16          MDrv_SYS_GetChipID(void);
void            MDrv_SYS_WDTEnable(MS_BOOL bEnable);
void            MDrv_SYS_WDTClear(void);
MS_BOOL         MDrv_SYS_WDTLastStatus(void);
void            MDrv_SYS_WDTSetTime(MS_U32 u32Ms);
void            MDrv_SYS_ResetChip(void);
void            MDrv_SYS_ResetCPU(void);
void            MDrv_SYS_SetDbgLevel(SYS_DbgLv eLevel);
void            MDrv_SYS_FlushMemory(void);
void            MDrv_SYS_ReadMemory(void);
void            MDrv_SYS_VIFWriteByteByVDMbox(MS_U32 u32Reg, MS_U8 u8Val);
void            MDrv_SYS_VIFWriteByteMaskByVDMbox(MS_U32 u32Reg, MS_U8 u8Val, MS_U8 u8Mask);
void            MDrv_SYS_VIFWriteRegBitByVDMbox(MS_U32 u32Reg, MS_U8 bEnable, MS_U8 u8Mask);
MS_U8           MDrv_SYS_VIFReadByteByVDMbox(MS_U32 u32Reg);
MS_U16          MDrv_SYS_VIFRead2ByteByVDMbox(MS_U32 u32Reg);

MS_BOOL         MDrv_SYS_Query(E_SYS_QUERY id);

#ifdef _SYS_DAC_GAIN_CTRL_
void MDrv_SYS_EnhanceDACGain(MS_U8 u8DAC_ID, MS_BOOL bEnable);
#endif

void            MDrv_SYS_GetSoftwareVersion(MS_SW_VERSION_INFO *pSoftwareVersionInfo);
void            MDrv_SYS_SetAGCPadMux(SYS_AGC_PAD_SET eAgcPadMux);
MS_BOOL         MDrv_SYS_SetPadMux(SYS_PAD_MUX_SET ePadMuxType,SYS_PAD_SEL ePadSel);
MS_BOOL         MDrv_SYS_SetPCMCardDetectMode(SYS_PCM_CD_MODE ePCMCDMode);
MS_BOOL         MDrv_SYS_DisableDebugPort(void);
MS_BOOL         MDrv_SYS_EnableDebugPort(void);
MS_BOOL         MDrv_SYS_SetTSOutClockPhase(MS_U16 u16Val);

#ifdef __cplusplus
}
#endif


#endif // _DRV_SYS_H_

