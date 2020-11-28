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


//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <command.h>
#include <drvSERFLASH.h>
#include <ShareType.h>
#include <MsDebug.h>
#include <linux/list.h>
#include <exports.h>
#include <MsSystem.h>
#include <MsApiSpi.h>
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define SPI_PARTITON_NAME_SIZE 32
typedef struct{
    char name[SPI_PARTITON_NAME_SIZE];
    unsigned int num;
    unsigned int offset;
    unsigned int size;
    struct list_head list;
}ST_SPI_PARTITION;

#define ENV_SPI_LAYOUT "mtdparts"
#define SPI_LAYOUT_ID "mtdparts=edb8M-SPI:"
#define MBOOT_PARTITION "MBOOT"
#if 1
#define MAIN_PART_OFFSET "MainPartOffset"
#endif
//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
extern unsigned int cfg_env_offset;

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

static struct list_head spi_partition_list;
static unsigned int partition_list_ready=0;
static unsigned int spi_size=0;
static SERFLASH_Info spiInfo;
//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
int add2MtdPart(char *name,unsigned int size);
int delMtdPart(void);
char *get_next_member_info(char *source, char *name, unsigned int *size);
int parse_mtdpart(void);


//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
int getSpiInfo(SERFLASH_Info *info)
{
    int ret=-1;
    const SERFLASH_Info *temp=NULL;
    UBOOT_TRACE("IN\n");

    if(info==NULL)
    {
        UBOOT_ERROR("The input parameter 'info' is a null pointer\n");
        return ret;
    }

    ret=run_command("spi init",0);
    if(ret==-1)
    {
        UBOOT_ERROR("do 'spi init' fail\n");
        return ret;
    }

    temp=MDrv_SERFLASH_GetInfo();

    if(temp==NULL)
    {
        UBOOT_ERROR("do 'MDrv_SERFLASH_GetInfo' fail\n");
        return ret;
    }
    memcpy(info,temp,sizeof(SERFLASH_Info));

    UBOOT_TRACE("OK\n");
    return 0;
}


int getSpiSize(unsigned int *u32SpiSize)
{
    MS_BOOL ret =0;
    UBOOT_TRACE("IN\n");
    if(spi_size==0)
    {
        ret = MDrv_SERFLASH_DetectSize((MS_U32 *)&spi_size);
        if(ret != TRUE)
        {
           UBOOT_ERROR("detect SPI size fail\n");
           return -1;
        }
     }
    UBOOT_DEBUG("spi_size=0x%x\n",spi_size);
    *u32SpiSize=(unsigned int)spi_size;

    UBOOT_TRACE("OK\n");
    return 0;
}



int init_spi_partition(void)
{
    int ret=0;
    UBOOT_TRACE("IN\n");
    INIT_LIST_HEAD(&spi_partition_list);
    partition_list_ready=1;

    ret=getSpiInfo(&spiInfo);
    if(ret!=0)
    {
        UBOOT_ERROR("get spi info fail\n");
        return -1;
    }

    parse_mtdpart();

    ret=add_mboot_partition();

    if(ret!=0)
    {
        UBOOT_ERROR("Add MBoot partition fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}


int add_mboot_partition(void)
{
   int ret=0;
   unsigned int uboot_rom_end=0;

   UBOOT_TRACE("IN\n");
   unsigned size = 0;




   ret=MsApiChunkHeader_GetValue(CH_UBOOT_ROM_END,&uboot_rom_end);
   if(ret!=0)
   {
       UBOOT_ERROR("get the end rom address of uboot fail\n");
       return -1;
   }
   UBOOT_DEBUG("The end rom address of uboot is 0x%x\n",uboot_rom_end);

#if CONFIG_LOGO_STORE_IN_MBOOT
    {
        unsigned int u32LogoOffset=0;
        unsigned int u32LogoSize=0;
        unsigned int u32UbootOffset=0;
        const unsigned int U32SPIBANKSIZE = 0x10000; // 64KB

        ret=MsApiChunkHeader_GetValue(CH_LOGO_ROM_OFFSET,&u32LogoOffset);
        if(ret!=0)
        {
            UBOOT_ERROR("Get u32LogoOffset fail\n");
            return -1;
        }
        u32UbootOffset = uboot_rom_end-SPI_FLAS_BASE_ADDRESS; // NOTE: should be less then SPI size
        UBOOT_INFO("u32UbootOffset: 0x%x\n", u32UbootOffset);
        if((u32LogoOffset > u32UbootOffset)&&((u32LogoOffset-u32UbootOffset)<U32SPIBANKSIZE)) // NOTE: LOGO is in the neighbor bank of u-boot
        {
            unsigned int u32BankCnt = 0;
            ret=MsApiChunkHeader_GetValue(CH_LOGO_ROM_SIZE,&u32LogoSize);
            if(ret!=0)
            {
                UBOOT_ERROR("Get u32LogoSize fail\n");
                return -1;
            }
            u32BankCnt = 1;
            u32BankCnt += (u32LogoSize/U32SPIBANKSIZE);
            UBOOT_INFO("%s: u32LogoSize: 0x%x, at %d\n", __func__, u32LogoSize, __LINE__);
            UBOOT_INFO("%s: u32BankCnt: 0x%x, at %d\n", __func__, u32BankCnt, __LINE__);
            size = u32UbootOffset+(U32SPIBANKSIZE*u32BankCnt);
            ret=add_partition(MBOOT_PARTITION ,u32UbootOffset+(U32SPIBANKSIZE*u32BankCnt));
        }
    }
#else
   size = uboot_rom_end-SPI_FLAS_BASE_ADDRESS;
   ret=add_partition(MBOOT_PARTITION,uboot_rom_end-SPI_FLAS_BASE_ADDRESS);
#endif

   if(ret!=0)
   {
       UBOOT_ERROR("set partition '%s' fail\n",MBOOT_PARTITION); 
       return -1;
   }

#if 1 //SET MAIN PARTITION OFFSET IN ENV
       
       //alignment to block size
       UBOOT_DEBUG("origin size=0x%x\n",size);
       if((size%spiInfo.u32SecSize)!=0)
       {
           size+=(spiInfo.u32SecSize-size%spiInfo.u32SecSize);
       }
       UBOOT_DEBUG("final size=0x%x\n",size);

       char *buf=NULL;
       buf=malloc(CMD_BUF);
       if(buf==NULL)
       {
           UBOOT_ERROR("malloc fail\n");
           return -1;
       }
       
       memset(buf,0,CMD_BUF);
       snprintf(buf,CMD_BUF,"setenv %s 0x%x",MAIN_PART_OFFSET, size);
       ret=run_command(buf,0);
       
       if(ret==0)
       {
           UBOOT_TRACE("OK\n");
       }
       else
       {
           UBOOT_ERROR("Set %s Failed.\n", MAIN_PART_OFFSET);

       }
       free(buf);
#endif



   UBOOT_TRACE("OK\n");
   return 0;
}
int add_partition(char *name, unsigned size)
{
    int ret=0;
    unsigned int _spi_size=0;
    unsigned int cur_offset=0;
    unsigned int last_num=0;
    ST_SPI_PARTITION *stSpiPartition=NULL;
    UBOOT_TRACE("IN\n");

    if(partition_list_ready==0)
    {
        UBOOT_ERROR("spi partition list is not ready\n");
        return -1;
    }

    if(name==NULL)
    {
        UBOOT_ERROR("'name' is a null pointer\n");
        return -1;
    }

    if(size==0)
    {
        UBOOT_ERROR("The size of 0x%x is zero\n",size);
        return -1;
    }

    if((strlen(name)+1)>SPI_PARTITON_NAME_SIZE)
    {
        UBOOT_ERROR("The length of %s is over 0x%x\n",name,SPI_PARTITON_NAME_SIZE);
        return -1;
    }

    //alignment to block size
    UBOOT_DEBUG("origin size=0x%x\n",size);
    if((size%spiInfo.u32SecSize)!=0)
    {
        size+=(spiInfo.u32SecSize-size%spiInfo.u32SecSize);
    }
    UBOOT_DEBUG("final size=0x%x\n",size);

    ret=getSpiSize(&_spi_size);
    if(ret!=0)
    {
        UBOOT_ERROR("get spi's size fail\n");
        return -1;
    }

    if(size>_spi_size)
    {
        UBOOT_ERROR("This partition size is larger than this SPI size\n");
        return -1;
    }
    //Check if this partition exist or not
     list_for_each_entry(stSpiPartition,&spi_partition_list,list)
     {
         UBOOT_DEBUG("stSpiPartition->name=%s\n",stSpiPartition->name);
         if(strcmp(stSpiPartition->name,name)==0)
         {
             UBOOT_ERROR("This partition alraedy exist\n");
             return -1;
         }
         cur_offset+=stSpiPartition->size;
         last_num=stSpiPartition->num;
     }


    //Check whether or not the total size is over the SPI size.
    UBOOT_DEBUG("cur_offset=0x%x\n",cur_offset);
    if((cur_offset+size)>_spi_size)
    {
        UBOOT_ERROR("The total size is over the size of this SPI\n");
        return -1;
    }
#if (1!=CONFIG_MINIUBOOT)
    //if the partition area overlay the env area?
    if((cur_offset+size)>cfg_env_offset)
    {
        UBOOT_ERROR("The partition area overlay the env area\n");
        return -1;
    }
#endif
    //Create a partition info for this new partition
    stSpiPartition=malloc(sizeof(ST_SPI_PARTITION));
    if(stSpiPartition==NULL)
    {
        UBOOT_ERROR("malloc for stSpiPartition fail\n");
        return -1;
    }
    memset(stSpiPartition,0,sizeof(ST_SPI_PARTITION));

    ret=add2MtdPart(name,size);
    if(ret!=0)
    {
        free(stSpiPartition);
        UBOOT_ERROR("edit env 'mtdpart' fail\n");
        return -1;
    }

    INIT_LIST_HEAD(&stSpiPartition->list);
    strcpy(stSpiPartition->name,name);
    stSpiPartition->offset=cur_offset;
    stSpiPartition->size=size;
    stSpiPartition->num=last_num+1;
    UBOOT_DEBUG("stSpiPartition->name=%s\n",stSpiPartition->name);
    UBOOT_DEBUG("stSpiPartition->offset=0x%x\n",stSpiPartition->offset);
    UBOOT_DEBUG("stSpiPartition->size=0x%x\n",stSpiPartition->size);
    UBOOT_DEBUG("stSpiPartition->num=0x%x\n",stSpiPartition->num);
    list_add_tail(&stSpiPartition->list,&spi_partition_list);


    UBOOT_TRACE("OK\n");
    return 0;
}

int del_all_partitions(void)
{
    ST_SPI_PARTITION *stSpiPartition=NULL;

    UBOOT_TRACE("IN\n");

    if(partition_list_ready==0)
    {
        UBOOT_ERROR("spi partition list is not ready\n");
        return -1;
    }

    if(list_empty(&spi_partition_list)==1)
    {
        UBOOT_INFO("no partition\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }

    while(list_empty(&spi_partition_list)!=1)
    {
        stSpiPartition=list_entry(spi_partition_list.next, ST_SPI_PARTITION, list);
        UBOOT_DEBUG("delete %s\n",stSpiPartition->name);
        list_del(&stSpiPartition->list);
        free(stSpiPartition);
    }

    if(delMtdPart()!=0)
    {
        UBOOT_ERROR("delete all partitions infor fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}
int del_partition(char *name)
{
    ST_SPI_PARTITION *stSpiPartition=NULL;
    char exist=0;
    UBOOT_TRACE("IN\n");

    if(name==NULL)
    {
        UBOOT_ERROR("'name' is a null pointer\n");
        return -1;
    }

    if(partition_list_ready==0)
    {
        UBOOT_ERROR("spi partition list is not ready\n");
        return -1;
    }

    if(list_empty(&spi_partition_list)==1)
    {
        UBOOT_ERROR("no partition\n");
        return -1;
    }

    list_for_each_entry(stSpiPartition,&spi_partition_list,list)
    {
        if(strcmp(stSpiPartition->name,name)==0)
        {
            exist=1;
            break;
        }
    }
    if(exist==1)
    {
        UBOOT_DEBUG("%s exist in the partition list\n",name);
        list_del(&stSpiPartition->list);
        free(stSpiPartition);
        UBOOT_TRACE("OK\n");
        return 0;
    }
    else
    {
        UBOOT_ERROR("This partition doesn't exist\n");
        return -1;
    }

}

int list_partition(void)
{
    ST_SPI_PARTITION *stSpiPartition=NULL;
    UBOOT_TRACE("IN\n");
    if(partition_list_ready==0)
    {
        UBOOT_ERROR("spi partition list is not ready\n");
        return -1;
    }

    if(list_empty(&spi_partition_list)==1)
    {
        UBOOT_ERROR("no partition\n");
        return -1;
    }

    UBOOT_INFO("The partiton layout in SPI\n");
    UBOOT_INFO("num     name    offset      size\n");

    list_for_each_entry(stSpiPartition,&spi_partition_list,list)
    {
        //UBOOT_INFO("num     name    offset      size\n");
          UBOOT_INFO("%d     %s     0x%x    0x%x\n",stSpiPartition->num,stSpiPartition->name,stSpiPartition->offset,stSpiPartition->size);
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int get_spi_partition_info(char *name, unsigned int *offset, unsigned int *size)
{
    ST_SPI_PARTITION *stSpiPartition=NULL;
    char exist=0;
    UBOOT_TRACE("IN\n");

    if(name==NULL)
    {
        UBOOT_ERROR("'name' is a null pointer\n");
        return -1;
    }

    if(offset==NULL)
    {
        UBOOT_ERROR("'offset' is a null pointer\n");
        return -1;
    }

    if(size==NULL)
    {
        UBOOT_ERROR("'size' is a null pointer\n");
        return -1;
    }

    if(list_empty(&spi_partition_list)==1)
    {
        UBOOT_ERROR("no partition\n");
        return -1;
    }

    list_for_each_entry(stSpiPartition,&spi_partition_list,list)
    {
        if(strcmp(stSpiPartition->name,name)==0)
        {
            exist=1;
            break;
        }
    }
    if(exist==1)
    {
        *offset=stSpiPartition->offset;
        *size=stSpiPartition->size;
        UBOOT_TRACE("OK\n");
        return 0;
    }
    else
    {
        UBOOT_ERROR("%s doesn't exist\n",name);
        return -1;
    }

}

int add2MtdPart(char *name,unsigned int size)
{
    #define MTD_LAYOUT_SIZE 512
    char *pEnv=NULL;
    char *mtdlayout=NULL;
    char env_exist=0;
    UBOOT_TRACE("IN\n");
    if(name==NULL)
    {
        UBOOT_ERROR("'name' is a null pointer\n");
        return 0;
    }

    if(size==0)
    {
        UBOOT_ERROR("The size of partition is zero\n");
        return -1;
    }

    if((strlen(name)+1)>SPI_PARTITON_NAME_SIZE)
    {
        UBOOT_ERROR("The length of %s is over 0x%x\n",name,SPI_PARTITON_NAME_SIZE);
        return -1;
    }

    mtdlayout=malloc(MTD_LAYOUT_SIZE);
    if(mtdlayout==NULL)
    {
        UBOOT_ERROR("malloc for mtdlayout fail\n");
        return -1;
    }
    memset(mtdlayout,0,MTD_LAYOUT_SIZE);

    pEnv=getenv(ENV_SPI_LAYOUT);
    if(pEnv==NULL)
    {
        snprintf(mtdlayout,MTD_LAYOUT_SIZE,"%s",SPI_LAYOUT_ID);
        env_exist=1;
    }
    else
    {
        strncpy(mtdlayout,pEnv,strlen(pEnv)+1);
    }

    if(strstr(mtdlayout,name)!=NULL)
    {
        free(mtdlayout);
        UBOOT_DEBUG("%s exist in mtdparts\n",name);
        UBOOT_TRACE("OK\n");
        return 0;
    }

    UBOOT_DEBUG("mtdparts=%s\n",mtdlayout);
    //Add a ','
    if(env_exist==0)
    {
       snprintf(mtdlayout,MTD_LAYOUT_SIZE,"%s,",mtdlayout);
    }
#if 0
    if((size/1024)/1024) // size is larger than 1MBytes
    {
        snprintf(mtdlayout,MTD_LAYOUT_SIZE,"%s%dm(%s)",mtdlayout,((size/1024)/1024),name);
    }
    else
#endif
    if((size/1024)) // size is larger than 1KBytes
    {
        snprintf(mtdlayout,MTD_LAYOUT_SIZE,"%s%dk(%s)",mtdlayout,((size/1024)),name);
    }
    else
    {
        snprintf(mtdlayout,MTD_LAYOUT_SIZE,"%s%d(%s)",mtdlayout,(size),name);
    }
    UBOOT_DEBUG("mtdparts=%s\n",mtdlayout);

    setenv(ENV_SPI_LAYOUT,mtdlayout);
    free(mtdlayout);

    UBOOT_TRACE("OK\n");
    return 0;
}

int delMtdPart(void)
{
    char *buf=NULL;
    int ret=0;
    UBOOT_TRACE("IN\n");
    buf=malloc(CMD_BUF);
    if(buf==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(buf,0,CMD_BUF);
    snprintf(buf,CMD_BUF,"setenv %s",ENV_SPI_LAYOUT);
    ret=run_command(buf,0);
    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("delet %s fail\n",ENV_SPI_LAYOUT);
    }
    free(buf);

    return 0;
}

int parse_mtdpart(void)
{
    char member_name[SPI_PARTITON_NAME_SIZE];
    unsigned int member_size=0;
    char *pEnv=NULL;
    char *p1=NULL, *p2=NULL;
    int ret=0;

    UBOOT_TRACE("IN\n");
    if(partition_list_ready==0)
    {
        UBOOT_ERROR("partition_list_ready=0\n");
        return -1;
    }
    pEnv=getenv(ENV_SPI_LAYOUT);
    if(pEnv==NULL)
    {
        UBOOT_ERROR("get env '%s' fail\n",ENV_SPI_LAYOUT);
        return -1;
    }
    p1=malloc(strlen(pEnv)+1);
    if(p1==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    p2=p1;
    memset(p1,0,strlen(pEnv)+1);
    strcpy(p1,pEnv);
    UBOOT_DEBUG("p1=%s\n",p1);
    while((p1=get_next_member_info(p1,member_name,&member_size))!=NULL)
    {
        ret=add_partition(member_name,member_size);
        if(ret!=0)
        {
            free(p2);
            UBOOT_ERROR("parse mtdpart fail\n");
            return -1;
        }
    }

    free(p1);
    UBOOT_TRACE("OK\n");
    return 0;
}


char *get_next_member_info(char *source, char *name, unsigned int *size)
{
    char *pS=NULL;
    char *pE=NULL;
    char *pSize=NULL;
    char *pName=NULL;
    char *p=NULL;
    UBOOT_TRACE("IN\n");
    if(source==NULL)
    {
        UBOOT_ERROR("'source' is a null pointer\n");
        return NULL;
    }

    if(size==NULL)
    {
        UBOOT_ERROR("'source' is a null pointer\n");
        return NULL;
    }

    //avoid mtdparts=xxxx:
    if(strchr(source,':')!=NULL)
    {
       source=strchr(source,':');
       source+=1;
    }
    else
    {
        //avoid mtdparts=xxxx:5M(KL),2M(RFS),.....
        if(strchr(source,',')!=NULL)
        {
           source=strchr(source,',');
           source+=1;
        }
    }

    pS=strchr(source,'(');
    if(pS==NULL)
    {
        UBOOT_DEBUG("No symbol '('\n");
        return NULL;
    }

    pE=strchr(source,')');
    if(pS==pE)
    {
        UBOOT_DEBUG("No symbol ')'\n");
        return NULL;
    }

    *pE='\0';
    *pS='\0';

    pName=pS+1;
    UBOOT_DEBUG("member name =%s\n",pName);
    pSize=source;
    UBOOT_DEBUG("member size =%s\n",pSize);
    if((strchr(pSize,'m')!=NULL)||(strchr(pSize,'M')!=NULL))
    {

         p=(char *)((unsigned int)pSize+strlen(pSize));
        *p='\0';
        *size=simple_strtol(pSize, NULL,10);
        UBOOT_DEBUG("size=0x%xMBytes\n",*size);
        *size=(*size<<20);

    }
    else if ((strchr(pSize,'k')!=NULL)||(strchr(pSize,'K')!=NULL))
    {
         p=(char *)((unsigned int)pSize+strlen(pSize));
        *p='\0';
        *size=simple_strtol(pSize, NULL,10);
        UBOOT_DEBUG("size=0x%xKBytes\n",*size);
        *size=(*size<<10);

    }
    else
    {
        *size=simple_strtol(pSize, NULL,10);
    }

    if((strlen(pName)+1)>SPI_PARTITON_NAME_SIZE)
    {
        UBOOT_ERROR("The lenght of partition '%s' is over 0x%x\n",pName,SPI_PARTITON_NAME_SIZE);
        return NULL;
    }
    strcpy(name,(const char *)pName);

    UBOOT_TRACE("OK\n");
    return (pE+1);
}

