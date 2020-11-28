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
/// @file   drvPM.h
/// @brief  PM Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_PM_H_
#define _DRV_PM_H_

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
/// define PM library version
#define MSIF_PM_LIB_CODE               {'P','M','_','_'}
#define MSIF_PM_LIBVER                 {'0','3'}
#define MSIF_PM_BUILDNUM               {'0','0'}
#define MSIF_PM_CHANGELIST             {'0','0','3','5','2','1','6','3'}
#define MSIF_PM_OS                           '0'                  //OS

#define PM_DRV_VERSION                 /* Character String for DRV/API version  */  \
    MSIF_TAG,                           /* 'MSIF' */  \
    MSIF_CLASS,                         /* '00' */  \
    MSIF_CUS,                           /* 0x0000 */  \
    MSIF_MOD,                           /* 0x0000 */  \
    MSIF_CHIP,                                       \
    MSIF_CPU,                                        \
    MSIF_PM_LIB_CODE,                  /* IP__ */  \
    MSIF_PM_LIBVER,                    /* 0.0 ~ Z.Z */  \
    MSIF_PM_BUILDNUM,                  /* 00 ~ 99 */  \
    MSIF_PM_CHANGELIST,                /* CL# */  \
    MSIF_PM_OS


#define PM_MAX_BUF_WAKE_IR             (32) //Both IR and Keypad share this pool
#define PM_MAX_BUF_WAKE_IR2            (16) //Only 2nd IR share this pool
#define PM_MAX_BUF_WAKE_KEYPAD         (32) //RESERVED
#define PM_MAX_BUF_WAKE_MAC_ADDRESS    (6)//For Mac address



//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

/// PM_CMD opcode
#define WRITE_CMD       0
#define READ_CMD        1
#define SLEEP_CMD       2
#define CTRL_WRITE_CMD  3
#define CTRL_READ_CMD   4

/// select sleep mode
#define SLEEP_MODE      0
#define DEEP_SLEEP_MODE 1

/// enable wakeup source
#define IR_WAKEUP       (1<<0)
#define CEC_WAKEUP      (1<<1)
#define GPIO5_WAKEUP    (1<<2)
#define GPIO6_WAKEUP    (1<<3)
#define KEYPAD_WAKEUP   (1<<4)
#define EASYSYNC_WAKEUP (1<<5)
#define SYNC_WAKEUP     (1<<6)
#define RTC_WAKEUP      (1<<7)

#define DVI_DET_WAKEUP  (1<<10)
#define DVI_DET2_WAKEUP (1<<11)

/// power off PM4 polarity
#define POWER_OFF_HIGH  (1<<15)

/// IR types
#define IR_TYPE_FULLDECODE_MODE 1
#define IR_TYPE_RAWDATA_MODE    2
#define IR_TYPE_SWDECODE_MODE   3

/// IRQ
#define MDRV_IRQ_BEGIN      0x40
#define MDRV_IRQ_END        0x7F
#define IRQ_PMSLEEP     (MDRV_IRQ_BEGIN + 12)

/// Enable GPIO
#define ENABLE_GPIO0    (1<<0)
#define ENABLE_GPIO1    (1<<1)
#define ENABLE_GPIO2    (1<<2)
#define ENABLE_GPIO3    (1<<3)  //GPIO 4&5 are reserved
#define ENABLE_GPIO6    (1<<6)
#define ENABLE_GPIO7    (1<<7)
#define ENABLE_GPIO8    (1<<8)
#define ENABLE_GPIO9    (1<<9)
#define ENABLE_GPIO10   (1<<10)
#define ENABLE_GPIO11   (1<<11)
#define ENABLE_GPIO12   (1<<12)


/// MICOM(PM_SLEEP) DDI Layer Command
typedef enum
{
    /// write data from host to PM : direction
    CP_WRITE_HOST_MEM_TO_MICOM = 0xE0,

    /// write data from host to PM : start
    CP_WRITE_HOST_MEM_TO_MICOM_START = 0xE1,

    /// write data from host to PM : data content
    CP_WRITE_HOST_MEM_TO_MICOM_DATA = 0xE2,

    /// write keypad boundary parameter 1 to PM
    CP_WRITE_KEYPAD_BOUND_1 = 0xE6,

    /// write keypad boundary parameter 2 to PM
    CP_WRITE_KEYPAD_BOUND_2 = 0xE7,

    /// read data from PM to host : direction
    CP_READ_MICOM_TO_HOST_MEM = 0xE3,

    /// read data from PM to host : start
    CP_WRITE_MICOM_TO_HOST_MEM_START = 0xE4,

    /// read data from PM to host : data content
    CP_READ_MICOM_TO_HOST_MEM_DATA = 0xE5,

    /// no command
    CP_NO_CMD = 0

} DDI_MICOM_CMDTYPE;

/// For PM mailbox command header
typedef struct
{
    MS_U8 Preamble  : 2;    /// two bits for command index
    MS_U8 Opcode    : 6;    /// 6 bits for operation codes
} PM_Cmd;

/// For initializing IR timing configuration
typedef struct
{
    MS_S16 s16Time;    /// time
    MS_S16 s16UpBnd;   /// upper bound
    MS_S16 s16LowBnd;  /// low bound
} PM_IrTimeCfg;

/// For initializing IR registers configuration
typedef struct
{
    MS_U8  u8IrModeSel;                 /// IR mode selection
    MS_U8  u8IrCtrl;                    /// IR enable control
    MS_U8  u8IrHdrCode0;                /// IR header code 0
    MS_U8  u8IrHdrCode1;                /// IR header code 1
    MS_U32 u32IrTimOutCyc;              /// IR timerout counter
    PM_IrTimeCfg tIrHdrCoTim;           /// header code time
    PM_IrTimeCfg tIrOffCoTim;           /// off code time
    PM_IrTimeCfg tIrOffCoRpTim;         /// off code repeat time
    PM_IrTimeCfg tIrLg01HighTim;        /// logical 0/1 high time
    PM_IrTimeCfg tIrLg0Tim;             /// logical 0 time
    PM_IrTimeCfg tIrLg1Tim;             /// logical 1 time
} PM_IrRegCfg;

/// For initializing keypad boundary configuration
typedef struct
{
    MS_U8 u8UpBnd;   /// upper bound
    MS_U8 u8LowBnd;  /// low bound
} PM_SarBndCfg;

/// For initializing keypad boundary configuration
typedef struct
{
    PM_SarBndCfg tSarChan1;          /// Channel 1 interrupt trigger boundary
    PM_SarBndCfg tSarChan2;          /// Channel 2 interrupt trigger boundary
    PM_SarBndCfg tSarChan3;          /// Channel 3 interrupt trigger boundary
    PM_SarBndCfg tSarChan4;          /// Channel 4 interrupt trigger boundary
} PM_SarRegCfg;

/// For initializing keypad wake-up parameter configuration
typedef struct
{
    PM_SarBndCfg tChanMinus;    /// parameter for Channel Minus
    PM_SarBndCfg tChanPlus;     /// parameter for Channel Plus
    PM_SarBndCfg tInput;        /// parameter for Input Source
    PM_SarBndCfg tMenu;         /// parameter for Menu
    PM_SarBndCfg tOk;           /// parameter for OK
    PM_SarBndCfg tPower;        /// parameter for Power
    PM_SarBndCfg tVolumeMinus;  /// parameter for Volume Minus
    PM_SarBndCfg tVolumePlus;   /// parameter for Volume Plus
} PM_SarParamCfg;

typedef enum
{
    E_PM_RTC_0=0,
    E_PM_RTC_2=1,
}E_PM_RTC;

///Define PM IRQ Type
typedef enum
{
    /// IRQ Type for IR
    E_PM_IRQ_IR         = 0,
    /// IRQ Type for CEC Wake-up
    E_PM_IRQ_CEC_WAKE   = 1,
    /// IRQ Type for External Interrup
    E_PM_IRQ_EX_INT     = 2,
    /// IRQ Type for External Interrup 2
    E_PM_IRQ_EX_INT2    = 3,
    /// IRQ Type for SAR(Keypad)
    E_PM_IRQ_SAR        = 4,
    /// IRQ Type for Sync Detection
    E_PM_IRQ_SYNC_DET   = 5,
    /// IRQ Type for DVI clock Detection
    E_PM_IRQ_DVICLK_DET = 6,
    /// IRQ Type for RTC
    E_PM_IRQ_RTC        = 7,
    /// IRQ Type for WDT
    E_PM_IRQ_WDT        = 8,
    /// IRQ Type for Mail Box 0
    E_PM_IRQ_MBOX0      = 9,
    /// IRQ Type for Mail Box 1
    E_PM_IRQ_MBOX1      = 10,
    /// IRQ Type for Mail Box 2
    E_PM_IRQ_MBOX2      = 11,
    /// IRQ Type for Mail Box 3
    E_PM_IRQ_MMOX3      = 12,
    /// Maximum IRQ Type
    E_PM_IRQ_MAX        = E_PM_IRQ_MMOX3,

} PM_IRQ_TYPE;

///Define PM Saved Registers
typedef struct
{
    unsigned long   r[32];          /// GPR regs
#ifdef __AEONR2__
    unsigned long   machi2;         // Highest 32-bits of new 32x32=64 multiplier
#endif
    unsigned long   machi;          /// High and low words of
    unsigned long   maclo;          /// multiply/accumulate reg

    unsigned long   pc;             /// Program Counter

    /// Saved only for exceptions, and not restored when continued:
    /// Effective address of instruction/data access that caused exception
    unsigned long   eear;           /// Exception effective address reg
    /// These are only saved for exceptions and interrupts
    int             vector;         /// Vector number
    int             sr;             /// Status Reg

} PM_SavedRegisters;

typedef void (*PM_IsrCb_Type)(PM_SavedRegisters *regs, MS_U32 vector);


typedef void ( *IRRecord_Callback ) (MS_U32 u32SrcAddr, MS_U16 u16DataSize);

///Define PM IRQ Struct
typedef struct
{
    PM_IsrCb_Type  isr;     /// PM ISR call back type
    MS_U32         data;    /// PM ISR data parameter
} PM_IrqStruct;





///Define PM debug level
typedef enum _PM_DbgLv
{
    E_PM_DBGLV_NONE,          /// no debug message
    E_PM_DBGLV_ERR_ONLY,      /// show error only
    E_PM_DBGLV_INFO,          /// show error & informaiton
    E_PM_DBGLV_ALL,           /// show error, information & funciton name
}PM_DbgLv;

///Define PM Return Value
typedef enum
{
    /// fail
    E_PM_FAIL = 0,
    /// success
    E_PM_OK = 1,

} PM_Result;

///Define PM return to HK PowerOn Mode
typedef enum
{
    E_PM_POWERON_STANBY = 1,
    E_PM_POWERON_SLEEP  = 2,
    E_PM_POWERON_DEEPSLEEP = 3,
    E_PM_POWERON_ACON = 0xff,

} PM_PowerOnMode;

typedef enum
{
	E_PM_WAKEUPSRC_NONE = 0,
	E_PM_WAKEUPSRC_IR,
	E_PM_WAKEUPSRC_DVI,
	E_PM_WAKEUPSRC_DVI2,
	E_PM_WAKEUPSRC_CEC,
	E_PM_WAKEUPSRC_SAR,
	E_PM_WAKEUPSRC_ESYNC,
	E_PM_WAKEUPSRC_SYNC,
	E_PM_WAKEUPSRC_RTC,
	E_PM_WAKEUPSRC_RTC2,
	E_PM_WAKEUPSRC_AVLINK,
	E_PM_WAKEUPSRC_UART,
	E_PM_WAKEUPSRC_GPIO,
	E_PM_WAKEUPSRC_MHL,
	E_PM_WAKEUPSRC_WOL,

} PM_WakeupSource;

///Define PM Acknoledge Flags
typedef enum
{
    E_PM_ACKFLG_NULL        = 0,                    /// Ack flag for NULL
    E_PM_ACKFLG_WAIT_INIT   = (1<<0),               /// Ack flag for Init
    E_PM_ACKFLG_WAIT_STATUS = (1<<1),               /// Ack flag for Status
    E_PM_ACKFLG_WAIT_LIBVER = (1<<2),               /// Ack flag for Library version
    E_PM_ACKFLG_WAIT_POWERDOWN = (1<<3),            /// Ack flag for Power down
    E_PM_ACKFLG_WAIT_RTCINIT = (1<<4),              /// Ack flag for Rtc Init
    E_PM_ACKFLG_WAIT_RTCSETCOUNTER = (1<<5),        /// Ack flag for set rtc counter
    E_PM_ACKFLG_WAIT_RTCGETCOUNTER = (1<<6),        /// Ack flag for get rtc counter
    E_PM_ACKFLG_WAIT_RTCSETMATCHCOUNTER = (1<<7),   /// Ack flag for set match counter
    E_PM_ACKFLG_WAIT_RTCGETMATCHCOUNTER = (1<<8),   /// Ack flag for get match counter
    E_PM_ACKFLG_WAIT_INFO = (1<<9),                 /// Ack flag for Get info
    E_PM_ACKFLG_WAIT_GETMASTERKEY = (1<<10),        /// Ack flag for Get master key
    E_PM_ACKFLG_WAIT_GETDEVICEID = (1<<11),         /// Ack flag for Get device ID
    E_PM_ACKFLG_WAIT_GETCHIPID = (1<<12),           /// Ack flag for Get chip ID
    E_PM_ACKFLG_WAIT_GPIOINIT = (1<<13),            /// Ack flag for init GPIO
    E_PM_ACKFLG_WAIT_PWMINIT = (1<<14),             /// Ack flag for PWM init
    E_PM_ACKFLG_WAIT_PWMCONFIG = (1<<15),           /// Ack flag for PWM config
    E_PM_ACKFLG_WAIT_GETPMMEMADDR = (1<<16),        /// Ack flag for Get PM mem addr
    E_PM_ACKFLG_WAIT_GETEXTRASRAMDATA = (1<<17),    /// Ack flag for Get PM extra sram data
    E_PM_ACKFLG_WAIT_SETEXTRASRAMDATA = (1<<18),    /// Ack flag for Set PM extra sram data
} PM_AckFlags;

///Define PM PWM Acknowledge Flags
typedef enum
{
    E_PM_PWM_ACKFLG_NULL        = 0,                    /// Ack flag for NULL
    E_PM_PWM_ACKFLG_WAIT_INIT   = (1<<0),               /// Ack flag for Init
    E_PM_PWM_ACKFLG_WAIT_CONF   = (1<<1),               /// Ack flag for Init
    E_PM_PWM_ACKFLG_WAIT_IRRECORD_RECIEVE_REQUIRE           = (1<<2),               /// Ack flag for ir recored reciecve require
    E_PM_PWM_ACKFLG_WAIT_IRRECORD_RECIEVE_COMPLETE          = (1<<3),              /// Ack flag for ir recored reciecve complete
    E_PM_PWM_ACKFLG_WAIT_IRRECORD_TRANSMIT                 = (1<<4),              /// Ack flag for ir record transmit
    E_PM_PWM_ACKFLG_WAIT_IRRECORD_SETCALLBACK              = (1<<5),               /// Ack flag for ir record reciecve set call back
    E_PM_PWM_ACKFLG_WAIT_IRRECORD_RECIEVE_EXIT             = (1<<6),               /// Ack flag for ir record reciecve exit
} PM_PWM_AckFlags;

#if defined(MSOS_TYPE_ECOS)
typedef enum
{
    E_PM_ST_NULL = 0,          /// PM Driver Status is NULL
    E_PM_ST_BOOTING = 1,       /// PM Driver Status is Booting
    E_PM_ST_READY = 2,         /// PM Driver Status is Ready
    E_PM_ST_STANDBY = 3,       /// PM Driver Status is Standby
    E_PM_ST_PMMODE = 4,        /// PM Driver Status is PmMode
    E_PM_ST_MAX_STATUS = 255   /// Maximum status for PM Driver Status

} __attribute__ ((aligned (4096))) PM_DrvStatus;

#else
///Define PM Driver Status
typedef enum __attribute__ ((aligned (4096)))
{
    E_PM_ST_NULL = 0,          /// PM Driver Status is NULL
    E_PM_ST_BOOTING = 1,       /// PM Driver Status is Booting
    E_PM_ST_READY = 2,         /// PM Driver Status is Ready
    E_PM_ST_STANDBY = 3,       /// PM Driver Status is Standby
    E_PM_ST_PMMODE = 4,        /// PM Driver Status is PmMode
    E_PM_ST_MAX_STATUS = 255   /// Maximum status for PM Driver Status

} PM_DrvStatus;
#endif

///Define PM Power Down Mode
#define E_PM_STANDBY     0      /// PM Power Down Mode is Standby
#define E_PM_SLEEP      1       /// PM Power Down Mode is Sleep
#define E_PM_DEEP_SLEEP 2       /// PM Power Down Mode is Deep Sleep
#define E_PM_NORMAL     3

///Define PM WakeUp Mode
#define E_PM_WAKE_ZERO  0       /// PM Wakeup Mode is zero
#define E_PM_WAKE_LAST  1       /// PM Wakeup Mode is last
#define E_PM_ZERO_TWOSTAGE_POWERDOWN    2
#define E_PM_LAST_TWOSTAGE_POWERDOWN    3

///Define PM Command Index
typedef enum
{
    //Aeon-->51 Command Index
    PM_CMDIDX_INIT = 0x01,                  /// PM Command Index is INIT
    PM_CMDIDX_GET_STATUS = 0x02,            /// PM Command Index is GET STATUS
    PM_CMDIDX_GET_LIBVER = 0x03,            /// PM Command Index is GET LIBVER
    PM_CMDIDX_POWER_DOWN = 0x04,            /// PM Command Index is POWER DOWN
    PM_CMDIDX_RTC_INIT = 0x05,              /// PM Command Index is RTC INIT
    PM_CMDIDX_RTC_SETCOUNTER = 0x06,        /// PM Command Index is SET COUNTER
    PM_CMDIDX_RTC_GETCOUNTER = 0x07,        /// PM Command Index is GET COUNTER
    PM_CMDIDX_RTC_SETMATCHCOUNTER = 0x08,   /// PM Command Index is SET MATCH COUNTER
    PM_CMDIDX_RTC_GETMATCHCOUNTER = 0x09,   /// PM Command Index is GET MATCH COUNTER
    PM_CMDIDX_GET_INFO = 0x0A,              /// PM Command Index is GET INFO
    PM_CMDIDX_GET_MASTERKEY = 0x0B,
    PM_CMDIDX_GET_DEVICEID = 0x0C,
    PM_CMDIDX_GET_CHIPID = 0x0D,
    PM_CMDIDX_GPIO_INIT = 0x0E,
    PM_CMDIDX_PWM_INIT =0x0F,
    PM_CMDIDX_PWM_CONFIG =0x10,

    PM_CMDIDX_PWM_IRRECORD_RECEIVED_SETCALLBACK = 0x11,
    PM_CMDIDX_PWM_IRRECORD_RECEIVED_REQUIRE = 0x12,
    PM_CMDIDX_PWM_IRRECORD_RECEIVED_COMPLETE = 0x13,
    PM_CMDIDX_PWM_IRRECORD_TRANSMIT = 0x14,
    PM_CMDIDX_PWM_IRRECORD_RECEIVED_EXIT = 0x15,
    PM_CMDIDX_GETEXTRASRAMDATA = 0x16,
    PM_CMDIDX_SETEXTRASRAMDATA = 0x17,
    PM_CMDIDX_SET_ONBOARD_LED = 0x18,             // Control On Board LED
    PM_CMDIDX_SET_POWER_LED_N_PROGRAM_TIMER_LED = 0x19,

    PM_CMDIDX_LED_FLASH     = 0x20,             // PM Command Index is LED Start        //@@++-- 20110329 Arki
    PM_CMDIDX_GLOBAL_CHIP_RESET = 0x21,
    PM_CMDIDX_GET_PM_MEMADDR = 0x22,
    PM_CMDIDX_GET_SYSTEM_ALIVE_STATUS    = 0x23,
    PM_CMDIDX_WDT_STATUS  = 0x24,
    PM_CMDIDX_UPATE_POWER_LED_STATUS = 0X25,
    PM_CMDIDX_LED_FLASH_TOGGLE     = 0x28,             // facory LED toggle
    PM_CMDIDX_POWER_ON_TIME_RECORD     = 0x29,  // PM Command Index is record AC and DC on time  Kenny
    
    PM_CMDIDX_ACK_51ToAEON = 0x30,          /// PM Command Index is ACK 51 To AEON
    PM_CMDIDX_SN_INIT_ACK   =  0x50,        /// to inform PM SN is start up
    //51->Aeon Command Index
    PM_CMDIDX_ACK_AEONTo51 = 0xA0,          /// PM Command Index is ACK AEON To 51

} PM_CmdIndex;

typedef enum
{
    E_WDT_NOT_ENABLE,
    E_WDT_REFRESH,
    E_WDT_STOP_REFRESH,
    E_WDT_RESET_SYSTEM_IMMEDIATE,
} WDT_STATUS;



typedef enum
{
    E_ON_BOARD_LED_OFF= 0,
    E_ON_BOARD_LED_PATTERN_1 = 1,
    E_ON_BOARD_LED_PATTERN_2 = 2,
    E_ON_BOARD_LED_PATTERN_3 = 3,
    E_ON_BOARD_LED_PATTERN_4 = 4,
    E_ON_BOARD_LED_PATTERN_5 = 5,
    E_ON_BOARD_LED_ON= 255,
} USB_LED_PATTERN;

typedef enum
{
    E_ON_BOARD_LED_STAGE_BIST= 0,
    E_ON_BOARD_LED_STAGE_MBOOT_SUCCESS=1,
    E_ON_BOARD_LED_STAGE_APL_SUCCESS= 2,
    E_ON_BOARD_LED_STAGE_UPDATE_SW= 3,
} ON_BOARD_LED_STAGE;


typedef enum
{
    E_PROGRAM_TIMER_IS_SET= 0,
    E_PROGRAM_TIMER_IS_REMINDING= 1,
    E_PROGRAM_TIMER_IS_RECORDING=2,
    E_PROGRAM_TIMER_IS_NOT_SET= 3,
} PROGRAM_TIMER_LED_STATUS;

typedef enum
{
    E_SW_UPDATE_NOT_IN_PROGRESS= 0,
    E_SW_UPDATE_IN_PROGRESS= 1,
    E_SW_UPDATE_FAILED= 2,
    E_SW_UPDATE_SUCCESSFUL= 3,
    E_SW_UPDATE_FAN_ERROR=4,
    E_SW_UPDATE_FAN_ERROR_RECOVER=5,
} SW_UPDATE_STATUS;

typedef enum
{
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE1= 1,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE2= 2,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE3= 3,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE4= 4,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE5= 5,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE6= 6,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE7= 7,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE8= 8,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE9= 9,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE10= 10,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE11= 11,
    E_POWER_LED_N_PROGRAM_TIMER_LED_MODE12= 12,
} POWER_LED_N_PROGRAM_TIMER_LED_MODE;

typedef enum
{
    E_POWER_LED_KEEP= 0,
    E_POWER_LED_GREEN,
    E_POWER_LED_RED,
    E_POWER_LED_ORANGE,
} UPATE_POWER_LED_PATTERN;


///Define PM STR Mode enum
typedef enum
{
    E_PM_NON_STR=0,           /// non-str dc on
    E_PM_NON_STR_AC,        /// non-str ac on
    E_PM_STR,               /// str
    E_PM_STR_CRC,           /// str and crc
}PM_STRMode;

/// Define PM Wake-up Configuration
#define CRC_KERNEL_BUF                 (3)
typedef struct __attribute__ ((aligned (4096)))
{
    MS_U8 bPmWakeEnableIR         : 1;/// For PM IR Wake-up
    MS_U8 bPmWakeEnableSAR        : 1;/// For PM SAR Wake-up
    MS_U8 bPmWakeEnableGPIO0      : 1;/// For PM GPIO0 Wake-up
    MS_U8 bPmWakeEnableGPIO1      : 1;/// For PM GPIO1 Wake-up
    MS_U8 bPmWakeEnableUART1      : 1;  /// For PM UART1 Wake-up
    MS_U8 bPmWakeEnableSYNC       : 1;/// For PM SYNC Wake-up
    MS_U8 bPmWakeEnableESYNC      : 1;/// For PM EasySYNC Wake-up

    MS_U8 bPmWakeEnableRTC0       : 1;/// For PM RTC0 Wake-up
    MS_U8 bPmWakeEnableRTC1       : 1;/// For PM RTC1 Wake-up
    MS_U8 bPmWakeEnableDVI0       : 1;/// For PM DVI0 Wake-up
    MS_U8 bPmWakeEnableDVI2       : 1;/// For PM DVI1 Wake-up
    MS_U8 bPmWakeEnableCEC        : 1;/// For PM CEC Wake-up
    MS_U8 bPmWakeEnableAVLINK     : 1;/// For PM AVLINK Wake-up
    MS_U8 bPmWakeEnableMHL        : 1;/// For PM MHL Wake-up
    MS_U8 bPmWakeEnableWOL        : 1;/// For PM WOL Wake-up

    MS_U8 u8PmWakeIR[PM_MAX_BUF_WAKE_IR];///For PM IR Wake-up key define
    MS_U8 u8PmWakeIR2[PM_MAX_BUF_WAKE_IR2];///For PM IR Wake-up key define
    MS_U8 u8PmWakeMACAddress[PM_MAX_BUF_WAKE_MAC_ADDRESS];///For PM WOL Wake-up Mac define
  
    MS_U8 u8PmStrMode;
    MS_BOOL bLxCRCMiu[CRC_KERNEL_BUF];
    MS_U32 u32LxCRCAddress[CRC_KERNEL_BUF];
    MS_U32 u32LxCRCSize[CRC_KERNEL_BUF]; 
} PM_WakeCfg;

/// Define PWM  simaulator IR mode
typedef struct __attribute__ ((aligned (4096)))
{
    MS_U8 u8IREncodeMode;
    MS_U8 u8Customercode1;
    MS_U8 u8Customercode2;
    MS_U8 u8IRKeycode;
    MS_U8 u8IRRepeat;
    MS_U8 u8Reserved0;              /// Reserved
    MS_U8 u8Reserved1;              /// Reserved
    MS_U8 u8Reserved2;              /// Reserved
} PWMSimIR_CFG;

typedef struct __attribute__ ((aligned (4096)))
{
    //MS_U32 u32RtcCounter;
    //MS_U8 u8WakeupSource;
    MS_U16 u16Offset;
    MS_U16 u16DataLen;
    MS_U8  u8ExtraSramData[]; //Max size 512 bytes
} PM_ExtraSramData;

/// Define PM Power Down Modes
typedef struct __attribute__ ((aligned (4096)))
{
    MS_U8 u8PowerDownMode;        /// Power Down Mode
    MS_U8 u8WakeAddress;

} PM_PowerDownCfg;

/// Define PM RTC Parameters
typedef struct __attribute__ ((aligned (4096)))
{
    MS_U32 u32RtcCtrlWord;          /// Define PM RTC Control Word
    MS_U32 u32RtcSetMatchCounter;   /// Define PM RTC for Set Match Counter
    MS_U32 u32RtcGetMatchCounter;   /// Define PM RTC for Get Match Counter
    MS_U32 u32RtcSetCounter;        /// Define PM RTC for Set Counter
    MS_U32 u32RtcGetCounter;        /// Define PM RTC for Get Counter
    MS_U8 u8PmRtcIndex;             /// Define PM RTC Index
    MS_U8 u8Reserved0;              /// Reserved
    MS_U8 u8Reserved1;              /// Reserved
    MS_U8 u8Reserved2;              /// Reserved

} PM_RtcParam;

/// Define PM Driver Information
typedef struct __attribute__ ((aligned (4096)))
{
    MS_U8 u8PmSupSleepMode; /// Spuuort PM Sleep Mode
    MS_U8 u8PmSupRtcIdxMax; /// Support RTC Index Max

}PM_DrvInfo;

typedef struct
{
    MS_U8 u8Reserved[16]; ///Dummy Write for MIU FIFO

}PM_Dummy;


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_PM_isRunning(void);
void MDrv_PM_InterruptRequest( void );
void MDrv_PM_LoadFw( MS_U8 *pPmCode, MS_U16 u16Len );
MS_BOOL MDrv_PM_RegWrite( MS_U16 u16Addr, MS_U8 u8Data );
MS_U8 MDrv_PM_RegRead( MS_U16 u16Addr );
void MDrv_PM_RegWriteBit(MS_U16 u16Addr, MS_U8 bBit, MS_U8 u8BitPos );
MS_U8 MDrv_PM_RegReadBit(MS_U16 u16Addr, MS_U8 u8BitPos);
void MDrv_PM_RegWrite2byte( MS_U16 u16RegIndex, MS_U16 u16Value );
void MDrv_PM_RegWrite3byte( MS_U16 u16Regndex, MS_U32 u32Value );
MS_BOOL MDrv_PM_Control( MS_U8 u8opcode, MS_U8 u8Data, MS_U16 u16Data );
MS_BOOL MDrv_PM_CtrlWrite( MS_U8 u8Opcode, MS_U8 u8CmdType, MS_U8 u8DataNum, MS_U8 *pu8Data );
MS_BOOL MDrv_PM_CtrlRead( MS_U8 u8Opcode, MS_U8 u8CmdType, MS_U8 u8DataNum, MS_U8 *pu8Data );
MS_BOOL MDrv_PM_MemoryWrite(MS_U8 *pu8Data, MS_U16 u16MemLen);
MS_BOOL MDrv_PM_MemoryRead(MS_U8 *pu8Data, MS_U16 u16MemLen);
void MDrv_PM_RTCEnableInterrupt(MS_BOOL bEnable);
/*add by owen.qin begin*/
void MDrv_PM_RTC2EnableInterrupt(MS_BOOL bEnable);
void MDrv_PM_RTC2SetMatchTime(MS_U32 u32PmSysTime);
/*add by owen.qin end*/
void MDrv_PM_RTCSetMatchTime(MS_U32 u32PmSysTime);
MS_U32 MDrv_PM_RTCGetMatchTime(void);
void MDrv_PM_RTCSetSystemTime(MS_U32 u32PmSysTime);
MS_U32 MDrv_PM_RTCGetSystemTime(void);
void MDrv_PM_RTCInit(MS_U32 u32CtrlWord);
void MDrv_PM_IRInit(MS_U8 irclk_mhz, PM_IrRegCfg *irRegCfg);
void MDrv_PM_KeypadInit(PM_SarRegCfg *sarRegCfg, PM_SarParamCfg *sarParamCfg);
void MDrv_PM_CalibrateRC(void);
MS_BOOL MDrv_PM_isDownloaded(void);
void MDrv_PM_Set_Download(void);

void MDrv_PM_IrqAttach(PM_IRQ_TYPE irq, PM_IsrCb_Type isr, MS_U32 data);
void MDrv_PM_IrqDetach(PM_IRQ_TYPE irq);
void MDrv_PM_IrqUnmask(PM_IRQ_TYPE irq);
void MDrv_PM_IrqMask(PM_IRQ_TYPE irq);
void MDrv_PM_IrqMaskAll(void);

PM_Result MDrv_PM_ActiveStandbyMode(MS_BOOL bTrigger);
PM_Result MDrv_PM_IsActiveStandbyMode(MS_BOOL *bActive);

PM_Result MDrv_PM_Init(PM_WakeCfg *pPmWakeCfg);
PM_Result MDrv_PM_GetStatus(PM_DrvStatus *pDrvStatus);
PM_Result MDrv_PM_GetLibVer(const MSIF_Version **ppVersion);
PM_Result MDrv_PM_PowerDown(PM_PowerDownCfg *pPmPowerDownCfg);
PM_Result MDrv_PM_GetMasterKey(MS_U8 *pPmPowerDownCfg);
PM_Result MDrv_PM_GetDeviceID(MS_U8 *DeviceID);
PM_Result MDrv_PM_GetChipID(MS_U8 *ChipParam);
PM_Result MDrv_PM_GetPMMemAddr(MS_U8 *PmMemAddr);
const PM_DrvInfo* MDrv_PM_GetInfo(void);
PM_Result MDrv_PM_GPIOInit(MS_U16 u16GPIOIndex);
PM_Result MDrv_PM_SetDbgLevel(PM_DbgLv eLevel);
PM_Result MDrv_PM_RtcInit(PM_RtcParam *pPmRtcParam);
void MDrv_PM_Rtc_DisableInit(E_PM_RTC eRtc);
PM_Result MDrv_PM_RtcSetCounter(PM_RtcParam *pPmRtcParam);
PM_Result MDrv_PM_RtcGetCounter(PM_RtcParam *pPmRtcParam);
PM_Result MDrv_PM_RtcSetMatchCounter(PM_RtcParam *pPmRtcParam);
PM_Result MDrv_PM_RtcGetMatchCounter(PM_RtcParam *pPmRtcParam);
PM_Result MDrv_PM_GetExtraSramData(PM_ExtraSramData *pPmExtraSramData);
PM_Result MDrv_PM_SetExtraSramData(PM_ExtraSramData *pPmExtraSramData);

void MDrv_PM_SetSPIOffsetForMCU(MS_U32 BANK);
void MDrv_PM_SetSRAMOffsetForMCU(void);
void MDrv_PM_SetDRAMOffsetForMCU(MS_U32 u32Offset);

PM_PowerOnMode MDrv_PM_PowerOnMode(void);
PM_WakeupSource MDrv_PM_GetWakeupSource(void);
MS_U8 MDrv_PM_GetWakeupKey(void);
PM_Result MDrv_PM_Disable51(void);

PM_Result MDrv_PM_GPIO4_SetPower(MS_BOOL bOn);

PM_Result MDrv_PM_PWM_Init(MS_U8 u8PWM);
PM_Result MDrv_PM_PWM_Config(PWMSimIR_CFG *pPmPWMCfg);

PM_Result MDrv_PM_PWM_IRRecord_Init(void);
PM_Result MDrv_PM_PWM_IRRecord_Receive_Complete(MS_U32 u32BufferAddr,MS_U16 u16BufferSize);
PM_Result MDrv_PM_PWM_IRRecord_Receive_Require(MS_U32 u32BufferAddr,MS_U16 u16BufferSize);
PM_Result MDrv_PM_PWM_IRRecord_Transmit(MS_U32 u32BufferAddr,MS_U16 u16BufferSize);
PM_Result MDrv_PM_PWM_IRRecord_SetCallBackFunction(IRRecord_Callback pCallback);
PM_Result MDrv_PM_PWM_IRRecord_Receive_Exit(void);

void MDrv_PM_RunTimePM_Disable_PassWord(void);
void MDrv_PM_STR_CheckFactoryPowerOnModePassword(void);
PM_Result MDrv_PM_STR_CheckFactoryPowerOnMode_Second(MS_BOOL bCheck);

PM_Result MDrv_PM_Check_Version(MS_BOOL bCheck);
MS_U16 MDrv_PM_GetSRAMSize(void);
MS_U8 MDrv_PM_GetIRPowerOnKey(void);

#ifdef __cplusplus
}
#endif

#endif // _DRV_PM_H_

