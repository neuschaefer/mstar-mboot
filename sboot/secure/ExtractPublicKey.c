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
#include <memory.h>

unsigned char t_buf[512], hexbuf[256];
unsigned char PublicKeyE[4];
    
// Convert binary file into HEX bytes for being included in a .c file.
int str2hex(unsigned char* pInput, unsigned char *pOutput, int *len)
{
    char c1, c2;
    int i, length;
    
    length = strlen(pInput);
    if(length%2)
    {
        return 0;
    }
    
    for(i=0; i<length; i++)
    {
    	pInput[i] = toupper(pInput[i]);
    }
    
    for(i=0; i< length/2; i++)
    {
        c1 = pInput[2*i];
        c2 = pInput[2*i+1];
        if(c1<'0' || (c1 > '9' && c1 <'A') || c1 > 'F')
        {
            continue;
        }
        
        if(c2<'0' || (c2 > '9' && c2 <'A') || c2 > 'F')
        {
            continue;
        }
        
        c1 = c1>'9' ? c1-'A'+10 : c1 -'0';
        c2 = c2>'9' ? c2-'A'+10 : c2 -'0';
        pOutput[i] = c1<<4 | c2;
    }
    *len = i;
    return 1;
}

int main(int argc, char* argv[])
{
    FILE* t_fpin;
    FILE *t_fpout;
    int len;
    int  t_i;

    if (3 != argc) 
    {
        printf("Usage: %s <input>\n", argv[0]);
        return 0;
    }

    t_fpin = fopen(argv[1], "rb");
    if (NULL == t_fpin)
    {
        printf("[Error]cannot open %s\n", argv[1]);
        return -1;
    }

    t_fpout = fopen(argv[2], "wb");
    if (NULL == t_fpout)
    {
        printf("[Error]cannot open %s\n", argv[2]);
        return -1;
    }

    fseek(t_fpin,(33*2),SEEK_SET);//skip 33 bytes header
    memset(t_buf, 0, sizeof(unsigned char)*512);
    fread(t_buf, 1, 256*2, t_fpin);
    str2hex(t_buf, hexbuf, &len);
    //write public_key_N(256 byte) into file
    fwrite(hexbuf, sizeof(unsigned char),256,t_fpout);

    //skip 33+256 bytes to public_key_e header position
    fseek(t_fpin,((33*2)+(256*2)),SEEK_SET);
    memset(t_buf, 0, sizeof(unsigned char)*512);
    fread(t_buf, 1, 2, t_fpin);
    str2hex(t_buf, hexbuf, &len);
    if (hexbuf[0] == 0x02)
    {
        fread(t_buf, 1, 2, t_fpin);
        str2hex(t_buf, hexbuf, &len);
        if (hexbuf[0] == 0x01)
        {
            fread(t_buf, 1, 2, t_fpin);
            str2hex(t_buf, &PublicKeyE[3], &len);
            PublicKeyE[0] = PublicKeyE[1] = PublicKeyE[2] = 0x00;
            //write public_key_E(4 byte) into file
            fwrite(PublicKeyE, sizeof(unsigned char), 4, t_fpout);
        }
    }
    fclose(t_fpin);
    fclose(t_fpout);
    printf("ExtractPublicKey Done !!\n");
    return 0;
}
