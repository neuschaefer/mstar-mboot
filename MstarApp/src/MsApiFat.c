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
#include <linux/list.h>
#include <s_record.h>
#include <exports.h> // MStar
#include <net.h>
#include <ata.h>
#include <part.h>
#include <fat.h>
#include <MsApiFat.h>
#include <MsDebug.h>

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define MAX_FILE_NUMBER 200
#define MAX_FILE_INFO_DATA_BASE_SIZE (MAX_FILE_NUMBER*MAX_FILE_NAME_LENGTH)



//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static ST_FILE_INFO fileList[MAX_FILE_NUMBER];
static unsigned int totalFileNum=0;
//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------

int do_fat_fsfilesize (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    long size=0;
    char buf [12];
    block_dev_desc_t *dev_desc=NULL;
    int dev=0;
    long part=0;
    char *ep=NULL;
    long lPartno = 0;
    char * cPartno = getenv(ENV_PARTNO);
    char* cmd_buf = NULL;
    char bSeekPartition = 1; // flag for seeking all possible partitions of USB
    UBOOT_TRACE("IN\n");    
    
    cmd_buf = (char *)malloc(CMD_BUF_SIZE);

    if(cmd_buf == NULL)
    {
        UBOOT_ERROR("No memory for command buffer!!\n");
        return -1;
    }

    if(cPartno == NULL) {
        part = 1;
        lPartno = 1;
    }
    else {
        lPartno = simple_strtol(cPartno, NULL, 10);
        part = lPartno;
        bSeekPartition = 0;
    }

    if (argc < 4) {
        free(cmd_buf);
        cmd_usage(cmdtp);
        return 1;
    }
    UBOOT_DEBUG("argv[1]=%s,argv[2]=%s,argv[3]=%s\n",argv[1],argv[2],argv[3]);
    
    dev = (int)simple_strtoul (argv[2], &ep, 16);
    dev_desc=get_dev(argv[1],dev);
    if (dev_desc==NULL) {
        free(cmd_buf);
        UBOOT_ERROR ("\n** Invalid boot device **\n");
        return 1;
    }
    UBOOT_DEBUG("*ep=0x%x,part=0x%x\n",(unsigned int)*ep,(unsigned int)part);  
    
    if (*ep) {
        if (*ep != ':') {
            free(cmd_buf);
            UBOOT_ERROR ("\n** Invalid boot device, use `dev[:part]' **\n");
            return 1;
        }
        part = (int)simple_strtoul(++ep, NULL, 16);
    }
    UBOOT_DEBUG("dev_desc=0x%x,part=0x%x\n",(unsigned int)dev_desc,(unsigned int)part);  

    /* We may need to search a proper partition for many times */
    while (1)
    {
        while (fat_register_device(dev_desc,part)!=0)
        {
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if ((bSeekPartition == 0) || (part == lPartno))
            {
                free(cmd_buf);
                UBOOT_ERROR("\n** Unable to use %s %d:%ld for fatfilesize **\n",argv[1],dev,part);
                return 1;
            }
        }

        size = file_fat_filesize (argv[3]);

        if(size == -1)
        {
            UBOOT_INFO("\n** Unable to read \"%s\" from %s %d:%ld **\n",argv[4],argv[1],dev,part);
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if (part == lPartno)
            {
                free(cmd_buf);
                UBOOT_ERROR("\n** Unable to use %s %d:%ld for fatfilesize **\n",argv[1],dev,part);
                return 1;
            }
        }
        else
        {
            if (part != lPartno)
            {
                memset(cmd_buf, 0 , CMD_BUF_SIZE);
                snprintf(cmd_buf, CMD_BUF_SIZE, "setenv %s %ld", ENV_PARTNO, part);
                run_command(cmd_buf, 0); // run_command("setenv partno cPartno");
                saveenv();
            }

            UBOOT_INFO ("\n%ld bytes read\n", size);

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "%lX", size);
            setenv("filesize", buf);
            free(cmd_buf);

            break;
        }
    }
    if(argc==5){
      unsigned int *retSize=NULL;
      retSize=(unsigned int*)simple_strtoul(argv[4], NULL, 16);
      *retSize=size;
    }

    UBOOT_TRACE("OK\n");

    return 0;
}


int do_fat_fspartload (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    long size=0;
    unsigned long offset=0;
    unsigned long count=0;
    unsigned long file_offset=0;
    char buf [12];
    block_dev_desc_t *dev_desc=NULL;
    int dev=0;
    long part=0;
    char *ep=NULL;
    long lPartno = 0;
    char * cPartno = getenv(ENV_PARTNO);
    char* cmd_buf = NULL;
    char bSeekPartition = 1; // flag for seeking all possible partitions of USB

    UBOOT_TRACE("IN\n");    

    cmd_buf = (char *)malloc(CMD_BUF_SIZE);

    if(cmd_buf == NULL)
    {
        UBOOT_ERROR("No memory for command buffer!!\n");
        return -1;
    }

    if(cPartno == NULL) {
        part = 1;
        lPartno = 1;
    }
    else {
        lPartno = simple_strtol(cPartno, NULL, 10);
        part = lPartno;
        bSeekPartition = 0;
    }

    if (argc < 6) {
        free(cmd_buf);
        UBOOT_ERROR ("usage: fatpartload <interface> <dev[:part]> <addr> <filename> <offset> [bytes]\n");
        return 1;
    }
    UBOOT_DEBUG("argv[1]=%s,argv[2]=%s,argv[3]=%s,argv[4]=%s,argv[5]=%s\n",argv[1],argv[2],argv[3],argv[4],argv[4]);
    dev = (int)simple_strtoul (argv[2], &ep, 16);
    dev_desc=get_dev(argv[1],dev);
    if (dev_desc==NULL) {
        free(cmd_buf);
        UBOOT_ERROR ("\n** Invalid boot device **\n");
        return 1;
    }
    if (*ep) {
        if (*ep != ':') {
            free(cmd_buf);
            UBOOT_ERROR ("\n** Invalid boot device, use `dev[:part]' **\n");
            return 1;
        }
        part = (int)simple_strtoul(++ep, NULL, 16);
    }

    /* We may need to search a proper partition for many times */
    while (1)
    {
		while (fat_register_device(dev_desc,part)!=0)
		{
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if ((bSeekPartition == 0) || (part == lPartno))
            {
                free(cmd_buf);
                UBOOT_ERROR("\n** Unable to use %s %d:%ld for fatpartload **\n",argv[1],dev,part);
                return 1;
            }
        }

        offset = simple_strtoul (argv[3], NULL, 16);
        if (argc == 7)
            count = simple_strtoul (argv[6], NULL, 16);
        else
            count = 0;
        file_offset = simple_strtoul (argv[5], NULL, 16);
        size = file_fat_part_read (argv[4], (unsigned char *) offset, file_offset, count);

        if(size == -1)
        {
            UBOOT_INFO("\n** Unable to read \"%s\" from %s %d:%ld **\n",argv[4],argv[1],dev,part);
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if (part == lPartno)
            {
                free(cmd_buf);
                UBOOT_ERROR("\n** Unable to use %s %d:%ld for fatpartload **\n",argv[1],dev,part);
                return 1;
            }
        }
        else
        {
            if (part != lPartno)
            {
                UBOOT_DEBUG("==== part    : %ld =====\n",part);
                UBOOT_DEBUG("==== lPartno : %ld =====\n",lPartno);                
                memset(cmd_buf, 0 , CMD_BUF_SIZE);
                snprintf(cmd_buf, CMD_BUF_SIZE, "setenv %s %ld", ENV_PARTNO, part);
                run_command(cmd_buf, 0); // run_command("setenv partno cPartno");
                saveenv();
            }

            //printf ("\n%ld bytes read\n", size);

            memset(buf, 0 , sizeof(buf));
            snprintf(buf, sizeof(buf), "%lX", size);
            setenv("filesize", buf);
            free(cmd_buf);

            break;
        }
    }
#if !defined(CONFIG_JANUS)
    Chip_Flush_Memory();
#endif

    UBOOT_TRACE("OK\n");
    return 0;
}


int do_fat_fswrite (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //long size;
    unsigned long offset=0;
    unsigned long count=0;
    //char buf [12];
    block_dev_desc_t *dev_desc=NULL;
    int dev=0;
    int part=0;
    char *ep=NULL;
    int fd=0;
    long lPartno = 0;
    char * cPartno = getenv(ENV_PARTNO);

    UBOOT_TRACE("IN\n");

    if(cPartno == NULL) {
        part = 1;
        lPartno = 1;
    }
    else {
        lPartno = simple_strtol(cPartno, NULL, 10);
        part = lPartno;
    }
    

    if (argc < 5) {
        UBOOT_ERROR ("usage: fatwrite <interface> <dev[:part]> <addr> <filename> [bytes]\n");
        return 1;
    }
    UBOOT_DEBUG("argv[1]=%s,argv[2]=%s,argv[3]=%s,argv[4]=%s\n",argv[1],argv[2],argv[3],argv[4]);
    dev = (int)simple_strtoul (argv[2], &ep, 16);
    dev_desc=get_dev(argv[1],dev);
    if (dev_desc==NULL) {
        UBOOT_ERROR ("\n** Invalid boot device **\n");
        return 1;
    }
    UBOOT_DEBUG("*ep=0x%x,part=0x%x\n",(unsigned int)*ep,(unsigned int)part);    
    if (*ep) {
        if (*ep != ':') {
            UBOOT_ERROR ("\n** Invalid boot device, use `dev[:part]' **\n");
            return 1;
        }
        part = (int)simple_strtoul(++ep, NULL, 16);
    }
    if (fat_register_device(dev_desc,part)!=0) {
        UBOOT_ERROR ("\n** Unable to use %s %d:%d for fatwrite **\n",argv[1],dev,part);
        return 1;
    }
    offset = (0 == strncmp(argv[3], UPGRADE_ADDR_STR, strlen(UPGRADE_ADDR_STR))) ? UPGRADE_BUFFER_ADDR : simple_strtoul (argv[3], NULL, 16);
    if (argc == 6)
        count = simple_strtoul (argv[5], NULL, 16);
    else
        count = 0;
    //size = file_fat_writefile (argv[4], (unsigned char *) offset, count);
    fd = file_fat_open(argv[4], "w");
    if (fd < 0) {
        UBOOT_ERROR("\n** Unable to open \"%s\" from %s %d:%d **\n",argv[4],argv[1],dev,part);
        return 1;
    }

    int ret = file_fat_write(fd, (unsigned char *) offset, count);
    file_fat_close(fd);

    if (ret < 0) {
        UBOOT_ERROR("\n** Unable to write \"%s\" from %s %d:%d **\n",argv[4],argv[1],dev,part);
        return 1;
    }

    UBOOT_TRACE("OUT\n");

    return 0;

}

int do_fat_fileList_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    ST_FILE_INFO curr;
    memset(&curr,0,sizeof(curr));
    UBOOT_TRACE("IN\n");
    createfileList("/",&curr);
    UBOOT_INFO("Current file =%s\n",curr.name);

    while(getNextFile(&curr)==0)
    {
        UBOOT_INFO("Next file =%s\n",curr.name);
    }

    while(getPrevFile(&curr)==0)
    {
        UBOOT_INFO("Prev =%s\n",curr.name);
    }

    getFirstFile(&curr);
    UBOOT_INFO("First =%s\n",curr.name);    

    getLastFile(&curr);
    UBOOT_INFO("Last =%s\n",curr.name);    
  
    DeleteFileList();
    UBOOT_TRACE("OK\n");
    return 0;
}

int do_dump_fileList(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int i=0;
    UBOOT_TRACE("IN\n");
    if(argc!=1)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(totalFileNum==0)
    {
        printf("No any files in file list\n");
    }
    else
    {
        for(i=0;i<totalFileNum;i++)
        {
            printf("%s\n",((ST_FILE_INFO *)&fileList[i])->name);
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;
} 

int createfileList(char *path, ST_FILE_INFO *cur)
{
    char cmd_buf[CMD_BUF_SIZE]="\0";
    block_dev_desc_t *dev_desc=NULL;
    char *buf=NULL;
    char *name = NULL;
    char * cPartno = NULL;    
    char *ep=NULL;     
    int ret=0;
    int dev=0;
    int part=0;
    long lPartno = 0;
    ST_FILE_INFO *ptr=NULL;
    
    UBOOT_TRACE("IN\n");
    
    #define DEVICE "0"
    #define INTERFACE "usb"
    
    if(path==NULL)
    {
       UBOOT_ERROR("input parameter 'path' is a null pointer\n");
       return -1;
    }

    if(cur==NULL)
    {
       UBOOT_ERROR("input parameter 'cur' is a null pointer\n");
       return -1;   
    }
    cPartno= getenv(ENV_PARTNO);
    if(cPartno == NULL) {
        part = 1;
        lPartno = 1;
    }
    else {
        lPartno = simple_strtol(cPartno, NULL, 10);
        part = lPartno;
        if (part == 0)//env haven't set
            part = lPartno = 1;
            //bSeekPartition = 0;
	}    
    
     buf=malloc(MAX_FILE_INFO_DATA_BASE_SIZE);
     if(buf==NULL)
     {
         UBOOT_ERROR("malloc fail\n");
         return  -1;
     }
    
    dev = (int)simple_strtoul (DEVICE, &ep, 16);
    dev_desc=get_dev(INTERFACE,dev);
    if (dev_desc==NULL) {
        free(buf);        
        UBOOT_ERROR ("\n** Invalid boot device **\n");
        return  -1;
    }
    UBOOT_DEBUG("*ep=0x%x,part=0x%x\n",(unsigned int)*ep,(unsigned int)part);   
    
    if (*ep) {
        if (*ep != ':') {
            free(buf);            
            UBOOT_ERROR ("\n** Invalid boot device, use `dev[:part]' **\n");
            return  -1;
        }
        part = (int)simple_strtoul(++ep, NULL, 16);
    }
    /* We may need to search a proper partition for many times */
    while (1)
    {
        while (fat_register_device(dev_desc,part)!=0)
        {
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if (part == lPartno)
            {
//                free(cmd_buf);
                memset(cmd_buf, 0 , CMD_BUF_SIZE);
                return  -1;
            }
        }
        
	    UBOOT_DEBUG("path=%s\n",path);
	    ret=file_fat_list(path,buf,MAX_FILE_INFO_DATA_BASE_SIZE);
	    if(ret!=0)
	    {
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if (part == lPartno)
            {
		        free(buf);    
		        UBOOT_ERROR("dofatls fail\n");
		        return  -1;
		    }
        }
        else
        {
            if (part != lPartno)
            {

                memset(cmd_buf, 0 , CMD_BUF_SIZE);
                snprintf(cmd_buf, CMD_BUF_SIZE, "setenv %s %ld", ENV_PARTNO, part);
                run_command(cmd_buf, 0); // run_command("setenv partno cPartno");
                saveenv();
            }
            break;
        }
    }

    memset(fileList,0,sizeof(fileList));
    totalFileNum=0;
    name=buf;
    while(1)
    {
        if(strlen(name)==0)
        {
            break;
        }
        
        ptr=(ST_FILE_INFO *)&fileList[totalFileNum];
        if(strlen(name)>MAX_FILE_NAME_LENGTH)
        {
            UBOOT_DEBUG("%s, string lenght is larger than buffer\n",name);
            memcpy((void *)ptr->name,name,MAX_FILE_NAME_LENGTH-1);
        }
        else
        {
            UBOOT_DEBUG("%s\n",name);
            memcpy((void *)ptr->name,name, MAX_FILE_NAME_LENGTH);
        }
        ptr->idx=totalFileNum;
        totalFileNum++;
        name=name+strlen(name)+1;
    }
    UBOOT_DEBUG("totalFileNum=%d\n",totalFileNum);
  
    free(buf);
    
    memcpy(cur, (ST_FILE_INFO *)&fileList[0], sizeof(ST_FILE_INFO));

    UBOOT_DEBUG("first->idx=%d, first->name=%s\n",cur->idx,cur->name);      
    
    UBOOT_TRACE("OUT\n");

    return 0;

}


int getFirstFile(ST_FILE_INFO *cur)
{
    
    UBOOT_TRACE("IN\n");
    if(cur==0)
    {
       UBOOT_ERROR("input parameter 'cur' is null\n");
       return -1;
    }
    memcpy(cur, (ST_FILE_INFO *)&fileList[0], sizeof(ST_FILE_INFO));
    
    UBOOT_DEBUG("first->idx=%d, first->name=%s\n",cur->idx,cur->name);    
    UBOOT_TRACE("OK\n");   

    return 0;    
}

int getLastFile(ST_FILE_INFO *cur)
{
    UBOOT_TRACE("IN\n");
    if(cur==0)
    {
       UBOOT_ERROR("input parameter 'cur' is null\n");
       return -1;
    }
    memcpy(cur, (ST_FILE_INFO *)&fileList[totalFileNum-1], sizeof(ST_FILE_INFO));

    UBOOT_DEBUG("last->idx=%d, last->name=%s\n",cur->idx,cur->name);
    UBOOT_TRACE("OK\n");   

    return 0;     
}

int getNextFile(ST_FILE_INFO *cur)
{   
    ST_FILE_INFO *ptr=NULL;
    
    UBOOT_TRACE("IN\n");

    if(cur==0)
    {
        UBOOT_ERROR("input parameter 'cur' is null\n");
        return -1;
    }
    
    UBOOT_DEBUG("cur->idx=%d,cur->name=%s\n",cur->idx,cur->name);

    if(totalFileNum==0)
    {
        UBOOT_ERROR("No file in file list\n");
        return -1;
    }
    
    if(cur->idx == (totalFileNum-1))
    {
        UBOOT_INFO("No next file in file list\n");
        return 1;
    }
    else
    {
        ptr=(ST_FILE_INFO *)&fileList[cur->idx+1];
    }

    if(strlen(ptr->name)==0)
    {
        UBOOT_ERROR("invalid file length\n");
        return -1;
    }
    
    memcpy(cur,ptr,sizeof(ST_FILE_INFO));

    UBOOT_DEBUG("next->idx=%d, next->name=%s\n",cur->idx,cur->name);
    
    UBOOT_TRACE("OK\n");   

    return 0;
}

int getPrevFile(ST_FILE_INFO *cur)
{
    ST_FILE_INFO *ptr=NULL;
    UBOOT_TRACE("IN\n");
    
    if(cur==0)
    {
        UBOOT_ERROR("input parameter 'cur' is null\n");
        return -1;
    }

    if(totalFileNum==0)
    {
        UBOOT_ERROR("No file in file list\n");
        return -1;
    }

    UBOOT_DEBUG("cur->idx=%d,cur->name=%s\n",cur->idx,cur->name);   

    if(cur->idx == 0)
    {
        UBOOT_INFO("No previous file in file list\n");
        return 1;
    }
    else
    {
        ptr=(ST_FILE_INFO *)&fileList[cur->idx-1];
    }

    if(strlen(ptr->name)==0)
    {
        UBOOT_ERROR("invalid file length\n");
        return -1;
    }
    memcpy(cur,ptr,sizeof(ST_FILE_INFO));

    UBOOT_DEBUG("prev->idx=%d, prev->name=%s\n",cur->idx,cur->name);

    UBOOT_TRACE("OK\n");   

    return 0;        
 
}

int DeleteFileList(void)
{
    UBOOT_TRACE("IN\n");
    memset(fileList,0,sizeof(fileList));
    totalFileNum=0;
    UBOOT_TRACE("OK\n");  
    return 0;
}


