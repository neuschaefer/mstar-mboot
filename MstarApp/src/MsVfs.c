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
#include <watchdog.h>
#include <command.h>
#include <malloc.h>   /* for free() prototype */
#include <stdio.h>
#include <post.h>
#include <ShareType.h>
#include <MsDebug.h>
#include <MsVfs.h>
#include <MsUtility.h>
#include <CusConfig.h>
#include <MsTypes.h>
//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static BOOLEAN bVfsReady=FALSE;
//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#ifdef CONFIG_UBI
int vfs_mount(char *volume)
{
    char *buffer=NULL;
    char *pEnv=NULL;
    char *pStr=NULL;
    char *pStart=NULL;
    char *pEnd=NULL;    
    int ret=-1;
    UBOOT_TRACE("IN\n");

    if(volume==NULL)
    {
        bVfsReady=FALSE;
        UBOOT_ERROR("Input parameter 'volume' is a null pointer\n");
        return -1;
    }

    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        bVfsReady=FALSE;        
        UBOOT_ERROR("malloc buffer fail\n");        
        return -1;
    }
     
    ret=vfs_umount();
    if(ret==-1)
    {
        free(buffer);
        bVfsReady=FALSE;   
        UBOOT_ERROR("umount previous filesystem fail\n");
        return -1;
    }
    
    
    //Assume this volume is in UBI partition
    memset(buffer,0,CMD_BUF);    
    snprintf(buffer,CMD_BUF,"ubi part %s",UBIPART);
    ret=run_command(buffer,0);

    if(ret!=-1)
    {
        memset(buffer,0,CMD_BUF);
        snprintf(buffer,CMD_BUF,"ubifsmount %s",volume);
        UBOOT_DEBUG("cmd=%s\n",buffer);
        ret=run_command(buffer,0);
        if(ret==-1)
        {
            UBOOT_ERROR("ubifsmount fail (Assume this volume is in UBI(or ubi) partition)\n");
        }
        else
        {
            free(buffer);
            bVfsReady=TRUE;              
            UBOOT_TRACE("OK\n");
            return ret;
        }
    }

    
    
    //Check ever partition 
    pEnv=getenv("mtdparts");
    if(pEnv==NULL)
    {
        free(buffer);
        bVfsReady=FALSE;          
        UBOOT_ERROR("No MTD partition\n");
        return ret;
    }
    else
    {
        pStr=malloc(strlen(pEnv)+1);
        if(pStr==NULL)
        {
            free(buffer);
            bVfsReady=FALSE;              
            UBOOT_ERROR("malloc fail\n");
            return ret;
        }
        memset(pStr,0,strlen(pEnv)+1);
        memcpy(pStr,pEnv,strlen(pEnv));
        pStart=pStr;
        while(1)
        {
            pStart=strchr(pStart,'(');
            
            if(pStart==NULL)
            {
                free(buffer);    
                bVfsReady=FALSE;                  
                UBOOT_ERROR("error partition symbol\n");
                return -1;
            }
            else
            {
                UBOOT_DEBUG("pStart=%s\n",pStart);
                pEnd=strchr(pStart,')');
                                
                if(pEnd==NULL)
                {
                    free(buffer);
                    bVfsReady=FALSE;                      
                    UBOOT_ERROR("error partition symbol\n");
                    return -1;
                }
                else
                {
                    UBOOT_DEBUG("pEnd=%s\n",pEnd);
                    *pEnd='\0';
                    memset(buffer,0,CMD_BUF);
                    snprintf(buffer,CMD_BUF,"ubi part %s",pStart+1);
                    UBOOT_DEBUG("cmd=%s\n",buffer);
                    ret=run_command(buffer,0);
                    if(ret!=-1)
                    {
                        memset(buffer,0,CMD_BUF);
                        snprintf(buffer,CMD_BUF,"ubifsmount %s",volume);
                        UBOOT_DEBUG("cmd=%s\n",buffer);
                        ret=run_command(buffer,0);
                        if(ret!=-1)
                        {
                            break;
                        }
                    }
                    pStart=pEnd+1;
                }
            }
        }
    }
    free(buffer); 
    bVfsReady=TRUE;    
    UBOOT_TRACE("OK\n");    
    return 0;
}

int vfs_umount(void)
{
    int ret = 0;
    UBOOT_TRACE("IN\n");
    if(bVfsReady==TRUE)
    {
        ret = run_command("ubifsumount",0);
    }
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("unmount fail\n");
    }
    bVfsReady=FALSE;  
  	return ret;
}



U32 vfs_getsize(char *filedir)
{
    int ret = -1;
	U32 filesize = 0;
    char *buffer=NULL;
    UBOOT_TRACE("IN\n"); 
    if(filedir==NULL)
    {
        UBOOT_ERROR("filedir is a null pointer\n");
        return FALSE;
    }
    if(bVfsReady==FALSE)
    {
        UBOOT_ERROR("filesystem is not mounted\n");
        return FALSE;
    }
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc buffer fail\n");
        return FALSE;
    }
    memset(buffer,0,CMD_BUF);
    
    snprintf(buffer, CMD_BUF, "ubifsfilesize %s 0x%x",filedir,&filesize);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret = run_command(buffer, 0);
    if(ret==-1)
    {
        UBOOT_ERROR("ubifsfilesize %s fail\n",filedir);
        filesize=0;
    }
    else
    {
        UBOOT_TRACE("OK\n");     
    }
    free(buffer);
	return filesize;
}
int vfs_read(void* addr,char* filedir,unsigned int offset,unsigned int size )
{
    int ret = -1;
    char *buffer=NULL;
    UBOOT_TRACE("IN\n");
    
    if(addr==NULL)
    {
        UBOOT_ERROR("addr is a null pointer\n");
        return -1;
    }
    
    if(filedir==NULL)
    {
        UBOOT_ERROR("filedir is a null pointer\n");
        return -1;
    }

    if(bVfsReady==FALSE)
    {
        UBOOT_ERROR("filesystem is not mounted\n");
        return -1;
    }
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc buffer fail\n");
        return -1;
    }
    memset(buffer,0,CMD_BUF);
    snprintf(buffer, CMD_BUF, "ubifspartload %x %s %x %x", (unsigned int)addr, filedir, offset,size);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret = run_command(buffer, 0);
    if(ret==-1)
    {
        UBOOT_ERROR("ubifspartload %s fail\n",filedir);
    }
    else
    {
        UBOOT_TRACE("OK\n"); 
    }
    free(buffer);
	return ret;  
}

int vfs_write(void* addr,char* filedir,unsigned int offset,unsigned int size )
{
    UBOOT_TRACE("IN\n");
    
    if(addr==NULL)
    {
        UBOOT_ERROR("addr is a null pointer\n");
        return -1;
    }
    if(filedir==NULL)
    {
        UBOOT_ERROR("filedir is a null pointer\n");
        return -1;
    }

    if(bVfsReady==FALSE)
    {
        UBOOT_ERROR("filesystem is not mounted\n");
        return -1;
    }
    UBOOT_ERROR("Not implement now\n");
    return -1;
}




#else
static char* mmc_volume = "";
int vfs_mount(char *volume)
{
    int ret = 0;
    UBOOT_TRACE("IN\n");
    mmc_volume = volume;
    UBOOT_INFO("mmc change mount : %s\n",mmc_volume);
    bVfsReady=TRUE;
    UBOOT_TRACE("OK\n");
	return ret;
}

int vfs_umount(void)
{
    int ret = 0;
    UBOOT_TRACE("IN\n");
    mmc_volume = "";
    bVfsReady=FALSE;
    UBOOT_TRACE("OK\n");
	return ret;
}

U32 vfs_getsize(char *filedir)
{
	U32 filesize = 0;
    int ret = 0;
    char *buffer=NULL;
    
    UBOOT_TRACE("IN\n"); 

    if(filedir==NULL)
    {
        UBOOT_ERROR("filedir is a null pointer\n");
        return FALSE;
    }

    if(bVfsReady==FALSE)
    {
        UBOOT_ERROR("filesystem is not mounted\n");
        return FALSE;
    }
    
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc buffer fail\n");
        return FALSE;
    }
    memset(buffer,0,CMD_BUF);    
    //snprintf(cmd, CMD_BUF, "ext4filesize mmc 0:%s %s",mmc_partition,filedir);
    snprintf(buffer, CMD_BUF, "ext4filesize mmc 0:%s %s %x",mmc_volume,filedir,(U32)&filesize);
    UBOOT_DEBUG("cmd=%s\n",buffer);    
    ret=run_command(buffer, 0);
    if(ret==-1)
    {
        UBOOT_DEBUG("ext4filesize mmc fail\n");
        filesize=0;
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }
    free(buffer);
	return filesize;
}

int vfs_read(void* addr,char* filedir,unsigned int offset,unsigned int size )
{
    int ret = -1;
    char *buffer=NULL;
    
    UBOOT_TRACE("IN\n");

    if(addr==NULL)
    {
        UBOOT_ERROR("addr is a null pointer\n");
        return -1;
    }
    
    if(filedir==NULL)
    {
        UBOOT_ERROR("filedir is a null pointer\n");
        return -1;
    }

    if(bVfsReady==FALSE)
    {
        UBOOT_ERROR("filesystem is not mounted\n");
        return -1;
    }
    
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc buffer fail\n");
        return -1;
    }
    memset(buffer,0,CMD_BUF);       
    snprintf(buffer, CMD_BUF, "ext4partload mmc 0:%s %x %s %x %x",mmc_volume, (unsigned int)addr, filedir, offset,size);
    UBOOT_DEBUG("cmd=%s\n",buffer); 
    ret = run_command(buffer, 0);
    if(ret==-1)
    {
      UBOOT_ERROR("ext4load mmc fail\n");
    }
    else
    {
      UBOOT_TRACE("OK\n");
    }
    free(buffer);
	return ret;  
}

int vfs_write(void* addr,char* filedir,unsigned int offset,unsigned int size )
{
    UBOOT_TRACE("IN\n");
    
    if(addr==NULL)
    {
        UBOOT_ERROR("addr is a null pointer\n");
        return -1;
    }
    
    if(filedir==NULL)
    {
        UBOOT_ERROR("filedir is a null pointer\n");
        return -1;
    }

    if(bVfsReady==FALSE)
    {
        UBOOT_ERROR("filesystem is not mounted\n");
        return -1;
    }
    UBOOT_ERROR("Not implement now\n");
    return -1;
}

#endif
