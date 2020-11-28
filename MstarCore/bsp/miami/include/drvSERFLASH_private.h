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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVSERFLASH_PRIV_H_
#define _DRVSERFLASH_PRIV_H_

////////////////////////////////////////////////////////////////////////////////
/// @file drvBDMA.h
/// @author MStar Semiconductor Inc.
/// @brief Byte DMA control driver
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#include "MsTypes.h"
#include "drvSERFLASH.h"


typedef const SERFLASH_Info* (*IOCTL_SERFLASH_GetInfo)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_GetLibVer)(const MSIF_Version**);
typedef MS_BOOL (*IOCTL_SERFLASH_GetStatus)(SERFLASH_DrvStatus*);
typedef MS_BOOL (*IOCTL_SERFLASH_SetDbgLevel)(MS_U8);
typedef MS_BOOL (*IOCTL_SERFLASH_SetWPInfo)(MS_BOOL);
typedef void (*IOCTL_SERFLASH_SetMcuCSCallBack)(ms_Mcu_ChipSelect_CB);
typedef void (*IOCTL_SERFLASH_SetFlashWPCallBack)(ms_Flash_SetHWWP_CB);
typedef MS_BOOL (*IOCTL_SERFLASH_DetectType)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_DetectSize)(MS_U32*);
typedef MS_BOOL (*IOCTL_SERFLASH_Set2XRead)(MS_BOOL);
typedef MS_BOOL (*IOCTL_SERFLASH_SetCKG)(SPI_DrvCKG);
typedef void (*IOCTL_SERFLASH_ClkDiv)(SPI_DrvClkDiv);
typedef MS_BOOL (*IOCTL_SERFLASH_SetMode)(MS_BOOL);
typedef MS_U64 (*IOCTL_SERFLASH_ReadUID)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_ChipSelect)(MS_U8);
typedef void (*IOCTL_SERFLASH_Init)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_ReadID)(MS_U8*, MS_U32);
typedef MS_BOOL (*IOCTL_SERFLASH_Read)(MS_U32, MS_U32, MS_U8*);
typedef MS_BOOL (*IOCTL_SERFLASH_EraseChip)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_AddressToBlock)(MS_U32, MS_U32*);
typedef MS_BOOL (*IOCTL_SERFLASH_BlockToAddress)(MS_U32, MS_U32*);
typedef MS_BOOL (*IOCTL_SERFLASH_AddressErase)(MS_U32, MS_U32, MS_BOOL);
typedef MS_BOOL (*IOCTL_SERFLASH_BlockErase)(MS_U32, MS_U32, MS_BOOL);
typedef MS_BOOL (*IOCTL_SERFLASH_SectorErase)(MS_U32, MS_U32);
typedef MS_BOOL (*IOCTL_SERFLASH_CheckWriteDone)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_Write)(MS_U32, MS_U32, MS_U8*);
typedef MS_BOOL (*IOCTL_SERFLASH_DMA)(MS_U32, MS_U32, MS_U32);
typedef MS_BOOL (*IOCTL_SERFLASH_WriteProtect)(MS_BOOL);
typedef MS_BOOL (*IOCTL_SERFLASH_WriteProtect_Enable_All_Range)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_WriteProtect_Disable_All_Range)(void);
typedef MS_BOOL (*IOCTL_SERFLASH_WriteProtect_Disable_Range_Set)(MS_U32, MS_U32);
typedef MS_BOOL (*IOCTL_SERFLASH_WriteProtect_Area)(MS_BOOL, MS_U8);
typedef MS_BOOL (*IOCTL_SERFLASH_ReadStatusRegister)(MS_U8*);
typedef MS_BOOL (*IOCTL_SERFLASH_ReadStatusRegister2)(MS_U8*);
typedef MS_BOOL (*IOCTL_SERFLASH_WriteStatusRegister)(MS_U16);
typedef MS_BOOL (*IOCTL_SERFLASH_CopyHnd)(MS_PHYADDR, MS_PHYADDR, MS_U32, SPIDMA_Dev, MS_U8);
typedef void (*IOCTL_SERFLASH_SetGPIO)(MS_BOOL);


typedef struct _SERFLASH_RESOURCE_PRIVATE
{
    MS_U32 Dummy;
}SERFLASH_RESOURCE_PRIVATE;

typedef struct _SERFLASH_INSTANT_PRIVATE
{
    IOCTL_SERFLASH_GetInfo                              fpSERFLASHGetInfo;
    IOCTL_SERFLASH_GetLibVer                            fpSERFLASHGetLibVer;
    IOCTL_SERFLASH_GetStatus                            fpSERFLASHGetStatus;
    IOCTL_SERFLASH_SetDbgLevel                          fpSERFLASHSetDbgLevel;
    IOCTL_SERFLASH_SetWPInfo                            fpSERFLASHSetWPInfo;
    IOCTL_SERFLASH_SetMcuCSCallBack                     fpSERFLASHSetMcuCSCallBack;
    IOCTL_SERFLASH_SetFlashWPCallBack                   fpSERFLASHSetFlashWPCallBack;
    IOCTL_SERFLASH_DetectType                           fpSERFLASHDetectType;
    IOCTL_SERFLASH_DetectSize                           fpSERFLASHDetectSize;
    IOCTL_SERFLASH_Set2XRead                            fpSERFLASHSet2XRead;
    IOCTL_SERFLASH_SetCKG                               fpSERFLASHSetCKG;
    IOCTL_SERFLASH_ClkDiv                               fpSERFLASHClkDiv;
    IOCTL_SERFLASH_SetMode                              fpSERFLASHSetMode;
    IOCTL_SERFLASH_ReadUID                              fpSERFLASHReadUID;
    IOCTL_SERFLASH_ChipSelect                           fpSERFLASHChipSelect;
    IOCTL_SERFLASH_Init                                 fpSERFLASHInit;
    IOCTL_SERFLASH_ReadID                               fpSERFLASHReadID;
    IOCTL_SERFLASH_Read                                 fpSERFLASHRead;
    IOCTL_SERFLASH_EraseChip                            fpSERFLASHEraseChip;
    IOCTL_SERFLASH_AddressToBlock                       fpSERFLASHAddressToBlock;
    IOCTL_SERFLASH_BlockToAddress                       fpSERFLASHBlockToAddress;
    IOCTL_SERFLASH_AddressErase                         fpSERFLASHAddressErase;
    IOCTL_SERFLASH_BlockErase                           fpSERFLASHBlockErase;
    IOCTL_SERFLASH_SectorErase                          fpSERFLASHSectorErase;
    IOCTL_SERFLASH_CheckWriteDone                       fpSERFLASHCheckWriteDone;
    IOCTL_SERFLASH_Write                                fpSERFLASHWrite;
    IOCTL_SERFLASH_DMA                                  fpSERFLASHDMA;
    IOCTL_SERFLASH_WriteProtect                         fpSERFLASHWriteProtect;
    IOCTL_SERFLASH_WriteProtect_Enable_All_Range        fpSERFLASHWriteProtectEnableAllRange;
    IOCTL_SERFLASH_WriteProtect_Disable_All_Range       fpSERFLASHWriteProtectDisableAllRange;
    IOCTL_SERFLASH_WriteProtect_Disable_Range_Set       fpSERFLASHWriteProtectDisableRangeSet;
    IOCTL_SERFLASH_WriteProtect_Area                    fpSERFLASHWriteProtectArea;
    IOCTL_SERFLASH_ReadStatusRegister                   fpSERFLASHReadStatusRegister;
    IOCTL_SERFLASH_ReadStatusRegister2                  fpSERFLASHReadStatusRegister2;
    IOCTL_SERFLASH_WriteStatusRegister                  fpSERFLASHWriteStatusRegister;
    IOCTL_SERFLASH_CopyHnd                              fpSERFLASHCopyHnd;
    IOCTL_SERFLASH_SetGPIO                              fpSERFLASHSetGPIO;
}SERFLASH_INSTANT_PRIVATE;

void FLASHRegisterToUtopia(FUtopiaOpen ModuleType);
MS_U32 FLASHOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
MS_U32 FLASHClose(void* pInstance);
MS_U32 FLASHIoctl(void* pInstance, MS_U32 u32Cmd, void* pArgs);
#if (SERFLASH_UTOPIA20)
//------------------------------------------------------------------------------
/// Description : Set detailed level of Parallel Flash driver debug message
/// @param u8DbgLevel    \b IN  debug level for Serial Flash driver
/// @return TRUE : succeed
/// @return FALSE : failed to set the debug level
//------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_SetDbgLevel(MS_U8 u8DbgLevel);

//------------------------------------------------------------------------------
/// Description : Set WP pin info to driver
/// @param bWPInfo
/// @return TRUE : succeed
/// @return FALSE : failed to set the WP pin info
//------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_SetWPInfo(MS_BOOL bWPInfo);

//------------------------------------------------------------------------------
/// Description : HK ask 8051 to select flash chip by call back function
/// @param ms_Mcu_ChipSelect_CB    \b IN  call back function
/// @return TRUE : succeed
/// @return NULL :
//------------------------------------------------------------------------------
void _MDrv_SERFLASH_SetMcuCSCallBack(ms_Mcu_ChipSelect_CB ChipSel_cb);

void _MDrv_SERFLASH_SetFlashWPCallBack(ms_Flash_SetHWWP_CB FlashWP_cb);

//-------------------------------------------------------------------------------------------------
/// Description : Detect flash type by reading the MID and DID
/// @return TRUE : succeed
/// @return FALSE : unknown flash type
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_DetectType(void);

//-------------------------------------------------------------------------------------------------
/// Description : Detect flash Size
/// @param  u32FlashSize    \b OUT: u32 ptr to store flash size
/// @return TRUE : succeed
/// @return FALSE : unknown flash size
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_DetectSize(MS_U32 *u32FlashSize);

//-------------------------------------------------------------------------------------------------
/// Description : Enable Flash 2XREAD mode, if support
/// @param  b2XMode    \b IN: ENABLE/DISABLE
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   Please ref. sprc. to confirm Flash support or not
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_Set2XRead(MS_BOOL b2XMode);

//-------------------------------------------------------------------------------------------------
/// Description : Set ckg_spi which flash supports (please ref. the spec. before using this function)
/// @param  SPI_DrvCKG    \b IN: enumerate the ckg_spi
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   Please ref. sprc. to confirm Flash support or not. It is safty to run at 43M (Default).
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_SetCKG(SPI_DrvCKG eCKGspi);

//-------------------------------------------------------------------------------------------------
/// Description : Set clock div such that spi clock = mcu clock /clock_div.
/// @param  SPI_DrvClkDiv    \b IN: enumerate the clock_div
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note
//-------------------------------------------------------------------------------------------------
void _MDrv_SERFLASH_ClkDiv(SPI_DrvClkDiv eClkDivspi);

//-------------------------------------------------------------------------------------------------
/// Description : Set XIU/RIU mode (Default : XIU)
/// @param  bXiuRiu    \b IN: 1 for XIU, 0 for RIU
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   XIU mode is faster than RIU mode. It is stable to run by XIU (Default)
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_SetMode(MS_BOOL bXiuRiu);

//-------------------------------------------------------------------------------------------------
/// Description :  Set active flash among multi-spi flashes
/// @param  u8FlashIndex    \b IN: The Flash index, 0 for external #1 spi flash, 1 for external #2 spi flash
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   For Secure booting = 0, please check hw_strapping or e-fuse (the board needs to jump)
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_ChipSelect(MS_U8 u8FlashIndex);

//-------------------------------------------------------------------------------------------------
/// Description : Erase all sectors in Serial Flash
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_EraseChip(void);

//-------------------------------------------------------------------------------------------------
/// Description : Get flash start block index of a flash address
/// @param  u32FlashAddr    \b IN: flash address
/// @param  pu32BlockIndex    \b IN: poniter to store the returning block index
/// @return TRUE : succeed
/// @return FALSE : illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_AddressToBlock(MS_U32 u32FlashAddr, MS_U32 *pu32BlockIndex);

//-------------------------------------------------------------------------------------------------
/// Description : Get flash start address of a block index
/// @param  u32BlockIndex    \b IN: block index
/// @param  pu32FlashAddr    \b IN: pointer to store the returning flash address
/// @return TRUE : succeed
/// @return FALSE : illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_BlockToAddress(MS_U32 u32BlockIndex, MS_U32 *pu32FlashAddr);

//-------------------------------------------------------------------------------------------------
/// Description : Get Unique ID
/// @param  None
/// @return the SPI Flash's Unique ID
//-------------------------------------------------------------------------------------------------
MS_U64 _MDrv_SERFLASH_ReadUID(void);

//-------------------------------------------------------------------------------------------------
/// Description : Erase certain sectors given starting address and size in Serial Flash
/// @param  u32StartAddr    \b IN: start address at block boundry
/// @param  u32EraseSize    \b IN: size to erase
/// @param  bWait    \b IN: wait write done or not
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_AddressErase(MS_U32 u32StartAddr, MS_U32 u32EraseSize, MS_BOOL bWait);

//-------------------------------------------------------------------------------------------------
/// Description : Erase certain sectors in Serial Flash
/// @param  u32StartBlock    \b IN: start block
/// @param  u32EndBlock    \b IN: end block
/// @param  bWait    \b IN: wait write done or not
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_BlockErase(MS_U32 u32StartBlock, MS_U32 u32EndBlock, MS_BOOL bWait);

//-------------------------------------------------------------------------------------------------
/// Description : Erase certain 4K sectors in Serial Flash
/// @param  u32StartBlock    \b IN: start address
/// @param  u32EndBlock    \b IN: end address
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_SectorErase(MS_U32 u32StartAddr, MS_U32 u32EndAddr);

//-------------------------------------------------------------------------------------------------
/// Description : Check write done in Serial Flash
/// @return TRUE : done
/// @return FALSE : not done
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_CheckWriteDone(void);

//-------------------------------------------------------------------------------------------------
/// Description : Write data to Serial Flash
/// @param  u32FlashAddr    \b IN: start address (4-B aligned)
/// @param  u32FlashSize    \b IN: size in Bytes (4-B aligned)
/// @param  user_buffer    \b IN: Virtual Buffer Address ptr to flash write data
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_Write(MS_U32 u32FlashAddr, MS_U32 u32FlashSize, MS_U8 *user_buffer);

//-------------------------------------------------------------------------------------------------
/// Description : Read data from Serial Flash
/// @param  u32FlashAddr    \b IN: Flash Address
/// @param  u32FlashSize    \b IN: Flash Size Data in Bytes
/// @param  user_buffer    \b OUT: Virtual Buffer Address ptr to store flash read data
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_Read(MS_U32 u32FlashAddr, MS_U32 u32FlashSize, MS_U8 *user_buffer);

//-------------------------------------------------------------------------------------------------
/// Description : Protect blocks in Serial Flash
/// @param  bEnable    \b IN: TRUE/FALSE: enable/disable protection
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
/// @note
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_WriteProtect(MS_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// Description : Enables all range of flash write protection
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_WriteProtect_Enable_All_Range(void);

//-------------------------------------------------------------------------------------------------
/// Description : Disables all range of flash write protection
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_WriteProtect_Disable_All_Range(void);

//-------------------------------------------------------------------------------------------------
/// Description : Set flash disable lower bound and size
/// @param  u32DisableLowerBound    \b IN: the lower bound to disable write protect
/// @param  u32DisableSize    \b IN: size to disable write protect
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_WriteProtect_Disable_Range_Set(MS_U32 u32DisableLowerBound, MS_U32 u32DisableSize);

//-------------------------------------------------------------------------------------------------
/// Description : Protect blocks in Serial Flash
/// @param  bEnableAllArea    \b IN: enable or disable protection
/// @param  u8BlockProtectBits    \b IN: block protection bits which stand for the area to enable write protect
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_WriteProtect_Area(MS_BOOL bEnableAllArea, MS_U8 u8BlockProtectBits);

//-------------------------------------------------------------------------------------------------
/// Description : Read ID from Serial Flash
/// @param  pu8FlashID    \b OUT: Virtual data ptr to store the read ID
/// @param  u32IDSize    \b IN: size in Bytes
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
/// @note
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_ReadID(MS_U8 *pu8FlashID, MS_U32 u32IDSize);

//-------------------------------------------------------------------------------------------------
/// Description : Read data from Serial Flash to DRAM in DMA mode
/// @param  u32FlashStart    \b IN: src start address in flash (0 ~ flash size-1)
/// @param  u32DRAMStart    \b IN: dst start address in DRAM (16B-aligned) (0 ~ DRAM size-1)
/// @param  u32Size    \b IN: size in Bytes (8B-aligned) (>=8)
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
/// @note
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_DMA(MS_U32 u32FlashStart, MS_U32 u32DRAMStart, MS_U32 u32Size);

//------- ------------------------------------------------------------------------------------------
/// Description : Read Status Register in Serial Flash
/// @param  pu8StatusReg    \b OUT: ptr to Status Register value
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
/// @note
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_ReadStatusRegister(MS_U8 *pu8StatusReg);

//------- ------------------------------------------------------------------------------------------
/// Description : Read Status Register2 in Serial Flash
/// @param  pu8StatusReg    \b OUT: ptr to Status Register value
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
/// @note   For Specific Flash IC with 16-bit status register (high-byte)
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_ReadStatusRegister2(MS_U8 *pu8StatusReg);

//------- ------------------------------------------------------------------------------------------
/// Description : Write Status Register in Serial Flash
/// @param  u16StatusReg    \b IN: Status Register value
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
/// @note   For Specific Flash IC with 16-bit status register
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_WriteStatusRegister(MS_U16 u16StatusReg);

//------- ------------------------------------------------------------------------------------------
/// Description : Handle for BDMA copy data from ONLY Flash src to other dst
/// @param u32FlashAddr \b IN: Physical Source address in spi flash
/// @param u32DramAddr \b IN: Physical Dst address
/// @param u32Len \b IN: data length
/// @param eDstDev \b IN: The Dst Device of Flash BDMA
/// @param u8OpCfg \b IN: u8OpCfg: default is SPIDMA_OPCFG_DEF
/// - Bit0: inverse mode --> SPIDMA_OPCFG_INV_COPY
/// - Bit2: Copy & CRC check in wait mode --> SPIDMA_OPCFG_CRC_COPY
/// - Bit3: Copy without waiting --> SPIDMA_OPCFG_NOWAIT_COPY
/// @return \b MS_BOOL
/// [NONOS_SUPPORT]
/// [fw : drvBDMA ]
//-------------------------------------------------------------------------------------------------
MS_BOOL _MDrv_SERFLASH_CopyHnd(MS_PHYADDR u32FlashAddr,
                                          MS_PHYADDR u32DstAddr,
                                          MS_U32 u32Len,
                                          SPIDMA_Dev eDstDev,
                                          MS_U8 u8OpCfg);

//------- ------------------------------------------------------------------------------------------
/// Description : Switch SPI as GPIO Input
/// @param  bSwitch    \b IN: 1 for GPIO, 0 for NORMAL
/// @note   Not allowed in interrupt context
/// @note   For project's power consumption
/// [NONOS_SUPPORT]
//-------------------------------------------------------------------------------------------------
void _MDrv_SERFLASH_SetGPIO(MS_BOOL bSwitch);

#endif

#ifdef __cplusplus
}
#endif
#endif // _DRVBDMA_PRIV_H_
