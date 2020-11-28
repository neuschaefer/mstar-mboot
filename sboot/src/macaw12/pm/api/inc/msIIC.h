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

#ifndef _IIC_H_
#define _IIC_H_

#ifdef _IIC_C_
#define _IICDEC_
#else
#define _IICDEC_ extern
#endif

#include "Board.h"

  // Speed Mapping: Base on the Driver loading, maybe you must to use the oscilloscope to measure this Value
  // 250K => SwIicDly =1
  // 200K => SwIicDly =10
  // 150K => SwIicDly =20
  // 100K => SwIicDly =40

#if (USE_SW_I2C_HIGHSPEED==1)
#if 1//base on CPU running at 172.8MHz
#define I2C_SPEED_MAPPING_400K           1
#define I2C_SPEED_MAPPING_350K           4
#define I2C_SPEED_MAPPING_300K           8
#define I2C_SPEED_MAPPING_250K          12
#define I2C_SPEED_MAPPING_200K          20
#define I2C_SPEED_MAPPING_150K          30
#define I2C_SPEED_MAPPING_100K          60
#else//base on CPU running at 216MHz
#define I2C_SPEED_MAPPING_400K          14
#define I2C_SPEED_MAPPING_350K          20
#define I2C_SPEED_MAPPING_300K          30
#define I2C_SPEED_MAPPING_250K          44
#define I2C_SPEED_MAPPING_200K          60
#define I2C_SPEED_MAPPING_150K         100
#define I2C_SPEED_MAPPING_100K         150
#endif
#else
//base on CPU running at 384MHz
#define I2C_SPEED_MAPPING_400K           50
#define I2C_SPEED_MAPPING_350K           60
#define I2C_SPEED_MAPPING_300K           70
#define I2C_SPEED_MAPPING_250K           80
#define I2C_SPEED_MAPPING_200K          100
#define I2C_SPEED_MAPPING_150K          135
#define I2C_SPEED_MAPPING_100K          135//200
#endif

typedef enum {
    E_I2C_BUS_DDCROM,
    E_I2C_BUS_SYS = E_I2C_BUS_DDCROM,
    E_I2C_BUS_DDCA0,
    E_I2C_BUS_DDCD0,
    E_I2C_BUS_DDCD1,
    E_I2C_BUS_DDCD2,
    E_I2C_BUS_USR0,
    E_I2C_BUS_USR1,
    E_I2C_BUS_USR2,
    E_I2C_BUS_USR3,
} E_I2C_BUS_CHANNEL;

_IICDEC_ void MDrv_IIC_Init(void);
_IICDEC_ BOOLEAN MDrv_IIC_WriteBytes(U16 u16BusNumSlaveID, U8 u8addrcount, U8* pu8addr, U16 u16size, U8* pu8data);
_IICDEC_ BOOLEAN MDrv_IIC_ReadBytes(U16 u16BusNumSlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
_IICDEC_ BOOLEAN MDrv_IIC_ReadByte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 *pu8Data);
_IICDEC_ BOOLEAN MDrv_IIC_WriteByte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 u8Data);

_IICDEC_ BOOLEAN MDrv_IIC_Write2Bytes(U16 u16BusNumSlaveID, U8 u8addr, U16 u16data);
_IICDEC_ U16 MDrv_IIC_Read2Bytes(U16 u16BusNumSlaveID, U8 u8addr);
_IICDEC_ BOOLEAN MDrv_IIC_Write4Bytes(U16 u16BusNumSlaveID, U32 u32Data, U8 u8EndData);

_IICDEC_ BOOLEAN MDrv_IIC_ReadByteDirectly(U16 u16BusNumSlaveID, U8 * pu8Data);

_IICDEC_ BOOLEAN MDrv_IIC_WriteGroupBytes(U16 u16BusNumSlaveID, U8 u8SubGroup, U16 u16Addr, U16 u16Data);
_IICDEC_ U16 MDrv_IIC_ReadGroupBytes(U16 u16BusNumSlaveID, U8 u8SubGroup, U16 u16Addr);

_IICDEC_ U32 MDrv_IIC_Speed_Setting(U8 u8BusNum, U32 u32Speed_K);

_IICDEC_ U8 IIC_GetByte (U16  bAck);
_IICDEC_ BOOLEAN IIC_SendByte(U8 u8dat);
_IICDEC_ BOOLEAN IIC_AccessStart(U8 ucSlaveAdr, U8 trans_t);
_IICDEC_ void IIC_Stop(void);

#undef _IICDEC_

#endif // _IIC_H_
