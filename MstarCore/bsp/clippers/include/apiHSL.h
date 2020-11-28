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
/**************************************************************************
 * Copyright (c) 2008 MStar Semiconductor, Inc. All Rights Reserved.
 **************************************************************************/
/** \file
 * \brief This is the low-level drivers header file for the FrHsl module.
 *
 */


/*!!!!!!!!!!!: MUST include this file after stdio.h because we use our own "printf" definition*/
#if defined (MSOS_TYPE_LINUX)
#ifndef FRHSL_H
#define FRHSL_H

/*******************************************************************************
** Includes
*******************************************************************************/

#include "MsTypes.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define HSL_TCPIP                   true


// max. number of ID
#define HSL_GROUP_MAX               1024    // group id
#define HSL_LOG_ID_MAX              1024    // log id
#define DEFAULT_GROUP               HSL_DBG_SN_ALL_DEBUG  // To support default group filtering inserted by silox.exe when none are specified.

// Group ID for all modules
// utopia
#define HSL_DBG_UTOPIA_ALL_DEBUG    (GROUP_MODULE_UTOPIA_ALL<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_UTOPIA_ALL_INFO     (GROUP_MODULE_UTOPIA_ALL<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_UTOPIA_GOP_DEBUG    (GROUP_MODULE_UTOPIA_GOP<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_UTOPIA_GOP_INFO     (GROUP_MODULE_UTOPIA_GOP<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_UTOPIA_GE_DEBUG     (GROUP_MODULE_UTOPIA_GE<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_UTOPIA_GE_INFO      (GROUP_MODULE_UTOPIA_GE<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_UTOPIA_HSL_DEBUG     (GROUP_MODULE_UTOPIA_HSL<<2 | GROUP_LEVEL_DEBUG)
//¡K

// middleware
#define HSL_DBG_MW_ALL_DEBUG        (GROUP_MODULE_MW_ALL<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_MW_ALL_INFO         (GROUP_MODULE_MW_ALL<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_MW_PGS_DEBUG        (GROUP_MODULE_MW_PGS<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_MW_PGS_INFO         (GROUP_MODULE_MW_PGS<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_MW_MHEG5_DEBUG      (GROUP_MODULE_MW_MHEG5<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_MW_MHEG5_INFO       (GROUP_MODULE_MW_MHEG5<<2 | GROUP_LEVEL_INFO)
//¡K

// supernova
#define HSL_DBG_SN_ALL_DEBUG        (GROUP_MODULE_SN_ALL<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_SN_ALL_INFO         (GROUP_MODULE_SN_ALL<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_SN_MUF_DEBUG        (GROUP_MODULE_SN_MUF<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_SN_MUF_INFO         (GROUP_MODULE_SN_MUF<<2 | GROUP_LEVEL_INFO)
#define HSL_DBG_SN_AUTO_TEST_DEBUG  (GROUP_MODULE_SN_AUTO_TEST<<2 | GROUP_LEVEL_DEBUG)
#define HSL_DBG_SN_AUTO_TEST_INFO   (GROUP_MODULE_SN_AUTO_TEST<<2 | GROUP_LEVEL_INFO)

#define HSL_DBG_SN_PROFILING        (GROUP_MODULE_SN_ALL<<2 | GROUP_LEVEL_DEBUG)
//¡K

#define HSL_GROUP_ID_MAX            (HSL_DBG_SN_AUTO_TEST_INFO + 1)

#define HSL_PROFILING_ADD_MODULE_CONSTRUCTOR(_mODULEnAME) \
        void __attribute__ ((constructor)) onLoad_ ## _mODULEnAME (void); \
        \
        void onLoad_ ## _mODULEnAME (void) \
        { \
            Dl_info info; \
            dladdr((const void*)(&onLoad_ ## _mODULEnAME), &info); \
            FrHslAddDynamicLibInfo(info.dli_fbase, info.dli_saddr, info.dli_fname); \
        }

// group module ID
typedef enum
{
    // utopia scheme                ¡V 0 ~ 127
    GROUP_MODULE_UTOPIA_ALL         = 0x00,
    GROUP_MODULE_UTOPIA_GOP         = 0x01,
    GROUP_MODULE_UTOPIA_GE          = 0x02,
    GROUP_MODULE_UTOPIA_HSL         = 0x03,

    // ¡K

    // middleware scheme            ¡V 128 ~ 191
    GROUP_MODULE_MW_ALL             = 0x80, // BD subtitle
    GROUP_MODULE_MW_PGS             = 0x81, // BD subtitle
    GROUP_MODULE_MW_MHEG5           = 0x82,
    // ¡K

    // SN scheme                    ¡V 192 ~ 255
    GROUP_MODULE_SN_ALL             = 0xC0,
    GROUP_MODULE_SN_MUF             = 0xC1,
    GROUP_MODULE_SN_AUTO_TEST       = 0xC2,
    GROUP_MODULE_SN_PROFILE         = 0xC3
    // ¡K

} EN_HSL_GROUP_MODULE;

// group level ID, 2 bits to display the 4 conditions
typedef enum
{
    GROUP_LEVEL_DEBUG               = 0x00,
    GROUP_LEVEL_INFO                = 0x01,
    GROUP_LEVEL_XXX1                = 0x02,
    GROUP_LEVEL_XXX2                = 0x03,

} EN_HSL_GROUP_LEVEL;

// -- communication flow --------------------------->

typedef enum
{
    // cmd type
    HSL_CMD_TYPE                    = 0x10,

    // cmd group
    HSL_CMD_CARD_STATUS             = 0x20,
    HSL_CMD_SEND_DATA               = 0x21,
    HSL_CMD_RESET                   = 0x22,
    HSL_CMD_GROUP_ID_FILTER         = 0x23,
    HSL_CMD_LOG_ID_FILTER           = 0x24,
    HSL_CMD_ACK_TARGET              = 0x25,
    HSL_CMD_RB_TOTAL_SIZE           = 0x26,
    HSL_CMD_RB_EXIST_DATA_SIZE      = 0x27,
    HSL_CMD_GET_HSL_DATA            = 0x28,

    // end
    HSL_CMD_END

} EN_HSL_CMD_TYPE;

// cmd queue header.
typedef struct
{
    MS_U32  u32Pid;     // PC process id
    MS_U32  u32Len;     // buffer length
    MS_U16  u16Cmd;     // command
    MS_U8 *   pu8Buf;    // data buffer
}CmdInfo;

/** Sets Filter Matrix.
 * The KiSetsFilterMatrix signal is used to send the signal logging filter
 * into the system.
 *
 * This type of filter is needed when signal sets are
 * being used. The actual size of this signal when sent may be different
 * from the compile time structure as the matrix array will change size
 * depending on the number of signal sets, bases and id's defined in the
 * system.
 *
 * The Sets filter is like an array of 2 dimensional arrays, one for
 * each signal set. This results in the Sets filter being a 3 dimensional
 * array (but with variable sized dimensions).
 *
 * DO NOT CHANGE THIS STRUCTURE'S NAME OR MEMBERS AS PC TEST TOOLS
 * MAY REFERENCE THESE. */

typedef struct KiSetsFilterMatrixTag
{
    /** The number of signal sets in the matrix array. */
    MS_U16 numSets;

    /** The number of signal bases in the matrix array. */
    MS_U32 numBases;

    /** The size in bytes of the matrix array. */
    MS_U32 matrixSize;

    /** The filter matrix.
     * The size of this array is given by the matrixSize array rather than
     * the statically defined dimension. This array has information on what
     * signals within each set and base should be logged.
     * The matrix array is split into 3 parts. The first part is an array
     * from 0 to (numSets - 1) of 4 byte indexes into the base offsets (the
     * 2nd part), each index represents the first base in the associated set.
     * The second part is an array from numSets to (numSets + numBases - 1)
     * of 4 byte indexes into the signal bitmap (the 3rd part), each index
     * represents the first signal in the associated base. The third part
     * is the signal bitmap, each bit represents the logging state of a
     * signal, the signals within a base always start on an MS_U8 boundary
     * (i.e. there is padding at the end of bases to get to an MS_U8 boundary).*/
    MS_U8 matrix[10];

} KiSetsFilterMatrix;


// <-------------------------------------------------


/**
 *  This function is called to initialise the HSL controller.
 *  This function is called to initialise the HSL controller.
 */
MS_BOOL FrHslInitialise(const MS_PHYADDR PhyAddr, const MS_U32 u32BufByteLen);
MS_BOOL FrHslInitialiseMulti(MS_U8 _ICount, MS_U32 *_params);
MS_BOOL FrHslDynamicLogPointEnable(const MS_U16 lgHdr);
MS_BOOL FrHslDynamicLogPointDisable(const MS_U16 lgHdr);
MS_BOOL FrHslDynamicLogPointEnableAll(void);
MS_BOOL FrHslDynamicLogPointDisableAll(void);
MS_BOOL FrHslDynamicLogGroupEnable(const MS_U16 groupId);
MS_BOOL FrHslDynamicLogGroupDisable(const MS_U16 groupId);
MS_BOOL FrHslDynamicLogGroupEnableAll(void);
MS_BOOL FrHslDynamicLogGroupDisableAll(void);
MS_BOOL FrHslV2ApplySingleLogPointFiltering(const MS_U16 lgHdr, const MS_BOOL enableState);
MS_BOOL FrHslV2ApplyMultipleLogPointsFilter(const MS_U16* lgHdr_p, const MS_BOOL* enableState_p, const MS_U16 sizeArray);
MS_BOOL FrHslV2InitialiseLogPointFiltering(void);
MS_BOOL FrHslV2InitialiseGroupIdFiltering(void);
MS_BOOL FrHslFinalize(void);
void KiTtiProcessSetsFilter(const KiSetsFilterMatrix * signalData);

MS_BOOL FrHslAddDynamicLibInfo(void* baseAddress, void* onLoadAddress, const char *libFileName);
MS_BOOL FrHslAddThreadInfo(const MS_U32 threadId, const char * threadName);

#if 1 // remove these test functions later
MS_BOOL FrHslDynamicLogPointTest(const MS_U16 lgHdr);
#endif

#define M_FrHslWriteSPMsgHeader(value, pu8Buffer, u32Time)  FrHslWriteHeader(HSL_RAWLOB_SP, (MS_U16)value, pu8Buffer, u32Time)

#define M_FrHslWriteVLMsgHeader(value, pu8Buffer, u32Time)  FrHslWriteHeader(HSL_RAWLOB_VL, (MS_U16)value, pu8Buffer, u32Time)

#define M_FrHslWritePacketCounts(value, pu8Buffer) FrHslWritePayload(FALSE, value, pu8Buffer)

#define M_FrHslWritePayload(value, pu8Buffer) FrHslWritePayload(FALSE, value, pu8Buffer)

#define M_FrHslWriteLastPayload(value, pu8Buffer) FrHslWritePayload(TRUE, value, pu8Buffer)


#define HSL_SPLIT_INT32(a) (a>>16),(a)

/*******************************************************************************
** Global Function Prototypes
*******************************************************************************/

/** Write a 0 argument message to HSL (just a message header, no data).
  * Write a 0 argument message to HSL (just a message header, no data). Equivalent
  * Equivalent to former LG_MES_0 macro.
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  */
void M_FrHslPrintf0(const MS_U32 u32Id, const MS_U16 u16GId, const char* u8Fmt);

/** Write a 1 argument message to HSL (just a message header, no data).
  * Write a 1 argument message to HSL (just a message header, no data).
  * Equivalent to former LG_MES_1 macro.
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = argument value to log
  */
void M_FrHslPrintf1(const MS_U32 u32Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1);


/** Write a 2 argument message to HSL (just a message header, no data).
  * Write a 2 argument message to HSL (just a message header, no data).
  * Equivalent to former LG_MES_2 macro.
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  */
void M_FrHslPrintf2(const MS_U32 u32Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2);


/** Write a 3 argument message to HSL (just a message header, no data).
  * Write a 3 argument message to HSL (just a message header, no data).
  * Equivalent to former LG_MES_3 macro.
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  */
void M_FrHslPrintf3(const MS_U32 u32Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2,const MS_U16 u16Arg3);


/** Write a 4 argument message to HSL (just a message header, no data).
  * Write a 4 argument message to HSL (just a message header, no data).
  * Equivalent to former LG_MES_4 macro.
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  */
void M_FrHslPrintf4(const MS_U32 u32Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4);

/** Write a 5 argument message to HSL (just a message header, no data).
  * Write a 5 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_5 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  */
void M_FrHslPrintf5(const MS_U32 u32Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5);

/** Write a 6 argument message to HSL (just a message header, no data).
  * Write a 6 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  */
void M_FrHslPrintf6(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1 , const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5, const MS_U16 u16Arg6);


/** Write a 7 argument message to HSL (just a message header, no data).
  * Write a 7 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  */
void M_FrHslPrintf7(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7);


/** Write a 8 argument message to HSL (just a message header, no data).
  * Write a 8 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  */
void M_FrHslPrintf8(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8);


/** Write a 9 argument message to HSL (just a message header, no data).
  * Write a 9 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  */
void M_FrHslPrintf9(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9);


/** Write a 10 argument message to HSL (just a message header, no data).
  * Write a 10 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  */
void M_FrHslPrintf10(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10);


/** Write a 11 argument message to HSL (just a message header, no data).
  * Write a 11 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  * \param MS_U16 aRG11 = eleventh argument value to log
  */
void M_FrHslPrintf11(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10,
                                    const MS_U16 u16Arg11);


/** Write a 12 argument message to HSL (just a message header, no data).
  * Write a 12 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  * \param MS_U16 aRG11 = eleventh argument value to log
  * \param MS_U16 aRG12 = twelveth argument value to log
  */
void M_FrHslPrintf12(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10,
                                    const MS_U16 u16Arg11 , const MS_U16 u16Arg12);


/** Write a 13 argument message to HSL (just a message header, no data).
  * Write a 13 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  * \param MS_U16 aRG11 = eleventh argument value to log
  * \param MS_U16 aRG12 = twelveth argument value to log
  * \param MS_U16 aRG13 = thirteenth argument value to log
  */
void M_FrHslPrintf13(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10,
                                    const MS_U16 u16Arg11 , const MS_U16 u16Arg12, const MS_U16 u16Arg13);


/** Write a 14 argument message to HSL (just a message header, no data).
  * Write a 14 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  * \param MS_U16 aRG11 = eleventh argument value to log
  * \param MS_U16 aRG12 = twelveth argument value to log
  * \param MS_U16 aRG13 = thirteenth argument value to log
  * \param MS_U16 aRG14 = fourteenth argument value to log
  */
void M_FrHslPrintf14(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10,
                                    const MS_U16 u16Arg11 , const MS_U16 u16Arg12, const MS_U16 u16Arg13, const MS_U16 u16Arg14);


/** Write a 15 argument message to HSL (just a message header, no data).
  * Write a 15 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  * \param MS_U16 aRG11 = eleventh argument value to log
  * \param MS_U16 aRG12 = twelveth argument value to log
  * \param MS_U16 aRG13 = thirteenth argument value to log
  * \param MS_U16 aRG14 = fourteenth argument value to log
  * \param MS_U16 aRG15 = fifteenth argument value to log
  */
void M_FrHslPrintf15(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10,
                                    const MS_U16 u16Arg11 , const MS_U16 u16Arg12, const MS_U16 u16Arg13, const MS_U16 u16Arg14, const MS_U16 u16Arg15);


/** Write a 16 argument message to HSL (just a message header, no data).
  * Write a 16 argument message to HSL (just a message header, no data).
  * \param MS_U16 hDR = Autogenerated Log point ID.
  * Equivalent to former LG_MES_6 macro.
  * \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
  * \param MS_U16 aRG1 = first argument value to log
  * \param MS_U16 aRG2 = second argument value to log
  * \param MS_U16 aRG3 = third argument value to log
  * \param MS_U16 aRG4 = fourth argument value to log
  * \param MS_U16 aRG5 = fifth argument value to log
  * \param MS_U16 aRG6 = sixth argument value to log
  * \param MS_U16 aRG7 = seventh argument value to log
  * \param MS_U16 aRG8 = eighth argument value to log
  * \param MS_U16 aRG9 = nineth argument value to log
  * \param MS_U16 aRG10 = tenth argument value to log
  * \param MS_U16 aRG11 = eleventh argument value to log
  * \param MS_U16 aRG12 = twelveth argument value to log
  * \param MS_U16 aRG13 = thirteenth argument value to log
  * \param MS_U16 aRG14 = fourteenth argument value to log
  * \param MS_U16 aRG15 = fifteenth argument value to log
  * \param MS_U16 aRG16 = sixteenth argument value to log
  */
void M_FrHslPrintf16(MS_U32 u32Id, MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Arg1, const MS_U16 u16Arg2, const MS_U16 u16Arg3, const MS_U16 u16Arg4, const MS_U16 u16Arg5,
                                    const MS_U16 u16Arg6, const MS_U16 u16Arg7 , const MS_U16 u16Arg8, const MS_U16 u16Arg9, const MS_U16 u16Arg10,
                                    const MS_U16 u16Arg11 , const MS_U16 u16Arg12, const MS_U16 u16Arg13, const MS_U16 u16Arg14, const MS_U16 u16Arg15, const MS_U16 u16Arg16);


/** Write a string message
 *  Write a string message
 *  \param MS_U16 hDR = Message header word.
 *  \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
 *  \param MS_U16 *pDATA = Array of lENGTH MS_U16s.
 */
void M_FrHslString(const MS_U16 u16Id, const MS_U16 u16GId, const char* u8fmt, const void* pArray);


/** Write a message that is an array of MS_U16s.
 *  Write a message that is an array of MS_U16s. Equivalent to former LG_MS_U16_DATA macro.
 *  \param MS_U16 hDR = Message header word.
 *  \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
 *  \param MS_U16 lENGTH = Number of MS_U16s in the array.
 *  \param MS_U16 *pDATA = Array of lENGTH MS_U16s.
 */
void M_FrHslArray16(const MS_U16 u16Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Length, const void* pArray);


/**  Write a message that is an array of MS_U32s. Filter applied at run time.
 *   Write a message that is an array of MS_U32s. Filter applied at run time.
 *  \param MS_U16 hDR = Message header word.
 *  \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
 *  \param MS_U16 lENGTH = Number of MS_U32s in the array.
 *  \param MS_U32 *pDATA = Array of lENGTH MS_U32s.
 *  \param MS_U16 lASTwORDeMPTY = Logging indicator for the last 16 bit word - if set to 1 the last 16 bit word is not logged.
 */
void M_FrHslArray32(const MS_U16 u16Id, const MS_U16 u16GId, const char* u8Fmt, const MS_U16 u16Length, const void* pArray, const MS_BOOL bLastWordEmpty);


/** Write a message that captures an instance of a structure.
 *  \param MS_U16 hDR = Message header word.
 *  \param String fORMATsPECIFER = Format specifier string which resolves to nothing at compile time.
 *  \param MS_U16 lENGTH = Number of MS_U16s in the array.
 *  \param MS_U16 *pDATA = Array of lENGTH MS_U16s.
 */

void FrHslTypedefCall(const MS_U16 u16Id, const MS_U16 u16GId, const MS_U16 u16Length, const void* pArray, const MS_BOOL bOddBytePresent);

#define M_FrHslTypedef(u16Id, u16GId, u8Fmt, type, pArray)                                                        \
{                                                                                                                 \
   FrHslTypedefCall(u16Id, u16GId, sizeof(type)/sizeof(MS_U16) + sizeof(type)%sizeof(MS_U16), pArray, (MS_BOOL)(sizeof(type)%sizeof(MS_U16)));  \
}



#ifdef  __cplusplus
}
#endif

#endif
#endif
/* END OF FILE */
