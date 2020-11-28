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

#ifndef __DRVMIU__
#define __DRVMIU__

#include <common.h>
#include <malloc.h>
#include <asm/io.h>
#include <configs/uboot_board_config.h>
#include <ShareType.h>
#include <drvMIU.h>

#if 0
#define BIT1        0x0002
#define BIT2        0x0004
#define BIT3        0x0008
#define BIT4        0x0010
#define BIT5        0x0020
#define BIT6        0x0040
#define BIT7        0x0080
#define BIT8        0x0100
#define BIT9        0x0200
#define BIT10       0x0400
#define BIT11       0x0800
#define BIT12       0x1000
#define BIT13       0x2000
#define BIT14       0x4000
#define BIT15       0x8000
#endif

#define CONFIG_SYS_MIU2_INTERVAL 0xC0000000

#if defined(CONFIG_JANUS) || defined(CONFIG_MARIA10)

#define		MIUREG_BASE		            (0xA0200000)
//Max MIU Group number
#define		MIU_MAX_GP_NUM		        (4)
//MIU group priority
#define		REG_MIU_GP_PRIORITY		    (0x6E << 1)

#define      PM_TOP_BASE               0xA0000000
#define      CHIP_ID                   0x001E00
#define      CHIP_VER                  0x001E03


#elif defined(CONFIG_AMBER1) || defined(CONFIG_KRONUS) || defined(CONFIG_KAISERIN) || defined(CONFIG_KENYA) || defined(CONFIG_KERES) || defined(CONFIG_KRITI)
#define		MIUREG_BASE		            (0xBF200000)
//Max MIU Group number
#define		MIU_MAX_GP_NUM		        (4)
//MIU group priority
#define		REG_MIU_GP_PRIORITY		    (0x7F << 1)

#define      PM_TOP_BASE               0xBF000000
#define      CHIP_ID                   0x001E00
#define      CHIP_VER                  0x001E03

#elif (ENABLE_AGATE == 1)

#define		MIUREG_BASE		            (0x1F200000)
//Max MIU Group number
#define		MIU_MAX_GP_NUM		        (4)
//MIU group priority
#define		REG_MIU_GP_PRIORITY		    (0x7F << 1)

#define      PM_TOP_BASE               0x1F000000
#define      CHIP_ID                   0x001E00
#define      CHIP_VER                  0x001E03

#elif (ENABLE_AMBER3 == 1)

#define		MIUREG_BASE		            (0x1F200000)
//Max MIU Group number
#define		MIU_MAX_GP_NUM		        (4)
//MIU group priority
#define		REG_MIU_GP_PRIORITY		    (0x7F << 1)

#define      PM_TOP_BASE               0x1F000000
#define      CHIP_ID                   0x001E00
#define      CHIP_VER                  0x001E03

#elif (ENABLE_EDISON == 1)

#define		MIUREG_BASE		            (0x1F200000)
//Max MIU Group number
#define		MIU_MAX_GP_NUM		        (4)
//MIU group priority
#define		REG_MIU_GP_PRIORITY		    (0x7F << 1)

#define      PM_TOP_BASE               0x1F000000
#define      CHIP_ID                   0x001E00
#define      CHIP_VER                  0x001E03

#elif (ENABLE_KAISER==1)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_EAGLE)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_EIFFEL)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_NIKE)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_MADISON)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_CLIPPERS)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_MIAMI)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (6)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_NADAL)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER                    0x001E03

#elif (ENABLE_EINSTEIN)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER   					0x001E03

#elif (ENABLE_NAPOLI)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (4)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER   					0x001E03

#elif (ENABLE_MONACO)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (6)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER   					0x001E03

#elif (ENABLE_MUJI)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (6)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER   					0x001E03

#elif (ENABLE_CELTICS)
#define MIUREG_BASE		            (0x1F200000)
#define	MIU_MAX_GP_NUM		        (6)         //Max MIU Group number
#define	REG_MIU_GP_PRIORITY		    (0x7F << 1) //MIU group priority
#define PM_TOP_BASE                 0x1F000000
#define CHIP_ID                     0x001E00
#define CHIP_VER   					0x001E03

#else

#define		MIUREG_BASE		            (0xBF200000)
//Max MIU Group number
#define		MIU_MAX_GP_NUM		        (4)
//MIU group priority
#define		REG_MIU_GP_PRIORITY		    (0x6E << 1)

#define      PM_TOP_BASE               0xBF000000
#define      CHIP_ID                   0x001E00
#define      CHIP_VER                  0x001E03


#endif
typedef struct
{
    MIU_ID miu_id;
    MS_U8 u8Group;
    char *c_Mmap_Id;
    MS_U32 u32Start; 
    MS_U32 u32End;
    MS_U8 clientID[16];
} stMIU_PortectInfo;



///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Register Map
///
///////////////////////////////////////////////////////////////////////////////////////////////////
#define MIU0_REG_BASE				    (0x1200)
#define MIU1_REG_BASE				    (0x0600)
#define MIU2_REG_BASE				    (0x62000)

//MIU select group 0
#define		REG_MIUSEL_GP0				(0x78 << 1)
//MIU select group 1
#define		REG_MIUSEL_GP1				(0x79 << 1)
//MIU select group 2
#define		REG_MIUSEL_GP2				(0x7A << 1)
//MIU select group 3
#if(ENABLE_MSTAR_CLIPPERS) 
#define		REG_MIUSEL_GP3				(0x7C << 1)
#else
#define		REG_MIUSEL_GP3				(0x7B << 1)
#endif
//MIU select group 4
#define		REG_MIUSEL_GP4				(0x7C << 1)
//MIU select group 5
#define		REG_MIUSEL_GP5				(0x7D << 1)

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Global Functions
///
///////////////////////////////////////////////////////////////////////////////////////////////////
U8 MDrv_MIU_SelectMIU_UBoot(U8 bMIU1, U16 *au16SelMiu, U8 u8GpNum);
U8 MDrv_MIU_SetGroupPriority_UBoot(U8 bMIU1, U8 *au8GpPriority, U8 u8GpNum);
MS_BOOL MsDrv_MIU_Protect(MS_U8  u8Blockx, MS_U8  *pu8ProtectId, MS_U32 u32Start, MS_U32 u32End, MS_BOOL bSetFlag);
void MsDrv_kernelProtect(MS_U8  u8Blockx,MS_U32 u32Lx1Start, MS_U32 u32Lx1End);
void MsDrv_PMProtect(MS_U8  u8Blockx,MS_U32 u32Lx1Start, MS_U32 u32Lx1End);
void MsDrv_NuttxProtect(MS_U8  u8Blockx,MS_U32 u32NuttxStart, MS_U32 u32NuttxEnd);
void MsDrv_MiuInit(void);
MIU_DDR_SIZE dram_size_to_enum(MS_U32 u32DramSize);
MS_U32 BA2PA(MS_U32 u32BusAddr);
MS_U32 PA2BA(MS_U32 u32PhyAddr);


#endif	//__DRVMIU__

