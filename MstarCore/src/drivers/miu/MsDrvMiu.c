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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Inlucde Fils
///
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <drvMIU.h>
#include <MsTypes.h>

#include <common.h>
#include <MsDebug.h>

#include <miu/MsDrvMiu.h>
#define MIU_ALIGN(_val_,_shift_) (((_val_) >> _shift_) << _shift_)
static MS_U8 miuInit=0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Internal Functions
///
///////////////////////////////////////////////////////////////////////////////////////////////////
U8 _MIU_ReadByte(U32 u32RegOffset)
{
    return ((volatile U8*)(MIUREG_BASE))[(u32RegOffset << 1) - (u32RegOffset & 1)];
}

U16 _MIU_Read2Bytes(U32 u32RegOffset)
{
    return ((volatile U16*)(MIUREG_BASE))[u32RegOffset];
}

void _MIU_WriteByte(U32 u32RegOffset, U8 u8Val)
{
    ((volatile U8*)(MIUREG_BASE))[(u32RegOffset << 1) - (u32RegOffset & 1)] = u8Val;
}

void _MIU_Write2Bytes(U32 u32RegOffset, U16 u16Val)
{
    ((volatile U16*)(MIUREG_BASE))[u32RegOffset] = u16Val;
}

void _MIU_WriteBytesBit(U32 u32RegOffset, U8 bEnable, U16 u16Mask)
{
    U16 val = _MIU_Read2Bytes(u32RegOffset);
    val = (bEnable) ? (val | u16Mask) : (val & ~u16Mask);
    _MIU_Write2Bytes(u32RegOffset, val);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Global Functions
///
///////////////////////////////////////////////////////////////////////////////////////////////////
MS_U32 BA2PA(MS_U32 u32BusAddr)
{
#if defined(__ARM__)

if(u32BusAddr<CONFIG_SYS_MIU1_BUS)
{
    return (u32BusAddr - CONFIG_SYS_MIU0_BUS);
}
else
{
    return (u32BusAddr - CONFIG_SYS_MIU1_BUS+CONFIG_SYS_MIU_INTERVAL);
}


#else
	if ((0x00000000 <= u32BusAddr) && (0x10000000 > u32BusAddr))
    {
        return (u32BusAddr);
    }
	if ((0x40000000 <= u32BusAddr) && (0x50000000 > u32BusAddr))
    {
        return (u32BusAddr & 0x0fffffff);
    }
	if ((0x50000000 <= u32BusAddr) && (0x60000000 > u32BusAddr))
    {
        return (u32BusAddr & 0x1fffffff);
    }
	if ((0x60000000 <= u32BusAddr) && (0x70000000 > u32BusAddr))
    {
        return ((u32BusAddr & 0x0fffffff)+CONFIG_SYS_MIU_INTERVAL);
    }
	if ((0x70000000 <= u32BusAddr) && (0x80000000 > u32BusAddr))
    {
        return ((u32BusAddr & 0x1fffffff)+CONFIG_SYS_MIU_INTERVAL);
    }
    if ((0xE0000000 <= u32BusAddr) && (0xFFFFFFFF >= u32BusAddr)) //BA 0xE --> PA 0xC
    {
        return ((u32BusAddr & 0x1fffffff)+CONFIG_SYS_MIU2_INTERVAL);
    }
	return 0;
#endif
}

MS_U32 PA2BA(MS_U32 u32PhyAddr)
{
#if defined(__ARM__)

if (u32PhyAddr>=CONFIG_SYS_MIU2_INTERVAL) //PA 0xC --> BA 0xE
{
    return (u32PhyAddr + 0x20000000);
}
else
{
    return (u32PhyAddr + CONFIG_SYS_MIU0_BUS);
}

#else // MIPS
    if(u32PhyAddr>=CONFIG_SYS_MIU_INTERVAL)
    {
        return (u32PhyAddr - CONFIG_SYS_MIU_INTERVAL + CONFIG_SYS_MIU1_BUS);
    }
    else
    {
        return u32PhyAddr;        
    }
#endif
}

MIU_DDR_SIZE dram_size_to_enum(MS_U32 u32DramSize)
{
    switch(u32DramSize)
    {
        case 0x02000000:
            return E_MIU_DDR_32MB;
        case 0x04000000:
            return E_MIU_DDR_64MB;
        case 0x08000000:
            return E_MIU_DDR_128MB;
        case 0x10000000:
            return E_MIU_DDR_256MB;
        case 0x20000000:
            return E_MIU_DDR_512MB;
        case 0x40000000:
            return E_MIU_DDR_1024MB;
        case 0x80000000:
            return E_MIU_DDR_2048MB;
        default:
            printf("[PROTECT ERROR], not expected dram size: 0x%X\n", (unsigned int)u32DramSize);
            return -1;
    }
}

U8 MDrv_MIU_SetGroupPriority_UBoot(U8 bMIU1, U8 *au8GpPriority, U8 u8GpNum)
{
    u8 u8MIUGpPriority = 0, idx=0;
	U32 u32RegAddr = 0;
	UBOOT_TRACE("IN\n");
    
    if(bMIU1==0)
        {
            u32RegAddr =MIU0_REG_BASE+REG_MIU_GP_PRIORITY;
        }
        else if(bMIU1==1)
        {
            u32RegAddr =MIU1_REG_BASE+REG_MIU_GP_PRIORITY;
        }
        else if(bMIU1==2)
        {
            u32RegAddr =MIU2_REG_BASE+REG_MIU_GP_PRIORITY;
        }

    /*u8MIUGpPriority=u8MIUGpPriority;*/
    /*idx=idx;*/
	if (u8GpNum > MIU_MAX_GP_NUM)
	{
		UBOOT_ERROR("%s: exced max group number!\n", __FUNCTION__);
		return FALSE;
	}

    for (idx = 0; idx < MIU_MAX_GP_NUM; idx++)
    {
        if (au8GpPriority[idx] > (MIU_MAX_GP_NUM-1))
        {
            UBOOT_ERROR("%s: wrong group number!\n", __FUNCTION__);
            return FALSE;
        }
        u8MIUGpPriority |= (au8GpPriority[idx] << (idx*2));
    }
    //printf("Set MIU%u group priority:%x.....\n", bMIU1, u8MIUGpPriority);
    //A3 Revision 1 can not modify miu priority
    if(((volatile U16*)(PM_TOP_BASE))[CHIP_ID]== 0x47 && ((volatile U8*)(PM_TOP_BASE))[((CHIP_VER<<1)-(CHIP_VER&1))] <= 0x01)
        return TRUE;

	_MIU_WriteBytesBit(u32RegAddr,DISABLE, BIT8);
	_MIU_WriteByte(u32RegAddr, u8MIUGpPriority);
	_MIU_WriteBytesBit(u32RegAddr,ENABLE, BIT8);
	udelay(2);
	_MIU_WriteBytesBit(u32RegAddr,DISABLE, BIT8);
	UBOOT_TRACE("OK\n");

	return TRUE;
}

const U16 client_gp[7] = {REG_MIUSEL_GP0, REG_MIUSEL_GP1, REG_MIUSEL_GP2, REG_MIUSEL_GP3, REG_MIUSEL_GP4, REG_MIUSEL_GP5, 0};
U8 MDrv_MIU_SelectMIU_UBoot(U8 bMIU1, U16 *au16SelMiu, U8 u8GpNum)
{
	U8 idx;
	U32 u32RegAddr = 0;
    if(bMIU1==0)
    {
        u32RegAddr =MIU0_REG_BASE;
    }
    else if(bMIU1==1)
    {
        u32RegAddr =MIU1_REG_BASE;
    }
    else if(bMIU1==2)
    {
        u32RegAddr =MIU2_REG_BASE;
    }

	if (u8GpNum > MIU_MAX_GP_NUM)
	{
		UBOOT_ERROR("%s: exced max group number!\n", __FUNCTION__);
		return FALSE;
	}

    //printf("Change MIU%u select.....\n", bMIU1);
	for (idx = 0; idx < u8GpNum; idx++)
	{
	    //printf("Group%u:%-4x  ", idx, au16SelMiu[idx]);
		_MIU_Write2Bytes( ( u32RegAddr+client_gp[idx]), au16SelMiu[idx]);
    }
    //printf("\n");
    return TRUE;
}

void MsDrv_MiuInit(void)
{
		UBOOT_TRACE("IN\n");
		if(miuInit==0)
		{
				UBOOT_DEBUG("do MDrv_MIU_Init\n");
				MDrv_MIU_Init();
				miuInit=1;
		}
		UBOOT_TRACE("OK\n");
}
void MsDrv_kernelProtect(MS_U8  u8Blockx,MS_U32 u32Lx1Start, MS_U32 u32Lx1End)

{
	UBOOT_TRACE("IN\n");

    MS_U8 u8MIUProtectkernel_ID[16]={0};

    // ==== Linux kernel ID Protect
    UBOOT_DEBUG("Kernel Protect Index[%d] LX[0x%lx][0x%lx] \n",u8Blockx,u32Lx1Start,u32Lx1End);
#if ENABLE_NIKON  

    u8MIUProtectkernel_ID[0] = MIU_CLIENT_MIPS_RW; //MIPS W

    u8MIUProtectkernel_ID[1] = MIU_CLIENT_BDMA_RW;//MIU_CLIENT_NAND_RW;//MIU_CLIENT_BDMA_RW; //BDMA    

    u8MIUProtectkernel_ID[2] = MIU_CLIENT_USB_UHC0_RW; //USB0

    u8MIUProtectkernel_ID[3] = MIU_CLIENT_USB_UHC1_RW; //USB1

    u8MIUProtectkernel_ID[4] = MIU_CLIENT_USB_UHC2_RW; //USB2

    u8MIUProtectkernel_ID[5] = MIU_CLIENT_FCIE_RW;//MIU_CLIENT_G3D_RW; //G3D     

   // u8MIUProtectkernel_ID[6] = MIU_CLIENT_USB3_RW; //USB3.0      

   // u8MIUProtectkernel_ID[7] = MIU_CLIENT_SDIO_RW; //SD IO        

   // u8MIUProtectkernel_ID[8] = MIU_CLIENT_SATA_RW; //SATA       
#else
    u8MIUProtectkernel_ID[0] = MIU_CLIENT_MIPS_RW; //MIPS W

    u8MIUProtectkernel_ID[1] = MIU_CLIENT_NAND_RW;//MIU_CLIENT_BDMA_RW; //BDMA

    u8MIUProtectkernel_ID[2] = MIU_CLIENT_USB_UHC0_RW; //USB0

    u8MIUProtectkernel_ID[3] = MIU_CLIENT_USB_UHC1_RW; //USB1

    u8MIUProtectkernel_ID[4] = MIU_CLIENT_USB_UHC2_RW; //USB2

    u8MIUProtectkernel_ID[5] = MIU_CLIENT_G3D_RW; //G3D

    u8MIUProtectkernel_ID[6] = MIU_CLIENT_USB3_RW; //USB3.0

    u8MIUProtectkernel_ID[7] = MIU_CLIENT_SDIO_RW; //SD IO

    u8MIUProtectkernel_ID[8] = MIU_CLIENT_SATA_RW; //SATA

    u8MIUProtectkernel_ID[9] = MIU_CLIENT_USB_UHC3_RW; //USB3
# if(ENABLE_MSTAR_MONACO == 1 || ENABLE_MSTAR_MUJI == 1) || (ENABLE_MSTAR_CELTICS == 1)

    u8MIUProtectkernel_ID[10] = MIU_CLIENT_USB30_1_RW; //USB3
    u8MIUProtectkernel_ID[11] = MIU_CLIENT_USB30_2_RW; //USB3

# endif
#endif
    MsDrv_MIU_Protect(u8Blockx, &u8MIUProtectkernel_ID[0], u32Lx1Start, u32Lx1End, ENABLE);

	UBOOT_TRACE("OK\n");


}

void MsDrv_NuttxProtect(MS_U8  u8Blockx,MS_U32 u32NuttxStart, MS_U32 u32NuttxEnd)
{
	  UBOOT_TRACE("IN\n");

    MsDrv_MiuInit();

    MS_U8 u8MIUProtect_ID[16]={0};

    // ==== Linux kernel ID Protect
    UBOOT_DEBUG("Nuttx Protect Index[%d] start:[0x%lx],end:[0x%lx] \n",u8Blockx,u32NuttxStart,u32NuttxEnd);
    memset(u8MIUProtect_ID,0,sizeof(u8MIUProtect_ID));

    u8MIUProtect_ID[0] = MIU_CLIENT_SECURE_R2_RW; //MIPS W



    MsDrv_MIU_Protect(u8Blockx, &u8MIUProtect_ID[0], u32NuttxStart, u32NuttxEnd, ENABLE);

	  UBOOT_TRACE("OK\n");


}

void MsDrv_PMProtect(MS_U8  u8Blockx,MS_U32 u32Start, MS_U32 u32End)

{

	 UBOOT_TRACE("IN\n");

    MsDrv_MiuInit();

    MS_U8 u8MIUProtect_ID[16]={0};

    // ==== Linux kernel ID Protect
    UBOOT_DEBUG("PM Protect Index[%d] LX[0x%lx][0x%lx] \n",u8Blockx,u32Start,u32End);

    u8MIUProtect_ID[0] = MIU_CLIENT_PM51_RW; //PM RW

    MsDrv_MIU_Protect(u8Blockx, &u8MIUProtect_ID[0], u32Start, u32End, DISABLE);

    MsDrv_MIU_Protect(u8Blockx, &u8MIUProtect_ID[0], u32Start, u32End, ENABLE);

	UBOOT_TRACE("OK\n");


}

MS_BOOL MsDrv_MIU_Protect(MS_U8  u8Blockx, MS_U8  *pu8ProtectId, MS_U32 u32Start, MS_U32 u32End, MS_BOOL bSetFlag)

{
    MS_BOOL isProtect=FALSE;
    MS_U32 u32PageShift;
	UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("MsDrv_MIU_Protect Index[%d] LX[0x%lx][0x%lx] \n",u8Blockx,u32Start,u32End);

    if(!MDrv_MIU_ProtectAlign(&u32PageShift))
    {
        UBOOT_ERROR("ERROR MDrv_MIU_ProtectAlign FAIL \n");
    }

    isProtect=MDrv_MIU_Protect(u8Blockx, pu8ProtectId, MIU_ALIGN(u32Start, u32PageShift), MIU_ALIGN(u32End, u32PageShift), bSetFlag);
    
    if(!isProtect)
    {
        UBOOT_ERROR("ERROR MDrv_MIU_Protect FAIL \n");
    }

	UBOOT_TRACE("OK\n");

    return isProtect;

}


