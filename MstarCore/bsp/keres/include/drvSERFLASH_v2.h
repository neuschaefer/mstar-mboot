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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvBDMA_v2.h
/// @brief  MIU Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_SERFLASH_V2_H_
#define _DRV_SERFLASH_V2_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// below for utopia20 structure


typedef enum {
    MDrv_CMD_SERFLASH_GetInfo,
	MDrv_CMD_SERFLASH_GetLibVer,
    MDrv_CMD_SERFLASH_GetStatus,
    MDrv_CMD_SERFLASH_SetDbgLevel,
    MDrv_CMD_SERFLASH_SetWPInfo,
    MDrv_CMD_SERFLASH_SetMcuCSCallBack,
    MDrv_CMD_SERFLASH_SetFlashWPCallBack,
    MDrv_CMD_SERFLASH_DetectType,
    MDrv_CMD_SERFLASH_DetectSize,
    MDrv_CMD_SERFLASH_Set2XRead,
    MDrv_CMD_SERFLASH_SetCKG,
    MDrv_CMD_SERFLASH_ClkDiv,
    MDrv_CMD_SERFLASH_SetMode,
    MDrv_CMD_SERFLASH_ReadUID,
    MDrv_CMD_SERFLASH_ChipSelect,
    MDrv_CMD_SERFLASH_Init,
    MDrv_CMD_SERFLASH_ReadID,
    MDrv_CMD_SERFLASH_Read,
    MDrv_CMD_SERFLASH_EraseChip,
    MDrv_CMD_SERFLASH_AddressToBlock,
    MDrv_CMD_SERFLASH_BlockToAddress,
    MDrv_CMD_SERFLASH_AddressErase,
    MDrv_CMD_SERFLASH_BlockErase,
    MDrv_CMD_SERFLASH_SectorErase,
    MDrv_CMD_SERFLASH_CheckWriteDone,
    MDrv_CMD_SERFLASH_Write,
    MDrv_CMD_SERFLASH_DMA,
    MDrv_CMD_SERFLASH_WriteProtect,
    MDrv_CMD_SERFLASH_WriteProtect_Enable_All_Range,
    MDrv_CMD_SERFLASH_WriteProtect_Disable_All_Range,
    MDrv_CMD_SERFLASH_WriteProtect_Disable_Range_Set,
    MDrv_CMD_SERFLASH_WriteProtect_Area,
    MDrv_CMD_SERFLASH_ReadStatusRegister,
    MDrv_CMD_SERFLASH_ReadStatusRegister2,
    MDrv_CMD_SERFLASH_WriteStatusRegister,
    MDrv_CMD_SERFLASH_CopyHnd,
    MDrv_CMD_SERFLASH_SetGPIO,
} eSerflashIoctlOpt;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------

typedef struct _SERFLASH_READID
{
    MS_U8 *pu8FlashID;
    MS_U32 u32IDSize;
}SERFLASH_READID, *PSERFLASH_READID;

typedef struct _SERFLASH_READ
{
    MS_U32 u32FlashAddr;
    MS_U32 u32FlashSize;
    MS_U8 *user_buffer;
}SERFLASH_READ, *PSERFLASH_READ;

typedef struct _SERFLASH_ADDRTOBLK
{
    MS_U32 u32FlashAddr;
    MS_U32 *pu32BlockIndex;
}SERFLASH_ADDRTOBLK, *PSERFLASH_ADDRTOBLK;

typedef struct _SERFLASH_BLKTOADDR
{
    MS_U32 u32BlockIndex;
    MS_U32 *pu32FlashAddr;
}SERFLASH_BLKTOADDR, *PSERFLASH_BLKTOADDR;

typedef struct _SERFLASH_ADDRERASE
{
    MS_U32 u32StartAddr;
    MS_U32 u32EraseSize;
    MS_BOOL bWait;
}SERFLASH_ADDRERASE, *PSERFLASH_ADDRERASE;

typedef struct _SERFLASH_BLKERASE
{
    MS_U32 u32StartBlock;
    MS_U32 u32EndBlock;
    MS_BOOL bWait;
}SERFLASH_BLKERASE, *PSERFLASH_BLKERASE;

typedef struct _SERFLASH_SECERASE
{
    MS_U32 u32StartAddr;
    MS_U32 u32EndAddr;
}SERFLASH_SECERASE, *PSERFLASH_SECERASE;

typedef struct _SERFLASH_WRITE
{
    MS_U32 u32FlashAddr;
    MS_U32 u32FlashSize;
    MS_U8 *user_buffer;
}SERFLASH_WRITE, *PSERFLASH_WRITE;

typedef struct _SERFLASH_DMA
{
    MS_U32 u32FlashStart;
    MS_U32 u32DRAMStart;
    MS_U32 u32Size;
}SERFLASH_DMA, *PSERFLASH_DMA;

typedef struct _SERFLASH_WP
{
    MS_BOOL bEnable;
}SERFLASH_WP, *PSERFLASH_WP;

typedef struct _SERFLASH_WPDISABLERANGESET
{
    MS_U32 u32DisableLowerBound;
    MS_U32 u32DisableSize;
}SERFLASH_WPDISABLERANGESET, *PSERFLASH_WPDISABLERANGESET;

typedef struct _SERFLASH_WPAREA
{
    MS_BOOL bEnableAllArea;
    MS_U8 u8BlockProtectBits;
}SERFLASH_WPAREA, *PSERFLASH_WPAREA;

typedef struct _SERFLASH_COPYHND
{
    MS_PHYADDR u32FlashAddr;
    MS_PHYADDR u32DstAddr;
    MS_U32 u32Len;
    SPIDMA_Dev eDstDev;
    MS_U8 u8OpCfg;
}SERFLASH_COPYHND, *PSERFLASH_COPYHND;

typedef struct _SERFLASH_GETSTATUS
{
    SERFLASH_DrvStatus* pDrvStatus;
}SERFLASH_GETSTATUS, *PSERFLASH_GETSTATUS;

typedef struct _SERFLASH_GETLIBVER
{
    const MSIF_Version **ppVersion;
}SERFLASH_GETLIBVER, *PSERFLASH_GETLIBVER;

typedef struct _SERFLASH_SETDBGLEVEL
{
    MS_U8 u8DbgLevel;
}SERFLASH_SETDBGLEVEL, *PSERFLASH_SETDBGLEVEL;

typedef struct _SERFLASH_SETWPINFO
{
    MS_BOOL bWPInfo;
}SERFLASH_SETWPINFO, *PSERFLASH_SETWPINFO;

typedef struct _SERFLASH_SETMCUCSCB
{
    ms_Mcu_ChipSelect_CB ChipSel_cb;
}SERFLASH_SETMCUCSCB, *PSERFLASH_SETMCUCSCB;

typedef struct _SERFLASH_SETFLASHWPCB
{
    ms_Flash_SetHWWP_CB FlashWP_cb;
}SERFLASH_SETFLASHWPCB, *PSERFLASH_SETFLASHWPCB;

typedef struct _SERFLASH_DETECTSIZE
{
    MS_U32 *u32FlashSize;
}SERFLASH_DETECTSIZE, *PSERFLASH_DETECTSIZE;

typedef struct _SERFLASH_SET2XREAD
{
    MS_BOOL b2XMode;
}SERFLASH_SET2XREAD, *PSERFLASH_SET2XREAD;

typedef struct _SERFLASH_SETCKG
{
    SPI_DrvCKG eCKGspi;
}SERFLASH_SETCKG, *PSERFLASH_SETCKG;

typedef struct _SERFLASH_CLKDIV
{
    SPI_DrvClkDiv eClkDivspi;
}SERFLASH_CLKDIV, *PSERFLASH_CLKDIV;

typedef struct _SERFLASH_SETMODE
{
    MS_BOOL bXiuRiu;
}SERFLASH_SETMODE, *PSERFLASH_SETMODE;

typedef struct _SERFLASH_CHIPSELECT
{
    MS_U8 u8FlashIndex;
}SERFLASH_CHIPSELECT, *PSERFLASH_CHIPSELECT;

typedef struct _SERFLASH_READSTATUSREG
{
    MS_U8 *pu8StatusReg;
}SERFLASH_READSTATUSREG, *PSERFLASH_READSTATUSREG;

typedef struct _SERFLASH_READSTATUSREG2
{
    MS_U8 *pu8StatusReg;
}SERFLASH_READSTATUSREG2, *PSERFLASH_READSTATUSREG2;

typedef struct _SERFLASH_WRITESTATUSREG
{
    MS_U16 u16StatusReg;
}SERFLASH_WRITESTATUSREG, *PSERFLASH_WRITESTATUSREG;

typedef struct _SERFLASH_SETGPIO
{
    MS_BOOL bSwitch;
}SERFLASH_SETGPIO, *PSERFLASH_SETGPIO;

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif // _DRV_SERFLASH_V2_H_

