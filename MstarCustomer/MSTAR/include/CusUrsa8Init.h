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

#ifndef __CUS_ENVIRONMENT_H__
#define __CUS_ENVIRONMENT_H__
#include <MsTypes.h>

#define UINSIDE "uinside"

#ifdef CONFIG_ANDROID_BOOT
#define CONFIG   "tvservice"
#else
#define CONFIG   ""
#endif

#define CONFIG_PATH   "/config"
#define CSOT_BIN_PATH "ukulele/MERGE_VB1.bin"
#define CMI_BIN_PATH "ukulele/MERGE_4CH_LVDS.bin"
#define FULLHD_BIN_PATH "ukulele/MERGE_LVDS.bin"
#define FULLHD_PANEL_NAME "FullHD_CMO216_H1L01"
#define CSOT_PANEL_NAME "FullHD_CMO216_H1L01_NIKEU_CSOT"
#define CMI_PANEL_NAME "FullHD_CMO216_H1L01_NIKEU_CMI"
#define Dram_Addr (CONFIG_UBOOT_LOADADDR-CONFIG_MIU0_BUSADDR)  //0x300000
#define HEADER_LEN 0xA080
#define UKULELE_AP_START_ADDR 0x10000 //AP addr in ursa miu
#define UKULELE_BIN_START_ADDR 0x100000 //bin file addr in ursa miu
#define UKULELE_BIN_FILE_ADDR_IN_NIKE_MIU (Dram_Addr+CONFIG_MIU0_BUSADDR+0xA00C) //0x2030A00C //bin file aaddr in nike miu, file header A00C~A00E is bin file addr,0x20000000 is nike VA,0x300000 is Dram_Addr, 0x20000000+0x300000+A00C=0x2030A00C
#define UKULELE_BIN_GROUP_ADDR_IN_NIKE_MIU (Dram_Addr+CONFIG_MIU0_BUSADDR+0xA018)//18~1B: BIN_GROUP_MEM_ADDR

#define RIU_RT1_CMD    0x11
#define RIU_W1_CMD     0x1D
#define RIU_R1T_CMD      0x1C
#define MIU_W_CMD      0x25
#define MIU_R_CMD   0x20
#define MIU_ST_CMD       0x21
#define SPI_DEVICE_BUFFER_SIZE           256

#define BIT0  0x000001
#define BIT1  0x000002
#define BIT2  0x000004
#define BIT3  0x000008
#define BIT4  0x000010
#define BIT5  0x000020
#define BIT6  0x000040
#define BIT7  0x000080
#define BIT8  0x000100
#define BIT9  0x000200
#define BIT10 0x000400
#define BIT11 0x000800
#define BIT12 0x001000
#define BIT13 0x002000
#define BIT14 0x004000
#define BIT15 0x008000
#define BIT16 0x010000


MS_BOOL MDrv_SS_RIU_Write8(MS_U16 u16Addr, MS_U8 data);
MS_BOOL MDrv_SS_RIU_Read8(MS_U16 u16Addr, MS_U8 *pdata);
MS_BOOL MDrv_SS_RIU_Write16(MS_U16 u16Addr, MS_U16 data);
MS_BOOL MDrv_SS_MIU_Reads(MS_U32 u32Addr, MS_U8 *pdata, MS_U16 u16Size);
MS_BOOL MDrv_SS_MIU_Writes(MS_U32 u32Addr, MS_U8 *pdata, MS_U32 u16Size);
MS_BOOL MDrv_SS_RIU_Write8_Mask(MS_U16 u16Addr, MS_U8 data, MS_U8 mask);

void InitialSystemPowerUp( void );
void MDrv_Macaw12_MiuInitial(void);
void MDrv_MIU_SimpleBist(void);



int do_cusUrsa8Init( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);



#endif

