/*
 * See also Linux sources, fs/partitions/mac.h
 *
 * This file describes structures and values related to the standard
 * Apple SCSI disk partitioning scheme. For more information see:
 * http://developer.apple.com/techpubs/mac/Devices/Devices-126.html#MARKER-14-92
 * Refined by rui.wang@mstarsemi.com
 */
 
#include <common.h>
#include <command.h>
#include <ide.h>
#include "part_emmc.h"

#if defined(CONFIG_CMD_IDE) || \
    defined(CONFIG_CMD_MG_DISK) || \
    defined(CONFIG_CMD_SCSI) || \
    defined(CONFIG_CMD_SATA) || \
    defined(CONFIG_CMD_USB) || \
    defined(CONFIG_MMC) || \
    defined(CONFIG_SD) ||\
    defined(CONFIG_SYSTEMACE)

/* stdlib.h causes some compatibility problems; should fixe these! -- wd */
#ifndef __ldiv_t_defined
typedef struct {
        long int quot;      /* Quotient	*/
        long int rem;       /* Remainder	*/
} ldiv_t;
extern ldiv_t ldiv (long int __numer, long int __denom);
# define __ldiv_t_defined   1
#endif

static int part_emmc_read_ddb (block_dev_desc_t *dev_desc, emmc_driver_desc_t *ddb_p);
static int part_emmc_read_pdb (block_dev_desc_t *dev_desc, int part, emmc_partition_t *pdb_p);

static int part_emmc_write_ddb (block_dev_desc_t *dev_desc, emmc_driver_desc_t *ddb_p);
#ifdef CONFIG_DOUBLE_MBOOT
static int part_emmc_write_pdb (block_dev_desc_t *dev_desc, emmc_partition_t *pdb_p,unsigned short version);
#else
static int part_emmc_write_pdb (block_dev_desc_t *dev_desc, emmc_partition_t *pdb_p);
#endif

static int check_partition_table_version(block_dev_desc_t *dev_desc, emmc_driver_desc_t *ddb_p);

__u16 g_emmc_reserved_for_map = EMMC_RESERVED_FOR_MAP_V2;
__u8 g_disable_nopdb_warning = 0;

/*
 * Test for a valid EMMC partition
 */
int test_part_emmc (block_dev_desc_t *dev_desc)
{
        emmc_driver_desc_t  ddesc;
        emmc_partition_t    mpart;
        ulong i, n;

        if (check_partition_table_version(dev_desc, &ddesc) < 0) {
                return (-1);
        }
            
        n = g_emmc_reserved_for_map;
        
        for (i=1; i<=n; ++i) {
            if ((dev_desc->block_read(dev_desc->dev, i, 1, (ulong *)&mpart) != 1) ||
                (mpart.signature != EMMC_PARTITION_MAGIC) ) {
                    return (-1);
            }
            /* update partition count */
//            n = mpart.map_count;
        }
        return (0);
}

unsigned int get_emmc_used_blockcount(block_dev_desc_t *dev_desc)
{
    int i;
    emmc_partition_t    mpart;
    emmc_driver_desc_t  ddesc;
    unsigned int u32UsedBlockCount = 0;
    if (check_partition_table_version(dev_desc, &ddesc) < 0) 
    {
            return 0;
    }

    for(i=1;i<= g_emmc_reserved_for_map;i++)
    {
        if(part_emmc_read_pdb(dev_desc, i, &mpart) == 0)
        {
            u32UsedBlockCount += mpart.block_count ; /* assumes blk_size == 512 */
        }
        else
        {
            break;
        }
    }
    return u32UsedBlockCount;  
}

void print_part_emmc (block_dev_desc_t *dev_desc)
{
        ulong i, n;
        emmc_driver_desc_t  ddesc;
        emmc_partition_t    mpart;

#if 0        
        ldiv_t mb, gb;

        n  = ddesc.blk_count;

        mb = ldiv(n, ((1024 * 1024) / ddesc.blk_size)); /* MB */
        /* round to 1 digit */
        mb.rem *= 10 * ddesc.blk_size;
        mb.rem += 512 * 1024;
        mb.rem /= 1024 * 1024;

        gb = ldiv(10 * mb.quot + mb.rem, 10240);
        gb.rem += 512;
        gb.rem /= 1024;


        printf ( "Block Size=%d, Number of Blocks=%d, "
            "Total Capacity: %ld.%ld MB = %ld.%ld GB\n"
            "DeviceType=0x%x, DeviceId=0x%x\n\n" 
            "   #:                 type name"
            "                   length   base       (size)\n",
            ddesc.blk_size,
            ddesc.blk_count,
            mb.quot, mb.rem, gb.quot, gb.rem,
            ddesc.dev_type, ddesc.dev_id
            );
#endif
         if (check_partition_table_version(dev_desc, &ddesc) < 0) {
                return;
        }
         
        printf ("   #:                 type name"
            "                   length   base       (size)\n");
        
        n = g_emmc_reserved_for_map; 
        for (i=1; i<=n; ++i) {
                ulong bytes=0, bytes_tail=0;
                char c;

                if (dev_desc->block_read (dev_desc->dev, i, 1, (ulong *)&mpart) != 1) {
                    printf ("** Can't read Partition Map on %d:%ld **\n",
                            dev_desc->dev, i);
                    return;
        }

        if (mpart.signature != EMMC_PARTITION_MAGIC) {
                printf("\n");
                return;
        }

                printf ("%4ld: ", i);
        /* update partition count */

        c      = 'k';
        bytes  = mpart.block_count;      
        bytes /= (1024 / 512);  /* kB; assumes blk_size == 512 */
        if (bytes >= 1024) {
                bytes_tail = (bytes & 1023) * 1000 /1024;
                bytes >>= 10;
                c = 'M';
        }    
        if (bytes >= 1024) {
                bytes_tail = (bytes & 1023) * 1000 /1024;
                bytes >>= 10;
                c = 'G';
        }
        printf("%20.32s %-18.32s %10u @ %-10u (%ld.%03ld%c)\n",
                    mpart.type,
                    mpart.name,
                    mpart.block_count,
                    mpart.start_block,
                    bytes, bytes_tail, c
                );
        }

        return;
}


/*
 * Read Device Descriptor Block
 */
static int part_emmc_read_ddb (block_dev_desc_t *dev_desc, emmc_driver_desc_t *ddb_p)
{
        if (dev_desc->block_read(dev_desc->dev, 0, 1, (ulong *)ddb_p) != 1) {
                printf ("** Can't read Driver Desriptor Block **\n");
                return (-1);
        }

        if (ddb_p->signature != EMMC_DRIVER_MAGIC) {
#if 0
            printf ("** Bad Signature: expected 0x%04x, got 0x%04x\n",
                        AC_DRIVER_MAGIC, ddb_p->signature);
#endif

            return (-1);
        }

        return (0);
}

/*
 * Read Partition Descriptor Block
 */
static int part_emmc_read_pdb (block_dev_desc_t *dev_desc, int part, emmc_partition_t *pdb_p)
{
        int n = 1;

        for (;;) {
                /*
                * We must always read the descritpor block for
                * partition 1 first since this is the only way to
                * know how many partitions we have.
                */
                if (dev_desc->block_read (dev_desc->dev, n, 1, (ulong *)pdb_p) != 1) {
                    printf ("** Can't read Partition Map on %d:%d **\n",
                                dev_desc->dev, n);
                    return (-1);
                }

                if (pdb_p->signature != EMMC_PARTITION_MAGIC) {
                    if(!g_disable_nopdb_warning)
                        printf ("** Bad Signature on %d:%d: "
                                    "expected 0x%04x, got 0x%04x\n",
                                    dev_desc->dev, n, EMMC_PARTITION_MAGIC, pdb_p->signature);
                    return (-1);
                }

                if (n == part)
                    return (0);

                if ((part < 1) || (part > g_emmc_reserved_for_map)) {
                    printf ("** Invalid partition %d:%d [%d:1...%d:%d only]\n",
                                dev_desc->dev, part,
                                dev_desc->dev,
                                dev_desc->dev, pdb_p->map_count);
                    return (-1);
                }

                /* update partition count */
                n = part;
        }

        /* NOTREACHED */
}

static int part_emmc_write_ddb (block_dev_desc_t *dev_desc, emmc_driver_desc_t *ddb_p)
{

        if(ddb_p->signature != EMMC_DRIVER_MAGIC){
                printf ("** Bad Signature: expected 0x%04x, try to write 0x%04x **\n",
                        EMMC_DRIVER_MAGIC, ddb_p->signature);
                return (-1);
        }

        if(dev_desc->block_write(dev_desc->dev, 0, 1, (ulong *)ddb_p) != 1){
                printf("** Can't write Driver Desiptor Block **\n");
                return (-1);
        }

        return (0);
}

#ifdef CONFIG_DOUBLE_MBOOT
static int part_emmc_write_pdb (block_dev_desc_t *dev_desc, emmc_partition_t *pdb_p,unsigned short version)
{
        int n = 1;
        emmc_partition_t exist_pdb;
        ulong special_start, start_block,usr_partition_start;

	if(version==EMMC_PARTITIONTABLE_VERSION2)
	{
		start_block=EMMC_PARTITION_START_V2;
		usr_partition_start=EMMC_PARTITION_START_V2;
	}
	else if(version==EMMC_PARTITIONTABLE_VERSION3)
	{
		start_block=EMMC_PARTITION_START_V3;
		usr_partition_start=EMMC_PARTITION_START_V3;
	}
	else
	{
		start_block=EMMC_PARTITION_START_V1;
		usr_partition_start=EMMC_PARTITION_START_V1;
	}
  
        if(pdb_p->signature != EMMC_PARTITION_MAGIC){
                printf ("** Bad Signature: expected 0x%04x, try to write 0x%04x **\n",
                        EMMC_PARTITION_MAGIC, pdb_p->signature);
                return (-1);
        }

        special_start = pdb_p->start_block;
            
        for (;;) {
                /*
                * We must always read the descritpor block for
                * partition 1 first since this is the only way to
                * know how many partitions we have.
                */
                if (dev_desc->block_read (dev_desc->dev, n, 1, &exist_pdb) != 1) {
                        printf ("** Can't read Partition Map on %d:%d **\n",
                                dev_desc->dev, n);
                        return (-1);
                }

                if(exist_pdb.signature == EMMC_PARTITION_MAGIC){
                        if(!strcmp((const char *)pdb_p->name, (const char *)exist_pdb.name)){
                            printf("** Try to change a exist partition %s **\n", exist_pdb.name);
                            if(pdb_p->block_count > exist_pdb.block_count){
                                printf("** The new size of the partition is too big!\n");
                                return (-1);
                            }

                            if(special_start != 0)
                                pdb_p->start_block = special_start;
                            else
                                pdb_p->start_block = exist_pdb.start_block;
                           
                            if(pdb_p->start_block + pdb_p->block_count > dev_desc->lba){
                                printf("** Partition exceed emmc capacity**\n");
                                return (-1);
                            }                         
                                
                            if(dev_desc->block_write(dev_desc->dev, n, 1, (ulong *)pdb_p) != 1){
                                printf("** Can't write Driver Desiptor Block **\n");
                                return (-1);
                            }                         
                            return (0);
                        }

                        if(exist_pdb.start_block + exist_pdb.block_count > usr_partition_start)
                            /* skip UBOOT partition */
                            start_block += exist_pdb.block_count;
                        
                        ++n;
                        if(n > g_emmc_reserved_for_map){
                            printf("** Exceed the max number of partition, STOP!**\n");
                            return (-1);
                        }
                }
                else{
                        if(special_start != 0)
                            pdb_p->start_block = special_start;
                        else
                            pdb_p->start_block = start_block;
                        
                        if(pdb_p->start_block + pdb_p->block_count > dev_desc->lba){
                            printf("** Partition exceed emmc capacity**\n");
                            return (-1);
                        }
                      
                        if(dev_desc->block_write(dev_desc->dev, n, 1, (ulong *)pdb_p) != 1){
                            printf("** Can't write Driver Desiptor Block **\n");
                            return (-1);
                        }
                        return (0);
                }
                
        }

        /* NOTREACHED */
}
#else
static int part_emmc_write_pdb (block_dev_desc_t *dev_desc, emmc_partition_t *pdb_p)
{
        int n = 1;
        emmc_partition_t exist_pdb;
        ulong special_start, start_block = EMMC_PARTITION_START;
        
        if(pdb_p->signature != EMMC_PARTITION_MAGIC){
                printf ("** Bad Signature: expected 0x%04x, try to write 0x%04x **\n",
                        EMMC_PARTITION_MAGIC, pdb_p->signature);
                return (-1);
        }

        special_start = pdb_p->start_block;
            
        for (;;) {
                /*
                * We must always read the descritpor block for
                * partition 1 first since this is the only way to
                * know how many partitions we have.
                */
                if (dev_desc->block_read (dev_desc->dev, n, 1, &exist_pdb) != 1) {
                        printf ("** Can't read Partition Map on %d:%d **\n",
                                dev_desc->dev, n);
                        return (-1);
                }

                if(exist_pdb.signature == EMMC_PARTITION_MAGIC){
                        if(!strcmp((const char *)pdb_p->name, (const char *)exist_pdb.name)){
                            printf("** Try to change a exist partition %s **\n", exist_pdb.name);
                            if(pdb_p->block_count > exist_pdb.block_count){
                                printf("** The new size of the partition is too big!\n");
                                return (-1);
                            }

                            if(special_start != 0)
                                pdb_p->start_block = special_start;
                            else
                                pdb_p->start_block = exist_pdb.start_block;
                           
                            if(pdb_p->start_block + pdb_p->block_count > dev_desc->lba){
                                printf("** Partition exceed emmc capacity**\n");
                                return (-1);
                            }                         
                                
                            if(dev_desc->block_write(dev_desc->dev, n, 1, (ulong *)pdb_p) != 1){
                                printf("** Can't write Driver Desiptor Block **\n");
                                return (-1);
                            }                         
                            return (0);
                        }

                        if(exist_pdb.start_block + exist_pdb.block_count > EMMC_PARTITION_START)
                            /* skip UBOOT partition */
                            start_block += exist_pdb.block_count;
                        
                        ++n;
                        if(n > g_emmc_reserved_for_map){
                            printf("** Exceed the max number of partition, STOP!**\n");
                            return (-1);
                        }
                }
                else{
                        if(special_start != 0)
                            pdb_p->start_block = special_start;
                        else
                            pdb_p->start_block = start_block;
                        
                        if(pdb_p->start_block + pdb_p->block_count > dev_desc->lba){
                            printf("** Partition exceed emmc capacity**\n");
                            return (-1);
                        }
                      
                        if(dev_desc->block_write(dev_desc->dev, n, 1, (ulong *)pdb_p) != 1){
                            printf("** Can't write Driver Desiptor Block **\n");
                            return (-1);
                        }
                        return (0);
                }
                
        }

        /* NOTREACHED */
}
#endif

static int check_partition_table_version(block_dev_desc_t *dev_desc, emmc_driver_desc_t *ddb_p)
{        
        if (part_emmc_read_ddb (dev_desc, ddb_p) < 0) {
                return (-1);
        }

		#ifdef CONFIG_DOUBLE_MBOOT
        if (ddb_p->version == EMMC_PARTITIONTABLE_VERSION2 || ddb_p->version == EMMC_PARTITIONTABLE_VERSION3){
		#else
        if (ddb_p->version == EMMC_PARTITIONTABLE_VERSION2){
		#endif
            g_emmc_reserved_for_map = ddb_p->drvr_cnt;
            return 1;
        }
        else{            
            g_emmc_reserved_for_map = EMMC_RESERVED_FOR_MAP;
            return 0;
        }
}


int get_partition_info_emmc (block_dev_desc_t *dev_desc, int part, disk_partition_t *info)
{
        emmc_driver_desc_t  ddesc;
        emmc_partition_t    mpart;

        if (check_partition_table_version(dev_desc, &ddesc) < 0) {
                return (-1);
        }
        
        if ((part > g_emmc_reserved_for_map) || (part < 1)){
                return (-1);
        }

        info->blksz = ddesc.blk_size;

        if (part_emmc_read_pdb (dev_desc, part, &mpart)) {
                return (-1);
        }

        info->start = mpart.start_block;
        info->size  = mpart.block_count;
        info->blksz  =   512;
        memcpy (info->type, mpart.type, sizeof(info->type));
        memcpy (info->name, mpart.name, sizeof(info->name));

        return (0);
}

int Search_Mboot_partition_emmc (block_dev_desc_t *dev_desc)
{
        int i;
        emmc_partition_t    mpart;
		
        g_disable_nopdb_warning = 1;
        for(i=1;i<= EMMC_RESERVED_FOR_MAP_V2;i++)
        {
            if(part_emmc_read_pdb(dev_desc, i, &mpart) == 0)
            {
                if(strcmp("MBOOT", (const char *)mpart.name)==0)
                {
                    printf("** Find MBOOT **\n");
                    g_disable_nopdb_warning = 0;
                    return i;
                }
            }
        }
        g_disable_nopdb_warning = 0;
        return 0;
}

#ifdef CONFIG_DOUBLE_MBOOT
int Search_Mbootbak_partition_emmc (block_dev_desc_t *dev_desc)
{
        int i;
        emmc_partition_t    mpart;
		
        g_disable_nopdb_warning = 1;
        for(i=1;i<= EMMC_RESERVED_FOR_MAP_V2;i++)
        {
            if(part_emmc_read_pdb(dev_desc, i, &mpart) == 0)
            {
                if(strcmp("MBOOTBAK", (const char *)mpart.name)==0)
                {
                    printf("** Find MBOOTBAK **\n");
                    g_disable_nopdb_warning = 0;
                    return i;
                }
            }
        }
        g_disable_nopdb_warning = 0;
        return 0;
}
#endif
int Search_Mpool_partition_emmc (block_dev_desc_t *dev_desc)
{
        int i;
        emmc_partition_t    mpart;
    
        g_disable_nopdb_warning = 1;
        for(i=1;i<= EMMC_RESERVED_FOR_MAP_V2;i++)
        {
            if(part_emmc_read_pdb(dev_desc, i, &mpart) == 0)
            {
                if(strcmp("MPOOL", (const char *)mpart.name)==0)
                {
                    printf("** Find MPOOL **\n");
                    g_disable_nopdb_warning = 0;
                    return i;
                }
            }
        }
        g_disable_nopdb_warning = 0;
        return 0;
}


#ifdef CONFIG_DOUBLE_MBOOT
int add_new_emmc_partition(block_dev_desc_t *dev_desc, disk_partition_t *info)
{
        int ret;
        int flag = 0;
        emmc_driver_desc_t ddb, ddb_base;
        emmc_partition_t pdb_base;        
        
        ddb_base.signature = EMMC_DRIVER_MAGIC;
        ddb_base.version = EMMC_PARTITIONTABLE_VERSION3;
        ddb_base.drvr_cnt = EMMC_RESERVED_FOR_MAP_V3;
        pdb_base.signature = EMMC_PARTITION_MAGIC;

	  flag = part_emmc_read_ddb(dev_desc, &ddb);	
	  
        if(flag){
            printf("Need write new driver description table!\n");
            ret = part_emmc_write_ddb(dev_desc, &ddb_base);
            if(ret){
                printf("Error during write new driver description table!\n");
                return ret;
            }
            g_emmc_reserved_for_map= ddb_base.drvr_cnt;
        }else if(ddb.version == EMMC_PARTITIONTABLE_VERSION2 ||ddb.version == EMMC_PARTITIONTABLE_VERSION3)
                g_emmc_reserved_for_map = ddb_base.drvr_cnt;
            else
                g_emmc_reserved_for_map = EMMC_RESERVED_FOR_MAP;

        strcpy((char *)pdb_base.name, (const char *)info->name);
        pdb_base.block_count = info->size;
        pdb_base.start_block = info->start;
        
        ret = part_emmc_write_pdb(dev_desc, &pdb_base,flag==0?ddb.version:ddb_base.version);
        if(ret){
            printf("Error during write new partition description table!\n");
            return ret;
        }

        return 0;        
}
#else
int add_new_emmc_partition(block_dev_desc_t *dev_desc, disk_partition_t *info)
{
        int ret;
        emmc_driver_desc_t ddb, ddb_base;
        emmc_partition_t pdb_base;        
        
        ddb_base.signature = EMMC_DRIVER_MAGIC;
        ddb_base.version = EMMC_PARTITIONTABLE_VERSION2;
        ddb_base.drvr_cnt = EMMC_RESERVED_FOR_MAP_V2;
        pdb_base.signature = EMMC_PARTITION_MAGIC;
        
        if(part_emmc_read_ddb(dev_desc, &ddb)){
            printf("Need write new driver description table!\n");
            ret = part_emmc_write_ddb(dev_desc, &ddb_base);
            if(ret){
                printf("Error during write new driver description table!\n");
                return ret;
            }
            g_emmc_reserved_for_map= ddb_base.drvr_cnt;
        }else if(ddb.version == EMMC_PARTITIONTABLE_VERSION2)
                g_emmc_reserved_for_map = ddb_base.drvr_cnt;
            else
                g_emmc_reserved_for_map = EMMC_RESERVED_FOR_MAP;

        strcpy((char *)pdb_base.name, (const char *)info->name);
        pdb_base.block_count = info->size;
        pdb_base.start_block = info->start;
        
        ret = part_emmc_write_pdb(dev_desc, &pdb_base);
        if(ret){
            printf("Error during write new partition description table!\n");
            return ret;
        }

        return 0;        
}
#endif

int remove_emmc_partition(block_dev_desc_t *dev_desc, disk_partition_t *info)
{
        int n = 0;
        emmc_driver_desc_t ddb;
        emmc_partition_t exist_pdb, pdb;        

        pdb.signature = 0;

        if (check_partition_table_version(dev_desc, &ddb) < 0) {
            printf("Haven't driver description table!\n");
            return (-1);
        }
        
        for (;;) {
                /*
                * We must always read the descritpor block for
                * partition 1 first since this is the only way to
                * know how many partitions we have.
                */
                if(n > g_emmc_reserved_for_map){
                        printf("** Cannot remove the partition, not found **\n");
                        return (-1);
                }
                if (dev_desc->block_read (dev_desc->dev, n, 1, (ulong *)&exist_pdb) != 1) {
                        printf ("** Can't read Partition Map on %d:%d **\n",
                                dev_desc->dev, n);
                        return (-1);
                }

                if(exist_pdb.signature == EMMC_PARTITION_MAGIC){
                        if(!strcmp((const char *)info->name, (const char *)exist_pdb.name)){
                            if(dev_desc->block_write(dev_desc->dev, n, 1, (ulong *)&pdb) != 1){
                                printf("** Can't remove the partition %s **\n", exist_pdb.name);
                                return (-1);
                            }                         
                            return (0);
                        }
                }
                ++n;                                
        }
        
        return (-1);        
}

int _get_mmc_partsize (block_dev_desc_t *dev_desc,char *puPartName,unsigned int *u32PartSize)
{
    int i;
    emmc_partition_t    mpart;
    emmc_driver_desc_t  ddesc;
    
    if (check_partition_table_version(dev_desc, &ddesc) < 0) {
            return (-1);
    }
    
    for(i=1;i<= g_emmc_reserved_for_map;i++)
    {
        if(part_emmc_read_pdb(dev_desc, i, &mpart) == 0)
        {
            if(strcmp(puPartName, (const char *)mpart.name)==0)
            {
                *u32PartSize = mpart.block_count * 512; /* assumes blk_size == 512 */
                printf("%s size : 0x%x\n",puPartName,*u32PartSize);
                break;
            }
        }
    }

    return 0;
}

#endif
