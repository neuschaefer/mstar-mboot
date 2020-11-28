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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mmap_32mb.h
/// @brief  Memory mapping for 32MB RAM
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////
//#include <linux/undefconf.h>
//#include "../../../../../include/linux/undefconf.h"
#ifndef _MS_MMAP_32MB_H_
#define _MS_MMAP_32MB_H_

// Memory alignment
#define MemAlignUnit                64UL
#define MemAlign(n, unit)           ((((n)+(unit)-1)/(unit))*(unit))

#define MIU_DRAM_LEN                    0x2000000                       // 32M

//----------------------------------------------------------------------
// 32M
//----------------------------------------------------------------------
#if 0 // for example usage
// Aeon code start address, need DRAM start address
#define AEON_MEM_AVAILABLE          0x00000000UL
#define AEON_MEM_BASE_ADR           (AEON_MEM_AVAILABLE)
#define AEON_MEM_GAP_CHK            (AEON_MEM_BASE_ADR-AEON_MEM_AVAILABLE)
#define AEON_MEM_LEN                0x300000                        // 3MB

// need 64k align - need to be within 4MB
#define SECBUF_START_AVAILABLE      (AEON_MEM_BASE_ADR + AEON_MEM_LEN)
#define SECBUF_START_ADR            MemAlign(SECBUF_START_AVAILABLE, 0x10000)
#define SECBUF_START_ADR_GAP_CHK    (SECBUF_START_ADR - SECBUF_START_AVAILABLE)
#define SECBUF_LEN                  0x23000                         // 140K
#endif

#if 0
#define EMAC_MEM_LEN                0x100000
#define EMAC_MEM_ADR                0x00200000UL

#define NULL_MEM_LEN                0x100000
// Linux kernel space
#define LINUX_MEM_AVAILABLE			(EMAC_MEM_ADR+EMAC_MEM_LEN+NULL_MEM_LEN)
#define LINUX_MEM_BASE_ADR 			(LINUX_MEM_AVAILABLE)
#define LINUX_MEM_GAP_CHK  			(LINUX_MEM_BASE_ADR-LINUX_MEM_AVAILABLE)
#define LINUX_MEM_LEN               (0xD00000)    // 16MB
#else

// Linux kernel space
#define LINUX_MEM_AVAILABLE			0x00000000UL
#define LINUX_MEM_BASE_ADR 			(LINUX_MEM_AVAILABLE)
#define LINUX_MEM_GAP_CHK  			(LINUX_MEM_BASE_ADR-LINUX_MEM_AVAILABLE)
#define LINUX_MEM_LEN               (0x1000000)     // 16MB
#endif
             
// need 512 byte alignment SD
#define MVD_FRAMEBUFFER_AVAILABLE   (LINUX_MEM_BASE_ADR + LINUX_MEM_LEN)
#define MVD_FRAMEBUFFER_ADR         MemAlign(MVD_FRAMEBUFFER_AVAILABLE, 512)
#define MVD_FRAMEBUFFER_ADR_GAP_CHK (MVD_FRAMEBUFFER_ADR-MVD_FRAMEBUFFER_AVAILABLE)
#define MVD_FRAMEBUFFER_LEN         0x1DB000 // 1900KB, 3 Buffers=720*576*1.5*3

#if 0   // 8K only. It can be allocated via kmalloc
#define BMP_INFO_AVAILABLE          (MVD_FRAMEBUFFER_ADR+MVD_FRAMEBUFFER_LEN)
#define BMP_INFO_POOL_ADR           MemAlign(BMP_INFO_AVAILABLE, 8)
#define BMP_INFO_GAP_CHK            (BMP_INFO_POOL_ADR-BMP_INFO_AVAILABLE)
#define BMP_INFO_POOL_LEN           0x2000                         // 8K
#endif

// must start at nnn0000 - 512k alignment   --[Dean] be careful allocate this big alignment area
#define MAD_BASE_AVAILABLE          (MVD_FRAMEBUFFER_ADR+MVD_FRAMEBUFFER_LEN)
#define MAD_BASE_BUFFER_ADR         MemAlign(MAD_BASE_AVAILABLE, 0x80000)
#define MAD_BASE_BUFFER_ADR_GAP_CHK (MAD_BASE_BUFFER_ADR-MAD_BASE_AVAILABLE)
#define MAD_BASE_BUFFER_LEN         0x80000                      // 352K
//------------------------------------------------------------------
// details for MAD BUFFER (ES buffer + PCM buffer)
#define MAD_ES_AVAILABLE        (MAD_BASE_BUFFER_ADR)
#define MAD_ES_BUFFER_ADR       (MAD_ES_AVAILABLE)
#define MAD_ES_GAP_CHK          (MAD_ES_BUFFER_ADR-MAD_ES_AVAILABLE)
#define MAD_ES_BUFFER_LEN       0x8000                        // 32K

#define MAD_PCM_AVAILABLE       (MAD_ES_BUFFER_ADR+MAD_ES_BUFFER_LEN)
#define MAD_PCM_BUFFER_ADR      (MAD_PCM_AVAILABLE)
#define MAD_PCM_GAP_CHK         (MAD_PCM_BUFFER_ADR-MAD_PCM_AVAILABLE)
#define MAD_PCM_BUFFER_LEN      0x10000                       // 64K

//------------------------------------------------------------------
// co buffer with MAD_BASE_BUFFER_ADR
#if 0
#define FILE_SYSTEM_AVAILABLE   (MAD_BASE_BUFFER_ADR)
#define FILE_SYSTEM_TABLE_ADR   (FILE_SYSTEM_AVAILABLE)
#define FILE_SYSTEM_GAP_CHK     (FILE_SYSTEM_TABLE_ADR-FILE_SYSTEM_AVAILABLE)
#define FILE_SYSTEM_TABLE_LEN   0x2000                         // 8K
#endif

#define MAD_JPEG_IN_AVAILABLE   (MAD_BASE_BUFFER_ADR)
#define MAD_JPEG_INBUFFER_ADR   (MAD_JPEG_IN_AVAILABLE)
#define MAD_JPEG_IN_GAP_CHK     (MAD_JPEG_INBUFFER_ADR-MAD_JPEG_IN_AVAILABLE)
#define MAD_JPEG_INBUFFER_LEN   (MAD_BASE_BUFFER_LEN)
//--------------------------------------------------------------

// need 64k align
#define XD_MAP_BASE_AVAILABLE       (MAD_BASE_BUFFER_ADR + MAD_BASE_BUFFER_LEN)
#define XD_MAP_BASE_ADR             MemAlign(XD_MAP_BASE_AVAILABLE, 0x10000)
#define XD_MAP_BASE_ADR_GAP_CHK     (XD_MAP_BASE_ADR-XD_MAP_BASE_AVAILABLE)
#define XD_MAP_LEN                  0x10000                       // 64K

// need 4k byte alignment
#define GOP_REGDMABASE_AVAILABLE            XD_MAP_BASE_AVAILABLE
#define GOP_REGDMABASE_START_ADR            MemAlign(GOP_REGDMABASE_AVAILABLE, 0x1000)
#define GOP_REGDMABASE_START_ADR_GAP_CHK    (GOP_REGDMABASE_START_ADR-GOP_REGDMABASE_AVAILABLE)
#define GOP_REGDMABASE_LEN                  512

#if 0   // this is code area of 8051. [Dean]
// need 64k align
#define CODE_MAP_BASE_AVAILABLE     (XD_MAP_BASE_ADR + XD_MAP_LEN)
#define CODE_MAP_BASE_ADR           MemAlign(CODE_MAP_BASE_AVAILABLE, 0x10000)
#define CODE_MAP_BASE_ADR_GAP_CHK   (CODE_MAP_BASE_ADR-CODE_MAP_BASE_AVAILABLE)
#define CODE_MAP_LEN                MCU_CODE_SIZE
#endif

// need 8 byte alignment
#define MVD_BITSTREAM_AVAILABLE     (GOP_REGDMABASE_START_ADR + GOP_REGDMABASE_LEN)
#define MVD_BITSTREAM_ADR           MemAlign(MVD_BITSTREAM_AVAILABLE, 8)
#define MVD_BITSTREAM_ADR_GAP_CHK   (MVD_BITSTREAM_ADR-MVD_BITSTREAM_AVAILABLE)
#define MVD_BITSTREAM_LEN           0x40000                     // 256KB

#if 0   // needed?? [Dean]
#define DATABASE_START_AVAILABLE    (MVD_BITSTREAM_ADR + MVD_BITSTREAM_LEN)
#define DATABASE_START_ADR          MemAlign(DATABASE_START_AVAILABLE, 8)
#define DATABASE_START_ADR_GAP_CHK  (DATABASE_START_ADR-DATABASE_START_AVAILABLE)
#define DATABASE_LEN                0x10800                              // 66K

#define FONT_AVAILABLE              (DATABASE_START_ADR + DATABASE_LEN)
#define FONT_START_ADR              MemAlign(FONT_AVAILABLE, 8)
#define FONT_START_ADR_GAP_CHK      (FONT_START_ADR-FONT_AVAILABLE)
#define FONT_LEN                    0x12C000                   // 1200KB

// need 2k byte alignment
#define BMP_AVAILABLE               (FONT_START_ADR + FONT_LEN)
#define BMP_START_ADR               MemAlign(BMP_AVAILABLE, 0x800)
#define BMP_START_ADR_GAP_CHK       (BMP_START_ADR-BMP_AVAILABLE)
//#define BMP_LEN                     0x29B000                   // 2668KB
//#define BMP_LEN                     0xE1000                   // 900KB
#define BMP_LEN                     0x200000                   // 2048KB

// need 2k byte alignment
#define STRING_AVAILABLE            (BMP_START_ADR + BMP_LEN)
#define STRING_START_ADR            MemAlign(STRING_AVAILABLE, 0x800)
#define STRING_START_ADR_GAP_CHK    (STRING_START_ADR-STRING_AVAILABLE)
#define STRING_LEN                  0                          // 0KB
#endif

#define GE_FRAMEBUFFER_AVAILABLE    (MVD_BITSTREAM_ADR + MVD_BITSTREAM_LEN)
#define GE_FRAMEBUFFER_ADR          MemAlign(GE_FRAMEBUFFER_AVAILABLE, 8)
#define GE_FRAMEBUFFER_ADR_GAP_CHK  (GE_FRAMEBUFFER_ADR-GE_FRAMEBUFFER_AVAILABLE)
#define GE_FRAMEBUFFER_LEN          (0x426800+0x80000+0x100000)         // 5786KB

//------------------------------------------------------------------
// GOP
#define GOP_GWIN_RB_AVAILABLE   GE_FRAMEBUFFER_ADR
#define GOP_GWIN_RB_BASE_ADR    (GOP_GWIN_RB_AVAILABLE)
#define GOP_GWIN_RB_GAP_CHK     (GOP_GWIN_RB_BASE_ADR-GOP_GWIN_RB_AVAILABLE)
#define GOP_GWIN_RB_BASE_LEN    GE_FRAMEBUFFER_LEN

// SUBTITLE
#define SUBTITLE_AVAILABLE      ((GE_FRAMEBUFFER_ADR + GE_FRAMEBUFFER_LEN) - 0x189000)  //reserved 1610KB
#define SUBTITLE_START_ADR      MemAlign(SUBTITLE_AVAILABLE, 0x10000)
#define SUBTITLE_GAP_CHK        (SUBTITLE_START_ADR-SUBTITLE_AVAILABLE)
#define SUBTITLE_LEN            0x178000                     // 1510KB
//------------------------------------------------------------------

//------------------------------------------------------------------
#if 0   // needed?? [Dean]
// need 8 bytes alignment for GE DMA
#define SI_MONITOR_DB_AVAILABLE     (GE_FRAMEBUFFER_ADR + GE_FRAMEBUFFER_LEN)
#define SI_MONITOR_DB_START_ADR     MemAlign(SI_MONITOR_DB_AVAILABLE, 8)
#define SI_MONITOR_DB_GAP_CHK       (SI_MONITOR_DB_START_ADR-SI_MONITOR_DB_AVAILABLE)
#define SI_MONITOR_DB_LEN           0xD000                  //52K

#define FONT_INFO_AVAILABLE         (SI_MONITOR_DB_START_ADR + SI_MONITOR_DB_LEN)
#define FONT_INFO_POOL_ADR          MemAlign(FONT_INFO_AVAILABLE, 8)
#define FONT_INFO_GAP_CHK           (FONT_INFO_POOL_ADR-FONT_INFO_AVAILABLE)
#define FONT_INFO_POOL_LEN          0x800                   // 2K

// need 4K bytes alignment for slice window
#define SRV_NAME_BUF_AVAILABLE     (FONT_INFO_POOL_ADR + FONT_INFO_POOL_LEN)
#define SRV_NAME_BUF_START_ADR     MemAlign(SRV_NAME_BUF_AVAILABLE, 0x1000)
#define SRV_NAME_BUF_GAP_CHK       (SRV_NAME_BUF_START_ADR-SRV_NAME_BUF_AVAILABLE)
#define SRV_NAME_BUF_LEN           0x1000                   //4K

// Common Interface, 4K alignment
#define MMI_TEXTSTRING_AVAILABLE    (SRV_NAME_BUF_START_ADR+SRV_NAME_BUF_LEN)
#define MMI_TEXTSTRING_ADR          MemAlign(MMI_TEXTSTRING_AVAILABLE, 0x1000)
#define MMI_TEXTSTRING_ADR_GAP_CHK (MMI_TEXTSTRING_ADR - MMI_TEXTSTRING_AVAILABLE)
#define MMI_TEXTSTRING_LEN          0x1000                  // 4K

#define CI_PMT_BUFFER_AVAILABLE     (MMI_TEXTSTRING_ADR+MMI_TEXTSTRING_LEN)
#define CI_PMT_BUFFER_ADR           (CI_PMT_BUFFER_AVAILABLE)
#define CI_PMT_BUFFER_ADR_GAP_CHK   (CI_PMT_BUFFER_ADR-CI_PMT_BUFFER_AVAILABLE)
#define CI_PMT_BUFFER_LEN           0x1000                  // 4K
#endif

#define EVENTDB_SDRAM_AVAILABLE     (SUBTITLE_START_ADR + SUBTITLE_LEN)
// *** Event DB need 4K alignment because this address is used in 4K xdata window ***
#define EVENTDB_SDRAM_START_ADR     MemAlign(EVENTDB_SDRAM_AVAILABLE, 4096)
#define EVENTDB_SDRAM_ADR_GAP_CHK   (EVENTDB_SDRAM_START_ADR-EVENTDB_SDRAM_AVAILABLE)
#define EVENTDB_SDRAM_LEN           0x385000                // 3.52MB

#define VE_FRAMEBUFFER_AVAILABLE    (EVENTDB_SDRAM_START_ADR + EVENTDB_SDRAM_LEN)
#define VE_FRAMEBUFFER_ADR          MemAlign(VE_FRAMEBUFFER_AVAILABLE, 8)
#define VE_FRAMEBUFFER_ADR_GAP_CHK  (VE_FRAMEBUFFER_ADR-VE_FRAMEBUFFER_AVAILABLE)
#define VE_FRAMEBUFFER_LEN          0x195000UL            // 720*576*2*2

#define EMAC_MEM_LEN                0x100000
#define EMAC_MEM_ADR                (VE_FRAMEBUFFER_ADR+VE_FRAMEBUFFER_LEN)//0x00200000UL
#define MIU0_END_ADR                (EMAC_MEM_ADR+EMAC_MEM_LEN)//(MPOOL_ADR+MPOOL_LEN)

#if 0
//------------------------------------------------------------------
// co_buffer with VE_FRAMEBUFFER_ADR and SCALER_DNR_BUF_ADR
#define DOWNLOAD_WIN1_ADR           MemAlign(VE_FRAMEBUFFER_AVAILABLE, 4096)    // Need 4K alignment
#define DOWNLOAD_WIN1_LEN           XDATA_WIN1_SIZE                             // Same as XDATA Window1

#define DOWNLOAD_AVAILABLE          (DOWNLOAD_WIN1_ADR + DOWNLOAD_WIN1_LEN)
#define DOWNLOAD_BUFFER_ADR         MemAlign(DOWNLOAD_AVAILABLE, 4096)          // Need 4K alignment
#define DOWNLOAD_GAP_CHK            (DOWNLOAD_BUFFER_ADR - DOWNLOAD_AVAILABLE)
#define DOWNLOAD_BUFFER_LEN         0x400000                                    // 4MB
//------------------------------------------------------------------
#endif
//======================================================================
// Can not add any buffer here (in between VE_FRAMEBUFFER_ADR and SCALER_DNR_BUF_ADR)
// Because USB/OAD download use the buffer from VE_FRAMEBUFFER_ADR to the end of SCALER_DNR_BUF_ADR
//======================================================================

// For Maximum is 1920x1088x3x2 about 12MB in HDMI and YPbPr
// Let it overwrite EVENTDB and MHEG5 buffer(These buffers is DTV only)
#define SCALER_DNR_AVAILABLE        (VE_FRAMEBUFFER_ADR + VE_FRAMEBUFFER_LEN)
#define SCALER_DNR_BUF_ADR          MemAlign(SCALER_DNR_AVAILABLE, 8)
#define SCALER_DNR_GAP_CHK          (SCALER_DNR_BUF_ADR-SCALER_DNR_AVAILABLE)
#define SCALER_DNR_BUF_LEN          (((736UL*3+0x0F) & ~0x0F) * 581UL *2)  //(720UL*576*3*2)   // SCALER_MEM_SIZE

#define SCALER_DNR_W_AVAILABLE      (SCALER_DNR_BUF_ADR + SCALER_DNR_BUF_LEN)
#define SCALER_DNR_W_BARRIER_ADR    (SCALER_DNR_W_AVAILABLE)
#define SCALER_DNR_W_GAP_CHK        (SCALER_DNR_W_BARRIER_ADR-SCALER_DNR_W_AVAILABLE)
#define SCALER_DNR_W_BARRIER_LEN    80//16  // DNR submit 2 64-bit data before compare limit

#define SCALER_DNR_BUF_LEN_EXT      ((((896UL-736UL)*3+0x0F) & ~0x0F) * 581UL *2) // the output size of VD will be 848 * 581

#define MHEG5_BUFFER_AVAILABLE      (SCALER_DNR_W_BARRIER_ADR+SCALER_DNR_W_BARRIER_LEN)
#define MHEG5_BUFFER_ADR            MemAlign(MHEG5_BUFFER_AVAILABLE, 256)
#define MHEG5_BUFFER_ADR_GAP_CHK    (MHEG5_BUFFER_ADR-MHEG5_BUFFER_AVAILABLE)
#define MHEG5_BUFFER_LEN            0x864C00                   // 8595KB
//------------------------------------------------------------------
// co_buffer with MHEG5_BUFFER_ADR
// TTX
#define TTXBUF_START_AVAILABLE  (MHEG5_BUFFER_ADR + SCALER_DNR_BUF_LEN_EXT)
#define TTXBUF_START_ADR        MemAlign(TTXBUF_START_AVAILABLE, 8)
#define TTXBUF_START_GAP_CHK    (TTXBUF_START_ADR-TTXBUF_START_AVAILABLE)
#define TTXBUF_LEN              0x23E000   // 2048K + 256K
//--------------------------------------------------------------
// TTX Internal define
#define TTXBUF_VBI_SIZE         (360*48)
#define TTX_MAX_PAGES       1000
//--------------------------------------------------------------
#define TTX_VE_BUFFER_AVAILABLE (TTXBUF_START_ADR+TTXBUF_LEN)
#define TTX_VE_BUFFER_ADDR      MemAlign(TTX_VE_BUFFER_AVAILABLE, 8)
#define TTX_VE_BUFFER_GAP_CHK   (TTX_VE_BUFFER_ADDR-TTX_VE_BUFFER_AVAILABLE)
#define TTX_VE_BUFFER_LEN       0x2000

#define TTX_FONT_START_AVAILABLE (TTX_VE_BUFFER_ADDR + TTX_VE_BUFFER_LEN)
#define TTX_FONT_START_ADR MemAlign(TTX_FONT_START_AVAILABLE, 8)
#define TTX_FONT_START_GAP_CHK (TTX_FONT_START_ADR - TTX_FONT_START_AVAILABLE)
#define TTX_FONT_START_LEN   0x40000   // 256KB

//------------------------------------------------------------------
// co_buffer with MHEG5_BUFFER_ADR
// need 512k byte alignment
#define DECOMPRESS_DATA_BUFFER_AVAILABLE  (TTX_FONT_START_ADR+TTX_FONT_START_LEN)
#define DECOMPRESS_DATA_BUFFER_ADR        MemAlign(DECOMPRESS_DATA_BUFFER_AVAILABLE, 0x80000)
#define DECOMPRESS_DATA_BUFFER_GAP_CHK    (DECOMPRESS_DATA_BUFFER_ADR-DECOMPRESS_DATA_BUFFER_GAP_CHK)
#define DECOMPRESS_DATA_BUFFER_LEN        0x100000                // 1M
//------------------------------------------------------------------

#ifdef COMB_3D
// 3D_COMB buffer start address
#define COMB_3D_BUF_AVAILABLE   (DECOMPRESS_DATA_BUFFER_ADR+DECOMPRESS_DATA_BUFFER_LEN)
#define COMB_3D_BUF_START_ADR   MemAlign(COMB_3D_BUF_AVAILABLE ,8) // if you want to change this line, please check msAPI_Aeon_Disable() and msAPI_Aeon_ReInitial() @ msAPI_Memory.c because it is co-buffer with MHEG5
#define COMB_3D_BUF_GAP_CHK     (COMB_3D_BUF_START_ADR-COMB_3D_BUF_AVAILABLE)
#define COMB_3D_BUF_LEN         (4UL * 1024 * 1024)         // 3.9MB
#endif

//------------------------------------------------------------------
// co_buffer with MHEG5_BUFFER_ADR
#define MAD_JPEG_OUT_AVAILABLE  (MHEG5_BUFFER_ADR)
#define MAD_JPEG_OUTBUFFER_ADR  (MAD_JPEG_OUT_AVAILABLE)
#define MAD_JPEG_OUT_GAP_CHK    (MAD_JPEG_OUTBUFFER_ADR-MAD_JPEG_OUT_AVAILABLE)
#define MAD_JPEG_OUTBUFFER_LEN  0x3FC000                // 3.984375M
//------------------------------------------------------------------

//------------------------------------------------------------------
// co_buffer with MHEG5_BUFFER_ADR
#define DOWNLOAD_ZIPBUFFER_ADR  (MHEG5_BUFFER_ADR)
#define DOWNLOAD_ZIPBUFFER_LEN  0x400000            // 4M
//------------------------------------------------------------------


// USB driver buffe
#define USB_BUFFER_START_ADR_4K_ALIGN        (MemAlign( (MHEG5_BUFFER_ADR+MHEG5_BUFFER_LEN), 4096))
#define USB_BUFFER_START_ADR_4K_ALIGN_LEN              0x1000                                      // 4K

#define FILE_SYSTEM_POOL_ADR           MemAlign(USB_BUFFER_START_ADR_4K_ALIGN + USB_BUFFER_START_ADR_4K_ALIGN_LEN, 0x1000)
#define FILE_SYSTEM_POOL_LEN            0x14000  //84K


#define DMDATA_AVAILABLE                (FILE_SYSTEM_POOL_ADR + FILE_SYSTEM_POOL_LEN)
#define DMDATA_ADR                      MemAlign(DMDATA_AVAILABLE, 4096)   // for Window1 alignment
#define DMDATA_GAP_CHK                  (DMDATA_ADR-DMDATA_AVAILABLE)
#define DMDATA_SPACE_LEN                (4096)   // allocate window1 size of DMDATA


#define DUMMY_AVAILABLE             (DMDATA_ADR + DMDATA_SPACE_LEN)
#define DUMMY_SPACE                 MemAlign(DUMMY_AVAILABLE, 8)
#define DUMMY_GAP_CHK               (DUMMY_SPACE-DUMMY_AVAILABLE)
#define DUMMY_SPACE_LEN             0x0008                    // 8 bytes

#define END_OF_MEMORY_MAP           (DUMMY_SPACE+DUMMY_SPACE_LEN)
#define END_MEMORY_GAP              (MIU_DRAM_LEN-END_OF_MEMORY_MAP)

#define MIU0_END_ADR                (MPOOL_ADR+MPOOL_LEN)

#if (END_OF_MEMORY_MAP > MIU_DRAM_LEN)
#error "Memory MAP Overflow!!!"
#endif

#endif

