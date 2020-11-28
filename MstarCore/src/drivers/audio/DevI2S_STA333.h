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

#ifndef _DEVI2S_H_
#define _DEVI2S_H_

#ifndef _BIT0
#define _BIT0  0x0001
#endif
#ifndef _BIT1
#define _BIT1  0x0002
#endif
#ifndef _BIT2
#define _BIT2  0x0004
#endif
#ifndef _BIT3
#define _BIT3  0x0008
#endif
#ifndef _BIT4
#define _BIT4  0x0010
#endif
#ifndef _BIT5
#define _BIT5  0x0020
#endif
#ifndef _BIT6
#define _BIT6  0x0040
#endif
#ifndef _BIT7
#define _BIT7  0x0080
#endif
#ifndef _BIT8
#define _BIT8  0x0100
#endif
#ifndef _BIT9
#define _BIT9  0x0200
#endif
#ifndef _BIT10
#define _BIT10 0x0400
#endif
#ifndef _BIT11
#define _BIT11 0x0800
#endif
#ifndef _BIT12
#define _BIT12 0x1000
#endif
#ifndef _BIT13
#define _BIT13 0x2000
#endif
#ifndef _BIT14
#define _BIT14 0x4000
#endif
#ifndef _BIT15
#define _BIT15 0x8000
#endif

#define DDX_I2C_WRITE_ADD							        0x38
#define STA333_ADDR     (((U16) E_I2C_BUS_SYS << 8) | DDX_I2C_WRITE_ADD)
#define DDX_CONFIGURE_A								0x00
#define DDX_CONFIGURE_B								0x01
#define DDX_CONFIGURE_C								0x02
#define DDX_CONFIGURE_D								0x03
#define DDX_CONFIGURE_E								0x04
#define DDX_CONFIGURE_F								0x05

#define DDX_MUTE									0x06
#define DDX_MAIN_VOLUME								0x07
#define DDX_CHANNEL1_VOL							0x08
#define DDX_CHANNEL2_VOL							0x09
#define DDX_CHANNEL3_VOL 							0x0a

#define DDX_AUTO1			 						0x0b
#define DDX_AUTO2			 						0x0c
#define DDX_AUTO3			 						0x0d

#define DDX_CHANNEL1_CFG 							0x0e
#define DDX_CHANNEL2_CFG 							0x0f
#define DDX_CHANNEL3_CFG 							0x10

#define DDX_TONEBASS								0x11
#define DDX_L1AR_RATE								0x12
#define DDX_L1AR_THRESHOLD							0x13
#define DDX_L2AR_RATE								0x14
#define DDX_L2AR_THRESHOLD							0x15

#define		REG_CFADDR1			0x16	/* Cfaddr1 */
#define		REG_B1CF1			0x17	/* B1cf1 */
#define		REG_B1CF2			0x18	/* B1cf2 */
#define		REG_B1CF3			0x19	/* B1cf3 */
#define		REG_B2CF1			0x1a	/* B2cf1 */
#define		REG_B2CF2			0x1b	/* B2cf2 */
#define		REG_B2CF3			0x1c	/* B2cf3 */
#define		REG_A1CF1			0x1d	/* A1cf1 */
#define		REG_A1CF2			0x1e	/* A1cf2 */
#define		REG_A1CF3			0x1f	/* A1cf3 */
#define		REG_A2CF1			0x20	/* A2cf1 */
#define		REG_A2CF2			0x21	/* A2cf2 */
#define		REG_A2CF3			0x22	/* A2cf3 */
#define		REG_B0CF1			0x23	/* B0cf1 */
#define		REG_B0CF2			0x24	/* B0cf2 */
#define		REG_B0CF3			0x25	/* B0cf3 */
#define		REG_CFUD			0x26	/* Cfud */


#define MAX_VOLUME				50

void DevI2s_STA333_Init(void);
void DevI2S_STA333_SubwoofValue(MS_U8 Subwoof);
#if 0//(ENABLE_WALL_MODE)
void DevI2SSetCFTableByMode(SoundWallModeType mode);
#else
void DevI2S_STA333_SetCFTable(void);
#endif
void DecI2S_STA333_Patch(BYTE ucCtl);
MS_BOOL STA333_GetPowerDNStatus(void);
#endif
