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
#include <exports.h>
#include <MsTypes.h>
#include <msAPI_Power.h>
#include <drvBDMA.h>
#include <drvPM.h>
#include <drvWDT.h>
#include <MsApiMiu.h>
#include <MsDebug.h>
#include <MsMmap.h>
#include <MsSystem.h>
#if (CONFIG_VESTEL_MB100 == 1)
#include <MsSysUtility.h>
#endif
#define WDT_STANDBY_MODE 0

#define u32Dummy 0x0EA2
#define URSA6 0x2
#define URSA7 0x4

extern int snprintf(char *str, size_t size, const char *fmt, ...);
#if (CONFIG_ENABLE_RTPM)

int do_run_time_pm( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN");

#if(CONFIG_ENABLE_URSA_RTPM)
    #if(CONFIG_MSTAR_URSA6_VB1)
        Write2Byte(u32Dummy, URSA6);                      //write flag for ursa6
    #endif
    
    #if(CONFIG_MSTAR_URSA7_VB1)                     //write flag for ursa7
        Write2Byte(u32Dummy, URSA7);
    #endif
#endif

#if (CONFIG_MSTAR_RT_PM_IN_SPI)
	U32  u32Addr=0;
	if(get_addr_from_mmap("MMAP_PM_PROGRAM", &u32Addr)!=0)
	{
		UBOOT_ERROR("get MMAP_PM_PROGRAM mmap fail\n");
	}
	if(get_addr_from_mmap("E_MMAP_ID_PM51_USAGE_MEM", &u32Addr)!=0)
	{
		UBOOT_ERROR("get E_MMAP_ID_PM51_USAGE_MEM mmap fail\n");
	}

    if(u32Addr==0xFFFF)
    {
        UBOOT_ERROR("Get Mmap for PM51 Failed Skip Runtime PM !!! \n");
        return -1;
    }

    UBOOT_DEBUG("=================================================\n");
    UBOOT_DEBUG("|        |    SPI    |     DRAM     |    SIZ     |\n");
    UBOOT_DEBUG("|--------+-----------+--------------+------------|\n");
    UBOOT_DEBUG("| DDR_PM |  0x20000  |");
	UBOOT_DEBUG("    0x%x       |",u32Addr);
	UBOOT_DEBUG("    0x%x   |\n",RUNTIME_PM_START_SIZE);
    UBOOT_DEBUG("=================================================\n");
	if(u32Addr==0xFFFF)
	{
		UBOOT_ERROR("Get Mmap for PM51 Failed Skip Runtime PM !!! \n");
		return -1;
	}
    MDrv_BDMA_CopyHnd(0x20000,u32Addr,RUNTIME_PM_START_SIZE,E_BDMA_FLASH2SDRAM,0);
	MsApi_RunTimePmProtect();
    MDrv_PM_SetDRAMOffsetForMCU(u32Addr);                // Wake up DDR_PM

    return 0;
#endif

#if (CONFIG_MSTAR_RT_PM_IN_NAND)
    U32 u32Addr=0;
    char cmd[128];
    
    memset(cmd, 0, sizeof(cmd));
    #if (CONFIG_VESTEL_MB100 == 0)
    if(get_addr_from_mmap("E_MMAP_ID_PM51_USAGE_MEM", &u32Addr)!=0)
	{
		UBOOT_ERROR("get E_MMAP_ID_PM51_USAGE_MEM mmap fail\n");
		return -1;
	}
    
    if(u32Addr==0xFFFF)
    {
		UBOOT_ERROR("Get Mmap for PM51 Failed Skip Runtime PM !!! \n");
		return -1;
    }
    #else
    //E_MMAP_ID_DUMMY1 (MMAP_PM_PROGRAM), //@ 0x2FE90000 0x10000 0x10000
    u32Addr = 0x2FE90000; //temp hard coding from mbrg_mmap_MB99_1_256_256.h
    #endif
    UBOOT_DEBUG("=================================================\n");
    UBOOT_DEBUG("    u32Addr=0x%x\n",u32Addr);
    UBOOT_DEBUG("    RUNTIME_PM_START_SIZE=0x%x\n",RUNTIME_PM_START_SIZE);
    UBOOT_DEBUG("=================================================\n");
    
    snprintf(cmd, sizeof(cmd)-1, "nand read.e 0x%08lX RTPM 10000", (U32)(PA2NVA(u32Addr)));    
    
    if(-1 != run_command(cmd, 0))
    {
        UBOOT_DEBUG("\n[%s: %d] read the RTPM partion data:\n",__func__,__LINE__);
    }
    else
    {
        UBOOT_ERROR("%s: '%s' fails, at %d\n", __func__, cmd, __LINE__);
        return -1;
    }    
    MsApi_RunTimePmProtect();
    MDrv_PM_SetDRAMOffsetForMCU(u32Addr);                     // Wake up DDR_PM
    UBOOT_TRACE("OK\n");
	return 0;
#endif

#if (CONFIG_MSTAR_RT_PM_IN_EMMC)
    U32 u32Addr=0;
    char cmd[128];
    
    memset(cmd, 0, sizeof(cmd));
#if (CONFIG_VESTEL_MB100 == 1)
    if(get_addr_from_mmap("MMAP_PM_PROGRAM", &u32Addr)!=0)
	{
		UBOOT_ERROR("get MMAP_PM_PROGRAM mmap fail\n");
		return -1;
    }
#else
    if(get_addr_from_mmap("E_MMAP_ID_PM51_USAGE_MEM", &u32Addr)!=0)
	{
		UBOOT_ERROR("get E_MMAP_ID_PM51_USAGE_MEM mmap fail\n");
		return -1;
    }
#endif
    
    if(u32Addr==0xFFFF)
    {
		UBOOT_ERROR("Get Mmap for PM51 Failed Skip Runtime PM !!! \n");
		return -1;
    }

    UBOOT_DEBUG("=================================================\n");
    UBOOT_DEBUG("    u32Addr=0x%x\n",u32Addr);
    UBOOT_DEBUG("    RUNTIME_PM_START_SIZE=0x%x\n",RUNTIME_PM_START_SIZE);
    UBOOT_DEBUG("=================================================\n");
    
    snprintf(cmd, sizeof(cmd)-1, "mmc read.p 0x%08lX RTPM 0x10000", (U32)(PA2NVA(u32Addr)));    
    
    if(-1 != run_command(cmd, 0))
    {
        UBOOT_DEBUG("\n[%s: %d] read the RTPM partion data:\n",__func__,__LINE__);
    }
    else
    {
        UBOOT_ERROR("%s: '%s' fails, at %d\n", __func__, cmd, __LINE__);
        return -1;
    }    
    MsApi_RunTimePmProtect();
    MDrv_PM_SetDRAMOffsetForMCU(u32Addr);                     // Wake up DDR_PM
	UBOOT_TRACE("OK\n");
    return 0;
#endif    
}
#endif
MS_BOOL pm_check_back_ground_active(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_BOOL bActive = FALSE;
    if(E_PM_FAIL  == MDrv_PM_IsActiveStandbyMode(&bActive))
    {
        printf("\x1b[37;41m ===== [%s:%s:%d] MDrv_PM_IsBackGroundModeActive FAIL ===== \x1b[0m\n",__FILE__,__FUNCTION__,__LINE__);
    }
    if(bActive)
    {
        UBOOT_DEBUG(" Active Standby Mode TRUE =====");
    }
    else
    {
        UBOOT_DEBUG(" Active Standby Mode False =====");
    }
    //FOR TM14 STR Resume  
    if(E_PM_WAKEUPSRC_AVLINK==MDrv_PM_GetWakeupSource())
    {
        bActive = TRUE;
        UBOOT_DEBUG(" MDrv_PM_GetWakeupSource TRUE =====");

    }
    return bActive;
}



