/*
 * (C) Copyright 2004
 *  esd gmbh <www.esd-electronics.com>
 *  Reinhard Arlt <reinhard.arlt@esd-electronics.com>
 *
 *  based on code from grub2 fs/ext2.c and fs/fshelp.c by
 *
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2003, 2004  Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <common.h>
#include <ext2fs.h>
#include <ext_common.h>
#include <malloc.h>
#include <asm/byteorder.h>

extern int ext2fs_devread (int sector, int byte_offset, int byte_len,
               char *buf);


struct ext2_data *ext2fs_root = NULL;
struct ext2fs_node *ext2fs_file;
int symlinknest = 0;
uint32_t *indir1_block = NULL;
int indir1_size = 0;
int indir1_blkno = -1;
uint32_t *indir2_block = NULL;
int indir2_size = 0;
int indir2_blkno = -1;
static unsigned int inode_size;


static int ext2fs_blockgroup
    (struct ext2_data *data, int group, struct ext2_block_group *blkgrp) {
    unsigned int blkno;
    unsigned int blkoff;
    unsigned int desc_per_blk;

    desc_per_blk = EXT2_BLOCK_SIZE(data) / sizeof(struct ext2_block_group);

    blkno = __le32_to_cpu(data->sblock.first_data_block) + 1 +
    group / desc_per_blk;
    blkoff = (group % desc_per_blk) * sizeof(struct ext2_block_group);
#ifdef DEBUG
    printf ("ext2fs read %d group descriptor (blkno %d blkoff %d)\n",
        group, blkno, blkoff);
#endif
    return (ext2fs_devread (blkno << LOG2_EXT2_BLOCK_SIZE(data),
        blkoff, sizeof(struct ext2_block_group), (char *)blkgrp));

}


static int ext2fs_read_inode
    (struct ext2_data *data, int ino, struct ext2_inode *inode) {
    struct ext2_block_group blkgrp;
    struct ext2_sblock *sblock = &data->sblock;
    int inodes_per_block;
    int status;

    unsigned int blkno;
    unsigned int blkoff;

#ifdef DEBUG
    printf ("ext2fs read inode %d, inode_size %d\n", ino, inode_size);
#endif
    /* It is easier to calculate if the first inode is 0.  */
    ino--;
    status = ext2fs_blockgroup (data, ino / __le32_to_cpu
                    (sblock->inodes_per_group), &blkgrp);
    if (status == 0) {
        return (0);
    }

    inodes_per_block = EXT2_BLOCK_SIZE(data) / inode_size;

    blkno = __le32_to_cpu (blkgrp.inode_table_id) +
        (ino % __le32_to_cpu (sblock->inodes_per_group))
        / inodes_per_block;
    blkoff = (ino % inodes_per_block) * inode_size;
#ifdef DEBUG
    printf ("ext2fs read inode blkno %d blkoff %d\n", blkno, blkoff);
#endif
    /* Read the inode.  */
    status = ext2fs_devread (blkno << LOG2_EXT2_BLOCK_SIZE (data), blkoff,
                 sizeof (struct ext2_inode), (char *) inode);
    if (status == 0) {
        return (0);
    }

    return (1);
}


void ext2fs_free_node(struct ext2fs_node *node, struct ext2fs_node *currroot)
{
    if ((node != &ext2fs_root->diropen) && (node != currroot)) {
        free (node);
    }
}


static int ext2fs_read_block(struct ext2fs_node *node, int fileblock)
{
    struct ext2_data *data = node->data;
    struct ext2_inode *inode = &node->inode;
    int blknr;
    int blksz = EXT2_BLOCK_SIZE (data);
    int log2_blksz = LOG2_EXT2_BLOCK_SIZE (data);
    int status;

    /* Direct blocks.  */
    if (fileblock < INDIRECT_BLOCKS) {
        blknr = __le32_to_cpu (inode->b.blocks.dir_blocks[fileblock]);
    }
    /* Indirect.  */
    else if (fileblock < (INDIRECT_BLOCKS + (blksz / 4))) {
        if (indir1_block == NULL) {
            indir1_block = (uint32_t *) malloc (blksz);
            if (indir1_block == NULL) {
                printf ("** ext2fs read block (indir 1) malloc failed. **\n");
                return (-1);
            }
            indir1_size = blksz;
            indir1_blkno = -1;
        }
        if (blksz != indir1_size) {
            free (indir1_block);
            indir1_block = NULL;
            indir1_size = 0;
            indir1_blkno = -1;
            indir1_block = (uint32_t *) malloc (blksz);
            if (indir1_block == NULL) {
                printf ("** ext2fs read block (indir 1) malloc failed. **\n");
                return (-1);
            }
            indir1_size = blksz;
        }
        if ((__le32_to_cpu (inode->b.blocks.indir_block) <<
             log2_blksz) != indir1_blkno) {
            status = ext2fs_devread (__le32_to_cpu(inode->b.blocks.indir_block) << log2_blksz,
                         0, blksz,
                         (char *) indir1_block);
            if (status == 0) {
                printf ("** ext2fs read block (indir 1) failed. **\n");
                return (0);
            }
            indir1_blkno =
                __le32_to_cpu (inode->b.blocks.
                           indir_block) << log2_blksz;
        }
        blknr = __le32_to_cpu (indir1_block
                       [fileblock - INDIRECT_BLOCKS]);
    }
    /* Double indirect.  */
    else if (fileblock <
         (INDIRECT_BLOCKS + (blksz / 4 * (blksz / 4 + 1)))) {
        unsigned int perblock = blksz / 4;
        unsigned int rblock = fileblock - (INDIRECT_BLOCKS
                           + blksz / 4);

        if (indir1_block == NULL) {
            indir1_block = (uint32_t *) malloc (blksz);
            if (indir1_block == NULL) {
                printf ("** ext2fs read block (indir 2 1) malloc failed. **\n");
                return (-1);
            }
            indir1_size = blksz;
            indir1_blkno = -1;
        }
        if (blksz != indir1_size) {
            free (indir1_block);
            indir1_block = NULL;
            indir1_size = 0;
            indir1_blkno = -1;
            indir1_block = (uint32_t *) malloc (blksz);
            if (indir1_block == NULL) {
                printf ("** ext2fs read block (indir 2 1) malloc failed. **\n");
                return (-1);
            }
            indir1_size = blksz;
        }
        if ((__le32_to_cpu (inode->b.blocks.double_indir_block) <<
             log2_blksz) != indir1_blkno) {
            status = ext2fs_devread (__le32_to_cpu(inode->b.blocks.double_indir_block) << log2_blksz,
                        0, blksz,
                        (char *) indir1_block);
            if (status == 0) {
                printf ("** ext2fs read block (indir 2 1) failed. **\n");
                return (-1);
            }
            indir1_blkno =
                __le32_to_cpu (inode->b.blocks.double_indir_block) << log2_blksz;
        }

        if (indir2_block == NULL) {
            indir2_block = (uint32_t *) malloc (blksz);
            if (indir2_block == NULL) {
                printf ("** ext2fs read block (indir 2 2) malloc failed. **\n");
                return (-1);
            }
            indir2_size = blksz;
            indir2_blkno = -1;
        }
        if (blksz != indir2_size) {
            free (indir2_block);
            indir2_block = NULL;
            indir2_size = 0;
            indir2_blkno = -1;
            indir2_block = (uint32_t *) malloc (blksz);
            if (indir2_block == NULL) {
                printf ("** ext2fs read block (indir 2 2) malloc failed. **\n");
                return (-1);
            }
            indir2_size = blksz;
        }
        if ((__le32_to_cpu (indir1_block[rblock / perblock]) <<
             log2_blksz) != indir2_blkno) {
            status = ext2fs_devread (__le32_to_cpu(indir1_block[rblock / perblock]) << log2_blksz,
                         0, blksz,
                         (char *) indir2_block);
            if (status == 0) {
                printf ("** ext2fs read block (indir 2 2) failed. **\n");
                return (-1);
            }
            indir2_blkno =
                __le32_to_cpu (indir1_block[rblock / perblock]) << log2_blksz;
        }
        blknr = __le32_to_cpu (indir2_block[rblock % perblock]);
    }
    /* Tripple indirect.  */
    else {
        printf ("** ext2fs doesn't support tripple indirect blocks. **\n");
        return (-1);
    }
#ifdef DEBUG
    printf ("ext2fs_read_block %08x\n", blknr);
#endif
    return (blknr);
}


int ext2fs_read_file
    (struct ext2fs_node *node, int pos, unsigned int len, char *buf)
{
    int i;
    int blockcnt;
    int log2blocksize = LOG2_EXT2_BLOCK_SIZE (node->data);
    int blocksize = 1 << (log2blocksize + DISK_SECTOR_BITS);
    unsigned int filesize = __le32_to_cpu(node->inode.size);

    /* Adjust len so it we can't read past the end of the file.  */
    if (len > filesize) {
        len = filesize;
    }
    blockcnt = ((len + pos) + blocksize - 1) / blocksize;

    for (i = pos / blocksize; i < blockcnt; i++) {
        int blknr;
        int blockoff = pos % blocksize;
        int blockend = blocksize;

        int skipfirst = 0;

        blknr = ext2fs_read_block (node, i);
        if (blknr < 0) {
            return (-1);
        }
        blknr = blknr << log2blocksize;

        /* Last block.  */
        if (i == blockcnt - 1) {
            blockend = (len + pos) % blocksize;

            /* The last portion is exactly blocksize.  */
            if (!blockend) {
                blockend = blocksize;
            }
        }

        /* First block.  */
        if (i == pos / blocksize) {
            skipfirst = blockoff;
            blockend -= skipfirst;
        }

        /* If the block number is 0 this block is not stored on disk but
           is zero filled instead.  */
        if (blknr) {
            int status;

            status = ext2fs_devread (blknr, skipfirst, blockend, buf);
            if (status == 0) {
                return (-1);
            }
        } else {
            memset (buf, 0, blocksize - skipfirst);
        }
        buf += blocksize - skipfirst;
    }
    return (len);
}

int ext2fs_iterate_dir(struct ext2fs_node *dir, char *name,
                    struct ext2fs_node **fnode, int *ftype)
{
    unsigned int fpos = 0;
    int status;
    struct ext2fs_node *diro = (struct ext2fs_node *) dir;

#ifdef DEBUG
    if (name != NULL)
        printf ("Iterate dir %s\n", name);
#endif /* of DEBUG */
    if (!diro->inode_read) {
        status = ext2fs_read_inode (diro->data, diro->ino,
                        &diro->inode);
        if (status == 0) {
            return (0);
        }
    }
    /* Search the file.  */
    while (fpos < __le32_to_cpu (diro->inode.size)) {
        struct ext2_dirent dirent;

        status = ext2fs_read_file (diro, fpos,
                       sizeof (struct ext2_dirent),
                       (char *) &dirent);
        if (status < 1) {
            return (0);
        }
        if (dirent.namelen != 0) {
            char filename[dirent.namelen + 1];
            struct ext2fs_node *fdiro;
            int type = FILETYPE_UNKNOWN;

            status = ext2fs_read_file (diro,
                           fpos + sizeof (struct ext2_dirent),
                           dirent.namelen, filename);
            if (status < 1) {
                return (0);
            }
            fdiro = malloc (sizeof (struct ext2fs_node));
            if (!fdiro) {
                return (0);
            }

            fdiro->data = diro->data;
            fdiro->ino = __le32_to_cpu (dirent.inode);

            filename[dirent.namelen] = '\0';

            if (dirent.filetype != FILETYPE_UNKNOWN) {
                fdiro->inode_read = 0;

                if (dirent.filetype == FILETYPE_DIRECTORY) {
                    type = FILETYPE_DIRECTORY;
                } else if (dirent.filetype ==
                       FILETYPE_SYMLINK) {
                    type = FILETYPE_SYMLINK;
                } else if (dirent.filetype == FILETYPE_REG) {
                    type = FILETYPE_REG;
                }
            } else {
                /* The filetype can not be read from the dirent, get it from inode */

                status = ext2fs_read_inode (diro->data,
                                __le32_to_cpu(dirent.inode),
                                &fdiro->inode);
                if (status == 0) {
                    free (fdiro);
                    return (0);
                }
                fdiro->inode_read = 1;

                if ((__le16_to_cpu (fdiro->inode.mode) &
                     FILETYPE_INO_MASK) ==
                    FILETYPE_INO_DIRECTORY) {
                    type = FILETYPE_DIRECTORY;
                } else if ((__le16_to_cpu (fdiro->inode.mode)
                        & FILETYPE_INO_MASK) ==
                       FILETYPE_INO_SYMLINK) {
                    type = FILETYPE_SYMLINK;
                } else if ((__le16_to_cpu (fdiro->inode.mode)
                        & FILETYPE_INO_MASK) ==
                       FILETYPE_INO_REG) {
                    type = FILETYPE_REG;
                }
            }
#ifdef DEBUG
            printf ("iterate >%s<\n", filename);
#endif /* of DEBUG */
            if ((name != NULL) && (fnode != NULL)
                && (ftype != NULL)) {
                if (strcmp (filename, name) == 0) {
                    *ftype = type;
                    *fnode = fdiro;
                    return (1);
                }
            } else {
                if (fdiro->inode_read == 0) {
                    status = ext2fs_read_inode (diro->data,
                                __le32_to_cpu (dirent.inode),
                                &fdiro->inode);
                    if (status == 0) {
                        free (fdiro);
                        return (0);
                    }
                    fdiro->inode_read = 1;
                }
                switch (type) {
                case FILETYPE_DIRECTORY:
                    printf ("<DIR> ");
                    break;
                case FILETYPE_SYMLINK:
                    printf ("<SYM> ");
                    break;
                case FILETYPE_REG:
                    printf ("      ");
                    break;
                default:
                    printf ("< ? > ");
                    break;
                }
                printf ("%10d %s\n",
                    __le32_to_cpu (fdiro->inode.size),
                    filename);
            }
            free (fdiro);
        }
        fpos += __le16_to_cpu (dirent.direntlen);
    }
    return (0);
}

static char *ext2fs_read_symlink(struct ext2fs_node *node)
{
    char *symlink;
    struct ext2fs_node *diro = node;
    int status;

    if (!diro->inode_read) {
        status = ext2fs_read_inode (diro->data, diro->ino,
                        &diro->inode);
        if (status == 0) {
            return (0);
        }
    }
    symlink = malloc (__le32_to_cpu (diro->inode.size) + 1);
    if (!symlink) {
        return (0);
    }
    /* If the filesize of the symlink is bigger than
       60 the symlink is stored in a separate block,
       otherwise it is stored in the inode.  */
    if (__le32_to_cpu (diro->inode.size) <= 60) {
        strncpy (symlink, diro->inode.b.symlink,
             __le32_to_cpu (diro->inode.size));
    } else {
        status = ext2fs_read_file (diro, 0,
                       __le32_to_cpu (diro->inode.size),
                       symlink);
        if (status == 0) {
            free (symlink);
            return (0);
        }
    }
    symlink[__le32_to_cpu (diro->inode.size)] = '\0';
    return (symlink);
}


int ext2fs_find_file1
    (const char *currpath, struct ext2fs_node *currroot,
        struct ext2fs_node **currfound, int *foundtype)
{
    char fpath[strlen (currpath) + 1];
    char *name = fpath;
    char *next;
    int status;
    int type = FILETYPE_DIRECTORY;
    struct ext2fs_node *currnode = currroot;
    struct ext2fs_node *oldnode = currroot;

    strncpy (fpath, currpath, strlen (currpath) + 1);

    /* Remove all leading slashes.  */
    while (*name == '/') {
        name++;
    }
    if (!*name) {
        *currfound = currnode;
        return (1);
    }

    for (;;) {
        int found;

        /* Extract the actual part from the pathname.  */
        next = strchr (name, '/');
        if (next) {
            /* Remove all leading slashes.  */
            while (*next == '/') {
                *(next++) = '\0';
            }
        }

        /* At this point it is expected that the current node is a directory, check if this is true.  */
        if (type != FILETYPE_DIRECTORY) {
            ext2fs_free_node (currnode, currroot);
            return (0);
        }

        oldnode = currnode;

        /* Iterate over the directory.  */
        found = ext2fs_iterate_dir (currnode, name, &currnode, &type);
        if (found == 0) {
            return (0);
        }
        if (found == -1) {
            break;
        }

        /* Read in the symlink and follow it.  */
        if (type == FILETYPE_SYMLINK) {
            char *symlink;

            /* Test if the symlink does not loop.  */
            if (++symlinknest == 8) {
                ext2fs_free_node (currnode, currroot);
                ext2fs_free_node (oldnode, currroot);
                return (0);
            }

            symlink = ext2fs_read_symlink (currnode);
            ext2fs_free_node (currnode, currroot);

            if (!symlink) {
                ext2fs_free_node (oldnode, currroot);
                return (0);
            }
#ifdef DEBUG
            printf ("Got symlink >%s<\n", symlink);
#endif /* of DEBUG */
            /* The symlink is an absolute path, go back to the root inode.  */
            if (symlink[0] == '/') {
                ext2fs_free_node (oldnode, currroot);
                oldnode = &ext2fs_root->diropen;
            }

            /* Lookup the node the symlink points to.  */
            status = ext2fs_find_file1 (symlink, oldnode,
                            &currnode, &type);

            free (symlink);

            if (status == 0) {
                ext2fs_free_node (oldnode, currroot);
                return (0);
            }
        }

        ext2fs_free_node (oldnode, currroot);

        /* Found the node!  */
        if (!next || *next == '\0') {
            *currfound = currnode;
            *foundtype = type;
            return (1);
        }
        name = next;
    }
    return (-1);
}


int ext2fs_find_file
    (const char *path, struct ext2fs_node *rootnode,
    struct ext2fs_node **foundnode, int expecttype)
{
    int status;
    int foundtype = FILETYPE_DIRECTORY;


    symlinknest = 0;
    if (!path) {
        return (0);
    }

    status = ext2fs_find_file1 (path, rootnode, foundnode, &foundtype);
    if (status == 0) {
        return (0);
    }
    /* Check if the node that was found was of the expected type.  */
    if ((expecttype == FILETYPE_REG) && (foundtype != expecttype)) {
        return (0);
    } else if ((expecttype == FILETYPE_DIRECTORY)
           && (foundtype != expecttype)) {
        return (0);
    }
    return (1);
}


int ext2fs_ls (const char *dirname) {
    struct ext2fs_node *dirnode;
    int status;

    if (ext2fs_root == NULL) {
        return (0);
    }

    status = ext2fs_find_file (dirname, &ext2fs_root->diropen, &dirnode,
                   FILETYPE_DIRECTORY);
    if (status != 1) {
        printf ("** Can not find directory. **\n");
        return (1);
    }
    ext2fs_iterate_dir (dirnode, NULL, NULL, NULL);
    ext2fs_free_node (dirnode, &ext2fs_root->diropen);
    return (0);
}


int ext2fs_open (const char *filename) {
    struct ext2fs_node *fdiro = NULL;
    int status;
    int len;

    if (ext2fs_root == NULL) {
        return (-1);
    }
    ext2fs_file = NULL;
    status = ext2fs_find_file (filename, &ext2fs_root->diropen, &fdiro,
                   FILETYPE_REG);
    if (status == 0) {
        goto fail;
    }
    if (!fdiro->inode_read) {
        status = ext2fs_read_inode (fdiro->data, fdiro->ino,
                        &fdiro->inode);
        if (status == 0) {
            goto fail;
        }
    }
    len = __le32_to_cpu (fdiro->inode.size);
    ext2fs_file = fdiro;
    return (len);

fail:
    ext2fs_free_node (fdiro, &ext2fs_root->diropen);
    return (-1);
}


int ext2fs_close(void)
{
    if ((ext2fs_file != NULL) && (ext2fs_root != NULL)) {
        ext2fs_free_node (ext2fs_file, &ext2fs_root->diropen);
        ext2fs_file = NULL;
    }
    if (ext2fs_root != NULL) {
        free (ext2fs_root);
        ext2fs_root = NULL;
    }
    if (indir1_block != NULL) {
        free (indir1_block);
        indir1_block = NULL;
        indir1_size = 0;
        indir1_blkno = -1;
    }
    if (indir2_block != NULL) {
        free (indir2_block);
        indir2_block = NULL;
        indir2_size = 0;
        indir2_blkno = -1;
    }
    return (0);
}


int ext2fs_read (char *buf, unsigned len) {
    int status;

    if (ext2fs_root == NULL) {
        return (0);
    }

    if (ext2fs_file == NULL) {
        return (0);
    }

    status = ext2fs_read_file (ext2fs_file, 0, len, buf);
    return (status);
}


int ext2fs_mount (unsigned part_length) {
    struct ext2_data *data;
    int status;

    data = malloc (sizeof (struct ext2_data));
    if (!data) {
        return (0);
    }
    /* Read the superblock.  */
    status = ext2fs_devread (1 * 2, 0, sizeof (struct ext2_sblock),
                 (char *) &data->sblock);
    if (status == 0) {
        goto fail;
    }
    /* Make sure this is an ext2 filesystem.  */
    if (__le16_to_cpu (data->sblock.magic) != EXT2_MAGIC) {
        goto fail;
    }
    if (__le32_to_cpu(data->sblock.revision_level == 0)) {
        inode_size = 128;
    } else {
        inode_size = __le16_to_cpu(data->sblock.inode_size);
    }
#ifdef DEBUG
    printf("EXT2 rev %d, inode_size %d\n",
            __le32_to_cpu(data->sblock.revision_level), inode_size);
#endif
    data->diropen.data = data;
    data->diropen.ino = 2;
    data->diropen.inode_read = 1;
    data->inode = &data->diropen.inode;

    status = ext2fs_read_inode (data, 2, data->inode);
    if (status == 0) {
        goto fail;
    }

    ext2fs_root = data;

    return (1);

fail:
    printf ("Failed to mount ext2 filesystem...\n");
    free (data);
    ext2fs_root = NULL;
    return (0);
}
