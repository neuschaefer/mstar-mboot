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
#include <command.h>
#include <MsUtility.h>

#if(ENABLE_MODULE_COMPRESS==1)
U_BOOT_CMD(
	mscompress7,	 6, 0, do_mscompress7,
	"Compress or decompress lzma files",
	"\n"
	"Usage:  lzma <e|d> <index> Src_Address Src_Length Dst_Address\n"
	"      e: encode file\n"
	"      d: decode file\n"
	"      <index> start to (de)compress position\n"
);
#endif

U_BOOT_CMD(
	delay,	 6, 0, do_mdelay,
	"delay time, time unit is ms\n",
	"Usage: delay [time]."
);

#if ((ENABLE_MODULE_USB == 1)&&(ENABLE_MODULE_FAT==1))
#if (ENABLE_MODULE_FAT_WRITE==1)
U_BOOT_CMD(
    spi2usb, 4, 0, do_spi2usb,
    "Read data from spi to usb",
    "[spi offset] [length] [output file name]\n"
);
#endif

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
    usb2spi, 4, 0, do_usb2spi,
    "write data from usb to spi",
    "[spi offset] [length] [intput file name]\n"
);
#endif

#endif

#if ((ENABLE_MODULE_USB == 1)&&(ENABLE_MODULE_EEPROM==1))
U_BOOT_CMD(eeprom2usb, 4, 0, do_eeprom2usb,
    "dump data from eeprom to usb",
    "<eeprom offset> <len> <output file name>\n"
    );


U_BOOT_CMD(usb2eeprom, 4, 0, do_usb2eeprom,
    "write data from usb to eeprom",
    "<eeprom offset> <len> <intput file name>\n"
    );

#endif

#if defined(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN) && defined (CONFIG_MSTAR_TOOL_PROGRAM)
U_BOOT_CMD(nandprogramforrom, 1, 0, do_nandprogramforrom,
    "program nand for rom boot",
    "\n"
    );
#endif

#if defined(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN) && defined (CONFIG_MSTAR_TOOL_CMDLINE)
U_BOOT_CMD(skipnandprogramforrom, 1, 0, do_skipnandprogramforrom,
    "enter cmd line when use tv tool for nand program",
    "\n"
    );
#endif
