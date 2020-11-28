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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvCMDQ.h
/// @brief  CMDQ Driver Interface
/// @author MStar Semiconductor,Inc.
///
////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef _DRVCMDQ_H_
#define _DRVCMDQ_H_

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------------------------------------
//  Define
//--------------------------------------------------------------------------------------------------
#define AES_ENABLE                   0x01
#define TDES_ENABLE                  0x10
#define WORD_MASK                    0x0000000F

#define DIRECT_MODE                 0x01
#define INCREMENT_MODE              0x00

#define MSIF_CMDQ_LIB_CODE                     {'C','M','D','Q'}    //Lib code
#define MSIF_CMDQ_LIBVER                       {'0','1'}            //LIB version
#define MSIF_CMDQ_BUILDNUM                     {'0','1'}            //Build Number
#define MSIF_CMDQ_CHANGELIST                   {'0','0','0','0','0','0','0','0'} //P4 ChangeList Number

#define CMDQ_DRV_VERSION                 /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_CMDQ_LIB_CODE,                  /* IP__                                             */  \
    MSIF_CMDQ_LIBVER,                          /* 0.0 ~ Z.Z                                        */  \
    MSIF_CMDQ_BUILDNUM,                          /* 00 ~ 99                                          */  \
    MSIF_CMDQ_CHANGELIST,  /* CL#                                              */  \
    MSIF_OS


typedef enum //_DrvTSP_DbgLevel
{
    E_DRVCMDQ_DBG_Release = 0,
    E_DRVCMDQ_DBG_L1, // display error msg
    E_DRVCMDQ_DBG_L2, // display error msg and enter while(1)
} DrvCMDQ_DbgLevel;

//--------------------------------------------------------------------------------------------------
//  Driver Capability
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  Local variable
//-----------------------------------------------------------------------------------------------
#define CMDQ_DUMMY_ZERO                0x00000000
#define CMDQ_DUMMY_BIT_0x00            0x00000001
#define CMDQ_DUMMY_BIT_0x01            0x00000002
#define CMDQ_DUMMY_BIT_0x02            0x00000004
#define CMDQ_DUMMY_BIT_0x03            0x00000008
#define CMDQ_DUMMY_BIT_0x04            0x00000010
#define CMDQ_DUMMY_BIT_0x05            0x00000020
#define CMDQ_DUMMY_BIT_0x06            0x00000040
#define CMDQ_DUMMY_BIT_0x07            0x00000080
#define CMDQ_DUMMY_BIT_0x08            0x00000100
#define CMDQ_DUMMY_BIT_0x09            0x00000200
#define CMDQ_DUMMY_BIT_0x0A            0x00000400
#define CMDQ_DUMMY_BIT_0x0B            0x00000800
#define CMDQ_DUMMY_BIT_0x0C            0x00001000
#define CMDQ_DUMMY_BIT_0x0D            0x00002000
#define CMDQ_DUMMY_BIT_0x0E            0x00004000
#define CMDQ_DUMMY_BIT_0x0F            0x00008000
//--------------------------------------------------------------------------------------------------
//  Type and Structure
//--------------------------------------------------------------------------------------------------
struct COMMAND_ARRAY_FORMAT 
{
  MS_U8   operation;
  MS_U32  destionation_address;  // 寫入的register位置
  MS_U16  destionation_value;    // 寫入register 數值
  MS_U16  mask;                   //  mask數值
     
};
typedef struct COMMAND_ARRAY_FORMAT CAF_Struct;
typedef CAF_Struct *CAF_Struct_Pointer;

struct CMDQ_HEAD
{
   MS_U16 Command_Number;
   MS_U32 Ticket_Number;
   CAF_Struct_Pointer Pointer_To_CAFArray;
  
};
typedef struct CMDQ_HEAD CH_Struct;
typedef CH_Struct *CH_Struct_Pointer;


/// CMDQ DDI return value
typedef MS_U32                         DRVCMDQ_RESULT;

/// @name DRVCMDQ_RESULT
/// @ref DRVCMDQ_RESULT
/// return value
/// @{
#define DRVCMDQ_OK                   0x00000000
#define DRVCMDQ_FAIL                 0x00000001
#define DRVCMDQ_INVALID_PARAM        0x00000002
#define DRVCMDQ_FUNC_ERROR           0x00000003
#define DRVCMDQ_MIU_ADDR_ERROR       0x00000004
#define DRVCMDQ_CMDQ_MEMORY_FULL     0x00000005
#define DRVCMDQ_CMDQ_BUSY            0x00000006
#define DRVCMDQ_CMDQ_TICKET_FAIL     0x00000007

/// @}

#define CMDQ_DMA_DONE                     0x00010000
#define CMDQ_DMA_PAUSE                    0x00020000
#define CMDQ_STATES_GROUP                 (CMDQ_DMA_DONE  | \
                                             CMDQ_DMA_PAUSE  )

/// CMDQ notification function


//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------
DRVCMDQ_RESULT MDrv_CMDQ_Init(void);
DRVCMDQ_RESULT MDrv_CMDQ_GetLibVer(const MSIF_Version **ppVersion);
DRVCMDQ_RESULT MDrv_CMDQ_Start(MS_BOOL bStart);
DRVCMDQ_RESULT MDrv_CMDQ_Get_Memory_Size(MS_U32 SmallAddr, MS_U32 BigAddr);
DRVCMDQ_RESULT MDrv_CMDQ_Set_Buffer(MS_U32 StartAddr, MS_U32 EndAddr);
DRVCMDQ_RESULT MDrv_CMDQ_Set_Start_Pointer(MS_U32 StartAddr);
DRVCMDQ_RESULT MDrv_CMDQ_Set_End_Pointer(MS_U32 EndAddr);
DRVCMDQ_RESULT MDrv_CMDQ_Reset(void);
DRVCMDQ_RESULT MDrv_CMDQ_Exit(void);
DRVCMDQ_RESULT MDrv_CMDQ_Stop(void);
DRVCMDQ_RESULT MDrv_CMDQ_Set_Mode(MS_BOOL BModeSel);
DRVCMDQ_RESULT MDrv_CMDQ_Isr(void);
DRVCMDQ_RESULT MDrv_CMDQ_SetDbgLevel(DrvCMDQ_DbgLevel DbgLevel);
MS_BOOL MDrv_CMDQ_Calculate_Memory_Space(int Command_number);
MS_U32 MDrv_CMDQ_Apply_Use_Ticket(MS_U32 Admission_Number, MS_U32 Flag);
DRVCMDQ_RESULT MDrv_CMDQ_Receive(CH_Struct_Pointer New_IP_Head);
void MDrv_CMDQ_Transfer(CAF_Struct_Pointer Array_Command, int Number_Array_Command);
void MDrv_CMDQ_Set_Queue_NULL_And_Polling(int next_reg_value,int bit_place,int Null_number);
void MDrv_CMDQ_Set_Queue_Memory_StartAddress(MS_U32 StartAddr);
void MDrv_CMDQ_Set_Queue_Memory_EndAddress(MS_U32 EndAddr);
void MDrv_CMDQ_Set_dummy_Address(MS_U32 dummyAddr);
DRVCMDQ_RESULT MDrv_CMDQ_Set_timer_ratio(MS_U32 time,MS_U32 ratio);
DRVCMDQ_RESULT MDrv_CMDQ_Printf_Crash_Command(void);

#ifdef __cplusplus
}
#endif


#endif // _DRVCMDQ_H_
