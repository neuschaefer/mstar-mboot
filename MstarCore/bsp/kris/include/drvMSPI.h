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
/// @file   drvMSPI.h
/// @brief  Master SPI Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MSPI_H_
#define _DRV_MSPI_H_
#include "MsCommon.h"


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
#define MSPI_UTOPIA20                  (0)
#define MSPI_READ_OPERATION    0
#define MSPI_WRITE_OPERATION   1
#define MSPI_CMD_TYPE          3

// config bit map
#define MSPI_DC_CONFIG        1
#define MSPI_CLK_CONFIG       2
#define MSPI_FRAME_CONFIG     4

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef struct
{
    MS_U8 u8TrStart;      //time from trigger to first SPI clock
    MS_U8 u8TrEnd;        //time from last SPI clock to transferred done
    MS_U8 u8TB;           //time between byte to byte transfer
    MS_U8 u8TRW;          //time between last write and first read
} MSPI_DCConfig;

typedef struct
{
    MS_U8 u8WBitConfig[7];      //bits will be transferred in write buffer
    MS_U8 u8RBitConfig[7];      //bits Will be transferred in read buffer
} MSPI_FrameConfig;


typedef struct
{
	MS_U8 U8Clock;
	MS_BOOL BClkPolarity;
	MS_BOOL BClkPhase;
    MS_U32 u32MAXClk;
} MSPI_CLKConfig;

typedef struct
{
	MSPI_DCConfig  tMSPI_DCConfig[MSPI_CMD_TYPE];
	MSPI_FrameConfig  tMSPI_FrameConfig[MSPI_CMD_TYPE];
	MSPI_CLKConfig tMSPI_ClockConfig[MSPI_CMD_TYPE]; 
	MS_U8 U8ChipSel;
	MS_BOOL BLsbFirst;
	void (*MSPIIntHandler)(void); // interrupt handler
	MS_BOOL BIntEnable;   // interrupt mode enable or polling mode
	MS_U8 U8BitMapofConfig[MSPI_CMD_TYPE];
    MS_U32 u32DevId;
} MSPI_config;

typedef struct
{
    MS_U16 PadCs;
}stMSPI_csPdCfg;
typedef enum _MSPI_ERRORNOn
{
     E_MSPI_OK = 0
    ,E_MSPI_INIT_FLOW_ERROR =1
    ,E_MSPI_DCCONFIG_ERROR =2
    ,E_MSPI_CLKCONFIG_ERROR =4
    ,E_MSPI_FRAMECONFIG_ERROR =8
    ,E_MSPI_OPERATION_ERROR = 0x10
    ,E_MSPI_PARAM_OVERFLOW = 0x20
    ,E_MSPI_MMIO_ERROR = 0x40
    ,E_MSPI_HW_NOT_SUPPORT = 0x80
    ,E_MSPI_NULL
}MSPI_ErrorNo;

typedef enum
{
    E_MSPI_DBGLV_NONE,    //disable all the debug message
    E_MSPI_DBGLV_INFO,    //information
    E_MSPI_DBGLV_NOTICE,  //normal but significant condition
    E_MSPI_DBGLV_WARNING, //warning conditions
    E_MSPI_DBGLV_ERR,     //error conditions
    E_MSPI_DBGLV_CRIT,    //critical conditions
    E_MSPI_DBGLV_ALERT,   //action must be taken immediately
    E_MSPI_DBGLV_EMERG,   //system is unusable
    E_MSPI_DBGLV_DEBUG,   //debug-level messages
} MSPI_DbgLv;

////////////////////////////////////////////////////////////////////////////////
// include utopia v2  header files here
////////////////////////////////////////////////////////////////////////////////
#include "drvMSPI_v2.h"

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Description : MSPI initial EXt
/// @return E_MSPI_OK : 
/// @return >1 : failed to initial 
//------------------------------------------------------------------------------ 
MSPI_ErrorNo MDrv_MSPI_Init_Ext(MS_U8 u8HWNum);

//------------------------------------------------------------------------------
/// Description : MSPI initial
/// @return E_MSPI_OK : 
/// @return >1 : failed to initial 
//------------------------------------------------------------------------------ 
MSPI_ErrorNo MDrv_MSPI_Init(MSPI_config *tMSPIConfig, MS_U8 u8HWNum);

//-------------------------------------------------------------------------------------------------
/// Description : read data from MSPI
/// @param pData \b IN :pointer to receive data from MSPI read buffer 
/// @param u16Size \ b OTU : read data size
/// @return the errorno of operation
//-------------------------------------------------------------------------------------------------
MSPI_ErrorNo MDrv_MSPI_Read(MS_U8 *pData, MS_U16 u16Size);

//------------------------------------------------------------------------------
/// Description : read data from MSPI
/// @param pData \b OUT :pointer to write  data to MSPI write buffer 
/// @param u16Size \ b OTU : write data size
/// @return the errorno of operation
//------------------------------------------------------------------------------
MSPI_ErrorNo MDrv_MSPI_Write(MS_U8 *pData, MS_U16 u16Size);

//------------------------------------------------------------------------------
/// Description : config spi transfer timing
/// @param ptDCConfig    \b OUT  struct pointer of transfer timing config
/// @return E_MSPI_OK : succeed
/// @return E_MSPI_DCCONFIG_ERROR : failed to config transfer timing
//------------------------------------------------------------------------------
MSPI_ErrorNo MDrv_MSPI_DCConfig(MSPI_DCConfig *ptDCConfig);

//------------------------------------------------------------------------------
/// Description : config spi clock setting
/// @param ptCLKConfig    \b OUT  struct pointer of clock config
/// @return E_MSPI_OK : succeed
/// @return E_MSPI_CLKCONFIG_ERROR : failed to config spi clock
//------------------------------------------------------------------------------
MSPI_ErrorNo MDrv_MSPI_CLKConfig(MSPI_CLKConfig *ptCLKConfig);


//------------------------------------------------------------------------------
/// Description : config spi transfer timing
/// @param ptDCConfig    \b OUT  struct pointer of bits of buffer tranferred to slave config
/// @return E_MSPI_OK : succeed
/// @return E_MSPI_FRAMECONFIG_ERROR : failed to config transfered bit per buffer
//------------------------------------------------------------------------------
MSPI_ErrorNo MDrv_MSPI_FRAMEConfig(MSPI_FrameConfig *ptFrameConfig);

//------------------------------------------------------------------------------
/// Description : Enable Slave device
//------------------------------------------------------------------------------
void MDrv_MSPI_SlaveEnable(MS_BOOL Enable);

//------------------------------------------------------------------------------
/// Description : 
/// @return TRUE : chip support 
/// @return FALSE: 
//------------------------------------------------------------------------------
MS_BOOL MDrv_MSPI_HW_Support(void);

MS_U32 MDrv_MSPI_SetPowerState(EN_POWER_MODE enPowerState);
  
MS_BOOL MDrv_MSPI_SetDbgLevel(MS_U8 u8DbgLevel);

//==================================================================
//         Master SPI API with slave device id to support multiple slave device 
//==================================================================
MSPI_ErrorNo MDrv_MasterSPI_Init(MSPI_config *tMSPIConfig, MS_U8 u8HWNum);

MSPI_ErrorNo MDrv_MasterSPI_Read(MS_U32 u32DevID, MS_U8 *pData, MS_U16 u16Size);

MSPI_ErrorNo MDrv_MasterSPI_Write(MS_U32 u32DevID, MS_U8 *pData, MS_U16 u16Size);

MSPI_ErrorNo MDrv_MasterSPI_DCConfig(MS_U32 u32DevID, MSPI_DCConfig *ptDCConfig);

MSPI_ErrorNo MDrv_MasterSPI_CLKConfig(MS_U32 u32DevID, MSPI_CLKConfig *ptCLKConfig);

MSPI_ErrorNo MDrv_MasterSPI_FRAMEConfig(MS_U32 u32DevID, MSPI_FrameConfig *ptFrameConfig);

MSPI_ErrorNo MDrv_MasterSPI_SlaveEnable(MS_U32 u32DevID, MS_BOOL Enable);

MS_BOOL MDrv_MasterSPI_CsPadConfig(MS_U32 u32DevID, MS_U32 u32CsPad);

MS_BOOL MDrv_MasterSPI_MaxClkConfig(MS_U32 u32DevID, MS_U32 u32MaxClk);

#ifdef __cplusplus
}
#endif

#endif // _DRV_MSPI_H_

