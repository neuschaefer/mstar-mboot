/*
 * Unsorted Block Image commands
 *
 *  Copyright (C) 2008 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 * Copyright 2008-2009 Stefan Roese <sr@denx.de>, DENX Software Engineering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <common.h>
#include <command.h>
#include <exports.h>

#include <nand.h>
#include <onenand_uboot.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <ubi_uboot.h>
#include <asm/errno.h>
#include <jffs2/load_kernel.h>
#include <config.h> // MStar

#define DEV_TYPE_NONE		0
#define DEV_TYPE_NAND		1
#define DEV_TYPE_ONENAND	2
#define DEV_TYPE_NOR		3

/* Private own data */
static struct ubi_device *ubi;
static char buffer[80];
static int ubi_initialized;

struct selected_dev {
	char part_name[80];
	int selected;
	int nr;
	struct mtd_info *mtd_info;
};

static struct selected_dev ubi_dev;

struct ubi_volume last_upd_vol;
char *upd_buf;

#ifdef CONFIG_CMD_UBIFS
int ubifs_is_mounted(void);
void cmd_ubifs_umount(void);
#endif

extern struct mtd_device *current_mtd_dev;
extern struct part_info* mtd_part_info(struct mtd_device *dev, unsigned int part_num);

void restore_volume(struct ubi_volume *vol)
{
	printf("restore volume...\n");
	if(vol && last_upd_vol.upd_marker){
		vol->updating = last_upd_vol.updating;
		vol->upd_ebs = last_upd_vol.upd_ebs;
		vol->ch_lnum = last_upd_vol.ch_lnum;
		vol->ch_dtype = last_upd_vol.ch_dtype;
		vol->upd_bytes = last_upd_vol.upd_bytes;
		vol->upd_received = last_upd_vol.upd_received;
		vol->usable_leb_size = last_upd_vol.usable_leb_size;
		vol->used_ebs = last_upd_vol.used_ebs;
		vol->last_eb_bytes = last_upd_vol.last_eb_bytes;
		vol->used_bytes = last_upd_vol.used_bytes;
		vol->data_pad = last_upd_vol.data_pad;
		vol->checked = last_upd_vol.checked;
		vol->corrupted = last_upd_vol.corrupted;
		vol->upd_marker = last_upd_vol.upd_marker;
		vol->changing_leb = last_upd_vol.changing_leb;
		
		vol->upd_buf =vol->ubi->peb_buf1;
		memcpy(vol->upd_buf, upd_buf, ubi->peb_size);
		
		#ifdef CONFIG_MTD_UBI_GLUEBI
		vol->gluebi_refcount = last_upd_vol.gluebi_refcount;
		#endif
	}
}

void ubi_get_part_name(char *name)
{
	struct part_info *part;
	int index;
	if(ubi_initialized && name && ubi){
		index =atoi(ubi->mtd->name + strlen("mtd="));
		part = mtd_part_info(current_mtd_dev, index);
		strcpy(name, part->name);
	}
}

static void ubi_dump_vol_info(const struct ubi_volume *vol)
{
    ubi_msg("volume information dump:");
    ubi_msg("vol_id          %d", vol->vol_id);
    ubi_msg("reserved_pebs   %d", vol->reserved_pebs);
    ubi_msg("alignment       %d", vol->alignment);
    ubi_msg("data_pad        %d", vol->data_pad);
    ubi_msg("vol_type        %d", vol->vol_type);
    ubi_msg("name_len        %d", vol->name_len);
    ubi_msg("usable_leb_size %d", vol->usable_leb_size);
    ubi_msg("used_ebs        %d", vol->used_ebs);
    ubi_msg("used_bytes      %lld", vol->used_bytes);
    ubi_msg("last_eb_bytes   %d", vol->last_eb_bytes);
    ubi_msg("corrupted       %d", vol->corrupted);
    ubi_msg("upd_marker      %d", vol->upd_marker);

	if (vol->name_len <= UBI_VOL_NAME_MAX &&
		strnlen(vol->name, vol->name_len + 1) == vol->name_len) {
        ubi_msg("name            %s", vol->name);
	} else {
        ubi_msg("the 1st 5 characters of the name: %c%c%c%c%c",
				vol->name[0], vol->name[1], vol->name[2],
				vol->name[3], vol->name[4]);
	}
}

static void display_volume_info(struct ubi_device *ubi)
{
	int i;

	for (i = 0; i < (ubi->vtbl_slots + 1); i++) {
		if (!ubi->volumes[i])
			continue;	/* Empty record */
		ubi_dump_vol_info(ubi->volumes[i]);
	}
}

static void display_ubi_info(struct ubi_device *ubi)
{
	ubi_msg("MTD device name:            \"%s\"", ubi->mtd->name);
	ubi_msg("MTD device size:            %llu MiB", ubi->flash_size >> 20);
    ubi_msg("physical eraseblock size:   %d bytes (%d KiB)",
    		ubi->peb_size, ubi->peb_size >> 10);
    ubi_msg("logical eraseblock size:    %d bytes", ubi->leb_size);
    ubi_msg("number of good PEBs:        %d", ubi->good_peb_count);
    ubi_msg("number of bad PEBs:         %d", ubi->bad_peb_count);
    ubi_msg("smallest flash I/O unit:    %d", ubi->min_io_size);
    ubi_msg("VID header offset:          %d (aligned %d)",
    		ubi->vid_hdr_offset, ubi->vid_hdr_aloffset);
    ubi_msg("data offset:                %d", ubi->leb_start);
    ubi_msg("max. allowed volumes:       %d", ubi->vtbl_slots);
    ubi_msg("wear-leveling threshold:    %d", CONFIG_MTD_UBI_WL_THRESHOLD);
    ubi_msg("number of internal volumes: %d", UBI_INT_VOL_COUNT);
    ubi_msg("number of user volumes:     %d",
    		ubi->vol_count - UBI_INT_VOL_COUNT);
    ubi_msg("available PEBs:             %d", ubi->avail_pebs);
    ubi_msg("total number of reserved PEBs: %d", ubi->rsvd_pebs);
    ubi_msg("number of PEBs reserved for bad PEB handling: %d",
    		ubi->beb_rsvd_pebs);
    ubi_msg("max/mean erase counter: %d/%d", ubi->max_ec, ubi->mean_ec);
}

//mstar

int ubi_detach_mtd(void)
{

#ifdef CONFIG_CMD_UBIFS
	/*
	 * Automatically unmount UBIFS partition when user
	 * changes the UBI device. Otherwise the following
	 * UBIFS commands will crash.
	 */
	if (ubifs_is_mounted())
		cmd_ubifs_umount();
#endif


	if (ubi_initialized) {
		ubi_exit();
		del_mtd_partitions(ubi_dev.mtd_info);
		ubi_initialized = 0;
	}
	return 0;
}

int ubi_get_leb_size(void)
{
	return ubi->leb_size;
}

int ubi_get_avai_peb(void)
{
	return ubi->avail_pebs;
}

static int ubi_info(int layout)
{
	if (layout)
		display_volume_info(ubi);
	else
		display_ubi_info(ubi);

	return 0;
}

static int verify_mkvol_req(const struct ubi_device *ubi,
			    const struct ubi_mkvol_req *req)
{
	int n, err = EINVAL;

	if (req->bytes < 0 || req->alignment < 0 || req->vol_type < 0 ||
	    req->name_len < 0)
		goto bad;

	if ((req->vol_id < 0 || req->vol_id >= ubi->vtbl_slots) &&
	    req->vol_id != UBI_VOL_NUM_AUTO)
		goto bad;

	if (req->alignment == 0)
		goto bad;

	if (req->bytes == 0) {
		printf("No space left in UBI device!\n");
		err = ENOMEM;
		goto bad;
	}

	if (req->vol_type != UBI_DYNAMIC_VOLUME &&
	    req->vol_type != UBI_STATIC_VOLUME)
		goto bad;

	if (req->alignment > ubi->leb_size)
		goto bad;

	n = req->alignment % ubi->min_io_size;
	if (req->alignment != 1 && n)
		goto bad;

	if (req->name_len > UBI_VOL_NAME_MAX) {
		printf("Name too long!\n");
		err = ENAMETOOLONG;
		goto bad;
	}

	return 0;
bad:
	return err;
}

int ubi_create_vol(char *volume, size_t size, int dynamic)
{
	struct ubi_mkvol_req req;
	int err;

	if (dynamic)
		req.vol_type = UBI_DYNAMIC_VOLUME;
	else
		req.vol_type = UBI_STATIC_VOLUME;

	req.vol_id = UBI_VOL_NUM_AUTO;
	req.alignment = 1;
	req.bytes = size;

	//strcpy(req.name, volume);
	if(strlen(volume)>=sizeof(req.name)){
    	strncpy(req.name, volume, sizeof(req.name)-1);
        req.name[sizeof(req.name)-1]='\0';
    }
    else{
	strcpy(req.name, volume);
    }
	req.name_len = strlen(volume);
	req.name[req.name_len] = '\0';
	req.padding1 = 0;
	/* It's duplicated at drivers/mtd/ubi/cdev.c */
	err = verify_mkvol_req(ubi, &req);
	if (err) {
		printf("verify_mkvol_req failed %d\n", err);
		return err;
	}
	printf("Creating %s volume %s of size %lu\n",
		dynamic ? "dynamic" : "static", volume, (unsigned long)size);
	/* Call real ubi create volume */
	return ubi_create_volume(ubi, &req);
}

struct ubi_volume *ubi_find_volume(char *volume)
{
	struct ubi_volume *vol = NULL;
	int i;

    if(ubi ==NULL)
        return NULL;
	
	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume))
			return vol;
        }

	printf("Volume %s not found!\n", volume);
	return NULL;
}

static int ubi_remove_vol(char *volume)
{
	int err, reserved_pebs, i;
	struct ubi_volume *vol;

	vol = ubi_find_volume(volume);
	if (vol == NULL)
		return ENODEV;

	printf("Remove UBI volume %s (id %d)\n", vol->name, vol->vol_id);

	if (ubi->ro_mode) {
		printf("It's read-only mode\n");
		err = EROFS;
		goto out_err;
	}

	err = ubi_change_vtbl_record(ubi, vol->vol_id, NULL);
	if (err) {
		printf("Error changing Vol tabel record err=%x\n", err);
		goto out_err;
	}
	reserved_pebs = vol->reserved_pebs;
	for (i = 0; i < vol->reserved_pebs; i++) {
		err = ubi_eba_unmap_leb(ubi, vol, i);
		if (err)
			goto out_err;
	}

	kfree(vol->eba_tbl);
	ubi->volumes[vol->vol_id]->eba_tbl = NULL;
	ubi->volumes[vol->vol_id] = NULL;

	ubi->rsvd_pebs -= reserved_pebs;
	ubi->avail_pebs += reserved_pebs;
	i = ubi->beb_rsvd_level - ubi->beb_rsvd_pebs;
	if (i > 0) {
		i = ubi->avail_pebs >= i ? i : ubi->avail_pebs;
		ubi->avail_pebs -= i;
		ubi->rsvd_pebs += i;
		ubi->beb_rsvd_pebs += i;
		if (i > 0)
			ubi_msg("reserve more %d PEBs", i);
	}
	ubi->vol_count -= 1;

	return 0;
out_err:
	ubi_err("cannot remove volume %s, error %d", volume, err);
	if (err < 0)
		err = -err;
	return err;
}

// MStar start
int ubi_volume_write_offset(char *volume, void *buf, size_t size, off_t offset)
{
	int err = -1;
	struct ubi_volume *vol;

	vol = ubi_find_volume(volume);
	if (vol == NULL)
		return ENODEV;
	//check "offset + size" is less than total size of volume
	if((offset + size) > (vol->reserved_pebs * ubi->leb_size))
	{
		printf("Succeed volume size in Volume \"%s\"\n", volume);
		return 1;
	}
	//==================Partial Update=======================
	err = ubi_update_partial_data(ubi, vol, buf, offset, size);

	if(err)
		printf("[%s]\tCan't Partial update data\n", __func__);

	return err;	
}

int ubi_get_volume_size(char *volume, size_t* size)
{
	int i = 0, err = -1;
	int found = 0;
	struct ubi_volume *vol;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			printf("Volume \"%s\" found at volume id %d\n", volume, i);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("%s volume not found\n", volume);
		return 1;
	}

	vol = ubi_find_volume(volume);
	if (vol == NULL)
		return ENODEV;
	
	*size = vol->used_bytes;

	return err;	
}

static int ubi_volume_write_cont(char *volume, void *buf, size_t size)
{
	int i = 0, err = -1;
	int found = 0;
	struct ubi_volume *vol;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			printf("Volume \"%s\" found at volume id %d\n", volume, i);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("%s volume not found\n", volume);
		return 1;
	}

	vol = ubi_find_volume(volume);
	if (vol == NULL)
		return ENODEV;

	err = ubi_more_update_data(ubi, vol, buf, size);
	if (err < 0) {
		printf("Couldnt or partially wrote data \n");
		return err;
	}

	if (err) {
		size = err;

		err = ubi_check_volume(ubi, vol->vol_id);
		if ( err < 0 )
			return err;

		if (err) {
			ubi_warn("volume %d on UBI device %d is corrupted",
					vol->vol_id, ubi->ubi_num);
			vol->corrupted = 1;
		}

		vol->checked = 1;
		ubi_gluebi_updated(vol);
	}
	if (vol->upd_received == vol->upd_bytes && upd_buf) {
		free(upd_buf);
	}
	else{
		memcpy(&last_upd_vol, vol, sizeof(struct ubi_volume));
		memcpy(upd_buf, vol->upd_buf, ubi->peb_size);
	}

	return 0;
}
// MStar end

#if 1 // MStar
static int ubi_volume_write(char *volume, void *buf, size_t size, size_t total_size)
#else
static int ubi_volume_write(char *volume, void *buf, size_t size)
#endif
{
	int err = 1;
	int rsvd_bytes = 0;
	struct ubi_volume *vol;

	vol = ubi_find_volume(volume);
	if (vol == NULL)
		return ENODEV;

	rsvd_bytes = vol->reserved_pebs * (ubi->leb_size - vol->data_pad);
	if (size < 0 || size > rsvd_bytes) {
		printf("size > volume size! Aborting!\n");
		return EINVAL;
	}

	upd_buf = (char *)malloc(ubi->peb_size);
	if(!upd_buf){
		printf("malloc ubi updating buffer failed\n");
		return -1;
	}

#if 1 // MStar
        err = ubi_start_update(ubi, vol, total_size);
#else
	err = ubi_start_update(ubi, vol, size);
#endif
	if (err < 0) {
		printf("Cannot start volume update\n");
		return -err;
	}

	err = ubi_more_update_data(ubi, vol, buf, size);
	if (err < 0) {
		printf("Couldnt or partially wrote data\n");
		return -err;
	}

	if (err) {
		size = err;

		err = ubi_check_volume(ubi, vol->vol_id);
		if (err < 0)
			return -err;

		if (err) {
			ubi_warn("volume %d on UBI device %d is corrupted",
					vol->vol_id, ubi->ubi_num);
			vol->corrupted = 1;
		}

		vol->checked = 1;
		ubi_gluebi_updated(vol);
	}

	printf("%d bytes written to volume %s\n", size, volume);

	if (vol->upd_received == vol->upd_bytes && upd_buf) {
		free(upd_buf);
	}
	else{
		memcpy(&last_upd_vol, vol, sizeof(struct ubi_volume));
		memcpy(upd_buf, vol->upd_buf, ubi->peb_size);
	}

	return 0;
}

// MStar start
int ubi_volume_partial_read(char *volume, char *buf, size_t size, size_t partition_offset)
{
	int err, lnum, off, len, tbuf_size, i = 0;
	size_t count_save = size;
	void *tbuf;
	unsigned long long tmp;
	struct ubi_volume *vol = NULL;
	loff_t offp = 0;
        size_t offset;
        size_t bnum;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			//printf("Volume %s found at volume id %d\n",
			//	volume, vol->vol_id);
			break;
		}
	}
	if ((i == ubi->vtbl_slots)||(vol==NULL)) {
		printf("%s volume not found\n", volume);
		return -ENODEV;
	}

	//printf("read %d bytes from volume %d to %x(buf address) with offset 0x%x\n",
	//       (int) size, vol->vol_id, (unsigned)buf, (unsigned)partition_offset);

	if (vol->updating) {
		printf("updating");
		return -EBUSY;
	}
	if (vol->upd_marker) {
		printf("damaged volume, update marker is set");
		return -EBADF;
	}
	if (offp == vol->used_bytes)
		return 0;

	if (size == 0) {
		printf("Read [%lu] bytes\n", (unsigned long) vol->used_bytes);
		size = vol->used_bytes;
	}

	if (vol->corrupted)
		printf("read from corrupted volume %d", vol->vol_id);
	if (offp + size > vol->used_bytes)
		count_save = size = vol->used_bytes - offp;

	tbuf_size = vol->usable_leb_size;
	if (size < tbuf_size)
		tbuf_size = ALIGN(size, ubi->min_io_size);
	tbuf = malloc(tbuf_size);
	if (!tbuf) {
		printf("NO MEM\n");
		return -ENOMEM;
	}
	len = size > tbuf_size ? tbuf_size : size;

	tmp = offp;
    //red flag CL613675
    offset=partition_offset%vol->usable_leb_size;
    bnum=partition_offset/vol->usable_leb_size;
    off = offset;//do_div(tmp, vol->usable_leb_size);
	lnum = tmp;
#if 1
    do {
		if (off + len >= vol->usable_leb_size)
			len = vol->usable_leb_size - off;

		err = ubi_eba_read_leb(ubi, vol, (lnum+bnum), tbuf, off, len, 0);

		if (err) {
			printf("read err %x\n", err);
			break;
		}
		off += len;
		if (off == vol->usable_leb_size) {
			lnum += 1;
			off -= vol->usable_leb_size;
		}

		size -= len;
		offp += len;

		memcpy(buf, tbuf, len);

		buf += len;
		len = size > tbuf_size ? tbuf_size : size;
	} while (size);
		if (err) {
			printf("read err %x\n", err);
		}
#else
    do {
		if (off + len >= vol->usable_leb_size)
			len = vol->usable_leb_size - off;

		err = ubi_eba_read_leb(ubi, vol, lnum, tbuf, off, len, 0);
        printf("\n\n1111====off=0x%x,len=0x%x,lnum=0x%x, tbuf=0x%x=====\n\n",off,len,lnum,tbuf);
		if (err) {
			printf("read err %x\n", err);
			break;
		}
		off += len;
		if (off == vol->usable_leb_size) {
			lnum += 1;
			off -= vol->usable_leb_size;
        printf("\n\n2222====off=0x%x,len=0x%x,vol->usable_leb_size=0x%x=====\n\n",off,len,vol->usable_leb_size);
		}

		size -= len;
		offp += len;

		memcpy(buf, tbuf, len);

		buf += len;
		len = size > tbuf_size ? tbuf_size : size;
	} while (size);
#endif

	free(tbuf);
    //return err ? err : count_save - size;
    return err;
}
// MStar end

static int ubi_volume_read(char *volume, char *buf, size_t size)
{
	int err, lnum, off, len, tbuf_size;
	size_t count_save = size;
	void *tbuf;
	unsigned long long tmp;
	struct ubi_volume *vol;
	loff_t offp = 0;

	vol = ubi_find_volume(volume);
	if (vol == NULL)
		return ENODEV;

	//printf("Read %d bytes from volume %s to %p\n", size, volume, buf);

	if (vol->updating) {
		printf("updating");
		return EBUSY;
	}
	if (vol->upd_marker) {
		printf("damaged volume, update marker is set");
		return EBADF;
	}
	if (offp == vol->used_bytes)
		return 0;

	if (size == 0) {
		printf("No size specified -> Using max size (%lld)\n", vol->used_bytes);
		size = vol->used_bytes;
	}

	if (vol->corrupted)
		printf("read from corrupted volume %d", vol->vol_id);
	if (offp + size > vol->used_bytes)
		count_save = size = vol->used_bytes - offp;

	tbuf_size = vol->usable_leb_size;
	if (size < tbuf_size)
		tbuf_size = ALIGN(size, ubi->min_io_size);
	tbuf = malloc(tbuf_size);
	if (!tbuf) {
		printf("NO MEM\n");
		return ENOMEM;
	}
	len = size > tbuf_size ? tbuf_size : size;

	tmp = offp;
	off = do_div(tmp, vol->usable_leb_size);
	lnum = tmp;
	do {
		if (off + len >= vol->usable_leb_size)
			len = vol->usable_leb_size - off;

		err = ubi_eba_read_leb(ubi, vol, lnum, tbuf, off, len, 0);
		if (err) {
			printf("read err %x\n", err);
			err = -err;
			break;
		}
		off += len;
		if (off == vol->usable_leb_size) {
			lnum += 1;
			off -= vol->usable_leb_size;
		}

		size -= len;
		offp += len;

		memcpy(buf, tbuf, len);

		buf += len;
		len = size > tbuf_size ? tbuf_size : size;
	} while (size);

	free(tbuf);
	return err;
}

static int ubi_dev_scan(struct mtd_info *info, char *ubidev,
		const char *vid_header_offset)
{
	struct mtd_device *dev;
	struct part_info *part;
	struct mtd_partition mtd_part;
#ifdef CONFIG_MTD_UBI_ENHANCE_INIT
    struct mtd_partition mtd_part_en[2];
	struct mtd_info *ctrl_tbl_info;
	const char * ubispeedup_part;
	char tmp_part[16];
	int count = 0;
#endif
	char ubi_mtd_param_buffer[80];
	u8 pnum;
	int err;

	if (find_dev_and_part(ubidev, &dev, &pnum, &part) != 0)
		return 1;

	sprintf(buffer, "mtd=%d", pnum);
	memset(&mtd_part, 0, sizeof(mtd_part));
	mtd_part.name = buffer;
	mtd_part.size = part->size;
	mtd_part.offset = part->offset;
	add_mtd_partitions(info, &mtd_part, 1);

#ifdef CONFIG_MTD_UBI_ENHANCE_INIT
    count = 0;
	memset(mtd_part_en, 0, sizeof(mtd_part_en));
    memset(tmp_part, 0, 16);
	ubispeedup_part = getenv("UBI_SPEED_UP");

	if(ubispeedup_part)
	{
		if (strncmp(ubispeedup_part, "ubispeedup=", 11) == 0)
		{
	    	ubispeedup_part += 11;
			strncpy(tmp_part, ubispeedup_part, strlen(ubispeedup_part));
		}
		else
		{
			memset(tmp_part, 0, 16);
    	    printf("ubispeedup variable doesn't start with 'ubispeedup='\n");
		}
	}
	else
	{
		memset(tmp_part, 0, 16);
	}

//	if (!strncmp(ubidev, MTD_SPEED_UP_PART, strlen(MTD_SPEED_UP_PART)) && strlen(ubidev) == strlen(MTD_SPEED_UP_PART))
	if (!strncmp(ubidev, tmp_part, strlen(tmp_part)) && strlen(ubidev) == strlen(tmp_part) && tmp_part[0]!= 0)
	{
		if (find_dev_and_part("CTRL", &dev, &pnum, &part) == 0)
		{
			char mtd_dev[16];
			mtd_part_en[0].name = "CTRL";
		    mtd_part_en[0].size = part->size;
		    mtd_part_en[0].offset = part->offset;
			count ++;

			if (find_dev_and_part("TBL", &dev, &pnum, &part) == 0)
			{
				mtd_part_en[1].name = "TBL";
		    	mtd_part_en[1].size = part->size;
			    mtd_part_en[1].offset = part->offset;
				count ++;
			}

			sprintf(mtd_dev, "%s%d", MTD_DEV_TYPE(dev->id->type), dev->id->num);
			ctrl_tbl_info = get_mtd_device_nm(mtd_dev);
			if (IS_ERR(ctrl_tbl_info)) {
				printf("Partition %s not found on device %s!\n", "TBL", mtd_dev);
			}
			else
			{
				printf("Find %s device\n", mtd_dev);
				add_mtd_partitions(ctrl_tbl_info, mtd_part_en, count);
			}
		}
	}

#endif
	strcpy(ubi_mtd_param_buffer, buffer);
	if (vid_header_offset)
		sprintf(ubi_mtd_param_buffer, "mtd=%d,%s", pnum,
				vid_header_offset);
	err = ubi_mtd_param_parse(ubi_mtd_param_buffer, NULL);
	if (err) {
		del_mtd_partitions(info);
		return -err;
	}

	err = ubi_init();
	if (err) {
        ubi_exit();
		del_mtd_partitions(info);
		return -err;
	}

	ubi_initialized = 1;

	return 0;
}

#if 1 // MStar
#define BURNIN_VOLUME_NAME "BURNIN"
#define VOLUME_TEST_BURNIN 0
#define VOLUME_TEST_SPEED  1

#if defined(CONFIG_MIPS32)
#define TIMER1_ENABLE			0xBF006080
#define TIMER1_HIT				0xBF006084
#define TIMER1_MAX_LOW			0xBF006088
#define TIMER1_MAX_HIGH			0xBF00608C
#define TIMER1_CAP_LOW			0xBF006090
#define TIMER1_CAP_HIGH			0xBF006094
#elif defined(CONFIG_ARM)
#define TIMER1_ENABLE			0x1F006080
#define TIMER1_HIT				0x1F006084
#define TIMER1_MAX_LOW			0x1F006088
#define TIMER1_MAX_HIGH			0x1F00608C
#define TIMER1_CAP_LOW			0x1F006090
#define TIMER1_CAP_HIGH			0x1F006094
#endif

#define REG(Reg_Addr)                       (*(volatile unsigned short*)(Reg_Addr))
#define REG_WRITE_UINT16(reg_addr, val)     REG(reg_addr) = val
#define REG_READ_UINT16(reg_addr, val)      val = REG(reg_addr)
#define REG_SET_BITS_UINT16(reg_addr, val)  REG(reg_addr) |= (val)

#if defined(CONFIG_MIPS32) || defined(CONFIG_ARM)
void DrvHwTimerStart(void)
{
    // reset HW timer
    REG_WRITE_UINT16(TIMER1_MAX_LOW, 0xFFFF);
    REG_WRITE_UINT16(TIMER1_MAX_HIGH, 0xFFFF);
    REG_WRITE_UINT16(TIMER1_ENABLE, 0);

    // start HW timer
    REG_SET_BITS_UINT16(TIMER1_ENABLE, 0x0001);
}

unsigned long DrvHwTimerEnd(void)
{
    unsigned long u32HWTimer = 0;
    unsigned short u16TimerLow = 0;
    unsigned short u16TimerHigh = 0;

    // Get HW timer
    REG_READ_UINT16(TIMER1_CAP_LOW, u16TimerLow);
    REG_READ_UINT16(TIMER1_CAP_HIGH, u16TimerHigh);

    u32HWTimer = (u16TimerHigh<<16) | u16TimerLow;

    return u32HWTimer;
}
#else
void DrvHwTimerStart(void)
{
}

U32 DrvHwTimerEnd(void)
{
	return 0;
}
#endif

int ubi_volume_test(int test_item)
{
	struct ubi_volume *vol = NULL;
	int i;
	size_t size = 0;
	int ret;
	unsigned char *wbuf, *rbuf;
	size_t ShowLogGB;
	unsigned long tick;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol) {
			ret = ubi_remove_vol(vol->name);
		}
	}

	size = ubi->avail_pebs * ubi->leb_size;
	ret = ubi_create_vol(BURNIN_VOLUME_NAME, size, 1);
	if(ret) {
		printf("Can not create BURNIN vol, err=%d!\n", ret);
		return ret;
	}

	vol = ubi_find_volume(BURNIN_VOLUME_NAME);
	if(!vol) {
		printf("%s vol not found\n", BURNIN_VOLUME_NAME);
		return -ENODEV;
	}
		
	wbuf = vmalloc(ubi->leb_size);
	rbuf = vmalloc(ubi->leb_size);
	if (!wbuf || !rbuf) {
		printf("NO MEM\n");
		return -ENOMEM;
	}

	for(i=0 ; i<ubi->leb_size ; i++)
		wbuf[i] = i;
	if(test_item == VOLUME_TEST_BURNIN)
	{
		ShowLogGB = (1024*1024)/(ubi->leb_size/1024);
		size = 0; // total number of LEB r/w
		printf("************** UBI Burn-In Start **************\n");
		printf("Total number of PEB = %u\n", vol->used_ebs);
		printf("LEB size = %u\n", ubi->leb_size);	
		do {
			ret = ubi_eba_unmap_leb(ubi, vol, 0);
			if (ret) {
				printf("unmap err %d\n", ret);
				break;
			}

			ret = ubi_eba_write_leb(ubi, vol, 0, wbuf, 0, ubi->leb_size, UBI_SHORTTERM);
			if (ret) {
				printf("write err %d\n", ret);
				break;
			}

			memset(rbuf, 0, ubi->leb_size);
			ret = ubi_eba_read_leb(ubi, vol, 0, rbuf, 0, ubi->leb_size, 0);
			if (ret) {
				printf("read err %d\n", ret);
				break;
			}

			if(memcmp((const void *) wbuf, (const void *) rbuf, ubi->leb_size) != 0) {
				ret = -EIO;
				printf("compare err %d\n", ret);
				break;
			}

			size++;
			if(size%ShowLogGB == 0) {
				printf("R/W %uGB totally\n", size/ShowLogGB);
			}
		}while(ret == 0);

		printf("R/W %uGB %uMB totally\n", size/ShowLogGB, ((size*1024)/ShowLogGB)-(size/ShowLogGB)*1024);
		printf("************** UBI Burn-In Stop **************\n");	
	}
	else if(test_item == VOLUME_TEST_SPEED)
	{
		printf("************** UBI Test Speed Start **************\n");
		
		ret = ubi_eba_unmap_leb(ubi, vol, 0);
		if (ret) {
			printf("unmap err %d\n", ret);
			goto END_SPEED;
		}
		ret = ubi_wl_flush(ubi);
		if (ret) {
			printf("flush err %d\n", ret);
			goto END_SPEED;
		}		

		DrvHwTimerStart();
		ret = ubi_eba_write_leb(ubi, vol, 0, wbuf, 0, ubi->leb_size, UBI_SHORTTERM);
		if (ret) {
			printf("write err %d\n", ret);
			goto END_SPEED;
		}	
		tick = DrvHwTimerEnd();
		printf("UBI Volume Write(%d KB) = %lu.%lu MB/s\n", ubi->leb_size/1024, (ubi->leb_size*12)/tick, 
			(((ubi->leb_size*12)%tick)*1000)/tick);

		DrvHwTimerStart();
		ret = ubi_eba_read_leb(ubi, vol, 0, rbuf, 0, ubi->leb_size, 0);
		if (ret) {
			printf("read err %d\n", ret);
			goto END_SPEED;
		}
		tick = DrvHwTimerEnd();
		printf("UBI Volume Read(%d KB) = %lu.%lu MB/s\n", ubi->leb_size/1024, (ubi->leb_size*12)/tick, 
			(((ubi->leb_size*12)%tick)*1000)/tick);		

	END_SPEED:
		printf("************** UBI Test Speed Stop **************\n");			
		
	}

	vfree(wbuf);
	vfree(rbuf);

	return ret;
}

#endif

static int do_ubi(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	size_t size = 0;
	ulong addr = 0;
	int err = 0;

	if (argc < 2)
		return cmd_usage(cmdtp);

	if (mtdparts_init() != 0) {
		printf("Error initializing mtdparts!\n");
		return 1;
	}

	if (strcmp(argv[1], "part") == 0) {
		char mtd_dev[16];
		struct mtd_device *dev;
		struct part_info *part;
		const char *vid_header_offset = NULL;
		u8 pnum;
		struct ubi_volume *vol;

		/* Print current partition */
		if (argc == 2) {
			if (!ubi_dev.selected) {
				printf("Error, no UBI device/partition selected!\n");
				return 1;
			}

			printf("Device %d: %s, partition %s\n",
			       ubi_dev.nr, ubi_dev.mtd_info->name, ubi_dev.part_name);
			return 0;
		}

		if (argc < 3)
			return cmd_usage(cmdtp);

#ifdef CONFIG_CMD_UBIFS
		/*
		 * Automatically unmount UBIFS partition when user
		 * changes the UBI device. Otherwise the following
		 * UBIFS commands will crash.
		 */
		if (ubifs_is_mounted())
			cmd_ubifs_umount();
#endif

		/* todo: get dev number for NAND... */
		ubi_dev.nr = 0;

		/*
		 * Call ubi_exit() before re-initializing the UBI subsystem
		 */

		//mstar modify for reducing ubi part effort
		#if 1
		if (ubi_initialized) {
			ubi_exit();
			del_mtd_partitions(ubi_dev.mtd_info);
		}
		#else
		if (ubi_initialized) {
			if(strcmp(argv[2],ubi_dev.part_name)!= 0)
			{
				ubi_exit();
				del_mtd_partitions(ubi_dev.mtd_info);
			}
			else
			{
				printf("Partition %s has been attached, skip attaching process\n", argv[2]);
				return 0;
			}
		}
		#endif

		/*
		 * Search the mtd device number where this partition
		 * is located
		 */
		if (find_dev_and_part(argv[2], &dev, &pnum, &part)) {
			printf("Partition %s not found!\n", argv[2]);
			return 1;
		}
		sprintf(mtd_dev, "%s%d", MTD_DEV_TYPE(dev->id->type), dev->id->num);
		ubi_dev.mtd_info = get_mtd_device_nm(mtd_dev);
		if (IS_ERR(ubi_dev.mtd_info)) {
			printf("Partition %s not found on device %s!\n", argv[2], mtd_dev);
			return 1;
		}

		ubi_dev.selected = 1;

		if (argc > 3)
		#if 1 // MStar
			if ((strcmp(argv[3], "burnin") != 0) && (strcmp(argv[3], "speed") != 0))			
		#endif
			vid_header_offset = argv[3];
		strcpy(ubi_dev.part_name, argv[2]);
		err = ubi_dev_scan(ubi_dev.mtd_info, ubi_dev.part_name,
				vid_header_offset);
		if (err) {
			printf("UBI init error %d\n", err);
			ubi_dev.selected = 0;
			return err;
		}

		ubi = ubi_devices[0];

		#if 1 // MStar
		if (argc > 3 && (strcmp(argv[3], "burnin") == 0) )
			return ubi_volume_test(VOLUME_TEST_BURNIN);
		else if (argc > 3 && (strcmp(argv[3], "speed") == 0) )
			return ubi_volume_test(VOLUME_TEST_SPEED);
		#endif

		vol = ubi_find_volume(last_upd_vol.name);
		if(vol)
			restore_volume(vol);

		return 0;
	}

	if ((strcmp(argv[1], "part") != 0) && (!ubi_dev.selected)) {
		printf("Error, no UBI device/partition selected!\n");
		return 1;
	}

	if (strcmp(argv[1], "info") == 0) {
		int layout = 0;
		if (argc > 2 && !strncmp(argv[2], "l", 1))
			layout = 1;
		return ubi_info(layout);
	}

	if (strncmp(argv[1], "create", 6) == 0) {
		int dynamic = 1;	/* default: dynamic volume */

		/* Use maximum available size */
		size = 0;

		/* E.g., create volume size type */
		if (argc == 5) {
			if (strncmp(argv[4], "s", 1) == 0)
				dynamic = 0;
			else if (strncmp(argv[4], "d", 1) != 0) {
				printf("Incorrect type\n");
				return 1;
			}
			argc--;
		}
		/* E.g., create volume size */
		if (argc == 4) {
			size = simple_strtoul(argv[3], NULL, 16);
			argc--;
		}
		/* Use maximum available size */
		if (!size) {
			size = ubi->avail_pebs * ubi->leb_size;
			printf("No size specified -> Using max size (%u)\n", size);
		}
		/* E.g., create volume */
		if (argc == 3)
			return ubi_create_vol(argv[2], size, dynamic);
	}

	if (strncmp(argv[1], "remove", 6) == 0) {
		/* E.g., remove volume */
		if (argc == 3) {
			ubi_remove_vol(argv[2]);
			return 0;
		}
	}

//MStar start
        if (strncmp(argv[1], "write_cont", 10) == 0) {
            if (argc < 5) {
                printf("Please see usage\n");
                return -EPERM;
            }

            addr = (0 == strncmp(argv[2], UPGRADE_ADDR_STR, strlen(UPGRADE_ADDR_STR))) ? UPGRADE_BUFFER_ADDR : simple_strtoul(argv[2], NULL, 16);
            size = simple_strtoul(argv[4], NULL, 16);
            err=ubi_volume_write_cont(argv[3], (void *)addr, size);
#if defined (CONFIG_BACKUP_PARTITION)
            if(err!=0){
                 printf("setenv updateUBIRPermit NO\n");
                 run_command("setenv updateUBIRPermit NO",0);
                 //run_command("saveenv",0);
            }
#endif
            return err;
        }
//MStar end

	if (strncmp(argv[1], "write", 5) == 0) {
		if (argc < 5) {
			printf("Please see usage\n");
			return 1;
		}

		addr = simple_strtoul(argv[2], NULL, 16);
		size = simple_strtoul(argv[4], NULL, 16);
#if 1 //MStar
            {
                size_t total_size =0;
                if(argc == 6)
                {
                    total_size = simple_strtoul(argv[5], NULL, 16);
                    printf("total size = %d\n", total_size);
                }
                else
                {
                    total_size = size;
                }
                err=ubi_volume_write(argv[3], (void *)addr, size, total_size);
                return err;
            }
#else
		return ubi_volume_write(argv[3], (void *)addr, size);
#endif
	}

        // MStar start
        if(argc == 6)
        {
            if (strncmp(argv[1], "partial_read", 12) == 0)
            {
                size_t partition_offset;
                addr = simple_strtoul(argv[2], NULL, 16);
                size= simple_strtoul(argv[4], NULL, 16);
                partition_offset = simple_strtoul(argv[5], NULL, 16);

                return ubi_volume_partial_read(argv[3], (char *)addr, size ,partition_offset);
            }
        }
        // MStar end

	if (strncmp(argv[1], "read", 4) == 0) {
		size = 0;

		/* E.g., read volume size */
		if (argc == 5) {
			size = simple_strtoul(argv[4], NULL, 16);
			argc--;
		}

		/* E.g., read volume */
		if (argc == 4) {
			addr = simple_strtoul(argv[2], NULL, 16);
			argc--;
		}

		if (argc == 3)
			return ubi_volume_read(argv[3], (char *)addr, size);
	}

    	if (strncmp(argv[1], "reinit", 6) == 0) {
		/* E.g., reinit ubi partition */
		if (argc == 2)
		{
			/*
			 * Call ubi_exit() before re-initializing the UBI subsystem
			 */
			if (ubi_initialized) {
				ubi_exit();
				del_mtd_partitions(ubi_dev.mtd_info);
				ubi_initialized = 0;
				return 0;
			}
		}
	}
		if(strncmp(argv[1], "partial_write", 13) == 0 )
		{
			if(argc == 6)
			{
				ulong off;
				size = simple_strtoul(argv[4], NULL, 16);
				off = simple_strtoul(argv[5], NULL, 16);
				addr = simple_strtoul(argv[2], NULL, 16);
				return ubi_volume_write_offset(argv[3], (void *)addr, size, off);
			}
		}

        if (strncmp(argv[1], "dump", 4) == 0) {
              ulong lebnum = 0, pebnum = 0, dumpoff = 0;
              int     volnum, i, dpret, j;
              struct ubi_volume *vol = NULL, *voltmp = NULL, *volterm = NULL;
              u_char *buf = NULL, *p = NULL;
              if(argc < 4)
                    goto usage;

              volnum = (int)simple_strtoul(argv[2], NULL, 16);
              lebnum = (int)simple_strtoul(argv[3], NULL, 16);
              if(argc > 4)
                    dumpoff = (int)simple_strtoul(argv[4], NULL, 16);
              if((volnum > 0) && (volnum < ubi->vtbl_slots))
                      vol = ubi->volumes[volnum];

              if(vol){
                    printf("Volume %s found at volume id %d\n",
                            vol->name, volnum);
                    goto dump;
              }

              for (i = 0; i < ubi->vtbl_slots; i++) {
                    voltmp = ubi->volumes[i];
                    if (voltmp && (!strcmp(voltmp->name, argv[2]))) {
                            printf("Volume %s found at volume id %d\n",
                                argv[2], voltmp->vol_id);
                            goto dump;
                    }
              }
              printf("volume not found!\n");
              goto usage;

dump:
                if(argc <= 4)
                    dumpoff = 0;

                if(vol)
                    volterm = vol;
                else if(voltmp && (!strcmp(voltmp->name, argv[2])))
                    volterm = voltmp;
                else{
                    printf("volume not found!\n");
                    goto usage;
                    }

                buf = vmalloc(ubi->min_io_size);
                if (!buf) {
                    printf("NO MEM\n");
                    return -ENOMEM;
                }
                pebnum = volterm->eba_tbl[lebnum];
                if(!pebnum)
                {
                     printf("Can not found the corresponding Peb!\n");
                     goto usage;
                }
                printf("lebnum:%ld, pebnum:%ld\n ", lebnum, pebnum);
                dumpoff = ALIGN(dumpoff, ubi->min_io_size);
                dpret = ubi_eba_read_leb(ubi, volterm, lebnum, buf, dumpoff, ubi->min_io_size, 0);
                printf("Page offset in block: 0x%lx\n", dumpoff);
                j = ubi->min_io_size >> 4; p = buf;
                while (j--) {
                    printf( "\t%02x %02x %02x %02x %02x %02x %02x %02x"
                            "  %02x %02x %02x %02x %02x %02x %02x %02x\n",
                            p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7],
                            p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
                    p += 16;
                }
                vfree(buf);
            return dpret == 0 ? 1 : 0;
            }

        if (strncmp(argv[1], "read.e", 6) == 0) {
              ulong lebnum, pebnum, memaddr;
              int     volnum, i, dumplebnum = 0, dpret = 0;
              struct ubi_volume *vol = NULL, *voltmp = NULL, *volterm = NULL;

              if(argc < 5)
                    goto usage;

              memaddr = (int)simple_strtoul(argv[2], NULL, 16);
              volnum = (int)simple_strtoul(argv[3], NULL, 16);
              lebnum = (int)simple_strtoul(argv[4], NULL, 16);

              if(argc > 5)
                      dumplebnum = (int)simple_strtoul(argv[5], NULL, 16);

              if((volnum > 0) && (volnum < ubi->vtbl_slots))
                      vol = ubi->volumes[volnum];

              if(vol){
                    printf("Volume %s found at volume id %d\n",
                            vol->name, volnum);
                    goto readdump;
              }

              for (i = 0; i < ubi->vtbl_slots; i++) {
                    voltmp = ubi->volumes[i];
                    if (voltmp && (!strcmp(voltmp->name, argv[3]))) {
                            printf("Volume %s found at volume id %d\n",
                                argv[2], voltmp->vol_id);
                            goto readdump;
                    }
              }
              printf("volume not found!\n");
              goto usage;

readdump:

                for(i = 0;;i ++){
                        if(vol)
                            volterm = vol;
                        else if(voltmp && (!strcmp(voltmp->name, argv[2])))
                            volterm = voltmp;
                        else{
                            printf("volume not found!\n");
                            goto usage;
                            }
                        pebnum = volterm->eba_tbl[lebnum + i];
                        if(!pebnum)
                        {
                            printf("Can not found the corresponding Peb!\n");
                            continue;
                            }
                        if(!dumplebnum)
                            break;

                        dpret = ubi_eba_read_leb(ubi, volterm, lebnum+i,
                            (u_char*) memaddr, 0, volterm->usable_leb_size, 0);
                        printf("lebnum:%ld, pebnum:%ld\n ", lebnum+i, pebnum);
                        flush_cache(memaddr, volterm->usable_leb_size);

                        if(dumplebnum > 0){
                            --dumplebnum;
                            memaddr += volterm->usable_leb_size;
                            }
                        else
                            break;
                    }

            return dpret == 0 ? 1 : 0;
            }
usage:
	printf("Please see usage\n");
	return 1;
}

U_BOOT_CMD(
	ubi, 6, 1, do_ubi,
	"ubi commands",
	"part [part] [offset | 'burnin' | 'speed']\n"
		" - Show or set current partition (with optional VID"
		" header offset), or burning/speed test\n"
	"ubi info [l[ayout]]"
		" - Display volume and ubi layout information\n"
	"ubi create[vol] volume [size] [type]"
		" - create volume name with size\n"
	"ubi write[vol] address volume size [total_size]"
		" - Write volume from address with size this time, write the left data within total_size with ubi write_cont later\n"
	"ubi write_cont addr vol size"
		" - Write volume from address with size within total_size after 'ubi write'\n"
	"ubi read[vol] address volume [size]"
		" - Read volume to address with size\n"
	"ubi partial_read/paritial_write address volume size offset\n"
		" - Write/Read volume from/to address with offset and size\n"
	"ubi read.e address vol leb [lebnum]"
		" - Read lebnum lebs from leb of vol to address\n"
	"ubi dump vol leb [offset]"
		" - Display data and mapping information from offset of leb, volume vol\n"
	"ubi reinit"
		" - ubi exit\n"
	"ubi remove[vol] volume"
		" - Remove volume\n"
	"[Legends]\n"
	" volume: character name\n"
	" size: specified in bytes\n"
	" type: s[tatic] or d[ynamic] (default=dynamic)"
);
