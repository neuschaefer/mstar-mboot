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
//#include <config.h>
//#include <common.h>
//#include <command.h>
//#include <mmc.h>
//#include <part.h>
//#include <malloc.h>
//#include <asm/errno.h>

#include "../../inc/common/eMMC.h"


#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER
#if 0
static U32 eMMC_ReadPartitionInfo_Ex(void);
static U32 eMMC_GetPartitionIndex(U16 u16_PartType,
							               U32 u32_LogicIdx,
							               volatile U16 *pu16_PartIdx);
#endif
#define eMMC_NOT_READY_MARK    ~(('e'<<24)|('M'<<16)|('M'<<8)|'C')
static U32 sgu32_IfReadyGuard = eMMC_NOT_READY_MARK;



//========================================================
U32 eMMC_LoadImages(U32 u32_Addr, U32 u32_ByteCnt, U32 u32_BlkAddr)
{
	U32 u32_err;
    #if defined(eMMC_ROM_ReLoadImages) && eMMC_ROM_ReLoadImages
	U32 (*pf)(U32,U32,U32);

	pf = (void*)eMMC_ROM_LoadImages_Addr();

    if(u32_Addr<=(BOOT_SRAM_START_ADDRESS+Total_SRAM_SIZE))
    {
		u32_err = (*pf)(u32_Addr,u32_ByteCnt,1);
		if(u32_err != eMMC_ST_SUCCESS)
		{
			goto LABEL_LOAD_IMAGE_END;
		}
    }
	else
	{
		//eMMC Identify
		u32_err = eMMC_CheckIfReady();

		if(u32_err != eMMC_ST_SUCCESS)
		{
			goto LABEL_LOAD_IMAGE_END;
		}

		u32_err = eMMC_ReadBootPart((U8*)u32_Addr, u32_ByteCnt,u32_BlkAddr);
		if(u32_err != eMMC_ST_SUCCESS)
		{
			goto LABEL_LOAD_IMAGE_END;
		}
	}

	// --------------------------------
    return eMMC_ST_SUCCESS;
	LABEL_LOAD_IMAGE_END:
	return u32_err;
    #else
	//eMMC Identify
	u32_err = eMMC_CheckIfReady();

    if(u32_err != eMMC_ST_SUCCESS)
    {
	    goto LABEL_LOAD_IMAGE_END;
    }

	u32_err = eMMC_ReadBootPart((U8*)u32_Addr, u32_ByteCnt,u32_BlkAddr);
    if(u32_err != eMMC_ST_SUCCESS)
    {
	    goto LABEL_LOAD_IMAGE_END;
    }
	// --------------------------------
    return eMMC_ST_SUCCESS;
	LABEL_LOAD_IMAGE_END:

	return u32_err;
	#endif
}




//========================================================

eMMC_ALIGN0 U8 g_eMMCDrv_array[15] eMMC_ALIGN1={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static U32 eMMC_Init_Ex(void)
{
	U32 u32_err;
	U8  u8_retry=0;

    eMMC_DRIVER *g_eMMCDrv = (eMMC_DRIVER *)g_eMMCDrv_array;
	// ---------------------------------
    // init platform & FCIE
    g_eMMCDrv->u16_RCA=1;
	eMMC_PlatformInit();
    LABEL_INIT_START:
	eMMC_RST_L();
	eMMC_hw_timer_delay(HW_TIMER_DELAY_1ms);
	g_eMMCDrv->u8_BUS_WIDTH = BIT_SD_DATA_WIDTH_1;
	g_eMMCDrv->u16_Reg10_Mode = BIT_SD_DEFAULT_MODE_REG;
	eMMC_RST_H();
	u32_err = eMMC_FCIE_Init();
	if(u32_err)
        goto  LABEL_INIT_END;

	// ---------------------------------
	// init eMMC device
	u32_err = eMMC_Identify();
	if(eMMC_ST_SUCCESS != u32_err){
		if(u8_retry < 10)
		{
			u8_retry++;
			goto LABEL_INIT_START;
		}
        goto  LABEL_INIT_END;
	}


    REG_FCIE_CLRBIT(FCIE_BOOT_CONFIG, BIT_NAND_BOOT_MODE_EN);
	eMMC_clock_setting(FCIE_SLOW_CLK);

    // setup eMMC device
	// CMD7
	u32_err = eMMC_CMD3_CMD7(g_eMMCDrv->u16_RCA, 7);
	if(eMMC_ST_SUCCESS != u32_err)
		goto  LABEL_INIT_END;


#ifdef IP_FCIE_VERSION_5

	u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HIGH);
	if(eMMC_ST_SUCCESS != u32_err)
        goto  LABEL_INIT_END;
#endif

	// ---------------------------------
	u32_err = eMMC_SetBusWidth(8);
	if(eMMC_ST_SUCCESS != u32_err)
        goto  LABEL_INIT_END;

	sgu32_IfReadyGuard = ~eMMC_NOT_READY_MARK;
	LABEL_INIT_END:
	return u32_err;
}

U32 eMMC_CheckIfReady(void)
{
	if(eMMC_NOT_READY_MARK != sgu32_IfReadyGuard)
	{
		return eMMC_ST_SUCCESS;
	}
	else
	{
    	// boot end
    	#ifndef IP_FCIE_VERSION_5
        REG_FCIE_SETBIT(FCIE_BOOT_CONFIG, BIT_BOOT_END_EN);
        while(1)
        {
            if(REG_FCIE(FCIE_MIE_EVENT)&BIT_CARD_BOOT_DONE)
            {
                REG_FCIE_CLRBIT(FCIE_BOOT_CONFIG, BIT_EMMC_BOOT_MODE_EN);
    			break;
            }
    		eMMC_hw_timer_delay(HW_TIMER_DELAY_1ms);
        }
		REG_FCIE_SETBIT(FCIE_MIE_EVENT, BIT_CARD_BOOT_DONE);
		#endif
	    return eMMC_Init_Ex();
	}
}

U32 eMMC_ReadBootPart(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
	U32 u32_err=0;
	U16 u16_SecCnt;

	// set Access Boot Partition 1
	#ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3|BIT0);
	#else
	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3|BIT0);
	#endif
	if(eMMC_ST_SUCCESS != u32_err)
	{
		return u32_err;
	}

	// read Boot Code
	u16_SecCnt = (u32_DataByteCnt>>eMMC_SECTOR_512BYTE_BITS) + ((u32_DataByteCnt&0x1FF)?1:0);
    #if defined(eMMC_ROM_ReLoadImages) && eMMC_ROM_ReLoadImages
	u32_err = eMMC_ReadData_MIU(pu8_DataBuf, u16_SecCnt<<eMMC_SECTOR_512BYTE_BITS, u32_BlkAddr);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		return u32_err;
	}
	#else
	u32_err = eMMC_ReadData_CIFD(pu8_DataBuf, u16_SecCnt<<eMMC_SECTOR_512BYTE_BITS, u32_BlkAddr);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		return u32_err;
	}
    #endif

	// clear Access Boot Partition
	#ifdef IP_FCIE_VERSION_5
    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT3);
	#else
	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 179, BIT6|BIT3);
	#endif
	if(eMMC_ST_SUCCESS != u32_err)
	{
		return u32_err;
	}

	return u32_err;
}



// =======================================================
// u32_DataByteCnt: has to be 512B-boundary !
// =======================================================
U32 eMMC_ReadData_CIFD(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
	U32 u32_err;
	U16 u16_BlkCnt;

	u16_BlkCnt = 1;
 	while(u32_DataByteCnt)
	{
	    u32_err = eMMC_CMD17_CIFD(u32_BlkAddr, pu8_DataBuf);

		if(eMMC_ST_SUCCESS != u32_err)
		{
			break;
		}

		u32_BlkAddr += u16_BlkCnt;
		pu8_DataBuf += u16_BlkCnt << eMMC_SECTOR_512BYTE_BITS;
		u32_DataByteCnt -= u16_BlkCnt << eMMC_SECTOR_512BYTE_BITS;
	}

	return u32_err;
}

// =======================================================
// u32_DataByteCnt: has to be 512B-boundary !
// =======================================================
U32 eMMC_ReadData_MIU(U8* pu8_DataBuf, U32 u32_DataByteCnt, U32 u32_BlkAddr)
{
	U32 u32_err;
	U16 u16_BlkCnt;

	// read data
	// first 512 bytes, special handle if not cache line aligned
    u16_BlkCnt = (u32_DataByteCnt>>eMMC_SECTOR_512BYTE_BITS) + ((u32_DataByteCnt&0x1FF)?1:0);
	u32_err = eMMC_CMD18_MIU(u32_BlkAddr, pu8_DataBuf, u16_BlkCnt);

	if(eMMC_ST_SUCCESS != u32_err)
	{
		return u32_err;
	}

	return eMMC_ST_SUCCESS;
}


#endif

