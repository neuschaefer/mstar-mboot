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

///
/// @file   drvMPIF.h
/// @brief  MPIF Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_MPIF_H_
#define _DRV_MPIF_H_

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
#define MSIF_MPIF_TAG                          {'M','S','I','F'}    //Version ID header
#define MSIF_MPIF_CLASS                        {'1','0'}            //info Class code
#define MSIF_MPIF_CUS                          0x6666               //Customer ID
#define MSIF_MPIF_MOD                          0x0000               //Module ID
#define MSIF_MPIF_CHIP                         0x000F               //CHIP ID: T3
#define MSIF_MPIF_CPU                          '1'                  //CPU
#define MSIF_MPIF_LIB_CODE                     {'M','P','I','F'}    //Lib code
#define MSIF_MPIF_LIBVER                       {'0','2'}            //LIB version
#define MSIF_MPIF_BUILDNUM                     {'0','3'}            //Build Number
#define MSIF_MPIF_CHANGELIST                   {'0','0','5','6','7','4','8','0'} //P4 ChangeList Number
#define MSIF_MPIF_OS                           '0'                  //OS

#define     MPIF_DRV_VERSION                  /* Character String for DRV/API version             */  \
            MSIF_MPIF_TAG,                         /* 'MSIF'                                           */  \
            MSIF_MPIF_CLASS,                       /* '00'                                             */  \
            MSIF_MPIF_CUS,                         /* 0x0000                                           */  \
            MSIF_MPIF_MOD,                         /* 0x0000                                           */  \
            MSIF_MPIF_CHIP,                                                                              \
            MSIF_MPIF_CPU,                                                                               \
            MSIF_MPIF_LIB_CODE,                    /* IP__                                             */  \
            MSIF_MPIF_LIBVER,                      /* 0.0 ~ Z.Z                                        */  \
            MSIF_MPIF_BUILDNUM,                    /* 00 ~ 99                                          */  \
            MSIF_MPIF_CHANGELIST,                  /* CL#                                              */  \
            MSIF_MPIF_OS

#define MPIF_TR_CYCLE_0T								0
#define MPIF_TR_CYCLE_1T								1
#define MPIF_TR_CYCLE_2T								2
#define MPIF_TR_CYCLE_3T								3
#define MPIF_TR_CYCLE_4T								4
#define MPIF_TR_CYCLE_5T								5
#define MPIF_TR_CYCLE_6T								6
#define MPIF_TR_CYCLE_7T								7
#define MPIF_TR_CYCLE_1A2X_SEL							MPIF_TR_CYCLE_1T 
#define MPIF_TR_CYCLE_3X4A_SEL							MPIF_TR_CYCLE_1T 


#define MPIF_WAIT_CYCLE_0T								0
#define MPIF_WAIT_CYCLE_1T								1
#define MPIF_WAIT_CYCLE_2T								2
#define MPIF_WAIT_CYCLE_3T								3
#define MPIF_WAIT_CYCLE_SEL								MPIF_WAIT_CYCLE_1T

#define MPIF_SLAVE_DATAWIDTH_1bit						0
#define MPIF_SLAVE_DATAWIDTH_2bit						1
#define MPIF_SLAVE_DATAWIDTH_4bit						2
#define MPIF_SLAVE_DATAWIDTH_8bit						3
#define MPIF_SLAVE_DATAWIDTH_SEL						MPIF_SLAVE_DATAWIDTH_1bit

#define MPIF_CMD_DATAWIDTH_1bit							0
#define MPIF_CMD_DATAWIDTH_2bit							1
#define MPIF_CMD_DATAWIDTH_4bit							2
#define MPIF_CMD_DATAWIDTH_8bit							3
#define MPIF_CMD_DATAWIDTH_SEL							MPIF_CMD_DATAWIDTH_1bit

#define MPIF_LC1A_INDEX_0								0x00
#define MPIF_LC1A_INDEX_1								0x01
#define MPIF_LC1A_INDEX_2								0x02
#define MPIF_LC1A_INDEX_3								0x03
#define MPIF_LC1A_INDEX_4								0x04
#define MPIF_LC1A_INDEX_5								0x05
#define MPIF_LC1A_INDEX_6								0x06
#define MPIF_LC1A_INDEX_7								0x07

#define MPIF_2X_DEST_SPIF								0
#define MPIF_2X_DEST_XIU								1

#define MPIF_MAX_RTX_0									0x00    // 0 time
#define MPIF_MAX_RTX_1									0x01    // 1 times
#define MPIF_MAX_RTX_2									0x02    // 2 times
#define MPIF_MAX_RTX_3									0x03    // 3 times
#define MPIF_MAX_RTX_SEL								MPIF_MAX_RTX_0

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef struct _MPIF_CONFIG
{	
	MS_U8 u8trc_1A2X; //MPIF read/write turn around cycle for 1A/2X channel
	MS_U8 u8trc_3X4A; //MPIF read/write turn around cycle for 3X/4A channel
	MS_U8 u8wc; //MPIF wait ACK/NAK cycle
	MS_U8 u8Slave0Dw; //Slave 0 Data Width
	MS_U8 u8Slave1Dw; //Slave 1 Data Width
	MS_U8 u8Slave2Dw; //Slave 2 Data Width
	MS_U8 u8Slave3Dw; //Slave 3 Data Width
	MS_U8 u8CmdDw; //commend data width		
}MPIF_CONFIG;

typedef struct _MPIF_3XCTL
{
	MS_BOOL bChkSum;
	MS_U8 u8rtx;
	MS_BOOL bFastMode;
	MS_U8 u8wcnt;
}MPIF_3XCTL;

typedef struct _MPIF_DrvStatus
{
    MS_BOOL bIsBusy;
}MPIF_DrvStatus;

#ifdef MPIF_SPI_SUPPORT

typedef struct _MPIF_SPI_CONFIG
{    
	MS_U8 u8SerialMode;  //[0]: CPHA, [1]:CPOL
	MS_U8 u8LeadingCyc;
	MS_U8 u8TrailingCyc;
	MS_U8 u8CMDLen;
	MS_BOOL bSrcMIU;	
	MS_U8 u8MIUSel;
} MPIF_SPI_CONFIG;

#endif
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Description: Show the MPIF driver version
/// @param ppVersion  \b OUT  Library version string
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_GetLibVer(const MSIF_Version **ppVersion);

//------------------------------------------------------------------------------
/// Description: Get MPIF driver information
/// @return MPIF_CONFIG: mpif driver configuration informtion.
//------------------------------------------------------------------------------
const MPIF_CONFIG* MDrv_MPIF_GetInfo(void);

//------------------------------------------------------------------------------
/// Description: Show MPIF driver status
/// @param pStatus  \b OUT  pointer to store status data
//------------------------------------------------------------------------------
void MDrv_MPIF_GetStatus(MPIF_DrvStatus *pStatus);

//------------------------------------------------------------------------------
/// Set detailed level of MPIF driver debug message
/// @param u8DbgLevel  \b IN  debug level for MPIF driver
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SetDbgLevel(MS_U8 u8DbgLevel);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 1A read/write
/// @param bWite    	\b IN : If writing, set to TRUE; if reading, set to FALSE.
/// @param u8slaveid  	\b IN : Slave ID
/// @param u8index    	\b IN : index of 1A channel
/// @param pu8data    \b IN/OUT : pointer which stored wrriten/read data
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
void MDrv_MPIF_Init(MPIF_CONFIG* pcfg);

void MDrv_MPIF_Uninit(void);
//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 1A read/write
/// @param bWrite  	\b IN : If set to true, do writing; else do reading.
/// @param u8slaveid  	\b IN : Slave ID
/// @param u8index    	\b IN : index of 1A channel
/// @param pu8data    \b OUT : pointer which stored reading data or writing data
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC1A_RW(MS_U8 bWrite, MS_U8 u8slaveid, MS_U8 u8index, MS_U8 *pu8data);

//-------------------------------------------------------------------------------------------------
/// MPIF set 2X path to be SPIF or XIU
/// @param u8slaveid  	\b IN : Slave ID
/// @param u8path      \b IN : 2X path data
/// @return TRUE if successed or return FALSE if failed.
/// @note   Please always call this function before calling LC2X read/write function
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_Set_LC2XPath(MS_U8 u8slaveid, MS_U8 u8path);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 2A read/write
/// @param bWrite  		 \b IN : If set to TRUE, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param bchecksum    	 \b IN : If set to TRUE, do checksum enabled; else do checksum disabled.
/// @param u8rtx    	 	 \b IN : Re-transmit/receive count limit. 0~3 times.
/// @param u16addr   		 \b IN : Reading address
/// @param pu16data   	 \b OUT : Pointer to stored reading data. It's a visual address.
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC2A_RW(MS_U8 bWrite, MS_U8 u8slaveid, MS_BOOL bchecksum, MS_U8 u8rtx, MS_U16 u16addr, MS_U16* pu16data);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 2B read/write
/// @param bWrite  		 \b IN : If set to TRUE, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param bchecksum    	 \b IN : If set to TRUE, do checksum enabled; else do checksum disabled.
/// @param u8rtx    	 	 \b IN : Re-transmit/receive count limit. 0~3 times.
/// @param u16addr   		 \b IN : Reading address
/// @param pu16data   	 \b OUT : Pointer to stored reading data. It's a visual address.
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC2B_RW(MS_U8 bWrite, MS_U8 u8slaveid, MS_BOOL bchecksum, MS_U8 u8rtx, MS_U16 u16addr, MS_U16* pu16data);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 3A RIU mode ead/write
/// @param bWrite	    	 \b IN : If set to true, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u8datalen 		 \b IN : Data length. Unit by 16 bytes.
/// @param pu8data  		 \b IN/OUT : pointer to store writing/reading data. It's a visual address.
/// @param p3xctl  		 \b IN/OUT : pointer to store 3X control configure data
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC3A_RIURW(MS_BOOL bWrite, MS_U8 u8slaveid, MS_U8 u8datalen, MS_U8 *pu8data, MPIF_3XCTL *p3xctl);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 3B RIU mode read/write
/// @param bWrite	    	 \b IN : If set to true, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u8datalen 		 \b IN : Data length. Unit by 16 bytes.
/// @param pu8data  		 \b IN/OUT : pointer to store writing/reading data. It's a visual address.
/// @param p3xctl  		 \b IN/OUT : pointer to store 3X control configure data
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC3B_RIURW(MS_BOOL bWrite, MS_U8 u8slaveid, MS_U8 u8datalen, MS_U8 *pu8data, MPIF_3XCTL *p3xctl);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 3A MIU mode read/write
/// @param bWrite	    	 \b IN : If set to true, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u32datalen		 \b IN : Data length. Unit by 16 bytes.
/// @param u32miu_addr	 \b IN : MPIF MIU Start address. Unit is byte. Must be 8bytes aligmant.
/// @param u32spif_mdr	 \b IN : SPIF MIU Start address. Unit is byte. Must be 8bytes aligmant. 
/// @param p3xctl  		 \b IN/OUT : pointer to store 3X control configure data
/// @return TRUE if successed or return FALSE if failed.
/// @note   If using cache buffer, please do buffer flush first.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC3A_MIURW(MS_BOOL bWrite, MS_U8 u8slaveid, MS_U32 u32datalen, MS_PHYADDR u32miu_addr, MS_PHYADDR u32spif_mdr, MPIF_3XCTL *p3xcfg);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 3B MIU mode read/write
/// @param bWrite	    	 \b IN : If set to true, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u32datalen		 \b IN : Data length. Unit by 16 bytes.
/// @param u32miu_addr	 \b IN : MPIF MIU Start address. Unit is byte. Must be 8bytes aligmant.
/// @param u32spif_mdr	 \b IN : SPIF MIU Start address. Unit is byte. Must be 8bytes aligmant.
/// @param p3xctl  		 \b IN/OUT : pointer to store 3X control configure data
/// @return TRUE if successed or return FALSE if failed.
/// @note   If using cache buffer, please do buffer flush first.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC3B_MIURW(MS_BOOL bWrite, MS_U8 u8slaveid, MS_U32 u32datalen, MS_PHYADDR u32miu_addr, MS_PHYADDR u32spif_mdr, MPIF_3XCTL *p3xcfg);

//-------------------------------------------------------------------------------------------------
/// MPIF logical channel 3B MIU mode read/write
/// @param bWrite	    	 \b IN : If set to true, do writing; else do reading.
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u16datalen		 \b IN : Data length. Unit by 16 bytes.
/// @param u32miu_addr	 \b IN : MPIF MIU Start address. Unit is byte. Must be 8bytes aligmant.
/// @param u32spif_mdr	 \b IN : SPIF MIU Start address. Unit is byte. Must be 8bytes aligmant.
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_LC4A_MIURW(MS_BOOL bWrite, MS_U8 u8slaveid, MS_U16 u16datalen, MS_PHYADDR u32miu_addr, MS_PHYADDR u32spif_mdr);

//-------------------------------------------------------------------------------------------------
/// MPIF printf SPIF's configure information
/// @param u8slaveid    	 \b IN : Slave ID
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_Print_SPIFCfgInfo(MS_U8 u8slaveid);

//-------------------------------------------------------------------------------------------------
/// MPIF Set commend and slave data-width
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u8cmdwidth	 \b IN : Commend data width
/// @param u8datawidth	 \b IN : Slave data width
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SetCmdDataMode(MS_U8 u8slaveid, MS_U8 u8cmdwidth, MS_U8 u8datawidth);

//-------------------------------------------------------------------------------------------------
/// MPIF Set Clock
/// @param u8slaveid    			 \b IN : Slave ID
/// @param u8clk		    	 		 \b IN : Select MPIF clock
/// @param u8slaveClkInvDlyNum	 \b IN : Slave Delay buffer number. (0~15)
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_Set_Clock(MS_U8 u8slaveid, MS_U8 u8clk, MS_U8 u8slaveClkInvDlyNum);

//-------------------------------------------------------------------------------------------------
/// MPIF Clock Disable or Enable
/// @param bDisabled    			 \b IN : If true, enable MPIF clock; if false, disable MPIF clock 
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_Clock_Disable(MS_BOOL bDisabled);

//-------------------------------------------------------------------------------------------------
/// MPIF Set Slave Clock Invers delay
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u8DlyBufNum	 \b IN : Delay buffer number. (0~15)
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SetSlave_ClkInv_Delay(MS_U8 u8slaveid, MS_U8 u8DlyBufNum);

//-------------------------------------------------------------------------------------------------
/// MPIF Set Slave turn around cycle and wait ack cycle
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u8trc			 \b IN : Turn around cycle. (0T~3T)
/// @param u8wt			 \b IN : Wait ACK cycle. (0T~3T)
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SetSlave_Trc_Wt(MS_U8 u8slaveid, MS_U8 u8trc, MS_U8 u8wt);

//-------------------------------------------------------------------------------------------------
/// MPIF Set Slave Clock delay
/// @param u8slaveid    	 \b IN : Slave ID
/// @param u8DlyBufNum	 \b IN : Delay buffer number. (0~15)
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SetSlave_Clk_Delay(MS_U8 u8slaveid, MS_U8 u8DlyBufNum);

#ifdef MPIF_SPI_SUPPORT
//-------------------------------------------------------------------------------------------------
/// Configure MPIF SPI mode
/// @param u8slaveid    	 	\b IN : Slave ID
/// @param pcfg  				\b IN  pointer stored configure data
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
// struct MPIF_SPI_CONFIG must sync to HAL struct HAL_MPIF_SPI_CONFIG
MS_BOOL MDrv_MPIF_SPI_Configure(MS_U8 u8slaveid, MPIF_SPI_CONFIG* pcfg);

//-------------------------------------------------------------------------------------------------
/// Use SPI RIU mode to read flash ID
/// @param bWrite    	 		\b IN : If TRUE, it is write data mode, otherwise is read data mode
/// @param pu32cmd    	 	\b IN : pointer stored commend
/// @param u8cmdlen    	 	\b IN : commend length to write
/// @param pudata			\b IN/OUT : pointer to store write/read data
/// @param u16datalen    	 	\b IN : data length to write/read
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SPI_RIU_RWData(MS_BOOL bWrite, MS_U32 *pu32cmd, MS_U8 u8cmdlen, MS_U8 *pudata, MS_U16 u16datalen);


//-------------------------------------------------------------------------------------------------
/// Use SPI RIU mode to read flash ID
/// @param bWrite    	 		\b IN : If TRUE, it is write data mode, otherwise is read data mode
/// @param pu32cmd    	 	\b IN : pointer stored commend
/// @param u8cmdlen    	 	\b IN : commend length to write
/// @param u32MiuAddr		\b IN : MIU write/read base address
/// @param u16datalen    	 	\b IN : data length to write/read
/// @return TRUE if successed or return FALSE if failed.
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_MPIF_SPI_MIU_RWData(MS_BOOL bWrite, MS_U32 *pu32cmd, MS_U8 u8cmdlen, MS_PHYADDR u32MiuAddr, MS_U16 u16datalen);


#endif //MPIF_SPI_SUPPORT

#ifdef __cplusplus
}
#endif

#endif // _DRV_MPIF_H_
