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
#include <common.h>
#include <MsRawIO.h>
#include <stdio.h>
#include <MsTypes.h>
#include <MsOS.h>
#include <drvBDMA.h>
#include <drvMIU.h>
#include <MsDebug.h>
#include <miu/MsDrvMiu.h>
#include <ShareType.h>
#include <bootlogo/MsPoolDB.h>
#include <MsMmap.h>
#include <MsSysUtility.h>


MS_U32 u32DramSize1 = 0, u32DramSize2 = 0,u32DramSize3 = 0;

MS_U32 u32Lx1Start = 0, u32Lx1Size = 0;
MS_U32 u32Lx2Start = 0, u32Lx2Size = 0;
MS_U32 u32Lx3Start = 0, u32Lx3Size = 0;
MS_U32 u32Block = 0;
#if 0

int MsApi_kernelProtect(void)

{
    MS_U32 u32LxStart=0,u32Size=0;
    char lx1[32]={0},lx2[32]={0},lx3[32]={0}, *start=0;
    char dram_size_tmp[32];
    MS_U8 u8BlockMiu0Index=0;
    MS_U8 u8BlockMiu1Index=0;
    MS_U8 u8BlockMiu2Index=0;    
//LX_MEM=0x9C00000 EMAC_MEM=0x100000 DRAM_LEN=0x20000000 LX_MEM2=0x50E00000,0xC200000 LX_MEM3=0xB0000000,0x0000000
    char * tok;
//MIU_INTERVAL
    char cEnvBuffer[512]= {0};

    char *s = getenv("bootargs");

    MDrv_MIU_Init();
    if (s != NULL)
    {
        strncpy(cEnvBuffer, s,255);
        u32Lx1Start = CONFIG_KERNEL_START_ADDRESS;
        u32LxStart = BA2PA(CONFIG_KERNEL_START_ADDRESS);
        UBOOT_DEBUG("Lx start:[0x%lx]\n",u32LxStart);

        tok = strtok (cEnvBuffer," ");
        while (tok != NULL)
        {
            if((start = strstr (tok, "LX_MEM=")) != NULL)
            {
                memset(lx1, 0, sizeof(lx1));
                strncpy(lx1, tok+7, strlen(lx1)-7);
            }
            else if((start = strstr (tok, "LX_MEM2=")) != NULL)
            {
                memset(lx2, 0, sizeof(lx2));
                strncpy(lx2, tok+8, strlen(lx2)-8);
            }
            else if((start = strstr (tok, "LX_MEM3=")) != NULL)
            {
                memset(lx3, 0, sizeof(lx3));
                strncpy(lx3, tok+8, strlen(lx3)-8);
            }
            
            tok = strtok (NULL, " ");
        }

        // decide whether to do kernel protect or not
        s = getenv("KERNEL_PROTECT");
        memset(cEnvBuffer, 0, 256);
        if (s != NULL)
        {
            strncpy(cEnvBuffer, s,255);
            tok = strtok (cEnvBuffer," ");
            while (tok != NULL)
            {
                if((start = strstr (tok, "DRAM_SIZE1=")) != NULL)
                {
                    memset(dram_size_tmp, 0, sizeof(dram_size_tmp));
                    strncpy(dram_size_tmp, tok+11, strlen(dram_size_tmp)-8);
                    u32DramSize1=(simple_strtoul(dram_size_tmp, NULL, 16));
                    MDrv_MIU_Dram_Size(E_MIU_0, dram_size_to_enum(u32DramSize1));
                }
                else if((start = strstr (tok, "DRAM_SIZE2=")) != NULL)
                {
                    memset(dram_size_tmp,0,sizeof(dram_size_tmp));
                    strncpy(dram_size_tmp, tok+11, strlen(dram_size_tmp)-8);
                    u32DramSize2=(simple_strtoul(dram_size_tmp, NULL, 16));
                    MDrv_MIU_Dram_Size(E_MIU_1, dram_size_to_enum(u32DramSize2));
                }               
                else if((start = strstr (tok, "DRAM_SIZE3=")) != NULL)
                {
                    memset(dram_size_tmp,0,sizeof(dram_size_tmp));
                    strncpy(dram_size_tmp, tok+11, strlen(dram_size_tmp)-8);
                    u32DramSize3=(simple_strtoul(dram_size_tmp, NULL, 16));
                    MDrv_MIU_Dram_Size(2, dram_size_to_enum(u32DramSize3));// 2:E_MIU_2
                }                 
                tok = strtok (NULL, " ");
            }
        }
#if ENABLE_NIKON || ENABLE_MILAN
        if (u32DramSize1 == 0)
        {
            printf("#######################################################################\n");
            if (u32DramSize1 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on first dram  #\n");
            printf("#######################################################################\n");            
            return 0;                              
        }
#else
        if (u32DramSize1 == 0 || u32DramSize2 == 0 || u32DramSize3 == 0)
        {
            printf("#######################################################################\n");
            if (u32DramSize1 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on first dram  #\n");
            if (u32DramSize2 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on second dram #\n");
            #if ENABLE_MONACO            
            if (u32DramSize3 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on second dram #\n");                         
            #endif            
                printf("#######################################################################\n");
            return 0;                               
        }
#endif
        //lx1
        {
            u32Lx1Size = u32Size = (simple_strtoul(lx1, NULL, 16));
            if(u32Size>0)
            {
                UBOOT_DEBUG("Lx1 start:[0x%lx]Size[0x%lx]\n",u32LxStart,u32Size);
                if(u32LxStart>=CONFIG_SYS_MIU_INTERVAL)
                {
                    MsDrv_kernelProtect(u8BlockMiu1Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu1Index+=1;
                }
                else
                {
                    MsDrv_kernelProtect(u8BlockMiu0Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu0Index+=1;
                }
            }
        }
        // lx2
        {
            tok=strtok(lx2,",");
            u32Lx2Start = u32LxStart = (simple_strtoul(tok, NULL, 16));
            tok = strtok (NULL, ",");
            u32Lx2Size = u32Size = (simple_strtoul(tok, NULL, 16));
            if(u32LxStart!=0 && u32Size!=0)
            {
                UBOOT_DEBUG("Lx2 start:[0x%lx]\n",u32LxStart);

                u32LxStart=BA2PA(u32LxStart);
                UBOOT_DEBUG("Lx2 start:[0x%lx]Size[0x%lx]\n",u32LxStart,u32Size);
                if(u32LxStart>=CONFIG_SYS_MIU2_INTERVAL)
                {
                    UBOOT_DEBUG("Lx2 At MIU 2 \n");
                    MsDrv_kernelProtect(u8BlockMiu2Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu2Index+=1;
                }                
                else if(u32LxStart>=CONFIG_SYS_MIU_INTERVAL)
                {
                    UBOOT_DEBUG("Lx2 At MIU 1 \n");
                    MsDrv_kernelProtect(u8BlockMiu1Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu1Index+=1;
                }
                else
                {
                    UBOOT_DEBUG("Lx2 At MIU 0 \n");
                    MsDrv_kernelProtect(u8BlockMiu0Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu0Index+=1;
                }
            }

        }

        //lx3

        {
            if (0 == *lx3)
            {
               UBOOT_DEBUG("lx3[32]={0}\n");
            }
            else
            {
                tok=strtok(lx3,",");
                u32Lx3Start = u32LxStart = (simple_strtoul(tok, NULL, 16));
                tok = strtok (NULL, ",");
                u32Lx3Size = u32Size = (simple_strtoul(tok, NULL, 16));
                if(u32LxStart!=0 && u32Size!=0)
                {
                    UBOOT_DEBUG("Lx3 start:[0x%lx]\n",u32LxStart);
                    u32LxStart=BA2PA(u32LxStart);
                    UBOOT_DEBUG("Lx3 start:[0x%lx]Size[0x%lx]\n",u32LxStart,u32Size);
                    if(u32LxStart>=CONFIG_SYS_MIU2_INTERVAL)
                    {
                        UBOOT_DEBUG("Lx3 At MIU 2 \n");
                        MsDrv_kernelProtect(u8BlockMiu2Index,u32LxStart,(u32LxStart + u32Size));
                        u8BlockMiu2Index+=1;
                    }                    
                    else if(u32LxStart>=CONFIG_SYS_MIU_INTERVAL)
                    {
                        UBOOT_DEBUG("Lx3 At MIU 1 \n");
                        MsDrv_kernelProtect(u8BlockMiu1Index,u32LxStart,(u32LxStart + u32Size));
                        u8BlockMiu1Index+=1;
                    }
                    else
                    {
                        UBOOT_DEBUG("Lx3 At MIU 0 \n");
                        MsDrv_kernelProtect(u8BlockMiu0Index,u32LxStart,(u32LxStart + u32Size));
                        u8BlockMiu0Index+=1;
                    }
                }
            }
        }

    }



    // decide whether to do kernel protect bist or not
    s = getenv("kernelProtectBist");
    tok = strtok (s," ");
    if (tok != NULL && 0 == strcmp(tok, "block"))
        u32Block = 1;

    return 0;
}
#else
int MsApi_kernelProtect(void)
{
    U32 u32LxStart=0,u32Size=0;
    char *start=0;
    char dram_size_tmp[32];
    MS_U8 u8BlockMiu0Index=0;
    MS_U8 u8BlockMiu1Index=0;
    MS_U8 u8BlockMiu2Index=0; 
    char cEnvBuffer[512]= {0};
    char * tok;
    char *s = getenv("KERNEL_PROTECT");
    memset(cEnvBuffer, 0, 256);
    if (s != NULL)
    {
        MsDrv_MiuInit();
        strncpy(cEnvBuffer, s,255);
        tok = strtok (cEnvBuffer," ");
        while (tok != NULL)
        {
            if((start = strstr (tok, "DRAM_SIZE1=")) != NULL)
            {
                memset(dram_size_tmp, 0, sizeof(dram_size_tmp));
                strncpy(dram_size_tmp, tok+11, strlen(dram_size_tmp)-8);
                u32DramSize1=(simple_strtoul(dram_size_tmp, NULL, 16));
                UBOOT_DEBUG("DRAM_SIZE1 0x%lx \n",u32DramSize1);
#if ((CONFIG_VESTEL_MB100 == 0))
                MDrv_MIU_Dram_Size(E_MIU_0, dram_size_to_enum(u32DramSize1));
#else
                WriteByte((0x1012D3), 0x00); //MIU_REG_BASE //disable overboundary read/write detection for MIU0 for Monaco
#endif
            }
            else if((start = strstr (tok, "DRAM_SIZE2=")) != NULL)
            {
                memset(dram_size_tmp,0,sizeof(dram_size_tmp));
                strncpy(dram_size_tmp, tok+11, strlen(dram_size_tmp)-8);
                u32DramSize2=(simple_strtoul(dram_size_tmp, NULL, 16));
                UBOOT_DEBUG("DRAM_SIZE2 0x%lx \n",u32DramSize2);
                MDrv_MIU_Dram_Size(E_MIU_1, dram_size_to_enum(u32DramSize2));
            }               
            else if((start = strstr (tok, "DRAM_SIZE3=")) != NULL)
            {
                memset(dram_size_tmp,0,sizeof(dram_size_tmp));
                strncpy(dram_size_tmp, tok+11, strlen(dram_size_tmp)-8);
                u32DramSize3=(simple_strtoul(dram_size_tmp, NULL, 16));
                UBOOT_DEBUG("DRAM_SIZE3 0x%lx \n",u32DramSize3);
#if ((CONFIG_VESTEL_MB100 == 0))
                if(u32DramSize3!=0)
                {
                    MDrv_MIU_Dram_Size(2, dram_size_to_enum(u32DramSize3));// 2:E_MIU_2
                }
#else
                WriteByte((0x1620D3), 0x00); //MIU2_REG_BASE //disable overboundary read/write detection for MIU2 for Monaco
#endif
            }                
            tok = strtok (NULL, " ");
        }

#if ENABLE_NIKON || ENABLE_MILAN
        if (u32DramSize1 == 0)
        {
            printf("#######################################################################\n");
            if (u32DramSize1 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on first dram  #\n");
            printf("#######################################################################\n");            
            return 0;                              
        }
#else
        if (u32DramSize1 == 0 || u32DramSize2 == 0 || u32DramSize3 == 0)
        {
            printf("#######################################################################\n");
            if (u32DramSize1 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on first dram  #\n");
            if (u32DramSize2 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on second dram #\n");
            #if ENABLE_MONACO            
            if (u32DramSize3 == 0)
                printf("# [PROTECT WARNING], miu kernel protect is not enabled on 3rd dram #\n");                         
            #endif            
                printf("#######################################################################\n");
            if (u32DramSize1 == 0 || u32DramSize2 == 0) 
            {
                return 0;
            }
        }
#endif
        //lx1
        if(get_addr_from_mmap("E_MMAP_LX_MEM", &u32LxStart)==0)
        {
            get_length_from_mmap("E_MMAP_LX_MEM", &u32Size);
            if(u32Size>0)
            {
                UBOOT_DEBUG("Lx1 start:[0x%x]Size[0x%x]\n",u32LxStart,u32Size);
                if(u32LxStart>=CONFIG_SYS_MIU_INTERVAL)
                {
                    MsDrv_kernelProtect(u8BlockMiu1Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu1Index+=1;
                }
                else
                {
                    MsDrv_kernelProtect(u8BlockMiu0Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu0Index+=1;
                }
            }

        }
        
        if(get_addr_from_mmap("E_LX_MEM2", &u32LxStart)==0)
        {
            get_length_from_mmap("E_LX_MEM2",&u32Size);
            if(u32Size>0)
            {
                UBOOT_DEBUG("Lx2 start:[0x%x]Size[0x%x]\n",u32LxStart,u32Size);
                if(u32LxStart>=CONFIG_SYS_MIU2_INTERVAL)
                {
                    UBOOT_DEBUG("Lx2 At MIU 2 \n");
                    MsDrv_kernelProtect(u8BlockMiu2Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu2Index+=1;
                }                
                else if(u32LxStart>=CONFIG_SYS_MIU_INTERVAL)
                {
                    UBOOT_DEBUG("Lx2 At MIU 1 \n");
                    MsDrv_kernelProtect(u8BlockMiu1Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu1Index+=1;
                }
                else
                {
                    UBOOT_DEBUG("Lx2 At MIU 0 \n");
                    MsDrv_kernelProtect(u8BlockMiu0Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu0Index+=1;
                }
            }

        }
        
        if(get_addr_from_mmap("E_LX_MEM3", &u32LxStart)==0)
        {
            get_length_from_mmap("E_LX_MEM3",&u32Size);
            if(u32Size>0)
            {
                UBOOT_DEBUG("Lx2 start:[0x%x]Size[0x%x]\n",u32LxStart,u32Size);
                if(u32LxStart>=CONFIG_SYS_MIU2_INTERVAL)
                {
                    UBOOT_DEBUG("Lx3 At MIU 2 \n");
                    MsDrv_kernelProtect(u8BlockMiu2Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu2Index+=1;
                }                    
                else if(u32LxStart>=CONFIG_SYS_MIU_INTERVAL)
                {
                    UBOOT_DEBUG("Lx3 At MIU 1 \n");
                    MsDrv_kernelProtect(u8BlockMiu1Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu1Index+=1;
                }
                else
                {
                    UBOOT_DEBUG("Lx3 At MIU 0 \n");
                    MsDrv_kernelProtect(u8BlockMiu0Index,u32LxStart,(u32LxStart + u32Size));
                    u8BlockMiu0Index+=1;
                }
                
            }

        }

    }
    return 0;
}



#endif
/*
setenv DynMmapID E_LX_MEM2 E_LX_MEM2 E_LX_MEM2 E_LX_MEM2 E_LX_MEM2 E_LX_MEM2 E_LX_MEM2
setenv MIUPRO0 0 0 E_LX_MEM2 0x00000000 0x00200000 0 43 57 82 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO1 0 1 E_LX_MEM2 0x00300000 0x00500000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO2 0 2 E_LX_MEM2 0x00600000 0x00700000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO3 0 3 E_LX_MEM2 0x00600000 0x00700000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO4 1 0 E_LX_MEM2 0x00600000 0x00700000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO5 1 1 E_LX_MEM2 0x00600000 0x00700000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO6 1 2 E_LX_MEM2 0x00600000 0x00700000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0
setenv MIUPRO7 1 3 E_LX_MEM2 0x00600000 0x00700000 0 03 06 07 08 11 12 13 15 24 26 28 29 0 0 0 0


*/
int MsApi_MiuProtect(void)
{
    char cTempBuffer[BUFFER_SIZE]= {0};
    char cEnvBuffer[BUFFER_SIZE]= {0};
    char * p_str = NULL;
    char * tok=NULL;
    int index=0;
    int client_index=0;
    U32 temp_start=0;
    U32 temp_length=0;
    MS_BOOL checkIndex=TRUE;
    UBOOT_TRACE("IN\n");
    do
    {
        memset(cTempBuffer, 0, BUFFER_SIZE);
        memset(cEnvBuffer, 0, BUFFER_SIZE);
        p_str = NULL;
        tok = NULL;
        snprintf(cTempBuffer, BUFFER_SIZE, "MIUPRO%d", index);
        UBOOT_DEBUG(" getenv[%s] \n",cTempBuffer);
        p_str = getenv (cTempBuffer);
        if(p_str != NULL)
        {
            strncpy(cEnvBuffer, p_str,BUFFER_SIZE-1);
            stMIU_PortectInfo portectInfo;
            tok = strtok (cEnvBuffer," ");
            portectInfo.miu_id=(MIU_ID)((int)simple_strtol(tok, NULL, 16));
            tok = strtok (NULL," ");
            portectInfo.u8Group=(int)simple_strtol(tok, NULL, 16);
            tok = strtok (NULL," ");
            portectInfo.c_Mmap_Id=tok;
            UBOOT_DEBUG(" MMAP ID =%s",portectInfo.c_Mmap_Id);
            checkIndex=TRUE;
            
            if( NULL!= strstr (tok, "E_") )
            {
                
                tok = strtok (NULL," ");//start not used
                tok = strtok (NULL," ");//end not used
                if(get_addr_from_mmap(portectInfo.c_Mmap_Id, &temp_start)==0)
                {
                    portectInfo.u32Start=temp_start;
                }
                else
                {
                    UBOOT_DEBUG(" index[%d]%s get mmap fail %s !!!\n",index,cTempBuffer,portectInfo.c_Mmap_Id);
                    checkIndex=FALSE;
                    
                }
                if(get_length_from_mmap(portectInfo.c_Mmap_Id, &temp_length)==0)
                {
                    portectInfo.u32End=temp_start+temp_length;
                }
                else
                {
                    UBOOT_DEBUG(" index[%d]%s get mmap fail %s !!!\n",index,cTempBuffer,portectInfo.c_Mmap_Id);
                    checkIndex=FALSE;
                }
            }
            else
            {
                
                tok = strtok (NULL," ");
                portectInfo.u32Start=simple_strtol(tok, NULL, 16);
                tok = strtok (NULL," ");
                portectInfo.u32End=simple_strtol(tok, NULL, 16);
                if(portectInfo.u32End==0)
                {
                    UBOOT_DEBUG(" index[%d] %s end of address is 0  !!!\n",index,cTempBuffer);

                    if(portectInfo.u32Start==0)
                    {
                        index=index+1;
                        continue;
                    }
                    else
                        checkIndex=FALSE;
                }
            }
            if(checkIndex==FALSE)
            {
                UBOOT_ERROR(" %s parse Fail  !!!\n",cTempBuffer);
                index=index+1;
                continue;
            }
            tok = strtok (NULL," ");// do nothing for enable/disable flag
            for(client_index=0;client_index<16;client_index++)
            {
                tok = strtok (NULL," ");
                if(tok==NULL)
                {
                    UBOOT_DEBUG(" index[%d] Client ID end of index [%d] !!!\n",index,client_index);
                    break;
                }
                portectInfo.clientID[client_index]=(MS_U8)simple_strtol(tok, NULL, 10);
            }
            if(dbgLevel>=EN_DEBUG_LEVEL_DEBUG)
            {
                printf(" Block[%d]start[%lx]end[%lx]\n",portectInfo.u8Group,portectInfo.u32Start,portectInfo.u32End);
                printf("portect IDs \n");
                for(client_index=0;client_index<16;client_index++)
                {
                    printf("%d[0x%x] ",client_index,portectInfo.clientID[client_index]);
                    if(client_index==7)
                        printf("\n");
                }
                printf("\n");
            }
                
            MsDrv_MIU_Protect(portectInfo.u8Group,portectInfo.clientID,portectInfo.u32Start,portectInfo.u32End,true);
            
        }
        else
        {
            UBOOT_DEBUG("No Portect Infor !!!\n");
            return -1;
        }
        index=index+1;
    }
    while (p_str!=NULL);
    

    UBOOT_TRACE("OK\n");
    return 0;

}

int do_MsApi_kernelProtect( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    return MsApi_kernelProtect();

}
int do_MsApi_MiuProtect( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    return MsApi_MiuProtect();

}

void MsApi_RunTimePmProtect(void)
{
    #ifdef CONFIG_MSTAR_RT_PM_IN_SPI
    {
        MsDrv_PMProtect(3,RUNTIME_PM_START_ADDR,RUNTIME_PM_START_SIZE); //64K run time PM
    }
    #endif
}
int do_MsApi_RunTimePmProtect( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    MsApi_RunTimePmProtect();
    return 0;
}

extern unsigned int u32UbootStart;
extern unsigned int u32UbootEnd;
#if 0 // by jh

// return 1 for overlap case, 0 for non-overlap case
static MS_U32 isOverlapUboot(MS_U32 u32Start, MS_U32 u32Size)
{
    if ((u32UbootStart <= u32Start) && (u32Start <= u32UbootEnd))
        return 1;
    if ((u32UbootStart <= (u32Start+u32Size)) && ((u32Start+u32Size) <= u32UbootEnd))
        return 1;
    return 0;
}

static MS_U32 return_or_block(MS_U32 u32RetVal)
{
    if (u32Block)
        while(1);

    return u32RetVal;
}


#define TEST_OFFSET (128*1024*1024) // set 128M offset
#define TEST_OFFSET_MASK (TEST_OFFSET-1)
#define MIU1_OFFSET (0xA0000000)
#define TEST_RANGE (0x80000000) // set 2G test range for each miu
static MS_U32 write_test_to_lxmem(MS_U32 u32Start, MS_U32 u32Size)
{
    MS_U32 i;
    MS_U32 u32DramValue[u32Size/sizeof(MS_U32)];
    MS_U32* pu32Start = (MS_U32*)u32Start;
    MS_U32 failed = 0;
    MS_U32 u32DramSize = 0, u32MiuOffset = 0;
    MS_U32 u32BdmaStart = 0;
    BDMA_CpyType eBdmaCpyType;

    if (!u32Size)
    {
        printf("[PROTECT ERROR], lxmem size = 0\n");
        return return_or_block(-1);
    }

    // 1. decide dram parameters
    u32DramSize = (u32Start < MIU1_OFFSET) ? u32DramSize1 : u32DramSize2;
    u32MiuOffset = (u32Start < MIU1_OFFSET) ? 0 : MIU1_OFFSET;
    eBdmaCpyType = (u32Start < MIU1_OFFSET) ? E_BDMA_FLASH2SDRAM : E_BDMA_FLASH2SDRAM1;
    if (!u32DramSize)
    {
        printf("[PROTECT ERROR], dram size = 0\n");
        return return_or_block(-1);
    }

    // 2. backup parital values in protected region
    for (i = 0; i < sizeof(u32DramValue)/sizeof(MS_U32); i++)
        u32DramValue[i] = *(pu32Start + i);

    // 3. bdma attack
    u32BdmaStart = (u32Start & TEST_OFFSET_MASK) + u32MiuOffset;
    for (i = 0; i < (TEST_RANGE/TEST_OFFSET); i++)
    {
        u32BdmaStart += TEST_OFFSET;
        if (isOverlapUboot(u32BdmaStart, u32Size))
            continue;
        // bdma source is not important, just fill it with reasonable address
        MDrv_BDMA_CopyHnd(0x20000, u32BdmaStart, u32Size, eBdmaCpyType, 0);
    }
    flush_cache(u32Start, u32Size); // necessary, or the value would be kept in cache

    // 4. check whether the region is protected or not
    for (i = 0; i < sizeof(u32DramValue)/sizeof(MS_U32); i++)
    {
        if (u32DramValue[i] != *(pu32Start + i))
        {
            failed = 1;
            break;
        }
    }

    if (failed)
    {
        printf("[PROTECT ERROR], fail at address 0x%p \n", pu32Start + i);
        return return_or_block(-1);
    }
    else
    {
        printf("[PROTECT INFO], pass at address 0x%X, size 0x%X\n", (unsigned int)u32Start, (unsigned int)u32Size);
        return 0;
    }
}

static MS_U32 isDramExist(MS_U32 u32LxStart)
{
    if (u32LxStart < MIU1_OFFSET)
        return u32DramSize1 ? 1 : 0;
    else
        return u32DramSize2 ? 1 : 0;
}

#define TEST_SIZE (256) // it's enough to test 256 bytes on lx mem head & tail
#endif
void MsApi_kernelProtectBist(void)
{
    #if 0 //jh
    MIU_PortectInfo info;

    if (isDramExist(u32Lx1Start) && u32Lx1Size >= TEST_SIZE)
    {
        write_test_to_lxmem(u32Lx1Start, TEST_SIZE);
        write_test_to_lxmem(u32Lx1Start + u32Lx1Size - TEST_SIZE, TEST_SIZE);
    }
    if (isDramExist(u32Lx2Start) && u32Lx2Size >= TEST_SIZE)
    {
        write_test_to_lxmem(u32Lx2Start, TEST_SIZE);
        write_test_to_lxmem(u32Lx2Start + u32Lx2Size - TEST_SIZE, TEST_SIZE);
    }
    if (isDramExist(u32Lx3Start) && u32Lx3Size >= TEST_SIZE)
    {
        write_test_to_lxmem(u32Lx3Start, TEST_SIZE);
        write_test_to_lxmem(u32Lx3Start + u32Lx3Size - TEST_SIZE, TEST_SIZE);
    }

    MDrv_MIU_GetProtectInfo(0, &info);
    MDrv_MIU_GetProtectInfo(1, &info);
    #endif
}

int do_MsApi_kernelProtectBist(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MsApi_kernelProtectBist();
    return 0;
}


void MsApi_NuttxProtect(MS_U32 u32StartAddr, MS_U32 u32EndAddr)
{
    UBOOT_DEBUG("IN\n");
    
    UBOOT_DEBUG("u32StartAddr=0x%x\n",(unsigned int)u32StartAddr);
    UBOOT_DEBUG("u32EndAddr=0x%x\n",(unsigned int)u32EndAddr);
    MsDrv_NuttxProtect(3,u32StartAddr,u32EndAddr); 

    UBOOT_DEBUG("OK\n");
}

int do_MsApi_NuttxProtect(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
        U32 u32Start=0;
        U32 u32End=0;
        if(argc<3) {
        cmd_usage(cmdtp);
        return -1;
    }
    u32Start=simple_strtoul(argv[1], NULL, 16);  
    u32End=simple_strtoul(argv[2], NULL, 16);  
    UBOOT_DEBUG("u32Start=0x%x\n",u32Start);
        UBOOT_DEBUG("u32End=0x%x\n",u32End);
    MsApi_NuttxProtect(u32Start,u32End); //"protect address" and "protect lenth" must align to 64K
    return 0;
}
