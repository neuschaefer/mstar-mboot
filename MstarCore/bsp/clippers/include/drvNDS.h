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
/// @file   drvNDS.h
/// @brief  NDS Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_NDS_H_
#define _DRV_NDS_H_


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
#define NDS_ENFLAGS_CTRL_ENC_SUPPORTED  0x01
#define NDS_ENFLAGS_CTRL_ENC_HW_FORCED  0x02    // permanently
#define NDS_ENFLAGS_CTRL_ENC_SW_FORCED  0x04    // force until reset
#define NDS_ENFLAGS_JTAG_PWD            0x08
#define NDS_ENFLAGS_BOOTROM             0x10
#define NDS_ENFLAGS_DATA_ENC            0x20
#define NDS_ENFLAGS_GETRESP2CHALLENGE   0x40


// Predefined by NDS
// ref. icq063
#define NDS_KTE_ESA_SEL_AES             0x0
#define NDS_KTE_ESA_SEL_CSA             0x1
#define NDS_KTE_ESA_SEL_DES             0x2
#define NDS_KTE_ESA_SEL_TDES            0x3
#define NDS_KTE_ESA_SEL_MULTI2          0x4
#define NDS_KTE_ESA_SEL_DFAST           0x5
#define NDS_KTE_ESA_SEL_USER            0xF

#define NDS_KTE_ESA_SUB_ECB             0x0
#define NDS_KTE_ESA_SUB_CBC             0x1
#define NDS_KTE_ESA_SUB_NSA             0x7



//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_NDS_OK,
    E_NDS_FAIL,

} NDS_Result;


typedef enum
{
    E_NDS_SC_EVENT_CARD_REMOVED     =   0x00000000,
    E_NDS_SC_EVENT_CARD_INSERTED    =   0x00000001,

} NDS_SC_Event;


typedef enum
{
    E_NDS_SC_CLK_27M_D6,
    E_NDS_SC_CLK_27M_D2,
    E_NDS_SC_CLK_27M_D4,
    E_NDS_SC_CLK_27M_D8,

} NDS_SC_Clk;


typedef enum
{
    E_NDS_SC_BAUD_RATE_9600,
    E_NDS_SC_BAUD_RATE_19200,
    E_NDS_SC_BAUD_RATE_38400,
    E_NDS_SC_BAUD_RATE_76800,
    E_NDS_SC_BAUD_RATE_153600,
    E_NDS_SC_BAUD_RATE_223200,
} NDS_SC_BaudRate;


typedef enum
{
    E_NDS_CAP_ECM_NUM               =   0x00,

    E_NDS_CAP_EMM_NUM               =   0x10,

    E_NDS_CAP_BUF_PITCH             =   0x20,
    E_NDS_CAP_BUF_ALIGN,
    E_NDS_CAP_BUF_TOTALSIZE,
    E_NDS_CAP_RASP_BUF_TOTALSIZE,

} NDS_Caps;


typedef MS_BOOL                     (*P_NDS_SC_CbSetVcc)(MS_BOOL b5V);
typedef void                        (*P_NDS_SC_CbEvent)(NDS_SC_Event event);

typedef struct _NDS_SC_Param
{
    P_NDS_SC_CbSetVcc               cbSetVcc;

    P_NDS_SC_CbEvent                cbEvent;                            // for HDI certification
    MS_BOOL                         bCommDump;                          // for card debugging // @TODO: remove

} NDS_SC_Param;


typedef struct _NDS_FLT_Param
{
    MS_PHYADDR                      ecm_emm_addr;                       // NDS_CAP_BUF_SIZE*(NDS_CAP_ECM_NUM+NDS_CAP_EMM_NUM) at least
                                                                        // NDS_CAP_BUF_ALIGN aligned
    MS_U8*                          pu8ecm_emm_buf;                     // virtual address of ecm_emm_addr
    MS_U32                          ecm_emm_size;                       // total buffer size from emm_ecm_addr
} NDS_FLT_Param;

typedef struct _NDS_RASP_Param
{
    MS_PHYADDR                      ecm_addr;                       // NDS_CAP_BUF_SIZE * NDS_CAP_ECM_NUM
    MS_U8                          *pu8ecm_buf;                     // virtual address of ecm address
    MS_U32                          ecm_size;                       // total buffer size from emm_ecm_addr

    MS_PHYADDR                      payload_addr;                   // NDS_CAP_BUF_SIZE * NDS_CAP_ECM_NUM
    MS_U8                          *pu8playload_buf;                // virtual address of ecm address
    MS_U32                          payload_size;                   // total buffer size from emm_ecm_addr

} NDS_RASP_Param;

typedef struct _NDS_Param
{
    NDS_FLT_Param                   flt;
    NDS_SC_Param                    sc;
    NDS_RASP_Param                  rasp;
} NDS_Param;


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

NDS_Result                          MDrv_NDS_Init(NDS_Param *param);
NDS_Result                          MDrv_NDS_Exit(void);
NDS_Result                          MDrv_NDS_PowerOff(void);
NDS_Result                          MDrv_NDS_SetMagicValue(MS_U8 idx, MS_U16 word_0, MS_U16 word_1, MS_U16 word_2, MS_U16 word_3);
MS_U32                              MDrv_NDS_GetCaps(NDS_Caps cap);

NDS_Result                          MDrv_NDS_NSK_Open(MS_U32 nsk_id);
NDS_Result                          MDrv_NDS_NSK_Close(MS_U32 nsk_id);


#ifdef __cplusplus
}
#endif

#endif // _DRV_NDS_H_

