/*
 * (C) Copyright 2011 - 2012 Samsung Electronics
 * EXT4 filesystem implementation in Uboot by
 * Uma Shankar <uma.shankar@samsung.com>
 * Manjunatha C Achar <a.manjunatha@samsung.com>
 *
 * Ext4fs support
 * made from existing cmd_ext2.c file of Uboot
 *
 * (C) Copyright 2004
 * esd gmbh <www.esd-electronics.com>
 * Reinhard Arlt <reinhard.arlt@esd-electronics.com>
 *
 * made from cmd_reiserfs by
 *
 * (C) Copyright 2003 - 2004
 * Sysgo Real-Time Solutions, AG <www.elinos.com>
 * Pavel Bartusek <pba@sysgo.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

/*
 * Changelog:
 *    0.1 - Newly created file for ext4fs support. Taken from cmd_ext2.c
 *            file in uboot. Added ext4fs ls load and write support.
 */

#include <common.h>
#include <part.h>
#include <config.h>
#include <command.h>
#include <image.h>
#include <linux/ctype.h>
#include <asm/byteorder.h>
#include <ext_common.h>
#include <ext4fs.h>
#include <linux/stat.h>
#include <malloc.h>

#if defined CONFIG_GENERIC_MMC
#include <mmc.h>
#endif

#if defined(CONFIG_CMD_USB) && defined(CONFIG_USB_STORAGE)
#include <usb.h>
#endif

#if !defined(CONFIG_DOS_PARTITION) && !defined(CONFIG_EFI_PARTITION)
#error DOS or EFI partition support must be selected
#endif

uint64_t total_sector;
uint64_t part_offset;
static uint64_t part_size;
static uint16_t cur_part = 1;

#define DOS_PART_MAGIC_OFFSET    0x1fe
#define DOS_FS_TYPE_OFFSET    0x36
#define DOS_FS32_TYPE_OFFSET    0x52

static int ext4_register_device(block_dev_desc_t *dev_desc, int part_no);

static int do_ext4_part_load(cmd_tbl_t *cmdtp, int flag, int argc,
                        char *const argv[])
{
    char *filename = NULL;
    char *ep;
    int dev;
    unsigned long part = 1;
    ulong addr = 0;
    ulong part_length;
    int filelen, off = 0;
    disk_partition_t info;
    struct ext_filesystem *fs;
    char buf[12];
    unsigned long count;
    const char *addr_str;
    u32 partnum = 1;
    
    count = 0;
    addr = simple_strtoul(argv[3], NULL, 16);
    filename = getenv("bootfile");
    switch (argc) {
    case 3:
        addr_str = getenv("loadaddr");
        if (addr_str != NULL)
            addr = simple_strtoul(addr_str, NULL, 16);
        else
            addr = CONFIG_SYS_LOAD_ADDR;

        break;
    case 4:
        break;
    case 5:
        filename = argv[4];
        break;
    case 6:
        filename = argv[4];
        off = (int)simple_strtoul(argv[5], NULL, 16);
        break;
    case 7:
        filename = argv[4];
        off = (int)simple_strtoul(argv[5], NULL, 16);
        count = simple_strtoul(argv[6], NULL, 16);
        break;        
    default:
        return cmd_usage(cmdtp);
    }

    if (!filename) {
        puts("** No boot file defined **\n");
        return 1;
    }

#if defined CONFIG_GENERIC_MMC    
    static int curr_device = 0;
    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }
    mmc_init(mmc);
#endif

    dev = (int)simple_strtoul(argv[2], &ep, 16);
    ext4_dev_desc = get_dev(argv[1], dev);
    if (ext4_dev_desc == NULL) {
        printf("** Block device %s %d not supported\n", argv[1], dev);
        return 1;
    }
    if (init_fs(ext4_dev_desc))
        return 1;

    fs = get_fs();
    if (*ep) {
        if (*ep != ':') {
            puts("** Invalid boot device, use `dev[:part]' **\n");
            goto fail;
        }
        part = simple_strtoul(++ep, NULL, 10);
    }

    if (get_partition_info(fs->dev_desc, part, &info)){      
        for(;;){
            if(get_partition_info(fs->dev_desc, partnum, &info))
                break;
            if(!strcmp(ep, (const char *)info.name)){
                part = partnum;
                break;
            }
            partnum++;
        }
    }
    
    if (part != 0) {
        if (get_partition_info(fs->dev_desc, part, &info)) {
            printf("** Bad partition %lu **\n", part);
            goto fail;
        }       
        printf("Loading file \"%s\" at offset 0x%x "
               "from %s device %d partition %s\n",
               filename, off, argv[1], dev, info.name);
    } else {
        printf("Loading file \"%s\" at offset 0x%x from %s device %d\n",
               filename, off, argv[1], dev);
    }

    part_length = ext4fs_set_blk_dev(fs->dev_desc, part);
    if (part_length == 0) {
        printf("**Bad partition - %s %d:%lu **\n", argv[1], dev, part);
        goto fail;
    }
    
    /* register the device and partition */
    if (ext4_register_device(fs->dev_desc, part) != 0) {
        printf("Unable to use %s %d:%lu for fattable\n",
               argv[1], dev, part);
        goto fail;
    }

    /* get the partition information */
    if (!get_partition_info(fs->dev_desc, part, &info)) {
        total_sector = (info.size * info.blksz) / SECTOR_SIZE;
        fs->total_sect = total_sector;
    } else {
        printf("error : get partition info\n");
        goto fail;
    }

    if (!ext4fs_mount(part_length)) {
        printf("** Bad ext4 partition or disk - %s %d:%lu **\n",
               argv[1], dev, part);
        goto fail;
    }

    filelen = ext4fs_open(filename);
    if (filelen < 0) {
        printf("** File not found %s **\n", filename);
        goto fail;
    }
    
    if (filelen < off) {
        printf("** Offset 0x%x too large! **\n", off);
        goto fail;
    }else{
        if(argc!=7)
        {
            count = filelen - off;
        }
    }
    if (ext4fs_part_read((char *)addr, off, count) != count) {
        printf("** Unable to read \"%s\" from %s %d:%lu **\n",
               filename, argv[1], dev, part);
        goto fail;
    }

    /* Loading ok, update default load address */
    load_addr = addr;

    printf("%ld bytes read\n", count);
    sprintf(buf, "%lX", count);
    setenv("filesize", buf);

    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 0;

fail:
    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 1;
}

static int do_ext4_load(cmd_tbl_t *cmdtp, int flag, int argc,
                        char *const argv[])
{
    char *filename = NULL;
    char *ep;
    int dev;
    unsigned long part = 1;
    ulong addr = 0;
    ulong part_length;
    int filelen;
    disk_partition_t info;
    struct ext_filesystem *fs;
    char buf[12];
    unsigned long count;
    const char *addr_str;
    u32 partnum = 1;
    
    count = 0;
    addr = simple_strtoul(argv[3], NULL, 16);
    filename = getenv("bootfile");
    switch (argc) {
    case 3:
        addr_str = getenv("loadaddr");
        if (addr_str != NULL)
            addr = simple_strtoul(addr_str, NULL, 16);
        else
            addr = CONFIG_SYS_LOAD_ADDR;

        break;
    case 4:
        break;
    case 5:
        filename = argv[4];
        break;
    case 6:
        filename = argv[4];
        count = simple_strtoul(argv[5], NULL, 16);
        break;

    default:
        return cmd_usage(cmdtp);
    }

    if (!filename) {
        puts("** No boot file defined **\n");
        return 1;
    }

#if defined CONFIG_GENERIC_MMC    
    static int curr_device = 0;
    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }
    mmc_init(mmc);
#endif

    dev = (int)simple_strtoul(argv[2], &ep, 16);
    ext4_dev_desc = get_dev(argv[1], dev);
    if (ext4_dev_desc == NULL) {
        printf("** Block device %s %d not supported\n", argv[1], dev);
        return 1;
    }
    if (init_fs(ext4_dev_desc))
        return 1;

    fs = get_fs();
    if (*ep) {
        if (*ep != ':') {
            puts("** Invalid boot device, use `dev[:part]' **\n");
            goto fail;
        }
        part = simple_strtoul(++ep, NULL, 10);
    }

    if (get_partition_info(fs->dev_desc, part, &info)){      
        for(;;){
            if(get_partition_info(fs->dev_desc, partnum, &info))
                break;
            if(!strcmp(ep, (const char *)info.name)){
                part = partnum;
                break;
            }
            partnum++;
        }
    }
    
    if (part != 0) {
        if (get_partition_info(fs->dev_desc, part, &info)) {
            printf("** Bad partition %lu **\n", part);
            goto fail;
        }

/*
        if (strncmp((char *)info.type, BOOT_PART_TYPE,
                strlen(BOOT_PART_TYPE)) != 0) {
            printf("** Invalid partition type \"%s\""
                   " (expect \"" BOOT_PART_TYPE "\")\n", info.type);
            return 1;
        }
*/        
        printf("Loading file \"%s\" "
               "from %s device %d partition %s\n",
               filename, argv[1], dev, info.name);
    } else {
        printf("Loading file \"%s\" from %s device %d\n",
               filename, argv[1], dev);
    }

    part_length = ext4fs_set_blk_dev(fs->dev_desc, part);
    if (part_length == 0) {
        printf("**Bad partition - %s %d:%lu **\n", argv[1], dev, part);
        goto fail;
    }
    
    /* register the device and partition */
    if (ext4_register_device(fs->dev_desc, part) != 0) {
        printf("Unable to use %s %d:%lu for fattable\n",
               argv[1], dev, part);
        goto fail;
    }

    /* get the partition information */
    if (!get_partition_info(fs->dev_desc, part, &info)) {
        total_sector = (info.size * info.blksz) / SECTOR_SIZE;
        fs->total_sect = total_sector;
    } else {
        printf("error : get partition info\n");
        goto fail;
    }

    if (!ext4fs_mount(part_length)) {
        printf("** Bad ext4 partition or disk - %s %d:%lu **\n",
               argv[1], dev, part);
        goto fail;
    }

    filelen = ext4fs_open(filename);
    if (filelen < 0) {
        printf("** File not found %s\n", filename);
        goto fail;
    }
    if ((count < filelen) && (count != 0))
        filelen = count;

    if (ext4fs_read((char *)addr, filelen) != filelen) {
        printf("** Unable to read \"%s\" from %s %d:%lu **\n",
               filename, argv[1], dev, part);
        goto fail;
    }
    
    /* Loading ok, update default load address */
    load_addr = addr;

    printf("%d bytes read\n", filelen);
    sprintf(buf, "%X", filelen);
    setenv("filesize", buf);

    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 0;

fail:
    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 1;
}

static int do_ext4_ls(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    const char *filename = "/";
    int dev;
    unsigned long part = 1;
    char *ep;
    struct ext_filesystem *fs;
    int part_length;
    disk_partition_t info;    
    u32 partnum = 1;
    
    if (argc < 3)
        return cmd_usage(cmdtp);

#if defined CONFIG_GENERIC_MMC    
    static int curr_device = 0;
    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }
    mmc_init(mmc);
#endif

    dev = (int)simple_strtoul(argv[2], &ep, 16);
    ext4_dev_desc = get_dev(argv[1], dev);

    if (ext4_dev_desc == NULL) {
        printf("\n** Block device %s %d not supported\n", argv[1], dev);
        return 1;
    }

    if (init_fs(ext4_dev_desc))
        return 1;

    fs = get_fs();
    if (*ep) {
        if (*ep != ':') {
            puts("\n** Invalid boot device, use `dev[:part]' **\n");
            goto fail;
        }
        part = simple_strtoul(++ep, NULL, 10);
    }
 
    if (get_partition_info(fs->dev_desc, part, &info)){     
        for(;;){
            if(get_partition_info(fs->dev_desc, partnum, &info))
                break;
            if(!strcmp(ep, (const char *)info.name)){
                part = partnum;
                break;
            }
            partnum++;
        }
    }
  
    if (argc == 4)
        filename = argv[3];

    part_length = ext4fs_set_blk_dev(fs->dev_desc, part);
    if (part_length == 0) {
        printf("** Bad partition - %s %d:%lu **\n", argv[1], dev, part);
        goto fail;
    }
    
    /* register the device and partition */
    if (ext4_register_device(fs->dev_desc, part) != 0) {
        printf("Unable to use %s %d:%lu for fattable\n",
               argv[1], dev, part);
        goto fail;
    }

    /* get the partition information */
    if (!get_partition_info(fs->dev_desc, part, &info)) {
        total_sector = (info.size * info.blksz) / SECTOR_SIZE;
        fs->total_sect = total_sector;
    } else {
        printf("error : get partition info\n");
        goto fail;
    }

    if (!ext4fs_mount(part_length)) {
        printf("** Bad ext4 partition or disk - %s %d:%lu **\n",
               argv[1], dev, part);
        goto fail;
    }
    if (ext4fs_ls(filename)) {
        printf("** Error ext4fs_ls() **\n");
        goto fail;
    };

    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 0;

fail:    
    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 1;    
    
}

static int do_ext4_filesize(cmd_tbl_t *cmdtp, int flag, int argc,
                        char *const argv[])
{
    char *filename = NULL;
    char *ep;
    int dev;
    unsigned long part = 1;
    ulong part_length;
    u32  filelen;
    u32 *size;
    disk_partition_t info;
    struct ext_filesystem *fs;
    u32 partnum = 1;

    filename = argv[3];

    if (!filename) {
        puts("** Invalid file name **\n");
        return 1;
    }

#if defined CONFIG_GENERIC_MMC    
    static int curr_device = 0;
    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }
    mmc_init(mmc);
#endif

    dev = (int)simple_strtoul(argv[2], &ep, 16);
    ext4_dev_desc = get_dev(argv[1], dev);
    if (ext4_dev_desc == NULL) {
        printf("** Block device %s %d not supported\n", argv[1], dev);
        return 1;
    }
    if (init_fs(ext4_dev_desc))
        return 1;

    fs = get_fs();
    if (*ep) {
        if (*ep != ':') {
            puts("** Invalid boot device, use `dev[:part]' **\n");
            goto fail;
        }
        part = simple_strtoul(++ep, NULL, 10);
    }

    if (get_partition_info(fs->dev_desc, part, &info)){     
        for(;;){
            if(get_partition_info(fs->dev_desc, partnum, &info))
                break;
            if(!strcmp(ep, (const char *)info.name)){
                part = partnum;
                break;
            }
            partnum++;
        }
    }
                
    if ((part != 0) && (get_partition_info(fs->dev_desc, part, &info))) {
        printf("** Bad partition %lu **\n", part);
        goto fail;
    } 

    part_length = ext4fs_set_blk_dev(fs->dev_desc, part);
    if (part_length == 0) {
        printf("**Bad partition - %s %d:%lu **\n", argv[1], dev, part);
        goto fail;
    }

    /* register the device and partition */
    if (ext4_register_device(fs->dev_desc, part) != 0) {
        printf("Unable to use %s %d:%lu for fattable\n",
               argv[1], dev, part);
        goto fail;
    }

    /* get the partition information */
    if (!get_partition_info(fs->dev_desc, part, &info)) {
        total_sector = (info.size * info.blksz) / SECTOR_SIZE;
        fs->total_sect = total_sector;
    } else {
        printf("error : get partition info\n");
        goto fail;
    }

    if (!ext4fs_mount(part_length)) {
        printf("** Bad ext4 partition or disk - %s %d:%lu **\n",
               argv[1], dev, part);
        goto fail;
    }

    filelen = ext4fs_open(filename);
    if (filelen < 0) {
        printf("** File not found %s\n", filename);
        goto fail;
    }

    if(part !=0){
        printf("Size of file \"%s\" from %s device %d partition %s: %d bytes\n",
                filename, argv[1], dev, info.name, filelen);
    }else{
        printf("Size of file \"%s\" from %s device %d Size: %d bytes\n",
                filename, argv[1], dev, filelen);
    }
    size = (u32*)simple_strtoul(argv[4], NULL, 16);
    *size = filelen;   

    ext4fs_close();
    deinit_fs(fs->dev_desc);    
    return 0;

fail:    
    ext4fs_close();
    deinit_fs(fs->dev_desc);
    return 1;      
}

static int ext4_register_device(block_dev_desc_t *dev_desc, int part_no)
{
    disk_partition_t info;

    if (!dev_desc->block_read)
        return -1;

    /* First we assume there is a MBR */
    if (!get_partition_info(dev_desc, part_no, &info)) {
        part_offset = info.start;
        cur_part = part_no;
        part_size = info.size;
    } else {
        printf("** Partition %d not valid on device %d **\n",
               part_no, dev_desc->dev);
        return -1;
    }

    return 0;
}

#if defined(CONFIG_CMD_EXT4_WRITE)
static int do_ext4_write(cmd_tbl_t *cmdtp, int flag, int argc,
                char *const argv[])
{
    const char *filename = "/";
    int part_length;
    unsigned long part = 1;
    int dev;
    char *ep;
    unsigned long ram_address;
    unsigned long file_size;
    disk_partition_t info;
    struct ext_filesystem *fs;
    u32 partnum = 1;
    
    if (argc < 6)
        return cmd_usage(cmdtp);
    
#if defined CONFIG_GENERIC_MMC    
    static int curr_device = 0;
    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }
    mmc_init(mmc);
#endif

    dev = (int)simple_strtoul(argv[2], &ep, 16);
    ext4_dev_desc = get_dev(argv[1], dev);
    if (ext4_dev_desc == NULL) {
        printf("Block device %s %d not supported\n", argv[1], dev);
        return 1;
    }
    if (init_fs(ext4_dev_desc))
        return 1;

    fs = get_fs();
    if (*ep) {
        if (*ep != ':') {
            puts("Invalid boot device, use `dev[:part]'\n");
            goto fail;
        }
        part = simple_strtoul(++ep, NULL, 10);
    }
    
    if (get_partition_info(fs->dev_desc, part, &info)){ 
        for(;;){
            if(get_partition_info(fs->dev_desc, partnum, &info))
                break;
            if(!strcmp(ep, (const char *)info.name)){
                part = partnum;
                break;
            }
            partnum++;
        }
    }
    
    /* get the filename */
    filename = argv[3];

    /* get the address in hexadecimal format (string to int) */
    ram_address = simple_strtoul(argv[4], NULL, 16);

    /* get the filesize in base 10 format */
    file_size = simple_strtoul(argv[5], NULL, 10);

    /* set the device as block device */
    part_length = ext4fs_set_blk_dev(fs->dev_desc, part);
    if (part_length == 0) {
        printf("Bad partition - %s %d:%lu\n", argv[1], dev, part);
        goto fail;
    }

    /* register the device and partition */
    if (ext4_register_device(fs->dev_desc, part) != 0) {
        printf("Unable to use %s %d:%lu for fattable\n",
               argv[1], dev, part);
        goto fail;
    }

    /* get the partition information */
    if (!get_partition_info(fs->dev_desc, part, &info)) {
        total_sector = (info.size * info.blksz) / SECTOR_SIZE;
        fs->total_sect = total_sector;
    } else {
        printf("error : get partition info\n");
        goto fail;
    }

    /* mount the filesystem */
    if (!ext4fs_mount(part_length)) {
        printf("Bad ext4 partition %s %d:%lu\n", argv[1], dev, part);
        goto fail;
    }

    /* start write */
    if (ext4fs_write(filename, (unsigned char *)ram_address, file_size)) {
        printf("** Error ext4fs_write() **\n");
        goto fail;
    }
    ext4fs_close();
    deinit_fs(fs->dev_desc);

    return 0;

fail:
    ext4fs_close();
    deinit_fs(fs->dev_desc);

    return 1;
}

U_BOOT_CMD(ext4write, 6, 1, do_ext4_write,
    "create a file in the root directory",
    "<interface> <dev[:part id/name]> [Absolute filename path] [Address] [sizebytes]\n"
    "      - create a file in / directory");

#endif

U_BOOT_CMD(ext4ls, 4, 1, do_ext4_ls,
       "list files in a directory (default /)",
       "<interface> <dev[:part id/name]> [directory]\n"
       "      - list files from 'dev' partition 'part' on 'interface' in a 'directory'");

U_BOOT_CMD(ext4partload, 7, 0, do_ext4_part_load,
       "part load binary file from a Ext4 filesystem",
       "<interface> <dev[:part id/name]> [addr] [filename] [offset] [bytes]\n"
       "      - load binary file 'filename' from 'dev' partition 'part' on 'interface'\n"
       "         to address 'addr' from ext4 filesystem");

U_BOOT_CMD(ext4load, 6, 0, do_ext4_load,
       "load binary file from a Ext4 filesystem",
       "<interface> <dev[:part id/name]> [addr] [filename] [bytes]\n"
       "      - load binary file 'filename' from 'dev' partition 'part' on 'interface'\n"
       "         to address 'addr' from ext4 filesystem");

U_BOOT_CMD(ext4filesize, 5, 0, do_ext4_filesize,
       "get file size from a Ext4 filesystem",
       "<interface> <dev[:part id/name]> [filename] [addr]\n"
       "      - get file 'filename' size from 'dev' partition 'part' on 'interface'\n"
       "         to address 'addr'");

