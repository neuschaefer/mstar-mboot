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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *t_fpin;
    FILE *t_fpout;
    unsigned int t_filesize = 0;
    unsigned int align_size = 0;	
	unsigned int padding_size = 0;
    unsigned char *t_buf = NULL;
	unsigned char i;
    int t_i;
	
	if (argc < 3)
	{
	    printf("[Error]please enter the correct input!\n");
        return -1;
	}

	//get align size
	align_size=strtoul(argv[2], NULL, 16);
	//printf("align_size : 0x%x\n",align_size);
   
    if(align_size == 0)
    {
        printf("[Warning] Ignore Alignment Size : 0x%x\n",align_size);
        return 0;
    }    

    t_fpin = fopen(argv[1], "rb");
    if (NULL == t_fpin)
    {
        printf("[Error]cannot open %s\n", argv[1]);
        return -1;
    }
	
	//get file size
	fseek(t_fpin, 0, SEEK_END);
	t_filesize = ftell(t_fpin);
	fseek(t_fpin, 0, SEEK_SET);
	fclose(t_fpin);
	//printf("t_filesize : 0x%x\n",t_filesize);
	
	//get padding size
	if(t_filesize > align_size)
	{
        if(t_filesize % align_size != 0)
        {    
		    padding_size = align_size - (t_filesize % align_size);
        }
        else
        {
            padding_size = 0;
        }
		//printf("padding_size = 0x%x\n",padding_size);			
	}
	else if(t_filesize == align_size)
	{
	    //unnecessary padding		
		padding_size = 0;
		//printf("padding_size = 0x%x\n",padding_size);		
		return 0;
	}
	else
	{		
		padding_size = align_size - t_filesize;
    	//printf("padding_size = 0x%x\n",padding_size);		
	}
	
	// put pending data to target file
	t_buf = (unsigned char*)malloc(padding_size);
	if (NULL == t_buf)
	{
		printf("[Error]memory allocation.\n");
		return -1;
	}
	t_fpout = fopen(argv[1], "ab");
	if (NULL == t_fpout)
	{
		printf("[Error]cannot open %s\n", argv[1]);
		return -1;
	}
	memset(t_buf,0,padding_size);
	fwrite(t_buf, sizeof(unsigned char), padding_size, t_fpout);

    free(t_buf);
    fclose(t_fpout);
    return 0;
}
