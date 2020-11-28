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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define _APIXC_CUS_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "datatype.h"
#include "drvGlobal.h"
#include "hwreg.h"
#include "MsCommon.h"
#include "xcSys.h"
#include "apiXC_Cus.h"

////////////////////////////////////////////////////////////////////////////////

static MS_PCADC_MODETABLE_TYPE astStandardModeTable[MD_STD_MODE_MAX_INDEX] =
{
    // 640x350 70Hz (IBM VGA)   --> 0
    {//MD_640x350_70    925FS-31    //0
    RES_640X350, // resolution index, use 640x400 resolution
    315, 700,     // HFreq, VFreq
    141, 59,      // HStart, VStart
    800, 449,     // HTotal, VTotal
    5,           // VTotalTorance
    0x26,         // ADC phase
    MD_FLAG_POR_HPVN,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 640x350 85Hz (VESA)--->
    {
    RES_640X350, // resolution index
    379, 851,     // HFreq, VFreq
    160, 63,      // HStart, VStart
    832, 445,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HPVN,
    },
#endif // #if ENABLE_RGB_SUPPORT_85HZ

    // 640x350 60Hz ()  --> 1
    {
    RES_640X350, // resolution index, use 640x400 resolution
    314, 592,     // HFreq, VFreq
    80, 3,  // HStart, VStart
    800, 369,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 720x400 70Hz (VGA)   --> 2
    {//MD_720x400_70    925FS-40    2
    RES_720X400, // resolution index
    315, 700,       // HFreq, VFreq
    158, 34,         // HStart, VStart
    //155, 33,         // HStart, VStart
    900, 449,       // HTotal, VTotal
    5,           // VTotalTorance
    0x2B,      // ADC phase
    MD_FLAG_POR_HNVP | MD_FLAG_POR_HNVN | MD_FLAG_POR_HPVP | MD_FLAG_POR_HPVN,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 640x400 85Hz (VESA)--->
    {
    RES_640X400, // resolution index
    379, 851,     // HFreq, VFreq
    160, 44,      // HStart, VStart
    832, 445,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HNVP,
    },
#endif //#if ENABLE_RGB_SUPPORT_85HZ

    // 640x400 70Hz (IBM VGA)   -->3
    {
    RES_640X400, // resolution index
    315, 700,     // HFreq, VFreq
    156, 33,       // HStart, VStart
    800, 449,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,      // ADC phase
    MD_FLAG_POR_HNVP,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 720x400 85Hz (VESA)--->
    {
    RES_720X400, // resolution index
    379, 850,     // HFreq, VFreq
    180, 45,      // HStart, VStart
    936, 446,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HNVP,
    },
#endif //#if ENABLE_RGB_SUPPORT_85HZ

    {//MD_640x480_60    925FS-35    //--->4
    RES_640X480, // resolution index
    315, 599,     // HFreq, VFreq
    141, 32,      // HStart, VStart
    800, 525,     // HTotal, VTotal
    5,           // VTotalTorance
    0x25,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

    {//MD_640x480_66    925FS-36    //--->5
    RES_640X480, // resolution index
    350, 667,     // HFreq, VFreq
    156, 38,      // HStart, VStart
    864, 525,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3C,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

    {//MD_640x480_72    925FS-37   //--->6
    RES_640X480, // resolution index
    379, 728,     // HFreq, VFreq
    164, 27,      // HStart, VStart
    832, 520,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3A,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 640x480 75Hz (VESA)  --> 7
    {//MD_640x480_75    925FS-38    7
    RES_640X480, // resolution index
    375, 750,     // HFreq, VFreq
    180, 15,      // HStart, VStart
    840, 500,     // HTotal, VTotal
    5,           // VTotalTorance
    0x39,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 640x480 85Hz (VESA)  -->
    {
    RES_640X480, // resolution index
    433, 850,     // HFreq, VFreq
    136, 28,      // HStart, VStart
    832, 509,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HNVN,
    },
#endif // #if ENABLE_RGB_SUPPORT_85HZ

    // 800x600 56Hz (VESA)  --> 8
    {//MD_800x600_56    925FS-44    8
        //              925FS-45(À¯»ç)
    RES_800X600, // resolution index
    352, 562,     // HFreq, VFreq
    198, 21,      // HStart, VStart
    1024, 625,   // HTotal, VTotal
    5,           // VTotalTorance
    0x04,         // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 800x600 60Hz (VESA)  --> 9
    {//MD_800x600_60    925FS-46    9
    RES_800X600, // resolution index
    379, 603,     // HFreq, VFreq
    213, 22,      // HStart, VStart
    1056, 628,   // HTotal, VTotal
    5,           // VTotalTorance
    0x30,         // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 800x600 72Hz (VESA)  --> 10
    {//MD_800x600_72    925FS-47    10
    RES_800X600, // resolution index
    481, 722,     // HFreq, VFreq
    182, 22,      // HStart, VStart
    1040, 666,   // HTotal, VTotal
    5,           // VTotalTorance
    0x06,         // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 800x600 75Hz (VESA)  --> 11
    {//MD_800x600_75    925FS-48    11
    RES_800X600, // resolution index
    469, 750,     // HFreq, VFreq
    237, 20,      // HStart, VStart
    1056, 625,   // HTotal, VTotal
    5,           // VTotalTorance
    0x2A,         // ADC phase
    MD_FLAG_POR_HPVP,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 800x600 85Hz (VESA)  -->
    {
    RES_800X600, // resolution index
    537, 851,     // HFreq, VFreq
    216, 30,      // HStart, VStart
    1048, 631,   // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HPVP,
    },
#endif //#if ENABLE_RGB_SUPPORT_85HZ

    // 832x624 75Hz (MAC)  --> 12
    {//MD_832x624_75    925FS-53    12
    RES_832X624, // resolution index
    497, 746,     // HFreq, VFreq
    283, 36,      // HStart, VStart
    1152, 667,   // HTotal, VTotal
    5,           // VTotalTorance
    0x2C,         // ADC phase
    MD_FLAG_POR_HNVN,//MD_FLAG_POR_HPVP,
    },

    // 848x480 59Hz ()  --> 13
    {//MD_848x480_59    925FS-55    13
    RES_848X480, // resolution index
    298, 596,     // HFreq, VFreq
    180, 11,      // HStart, VStart
    1056, 500,    // HTotal, VTotal
    5,           // VTotalTorance
    0x27,         // ADC phase
    MD_FLAG_POR_HNVP, //flags
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 1024x768 43i (VESA)  -->
    {
    RES_1024X768, // resolution index
    355, 868,      // HFreq, VFreq
    232, 24,       // HStart, VStart
    1264, 817,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_INTERLACE, // flags
    },
#endif // #if ENABLE_RGB_SUPPORT_85HZ

    // 1024x768 60Hz (VESA)  --> 14
    {//MD_1024x768_60   925FS_60    14
    RES_1024X768, // resolution index
    484, 600,      // HFreq, VFreq
    290, 28,       // HStart, VStart
    1344, 806,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1024x768 70Hz (VESA)  --> 15
    {//MD_1024x768_70   925FS_62    15
    RES_1024X768, // resolution index
    565, 700,      // HFreq, VFreq
    275, 28,       // HStart, VStart
    1328, 806,    // HTotal, VTotal
    5,           // VTotalTorance
    0x00,          // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1024x768 75Hz (VESA)  --> 16
    {//MD_1024x768_75   925FS_65    16
    RES_1024X768, // resolution index
    600, 750,      // HFreq, VFreq
    269, 27,       // HStart, VStart
    1312, 800,    // HTotal, VTotal
    5,           // VTotalTorance
    0x29,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 1024x768 85Hz (VESA)  -->
    {
    RES_1024X768, // resolution index
    687, 850,      // HFreq, VFreq
    304, 39,       // HStart, VStart
    1376, 808,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HPVP,
    },
#endif // #if ENABLE_RGB_SUPPORT_85HZ

  // 1152x864 60Hz (VESA)  --> 17
    {//MD_1152x864_60   925FS_71    17
    RES_1152X864,  // resolution index
    543, 600,      // HFreq, VFreq
    //540, 600,      // HFreq, VFreq
    285, 36,       // HStart, VStart
    1472, 905,    // HTotal, VTotal
    //1480, 900,    // HTotal, VTotal
    5,             // VTotalTorance
    0x33,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1152x864 70Hz (VESA)  --> 18
    {//18
    RES_1152X864, // resolution index
    639, 702,      // HFreq, VFreq
    288, 49,       // HStart, VStart
    1472, 912,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1152x864 75Hz (VESA)  --> 19
    {//MD_1152x864_75   925FS_72    19
    RES_1152X864, // resolution index
    675, 750,      // HFreq, VFreq
    381, 31,       // HStart, VStart
    1600, 900,    // HTotal, VTotal
    5,           // VTotalTorance
    0x11,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 1152x864 85Hz (VESA)  -->
    {
    RES_1152X864, // resolution index
    771, 850,      // HFreq, VFreq
    360, 42,       // HStart, VStart
    1552, 910,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },
#endif // #if ENABLE_RGB_SUPPORT_85HZ

    // 1152x870 75Hz (MAC)  --> 20
    {//MD_1152x870_75   925FS_74    20
    RES_1152X870, // resolution index
    689, 751,      // HFreq, VFreq
    265, 38,       // HStart, VStart
    1456, 916,    // HTotal, VTotal
    5,           // VTotalTorance
    0x1B,          // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1280x768 60Hz (VESA-GTF)  --> 21
    {// MSPG1025D_85                 21
    RES_1280X768, // resolution index
    477, 598,      // HFreq, VFreq
    314, 19,       // HStart, VStart
    1664, 798,    // HTotal, VTotal
    5,           // VTotalTorance
    0x26,          // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1280x768 75Hz (VESA-GTF)  --> 22
    {//MSPG1025D_89                  22
    RES_1280X768, // resolution index
    602, 748,      // HFreq, VFreq
    329, 26,       // HStart, VStart
    1696, 805,    // HTotal, VTotal
    5,           // VTotalTorance
    0x13,          // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1280x960 60Hz (VESA)  --> 23
    {// MSPG1025D-94             23
    RES_1280X960, // resolution index
    600, 600,      // HFreq, VFreq
    421, 35,       // HStart, VStart
    1800, 1000,   // HTotal, VTotal
    5,           // VTotalTorance
    0x11,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1280x960 75Hz (VESA)  --> 24
    {// MSPG1025D-95             24
    RES_1280X960, // resolution index
    750, 750,      // HFreq, VFreq
    381, 35,       // HStart, VStart
    1728, 1002,   // HTotal, VTotal
    5,           // VTotalTorance
    0x11,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 1280x960 85Hz (VESA)  -->
    {
    RES_1280X960, // resolution index
    859, 850,      // HFreq, VFreq
    384, 50,       // HStart, VStart
    1728, 1011,   // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HPVP,
    },
#endif // #if ENABLE_RGB_SUPPORT_85HZ

    // 1280x1024 60Hz (VESA)  --> 25
    {// MSPG1025D-99              25
    RES_1280X1024, // resolution index
    639, 600,       // HFreq, VFreq
    357, 37,        // HStart, VStart
    1688, 1066, // HTotal, VTotal
    5,           // VTotalTorance
    0x22,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1280x1024 59Hz (VESA)  --> 26
    {// MSPG1025D-98              26
    RES_1280X1024, // resolution index
    633, 599,      // HFreq, VFreq
    345, 28,       // HStart, VStart
    1712, 1063,    // HTotal, VTotal
    5,           // VTotalTorance
    0x02,          // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1280x1024 72Hz (VESA)  --> 27
    {// MSPG1025D-101             27
    RES_1280X1024, // resolution index
    760, 720,       // HFreq, VFreq
    375, 54,        // HStart, VStart
    1712, 1064, // HTotal, VTotal
    5,           // VTotalTorance
    0x3A,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1280x1024 75Hz (VESA)  --> 28
    {// MSPG1025D-102             28
    RES_1280X1024, // resolution index
    800, 750,       // HFreq, VFreq
    389, 37,        // HStart, VStart
    1688, 1066, // HTotal, VTotal
    5,           // VTotalTorance
    0x02,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1280x1024 76Hz (VESA)  --> 29
    {// MSPG1025D-103             29
    RES_1280X1024, // resolution index
    811, 760,       // HFreq, VFreq
    343, 31,        // HStart, VStart
    1664, 1066, // HTotal, VTotal
    5,           // VTotalTorance
    0x3A,           // ADC phase
    MD_FLAG_POR_HNVN,
    },

#if ENABLE_RGB_SUPPORT_85HZ
    // 1280x1024 85Hz (VESA)  -->
    {
    RES_1280X1024, // resolution index
    911, 850,       // HFreq, VFreq
    384, 47,        // HStart, VStart
    1728, 1072, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HPVP,
    },
#endif //#if ENABLE_RGB_SUPPORT_85HZ

    // 1600x1200 59Hz (R.B)  --> 30
    {// MSPG1025D-117            30
    RES_1600X1200, // resolution index
    741, 599,       // HFreq, VFreq
    146, 20,        // HStart, VStart
    1760, 1236, // HTotal, VTotal
    5,           // VTotalTorance
    0x11,           // ADC phase
    MD_FLAG_POR_HPVN,
    },

    // 1600x1200 60Hz (VESA)  --> 31
    {// MSPG1025D-120             31
    RES_1600X1200, // resolution index
    750, 600,       // HFreq, VFreq
    492, 45,        // HStart, VStart
    2160, 1250, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1600x1200 65Hz (VESA)  --> 32
    {//32
    RES_1600X1200, // resolution index
    813, 650,       // HFreq, VFreq
    496, 49,        // HStart, VStart
    2160, 1250, // HTotal, VTotal
    5,           // VTotalTorance
    0x39,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1600x1200 70Hz (VESA)  --> 33
    {//33
    RES_1600X1200, // resolution index
    875, 700,       // HFreq, VFreq
    496, 49,        // HStart, VStart
    2160, 1250, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1600x1200 75Hz (VESA)  --> 34
    {// MSPG1025D-121             34
    RES_1600X1200, // resolution index
    938, 750,       // HFreq, VFreq
    493, 45,        // HStart, VStart
    2160, 1250, // HTotal, VTotal
    5,           // VTotalTorance
    0x11,           // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1920x1200 59Hz (R.B)  --> 35
    {// 35
    RES_1920X1200,  // resolution index
    740, 599,       // HFreq, VFreq
    110, 30,        // HStart, VStart
    2080, 1235,     // HTotal, VTotal
    5,              // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HPVN,
    },

    // 1920x1200 60Hz ()  --> 36
    {// MSPG1025D-128         36
    RES_1920X1200, // resolution index
    745, 599,       // HFreq, VFreq
    500, 40,        // HStart, VStart
    2592, 1245, // HTotal, VTotal
    5,           // VTotalTorance
    0x31,           // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1920x1200 65Hz ()  --> 37
    {//37
    RES_1920X1200, // resolution index
    812, 650,       // HFreq, VFreq
    496, 49,        // HStart, VStart
    2592, 1248, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1920x1200 75Hz ()  --> 38
    {//38
    RES_1920X1200, // resolution index
    940, 749,       // HFreq, VFreq
    344, 49,        // HStart, VStart
    2608, 1255, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HNVP,
    },

#if 0
    // 1400x1050 59Hz (R.B)  --> 48
    {//39
    RES_1400X1050, // resolution index
    647, 599,      // HFreq, VFreq
    110, 26,       // HStart, VStart
    1560, 1080, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HPVN,// | MD_FLAG_POR_HNVP,
    },
#endif
    // 1400x1050 59Hz (R.B)  --> 39
    {//39
    RES_1400X1050, // resolution index
    647, 599,      // HFreq, VFreq
    232, 32,       // HStart, VStart
    1560, 1080, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HPVN | MD_FLAG_POR_HNVP,
    },

#if 0
    // 1400x1050 60Hz ()  --> 49
    {//40
    RES_1400X1050, // resolution index
    653, 599,      // HFreq, VFreq
    332, 35,       // HStart, VStart
    1864, 1089, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },
#endif
    // 1400x1050 60Hz ()  --> 40
    {//40
    RES_1400X1050, // resolution index
    653, 599,      // HFreq, VFreq
    232, 32,       // HStart, VStart
    1864, 1088, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1400x1050 75Hz ()  --> 41
    {// MSPG1025D-111         41
    RES_1400X1050, // resolution index
    823, 748,      // HFreq, VFreq
    382, 41,       // HStart, VStart
    1896, 1099, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1440x900 60Hz (RB)  --> 42
    {// MSPG1025D-113        42
    RES_1440X900, // resolution index
    554, 599,    //559, 598,      // HFreq, VFreq
    110, 23,       // HStart, VStart
    1600, 926,  //1904, 934,    // HTotal, VTotal
    5,           // VTotalTorance
    0x0E,          // ADC phase
    MD_FLAG_POR_HPVN, //MD_FLAG_POR_HNVP,
    },

    // 1440x900 75Hz ()  --> 43
    {//43
    RES_1440X900, // resolution index
    706, 749,      // HFreq, VFreq
    248, 33,       // HStart, VStart
    1936, 942,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },
#if 0
    // 1680x1050 59Hz (R.B)  --> 53
    {//44
    RES_1680X1050, // resolution index
    647, 599,      // HFreq, VFreq
    112, 25,       // HStart, VStart
    1840, 1080, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HPVN | MD_FLAG_POR_HNVP,
    },

#endif

    // 1680x1050 59Hz (R.B)  --> 44
    {//44
    RES_1680X1050, // resolution index
    646, 598,      // HFreq, VFreq
    108, 19,       // HStart, VStart    //may_20070614 adjust default position
    //280, 30,       // HStart, VStart
    1840, 1080, // HTotal, VTotal
    5,           // VTotalTorance
    32,          // ADC phase            //may_20070614 adjust default position
    //0x3f,          // ADC phase
    MD_FLAG_POR_HPVN | MD_FLAG_POR_HNVP,
    },
#if 0
    // 1680x1050 60Hz ()  --> 54
    {//45
    RES_1680X1050, // resolution index
    653, 599,      // HFreq, VFreq
    280, 30,       // HStart, VStart
    2240, 1089, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },
#endif

    // 1680x1050 60Hz ()  --> 45
    {//45
    RES_1680X1050, // resolution index
    652, 599,      // HFreq, VFreq
    450, 28,       // HStart, VStart    //may_20070614 adjust default position
    //280, 30,       // HStart, VStart
    2240, 1089, // HTotal, VTotal
    5,           // VTotalTorance
    6,          // ADC phase            //may_20070614 adjust default position
    //0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1680x1050 75Hz ()  --> 46
    {//46
    RES_1680X1050, // resolution index
    823, 748,      // HFreq, VFreq
    296, 40,       // HStart, VStart
    2272, 1099, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 720x480I 60Hz (YPbPr)  --> 47  Start of YPbPr
    {//47
    RES_720X480, // resolution index
    156, 600,     // HFreq, VFreq
    54, 24,      // HStart, VStart
    858, 525,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3C,         // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_INTERLACE, // flags
    },

    // 720x480P 60Hz (YPbPr)  --> 48
    {//48
    RES_720X480,  // resolution index
    315, 600,     // HFreq, VFreq
    57, 28,       // HStart, VStart
    858, 525,     // HTotal, VTotal
    5,            // VTotalTorance
    0x2E,         // ADC phase
    MD_FLAG_YPBPR_BIT, // flags
    },

    // 720x576I 50Hz (YPbPr)  --> 49
    {//49
    RES_720X576,  // resolution index
    156, 500,     // HFreq, VFreq
    67, 32,       // HStart, VStart
    864, 625,     // HTotal, VTotal
    5,            // VTotalTorance
    0x3B,         // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_INTERLACE, // flags
    },

    // 720x576P 50Hz (YPbPr)  --> 50
    {//50
    RES_720X576, // resolution index
    312, 500,     // HFreq, VFreq
    66, 35,     // HStart, VStart
    864, 625,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3B,         // ADC phase
    MD_FLAG_YPBPR_BIT, // flags
    },

    // 1280x720P 50Hz (YPbPr)  --> 51
    {//51
    RES_1280X720, // resolution index
    375, 500,      // HFreq, VFreq
    0x102, 0x10,       // HStart, VStart
    //0x10B, 0x11,       // HStart, VStart
    1980, 750,    // HTotal, VTotal
    5,           // VTotalTorance
    0x05,        // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },

    // 1280x720P 60Hz (YPbPr)  --> 52
    {//52
    RES_1280X720, // resolution index
    450, 600,      // HFreq, VFreq
    0x101, 0x10,       // HStart, VStart
    1650, 750,    // HTotal, VTotal
    5,           // VTotalTorance
    0x05,        // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT , // flags
    },

    // 1920x1080i 50Hz (YPbPr)  --> 53
    {//53
    RES_1920X1080, // resolution index
    281, 500,       // HFreq, VFreq
    0xbd, 0x17,     // HStart, VStart
    //0xC7, 0x1B,     // HStart, VStart
    2640, 1125, // HTotal, VTotal (patch)
    5,           // VTotalTorance
    0x06,         // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT | MD_FLAG_INTERLACE, // flags
    },

    // 1920x1080i 60Hz (YPbPr)  --> 54
    {//54
    RES_1920X1080, // resolution index
    337, 600,       // HFreq, VFreq
    0xbd, 0x16,     // HStart, VStart
    //0xC7, 0x1B,     // HStart, VStart
    2200, 1125, // HTotal, VTotal (patch)
    5,           // VTotalTorance
    0x05,         // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT | MD_FLAG_INTERLACE, // flags
    },

#if (SUPPORT_EURO_HDTV)
    // 1920x1080i 50Hz (YPbPr)  -->
    {//MODE_NAME("1080i50_Euro")
     RES_1920X1080, // resolution index
     313, 500,      // HFreq, VFreq
     304, 152,      // HStart, VStart
     2376, 1250,    // HTotal, VTotal
     5,           // VTotalTorance
     0x1f,          // ADC phase
     MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT | MD_FLAG_INTERLACE | MD_FLAG_EURO_HDTV_BIT, // flags
    },
#endif

    // 1920x1080P 24Hz (YPbPr)  -->55
    {//55
    RES_1920X1080P, // resolution index
    270, 240,       // HFreq, VFreq
    0xbc, 0x21,     // HStart, VStart
    2750, 1125, // HTotal, VTotal (patch) 135Hz
    5,           // VTotalTorance
    0x21,           // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },
    
    // 1920x1080P 25Hz (YPbPr)  -->56
    {//56
    RES_1920X1080P, // resolution index
    281, 250,       // HFreq, VFreq
    0xbc, 0x21,     // HStart, VStart
    2640, 1125, // HTotal, VTotal (patch) 135Hz
    5,           // VTotalTorance
    0x21,           // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },

    // 1920x1080P 30Hz (YPbPr)  -->56
    {//56
    RES_1920X1080P, // resolution index
    337, 300,       // HFreq, VFreq
    0xbc, 0x20,     // HStart, VStart
    //0xD0, 0x20,     // HStart, VStart
    2200, 1125, // HTotal, VTotal (patch)  135
    5,           // VTotalTorance
    0x21,           // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },

    // 1920x1080P 50Hz (YPbPr)  --> 57
    {//57
    RES_1920X1080P, // resolution index
    562, 500,       // HFreq, VFreq
    0xbc, 0x20,     // HStart, VStart
    2640, 1125, // HTotal, VTotal (patch) 148MHz
    5,           // VTotalTorance
    0x17,           // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },

    // 1920x1080P 60Hz (YPbPr)  --> 58
    {//58
    RES_1920X1080P, // resolution index
    675, 600,       // HFreq, VFreq
    280, 0x20,     // HStart, VStart
    2200, 1125, // HTotal, VTotal (patch)  148MHz
    5,           // VTotalTorance
    0x12,           // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },

    // 720x480I 60Hz (YPbPr)  --> 56  Start of YPbPr
    {//59, patch for DVD 480i -> Sherwood -> component output -> OSD unsupport mode
    RES_720X480, // resolution index
    156, 300,     // HFreq, VFreq
    0x3b, 0x1a,   // HStart, VStart    //may_070401_CompPosAdj
    //0x41, 0x1E,   // HStart, VStart
    858, 525,     // HTotal, VTotal
    5,           // VTotalTorance
    0x1f,         // ADC phase
    MD_FLAG_YPBPR_BIT, // flags
    },
#if ENABLE_3D_PROCESS//for mode like 1280x1470(720x2+30)
    // 1280X1470P 50Hz (YPbPr)  --> 
    {//
    RES_1280X1470, // resolution index
    750, 500,      // HFreq, VFreq
    0x101, 0x20,       // HStart, VStart
    1980, 1500,    // HTotal, VTotal
    5,           // VTotalTorance
    0x05,        // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT , // flags
    },

    // 1280X1470P 60Hz (YPbPr)  --> 
    {//
    RES_1280X1470, // resolution index
    900, 600,      // HFreq, VFreq
    0x101, 0x20,       // HStart, VStart
    1650, 1500,    // HTotal, VTotal
    5,           // VTotalTorance
    0x05,        // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT , // flags
    },

    // 1920X2205P 24Hz (YPbPr)  --> 
    {//
    RES_1920X2205, // resolution index
    540, 240,       // HFreq, VFreq
    0xbc, 0x21,     // HStart, VStart
    2750, 2250, // HTotal, VTotal (patch) 135Hz
    5,           // VTotalTorance
    0x21,           // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },
#endif
    // 1152x870 60Hz    --> 59
    {//59
    RES_1152X870,   // resolution index
    541, 599,       // HFreq, VFreq
    304, 25,        // HStart, VStart
    1520, 903,  // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HNVP,
    },
    // 1280x800 60Hz    --> 60
    {//60
    RES_1280X800,   // resolution index
    495, 598,       // HFreq, VFreq
    323, 20,        // HStart, VStart
    1680, 828,  // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HNVP,
    },
    // 1280x800 75Hz    --> 61
    {//61
    RES_1280X800,   // resolution index
    625, 749,       // HFreq, VFreq
    //154, 36,        // HStart, VStart
    323, 36,        // HStart, VStart//??
    1712, 835,  // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1600x1024 60Hz   --> 62
    {// MSPG1025D-114       62
    RES_1600X1024,  // resolution index
    621, 597,       // HFreq, VFreq
    //637, 601,       // HFreq, VFreq
    154, 20,        // HStart, VStart
    1808, 1040,  // HTotal, VTotal
    //2144, 1060,  // HTotal, VTotal
    5,           // VTotalTorance
    0x38,           // ADC phase
    MD_FLAG_POR_HNVN,
    //MD_FLAG_POR_HNVP,
    },

    // 1600x1024 75Hz   --> 63
    {//63
    RES_1600X1024,  // resolution index
    802, 750,       // HFreq, VFreq
    154, 20,        // HStart, VStart
    2176, 1069,  // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1600x900 60Hz ()  --> 64
    {//64
    RES_1600X900, // resolution index
    557, 598,      // HFreq, VFreq
    232, 25,       // HStart, VStart
    2128, 932,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1600x900 75Hz ()  --> 65
    {//65
    RES_1600X900, // resolution index
    702, 747,      // HFreq, VFreq
    248, 33,       // HStart, VStart
    2160, 940,    // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,          // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1280x720 75Hz ()  --> 66
    {// MSPG1025D-81         66
    RES_1280X720, // resolution index
    564, 750,     // HFreq, VFreq
    329, 26,      // HStart, VStart
    1696, 752,   // HTotal, VTotal
    5,           // VTotalTorance
    0x2d,         // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 640x480 57Hz ()  --> 67
    {//67
    RES_640X480, // resolution index
    300, 571,     // HFreq, VFreq
    138, 31,      // HStart, VStart
    800, 525,     // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1360x768 60Hz ()  --> 68
    {// MSPG1025D_109        68
    RES_1360X768, // resolution index
    477, 600,     // HFreq, VFreq
    365, 17,      // HStart, VStart
    1792, 795,    // HTotal, VTotal
    5,           // VTotalTorance
    0x22,         // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1600x1200 51Hz ()  --> 69
    {//69
    RES_1600X1200, // resolution index
    648, 518,       // HFreq, VFreq
    496, 46,        // HStart, VStart
    2160, 1250, // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,           // ADC phase
    MD_FLAG_POR_HPVP, //flags
    },

    // 848x480 60Hz ()  --> 70
    {//70
    RES_848X480, // resolution index
    310, 600,     // HFreq, VFreq
    139, 31,      // HStart, VStart
    1088, 517,    // HTotal, VTotal
    5,           // VTotalTorance
    0x12,         // ADC phase
    MD_FLAG_POR_HPVP, //flags
    },

    // 1280x768 50Hz (925FS 83)  --> 71
    {//MD_1280x768_50   //71
    RES_1280X768, // resolution index
    395, 500,      // HFreq, VFreq
    307, 14,       // HStart, VStart
    1648, 791,    // HTotal, VTotal
    5,           // VTotalTorance
    0x13,          // ADC phase
    MD_FLAG_POR_HPVP,
    },

    // 1366x768 60Hz ()  --> 72
    {//MD_1366x768_60   925FS_106, MSPG1025D_115   72
    RES_1366X768, // resolution index
    491, 600,     // HFreq, VFreq
    346, 32,      // HStart, VStart
    1780, 817,    // HTotal, VTotal
    5,           // VTotalTorance
    0x2f,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 720x576 60Hz ()  --> 73
    {//73    //Radeon 9200
    RES_720X576, // resolution index
    357, 598,     // HFreq, VFreq
    0xA3, 0x0F,   // HStart, VStart
    912, 597,     // HTotal, VTotal
    5,           // VTotalTorance
    0x1f,         // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 864x648 60Hz ()  --> 74
    {//74    //Radeon X850 XT Platinum Ed
    RES_864X648, // resolution index
    403, 600,     // HFreq, VFreq
    212, 17,      // HStart, VStart
    1120, 671,   // HTotal, VTotal
    5,           // VTotalTorance
    0x3f,         // ADC phase
    MD_FLAG_POR_HNVP,
    },

    // 1920x1080 60Hz ()  --> 75
    {//75        //925FS_126
    RES_1920X1080, // resolution index
    667, 600,       // HFreq, VFreq
    109, 21,     // HStart, VStart
    2080, 1111, // HTotal, VTotal (patch)  148MHz
    5,           // VTotalTorance
    0x12,           // ADC phase
    MD_FLAG_POR_HPVN, // flags
    },

    // 720x480 60Hz ()  --> 76
    {//76        //925FS_126
    RES_720X480, // resolution index
    351, 598,     // HFreq, VFreq
    0xA3, 0x0F,   // HStart, VStart
    891, 587,     // HTotal, VTotal
    5,           // VTotalTorance
    0x1f,         // ADC phase
    MD_FLAG_POR_HNVN,
    },

    // 1440x900 60Hz () --> 77
    {//77
    RES_1440X900, // resolution index
    559, 598,    //559, 598,      // HFreq, VFreq
    381, 24,       // HStart, VStart
    1904, 934,  //1904, 934,    // HTotal, VTotal
    5,           // VTotalTorance
    0x0E,          // ADC phase
    MD_FLAG_POR_HNVP, //MD_FLAG_POR_HNVP,
    },

    // 1280x768 60Hz RB (VESA)--> 78
    {// 78
    RES_1280X768, // resolution index
    474, 600,      // HFreq, VFreq
    110, 19,       // HStart, VStart
    1440, 790,    // HTotal, VTotal
    5,           // VTotalTorance
    0x26,          // ADC phase
    MD_FLAG_POR_HPVN,
    },

    // 1280x720P 25Hz (YPbPr)  --> 79
    {//79
    RES_1280X720, // resolution index
    184, 250,      // HFreq, VFreq
    0xC1, 5,       // HStart, VStart
    1600, 734,    // HTotal, VTotal
    5,           // VTotalTorance
    0x05,        // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT , // flags
    },

    // 1280x720P 30Hz (YPbPr)  --> 80
    {//80
    RES_1280X720, // resolution index
    221, 300,      // HFreq, VFreq
    0xC2, 5,       // HStart, VStart
    1600, 736,    // HTotal, VTotal
    5,           // VTotalTorance
    0x05,        // ADC phase
    MD_FLAG_YPBPR_BIT | MD_FLAG_HDTV_BIT, // flags
    },

};

/***************************************************************************************/

MS_PCADC_MODETABLE_TYPE* MApi_XC_GetModeTable(void)
{
    return astStandardModeTable;
}

MS_U8 MApi_XC_GetTotalModeCount(void)
{
    return MD_STD_MODE_MAX_INDEX;
}









////////////////////////////////////////////////////////////////////////////////
#undef _APIXC_CUS_C_

