/*
 * (C) Copyright 2011 - 2012 Samsung Electronics
 * EXT4 filesystem implementation in Uboot by
 * Uma Shankar <uma.shankar@samsung.com>
 * Manjunatha C Achar <a.manjunatha@samsung.com>
 *
 * Journal data structures and headers for Journaling feature of ext4
 * have been referred from JBD2 (Journaling Block device 2)
 * implementation in Linux Kernel.
 * Written by Stephen C. Tweedie <sct@redhat.com>
 *
 * Copyright 1998-2000 Red Hat, Inc --- All Rights Reserved
 * This file is part of the Linux kernel and is made available under
 * the terms of the GNU General Public License, version 2, or at your
 * option, any later version, incorporated herein by reference.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <common.h>
#include <ext4fs.h>
#include <malloc.h>
#include <ext_common.h>
#include "ext4_common.h"
#include <linux/crc32.h>

static struct revoke_blk_list *revk_blk_list;
static struct revoke_blk_list *prev_node;
static int first_node = TRUE;

int gindex;
int gd_index;
int jrnl_blk_idx;
unsigned int end_transaction;
struct journal_log *journal_ptr[MAX_JOURNAL_ENTRIES];
struct dirty_blocks *dirty_block_ptr[MAX_JOURNAL_ENTRIES];

/* Make sure we wrap around the log correctly! */
#define wrap(journal, var)						\
do {									\
	if ((var) >= be32_to_cpu((journal)->s_maxlen))					\
		(var) -= (be32_to_cpu((journal)->s_maxlen) - be32_to_cpu((journal)->s_first));	\
} while (0)

static inline int tid_geq(unsigned int x, unsigned int y)
{
	int difference = (x - y);
	return (difference >= 0);
}

/*
 * Count the number of in-use tags in a journal descriptor block.
 */

static int count_tags(struct ext_filesystem *fs, char *jrnl_buf)
{
    char *			tagp;
    struct ext3_journal_block_tag *	tag;
    int			nr = 0, size = fs->blksz;
    int			tag_bytes;

    tag_bytes = sizeof(struct ext3_journal_block_tag);

    tagp = &jrnl_buf[sizeof(struct journal_header_t)];

    while ((tagp - jrnl_buf + tag_bytes) <= size) {
        tag = (struct ext3_journal_block_tag *) tagp;
        debug("nr=%d, tag_bytes=%d\n",nr,tag_bytes);
        nr++;
        tagp += tag_bytes;
        if (!(tag->flags & cpu_to_be32(EXT3_JOURNAL_FLAG_SAME_UUID)))
            tagp += 16;

            if (tag->flags & cpu_to_be32(EXT3_JOURNAL_FLAG_LAST_TAG))
                break;
    }
    
    return nr;
}

/*
 * calc_chksums calculates the checksums for the blocks described in the
 * descriptor block.
 */
static int calc_chksums(struct journal_superblock_t *journal,
                    char *jrnl_buf, int next_log_block, unsigned int *crc32_sum)
{
    int i, num_blks, res;
    unsigned int io_block, blknr;
    struct ext2_inode inode_journal;
    struct ext_filesystem *fs = get_fs();
    char *temp_buff = zalloc(fs->blksz);
    if (!temp_buff)
        return -ENOMEM;
    
    num_blks = count_tags(fs, jrnl_buf);
    
    /* Calculate checksum of the descriptor block. */
    *crc32_sum = crc32_be(*crc32_sum, (void *)jrnl_buf, fs->blksz);
        
    ext4fs_read_inode(ext4fs_root, EXT2_JOURNAL_INO,
              (struct ext2_inode *)&inode_journal);

    for (i = 0; i < num_blks; i++) {
        io_block = next_log_block++;
        wrap(journal, next_log_block);
        blknr = read_allocated_block((struct ext2_inode *)
                            &inode_journal, io_block);
        res = ext4fs_devread(blknr * fs->sect_perblk, 0, fs->blksz, temp_buff);
        if (!res) {
            printf("JBD: IO error %d recovering block "
                    "%u in log\n", res, io_block);
            free(temp_buff);
            return 1;
        } else {
            debug("###crc32_sum=%x###\n", *crc32_sum);
            *crc32_sum = crc32_be(*crc32_sum, (void *)temp_buff, fs->blksz);
		}
    }
    
    free(temp_buff);
    return 0;
}

int ext4fs_init_journal(void)
{
    int i;
    char *temp = NULL;
    struct ext_filesystem *fs = get_fs();

    /* init globals */
    revk_blk_list = NULL;
    prev_node = NULL;
    gindex = 0;
    gd_index = 0;
    jrnl_blk_idx = 1;
    end_transaction = 0;

    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        journal_ptr[i] = zalloc(sizeof(struct journal_log));
        if (!journal_ptr[i])
            goto fail;
        dirty_block_ptr[i] = zalloc(sizeof(struct dirty_blocks));
        if (!dirty_block_ptr[i])
            goto fail;
        journal_ptr[i]->buf = NULL;
        journal_ptr[i]->blknr = -1;

        dirty_block_ptr[i]->buf = NULL;
        dirty_block_ptr[i]->blknr = -1;
    }

    if (fs->blksz == 4096) {
        temp = zalloc(fs->blksz);
        if (!temp)
            goto fail;
        journal_ptr[gindex]->buf = zalloc(fs->blksz);
        if (!journal_ptr[gindex]->buf)
            goto fail;
        
        ext4fs_devread(0, 0, fs->blksz, temp);
        memcpy(temp + SUPERBLOCK_SIZE, fs->sb, SUPERBLOCK_SIZE);
        memcpy(journal_ptr[gindex]->buf, temp, fs->blksz);
        journal_ptr[gindex++]->blknr = 0;
        free(temp);
    } else {
        journal_ptr[gindex]->buf = zalloc(fs->blksz);
        if (!journal_ptr[gindex]->buf)
            goto fail;
        memcpy(journal_ptr[gindex]->buf, fs->sb, SUPERBLOCK_SIZE);
        journal_ptr[gindex++]->blknr = 1;
    }

    /* Check the file system state using journal super block */
    if (ext4fs_check_journal_state(SCAN))
        goto fail;
    /* Check the file system state using journal super block */
    if (ext4fs_check_journal_state(RECOVER))
        goto fail;

    return 0;
 fail:
    return -1;
}

void ext4fs_dump_metadata(void)
{
    struct ext_filesystem *fs = get_fs();
    int i;
    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (dirty_block_ptr[i]->blknr == -1)
            break;
        put_ext4((uint64_t) (dirty_block_ptr[i]->blknr * fs->blksz),
             dirty_block_ptr[i]->buf, (uint32_t) fs->blksz);
    }
}

void ext4fs_free_journal(void)
{
    int i;
    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (dirty_block_ptr[i]->blknr == -1)
            break;
        if (dirty_block_ptr[i]->buf)
            free(dirty_block_ptr[i]->buf);
    }

    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (journal_ptr[i]->blknr == -1)
            break;
        if (journal_ptr[i]->buf)
            free(journal_ptr[i]->buf);
    }

    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (journal_ptr[i])
            free(journal_ptr[i]);
        if (dirty_block_ptr[i])
            free(dirty_block_ptr[i]);
    }
    gindex = 0;
    gd_index = 0;
    jrnl_blk_idx = 1;
    end_transaction = 0;
}

int ext4fs_log_gdt(char *gd_table)
{
    struct ext_filesystem *fs = get_fs();
    short i;
    long int var = fs->gdtable_blkno;
    for (i = 0; i < fs->no_blk_pergdt; i++) {
        journal_ptr[gindex]->buf = zalloc(fs->blksz);
        if (!journal_ptr[gindex]->buf)
            return -ENOMEM;
        memcpy(journal_ptr[gindex]->buf, gd_table, fs->blksz);
        gd_table += fs->blksz;
        journal_ptr[gindex++]->blknr = var++;
    }

    return 0;
}

/*
 * This function stores the backup copy of meta data in RAM
 * journal_buffer -- Buffer containing meta data
 * blknr -- Block number on disk of the meta data buffer
 */
int ext4fs_log_journal(char *journal_buffer, long int blknr)
{
    struct ext_filesystem *fs = get_fs();
    short i;

    if (!journal_buffer) {
        printf("Invalid input arguments %s\n", __func__);
        return -EINVAL;
    }

    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (journal_ptr[i]->blknr == -1)
            break;
        if (journal_ptr[i]->blknr == blknr)
            return 0;
    }

    journal_ptr[gindex]->buf = zalloc(fs->blksz);
    if (!journal_ptr[gindex]->buf)
        return -ENOMEM;

    memcpy(journal_ptr[gindex]->buf, journal_buffer, fs->blksz);
    journal_ptr[gindex++]->blknr = blknr;

    return 0;
}

/*
 * This function stores the modified meta data in RAM
 * metadata_buffer -- Buffer containing meta data
 * blknr -- Block number on disk of the meta data buffer
 */
int ext4fs_put_metadata(char *metadata_buffer, long int blknr)
{
    struct ext_filesystem *fs = get_fs();
    if (!metadata_buffer) {
        printf("Invalid input arguments %s\n", __func__);
        return -EINVAL;
    }
    dirty_block_ptr[gd_index]->buf = zalloc(fs->blksz);
    if (!dirty_block_ptr[gd_index]->buf)
        return -ENOMEM;
    memcpy(dirty_block_ptr[gd_index]->buf, metadata_buffer, fs->blksz);
    dirty_block_ptr[gd_index++]->blknr = blknr;

    return 0;
}

void print_revoke_blks(char *revk_blk)
{
    int offset;
    int max;
    long int blocknr;
    struct journal_revoke_header_t *header;

    if (revk_blk == NULL)
        return;

    header = (struct journal_revoke_header_t *)revk_blk;
    offset = sizeof(struct journal_revoke_header_t);
    max = be32_to_cpu(header->r_count);
    printf("total bytes %d\n", max);

    while (offset < max) {
        blocknr = be32_to_cpu(*((long int *)(revk_blk + offset)));
        printf("revoke blknr is %ld\n", blocknr);
        offset += 4;
    }
}

static struct revoke_blk_list *_get_node(void)
{
    struct revoke_blk_list *tmp_node;
    tmp_node = zalloc(sizeof(struct revoke_blk_list));
    if (tmp_node == NULL)
        return NULL;
    tmp_node->content = NULL;
    tmp_node->next = NULL;

    return tmp_node;
}

void ext4fs_push_revoke_blk(char *buffer)
{
    struct revoke_blk_list *node = NULL;
    struct ext_filesystem *fs = get_fs();
    if (buffer == NULL) {
        printf("buffer ptr is NULL\n");
        return;
    }
    node = _get_node();
    if (!node) {
        printf("_get_node: malloc failed\n");
        return;
    }

    node->content = zalloc(fs->blksz);
    if (node->content == NULL)
        return;
    memcpy(node->content, buffer, fs->blksz);

    if (first_node == TRUE) {
        revk_blk_list = node;
        prev_node = node;
        first_node = FALSE;
    } else {
        prev_node->next = node;
        prev_node = node;
    }
}

void ext4fs_free_revoke_blks(void)
{
    struct revoke_blk_list *tmp_node = revk_blk_list;
    struct revoke_blk_list *next_node = NULL;

    while (tmp_node != NULL) {
        if (tmp_node->content)
            free(tmp_node->content);
        tmp_node = tmp_node->next;
    }

    tmp_node = revk_blk_list;
    while (tmp_node != NULL) {
        next_node = tmp_node->next;
        free(tmp_node);
        tmp_node = next_node;
    }

    revk_blk_list = NULL;
    prev_node = NULL;
    first_node = TRUE;
}

int check_blknr_for_revoke(long int blknr, int sequence_no)
{
    struct journal_revoke_header_t *header;
    int offset;
    int max;
    long int blocknr;
    char *revk_blk;
    struct revoke_blk_list *tmp_revk_node = revk_blk_list;
    while (tmp_revk_node != NULL) {
        revk_blk = tmp_revk_node->content;

        header = (struct journal_revoke_header_t *)revk_blk;
        if (sequence_no <= be32_to_cpu(header->r_header.h_sequence)) {
            offset = sizeof(struct journal_revoke_header_t);
            max = be32_to_cpu(header->r_count);

            while (offset < max) {
                blocknr = be32_to_cpu(*((long int *)
                            (revk_blk + offset)));
                if (blocknr == blknr)
                    goto found;
                offset += 4;
            }
        }
        tmp_revk_node = tmp_revk_node->next;
    }

    return -1;

 found:
    return 0;
}

/*
 * This function parses the journal blocks and replays the
 * suceessful transactions. A transaction is successfull
 * if commit block is found for a descriptor block
 * The tags in descriptor block contain the disk block
 * numbers of the metadata  to be replayed
 */
int recover_transaction(struct journal_superblock_t *journal, char *jrnl_buf, int prev_desc_logical_no)
{
    struct ext2_inode inode_journal;
    struct ext_filesystem *fs = get_fs();
    struct journal_header_t *jdb;
    long int blknr;
    char *p_jdb;
    int ofs, flags;
    int next_log_block, io_block;
    struct ext3_journal_block_tag *tag;
    char *metadata_buff = zalloc(fs->blksz);
    int tag_bytes;
    debug("recover journal blk no %x\n",prev_desc_logical_no);
    tag_bytes = sizeof(struct ext3_journal_block_tag);
    
    if (!jrnl_buf || !metadata_buff)
        goto fail;
    
    next_log_block = prev_desc_logical_no;
    ext4fs_read_inode(ext4fs_root, EXT2_JOURNAL_INO,
              (struct ext2_inode *)&inode_journal);
    p_jdb = (char *)jrnl_buf;
    jdb = (struct journal_header_t *)jrnl_buf;
    ofs = sizeof(struct journal_header_t);
    do {
        tag = (struct ext3_journal_block_tag *)&p_jdb[ofs];
        ofs += tag_bytes;

        if (ofs > fs->blksz)
            break;

        flags = be32_to_cpu(tag->flags);
        if (!(flags & EXT3_JOURNAL_FLAG_SAME_UUID))
            ofs += 16;

        io_block =  next_log_block++;
        wrap(journal, next_log_block);
        debug("\t\ttag 0x%x flag 0x%x\n", be32_to_cpu(tag->block), flags);
        if (revk_blk_list != NULL) {
            if (check_blknr_for_revoke(be32_to_cpu(tag->block),
                           be32_to_cpu(jdb->
                                   h_sequence)) ==
                0)
                continue;
        }
        blknr = read_allocated_block(&inode_journal, io_block);
        if(!ext4fs_devread(blknr * fs->sect_perblk, 0,
                   fs->blksz, metadata_buff))
            goto fail;

        put_ext4((uint64_t) (be32_to_cpu(tag->block) * fs->blksz),
             metadata_buff, (uint32_t) fs->blksz);
    } while (!(flags & EXT3_JOURNAL_FLAG_LAST_TAG));


    free(metadata_buff);
    return 1;

fail:
    free(metadata_buff);
    return 0;
}

void print_jrnl_status(int recovery_flag)
{
    if (recovery_flag == RECOVER)
        printf("Journal Recovery Completed\n");
    else
        printf("Journal Scan Completed\n");
}

int ext4fs_check_journal_state(int recovery_flag)
{
    int next_log_block;
    long int blknr;
    struct ext2_inode inode_journal;
    struct journal_superblock_t *jsb = NULL;
    struct journal_header_t *jdb = NULL;
    char *temp_buff = NULL;
    char *temp_buff1 = NULL;
    struct ext_filesystem *fs = get_fs();
    int tag_bytes;
    unsigned int crc32_sum = ~0; /* Transactional Checksums */

    tag_bytes = sizeof(struct ext3_journal_block_tag);

    temp_buff = zalloc(fs->blksz);
    if (!temp_buff)
        return -ENOMEM;
    temp_buff1 = zalloc(fs->blksz);
    if (!temp_buff1) {
        free(temp_buff);
        return -ENOMEM;
    }

    if (recovery_flag == SCAN)
        debug("In SCAN pass!\n");

    if (recovery_flag == RECOVER)
        debug("In RECOVER pass!\n");

    ext4fs_read_inode(ext4fs_root, EXT2_JOURNAL_INO, &inode_journal);
    blknr = read_allocated_block(&inode_journal, EXT2_JOURNAL_SUPERBLOCK);
    ext4fs_devread(blknr * fs->sect_perblk, 0, fs->blksz, temp_buff);

    jsb = (struct journal_superblock_t *)temp_buff;
    if(jsb->s_header.h_magic != cpu_to_be32(EXT3_JOURNAL_MAGIC_NUMBER) ||
        jsb->s_blocksize != cpu_to_be32(fs->blksz)){
        printf("JBD: no valid journal superblock found\n");
        goto done;
    }

    if ((fs->sb->feature_incompat & EXT3_FEATURE_INCOMPAT_RECOVER) &&
            be32_to_cpu(jsb->s_start) ) {
        if (recovery_flag == RECOVER)
            printf("Recovery required\n");
    } else {
        if (recovery_flag == RECOVER)
            printf("File System is consistent\n");
        goto done;
    }

    if (!(jsb->s_feature_compat &
          cpu_to_be32(JBD2_FEATURE_COMPAT_CHECKSUM)))
        jsb->s_feature_compat |=
            cpu_to_be32(JBD2_FEATURE_COMPAT_CHECKSUM);

    next_log_block = be32_to_cpu(jsb->s_start);

    while (1) {
        if (recovery_flag != SCAN)
            if (tid_geq(be32_to_cpu(jsb->s_sequence), end_transaction)){
                debug("jsb->s_sequence=%d, end_transaction=%d\n", 
                    be32_to_cpu(jsb->s_sequence), end_transaction);
                break;
            }
        blknr = read_allocated_block(&inode_journal, next_log_block);
        debug("next_log_block=%d, blknr=%ld\n",next_log_block,blknr * fs->sect_perblk);
        memset(temp_buff1, '\0', fs->blksz);
        ext4fs_devread(blknr * fs->sect_perblk,
                   0, fs->blksz, temp_buff1);
        next_log_block++;
        wrap(jsb, next_log_block);

        jdb = (struct journal_header_t *)temp_buff1;
        debug("next_log_block=%d, blknr=%ld, jsb_sequence=%x, jdb_sequence=%x\n",
            next_log_block,blknr * fs->sect_perblk,be32_to_cpu(jsb->s_sequence),be32_to_cpu(jdb->h_sequence));  
        if (jdb->h_magic != cpu_to_be32(EXT3_JOURNAL_MAGIC_NUMBER)) {
            debug("JBD: recovery pass %d hit the end, ID=%d\n", recovery_flag, be32_to_cpu(jdb->h_sequence));
            print_jrnl_status(recovery_flag);
            break;
        }

        if (be32_to_cpu(jdb->h_sequence) !=
            be32_to_cpu(jsb->s_sequence)) {
            print_jrnl_status(recovery_flag);
            break;
        }

        if (be32_to_cpu(jdb->h_blocktype) ==
            EXT3_JOURNAL_DESCRIPTOR_BLOCK) {

            if((recovery_flag != RECOVER) && !end_transaction){
                if (calc_chksums(jsb, temp_buff1, next_log_block, &crc32_sum))
                    break;
            }

            if(recovery_flag == RECOVER){
                if(!recover_transaction(jsb, temp_buff1, next_log_block))
                    break;
            }

            next_log_block += count_tags(fs, temp_buff1);
            wrap(jsb, next_log_block);

            if(recovery_flag != RECOVER)
                continue;

        } else if (be32_to_cpu(jdb->h_blocktype) ==
               EXT3_JOURNAL_COMMIT_BLOCK) {

            if(recovery_flag == SCAN){
                int chksum_err, chksum_seen;
                struct commit_header *ch = (struct commit_header *)temp_buff1;
                unsigned int found_chksum =
					be32_to_cpu(ch->h_chksum[0]);

                chksum_err = chksum_seen = 0;

                if(end_transaction){
                    printf("JBD: Commit transaction %d error!\n", be32_to_cpu(jsb->s_sequence));
                    goto end;
                }

                if (crc32_sum == found_chksum &&
                    ch->h_chksum_type == JBD2_CRC32_CHKSUM &&
                    ch->h_chksum_size == JBD2_CRC32_CHKSUM_SIZE)
                        chksum_seen = 1;
                else if (!(be32_to_cpu(ch->h_chksum_type)  == 0 &&
                                be32_to_cpu(ch->h_chksum_size) == 0 &&
                                found_chksum == 0 &&
                                !chksum_seen)){
                        /*
                        * If fs is mounted using an old kernel and then
                        * kernel with journal_chksum is used then we
                        * get a situation where the journal flag has
                        * checksum flag set but checksums are not
                        * present i.e chksum = 0, in the individual
                        * commit blocks.
                        * Hence to avoid checksum failures, in this
                        * situation, this extra check is added.
                        */
                        printf("h_chksum_type=%x, h_chksum_size=%x, crc32_sum=%x, found_chksum=%x\n",
                                be32_to_cpu(ch->h_chksum_type), be32_to_cpu(ch->h_chksum_size), crc32_sum, found_chksum);
                        chksum_err = 1;
                    }

                if (chksum_err) {
                        end_transaction = be32_to_cpu(jsb->s_sequence);

                        if(fs->sb->feature_incompat & JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT){
                                printf("JBD: Commit transaction %d CRC error!\n", be32_to_cpu(jsb->s_sequence));
                                break;
                        }
                }
                crc32_sum = ~0;
            }

            if (recovery_flag == SCAN)
                debug("JBD: sequence %d need commit\n", be32_to_cpu(jsb->s_sequence));
            jsb->s_sequence = cpu_to_be32(be32_to_cpu(jsb->s_sequence) + 1);

            debug("%s next_log_block=%d, jsb->s_sequence=%d\n",
                        __func__, next_log_block, be32_to_cpu(jsb->s_sequence));
        } else if (be32_to_cpu(jdb->h_blocktype) ==
               EXT3_JOURNAL_REVOKE_BLOCK) {

            if (recovery_flag == SCAN)
                ext4fs_push_revoke_blk((char *)jdb);
        } else {

            debug("Else Case\n");

        }
    }

 end:
    if (recovery_flag == SCAN) {
            if(!end_transaction)
                end_transaction = be32_to_cpu(jsb->s_sequence);

        }else if (recovery_flag == RECOVER){

            if(end_transaction != be32_to_cpu(jsb->s_sequence)){
                printf ("JBD: recovery pass %d ended at "
				"transaction %u, expected %u\n",
				recovery_flag, be32_to_cpu(jsb->s_sequence), end_transaction);
                free(temp_buff);
                free(temp_buff1);
                return -EIO;
            }

            jsb->s_start = jsb->s_first;
            jsb->s_sequence = cpu_to_be32(be32_to_cpu(jsb->s_sequence) + 1);
            /* get the superblock */
            ext4fs_devread(SUPERBLOCK_SECTOR, 0, SUPERBLOCK_SIZE,
                       (char *)fs->sb);
            fs->sb->feature_incompat |= EXT3_FEATURE_INCOMPAT_RECOVER;

            /* Update the super block */
            put_ext4((uint64_t) (SUPERBLOCK_SIZE),
                 (struct ext2_sblock *)fs->sb,
                 (uint32_t) SUPERBLOCK_SIZE);
            ext4fs_devread(SUPERBLOCK_SECTOR, 0, SUPERBLOCK_SIZE,
                       (char *)fs->sb);

            blknr = read_allocated_block(&inode_journal,
                             EXT2_JOURNAL_SUPERBLOCK);
            if(blknr < 0)
                goto done;

            put_ext4((uint64_t) (blknr * fs->blksz),
                 (struct journal_superblock_t *)temp_buff,
                 (uint32_t) fs->blksz);
            ext4fs_free_revoke_blks();
    }

done:
    free(temp_buff);
    free(temp_buff1);

    return 0;
}

static void update_descriptor_block(long int blknr)
{
    int i;
    long int jsb_blknr;
    struct journal_header_t jdb;
    struct ext3_journal_block_tag tag;
    struct ext2_inode inode_journal;
    struct journal_superblock_t *jsb = NULL;
    char *buf = NULL;
    char *temp = NULL;
    struct ext_filesystem *fs = get_fs();
    char *temp_buff = zalloc(fs->blksz);
    if (!temp_buff)
        return;

    ext4fs_read_inode(ext4fs_root, EXT2_JOURNAL_INO, &inode_journal);
    jsb_blknr = read_allocated_block(&inode_journal,
                     EXT2_JOURNAL_SUPERBLOCK);
    ext4fs_devread(jsb_blknr * fs->sect_perblk, 0, fs->blksz, temp_buff);
    jsb = (struct journal_superblock_t *)temp_buff;

    jdb.h_blocktype = cpu_to_be32(EXT3_JOURNAL_DESCRIPTOR_BLOCK);
    jdb.h_magic = cpu_to_be32(EXT3_JOURNAL_MAGIC_NUMBER);
    jdb.h_sequence = jsb->s_sequence;
    buf = zalloc(fs->blksz);
    if (!buf) {
        free(temp_buff);
        return;
    }
    temp = buf;
    memcpy(buf, &jdb, sizeof(struct journal_header_t));
    temp += sizeof(struct journal_header_t);

    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (journal_ptr[i]->blknr == -1)
            break;

        tag.block = cpu_to_be32(journal_ptr[i]->blknr);
        tag.flags = cpu_to_be32(EXT3_JOURNAL_FLAG_SAME_UUID);
        memcpy(temp, &tag, sizeof(struct ext3_journal_block_tag));
        temp = temp + sizeof(struct ext3_journal_block_tag);
    }

    tag.block = cpu_to_be32(journal_ptr[--i]->blknr);
    tag.flags = cpu_to_be32(EXT3_JOURNAL_FLAG_LAST_TAG);
    memcpy(temp - sizeof(struct ext3_journal_block_tag), &tag,
           sizeof(struct ext3_journal_block_tag));
    put_ext4((uint64_t) (blknr * fs->blksz), buf, (uint32_t) fs->blksz);

    free(temp_buff);
    free(buf);
}

static void update_commit_block(long int blknr)
{
    struct journal_header_t jdb;
    struct ext_filesystem *fs = get_fs();
    char *buf = NULL;
    struct ext2_inode inode_journal;
    struct journal_superblock_t *jsb;
    long int jsb_blknr;
    char *temp_buff = zalloc(fs->blksz);
    if (!temp_buff)
        return;

    ext4fs_read_inode(ext4fs_root, EXT2_JOURNAL_INO, &inode_journal);
    jsb_blknr = read_allocated_block(&inode_journal,
                     EXT2_JOURNAL_SUPERBLOCK);
    ext4fs_devread(jsb_blknr * fs->sect_perblk, 0, fs->blksz, temp_buff);
    jsb = (struct journal_superblock_t *)temp_buff;

    jdb.h_blocktype = cpu_to_be32(EXT3_JOURNAL_COMMIT_BLOCK);
    jdb.h_magic = cpu_to_be32(EXT3_JOURNAL_MAGIC_NUMBER);
    jdb.h_sequence = jsb->s_sequence;
    buf = zalloc(fs->blksz);
    if (!buf) {
        free(temp_buff);
        return;
    }
    memcpy(buf, &jdb, sizeof(struct journal_header_t));
    put_ext4((uint64_t) (blknr * fs->blksz), buf, (uint32_t) fs->blksz);

    free(temp_buff);
    free(buf);
}

void ext4fs_update_journal(void)
{
    struct ext2_inode inode_journal;
    struct ext_filesystem *fs = get_fs();
    long int blknr;
    int i;
    ext4fs_read_inode(ext4fs_root, EXT2_JOURNAL_INO, &inode_journal);
    blknr = read_allocated_block(&inode_journal, jrnl_blk_idx++);
    if(blknr < 0){
        printf("update journal failed\n");
        return;
    }
    
    update_descriptor_block(blknr);
    for (i = 0; i < MAX_JOURNAL_ENTRIES; i++) {
        if (journal_ptr[i]->blknr == -1)
            break;
        blknr = read_allocated_block(&inode_journal, jrnl_blk_idx++);
        if(blknr < 0){
            printf("update journal failed\n");
            return;
        }
        put_ext4((uint64_t) (blknr * fs->blksz),
             journal_ptr[i]->buf, (uint32_t) fs->blksz);
    }
    blknr = read_allocated_block(&inode_journal, jrnl_blk_idx++);
    if(blknr < 0){
        printf("update journal failed\n");
        return;
    }    
    update_commit_block(blknr);
    printf("update journal finished\n");
}
