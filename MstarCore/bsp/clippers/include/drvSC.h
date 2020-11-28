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
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvSC.h
/// @brief  SmartCard Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_SC_H__
#define __DRV_SC_H__


#ifdef __cplusplus
extern "C"
{
#endif

#include "MsDevice.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define MSIF_SC_LIB_CODE            {'S','C'}    //Lib code
#define MSIF_SC_LIBVER              {'0','1'}            //LIB version
#define MSIF_SC_BUILDNUM            {'0','1'}            //Build Number
#define MSIF_SC_CHANGELIST          {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define SC_DRV_VERSION              /* Character String for DRV/API version             */  \
    MSIF_TAG,                       /* 'MSIF'                                           */  \
    MSIF_CLASS,                     /* '00'                                             */  \
    MSIF_CUS,                       /* 0x0000                                           */  \
    MSIF_MOD,                       /* 0x0000                                           */  \
    MSIF_CHIP,                                                                              \
    MSIF_CPU,                                                                               \
    MSIF_SC_LIB_CODE,               /* IP__                                             */  \
    MSIF_SC_LIBVER,                 /* 0.0 ~ Z.Z                                        */  \
    MSIF_SC_BUILDNUM,               /* 00 ~ 99                                          */  \
    MSIF_SC_CHANGELIST,             /* CL#                                              */  \
    MSIF_OS

#define SC_ATR_LEN_MAX              33                                  ///< Maximum length of ATR
#define SC_ATR_LEN_MIN              2                                   ///< Minimum length of ATR
#define SC_HIST_LEN_MAX             15                                  ///< Maximum length of ATR history
#define SC_PPS_LEN_MAX              6                                   ///< Maximum length of PPS
#define SC_FIFO_SIZE                512                                 // Rx fifo size

///SC_Param.u8UartMode
#define SC_UART_CHAR_7              (0x02)
#define SC_UART_CHAR_8              (0x03)
#define SC_UART_STOP_1              (0x00)
#define SC_UART_STOP_2              (0x04)
#define SC_UART_PARITY_NO           (0x00)
#define SC_UART_PARITY_ODD          (0x08)
#define SC_UART_PARITY_EVEN         (0x08|0x10)


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef struct _SC_Status
{
    MS_BOOL                         bCardIn;                            ///< Card status

} SC_Status;

typedef enum _SC_DbgLv
{
    E_SC_DBGLV_NONE,                                                    //no debug message
    E_SC_DBGLV_ERR_ONLY,                                                //show error only
    E_SC_DBGLV_REG_DUMP,                                                //show error & reg dump
    E_SC_DBGLV_INFO,                                                    //show error & informaiton
    E_SC_DBGLV_ALL,                                                     //show error, information & funciton name
} SC_DbgLv;

/// SmartCard DDI error code
typedef enum
{
    E_SC_FAIL,                                                          ///< Function fail
    E_SC_OK,                                                            ///< No Error
    E_SC_PPSFAIL,                                                       ///< Do PPS fail
    E_SC_INVCONV,                                                       ///< Inverse convention
    E_SC_CARDIN,                                                        ///< Card in
    E_SC_CARDOUT,                                                       ///< Card out
    E_SC_NODATA,                                                        ///< No data
    E_SC_TIMEOUT,                                                       ///< Timeout
    E_SC_OVERFLOW,                                                      ///< Rx data fifo overflow
    E_SC_CRCERROR,                                                      ///< ATR checksum error
    E_SC_DATAERROR,                                                     ///< Data error
    E_SC_PARMERROR,                                                     ///< Parameter error
} SC_Result;

/// SmartCard event
typedef enum
{
    E_SC_EVENT_DATA,                                                    ///< Rx data valid
    E_SC_EVENT_IN,                                                      ///< Card in
    E_SC_EVENT_OUT,                                                     ///< Card out

} SC_Event;

/// SmartCard CLK setting
typedef enum
{
    E_SC_CLK_3M,                                                        ///< 3 MHz
    E_SC_CLK_4P5M,                                                      ///< 4.5 MHz
    E_SC_CLK_6M,                                                        ///< 6 MHz
    E_SC_CLK_13M,                                                        ///< 6 MHz
} SC_ClkCtrl;

/// SmartCard VCC control mode
typedef enum
{
    E_SC_VCC_CTRL_8024_ON,                                              ///< by external 8024 on
    E_SC_VCC_CTRL_LOW,                                                  ///< by direct Vcc (low active)
    E_SC_VCC_CTRL_HIGH,                                                 ///< by direct Vcc (high active)
    E_SC_OCP_VCC_HIGH,
} SC_VccCtrl;

// smart card 3V/5V control
typedef enum
{
    E_SC_VOLTAGE_3_POINT_3V,                                              ///<3.3V
    E_SC_VOLTAGE_5V,                                                      ///< 5V
    E_SC_VOLTAGE_MAX
} SC_VoltageCtrl;

typedef void(*P_SC_En5V_Callback)(MS_BOOL bEnable);

/// SmartCard configuration
typedef struct
{
    MS_U8                           u8Protocal;                         ///< T=
    SC_ClkCtrl                      eCardClk;                           ///< Clock
    MS_U8                           u8UartMode;                         ///< Uart Mode
    MS_U16                          u16ClkDiv;                          ///< Div
    SC_VccCtrl                      eVccCtrl;
    MS_U16                          u16Bonding;                         ///Chip Bonding type
    P_SC_En5V_Callback              pfOCPControl;
    MS_U8                           u8Convention;                       ///< Convention
    SC_VoltageCtrl                  eVoltage;
} SC_Param;

/// SmartCard event callback
typedef void (*P_SC_Callback)(MS_U8 u8SCID, SC_Event eEvent);

typedef struct _Smart_Dev
{

} SC_Dev;


/// SmartCard Info
typedef struct
{
    // SmsartCard Protocol
    MS_U8                           u8Protocol;                         ///T= Protocol
    MS_BOOL                         bSpecMode;                          ///Special mode
    MS_U8                           pu8Atr[SC_ATR_LEN_MAX];             ///Atr buffer
    MS_U16                          u16AtrLen;                          ///Atr length
    MS_U8                           pu8Hist[SC_HIST_LEN_MAX];           ///History buffer
    MS_U16                          u16HistLen;                         ///History length
    MS_U8                           u8Fi;                               ///Fi
    MS_U8                           u8Di;                               ///Di

    // Device Setting
    MS_BOOL                         bInited;
    MS_BOOL                         bOpened;                           ///Open
    MS_BOOL                         bCardIn;                            ///Status care in
    MS_BOOL                         blast_cardin;
    SC_ClkCtrl                      eCardClk;                           ///< Clock
    MS_U8                           u8UartMode;                         ///< Uart Mode
    SC_VccCtrl                      eVccCtrl;
    MS_U16                          u16ClkDiv;                         ///< Div
    MS_U16                          u16Bonding; //@TODO: how to take care of bonding?????
    P_SC_En5V_Callback              pfEn5V;
    MS_U8                           u8Convention;

    MS_U8                           u8FifoRx[SC_FIFO_SIZE];
    MS_U16                          u16FifoRxRead;
    MS_U16                          u16FifoRxWrite;

    MS_U8                           u8FifoTx[SC_FIFO_SIZE];
    MS_U16                          u16FifoTxRead;
    MS_U16                          u16FifoTxWrite;
    P_SC_Callback                   pfNotify;                           ///Call back funtcion

    MS_BOOL                         bLastCardIn;
    MS_S32                          s32DevFd;

} SC_Info;


/// SmartCard Caps
typedef struct
{
    MS_U8                           u8DevNum;                           ///SmartCard Device Number

} SC_Caps;

///Define SC Command Index
typedef enum
{
    //MIPS-->51 Command Index
    SC_CMDIDX_RAW_EXCHANGE = 0x01,                  /// SC Command Index is Raw Data Exchange
    SC_CMDIDX_GET_ATR      = 0x02,                  /// SC Command Index is Get ATR
    SC_CMDIDX_SEND         = 0x03,                  /// SC Command Index is Send Data
    SC_CMDIDX_RECV         = 0x04,                  /// SC Command Index is Receive Data

    SC_CMDIDX_ACK_51ToMIPS = 0x30,                  /// SC Command Index is ACK 51 To MIPS

    //51->MIPS Command Index
    SC_CMDIDX_ACK_MIPSTo51 = 0xA0,                  /// SC Command Index is ACK MIPS To 51

} SC_CmdIndex;


///Define SC Acknowledge Flags
typedef enum
{
    E_SC_ACKFLG_NULL                = 0,            /// Ack flag for NULL
    E_SC_ACKFLG_WAIT_RAW_EXCHANGE   = (1<<0),       /// Ack flag for Raw Exchange
    E_SC_ACKFLG_WAIT_GET_ATR        = (1<<1),       /// Ack flag for ATR
    E_SC_ACKFLG_WAIT_SEND           = (1<<2),       /// Ack flag for Sending
    E_SC_ACKFLG_WAIT_RECV           = (1<<3),       /// Ack flag for Receiving

} SC_AckFlags;

typedef struct __attribute__ ((packed, aligned (4096)))
{
    MS_U8  u8SCID;
    MS_U16 u16DataLen;       /* Send and reply data length*/
    MS_U16 u16ReplyMaxLen;   /* Maximum length of reply data */
    MS_U8  u8Data[259];      /* T=0, 256 data bytes plus the two status words SW1 and SW2
                                                T=1, 254 INF bytes plus NAD, PCB, LEN, and two EDC bytes
                                                Send and reply data buffer*/
} SC_DataCfg;

/// SmartCard Caps
typedef struct
{
    MS_U32   u32DataBuffAddr;                            ///SmartCard Data Buffer Address, 4K alignment
    MS_U32   u32FwBuffAddr;                              ///SmartCard Firmware Buffer Address, 64K alignment
} SC_BuffAddr;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

SC_Result       MDrv_SC_Init(MS_U8 u8SCID);
SC_Result       MDrv_SC_Open(MS_U8 u8SCID, MS_U8 u8Protocol, SC_Param* pParam, P_SC_Callback pfSmartNotify);
SC_Result       MDrv_SC_Config(MS_U8 u8SCID, SC_Param* pParam);
SC_Result       MDrv_SC_Close(MS_U8 u8SCID);
SC_Result       MDrv_SC_Reset(MS_U8 u8SCID, SC_Param* pParam);
SC_Result       MDrv_SC_Activate(MS_U8 u8SCID);
SC_Result       MDrv_SC_Deactivate(MS_U8 u8SCID);
SC_Result       MDrv_SC_Reset_ATR(MS_U8 u8SCID, SC_Param* pParam, MS_U8 *pu8Atr, MS_U16 *pu16AtrLen, MS_U8 *pu8His, MS_U16 *pu16HisLen);
SC_Result       MDrv_SC_PPS(MS_U8 u8SCID);
SC_Result       MDrv_SC_Send(MS_U8 u8SCID, MS_U8 *pu8SendData, MS_U16 u16SendDataLen, MS_U32 u32TimeoutMs);
SC_Result       MDrv_SC_Recv(MS_U8 u8SCID, MS_U8 *pu8ReadData, MS_U16 *u16ReadDataLen, MS_U32 u32TimeoutMs);
SC_Result       MDrv_SC_T0_SendRecv(MS_U8 u8SCID, MS_U8 *pu8SendData, MS_U16 u16SendLen, MS_U8 *pu8RecvData, MS_U16 *pu16RecvLen);
SC_Result       MDrv_SC_T1_SendRecv(MS_U8 u8SCID, MS_U8 *pu8SendData, MS_U16 *u16SendDataLen, MS_U8 *pu8ReadData, MS_U16 *u16ReadDataLen);
SC_Result       MDrv_SC_T14_SendRecv(MS_U8 u8SCID, MS_U8 *pu8SendData, MS_U16 u16SendLen, MS_U8 *pu8RecvData, MS_U16 *pu16RecvLen);
SC_Result       MDrv_SC_Exit(MS_U8 u8SCID);

SC_Result       MDrv_SC_GetATR(MS_U8 u8SCID, MS_U32 u32TimeOut,MS_U8 *pu8Atr, MS_U16 *pu16AtrLen, MS_U8 *pu8His, MS_U16 *pu16HisLen);
const SC_Info*  MDrv_SC_GetInfo(MS_U8 u8SCID);
SC_Result       MDrv_SC_GetLibVer(const MSIF_Version **ppVersion);
SC_Result       MDrv_SC_GetStatus(MS_U8 u8SCID, SC_Status *pStatus);
void            MDrv_SC_SetDbgLevel(SC_DbgLv eLevel);
SC_Result       MDrv_SC_SetPPS(MS_U8 u8SCID, MS_U8 u8SCProtocol, MS_U8 u8Di,MS_U8 u8Fi);
SC_Result       MDrv_SC_ClearState(MS_U8 u8SCID);
SC_Result       MDrv_SC_PowerOff(void);
SC_Result       MDrv_SC_SetGuardTime(MS_U8 u8SCID, MS_U8 u8GuardTime);

SC_Result       MDrv_SC_Task_Proc(void);
MS_BOOL         MDrv_SC_ISR_Proc(MS_U8 u8SCID);
SC_Result       MDrv_SC_RawExchange(MS_U8 u8SCID, MS_U8 *pu8SendData, MS_U16 *u16SendDataLen, MS_U8 *pu8ReadData, MS_U16 *u16ReadDataLen);
SC_Result       MDrv_SC_RawExchangeTimeout(MS_U8 u8SCID, MS_U8 *pu8SendData, MS_U16 *u16SendDataLen, MS_U8 *pu8ReadData, MS_U16 *u16ReadDataLen, MS_U32 u32TimeoutMs);
SC_Result       MDrv_SC_SetBuffAddr(SC_BuffAddr *pScBuffAddr);
MS_BOOL         MDrv_SC_CardVoltage_Config(MS_U8 u8SCID, SC_VoltageCtrl eVoltage);
void            MDrv_SC_EnableTimeout(MS_BOOL bTimeout);
MS_U32          MDrv_SC_SetPowerState(EN_POWER_MODE u16PowerState);

#ifdef __cplusplus
}
#endif

#endif // __DRV_SC_H__
