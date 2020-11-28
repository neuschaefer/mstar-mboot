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
//=======================================================================
//  MStar Semiconductor - Unified Nand Flash Driver
//
//  drvNAND_platform.c - Storage Team, 2009/08/20
//
//  Design Notes: defines common platform-dependent functions.
//
//    1. 2009/08/25 - support C5 eCos platform
//
//=======================================================================
#include "../../inc/common/drvNAND.h"

//=============================================================
#if (defined(NAND_DRV_TV_SBOOT) && NAND_DRV_TV_SBOOT)

U32 nand_hw_timer_delay(U32 u32usTick)
{
    U32 u32HWTimer = 0;
	volatile U16 u16TimerLow = 0;
	volatile U16 u16TimerHigh = 0;

	// reset HW timer
	REG_WRITE_UINT16(TIMER0_MAX_LOW, 0xFFFF);
	REG_WRITE_UINT16(TIMER0_MAX_HIGH, 0xFFFF);
	REG_WRITE_UINT16(TIMER0_ENABLE, 0);

	// start HW timer
	REG_SET_BITS_UINT16(TIMER0_ENABLE, 0x0001);

	while( u32HWTimer < 12*u32usTick ) // wait for u32usTick micro seconds
	{
		REG_READ_UINT16(TIMER0_CAP_LOW, u16TimerLow);
		REG_READ_UINT16(TIMER0_CAP_HIGH, u16TimerHigh);

		u32HWTimer = (u16TimerHigh<<16) | u16TimerLow;
	}

	REG_WRITE_UINT16(TIMER0_ENABLE, 0);

    return u32usTick+1;
}


//static UNFD_ALIGN0 NAND_DRIVER sg_NandDrv UNFD_ALIGN1;

void *drvNAND_get_DrvContext_address(void) // exposed API
{
	return (void*)(CONFIG_SRAM_BASE_ADDRESS + CONFIG_SRAM_FCIE_OFFSET);
}

U32 nand_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt)
{
#if defined(CONFIG_MCU_MIPS32)
	flush_cache(u32_DMAAddr, u32_ByteCnt);
	return (u32_DMAAddr & 0x1fffffff);
#else
	u32_ByteCnt = u32_ByteCnt;
	return (u32_DMAAddr & 0x1fffffff);
#endif
}

void nand_switch_sram(U32 u32_Offset)
{
	u32_Offset = u32_Offset;
	#if  defined(CONFIG_MSTAR_MADISON) || defined(CONFIG_MSTAR_MILAN)
	if( u32_Offset >= 8192 )
		REG_SET_BITS_UINT16(NC_REG_PAD_SWITCH, BIT6);
	else
		REG_CLR_BITS_UINT16(NC_REG_PAD_SWITCH, BIT6);
	#endif
}

#ifdef REMAP_PPM_ADDR
void nand_remap_ppm_addr(PAIRED_PAGE_MAP_t **pptPairedPageMapSRAM)
{
	U16 u16_Reg;

	REG_READ_UINT16(REG_CHIP_REVISION, u16_Reg);
	u16_Reg = (u16_Reg>>8)&0xFF;

	#if defined(CONFIG_MSTAR_EIFFEL)
	if(u16_Reg >= 1)
		*pptPairedPageMapSRAM = (PAIRED_PAGE_MAP_t *) (ROM_PPM_ADDR_U02);
	#elif defined(CONFIG_MSTAR_NIKE)
	if(u16_Reg >= 2)
		*pptPairedPageMapSRAM = (PAIRED_PAGE_MAP_t *) (ROM_PPM_ADDR_U03);
	#elif defined(CONFIG_MSTAR_NADAL)
	if(u16_Reg >= 0)
		*pptPairedPageMapSRAM = (PAIRED_PAGE_MAP_t *) (ROM_PPM_ADDR_U01);
	#elif defined(CONFIG_MSTAR_NUGGET)
	if(u16_Reg >= 1)
		*pptPairedPageMapSRAM = (PAIRED_PAGE_MAP_t *) (ROM_PPM_ADDR_U02);
	#endif
}
#endif

#else

    #error "Error! no platform functions."

#endif

