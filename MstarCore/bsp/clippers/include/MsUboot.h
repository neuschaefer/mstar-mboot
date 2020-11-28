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
/// @file   MsUboot.h
/// @brief  MStar Common Interface Header File
/// @author MStar Semiconductor Inc.
/// @note   MsUboot.h includes most command header files including basic data type, macro(MsTypes.h),\n
/// board configuration(MsBoard.h), and OS related API(MsOS.h).\n
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MS_UBOOT_H_
#define _MS_UBOOT_H_

#define BIT0			                 0x01
#define BIT1			                 0x02
#define BIT2			                 0x04
#define BIT3			                 0x08
#define BIT4			                 0x10
#define BIT5			                 0x20
#define BIT6			                 0x40
#define BIT7			                 0x80

#define MST_MACRO_START     do {
#define MST_MACRO_END       } while (0)

extern unsigned long MS_RIU_MAP;
#define RIU     ((unsigned short volatile *) MS_RIU_MAP)
#define RIU8    ((unsigned char  volatile *) MS_RIU_MAP)

#define MDrv_WriteByte(u32Reg, u8Value)     RIU8[(u32Reg << 1) - (u32Reg & 1)] = u8Value
#define MDrv_ReadByte(u32Reg)                   RIU8[(u32Reg << 1) - (u32Reg & 1)]

extern unsigned long RIU_MAP;
extern void MDrv_Sys_WholeChipReset(void);

#endif /*_MS_UBOOT_H_*/

