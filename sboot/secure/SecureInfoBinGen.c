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

/* arguments:   "MBoot file path" "MBoot address" "sensitive file path" "Sensitive address"
                "str_rsa_loader_key" "str_signature_root" "str_signature_loader" "str_signature_fw"
*/
#include <stdio.h>
#include <string.h>
#include <memory.h>

unsigned char t_buf[512];
unsigned char t_buf_chunk[1024];

#define SIGNATURE_LEN	256

typedef struct
{
    unsigned char RSA_loader_public_key_n[256];
    unsigned char RSA_loader_public_key_e[4];
    unsigned char signature_loader[SIGNATURE_LEN];
}SECURITY_INFO;

int str2hex(char* pInput, unsigned char* pOutput, int* len)
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
    
    for(i = 0; i< strlen(pInput)/2; i++)
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

int main(int argc, char *argv[])
{
    FILE	*t_fpin;
    FILE 	*t_fpout;
    SECURITY_INFO sec;
    
    int len;
    int t_filesize = 0;
    
    if (4!=argc)
    {
        printf("[usage]:\n");
        printf("%s ChunkHeader RsaPublicLoaderKey SignatureLoader \n", argv[0]);
        return -1;
    }

		/* init security structure */
    memset(&sec, 0, sizeof(SECURITY_INFO));
    
    /* set Chunk Header start address and size */
    t_fpin = fopen(argv[1], "rb");
    if (NULL == t_fpin)
    {
        printf("[Error]cannot open %s\n", argv[1]);
        return -1;
    }
    
    memset(t_buf_chunk, 0, sizeof(unsigned char)*sizeof(t_buf_chunk));
    fread(t_buf_chunk, sizeof(unsigned char), sizeof(t_buf_chunk), t_fpin);
    
    fclose(t_fpin);

		//start to parse Public_Key into PubKey_E and PubKey_N
		t_fpin = fopen(argv[2],"rb");
		if (NULL == t_fpin)
    {
        printf("[Error]cannot open %s\n", argv[2]);
        return -1;
    }
		fseek(t_fpin,(33*2),SEEK_SET);//skip 33 bytes header

		//Public_Key_N
		memset(t_buf, 0, sizeof(unsigned char)*512);
		fread(t_buf, sizeof(char), 256*2, t_fpin);
		str2hex(t_buf, sec.RSA_loader_public_key_n, &len);
	
		fseek(t_fpin,((33*2)+(256*2)),SEEK_SET);//33+256 bytes header
		
		//Public_Key_E
    memset(t_buf, 0, sizeof(unsigned char)*512);
    fread(t_buf,1,2,t_fpin);
		str2hex(t_buf, &t_buf[2], &len);
		if (t_buf[2]==0x02) // 2 byte
		{
        memset(t_buf, 0, sizeof(unsigned char)*512);
	 		  fread(t_buf,1,2,t_fpin);
			  str2hex(t_buf, &t_buf[2], &len);
			  if(t_buf[2]==0x01)
			  {
	          // KEY_E: {0x00,0x00,0x00,0x11}
	          memset(t_buf, 0, sizeof(unsigned char)*512);
	 			    fread(t_buf,1,2,t_fpin);
				    str2hex(t_buf, &sec.RSA_loader_public_key_e[3], &len);
				    sec.RSA_loader_public_key_e[0]=sec.RSA_loader_public_key_e[1]=sec.RSA_loader_public_key_e[2]=0x00;
        }
    }
		fclose(t_fpin);

    /* get the signature_loader */
    t_fpin = fopen(argv[3], "rb");
    if (NULL == t_fpin)
    {
        printf("[Error]cannot open %s\n", argv[3]);
        return -1;
    }
    
    fseek(t_fpin, 0, SEEK_END);
    if (512 != ftell(t_fpin))
    {
        printf("[Error]the size of Signature_loader is not equal to 256 bytes\n");
        return -1;
    }
    
    fseek(t_fpin, 0, SEEK_SET);
    memset(t_buf, 0, sizeof(unsigned char)*512);
    fread(t_buf, 1, 256*2, t_fpin);
    str2hex(t_buf, sec.signature_loader, &len);
    fclose(t_fpin);

		memcpy((void *)&t_buf_chunk[128], (void *)&sec, sizeof(sec));
		
		/* set Chunk Header start address and size */
    t_fpout = fopen(argv[1], "wb");
    if (NULL == t_fpout)
    {
        printf("[Error]cannot open %s\n", argv[1]);
        return -1;
    }
    
		fwrite(t_buf_chunk, 1, sizeof(t_buf_chunk), t_fpout);
		fclose(t_fpout);

    //printf("SecureInfoBinGen Done !!\n");
    return 0;
}
