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
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "datatype.h"
#include "Board.h"
#include "c_riubase.h"
#include "hwreg_M12.h"
#include "chip/bond.h"
#include "drvGlobal.h"
#include "drvPadConf.h"

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#define _MapBase_nonPM_M12 0xA0200000
#define _MapBase_PM_M12    0xA0000000

#define _MEMMAP_nonPM_  _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_     _RVM1(0x0000, 0x00, 0xFF)

static U32 u32MapBase;

static void MDrv_PAD_WriteByte(U32 u32RegAddr, U8 u8Val)
{
    ((volatile U8*)(u32MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)] = u8Val;
}

static U8 MDrv_PAD_ReadByte(U32 u32RegAddr)
{
    return ((volatile U8*)(u32MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)];
}

static void MDrv_PAD_WriteByteMask(U32 u32Reg_addr, U8 u8Value, U8 u8Mask)
{
    U8 u8Val = MDrv_PAD_ReadByte(u32Reg_addr);

    u8Val = (u8Val & ~(u8Mask)) | (u8Value & u8Mask);
    MDrv_PAD_WriteByte(u32Reg_addr, u8Val);
}

//static code U8 padInitTbl[] =
volatile U8 code padInitTbl[]= //__attribute__((__section__ (".isp_info"))) =
{
    0x39, 0xB6, 0x5B, 0x53,     // magic code for ISP_Tool

    // programable device number
    // spi flash count
    2,
    //1 + (PIN_SPI_CZ1 != 0) + (PIN_SPI_CZ2 != 0) + (PIN_SPI_CZ3 != 0),
    0x00,                       // nor
    0x00,                       // nand
    0x00,                       // reserved
    0x00,                       // reserved
    0x00,                       // reserved

//---------------------------------------------------------------------
// GPIO Configuartion
//---------------------------------------------------------------------
    _MEMMAP_nonPM_,

#if(PAD_TCON0_IS_GPIO != GPIO_NONE)
#define PAD_TCON0_OEN (PAD_TCON0_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_TCON0_OUT (PAD_TCON0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e5e, PAD_TCON0_OUT, BIT0),
    _RVM1(0x1e60, PAD_TCON0_OEN, BIT0),
    //reg_tconconfig[0] = 0b
    _RVM1(0x1ef2, 0, BIT0 ),   //reg[101ef2]#0 = 0b
    //reg_seconduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1~#0 = 00b
    //reg_3d_lr_config[2:0] = 000b
    _RVM1(0x1e10, 0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    //reg_usbdrvvbusconfig[1:0] = 00b
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~#0 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON1_IS_GPIO != GPIO_NONE)
#define PAD_TCON1_OEN (PAD_TCON1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON1_OUT (PAD_TCON1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e5e, PAD_TCON1_OUT, BIT1),
    _RVM1(0x1e60, PAD_TCON1_OEN, BIT1),
    //reg_tconconfig[1] = 0b
    _RVM1(0x1ef2, 0, BIT1 ),   //reg[101ef2]#1 = 0b
    //reg_seconduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1~#0 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON2_IS_GPIO != GPIO_NONE)
#define PAD_TCON2_OEN (PAD_TCON2_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_TCON2_OUT (PAD_TCON2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e5e, PAD_TCON2_OUT, BIT2),
    _RVM1(0x1e60, PAD_TCON2_OEN, BIT2),
    //reg_tconconfig[2] = 0b
    _RVM1(0x1ef2, 0, BIT2 ),   //reg[101ef2]#2 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON3_IS_GPIO != GPIO_NONE)
#define PAD_TCON3_OEN (PAD_TCON3_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_TCON3_OUT (PAD_TCON3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e5e, PAD_TCON3_OUT, BIT3),
    _RVM1(0x1e60, PAD_TCON3_OEN, BIT3),
    //reg_tconconfig[3] = 0b
    _RVM1(0x1ef2, 0, BIT3 ),   //reg[101ef2]#3 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON4_IS_GPIO != GPIO_NONE)
#define PAD_TCON4_OEN (PAD_TCON4_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_TCON4_OUT (PAD_TCON4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e5e, PAD_TCON4_OUT, BIT4),
    _RVM1(0x1e60, PAD_TCON4_OEN, BIT4),
    //reg_tconconfig[4] = 0b
    _RVM1(0x1ef2, 0, BIT4 ),   //reg[101ef2]#4 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON5_IS_GPIO != GPIO_NONE)
#define PAD_TCON5_OEN (PAD_TCON5_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_TCON5_OUT (PAD_TCON5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e5e, PAD_TCON5_OUT, BIT5),
    _RVM1(0x1e60, PAD_TCON5_OEN, BIT5),
    //reg_tconconfig[5] = 0b
    _RVM1(0x1ef2, 0, BIT5 ),   //reg[101ef2]#5 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON6_IS_GPIO != GPIO_NONE)
#define PAD_TCON6_OEN (PAD_TCON6_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_TCON6_OUT (PAD_TCON6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e5e, PAD_TCON6_OUT, BIT6),
    _RVM1(0x1e60, PAD_TCON6_OEN, BIT6),
    //reg_tconconfig[6] = 0b
    _RVM1(0x1ef2, 0, BIT6 ),   //reg[101ef2]#6 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON7_IS_GPIO != GPIO_NONE)
#define PAD_TCON7_OEN (PAD_TCON7_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_TCON7_OUT (PAD_TCON7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e5e, PAD_TCON7_OUT, BIT7),
    _RVM1(0x1e60, PAD_TCON7_OEN, BIT7),
    //reg_tconconfig[7] = 0b
    _RVM1(0x1ef2, 0, BIT7 ),   //reg[101ef2]#7 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON8_IS_GPIO != GPIO_NONE)
#define PAD_TCON8_OEN (PAD_TCON8_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_TCON8_OUT (PAD_TCON8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e5f, PAD_TCON8_OUT, BIT0),
    _RVM1(0x1e61, PAD_TCON8_OEN, BIT0),
    //reg_tconconfig[8] = 0b
    _RVM1(0x1ef3, 0, BIT0 ),   //reg[101ef3]#0 = 0b
#endif

#if(PAD_TCON9_IS_GPIO != GPIO_NONE)
#define PAD_TCON9_OEN (PAD_TCON9_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON9_OUT (PAD_TCON9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e5f, PAD_TCON9_OUT, BIT1),
    _RVM1(0x1e61, PAD_TCON9_OEN, BIT1),
    //reg_tconconfig[9] = 0b
    _RVM1(0x1ef3, 0, BIT1 ),   //reg[101ef3]#1 = 0b
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_fastuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5~#4 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON10_IS_GPIO != GPIO_NONE)
#define PAD_TCON10_OEN (PAD_TCON10_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_TCON10_OUT (PAD_TCON10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e5f, PAD_TCON10_OUT, BIT2),
    _RVM1(0x1e61, PAD_TCON10_OEN, BIT2),
    //reg_tconconfig[10] = 0b
    _RVM1(0x1ef3, 0, BIT2 ),   //reg[101ef3]#2 = 0b
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_fastuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5~#4 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON11_IS_GPIO != GPIO_NONE)
#define PAD_TCON11_OEN (PAD_TCON11_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_TCON11_OUT (PAD_TCON11_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e52, PAD_TCON11_OUT, BIT0),
    _RVM1(0x1e54, PAD_TCON11_OEN, BIT0),
    //reg_tconconfig[11] = 0b
    _RVM1(0x1ef3, 0, BIT3 ),   //reg[101ef3]#3 = 0b
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON12_IS_GPIO != GPIO_NONE)
#define PAD_TCON12_OEN (PAD_TCON12_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON12_OUT (PAD_TCON12_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e52, PAD_TCON12_OUT, BIT1),
    _RVM1(0x1e54, PAD_TCON12_OEN, BIT1),
    //reg_tconconfig[12] = 0b
    _RVM1(0x1ef3, 0, BIT4 ),   //reg[101ef3]#4 = 0b
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON13_IS_GPIO != GPIO_NONE)
#define PAD_TCON13_OEN (PAD_TCON13_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_TCON13_OUT (PAD_TCON13_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e52, PAD_TCON13_OUT, BIT2),
    _RVM1(0x1e54, PAD_TCON13_OEN, BIT2),
    //reg_tconconfig[13] = 0b
    _RVM1(0x1ef3, 0, BIT5 ),   //reg[101ef3]#5 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON14_IS_GPIO != GPIO_NONE)
#define PAD_TCON14_OEN (PAD_TCON14_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_TCON14_OUT (PAD_TCON14_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e52, PAD_TCON14_OUT, BIT3),
    _RVM1(0x1e54, PAD_TCON14_OEN, BIT3),
    //reg_tconconfig[14] = 0b
    _RVM1(0x1ef3, 0, BIT6 ),   //reg[101ef3]#6 = 0b
    //reg_i2sinconfig = 0b
    _RVM1(0x1eae, 0, BIT3 ),   //reg[101eae]#3 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_TCON15_IS_GPIO != GPIO_NONE)
#define PAD_TCON15_OEN (PAD_TCON15_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_TCON15_OUT (PAD_TCON15_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e52, PAD_TCON15_OUT, BIT4),
    _RVM1(0x1e54, PAD_TCON15_OEN, BIT4),
    //reg_tconconfig[15] = 0b
    _RVM1(0x1ef3, 0, BIT7 ),   //reg[101ef3]#7 = 0b
    //reg_i2sinconfig = 0b
    _RVM1(0x1eae, 0, BIT3 ),   //reg[101eae]#3 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON16_IS_GPIO != GPIO_NONE)
#define PAD_TCON16_OEN (PAD_TCON16_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_TCON16_OUT (PAD_TCON16_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e52, PAD_TCON16_OUT, BIT5),
    _RVM1(0x1e54, PAD_TCON16_OEN, BIT5),
    //reg_tconconfig[16] = 0b
    _RVM1(0x1ef4, 0, BIT0 ),   //reg[101ef4]#0 = 0b
    //reg_i2sinconfig = 0b
    _RVM1(0x1eae, 0, BIT3 ),   //reg[101eae]#3 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON17_IS_GPIO != GPIO_NONE)
#define PAD_TCON17_OEN (PAD_TCON17_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_TCON17_OUT (PAD_TCON17_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e52, PAD_TCON17_OUT, BIT6),
    _RVM1(0x1e54, PAD_TCON17_OEN, BIT6),
    //reg_tconconfig[17] = 0b
    _RVM1(0x1ef4, 0, BIT1 ),   //reg[101ef4]#1 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON18_IS_GPIO != GPIO_NONE)
#define PAD_TCON18_OEN (PAD_TCON18_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_TCON18_OUT (PAD_TCON18_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e52, PAD_TCON18_OUT, BIT7),
    _RVM1(0x1e54, PAD_TCON18_OEN, BIT7),
    //reg_tconconfig[18] = 0b
    _RVM1(0x1ef4, 0, BIT2 ),   //reg[101ef4]#2 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON19_IS_GPIO != GPIO_NONE)
#define PAD_TCON19_OEN (PAD_TCON19_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_TCON19_OUT (PAD_TCON19_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e53, PAD_TCON19_OUT, BIT0),
    _RVM1(0x1e55, PAD_TCON19_OEN, BIT0),
    //reg_tconconfig[19] = 0b
    _RVM1(0x1ef4, 0, BIT3 ),   //reg[101ef4]#3 = 0b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON20_IS_GPIO != GPIO_NONE)
#define PAD_TCON20_OEN (PAD_TCON20_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_TCON20_OUT (PAD_TCON20_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e53, PAD_TCON20_OUT, BIT1),
    _RVM1(0x1e55, PAD_TCON20_OEN, BIT1),
    //reg_tconconfig[20] = 0b
    _RVM1(0x1ef4, 0, BIT4 ),   //reg[101ef4]#4 = 0b
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_TCON21_IS_GPIO != GPIO_NONE)
#define PAD_TCON21_OEN (PAD_TCON21_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_TCON21_OUT (PAD_TCON21_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e53, PAD_TCON21_OUT, BIT2),
    _RVM1(0x1e55, PAD_TCON21_OEN, BIT2),
    //reg_tconconfig[21] = 0b
    _RVM1(0x1ef4, 0, BIT5 ),   //reg[101ef4]#5 = 0b
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
#endif

#if(PAD_PWM3_IS_GPIO != GPIO_NONE)
#define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e85, PAD_PWM3_OUT, BIT7),
    _RVM1(0x1e87, PAD_PWM3_OEN, BIT7),
    //reg_pwm3config = 0b
    _RVM1(0x1e40, 0, BIT7 ),   //reg[101e40]#7 = 0b
#endif

#if(PAD_PWM2_IS_GPIO != GPIO_NONE)
#define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e85, PAD_PWM2_OUT, BIT6),
    _RVM1(0x1e87, PAD_PWM2_OEN, BIT6),
    //reg_pwm2config = 0b
    _RVM1(0x1e40, 0, BIT6 ),   //reg[101e40]#6 = 0b
#endif

#if(PAD_PWM1_IS_GPIO != GPIO_NONE)
#define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e85, PAD_PWM1_OUT, BIT5),
    _RVM1(0x1e87, PAD_PWM1_OEN, BIT5),
    //reg_pwm1config = 0b
    _RVM1(0x1e40, 0, BIT5 ),   //reg[101e40]#5 = 0b
#endif

#if(PAD_PWM0_IS_GPIO != GPIO_NONE)
#define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e85, PAD_PWM0_OUT, BIT4),
    _RVM1(0x1e87, PAD_PWM0_OEN, BIT4),
    //reg_pwm0config = 0b
    _RVM1(0x1e40, 0, BIT4 ),   //reg[101e40]#4 = 0b
#endif

#if(PAD_LVSYNC_IS_GPIO != GPIO_NONE)
#define PAD_LVSYNC_OEN (PAD_LVSYNC_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_LVSYNC_OUT (PAD_LVSYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x329e, PAD_LVSYNC_OUT, BIT0),
    _RVM1(0x32a2, PAD_LVSYNC_OEN, BIT0),
    //reg_output_conf[1:0]
    _RVM1(0x32da, 0, BIT1|BIT0 ),   //reg[1032da]#1~#0 = 00b
    //reg_ext_data_en[0]
    _RVM1(0x328c, BIT0 , BIT0 ),   //reg[10328c]#0 = 1b
    //reg_gpo_sel[0]
    _RVM1(0x329a, BIT0 , BIT0 ),   //reg[10329a]#0 = 1b
#endif

#if(PAD_LHSYNC_IS_GPIO != GPIO_NONE)
#define PAD_LHSYNC_OEN (PAD_LHSYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_LHSYNC_OUT (PAD_LHSYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x329e, PAD_LHSYNC_OUT, BIT1),
    _RVM1(0x32a2, PAD_LHSYNC_OEN, BIT1),
    //reg_output_conf[1:0]
    _RVM1(0x32da, 0, BIT1|BIT0 ),   //reg[1032da]#1~#0 = 00b
    //reg_ext_data_en[1]
    _RVM1(0x328c, BIT1 , BIT1 ),   //reg[10328c]#1 = 1b
    //reg_gpo_sel[1]
    _RVM1(0x329a, BIT1 , BIT1 ),   //reg[10329a]#1 = 1b
#endif

#if(PAD_LDE_IS_GPIO != GPIO_NONE)
#define PAD_LDE_OEN (PAD_LDE_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_LDE_OUT (PAD_LDE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x329e, PAD_LDE_OUT, BIT2),
    _RVM1(0x32a2, PAD_LDE_OEN, BIT2),
    //reg_output_conf[3:2]
    _RVM1(0x32da, 0, BIT3|BIT2 ),   //reg[1032da]#3~#2 = 00b
    //reg_ext_data_en[2]
    _RVM1(0x328c, BIT2 , BIT2 ),   //reg[10328c]#2 = 1b
    //reg_gpo_sel[2]
    _RVM1(0x329a, BIT2 , BIT2 ),   //reg[10329a]#2 = 1b
#endif

#if(PAD_LCK_IS_GPIO != GPIO_NONE)
#define PAD_LCK_OEN (PAD_LCK_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_LCK_OUT (PAD_LCK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x329e, PAD_LCK_OUT, BIT3),
    _RVM1(0x32a2, PAD_LCK_OEN, BIT3),
    //reg_output_conf[3:2]
    _RVM1(0x32da, 0, BIT3|BIT2 ),   //reg[1032da]#3~#2 = 00b
    //reg_ext_data_en[3]
    _RVM1(0x328c, BIT3 , BIT3 ),   //reg[10328c]#3 = 1b
    //reg_gpo_sel[3]
    _RVM1(0x329a, BIT3 , BIT3 ),   //reg[10329a]#3 = 1b
#endif

#if(PAD_R_ODD7_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD7_OEN (PAD_R_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_R_ODD7_OUT (PAD_R_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x329e, PAD_R_ODD7_OUT, BIT4),
    _RVM1(0x32a2, PAD_R_ODD7_OEN, BIT4),
    //reg_output_conf[5:4]
    _RVM1(0x32da, 0, BIT5|BIT4 ),   //reg[1032da]#5~#4 = 00b
    //reg_ext_data_en[4]
    _RVM1(0x328c, BIT4 , BIT4 ),   //reg[10328c]#4 = 1b
    //reg_gpo_sel[12]
    _RVM1(0x329a, BIT4 , BIT4 ),   //reg[10329a]#4 = 1b
#endif

#if(PAD_R_ODD6_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD6_OEN (PAD_R_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_R_ODD6_OUT (PAD_R_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x329e, PAD_R_ODD6_OUT, BIT5),
    _RVM1(0x32a2, PAD_R_ODD6_OEN, BIT5),
    //reg_output_conf[5:4]
    _RVM1(0x32da, 0, BIT5|BIT4 ),   //reg[1032da]#5~#4 = 00b
    //reg_ext_data_en[5]
    _RVM1(0x328c, BIT5 , BIT5 ),   //reg[10328c]#5 = 1b
    //reg_gpo_sel[5]
    _RVM1(0x329a, BIT5 , BIT5 ),   //reg[10329a]#5 = 1b
#endif

#if(PAD_R_ODD5_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD5_OEN (PAD_R_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_R_ODD5_OUT (PAD_R_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x329e, PAD_R_ODD5_OUT, BIT6),
    _RVM1(0x32a2, PAD_R_ODD5_OEN, BIT6),
    //reg_output_conf[7:6]
    _RVM1(0x32da, 0, BIT7|BIT6 ),   //reg[1032da]#7~#6 = 00b
    //reg_ext_data_en[6]
    _RVM1(0x328c, BIT6 , BIT6 ),   //reg[10328c]#6 = 1b
    //reg_gpo_sel[6]
    _RVM1(0x329a, BIT6 , BIT6 ),   //reg[10329a]#6 = 1b
#endif

#if(PAD_R_ODD4_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD4_OEN (PAD_R_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_R_ODD4_OUT (PAD_R_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x329e, PAD_R_ODD4_OUT, BIT7),
    _RVM1(0x32a2, PAD_R_ODD4_OEN, BIT7),
    //reg_output_conf[7:6]
    _RVM1(0x32da, 0, BIT7|BIT6 ),   //reg[1032da]#7~#6 = 00b
    //reg_ext_data_en[7]
    _RVM1(0x328c, BIT7 , BIT7 ),   //reg[10328c]#7 = 1b
    //reg_gpo_sel[7]
    _RVM1(0x329a, BIT7 , BIT7 ),   //reg[10329a]#7 = 1b
#endif

#if(PAD_R_ODD3_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD3_OEN (PAD_R_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_R_ODD3_OUT (PAD_R_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x329f, PAD_R_ODD3_OUT, BIT0),
    _RVM1(0x32a3, PAD_R_ODD3_OEN, BIT0),
    //reg_output_conf[9:8]
    _RVM1(0x32db, 0, BIT1|BIT0 ),   //reg[1032db]#1~#0 = 00b
    //reg_ext_data_en[8]
    _RVM1(0x328d, BIT0 , BIT0 ),   //reg[10328d]#0 = 1b
    //reg_gpo_sel[8]
    _RVM1(0x329b, BIT0 , BIT0 ),   //reg[10329b]#0 = 1b
#endif

#if(PAD_R_ODD2_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD2_OEN (PAD_R_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_R_ODD2_OUT (PAD_R_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x329f, PAD_R_ODD2_OUT, BIT1),
    _RVM1(0x32a3, PAD_R_ODD2_OEN, BIT1),
    //reg_output_conf[9:8]
    _RVM1(0x32db, 0, BIT1|BIT0 ),   //reg[1032db]#1~#0 = 00b
    //reg_ext_data_en[9]
    _RVM1(0x328d, BIT1 , BIT1 ),   //reg[10328d]#1 = 1b
    //reg_gpo_sel[9]
    _RVM1(0x329b, BIT1 , BIT1 ),   //reg[10329b]#1 = 1b
#endif

#if(PAD_R_ODD1_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD1_OEN (PAD_R_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_R_ODD1_OUT (PAD_R_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x329f, PAD_R_ODD1_OUT, BIT2),
    _RVM1(0x32a3, PAD_R_ODD1_OEN, BIT2),
    //reg_output_conf[11:10]
    _RVM1(0x32db, 0, BIT3|BIT2 ),   //reg[1032db]#3~#2 = 00b
    //reg_ext_data_en[10]
    _RVM1(0x328d, BIT2 , BIT2 ),   //reg[10328d]#2 = 1b
    //reg_gpo_sel[10]
    _RVM1(0x329b, BIT2 , BIT2 ),   //reg[10329b]#2 = 1b
#endif

#if(PAD_R_ODD0_IS_GPIO != GPIO_NONE)
#define PAD_R_ODD0_OEN (PAD_R_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_R_ODD0_OUT (PAD_R_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x329f, PAD_R_ODD0_OUT, BIT3),
    _RVM1(0x32a3, PAD_R_ODD0_OEN, BIT3),
    //reg_output_conf[11:10]
    _RVM1(0x32db, 0, BIT3|BIT2 ),   //reg[1032db]#3~#2 = 00b
    //reg_ext_data_en[11]
    _RVM1(0x328d, BIT3 , BIT3 ),   //reg[10328d]#3 = 1b
    //reg_gpo_sel[11]
    _RVM1(0x329b, BIT3 , BIT3 ),   //reg[10329b]#3 = 1b
#endif

#if(PAD_G_ODD7_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD7_OEN (PAD_G_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_G_ODD7_OUT (PAD_G_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x329f, PAD_G_ODD7_OUT, BIT4),
    _RVM1(0x32a3, PAD_G_ODD7_OEN, BIT4),
    //reg_output_conf[13:12]
    _RVM1(0x32db, 0, BIT5|BIT4 ),   //reg[1032db]#5~#4 = 00b
    //reg_ext_data_en[12]
    _RVM1(0x328d, BIT4 , BIT4 ),   //reg[10328d]#4 = 1b
    //reg_gpo_sel[12]
    _RVM1(0x329b, BIT4 , BIT4 ),   //reg[10329b]#4 = 1b
#endif

#if(PAD_G_ODD6_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD6_OEN (PAD_G_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_G_ODD6_OUT (PAD_G_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x329f, PAD_G_ODD6_OUT, BIT5),
    _RVM1(0x32a3, PAD_G_ODD6_OEN, BIT5),
    //reg_output_conf[13:12]
    _RVM1(0x32db, 0, BIT5|BIT4 ),   //reg[1032db]#5~#4 = 00b
    //reg_ext_data_en[13]
    _RVM1(0x328d, BIT5 , BIT5 ),   //reg[10328d]#5 = 1b
    //reg_gpo_sel[13]
    _RVM1(0x329b, BIT5 , BIT5 ),   //reg[10329b]#5 = 1b
#endif

#if(PAD_G_ODD5_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD5_OEN (PAD_G_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_G_ODD5_OUT (PAD_G_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x329f, PAD_G_ODD5_OUT, BIT6),
    _RVM1(0x32a3, PAD_G_ODD5_OEN, BIT6),
    //reg_output_conf[15:14]
    _RVM1(0x32db, 0, BIT7|BIT6 ),   //reg[1032db]#7~#6 = 00b
    //reg_ext_data_en[14]
    _RVM1(0x328d, BIT6 , BIT6 ),   //reg[10328d]#6 = 1b
    //reg_gpo_sel[14]
    _RVM1(0x329b, BIT6 , BIT6 ),   //reg[10329b]#6 = 1b
#endif

#if(PAD_G_ODD4_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD4_OEN (PAD_G_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_G_ODD4_OUT (PAD_G_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x329f, PAD_G_ODD4_OUT, BIT7),
    _RVM1(0x32a3, PAD_G_ODD4_OEN, BIT7),
    //reg_output_conf[15:14]
    _RVM1(0x32db, 0, BIT7|BIT6 ),   //reg[1032db]#7~#6 = 00b
    //reg_ext_data_en[15]
    _RVM1(0x328d, BIT7 , BIT7 ),   //reg[10328d]#7 = 1b
    //reg_gpo_sel[15]
    _RVM1(0x329b, BIT7 , BIT7 ),   //reg[10329b]#7 = 1b
#endif

#if(PAD_G_ODD3_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD3_OEN (PAD_G_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_G_ODD3_OUT (PAD_G_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x32a0, PAD_G_ODD3_OUT, BIT0),
    _RVM1(0x32a4, PAD_G_ODD3_OEN, BIT0),
    //reg_output_conf[17:16]
    _RVM1(0x32dc, 0, BIT1|BIT0 ),   //reg[1032dc]#1~#0 = 00b
    //reg_ext_data_en[16]
    _RVM1(0x328e, BIT0 , BIT0 ),   //reg[10328e]#0 = 1b
    //reg_gpo_sel[16]
    _RVM1(0x329c, BIT0 , BIT0 ),   //reg[10329c]#0 = 1b
#endif

#if(PAD_G_ODD2_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD2_OEN (PAD_G_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_G_ODD2_OUT (PAD_G_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x32a0, PAD_G_ODD2_OUT, BIT1),
    _RVM1(0x32a4, PAD_G_ODD2_OEN, BIT1),
    //reg_output_conf[17:16]
    _RVM1(0x32dc, 0, BIT1|BIT0 ),   //reg[1032dc]#1~#0 = 00b
    //reg_ext_data_en[17]
    _RVM1(0x328e, BIT1 , BIT1 ),   //reg[10328e]#1 = 1b
    //reg_gpo_sel[17]
    _RVM1(0x329c, BIT1 , BIT1 ),   //reg[10329c]#1 = 1b
#endif

#if(PAD_G_ODD1_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD1_OEN (PAD_G_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_G_ODD1_OUT (PAD_G_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x32a0, PAD_G_ODD1_OUT, BIT2),
    _RVM1(0x32a4, PAD_G_ODD1_OEN, BIT2),
    //reg_output_conf[19:18]
    _RVM1(0x32dc, 0, BIT3|BIT2 ),   //reg[1032dc]#3~#2 = 00b
    //reg_ext_data_en[18]
    _RVM1(0x328e, BIT2 , BIT2 ),   //reg[10328e]#2 = 1b
    //reg_gpo_sel[18]
    _RVM1(0x329c, BIT2 , BIT2 ),   //reg[10329c]#2 = 1b
#endif

#if(PAD_G_ODD0_IS_GPIO != GPIO_NONE)
#define PAD_G_ODD0_OEN (PAD_G_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_G_ODD0_OUT (PAD_G_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x32a0, PAD_G_ODD0_OUT, BIT3),
    _RVM1(0x32a4, PAD_G_ODD0_OEN, BIT3),
    //reg_output_conf[19:18]
    _RVM1(0x32dc, 0, BIT3|BIT2 ),   //reg[1032dc]#3~#2 = 00b
    //reg_ext_data_en[19]
    _RVM1(0x328e, BIT3 , BIT3 ),   //reg[10328e]#3 = 1b
    //reg_gpo_sel[19]
    _RVM1(0x329c, BIT3 , BIT3 ),   //reg[10329c]#3 = 1b
#endif

#if(PAD_B_ODD7_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD7_OEN (PAD_B_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_B_ODD7_OUT (PAD_B_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x32a0, PAD_B_ODD7_OUT, BIT4),
    _RVM1(0x32a4, PAD_B_ODD7_OEN, BIT4),
    //reg_output_conf[21:20]
    _RVM1(0x32dc, 0, BIT5|BIT4 ),   //reg[1032dc]#5~#4 = 00b
    //reg_ext_data_en[20]
    _RVM1(0x328e, BIT4 , BIT4 ),   //reg[10328e]#4 = 1b
    //reg_gpo_sel[20]
    _RVM1(0x329c, BIT4 , BIT4 ),   //reg[10329c]#4 = 1b
#endif

#if(PAD_B_ODD6_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD6_OEN (PAD_B_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_B_ODD6_OUT (PAD_B_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x32a0, PAD_B_ODD6_OUT, BIT5),
    _RVM1(0x32a4, PAD_B_ODD6_OEN, BIT5),
    //reg_output_conf[21:20]
    _RVM1(0x32dc, 0, BIT5|BIT4 ),   //reg[1032dc]#5~#4 = 00b
    //reg_ext_data_en[21]
    _RVM1(0x328e, BIT5 , BIT5 ),   //reg[10328e]#5 = 1b
    //reg_gpo_sel[21]
    _RVM1(0x329c, BIT5 , BIT5 ),   //reg[10329c]#5 = 1b
#endif

#if(PAD_B_ODD5_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD5_OEN (PAD_B_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_B_ODD5_OUT (PAD_B_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x32a0, PAD_B_ODD5_OUT, BIT6),
    _RVM1(0x32a4, PAD_B_ODD5_OEN, BIT6),
    //reg_output_conf[23:22]
    _RVM1(0x32dc, 0, BIT7|BIT6 ),   //reg[1032dc]#7~#6 = 00b
    //reg_ext_data_en[22]
    _RVM1(0x328e, BIT6 , BIT6 ),   //reg[10328e]#6 = 1b
    //reg_gpo_sel[22]
    _RVM1(0x329c, BIT6 , BIT6 ),   //reg[10329c]#6 = 1b
#endif

#if(PAD_B_ODD4_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD4_OEN (PAD_B_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_B_ODD4_OUT (PAD_B_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x32a0, PAD_B_ODD4_OUT, BIT7),
    _RVM1(0x32a4, PAD_B_ODD4_OEN, BIT7),
    //reg_output_conf[23:22]
    _RVM1(0x32dc, 0, BIT7|BIT6 ),   //reg[1032dc]#7~#6 = 00b
    //reg_ext_data_en[23]
    _RVM1(0x328e, BIT7 , BIT7 ),   //reg[10328e]#7 = 1b
    //reg_gpo_sel[23]
    _RVM1(0x329c, BIT7 , BIT7 ),   //reg[10329c]#7 = 1b
#endif

#if(PAD_B_ODD3_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD3_OEN (PAD_B_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_B_ODD3_OUT (PAD_B_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x32a1, PAD_B_ODD3_OUT, BIT0),
    _RVM1(0x32a5, PAD_B_ODD3_OEN, BIT0),
    //reg_output_conf[25:24]
    _RVM1(0x32dd, 0, BIT1|BIT0 ),   //reg[1032dd]#1~#0 = 00b
    //reg_ext_data_en[24]
    _RVM1(0x328f, BIT0 , BIT0 ),   //reg[10328f]#0 = 1b
    //reg_gpo_sel[24]
    _RVM1(0x329d, BIT0 , BIT0 ),   //reg[10329d]#0 = 1b
#endif

#if(PAD_B_ODD2_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD2_OEN (PAD_B_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_B_ODD2_OUT (PAD_B_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x32a1, PAD_B_ODD2_OUT, BIT1),
    _RVM1(0x32a5, PAD_B_ODD2_OEN, BIT1),
    //reg_output_conf[25:24]
    _RVM1(0x32dd, 0, BIT1|BIT0 ),   //reg[1032dd]#1~#0 = 00b
    //reg_ext_data_en[25]
    _RVM1(0x328f, BIT1 , BIT1 ),   //reg[10328f]#1 = 1b
    //reg_gpo_sel[25]
    _RVM1(0x329d, BIT1 , BIT1 ),   //reg[10329d]#1 = 1b
#endif

#if(PAD_B_ODD1_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD1_OEN (PAD_B_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_B_ODD1_OUT (PAD_B_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x32a1, PAD_B_ODD1_OUT, BIT2),
    _RVM1(0x32a5, PAD_B_ODD1_OEN, BIT2),
    //reg_output_conf[27:26]
    _RVM1(0x32dd, 0, BIT3|BIT2 ),   //reg[1032dd]#3~#2 = 00b
    //reg_ext_data_en[26]
    _RVM1(0x328f, BIT2 , BIT2 ),   //reg[10328f]#2 = 1b
    //reg_gpo_sel[26]
    _RVM1(0x329d, BIT2 , BIT2 ),   //reg[10329d]#2 = 1b
#endif

#if(PAD_B_ODD0_IS_GPIO != GPIO_NONE)
#define PAD_B_ODD0_OEN (PAD_B_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_B_ODD0_OUT (PAD_B_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x32a1, PAD_B_ODD0_OUT, BIT3),
    _RVM1(0x32a5, PAD_B_ODD0_OEN, BIT3),
    //reg_output_conf[27:26]
    _RVM1(0x32dd, 0, BIT3|BIT2 ),   //reg[1032dd]#3~#2 = 00b
    //reg_ext_data_en[27]
    _RVM1(0x328f, BIT3 , BIT3 ),   //reg[10328f]#3 = 1b
    //reg_gpo_sel[27]
    _RVM1(0x329d, BIT3 , BIT3 ),   //reg[10329d]#3 = 1b
#endif

#if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
#define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7a, PAD_GPIO0_OUT, BIT0),
    _RVM1(0x1e7e, PAD_GPIO0_OEN, BIT0),
    //reg_seconduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1~#0 = 00b
    //reg_3d_lr_config[2:0] = 000b
    _RVM1(0x1e10, 0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    //reg_6bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT0 ),   //reg[101ef8]#0 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
#define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e7a, PAD_GPIO1_OUT, BIT1),
    _RVM1(0x1e7e, PAD_GPIO1_OEN, BIT1),
    //reg_seconduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1~#0 = 00b
    //reg_6bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT0 ),   //reg[101ef8]#0 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
#define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e7a, PAD_GPIO2_OUT, BIT2),
    _RVM1(0x1e7e, PAD_GPIO2_OEN, BIT2),
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
#endif

#if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
#define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e7a, PAD_GPIO3_OUT, BIT3),
    _RVM1(0x1e7e, PAD_GPIO3_OEN, BIT3),
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_PWM5Config[1:0] = 00b
    _RVM1(0x1e41, 0, BIT3|BIT2 ),   //reg[101e41]#3 ~#2 = 00b
#endif

#if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
#define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e7a, PAD_GPIO4_OUT, BIT4),
    _RVM1(0x1e7e, PAD_GPIO4_OEN, BIT4),
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
#endif

#if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
#define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e7a, PAD_GPIO5_OUT, BIT5),
    _RVM1(0x1e7e, PAD_GPIO5_OEN, BIT5),
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_spdifoutconfig = 0b
    _RVM1(0x1eaf, 0, BIT1 ),   //reg[101eaf]#1 = 0b
#endif

#if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
#define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e7a, PAD_GPIO6_OUT, BIT6),
    _RVM1(0x1e7e, PAD_GPIO6_OEN, BIT6),
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_fastuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5~#4 = 00b
    //reg_usbdrvvbusconfig[1:0] = 00b
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1 ~#0 = 00b
    //reg_spdifinconfig = 0b
    _RVM1(0x1eae, 0, BIT7 ),   //reg[101eae]#7 = 0b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
#define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT7: 0)
#define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e7a, PAD_GPIO7_OUT, BIT7),
    _RVM1(0x1e7e, PAD_GPIO7_OEN, BIT7),
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_fastuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT5|BIT4 ),   //reg[101e04]#5~#4 = 00b
    //reg_PWM4Config[1:0] = 00b
    _RVM1(0x1e41, 0, BIT1|BIT0 ),   //reg[101e41]#1 ~#0 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif

#if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
#define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e7b, PAD_GPIO10_OUT, BIT2),
    _RVM1(0x1e7f, PAD_GPIO10_OEN, BIT2),
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
#endif

#if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
#define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e7b, PAD_GPIO11_OUT, BIT3),
    _RVM1(0x1e7f, PAD_GPIO11_OEN, BIT3),
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_PWM4Config[1:0] = 00b
    _RVM1(0x1e41, 0, BIT1|BIT0 ),   //reg[101e41]#1 ~#0 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
#endif

#if(PAD_INT_IS_GPIO != GPIO_NONE)
#define PAD_INT_OEN (PAD_INT_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_INT_OUT (PAD_INT_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e45, PAD_INT_OUT, BIT2),
    _RVM1(0x1e49, PAD_INT_OEN, BIT2),
    //reg_int_gpio = 0b
    _RVM1(0x1e4f, BIT2 , BIT2 ),   //reg[101e4f]#2 = 1b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_serial_TS_in_Config[3:0] = 0000b
    _RVM1(0x1ef7, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef7]#3 ~#0 = 0000b
#endif


    _MEMMAP_PM_,

#if(PAD_PMGPIO_IS_GPIO != GPIO_NONE)
#define PAD_PMGPIO_OEN (PAD_PMGPIO_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_PMGPIO_OUT (PAD_PMGPIO_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e3a, PAD_PMGPIO_OUT, BIT1),
    _RVM1(0x0e3c, PAD_PMGPIO_OEN, BIT1),
    //reg_3d_lr_config[2:0] = 000b
    _MEMMAP_nonPM_,
    _RVM1(0x1e10, 0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    _MEMMAP_PM_,
#endif

#if(PAD_GPIO_PM1_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM1_OEN (PAD_GPIO_PM1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_GPIO_PM1_OUT (PAD_GPIO_PM1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0e20, PAD_GPIO_PM1_OUT, BIT1),
    _RVM1(0x0e1e, PAD_GPIO_PM1_OEN, BIT1),
#endif

#if(PAD_GPIO_PM4_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM4_OEN (PAD_GPIO_PM4_IS_GPIO == GPIO_IN ? BIT4: 0)
#define PAD_GPIO_PM4_OUT (PAD_GPIO_PM4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0e20, PAD_GPIO_PM4_OUT, BIT4),
    _RVM1(0x0e1e, PAD_GPIO_PM4_OEN, BIT4),
#endif

#if(PAD_GPIO_PM5_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM5_OEN (PAD_GPIO_PM5_IS_GPIO == GPIO_IN ? BIT5: 0)
#define PAD_GPIO_PM5_OUT (PAD_GPIO_PM5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0e20, PAD_GPIO_PM5_OUT, BIT5),
    _RVM1(0x0e1e, PAD_GPIO_PM5_OEN, BIT5),
#endif

#if(PAD_GPIO_PM6_IS_GPIO != GPIO_NONE)
#define PAD_GPIO_PM6_OEN (PAD_GPIO_PM6_IS_GPIO == GPIO_IN ? BIT6: 0)
#define PAD_GPIO_PM6_OUT (PAD_GPIO_PM6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0e20, PAD_GPIO_PM6_OUT, BIT6),
    _RVM1(0x0e1e, PAD_GPIO_PM6_OEN, BIT6),
#endif

#if(PAD_CEC_IS_GPIO != GPIO_NONE)
#define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0E3a, PAD_CEC_OUT, BIT2),
    _RVM1(0x0E3c, PAD_CEC_OEN, BIT2),
    //reg_pmcec_en[6] = 0b
    _RVM1(0x3401, 0, BIT6 ),   //reg[3401]#6 = 0b
    //reg_cec_is_gpio = 1b
    _RVM1(0x0E38, BIT6 , BIT6 ),   //reg[0E38]#6 = 1b
#endif

#if(PAD_SAR3_IS_GPIO != GPIO_NONE)
#define PAD_SAR3_OEN (PAD_SAR3_IS_GPIO == GPIO_IN ? BIT3: 0)
#define PAD_SAR3_OUT (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1424, PAD_SAR3_OUT, BIT3),
    _RVM1(0x1423, PAD_SAR3_OEN, BIT3),
#endif

#if(PAD_SAR2_IS_GPIO != GPIO_NONE)
#define PAD_SAR2_OEN (PAD_SAR2_IS_GPIO == GPIO_IN ? BIT2: 0)
#define PAD_SAR2_OUT (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1424, PAD_SAR2_OUT, BIT2),
    _RVM1(0x1423, PAD_SAR2_OEN, BIT2),
#endif

#if(PAD_SAR1_IS_GPIO != GPIO_NONE)
#define PAD_SAR1_OEN (PAD_SAR1_IS_GPIO == GPIO_IN ? BIT1: 0)
#define PAD_SAR1_OUT (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1424, PAD_SAR1_OUT, BIT1),
    _RVM1(0x1423, PAD_SAR1_OEN, BIT1),
#endif

#if(PAD_SAR0_IS_GPIO != GPIO_NONE)
#define PAD_SAR0_OEN (PAD_SAR0_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_SAR0_OUT (PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1424, PAD_SAR0_OUT, BIT0),
    _RVM1(0x1423, PAD_SAR0_OEN, BIT0),
#endif

#if(PAD_IRIN_IS_GPIO != GPIO_NONE)
#define PAD_IRIN_OEN (PAD_IRIN_IS_GPIO == GPIO_IN ? BIT0: 0)
#define PAD_IRIN_OUT (PAD_IRIN_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x3402, PAD_IRIN_OUT, BIT0),
    _RVM1(0x3404, PAD_IRIN_OEN, BIT0),
    //reg_wdummy_0[5] = 0b
    _RVM1(0x340c, 0, BIT5 ),   //reg[340c]#5 = 0b
    //reg_ir_gpio_en#0 = 1b
    _RVM1(0x3400, BIT0 , BIT0 ),   //reg[3400]#0 =1b
#endif


//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
    _MEMMAP_nonPM_,

#if (PADS_TCON_CONFIG != Unknown_pad_mux)
#define TCON0    ((PADS_TCON_CONFIG & BIT0) ? BIT0 : 0)
#define TCON1    ((PADS_TCON_CONFIG & BIT1) ? BIT1 : 0)
#define TCON2    ((PADS_TCON_CONFIG & BIT2) ? BIT2 : 0)
#define TCON3    ((PADS_TCON_CONFIG & BIT3) ? BIT3 : 0)
#define TCON4    ((PADS_TCON_CONFIG & BIT4) ? BIT4 : 0)
#define TCON5    ((PADS_TCON_CONFIG & BIT5) ? BIT5 : 0)
#define TCON6    ((PADS_TCON_CONFIG & BIT6) ? BIT6 : 0)
#define TCON7    ((PADS_TCON_CONFIG & BIT7) ? BIT7 : 0)
#define TCON8    ((PADS_TCON_CONFIG & BIT8) ? BIT8 : 0)
#define TCON9    ((PADS_TCON_CONFIG & BIT9) ? BIT9 : 0)
#define TCON10   ((PADS_TCON_CONFIG & BIT10) ? BIT10 : 0)
#define TCON11   ((PADS_TCON_CONFIG & BIT11) ? BIT11 : 0)
#define TCON12   ((PADS_TCON_CONFIG & BIT12) ? BIT12 : 0)
#define TCON13   ((PADS_TCON_CONFIG & BIT13) ? BIT13 : 0)
#define TCON14   ((PADS_TCON_CONFIG & BIT14) ? BIT14 : 0)
#define TCON15   ((PADS_TCON_CONFIG & BIT15) ? BIT15 : 0)
#define TCON16   ((PADS_TCON_CONFIG & BIT16) ? BIT16 : 0)
#define TCON17   ((PADS_TCON_CONFIG & BIT17) ? BIT17 : 0)
#define TCON18   ((PADS_TCON_CONFIG & BIT18) ? BIT18 : 0)
#define TCON19   ((PADS_TCON_CONFIG & BIT19) ? BIT19 : 0)
#define TCON20   ((PADS_TCON_CONFIG & BIT20) ? BIT20 : 0)
#define TCON21   ((PADS_TCON_CONFIG & BIT21) ? BIT21 : 0)
#define SET_TCON TCON0|TCON1|TCON2|TCON3|TCON4|TCON5|TCON6|TCON7|TCON8  \
                 |TCON9|TCON10|TCON11|TCON12|TCON13|TCON14|TCON15|TCON16 \
                 |TCON17|TCON18|TCON19|TCON20|TCON21
        _RVM3(0x1EF2, SET_TCON, 0x3FFFFF),
#endif

#if (PADS_UART2_MODE != Unknown_pad_mux)
#define UART2_MODE   ((PADS_UART2_MODE == PAD_GPIO0) ? BIT0: \
                      (PADS_UART2_MODE == PAD_GPIO1) ? BIT0: \
                      (PADS_UART2_MODE == PAD_TCON0) ? BIT1: \
                      (PADS_UART2_MODE == PAD_TCON1) ? BIT1: 0)
        _RVM1(0x1E05, UART2_MODE, BIT1|BIT0),
#endif

#if (PADS_UART3_MODE != Unknown_pad_mux)
#define UART3_MODE   ((PADS_UART3_MODE == PAD_TCON9) ? BIT2: \
                      (PADS_UART3_MODE == PAD_TCON10) ? BIT2: \
                      (PADS_UART3_MODE == PAD_GPIO10) ? BIT3: \
                      (PADS_UART3_MODE == PAD_GPIO11) ? BIT3: \
                      (PADS_UART3_MODE == PAD_TCON20) ? (BIT3|BIT2): \
                      (PADS_UART3_MODE == PAD_TCON21) ? (BIT3|BIT2): 0)
        _RVM1(0x1E05, UART3_MODE, BIT3|BIT2),
#endif

#if (PADS_UART4_MODE != Unknown_pad_mux)
#define UART4_MODE   ((PADS_UART4_MODE == PAD_TCON11) ? BIT6: \
                      (PADS_UART4_MODE == PAD_TCON12) ? BIT6: \
                      (PADS_UART4_MODE == PAD_GPIO6) ? BIT7: \
                      (PADS_UART4_MODE == PAD_GPIO7) ? BIT7: \
                      (PADS_UART4_MODE == PAD_GPIO4) ? (BIT7|BIT6): \
                      (PADS_UART4_MODE == PAD_GPIO5) ? (BIT7|BIT6): 0)
        _RVM1(0x1E04, UART4_MODE, BIT7|BIT6),
#if 0
#define UART4_DISP 	((PADS_UART4_MODE == PAD_LCK) ? (BIT3|BIT2) : \
                             (PADS_UART4_MODE == PAD_LDE) ? (BIT3|BIT2) : 0)
	_RVM1(0x328C, UART4_DISP, BITMASK(3:2)),
#define GPIO_SEL 	((PADS_UART4_MODE == PAD_LCK) ? 0 : \
                             (PADS_UART4_MODE == PAD_LDE) ? 0: (BIT3|BIT2) )
	_RVM1(0x329A, GPIO_SEL, BITMASK(3:2)),
#endif
#endif

#if (PADS_FAST_UART_MODE != Unknown_pad_mux)
#define FAST_UART_MODE   ((PADS_FAST_UART_MODE == PAD_TCON9) ? BIT4: \
                          (PADS_FAST_UART_MODE == PAD_TCON10) ? BIT4: \
                          (PADS_FAST_UART_MODE == PAD_GPIO6) ? BIT5: \
                          (PADS_FAST_UART_MODE == PAD_GPIO7) ? BIT5: 0 )
        _RVM1(0x1E04, FAST_UART_MODE, BIT5|BIT4),
#endif

#define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                     (UART1_INV ? BIT1 : 0) | \
                     (UART2_INV ? BIT2 : 0) | \
                     (UART3_INV ? BIT3 : 0) | \
                     (UART4_INV ? BIT4 : 0))

        _RVM1(0x1EAB, UART_INV, BITMASK(4:0)),
        _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),
        
#if (PADS_3DLR_MODE != Unknown_pad_mux)
//XC3DLR_PATH1 : PAD_TCON0
//XC3DLR_PATH2 : PAD_GPIO0
//XC3DLR_VSYNC_PATH1 : PAD_TCON0 (scaler out with VSync)
//XC3DLR_VSYNC_PATH2 : PAD_GPIO0 (scaler out with VSync)
#define LR_3D_MODE   ((PADS_3DLR_SEL == XC3DLR_PATH1) ? BIT0: \
                      (PADS_3DLR_SEL == XC3DLR_PATH2) ? BIT1: \
                      (PADS_3DLR_SEL == XC3DLR_VSYNC_PATH1) ? (BIT1|BIT0): \
                      (PADS_3DLR_SEL == XC3DLR_VSYNC_PATH2) ? BIT2: 0)
        _RVM1(0x1E10, LR_3D_MODE, BIT2|BIT1|BIT0),
#endif

#if (PADS_I2S_IN != Unknown_pad_mux)
//I2S_IN_MODE1 : PAD_TCON14,PAD_TCON15,PAD_TCON16
#define I2S_IN    ((PADS_I2S_IN == I2S_IN_MODE1) ? BIT3 : 0)
        _RVM1(0x1EAE, I2S_IN, BIT4|BIT3),
#endif

#if (PADS_I2S_OUT != Unknown_pad_mux)
//I2S_OUT_MODE1 : PAD_GPIO0,PAD_GPIO1,PAD_GPIO2,PAD_GPIO3,PAD_GPIO4
//I2S_OUT_MODE2 : PAD_GPIO0,PAD_GPIO2,PAD_GPIO3,PAD_GPIO4
#define I2S_OUT   ((PADS_I2S_OUT == I2S_OUT_MODE1) ? BIT5 : \
                   (PADS_I2S_OUT == I2S_OUT_MODE2) ? (BIT6|BIT5) : 0)
        _RVM1(0x1EAE, I2S_OUT, BIT6|BIT5),
#endif

#if (PADS_SPDIF_IN != Unknown_pad_mux)
#define SPDIF_IN   ((PADS_SPDIF_IN == PAD_GPIO6) ? BIT7 : 0)
        _RVM1(0x1EAE, SPDIF_IN, BIT7),
#endif

#if (PADS_SPDIF_OUT != Unknown_pad_mux)
#define SPDIF_OUT   ((PADS_SPDIF_OUT == PAD_GPIO5) ? BIT1: 0)
        _RVM1(0x1EAF, SPDIF_OUT, BIT1),
#endif

#if (PADS_INT_GPIO != Unknown_pad_mux)
#define INT_GPIO   ((PADS_INT_GPIO == PAD_INT) ? BIT2: 0)
        _RVM1(0x1E4F, INT_GPIO, BIT2),
#endif

#if (PADS_PWM0_MODE != Unknown_pad_mux)
#define PWM0_MODE   ((PADS_PWM0_MODE == PAD_PWM0) ? BIT4: 0)
        _RVM1(0x1E40, PWM0_MODE, BIT4),
        _RVM1(0x1E06, 0, BIT0),//pwm0 output enable 
#endif

#if (PADS_PWM1_MODE != Unknown_pad_mux)
#define PWM1_MODE   ((PADS_PWM1_MODE == PAD_PWM1) ? BIT5: 0)
        _RVM1(0x1E40, PWM1_MODE, BIT5),
        _RVM1(0x1E06, 0, BIT1),//pwm1 output enable 
#endif

#if (PADS_PWM2_MODE != Unknown_pad_mux)
#define PWM2_MODE   ((PADS_PWM2_MODE == PAD_PWM2) ? BIT6: 0)
        _RVM1(0x1E40, PWM2_MODE, BIT6),
        _RVM1(0x1E06, 0, BIT2),//pwm2 output enable 
#endif

#if (PADS_PWM3_MODE != Unknown_pad_mux)
#define PWM3_MODE   ((PADS_PWM3_MODE == PAD_PWM3) ? BIT7: 0)
        _RVM1(0x1E40, PWM3_MODE, BIT7),
        _RVM1(0x1E06, 0, BIT3),//pwm3 output enable 
#endif

#if (PADS_PWM4_MODE != Unknown_pad_mux)
#define PWM4_MODE   ((PADS_PWM4_MODE == PAD_GPIO7) ? BIT0: \
                     (PADS_PWM4_MODE == PAD_GPIO11) ? BIT1: 0)
        _RVM1(0x1E41, PWM4_MODE, BIT1|BIT0),
        _RVM1(0x1E06, 0, BIT4),//pwm4 output enable 
#endif

#if (PADS_PWM5_MODE != Unknown_pad_mux)
#define PWM5_MODE   ((PADS_PWM5_MODE == PAD_TCON21) ? BIT2: \
                     (PADS_PWM5_MODE == PAD_GPIO3) ? BIT3: 0)
        _RVM1(0x1E41, PWM5_MODE, BIT3|BIT2),
        _RVM1(0x1E06, 0, BIT5),//pwm5 output enable 
#endif

#if (PADS_DDCR_MODE != Unknown_pad_mux)
#define DDCR_MODE   ((PADS_DDCR_MODE == IIC_PATH(1)) ? BIT0: \
                     (PADS_DDCR_MODE == IIC_PATH(2)) ? (BIT0|BIT1): \
                     (PADS_DDCR_MODE == IIC_PATH(3)) ? (BIT2|BIT0): \
                     (PADS_DDCR_MODE == IIC_PATH(4)) ? (BIT2|BIT1|BIT0): \
                     (PADS_DDCR_MODE == DDCR_PATH(1)) ? BIT1: \
                     (PADS_DDCR_MODE == DDCR_PATH(2)) ? BIT2: \
                     (PADS_DDCR_MODE == DDCR_PATH(3)) ? (BIT2|BIT1): \
                     (PADS_DDCR_MODE == DDCR_PATH(4)) ? BIT3: 0)
        _RVM1(0x1EF6, DDCR_MODE, BIT3|BIT2|BIT1|BIT0),
#endif

#if (PADS_TS_IN_P_CFG != Unknown_pad_mux)
#define TS_IN_P_CFG ((PADS_TS_IN_P_CFG == TS_IN_P_MODE(1)) ? BIT4 : \
                     (PADS_TS_IN_P_CFG == TS_IN_P_MODE(2)) ? BIT5 : \
                     (PADS_TS_IN_P_CFG == TS_IN_P_MODE(3)) ? (BIT5|BIT4): 0)
        _RVM1(0x1EF7, TS_IN_P_CFG, BIT4|BIT5),
#endif

#if (PADS_TS_IN_S_CFG != Unknown_pad_mux)
#define TS_IN_S_CFG ((PADS_TS_IN_S_CFG == TS_IN_S_MODE(1)) ? BIT0 : \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(2)) ? BIT1 : \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(3)) ? (BIT1|BIT0): \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(4)) ? (BIT2): \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(5)) ? (BIT2|BIT0): \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(6)) ? (BIT2|BIT1): \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(7)) ? (BIT2|BIT1|BIT0): \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(8)) ? (BIT3): \
                     (PADS_TS_IN_S_CFG == TS_IN_S_MODE(9)) ? (BIT3|BIT0): 0)
        _RVM1(0x1EF7, TS_IN_S_CFG, BIT3|BIT2|BIT1|BIT0),
#endif


    _MEMMAP_nonPM_,

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL2_,

    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select external flash #1)

    _MEMMAP_nonPM_,

#if (PIN_FLASH_WP0)
  #if(MS_BOARD_TYPE_SEL == BD_MST149A_D01A_S) //PAD_PWM1
    _RVM1(0x1e40,    0,  BIT5), //reg[101e40]#5 = 0b
    _RVM1(0x1e85, BIT5, BIT5), //output high
    _RVM1(0x1e87,    0,  BIT5), //oen: output(0)
  #elif(MS_BOARD_TYPE_SEL == BD_MST149B_D01A_S) //PAD_PWM2
    _RVM1(0x1e40,    0,  BIT6), //reg[101e40]#6 = 0b
    _RVM1(0x1e85, BIT6, BIT6), //output high
    _RVM1(0x1e87,    0,  BIT6), //oen: output(0)
  #elif((MS_BOARD_TYPE_SEL == BD_MST149C_D01A_S)||(MS_BOARD_TYPE_SEL == BD_MST149D_D01A_S)) //PAD_GPIOPM
    _RVM1(0x1e10,    0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    _MEMMAP_PM_,
    _RVM1(0x0e3a, BIT1, BIT1), //output high
    _RVM1(0x0e3c,    0, BIT1), //oen: output(0)
  #elif(MS_BOARD_TYPE_SEL == BD_MST149E_D01A_S) //PAD_GPIO4
    _RVM1(0x1e04,    0, BIT7|BIT6 ), //reg[101e04]#7~#6 = 00b
    _RVM1(0x1eae,    0, BIT6|BIT5 ), //reg[101eae]#6 ~#5 = 00b
    _RVM1(0x1e7c, BIT4, BIT4), //output high
    _RVM1(0x1e7e,    0, BIT4), //oen: output(0)
  #else
    #error "Please select correct boards"
  #endif
#endif
    _END_OF_TBL2_,

};

void MDrv_Pad_Init( void )
{
    U8 code *pPadConfig;
    U8  u8Length;
    U16 u16Index; // register index

    u32MapBase = _MapBase_nonPM_M12;

    pPadConfig = (U8 *)padInitTbl + 10;

    while (1)
    {
        u16Index = (pPadConfig[0] << 8) + (pPadConfig[1]);

        if (u16Index == 0xFFFF) // check end of table
            break;

        pPadConfig += 2;

        if(u16Index == 0x0000) // switch base address
        {
            if((pPadConfig[0]==0x10)||(pPadConfig[0]==0x11))
            {
                u32MapBase = _MapBase_nonPM_M12;
            }
            else if(pPadConfig[0]==0x00)
            {
                u32MapBase = _MapBase_PM_M12;
            }
            pPadConfig += 2;
            continue;
        }

        u8Length = HIGHBYTE(u16Index) >> 6;
        u16Index &= 0x3FFF;

        while (1)
        {
            //printf("%x = %bx & %bx\n", u16Index, pPadConfig[0], pPadConfig[1]);
            MDrv_PAD_WriteByteMask((U32)u16Index, pPadConfig[0], pPadConfig[1]);
            pPadConfig += 2;

            if (u8Length == 0)
                break;

            u8Length--;
            u16Index++;
        }
    }

}

//-----------------------------------------------------------------
// Sanity check for PAD_TOP setting (TODO)
//-----------------------------------------------------------------
#if 0
#if (UART0_SRC_SEL == UART1_SRC_SEL) || \
    (UART0_SRC_SEL == UART2_SRC_SEL) || \
    (UART1_SRC_SEL == UART2_SRC_SEL)
    #error "UART src selection conflict"
#endif
#endif


