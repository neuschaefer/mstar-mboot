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
typedef unsigned int   U16;
typedef unsigned long  U32;

#define RIU_MAP  0xA0000000
#define RIU      ((unsigned short volatile *) RIU_MAP)

#define BIT0        0x0001
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

#define BRINGUP_MCU51   0


void PM_MCU_Init(void);
void PM_MCU_Init(void)
{



     #if (BRINGUP_MCU51)
    U32 start_addr = 0x00000;
    U32 end_addr = 0xff0000;
    U32 u32temCnt;
    #endif
    U16 u16temp;

    #if 1//gating mcu51 clock
    u16temp = *((unsigned short volatile *) 0xBF001ca4);
    u16temp = u16temp & (~BIT12);
    *((unsigned short volatile *) 0xBF001ca4) = u16temp;
    #endif

    #if (BRINGUP_MCU51)
    //set reset password 0x0e40=0x0c00
    //*((unsigned short volatile *) 0xBF001c80) = 0x0c00;

    #if 1//---Important!!!
    *((unsigned short volatile *) 0xBF001c80) &= (U16)(~BIT14); //spi_clk=xtal
    *((unsigned short volatile *) 0xBF001c80) &= (U16)(~BIT7);  //mcu51 clk=xtal
    *((unsigned short volatile *) 0xBF002030) &= (U16)(~BIT3);  // i_cache rstz
    *((unsigned short volatile *) 0xBF005740) |= (U16)(BIT0);   //disable i cache
    #endif

      *((unsigned short volatile *) 0xBF002028) = (U16)(start_addr & 0x0000FFFF);
    *((unsigned short volatile *) 0xBF002020) = (U16)((start_addr>>16) & 0x000000FF);
    *((unsigned short volatile *) 0xBF00202c) = (U16)(end_addr & 0x0000FFFF);
    *((unsigned short volatile *) 0xBF002024) = (U16)((end_addr>>16) & 0x000000FF);

    #if 1 //T3
    //set spi offset set reg_spi_offset_addr[7:0]     0x0010f9 = 0x01     => 0x10000
    //set reg_spi_offset_en               0x0010f8 = 0x01
    *((unsigned short volatile *) 0xBF0021f0) = 0x0101;
    #else //U3

    *((unsigned short volatile *) 0xBF007834) = 0x01;

    #endif
    //set reset password 0x0e54=0x829f
     *((unsigned short volatile *) 0xBF001cA8) = 0x829f;

    //reg_fire[3:0]                   0x000e53 = 0x01

    //reg_fire[3:0]                   0x000e53 = 0x00

    u16temp = *((unsigned short volatile *) 0xBF001ca4);
    u16temp = u16temp | (BIT8);
    *((unsigned short volatile *) 0xBF001ca4) = u16temp;

    for(u32temCnt=0; u32temCnt<0xffff; u32temCnt++);

    u16temp = *((unsigned short volatile *) 0xBF001ca4);
    u16temp = u16temp & (~BIT8);
    *((unsigned short volatile *) 0xBF001ca4) = u16temp;

    u16temp = *((unsigned short volatile *) 0xBF001ca4);
    u16temp = u16temp & (~BIT12);
    *((unsigned short volatile *) 0xBF001ca4) = u16temp;

    for(u32temCnt=0; u32temCnt<0xffff; u32temCnt++);

    u16temp = *((unsigned short volatile *) 0xBF001ca4);
    u16temp = u16temp | (BIT12);
    *((unsigned short volatile *) 0xBF001ca4) = u16temp;

    *((unsigned short volatile *) 0xBF001c48) = 0x08;
    u16temp=0;

    while(*((unsigned short volatile *) 0xBF001c48) == 0x08)
    {
        *((unsigned short volatile *) 0xBF206700) = (u16temp++);
        *((unsigned short volatile *) 0xBF206704) = (0x1234);
        //*((unsigned short volatile *) 0xBF206708) = (0x5678);

    }

	while(1)
	{
	    *((unsigned short volatile *) 0xBF206708) = (u16temp++);
	    *((unsigned short volatile *) 0xBF20670A) = (0x5678);
	}


#endif

   //while(1);

}



