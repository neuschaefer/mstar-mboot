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
#ifndef __UNFD_CONFIG_H__
#define __UNFD_CONFIG_H__

//=====================================================
// select a HW platform:
//   - 1: enable, 0: disable.
//   - only one platform can be 1, others have to be 0.
//=====================================================
#define NAND_DRV_TV_SBOOT           1


//=====================================================
// do NOT edit the following content.
//=====================================================
#if defined(CONFIG_MSTAR_EMERALD) && CONFIG_MSTAR_EMERALD
    #include "drvNAND_emerald_sboot.h"
#elif defined(CONFIG_MSTAR_NUGGET) && CONFIG_MSTAR_NUGGET
    #include "drvNAND_nugget_sboot.h"
#elif defined(CONFIG_MSTAR_NIKON) && CONFIG_MSTAR_NIKON
    #include "drvNAND_nikon_sboot.h"
#elif defined(CONFIG_MSTAR_EAGLE) && CONFIG_MSTAR_EAGLE
	#include "drvNAND_eagle_sboot.h"
#elif defined(CONFIG_MSTAR_EIFFEL) && CONFIG_MSTAR_EIFFEL
	#include "drvNAND_eiffel_sboot.h"
#elif defined(CONFIG_MSTAR_NIKE) && CONFIG_MSTAR_NIKE
	#include "drvNAND_nike_sboot.h"
#elif defined(CONFIG_MSTAR_MADISON) && CONFIG_MSTAR_MADISON
	#include "drvNAND_madison_sboot.h"
#elif defined(CONFIG_MSTAR_CLIPPERS) && CONFIG_MSTAR_CLIPPERS
	#include "drvNAND_clippers_sboot.h"
#elif defined(CONFIG_MSTAR_MIAMI) && CONFIG_MSTAR_MIAMI
	#include "drvNAND_miami_sboot.h"
#elif defined(CONFIG_MSTAR_MONACO) && CONFIG_MSTAR_MONACO
	#include "drvNAND_monaco_sboot.h"
#elif defined(CONFIG_MSTAR_MUJI) && CONFIG_MSTAR_MUJI
	#include "drvNAND_muji_sboot.h"
#elif defined(CONFIG_MSTAR_CELTICS) && CONFIG_MSTAR_CELTICS
	#include "drvNAND_celtics_sboot.h"
#elif defined(CONFIG_MSTAR_KENYA) && CONFIG_MSTAR_KENYA
    #include "drvNAND_kenya_sboot.h"
#elif defined(CONFIG_MSTAR_NADAL) && CONFIG_MSTAR_NADAL
	#include "drvNAND_nadal_sboot.h"
#elif defined(CONFIG_MSTAR_NAPOLI) && CONFIG_MSTAR_NAPOLI
	#include "drvNAND_napoli_sboot.h"
#elif defined(CONFIG_MSTAR_KRITI) && CONFIG_MSTAR_KRITI
    #include "drvNAND_kriti_sboot.h"	
#else
    #error "Error! no platform selected."
#endif


//do NOT edit the following content, for HAL use.
//=====================================================
// misc. do NOT edit the following content.
//=====================================================
#define NAND_DMA_RACING_PATCH       1
#define NAND_DMA_PATCH_WAIT_TIME    10000 // us -> 10ms
#define NAND_DMA_RACING_PATTERN0    (((U32)'M'<<24)|((U32)0<<16)|((U32)'S'<<8)|(U32)1)
#define NAND_DMA_RACING_PATTERN1    (((U32)'T'<<24)|((U32)6<<16)|((U32)'A'<<8)|(U32)8)


//===========================================================
// Time Dalay, do NOT edit the following content, for NC_WaitComplete use.
//===========================================================
#define DELAY_100us_in_us           HW_TIMER_DELAY_100us
#define DELAY_300us_in_us           HW_TIMER_DELAY_100us * 3
#define DELAY_500us_in_us           HW_TIMER_DELAY_100us * 5
#define DELAY_1ms_in_us             HW_TIMER_DELAY_1ms
#define DELAY_10ms_in_us            HW_TIMER_DELAY_10ms
#define DELAY_100ms_in_us           HW_TIMER_DELAY_100ms
#define DELAY_500ms_in_us           HW_TIMER_DELAY_500ms
#define DELAY_1s_in_us              HW_TIMER_DELAY_1s

#define WAIT_ERASE_TIME             (DELAY_1s_in_us)
#define WAIT_WRITE_TIME             (DELAY_1s_in_us)
#define WAIT_READ_TIME              (DELAY_1ms_in_us)
#define WAIT_PROBE_TIME             (DELAY_300us_in_us)
#define WAIT_RESET_TIME             (DELAY_10ms_in_us)

extern void nand_reset_WatchDog(void);
extern U32 nand_clock_setting(U32 u32ClkParam);
extern U32 nand_config_clock(U16 u16_SeqAccessTime);
extern U32 nand_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void nand_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size);
extern U32 nand_WaitCompleteIntr(U16 u16_WaitEvent, U32 u32_MicroSec);
extern void nand_enable_intr_mode(void);
extern void nand_flush_miu_pipe(void);

extern void drvNAND_CHECK_FLASH_TYPE(void);

#define NAND_PARTITAION_BYTE_CNT    0x200

#endif /* __UNFD_CONFIG_H__ */
