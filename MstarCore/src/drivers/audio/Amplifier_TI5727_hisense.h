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
#ifndef AMPLIFIER_TI5727_HISENSE_H
#define AMPLIFIER_TI5727_HISENSE_H

#define MAPI_BOOL MS_BOOL
#define MAPI_U8 MS_U8
#define MAPI_TRUE TRUE

enum
{
    I2C_Sub_ClockControlReg 		= 0x00,		// default 0x6C		1 byte
    I2C_Sub_DeviceIDReg       		= 0x01,		// default 0x28		1 byte
    I2C_Sub_ErrorStatusReg   		= 0x02,		// default 0x00		1 byte
    I2C_Sub_SystemControl1Reg     = 0x03,		// default 0xA0		1 byte
    I2C_Sub_SerialDataInterReg     = 0x04,		// default 0x05		1 byte
    I2C_Sub_SystemControl2Reg     = 0x05,		// default 0x40		1 byte
    I2C_Sub_SoftMuteReg			= 0x06,		// default 0x00		1 byte
    I2C_Sub_MasterVolumnReg		= 0x07,		// default 0xFF(Mute)	1 byte
    I2C_Sub_Channel1VolReg		= 0x08,		// default 0x30(0 db)		1 byte
    I2C_Sub_Channel2VolReg		= 0x09,		// default 0x30(0 db)		1 byte
    I2C_Sub_Channel3VolReg		= 0x0A,		// default 0x30(0 db)		1 byte
    I2C_Sub_Channel4VolReg		= 0x0B,		// default 0x30(0 db)		1 byte
    I2C_Sub_HpVolReg				= 0x0C,		// default 0x30(0 db)		1 byte
    I2C_Sub_Channel6VolReg		= 0x0D,		// default 0x30(0 db)		1 byte
    I2C_Sub_VolumnConfigReg		= 0x0E,		// default 0x91		1 byte
    //I2C_Sub_ReservedReg			= 0x0F,		//  Reserved

    I2C_Sub_ModLimitReg			= 0x10,		//  default 0x02		1 byte
    I2C_Sub_IcDelayCh1Reg		= 0x11,		//  default 0x4C	1 byte
    I2C_Sub_IcDelayCh2Reg		= 0x12,		//  default 0x34		1 byte
    I2C_Sub_IcDelayCh3Reg		= 0x13,		//  default 0x1C	1 byte
    I2C_Sub_IcDelayCh4Reg		= 0x14,		//  default 0x64		1 byte
    I2C_Sub_IcDelayCh5Reg		= 0x15,		//  default 0xB0	1 byte
    I2C_Sub_IcDelayCh6Reg		= 0x16,		//  default 0x90		1 byte
    I2C_Sub_OffsetReg			= 0x17,		//  default 0x00		1 byte
    I2C_Sub_ReservedReg			= 0x18,		//  Reserved
    I2C_Sub_PwmShutReg			= 0x19,		//  default 0x30		1 byte
    I2C_Sub_StartPeriodReg		= 0x1A,		//  default 0x0A	1 byte
    I2C_Sub_OscTrimReg			= 0x1B,		//  default 0x82		1 byte
    I2C_Sub_BkErrorReg			= 0x1C,		//  default 0x02		1 byte
    //I2C_Sub_ReservedReg			= 0x1D,		//  Reserved
    //I2C_Sub_ReservedReg			= 0x1E,		//  Reserved
    //I2C_Sub_ReservedReg			= 0x1F,		//  Reserved

    I2C_Sub_InputMuxReg			= 0x20,		//  default 0x0089777A		4 byte
    I2C_Sub_DownMixInputReg		= 0x21,		//  default 0x00004203		4 byte
    I2C_Sub_AmTunFreqReg		= 0x22,		//  default 0x00000000		4 byte
    I2C_Sub_Ch6Bq2Reg			= 0x23,		//  default 0x00800000		20 byte (loudness BQ)  ....other value eq 0x000000000
    I2C_Sub_Ch6Bq3Reg			= 0x24,		//  default 0x00800000		20 byte (post vol BQ)  ....other value eq 0x000000000
    I2C_Sub_PwmMuxReg			= 0x25,		//  default 0x01021345		4  byte
    I2C_Sub_1DivGReg			= 0x26,		//  default 0x00800000		4  byte
    //I2C_Sub_ReservedReg			= 0x27,		//  Reserved
    I2C_Sub_ScaleReg				= 0x28,		//  default 0x00800000		4  byte
    I2C_Sub_Ch1Bq0Reg			= 0x29,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch1Bq1Reg			= 0x2A,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch1Bq2Reg			= 0x2B,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch1Bq3Reg			= 0x2C,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch1Bq4Reg			= 0x2D,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch1Bq5Reg			= 0x2E,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch1Bq6Reg			= 0x2F,		//  default 0x00800000		20 byte   ....other value eq 0x000000000

    I2C_Sub_Ch2Bq0Reg			= 0x30,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch2Bq1Reg			= 0x31,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch2Bq2Reg			= 0x32,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch2Bq3Reg			= 0x33,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch2Bq4Reg			= 0x34,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch2Bq5Reg			= 0x35,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch2Bq6Reg			= 0x36,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch6Bq0Reg			= 0x37,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    I2C_Sub_Ch6Bq1Reg			= 0x38,		//  default 0x00800000		20 byte   ....other value eq 0x000000000
    //I2C_Sub_ReservedReg			= 0x39,		//  Reserved
    I2C_Sub_Drc1aeReg			= 0x3A,		//  default 0x00800000		8  byte   ....other value eq 0x000000000
    I2C_Sub_Drc1aaReg			= 0x3B,		//  default 0x00800000		8  byte   ....other value eq 0x000000000
    I2C_Sub_Drc1adReg			= 0x3C,		//  default 0x00800000		8  byte   ....other value eq 0x000000000
    I2C_Sub_Drc2aeReg			= 0x3D,		//  default 0x00800000		8  byte   ....other value eq 0x000000000
    I2C_Sub_Drc2aaReg			= 0x3E,		//  default 0x00800000		8  byte   ....other value eq 0x000000000
    I2C_Sub_Drc2adReg			= 0x3F,		//  default 0x00800000		8  byte   ....other value eq 0x000000000

    I2C_Sub_Drc1TReg			= 0x40,		//  default 0xFDA21490		4 byte
    I2C_Sub_Drc1KReg			= 0x41,		//  default 0x03842109		4 byte
    I2C_Sub_Drc1OReg			= 0x42,		//  default 0x03842109		4 byte
    I2C_Sub_Drc2TReg			= 0x43,		//  default 0xFDA21490		4 byte
    I2C_Sub_Drc2KReg			= 0x44,		//  default 0x03842109		4 byte
    I2C_Sub_Drc2OReg			= 0x45,		//  default 0x03842109		4 byte
    I2C_Sub_DrcControlReg		= 0x46,		//  default 0x00000000		4 byte
    //I2C_Sub_ReservedReg			= 0x47,		//  Reserved
    //I2C_Sub_ReservedReg			= 0x48,		//  Reserved
    //I2C_Sub_ReservedReg			= 0x49,		//  Reserved

    I2C_Sub_BankUpdateComReg	= 0x50,		//  default 0x00000000		4 byte

};

    MAPI_BOOL  Amplifier_TI5727_hisense_Init(void);
    //MAPI_BOOL  Amplifier_VolumeForSource(void);

    MAPI_BOOL Amplifier_TI5727_hisense_SWMute(MAPI_BOOL bMute);
    MAPI_BOOL Amplifier_TI5727_hisense_Mute(MAPI_U8 u8Para);
    MAPI_BOOL Amplifier_TI5727_hisense_StandBy(MAPI_U8 u8Para);
    MAPI_BOOL Amplifier_TI5727_hisense_Reset(MAPI_U8 u8Para);

//wjq20100112<<<
#endif
