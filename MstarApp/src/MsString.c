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

/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include <common.h>
#include <malloc.h>
#include <MsString.h>
#include <ShareType.h>
#include <linux/ctype.h>

char* strlower(char* str)
{
    int i = 0;
    if(str == NULL)
    {
       return NULL;
    }
    while(str[i]) 
    {
       str[i] = tolower(str[i]);
       i++;
    }
    return str;
}

char* array_reverse(char * array,int ArraySize)
{
   int i=0;
   char tmp;
   if(array == NULL)
       return NULL;
   for(i=0;i<(ArraySize/2);i++)
   {
       tmp=array[ArraySize-1-i];
       array[ArraySize-1-i]=array[i];
       array[i]=tmp;
   }
   return array; 
}

char* strrps(char* source,char* findstr, char *repstr)
{
    int i= 0;      
    int Replenth = 0;   
    char *tmp = NULL;   
    char *substr = NULL;

    substr=strstr(source,findstr);
    if(substr == NULL)
        return NULL;
    tmp=(char *)malloc(strlen(substr)+1); 
    if(tmp == NULL)
        return NULL;
    strcpy(tmp,substr+strlen(findstr));
    Replenth = strlen(repstr);
    for(i=0 ; i < Replenth; i++)
    {
        substr[i]=repstr[i];             
    }
    substr[Replenth]='\0';
    strcat(substr,tmp);
    free(tmp);
    
    return source;
}

char* ParaReplace(char *str,int argc,char * const argv[])
{
    int index = 0;
    static char tmpstr[CMD_BUF];    
    char *strptr = NULL;
    char findstr[3];
    findstr[0]='$';
    findstr[2]='\0';
    memset(tmpstr,0,sizeof(tmpstr));
    strcpy(tmpstr,str);
    strptr = tmpstr;
    while((strptr=strstr(strptr,"$"))!= NULL)
    {
        if( *(strptr+1)>'0' && *(strptr+1) < '9') //check the parameter is between 0 to 9.
        {
            index = *(strptr+1) - '0' ;
            if(index > argc)
            {
                printf("Error: Parameters is bigger than argc!\n");
                return NULL;
            }
            else
            {
                findstr[1]=*(strptr+1);
                strrps(tmpstr,findstr,argv[index]);
            }
        }
        else
        {
            strptr=strptr+1;
        }
    }
    return tmpstr;
}