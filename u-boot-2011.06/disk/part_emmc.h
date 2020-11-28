/*
 * See also Linux sources, fs/partitions/mac.h
 *
 * This file describes structures and values related to the standard
 * Apple SCSI disk partitioning scheme. For more information see:
 * http://developer.apple.com/techpubs/mac/Devices/Devices-126.html#MARKER-14-92
 * Refined by rui.wang@mstarsemi.com
 */

#ifndef _DISK_PART_EMMC_H
#define _DISK_PART_EMMC_H

/*      0 ~ 32KB for partition table. 
    32KB ~ 64KB reserved for partition table, but not used
    64KB ~   2MB reserved for emmc driver test
      2MB ~  7MB  reserved for chunk header, pm, uboot and env
      7MB ~          ordinary partition data start
*/

#define EMMC_RESERVED_FOR_MAP 10         
#define EMMC_RESERVED_FOR_MAP_V2 63   //0~32kb for partition table. 32kb~64kb reserved for partition table, but not used
#ifdef CONFIG_DOUBLE_MBOOT
#define EMMC_RESERVED_FOR_MAP_V3 EMMC_RESERVED_FOR_MAP_V2   //0~32kb for partition table. 32kb~64kb reserved for partition table, but not used
#endif
#define EMMC_CHUNK_HEAD_START 4096        // chunk head start addr
#ifdef CONFIG_DOUBLE_MBOOT
#define EMMC_PARTITION_START_V1 12       // ordinary partition data start addr
#define EMMC_PARTITION_START_V2 14336       // ordinary partition data start addr
#define EMMC_PARTITION_START_V3 65536       // ordinary partition data start addr
#else
#define EMMC_PARTITION_START 14336       // ordinary partition data start addr
#endif

#define EMMC_DRIVER_MAGIC   0x1630

/*
 * Driver Descriptor Structure, in block 0.
 * This block is (and shall remain) 512 bytes long.
 * Note that there is an alignment problem for the driver descriptor map!
 */
typedef struct emmc_driver_desc {
        __u16   signature;           /* expected to be EMMC_DRIVER_MAGIC  */
        __u16   blk_size;             /* block size of device */
        __u32   blk_count;           /* number of blocks on device */
        __u16   dev_type;            /* device type */
        __u16   dev_id;                /* device id */
        __u32   data;                   /* reserved */
        __u16   version;               /* version number of partition table */
        __u16   drvr_cnt;             /* number of blocks reserved for partition table */
        __u16   drvr_map[246];    /* driver descriptor map */
} emmc_driver_desc_t;

/*
 * Device Driver Entry
 * (Cannot be included in emmc_driver_desc because of alignment problems)
 */
typedef struct emmc_driver_entry {
        __u32   block;          /* block number of starting block */
        __u16   size;            /* size of driver, in 512 byte blocks */
        __u16   type;           /* OS Type */
} emmc_driver_entry_t;


#define EMMC_PARTITION_MAGIC    0x5840
#define EMMC_PARTITIONTABLE_VERSION2 0x2000
#ifdef CONFIG_DOUBLE_MBOOT
#define EMMC_PARTITIONTABLE_VERSION3 0x4000
#endif

/* type field value for A/UX or other Unix partitions */
#define APPLE_AUX_TYPE  "Apple_UNIX_SVR2"

/*
 * Each Partition Map entry (in blocks 1 ... N) has this format:
 */
typedef struct EMMC_partition {
        __u16   signature;          /* expected to be EMMC_PARTITION_MAGIC   */
        __u16   sig_pad;            /* reserved */
        __u32   map_count;       /* blocks in partition map   */
        __u32   start_block;       /* abs. starting block # of partition    */
        __u32   block_count;      /* number of blocks in partition  */
        uchar    name[32];          /* partition name   */
        uchar    type[32];           /* string type description */
        __u32   data_start;        /* rel block # of first data block   */
        __u32   data_count;       /* number of data blocks  */
        __u32   status;               /* partition status bits  */
        __u32   boot_start;         /* first block of boot code */
        __u32   boot_size;          /* size of boot code, in bytes  */
        __u32   boot_load;          /* boot code load address   */
        __u32   boot_load2;        /* reserved  */
        __u32   boot_entry;        /* boot code entry point */
        __u32   boot_entry2;      /* reserved   */
        __u32   boot_cksum;      /* boot code checksum  */
        uchar    processor[16];    /* Type of Processor */
        __u16   part_pad[188];   /* reserved    */
#ifdef CONFIG_ISO_PARTITION
	uchar   iso_dummy[2048];/* Reservere enough room for an ISO partition block to fit */
#endif
} emmc_partition_t;

#define EMMC_STATUS_BOOTABLE    8   /* partition is bootable */

#endif  /* _DISK_PART_EMMC_H */
