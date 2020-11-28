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
#ifndef __UNFD_DEVICE_H__
#define __UNFD_DEVICE_H__

#include "drvNAND.h"
#if IF_IP_VERIFY
#if defined(H9LA25G25HAMBR) && H9LA25G25HAMBR
	#define NAND_DEVICE_ID               {0xAD,0x35}
	#define NAND_DEVICE_ID_LEN           2
	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C3TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10

#elif defined(H8ACU0CE0BBR) && H8ACU0CE0BBR
    #define NAND_DEVICE_ID               {0xAD, 0x76}
	#define NAND_DEVICE_ID_LEN           2
	#define NAND_BLK_CNT                 4096
	#define NAND_BLK_PAGE_CNT            0x20
		
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS
		
	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10

#elif defined(TH58TVG7D2GBA) && TH58TVG7D2GBA
    #define NAND_DEVICE_ID               {0x98, 0xDE, 0x94, 0x82, 0x76, 0xD6}
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 4124 // original 2 /CE have 4124x2 blk, only use /CE0
	#define NAND_BLK_PAGE_CNT            0x100
	
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_40BIT1KB //
	
	#define NAND_PAGE_BYTE_CNT           0x2000
	#define NAND_SPARE_BYTE_CNT          640//0x200 // original 640

#elif defined(MT29F64G08CBAAB) && MT29F64G08CBAAB
    #define NAND_DEVICE_ID				 {0x2C, 0x88, 0x04, 0x4B, 0xA9, 0x00, 0x00, 0x00}
	#define NAND_DEVICE_ID_LEN           8
	#define NAND_BLK_CNT                 4096 // one /CE
	#define NAND_BLK_PAGE_CNT            0x100
		
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_24BIT1KB
		
	#define NAND_PAGE_BYTE_CNT           0x2000
	#define NAND_SPARE_BYTE_CNT          448

#elif defined(H8ACU0CE0DAR) && H8ACU0CE0DAR
	#define NAND_DEVICE_ID               {0xAD,0x76}
	#define NAND_DEVICE_ID_LEN           2
	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10

#elif defined(TY890A111431KA) && TY890A111431KA
	#define NAND_DEVICE_ID               {0x98,0xD0,0x00,0x15,0x72,0x14}
	#define NAND_DEVICE_ID_LEN           1
	#define NAND_BLK_CNT                 0x200
	#define NAND_BLK_PAGE_CNT            0x40
	
	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS
	
	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(TY8A0A111178KC4) && TY8A0A111178KC4
	#define NAND_DEVICE_ID               {0x98,0xC1,0x90,0x55,0x76,0x14}
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(TY890A111229KC40) && TY890A111229KC40
	#define NAND_DEVICE_ID               {0x98,0xD0,0x00,0x15,0x72,0x14}
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x200
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(TY8A0A111162KC40) && TY8A0A111162KC40 
	#define NAND_DEVICE_ID               {0x98,0xA1,0x90,0x15,0x76,0x14}
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(K9F1G08X0C) && K9F1G08X0C /* K9F1G08U0C, K9F1G08B0C */
	#define NAND_DEVICE_ID               {0xEC,0xF1,0x00,0x95,0x40}
	#define NAND_DEVICE_ID_LEN           5
	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_4BIT//ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(K9GAG08U0E) && K9GAG08U0E /* K9GAG08U0E, K9GAG08U0E */
	#define NAND_DEVICE_ID               {0xEC, 0xD5, 0x84, 0x72, 0x50, 0x42}
	#define NAND_DEVICE_ID_LEN           6
	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_24BIT1KB//ECC_TYPE_RS//ECC_TYPE_4BIT//
	#define NAND_PAGE_BYTE_CNT           0x2000
	#define NAND_SPARE_BYTE_CNT          0x1B0
	
#elif defined(K522H1GACE) && K522H1GACE /* K522H1GACE, K522H1GACE */
	#define NAND_DEVICE_ID               {0xEC,0xBA,0x00,0x55,0x44}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(H27UAG8T2M) && H27UAG8T2M
	#define NAND_DEVICE_ID               {0xAD,0xD5,0x14,0xB6,0x44}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x1000
	#define NAND_SPARE_BYTE_CNT          0x80

#elif defined(H27UAG8T2M_FAKE2K) && H27UAG8T2M_FAKE2K
	#define NAND_DEVICE_ID               {0xAD,0xD5,0x14,0xB6,0x44}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_24BIT1KB

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x80

#elif defined(NAND256W3A) && NAND256W3A
	#define NAND_DEVICE_ID               {0x20,0x75}
	#define NAND_DEVICE_ID_LEN           2

	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C3TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10

#elif defined(NAND512W3A2C) && NAND512W3A2C
	#define NAND_DEVICE_ID               {0x20,0x76}
	#define NAND_DEVICE_ID_LEN           2

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x20

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x200
	#define NAND_SPARE_BYTE_CNT          0x10

#elif defined(H27UF081G2A) && H27UF081G2A
	#define NAND_DEVICE_ID               {0xAD,0xF1,0x80,0x1D}
	#define NAND_DEVICE_ID_LEN           4

	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(H27UBG8T2A) && H27UBG8T2A
	#define NAND_DEVICE_ID               {0xAD,0xD7,0x94,0x9A,0x74,0x42}
	#define NAND_DEVICE_ID_LEN           6

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x100

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_24BIT1KB

	#define NAND_PAGE_BYTE_CNT           0x2000
	#define NAND_SPARE_BYTE_CNT          448

#elif defined(H27U1G8F2B) && H27U1G8F2B
	#define NAND_DEVICE_ID               {0xAD,0xF1,0x00,0x15}
	#define NAND_DEVICE_ID_LEN           4

	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(HY27UF084G2B) && HY27UF084G2B
	#define NAND_DEVICE_ID               {0xAD,0xDC,0x10,0x95,0x54}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(HY27UF082G2B) && HY27UF082G2B
	//#define NAND_DEVICE_ID               "\xAD\xDA\x10\x95\x44"
	#define NAND_DEVICE_ID               {0xAD,0xDA,0x10,0x95,0x44}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x800
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40//0x100
	
#elif defined(K9HAG08U1M) && K9HAG08U1M
	#define NAND_DEVICE_ID               {0xEC,0xD3,0x55,0x25,0x58}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(K511F12ACA) && K511F12ACA
	#define NAND_DEVICE_ID               {0xEC,0xA1,0x00,0x15,0x40}
	#define NAND_DEVICE_ID_LEN           5

	#define NAND_BLK_CNT                 0x400
	#define NAND_BLK_PAGE_CNT            0x40

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C4TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C2TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_RS

	#define NAND_PAGE_BYTE_CNT           0x800
	#define NAND_SPARE_BYTE_CNT          0x40

#elif defined(P1UAGA30AT) && P1UAGA30AT
	#define NAND_DEVICE_ID               {0xC8,0xD5,0x14,0x29,0x34,0x01}
	#define NAND_DEVICE_ID_LEN           0x6

	#define NAND_BLK_CNT                 0x1000
	#define NAND_BLK_PAGE_CNT            0x80

	#define NAND_RW_ADR_CYCLE_CNT        ADR_C5TFS0
	#define NAND_E_ADR_CYCLE_CNT         ADR_C3TRS0
	#define NAND_ECC_TYPE                ECC_TYPE_12BIT // only 8-bits specified

	#define NAND_PAGE_BYTE_CNT           0x1000
	#define NAND_SPARE_BYTE_CNT          218

#else
	#error "No NAND device specified\n"
#endif
#endif // IF_IP_VERIFY
#endif /* __UNFD_DEVICE_H__ */
