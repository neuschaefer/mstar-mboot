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
/// @file   drvDscmb.h
/// @brief  Descrambler (Dscmb) Driver Interface
/// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_DSCMB_H__
#define __DRV_DSCMB_H__

#include "MsTypes.h"
#include "MsCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MSIF_DSMB_LIB_CODE              {'D','S','M','B'}    //Lib code
#define MSIF_DSMB_LIBVER                {'0','2'}            //LIB version
#define MSIF_DSMB_BUILDNUM              {'1','8'}            //Build Number
#define MSIF_DSMB_CHANGELIST            {'0','0','5','6','5','9','8','0'} //P4 ChangeList Number

#define DSCMB_DRV_VERSION               /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DSMB_LIB_CODE,                 /* IP__                                             */  \
    MSIF_DSMB_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_DSMB_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_DSMB_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS


#define DSCMB_ASSERT_AND_RETURN(x)             if (!(x)){printf ("ASSERT FAIL: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__); return FALSE;}
#define DSCMB_ASSERT_NO_RETURN(x)             if (!(x)){printf ("ASSERT FAIL: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);}

#define DSCMB_LIB_TIME_MAX          16      ///< Maximum length of time
#define DSCMB_LIB_DATE_MAX          16      ///< Maximum length of date

typedef struct
{
    MS_U8   Time[DSCMB_LIB_TIME_MAX];       ///< Library Built Time
    MS_U8   Date[DSCMB_LIB_DATE_MAX];       ///< Library Built Date
} DSCMB_Info;

typedef struct
{
    MS_U32 u32Status;
} DSCMB_Status;

/// Descrambler null filter ID
#define DRV_DSCMB_FLT_NULL          0xFFFFFFFF

typedef enum
{
    /// Descrambler Slot Type :
    E_SLOT_TYPE_NORMAL = 0,  // Normal
    E_SLOT_TYPE_SHARE,       // Share
} DSCMB_SLOT_Type;

typedef enum
{
    E_DSCMB_FLT_3_KEYS        = 0x00000000, // Odd, Even, and Clear Key
    E_DSCMB_FLT_2_KEYS        = 0x00000001, // Odd and Even Key
    E_DSCMB_FLT_2_KEYS_SHARE  = 0x00000002, // Odd and Even Key (share key)
} DSCMB_Flt_Type;

/// Descrambler algorithm type
typedef enum
{
    /// Descrambler algorithm : CSA
    E_DSCMB_TYPE_CSA = 0,    // CSA
    /// Descrambler algorithm : NSA as ESA
    E_DSCMB_TYPE_NSA_AS_ESA, // NSA as ESA
    /// Descrambler algorithm : CI+ DES
    E_DSCMB_TYPE_DES,        // CI+ DES
    /// Descrambler algorithm : CI+ AES
    E_DSCMB_TYPE_AES,        // CI+ AES
    // E_DSCMB_TYPE_ESA,       // ESA
    // E_DSCMB_TYPE_NSAS,      // NSAS
    E_DSCMB_TYPE_AES_ECB,
    E_DSCMB_TYPE_AES_SCTE52,  // Descrambler algorithm : DBook, AES+CBC, S8 new, not support for all chips
    E_DSCMB_TYPE_AES_CTR,     // AES Counter mode
    E_DSCMB_TYPE_TDES_ECB,
    E_DSCMB_TYPE_TDES_SCTE52,

    // Synamedia AES
    E_DSCMB_TYPE_SYN_AES,    // AES Leading CLR EBC

    E_DSCMB_TYPE_MULTI2,    // Multi2

    /// Descrambler algorithm : CSA3
    E_DSCMB_TYPE_CSA3,    // CSA3

    /// Descrambler algorithm : CSA conformance mode
    E_DSCMB_TYPE_CSA_CONF,    // CSA conformance mode

    E_DSCMB_TYPE_OC,    // Open Cable
} DSCMB_Type;

/// Descrambler key type
typedef enum
{
    /// Descrambler key type : clear
    E_DSCMB_KEY_CLEAR = 0,
    /// Descrambler key type : even
    E_DSCMB_KEY_EVEN,
    /// Descrambler key type : odd
    E_DSCMB_KEY_ODD,
} DSCMB_Key_Type;

/// Scramble level
typedef enum
{
    /// Descrambler level : none
    E_DSCMB_NONE                    =   0x00000000,
    /// Descrambler level : TS level
    E_DSCMB_TS                      =   0x00000001,
    /// Descrambler level : PES level
    E_DSCMB_PES                     =   0x00000002,
    /// Descrambler level : TS and PES level
    E_DSCMB_TS_PES                  =   (E_DSCMB_TS | E_DSCMB_PES),
} SCMB_Level;

// Descrambler Engine Type //
typedef enum
{
    E_DSCMB_ENG_LSAS = 0x1,
    E_DSCMB_ENG_ESA  = 0x2,
    E_DSCMB_ENG_LSAD = 0x4,
} DSCMB_Eng_Type;

/// Key ladder input source
typedef enum
{
    /// Key ladder source from ACPU/SCPU
    E_DSCMB_KL_SRC_ACPU             =   0,
    /// Key ladder source from SECRET_1
    E_DSCMB_KL_SRC_SECRET_1         =   1,
    /// Key ladder source from SECRET_2
    E_DSCMB_KL_SRC_SECRET_2         =   2,
    /// Key ladder source from SECRET_3
    E_DSCMB_KL_SRC_SECRET_3         =   3,
    /// Key ladder source from SECRET_4
    E_DSCMB_KL_SRC_SECRET_4         =   4,
    /// Key ladder source from SECRET_5
    E_DSCMB_KL_SRC_SECRET_5         =   5,
    /// Key ladder source from SECRET_6
    E_DSCMB_KL_SRC_SECRET_6         =   6,
    /// Key ladder source from SECRET_7
    E_DSCMB_KL_SRC_SECRET_7         =   7,
    /// Key ladder source from SECRET_8
    E_DSCMB_KL_SRC_SECRET_8         =   8,

    /// Key ladder source from Private_0
    E_DSCMB_KL_SRC_PRIVATE_0        =   5,
    /// Key ladder source from Private_1
    E_DSCMB_KL_SRC_PRIVATE_1        =   6,
    /// Key ladder source from Private_2
    E_DSCMB_KL_SRC_PRIVATE_2        =   7,
    /// Key ladder source from Private_3
    E_DSCMB_KL_SRC_PRIVATE_3        =   8,

    /// Key ladder source from VGK
    E_DSCMB_KL_SRC_VGK              =   9,
} DSCMB_KLSrc;

/// Key ladder output destination
typedef enum
{
    E_DSCMB_KL_DST_ACPU             =   0x1,
    E_DSCMB_KL_DST_KT_NSA           =   0x3,
    E_DSCMB_KL_DST_DMA_AES          =   0x4,
    E_DSCMB_KL_DST_DMA_TDES         =   0x5,
    E_DSCMB_KL_DST_PRIVATE0         =   0x6,
    E_DSCMB_KL_DST_PRIVATE1         =   0x7,
    E_DSCMB_KL_DST_PRIVATE2         =   0x8,


    /// Key ladder destination to ACPU
    E_DSCMB_KL_DST_CPU_ACPU         =   0x00000080,
    /// Key ladder destination to Secure CPU
    E_DSCMB_KL_DST_CPU_SCPU         =   0x00000081,
    /// Key ladder destination to DSCMB (KeyTable)
    E_DSCMB_KL_DST_KT_LSAD          =   0x00008000,
    E_DSCMB_KL_DST_KT_ESA           =   0x00008100,
    E_DSCMB_KL_DST_KT_LSAS          =   0x00008200,
    /// Key ladder destination to DMA
    E_DSCMB_KL_DST_DMA_SK0         =    0x00800000,
    E_DSCMB_KL_DST_DMA_SK1         =    0x00810000,
    E_DSCMB_KL_DST_DMA_SK2         =    0x00820000,
    E_DSCMB_KL_DST_DMA_SPS0        =    0x00880000 ,
    E_DSCMB_KL_DST_DMA_SPS1        =    0x00890000 ,
    E_DSCMB_KL_DST_DMA_SPS2        =    0x008A0000 ,
    E_DSCMB_KL_DST_DMA_SPS3        =    0x008B0000 ,
    E_DSCMB_KL_DST_DMA_SPD0        =    0x008C0000 ,
    E_DSCMB_KL_DST_DMA_SPD1        =    0x008D0000 ,
    E_DSCMB_KL_DST_DMA_SPD2        =    0x008E0000 ,
    E_DSCMB_KL_DST_DMA_SPD3        =    0x008F0000 ,
    /// Key ladder destination to PRIVATE KEY
    E_DSCMB_KL_DST_PRIVATE_0       =    0x81000000   ,
    E_DSCMB_KL_DST_PRIVATE_1       =    0x82000000   ,
    E_DSCMB_KL_DST_PRIVATE_2       =    0x83000000   ,
    E_DSCMB_KL_DST_PRIVATE_3       =    0x84000000   ,
} DSCMB_KLDst;

typedef enum
{
    // descrambler engine
    E_DSCMB_CAP_ENGINE_NUM,
    // descrambler slot
    E_DSCMB_CAP_FLT_NUM,
    // descrambler type supported
    E_DSCMB_CAP_SUPPORT_ALGORITHM,
    // descrambler key type supported
    E_DSCMB_CAP_SUPPORT_KEY_TYPE,
    // descrambler mapping, start tsp pid filter
    E_DSCMB_CAP_PIDFILTER_MAP_START,
    // descrambler mapping, end tsp pid filter
    E_DSCMB_CAP_PIDFILTER_MAP_END,
    // share key slot max number
    E_DSCMB_CAP_SHARE_KEY_SLOT_MAX_NUM,
    // share key region number
    E_DSCMB_CAP_SHARE_KEY_REGION_NUM,
    // share key region start
    E_DSCMB_CAP_SHARE_KEY_REGION_START,
    // share key region end
    E_DSCMB_CAP_SHARE_KEY_REGION_END,
} DSCMB_Query_Type;

typedef enum
{
    E_DSCMB_KL_TDES                 =   0x00000000,
    E_DSCMB_KL_AES                  =   0x0000003F,
} DSCMB_KLEng;

typedef enum
{
    E_DSCMB_KL_SEL_DEFAULT = 0, //Backward compatible, actual default value is chosen in HAL driver
    E_DSCMB_KL_SEL_CW      , //CWKL
    E_DSCMB_KL_SEL_PVR     , //PVRKL
} DSCMB_KL_SelEng;

/// Key ladder configurations
typedef enum
{
    E_DSCMB_KL_LVL_0 = 0,
    E_DSCMB_KL_LVL_1 ,
    E_DSCMB_KL_LVL_2 ,
    E_DSCMB_KL_LVL_3 ,
    E_DSCMB_KL_LVL_9 = 9 ,
    E_DSCMB_KL_LVL_D = 0xD ,
} DSCMB_KLType;

typedef enum
{
    E_DSCMB_KL_128_BITS   ,
    E_DSCMB_KL_64_BITS  ,
} DSCMB_KL_OutputSize;

/// Key ladder configurations
typedef struct
{
    MS_BOOL         bDecrypt;
    MS_BOOL         bInverse;
    MS_BOOL         bKeepRound;
    MS_U32          u32Round;
    MS_U32          u32EngMode;
    DSCMB_KLType         eKLType;
    DSCMB_KL_OutputSize  eOutsize;

} DSCMB_KLCfg;


///New  Key ladder configurations for Keyladder run all.
typedef struct
{
    DSCMB_KLEng          eAlgo;
    DSCMB_KLSrc          eSrc;   // Select KL root key source //
    DSCMB_KLDst          eDst;   // Select KL output Key destination //
    DSCMB_KL_OutputSize  eOutsize;  // Select ouput Key size. ex: Key size of CSA and DES are E_DSCMB_KL_64_BITS//
    DSCMB_Key_Type       eKeyType;
    // Key ladder running level, support level 0 ~ 3 // [NOTE] Level 0 is only supported when destination is CryptoDMA
    MS_U32               u32Level;
    MS_U32               u32EngID;  // Select ESA/NSA as KL destination, Dscmb engine ID //
    MS_U32               u32DscID;  // Select ESA/NSA as KL destination, Dscmb ID //
    MS_U8                *u8KeyACPU;  // Select ACPU as KL root Key, KL root key //
    // KL inputs, pointer of bytes array for each level input, every input contains 16 bytes //
    // ex: MS_U8 input[48]: input[0-15] Level1 , input[16-31] Level2, input[32-47] Level3
    MS_U8                *pu8KeyKLIn;
    MS_BOOL              bDecrypt;
    MS_BOOL              bInverse;

    // New data member
    DSCMB_KL_SelEng      eKLSel;   //Select KeyLadder
    MS_U32               u32CAVid; //Set CAVid

    //TODO: Add Key property
} DSCMB_KLCfg_All;


typedef enum
{
    E_DSCMB_MAIN_ALGO_AES       ,
    E_DSCMB_MAIN_ALGO_CSA2      ,
    E_DSCMB_MAIN_ALGO_DES       ,
    E_DSCMB_MAIN_ALGO_TDES      ,
    E_DSCMB_MAIN_ALGO_MULTI2    ,
    E_DSCMB_MAIN_ALGO_CSA2_CONF ,
    E_DSCMB_MAIN_ALGO_CSA3      ,
    E_DSCMB_MAIN_ALGO_DEFAULT = 0xF,
    E_DSCMB_MAIN_ALGO_NUM,
} DSCMB_MainAlgo_Type;


typedef enum
{
    E_DSCMB_SUB_ALGO_NONE = 0   ,
    E_DSCMB_SUB_ALGO_MDI_CBC = 0,
    E_DSCMB_SUB_ALGO_MDI_RCBC  ,
    E_DSCMB_SUB_ALGO_MDD_CBC   ,
    E_DSCMB_SUB_ALGO_MDD_RCBC  ,
    E_DSCMB_SUB_ALGO_LEADING_CLEAR ,
    E_DSCMB_SUB_ALGO_ECB ,
    E_DSCMB_SUB_ALGO_CBC ,
    E_DSCMB_SUB_ALGO_CTR ,
    E_DSCMB_SUB_ALGO_OFB ,
    E_DSCMB_SUB_ALGO_DEFAULT = 0xF,
    E_DSCMB_SUB_ALGO_NUM,
} DSCMB_SubAlgo_Type;


typedef enum
{
    E_DSCMB_RESSB_ALGO_NONE = 0,
    E_DSCMB_RESSB_ALGO_CLR = 0,
    E_DSCMB_RESSB_ALGO_CTS,
    E_DSCMB_RESSB_ALGO_SCTE52,
    E_DSCMB_RESSB_ALGO_XORIV1,
    E_DSCMB_RESSB_ALGO_OC_M,
    E_DSCMB_RESSB_ALGO_XORIV2,
    E_DSCMB_RESSB_ALGO_DEFAULT = 0x7,
    E_DSCMB_RESSB_ALGO_NUM,
} DSCMB_ResSBAlgo_Type;


typedef struct
{
    DSCMB_MainAlgo_Type   eMainAlgo;
    DSCMB_SubAlgo_Type    eSubAlgo;
    DSCMB_ResSBAlgo_Type  eResAlgo;
    DSCMB_ResSBAlgo_Type  eSBAlgo;
    MS_BOOL               bDecrypt;
} DSCMB_Algo_Cfg;

// Error Status for KL //s
#define DSCMB_KL_Status MS_U32

#define    KL_STATUS_KEY_OK                            0x0000
#define    KL_STATUS_ACPU_KEY_NULL                     0x0001
#define    KL_STATUS_ACPU_OUTKEY_NULL                  0x0002
#define    KL_STATUS_INVALID_KEYROUND_PARAMETER        0x0004
#define    KL_STATUS_INVALID_INPUT_LEVEL               0x0008
#define    KL_STATUS_IVALID_DSCMB_ID                   0x0010
#define    KL_STATUS_WAIT_CW_READY_TIMEOUT             0x0020
#define    KL_STATUS_WAIT_KL_READY_TIMEOUT             0x0040
#define    KL_STATUS_KL_INPUT_NULL                     0x0080

#define    KL_STATUS_BAD_KEY                           0x0100
#define    KL_STATUS_INVALID_FUNCTION                  0x0200
#define    KL_STATUS_MULTI_FUNCTION                    0x0400
#define    KL_STATUS_ZERO_ORDER                        0x0800
#define    KL_STATUS_INTERNAL_BAD_KEY                  0x1000
#define    KL_STATUS_INVALID_KL_SEL                    0x2000



// Backward compatible
typedef DSCMB_KLSrc          DSCMB_KLadderSrc;
#define E_DSCMB_KLAD_SRC_ACPU               E_DSCMB_KL_SRC_ACPU
#define E_DSCMB_KLAD_SRC_SECRET_KEY1        E_DSCMB_KL_SRC_SECRET_1
#define E_DSCMB_KLAD_SRC_SECRET_KEY2        E_DSCMB_KL_SRC_SECRET_2
#define E_DSCMB_KLAD_SRC_SECRET_KEY3        E_DSCMB_KL_SRC_SECRET_3
#define E_DSCMB_KLAD_SRC_SECRET_KEY4        E_DSCMB_KL_SRC_SECRET_4
#define E_DSCMB_KLAD_SRC_VGK                E_DSCMB_KL_SRC_VGK

typedef DSCMB_KLDst          DSCMB_KLadderDst;
#define E_DSCMB_KLAD_DST_KTAB_ESA           E_DSCMB_KL_DST_KT_ESA
#define E_DSCMB_KLAD_DST_KTAB_NSA =         E_DSCMB_KL_DST_KT_NSA
#define E_DSCMB_KLAD_DST_AESDMA_AES =       E_DSCMB_KL_DST_DMA_AES
#define E_DSCMB_KLAD_DST_AESDMA_TDES =      E_DSCMB_KL_DST_DMA_TDES
#define E_DSCMB_KLAD_DST_ACPU =             E_DSCMB_KL_DST_ACPU

typedef DSCMB_KLCfg          DSCMB_KLadderConfig;


typedef enum
{
    DSCMB_FSCB_UNCHG = 0,
    DSCMB_FSCB_CLEAR,
    DSCMB_FSCB_EVEN,
    DSCMB_FSCB_ODD,
} DSCMB_FSCB;

// wrapper function
#define MDrv_DSCMB_FltAlloc(void)   \
    MDrv_DSCMB2_FltAlloc(0)
#define MDrv_DSCMB_FltAlloc_Ex(eFltType)   \
    MDrv_DSCMB2_FltAlloc_Ex(0, eFltType)
#define MDrv_DSCMB_FltFree(u32DscmbId)   \
    MDrv_DSCMB2_FltFree(0, u32DscmbId)
#define MDrv_DSCMB_FltConnectPid(u32DscmbId, u32Pid)  \
    MDrv_DSCMB2_FltConnectPid(0, u32DscmbId, u32Pid)
#define MDrv_DSCMB_FltDisconnectPid(u32DscmbId, u32Pid) \
    MDrv_DSCMB2_FltDisconnectPid(0, u32DscmbId, u32Pid)
#define MDrv_DSCMB_FltConnectFltId(u32DscmbId, u32FltId)    \
    MDrv_DSCMB2_FltConnectFltId(0, u32DscmbId, u32FltId)
#define MDrv_DSCMB_FltDisconnectPid_Ex(u32DscmbId, u32Pid) \
    MDrv_DSCMB2_FltDisconnectPid_Ex(0, u32DscmbId, u32Pid)
#define MDrv_DSCMB_FltDisconnectFltId(u32DscmbId, u32FltId)    \
    MDrv_DSCMB2_FltDisconnectFltId(0, u32DscmbId, u32FltId)
#define MDrv_DSCMB_FltDscmb(u32DscmbId, bDscmb) \
    MDrv_DSCMB2_FltDscmb(0, u32DscmbId, bDscmb)
#define MDrv_DSCMB_FltTypeSet(u32DscmbId, eType)    \
    MDrv_DSCMB2_FltTypeSet(0, u32DscmbId, eType)
#define MDrv_DSCMB_Multi2_SetRound(u32Round)    \
    MDrv_DSCMB2_Multi2_SetRound(0, u32Round)
#define MDrv_DSCMB_Multi2_SetSystemKey(u8Syskey)    \
    MDrv_DSCMB2_Multi2_SetSystemKey(0, u8Syskey)
#define MDrv_DSCMB_FltKeySet(u32DscmbId, eKeyType, pu8Key)  \
    MDrv_DSCMB2_FltKeySet(0, u32DscmbId, eKeyType, pu8Key)
#define MDrv_DSCMB_FltKeyReset(u32DscmbId, eKeyType)    \
    MDrv_DSCMB2_FltKeyReset(0, u32DscmbId, eKeyType)
#define MDrv_DSCMB_FltIVSet(u32DscmbId, eKeyType, pu8IV)    \
    MDrv_DSCMB2_FltIVSet(0, u32DscmbId, eKeyType, pu8IV)
#define MDrv_DSCMB_PidFlt_ScmbStatus(u32PidFltId, pScmbLevel)    \
    MDrv_DSCMB2_PidFlt_ScmbStatus(0, u32PidFltId, pScmbLevel)
#define MDrv_DSCMB_FltKeyReset(u32DscmbId, eKeyType)    \
    MDrv_DSCMB2_FltKeyReset(0, u32DscmbId, eKeyType)

//--------------------------------- --------------//
//--------------------DSCMB API -----------------//
//--------------------------------- --------------//

// descrambler initial function
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Init(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Exit(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_SetDefaultCAVid(MS_U32 u32EngId, MS_U32 u32CAVid);

// descrambler filter management
DLL_PUBLIC MS_U32  MDrv_DSCMB2_FltAlloc(MS_U32 u32EngId);
DLL_PUBLIC MS_U32  MDrv_DSCMB2_FltAlloc_Ex(MS_U32 u32EngId, DSCMB_Flt_Type eFltType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltFree(MS_U32 u32EngId, MS_U32 u32DscmbId);

// descrambler filter maps to TSP filter id
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltConnectFltId(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32FltId);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDisconnectFltId(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32FltId);

// descrambler filter maps to TSP pid
#ifndef MSOS_TYPE_NUTTX
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltConnectPid(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDisconnectPid(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDisconnectPid_Ex(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);
#endif

// Advanced descrambler settings with different engines.
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_EngSetAlgo(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Eng_Type eEngType, DSCMB_Algo_Cfg stConfig);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_EngSetKey(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Eng_Type eEngType, DSCMB_Key_Type eKeyType, MS_U8* pu8Key);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_EngResetKey(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Eng_Type eEngType, DSCMB_Key_Type eKeyType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_EngSetIV(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8IV);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_EngSetSwitch(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Eng_Type eUppSwitch, DSCMB_Eng_Type eLowSwitch);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_EngSetFSCB(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_FSCB eForceSCB );


// Set descrambler filter as scrambling/decrambling mode
// Default filter mode is descrambling if this function is not specified
// This function should be invoked before MDrv_DSCMB_FltTypeSet
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDscmb(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_BOOL bDscmb);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltTypeSet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Type DscmbType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltKeySet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8Key);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltKeyReset(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltIVSet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8IV);

// descrambler query function
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_GetCap(MS_U32 u32EngId, DSCMB_Query_Type eQueryType, void* pInput, void* pOutput);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_GetLibVer(const MSIF_Version **ppVersion);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_SetDBGLevel(MS_U32 u32Level);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_GetConnectStatus(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32TspFltId);


// descrambler altorithm related
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Multi2_SetRound(MS_U32 u32EngId, MS_U32 u32Round);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Multi2_SetSystemKey(MS_U32 u32EngId, MS_U8* u8Syskey);
//HDCP2
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_HDCP2_SetRIV(MS_U32 u32EngId, MS_U8* pu8RIV);

DLL_PUBLIC MS_BOOL MDrv_DSCMB2_PVR_RecCtrl(MS_U32 u32EngId, MS_BOOL Enable);
DLL_PUBLIC MS_U32  MDrv_DSCMB2_SetPowerState(EN_POWER_MODE u16PowerState);

// scramble status
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_PidFlt_ScmbStatus(MS_U32 u32EngId, MS_U32 u32PidFltId, SCMB_Level* pScmbLevel);

// Get TspFltid and DscmbId Status
DLL_PUBLIC MS_BOOL MDrv_DSCMB_GetStatus(DSCMB_Status *pStatus);
DLL_PUBLIC const DSCMB_Info* MDrv_DSCMB_GetInfo(void);


//--------------------------------- --------------//
//--------------------Keyladder API -----------------//
//--------------------------------- --------------//
// New Key Ladder API. Group all old key ladder APIs into one.
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_KLadder_ETSI(DSCMB_KLCfg_All* KLCfg , MS_U8 *ACPU_Out, MS_U8 *pu8Nonce, MS_U8 * pu8Response, DSCMB_KL_Status* u32Status );
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_KLadder_AtomicExec(DSCMB_KLCfg_All* KLCfg , MS_U8 *ACPU_Out, DSCMB_KL_Status* u32Status );


//--------------------------------- --------------//
//--------------------Depreted API -----------------//
//--------------------------------- --------------//
DLL_PUBLIC MS_BOOL MDrv_DSCMB_Init(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_Exit(void);

DLL_PUBLIC MS_BOOL MDrv_DSCMB_GetLibVer(const MSIF_Version **ppVersion);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_SetDBGLevel(MS_U32 u32Level);

DLL_PUBLIC MS_BOOL MDrv_DSCMB_GetConnectStatus(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32TspFltId);

DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_AtomicExec(DSCMB_KLCfg_All* KLCfg , MS_U8 *ACPU_Out, DSCMB_KL_Status* u32Status);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Reset(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_SetInput(MS_U32 u32Level, MS_U8* pu8In, MS_U32 u32InLen);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_SetKey(DSCMB_KLSrc KLSrc, MS_U8* pu8Key, MS_U32 u32KeyLen);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_SetDst(DSCMB_KLDst KLDst);
DLL_PUBLIC void    MDrv_DSCMB_KLadder_SetConfig(DSCMB_KLCfg *KLCfg);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Start(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_IsComplete(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Output_Start(MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Output_IsComplete(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Output_Stop(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_ResetAcpuAck(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_ReadDataFromAcpu(MS_U8* pu8Out);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Stop(void); // write KTE
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Lock(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Unlock(void);

DLL_PUBLIC MS_BOOL MDrv_DSCMB_2ndarySet(MS_U32 u32PidPrim, MS_U32 u32Pid2ndary);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_2ndaryReset(MS_U32 u32PidPrim);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_SlotSwitchWrite(MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U32 u32SW0, MS_U32 u32SW1, MS_U32 u32SW2);

DLL_PUBLIC MS_BOOL MDrv_DSCMB2_SetRecBuf(MS_U32 u32EngId , MS_U32 u32Start, MS_U32 u32Size);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_RecCtrl(MS_U32 u32EngId, MS_BOOL bEnable);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_GetRecWptr(MS_U32 u32EngId, MS_U32* pu32Write);

DLL_PUBLIC MS_U32  MApi_DSCMB_SetPowerState(EN_POWER_MODE u16PowerState);


#ifdef __cplusplus
}
#endif

#endif
