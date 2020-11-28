/*
 * (C) Copyright 2003
 * Kyle Harris, kharris@nexus-tech.net
 *
 * See file CREDITS for list of people who contributed to this
 * project.
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
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <mmc.h>
#include <malloc.h>
#include <watchdog.h>
#include <fat.h>
#include <drvWDT.h>
#include <MsMath.h>
#include <MsMmc.h>
#include <u-boot/crc.h>

#ifdef CONFIG_LZO
#include <linux/lzo.h>
#endif
#include "eMMC.h"
#include "../disk/part_emmc.h"
#include <CusRawIO.h>

#define MMC_SPEED_TEST      0
#define TEST_PERFORMANCE    0
#define EMMC_BLK_SZ         512
#define EMMC_RW_SHIFT       9
#define FAT_BUFFER_LEN      0x9AB000
#define EMMC_BIN_NAME       "emmc.bin"
#define EMMC_BOOT1_NAME      "boot1.bin"
#define EMMC_BOOT2_NAME      "boot2.bin"
#define EMMC_BOOT_NAME       "boot.bin"  // include boot1 and boot2
#define EMMC_CRC32_INIT 0xFFFFFFFFU
#define TRIM_START_OFFSET   (0x700000/512)
#define EMPTY_CHECK_BLK_NUM 0x800
#ifdef CONFIG_DOUBLE_MBOOT
#define EMMC_MBOOT_PATITION_START_V2 "0x200000"
#define EMMC_MBOOT_PATITION_SIZE_V2 "0x300000"
#define EMMC_MPOOL_PATITION_START_V2 "0x500000"
#define EMMC_MPOOL_PATITION_SIZE_V2 "0x200000"
#define EMMC_MBOOT_PATITION_START_V3 "0x200000"
#define EMMC_MBOOT_PATITION_SIZE_V3 "0x300000"
#define EMMC_MPOOL_PATITION_START_V3 "0x500000"
#define EMMC_MPOOL_PATITION_SIZE_V3 "0xA00000"
#define EMMC_MBOOTBAK_PATITION_START_V3 "0x1000000"
#define EMMC_MBOOTBAK_PATITION_SIZE_V3 "0x300000"
#else
#define EMMC_MBOOT_PATITION_START "0x200000"
#define EMMC_MBOOT_PATITION_SIZE "0x300000"
#define EMMC_MPOOL_PATITION_START "0x500000"
#define EMMC_MPOOL_PATITION_SIZE "0x200000"
#endif

#ifdef STATIC_RELIABLE_TEST
int do_test_reliable_write(void);
#endif

extern __u16 g_emmc_reserved_for_map;
unsigned char tmp_buf[EMMC_BLK_SZ];
static int curr_device = -1;

#ifdef CONFIG_LZO
static u32 unlzo_partition_blkcnt = 0;
#endif

static u32 do_mmc_empty_check(const void *buf, u32 len, u32 empty_flag);

#ifndef CONFIG_GENERIC_MMC
int do_mmc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int dev;

    if (argc < 2)
        return cmd_usage(cmdtp);

    if (strcmp(argv[1], "init") == 0) {
        if (argc == 2) {
            if (curr_device < 0)
                dev = 1;
            else
                dev = curr_device;
        } else if (argc == 3) {
            dev = (int)simple_strtoul(argv[2], NULL, 10);
        } else {
            return cmd_usage(cmdtp);
        }

#if 1 //TODO: fix it. mmc_legacy_init() is not available
        puts("mmc_legacy_init() is not available!\n");
        if (1) {
#else
        if (mmc_legacy_init(dev) != 0) {
#endif
            puts("No MMC card found\n");
            return 1;
        }

        curr_device = dev;
        printf("mmc%d is available\n", curr_device);
    } else if (strcmp(argv[1], "device") == 0) {
        if (argc == 2) {
            if (curr_device < 0) {
                puts("No MMC device available\n");
                return 1;
            }
        } else if (argc == 3) {
            dev = (int)simple_strtoul(argv[2], NULL, 10);

#ifdef CONFIG_SYS_MMC_SET_DEV
            if (mmc_set_dev(dev) != 0)
                return 1;
#endif
            curr_device = dev;
        } else {
            return cmd_usage(cmdtp);
        }

        printf("mmc%d is current device\n", curr_device);
    } else {
        return cmd_usage(cmdtp);
    }

    return 0;
}
#else /* !CONFIG_GENERIC_MMC */

/*
void dump_mem_line(char *buf, int cnt)
{
    int i;
    for(i = 0; i< cnt; i ++)
        printf("%02X ", (unsigned char)buf[i]);
    printf("|");
    for(i = 0; i< cnt; i ++)
        printf("%c", (buf[i] >= 32 && buf[i] < 128) ? buf[i] : '.');

    printf("\n");
}

void dump_mem(char *buf, int count)
{
    int i;
    for(i = 0; i < count; i +=16) {
        printf("%04d %04Xh: ", i, i);
        dump_mem_line(buf + i, 16);
        if(i%512==496) printf("\n");
    }
}
*/

#define LEAPDEF_NAME "LEAP.DEF"
#define FORCREAT_NAME "FORCT.DEF"
#define DEF_HEADER "GROUP DEFINE2\0\0\0"

static int write_mmcdef_leap(unsigned int partnum, struct mmc_bininfo *bininfo)
{
    int fd, ret = 0, last;
    u_char *buf = (u_char *)UPGRADE_BUFFER_ADDR;

    last = partnum & 0x8000;
    partnum &= ~0x8000;

    fd = fat_init(LEAPDEF_NAME, "a", 1);
    if(fd < 0){
        printf("[%s]: fat ini file %s failed\n", __func__, LEAPDEF_NAME);
        return -1;
    }

    if(last){
        memset(buf, 0xFF, 0x10);
        flush_cache((ulong)buf, 0x10);
        ret = file_fat_write(fd, buf, 0x10);
        if(ret < 0)
            printf("[%s]: write failed 1\n", __func__);
        return ret;
    }

    if(partnum == 0){
        file_fat_write(fd, DEF_HEADER, 0x10);
        if(ret < 0){
            printf("[%s]: write failed 2\n", __func__);
            return ret;
        }
    }

    *((ulong *)buf) = cpu_to_le32(0x00000001);
    *((ulong *)(buf + 0x4)) = cpu_to_le32(bininfo->dpt.start);
    *((ulong *)(buf + 0x8)) = cpu_to_le32(bininfo->dpt.start + bininfo->dpt.size - 1);
    *((ulong *)(buf + 0xc)) = cpu_to_le32(bininfo->valid_block);
    flush_cache((ulong)buf, 0x10);

    ret = file_fat_write(fd, (unsigned char *) buf, 0x10);
    if(ret < 0){
        printf("[%s]: write failed 3\n", __func__);
        return ret;
    }

    file_fat_close(fd);
    return 0;
}

static int write_mmcdef_forcreate(unsigned int partnum, struct mmc_bininfo *bininfo)
{
    int fd, ret, last;
    u_char *buf = (u_char *)UPGRADE_BUFFER_ADDR;

    last = partnum & 0x8000;
    partnum &= ~0x8000;

    fd = fat_init(FORCREAT_NAME, "a", 1);
    if(fd < 0){
        printf("[%s]: fat ini file %s failed\n", __func__, LEAPDEF_NAME);
        return -1;
    }

    if(partnum == 0){
        ret = file_fat_write(fd, DEF_HEADER, 0x10);
        if(ret < 0){
            printf("[%s]: write failed 1\n", __func__);
            return ret;
        }
    }

    *((ulong *)buf) = cpu_to_le32(0x0);
    *((ulong *)(buf+ 0x4)) = cpu_to_le32(bininfo->dpt.start);
    *((ulong *)(buf + 0x8)) = cpu_to_le32(bininfo->dpt.start + bininfo->dpt.size - 1);
    *((ulong *)(buf + 0xc)) = cpu_to_le32(bininfo->valid_block);
    flush_cache((ulong)buf, 0x10);

    ret = file_fat_write(fd, (unsigned char *) buf, 0x10);
    if(ret < 0){
        printf("[%s]: write failed 1\n", __func__);
        return ret;
    }

    file_fat_close(fd);
    return 0;
}

static int do_mmcpart_bininfo(int partnum, struct mmc_bininfo *bininfo)
{
    int i, ret = 0;
    int num;
    u32 empty_flag;
    unsigned char *buf;
    block_dev_desc_t *mmc_dev=NULL;
    struct mmc *mmc = NULL;

    if(!bininfo){
        printf("[%s]: NULL pointer\n", __func__);
        return -1;
    }

    if(partnum < 0){
        printf("[%s]: Invalid part num %d\n", __func__, partnum);
        return -1;
    }

    if (curr_device < 0) {
        if (get_mmc_num() > 0)
            curr_device = 0;
        else {
            puts("No MMC device available\n");
            return -1;
        }
    }

    mmc_dev = mmc_get_dev(curr_device);
    if ((mmc_dev == NULL) || (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
        printf("no mmc device found!\n");
        return -1;
    }

    mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }

    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    buf = (unsigned char *)malloc(EMPTY_CHECK_BLK_NUM * EMMC_BLK_SZ);
    if(!buf){
        printf("[%s]: malloc failed\b\n", __func__);
        ret = -1;
        goto out1;
    }

    if(mmc->ext_csd[181] == 0){
        empty_flag = 0;
    }
    else{
        empty_flag = ~0;
    }

    if(partnum == 0){//Check process block in partition table
        int ptbl_blk = EMMC_RESERVED_FOR_MAP_V2 + 1;
        for(i = 0; i < ptbl_blk; i += num){
            num = EMPTY_CHECK_BLK_NUM;
            if(num > ptbl_blk - i)
                num = ptbl_blk - i;

            if(mmc->block_dev.block_read(curr_device, ptbl_blk - i - num, num, buf) != num){
                printf("[%s]: emmc read partition table, block %x failed \n", __func__, ptbl_blk - i - num);
                ret = -1;
                goto out2;
            }
            ret = do_mmc_empty_check(buf, num * EMMC_BLK_SZ, empty_flag);
            if(ret < 0){
                printf("[%s]: emmc empty check partition table, block %x failed\n", __func__, ptbl_blk - i - num);
                goto out2;
            }
            if(ret)
                break;
        }
        bininfo->valid_block = ptbl_blk - i;
        bininfo->dpt.size = EMMC_RESERVED_FOR_MAP_V2 + 1;
        bininfo->dpt.start = 0;
        bininfo->dpt.blksz = EMMC_BLK_SZ;
        strcpy((char *)(bininfo->dpt.name), "partition tbl");
    }
    else{//Check common partitions in partition table
        ret = get_partition_info_emmc(mmc_dev, partnum, &(bininfo->dpt));
        if(ret < 0){
            goto out2;
        }
        for(i = 0; i < bininfo->dpt.size; i += num){
            num = EMPTY_CHECK_BLK_NUM;
            if(num > bininfo->dpt.size - i)
                num = bininfo->dpt.size;

            if(mmc->block_dev.block_read(curr_device, bininfo->dpt.start + bininfo->dpt.size - i - num, num, buf) != num){
                printf("[%s]: emmc read part %s, block %lx failed\n",
                    __func__,
                    bininfo->dpt.name,
                    bininfo->dpt.start + bininfo->dpt.size - i - num);
                ret = -1;
                goto out2;
            }
            ret = do_mmc_empty_check(buf, num * EMMC_BLK_SZ, empty_flag);
            if(ret < 0){
                printf("[%s]: emmc check empty part %s, block %lx failed\n",
                    __func__,
                    bininfo->dpt.name,
                    bininfo->dpt.start + bininfo->dpt.size - i - num);
                goto out2;
            }
            if(ret)
                break;
        }
        bininfo->valid_block = bininfo->dpt.size - i;
    }

out2:
    free(buf);
out1:
    return ret;
}

int do_mmc_bininfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int i, ret = 0, port = 0;
    struct mmc_bininfo bininfo;
    char usb_start_command[20];

    if(argc > 1){
        port = (int)simple_strtoul (argv[1], NULL, 16);
        sprintf(usb_start_command,"usb start %d",port);
        run_command(usb_start_command, 0);
    }

    printf("%-15s%-15s%-15s%-15s\n", "part", "start block", "end block", "process block");

    for(i = 0; i <= EMMC_RESERVED_FOR_MAP_V2; i++){
        memset(&bininfo, 0, sizeof(struct mmc_bininfo));
        ret = do_mmcpart_bininfo(i, &bininfo);
        if(ret < 0){
            printf("[%s]: check bininfo of part %d failed\n", __func__, i);
            return ret;
        }
        if(bininfo.dpt.size == 0)
            break;
        printf("%-15s0x%-15lx0x%-15lx0x%-15lx\n",
            bininfo.dpt.name,
            bininfo.dpt.start,
            bininfo.dpt.start + bininfo.dpt.size - 1,
            bininfo.valid_block);

        if(argc > 1){
            ret = write_mmcdef_leap(i, &bininfo);
            if(ret < 0)
                break;
            ret = write_mmcdef_forcreate(i, &bininfo);
            if(ret < 0)
                break;
        }
    }

    //Leap def file need 0xFF int the end
    if(argc > 1)
        ret = write_mmcdef_leap(0x8000, NULL);

    return ret;
}

static void print_mmcinfo(struct mmc *mmc)
{
    printf("Device: %s\n", mmc->name);
    printf("Manufacturer ID: %x\n", mmc->cid[0] >> 24);
    printf("OEM: %x\n", (mmc->cid[0] >> 8) & 0xff);
    printf("Name: %c%c%c%c%c \n", mmc->cid[0] & 0xff,
            (mmc->cid[1] >> 24), (mmc->cid[1] >> 16) & 0xff,
            (mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);

    printf("Tran Speed: %d\n", mmc->tran_speed);
    printf("Rd Block Len: %d\n", mmc->read_bl_len);

    printf("%s version %d.%d\n", IS_SD(mmc) ? "SD" : "MMC",
            (mmc->version >> 4) & 0xf, mmc->version & 0xf);

    printf("High Capacity: %s\n", mmc->high_capacity ? "Yes" : "No");
    puts("Capacity: ");
    print_size(mmc->capacity, "\n");

    printf("Bus Width: %d-bit\n", mmc->bus_width);
}

int do_mmcinfo (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    struct mmc *mmc;

    if (curr_device < 0) {
        if (get_mmc_num() > 0)
            curr_device = 0;
        else {
            puts("No MMC device available\n");
            return 1;
        }
    }

    mmc = find_mmc_device(curr_device);

    if (mmc) {
        mmc_init(mmc);

        print_mmcinfo(mmc);
        return 0;
    } else {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }
}

void dump_register(unchar *ext_csd)
{
    int i;

    printf("Show eMMC Extended CSD:");
    for(i=0; i<512; i++)
    {
        if ((i%32)==0)
        {
            printf("\r\n");
            printf("%03d : ", i);
        }
        printf("%02X ", ext_csd[i]);
    }
    printf("\r\n");
}

int do_mmcreg (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    switch (argc) {
    case 4:
        if (strcmp(argv[1], "show") == 0) {
            int dev = simple_strtoul(argv[3], NULL, 10);
            struct mmc *mmc = find_mmc_device(dev);

            if (!mmc)
                return 1;

            if (mmc_init(mmc)) {
                printf("mmc init fail\r\n");
                return 1;
             }

            dump_register((unchar *)mmc->ext_csd);
            return 0;
        }
    default:
        return 0;
    }
}

#if defined(CONFIG_USB) && defined(CONFIG_FAT)
int emmc_write_opts(const emmc_write_options_t *opts, u64 size, u64 wtoffset)
{
        int imglen = 0, fat_read_len = 0, ret=0;
        int percent_complete = -1;
        u64 imgoffset = opts->offset;
        u64 emmcoffset = 0;
        ulong writestartblk, writeblkcnt;

        struct mmc *mmc = find_mmc_device(curr_device);
        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }

        if(!mmc->has_init){
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }

        /* get image length */
        imglen = opts->length;

        if (imglen > mmc->capacity)
        {
            printf("Input block does not fit into device\n");
            return -1;
        }

        if (!opts->quiet)
        {
            printf("\n");
        }

        /* get data from input and write to the device */
        while (imglen && (imgoffset < size))
        {

            WATCHDOG_RESET ();

            if (imglen >= FAT_BUFFER_LEN)
            {
                fat_read_len = FAT_BUFFER_LEN;
            }
            else
            {
                fat_read_len = imglen;
            }

            fat_init(opts->fatfile_name, "a", 0);

            ret = file_fat_part_read (opts->fatfile_name, (unsigned long *)(opts->buffer), imgoffset, fat_read_len);
            flush_cache((ulong)opts->buffer, fat_read_len);

            if(ret == -1) {
                printf("\n** Unable to read \"%s\" **\n", opts->fatfile_name);
                return 1;
            }
            if(opts->pad)
                writestartblk = ALIGN((imgoffset + wtoffset), 512) / 512;
            else
                writestartblk = ALIGN((emmcoffset + wtoffset), 512) / 512;
            writeblkcnt = ALIGN(fat_read_len, 512) / 512;
            if(writeblkcnt != mmc->block_dev.block_write(curr_device, writestartblk, writeblkcnt, opts->buffer)){
                printf("\n** Unable to write data at emmc offset 0x%llx **\n", imgoffset + wtoffset);
                return 1;
            }

            imglen -= fat_read_len;

            if (!opts->quiet)
            {
                    int percent = (int)
                            ((unsigned long long)
                            (opts->length-imglen) * 100
                            / opts->length);
                    /* output progress message only at whole percent
                    * steps to reduce the number of messages printed
                    * on (slow) serial consoles
                    */
                    if (percent != percent_complete)
                    {
                            if(opts->pad)
                                    printf("\rWriting data at 0x%llx " "-- %3d%% complete.\n", imgoffset + wtoffset, percent);
                            else
                                    printf("\rWriting data at 0x%llx " "-- %3d%% complete.\n", emmcoffset + wtoffset, percent);
                            percent_complete = percent;
                    }
            }
            emmcoffset += fat_read_len;
            imgoffset += fat_read_len;
        }

        if (!opts->quiet)
        {
            printf("\n");
        }

        if (imglen > 0)
        {
            printf("Data did not fit into device, imglen= 0x%x\n",imglen);
            return -1;
        }

        /* return happy */
        return 0;
}

/* read bin file and restore it to emmc */
int do_emmc_bin_restore(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
        emmc_write_options_t opts;
        int port=0,ret=0, pad = 1;
        ulong imagesize, imagesizebak;
        u64 offset=0;
        disk_partition_t dpt;
        block_dev_desc_t *mmc_dev=NULL;
        ulong blk = 0, partnum = 1;
	  char usb_start_command[20];

        if (curr_device < 0) {
            if (get_mmc_num() > 0)
                    curr_device = 0;
            else {
                    puts("No MMC device available\n");
                    return 1;
            }
        }

        struct mmc *mmc = find_mmc_device(curr_device);
        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }

        if(!mmc->has_init){
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }

        memset(&opts, 0, sizeof(opts));
        opts.buffer = (unsigned long*)UPGRADE_BUFFER_ADDR;
        opts.fatfile_name = EMMC_BIN_NAME;
        opts.length = 0x1EF0000;
        opts.quiet      = 0;

        port = (int)simple_strtoul (argv[1], NULL, 16);
        sprintf(usb_start_command,"usb start %d",port);
        run_command(usb_start_command, 0);

        if(argc > 2){
            pad = simple_strtoull(argv[2], NULL, 16);
            opts.pad = pad;
        }

        if(argc >3){
            opts.fatfile_name = argv[3];
        }

        if(argc > 4){
            blk = (ulong) (ALIGN(simple_strtoull(argv[4], NULL, 16), 512) / 512);
        }

        mmc_dev = mmc_get_dev(curr_device);
        if ((mmc_dev == NULL) || (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
            printf("no mmc device found!\n");
            return -1;
        }

        //No Pad mode restore
        if(!pad){
            int fd, i;
            ulong start, end, valid;
            u64 emmcoffset = 0;
            ulong defsize;
            char *deffile = LEAPDEF_NAME;
            uchar *defbuf;

            fd = fat_init(deffile, "a", 0);
            defsize = (ulong) file_fat_filesize(deffile);

            defbuf = (uchar *)malloc(defsize);
            if(!defbuf){
                printf("malloc failed\n");
                return -1;
            }

            ret = file_fat_part_read (deffile, defbuf, 0, defsize);
            if(ret < 0){
                printf("read failed\n");
                free(defbuf);
                return ret;
            }

            if(strcmp((char *)defbuf, DEF_HEADER)){
                printf("def file head wrong\n");
                free(defbuf);
                return -1;
            }
            for(i = 1; i <= 0x10; i++){
                if(defbuf[defsize - i] != 0xFF){
                    printf("def file end wrong\n");
                    free(defbuf);
                    return -1;
                }
            }
            for(i = 0x10; i < defsize - 0x10; i += 0x10){
                start = *((ulong *)(defbuf + i + 4));
                end = *((ulong *)(defbuf + i + 8));
                valid = *((ulong *)(defbuf + i + 12));

                start = le32_to_cpu(start);
                end = le32_to_cpu(end);
                valid = le32_to_cpu(valid);

                printf("start %lx, end %lx, valid %lx\n", start, end, valid);
                if(start + valid > end + 1){
                    printf("Error: restore size large than partition size\n");
                    free(defbuf);
                    return -1;
                }

                opts.length = valid * EMMC_BLK_SZ;
                emmcoffset = start * EMMC_BLK_SZ;

                ret = emmc_write_opts(&opts, mmc->capacity - emmcoffset, emmcoffset);
                flush_cache((ulong)opts.buffer, opts.length);
                if(ret){
                    printf("Emmc write failed\n");
                    free(defbuf);
                    return ret;
                }
                opts.offset += opts.length;
            }
            free(defbuf);
            return ret;
        }

        //Get the partition offset from partition name
        for(;;)
        {
            if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
                break;
            if(!strcmp(argv[3], (const char *)dpt.name)){
                blk = dpt.start;
                break;
            }
            partnum++;
        }

        if(blk)
            offset = blk << 9;

        if((offset < 0) || (offset > mmc->capacity))
            offset = 0;

        imagesizebak = imagesize = file_fat_filesize(opts.fatfile_name);
        if(imagesize > (mmc->capacity - offset)){
            printf("\n Warning: image too big, check the emmc size and the image file name!\n");
            imagesize = mmc->capacity - offset;
//            return -1;
        }

        if(opts.length > imagesize)
            opts.length = imagesize;

        printf("\n %s size:0x%lx, Write start at emmc offset 0x%llx \n",
            opts.fatfile_name,imagesize,offset);

        for(opts.offset = 0; opts.offset < imagesize;){
            memset(opts.buffer, 0x00, opts.length);
            ret = emmc_write_opts(&opts, (u64)imagesize, offset);
            flush_cache((ulong)opts.buffer, opts.length);
            if(ret)
                return ret;
            opts.offset += opts.length;
            if(opts.offset + opts.length > imagesize)
                opts.length = imagesize - opts.offset;
        }

        printf("\n Restore Success!\n");
        printf("IMAGE SIZE: %ld bytes\n", imagesizebak);
        printf("RESTORED SIZE: %ld bytes\n", imagesize);
        if(imagesizebak > imagesize)
            printf("WARNING: SKIP THE IMAGE TAIL %ld bytes\n",imagesizebak - imagesize);

        return 0;
}

int emmc_read_opts(const emmc_read_options_t *opts, u64 size, u64 rdoffset)
{
        int imglen = 0, fat_read_len = 0, ret=0, fd=0;
        int percent_complete = -1;
        u64 imgoffset = opts->offset;
        ulong readstartblk, readblkcnt;

        struct mmc *mmc = find_mmc_device(curr_device);
        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }

        if(!mmc->has_init){
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }

        /* get image length */
        imglen = opts->length;

        if (imglen > mmc->capacity)
        {
            printf("Input block does not fit into device\n");
            return -1;
        }

        if (!opts->quiet)
        {
            printf("\n");
        }

        /* get data from input and write to the device */
        while (imglen && (imgoffset < size))
        {

            WATCHDOG_RESET ();

            if (imglen >= FAT_BUFFER_LEN)
            {
                fat_read_len = FAT_BUFFER_LEN;
            }
            else
            {
                fat_read_len = imglen;
            }

            readstartblk = ALIGN((imgoffset + rdoffset), 512) / 512;
            readblkcnt = ALIGN(fat_read_len, 512) / 512;
            if (opts->bootno == 0)
            {
                if(readblkcnt !=
                    mmc->block_dev.block_read(curr_device, readstartblk, readblkcnt, opts->buffer)){
                    printf("\n** Unable to read data at emmc offset 0x%llx **\n", imgoffset + rdoffset);
                    return 1;
                }
            }
            else
            {
                if(0 !=
                    eMMC_ReadBootPart(opts->buffer, readblkcnt << 9, readstartblk, opts->bootno)){
                    printf("\n** Unable to read data at emmc boot partition%d **\n", opts->bootno);
                    return 1;
                }
            }

            fd = fat_init(opts->fatfile_name, "a", 1);
            if (fd < 0) {
                printf("\n** Unable to open \"%s\" **\n",opts->fatfile_name);
                return 1;
            }

            ret = file_fat_write(fd, (unsigned char *) opts->buffer, fat_read_len);
            file_fat_close(fd);

            flush_cache((ulong)opts->buffer, fat_read_len);

            if(ret == -1) {
                printf("\n** Unable to write \"%s\" **\n", opts->fatfile_name);
                return 1;
            }

            imglen -= fat_read_len;

            if (!opts->quiet)
            {
                    int percent = (int)
                            ((unsigned long long)
                            (opts->length-imglen) * 100
                            / opts->length);
                    /* output progress message only at whole percent
                    * steps to reduce the number of messages printed
                    * on (slow) serial consoles
                    */
                    if (percent != percent_complete)
                    {
                        printf("\rWriting data at 0x%llx "
                                "-- %3d%% complete.\n",
                                imgoffset, percent);
                        percent_complete = percent;
                    }
            }

            imgoffset += fat_read_len;
        }

        if (!opts->quiet)
        {
            printf("\n");
        }

        if (imglen > 0)
        {
            printf("Data did not fit into device, imglen= 0x%x\n",imglen);
            return -1;
        }

        /* return happy */
        return 0;
}

/* read out the whole contents of emmc and store it to usb disk */
int do_emmcboot_mkbin(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret=0;
    emmc_read_options_t opts;
    u64 offset=0, dumpsize = 0;
    int port=0;
    block_dev_desc_t *mmc_dev=NULL;
    char usb_start_command[20];

    if (curr_device < 0) {
        if (get_mmc_num() > 0)
                    curr_device = 0;
        else {
            puts("No MMC device available\n");
            return -1;
       }
    }

    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }

    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    if (argc != 3)
    {
        printf("should input usb port num and boot partition name\n");
        return -1;
    }

    if(argc > 1)
        port = (int)simple_strtoul (argv[1], NULL, 16);

    sprintf(usb_start_command,"usb start %d",port);
    run_command(usb_start_command, 0);

    mmc_dev = mmc_get_dev(curr_device);
    if ((mmc_dev == NULL) ||
            (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
        printf("no mmc device found!\n");
        return -1;
    }

    memset(&opts, 0, sizeof(opts));
    //Get the boot partition num from partition name
    if(!strcmp(argv[2], "boot1"))
    {
        opts.fatfile_name = EMMC_BOOT1_NAME;
        opts.bootno = 1;
    }
    else if(!strcmp(argv[2], "boot2"))
    {
        opts.fatfile_name = EMMC_BOOT2_NAME;
        opts.bootno = 2;
    }
    else if(!strcmp(argv[2], "boot1_2"))
    {
        opts.fatfile_name = EMMC_BOOT1_NAME;
        opts.bootno = 1;
    }
    else if(!strcmp(argv[2], "boot12"))
    {
        opts.fatfile_name = EMMC_BOOT_NAME;
        opts.bootno = 1;
    }
    else
    {
        printf("Boot partition name is invalid,\n");
        printf("Only part name of boot1 boot2 boot1_2 boot12 are accepted\n");

        return -1;
    }

    // the last sector of boot partition of toshiba cann't be read
    dumpsize = 128 * 1024 * (mmc->ext_csd[226] & 0xff) - 0x200;

    // dump boot partition 1
    opts.buffer = (u_char*)UPGRADE_BUFFER_ADDR;
    opts.length = 0x1EF0000;
    opts.offset = 0;
    opts.quiet = 0;

    if(opts.length > dumpsize)
        opts.length = dumpsize;

    printf("\n Read 0x%llx bytes from emmc boot%d to %s \n",
        opts.length,opts.bootno,opts.fatfile_name);

    for(opts.offset = 0; opts.offset < dumpsize;){
        memset(opts.buffer, 0x00, opts.length);
        ret = emmc_read_opts(&opts, dumpsize, offset);
        flush_cache((ulong)opts.buffer, opts.length);
        if(ret)
            return ret;
        opts.offset += opts.length;
        if(opts.offset + opts.length > dumpsize)
                opts.length = dumpsize - opts.offset;
    }

    // dump boot partition 2
    if(!strcmp(argv[2], "boot1_2"))
    {
        opts.fatfile_name = EMMC_BOOT2_NAME;
        opts.bootno = 2;
    }
    else if(!strcmp(argv[2], "boot12"))
    {
        opts.bootno = 2;
    }
    else
    {
        return ret;
    }

    opts.length = 0x1EF0000;
    opts.offset = 0;

    if(opts.length > dumpsize)
        opts.length = dumpsize;

    printf("\n Read 0x%llx bytes from emmc boot%d to %s \n",
        opts.length,opts.bootno,opts.fatfile_name);

    for(opts.offset = 0; opts.offset < dumpsize;){
        memset(opts.buffer, 0x00, opts.length);
        ret = emmc_read_opts(&opts, dumpsize, offset);
        flush_cache((ulong)opts.buffer, opts.length);
        if(ret)
            return ret;
        opts.offset += opts.length;
        if(opts.offset + opts.length > dumpsize)
                opts.length = dumpsize - opts.offset;
    }

    return ret;
}

/* read out the whole contents of emmc and store it to usb disk */
int do_emmc_mkbin(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret=0, pad = 1, i;
    emmc_read_options_t opts;
    u64 offset=0, dumpsize=0;
    int port=0;
    char *partname=EMMC_BIN_NAME;
    disk_partition_t dpt;
    block_dev_desc_t *mmc_dev=NULL;
    ulong blk = -1, partnum = 1;
    char* cmdline = NULL;
    char usb_start_command[20];


    if (curr_device < 0) {
        if (get_mmc_num() > 0)
                    curr_device = 0;
        else {
            puts("No MMC device available\n");
            return -1;
       }
    }

    struct mmc *mmc = find_mmc_device(curr_device);
    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }

    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    if(argc > 1)
        port = (int)simple_strtoul (argv[1], NULL, 16);

    if(argc > 2)
        pad = (int)simple_strtoul (argv[2], NULL, 16);

    if(argc > 3)
        partname = argv[3];

    if(argc > 4)
        blk = (ulong) (ALIGN(simple_strtoull(argv[4], NULL, 16), 512) / 512);

    if(argc > 5)
        dumpsize =  ALIGN(simple_strtoull(argv[5], NULL, 16), 512);

    sprintf(usb_start_command,"usb start %d",port);
    run_command(usb_start_command, 0);

    mmc_dev = mmc_get_dev(curr_device);
    if ((mmc_dev == NULL) ||
            (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
        printf("no mmc device found!\n");
        return -1;
    }

    if ((offset == 0) && (dumpsize == 0))
    {
        cmdline = (char *)malloc(32);
        sprintf(cmdline, "%s %d %s", "emmcbootbin", port, "boot1_2");
        run_command(cmdline, 0);
        free(cmdline);
    }

    if(!pad){
        struct mmc_bininfo bininfo;

        offset = 0;

        memset(&opts, 0, sizeof(opts));
        opts.buffer = (u_char*)UPGRADE_BUFFER_ADDR;
        opts.fatfile_name = partname;
        opts.offset = 0;
        opts.quiet = 0;

        for(i = 0; i < EMMC_RESERVED_FOR_MAP_V2 + 1; i++){
            memset(&bininfo, 0, sizeof(struct mmc_bininfo));
            ret = do_mmcpart_bininfo(i, &bininfo);
            if(ret < 0){
                printf("[%s]: check bininfo of part %d failed\n", __func__, i);
                return ret;
            }
            if(bininfo.dpt.size == 0)
                break;
            if(bininfo.valid_block == 0)
                continue;

            printf("bininfo %s, start %lx, size %lx valid %lx\n", bininfo.dpt.name, bininfo.dpt.start, bininfo.dpt.size, bininfo.valid_block);

            offset = bininfo.dpt.start * EMMC_BLK_SZ;
            dumpsize = bininfo.valid_block * EMMC_BLK_SZ;

            opts.length = 0x1EF0000;

            if((offset < 0) || (offset > mmc->capacity))
                offset = 0;

            if((dumpsize > mmc->capacity - offset) || !dumpsize)
                dumpsize = mmc->capacity - offset;

            if(opts.length > dumpsize)
                opts.length = dumpsize;

            for(opts.offset = 0; opts.offset < dumpsize;){
                memset(opts.buffer, 0x00, opts.length);
                ret = emmc_read_opts(&opts, dumpsize, offset);
                flush_cache((ulong)opts.buffer, opts.length);
                if(ret)
                    return ret;
                opts.offset += opts.length;
                if(opts.offset + opts.length > dumpsize)
                    opts.length = dumpsize - opts.offset;
                 printf("length %llx\n", opts.length);
            }
            ret = write_mmcdef_leap(i, &bininfo);
            if(ret < 0){
                    printf("Write leap def file failed\n");
                    return ret;
            }
            ret = write_mmcdef_forcreate(i, &bininfo);
            if(ret < 0){
                    printf("Write forcreate def file failed\n");
                    return ret;
            }
        }
        ret = write_mmcdef_leap(0x8000, &bininfo);
        if(ret < 0){
                printf("Write leap def file end failed\n");
                return ret;
        }
        return ret;
    }

    //Get the partition offset from partition name
    for(;;)
    {
        if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
            break;
        if(!strcmp(argv[3], (const char *)dpt.name)){
            blk = dpt.start;
            break;
        }
        partnum++;
    }

    if(blk < 0){
        printf("ERR:Please check the partition name!\n");
        return 1;
    }

    if(blk)
        offset = blk << 9;

    memset(&opts, 0, sizeof(opts));
    opts.buffer = (u_char*)UPGRADE_BUFFER_ADDR;
    opts.fatfile_name = partname;
    opts.length = 0x1EF0000;
    opts.offset = 0;
    opts.quiet = 0;

    if((offset < 0) || (offset > mmc->capacity))
        offset = 0;

    if((dumpsize > mmc->capacity - offset) || !dumpsize)
        dumpsize = mmc->capacity - offset;

    if(opts.length > dumpsize)
        opts.length = dumpsize;

    printf("\n Read 0x%llx bytes from emmc offset 0x%llx to %s \n",
        dumpsize,offset,opts.fatfile_name);

    for(opts.offset = 0; opts.offset < dumpsize;){
        memset(opts.buffer, 0x00, opts.length);
        ret = emmc_read_opts(&opts, dumpsize, offset);
        flush_cache((ulong)opts.buffer, opts.length);
        if(ret)
            return ret;
        opts.offset += opts.length;
        if(opts.offset + opts.length > dumpsize)
            opts.length = dumpsize - opts.offset;
    }

    return ret;

}

#endif

extern void FCIE_HWTimer_Start(void);
extern U32 FCIE_HWTimer_End(void);

static u32 do_mmc_empty_check(const void *buf, u32 len, u32 empty_flag)
{
    int i;

    if ((!len) || (len & 511))
        return -1;

    for (i = (len >> 2) - 1; i >= 0; i--)
        if (((const uint32_t *)buf)[i] != empty_flag)
            break;

    /* The resulting length must be aligned to the minimum flash I/O size */
    len = ALIGN((i + 1) << 2, 512);
    return len;
}

static u32 do_mmc_write_emptyskip(struct mmc *mmc, s32 start_blk, u32 cnt_blk,
                                            const void *buf, u32 empty_skip)
{
    u32 n = 0;

    if (1 == empty_skip) // 1 indicates skipping empty area, 0 means writing all the data
    {
        u32 nn, empty_flag, rcnt, wcnt, cur_cnt = cnt_blk;
        int boffset = start_blk;
        int doffset = (int)buf;

        if(mmc->ext_csd[181] == 0)
        {
            empty_flag = 0;
        }
        else
        {
            empty_flag = 0xffffffff;
        }

        while(cur_cnt > 0)
        {
            if (cur_cnt >= 0x800)
                wcnt = 0x800;
            else
                wcnt = cur_cnt;

            rcnt = do_mmc_empty_check((void *)doffset, (wcnt << 9), empty_flag);
            if (-1 == rcnt)
            {
                printf("The block num(0x%x) is wrong!", wcnt);
                return 0;
            }
            rcnt >>= 9;
            if (rcnt == 0)
            {
                boffset += wcnt;
                doffset += wcnt << 9;
                cur_cnt -= wcnt;
                n += wcnt;

                continue;
            }

            nn = mmc->block_dev.block_write(0, boffset, rcnt, (void *)doffset);
            if (nn == rcnt)
            {
                n += wcnt;
            }
            else
            {
                n += nn;
                printf("Only 0x%x blk written to blk 0x%x\n, need 0x%x", nn, boffset, rcnt);

                return n;
            }

            boffset += wcnt;
            doffset += wcnt << 9;
            cur_cnt -= wcnt;
        }
    }
    else
    {
        n = mmc->block_dev.block_write(0, start_blk, cnt_blk, buf);
    }

    return n;
}

#ifdef CONFIG_LZO
static int do_unlzo (struct mmc *mmc, int argc, char * const argv[])
{
    int ret=0, cnt, cnt_total=0;
    unsigned char *AddrSrc=NULL, *AddrDst=NULL;
    size_t LengthSrc=0,  LengthDst=0;
    size_t LenTail=0, LenSpl=0, LenSrcAlign=0;
    disk_partition_t dpt;
    block_dev_desc_t *mmc_dev;
    s32 blk = -1, partnum = 1, n;
    u32 empty_skip = 0, partition_blkcnt = 0;
    char* cmdtail = strchr(argv[1], '.');

    AddrSrc = (unsigned char *) simple_strtol(argv[2], NULL, 16);
    LengthSrc = (size_t) simple_strtol(argv[3], NULL, 16);

    mmc_dev = mmc_get_dev(curr_device);
    if ((mmc_dev == NULL) ||
            (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
        printf("no mmc device found!\n");
        return 1;
    }

    //Get the partition offset from partition name
    for(;;){

        if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
            break;
        if(!strcmp(argv[4], (const char *)dpt.name)){
            blk = dpt.start;
            partition_blkcnt = dpt.size;
            break;
        }
        partnum++;
    }

    if(blk < 0){
        printf("ERR:Please check the partition name!\n");
        return 1;
    }

    if ((!cmdtail) || (strncmp(cmdtail, ".cont", 5)))
        unlzo_partition_blkcnt = 0;

    if(unlzo_partition_blkcnt >= partition_blkcnt){
        printf("ERR: The partition unlzo write has been done!\n");
        return 1;
    }

    blk += unlzo_partition_blkcnt;

    AddrDst = (unsigned char *) CONFIG_UNLZO_DST_ADDR;

    printf ("   Uncompressing ... \n");

    ret = lzop_decompress_part ((const unsigned char *)AddrSrc, LengthSrc,
                (unsigned char *)AddrDst, &LengthDst, &LenSrcAlign, 0);


    if (ret) {
        printf("LZO: uncompress, out-of-mem or overwrite error %d\n", ret);
        return 1;
    }

    if (argc == 6)
    {
        empty_skip = simple_strtoul(argv[5], NULL, 16);
    }

    /* We assume that the decompressed file is aligned to mmc block size
        when complete decompressing */
    cnt = LengthDst >> EMMC_RW_SHIFT;

    //n = mmc->block_dev.block_write(curr_device, blk, cnt, AddrDst);
      if((blk+cnt)<=(dpt.start+dpt.size))
        {
               n = do_mmc_write_emptyskip(mmc, blk, cnt, AddrDst, empty_skip);
        }
    else
    {
               printf("\n\n*****ERROR:the write data size (%d-%d) bigger than the partition %s size (%lu-%lu)!*****\n\n",blk,blk+cnt,dpt.name,dpt.start,dpt.start+dpt.size);
               return 1;
    }

    if(n == cnt)
        cnt_total += cnt;
    else{
        printf("%d blocks written error at %d\n", cnt, blk);
        return 1;
    }

    /* If the decompressed file is not aligned to mmc block size, we should
        split the not aligned tail and write it in the next loop */
    LenTail = LengthDst & (EMMC_BLK_SZ - 1);

    if(LenTail){
        memcpy((unsigned char *) CONFIG_UNLZO_DST_ADDR,
                    (const unsigned char *) (AddrDst + LengthDst - LenTail), LenTail);
        AddrDst = (unsigned char *) (CONFIG_UNLZO_DST_ADDR + LenTail);
    }else
        AddrDst = (unsigned char *) CONFIG_UNLZO_DST_ADDR;

    if(LenSrcAlign == LengthSrc)
        goto done;

    //Move the source address to the right offset
    AddrSrc += LenSrcAlign;

    printf("    Continue uncompressing and writing emmc...\n");

    for(;;){

        LengthDst = 0;
        ret = lzop_decompress_part ((const unsigned char *)AddrSrc, LengthSrc,
                (unsigned char *)AddrDst, &LengthDst, &LenSrcAlign, 1);
        if (ret) {
            printf("LZO: uncompress, out-of-mem or overwrite error %d\n", ret);
            return 1;
        }

        LenSpl = LenTail + LengthDst;
        cnt = LenSpl >> EMMC_RW_SHIFT;

        if(cnt){
            //n = mmc->block_dev.block_write(curr_device, (blk+cnt_total), cnt, (const unsigned char *)CONFIG_UNLZO_DST_ADDR);
            if((blk+cnt_total+cnt)<=(dpt.start+dpt.size))
            {
            n = do_mmc_write_emptyskip(mmc, (blk+cnt_total), cnt, (const unsigned char *)CONFIG_UNLZO_DST_ADDR, empty_skip);
            }
         else
         {
                  printf("\n\n*****ERROR:the write data size (%d-%d) bigger than the partition %s size (%ld-%ld)!*****\n\n",blk+cnt_total,blk+cnt_total+cnt,dpt.name,dpt.start,dpt.start+dpt.size);
               return 1;
         }

            if(n == cnt)
                cnt_total += cnt;
            else{
                printf("%d blocks written error at %d\n", cnt, (blk+cnt_total));
                return 1;
            }
        }

        LenTail = LenSpl & (EMMC_BLK_SZ - 1);
        if(LenTail){
            memcpy((unsigned char *) CONFIG_UNLZO_DST_ADDR,
                        (const unsigned char *) (AddrDst + LengthDst - LenTail), LenTail);
            AddrDst = (unsigned char *) (CONFIG_UNLZO_DST_ADDR + LenTail);
        }else
            AddrDst = (unsigned char *) CONFIG_UNLZO_DST_ADDR;

        if(LenSrcAlign == LengthSrc)
            break;

        AddrSrc += LenSrcAlign;
    }

done:


    if(LenTail){
        if(1 != mmc->block_dev.block_write(0, (blk + cnt_total),
                    1, (const unsigned char *)CONFIG_UNLZO_DST_ADDR))
        {
            printf("%d blocks written error at %d\n", cnt, blk);
            return 1;
        }
        cnt_total++;
    }

    unlzo_partition_blkcnt += cnt_total;

    printf("    Depressed OK! Write to %s partition OK!\nTotal write size: 0x%0x\n",
            argv[4], cnt_total << EMMC_RW_SHIFT);

    return 0;
}
#endif

#ifdef CONFIG_USB
int do_ddmmc(struct mmc *mmc, char * const argv[], int restore, int pad)
{
    int ret=0, percent_complete=-1;
    emmc_read_options_t opts;
    int part=1, dev=0, fat_read_len=0;
    char *ep;
    long lPartno = 0;
    char * cPartno = getenv("partno");
    block_dev_desc_t *dev_desc=NULL;
    ulong readstartblk, readblkcnt, totalcnt=0;
    u64 imglen=0, emmcoffset=0;

    if(cPartno == NULL) {
        part = 1;
        lPartno = 1;
    }
    else {
        lPartno = simple_strtol(cPartno, NULL, 10);
        part = lPartno;
        if (part == 0)//env haven't set
            part = 1;
    }

    dev = (int)simple_strtoul ("0", &ep, 16);
    dev_desc=get_dev("usb",dev);
    if (dev_desc==NULL) {
        puts ("\n** Invalid boot device **\n");
        return -1;
    }
//    printf("Blksz=%ld, Blknum=%ld\n",dev_desc->blksz, dev_desc->lba);
    if(!restore && (dev_desc->lba < mmc->block_dev.lba)){
        printf("\n** Please Check the usb storage capacity! **\n");
        return -1;
    }

    if (*ep) {
        if (*ep != ':') {
            puts ("\n** Invalid boot device, use `dev[:part]' **\n");
            return -1;
        }
        ++ep;
        part = (int)simple_strtoul(ep, NULL, 16);
    }

    memset(&opts, 0, sizeof(opts));

    if (!opts.quiet)
    {
        printf("\n");
    }

    if(!pad){
        int i;
        u64 usboffset = 0;
        ulong usbstartblk = 0;
        struct mmc_bininfo bininfo;
        if(restore){
            printf("Restore of dd is Not support\n");
            return 0;
        }
        else{
            for(i = 0; i < EMMC_RESERVED_FOR_MAP_V2 + 1; i++){
                memset(&bininfo, 0, sizeof(struct mmc_bininfo));
                ret = do_mmcpart_bininfo(i, &bininfo);
                if(ret < 0){
                    printf("[%s]: check bininfo of part %d failed\n", __func__, i);
                    return ret;
                }
                if(bininfo.dpt.size == 0)
                    break;
                if(bininfo.valid_block == 0)
                    continue;

                imglen = bininfo.valid_block * bininfo.dpt.blksz;

                opts.buffer = (u_char*)UPGRADE_BUFFER_ADDR;
                opts.length = mmc->capacity;
                opts.offset = bininfo.dpt.start * EMMC_BLK_SZ;
                opts.quiet = 0;

                emmcoffset = opts.offset;

                printf("bininfo: %s, start %lx, size %lx, valid %lx\n", bininfo.dpt.name, bininfo.dpt.start, bininfo.dpt.size, bininfo.valid_block);
                printf("imagelen %llx, emmcoffset%llx, usboffset %llx\n", imglen, emmcoffset, usboffset);

                while (imglen && (emmcoffset < mmc->capacity )){
                    WATCHDOG_RESET ();

                    if (imglen >= FAT_BUFFER_LEN)
                        fat_read_len = FAT_BUFFER_LEN;
                    else
                        fat_read_len = imglen;

                    readstartblk = ALIGN(emmcoffset, 512) / 512;
                    readblkcnt = ALIGN(fat_read_len, 512) / 512;
                    usbstartblk =  ALIGN(usboffset, 512) / 512;

                    printf("readstartblk %lx, readblkcnt %lx usbstart blk %lx\n", readstartblk, readblkcnt, usbstartblk);

                    if(readblkcnt != mmc->block_dev.block_read(curr_device, readstartblk, readblkcnt, opts.buffer)){
                        printf("\n** Unable to read data at emmc offset 0x%llx **\n", emmcoffset);
                        return 1;
                    }

                    ret = dev_desc->block_write(dev_desc->dev, usbstartblk, readblkcnt, (ulong*)opts.buffer);

                    flush_cache((ulong)opts.buffer, fat_read_len);

                    if(ret < 0) {
                        printf("\n** Unable to write the usb storage **\n");
                        return 1;
                    }
                    usboffset += fat_read_len;
                    imglen -= fat_read_len;
                    emmcoffset += fat_read_len;
                }
                printf("\n");
            }
        }
        return ret;
    }

    //Pad mode
    opts.buffer = (u_char*)UPGRADE_BUFFER_ADDR;
    opts.length = mmc->capacity;
    opts.offset = 0;
    opts.quiet = 0;

    /* get image length */
    imglen = mmc->capacity;
    emmcoffset = opts.offset;

    /* get data from input and write to the device */
    while (imglen && (emmcoffset < mmc->capacity ))
    {

        WATCHDOG_RESET ();

        if (imglen >= FAT_BUFFER_LEN)
        {
            fat_read_len = FAT_BUFFER_LEN;
        }
        else
        {
            fat_read_len = imglen;
        }

        readstartblk = ALIGN(emmcoffset, 512) / 512;
        readblkcnt = ALIGN(fat_read_len, 512) / 512;

        if(restore){
            ret = dev_desc->block_read(dev_desc->dev, readstartblk, readblkcnt, (ulong*)opts.buffer);
            if(ret < 0) {
                printf("\n** Unable to read the usb storage **\n");
                return 1;
            }

            if(readblkcnt != mmc->block_dev.block_write(curr_device, readstartblk, readblkcnt, opts.buffer)){
                printf("\n** Unable to write data at emmc offset 0x%llx **\n", emmcoffset);
                return 1;
            }

        }else{
            if(readblkcnt != mmc->block_dev.block_read(curr_device, readstartblk, readblkcnt, opts.buffer)){
                printf("\n** Unable to read data at emmc offset 0x%llx **\n", emmcoffset);
                return 1;
            }

            ret = dev_desc->block_write(dev_desc->dev, readstartblk, readblkcnt, (ulong*)opts.buffer);

            flush_cache((ulong)opts.buffer, fat_read_len);

            if(ret < 0) {
                printf("\n** Unable to write the usb storage **\n");
                return 1;
            }
        }

        imglen -= fat_read_len;

        if (!opts.quiet)
        {
            u64 percent = (u64)
                ((unsigned long long)
                (opts.length-imglen) * 100
                / opts.length);
            /* output progress message only at whole percent
            * steps to reduce the number of messages printed
            * on (slow) serial consoles
            */
            if (percent != percent_complete)
            {
                printf("\rWriting data at 0x%llux "
                        "-- %3lld%% complete.",
                        emmcoffset, percent);
                percent_complete = percent;
            }
        }

        emmcoffset += fat_read_len;
        totalcnt += readblkcnt;
    }

    if (!opts.quiet)
    {
        printf("\n");
    }

    printf("Dump Block: %ld\n", totalcnt);
    return ret;

}
#endif

#if ENABLE_BFE_WRITE_MMC
#define MIUIDTAG    (0x4D495530)      // 'MIU0'
#define LDRIDTAG    (0x4C445230)      // 'LDR0'
#define BINIDTAG    (0x42494E30)      // 'BIN0'

#define CHIPCFG_CMD_END        0xFFF0

static int read_miu_parm_cnt(U32 u32MIUPos)
{
    /*
    int              retlen=0;
    while (1)
    {
        U16 reg = *(U16*)u32MIUPos;

        retlen += 4;

        if (reg == CHIPCFG_CMD_END)
            return retlen;

        u32MIUPos += 4;
    }
    return 0;
    */
    //sync 707947 for CA flow
    //fix miu size to 0x2000
    return 0x2000;
}

int do_write_miu2emmc(U32 bfn_blk,U32 bfn_addr)
{
    U32   header_blk[128]={};
    U32  ParamMIUSize = 0;
    U32  u32_err =0;

    struct mmc *mmc = find_mmc_device(curr_device);

    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }

    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    ParamMIUSize = read_miu_parm_cnt(bfn_addr);
    printf("Read ParamLDRSize:0x%x\n",ParamMIUSize);

    ParamMIUSize = (ParamMIUSize&0xFFFFFE00) + (((ParamMIUSize&0x1ff)>0)?0x200:0);  //alliment 512B

    *header_blk     = MIUIDTAG;
    *(header_blk+1) = ParamMIUSize;

    if((ParamMIUSize>>9) > g_eMMCDrv.u32_BOOT_SEC_COUNT)
    {
        printf("\n eMMC has no enough boot partition size for write!\n");
        return 1;
    }

    // write header block
    u32_err = eMMC_WriteBootPart((U8 *)header_blk, 0x200, bfn_blk, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"Write header block fail %Xh\n", u32_err);
        return u32_err;
    }

    printf("Parm : bfn_addr:0x%x, ParamMIUSize:0x%x, bfn_blk:0x%x\n ",bfn_addr,ParamMIUSize,bfn_blk);
    printf("Read LDR run base:0x%x, LDR size:0x%x\n",*(U32 *)(bfn_addr+0xff8),*(U32 *)(bfn_addr+0xffc));

    u32_err = eMMC_WriteBootPart((U8 *)bfn_addr, ParamMIUSize, bfn_blk+1, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"Write miu parm block fail %Xh\n", u32_err);
        return u32_err;
    }

    printf("totally write 0x%x blks\n",ParamMIUSize>>9 );

    return eMMC_ST_SUCCESS;
}


int do_write_ldr2emmc(U32 bfn_blk,U32 bfn_addr)
{
    U32  header_blk[128] ={};
    U32  ParamLDRSize = 0;
    U32  u32_err =0;
    U32  LdrStackPoint = 0;
    U32  Ldr2MIUPos = 0;

    struct mmc *mmc = find_mmc_device(curr_device);

    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }

    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    ParamLDRSize = *(U32*)(bfn_addr + 12);
    LdrStackPoint = *(U32*)(bfn_addr + 8);
    Ldr2MIUPos = (*(U32*)(bfn_addr)) + (*((U32*)(bfn_addr+4)));
    printf("Read ParamLDRSize:%x\n",ParamLDRSize);
    printf("Read LdrStackPoint:%x\n",LdrStackPoint);
    printf("Read Ldr2MIUPos:%x\n",Ldr2MIUPos);

    *header_blk     = LDRIDTAG;
    *(header_blk+1) = ParamLDRSize;
    *(header_blk+2) = LdrStackPoint;
    *(header_blk+3) = Ldr2MIUPos;

    ParamLDRSize = (ParamLDRSize&0xFFFFFE00) + (((ParamLDRSize&0x1ff)>0)?0x200:0);  //alliment 512B

    printf("g_eMMCDrv.u32_BOOT_SEC_COUNT:%x\n",g_eMMCDrv.u32_BOOT_SEC_COUNT);
    if( (ParamLDRSize>>9) > g_eMMCDrv.u32_BOOT_SEC_COUNT)
    {
        printf("\n eMMC has no enough boot partition size for write!\n");
        return 1;
    }

    // write header block
    u32_err = eMMC_WriteBootPart((U8 *)header_blk, 0x200, bfn_blk, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"Write header block fail %Xh\n", u32_err);
        return u32_err;
    }

    printf("Para : bfn_addr:0x%x, ParamLDRSize:0x%x, bfn_blk:0x%x\n ",bfn_addr,ParamLDRSize,bfn_blk);

    u32_err = eMMC_WriteBootPart((U8 *)(bfn_addr+0x100), ParamLDRSize, bfn_blk+1, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"Write ldr parm block fail %Xh\n", u32_err);
        return u32_err;
    }

    printf("totally write 0x%x blks\n",ParamLDRSize>>9 );

    return eMMC_ST_SUCCESS;
}


int do_write_app2emmc(U32 bfn_blk,U32 bfn_addr)
{
    U32   header_blk[128] ={};
    U32  ParamAPPSize = 0;
    U32  u32_err =0;

    struct mmc *mmc = find_mmc_device(curr_device);

    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
    }

    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    ParamAPPSize = * (U32 * )(bfn_addr + 8);
    printf("Read ParamLDRSize:%x\n",ParamAPPSize);

    ParamAPPSize = (ParamAPPSize&0xFFFFFE00) + (((ParamAPPSize&0x1ff)>0)?0x200:0);  //alliment 512B

    printf("g_eMMCDrv.u32_SEC_COUNT:%x\n",g_eMMCDrv.u32_SEC_COUNT);
    if( (ParamAPPSize>>9) > g_eMMCDrv.u32_SEC_COUNT)
    {
        printf("\n eMMC has no enough partition size for write!\n");
        return 1;
    }

    *header_blk     = BINIDTAG;
    *(header_blk+1)  = ParamAPPSize;
    *(header_blk+2)  = (* (U32 * )(bfn_addr )) +  (* (U32 * )(bfn_addr + 4));

    // write header block
    u32_err = eMMC_WriteData((U8 *)header_blk, 0x200, bfn_blk);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"Write header block fail %Xh\n", u32_err);
        return u32_err;
    }

    printf("Parm: bfn_addr:0x%x, ParamMIUSize:0x%x, bfn_blk:0x%x\n ",bfn_addr,ParamAPPSize,bfn_blk);

    u32_err = eMMC_WriteData((U8 *)(bfn_addr+0x100), ParamAPPSize, bfn_blk+1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"Write app parm block fail %Xh\n", u32_err);
        return u32_err;
    }

    printf("totally write 0x%x blks\n",ParamAPPSize>>9 );

    return eMMC_ST_SUCCESS;
}

#endif

int do_mmcops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc < 2)
        return cmd_usage(cmdtp);

    if (curr_device < 0) {
        if (get_mmc_num() > 0)
            curr_device = 0;
        else {
            puts("No MMC device available\n");
            return 1;
        }
    }


    #if ENABLE_BFE_WRITE_MMC
        /*
        * Syntax is:
        *   0    1   2             3          4
        *   mmc  bfe [miu/ldr/app] [blk addr] [miu address]
        */
    if (strcmp(argv[1], "bfe") == 0){
        printf("Write BFE image to EMMC\n");
        if (argc < 4)
        {
            printf("argument wrong!\n");
            return 0;
        }
        U32 addr = simple_strtoul(argv[4], NULL, 16);
        U32 blk = simple_strtoul(argv[3], NULL, 16);

        if (strncmp(argv[2],"miu",3)==0)
        {
            printf("write the MIU param\n");

            if(do_write_miu2emmc(blk,addr)==eMMC_ST_SUCCESS) printf("write the MIU param OK!! \n");
            else                                             printf("write the MIU param FAIL!! \n");

        }
        else if (strncmp(argv[2],"ldr",3)==0)
        {
            printf("write the LDR param\n");

            if (do_write_ldr2emmc(blk,addr)==eMMC_ST_SUCCESS) printf("write the LDR param OK!! \n");
            else                                              printf("write the LDR param FAIL!! \n");
        }
        else if (strncmp(argv[2],"app",3)==0)
        {
            printf("write the APP param\n");

            if(do_write_app2emmc(blk,addr)==eMMC_ST_SUCCESS) printf("write the APP param OK!! \n");
            else                                             printf("write the APP param FAIL!! \n");
        }
        else
        {
            printf("error boot from nand parameter\n");
            return 0;
        }

        return 1;
    }
    #endif

    if (strcmp(argv[1], "rescan") == 0) {
        struct mmc *mmc = find_mmc_device(curr_device);

        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }
        mmc_init(mmc);
        return 0;

    } else if (strncmp(argv[1], "part", 4) == 0) {
        block_dev_desc_t *mmc_dev;
        char* cmdtail = strchr(argv[1], '.');
        struct mmc *mmc = find_mmc_device(curr_device);

        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }
        if(!mmc->has_init) {
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

        if(cmdtail == NULL)     //print user partition
        {
            mmc_dev = mmc_get_dev(curr_device);
            if (mmc_dev != NULL && mmc_dev->type != DEV_TYPE_UNKNOWN) {
                print_part(mmc_dev);
                return 0;
            }
        }
        else if((cmdtail) != NULL && (!strncmp(cmdtail, ".gp", 3)))     //print general purpose partition
        {
            eMMC_PrintGPPartition();
            return 0;
        }
        puts("get mmc type error!\n");
        return 1;
    }


    if (strncmp(argv[1], "look", 4) == 0)
    {
        block_dev_desc_t *mmc_dev=NULL;
        struct mmc *mmc=NULL;
        disk_partition_t dpt;
        ulong partnum=1;
        if(argc<3)
        {
        return cmd_usage(cmdtp);
        }

        mmc = find_mmc_device(curr_device);

        if (!mmc)
        {
        puts("no mmc devices available\n");
        return 1;
        }
        mmc_init(mmc);
        mmc_dev = mmc_get_dev(curr_device);
        if ((mmc_dev == NULL) ||
        (mmc_dev->type == DEV_TYPE_UNKNOWN))
        {
        printf("no mmc device found!\n");
        return 1;
        }

        for(;;)
        {
            if (get_partition_info_emmc(mmc_dev, partnum, &dpt))
            {
                printf("Error >> end searching partition\n");
                return 1;
            }

            if (!strcmp(argv[2], (const char *)dpt.name))
            {
                printf("name=%s\n",(const char *)dpt.name);
                printf("type=%s\n",(const char *)dpt.type);
                printf("start=0x%x # the first block in partition \n",(unsigned int)dpt.start);
                printf("size=0x%x # number of blocks \n",(unsigned int)dpt.size);
                printf("blksz=0x%x\n",(unsigned int)dpt.blksz);
                break;
            }
            partnum++;
        }
        return 0;

    }

    /*else if (strcmp(argv[1], "memdump") == 0) {
        U32 u32MemAddr = simple_strtoul(argv[2], NULL, 16);
        U32 u32ByteNum = simple_strtoul(argv[3], NULL, 16);
        printf("memdump %Xh, %Xh\n", u32MemAddr, u32ByteNum);
        dump_mem((char *)u32MemAddr, u32ByteNum);
        return 0;
    }*/

    else if (strcmp(argv[1], "list") == 0) {
        print_mmc_devices('\n');
        return 0;

    } else if (strcmp(argv[1], "dev") == 0) {
        int dev, part = -1;
        struct mmc *mmc;

        if (argc == 2)
            dev = curr_device;
        else if (argc == 3)
            dev = simple_strtoul(argv[2], NULL, 10);
        else if (argc == 4) {
            dev = (int)simple_strtoul(argv[2], NULL, 10);
            part = (int)simple_strtoul(argv[3], NULL, 10);
            if (part > PART_ACCESS_MASK) {
                printf("#part_num shouldn't be larger"
                    " than %d\n", PART_ACCESS_MASK);
                return 1;
            }
        } else
            return cmd_usage(cmdtp);

        mmc = find_mmc_device(dev);
        if (!mmc) {
            printf("no mmc device at slot %x\n", dev);
            return 1;
        }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }
        if (part != -1) {
            int ret;
            if (mmc->part_config == MMCPART_NOAVAILABLE) {
                printf("Card doesn't support part_switch\n");
                return 1;
            }

            if (part != mmc->part_num) {
                ret = mmc_switch_part(dev, part);
                if (!ret)
                    mmc->part_num = part;

                printf("switch to partions #%d, %s\n",
                        part, (!ret) ? "OK" : "ERROR");
            }
        }
        curr_device = dev;
        if (mmc->part_config == MMCPART_NOAVAILABLE)
            printf("mmc%d is current device\n", curr_device);
        else
            printf("mmc%d(part %d) is current device\n",
                curr_device, mmc->part_num);

        return 0;

    //} else if (strcmp(argv[1], "read") == 0) {
    } else if (strncmp(argv[1], "readall", 7) == 0) {
                    u32 blkChunk = 4095;
                    u32 buf_size = blkChunk*512;
                    u32 blkStart = 0, blkCount = 0, traceCount = 0;
                    u32 totalBlock = 0;
                    void *addr = (void *)malloc(buf_size);

                    if(addr == NULL)
                    {
                        printf("no memory\n");
                        return 1;
                    }

                    struct mmc *mmc = find_mmc_device(curr_device);
                    if (!mmc) {
                            printf("no mmc device at slot %x\n", curr_device);
                            free(addr);
                            addr = NULL;
                            return 1;
                    }

                    if(!mmc->has_init){
                        printf("Do mmc init first!\n");
                        mmc_init(mmc);
                        mmc->has_init = 1;
                    }

                    if(mmc->block_dev.block_read == NULL)
                    {
                        free(addr);
                        addr = NULL;
                        return 1;
                    }

                    printf("\nread eMMC device with %d blocks every time\n", blkChunk);
                    blkStart = 0;
                    totalBlock = mmc->block_dev.lba ;
                    while(totalBlock>0)
                    {
                       u32 ret = 0;
                       blkCount = (totalBlock > blkChunk ? blkChunk : totalBlock);
                       ret = mmc->block_dev.block_read(0, blkStart, blkCount, addr);

                       if(ret != blkCount)
                       {
                           printf("read error: start blk %u, blkCount %u\n", blkStart, blkCount);
                           free(addr);
                           addr = NULL;
                           return 1;
                       }
                       else
                       {
                           totalBlock -= ret;
                           blkStart += ret;
                           printf("#");
                           if(traceCount++>0x80)
                           {
                             printf("\n");
                             traceCount = 0;
                           }

                       }
                    }

                    printf("\n\nread eMMC device with 1 block every time\n");
                    blkStart = 0;
                    traceCount = 0;
                    blkCount = 1;
                    totalBlock = mmc->block_dev.lba;
                    while(totalBlock>0)
                    {
                       u32 ret = 0;
                       ret = mmc->block_dev.block_read(0, blkStart, blkCount, addr);

                       if(ret != blkCount)
                       {
                           printf("read error: start blk %u, blkCount %u\n", blkStart, blkCount);
                           free(addr);
                           addr = NULL;
                           return 1;
                       }
                       else
                       {
                           totalBlock -= ret;
                           blkStart += ret;
                           traceCount += ret;

                           if((traceCount&blkChunk)==0)
                              printf("#");

                           if(traceCount>(0x80*blkChunk))
                           {
                              printf("\n");
                              traceCount = 0;
                           }
                       }
                    }

                    free(addr);
                    addr = NULL;
                    printf("\nMMC read: dev # %d, block # %d, count %u success\n",
                                curr_device, 0, (u32)(mmc->block_dev.lba));
                    return 0;

    } else if (strncmp(argv[1], "crcall", 7) == 0) {

                    u32 blkChunk = 4095;
                    u32 buf_size = blkChunk*512;
                    u32 blkStart = 0, blkCount = 0, traceCount = 0;
                    u32 totalBlock = 0;
                    void *addr = (void *)malloc(buf_size);
                    u32 crc2 = 0, crc1 = EMMC_CRC32_INIT;

                    if(addr == NULL)
                    {
                        printf("no memory\n");
                        return 1;
                    }

                    struct mmc *mmc = find_mmc_device(curr_device);
                    if (!mmc) {
                            printf("no mmc device at slot %x\n", curr_device);
                            free(addr);
                            addr = NULL;
                            return 1;
                    }

                    if(!mmc->has_init){
                        printf("Do mmc init first!\n");
                        mmc_init(mmc);
                        mmc->has_init = 1;
                    }

                    if(mmc->block_dev.block_read == NULL)
                    {
                        free(addr);
                        addr = NULL;
                        return 1;
                    }

                    //printf("\nread eMMC device with %d blocks every time\n", blkChunk);
                    blkStart = 0;
                    totalBlock = mmc->block_dev.lba ;
                    while(totalBlock>0)
                    {
                       u32 ret = 0;
                       blkCount = (totalBlock > blkChunk ? blkChunk : totalBlock);
                       ret = mmc->block_dev.block_read(0, blkStart, blkCount, addr);

                       if(ret != blkCount)
                       {
                           printf("read error: start blk %u, blkCount %u\n", blkStart, blkCount);
                           free(addr);
                           addr = NULL;
                           return 1;
                       }
                       else
                       {
                           totalBlock -= ret;
                           blkStart += ret;
                           printf("#");
                           if(traceCount++>0x80)
                           {
                             printf("\n");
                             traceCount = 0;
                           }
                           crc2 = crc32(crc1, addr, blkCount * 512);
                           crc1 = crc2;
                       }
                    }

                    free(addr);
                    addr = NULL;
                    printf("\nMMC read: dev # %d, block # %d, count %u success\n",
                                curr_device, 0, (u32)(mmc->block_dev.lba));
                    printf("eMMC CRC32: 0x%x!!\n", crc2);

                    return 0;

    } else if (strncmp(argv[1], "read", 4) == 0) {

        void *addr = (void *)simple_strtoul(argv[2], NULL, 16);
        u32 n, n2, cnt, size, tail = 0, partnum = 1;
        block_dev_desc_t *mmc_dev;
        disk_partition_t dpt;
        s32 blk = -1;
        char* cmdtail = strchr(argv[1], '.');
        char* cmdlasttail = strrchr(argv[1], '.');
        struct mmc *mmc = find_mmc_device(curr_device);

        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }

        size = simple_strtoul(argv[4], NULL, 16);
        cnt = ALIGN(size, 512) / 512;

        if(!mmc->has_init) {
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }

        if((cmdtail)&&(!strncmp(cmdtail, ".p", 2))) {
            mmc_dev = mmc_get_dev(curr_device);
            if ((mmc_dev == NULL) || (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
                printf("no mmc device found!\n");
                return 1;
            }

        #ifdef CONFIG_DOUBLE_MBOOT
        emmc_driver_desc_t ddb;
        int version_flag=EMMC_PARTITIONTABLE_VERSION3;
        int ret=mmc_dev->block_read(mmc_dev->dev, 0, 1, &ddb);
        if( ret!= 1 || ddb.signature != EMMC_DRIVER_MAGIC)
        {
                  version_flag=  EMMC_PARTITIONTABLE_VERSION3;
         }
        else if(ddb.version == EMMC_PARTITIONTABLE_VERSION2)
        {
                    version_flag=  EMMC_PARTITIONTABLE_VERSION2;
        }
          else if(ddb.version == EMMC_PARTITIONTABLE_VERSION3)
        {
                   version_flag=  EMMC_PARTITIONTABLE_VERSION3;
        }
        #endif

            for(;;){

                if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
                {

                        if(!strcmp(argv[3], MMC_DEFAULT_VOLUME))
                        {
                            strcpy((char *)&dpt.name, argv[3]);
                            #ifdef CONFIG_DOUBLE_MBOOT
                            if(version_flag==EMMC_PARTITIONTABLE_VERSION2)
                            {

                                    dpt.size = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V2, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V2, NULL, 16), 512) / 512;

                            }
                            else if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                            {
                                    dpt.size = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V3, NULL, 16), 512) / 512;

                            }
                            #else
                            dpt.size = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE, NULL, 16), 512) / 512;
                            dpt.start = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START, NULL, 16), 512) / 512;
                            #endif

                            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                                partnum=1;
                                printf("Add new partition %s success!\n", dpt.name);
                                continue;
                            }

                        }
                        else if(!strcmp(argv[3], FLASH_MBOOT_VOLUME))
                        {
                            strcpy((char *)&dpt.name, argv[3]);

                            #ifdef CONFIG_DOUBLE_MBOOT
                            if(version_flag==EMMC_PARTITIONTABLE_VERSION2)
                            {
                                    dpt.size = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V2, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V2, NULL, 16), 512) / 512;
                            }
                            else if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                            {
                                    dpt.size = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V3, NULL, 16), 512) / 512;
                            }
                            #else
                            dpt.size = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE, NULL, 16), 512) / 512;
                            dpt.start = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START, NULL, 16), 512) / 512;
                            #endif

                            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                                partnum=1;
                                printf("Add new partition %s success!\n", dpt.name);
                                continue;
                            }

                        #ifdef CONFIG_DOUBLE_MBOOT
                        }else if(!strcmp(argv[3], "MBOOTBAK"))
                        {
                            strcpy((char *)&dpt.name, argv[3]);

                            if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                            {
                                dpt.size = ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                dpt.start = ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_START_V3, NULL, 16), 512) / 512;;
                            }
                            else
                                break;

                            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                                partnum=1;
                                printf("Add new partition %s success!\n", dpt.name);
                                continue;
                            }
                        #endif
                        }else
                            break;

                }
                else
                {

                    if(!strcmp(argv[3], FLASH_MBOOT_VOLUME) && !strcmp((const char *)dpt.name, FLASH_MBOOT_VOLUME))
                    {

                        ulong mboot_size;
                        ulong mboot_start;

                        #ifdef CONFIG_DOUBLE_MBOOT
                                      if(version_flag ==  EMMC_PARTITIONTABLE_VERSION3)
                        {
                             mboot_size=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V3 , NULL, 16), 512) / 512;
                             mboot_start=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V3 , NULL, 16), 512) / 512;
                                        }
                        else
                        {
                             mboot_size=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V2 , NULL, 16), 512) / 512;
                             mboot_start=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V2 , NULL, 16), 512) / 512;
                        }
                        #else
                             mboot_size=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE , NULL, 16), 512) / 512;
                             mboot_start=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START, NULL, 16), 512) / 512;
                        #endif

                        if(dpt.size != mboot_size || dpt.start != mboot_start)
                        {
                            if (remove_emmc_partition(mmc_dev, &dpt) == 0)
                            {
                                        printf("MBOOT PARTITION ERROR REPAIR:Remove partition %s success!\n", dpt.name);
                                 }
                            else
                            {
                                 printf("MBOOT PARTITION ERROR REPAIR:Can't remove partition %s !\n", dpt.name);
                                 return 1;
                            }

                            continue;
                        }

                    }

                    if(!strcmp(argv[3], MMC_DEFAULT_VOLUME) && !strcmp((const char *)dpt.name, MMC_DEFAULT_VOLUME))
                    {
                         ulong mpool_size;
                         ulong mpool_start;

                         #ifdef CONFIG_DOUBLE_MBOOT
                         if(version_flag == EMMC_PARTITIONTABLE_VERSION3)
                         {

                             mpool_size=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V3 , NULL, 16), 512) / 512;
                             mpool_start=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V3 , NULL, 16), 512) / 512;
                         }
                         else
                         {
                             mpool_size=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V2, NULL, 16), 512) / 512;
                             mpool_start=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V2 , NULL, 16), 512) / 512;
                         }
                         #else
                               mpool_size=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE, NULL, 16), 512) / 512;
                             mpool_start=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START , NULL, 16), 512) / 512;
                         #endif

                        if(dpt.size != mpool_size || dpt.start != mpool_start)
                        {
                            if (remove_emmc_partition(mmc_dev, &dpt) == 0)
                            {
                                        printf("MPOOL PARTITION ERROR REPAIR:Remove partition %s success!\n", dpt.name);
                                 }
                            else
                            {
                                 printf("MPOOL PARTITION ERROR REPAIR:Can't remove partition %s !\n", dpt.name);
                                 return 1;
                            }

                            continue;
                        }

                    }


                    #ifdef CONFIG_DOUBLE_MBOOT
                                if(!strcmp(argv[3], "MBOOTBAK") && !strcmp((const char *)dpt.name, "MBOOTBAK"))
                    {
                         ulong mbootbak_size;
                         ulong mbootbak_start;

                         if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                        {
                                  mbootbak_size=ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                    mbootbak_start=ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_START_V3 , NULL, 16), 512) / 512;
                        }
                        else
                                break;

                        if(dpt.size != mbootbak_size || dpt.start != mbootbak_start)
                        {
                            if (remove_emmc_partition(mmc_dev, &dpt) == 0)
                            {
                                        printf("MBOOTBAK PARTITION ERROR REPAIR:Remove partition %s success!\n", dpt.name);
                                 }
                            else
                            {
                                 printf("MBOOTBAK PARTITION ERROR REPAIR:Can't remove partition %s !\n", dpt.name);
                                 return 1;
                            }

                            continue;
                        }

                    }
                    #endif

                    }


                if(!strcmp(argv[3], (const char *)dpt.name)) {

                    blk = dpt.start;
                    if(!strncmp(cmdlasttail, ".continue", 9))
                    {
                        blk += simple_strtoul(argv[4], NULL, 16);
                        size = simple_strtoul(argv[5], NULL, 16);
                        cnt = ALIGN(size, 512) / 512;
                    }
                    break;
                }
                partnum++;
            }

        }
        else if (((cmdtail)&&(!strncmp(cmdtail, ".boot", 5)))|| ((cmdtail)&&(!strncmp(cmdtail, ".gp", 3))))
        {
            addr = (void *)simple_strtoul(argv[3], NULL, 16);
            blk  = simple_strtoul(argv[4], NULL, 16);
            size = simple_strtoul(argv[5], NULL, 16);
            cnt  = ALIGN(size, 512) / 512;
        }
        else
            blk = simple_strtoul(argv[3], NULL, 16);

        if(blk < 0){
            printf("ERR:Please check the blk# or partiton name!\n");
            return 1;
        }

        /* unaligned size is allowed */
        if ((cnt << 9) > size)
        {
            cnt--;
            tail = size - (cnt << 9);
        }

        //printf("\nMMC read: dev # %d, block # %d, count %d ... ",
        //            curr_device, blk, cnt);

#if defined(MMC_SPEED_TEST) && MMC_SPEED_TEST
        //FCIE_HWTimer_Start();
        eMMC_hw_timer_start();
#endif

#if 0
        n = mmc->block_dev.block_read(curr_device, blk, cnt, addr);
#else
        if ((cmdtail)&&(!strncmp(cmdtail, ".boot", 5)))
        {
            if (strncmp(argv[2], "1", 1) == 0)
                n = eMMC_ReadBootPart(addr, cnt << 9, blk, 1);
            else if (strncmp(argv[2], "2", 1) == 0)
                n = eMMC_ReadBootPart(addr, cnt << 9, blk, 2);
            else
            {
                printf("mmc access boot partition parameter not found!\n");
                return 1;
            }
            n = (n == 0) ? cnt : -1;

            if (tail)
            {
                if (strncmp(argv[2], "1", 1) == 0)
                    n2 = eMMC_ReadBootPart(tmp_buf, 512, (blk + cnt), 1);
                else if (strncmp(argv[2], "2", 1) == 0)
                    n2 = eMMC_ReadBootPart(tmp_buf, 512, (blk + cnt), 2);
                else
                {
                    printf("mmc access boot partition parameter not found!\n");
                    return 1;
                }

                n2 = (n2 == 0) ? 1 : -1;
                memcpy(((unsigned char *)addr + (cnt << 9)), tmp_buf, tail);
                n += n2;
                cnt++;
            }
        }
        else if ((cmdtail)&&(!strncmp(cmdtail, ".gp", 3)))
        {
            int gp_part;

            gp_part =  simple_strtoul(argv[2], NULL, 10);
            if(gp_part >= 0 && gp_part < 4)
                n = eMMC_ReadGPPart(addr, 512, blk, gp_part);
            else
            {
                printf("mmc access GP partition No. %d is invalid!\n", gp_part);
                return 1;
            }
            n = (n == 0) ? cnt : -1;

            if (tail)
            {
                if(gp_part >= 0 && gp_part < 4)
                    n2 = eMMC_ReadGPPart(tmp_buf, 512, (blk + cnt), gp_part);
                else
                {
                    printf("mmc access GP partition No. %d is invalid!\n", gp_part);
                    return 1;
                }

                n2 = (n2 == 0) ? 1 : -1;
                memcpy(((unsigned char *)addr + (cnt << 9)), tmp_buf, tail);
                n += n2;
                cnt++;
            }
        }
        else
        {
            //printf("\33[1;36mmmc->block_dev.block_read(blk: %d, cnt: %d, addr: 0x%08X)\33[m\n", blk, cnt, (u32)addr);
            if (cnt > 0)
            {
                n = mmc->block_dev.block_read(0, blk, cnt, addr);
            }
            else if (cnt == 0)
            {
                n = 0;
            }

            if (tail)
            {
                n2 = mmc->block_dev.block_read(0, (blk + cnt), 1, tmp_buf);
                n2 = (n2 == 1) ? 1 : -1;
                memcpy(((unsigned char *)addr + (cnt << 9)), tmp_buf, tail);
                n += n2;
                cnt++;
            }
        }

        //dump_mem((char *)addr, 512); // add for debug & test

#endif

#if defined(MMC_SPEED_TEST) && MMC_SPEED_TEST
        if( n )
        {
            float speed = 0, tmp;
            unsigned int a, b = 0;
            U32 u32TotalMMCRWTime = 0;

            u32TotalMMCRWTime = eMMC_hw_timer_tick(); //FCIE_HWTimer_End();

            speed = (((float)(n*512))/(((float)u32TotalMMCRWTime)/((float)12000000)))/((float)(1024*1024));
            a = (int)speed;

            tmp = (speed - ((float)a))*1000;
            b = (int)tmp;

            printf("total time = %d.%03ds(%d)\n", u32TotalMMCRWTime/12000000, u32TotalMMCRWTime/12000, u32TotalMMCRWTime);
            printf("total size = %X\n", n*512);
            printf("emmc read speed = %d.%03d MB/s\n", a, b);
        }
#endif

        /* flush cache after read */
        flush_cache((ulong)addr, (cnt*512)); /* FIXME */

        //printf("%d blocks read: %s\n",
        //            n, (n==cnt) ? "OK" : "ERROR");
        return (n == cnt) ? 0 : 1;

    } else if (strncmp(argv[1], "write", 5) == 0) {

            //if(argc < 5)
            //    return cmd_usage(cmdtp);
            void *addr = (void *)simple_strtoul(argv[2], NULL, 16);
            u32 n=0, cnt, partnum = 1, empty_skip = 0, cont = 0,partition_flag=0;
            char* cmdtail = strchr(argv[1], '.');
            char* cmdlasttail = strrchr(argv[1], '.');
            block_dev_desc_t *mmc_dev;
            disk_partition_t dpt;

            s32 blk = -1;

            struct mmc *mmc = find_mmc_device(curr_device);

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            cnt = ALIGN(simple_strtoul(argv[4], NULL, 16), 512) / 512;
            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

#ifndef CONFIG_TSD
        {
        int slc_mode = 0;
            //check slc mode config for pair page damage when power lost
            if ((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[160] & 0x3) == 3))
            {
                if(mmc->ext_csd[EXT_CSD_PARTITIONS_ATTRIBUTE]&0x01)
                {
                    u64 ea_size = mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_0] + (mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_1]<<8) + (mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_2]<<16);
                    ea_size *= (mmc->ext_csd[221] * mmc->ext_csd[224]);
                    ea_size <<= 19;
                    if(ea_size == mmc->capacity)
                        slc_mode = 1;

                    if(!slc_mode && (ea_size>0))
                        printf("mmc->capacity %lld, enhanced user data erea size %lld\n", mmc->capacity, ea_size);
                }
            }

            //check reliable write config for pair page damage when power lost if no slc
            if(slc_mode==0)
            {
               if ((mmc->ext_csd[192] < 5) || ((mmc->ext_csd[EXT_CSD_WR_REL_SET]&0x01) == 0))
                  printf("WARNING: not config mmc as slc mode or reliable write, operation write has serious risk when powerlost!!!");
            }
        }
#endif
            if((cmdtail)&&(!strncmp(cmdtail, ".p", 2))){
           partition_flag=1;
                mmc_dev = mmc_get_dev(curr_device);
                if ((mmc_dev == NULL) ||
                    (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
                        printf("no mmc device found!\n");
                        return 1;
                }

            #ifdef CONFIG_DOUBLE_MBOOT
            emmc_driver_desc_t ddb;
            int version_flag=EMMC_PARTITIONTABLE_VERSION3;
            int ret=mmc_dev->block_read(mmc_dev->dev, 0, 1, &ddb);
            if( ret!= 1 || ddb.signature != EMMC_DRIVER_MAGIC)
            {
                    version_flag=  EMMC_PARTITIONTABLE_VERSION3;
            }
            else if(ddb.version == EMMC_PARTITIONTABLE_VERSION2)
            {
                        version_flag=  EMMC_PARTITIONTABLE_VERSION2;
            }
            else if(ddb.version == EMMC_PARTITIONTABLE_VERSION3)
            {
                        version_flag=  EMMC_PARTITIONTABLE_VERSION3;
            }
            #endif


                for(;;){

                    if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
            {
                        if(!strcmp(argv[3], MMC_DEFAULT_VOLUME))
                        {
                            strcpy((char *)&dpt.name, argv[3]);
                            #ifdef CONFIG_DOUBLE_MBOOT
                            if(version_flag==EMMC_PARTITIONTABLE_VERSION2)
                            {

                                    dpt.size = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V2, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V2, NULL, 16), 512) / 512;

                            }
                            else if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                            {
                                    dpt.size = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V3, NULL, 16), 512) / 512;

                            }
                            #else

                            dpt.size = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE , NULL, 16), 512) / 512;
                            dpt.start = ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START , NULL, 16), 512) / 512;
                            #endif

                            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                                partnum=1;
                                printf("Add new partition %s success!\n", dpt.name);
                                   continue;
                            }
                        }
                        else if(!strcmp(argv[3], FLASH_MBOOT_VOLUME))
                        {
                            strcpy((char *)&dpt.name, argv[3]);

                            #ifdef CONFIG_DOUBLE_MBOOT
                            if(version_flag==EMMC_PARTITIONTABLE_VERSION2)
                            {
                                    dpt.size = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V2, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V2, NULL, 16), 512) / 512;
                            }
                            else if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                            {
                                    dpt.size = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                    dpt.start = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V3, NULL, 16), 512) / 512;
                            }
                            #else
                            dpt.size = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE , NULL, 16), 512) / 512;
                            dpt.start = ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START , NULL, 16), 512) / 512;
                            #endif

                            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                                partnum=1;
                                printf("Add new partition %s success!\n", dpt.name);
                                   continue;
                            }

                        #ifdef CONFIG_DOUBLE_MBOOT
                        }else if(!strcmp(argv[3], "MBOOTBAK"))
                        {
                            strcpy((char *)&dpt.name, argv[3]);

                            if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                            {
                                dpt.size = ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                dpt.start = ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_START_V3, NULL, 16), 512) / 512;;
                            }
                            else
                                break;

                            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                                partnum=1;
                                printf("Add new partition %s success!\n", dpt.name);
                                continue;
                            }
                        #endif
                        }else
                            break;

                }
                else
                {

                    if(!strcmp(argv[3], FLASH_MBOOT_VOLUME) && !strcmp((const char *)dpt.name, FLASH_MBOOT_VOLUME))
                    {

                        ulong mboot_size;
                        ulong mboot_start;

                        #ifdef CONFIG_DOUBLE_MBOOT
                                      if(version_flag==  EMMC_PARTITIONTABLE_VERSION3)
                        {
                             mboot_size=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V3 , NULL, 16), 512) / 512;
                             mboot_start=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V3 , NULL, 16), 512) / 512;
                                        }
                        else
                        {
                             mboot_size=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE_V2 , NULL, 16), 512) / 512;
                             mboot_start=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START_V2 , NULL, 16), 512) / 512;
                        }
                        #else
                             mboot_size=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_SIZE , NULL, 16), 512) / 512;
                             mboot_start=ALIGN(simple_strtoull(EMMC_MBOOT_PATITION_START , NULL, 16), 512) / 512;
                        #endif

                        if(dpt.size != mboot_size || dpt.start != mboot_start)
                        {
                            if (remove_emmc_partition(mmc_dev, &dpt) == 0)
                            {
                                        printf("MBOOT PARTITION ERROR REPAIR:Remove partition %s success!\n", dpt.name);
                                 }
                            else
                            {
                                 printf("MBOOT PARTITION ERROR REPAIR:Can't remove partition %s !\n", dpt.name);
                                 return 1;
                            }

                            continue;
                        }

                    }

                    if(!strcmp(argv[3], MMC_DEFAULT_VOLUME) && !strcmp((const char *)dpt.name, MMC_DEFAULT_VOLUME))
                    {
                         ulong mpool_size;
                         ulong mpool_start;

                         #ifdef CONFIG_DOUBLE_MBOOT
                         if(version_flag==  EMMC_PARTITIONTABLE_VERSION3)
                         {
                             mpool_size=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V3 , NULL, 16), 512) / 512;
                             mpool_start=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V3 , NULL, 16), 512) / 512;
                         }
                         else
                         {
                             mpool_size=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE_V2, NULL, 16), 512) / 512;
                             mpool_start=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START_V2 , NULL, 16), 512) / 512;
                         }
                         #else
                               mpool_size=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_SIZE, NULL, 16), 512) / 512;
                             mpool_start=ALIGN(simple_strtoull(EMMC_MPOOL_PATITION_START , NULL, 16), 512) / 512;
                         #endif

                        if(dpt.size != mpool_size || dpt.start != mpool_start)
                        {
                            if (remove_emmc_partition(mmc_dev, &dpt) == 0)
                            {
                                        printf("MPOOL PARTITION ERROR REPAIR:Remove partition %s success!\n", dpt.name);
                                 }
                            else
                            {
                                 printf("MPOOL PARTITION ERROR REPAIR:Can't remove partition %s !\n", dpt.name);
                                 return 1;
                            }

                            continue;
                        }

                    }


                    #ifdef CONFIG_DOUBLE_MBOOT
                                if(!strcmp(argv[3], "MBOOTBAK") && !strcmp((const char *)dpt.name, "MBOOTBAK"))
                    {
                         ulong mbootbak_size;
                         ulong mbootbak_start;

                         if(version_flag==EMMC_PARTITIONTABLE_VERSION3)
                        {
                                  mbootbak_size=ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_SIZE_V3, NULL, 16), 512) / 512;
                                    mbootbak_start=ALIGN(simple_strtoull(EMMC_MBOOTBAK_PATITION_START_V3 , NULL, 16), 512) / 512;
                        }
                        else
                                break;


                        if(dpt.size != mbootbak_size || dpt.start != mbootbak_start)
                        {
                            if (remove_emmc_partition(mmc_dev, &dpt) == 0)
                            {
                                        printf("MBOOTBAK PARTITION ERROR REPAIR:Remove partition %s success!\n", dpt.name);
                                 }
                            else
                            {
                                 printf("MBOOTBAK PARTITION ERROR REPAIR:Can't remove partition %s !\n", dpt.name);
                                 return 1;
                            }

                            continue;
                        }

                    }
                    #endif

                    }

                    if(!strcmp(argv[3], (const char *)dpt.name)){
                        blk = dpt.start;
                        if(!strncmp(cmdlasttail, ".continue", 9))
                        {
                            blk += simple_strtoul(argv[4], NULL, 16);
                            cnt = ALIGN(simple_strtoul(argv[5], NULL, 16), 512) / 512;
                            cont = 1;
                        }
                        break;
                    }
                    partnum++;
                    #if ENABLE_TVCONFIG_PARTITION
                    if (0 == strcmp(argv[3], "tvdatabase") || 0 == strcmp(argv[3], "tvconfig"))
                    {
                        setenv("upgrade_factorydb", "TRUE");
                        saveenv();
                    }
                    #endif
                }
            }
        else if (((cmdtail)&&(!strncmp(cmdtail, ".boot", 5))) || ((cmdtail)&&(!strncmp(cmdtail, ".gp", 3))))
            {
                addr = (void *)simple_strtoul(argv[3], NULL, 16);
                blk = simple_strtoul(argv[4], NULL, 16);
                cnt = ALIGN(simple_strtoul(argv[5], NULL, 16), 512) / 512;
            }
            else
                blk = simple_strtoul(argv[3], NULL, 16);

            if(blk < 0){
                printf("ERR:Please check the blk# or partiton name!\n");
                return 1;
            }

            //printf("MMC write: dev # %d, block # %d, count %d ...\n", curr_device, blk, cnt);

            #if defined(MMC_SPEED_TEST) && MMC_SPEED_TEST
            //FCIE_HWTimer_Start();
            eMMC_hw_timer_start();
            #endif

            #if 0
                n = mmc->block_dev.block_write(curr_device, blk, cnt, addr);
            #else
            if ((cmdtail)&&(!strncmp(cmdtail, ".boot", 5)))
            {
        if(cnt > g_eMMCDrv.u32_BOOT_SEC_COUNT)
        {
            printf("\n eMMC not enough boot partition size for write!");
            return 1;
        }

        if (strncmp(argv[2], "1", 1) == 0)
        {
                      n = eMMC_WriteBootPart(addr, cnt << 9, blk, 1);
        }
        else if (strncmp(argv[2], "2", 1) == 0)
        {
                      n = eMMC_WriteBootPart(addr, cnt << 9, blk, 2);
        }
        else {
            printf("mmc access boot partition parameter not found!\n");
            return 1;
        }

        n = (n == 0) ? cnt : -1;
            }
        else if ((cmdtail)&&(!strncmp(cmdtail, ".gp", 3)))
        {
            int gp_part;

            gp_part =  simple_strtoul(argv[2], NULL, 10);
            if(gp_part >= 0 && gp_part < 4)
                n = eMMC_WriteGPPart(addr, 512, blk, gp_part);
            else
            {
                printf("mmc access GP partition No. %d is invalid!\n", gp_part);
                return 1;
            }
            n = (n == 0) ? cnt : -1;
        }
            else
            {
                if ((argc == 6) && (cont == 0))
                {
                    empty_skip = simple_strtoul(argv[5], NULL, 16);
                }
                if ((argc == 7) && (cont == 1))
                {
                    empty_skip = simple_strtoul(argv[6], NULL, 16);
                }

                if(((blk+cnt)>(dpt.start+dpt.size)) && (partition_flag == 1))
                {
               printf("\n\n*****ERROR:the write data size (%d-%d) bigger than the partition %s size (%ld-%ld)!*****\n\n",blk,blk+cnt,dpt.name,dpt.start,dpt.start+dpt.size);
             return 1;
          }

                n = do_mmc_write_emptyskip(mmc, blk, cnt, addr, empty_skip);
            }
            #endif

            #if defined(MMC_SPEED_TEST) && MMC_SPEED_TEST
            if( n )
            {
                float speed = 0, tmp;
                unsigned int a, b = 0;
                U32 u32TotalMMCRWTime = 0;

                u32TotalMMCRWTime = eMMC_hw_timer_tick(); //FCIE_HWTimer_End();

                speed = (((float)(n*512))/(((float)u32TotalMMCRWTime)/((float)12000000)))/((float)(1024*1024));
                a = (int)speed;

                tmp = (speed - ((float)a))*1000;
                b = (int)tmp;

                printf("total time = %d.%03ds(%d)\n", u32TotalMMCRWTime/12000000, u32TotalMMCRWTime/12000, u32TotalMMCRWTime);
                printf("total size = %X\n", n*512);
                printf("emmc write speed = %d.%03d MB/s\n", a, b);
            }
            #endif

            printf("%d blocks written: %s\n",
                        n, (n == cnt) ? "OK" : "ERROR");
            return (n == cnt) ? 0 : 1;

    } else if(strncmp(argv[1], "create", 6) == 0) {

                block_dev_desc_t *mmc_dev;
                disk_partition_t dpt;
        char* cmdtail = strchr(argv[1], '.');
                struct mmc *mmc = find_mmc_device(curr_device);

                if (!mmc) {
                    printf("no mmc device at slot %x\n", curr_device);
                    return 1;
                }

                if(!mmc->has_init){
                    printf("Do mmc init first!\n");
                    mmc_init(mmc);
                    mmc->has_init = 1;
                }

                mmc_dev = mmc_get_dev(curr_device);
                if ((mmc_dev == NULL) ||
                    (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
                    printf("no mmc device found!\n");
                    return 1;
                }

        if(cmdtail == NULL)
        {
            if(!strncmp(argv[3], "MAX", 3)) //Use Remaining Emmc Size.
            {
                #define RESERVE_BLOCK 4160 //Emmc table:64block + Emmc driver:2MB
                unsigned int u32RemainingBlock = 0;
                unsigned int u32MmcCapacityBlock =0;
                u32MmcCapacityBlock=mmc->capacity/512;
                u32RemainingBlock=u32MmcCapacityBlock-get_emmc_used_blockcount(mmc_dev);
                if(u32RemainingBlock<=RESERVE_BLOCK)
                {
                    dpt.size=0;
                    printf("ERROR: no enoggh space!!\n");
                }
                else
                {
                    dpt.size=u32RemainingBlock-RESERVE_BLOCK;
                }
            }
            else
            {
                if(simple_strtoull(argv[3], NULL, 16)%512!=0)
                {
                    printf("\n\n\n******** ERROR:partition (%s) size must be 512-byte aligned! ******** \n\n\n",argv[2]);
                }
                dpt.size = ALIGN(simple_strtoull(argv[3], NULL, 16), 512) / 512;
            }
            if(argc > 4)
                dpt.start = ALIGN(simple_strtoull(argv[4], NULL, 16), 512) / 512;
            else
                dpt.start = 0;

            strcpy((char *)&dpt.name, argv[2]);
            if (add_new_emmc_partition(mmc_dev, &dpt) == 0){
                printf("Add new partition %s success!\n", dpt.name);
                return 0;
            }
        }
        else if((cmdtail)&&(!strncmp(cmdtail, ".gp", 3)))
        {
            uint8_t u8_PartNo, u8_EnAttr, u8_ExtAttr, u8_RelW;
            uint32_t u32_PartSize;

            if(argc < 7)
                return cmd_usage(cmdtp);

            u8_PartNo = simple_strtoul(argv[2], NULL, 16);
            u32_PartSize = simple_strtoull(argv[3], NULL, 16);
            u8_EnAttr = simple_strtoul(argv[4], NULL, 16);
            u8_ExtAttr = simple_strtoul(argv[5], NULL, 16);
            u8_RelW = simple_strtoul(argv[7], NULL, 16);

            return eMMC_SetGPPartition(u8_PartNo, u32_PartSize, u8_EnAttr, u8_ExtAttr, u8_RelW);
        }
        else if((cmdtail)&&(!strncmp(cmdtail, ".enhusr", 7)))
        {
            uint8_t u8_EnAttr, u8_RelW;
            uint32_t u32_StartAddr, u32_Size;

            if(argc < 6)
                return cmd_usage(cmdtp);

            u32_StartAddr = simple_strtoull(argv[2], NULL, 16);
            u32_Size = simple_strtoull(argv[3], NULL, 16);
            u8_EnAttr = simple_strtoul(argv[4], NULL, 16);
            u8_RelW = simple_strtoul(argv[4], NULL, 16);

            return eMMC_SetEnhanceUserPartition(u32_StartAddr,u32_Size, u8_EnAttr, u8_RelW);
        }
        else if((cmdtail)&&(!strncmp(cmdtail, ".complete", 9)))
        {
            int err;
            err =  eMMC_SetPartitionComplete();
            if(err)
                return err;
            else
            {
                while(1)
                    printf("General Purpose Partition and Enhance Partition are configured successfully. Please Reset Power.\n");
            }
        }
        else
            return cmd_usage(cmdtp);
                return 1;
    } else if(strncmp(argv[1], "remove", 6) == 0) {

                block_dev_desc_t *mmc_dev;
                disk_partition_t dpt;
                struct mmc *mmc = find_mmc_device(curr_device);

                if (!mmc) {
                    printf("no mmc device at slot %x\n", curr_device);
                    return 1;
                }

                if(!mmc->has_init){
                    printf("Do mmc init first!\n");
                    mmc_init(mmc);
                    mmc->has_init = 1;
                }

                mmc_dev = mmc_get_dev(curr_device);
                if ((mmc_dev == NULL) ||
                    (mmc_dev->type == DEV_TYPE_UNKNOWN)) {
//                    print_part(mmc_dev);
                    printf("no mmc device found!\n");
                    return 1;
                }
                strcpy((char *)&dpt.name, (const char *)argv[2]);

                if (remove_emmc_partition(mmc_dev, &dpt) == 0){
                    printf("Remove partition %s success!\n", dpt.name);
                    return 0;
                }
                return 1;

    } else if (strncmp(argv[1], "rmgpt", 5) == 0){

        struct mmc *mmc = find_mmc_device(curr_device);
        unsigned long *reset;
        int i;
        U8 u8_uboot_partnum,u8_mpool_partnum;
        #ifdef CONFIG_DOUBLE_MBOOT
        U8 u8_mbootbak_partnum;
        #endif
        block_dev_desc_t *mmc_dev;
        char* cmdtail = strchr(argv[1], '.');

        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }
        if(!mmc->has_init){
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }
        mmc_dev = mmc_get_dev(curr_device);
        if ( (mmc_dev == NULL) || (mmc_dev->type == DEV_TYPE_UNKNOWN) )
        {
            printf("no mmc device found!\n");
            return 1;
        }

        u8_uboot_partnum = Search_Mboot_partition_emmc(mmc_dev);
        u8_mpool_partnum = Search_Mpool_partition_emmc(mmc_dev);
        #ifdef CONFIG_DOUBLE_MBOOT
        u8_mbootbak_partnum = Search_Mbootbak_partition_emmc(mmc_dev);
        #endif

        if((u8_uboot_partnum > 0)||(u8_mpool_partnum > 0))
        {
            unsigned char force_rmgpt=0;
            reset = (unsigned long *)malloc(512);

            if(reset == NULL)
            {
                printf("malloc fail!\n");
                return 1;
            }

            memset(reset, 0, 512);
            if((cmdtail)&&(!strncmp(cmdtail, ".all", 4)))
            {
                force_rmgpt=1;
                printf("remove all partition info\n");
            }

            for(i=1;i<= EMMC_RESERVED_FOR_MAP_V2;i++)
            {
                #ifdef CONFIG_DOUBLE_MBOOT
                if((force_rmgpt==0)&&(((i == u8_uboot_partnum)&&(u8_uboot_partnum >0))
                    ||((i == u8_mpool_partnum)&&(u8_mpool_partnum >0))
                    || ((i == u8_mbootbak_partnum)&&(u8_mbootbak_partnum >0))))
                #else
                if((force_rmgpt==0)&&(((i == u8_uboot_partnum)&&(u8_uboot_partnum >0))
                    ||((i == u8_mpool_partnum)&&(u8_mpool_partnum >0))))
                #endif
                {
                    continue; // keep data for ROM boot
                }
                else
                {
                    mmc->block_dev.block_write(curr_device, i, 1, reset);
                }
            }
        }
        else
        {
            printf("no UBOOT or MPOOL Partition found!\n");
            reset = (unsigned long *)malloc(512);

            if(reset == NULL)
            {
                printf("malloc fail!\n");
                return 1;
            }

            memset(reset, 0, 512);

            for(i=1;i<= g_emmc_reserved_for_map;i++)
            {
                mmc->block_dev.block_write(curr_device, i, 1, reset);
            }
        }

        free(reset);
        return 0;

    } else if (strcmp(argv[1], "slc") == 0) {

            struct mmc *mmc = find_mmc_device(curr_device);
            unsigned long long size;
            int reliable_write, ret;
            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if (argc < 4) {
                printf ("Usage:\n%s\n", cmdtp->usage);
                return 1;
            }

            size = simple_strtoul(argv[2], NULL, 16);
            reliable_write = simple_strtoul(argv[3], NULL, 16);
            if ((reliable_write != 0) && (reliable_write != 1))
            {
                printf("Reliable write enable can only be set to be 0 or 1!!!\n");
                return 1;
            }
            if ((size == 0) && (reliable_write == 0))
            {
                printf("Both of slc size and reliable write configuration are zero, please input proper values!!!\n");
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            ret = mmc_slc_mode(mmc, size, reliable_write);

            return ret;

#ifndef CONFIG_TSD
    } else if (strcmp(argv[1], "ecsd") == 0) {
        struct mmc *mmc = find_mmc_device(curr_device);
        int ret;
        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }

        if(!mmc->has_init){
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }

        ret = mmc_ecsd_read(mmc);

        return ret;
#endif
    } else if (strcmp(argv[1], "size") == 0) {
        struct mmc *mmc = find_mmc_device(curr_device);
        u8 empty_flag;

        if (!mmc) {
            printf("no mmc device at slot %x\n", curr_device);
            return 1;
        }

        if(!mmc->has_init){
            printf("Do mmc init first!\n");
            mmc_init(mmc);
            mmc->has_init = 1;
        }

        u64 blksz=512, blknum=0;
        blknum = mmc->capacity / blksz;
        if(mmc->ext_csd[181] == 0)
        {
            empty_flag = 0;
        }
        else
        {
            empty_flag = 0xff;
        }

        printf("EMMC size info as below:\n");
        printf("Totalsize:%lld bytes\t Blocksize:%lld bytes\t Blocknum:%lld\n",mmc->capacity,blksz,blknum);
        printf("The default value after erase operation is: 0x%x\n", empty_flag);
        printf("SLC partition size:%lld bytes\t max slc size:%lld bytes\n", mmc->slc_size, mmc->max_slc_size);
        if ((mmc->max_slc_size << 1) == mmc->capacity)
        {
            printf("All space can be converted to slc mode\n");
        }
        else
        {
            printf("Only part of space can be converted to slc mode\n");
        }
        if (mmc->reliable_write == 1)
        {
            printf("Reliable write is supported but unconfigured\n");
        }
        else if (mmc->reliable_write == 2)
        {
            printf("Reliable write is supported and has been configured\n");
        }
        else if (mmc->reliable_write == 0)
        {
            printf("Reliable write is unsupported\n");
        }

        return 0;
    } else if (strcmp(argv[1], "slcchk") == 0) {
        // MStar Start
        struct mmc *mmc = find_mmc_device(curr_device);
        int ret;

        if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
        }

        if (!mmc->has_init)
        {
        mmc_init(mmc);
        mmc->has_init = 1;
        }

        ret = mmc_slc_check(mmc);
        return ret;
        // MStar End
    } else if (strcmp(argv[1], "relwrchk") == 0) {
        // MStar Start
        struct mmc *mmc = find_mmc_device(curr_device);
        int ret;

        if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return 1;
        }

        if (!mmc->has_init)
        {
        mmc_init(mmc);
        mmc->has_init = 1;
        }

        ret = mmc_relwr_check(mmc);
        return ret;
        // MStar End
        } else if (strcmp(argv[1], "slcrelwrchk") == 0) {
            // MStar Start
            struct mmc *mmc = find_mmc_device(curr_device);
            int ret;

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if (!mmc->has_init)
            {
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            ret = mmc_slc_relwr_check(mmc);
            return ret;
            // MStar End
    } else if(strncmp(argv[1], "unlzo", 5) == 0) {

#ifdef CONFIG_LZO
            struct mmc *mmc = find_mmc_device(curr_device);
            int ret=0;

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            if (argc < 5) {
                printf ("Usage:\n%s\n", cmdtp->usage);
                return 1;
            }

            ret = do_unlzo(mmc, argc, argv);
            return ret;
#else
            printf("Please check the LZO config\n");
            return 0;
#endif
    } else if (strncmp(argv[1], "erase", 5) == 0) {

            u32 boot_partition = 0;     //default user area partition
            u32 n, cnt = 0, partnum = 1;
            char* cmdtail = strchr(argv[1], '.');
            block_dev_desc_t *mmc_dev;
            u64 erase_size = 0;
            disk_partition_t dpt;
            s32 start = -1;

            struct mmc *mmc = find_mmc_device(curr_device);

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            if(argc==4) {
                start = simple_strtoul(argv[2], NULL, 16);
                erase_size =  simple_strtoull(argv[3], NULL, 16);  //Bytes
                if((erase_size<=0) || (erase_size&0x1FF))
                {
                    printf("invalied erase size [%llXh], must aligned to 512 bytes\n", erase_size);
                    return 1;
                }

                cnt = erase_size >> 9;  // /unit 512B
            }

            if((cmdtail)&&(!strncmp(cmdtail, ".p", 2)))
            {
                if(argc!=3) //not specify partition name
                    return cmd_usage(cmdtp);

                mmc_dev = mmc_get_dev(curr_device);
                if ((mmc_dev == NULL) ||
                    (mmc_dev->type == DEV_TYPE_UNKNOWN))
                {
                        printf("no mmc device found!\n");
                        return 1;
                }

                for(;;)
                {
                    if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
                        break;
                    if(!strcmp(argv[2], (const char *)dpt.name)){
                        start = dpt.start;
                        cnt = dpt.size; //block number
                        break;
                    }
                    partnum++;
                }

                if(cnt==0) {
                    printf("ERR:invalid parameter, please check partiton name!\n");
                    return 1;
                }
            }
            else if((cmdtail)&&(!strncmp(cmdtail, ".boot", 5))) { //erase boot partition
                boot_partition = 1;

                start = 0;
                cnt = g_eMMCDrv.u32_BOOT_SEC_COUNT;

                if(cnt==0)
                {
                    printf("ERR:emmc no boot partition size !\n");
                    return 1;
                }
            } else if(argc==2) {             //erase all blocks in user area partiiton
                start = 0;
                cnt = mmc->block_dev.lba;
            }

            if(start < 0)
            {
                printf("ERR:invalid parameter, please check the blk# or partiton name!\n");
                return 1;
            }

            if(cnt <= 0)
            {
                printf("ERR:invalid parameter, Please check size!\n");
                return 1;
            }

            if(((!boot_partition)&&(cnt > mmc->block_dev.lba)) ||((boot_partition)&&(cnt>g_eMMCDrv.u32_BOOT_SEC_COUNT)))
                printf("ERR:invalid parameter, please check the size#!\n");

            printf("MMC erase: dev # %d, %s part, block # %d, count %d (unit: sector)... \n",
                        curr_device, boot_partition ? "boot" : "user area", start, cnt);

        if(!boot_partition)
            n = mmc->block_dev.block_erase(0, start, cnt);
        else {
#ifndef CONFIG_TSD
            if (strncmp(argv[2], "1", 1) == 0)
                n = eMMC_EraseBootPart(start, start + cnt - 1, 1);
            else if (strncmp(argv[2], "2", 1) == 0)
                n = eMMC_EraseBootPart(start, start + cnt - 1, 2);
            else
            {
                printf("mmc access boot partition parameter not found!\n");
                return 1;
            }

            n = (n == 0) ? cnt : -1;
#else
            n = 0;
            printf("eMMC err: tSD has no boot partition\n");
#endif
        }
        printf("%d blocks erase: %s\n", n, (n == cnt) ? "OK" : "ERROR");

        return (n == cnt) ? 0 : 1;

    } else if(strcmp(argv[1], "dd") == 0) {

#ifdef CONFIG_USB
            struct mmc *mmc = find_mmc_device(curr_device);
            int ret=0, port=0, pad = 1;
	      char usb_start_command[20];

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            if(argc > 3)
                port = (int)simple_strtoul (argv[3], NULL, 16);

            if(argc > 4)
                pad = (int)simple_strtoul (argv[4], NULL, 16);

            sprintf(usb_start_command,"usb start %d",port);
            run_command(usb_start_command, 0);

            if(strcmp(argv[2], "mmc2usb") == 0)
                ret = do_ddmmc(mmc, argv, 0, pad);
            else if(strcmp(argv[2], "usb2mmc") == 0)
                ret = do_ddmmc(mmc, argv, 1, pad);
            else
                return cmd_usage(cmdtp);

            return ret;
#else
            printf("Please check the USB config\n");
            return 0;
#endif
    } else if (strcmp(argv[1], "alignsize") == 0) {
            struct mmc *mmc = find_mmc_device(curr_device);
            int ret;
            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            ret = mmc_get_alignsize(mmc);

            return ret;

#ifndef CONFIG_TSD

    } else if (strcmp(argv[1], "setecsd") == 0) {
            u8 num, mask, value;
            struct mmc *mmc = find_mmc_device(curr_device);
            int ret;

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            if (argc < 5) {
                printf ("Usage:\n%s\n", cmdtp->usage);
                return 1;
            }

            num = (u8)simple_strtoul(argv[2], NULL, 16);
            mask = (u8)simple_strtoul(argv[3], NULL, 16);
            value = (u8)simple_strtoul(argv[4], NULL, 16);

            ret = mmc_ecsd_write(mmc, num, mask, value);

            return ret;
#endif

    }else if (strncmp(argv[1], "trim_test", 4) == 0) {
            float speed = 0;
            u32 temp_start = TRIM_START_OFFSET,  duration = 0, chunk_size = 8, loop_count = 16;
            u64 totalsize = 0;
            u32 n, error_count = 0;
            ulong u32speed_write = 0, u32speed_trim_write = 0;
            ulong u32speed_read = 0, u32speed_trim_read = 0;
            void *addr = 0, *temp_addr = 0;

            struct mmc *mmc = find_mmc_device(curr_device);

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            if(mmc->ext_csd[192] <= 5 ){
                printf("Trim should be used on 4.5 version or later emmc!\n");
                //return 0;
            }

            if(argc > 3){
                chunk_size = (simple_strtoul(argv[2], NULL, 16)& (~511))/ 512;  //512B
                loop_count = simple_strtoul(argv[3], NULL, 16);
            }

            if((chunk_size < 1) || (loop_count <= 0))
            {
                printf("invalide parameters===========================\n");
                return 1;
            }

            addr = (char *)UPGRADE_BUFFER_ADDR;

            MDrv_WDT_Init((WDT_DbgLv)0);

            //printf("sequential emmc read test\n");
            //printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
            totalsize = 0;
            error_count = 0;
            speed = 0;
            temp_start = TRIM_START_OFFSET;
            temp_addr = addr;

            if(mmc->block_dev.block_write(0, 0, chunk_size*loop_count, temp_addr)
                != chunk_size*loop_count){
                printf("write failure!\n");
                return 1;
            }

            MDrv_TIMER_Count(E_TIMER_0, 1);

            for(n=0; n<loop_count; ++n)
            {
                if(mmc->block_dev.block_read(0, temp_start, chunk_size, temp_addr) != chunk_size)
                    ++error_count;
                else
                    totalsize += chunk_size;

                temp_start += chunk_size;
                temp_addr += chunk_size*512;
                if(temp_start > mmc->block_dev.lba)
                    temp_start = TRIM_START_OFFSET;
            }

            duration = MDrv_TIMER_GetMs(E_TIMER_0);
            totalsize *= 512;
            speed = (double)totalsize/((double)duration);
            u32speed_read= (ulong)speed;
            //printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed_read, error_count);
            //printf("\n\n");

            mmc->block_dev.block_erase(0, 0, chunk_size*loop_count);

            //printf("sequential emmc read after trim test\n");
            //printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
            totalsize = 0;
            error_count = 0;
            speed = 0;
            temp_start = TRIM_START_OFFSET;
            temp_addr = addr;
            MDrv_TIMER_Count(E_TIMER_0, 1);

            for(n=0; n<loop_count; ++n)
            {
                if(mmc->block_dev.block_read(0, temp_start, chunk_size, temp_addr) != chunk_size)
                    ++error_count;
                else
                    totalsize += chunk_size;

                temp_start += chunk_size;
                temp_addr += chunk_size*512;
                if(temp_start > mmc->block_dev.lba)
                    temp_start = TRIM_START_OFFSET;
            }

            duration = MDrv_TIMER_GetMs(E_TIMER_0);
            totalsize *= 512;
            speed = (double)totalsize/((double)duration);
            u32speed_trim_read= (ulong)speed;
            //printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed_trim_read, error_count);
            //printf("\n\n");

            //printf("sequential emmc write test\n");
            //printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
            totalsize = 0;
            error_count = 0;
            speed = 0;
            temp_start = TRIM_START_OFFSET;
            temp_addr = addr;

            if(mmc->block_dev.block_write(0, 0, chunk_size*loop_count, temp_addr)
                != chunk_size*loop_count){
                printf("write failure!\n");
                return 1;
            }

            MDrv_TIMER_Count(E_TIMER_0, 1);

            for(n=0; n<loop_count; ++n)
            {
                if(mmc->block_dev.block_write(0, temp_start, chunk_size, temp_addr) != chunk_size)
                    ++error_count;
                else
                    totalsize += chunk_size;

                temp_start += chunk_size;
                temp_addr += chunk_size*512;
                if(temp_start > mmc->block_dev.lba)
                    temp_start = TRIM_START_OFFSET;
            }

            duration = MDrv_TIMER_GetMs(E_TIMER_0);
            totalsize *= 512;
            speed = (double)totalsize/((double)duration);
            u32speed_write= (ulong)speed;
            //printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed, error_count);
            //printf("\n\n");

            mmc->block_dev.block_erase(0, 0, chunk_size*loop_count);

            //printf("sequential emmc write after trim test\n");
            //printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
            totalsize = 0;
            error_count = 0;
            speed = 0;
            temp_start = TRIM_START_OFFSET;
            temp_addr = addr;
            MDrv_TIMER_Count(E_TIMER_0, 1);

            for(n=0; n<loop_count; ++n)
            {
                if(mmc->block_dev.block_write(0, temp_start, chunk_size, temp_addr) != chunk_size)
                    ++error_count;
                else
                    totalsize += chunk_size;

                temp_start += chunk_size;
                temp_addr += chunk_size*512;
                if(temp_start > mmc->block_dev.lba)
                    temp_start = TRIM_START_OFFSET;
            }

            duration = MDrv_TIMER_GetMs(E_TIMER_0);
            totalsize *= 512;
            speed = (double)totalsize/((double)duration);
            u32speed_trim_write = (ulong)speed;
            //printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed_trim, error_count);
            //printf("\n\n");


            printf("sequential read speed %lu KB/s\n",u32speed_read);
            printf("(enable trim)sequential read speed %lu KB/s\n",u32speed_trim_read);
            printf("sequential write speed %lu KB/s\n",u32speed_write);
            printf("(enable trim)sequential write speed %lu KB/s\n",u32speed_trim_write);
            printf("\n");

            if(u32speed_trim_read>u32speed_read)
                printf("sequential read performance has been improved %lu%% after enable trim\n",
                            (u32speed_trim_read-u32speed_read)*100 / u32speed_read);
            else
                printf("sequential read performance has been worsened %lu%% after enable trim\n",
                            (u32speed_read-u32speed_trim_read)*100 / u32speed_read);

            if(u32speed_trim_write>u32speed_write)
                printf("sequential write performance has been improved %lu%% after enable trim\n",
                            (u32speed_trim_write-u32speed_write)*100 / u32speed_write);
            else
                printf("sequential write performance has been worsened %lu%% after enable trim\n",
                            (u32speed_write-u32speed_trim_write)*100 / u32speed_write);

            return 0;
    }
#if defined(TEST_PERFORMANCE) && TEST_PERFORMANCE
    else if (strncmp(argv[1], "test", 4) == 0) {
            float speed = 0;
            u32 temp_start = 0,  duration = 0, chunk_size = 512, loop_count = 16;
            u64 totalsize = 0;
            u32 n, error_count = 0;
            ulong * start = 0;
            ulong u32speed = 0;
            void *addr = 0;
            char* cmdtail = strchr(argv[1], '.');

            struct mmc *mmc = find_mmc_device(curr_device);

            if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return 1;
            }

            if(!mmc->has_init){
                printf("Do mmc init first!\n");
                mmc_init(mmc);
                mmc->has_init = 1;
            }

            if((cmdtail)&&(strncmp(cmdtail, ".life", 5)))
            {
                addr = (void *)simple_strtoul(argv[2], NULL, 16);
                chunk_size = (simple_strtoul(argv[3], NULL, 16)& (~511))/ 512;  //512B
                loop_count = simple_strtoul(argv[4], NULL, 16);
                if((addr<=0) || (chunk_size < 1) || (loop_count <= 0))
                {
                   printf("invalide parameters===========================\n");
                   return 1;
                }
            }

            //Sequential write test ******************************************************************//
            if((cmdtail)&&(!strncmp(cmdtail, ".ws", 3)))
            {
                printf("sequential emmc write test\n");
                printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
                memset(addr, 0xaa,  chunk_size*512);
                totalsize = 0;
                error_count = 0;
                speed = 0;
                temp_start = 0;

                MDrv_WDT_Init((WDT_DbgLv)0);
                MDrv_TIMER_Count(E_TIMER_0, 1);

                for(n=0; n<loop_count; ++n)
                {
                    if(mmc->block_dev.block_write(0, temp_start, chunk_size, addr) != chunk_size)
                        ++error_count;
                    else
                        totalsize += chunk_size;

                    temp_start += chunk_size;
                    if(temp_start > mmc->block_dev.lba)
                        temp_start = 0;
                }

                duration = MDrv_TIMER_GetMs(E_TIMER_0);
                totalsize *= 512;
                speed = (double)totalsize/((double)duration);
                u32speed = (ulong)speed;
                printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed, error_count);
                printf("\n\n");
                return 0;
            }

            //random write test****************************************************************************//
            if((cmdtail)&&(!strncmp(cmdtail, ".wr", 3)))
            {
                printf("random emmc write test\n");
                printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
                start = (ulong *)malloc(loop_count*4);
                if(start==0) {
                   printf("malloc buffer for random address failed\n");
                   return 1;
                }

                //generate ramdom start block address
                for(n=0; n<loop_count; ++n)
                {
                    start[n] = rRand(0, 0) % (mmc->block_dev.lba/chunk_size);

                    if(start[n] > 0)
                        start[n] -= 1;
                    //printf("mmc->block_dev.lba = %d,  n=%d, start = %d\n", mmc->block_dev.lba, n, start[n]);
                }

                memset(addr, 0xaa,  chunk_size*512);
                totalsize = 0;
                error_count = 0;
                speed = 0;
                MDrv_WDT_Init((WDT_DbgLv)0);
                MDrv_TIMER_Count(E_TIMER_0, 1);

                for(n=0; n<loop_count; ++n)
                {
                    if(mmc->block_dev.block_write(0, start[n]*chunk_size, chunk_size, addr) != chunk_size)
                        ++error_count;
                    else
                        totalsize += chunk_size;
                }

                duration = MDrv_TIMER_GetMs(E_TIMER_0);
                totalsize *= 512;
                speed = (double)totalsize/((double)duration);
                u32speed = (ulong)speed;
                printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed, error_count);
                free(start);
                printf("\n\n");
                return 0;
            }

            //Sequential read test ******************************************************************//
            if((cmdtail)&&(!strncmp(cmdtail, ".rs", 3)))
            {
                printf("sequential emmc read test\n");
                printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
                memset(addr, 0xaa,  chunk_size*512);
                totalsize = 0;
                error_count = 0;
                speed = 0;
                temp_start = 0;

                MDrv_WDT_Init((WDT_DbgLv)0);
                MDrv_TIMER_Count(E_TIMER_0, 1);

                for(n=0; n<loop_count; ++n)
                {
                    if(mmc->block_dev.block_read(0, temp_start, chunk_size, addr) != chunk_size)
                        ++error_count;
                    else
                        totalsize += chunk_size;

                    temp_start += chunk_size;
                    if(temp_start > mmc->block_dev.lba)
                        temp_start = 0;
                }

                duration = MDrv_TIMER_GetMs(E_TIMER_0);
                totalsize *= 512;
                speed = (double)totalsize /((double)duration);
                u32speed = (ulong)speed;
                printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed, error_count);
                printf("\n\n");
                return 0;
            }

            //random read test****************************************************************************//
            if((cmdtail)&&(!strncmp(cmdtail, ".rr", 3)))
            {
                printf("random emmc read test\n");
                printf("chunksize %d * 512B, loop count %d\n", chunk_size, loop_count);
                start = (ulong *)malloc(loop_count*4);
                if(start==0) {
                   printf("malloc buffer for random address failed\n");
                   return 1;
                }

                //generate ramdom start block num
                for(n=0; n<loop_count; ++n)
                {
                    start[n] = rRand(0, 0) % (mmc->block_dev.lba/chunk_size);

                    if(start[n] > 0)
                        start[n] -= 1;
                    //printf("mmc->block_dev.lba = %d, n=%d, start = %d\n", mmc->block_dev.lba, n, start[n]);
                }

                totalsize = 0;
                error_count = 0;
                speed = 0;

                MDrv_WDT_Init((WDT_DbgLv)0);
                MDrv_TIMER_Count(E_TIMER_0, 1);

                for(n=0; n<loop_count; ++n)
                {
                    if(mmc->block_dev.block_read(0, start[n]*chunk_size, chunk_size, addr) != chunk_size)
                        ++error_count;
                    else
                        totalsize += chunk_size;
                }

                duration = MDrv_TIMER_GetMs(E_TIMER_0);
                totalsize *= 512;
                speed = (double)totalsize/((double)duration);
                u32speed = (ulong)speed;
                printf("time %u ms, speed %lu KB/s, error count %u\n", duration, u32speed, error_count);
                free(start);
                printf("\n\n");
                return 0;
            }

            //working life test****************************************************************************//
            if((cmdtail)&&(!strncmp(cmdtail, ".life", 5)))
            {
                unsigned long *src = NULL;
                u32 blocks_todo = 0, max_block_num = 0;
                u32 cur = 0, try_count = 0;
                u64 write_count_loop = 0;
                char buf[80];

                printf("emmc working life test\n\n");
                sprintf(buf, "%d", 0);
                setenv("emmc_working_life_count", buf);
                saveenv();

                src = (unsigned long *)1342177280;
                max_block_num = 16*1024*2;

                while(1)
                {
                    blocks_todo = mmc->block_dev.lba;
                    temp_start = 0;
                    //write all eMMC device
                    do
                    {
                        cur = (blocks_todo > max_block_num) ? max_block_num : blocks_todo;
                        //printf("start %d   cur %d  blocktodo %d\n", temp_start, cur, blocks_todo);

                        if(mmc->block_dev.block_write(0, temp_start, cur, src) != cur)
                        {
                            ++try_count;
                            if(try_count > 10)
                            {
                                printf("eMMC life over, loop cout: %llu\n", write_count_loop);

                                sprintf(buf, "%llu", write_count_loop);
                                setenv("emmc_working_life_count", buf);
                                saveenv();
                                return 1;
                            }
                            continue; //write same address again
                        }

                        printf("#");
                        try_count = 0;
                        blocks_todo -= cur;
                        temp_start += cur;
                    } while (blocks_todo > 0);

                    ++write_count_loop;
                    printf("\neMMC lifetest loop %llu\n\n", write_count_loop);
                }

                return 0;
            }

            return 0;
    }
#endif
        return cmd_usage(cmdtp);
}

// =======================================================================
// quickly CMD for front lines
// =======================================================================
int do_eMMCops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u32 u32_err = eMMC_ST_SUCCESS;
    #if defined(IF_IP_VERIFY) && IF_IP_VERIFY
    u32 u32_buf,u32_BlkStartAddr;
    #endif

	// ----------------------------------------
	if (strcmp(argv[1], "info") == 0)
	{
        eMMC_Dump_eMMCStatus();
		eMMC_DumpDriverStatus();
		eMMC_PrintDeviceInfo();

        if(argc>2 && strcmp(argv[2], "more")==0)
        {
            printf("\n\n");
		    eMMC_DumpPadClk();
		    eMMC_FCIE_DumpRegisters();
		    eMMC_FCIE_DumpDebugBus();
            printf("\n\n");
        }
		return 1;
    }
    else if (strcmp(argv[1], "reg") == 0)
    {
        eMMC_FCIE_DumpRegisters();
        return 1;
    }
    else if (strcmp(argv[1], "CID") == 0)
    {
        unsigned char au8_CID[16];
        eMMC_GetCID(au8_CID);
        eMMC_dump_mem(au8_CID, 15);
        return 1;
    }
    else if (strcmp(argv[1], "reset") == 0)
    {
        if(simple_strtoul(argv[2], NULL, 16) )
        {
            printf("eMMC reset pin high\n");
            eMMC_RST_H();
        }
        else
        {   printf("eMMC reset pin low\n");
            eMMC_RST_L();
        }

        return 0;
    }
    else if (strcmp(argv[1], "sanitize") == 0)
    {
        U32 u32_t0, u32_t1, u32_err;

        printf("eMMC: please wait...\n");

        eMMC_hw_timer_start();
        u32_t0 = eMMC_hw_timer_tick();
        u32_err = eMMC_Sanitize(0xAA);
        u32_t1 = eMMC_hw_timer_tick();

        if(eMMC_ST_SUCCESS!=u32_err)
        {
            printf("eMMC Err: sanitize fail: %Xh\n", u32_err);
            return 0;
        }

        if(u32_t0 > u32_t1)
            printf("sanitize time: %u ms\n",
                (0xFFFFFFFF-u32_t0+u32_t1)/(eMMC_HW_TIMER_HZ/1000));
        else
            printf("sanitize time: %u ms\n",
                (u32_t1-u32_t0)/(eMMC_HW_TIMER_HZ/1000));

        return 0;
    }
    else if (strcmp(argv[1], "init") == 0)
    {
        u32 u32_LoopCnt, u32_i, u32_t0, u32_t1;

        eMMC_hw_timer_start();

        u32_LoopCnt = simple_strtoul(argv[2], NULL, 16);
        for(u32_i=0; u32_i<u32_LoopCnt; u32_i++)
        {
            eMMC_ResetReadyFlag();
            u32_t0 = eMMC_hw_timer_tick();
            eMMC_DISABLE_LOG(1);
            eMMC_Init();
            eMMC_DISABLE_LOG(0);
            u32_t1 = eMMC_hw_timer_tick();
            if(u32_t0 > u32_t1)
                printf("timer overflow\n");
            else
                printf("init time: %u ms\n",
                    (u32_t1-u32_t0)/(eMMC_HW_TIMER_HZ/1000));
        }
    }

    #if defined(IF_IP_VERIFY) && IF_IP_VERIFY
    // ----------------------------------------
    else if (strcmp(argv[1], "test") == 0)
    {
		u32 u32_LoopCnt, u32_i, u32_byte_cnt;
        void *addr_dma;
        // --------------------
        if(strcmp(argv[2], "rom")==0)
        {
            addr_dma = (void *)simple_strtoul(argv[3], NULL, 16);
            u32_byte_cnt = simple_strtoul(argv[4], NULL, 16);
            eMMC_BootMode(addr_dma, u32_byte_cnt);
            return 0;
        }
        else if(strcmp(argv[2], "wp")==0 && strcmp(argv[3], "boot")==0)
        {
            eMMC_verify_BootPartition_WP();
            return 0;
        }
        else if(strcmp(argv[2], "wp")==0 && strcmp(argv[3], "user")==0 && strcmp(argv[4], "st")==0)
        {
            eMMC_get_UserWPStatus(simple_strtoul(argv[5], NULL, 16), gau8_eMMC_SectorBuf);
            return 0;
        }
        else if(strcmp(argv[2], "wp")==0 && strcmp(argv[3], "user")==0)
        {
            printf("WPGrpSize: %u MB, total: %Xh sectors \n", eMMC_get_WPGropuSize(), g_eMMCDrv.u32_SEC_COUNT);
            eMMC_verify_UserWP_WRC(simple_strtoul(argv[4], NULL, 16));
            return 0;
        }

		// --------------------
        if(strcmp(argv[2], "hilowtemp") == 0)
        {
            eMMC_IPVerify_SDRDDR_AllClkTemp();
            return 1;
        }

        // --------------------
        u32_LoopCnt = simple_strtoul(argv[2], NULL, 16);
        printf("u32_LoopCnt: %Xh\n", u32_LoopCnt);

        if((strcmp(argv[3], "big") == 0))
        {
            puts("Warnning:\n"
               "big test option will damage all of your data\n"
               "including the kernel, file system\n"
               "and environments in eMMC.\n\n"
               "Do you really want to do it? (y/n)\n");
            if (!(getc() == 'y' && getc() == '\r'))
                return 0;
        }

        if(u32_LoopCnt==0x3697)
        {
            while(1) {
                if(strcmp(argv[3], "ro") == 0)
                    u32_err = eMMC_IPVerify_ReadOnly();
                else if(strcmp(argv[3], "wo") == 0)
                {
                    U16 u16_pattern = simple_strtoul(argv[4], NULL, 16);
                    u32_err = eMMC_IPVerify_WriteOnly(u16_pattern);
                }
                else if(strcmp(argv[3], "big") == 0)
                {
                        u32_err = eMMC_IPVerify_Main_Big();
                }
                else
                    u32_err = eMMC_IPVerify_Main();

                if(eMMC_ST_SUCCESS != u32_err)
                    break;
            }
        }
        for(u32_i=0; u32_i<u32_LoopCnt; u32_i++)
        {
            printf("Test: %u \n", u32_i);

            if(strcmp(argv[3], "ro") == 0)
            {
                u32_err = eMMC_IPVerify_ReadOnly();
            }
            else if(strcmp(argv[3], "wo") == 0)
            {
                U16 u16_pattern = simple_strtoul(argv[4], NULL, 16);
                printf("pattern --> %04Xh\n", u16_pattern );
                u32_err = eMMC_IPVerify_WriteOnly(u16_pattern);
            }
            else
                u32_err = eMMC_IPVerify_Main();

            if(eMMC_ST_SUCCESS != u32_err)
                break;
        }
        if(eMMC_ST_SUCCESS == u32_err)
            printf("ok\n");
    }
    // ----------------------------------------
      #if defined ENABLE_eMMC_ATOP && ENABLE_eMMC_ATOP
    else if (strcmp(argv[1], "pll") == 0)
    {
        static U32 u32_emmc_pll_clock = 0;

        if(!u32_emmc_pll_clock) {
            u32_emmc_pll_clock = eMMC_PLL_CLK_FAST;
            eMMC_clock_setting(u32_emmc_pll_clock);
            REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_CLK_EN);
        }
        else {
            u32_emmc_pll_clock--;
            if(u32_emmc_pll_clock == (eMMC_PLL_CLK_SLOW-1))
                u32_emmc_pll_clock = eMMC_PLL_CLK_FAST;
            eMMC_clock_setting(u32_emmc_pll_clock);
            REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_CLK_EN);
        }
    }
      #endif
    // ----------------------------------------
    else if (strcmp(argv[1], "speed") == 0)
    {
        eMMC_IPVerify_Performance();
    }
    else if (strcmp(argv[1], "life") == 0)
    {
        if(0 == strcmp(argv[2], "fixed"))
            eMMCTest_Lifetime(eMMC_LIFETIME_TEST_FIXED);
        if(0 == strcmp(argv[2], "filled"))
            eMMCTest_Lifetime(eMMC_LIFETIME_TEST_FILLED);
        if(0 == strcmp(argv[2], "random"))
            eMMCTest_Lifetime(eMMC_LIFETIME_TEST_RANDOM);

        return 0;
    }
    else if(strcmp(argv[1], "pwr_cut") == 0)
    {
        if(strcmp(argv[2], "init") == 0)
        {
            u32_buf = simple_strtoul(argv[3], NULL, 16);
            u32_BlkStartAddr = simple_strtoul(argv[4], NULL, 16);

            if(eMMC_ST_SUCCESS == eMMCTest_PwrCut_InitData((U8*)u32_buf,u32_BlkStartAddr))
                printf("eMMC Info: eMMC Power Cut Init OK\n");
            else
            {
                printf("eMMC Err: eMMC Power Cut Init Fail\n");
                return 1;
            }
        }
        else if(strcmp(argv[2], "test") == 0)
        {
            u32_buf = simple_strtoul(argv[3], NULL, 16);
            u32_BlkStartAddr = simple_strtoul(argv[4], NULL, 16);

            if(eMMC_ST_SUCCESS == eMMCTest_PwrCut_Test((U8*)u32_buf,u32_BlkStartAddr))
                printf("eMMC Info: eMMC Power Cut Test OK\n");
            else
            {
                printf("eMMC Err: eMMC Power Cut Test Fail\n");
                return 1;
            }
        }
        #ifdef STATIC_RELIABLE_TEST
        else if(strcmp(argv[2], "pmtest") == 0)
            {
            char buf[16];
                sprintf(buf, "%d", 1);
             setenv("eMMC_PMReliableWriteTest_enable_env", buf);
                do_test_reliable_write();
           }
    #endif
    }

    #endif // IF_IP_VERIFY

    // ----------------------------------------
    else if (strcmp(argv[1], "t_table") == 0)
    {
        // --------------------------------
        if(strcmp(argv[2], "erase") == 0)
        {
            U8 u8_i;

            g_eMMCDrv.TimingTable_t.u32_ChkSum = ~g_eMMCDrv.TimingTable_t.u32_ChkSum;

            memcpy(gau8_eMMC_SectorBuf, (U8*)&g_eMMCDrv.TimingTable_t, sizeof(g_eMMCDrv.TimingTable_t));

            for(u8_i=0; u8_i<4; u8_i++)
            {   // erase DDR, HS200, HS400, HS400 ext table
                u32_err = eMMC_CMD24(eMMC_DDRTABLE_BLK_0+(u8_i*2), gau8_eMMC_SectorBuf);
                if(eMMC_ST_SUCCESS != u32_err)
                {
                    printf("eMMC Err: erase t_table.1 fail: %Xh\n", u32_err);
                    return 1;
                }
                u32_err = eMMC_CMD24(eMMC_DDRTABLE_BLK_1+(u8_i*2), gau8_eMMC_SectorBuf);
                if(eMMC_ST_SUCCESS != u32_err)
                {
                    printf("eMMC Err: erase t_table.2 fail: %Xh\n", u32_err);
                    return 1;
                }
            }

            printf(" ok \n");
        }
        // --------------------------------
        else if(strcmp(argv[2], "hs400") == 0)
        {
            #if !(defined(ENABLE_eMMC_HS400) && ENABLE_eMMC_HS400)
            printf("\n host does not support \n");
            return 0;
            #else

            #if ((defined(eMMC_DRV_MONACO_UBOOT) && eMMC_DRV_MONACO_UBOOT) || \
                 (defined(eMMC_DRV_CLIPPERS_UBOOT) && eMMC_DRV_CLIPPERS_UBOOT) || \
                 (defined(eMMC_DRV_MONET_UBOOT) && eMMC_DRV_MONET_UBOOT))
            if( (REG_FCIE(reg_chip_version)>>8) >= 0x01 )
            {
            #endif
            g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HS400_DETECT;

            // DS mode uses HS200 timing table for CMD
            if(eMMC_ST_SUCCESS == eMMC_FCIE_BuildHS200TimingTable())
            {
                // HS400 use DLL setting for DAT[0-7]
                u32_err = eMMC_FCIE_DetectHS400Timing();
                if(eMMC_ST_SUCCESS != u32_err)
                {
                    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
                               "eMMC Err: eMMC_FCIE_DetectHS400Timing fail: %Xh\n", u32_err);
                    eMMC_FCIE_ErrHandler_Stop();
                }

                printf("\n ok \n");
            }
            else
                printf("\n fail \n");

            #if ((defined(eMMC_DRV_MONACO_UBOOT) && eMMC_DRV_MONACO_UBOOT) || \
                 (defined(eMMC_DRV_CLIPPERS_UBOOT) && eMMC_DRV_CLIPPERS_UBOOT) || \
                 (defined(eMMC_DRV_MONET_UBOOT) && eMMC_DRV_MONET_UBOOT))
            }
            else
            {
                printf("\n host does not support \n");
                return 0;
            }
            #endif
            #endif
        }
        // --------------------------------
        else if(strcmp(argv[2], "hs200") == 0)
        {
            #if !(defined(ENABLE_eMMC_HS200) && ENABLE_eMMC_HS200)
            printf("\n host does not support \n");
            return 0;
            #else
            if(eMMC_ST_SUCCESS == eMMC_FCIE_BuildHS200TimingTable())
                printf("\n ok \n");
            else
                printf("\n fail \n");
            #endif
        }
        // --------------------------------
        else if(strcmp(argv[2], "ddr") == 0)
        {
            #if !((defined(IF_DETECT_eMMC_DDR_TIMING) && IF_DETECT_eMMC_DDR_TIMING) || (defined(ENABLE_eMMC_ATOP) && ENABLE_eMMC_ATOP) )
            printf("\n host does not support \n");
            return 0;
            #else
            if(eMMC_ST_SUCCESS == eMMC_FCIE_BuildDDRTimingTable())
                printf("\n ok \n");
            else
                printf("\n fail \n");
            #endif
        }
        else if(strcmp(argv[2], "temp") == 0)
        {
            #if defined(ENABLE_eMMC_HS400) && ENABLE_eMMC_HS400
            U8 u8_i,u8_enable_error_log=0;

            u8_enable_error_log = simple_strtoul(argv[3], NULL, 16);
            for(u8_i=0;u8_i<10;u8_i++)
            {
                eMMC_FCIE_DetectHS200Timing_SKEW1_SKEW4(u8_enable_error_log);
            }

            for(u8_i=0;u8_i<10;u8_i++)
            {
               eMMC_FCIE_DetectHS400Timing_SKEW4_RX(u8_enable_error_log);
            }

            for(u8_i=0;u8_i<10;u8_i++)
            {
               eMMC_FCIE_DetectHS400Timing_SKEW4_SKEW1(u8_enable_error_log);
            }

            for(u8_i=0;u8_i<10;u8_i++)
            {
               eMMC_FCIE_DetectHS400Timing_SKEW1_SKEW2(u8_enable_error_log);
            }

            for(u8_i=0;u8_i<10;u8_i++)
            {
               eMMC_FCIE_DetectHS400Timing_TrigerLevel_RX(u8_enable_error_log);
            }
            #endif
            printf("\n done \n");

        }
        else if(strcmp(argv[2], "dump") == 0)
        {
            eMMC_FCIE_ChooseSpeedMode();
            eMMC_DumpTimingTable();
        }

        return 0;
    }
    // ----------------------------------------
    else if (strcmp(argv[1], "mode") == 0)
    {
        if(strcmp(argv[2], "sdr") == 0)
        {
            if(eMMC_ST_SUCCESS == eMMC_FCIE_EnableSDRMode())
            {
                printf("\neMMC Info: SDR mode ok \n");
                eMMC_clock_setting(FCIE_DEFAULT_CLK);
            }
            else
                printf("\neMMC Err: SDR mode fail \n");
        }
        else if(strcmp(argv[2], "best") == 0)
        {
            #if defined(IF_IP_VERIFY) && IF_IP_VERIFY
            if(eMMC_ST_SUCCESS == eMMC_FCIE_ChooseSpeedMode())
                printf("\neMMC Info: best speed mode ok \n");
            else
                printf("\neMMC Err: best speed mode fail \n");
            #endif
        }
        else
            return 1;
    }
    // ----------------------------------------
    else if (strcmp(argv[1], "clk") == 0)
    {
        u8 u8_clk = simple_strtoul(argv[2], NULL, 16);

        eMMC_clock_setting(u8_clk);
        printf("clk:%u KHz\n", (unsigned int)g_eMMCDrv.u32_ClkKHz);
    }
    // ----------------------------------------
    else if (strcmp(argv[1], "cis") == 0)
    {
        if(strcmp(argv[2], "check") == 0)
        {
            printf("\n");

            #if eMMC_RSP_FROM_RAM
            if(eMMC_ST_SUCCESS == eMMC_LoadDriverContext(gau8_eMMC_SectorBuf))
                printf("eMMC Info: DrvContext ok\n");
            else
                printf("eMMC Info: no DrvContext\n");

            if(eMMC_ST_SUCCESS == eMMC_LoadRsp(g_eMMCDrv.au8_AllRsp))
                printf("eMMC Info: AllRsp ok\n");
            else
                printf("eMMC Info: no AllRsp\n");
            #endif

            #if defined(IF_IP_VERIFY) && IF_IP_VERIFY
            #ifndef IP_FCIE_VERSION_5
            if(eMMC_ST_SUCCESS == eMMC_FCIE_ChooseSpeedMode())
                printf("eMMC Info: DDRT Table ok\n");
            else
            #endif
                printf("eMMC Info: no DDRT Table\n");
            #endif

        }
        else if(strcmp(argv[2], "erase") == 0)
        {
            if(eMMC_ST_SUCCESS == eMMC_EraseBlock(eMMC_CIS_BLK_0, eMMC_CIS_BLK_END))
                printf("eMMC Info: erase cis ok\n");
            else
                printf("eMMC Err: erase cis fail\n");
        }
        else
            return 1;
    }

    #if (defined(ENABLE_eMMC_ATOP) && ENABLE_eMMC_ATOP) && \
        ((defined(ENABLE_eMMC_HS200) && ENABLE_eMMC_HS200) || \
         (defined(ENABLE_eMMC_HS400) && ENABLE_eMMC_HS400))
    else if (strcmp(argv[1], "phase") == 0)
    {
        while(1)
        {
            eMMC_debug(0,0,"\n\n==================================================\n");
            #if defined(ENABLE_eMMC_HS200) && ENABLE_eMMC_HS200
            extern U32 eMMC_FCIE_HS200_IrwinTest(void);
            eMMC_FCIE_HS200_IrwinTest();
            #endif
            #if defined(ENABLE_eMMC_HS400) && ENABLE_eMMC_HS400
            extern U32 eMMC_FCIE_HS400_IrwinTest(void);
            eMMC_FCIE_HS400_IrwinTest();
            #endif
        }
    }
    #endif

    #if defined(ENABLE_eMMC_HS400) && ENABLE_eMMC_HS400
    else if (strcmp(argv[1], "settrig") == 0) // set trigger level
    {
        U8 u8TrigLevel;
        extern void eMMC_SetTrigerLevel(U8 u8Level);

        u8TrigLevel = simple_strtoul(argv[2], NULL, 10);
        eMMC_SetTrigerLevel(u8TrigLevel);
    }
    else if (strcmp(argv[1], "setwp") == 0) // set write phase
    {
        U8 u8WritePhase;
        extern void eMMC_SetWritePhase(U8 u8CmdData, U8 u8Phase);

        if(strcmp(argv[2], "cmd") == 0)
        {
            u8WritePhase = simple_strtoul(argv[3], NULL, 10);
            eMMC_SetWritePhase(3, u8WritePhase);
        }
        else if(strcmp(argv[2], "data") == 0)
        {
            u8WritePhase = simple_strtoul(argv[3], NULL, 10);
            eMMC_SetWritePhase(2, u8WritePhase);
        }
        else if(strcmp(argv[2], "clk") == 0)
        {
            u8WritePhase = simple_strtoul(argv[3], NULL, 10);
            eMMC_SetWritePhase(1, u8WritePhase);
        }
        else if(strcmp(argv[2], "skew4") == 0)
        {
            u8WritePhase = simple_strtoul(argv[3], NULL, 10);
            eMMC_SetWritePhase(4, u8WritePhase);
        }
    }
    #endif

    return 0;
}

#ifdef STATIC_RELIABLE_TEST
/*static reliable write test ***************************************************/
#define MAX_RLIABLE_TEST_LOOP 5000
#define MAX_RLIABLE_TRASACTION (16*0x100000/512) // block number: 2MB - 512bytes
#define MAX_RLIABLE_SLEEP_TIME 500  // 30 ms
#define MIN_RELIABLE_SLEEP_TIME 30
#define RLIABLE_SLEEP_TIME_START 0
#define RELIABLE_START_OFFSET   (0x2000000/512)
#define RELIABLE_TEST_SIZE          (mmc->block_dev.lba-0x800-RELIABLE_START_OFFSET)
#define RELIABLE_AUTOSET 1   //0
//check below value in fcie driver to cut off power
int reliable_test_sleep = 0; //ms
int enable_pm_sleep_flag = 0;

#if RELIABLE_AUTOSET
extern int mmc_switch(struct mmc *mmc, u8 set, u8 index, u8 value);
#endif

int do_test_reliable_write(void)
{
    char buf[16];
    char * reliable_test_sleep_c = 0;
    char * reliable_test_bstart_c = 0;
    char * reliable_test_loop_c = 0;
    char * reliable_test_success=0;
    char * reliable_write_test_enable = NULL;
    int check_memory = 1;
    u64 reliable_test_bstart = 0;
    u64 blocks_todo = 0, max_block_num = 0;
    u64 previous_startblk = 0;
    u64 start = 0, cur = 0;
    u64 test_loop = 0;
    u32 reliable_write_enable = 0;
    int slc_mode = 0;
    unsigned long *src = NULL;
    u64 startblk = 0;

    reliable_test_loop_c = getenv("static_reliable_testloop_env");
    reliable_test_sleep_c = getenv("static_reliable_sleep_env");
    reliable_test_bstart_c = getenv("static_reliable_pstart_env");
    reliable_test_success = getenv("static_reliable_test_success");

    if(reliable_test_loop_c==0 && (reliable_test_success==NULL || (int)simple_strtol(reliable_write_test_enable, NULL, 10)==0))
   {
   	  sprintf(buf, "%d", 1);
         setenv("eMMC_PMReliableWriteTest_enable_env", buf);
   }

    reliable_write_test_enable = getenv("eMMC_PMReliableWriteTest_enable_env");
    if(reliable_write_test_enable == NULL)
    {
        //printf("Please set env eMMC_ReliableWriteTest_enable_env 1 before issue reliable write test\n");
        return 0;
    }
    reliable_write_enable = (int)simple_strtol(reliable_write_test_enable, NULL, 10);
    if(reliable_write_enable == 0)
    {
        //printf("Please set env eMMC_ReliableWriteTest_enable_env 1 before issue reliable write test\n");
        return 0;
    }

    if (curr_device < 0)
    {
        if (get_mmc_num() > 0)
            curr_device = 0;
        else
        {
            puts("No MMC device available\n");
            return 1;
        }
    }

    struct mmc *mmc = find_mmc_device(curr_device);

    if (!mmc)
    {
          printf("no mmc device at slot %x\n", curr_device);
          return 1;
    }

    if(!mmc->has_init)
    {
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }

    //check slc mode config for pair page damage when power lost
    if ((mmc->ext_csd[192] >= 5) && ((mmc->ext_csd[160] & 0x3) == 3))
    {
        if(mmc->ext_csd[EXT_CSD_PARTITIONS_ATTRIBUTE]&0x01)
        {
            u64 ea_size = mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_0] + (mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_1]<<8) + (mmc->ext_csd[EXT_CSD_ENH_SIZE_MULT_2]<<16);
            ea_size *= (mmc->ext_csd[221] * mmc->ext_csd[224]);
            ea_size <<= 19;
            if(ea_size == mmc->capacity)
                slc_mode = 1;

            if(!slc_mode && (ea_size>0))
                printf("mmc->capacity %lld Bytes, enhanced user data erea size %lld Bytes\n", mmc->capacity, ea_size);
        }
    }

    //check reliable write config for pair page damage when power lost if no slc
    #if RELIABLE_AUTOSET
    if(slc_mode==0)
    {
        if (mmc->reliable_write == 2)
        {
            printf("Reliable write is supported and has been configured\n");
        }
        else if (mmc->reliable_write == 1)
        {
            printf("Reliable write is supported and has not been configured\n");
            mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_ERASE_GROUP_DEF, 1);
            mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, 167, 0x1f);

            // complete the partition configuration
            mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PARTITION_SETTING_COMPLETED, 0x01);

            while(1)
                printf("The reliable write has been setting, please RESET board to be in effect!!!!!!!!!!!!\n");
        }
        else if (mmc->reliable_write == 0)
        {
            printf("Reliable write is unsupported\n");
            return 1;
        }
    }
    else
        printf("slc mode has been set!\n");
    #endif

    printf("static reliable write ext_csd[167] %02x, ext_csd[156] %02x\n", mmc->ext_csd[167], mmc->ext_csd[156]);

    if(reliable_test_loop_c == 0)
    {
        src = (unsigned long *)UPGRADE_BUFFER_ADDR;
        memset((void *)src, 0xab, 16*1024*1024);  //16MB
        max_block_num = 16*1024*2;
    blocks_todo = (RELIABLE_TEST_SIZE == mmc->block_dev.lba) ?
        (mmc->block_dev.lba - RELIABLE_START_OFFSET) : RELIABLE_TEST_SIZE;
        start = RELIABLE_START_OFFSET;
        printf("init emmc with fixed value 0xab from blk 0x%llX to blk 0x%llX xxxxx\n", start, start + blocks_todo);

        do
        {
            cur = (blocks_todo > max_block_num) ? max_block_num : blocks_todo;
            if(mmc->block_dev.block_write(0, start, cur, src) != cur)
                return 0;
		flush_cache_all();
            blocks_todo -= cur;
            start += cur;
        } while (blocks_todo > 0);

        printf("init emmc with fixed value 0xab  done \n");
        test_loop = 0;
        check_memory = 0;
        sprintf(buf, "%d", 0);
        setenv("static_reliable_test_success", buf);
    }
    else
    {
        test_loop = (int)simple_strtol(reliable_test_loop_c, NULL, 10);
        if(test_loop == 0)
        {
            src = (unsigned long *)UPGRADE_BUFFER_ADDR;
            memset((void *)src, 0xab, 16*1024*1024);  //16MB
            max_block_num = 16*1024*2;
            blocks_todo = (RELIABLE_TEST_SIZE == mmc->block_dev.lba) ?
                (mmc->block_dev.lba - RELIABLE_START_OFFSET) : RELIABLE_TEST_SIZE;
            start = RELIABLE_START_OFFSET;
            printf("init emmc with fixed value 0xab from blk 0x%llX to blk 0x%llX yyyyyyy\n", start, start + blocks_todo);

            do
            {
                cur = (blocks_todo > max_block_num) ? max_block_num : blocks_todo;
                if(mmc->block_dev.block_write(0, start, cur, src) != cur)
                    return 0;
			flush_cache_all();
                blocks_todo -= cur;
                start += cur;
            } while (blocks_todo > 0);
            check_memory = 0;
            printf("init emmc with fixed value 0xab  done yyyyyyyyyyyyyyyyyyyyyyyyy\n");
            sprintf(buf, "%d", 0);
            setenv("static_reliable_test_success", buf);
        }
    }

    if(reliable_test_sleep_c == 0)
    {
       reliable_test_sleep = MIN_RELIABLE_SLEEP_TIME;
    }
    else
    {
        reliable_test_sleep = (int)simple_strtol(reliable_test_sleep_c, NULL, 10);
        if(test_loop == 0)
            reliable_test_sleep = MIN_RELIABLE_SLEEP_TIME;
    }

    if(reliable_test_bstart_c == 0)
    {
        reliable_test_bstart = RELIABLE_START_OFFSET + 133;
    }
    else
    {
        reliable_test_bstart = (int)simple_strtol(reliable_test_bstart_c, NULL, 10);
        if(test_loop == 0)
        {
           reliable_test_bstart = RELIABLE_START_OFFSET + 133;
           reliable_test_sleep = MIN_RELIABLE_SLEEP_TIME;
        }
    }

    previous_startblk = reliable_test_bstart;
    startblk = rRand(previous_startblk+test_loop, previous_startblk+333-test_loop);

    if(startblk == previous_startblk)
        startblk += 763;

    if((startblk+MAX_RLIABLE_TRASACTION) > (mmc->block_dev.lba))
    {
        startblk = startblk % (mmc->block_dev.lba);
    }

    if(startblk + MAX_RLIABLE_TRASACTION > (RELIABLE_TEST_SIZE + RELIABLE_START_OFFSET))
    {
        startblk = startblk % (RELIABLE_TEST_SIZE + RELIABLE_START_OFFSET);
    }

    if(startblk < RELIABLE_START_OFFSET)
    {
        startblk = startblk + RELIABLE_START_OFFSET;
    }

    char str[300];
    printf("loop %llu previous startblk %llu, now startblk %llu\n", test_loop, previous_startblk, startblk);
    sprintf(str,"loop %llu previous %llu, now %llu\n", test_loop, previous_startblk, startblk);
    setenv("reliable_test_info_3", str);
    saveenv();

    if(check_memory == 1)
    {
        char * p;
        u64 index = 0;
        u64 glo_pre_start, glo_pre_end;
        u64 glo_now_index = 0;

        glo_pre_start = previous_startblk * 512;
        glo_pre_end = glo_pre_start + MAX_RLIABLE_TRASACTION*512 -1;

        src = (unsigned long *)UPGRADE_BUFFER_ADDR; //0x50000000
        p = (char *) src;
        max_block_num = 16*1024*2;
        blocks_todo = (RELIABLE_TEST_SIZE == mmc->block_dev.lba) ?
            (mmc->block_dev.lba - RELIABLE_START_OFFSET) : RELIABLE_TEST_SIZE;
        start = RELIABLE_START_OFFSET;


        do
        {
            flush_cache_all();
            cur = (blocks_todo > max_block_num) ? max_block_num : blocks_todo;
            if(mmc->block_dev.block_read(0, start, cur, src) != cur)
                return 0;

            glo_now_index = start * 512;
            //check the value
            for(index=0; index< cur*512; ++index)
            {
                if((glo_now_index<glo_pre_start) || (glo_now_index>glo_pre_end))
                {
                    if(p[index] != 0xab)
                    {
                        printf("static reliable write test fail, startblk %llu index %llu\n", start, index);
                        sprintf(buf, "%d", 0);
			     sprintf(str,"startblk %llu index %llu\n",start,index);
                        setenv("static_reliable_testloop_env", buf);
			     setenv("reliable_test_info_1", str);
                        saveenv();
                        sprintf(buf, "%d", 0);
                        setenv("eMMC_PMReliableWriteTest_enable_env", buf);
                        saveenv();
			     printf("\n glo_now_index=%llu,glo_pre_start=%llu,glo_pre_end=%llu\n",glo_now_index,glo_pre_start,glo_pre_end);
			     sprintf(str,"\n now=%llu,start=%llu,end=%llu\n",glo_now_index,glo_pre_start,glo_pre_end);
                        setenv("reliable_test_info_2", str);
                        saveenv();
				 printf("\nError block info:\n");
			     int block_start=(index/512)*512;
			     int block_byte;
			     for(block_byte=0;block_byte<512;block_byte++)
				 {
				 	printf("%x ",p[block_start++]);
				 	if(block_byte%16==0)
						{
						printf("\n");
						}
				 }
			     printf("\nEnd\n");
                        return 1;
                    }
                }
        //Do not check the previous loop data because static reliable write
        // doesn't protect the current writing data when power-cutting.
        #if 0
        else
        {
            if(p[index] !=0xab &&  p[index] != 0xcd)
            {
                            printf("static reliable write test fail, startblk %d index %d value 0x%X\n", start, index, p[index]);
                            sprintf(buf, "%d", 0);
                            setenv("static_reliable_testloop_env", buf);
                            saveenv();
                                 sprintf(buf, "%d", 0);
                                 setenv("eMMC_PMReliableWriteTest_enable_env", buf);
                                 saveenv();
                            return 1;
            }
        }
        #endif
                ++glo_now_index;
            }
            blocks_todo -= cur;
            start += cur;
        } while (blocks_todo > 0);

        printf("loop %llu check memory success=============================\n", test_loop);
    }


    //save loop count
    ++test_loop;
    if(test_loop > MAX_RLIABLE_TEST_LOOP)
    {
       enable_pm_sleep_flag = 0;
       test_loop = 0;
       sprintf(buf, "%llu", test_loop);
       setenv("static_reliable_testloop_env", buf);
       sprintf(buf, "%d", 1);
       setenv("static_reliable_test_success", buf);
       saveenv();
       sprintf(buf, "%d", 0);
       setenv("eMMC_PMReliableWriteTest_enable_env", buf);
       saveenv();
       return 1;
    }
    else
    {
        sprintf(buf, "%llu", test_loop);
        setenv("static_reliable_testloop_env", buf);
    }

    reliable_test_sleep = rRand(reliable_test_sleep + 133, reliable_test_sleep+333-test_loop);
    reliable_test_sleep  = reliable_test_sleep % MAX_RLIABLE_SLEEP_TIME;

    //save sleep time
    if(reliable_test_sleep < MIN_RELIABLE_SLEEP_TIME)
    {
        sprintf(buf, "%d", reliable_test_sleep + MIN_RELIABLE_SLEEP_TIME - 1); //re-init sleep time
    }
    else
    {
        sprintf(buf, "%d", reliable_test_sleep+1);
    }
    setenv("static_reliable_sleep_env", buf);

    //save blknum now start with
    sprintf(buf, "%llu", startblk);
    setenv("static_reliable_pstart_env", buf);
    saveenv();

    //re-init previous memory range with fixed value
    src = (unsigned long *)UPGRADE_BUFFER_ADDR; //0x50000000
    memset((void *)src, 0xab, MAX_RLIABLE_TRASACTION*512);
    if(mmc->block_dev.block_write(0, previous_startblk, MAX_RLIABLE_TRASACTION, src)!= MAX_RLIABLE_TRASACTION)
    {
        printf("re-init previous memory range with a fixed value failed\n");
        return 1;
    }
    flush_cache_all();

    //ready for test reliable write
    MDrv_WDT_Init((WDT_DbgLv)0); //init watchdog

    memset((void *)src, 0xcd, MAX_RLIABLE_TRASACTION*512);

    enable_pm_sleep_flag = 1;
    printf("after %d ms power off, enable_pm_sleep_flag = %d ============================\n\n", reliable_test_sleep, enable_pm_sleep_flag);

    while(1)
    {
        if(mmc->block_dev.block_write(0, startblk, MAX_RLIABLE_TRASACTION, src) != MAX_RLIABLE_TRASACTION)
        {
            printf("write %d blocks for test failed\n", MAX_RLIABLE_TRASACTION);
            return 1;
        }

	  flush_cache_all();
    }
    enable_pm_sleep_flag = 0;

    //disable
    #if 0
    while(1)
    {
       if(mmc->block_dev.block_write(0, startblk, MAX_RLIABLE_TRASACTION, src) != MAX_RLIABLE_TRASACTION)
       {
           printf("write %d block for test failed\n", MAX_RLIABLE_TRASACTION);
           return 1;
       }
    }
    #endif

    return 0;
}
#endif


int get_mmc_partsize (char *puPartName,unsigned int *u32PartSize)
{
    block_dev_desc_t *mmc_dev;
    struct mmc *mmc = NULL;

    if (curr_device < 0)
    {
        if (get_mmc_num() > 0)
            curr_device = 0;
        else
        {
            puts("No MMC device available\n");
            return 1;
        }
    }

    mmc = find_mmc_device(curr_device);

    if (!mmc) {
        printf("no mmc device at slot %x\n", curr_device);
        return -1;
    }
    if(!mmc->has_init){
        printf("Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }
    mmc_dev = mmc_get_dev(curr_device);
    if (mmc_dev != NULL &&
            mmc_dev->type != DEV_TYPE_UNKNOWN) {
        _get_mmc_partsize(mmc_dev,puPartName,u32PartSize);
        return 0;
    }
    return -1;
}

#endif

