//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2014 MStar Semiconductor, Inc. All rights reserved.
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

#ifndef _MIU_MST206B_D01A_S_MIAMI_H_
#define _MIU_MST206B_D01A_S_MIAMI_H_

#if (ENABLE_MSTAR_BD_MST206B_D01A_S_MIAMI == 1)

const MS_REG_INIT MIU0_DDR_Init[] =
{
#if defined(CONFIG_MIU0_DDR3_1666)

#if defined(CONFIG_MIU0_4X_MODE)
    #error "No Support MIU 4x Mode"
#else

//================================================
// set DDRPLL0_1600MHz        
//================================================
    _RV32_2(0x110d78, 0x0001),
    _RV32_2(0x110d8a, 0x0001),
    _RV32_2(0x110d24, 0x1000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d36, 0x0400),
    _RV32_2(0x110d34, 0x2004),
    _RV32_2(0x110d30, 0x7236),
    _RV32_2(0x110d32, 0x0023),
    _RV32_2(0x110d22, 0x0004),

//================================================
// set DDR3-32-8X-CL13_1866        
//================================================
    _RV32_2(0x101202, 0x03a7),
    _RV32_2(0x101204, 0x000c),
    _RV32_2(0x101206, 0x1430), //[12:12] reg_cke_always_on	
    _RV32_2(0x101208, 0x1cbb),
    _RV32_2(0x10120a, 0x2766),
    _RV32_2(0x10120c, 0xc6c8),
    _RV32_2(0x10120e, 0x4080),
    _RV32_2(0x101210, 0x1d70),
    _RV32_2(0x101212, 0x4004),
    _RV32_2(0x101214, 0x8018),
    _RV32_2(0x101216, 0xc000),
    _RV32_2(0x101228, 0x0030),
    _RV32_2(0x1012d2, 0x9000), //dram size = 512MB
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d0a, 0x1133),
    _RV32_2(0x110d0e, 0x0089),
    _RV32_2(0x110d2e, 0x1111),
    _RV32_2(0x110d38, 0x0000),
    _RV32_2(0x110d3a, 0x2022),
    _RV32_2(0x110d3c, 0x1344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x3040),
    _RV32_2(0x110d4c, 0x3344),
    _RV32_2(0x110d4e, 0x0044),
    _RV32_2(0x110d50, 0x1100),
    _RV32_2(0x110d52, 0x0066),
    _RV32_2(0x110d58, 0x0a0a),
    _RV32_2(0x110d5a, 0xaaaa),
    _RV32_2(0x110d5c, 0xaaaa),
    _RV32_2(0x110d5e, 0xaaaa),
    _RV32_2(0x110d74, 0x0606),
    _RV32_2(0x110d76, 0x0606),
    _RV32_2(0x110d8a, 0x0001),
    _RV32_2(0x110d94, 0x0106),
    _RV32_2(0x110d96, 0x0306),
    _RV32_2(0x110d6c, 0x1010),
    _RV32_2(0x110d6e, 0x1010),
    _RV32_2(0x110da0, 0x3423),
    _RV32_2(0x110da2, 0x2011),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110da6, 0x3031),
    _RV32_2(0x110da8, 0x7342),
    _RV32_2(0x110daa, 0x3130),
    _RV32_2(0x110dac, 0x3120),
    _RV32_2(0x110dae, 0x4233),
    _RV32_2(0x110db8, 0x3333),
    _RV32_2(0x110dba, 0x0333),
    _RV32_2(0x110dbc, 0x0333),
    _RV32_2(0x110dbe, 0x0333),
    _RV32_2(0x110dd0, 0x5555),
    _RV32_2(0x110dd2, 0x5555),
    _RV32_2(0x110dd4, 0x5555),
    _RV32_2(0x110dd6, 0x5555),
    _RV32_2(0x110dd8, 0x0055),
    _RV32_2(0x110de0, 0x5555),
    _RV32_2(0x110de2, 0x5555),
    _RV32_2(0x110de4, 0x5555),
    _RV32_2(0x110de6, 0x5555),
    _RV32_2(0x110de8, 0x0055),

//=====================================================================
//MIU0 inivec setting start
//=====================================================================
//-----------------
//program DLL
//-----------------
    _RV32_2(0x110d62, 0x007f),
    _RV32_2(0x110d64, 0xf000),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00cf),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c3),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c3),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c2),
    _RV32_2(0x110d60, 0x00c0),
    _RV32_2(0x110d60, 0x33c8),
    _RV32_2(0x110d90, 0xf0f1),
//--------------------------- 
//program dig general setting 
//--------------------------- 
    _RV32_2(0x10122c, 0x8001),
    _RV32_2(0x101252, 0xffff),
    _RV32_2(0x101272, 0xffff),
    _RV32_2(0x101292, 0xffff),
    _RV32_2(0x1012b2, 0xffff),
    _RV32_2(0x161512, 0xffff),
    _RV32_2(0x161532, 0xffff),
//---------------------       
// Default BW setting         
//---------------------       
    _RV32_2(0x101240, 0x8015),
    _RV32_2(0x101260, 0x8015),
    _RV32_2(0x101280, 0x8015),
    _RV32_2(0x1012a0, 0x8015),
    _RV32_2(0x161500, 0x8015),
    _RV32_2(0x161520, 0x8015),
//--------------------------- 
//program ana general setting 
//--------------------------- 
    _RV32_2(0x110d70, 0x0800),
    _RV32_2(0x110d5a, 0xaaaa),
    _RV32_2(0x110d5c, 0xaaaa),
    _RV32_2(0x110d5e, 0xaaaa),
    _RV32_2(0x110d1a, 0x8110),
    _RV32_2(0x110d1c, 0x0020),
    _RV32_2(0x110d08, 0x003f),
    _RV32_2(0x110d54, 0xc000),
//--------------------------- 
//Toggle reset & disable GPIO 
//--------------------------- 
    _RV32_2(0x10121e, 0x0c01),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x110d00, 0x2010),
    _RV32_2(0x110d00, 0x0000),
    _RV32_2(0x110d18, 0x0000),
    _RV32_2(0x110d7c, 0x0000),
//--------------------------- 
//select Mapping              
//--------------------------- 
    _RV32_2(0x110d00, 0x0000),
//-----------                 
// DQSM RST                   
//-----------                 
    _RV32_2(0x110d1e, 0x0005),
    _RV32_2(0x110d1e, 0x000f),
    _RV32_2(0x110d1e, 0x0005),
    _RV32_2(0x101200, 0x0000),


#endif

#elif defined(CONFIG_MIU0_DDR3_1866)

#if defined(CONFIG_MIU0_4X_MODE)
    #error "No Support MIU 4x Mode"
#else
//================================================
// set DDRPLL0_1866MHz        
//================================================
    _RV32_2(0x110d78, 0x0001),
    _RV32_2(0x110d8a, 0x0001),
    _RV32_2(0x110d24, 0x1000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d36, 0x0400),
    _RV32_2(0x110d34, 0x2004),
    _RV32_2(0x110d30, 0x8f5c),
    _RV32_2(0x110d32, 0x001e),
    _RV32_2(0x110d22, 0x0004),

//================================================
// set DDR3-32-8X-CL13_1866        
//================================================
    _RV32_2(0x101202, 0x03a7),
    _RV32_2(0x101204, 0x000c),
    _RV32_2(0x101206, 0x1534), //[12:12] reg_cke_always_on	
    _RV32_2(0x101208, 0x20dd),
    _RV32_2(0x10120a, 0x2e76),
    _RV32_2(0x10120c, 0xc7e9),
    _RV32_2(0x10120e, 0x40f0),
    _RV32_2(0x101210, 0x1f14),
    _RV32_2(0x101212, 0x4004),
    _RV32_2(0x101214, 0x8020),
    _RV32_2(0x101216, 0xc000),
    _RV32_2(0x101228, 0x0040),
    _RV32_2(0x1012d2, 0x9000), //dram size = 512MB
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d0a, 0x1133),
    _RV32_2(0x110d0e, 0x0089),
    _RV32_2(0x110d2e, 0x1111),
    _RV32_2(0x110d38, 0x0000),
    _RV32_2(0x110d3a, 0x2022),
    _RV32_2(0x110d3c, 0x1344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x3040),
    _RV32_2(0x110d4c, 0x3344),
    _RV32_2(0x110d4e, 0x0044),
    _RV32_2(0x110d50, 0x1100),
    _RV32_2(0x110d52, 0x0066),
    _RV32_2(0x110d58, 0x0a0a),
    _RV32_2(0x110d5a, 0xaaaa),
    _RV32_2(0x110d5c, 0xaaaa),
    _RV32_2(0x110d5e, 0xaaaa),
    _RV32_2(0x110d74, 0x0606),
    _RV32_2(0x110d76, 0x0606),
    _RV32_2(0x110d8a, 0x0001),
    _RV32_2(0x110d94, 0x0106),
    _RV32_2(0x110d96, 0x0306),
    _RV32_2(0x110d6c, 0x1010),
    _RV32_2(0x110d6e, 0x1010),
    _RV32_2(0x110da0, 0x3423),
    _RV32_2(0x110da2, 0x2011),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110da6, 0x3031),
    _RV32_2(0x110da8, 0x7342),
    _RV32_2(0x110daa, 0x3130),
    _RV32_2(0x110dac, 0x3120),
    _RV32_2(0x110dae, 0x4233),
    _RV32_2(0x110db8, 0x3333),
    _RV32_2(0x110dba, 0x0333),
    _RV32_2(0x110dbc, 0x0333),
    _RV32_2(0x110dbe, 0x0333),
    _RV32_2(0x110dd0, 0x5555),
    _RV32_2(0x110dd2, 0x5555),
    _RV32_2(0x110dd4, 0x5555),
    _RV32_2(0x110dd6, 0x5555),
    _RV32_2(0x110dd8, 0x0055),
    _RV32_2(0x110de0, 0x5555),
    _RV32_2(0x110de2, 0x5555),
    _RV32_2(0x110de4, 0x5555),
    _RV32_2(0x110de6, 0x5555),
    _RV32_2(0x110de8, 0x0055),

//=====================================================================
//MIU0 inivec setting start
//=====================================================================
//-----------------
//program DLL
//-----------------
    _RV32_2(0x110d62, 0x007f),
    _RV32_2(0x110d64, 0xf000),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00cf),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c3),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c3),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c2),
    _RV32_2(0x110d60, 0x00c0),
    _RV32_2(0x110d60, 0x33c8),
    _RV32_2(0x110d90, 0xf0f1),
//--------------------------- 
//program dig general setting 
//--------------------------- 
    _RV32_2(0x10122c, 0x8001),
    _RV32_2(0x101252, 0xffff),
    _RV32_2(0x101272, 0xffff),
    _RV32_2(0x101292, 0xffff),
    _RV32_2(0x1012b2, 0xffff),
    _RV32_2(0x161512, 0xffff),
    _RV32_2(0x161532, 0xffff),
//---------------------       
// Default BW setting         
//---------------------       
    _RV32_2(0x101240, 0x8015),
    _RV32_2(0x101260, 0x8015),
    _RV32_2(0x101280, 0x8015),
    _RV32_2(0x1012a0, 0x8015),
    _RV32_2(0x161500, 0x8015),
    _RV32_2(0x161520, 0x8015),
//--------------------------- 
//program ana general setting 
//--------------------------- 
    _RV32_2(0x110d70, 0x0800),
    _RV32_2(0x110d5a, 0xaaaa),
    _RV32_2(0x110d5c, 0xaaaa),
    _RV32_2(0x110d5e, 0xaaaa),
    _RV32_2(0x110d1a, 0x8110),
    _RV32_2(0x110d1c, 0x0020),
    _RV32_2(0x110d08, 0x003f),
    _RV32_2(0x110d54, 0xc000),
//--------------------------- 
//Toggle reset & disable GPIO 
//--------------------------- 
    _RV32_2(0x10121e, 0x0c01),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x110d00, 0x2010),
    _RV32_2(0x110d00, 0x0000),
    _RV32_2(0x110d18, 0x0000),
    _RV32_2(0x110d7c, 0x0000),
//--------------------------- 
//select Mapping              
//--------------------------- 
    _RV32_2(0x110d00, 0x0000),
//-----------                 
// DQSM RST                   
//-----------                 
    _RV32_2(0x110d1e, 0x0005),
    _RV32_2(0x110d1e, 0x000f),
    _RV32_2(0x110d1e, 0x0005),
    _RV32_2(0x101200, 0x0000),


#endif

#elif defined(CONFIG_MIU0_DDR3_2133)

#if defined(CONFIG_MIU0_4X_MODE)
    #error "No Support MIU 4x Mode"
#else
//================================================
// set DDRPLL0_2133MHz        
//================================================
    _RV32_2(0x110d78, 0x0001),
    _RV32_2(0x110d8a, 0x0001),
    _RV32_2(0x110d24, 0x1000),
    _RV32_2(0x110d24, 0x0000),
    _RV32_2(0x110d36, 0x0400),
    _RV32_2(0x110d34, 0x2004),
    _RV32_2(0x110d30, 0xffff),
    _RV32_2(0x110d32, 0x001a),
    _RV32_2(0x110d22, 0x0004),

//================================================
// set DDR3-32-8X-CL13_1866        
//================================================
    _RV32_2(0x101202, 0x03a7),
    _RV32_2(0x101204, 0x000c),
    _RV32_2(0x101206, 0x1640), //[12:12] reg_cke_always_on	
    _RV32_2(0x101208, 0x24ee),
    _RV32_2(0x10120a, 0x3487),
    _RV32_2(0x10120c, 0xb80a),
    _RV32_2(0x10120e, 0xc0ab),
    _RV32_2(0x101210, 0x1124),
    _RV32_2(0x101212, 0x4004),
    _RV32_2(0x101214, 0x8028),
    _RV32_2(0x101216, 0xc000),
    _RV32_2(0x101228, 0x0050),
    _RV32_2(0x1012d2, 0x9000), //dram size = 512MB
    _RV32_2(0x110d02, 0xaaaa),
    _RV32_2(0x110d04, 0x0080),
    _RV32_2(0x110d0a, 0x1133),
    _RV32_2(0x110d0e, 0x0089),
    _RV32_2(0x110d2e, 0x1111),
    _RV32_2(0x110d38, 0x0000),
    _RV32_2(0x110d3a, 0x2022),
    _RV32_2(0x110d3c, 0x1344),
    _RV32_2(0x110d3e, 0x1033),
    _RV32_2(0x110d48, 0x0000),
    _RV32_2(0x110d4a, 0x3040),
    _RV32_2(0x110d4c, 0x3344),
    _RV32_2(0x110d4e, 0x0044),
    _RV32_2(0x110d50, 0x1100),
    _RV32_2(0x110d52, 0x0066),
    _RV32_2(0x110d58, 0x0a0a),
    _RV32_2(0x110d5a, 0xaaaa),
    _RV32_2(0x110d5c, 0xaaaa),
    _RV32_2(0x110d5e, 0xaaaa),
    _RV32_2(0x110d74, 0x0606),
    _RV32_2(0x110d76, 0x0606),
    _RV32_2(0x110d8a, 0x0001),
    _RV32_2(0x110d94, 0x0106),
    _RV32_2(0x110d96, 0x0306),
    _RV32_2(0x110d6c, 0x1010),
    _RV32_2(0x110d6e, 0x1010),
    _RV32_2(0x110da0, 0x3423),
    _RV32_2(0x110da2, 0x2011),
    _RV32_2(0x110da4, 0x2000),
    _RV32_2(0x110da6, 0x3031),
    _RV32_2(0x110da8, 0x7342),
    _RV32_2(0x110daa, 0x3130),
    _RV32_2(0x110dac, 0x3120),
    _RV32_2(0x110dae, 0x4233),
    _RV32_2(0x110db8, 0x3333),
    _RV32_2(0x110dba, 0x0333),
    _RV32_2(0x110dbc, 0x0333),
    _RV32_2(0x110dbe, 0x0333),
    _RV32_2(0x110dd0, 0x5555),
    _RV32_2(0x110dd2, 0x5555),
    _RV32_2(0x110dd4, 0x5555),
    _RV32_2(0x110dd6, 0x5555),
    _RV32_2(0x110dd8, 0x0055),
    _RV32_2(0x110de0, 0x5555),
    _RV32_2(0x110de2, 0x5555),
    _RV32_2(0x110de4, 0x5555),
    _RV32_2(0x110de6, 0x5555),
    _RV32_2(0x110de8, 0x0055),

//=====================================================================
//MIU0 inivec setting start
//=====================================================================
//-----------------
//program DLL
//-----------------
    _RV32_2(0x110d62, 0x007f),
    _RV32_2(0x110d64, 0xf000),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00cf),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c3),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c3),
    _RV32_2(0x110d60, 0x00cb),
    _RV32_2(0x110d60, 0x00c2),
    _RV32_2(0x110d60, 0x00c0),
    _RV32_2(0x110d60, 0x33c8),
    _RV32_2(0x110d90, 0xf0f1),
//--------------------------- 
//program dig general setting 
//--------------------------- 
    _RV32_2(0x10122c, 0x8001),
    _RV32_2(0x101252, 0xffff),
    _RV32_2(0x101272, 0xffff),
    _RV32_2(0x101292, 0xffff),
    _RV32_2(0x1012b2, 0xffff),
    _RV32_2(0x161512, 0xffff),
    _RV32_2(0x161532, 0xffff),
//---------------------       
// Default BW setting         
//---------------------       
    _RV32_2(0x101240, 0x8015),
    _RV32_2(0x101260, 0x8015),
    _RV32_2(0x101280, 0x8015),
    _RV32_2(0x1012a0, 0x8015),
    _RV32_2(0x161500, 0x8015),
    _RV32_2(0x161520, 0x8015),
//--------------------------- 
//program ana general setting 
//--------------------------- 
    _RV32_2(0x110d70, 0x0800),
    _RV32_2(0x110d5a, 0xaaaa),
    _RV32_2(0x110d5c, 0xaaaa),
    _RV32_2(0x110d5e, 0xaaaa),
    _RV32_2(0x110d1a, 0x8110),
    _RV32_2(0x110d1c, 0x0020),
    _RV32_2(0x110d08, 0x003f),
    _RV32_2(0x110d54, 0xc000),
//--------------------------- 
//Toggle reset & disable GPIO 
//--------------------------- 
    _RV32_2(0x10121e, 0x0c01),
    _RV32_2(0x10121e, 0x0c00),
    _RV32_2(0x110d00, 0x2010),
    _RV32_2(0x110d00, 0x0000),
    _RV32_2(0x110d18, 0x0000),
    _RV32_2(0x110d7c, 0x0000),
//--------------------------- 
//select Mapping              
//--------------------------- 
    _RV32_2(0x110d00, 0x0000),
//-----------                 
// DQSM RST                   
//-----------                 
    _RV32_2(0x110d1e, 0x0005),
    _RV32_2(0x110d1e, 0x000f),
    _RV32_2(0x110d1e, 0x0005),
    _RV32_2(0x101200, 0x0000),

#endif

#else
    #error "Invalid DRAM Setting"
#endif

    _END_OF_TBL32_,
    MIU_VER
};

#ifndef CONFIG_MIU1_DRAM_NONE
const MS_REG_INIT MIU1_DDR_Init[] =
{
#if defined(CONFIG_MIU1_DDR3_1666)

#if defined(CONFIG_MIU1_4X_MODE)
    #error "No Support MIU 4x Mode"
#else

//================================================
// set DDRPLL1_1600MHz        
//================================================
    _RV32_2(0x161678, 0x0001),
    _RV32_2(0x16168a, 0x0001),
    _RV32_2(0x161624, 0x1000),
    _RV32_2(0x161624, 0x0000),
    _RV32_2(0x161636, 0x0400),
    _RV32_2(0x161634, 0x2004),
    _RV32_2(0x161630, 0x7236),
    _RV32_2(0x161632, 0x0023),
    _RV32_2(0x161622, 0x0004),

//================================================
// set DDR3-16-8X-CL13_1866        
//================================================
    _RV32_2(0x100602, 0x03a3),
    _RV32_2(0x100604, 0x000c),
    _RV32_2(0x100606, 0x1430), //[12:12] reg_cke_always_on	
    _RV32_2(0x100608, 0x1cbb),
    _RV32_2(0x10060a, 0x2766),
    _RV32_2(0x10060c, 0xc6c8),
    _RV32_2(0x10060e, 0x4080),
    _RV32_2(0x100610, 0x1d70),
    _RV32_2(0x100612, 0x4004),
    _RV32_2(0x100614, 0x8018),
    _RV32_2(0x100616, 0xc000),
    _RV32_2(0x100628, 0x0030),
    _RV32_2(0x1006d2, 0x9000), //dram size = 512MB
    _RV32_2(0x161602, 0xaaaa),
    _RV32_2(0x161604, 0x0080),
    _RV32_2(0x16160a, 0x1133),
    _RV32_2(0x16160e, 0x0089),
    _RV32_2(0x16162e, 0x1111),
    _RV32_2(0x161638, 0xbb00),
    _RV32_2(0x16163a, 0x2022),
    _RV32_2(0x16163c, 0x1244),
    _RV32_2(0x16163e, 0x1033),
    _RV32_2(0x161648, 0xcc00),
    _RV32_2(0x16164a, 0x3040),
    _RV32_2(0x16164c, 0x3344),
    _RV32_2(0x16164e, 0x0044),
    _RV32_2(0x161650, 0x1111),
    _RV32_2(0x161652, 0x0022),
    _RV32_2(0x161658, 0x0a0a),
    _RV32_2(0x16165a, 0xaaaa),
    _RV32_2(0x16165c, 0xaaaa),
    _RV32_2(0x16165e, 0xaaaa),
    _RV32_2(0x161674, 0x0606),
    _RV32_2(0x161676, 0x0606),
    _RV32_2(0x16168a, 0x0001),
    _RV32_2(0x161694, 0x0107),
    _RV32_2(0x161696, 0x0207),
    _RV32_2(0x16166c, 0x1010),
    _RV32_2(0x16166e, 0x1010),
    _RV32_2(0x1616a0, 0x4735),
    _RV32_2(0x1616a2, 0x0516),
    _RV32_2(0x1616a4, 0x6161),
    _RV32_2(0x1616a6, 0x6073),
    _RV32_2(0x1616a8, 0x4413),
    _RV32_2(0x1616aa, 0x0524),
    _RV32_2(0x1616ac, 0x5131),
    _RV32_2(0x1616ae, 0x4071),
    _RV32_2(0x1616b8, 0x3333),
    _RV32_2(0x1616ba, 0x0333),
    _RV32_2(0x1616bc, 0x0333),
    _RV32_2(0x1616be, 0x0333),
    _RV32_2(0x1616d0, 0x5555),
    _RV32_2(0x1616d2, 0x5555),
    _RV32_2(0x1616d4, 0x5555),
    _RV32_2(0x1616d6, 0x5555),
    _RV32_2(0x1616d8, 0x0055),
    _RV32_2(0x1616e0, 0x4444),
    _RV32_2(0x1616e2, 0x4444),
    _RV32_2(0x1616e4, 0x4444),
    _RV32_2(0x1616e6, 0x4444),
    _RV32_2(0x1616e8, 0x0044),

//=====================================================================
//MIU1 inivec setting start
//=====================================================================
//-----------------
//program DLL
//-----------------
    _RV32_2(0x161662, 0x007f),
    _RV32_2(0x161664, 0xf000),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00cf),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c3),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c3),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c2),
    _RV32_2(0x161660, 0x00c0),
    _RV32_2(0x161660, 0x33c8),
    _RV32_2(0x161690, 0xf0f1),
//--------------------------- 
//program dig general setting 
//--------------------------- 
    _RV32_2(0x10062c, 0x8001),
    _RV32_2(0x100652, 0xffff),
    _RV32_2(0x100672, 0xffff),
    _RV32_2(0x100692, 0xffff),
    _RV32_2(0x1006b2, 0xffff),
    _RV32_2(0x162212, 0xffff),
    _RV32_2(0x162232, 0xffff),
//---------------------       
// Default BW setting         
//---------------------       
    _RV32_2(0x100640, 0x8015),
    _RV32_2(0x100660, 0x8015),
    _RV32_2(0x100680, 0x8015),
    _RV32_2(0x1006a0, 0x8015),
    _RV32_2(0x162200, 0x8015),
    _RV32_2(0x162220, 0x8015),
//--------------------------- 
//program ana general setting 
//--------------------------- 
    _RV32_2(0x161670, 0x0800),
    _RV32_2(0x16165a, 0xaaaa),
    _RV32_2(0x16165c, 0xaaaa),
    _RV32_2(0x16165e, 0xaaaa),
    _RV32_2(0x16161a, 0x8110),
    _RV32_2(0x16161c, 0x0020),
    _RV32_2(0x161608, 0x003f),
    _RV32_2(0x161654, 0xc000),
//--------------------------- 
//Toggle reset & disable GPIO 
//--------------------------- 
    _RV32_2(0x10061e, 0x0c01),
    _RV32_2(0x10061e, 0x0c00),
    _RV32_2(0x161600, 0x2010),
    _RV32_2(0x161600, 0x0000),
    _RV32_2(0x161618, 0x0000),
    _RV32_2(0x16167c, 0x0000),
//--------------------------- 
//select Mapping              
//--------------------------- 
    _RV32_2(0x161600, 0x0000),
//-----------                 
// DQSM RST                   
//-----------                 
    _RV32_2(0x16161e, 0x0005),
    _RV32_2(0x16161e, 0x000f),
    _RV32_2(0x16161e, 0x0005),
    _RV32_2(0x100600, 0x0000),

#endif

#elif defined(CONFIG_MIU1_DDR3_1866)

#if defined(CONFIG_MIU1_4X_MODE)
    #error "No Support MIU 4x Mode"
#else
//================================================
// set DDRPLL1_1866MHz        
//================================================
    _RV32_2(0x161678, 0x0001),
    _RV32_2(0x16168a, 0x0001),
    _RV32_2(0x161624, 0x1000),
    _RV32_2(0x161624, 0x0000),
    _RV32_2(0x161636, 0x0400),
    _RV32_2(0x161634, 0x2004),
    _RV32_2(0x161630, 0x8f5c),
    _RV32_2(0x161632, 0x001e),
    _RV32_2(0x161622, 0x0004),

//================================================
// set DDR3-16-8X-CL13_1866        
//================================================
    _RV32_2(0x100602, 0x03a3),
    _RV32_2(0x100604, 0x000c),
    _RV32_2(0x100606, 0x1534), //[12:12] reg_cke_always_on	
    _RV32_2(0x100608, 0x20dd),
    _RV32_2(0x10060a, 0x2e76),
    _RV32_2(0x10060c, 0xc7e9),
    _RV32_2(0x10060e, 0x40f0),
    _RV32_2(0x100610, 0x1f14),
    _RV32_2(0x100612, 0x4004),
    _RV32_2(0x100614, 0x8020),
    _RV32_2(0x100616, 0xc000),
    _RV32_2(0x100628, 0x0040),
    _RV32_2(0x1006d2, 0x9000), //dram size = 512MB
    _RV32_2(0x161602, 0xaaaa),
    _RV32_2(0x161604, 0x0080),
    _RV32_2(0x16160a, 0x1133),
    _RV32_2(0x16160e, 0x0089),
    _RV32_2(0x16162e, 0x1111),
    _RV32_2(0x161638, 0xbb00),
    _RV32_2(0x16163a, 0x2022),
    _RV32_2(0x16163c, 0x1244),
    _RV32_2(0x16163e, 0x1033),
    _RV32_2(0x161648, 0xcc00),
    _RV32_2(0x16164a, 0x3040),
    _RV32_2(0x16164c, 0x3344),
    _RV32_2(0x16164e, 0x0044),
    _RV32_2(0x161650, 0x1111),
    _RV32_2(0x161652, 0x0022),
    _RV32_2(0x161658, 0x0a0a),
    _RV32_2(0x16165a, 0xaaaa),
    _RV32_2(0x16165c, 0xaaaa),
    _RV32_2(0x16165e, 0xaaaa),
    _RV32_2(0x161674, 0x0606),
    _RV32_2(0x161676, 0x0606),
    _RV32_2(0x16168a, 0x0001),
    _RV32_2(0x161694, 0x0107),
    _RV32_2(0x161696, 0x0207),
    _RV32_2(0x16166c, 0x1010),
    _RV32_2(0x16166e, 0x1010),
    _RV32_2(0x1616a0, 0x4735),
    _RV32_2(0x1616a2, 0x0516),
    _RV32_2(0x1616a4, 0x6161),
    _RV32_2(0x1616a6, 0x6073),
    _RV32_2(0x1616a8, 0x4413),
    _RV32_2(0x1616aa, 0x0524),
    _RV32_2(0x1616ac, 0x5131),
    _RV32_2(0x1616ae, 0x4071),
    _RV32_2(0x1616b8, 0x3333),
    _RV32_2(0x1616ba, 0x0333),
    _RV32_2(0x1616bc, 0x0333),
    _RV32_2(0x1616be, 0x0333),
    _RV32_2(0x1616d0, 0x5555),
    _RV32_2(0x1616d2, 0x5555),
    _RV32_2(0x1616d4, 0x5555),
    _RV32_2(0x1616d6, 0x5555),
    _RV32_2(0x1616d8, 0x0055),
    _RV32_2(0x1616e0, 0x4444),
    _RV32_2(0x1616e2, 0x4444),
    _RV32_2(0x1616e4, 0x4444),
    _RV32_2(0x1616e6, 0x4444),
    _RV32_2(0x1616e8, 0x0044),

//=====================================================================
//MIU1 inivec setting start
//=====================================================================
//-----------------
//program DLL
//-----------------
    _RV32_2(0x161662, 0x007f),
    _RV32_2(0x161664, 0xf000),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00cf),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c3),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c3),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c2),
    _RV32_2(0x161660, 0x00c0),
    _RV32_2(0x161660, 0x33c8),
    _RV32_2(0x161690, 0xf0f1),
//--------------------------- 
//program dig general setting 
//--------------------------- 
    _RV32_2(0x10062c, 0x8001),
    _RV32_2(0x100652, 0xffff),
    _RV32_2(0x100672, 0xffff),
    _RV32_2(0x100692, 0xffff),
    _RV32_2(0x1006b2, 0xffff),
    _RV32_2(0x162212, 0xffff),
    _RV32_2(0x162232, 0xffff),
//---------------------       
// Default BW setting         
//---------------------       
    _RV32_2(0x100640, 0x8015),
    _RV32_2(0x100660, 0x8015),
    _RV32_2(0x100680, 0x8015),
    _RV32_2(0x1006a0, 0x8015),
    _RV32_2(0x162200, 0x8015),
    _RV32_2(0x162220, 0x8015),
//--------------------------- 
//program ana general setting 
//--------------------------- 
    _RV32_2(0x161670, 0x0800),
    _RV32_2(0x16165a, 0xaaaa),
    _RV32_2(0x16165c, 0xaaaa),
    _RV32_2(0x16165e, 0xaaaa),
    _RV32_2(0x16161a, 0x8110),
    _RV32_2(0x16161c, 0x0020),
    _RV32_2(0x161608, 0x003f),
    _RV32_2(0x161654, 0xc000),
//--------------------------- 
//Toggle reset & disable GPIO 
//--------------------------- 
    _RV32_2(0x10061e, 0x0c01),
    _RV32_2(0x10061e, 0x0c00),
    _RV32_2(0x161600, 0x2010),
    _RV32_2(0x161600, 0x0000),
    _RV32_2(0x161618, 0x0000),
    _RV32_2(0x16167c, 0x0000),
//--------------------------- 
//select Mapping              
//--------------------------- 
    _RV32_2(0x161600, 0x0000),
//-----------                 
// DQSM RST                   
//-----------                 
    _RV32_2(0x16161e, 0x0005),
    _RV32_2(0x16161e, 0x000f),
    _RV32_2(0x16161e, 0x0005),
    _RV32_2(0x100600, 0x0000),

#endif

#elif defined(CONFIG_MIU1_DDR3_2133)

#if defined(CONFIG_MIU1_4X_MODE)
    #error "No Support MIU 4x Mode"
#else
//================================================
// set DDRPLL1_2133MHz        
//================================================
    _RV32_2(0x161678, 0x0001),
    _RV32_2(0x16168a, 0x0001),
    _RV32_2(0x161624, 0x1000),
    _RV32_2(0x161624, 0x0000),
    _RV32_2(0x161636, 0x0400),
    _RV32_2(0x161634, 0x2004),
    _RV32_2(0x161630, 0xffff),
    _RV32_2(0x161632, 0x001a),
    _RV32_2(0x161622, 0x0004),

//================================================
// set DDR3-16-8X-CL13_1866        
//================================================
    _RV32_2(0x100602, 0x03a3),
    _RV32_2(0x100604, 0x000c),
    _RV32_2(0x100606, 0x1640), //[12:12] reg_cke_always_on	
    _RV32_2(0x100608, 0x24ee),
    _RV32_2(0x10060a, 0x3487),
    _RV32_2(0x10060c, 0xb80a),
    _RV32_2(0x10060e, 0xc0ab),
    _RV32_2(0x100610, 0x1124),
    _RV32_2(0x100612, 0x4004),
    _RV32_2(0x100614, 0x8028),
    _RV32_2(0x100616, 0xc000),
    _RV32_2(0x100628, 0x0050),
    _RV32_2(0x1006d2, 0x9000), //dram size = 512MB
    _RV32_2(0x161602, 0xaaaa),
    _RV32_2(0x161604, 0x0080),
    _RV32_2(0x16160a, 0x1133),
    _RV32_2(0x16160e, 0x0089),
    _RV32_2(0x16162e, 0x1111),
    _RV32_2(0x161638, 0xbb00),
    _RV32_2(0x16163a, 0x2022),
    _RV32_2(0x16163c, 0x1244),
    _RV32_2(0x16163e, 0x1033),
    _RV32_2(0x161648, 0xcc00),
    _RV32_2(0x16164a, 0x3040),
    _RV32_2(0x16164c, 0x3344),
    _RV32_2(0x16164e, 0x0044),
    _RV32_2(0x161650, 0x1111),
    _RV32_2(0x161652, 0x0022),
    _RV32_2(0x161658, 0x0a0a),
    _RV32_2(0x16165a, 0xaaaa),
    _RV32_2(0x16165c, 0xaaaa),
    _RV32_2(0x16165e, 0xaaaa),
    _RV32_2(0x161674, 0x0606),
    _RV32_2(0x161676, 0x0606),
    _RV32_2(0x16168a, 0x0001),
    _RV32_2(0x161694, 0x0107),
    _RV32_2(0x161696, 0x0207),
    _RV32_2(0x16166c, 0x1010),
    _RV32_2(0x16166e, 0x1010),
    _RV32_2(0x1616a0, 0x4735),
    _RV32_2(0x1616a2, 0x0516),
    _RV32_2(0x1616a4, 0x6161),
    _RV32_2(0x1616a6, 0x6073),
    _RV32_2(0x1616a8, 0x4413),
    _RV32_2(0x1616aa, 0x0524),
    _RV32_2(0x1616ac, 0x5131),
    _RV32_2(0x1616ae, 0x4071),
    _RV32_2(0x1616b8, 0x3333),
    _RV32_2(0x1616ba, 0x0333),
    _RV32_2(0x1616bc, 0x0333),
    _RV32_2(0x1616be, 0x0333),
    _RV32_2(0x1616d0, 0x5555),
    _RV32_2(0x1616d2, 0x5555),
    _RV32_2(0x1616d4, 0x5555),
    _RV32_2(0x1616d6, 0x5555),
    _RV32_2(0x1616d8, 0x0055),
    _RV32_2(0x1616e0, 0x4444),
    _RV32_2(0x1616e2, 0x4444),
    _RV32_2(0x1616e4, 0x4444),
    _RV32_2(0x1616e6, 0x4444),
    _RV32_2(0x1616e8, 0x0044),

//=====================================================================
//MIU1 inivec setting start
//=====================================================================
//-----------------
//program DLL
//-----------------
    _RV32_2(0x161662, 0x007f),
    _RV32_2(0x161664, 0xf000),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00cf),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c3),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c3),
    _RV32_2(0x161660, 0x00cb),
    _RV32_2(0x161660, 0x00c2),
    _RV32_2(0x161660, 0x00c0),
    _RV32_2(0x161660, 0x33c8),
    _RV32_2(0x161690, 0xf0f1),
//---------------------------
//program dig general setting
//---------------------------
    _RV32_2(0x10062c, 0x8001),
    _RV32_2(0x100652, 0xffff),
    _RV32_2(0x100672, 0xffff),
    _RV32_2(0x100692, 0xffff),
    _RV32_2(0x1006b2, 0xffff),
    _RV32_2(0x162212, 0xffff),
    _RV32_2(0x162232, 0xffff),
//---------------------
// Default BW setting  
//---------------------
    _RV32_2(0x100640, 0x8015),
    _RV32_2(0x100660, 0x8015),
    _RV32_2(0x100680, 0x8015),
    _RV32_2(0x1006a0, 0x8015),
    _RV32_2(0x162200, 0x8015),
    _RV32_2(0x162220, 0x8015),
//---------------------------
//program ana general setting
//---------------------------
    _RV32_2(0x161670, 0x0800),
    _RV32_2(0x16165a, 0xaaaa),
    _RV32_2(0x16165c, 0xaaaa),
    _RV32_2(0x16165e, 0xaaaa),
    _RV32_2(0x16161a, 0x8110),
    _RV32_2(0x16161c, 0x0020),
    _RV32_2(0x161608, 0x003f),
    _RV32_2(0x161654, 0xc000),
//---------------------------
//Toggle reset & disable GPIO
//---------------------------
    _RV32_2(0x10061e, 0x0c01),
    _RV32_2(0x10061e, 0x0c00),
    _RV32_2(0x161600, 0x2010),
    _RV32_2(0x161600, 0x0000),
    _RV32_2(0x161618, 0x0000),
    _RV32_2(0x16167c, 0x0000),
//---------------------------
//select Mapping
//---------------------------
    _RV32_2(0x161600, 0x0000),
//-----------
// DQSM RST  
//-----------
    _RV32_2(0x16161e, 0x0005),
    _RV32_2(0x16161e, 0x000f),
    _RV32_2(0x16161e, 0x0005),
    _RV32_2(0x100600, 0x0000),

#endif

#else
    #error "Invalid DRAM Selection"
#endif

    _END_OF_TBL32_,
};
#endif

#endif  //ENABLE_MSTAR_BD_MST206B_D01A_S_MIAMI

#endif /* _MIU_MST206B_D01A_S_MIAMI_H_ */
