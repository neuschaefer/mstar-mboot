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

#ifndef __CMD_MS_SYSTEM__
#define __CMD_MS_SYSTEM__
#include <MsOS.h>

#if defined(__ARM__)   
#define SPI_FLAS_BASE_ADDRESS 0x14000000
#else
#define SPI_FLAS_BASE_ADDRESS 0xBFC00000
#endif

typedef enum 
{
    //this valuse is offset in chunk header.
    CH_ITEM_FIRST=0x00,
    CH_UBOOT_ROM_START=CH_ITEM_FIRST,
    CH_UBOOT_RAM_START,//0x04
    CH_UBOOT_RAM_END,//0x08
    CH_UBOOT_ROM_END,//0x0c
    CH_UBOOT_RAM_ENTRY,//0x10
    RESERVED1,//0x14,Reserved1
    RESERVED2,//0x18,Reserved2
    CH_BINARY_ID,//0x1c   
    CH_LOGO_ROM_OFFSET,//0x20
    CH_LOGO_ROM_SIZE,//0x24
    CH_SBOOT_ROM_OFFSET,//0x28
    CH_SBOOT_SIZE,//0x2c
    CH_SBOOT_RAM_OFFSET,//0x30
    CH_PM_ROM_OFFSET,//0x34
    CH_PM_SIZE,//0x38
    CH_PM_RAM_OFFSET,//0x3c
    CH_SECURITY_INFO_LOADER_ROM_OFFSET,//0x40
    CH_SECURITY_INFO_LOADER_SIZE,//0x44
    CH_SECURITY_INFO_LOADER_RAM_OFFSET,//0x48
    CH_CUSTOMER_KEY_BANK_ROM_OFFSET,//0x4c
    CH_CUSTOMER_KEY_BANK_SIZE,//0x50
    CH_CUSTOMER_KEY_BANK_RAM_OFFSET,//0x54
    CH_SECURITY_INFO_AP_ROM_OFFSET,//0x58
    CH_SECURITY_INFO_AP_SIZE,//0x5C    
    CH_UBOOT_ENVIRONMENT_ROM_OFFSET,//0x60
    CH_UBOOT_ENVIRONMENT_SIZE,//0x64
    CH_DDR_BACKUP_TABLE_ROM_OFFSET,//0x68  
    CH_POWER_SEQUENCE_TABLE_ROM_OFFSET,//0x6c
    CH_UBOOT_POOL_ROM_OFFSET,//0x70
    CH_UBOOT_POOL_SIZE,//0x74
    CH_CLEANBOOT_ROM_OFFSET,//0x78
    CH_CLEANBOOT_SIZE,//0x7c
    CH_RT_AEON_ROM_OFFSET,//0x80
    CH_RT_AEON_SIZE,//0x84
    CH_NUTTX_CONFIG_OFFSET,//0x88
    CH_NUTTX_CONFIG_SIZE,//0x8c
    CH_MBOOT_CONFIG_BINARY_OFFSET, //0x90
    CH_MBOOT_CONFIG_BINARY_SIZE, //0x94
    CH_RESCURE_ENVIRONMENT_ROM_OFFSET,//0x98
    CH_RESCURE_ENVIRONMENT_SIZE,//0x9c
    CH_RESCURE_STATUS_ROM_OFFSET,//0xa0
    CH_RESCURE_STATUS_SIZE,//0xa4
    CH_ITEM_LAST=CH_RESCURE_STATUS_SIZE
} EN_CHUNK_HEADER_ITEM;

#if (ENABLE_MSTAR_PUMABOOT)
///List all mailbox command index
typedef enum
{
    E_MBX_PB_CMD_NONE=0x00,
    E_MBX_PB_CMD_DBCHAN,
    E_MBX_PB_CMD_DBUSER,
    E_MBX_PB_CMD_PANEL,
    E_MBX_PB_CMD_INPUT,
    E_MBX_PB_CMD_MMAP,
    E_MBX_PB_CMD_TUNEATV, //may be removed later
    E_MBX_PB_CMD_GROUP,
    E_MBX_PB_CMD_BVIDEO,
    E_MBX_PB_CMD_MAX
}EN_MBX_PBCMDIDX;

///List all input sources
typedef enum
{
    E_MBX_PB_INPUT_NONE=0x00,
    E_MBX_PB_INPUT_DTV,
    E_MBX_PB_INPUT_ATV,
    E_MBX_PB_INPUT_VGA,
    E_MBX_PB_INPUT_COMP,
    E_MBX_PB_INPUT_AV,
    E_MBX_PB_INPUT_SV,
    E_MBX_PB_INPUT_SCART,
    E_MBX_PB_INPUT_HDMI,
    E_MBX_PB_INPUT_MAX
}EN_MBX_PBINPUTIDX;

///List different output port for the same input source type
typedef enum
{
    E_MBX_PB_OUT_NONE=0x00,
    E_MBX_PB_OUT_1,
    E_MBX_PB_OUT_2,
    E_MBX_PB_OUT_3,
    E_MBX_PB_OUT_4,
    E_MBX_PB_OUT_MAX
}EN_MBX_PBOUTIDX;

typedef struct
{
    MS_U16 u16RFChaNum;
    MS_U16 u16VirChaNum;
    MS_U16 u16VideoPid;
    MS_U16 u16AudioPid;
    MS_U16 u16PCRPid;
    //MS_U8* pu8ChanName;
} PBChanDB;

// This section shuould sync with code in Pumaboot
typedef struct
{
    MS_U32 u32Address;     // offset of section physical address
    MS_U32 u32Length;      // length of section
} MMAP_INFO;

// Memory offset used by Pumaboot, this section shuould sync with code in Pumaboot
typedef struct
{
    MMAP_INFO MAD_R2_BUFFER;
    MMAP_INFO MAD_SE_BUFFER;
    MMAP_INFO MAD_DEC_BUFFER;
    MMAP_INFO VDEC_AEON;
    MMAP_INFO VDEC_FRAMEBUFFER;
    MMAP_INFO VDEC_BITSTREAM;
    MMAP_INFO SCALER_DNR;
    MMAP_INFO MENULOAD_BUFFER;
} MMAP_PUMABOOT_ADDRESS_LAYOUT;

#endif

#define VA2PA(addr) MS_VA2PA(addr)

#define PA2NVA(noncache_addr) MS_PA2KSEG1(noncache_addr)

#define PA2VA(cache_addr) MS_PA2KSEG0(cache_addr)

int MsApiChunkHeader_Init(void);
int MsApiChunkHeader_GetValue(EN_CHUNK_HEADER_ITEM item, unsigned int *puValue);

int do_wdt_enable (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_set_miu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_disable_uart ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int do_BrickTerminator_Main (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

void console_init(void);
void console_disable(void);

//-------------------------------------------------------------------------------------------------    
/// Query whether or not current booting mode is house keeping booting mode
/// @return  int                              \b OUT: TURE: Housekeeping booting , FALSE: Not Housekeeping booting
//-------------------------------------------------------------------------------------------------
MS_BOOL IsHouseKeepingBootingMode(void);

//-------------------------------------------------------------------------------------------------    
/// Query if system is configures as booting from mask rom
/// @return  int                              \b OUT: TURE: booting from mask rom , FALSE: Doesn't boot from mask rom
//-------------------------------------------------------------------------------------------------
MS_BOOL IsBootingFromMaskRom(void);

//-------------------------------------------------------------------------------------------------    
/// Do mailbox initializtion 
/// @return  int                              \b OUT: TURE: successfully , FALSE: fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MsApi_MBX_Init(void);

//-------------------------------------------------------------------------------------------------    
/// Do system reset
//-------------------------------------------------------------------------------------------------
void MsSystemReset(void);

//-------------------------------------------------------------------------------------------------    
/// Get boot time in ms
/// @return  unsigned long                         \b OUT: Tick
//-------------------------------------------------------------------------------------------------
unsigned long MsSystemGetBootTime(void);

#if CONFIG_RESCUE_ENV  && CONFIG_RESCUE_ENV_IR_TRIGGER
#define BRICK_TERMINATOR_IR_TRIGGERED_STRING "BRICK_TERMINATOR_IR_TRIGGERED"
#endif

#if (ENABLE_MSTAR_PUMABOOT)
MS_U32 MSys_GetBootTimeMs(void);
MS_U16 MSys_Read2Byte(MS_U32 u32Reg);
#endif

#endif

