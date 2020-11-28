/*
 *
 *
 *
 *
 *
 *
 */

#ifndef __UBI_ENHANCE_INITIALIZATION_H__

#define __UBI_ENHANCE_INITIALIZATION_H__

#ifdef CONFIG_MTD_UBI_ENHANCE_INIT
#include <linux/types.h>

//#define EN_INIT_DEBUG
#define MTD_SPEED_UP_PART CONFIG_MTD_UBI_ENHANCE_INIT_PART

#define ENINIT_MAX_SQNUM			0x7FFFFFFF
//control error code
#define ERR_CTRL_RECORD_FOUND		(0x600|1)
#define ERR_CTRL_RECORD_INVALID		(0x600|2)
#define ERR_CTRL_RECORD_FAIL		(0x600|3)
#define ERR_CTRL_RECORD_NOFOUND		(0x600|4)
#define ERR_CTRL_RECORD_NOAVLBLK 	(0x600|5)
#define ERR_CTRL_RECORD_WRITEFAIL 	(0x600|6)
#define ERR_TBL_RECORD_POWERCUT		(0x600|7)
#define ERR_TBL_RECORD_NOAVLBLK 	(0x600|8)

#ifdef EN_INIT_DEBUG
#define eninit_msg(fmt, ...)		\
		printf("UBI ENINIT DEBG [%s]: " fmt "\n",\
			__func__, ##__VA_ARGS__)
#else
#define eninit_msg(fmt, ...) 
#endif

#define eninit_err(fmt, ...)		\
		printf("UBI ENINIT ERR [%s]: " fmt "\n",\
			__func__, ##__VA_ARGS__)

//#define CONFIG_NAND_TWO_PLANE


//#include "drvNAND.h"
/*
ubi_en_tbl_record

collection of necessary info. in ec and vid header of each peb.
@ is_bad : represents current peb is bad block
@ pnum: represent the peb number, this record is belong to.
@ ec: erase count of current peb
@ image_seq: image_seq in ec header
@ has_vid: represent this peb contains vid records or not
@ other variables: necessity in vid header for completion of scan process.
*/

struct ubi_en_tbl_record
{
    //EC Header
    __be64  ec;
    __be64  sqnum;	//vid header
    __be32  image_seq;
    //Vid Header
    __be32  vol_id;
    __be32  lnum;
    __be32  used_ebs;
    __be32  data_pad;
    __be32  data_size;
    __be32  data_crc;
    __be16  pnum;
    __u8  is_bad;
    __u8    has_vid;
    __u8    compact;
    __u8    copy_flag;
    __u8    vol_type;
}__attribute__((packed));

struct ubi_tbl_rcd_node
{
	struct ubi_en_tbl_record etr;
	int pnum;
	__u32 rcd_page_idx;
};

#define UEBH 0x55454248

struct ubi_en_bitmap_hdr
{
	__be32 magic;
	__be64 sqnum;
	__be32 next_tbl_page;
}__attribute__((packed));

/*

*/

struct ubi_en_bitmap_record
{
    __u32	next_avail_bit_pages;
	__u32	next_avail_tbl_pages;
	int	is_valid;
	int avail_ctrl_blk_num;
	int avail_tbl_blk_num;
	struct ubi_en_bitmap_hdr * bh;
	__u8	*bitmap;
}__attribute__((packed));


/*
@ disable_flag:	
	disable enhance initialization flow, it is neccessary for 
	preventing ubi system from crash as failure
@ update_flag:
	whether there is an update-dirty-work in work queue currently or not.
@ valid_groups:
	records validation of each table group.
@ re_scan_pnums:
	used for records which pnum should be rescanned by ubi scan sub-system.
	after process valid table records
@ val_tbl_blk:
	records bad block position in tbl storage
@ dirty_pages
	records how many ec/vid header is dirty in each group
@ groups_num:
	number of table records groups
@ tbl_rcds_num:
	number of table records in a group
*/

struct tbl_storage_manager
{
	__u8 disable_flag;	
	__u8 update_flag;
	__u8 *valid_groups;
	__u8 *re_scan_pnums;
	__u8 *val_tbl_blk;
	__u16 *dirty_pages;
	int groups_num;
	int tbl_rcds_num;
	spinlock_t ctrl_lock;
	struct mutex tbl_work_sem;
};

#endif

#endif

