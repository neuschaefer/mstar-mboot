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
// ********************************************************
//
//  $Workfile: PCMCIA.h $
//
//   Author/Copyright    Gero Kuehn / GkWare e.K.
//                        Humboldtstrasse 177
//                        45149 Essen
//                        GERMANY
//                        Tel: +49 174 520 8026
//                        Email: support@gkware.com
//                        Web: http://www.gkware.com
//
//    $Date:  $
//    $Revision:  $
//
// ********************************************************
//
// @file PCMCIA.h
// @brief This file contains the API of the PCMCIA CIS parser and the declaration
// for the PCMCIA driver API. PCMCIA drivers are expected to implement the functions starting with PCMCIA_ except for MDrv_PCMCIA_ReadAttribMem(),
// The MDrv_PCMCIA_ReadAttribMem() implementation is provided together with the GkWare CI Stack

///////////////////////////////////////////////////////////////////////////////
///
/// @file   drvPCMCIA.h
/// @brief  PCMCIA Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_PCMCIA_H_
#define _DRV_PCMCIA_H_

#include "MsTypes.h"
//-----------------------------------------------------------------------------
//  Macro and Define
//-----------------------------------------------------------------------------
// PCMCIA
#define MAX_PCMCIA_CONFIGS              6       //!< The maximum number of configurations supported by a PCMCIA card
#define MAX_PCMCIA_STRLEN               (64)    //!< The maximum name of vendor/manufacturer/info strings
#define MAX_CIS_SIZE                    0x100   //!< The maximum size of a CIS, that is understood by this driver
#define PCMCIA_HW_TIMEOUT               3000
#define PCMCIA_IRQ_ENABLE               1

// IRQ_force status bits
#define PCMCIA_MEM_READY                (0x04)  //The same pin as IRQ in I/O mode

// Command Interface Hardware Registers
#define PCMCIA_PHYS_REG_DATA            (0)
#define PCMCIA_PHYS_REG_COMMANDSTATUS   (1)
#define PCMCIA_PHYS_REG_SIZELOW         (2)
#define PCMCIA_PHYS_REG_SIZEHIGH        (3)

// Status Register Bits
#define PCMCIA_STATUS_DATAAVAILABLE     (0x80)  //!< PCMCIA Status Register Bit - The module wants to send data
#define PCMCIA_STATUS_FREE              (0x40)  //!< PCMCIA Status Register Bit - The module can accept data
#define PCMCIA_STATUS_IIR               (0x10)  //!< PCMCIA Status Register Bit - IIR
#define PCMCIA_STATUS_RESERVEDBITS      (0x2C)  //!< PCMCIA Status Register Bits - reserved
#define PCMCIA_STATUS_WRITEERROR        (0x02)  //!< PCMCIA Status Register Bit - Write error
#define PCMCIA_STATUS_READERROR         (0x01)  //!< PCMCIA Status Register Bit - Read error

// Command Register Bits
#define PCMCIA_COMMAND_DAIE             (0x80)  //!< PCMCIA Command register bit - DAIE
                                                // when this bit is set, the module asserts IREQ# each time it has data to send
#define PCMCIA_COMMAND_FRIE             (0x40)  //!< PCMCIA Command register bit - FRIE
                                                // when this bit is set, the module asserts IREQ# each time it is free to receive data
#define PCMCIA_COMMAND_RESERVEDBITS     (0x30)  //!< PCMCIA Command register bits - reserved
#define PCMCIA_COMMAND_RESET            (0x08)  //!< PCMCIA Command register bit - Reset
#define PCMCIA_COMMAND_SIZEREAD         (0x04)  //!< PCMCIA Command register bit - Size read
#define PCMCIA_COMMAND_SIZEWRITE        (0x02)  //!< PCMCIA Command register bit - Size Write
#define PCMCIA_COMMAND_HOSTCONTROL      (0x01)  //!< PCMCIA Command register bit - Host control

#define PCMCIAINFO_MANID_VALID          (0x00000001)
#define PCMCIAINFO_VERS1_VALID          (0x00000002)
#define PCMCIAINFO_FUNCID_VALID         (0x00000004)

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// Constant & Macro Definition
////////////////////////////////////////////////////////////////////////////////
/// Version string.
#define MSIF_PCMCIA_LIB_CODE            {'P','C','M','_'}  //Lib code
#define MSIF_PCMCIA_LIBVER              {'0','1'}          //LIB version
#define MSIF_PCMCIA_BUILDNUM            {'0','1'}          //Build Number
#define MSIF_PCMCIA_CHANGELIST          {'0','0','2','5','8','4','9','3'} //P4 ChangeList Number

#define PCMCIA_DRV_VERSION  /* Character String for DRV/API version */  \
    MSIF_TAG,               /* 'MSIF' */                                \
    MSIF_CLASS,             /* '00'  */                                 \
    MSIF_CUS,               /* 0x0000 */                                \
    MSIF_MOD,               /* 0x0000 */                                \
    MSIF_CHIP,                                                          \
    MSIF_CPU,                                                           \
    MSIF_PCMCIA_LIB_CODE,   /* IP */                                    \
    MSIF_PCMCIA_LIBVER,     /* 00 ~ 99 */                               \
    MSIF_PCMCIA_BUILDNUM,   /* 00 ~ 99 */                               \
    MSIF_PCMCIA_CHANGELIST, /* CL# */                                   \
    MSIF_OS

typedef void (*IsrCallback)( void* wparam, void* lparam );

//-----------------------------------------------------------------------------
//  Enums
//-----------------------------------------------------------------------------
//! This enum contains the card types, that can be encoded in CISTPL_FUNCID (0x21)
typedef enum {
    E_PCMCIA_FUNC_CUSTOM        = 0,
    E_PCMCIA_FUNC_MEMORY        = 1,
    E_PCMCIA_FUNC_SERIAL        = 2,
    E_PCMCIA_FUNC_PARALLEL      = 3,
    E_PCMCIA_FUNC_DRIVE         = 4,
    E_PCMCIA_FUNC_VIDEO         = 5,
    E_PCMCIA_FUNC_NETWORK       = 6,
    E_PCMCIA_FUNC_AIMS          = 7,
    E_PCMCIA_FUNC_SCSI          = 8,
    E_PCMCIA_FUNC_CARDBUS       = 9,
    E_PCMCIA_FUNC_MANUFACTURER  = 0xFF      // manifacturer designed purpose
} PCMCIA_FUNCTYPE;

typedef enum {
    E_PCMCIA_MODULE_A           = 0,
    E_PCMCIA_MODULE_B           = 1,
    E_PCMCIA_MODULE_MAX         = 2
} PCMCIA_MODULE;

//-----------------------------------------------------------------------------
//  Structures
//-----------------------------------------------------------------------------
//! This structure contains information about exactly one possible PCMCIA card configuration.
typedef struct /* 13 Bytes */
{
    MS_U32 dwEAAddr;            //!< EA-address
    MS_U32 dwEALen;             //!< size of the EA area (zero for none)
    MS_U16 wIRQData;            //!< supported IRQ number mask
    MS_U8  bConfigIndex;        //!< cor //!< The value of bConfigIndex has to be written into the card configuration register to activate this configuration.
    MS_U8  bIRQDesc1;           //!< Interrupt descriptor byte
    MS_U8  fCITagsPresent;      //!< Bitfield which is 0x03 if both required CI tags are present. 0x01 for DVB_HOST, 0x02 for DVB_CI_MODULE
} PCMCIA_CONFIG;

//! This structure provides simple access to the PCMCIA card information
//! after decoding of the Card Information Structure. This decoding is performed by MDrv_CI_PCMCIA_ReadAttribMem()
typedef struct
{
    MS_U32 ConfigOffset;                            //!< Offset of the Configuration byte in the Attribute Memory
    MS_U32 dwValidFlags;                            //!< Bitmask that defines which of the other fields are valid
    MS_U16 wManufacturerId;                         //!< 16Bit Manufacturer ID (PCMCIAINFO_MANID_VALID)
    MS_U16 wCardID;                                 //!< 16Bit Card ID (PCMCIAINFO_MANID_VALID)

    /* 99 Bytes */
    MS_U16 wPCMCIAStdRev;                           //!< PCMCIA Standard version supported by the card (PCMCIAINFO_VERS1_VALID)
    MS_U8 pszManufacturerName[MAX_PCMCIA_STRLEN];   //!< Name of the card manufacturer (PCMCIAINFO_VERS1_VALID)
    MS_U8 pszProductName[MAX_PCMCIA_STRLEN];        //!< Product name (PCMCIAINFO_VERS1_VALID)
    MS_U8 pszProductInfo1[MAX_PCMCIA_STRLEN];       //!< (PCMCIAINFO_VERS1_VALID)
    MS_U8 pszProductInfo2[MAX_PCMCIA_STRLEN];       //!< (PCMCIAINFO_VERS1_VALID)
    MS_U8 bCI_PLUS;                                  //!< PCMCIA card CI Plus Compatibility Identification
    
    PCMCIA_FUNCTYPE FuncType;                       //!< Card function type (PCMCIAINFO_FUNCID_VALID)
    MS_U8 bFuncIDSysInfo;                           //!< SysInitByte from the FuncID block (PCMCIAINFO_FUNCID_VALID)

    MS_U8 bINT;                                     //!< PCMCIA card Support interrupt or not
    MS_U8 bNumConfigs;
    /* 13 * MAX_PCMCIA_CONFIGS(=10) = 130 Bytes*/   //!< The number of configurations supported by the card. Exactly bNumConfigs entries are valid in the Config array.
    PCMCIA_CONFIG Config[MAX_PCMCIA_CONFIGS];       //!< The array of possible card configurations
} PCMCIA_INFO;

//! This structure provides ISR data for upper layer
//! DO NOT change the current data member
//! Only allow to add new member in the tail of the structure
typedef struct {
    MS_BOOL bISRCardInsert;
    MS_BOOL bISRCardRemove;    
    MS_BOOL bISRCardData;    
} PCMCIA_ISR;

//! This file typedefs PCMCIA_HANDLE as void*.
//! Actual PCMCIA driver implementations can hide whatever they want inside this handle.
//! Higher level drivers pass
typedef void *PCMCIA_HANDLE;

//-----------------------------------------------------------------------------
//  Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  Global Functions
//-----------------------------------------------------------------------------
// PCMCIA

// revision history
// V2
//    for multiple PCMCIA slot support
//

void MDrv_PCMCIA_Init( MS_BOOL bCD_Reverse );

MS_BOOL MDrv_PCMCIA_PollingV2( PCMCIA_MODULE eModule );

void MDrv_PCMCIA_Set_HW_ResetDuration( MS_U8 u8HW_ResetDuration );

void MDrv_PCMCIA_ResetHW_V2( PCMCIA_MODULE eModule );
//! This function is called by higher level drivers to check if a module is (still) present.
//! Usually, this check is performed by checking the card detect GPIO pins of a PCMCIA slot.

void MDrv_PCMCIA_ReadAttribMemV2( PCMCIA_MODULE eModule, MS_U16 u16Addr, MS_U8 *pDest );
//! This function decodes a raw attribute memory dump into an easily readable
//! PCMCIA_INFO structure. The PCMCIA/PnP task is responsible for reading the raw attribute memory.
//! This function parses the card info structure (CIS) and decodes the relevant parts. Callers should
//! check the dwValidFlags Bitmask before accessing other fields.

void MDrv_PCMCIA_ParseAttribMem( MS_U8 *pAttribMem, MS_U16 dwLen, PCMCIA_INFO *pInfo );
//! Initialization function. During system initialization, this function
//! is called once to initialize the driver.

void MDrv_PCMCIA_WriteAttribMemV2( PCMCIA_MODULE eModule, MS_U16 wAddr, MS_U8 bData );
//! This function is called to write the byte bData into the card IO memory at address
//! wAddr.

void MDrv_PCMCIA_WriteIOMemV2( PCMCIA_MODULE eModule, MS_U16 wAddr, MS_U8 bData );
//! This function is read one byte of from the card IO memory at address wAddr.

void MDrv_PCMCIA_WriteIOMemLongV2( PCMCIA_MODULE eModule, MS_U16 u16Addr, MS_U8 u8Value, MS_U16 u16DataLen, MS_U8* u8pWriteBuffer);

MS_U8 MDrv_PCMCIA_ReadIOMemV2( PCMCIA_MODULE eModule, MS_U16 wAddr );

MS_BOOL MDrv_PCMCIA_IsModuleStillPluggedV2( PCMCIA_MODULE eModule );
//! This function is called to enable or disable the TS stream for PCMCIA common interface slots.

void MDrv_PCMCIA_Set_Detect_Trigger( MS_BOOL bActiveHigh );
void MDrv_PCMCIA_Set_Detect_Enable( MS_BOOL bEnable );
MS_U32 MDrv_PCMCIA_Get_CD_IntervalV2( PCMCIA_MODULE eModule );
MS_BOOL MDrv_PCMCIA_GetLibVer( const MSIF_Version **ppVersion );
void MDrv_PCMCIA_SetCommandBitV2( PCMCIA_MODULE eModule, MS_U8 u8CommandBit, MS_BOOL bValue );
MS_BOOL MDrv_PCMCIA_ResetInterfaceV2( PCMCIA_MODULE eModule );
MS_BOOL MDrv_PCMCIA_IsDataAvailableV2( PCMCIA_MODULE eModule );
MS_U16 MDrv_PCMCIA_ReadDataV2( PCMCIA_MODULE eModule, MS_U8* u8pReadBuffer, MS_U16 u16ReadBufferSize );
MS_BOOL MDrv_PCMCIA_WriteDataV2( PCMCIA_MODULE eModule, MS_U8* u8pWriteBuffer, MS_U16 u16DataLen );
MS_BOOL MDrv_PCMCIA_SwitchToIOmodeV2( PCMCIA_MODULE eModule, PCMCIA_INFO *pInfo );
MS_U16 MDrv_PCMCIA_NegotiateBufferSizeV2( PCMCIA_MODULE eModule, PCMCIA_INFO *pInfo );
void MDrv_PCMCIA_WriteBufferSizeV2( PCMCIA_MODULE eModule, MS_U16 u16BufferSize );
MS_BOOL MDrv_PCMCIA_WaitForStatusBitV2( PCMCIA_MODULE eModule, MS_U8 u8StatusBit );
MS_U8 MDrv_PCMCIA_ReadyStatus( void );

#if PCMCIA_IRQ_ENABLE
void MDrv_PCMCIA_Enable_InterruptV2( PCMCIA_MODULE eModule, MS_BOOL bEnable );
void MDrv_PCMCIA_Set_InterruptStatusV2( PCMCIA_MODULE eModule, MS_BOOL Status );
MS_BOOL MDrv_PCMCIA_Get_InterruptStatusV2( PCMCIA_MODULE eModule );
void MDrv_PCMCIA_InstarllIsrCallbackV2( PCMCIA_MODULE eModule, IsrCallback fnIsrCallback );
#endif


//-----------------------------------------------------------------------------
//  Function define for backward compatible
//-----------------------------------------------------------------------------
#define PCMCIA_DEFAULT_MODULE                   E_PCMCIA_MODULE_A
#if 0
    //#define MDrv_PCMCIA_Detect(p...)              MDrv_PCMCIA_DetectV2(E_PCMCIA_MODULE_A)
    #define MDrv_PCMCIA_Polling(p...)               MDrv_PCMCIA_PollingV2(PCMCIA_DEFAULT_MODULE)
    #define MDrv_PCMCIA_IsModuleStillPlugged(p...)  MDrv_PCMCIA_IsModuleStillPluggedV2(PCMCIA_DEFAULT_MODULE)
    #define MDrv_PCMCIA_SetCommandBit(p...)         MDrv_PCMCIA_SetCommandBitV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_ResetInterface(p...)        MDrv_PCMCIA_ResetInterfaceV2(PCMCIA_DEFAULT_MODULE)
    #define MDrv_PCMCIA_IsDataAvailable(p...)       MDrv_PCMCIA_IsDataAvailableV2(PCMCIA_DEFAULT_MODULE)
    #define MDrv_PCMCIA_ReadData(p...)              MDrv_PCMCIA_ReadDataV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_WriteData(p...)             MDrv_PCMCIA_WriteDataV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_SwitchToIOmode(p...)        MDrv_PCMCIA_SwitchToIOmodeV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_NegotiateBufferSize(p...)   MDrv_PCMCIA_NegotiateBufferSizeV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_WriteBufferSize(p...)       MDrv_PCMCIA_WriteBufferSizeV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_WaitForStatusBit(p...)      MDrv_PCMCIA_WaitForStatusBitV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_ResetHW(p...)               MDrv_PCMCIA_ResetHW_V2(PCMCIA_DEFAULT_MODULE)
    #define MDrv_PCMCIA_WriteAttribMem(p...)        MDrv_PCMCIA_WriteAttribMemV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_ReadAttribMem(p...)         MDrv_PCMCIA_ReadAttribMemV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_WriteIOMem(p...)            MDrv_PCMCIA_WriteIOMemV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_WriteIOMemLong(p...)        MDrv_PCMCIA_WriteIOMemLongV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_ReadIOMem(p...)             MDrv_PCMCIA_ReadIOMemV2(PCMCIA_DEFAULT_MODULE, p)
    #define MDrv_PCMCIA_Get_CD_Interval(p...)       MDrv_PCMCIA_Get_CD_IntervalV2(PCMCIA_DEFAULT_MODULE)

    #if PCMCIA_IRQ_ENABLE
        #define MDrv_PCMCIA_Enable_Interrupt(p...)      MDrv_PCMCIA_Enable_InterruptV2(PCMCIA_DEFAULT_MODULE, p)
        #define MDrv_PCMCIA_Set_InterruptStatus(p...)   MDrv_PCMCIA_Set_InterruptStatusV2(PCMCIA_DEFAULT_MODULE, p)
        #define MDrv_PCMCIA_Get_InterruptStatus(p...)   MDrv_PCMCIA_Get_InterruptStatusV2(PCMCIA_DEFAULT_MODULE)
        #define MDrv_PCMCIA_InstarllIsrCallback(p...)   MDrv_PCMCIA_InstarllIsrCallbackV2(PCMCIA_DEFAULT_MODULE, p)
    #endif    
#else
    MS_BOOL MDrv_PCMCIA_Polling( void );
    MS_BOOL MDrv_PCMCIA_IsModuleStillPlugged( void );
    void MDrv_PCMCIA_SetCommandBit( MS_U8 u8CommandBit, MS_BOOL bValue );
    MS_BOOL MDrv_PCMCIA_ResetInterface( void );
    MS_BOOL MDrv_PCMCIA_IsDataAvailable( void );
    MS_U16 MDrv_PCMCIA_ReadData( MS_U8* u8pReadBuffer, MS_U16 u16ReadBufferSize );
    MS_BOOL MDrv_PCMCIA_WriteData( MS_U8* u8pWriteBuffer, MS_U16 u16DataLen );
    MS_BOOL MDrv_PCMCIA_SwitchToIOmode( PCMCIA_INFO *pInfo );
    MS_U16 MDrv_PCMCIA_NegotiateBufferSize( PCMCIA_INFO *pInfo );
    void MDrv_PCMCIA_WriteBufferSize( MS_U16 u16BufferSize );
    MS_BOOL MDrv_PCMCIA_WaitForStatusBit( MS_U8 u8StatusBit );
    void MDrv_PCMCIA_ResetHW( void );
    void MDrv_PCMCIA_WriteAttribMem( MS_U16 wAddr, MS_U8 bData );
    void MDrv_PCMCIA_ReadAttribMem( MS_U16 u16Addr, MS_U8 *pDest );
    void MDrv_PCMCIA_WriteIOMem( MS_U16 wAddr, MS_U8 bData );
    void MDrv_PCMCIA_WriteIOMemLong( MS_U16 u16Addr, MS_U8 u8Value, MS_U16 u16DataLen, MS_U8* u8pWriteBuffer);
    MS_U8 MDrv_PCMCIA_ReadIOMem( MS_U16 wAddr );
    MS_U32 MDrv_PCMCIA_Get_CD_Interval( void );

    #if PCMCIA_IRQ_ENABLE
        void MDrv_PCMCIA_Enable_Interrupt( MS_BOOL bEnable );
        void MDrv_PCMCIA_Set_InterruptStatus( MS_BOOL Status );
        MS_BOOL MDrv_PCMCIA_Get_InterruptStatus( void );
        void MDrv_PCMCIA_InstarllIsrCallback( IsrCallback fnIsrCallback );
    #endif
#endif

#ifdef __cplusplus
}
#endif

#endif // _DRV_PCMCIA_H_
