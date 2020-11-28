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
#include <config.h>
#include <fat.h>
#include <asm/byteorder.h>
#include <part.h>
#include <configs/uboot_module_config.h>
#include <malloc.h>

#define ENV_PARTNO          "partno"
#define MAX_FAT_PARTNO      10 // support 10 partitions
#define CMD_BUF_SIZE        20

extern int fileNum ,lookup ,jffs2Num ;

__u8 g_enable_fatbuf;         /* fatbuf enable flag, used by usb start */
__u32 g_current_fatbuf[FATMEMBUFSIZE];          /* store mem fat for next fat operation */
__u32 g_last_entry=0;               /* used by getfree_cluster */
__u32 g_fatbuf_startblock=0;     /* mem fat start block offset */


#if 1

extern int strcmp(const char * cs,const char * ct);
extern char * strncpy(char * dest,const char *src,size_t count);
extern int snprintf(char *str, size_t size, const char *fmt, ...);

/*
 * Convert a string to lowercase.
 */
static void
downcase(char *str)
{
    while (*str != '\0') {
        TOLOWER(*str);
        str++;
    }
}

/*
 * Convert a string to lowercase.
 */
static void
upcase(char *str)
{
    while (*str != '\0') {
        TOHIGHER(*str);
        str++;
    }
}

static  block_dev_desc_t *cur_dev = NULL;
static unsigned long part_offset = 0;
static int cur_part = 1;

#define DOS_PART_TBL_OFFSET     0x1be
#define DOS_PART_MAGIC_OFFSET   0x1fe
#define DOS_FS_TYPE_OFFSET      0x36
#if 0 // for jffs2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function is to match filename
// [in] char * l_name  is filename pointer
// return 0 is not match
// return 1 is match
// date: 2009/08/17
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int validate_script_ready(char * l_name)
{
   int ret = 0;
   int i=0,j=0;
   char * const_filename[] ={
    "[[application_usb",
    "[[chakra_usb",
    "[[conf_usb",
    "[[font_usb",
    "[[kernel_usb",
    "[[opt_usb",
    "[[rootfs_usb",
    "[[vendor_usb",
    "set_config_usb",
    "usb_auto_update.txt",
    NULL
    };
   for(i=0;i<10;i++)
    {
       j = strcmp(l_name,const_filename[i]);
       if(j==0)
        {
           lookup++;
           ret = 1;
           break;

        }
    }

   return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function is to match filename
// [in] char * l_name  is filename pointer
// return 0 is not match
// return 1 is match
// date: 2009/08/17
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int validate_image_ready(char * l_name)
{
   int ret = 0;
   int i,j;
   char * const_filename[] ={
    "application.jffs2",
    "chakra.jffs2",
    "conf.jffs2",
    "font.jffs2",
    "opt.jffs2",
    "res.bin",
    "rootfs.jffs2",
    "uimage.lzo",
    "vendor.jffs2",
    NULL
    };
   for(i=0;i<9;i++)
    {
       j = strcmp(l_name,const_filename[i]);
       if(j==0)
        {
           jffs2Num++;
           ret = 1;
           break;

        }
    }

   return ret;
}
#endif

int disk_read (__u32 startblock, __u32 getsize, __u8 * bufptr)
{
    FAT_DPRINT("disk_read(%d, %d, %p)\n", startblock, getsize, bufptr);

    startblock += part_offset;
    if (cur_dev == NULL)
        return -1;
    if (cur_dev->block_read) {
        return cur_dev->block_read (cur_dev->dev, startblock, getsize, (unsigned long *)bufptr);
    }
    return -1;
}


int disk_write (__u32 startblock, __u32 putsize, __u8 * bufptr)
{
    FAT_DPRINT("disk_write(%d, %d, %p)\n", startblock, putsize, bufptr);

    startblock += part_offset;
    if (cur_dev == NULL)
        return -1;
    if (cur_dev->block_write) {
        return cur_dev->block_write(cur_dev->dev, startblock, putsize, (unsigned long *)bufptr);
    }
    return -1;
}

/* If single partition, only support FAT32 */
static inline int is_partition_supported(unsigned char *buf)
{
    return ((buf[3]=='M' && buf[4]=='S' && buf[5]=='D' && buf[6]=='O') ||
        (buf[3]=='M' && buf[4]=='S' && buf[5]=='W' && buf[6]=='I') ||
        (buf[3]=='m' && buf[4]=='k' && buf[5]=='d' && buf[6]=='o') ||
        (buf[54]=='F' && buf[55]=='A' && buf[56]=='T') ||
        (buf[82]=='F' && buf[83]=='A' && buf[84]=='T')
        );
}

int
fat_register_device(block_dev_desc_t *dev_desc, int part_no)
{
    unsigned char buffer[MAX_SECTOR_SIZE];

    if (!dev_desc->block_read)
        return -1;
    cur_dev=dev_desc;
    /* check if we have a MBR (on floppies we have only a PBR) */
    if (dev_desc->block_read (dev_desc->dev, 0, 1, (ulong *) buffer) != 1) {
        printf ("** Can't read from device %d **\n", dev_desc->dev);
        return -1;
    }
    if (buffer[DOS_PART_MAGIC_OFFSET] != 0x55 ||
        buffer[DOS_PART_MAGIC_OFFSET + 1] != 0xaa) {
        /* no signature found */
        return -1;
    }

    {
#if 1

#if defined(CONFIG_MAC_PARTITION) || \
    defined(CONFIG_DOS_PARTITION) || \
    defined(CONFIG_ISO_PARTITION) || \
    defined(CONFIG_AMIGA_PARTITION)

        disk_partition_t info;
        if(!get_partition_info(dev_desc, part_no, &info)) {
            part_offset = info.start;
            cur_part = part_no;
        }
        else {
           if(((buffer[0] == 0xEB) || (buffer[0] == 0xE9)) &&
               is_partition_supported(buffer)
               ) {
                /* ok, we assume we are on a PBR only */
                cur_part = 1;
                part_offset=0;
            }
            else
            {
                printf ("** Partition %d not valid on device %d **\n",part_no,dev_desc->dev);
                return -1;
            }
        }
#else
        /* FIXME we need to determine the start block of the
         * partition where the DOS FS resides. This can be done
         * by using the get_partition_info routine. For this
         * purpose the libpart must be included.
         */
        part_offset=32;
        cur_part = 1;
#endif
#else
        /* FIXME we need to determine the start block of the
         * partition where the DOS FS resides. This can be done
         * by using the get_partition_info routine. For this
         * purpose the libpart must be included.
         */
        part_offset=32;
        cur_part = 1;
#endif
    }
    return 0;
}


/*
 * Get the first occurence of a directory delimiter ('/' or '\') in a string.
 * Return index into string if found, -1 otherwise.
 */
static int
dirdelim(char *str)
{
    char *start = str;

    while (*str != '\0') {
        if (ISDIRDELIM(*str)) return str - start;
        str++;
    }
    return -1;
}


/*
 * Extract zero terminated short name from a directory entry.
 */
static void get_name (dir_entry *dirent, char *s_name)
{
    char *ptr=NULL;

    memcpy (s_name, dirent->name, 8);
    s_name[8] = '\0';
    ptr = s_name;
    while (*ptr && *ptr != ' ')
        ptr++;
    if (dirent->ext[0] && dirent->ext[0] != ' ') {
        *ptr = '.';
        ptr++;
        memcpy (ptr, dirent->ext, 3);
        ptr[3] = '\0';
        while (*ptr && *ptr != ' ')
            ptr++;
    }
    *ptr = '\0';
    if (*s_name == DELETED_FLAG)
        *s_name = '\0';
    else if (*s_name == aRING)
        *s_name = DELETED_FLAG;
    downcase (s_name);
}

/* flush the fat buffer into disk */
static long flush_fatent(fsdata *mydata, __u32 bufnum)
{

    __u32 startblock = bufnum * FATBUFBLOCKS - g_fatbuf_startblock;
    __u32 flushsize = mydata->partfatlength - startblock;
    __u8 *buf = (__u8 *) (mydata->fatbuf + startblock * SECTOR_SIZE);

    if(flushsize > FATBUFBLOCKS)
        flushsize = FATBUFBLOCKS;

    if(disk_write(bufnum* FATBUFBLOCKS + mydata->fat_sect, flushsize, buf) < 0) {
        FAT_ERROR("Error writing FAT blocks\n");
        return -1;
    }

    return 0;
}

/* get the cluster descripter location in fat buffer */
static long get_entloc(fsdata *mydata, __u32 entry, __u32 *startblock, __u32 *offset)
{
    __u32 bufnum = 0;

    bufnum = entry / mydata->fatbufsize;
    *offset = entry - bufnum * mydata->fatbufsize;

    if((bufnum * FATBUFBLOCKS < g_fatbuf_startblock) ||
            (bufnum * FATBUFBLOCKS >= g_fatbuf_startblock + mydata->partfatlength)){

        g_fatbuf_startblock = bufnum * FATBUFBLOCKS;
        FAT_DPRINT("re-reading the fat at %x in buf\n", g_fatbuf_startblock);
        if(mydata->fatlength - g_fatbuf_startblock < FATMEMBUFBLOCKS)
            mydata->partfatlength = mydata->fatlength - g_fatbuf_startblock;
        else
            mydata->partfatlength = FATMEMBUFBLOCKS;

        if(!mydata->partfatlength)
            return 1;

        if (disk_read(mydata->fat_sect + g_fatbuf_startblock, mydata->partfatlength, mydata->fatbuf) < 0) {
            FAT_ERROR("Error reading FAT blocks\n");
            return -1;
        }
    }

    *startblock = bufnum * FATBUFBLOCKS - g_fatbuf_startblock;

    return 0;
}

/* set fat buf entry value, return 0 as success */
static long set_fatent(fsdata *mydata, __u32 entry, __u32 value)
{
    __u32 offset=0;
    __u8 *bufptr = NULL;
    __u32 startblock = 0;

    if(get_entloc(mydata,entry, &startblock, &offset) <0)
        return -1;

    bufptr = (__u8 *) (mydata->fatbuf + startblock * SECTOR_SIZE);

    /* set the value to the actual entry of the table */
    if (mydata->fatsize == 32)
        ((__u32 *)bufptr)[offset] = value;
    else if(mydata->fatsize == 16)
        ((__u16 *)bufptr)[offset] = value;
    
    FAT_DPRINT("set_fatent:value: %d\n", value);
    return 0;
}

/*
 * Get the entry at index 'entry' in a memory base FAT (12/16/32) table.
 * On failure 0x00 is returned.
 */
static __u32
get_fatent(fsdata *mydata, __u32 entry)
{
    __u32 offset=0;
    __u32 ret = 0x00;
    __u8 *bufptr = NULL;
    __u32 startblock = 0;

    if(get_entloc(mydata,entry, &startblock, &offset) <0)
        return -1;

    bufptr = (__u8 *) (mydata->fatbuf + startblock * SECTOR_SIZE);

    /* Get the actual entry from the table */
    if (mydata->fatsize == 32)
        ret = FAT2CPU32(((__u32 *)bufptr)[offset]);
    else if(mydata->fatsize == 16)
        ret = FAT2CPU32(((__u16 *)bufptr)[offset]);

    FAT_DPRINT("entry:%d, ret: %d, offset: %d, startblock: %d\n", entry, ret, offset, startblock);

    return ret;
}

/*
 * Get free cluster in memory base FAT
*  getno alway 1
*/
__u32
getfree_cluster(fsdata *mydata, int  * getno)
{
    __u32 u32Result = 0x00;
    __u32 entry = g_last_entry;
    __u32 start_entry = entry;
    __u32 ret = -1;
    __u32 u32foundno = 0;
    __u32 u32lastentry = 0;
    __u8 rollback = 0;
    FAT_DPRINT("getfree_cluster:%d\n", *getno);
    FAT_DPRINT("g_last_entry=%x\n",g_last_entry);
    while(1) {
        /* check if rollbacking to the start to search */
        if(rollback && (entry > start_entry)){
            if(!u32foundno){
                FAT_ERROR("No more free cluster!\n");
                return -1;
            }
            FAT_DPRINT ("Reach the end\n");
            break;
        }

        /* Check if reaching the end */
        if(entry > mydata->entnum){
            if(!u32foundno){
                FAT_DPRINT("meet the bottom, entry=%d\n",entry);
                entry = 0;
                rollback = 1;
                continue;
            }
            FAT_DPRINT ("Reach the end\n");
            break;
        }

        u32Result = get_fatent(mydata,entry);
        FAT_DPRINT("entry=%d, u32Result=%d\n",entry,u32Result);
        if(u32Result < 0)
            return -1;

        if(u32Result == 0x0){  // found a free cluster
            if(u32foundno == 0){
                ret = entry;
                u32lastentry =entry;
            }

            if( entry - u32lastentry > 1 )
                break;

            u32foundno ++;
            u32lastentry = entry;
            if(u32foundno >= *getno)
                break;
        }

        entry++;
    }

    *getno = u32foundno;
    g_last_entry = ret;

    FAT_DPRINT("GOTfree_cluster:%d\n", *getno);
    return ret;
}

/*
 * Clear the files cluster in FAT.
 */
int
clear_fatent(fsdata *mydata, __u32 entry)
{
    __u32 bufnum=0;
    __u32 fatbufnum = -1;
    __u32 u32Result = 0;

    while(1) {
        FAT_DPRINT("entry = %d\n",entry);

        bufnum = entry / mydata->fatbufsize;

        /* Read a new block of FAT entries into the cache. */
        if (bufnum != fatbufnum) {
            if ( fatbufnum > -1) {
                if(flush_fatent(mydata, fatbufnum) < 0)
                    return -1;
            }

            fatbufnum = bufnum;
        }

        u32Result = get_fatent(mydata,entry);
        if(u32Result < 0)
            return -1;

        if(set_fatent(mydata, entry, 0) < 0)
            return -1;

        entry = u32Result;

        if(entry >= mydata->maxfatentry) {
            if(flush_fatent(mydata, fatbufnum) < 0)
                return -1;
            break;
        }

        if(entry > mydata->entnum) {
            FAT_DPRINT ("Reach the end\n");
            break;
        }

    }

    return 0;
}

/*
 * put the entry at index 'entry' in a FAT (12/16/32) table.
 * On failure 0x00 is returned.
 */
static __u32
put_fatent(fsdata *mydata, __u32 entry, __u32 free, int num)
{
    __u32 bufnum=0;
    __u32 fatbufnum = 0;

    if(entry == free) {
        FAT_DPRINT("put_fatent:entry = %x\n",entry);
        bufnum = entry / mydata->fatbufsize;
        if(set_fatent(mydata, entry, mydata->endfatentry) < 0)
            return -1;
        
        if(flush_fatent(mydata, bufnum) < 0)
            return -1;

        return 0;
    }

//old
    fatbufnum = entry / mydata->fatbufsize;

    while(1) {
        FAT_DPRINT("put_fatent:entry=%x, free=%x\n",entry,free);
        if(set_fatent(mydata, entry, free) < 0)
            return -1;

        bufnum = free / mydata->fatbufsize;

        if( fatbufnum != bufnum ) {
            if(flush_fatent(mydata, fatbufnum) < 0)
                return -1;
            fatbufnum = bufnum;
        }

        if(set_fatent(mydata, free, mydata->endfatentry) < 0)
            return -1;

        entry = free;
        free++;
        num--;
        if(num <= 0)
            break;
    }

    if(flush_fatent(mydata, fatbufnum) < 0)
        return -1;

    return 0;
}

static long check_fatbuf(fsdata *mydata)
{
    if(!g_enable_fatbuf)
        g_fatbuf_startblock = 0;

    if(mydata->fatlength - g_fatbuf_startblock < FATMEMBUFBLOCKS)
        mydata->partfatlength = mydata->fatlength - g_fatbuf_startblock;
    else
        mydata->partfatlength = FATMEMBUFBLOCKS;

    FAT_DPRINT("%s:g_enable_fatbuf=%d\n", __func__, g_enable_fatbuf);
    if(!g_enable_fatbuf){
        if (disk_read(mydata->fat_sect, mydata->partfatlength, mydata->fatbuf) < 0) {
            FAT_ERROR("Error reading FAT blocks\n");
            return -1;
        }
        g_enable_fatbuf = 1;
        g_last_entry = 0;
    }

    return 0;
}

/*
 * Read at most 'size' bytes from the specified cluster into 'buffer'.
 * Return 0 on success, -1 otherwise.
 */
static int
get_cluster(fsdata *mydata, __u32 clustnum, __u8 *buffer, unsigned long size)
{
    int idx = 0;
    __u32 startsect=0;

    if (clustnum > 0) {
        startsect = mydata->data_begin + clustnum*mydata->clust_size;
    } else {
        startsect = mydata->rootdir_sect;
    }
    /*show this in the windows add by yanlong.zhang 2009/08/14*/
    FAT_DPRINT("gc - clustnum: %d, startsect: %d\n", clustnum, startsect);

    if (disk_read(startsect, size/FS_BLOCK_SIZE , buffer) < 0) {
        FAT_DPRINT("Error reading data\n");
        return -1;
    }
    if(size % FS_BLOCK_SIZE) {
        __u8 tmpbuf[MAX_SECTOR_SIZE]; // TODO: review, stack size
        memset(tmpbuf,0,sizeof(tmpbuf));
        idx= size/FS_BLOCK_SIZE;
        if (disk_read(startsect + idx, 1, tmpbuf) < 0) {
            FAT_DPRINT("Error reading data\n");
            return -1;
        }
        buffer += idx*FS_BLOCK_SIZE;

        memcpy(buffer, tmpbuf, size % FS_BLOCK_SIZE);
        return 0;
    }

    return 0;
}

/*
 * from get_cluster().
 * Read at most 'size' bytes from the specified cluster into 'buffer'.
 * Return 0 on success, -1 otherwise.
 */
static int
get_part_cluster(fsdata *mydata, __u32 clustnum, __u8 *buffer, unsigned long size, unsigned long offset)
{
    int idx = 0;
    __u32 startsect=0;

    if((offset % FS_BLOCK_SIZE) != 0)
    {
        printf("ERROR: offset(0x%lx) should align to FS_BLOCK_SIZE(0x%lx)\n", offset, FS_BLOCK_SIZE);
        return -1;
    }
    if (clustnum > 0) {
        startsect = mydata->data_begin + clustnum*mydata->clust_size;
    } else {
        startsect = mydata->rootdir_sect;
    }
    /*show this in the windows add by yanlong.zhang 2009/08/14*/
    FAT_DPRINT("gc - clustnum: %d, startsect: %d\n", clustnum, startsect);

    if (disk_read(startsect+(offset/FS_BLOCK_SIZE), (size/FS_BLOCK_SIZE)-(offset/FS_BLOCK_SIZE) , buffer) < 0) {
        FAT_DPRINT("Error reading data\n");
        return -1;
    }
    if(size % FS_BLOCK_SIZE) {
        __u8 tmpbuf[MAX_SECTOR_SIZE]; // TODO: review, stack size
        memset(tmpbuf,0,sizeof(tmpbuf));
        idx= (size/FS_BLOCK_SIZE)-(offset/FS_BLOCK_SIZE);
        if (disk_read(startsect + idx + (offset/FS_BLOCK_SIZE), 1, tmpbuf) < 0) {
            FAT_DPRINT("Error reading data\n");
            return -1;
        }
        buffer += ((size/FS_BLOCK_SIZE)-(offset/FS_BLOCK_SIZE))*FS_BLOCK_SIZE;

        memcpy(buffer, tmpbuf, size % FS_BLOCK_SIZE);
        return 0;
    }

    return 0;
}

/*
 * Read at most 'maxsize' bytes from the file associated with 'dentptr'
 * into 'buffer'.
 * Return the number of bytes read or -1 on fatal errors.
 */
static long
get_contents(fsdata *mydata, dir_entry *dentptr, __u8 *buffer,
         unsigned long maxsize)
{
    unsigned long filesize = FAT2CPU32(dentptr->size), gotsize = 0;
    unsigned int bytesperclust = mydata->clust_size * SECTOR_SIZE;
    __u32 curclust = START(dentptr);
    __u32 endclust=0, newclust=0;
    unsigned long actsize=0;

    FAT_DPRINT("Filesize: %lu bytes\n", filesize);

    if (maxsize > 0 && filesize > maxsize) filesize = maxsize;

    FAT_DPRINT("Reading: %ld bytes\n", filesize);

    actsize=bytesperclust;
    endclust=curclust;
    do {
        /* search for consecutive clusters */
        while(actsize < filesize) {
            newclust = get_fatent(mydata, endclust);
            if((newclust -1)!=endclust)
                goto getit;
            if (CHECK_CLUST(newclust, mydata->fatsize)) {
                FAT_DPRINT("newclust: 0x%x\n", newclust);
                FAT_DPRINT("Invalid FAT entry - 1\n");
                return -1;
                //return gotsize;
            }
            endclust=newclust;
            actsize+= bytesperclust;
        }
        /* actsize >= file size */
        actsize -= bytesperclust;
        /* get remaining clusters */
        if (get_cluster(mydata, curclust, buffer, (int)actsize) != 0) {
            FAT_ERROR("Error reading cluster\n");
            return -1;
        }
        /* get remaining bytes */
        gotsize += (int)actsize;
        filesize -= actsize;
        buffer += actsize;
        actsize= filesize;
        if (get_cluster(mydata, endclust, buffer, (int)actsize) != 0) {
            FAT_ERROR("Error reading cluster\n");
            return -1;
        }
        gotsize+=actsize;
        return gotsize;
getit:
        if (get_cluster(mydata, curclust, buffer, (int)actsize) != 0) {
            FAT_ERROR("Error reading cluster\n");
            return -1;
        }
        gotsize += (int)actsize;
        filesize -= actsize;
        buffer += actsize;
        curclust = get_fatent(mydata, endclust);
        if (CHECK_CLUST(curclust, mydata->fatsize)) {
            FAT_DPRINT("curclust: 0x%x\n", curclust);
            FAT_ERROR("Invalid FAT entry - 2\n");
            return -1;
            //return gotsize;
        }
        actsize=bytesperclust;
        endclust=curclust;
    } while (1);
}

/*
 * Read at most 'maxsize' bytes from the file associated with 'dentptr'
 * into 'buffer'.
 * Return the number of bytes read or -1 on fatal errors.
 */
static long
get_part_contents(fsdata *mydata, dir_entry *dentptr, __u8 *data_buffer, unsigned long file_offset,
         unsigned long maxsize)
{
    unsigned long filesize = FAT2CPU32(dentptr->size), gotsize = 0;
    unsigned int bytesperclust = mydata->clust_size * SECTOR_SIZE;
    __u32 curclust = START(dentptr);
    __u32 endclust=0, newclust=0;
    unsigned long actsize=0;
    __u32 buffer_size = 0; //pseudo_buffer_size
    __u32 file_offset_addr = file_offset;

    FAT_DPRINT("Filesize: %ld bytes\n", filesize);

    if((filesize-file_offset) > maxsize)
    {
        //printf("%s: filesize: 0x%lx, at %d\n", __func__, filesize, __LINE__);
        filesize = file_offset+maxsize;
        //printf("%s: filesize: 0x%lx, at %d\n", __func__, filesize, __LINE__);
    }

    FAT_DPRINT("Reading: %ld bytes\n", filesize);

    actsize=bytesperclust;
    endclust=curclust;
    do {
        /* search for consecutive clusters */
        while(actsize < filesize) {
            newclust = get_fatent(mydata, endclust);
            if((newclust -1)!=endclust)
                goto getit;
            if (CHECK_CLUST(newclust, mydata->fatsize)) {
                FAT_DPRINT("curclust: 0x%x\n", newclust);
                FAT_DPRINT("Invalid FAT entry - 3\n");
                return -1;
                //return gotsize;
            }
            endclust=newclust;
            actsize+= bytesperclust;
        }
        /* actsize >= file size */
        actsize -= bytesperclust;
        /* get remaining clusters */
#if 1
        if((buffer_size+actsize) > file_offset_addr)
        {
            int data_size = actsize;
            unsigned long data_offset = 0;
            if(buffer_size < file_offset_addr)
            {
                data_offset = file_offset_addr - buffer_size;
            }
            if (get_part_cluster(mydata, curclust, data_buffer, data_size, data_offset) != 0) {
                FAT_ERROR("Error reading cluster\n");
                return -1;
            }
            data_buffer += (data_size-data_offset);
        }
#else
        if (get_cluster(mydata, curclust, buffer, (int)actsize) != 0) {
            FAT_ERROR("Error reading cluster\n");
            return -1;
        }
#endif
        /* get remaining bytes */
        gotsize += (int)actsize;
        filesize -= actsize;
        buffer_size += actsize;
        actsize= filesize;
#if 1
        if((buffer_size+actsize) > file_offset_addr)
        {
            int data_size = actsize;
            unsigned long data_offset = 0;
            if(buffer_size < file_offset_addr)
            {
                data_offset = file_offset_addr - buffer_size;
            }
            if (get_part_cluster(mydata, endclust, data_buffer, data_size, data_offset) != 0) {
                FAT_ERROR("Error reading cluster\n");
                return -1;
            }
            data_buffer += (data_size-data_offset);
        }
#else
        if (get_cluster(mydata, endclust, buffer, (int)actsize) != 0) {
            FAT_ERROR("Error reading cluster\n");
            return -1;
        }
#endif
        gotsize+=actsize;
        return gotsize;
getit:
#if 1
        if((buffer_size+actsize) > file_offset_addr)
        {
            int data_size = actsize;
            unsigned long data_offset = 0;
            if(buffer_size < file_offset_addr)
            {
                data_offset = file_offset_addr - buffer_size;
            }
            if (get_part_cluster(mydata, curclust, data_buffer, data_size, data_offset) != 0) {
                FAT_ERROR("Error reading cluster\n");
                return -1;
            }
            data_buffer += (data_size-data_offset);
        }
#else
        if (get_cluster(mydata, curclust, buffer, (int)actsize) != 0) {
            FAT_ERROR("Error reading cluster\n");
            return -1;
        }
#endif
        gotsize += (int)actsize;
        filesize -= actsize;
        buffer_size += actsize;
        curclust = get_fatent(mydata, endclust);
        if (CHECK_CLUST(curclust, mydata->fatsize)) {
            FAT_DPRINT("curclust: 0x%x\n", curclust);
            FAT_ERROR("Invalid FAT entry - 4\n");
            return -1;
            //return gotsize;
        }
        actsize=bytesperclust;
        endclust=curclust;
    } while (1);
}

#ifdef CONFIG_SUPPORT_VFAT
/*
 * Extract the file name information from 'slotptr' into 'l_name',
 * starting at l_name[*idx].
 * Return 1 if terminator (zero byte) is found, 0 otherwise.
 */
static int
slot2str(dir_slot *slotptr, char *l_name, int *idx)
{
    int j=0;

    for (j = 0; j <= 8; j += 2) {
        l_name[*idx] = slotptr->name0_4[j];
        if (l_name[*idx] == 0x00) return 1;
        (*idx)++;
    }
    for (j = 0; j <= 10; j += 2) {
        l_name[*idx] = slotptr->name5_10[j];
        if (l_name[*idx] == 0x00) return 1;
        (*idx)++;
    }
    for (j = 0; j <= 2; j += 2) {
        l_name[*idx] = slotptr->name11_12[j];
        if (l_name[*idx] == 0x00) return 1;
        (*idx)++;
    }

    return 0;
}


/*
 * Extract the full long filename starting at 'retdent' (which is really
 * a slot) into 'l_name'. If successful also copy the real directory entry
 * into 'retdent'
 * Return 0 on success, -1 otherwise.
 */
__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8     get_vfatname_block[MAX_CLUSTSIZE];
static int
get_vfatname(fsdata *mydata, int curclust, __u8 *cluster,
         dir_entry *retdent, char *l_name)
{
    dir_entry *realdent=NULL;
    dir_slot  *slotptr = (dir_slot*) retdent;
    __u8      *nextclust = cluster + mydata->clust_size * SECTOR_SIZE;
    __u8       counter = (slotptr->id & ~LAST_LONG_ENTRY_MASK) & 0xff;
    int idx = 0;

    while ((__u8*)slotptr < nextclust) {
        if (counter == 0) break;
        if (((slotptr->id & ~LAST_LONG_ENTRY_MASK) & 0xff) != counter)
            return -1;
        slotptr++;
        counter--;
    }

    if ((__u8*)slotptr >= nextclust) {
        dir_slot *slotptr2;

#if 0
        slotptr--; // this "--" is not necessary, it exists below while loop
#endif
        curclust = get_fatent(mydata, curclust);
        if (CHECK_CLUST(curclust, mydata->fatsize)) {
            FAT_DPRINT("curclust: 0x%x\n", curclust);
            FAT_ERROR("Invalid FAT entry - 5\n");
            return -1;
        }
        if (get_cluster(mydata, curclust, get_vfatname_block,
                mydata->clust_size * SECTOR_SIZE) != 0) {
            FAT_DPRINT("Error: reading directory block\n");
            return -1;
        }
        slotptr2 = (dir_slot*) get_vfatname_block;
#if 0
        while (slotptr2->id > 0x01) {
#else
        while (slotptr2->id > 0x01 && counter > 0) { // "counter == 0" if the first slot of the next cluster is the real directory entry
#endif
            slotptr2++;
        }
        /* Save the real directory entry */
        if (counter == 0)
        {
            realdent = (dir_entry*)slotptr2;
            slotptr2--;
        }
        else
        {
        realdent = (dir_entry*)slotptr2 + 1;
        }
        while ((__u8*)slotptr2 >= get_vfatname_block) {
            slot2str(slotptr2, l_name, &idx);
            slotptr2--;
        }
    } else {
        /* Save the real directory entry */
        realdent = (dir_entry*)slotptr;
    }

    do {
        slotptr--;
        if (slot2str(slotptr, l_name, &idx)) break;
    } while (!(slotptr->id & LAST_LONG_ENTRY_MASK));

    l_name[idx] = '\0';
    if (*l_name == DELETED_FLAG) *l_name = '\0';
    else if (*l_name == aRING) *l_name = DELETED_FLAG;
    downcase(l_name);

    /* Return the real directory entry */
    memcpy(retdent, realdent, sizeof(dir_entry));

    return 0;
}


/* Calculate short name checksum */
static __u8
mkcksum(const char *str)
{
    int i=0;
    __u8 ret = 0;

    for (i = 0; i < 11; i++) {
        ret = (((ret&1)<<7)|((ret&0xfe)>>1)) + str[i];
    }

    return ret;
}
#endif

//extern U32 KL_Size;
/*
 * Get the directory entry associated with 'filename' from the directory
 * starting at 'startsect'
 */
__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8 get_dentfromdir_block[MAX_CLUSTSIZE];
static dir_entry *get_dentfromdir (fsdata * mydata, int startsect,
                   char *filename, dir_entry * retdent,
                   int dols)
{
    __u16 prevcksum = 0xffff;
    __u32 curclust = START (retdent);
    int files = 0, dirs = 0;
    /*show in the windows*/
    FAT_DPRINT ("get_dentfromdir: %s\n", filename);

    while (1) {
    dir_entry *dentptr=NULL;
    int i=0;
    if (get_cluster (mydata, curclust, get_dentfromdir_block,
         mydata->clust_size * SECTOR_SIZE) != 0) {
        FAT_DPRINT ("Error: reading directory block\n");
        return NULL;
    }
    dentptr = (dir_entry *) get_dentfromdir_block;

    for (i = 0; i < DIRENTSPERCLUST; i++) {

        char s_name[14], l_name[256];

        l_name[0] = '\0';
        if (dentptr->name[0] == DELETED_FLAG) {
            dentptr++;
            continue;
        }
        if ((dentptr->attr & ATTR_VOLUME)) {
#ifdef CONFIG_SUPPORT_VFAT
        if ((dentptr->attr & ATTR_VFAT) &&
            (dentptr->name[0] & LAST_LONG_ENTRY_MASK))
         {
            prevcksum = ((dir_slot *) dentptr)->alias_checksum;

            get_vfatname (mydata, curclust, get_dentfromdir_block,dentptr, l_name);
            if (dols) {
            int isdir = (dentptr->attr & ATTR_DIR);
            char dirc;
            int doit = 0;

            if (isdir) {
                dirs++;
                dirc = '/';
                doit = 1;
            } else {
                dirc = ' ';
                if (l_name[0] != 0) {
                files++;
                doit = 1;
                }
            }
            if (doit) {
                if (dirc == ' ')
                {
#if (ENABLE_MODULE_SECURITY_BOOT)
                    if(strcmp(l_name, "uimage.aes") == 0)
                    {
                        //KL_Size = (long) FAT2CPU32 (dentptr->size);
                        //printf("@@ %ld\n", KL_Size);
                    }
#endif
                    printf (" %8ld   %s%c\n",(long) FAT2CPU32 (dentptr->size),l_name, dirc);//get long file name
#if 0 // for jffs2
                    validate_image_ready(l_name);
                    printf("print the image's number jffs2Num: %d\n", jffs2Num);
                    validate_script_ready(l_name);
                    printf("print the script's number lookup: %d\n",lookup);
#endif
                }
                else
                {
                    printf ("            %s%c\n", l_name, dirc);
                }
            }
            dentptr++;
            continue;
            }
            FAT_DPRINT ("vfatname: |%s|\n", l_name);
        }
        else
#endif
        {
            /* Volume label or VFAT entry */
            dentptr++;
            continue;
        }
        }


        if (dentptr->name[0] == 0) {
        if (dols) {
             printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);//print sub_directory number of file and folderd
        }
        FAT_DPRINT ("Dentname == NULL - %d\n", i);
        return NULL;
        }
#ifdef CONFIG_SUPPORT_VFAT
        if (dols) {
            char str[sizeof(dentptr->name)+sizeof(dentptr->ext)];
            memset(str, 0, sizeof(str));
            memcpy(str, dentptr->name, sizeof(dentptr->name));
            memcpy(str+sizeof(dentptr->name), dentptr->ext, sizeof(dentptr->ext));
            if(mkcksum (str) == prevcksum)
            {
                dentptr++;
                continue;
            }
        }
#endif

        get_name (dentptr, s_name);
        if (dols) {
        int isdir = (dentptr->attr & ATTR_DIR);
        char dirc;
        int doit = 0;

        if (isdir) {
            dirs++;
            dirc = '/';
            doit = 1;
        } else {
            dirc = ' ';
            if (s_name[0] != 0) {
            files++;
            doit = 1;
            }
        }
        if (doit) {
            if (dirc == ' ') {
            printf (" %8ld   %s%c\n",(long) FAT2CPU32 (dentptr->size), s_name,dirc);//s_name is little 8 byte, that is small filename
#if 0 // for jffs2
            validate_image_ready(s_name);
            printf("print the image's number jffs2Num_2: %d\n",jffs2Num);
#endif
            } else {
            printf ("            %s%c\n", s_name, dirc);
            }
        }
        dentptr++;
        continue;
        }
        if (strcmp (filename, s_name) && strcmp (filename, l_name)) {
        FAT_DPRINT ("Mismatch: |%s|%s|\n", s_name, l_name);
        dentptr++;
        continue;
        }
        memcpy (retdent, dentptr, sizeof (dir_entry));
        FAT_DPRINT ("DentName: %s", s_name);
        FAT_DPRINT (", start: 0x%x", START (dentptr));
        FAT_DPRINT (", size:  0x%x %s\n",FAT2CPU32 (dentptr->size),(dentptr->attr & ATTR_DIR) ? "(DIR)" : "");

        return retdent;
    }
    curclust = get_fatent(mydata, curclust);
    if (CHECK_CLUST(curclust, mydata->fatsize)) {
        FAT_DPRINT ("curclust: 0x%x\n", curclust);
        FAT_ERROR ("Invalid FAT entry - 6\n");
        return NULL;
    }
    }

    return NULL;
}

/*
 * Read boot sector and volume info from a FAT filesystem
 */
static int
read_bootsectandvi(boot_sector *bs, volume_info *volinfo, int *fatsize)
{
    __u8 block[MAX_SECTOR_SIZE];
    volume_info *vistart=NULL;
    memset(block,0,sizeof(block));
    if (disk_read(0, 1, block) < 0) {
        FAT_DPRINT("Error: reading block\n");
        return -1;
    }

    memcpy(bs, block, sizeof(boot_sector));
    bs->reserved    = FAT2CPU16(bs->reserved);
    bs->fat_length    = FAT2CPU16(bs->fat_length);
    bs->secs_track    = FAT2CPU16(bs->secs_track);
    bs->heads    = FAT2CPU16(bs->heads);
    bs->cluster_size = FAT2CPU16(bs->cluster_size);
#if 0 /* UNUSED */
    bs->hidden    = FAT2CPU32(bs->hidden);
#endif
    bs->total_sect    = FAT2CPU32(bs->total_sect);

    /* FAT32 entries */
    if (bs->fat_length == 0) {
        /* Assume FAT32 */
        bs->fat32_length = FAT2CPU32(bs->fat32_length);
        bs->flags     = FAT2CPU16(bs->flags);
        bs->root_cluster = FAT2CPU32(bs->root_cluster);
        bs->info_sector  = FAT2CPU16(bs->info_sector);
        bs->backup_boot  = FAT2CPU16(bs->backup_boot);
        vistart = (volume_info*) (block + sizeof(boot_sector));
        *fatsize = 32;
    } else {
        vistart = (volume_info*) &(bs->fat32_length);
        *fatsize = 0;
    }
    memcpy(volinfo, vistart, sizeof(volume_info));
    FAT_DPRINT("fat_length: 0x%x\n", bs->fat_length);
    FAT_DPRINT("fs_type: '%s'\n", vistart->fs_type);

    if (*fatsize == 32) {
        if (strncmp(FAT32_SIGN, vistart->fs_type, SIGNLEN) == 0) {
            return 0;
        }
    } else {
        if (strncmp(FAT12_SIGN, vistart->fs_type, SIGNLEN) == 0) {
            *fatsize = 12;
            return 0;
        }
        if (strncmp(FAT16_SIGN, vistart->fs_type, SIGNLEN) == 0) {
            *fatsize = 16;
            return 0;
        }
    }

    FAT_DPRINT("Error: broken fs_type sign\n");
    return -1;
}

__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8 do_fat_write_block[MAX_CLUSTSIZE];

__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8 do_fat_write_sector[MAX_SECTOR_SIZE * 2];

long do_fat_write (const char *filename, void *buffer, unsigned long maxsize,
         int dols)
{
    int fd=file_fat_open(filename, "w");

    if(fd < 0) {
        FAT_DPRINT ("Error: file open failed\n");
        return -1;
    }

    if(file_fat_write(fd, buffer, maxsize)< 0) {
        FAT_DPRINT ("Error: file write failed\n");
        return -1;
    }

    file_fat_close(fd);

    return 0;

}


__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8 do_fat_part_read_block[MAX_CLUSTSIZE];
long
do_fat_part_read (const char *filename, void *buffer, unsigned long offset, unsigned long maxsize,
         int dols)
{
#if 1 // CONFIG_NIOS /* NIOS CPU cannot access big automatic arrays */
    static
#endif
    char fnamecopy[2048];
    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    //fsdata datablock; //In order to pass converity checking.
    //fsdata *mydata = &datablock; //In order to pass converity checking.
    fsdata *mydata = NULL;
    dir_entry *dentptr=NULL;
    __u16 prevcksum = 0xffff;
    char *subname = "";
    int cursect=0;
    int idx=0, isdir = 0;
    int files = 0, dirs = 0;
    long ret = 0;
    int firsttime=0;
    __u32 cur_cluster=0;

    if(filename == NULL)
    {
        printf("%s: Error: file name is NULL, at %d\n", __func__, __LINE__);
        return 1;
    }
    
    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err2;
    }
    
    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    /* "cwd" is always the root... */
    while (ISDIRDELIM (*filename))
        filename++;
    /* Make a copy of the filename and convert it to lowercase */
    memset(fnamecopy, 0, sizeof(fnamecopy));
    strncpy (fnamecopy, filename, ((sizeof(fnamecopy)-1)<strlen(filename))?(sizeof(fnamecopy)-1):strlen(filename));
    downcase (fnamecopy);// convert it to lowercase

    if (*fnamecopy == '\0') {
        if (!dols){
            goto Err2;
        }
        dols = LS_ROOT;
    }
    else if ((idx = dirdelim (fnamecopy)) >= 0) {
        isdir = 1;
        fnamecopy[idx] = '\0';
        subname = fnamecopy + idx + 1;
        /* Handle multiple delimiters */
        while (ISDIRDELIM (*subname))
            subname++;
    }
    else if (dols) {
        isdir = 1;
    }

    while (1) {
        int i=0;
        if (disk_read (cursect, mydata->clust_size, do_fat_part_read_block) < 0) {
            FAT_DPRINT ("Error: reading rootdir block\n");
            goto Err2;
        }
        dentptr = (dir_entry *) do_fat_part_read_block;/*data is in do_fat_part_read_block*/

#if 0
        for (i = 0; i < DIRENTSPERBLOCK; i++)
#else
        for (i = 0; i < DIRENTSPERBLOCK * (mydata->clust_size); i++)
#endif
        {
            char s_name[14], l_name[256];

            l_name[0] = '\0';

            if((u8)dentptr->name[0]== 0xE5)
            {
                //skip the free dentry slot
                dentptr++;
                continue;
            }


            if ((dentptr->attr & ATTR_VOLUME)) {
#ifdef CONFIG_SUPPORT_VFAT
            if ((dentptr->attr & ATTR_VFAT) &&
                (dentptr->name[0] & LAST_LONG_ENTRY_MASK)) {
                prevcksum = ((dir_slot *) dentptr)->alias_checksum;
#if 0
                get_vfatname (mydata, 0, do_fat_read_block, dentptr, l_name);
#else

                get_vfatname (mydata, cur_cluster, do_fat_part_read_block, dentptr, l_name);
#endif

                if (dols == LS_ROOT) {
                    int isdir = (dentptr->attr & ATTR_DIR);
                    char dirc=0;
                    int doit = 0;

                    if (isdir) {
                        dirs++;
                        dirc = '/';
                        doit = 1;
                    } else {
                        dirc = ' ';
                        if (l_name[0] != 0) {
                            files++;
                            doit = 1;
                        }
                    }
                    if (doit)
                    {
                        if (dirc == ' ') {
                            printf (" %8ld   %s%c\n",
                                (long) FAT2CPU32 (dentptr->size),
                                l_name, dirc);

                        } else {
                            printf ("            %s%c\n", l_name, dirc);
                        }
                    }
                    dentptr++;
                    continue;
                }
                FAT_DPRINT ("Rootvfatname: |%s|\n", l_name);
            }
            else
#endif
            {
                /* Volume label or VFAT entry */
                dentptr++;
                continue;
            }

        }/*   */

      /*this segment is not run*/
        else if (dentptr->name[0] == 0)
        {
            FAT_DPRINT ("RootDentname == NULL - %d\n", i);
            if (dols == LS_ROOT) {
                printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);//root dirctory print number of file and folder
                goto Err1;
            }

            goto Err2;
        }


#ifdef CONFIG_SUPPORT_VFAT
        else if (dols == LS_ROOT)
        {
            char str[sizeof(dentptr->name)+sizeof(dentptr->ext)];
            memset(str, 0, sizeof(str));
            memcpy(str, dentptr->name, sizeof(dentptr->name));
            memcpy(str+sizeof(dentptr->name), dentptr->ext, sizeof(dentptr->ext));
            if(mkcksum (str) == prevcksum)
            {
                dentptr++;
                continue;
            }
        }
#endif
        get_name (dentptr, s_name);

        if (dols == LS_ROOT) {
            int isdir = (dentptr->attr & ATTR_DIR);
            char dirc=0;
            int doit = 0;

            if (isdir) {
                dirc = '/';
                if (s_name[0] != 0) {
                    dirs++;
                    doit = 1;
                }
            }
            else {
                dirc = ' ';
                if (s_name[0] != 0) {
                    files++;
                    doit = 1;
                }
            }
            if (doit) {
                if (dirc == ' ') {
                    printf (" %8ld   %s%c\n",(long) FAT2CPU32 (dentptr->size), s_name,dirc);
                }
                else {
                    printf ("            %s%c\n", s_name, dirc);
                }
            }
            dentptr++;
            continue;
        }

        if (strcmp (fnamecopy, s_name) && strcmp (fnamecopy, l_name)) {
            FAT_DPRINT ("RootMismatch: |%s|%s|\n", s_name, l_name);
            dentptr++;
            continue;
        }
        if (isdir && !(dentptr->attr & ATTR_DIR)){

            goto Err2;
        }
        FAT_DPRINT ("RootName: %s", s_name);/*root dirterory*/
        FAT_DPRINT (", start: 0x%x", START (dentptr));
        FAT_DPRINT (", size:  0x%x %s\n", FAT2CPU32 (dentptr->size), isdir ? "(DIR)" : "");

        goto rootdir_done;  /* We got a match */
    }
#if 0
    cursect++;
#else
        cur_cluster = get_fatent (mydata, cur_cluster);

        if (CHECK_CLUST(cur_cluster, mydata->fatsize))
        {
            FAT_DPRINT ("RootDentname == NULL - %d\n", i);
            if (dols == LS_ROOT)
            {
                printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);

                goto Err1;
            }

            goto Err2;
        }
        else
        {
            cursect = mydata->fat_sect + mydata->fatlength * bs->fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;
        }
#endif
    }

rootdir_done:
{
    dir_entry dent;
    firsttime = 1;
    while (isdir) {
        int startsect = mydata->data_begin
            + START (dentptr) * mydata->clust_size;
        //dir_entry dent;
        char *nextname = NULL;

        dent = *dentptr;
        dentptr = &dent;

        idx = dirdelim (subname);
        if (idx >= 0) {
            subname[idx] = '\0';
            nextname = subname + idx + 1;
            /* Handle multiple delimiters */
            while (ISDIRDELIM (*nextname))
                nextname++;
            if (dols && *nextname == '\0')
                firsttime = 0;
        }
        else {
            if (dols && firsttime) {
                firsttime = 0;
            }
            else {
                isdir = 0;
            }
        }
        /*DentName: ., start: 0x4, size:  0x0 (DIR)*/
        if (get_dentfromdir (mydata, startsect, subname, dentptr,
                     isdir ? 0 : dols) == NULL) {

            if (dols && !isdir){
                goto Err1;
            }

            goto Err2;
        }

        if (idx >= 0) {
            if (!(dentptr->attr & ATTR_DIR)){
                goto Err2;
            }
            subname = nextname;
        }
    }
    ret = get_part_contents (mydata, dentptr, buffer, offset, maxsize);
    FAT_DPRINT ("Size: %d, got: %ld\n", FAT2CPU32 (dentptr->size), ret);

    file_fat_deinit(mydata, bs, volinfo);
    return ret;
}

Err1:
    file_fat_deinit(mydata, bs, volinfo);
    return 0;
    
Err2:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;
}

__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8 do_fat_ls_block[MAX_CLUSTSIZE];
long
do_fat_list_file (const char *filename, void *buffer, unsigned long maxsize,
         int dols)
{
#if 1 // CONFIG_NIOS /* NIOS CPU cannot access big automatic arrays */
    static
#endif
    char fnamecopy[2048];
    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    //fsdata datablock;
    //fsdata *mydata = &datablock;
    fsdata *mydata = NULL;
    dir_entry *dentptr=NULL;
    __u16 prevcksum = 0xffff;
    char *subname = "";
    int cursect=0;
    int idx=0, isdir = 0;
    int files = 0, dirs = 0;
    int firsttime=0;
    __u32 cur_cluster=0;
    unsigned int remain=0;
    if(filename == NULL)
    {
        printf("%s: Error: file name is NULL, at %d\n", __func__, __LINE__);
        return 1;
    }
    
    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err;
    }
    
    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    memset(buffer,0,maxsize);
    remain=maxsize;
    /* "cwd" is always the root... */
    while (ISDIRDELIM (*filename))
        filename++;
    /* Make a copy of the filename and convert it to lowercase */
    memset(fnamecopy, 0, sizeof(fnamecopy));
    strncpy (fnamecopy, filename, ((sizeof(fnamecopy)-1)<strlen(filename))?(sizeof(fnamecopy)-1):strlen(filename));
    downcase (fnamecopy);// convert it to lowercase

    if (*fnamecopy == '\0') {
        if (!dols){
            goto Err;
        }
        dols = LS_ROOT;
    }
    else if ((idx = dirdelim (fnamecopy)) >= 0) {
        isdir = 1;
        fnamecopy[idx] = '\0';
        subname = fnamecopy + idx + 1;
        /* Handle multiple delimiters */
        while (ISDIRDELIM (*subname))
            subname++;
    }
    else if (dols) {
        isdir = 1;
    }

    while (1) {
        int i=0;
        if (disk_read (cursect, mydata->clust_size, do_fat_ls_block) < 0) {
            FAT_DPRINT ("Error: reading rootdir block\n");
            goto Err;
        }
        dentptr = (dir_entry *) do_fat_ls_block;/*data is in da_fat_read_block*/

#if 0
        for (i = 0; i < DIRENTSPERBLOCK; i++)
#else
        for (i = 0; i < DIRENTSPERBLOCK * (mydata->clust_size); i++)
#endif
        {
            char s_name[14], l_name[256];

            l_name[0] = '\0';

            if((u8)dentptr->name[0]== 0xE5)
            {
                //skip the free dentry slot
                dentptr++;
                continue;
            }


            if ((dentptr->attr & ATTR_VOLUME)) {
#ifdef CONFIG_SUPPORT_VFAT
                if ((dentptr->attr & ATTR_VFAT) &&
                    (dentptr->name[0] & LAST_LONG_ENTRY_MASK)) {
                    prevcksum = ((dir_slot *) dentptr)->alias_checksum;
#if 0
                    get_vfatname (mydata, 0, do_fat_ls_block, dentptr, l_name);
#else

                    get_vfatname (mydata, cur_cluster, do_fat_ls_block, dentptr, l_name);
#endif

                    if (dols == LS_ROOT) {
                        int isdir = (dentptr->attr & ATTR_DIR);
                        char dirc=0;
                        int doit = 0;

                        if (isdir) {
                            dirs++;
                            dirc = '/';
                            doit = 1;
                        } else {
                            dirc = ' ';
                            if (l_name[0] != 0) {
                                files++;
                                doit = 1;
                            }
                        }
                        if (doit)
                        {
                            if (dirc == ' ') {
                            #if 0
                            printf (" %8ld   %s%c\n",
                                (long) FAT2CPU32 (dentptr->size),
                                l_name, dirc);
                            #endif
                            if(remain>=(strlen(l_name)+1))
                            {
                                memcpy(buffer,l_name,strlen(l_name)+1);
                                buffer+=(strlen(l_name)+1);
                                remain-=(strlen(l_name)+1);
                            }

                            } else {
                                printf ("            %s%c\n", l_name, dirc);
                            }
                        }
                        dentptr++;
                        continue;
                    }
                    FAT_DPRINT ("Rootvfatname: |%s|\n", l_name);
                }
                else
#endif
                {
                    /* Volume label or VFAT entry */
                    dentptr++;
                    continue;
                }

            }/*   */

          /*this segment is not run*/
            else if (dentptr->name[0] == 0)
            {
                FAT_DPRINT ("RootDentname == NULL - %d\n", i);
                if (dols == LS_ROOT) {
                    printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);//root dirctory print number of file and folder
                    goto Done;
                }

                goto Err;
            }


#ifdef CONFIG_SUPPORT_VFAT
            else if (dols == LS_ROOT)
            {
                char str[sizeof(dentptr->name)+sizeof(dentptr->ext)];
                memset(str, 0, sizeof(str));
                memcpy(str, dentptr->name, sizeof(dentptr->name));
                memcpy(str+sizeof(dentptr->name), dentptr->ext, sizeof(dentptr->ext));
                if(mkcksum (str) == prevcksum)
                {
                    dentptr++;
                    continue;
                }
            }
#endif
            get_name (dentptr, s_name);

            if (dols == LS_ROOT) {
                int isdir = (dentptr->attr & ATTR_DIR);
                char dirc=0;
                int doit = 0;

                if (isdir) {
                    dirc = '/';
                    if (s_name[0] != 0) {
                        dirs++;
                        doit = 1;
                    }
                }
                else {
                    dirc = ' ';
                    if (s_name[0] != 0) {
                        files++;
                        doit = 1;
                    }
                }
                if (doit) {
                    if (dirc == ' ') {
                        printf (" %8ld   %s%c\n",(long) FAT2CPU32 (dentptr->size), s_name,dirc);
                    }
                    else {
                        printf ("            %s%c\n", s_name, dirc);
                    }
                }
                dentptr++;
                continue;
            }

            if (strcmp (fnamecopy, s_name) && strcmp (fnamecopy, l_name)) {
                FAT_DPRINT ("RootMismatch: |%s|%s|\n", s_name, l_name);
                dentptr++;
                continue;
            }
            if (isdir && !(dentptr->attr & ATTR_DIR))
            {
                if(dols != LS_FILESIZE)
                {
                    goto Err;
                }
            }
            FAT_DPRINT ("RootName: %s", s_name);/*root dirterory*/
            FAT_DPRINT (", start: 0x%x", START (dentptr));
            FAT_DPRINT (", size:  0x%x %s\n", FAT2CPU32 (dentptr->size), isdir ? "(DIR)" : "");

            goto rootdir_done;  /* We got a match */
        }
#if 0
    cursect++;
#else
        cur_cluster = get_fatent(mydata, cur_cluster);

        if (CHECK_CLUST(cur_cluster, mydata->fatsize))
        {
            FAT_DPRINT ("RootDentname == NULL - %d\n", i);
            if (dols == LS_ROOT)
            {
                printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);
                goto Done;
            }

            goto Err;
        }
        else
        {
            cursect = mydata->fat_sect + mydata->fatlength * bs->fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;
        }
#endif
    }

rootdir_done:
{
    dir_entry dent;
    firsttime = 1;
    while (isdir) {
        int startsect = mydata->data_begin
            + START (dentptr) * mydata->clust_size;
        //dir_entry dent;
        char *nextname = NULL;

        dent = *dentptr;
        dentptr = &dent;

        idx = dirdelim (subname);
        if (idx >= 0) {
            subname[idx] = '\0';
            nextname = subname + idx + 1;
            /* Handle multiple delimiters */
            while (ISDIRDELIM (*nextname))
                nextname++;
            if (dols && *nextname == '\0')
                firsttime = 0;
        }
        else {
            if (dols && firsttime) {
                firsttime = 0;
            }
            else {
                isdir = 0;
            }
        }
        /*DentName: ., start: 0x4, size:  0x0 (DIR)*/
        if (get_dentfromdir (mydata, startsect, subname, dentptr,
                     isdir ? 0 : dols) == NULL) {
           if (dols && !isdir){
                goto Done;
            }

            goto Err;
        }

        if (idx >= 0) {
           if (!(dentptr->attr & ATTR_DIR)){
                goto Err;
            }
            subname = nextname;
        }
    }
    
}

Done:
    file_fat_deinit(mydata, bs, volinfo);
    return 0;
    
Err:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;
}

__attribute__ ((__aligned__(__alignof__(dir_entry))))
__u8 do_fat_read_block[MAX_CLUSTSIZE];
long
do_fat_read (const char *filename, void *buffer, unsigned long maxsize,
         int dols)
{
#if 1 // CONFIG_NIOS /* NIOS CPU cannot access big automatic arrays */
    static
#endif
    char fnamecopy[2048];
    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    //fsdata datablock;
    //fsdata *mydata = &datablock;
    fsdata *mydata = NULL;
    dir_entry *dentptr=NULL;
    __u16 prevcksum = 0xffff;
    char *subname = "";
    int cursect=0;
    int idx=0, isdir = 0;
    int files = 0, dirs = 0;
    long ret = 0;
    int firsttime=0;
    __u32 cur_cluster=0;

    if(filename == NULL)
    {
        printf("%s: Error: file name is NULL, at %d\n", __func__, __LINE__);
        return 1;
    }

    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err2;
    }

    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    /* "cwd" is always the root... */
    while (ISDIRDELIM (*filename))
        filename++;
    /* Make a copy of the filename and convert it to lowercase */
    memset(fnamecopy, 0, sizeof(fnamecopy));
    strncpy (fnamecopy, filename, ((sizeof(fnamecopy)-1)<strlen(filename))?(sizeof(fnamecopy)-1):strlen(filename));
    downcase (fnamecopy);// convert it to lowercase

    if (*fnamecopy == '\0') {
        if (!dols){
            goto Err2;
        }
        dols = LS_ROOT;
    }
    else if ((idx = dirdelim (fnamecopy)) >= 0) {
        isdir = 1;
        fnamecopy[idx] = '\0';
        subname = fnamecopy + idx + 1;
        /* Handle multiple delimiters */
        while (ISDIRDELIM (*subname))
            subname++;
    }
    else if (dols) {
        isdir = 1;
    }

    while (1) {
        int i=0;
        if (disk_read (cursect, mydata->clust_size, do_fat_read_block) < 0) {
            FAT_DPRINT ("Error: reading rootdir block\n");
            goto Err2;
        }
        dentptr = (dir_entry *) do_fat_read_block;/*data is in da_fat_read_block*/

#if 0
        for (i = 0; i < DIRENTSPERBLOCK; i++)
#else
        for (i = 0; i < DIRENTSPERBLOCK * (mydata->clust_size); i++)
#endif
        {
            char s_name[14], l_name[256];

            l_name[0] = '\0';

            if((u8)dentptr->name[0]== 0xE5)
            {
                //skip the free dentry slot
                dentptr++;
                continue;
            }


            if ((dentptr->attr & ATTR_VOLUME)) {
#ifdef CONFIG_SUPPORT_VFAT
                if ((dentptr->attr & ATTR_VFAT) &&
                    (dentptr->name[0] & LAST_LONG_ENTRY_MASK)) {
                    prevcksum = ((dir_slot *) dentptr)->alias_checksum;
#if 0
                    get_vfatname (mydata, 0, do_fat_read_block, dentptr, l_name);
#else

                    get_vfatname (mydata, cur_cluster, do_fat_read_block, dentptr, l_name);
#endif

                    if (dols == LS_ROOT) {
                        int isdir = (dentptr->attr & ATTR_DIR);
                        char dirc=0;
                        int doit = 0;

                        if (isdir) {
                            dirs++;
                            dirc = '/';
                            doit = 1;
                        } else {
                            dirc = ' ';
                            if (l_name[0] != 0) {
                                files++;
                                doit = 1;
                            }
                        }
                        if (doit)
                        {
                            if (dirc == ' ') {
                            printf (" %8ld   %s%c\n",
                                (long) FAT2CPU32 (dentptr->size),
                                l_name, dirc);
                            } else {
                                printf ("            %s%c\n", l_name, dirc);
                            }
                        }
                        dentptr++;
                        continue;
                    }
                    FAT_DPRINT ("Rootvfatname: |%s|\n", l_name);
                }
                else
#endif
                {
                    /* Volume label or VFAT entry */
                    dentptr++;
                    continue;
                }

            }/*   */

          /*this segment is not run*/
            else if (dentptr->name[0] == 0)
            {
                FAT_DPRINT ("RootDentname == NULL - %d\n", i);
                if (dols == LS_ROOT) {
                    printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);//root dirctory print number of file and folder
                    goto Err1;
                }

                goto Err2;
            }


#ifdef CONFIG_SUPPORT_VFAT
            else if (dols == LS_ROOT)
            {
                char str[sizeof(dentptr->name)+sizeof(dentptr->ext)];
                memset(str, 0, sizeof(str));
                memcpy(str, dentptr->name, sizeof(dentptr->name));
                memcpy(str+sizeof(dentptr->name), dentptr->ext, sizeof(dentptr->ext));
                if(mkcksum (str) == prevcksum)
                {
                    dentptr++;
                    continue;
                }
            }
#endif
            get_name (dentptr, s_name);

            if (dols == LS_ROOT) {
                int isdir = (dentptr->attr & ATTR_DIR);
                char dirc=0;
                int doit = 0;

                if (isdir) {
                    dirc = '/';
                    if (s_name[0] != 0) {
                        dirs++;
                        doit = 1;
                    }
                }
                else {
                    dirc = ' ';
                    if (s_name[0] != 0) {
                        files++;
                        doit = 1;
                    }
                }
                if (doit) {
                    if (dirc == ' ') {
                        printf (" %8ld   %s%c\n",(long) FAT2CPU32 (dentptr->size), s_name,dirc);
                    }
                    else {
                        printf ("            %s%c\n", s_name, dirc);
                    }
                }
                dentptr++;
                continue;
            }

            if (strcmp (fnamecopy, s_name) && strcmp (fnamecopy, l_name)) {
                FAT_DPRINT ("RootMismatch: |%s|%s|\n", s_name, l_name);
                dentptr++;
                continue;
            }
            if (isdir && !(dentptr->attr & ATTR_DIR))
            {
                if(dols != LS_FILESIZE)
                {
                    goto Err2;
                }
            }
            FAT_DPRINT ("RootName: %s", s_name);/*root dirterory*/
            FAT_DPRINT (", start: 0x%x", START (dentptr));
            FAT_DPRINT (", size:  0x%x %s\n", FAT2CPU32 (dentptr->size), isdir ? "(DIR)" : "");

            goto rootdir_done;  /* We got a match */
        }
#if 0
    cursect++;
#else
        cur_cluster = get_fatent(mydata, cur_cluster);

        if (CHECK_CLUST(cur_cluster, mydata->fatsize))
        {
            FAT_DPRINT ("RootDentname == NULL - %d\n", i);
            if (dols == LS_ROOT)
            {
                printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);
                goto Err1;
            }

            goto Err2;
        }
        else
        {
            cursect = mydata->fat_sect + mydata->fatlength * bs->fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;
        }
#endif
    }

rootdir_done:
{
    dir_entry dent;
    firsttime = 1;
    while (isdir) {
        int startsect = mydata->data_begin
            + START (dentptr) * mydata->clust_size;
        //dir_entry dent;
        char *nextname = NULL;

        dent = *dentptr;
        dentptr = &dent;

        idx = dirdelim (subname);
        if (idx >= 0) {
            subname[idx] = '\0';
            nextname = subname + idx + 1;
            /* Handle multiple delimiters */
            while (ISDIRDELIM (*nextname))
                nextname++;
            if (dols && *nextname == '\0')
                firsttime = 0;
        }
        else {
            if (dols && firsttime) {
                firsttime = 0;
            }
            else {
                isdir = 0;
            }
        }
        /*DentName: ., start: 0x4, size:  0x0 (DIR)*/
        if (get_dentfromdir (mydata, startsect, subname, dentptr,
                     isdir ? 0 : dols) == NULL) {
           if (dols && !isdir){
                goto Err1;
            }

            goto Err2;
        }

        if (idx >= 0) {
           if (!(dentptr->attr & ATTR_DIR)){
                goto Err2;
            }
            subname = nextname;
        }
    }
    if (maxsize == 0xffffffff)
    {
        file_fat_deinit(mydata, bs, volinfo);
        return FAT2CPU32 (dentptr->size);
    }
    else
    {
        ret = get_contents (mydata, dentptr, buffer, maxsize);
        FAT_DPRINT ("Size: %d, got: %ld\n", FAT2CPU32 (dentptr->size), ret);

        file_fat_deinit(mydata, bs, volinfo);
        return ret;
    }
}

Err1:
    file_fat_deinit(mydata, bs, volinfo);
    return 0;
    
Err2:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;
}


int
file_fat_detectfs(void)
{
    boot_sector    bs;
    volume_info    volinfo;
    int        fatsize=0;
    char    vol_label[12];

    if(cur_dev==NULL) {
        printf("No current device\n");
        return 1;
    }
#if 1
    printf("Interface:  ");
    switch(cur_dev->if_type) {
        case IF_TYPE_IDE :      printf("IDE"); break;
        case IF_TYPE_SCSI :     printf("SCSI"); break;
        case IF_TYPE_ATAPI :    printf("ATAPI"); break;
        case IF_TYPE_USB :      printf("USB"); break;
        case IF_TYPE_DOC :      printf("DOC"); break;
        case IF_TYPE_MMC :      printf("MMC"); break;
        default :               printf("Unknown");
    }
    printf("\n  Device %d: ",cur_dev->dev);
    dev_print(cur_dev);
#endif
    if(read_bootsectandvi(&bs, &volinfo, &fatsize)) {
        printf("\nNo valid FAT fs found\n");
        return 1;
    }
    memcpy (vol_label, volinfo.volume_label, 11);
    vol_label[11] = '\0';
    volinfo.fs_type[5]='\0';
    printf("Partition %d: Filesystem: %s \"%s\"\n",cur_part,volinfo.fs_type,vol_label);
    return 0;
}

int
file_fat_list(const char *dir,void *buffer, unsigned long maxsize)
{
    return do_fat_list_file(dir, buffer, maxsize, LS_YES);
}


int
file_fat_ls(const char *dir)
{
    return do_fat_read(dir, NULL, 0, LS_YES);
}

long
file_fat_part_read(const char *filename, void *buffer, unsigned long offset, unsigned long maxsize)
{
    //printf("reading %s\n",filename);
    return do_fat_part_read(filename, buffer, offset, maxsize, LS_NO);
}

long
file_fat_read(const char *filename, void *buffer, unsigned long maxsize)
{
    printf("reading %s\n",filename);
    return do_fat_read(filename, buffer, maxsize, LS_NO);
}

long
file_fat_filesize(const char *filename)
{
    printf("reading %s\n",filename);
    return do_fat_read(filename, NULL, 0xffffffff, LS_NO/*LS_FILESIZE*/);
}

long
file_fat_writefile(const char *filename, void *buffer, unsigned long maxsize)
{
    printf("writing %s\n",filename);
    return do_fat_write(filename, buffer, maxsize, LS_NO);
}



__u8 do_fat_cache_sector[MAX_CLUSTSIZE];

//Supported mode:
//w
//a
//
//
struct filedescipter gfd[MAXFILEBUFFER];
static int iNumOfFile=0;

int file_fat_init(fsdata **pmydata, boot_sector **pbs, volume_info **pvolinfo)
{
    *pmydata = malloc(sizeof(fsdata));
    if(*pmydata==NULL){
        printf("Error: mydata memory allocate fail\n");
        return 1;
    }

    *pbs = malloc(sizeof(boot_sector));
    if(*pbs==NULL){
        printf("Error: bs memory allocate fail\n");
        return 1;
    }
    
    *pvolinfo = malloc(sizeof(volume_info));
    if(*pvolinfo==NULL){
        printf("Error: bs memory allocate fail\n");
        return 1;
    }
    
    memset(*pmydata, 0, sizeof(fsdata));
    memset(*pbs, 0, sizeof(boot_sector));
    memset(*pvolinfo, 0, sizeof(volume_info));

    /*read fat boot sector and volume info from filesystem */
    if (read_bootsectandvi (*pbs, *pvolinfo, &((*pmydata)->fatsize))) {
        FAT_DPRINT ("Error: reading boot sector\n");
        free(*pmydata);
        *pmydata = NULL;
        return -1;
    }

    /*affirm fat format is 32 or 16*/
    if ((*pmydata)->fatsize == 32) {
        (*pmydata)->fatlength = (*pbs)->fat32_length;
    }else if((*pmydata)->fatsize == 16){
        (*pmydata)->fatlength = (*pbs)->fat_length;
    }else{
        FAT_ERROR("\n ***Do not support Fat format!*** \n");
        free(*pmydata);
        *pmydata = NULL;
        return -1;
    }

    (*pmydata)->fat_sect = (*pbs)->reserved;
    (*pmydata)->clust_size = (*pbs)->cluster_size;
    (*pmydata)->rootdir_sect = (*pmydata)->fat_sect + (*pmydata)->fatlength * (*pbs)->fats;
    
    /*fat format is 32*/
    if ((*pmydata)->fatsize == 32) {
        (*pmydata)->rootdir_size = (*pmydata)->clust_size;
        (*pmydata)->data_begin = (*pmydata)->rootdir_sect   /* + (*pmydata)->rootdir_size */
            - ((*pmydata)->clust_size * 2);
        (*pmydata)->fatbufsize = FAT32BUFSIZE;
        (*pmydata)->maxfatentry = 0x0fffffff;
        (*pmydata)->endfatentry = 0xffffffff;
    }else if((*pmydata)->fatsize == 16){
        (*pmydata)->rootdir_size = (((*pbs)->dir_entries[1] * (int) 256 + (*pbs)->dir_entries[0])
                * sizeof (dir_entry)) / SECTOR_SIZE;
        (*pmydata)->data_begin = (*pmydata)->rootdir_sect + (*pmydata)->rootdir_size
            - ((*pmydata)->clust_size * 2);
        (*pmydata)->fatbufsize = FAT16BUFSIZE;
        (*pmydata)->maxfatentry = 0x0fff;
        (*pmydata)->endfatentry = 0xffff;
    }else {
        FAT_ERROR("\n ***Do not support Fat format!*** \n");
        free(*pmydata);
        *pmydata = NULL;
        return -1;
    }
    (*pmydata)->entnum = ALIGN((*pbs)->total_sect - (*pbs)->reserved
        - (*pbs)->fat32_length - 1, (*pbs)->cluster_size) / (*pbs)->cluster_size + 2;

    (*pmydata)->fatbuf = (__u8 *) &g_current_fatbuf;

    if(check_fatbuf(*pmydata) < 0){
        free(*pmydata);
        *pmydata = NULL;
        return -1;
    }
    
    /*FAT 32 fatlength:998 ----->print fat format and disk storage*/
    FAT_DPRINT ("FAT%d, fatlength: %d\n", (*pmydata)->fatsize,
        (*pmydata)->fatlength);
    FAT_DPRINT ("Rootdir begins at sector: %d, offset: %x, size: %d\n"
        "Data begins at: %d\n",
        (*pmydata)->rootdir_sect, (*pmydata)->rootdir_sect * SECTOR_SIZE,
        (*pmydata)->rootdir_size, (*pmydata)->data_begin);
    FAT_DPRINT ("Cluster size: %d\n", (*pmydata)->clust_size);

    return 0;
}

void file_fat_deinit(fsdata *mydata, boot_sector *bs, volume_info *volinfo)
{
    if(mydata)
        free(mydata);

    if(bs)
        free(bs);

    if(volinfo)
        free(volinfo);
}

long file_fat_write(int fd, void *buffer, unsigned long maxsize)
{
    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    //fsdata datablock; //In order to pass converity checking.
    //fsdata *mydata = &datablock; //In order to pass converity checking.
    fsdata *mydata = NULL;
    dir_entry *dentptr;

    __u32 cur_cluster=0;
    __u32 start_cluster=0;
    __u32 old_cluster=0;
    __u32 fileoffset = 0;
    long writesize = 0;
    int sharpnum = 1;
    int getno = 1;

    int cursect=0;
    if(fd<0 || fd>15) {
        printf("Invaild file num\n");
        return -1;
    }

    if(gfd[fd].fd == 0)
        return -1;

    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err;
    }
        
    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    cur_cluster = gfd[fd].ent_cluser;

    cursect = mydata->fat_sect + mydata->fatlength * bs->fats
                   + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;

    FAT_DPRINT("fd:%d, cur_cluster:%d, cursect:%d, offset:%d\n",fd, cur_cluster, cursect, gfd[fd].ent_offset);
    if (disk_read (cursect, mydata->clust_size, do_fat_read_block) < 0) {
        FAT_DPRINT ("Error: reading rootdir block\n");
        goto Err;
    }
    dentptr = (dir_entry *)(do_fat_read_block + (gfd[fd].ent_offset * sizeof(dir_entry))) ;

    //if file size == 0, must find new start cluster
    if(dentptr->size == 0) {
        start_cluster = getfree_cluster(mydata, &getno);

       if(start_cluster < 0){
            FAT_ERROR("get free cluster error!\n");
            goto Err;
       }

        dentptr->starthi = (u16)(start_cluster>>16);
        dentptr->start   = (u16)start_cluster;
        old_cluster =
        cur_cluster = start_cluster;
    }
    else {
        start_cluster = START(dentptr);
        old_cluster =
        cur_cluster = start_cluster;
        while(1) {
            cur_cluster = get_fatent(mydata, cur_cluster);
            if(CHECK_CLUST(cur_cluster, mydata->fatsize)) {
                break;
            }
            old_cluster = cur_cluster;
        }

        cur_cluster = old_cluster;
    }

    fileoffset = dentptr->size % (mydata->clust_size * SECTOR_SIZE);

    if(fileoffset != 0 || dentptr->size == 0 ) {
        memset(do_fat_cache_sector, 0, mydata->clust_size * SECTOR_SIZE);
        //cursect = mydata->fat_sect + mydata->fatlength * bs.fats + (old_cluster - ROOT_CLUSTER) * mydata->clust_size;
        cursect = mydata->data_begin + old_cluster*mydata->clust_size;
        //read the file tile
        if (disk_read (cursect, mydata->clust_size, do_fat_cache_sector) < 0) {
            FAT_DPRINT ("Error: reading block\n");
            goto Err;
        }

        if(maxsize <= (mydata->clust_size * SECTOR_SIZE) - fileoffset) {
            memcpy(do_fat_cache_sector + fileoffset, buffer, maxsize);
            writesize = maxsize;
            maxsize = 0;
        }else {
            memcpy(do_fat_cache_sector + fileoffset, buffer, (mydata->clust_size * SECTOR_SIZE) - fileoffset);
            writesize = (mydata->clust_size * SECTOR_SIZE) - fileoffset;
            maxsize -= (mydata->clust_size * SECTOR_SIZE) - fileoffset;
        }
        // write first block
        if (disk_write (cursect, mydata->clust_size, do_fat_cache_sector) < 0) {
            FAT_DPRINT ("Error: writing block\n");
            goto Err;
        }
        put_fatent(mydata,old_cluster,cur_cluster,1);
        printf("#");
    }
    //if(dentptr->size == 0)

    getno = MAX_CLUSTSIZE / (mydata->clust_size * SECTOR_SIZE);
    FAT_DPRINT("set getno = %d and clust_size = %d\n",getno, mydata->clust_size );
    //write left blocks

    while(maxsize != 0) {
        getno = MAX_CLUSTSIZE / (mydata->clust_size * SECTOR_SIZE);
        printf("#");
        if (sharpnum++ % 64 == 0)
            printf("\n");

        old_cluster = cur_cluster;
        cur_cluster = getfree_cluster(mydata, &getno);
        if(cur_cluster < 0){
            FAT_ERROR("get free cluster error!\n");
            goto Err;
        }
        //put_fatent(mydata,old_cluster,cur_cluster,getno);//update file entry

        //cursect = mydata->fat_sect + mydata->fatlength * bs.fats
        //            + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;
        cursect = mydata->data_begin + cur_cluster*mydata->clust_size;
        
        if(maxsize <= mydata->clust_size * SECTOR_SIZE * getno) {
            getno = maxsize / (mydata->clust_size * SECTOR_SIZE);
            //if(maxsize < mydata->clust_size * SECTOR_SIZE * getno)
            if((maxsize % (mydata->clust_size * SECTOR_SIZE)) > 0 )
                getno ++;

            if (disk_write (cursect, mydata->clust_size * getno, (u8 *)(buffer + writesize)) < 0) {
                FAT_DPRINT ("Error: Writing block\n");
                goto Err;
            }
            writesize += maxsize;
            maxsize = 0;
            put_fatent(mydata,old_cluster,cur_cluster,getno);//update file entry
            break;
        }
        else {
            if (disk_write (cursect, mydata->clust_size * getno, (u8 *)(buffer + writesize)) < 0) {
                FAT_DPRINT ("Error: Writing block\n");
                goto Err;
            }
            writesize += mydata->clust_size * SECTOR_SIZE  * getno;
            maxsize -= mydata->clust_size * SECTOR_SIZE  * getno;
        }
        put_fatent(mydata,old_cluster,cur_cluster,getno);//update file entry

        cur_cluster += (getno - 1);
    }

    //write file dir
    dentptr->size += writesize;
    cur_cluster = gfd[fd].ent_cluser;

    cursect = mydata->fat_sect + mydata->fatlength * bs->fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;

    if (disk_write (cursect, mydata->clust_size, do_fat_read_block) < 0) {
        FAT_DPRINT ("Error: reading rootdir block\n");
        goto Err;
    }
    printf("\n");

    file_fat_deinit(mydata, bs, volinfo);
    return 0;
    
Err:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;

}

int file_fat_open(const char *filename, const char *mode)
{
    int i=0;
    int fd = 0;

    if(strlen(filename)>12 || strlen(filename)<1)
        return -1;

    if(0==iNumOfFile)
        memset(gfd, 0, sizeof(struct filedescipter) * MAXFILEBUFFER);

    for(i=0; i<MAXFILEBUFFER; i++) {
        if(gfd[i].fd == 0) {
            gfd[i].fd = 1;
            fd = i;
            memset(gfd[i].filename, 0, sizeof(gfd[i].filename));
            strncpy (gfd[i].filename, filename, ((sizeof(gfd[i].filename)-1)<strlen(filename))?(sizeof(gfd[i].filename)-1):strlen(filename));
            break;
        }
    }

    if(strcmp("w",mode) == 0) {
        gfd[fd].mode = MODECREATE;
    }else if(strcmp("a",mode) == 0) {
        gfd[fd].mode = MODEAPPEND;
    }else {
        printf("file open failed: unsupported mode\n");
        return -1;
    }

    {
        if(!file_fat_search(fd))  //file exist
        {
            /* Don't recreate file in append mode */
            if(strcmp("a",mode) == 0)
            {
                iNumOfFile++;
             return fd;
            }
            printf("file exist, and will be recreate\n");
        }
        else
            gfd[fd].mode = MODENEW;

        file_fat_create(fd, mode);
    }

    iNumOfFile++;

    return fd;
}

void file_fat_close(int fd)
{
    if(fd<0 || fd>15) {
        printf("Invaild file num\n");
        return ;
    }

    memset(&gfd[fd], 0, sizeof(struct filedescipter));
    return;

}



long file_fat_create(int fd, const char *mode)
{
#if 1 // CONFIG_NIOS /* NIOS CPU cannot access big automatic arrays */
        static
#endif
    char fnamecopy[2048];

    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    //fsdata datablock;
    //fsdata *mydata = &datablock;
    fsdata *mydata = NULL;
    dir_entry *dentptr;

    __u32 cur_cluster=0;
    __u32 start_cluster=0;
    int i=0,j=0;
    int bfoundempty = 0;


    int cursect=0;

    if(fd<0 || fd>15) {
        printf("Invaild file num\n");
        return -1;
    }

    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err;
    }
    
    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    if(gfd[fd].mode == MODENEW) // didn't support long name
    {

        while(1){
            if(disk_read(cursect, mydata->clust_size, do_fat_read_block) < 0) {
                    FAT_DPRINT ("Error: reading rootdir block\n");
                    goto Err;
                    return -1;
            }

            dentptr = (dir_entry *) do_fat_read_block;/*data is in da_fat_read_block*/

#if 0
                for (i = 0; i < DIRENTSPERBLOCK; i++)
#else
                for (i = 0; i < DIRENTSPERBLOCK * (mydata->clust_size); i++)
#endif
                {
                    if(dentptr->name[0] == DELETED_FLAG)//Free entry
                    {
                        bfoundempty = 1;
                        break;
                    }
                    else if(dentptr->name[0] == 0x0) //last free entry
                    {
                        bfoundempty = 1;
                        break;
                    }
                    dentptr++;
                }

                if(bfoundempty) // didn't support long name
                {
                    gfd[fd].ent_cluser = cur_cluster;
                    gfd[fd].ent_offset = i;
                    memset(fnamecopy,0,2048);
                    memcpy(fnamecopy,gfd[fd].filename,12);
                    memset(&dentptr->name[0],0x20,sizeof(dentptr->name));
                    memset(&dentptr->ext[0],0x20,sizeof(dentptr->ext));
                    upcase(fnamecopy);
                    j=0;
                    for(i=0;i<8;i++) {
                        if(fnamecopy[i] == '.') {
                            j=i+1;
                            break;
                        }
                        dentptr->name[i] = fnamecopy[i];
                    }

                    for(i=0;i<3;i++) {
                        if(fnamecopy[j+i] == '\0')
                            break;
                        dentptr->ext[i] = fnamecopy[j+i];
                    }


                    dentptr->ctime =
                    dentptr->time  =
                    dentptr->ctime_ms = 0;
                    dentptr->date  = 0x21;
                    dentptr->adate = 0x3d6b;
                    dentptr->cdate = 0x21;
                    dentptr->start = 0;
                    dentptr->starthi = 0;
                    dentptr->size = 0;
                    dentptr->attr = 0x20;

                    break;

                }

                cur_cluster = get_fatent (mydata, cur_cluster);

                if (CHECK_CLUST(cur_cluster, mydata->fatsize))
                {
                    FAT_DPRINT ("RootDentname == NULL - %d\n", i);
                    break;
                }
                else
                {
                    cursect = mydata->fat_sect + mydata->fatlength * bs->fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;
                }

            //FAT16 special handle
            if((mydata->fatlength != 32) && cur_cluster == ROOT_CLUSTER) {
                if(0) {
                                FAT_DPRINT ("Error: FAT16 root dir full\n");
                                goto Err;
                }
            }
        }
    }
    else {

        cur_cluster = gfd[fd].ent_cluser;
        cursect = mydata->fat_sect + mydata->fatlength * bs->fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;


        FAT_DPRINT("fd:%d, cur_cluster:%d, cursect:%d, offset:%d\n",fd, cur_cluster, cursect, gfd[fd].ent_offset);
        if (disk_read (cursect, mydata->clust_size, do_fat_read_block) < 0) {
                FAT_DPRINT ("Error: reading rootdir block\n");
                goto Err;
        }
        dentptr = (dir_entry *)(do_fat_read_block + (gfd[fd].ent_offset * sizeof(dir_entry))) ;

        start_cluster = START(dentptr);
        FAT_DPRINT("start_cluster= %d\n",start_cluster);
        if(clear_fatent(mydata, start_cluster) < 0) {
                    FAT_DPRINT("error at clear fat ent");
            goto Err;
        }

    }


//FIXME: didn't check the dentptr

    dentptr->start = 0;
    dentptr->starthi= 0;
    dentptr->size = 0;

    //save fat table

    if(disk_write(cursect, mydata->clust_size, do_fat_read_block) < 0) {
            FAT_DPRINT ("Error: writing rootdir block\n");
            goto Err;
    }

    file_fat_deinit(mydata, bs, volinfo);
    return 0;
    
Err:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;

}

long file_fat_search(int fd)
{
#if 1 // CONFIG_NIOS /* NIOS CPU cannot access big automatic arrays */
    static
#endif
    char fnamecopy[2048];
    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    //fsdata datablock;
    //fsdata *mydata = &datablock;
    fsdata *mydata = NULL;
    dir_entry *dentptr=NULL;
    //__u16 prevcksum = 0xffff;
    char *subname = "";
    int cursect=0;
    int idx=0, isdir = 0;
    //int files = 0, dirs = 0;
    //long ret = 0;
    __u32 cur_cluster=0;
    __u32 bfnameexist = 0;
    int i=0 ;
    //char *pStr=NULL;
    //int dols = LS_NO;

    if(fd<0 || fd>15) {
        printf("Invaild file num\n");
        return -1;
    }

    if(gfd[fd].fd == 0)
        return -1;
    
    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err;
    }
    
    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    /* Make a copy of the filename and convert it to lowercase */
    memset(fnamecopy, 0, sizeof(fnamecopy));
    strncpy (fnamecopy, gfd[fd].filename, ((sizeof(fnamecopy)-1)<strlen(gfd[fd].filename))?(sizeof(fnamecopy)-1):strlen(gfd[fd].filename));
    downcase (fnamecopy);// convert it to lowercase

    if (*fnamecopy == '\0') {
        printf("%s: Error: wrong file name: %s, at %d\n", __func__, fnamecopy, __LINE__);
        goto Err;
    }
    else if ((idx = dirdelim (fnamecopy)) >= 0) {
        isdir = 1;
        fnamecopy[idx] = '\0';
        subname = fnamecopy + idx + 1;
        /* Handle multiple delimiters */
        while (ISDIRDELIM (*subname))
            subname++;
    }
#if 0 // can not enterm dead code
    else if (dols) {
        isdir = 1;
    }
#endif

    ///dir fetch
    /*while (1)*/ {

        if (disk_read (cursect, mydata->rootdir_size, do_fat_write_block) < 0) {
            FAT_DPRINT ("Error: reading rootdir block\n");
            goto Err;
            return -1;
        }
        dentptr = (dir_entry *) do_fat_write_block;/*data is in da_fat_read_block*/

#if 0
        for (i = 0; i < DIRENTSPERBLOCK; i++)
#else
        for (i = 0; i < DIRENTSPERBLOCK * mydata->rootdir_size; i++)
#endif
        {
            if((__u32)dentptr + (__u32)sizeof(dir_entry) > 
                (__u32)do_fat_write_block + FS_BLOCK_SIZE * mydata->rootdir_size){
                FAT_DPRINT("dentptr=0x%x, do_fat_write_block=0x%x\n",
                    (__u32)dentptr + (__u32)sizeof(dir_entry),
                    (__u32)do_fat_write_block+FS_BLOCK_SIZE * mydata->rootdir_size);
                break;
            }
            
            char s_name[14], l_name[256];

            l_name[0] = '\0';

            if ((dentptr->attr & ATTR_VOLUME)) {
#ifdef CONFIG_SUPPORT_VFAT
                if ((dentptr->attr & ATTR_VFAT) &&
                    (dentptr->name[0] & LAST_LONG_ENTRY_MASK)) {
                    //prevcksum = ((dir_slot *) dentptr)->alias_checksum;
#if 0
                    get_vfatname (mydata, 0, do_fat_read_block, dentptr, l_name);
#else

                    get_vfatname (mydata, cur_cluster, do_fat_write_block, dentptr, l_name);
#endif

#if 0 // can not enterm dead code
                    if (dols == LS_ROOT) {
                        int isdir = (dentptr->attr & ATTR_DIR);
                        char dirc;
                        int doit = 0;

                        if (isdir) {
                            dirs++;
                            dirc = '/';
                            doit = 1;
                        } else {
                            dirc = ' ';
                            if (l_name[0] != 0) {
                                files++;
                                doit = 1;
                            }
                        }
                        if (doit)
                        {
                            if (dirc == ' ') {
                            printf (" %8ld   %s%c\n",
                                (long) FAT2CPU32 (dentptr->size),
                                l_name, dirc);
                            } else {
                                printf ("            %s%c\n", l_name, dirc);
                            }
                        }
                        dentptr++;
                        continue;
                    }
#endif
                    FAT_DPRINT ("Rootvfatname: |%s|\n", l_name);
                }
                else
#endif
                {
                    /* Volume label or VFAT entry */
                    dentptr++;
                    continue;
                }

            }/*   */

            /*this segment is not run*/
            else if (dentptr->name[0] == 0)
            {
                FAT_DPRINT ("RootDentname == NULL - %d\n", i);
#if 0 // can not enterm dead code
                if (dols == LS_ROOT) {
                    printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);//root dirctory print number of file and folder
                    return 0;
                }
#endif
                break;
                //return -1;
            }


#ifdef CONFIG_SUPPORT_VFAT
#if 0 // can not enterm dead code
            else if (dols == LS_ROOT
                && mkcksum (dentptr->name) == prevcksum)
            {
                dentptr++;
                continue;
            }
#endif
#endif
            get_name (dentptr, s_name);
#if 0 // can not enterm dead code
            if (dols == LS_ROOT) {
                int isdir = (dentptr->attr & ATTR_DIR);
                char dirc=0;
                int doit = 0;

                if (isdir) {
                    dirc = '/';
                    if (s_name[0] != 0) {
                        dirs++;
                        doit = 1;
                    }
                }
                else {
                    dirc = ' ';
                    if (s_name[0] != 0) {
                        files++;
                        doit = 1;
                    }
                }
                if (doit) {
                    if (dirc == ' ') {
                        printf (" %8ld   %s%c\n",(long) FAT2CPU32 (dentptr->size), s_name,dirc);
                    }
                    else {
                        printf ("            %s%c\n", s_name, dirc);
                    }
                }
                dentptr++;
                continue;
            }
#endif
            if (strcmp (fnamecopy, s_name) && strcmp (fnamecopy, l_name)) {
                FAT_DPRINT ("RootMismatch: |%s|%s|\n", s_name, l_name);
                dentptr++;
                continue;
            }
            if (isdir && !(dentptr->attr & ATTR_DIR)) {
                printf("write 1\n");
                goto Err;
            }
            FAT_DPRINT ("RootName: %s", s_name);/*root dirterory*/
            FAT_DPRINT (", start: 0x%x", START (dentptr));
            FAT_DPRINT (", size:  0x%x %s\n", FAT2CPU32 (dentptr->size), isdir ? "(DIR)" : "");

            bfnameexist = 1;
            goto rootdir_done;  /* We got a match */
        }
#if 0
#if 0
        cursect++;
#else
        cur_cluster = get_fatent(mydata, cur_cluster);

        if (CHECK_CLUST(cur_cluster, mydata->fatsize))
        {
            FAT_DPRINT ("RootDentname == NULL - %d\n", i);
#if 0 // can not enterm dead code
            if (dols == LS_ROOT)
            {
                printf ("\n%d file(s), %d dir(s)\n\n", files, dirs);
                return 0;
            }
#endif
            break;
        }
        else
        {
            cursect = mydata->fat_sect + mydata->fatlength * bs.fats + (cur_cluster - ROOT_CLUSTER) * mydata->clust_size;
        }
#endif
#endif
    }

rootdir_done:

    if(bfnameexist) {
        printf("file %s found\n",gfd[fd].filename);
        memcpy(&(gfd[fd].dirEnt), dentptr, sizeof(struct dir_entry));
        gfd[fd].ent_cluser = cur_cluster;
        gfd[fd].ent_offset = i;

        file_fat_deinit(mydata, bs, volinfo);
        return 0;// fname exist
    }else{
        printf("file %s not found\n",gfd[fd].filename);

        file_fat_deinit(mydata, bs, volinfo);
        return -1; //
    }

Err:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;

}
int getFatVolumeLabel(char *label,char *uuid)
{
    block_dev_desc_t *cur_dev;
    boot_sector *bs = NULL;
    volume_info *volinfo = NULL;
    fsdata *mydata = NULL;
    dir_entry *dentptr=NULL;
    unsigned long cursect = 0;
    __u32 cur_cluster=0;
    block_dev_desc_t *dev_desc=NULL;
    int dev=0;
    int i = 0;
    char *ep=NULL;
	int len = 0;
    dev = (int)simple_strtoul ("0", &ep, 16);
    dev_desc=get_dev("usb",dev);
    if (dev_desc==NULL)
    {
        printf ("\n** Invalid boot device **\n");
        return -1;
    }
    
    if(file_fat_init(&mydata, &bs, &volinfo)){
        printf("Err in fat init!\n");
        goto Err;
    }
    
    cur_dev = dev_desc;
    cursect = mydata->rootdir_sect;
    cur_cluster = ROOT_CLUSTER;

    if (disk_read(cursect, mydata->clust_size, do_fat_read_block) < 0)
    {
        FAT_DPRINT ("Error: reading rootdir block\n");
        goto Err;
    }

    dentptr = (dir_entry *) do_fat_read_block;/*data is in da_fat_read_block*/
    for (i = 0; i < DIRENTSPERBLOCK * (mydata->clust_size); i++)
    {
        if (DELETED_FLAG == dentptr->name[0])
        {
            dentptr++;
            continue;
        }
        else if (ATTR_VOLUME == dentptr->attr)
        {
            if (0 != dentptr->starthi  || 0 != dentptr->start || 0 != dentptr->size)
            {
                dentptr++;
                continue;
            }
			len = sizeof(dentptr->name);
            if (0 == strncmp((const char*)dentptr->name,"           ",len))
            {
                strcpy(label,"NO NAME");
            }
            else
            {
                strncpy(label,(const char*)dentptr->name,len);
            }
            strncpy(uuid,(const char*)volinfo->volume_id,sizeof(volinfo->volume_id));
            goto Done;
        }
        else
        {
            if (0 != (dentptr->attr & ATTR_VOLUME))
            {
                if (ATTR_VFAT != dentptr->attr)
                {
                    break;
                }
            }
            else
            {
                if (0 < dentptr->attr && dentptr->attr < ATTR_VOLUME)
                {
                    dentptr++;
                    continue;
                }
                dentptr->attr = dentptr->attr & (~ATTR_VFAT);
                if (ATTR_DIR != dentptr->attr && ATTR_ARCH != dentptr->attr)
                {
                    break;
                }
            }
        }
        dentptr++;
    }
    len = sizeof(volinfo->volume_label);
    volinfo->volume_label[len - 1] = '\0';

    if ((0 == memcmp((char*)volinfo->volume_label, "           ", len - 1)) || (0 == memcmp("NO NAME    ",(char*)volinfo->volume_label,len - 1)))
    {
        strcpy(label,"NO NAME");
    }
    else
    {
        memcpy(label, (char*)volinfo->volume_label,len);
    }
    memcpy(uuid,(const char*)volinfo->volume_id,sizeof(volinfo->volume_id));

Done:
    file_fat_deinit(mydata, bs, volinfo);
    return 0;
    
Err:
    file_fat_deinit(mydata, bs, volinfo);
    return -1;
}

int fat_init(const char *filename, const char *mode, int rw)
{
    block_dev_desc_t *dev_desc=NULL;
    int size, dev=0, part = 1, fd = 0;
    char *cmd_buf = NULL, *ep=NULL;
    long lPartno = 0;
    char * cPartno = getenv(ENV_PARTNO);
    char bSeekPartition = 1; // flag for seeking all possible partitions of USB

    if(cPartno == NULL) {
        part = lPartno = 1;
    }
    else {
        lPartno = simple_strtol(cPartno, NULL, 10);
        part = lPartno;
        if (part == 0)//env haven't set
            part = lPartno = 1;
            //bSeekPartition = 0;
    }

    dev = (int)simple_strtoul ("0", &ep, 16);
    dev_desc=get_dev("usb", dev);
    if (dev_desc==NULL) {
        printf ("\n** Invalid boot device **\n");
        return -1;
    }
    if (*ep) {
        if (*ep != ':') {
            printf ("\n** Invalid boot device, use `dev[:part]' **\n");
            return -1;
        }
        part = (int)simple_strtoul(++ep, NULL, 16);
    }

    while (1)
    {
        while (fat_register_device(dev_desc,part) != 0)
        {
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if ((bSeekPartition == 0) || (part == lPartno))
            {
                printf("\n** Unable to use %s %d:%d for fat write **\n","usb", dev, part);
			    if (fd > 0)
			    {
				    file_fat_close(fd);
			    }

                return -1;
            }
        }

        if (fd > 0)
        {
            file_fat_close(fd);
        }
        if (rw)  // file open only for write
        {
            fd = file_fat_open(filename, mode);
            if (fd < 0)
            {
                printf("Invalid file descriptor: %d\r\n", fd);
                return -1;
            }
        }
        if (rw)
            size = file_fat_write(fd, ep, 0);
        else{
            size = file_fat_read(filename, ep, 1);
        }
        if (size == -1)
        {
            printf("\n** Unable to r/w \"%s\" from %s %d:%d **\n",filename,"usb",dev,part);
            /* Loop from lPartno to lPartno - 1 */
            part = (part++ % (MAX_FAT_PARTNO + 1))? part : 1;
            if (part == lPartno)
            {
            	if (fd > 0)
                    file_fat_close(fd);
                printf("\n** Unable to use %s %d:%d for fat r/w **\n","usb",dev,part);
                return -1;
            }
        }
        else
        {
            if (part != lPartno)
            {
                cmd_buf = (char *)malloc(CMD_BUF_SIZE);
                if(cmd_buf == NULL)
                {
                    printf("No memory for command buffer!!\n");
                    if (fd > 0)
                        file_fat_close(fd);
                    
                    return -1;
                }
                
                memset(cmd_buf, 0 , CMD_BUF_SIZE);
                snprintf(cmd_buf, CMD_BUF_SIZE, "setenv %s %ld", ENV_PARTNO, part);
                run_command(cmd_buf, 0); // run_command("setenv partno cPartno");

                memset(cmd_buf, 0 , CMD_BUF_SIZE);
                snprintf(cmd_buf, CMD_BUF_SIZE, "saveenv");
                run_command(cmd_buf, 0); // run_command("saveenv");

                free(cmd_buf);
            }

            break;
        }
    }

    return fd;
}

#endif /* #if (CONFIG_COMMANDS & CFG_CMD_FAT) */
