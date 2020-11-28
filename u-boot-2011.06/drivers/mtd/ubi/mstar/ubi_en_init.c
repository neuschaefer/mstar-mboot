#include <ubi_uboot.h>
#include "../ubi.h"
//#include <linux/kthread.h>
//#include <linux/freezer.h>
#include "../../../mstar/unfd/inc/api/drv_unfd.h"


struct mtd_info * ctrl_mtd;
struct mtd_info * tbl_mtd;
__u8 u8_Partfound;

int update_ctrl_content(struct ubi_device *ubi, __u32 prv_idx, __u32 nxt_idx);

int check_buf_all0xff(__u8 *buf, int len)
{
	int i = len;
	while (--i >= 0)
	{
		if(buf[i]!=0xFF)
			return 0;
	}
	return 1;
}

int dump_tbl_rcd(struct ubi_en_tbl_record etr)
{
	printf("table record\t compact %d\n", etr.compact);
	printf("table record\t copy_flag %d\n", etr.copy_flag);
	printf("table record\t data_crc %X\n", be32_to_cpu(etr.data_crc));
	printf("table record\t data_pad %d\n", be32_to_cpu(etr.data_pad));
	printf("table record\t data_size %d\n", be32_to_cpu(etr.data_size));
	printf("table record\t ec %lld\n", be64_to_cpu(etr.ec));
	printf("table record\t has_vid %d\n", etr.has_vid);
	printf("table record\t image_seq %d\n", be32_to_cpu(etr.image_seq));
	printf("table record\t is_bad %d\n", etr.is_bad);
	printf("table record\t lnum %d\n", be32_to_cpu(etr.lnum));
	printf("table record\t pnum %d\n", be16_to_cpu(etr.pnum));
	printf("table record\t sqnum %lld\n", be64_to_cpu(etr.sqnum));
	printf("table record\t used_ebs %d\n", be32_to_cpu(etr.used_ebs));
	printf("table record\t vol_id %d\n", be32_to_cpu(etr.vol_id));	
	printf("table record\t vol_type %d\n", (etr.vol_type));	
	return 0;
}

int print_buf(__u8 * Buf, int len)
{
	int i;
	for(i=0; i < len; i ++)
	{
		printf("%X ", Buf[i]);
		if((i & 0xF) == 0xF)
			printf("\n");
	}
	return 0;
}
/*
=====================================================
bfind_first_empty_page
=====================================================
find the first empty page in blk_idx-th block by binary search
*/

#if 1
__u32 bfind_first_empty_page(struct ubi_device * ubi, __u32 blk_idx, int blk_page_count)
{
	__u32 p1,p2, pn, ret_idx = blk_idx;
	struct ubi_en_bitmap_hdr *bh = 0;
	int u32_err;
	size_t read;
	__u8 * buf = kmalloc(ctrl_mtd->writesize, GFP_KERNEL);
	if(!buf)
		return -ENOMEM;
	// read first page
	// if(all 0xff) return first page;
	memset(buf, 0xFF, ctrl_mtd->writesize);

	u32_err = ctrl_mtd->read(ctrl_mtd, blk_idx * ctrl_mtd->writesize, 
		ctrl_mtd->writesize, &read, buf);
	
	if(u32_err)
	{
		if (u32_err!= -EUCLEAN)
		{
			eninit_err("read ecc fail");
			ret_idx = -1;
			goto end;
		}
		else
		{
			//handle bitflip
		}
	}
	if(check_buf_all0xff(buf, ctrl_mtd->writesize)) 
	{
		ret_idx = blk_idx;
		goto end;
	}
	// read last page 
	// if(not all 0xff) return 0;
	u32_err = ctrl_mtd->read(ctrl_mtd, (blk_idx + blk_page_count - 1) * ctrl_mtd->writesize, 
		ctrl_mtd->writesize, &read, buf);
	if(u32_err)
	{
		if (u32_err!= -EUCLEAN)
		{
			eninit_err("read ecc fail");
			ret_idx = -1;
			goto end;
		}
		else
		{
			//handle bitflip
		}
	}
	if(!check_buf_all0xff(buf, ctrl_mtd->writesize)) 
	{
		bh = (struct ubi_en_bitmap_hdr*) buf;
		if(be32_to_cpu(bh->magic) != UEBH)
			ret_idx = -1;
		else
			ret_idx = blk_idx + blk_page_count;
		goto end;
	}

	p1 = blk_idx;
	p2 = blk_idx + blk_page_count - 1;
	while( p1 < p2 -1)
	{
		pn = (p1+p2)/2;
		//read page pn
		u32_err = ctrl_mtd->read(ctrl_mtd, pn * ctrl_mtd->writesize, 
		ctrl_mtd->writesize, &read, buf);
		if(u32_err)
		{
			if (u32_err!= -EUCLEAN)
			{
				eninit_err("read ecc fail");
				ret_idx = -1;
				goto end;
			}
			else
			{
				//handle bitflip
			}
		}
		if(check_buf_all0xff(buf, ctrl_mtd->writesize))
			p2 = pn;
		else
		{
			bh = (struct ubi_en_bitmap_hdr*) buf;
			if(be32_to_cpu(bh->magic) != UEBH)
			{
				ret_idx = -1;
				goto end;
			}
			else
				p1 = pn;
		}
	}
	ret_idx = p1 + 1;
end:
	kfree(buf);
	return ret_idx;
}
#endif

/*
=====================================================
update_next_avail_ctrl_page
=====================================================
find the next empty page to write ctrl_page amoung the ctrl storage.
*/

int update_next_avail_ctrl_page(struct ubi_device *ubi)
{
	__u8 *pu8_DataBuf;
	size_t read;
	__u32 err = 0;
	int blk_page_count;
	blk_page_count = (ctrl_mtd->erasesize/ctrl_mtd->writesize);
	ubi->ebr->next_avail_bit_pages ++;

	pu8_DataBuf = kmalloc(ctrl_mtd->writesize, GFP_KERNEL);
	if(!pu8_DataBuf)
		return -ENOMEM;

	memset(pu8_DataBuf, 0xFF, ctrl_mtd->writesize);
	if(ubi->ebr->next_avail_bit_pages >= (ctrl_mtd->size / ctrl_mtd->writesize))
		ubi->ebr->next_avail_bit_pages = 0;

	if((ubi->ebr->next_avail_bit_pages & (blk_page_count - 1)) == 0)
	{
		retry:
		err = ctrl_mtd->block_isbad(ctrl_mtd,
			ubi->ebr->next_avail_bit_pages * ctrl_mtd->writesize);
		if(err > 0)
		{
			eninit_msg("Skip bad block %X",ubi->ebr->next_avail_bit_pages);
			ubi->ebr->next_avail_bit_pages += blk_page_count;
			if(ubi->ebr->next_avail_bit_pages >= (ctrl_mtd->size / ctrl_mtd->writesize))
				ubi->ebr->next_avail_bit_pages = 0;
			if(ubi->ebr->avail_ctrl_blk_num)
				goto retry;	//infinite retry : need to refine
			else
			{
				err = ERR_CTRL_RECORD_NOAVLBLK;
				goto end;
			}
		}
		else if(err < 0)
		{
			err = ERR_CTRL_RECORD_INVALID;
			goto end;
		}

		err = ctrl_mtd->read(ctrl_mtd,
			ubi->ebr->next_avail_bit_pages * ctrl_mtd->writesize, ctrl_mtd->writesize, &read,
			pu8_DataBuf);
		/*
		if(err < 0)
		{
			if(err != -EUCLEAN)
			{
				err = ERR_CTRL_RECORD_INVALID;
				goto end;
			}
			else
			{
				//handle Bitflip
			}
		}
		*/
		
		if(!check_buf_all0xff(pu8_DataBuf, ctrl_mtd->writesize))
		{
			struct erase_info ei;
			memset(&ei, 0, sizeof(struct erase_info));
			ei.mtd = ctrl_mtd;
			ei.addr = (ubi->ebr->next_avail_bit_pages / blk_page_count) 
				* ctrl_mtd->erasesize;
			ei.len = ctrl_mtd->erasesize;
			ei.callback = NULL;
			
			err = ctrl_mtd->erase(ctrl_mtd, &ei);
			
			if(err == -EIO)
			{
				eninit_msg("erase fail at %llX",ei.addr);
				err = ctrl_mtd->block_markbad(ctrl_mtd, 
					(ubi->ebr->next_avail_bit_pages / blk_page_count) 
					* ctrl_mtd->erasesize);
				if(err)
				{
					err = ERR_CTRL_RECORD_INVALID;
					goto end;
				}
				if(ubi->ebr->avail_ctrl_blk_num)
				{
					ubi->ebr->avail_ctrl_blk_num --;
					ubi->ebr->next_avail_bit_pages += blk_page_count;
					if(ubi->ebr->next_avail_bit_pages >= (ctrl_mtd->size / ctrl_mtd->writesize))
						ubi->ebr->next_avail_bit_pages = 0;
					goto retry;
				}
				else
				{
					err = ERR_CTRL_RECORD_NOAVLBLK;
					goto end;
				}
			}
			else if(err != -EIO && err < 0)
			{
				err = ERR_CTRL_RECORD_INVALID;
				goto end;
			}
			
		}

	}
	err = 0;
end:
	kfree(pu8_DataBuf);
	return (int)err;
}

/*
=====================================================
update_next_avail_tbl_page
=====================================================
find the next empty page to write tbl_page amoung the tbl storage.
including handling unclean reboot as updating tbl content.
*/

int update_next_avail_tbl_page(struct ubi_device *ubi)
{
	__u8 *pu8_DataBuf;
	size_t read;
	__u32 err = 0;
	int blk_page_count, powercut = 0;

	pu8_DataBuf = kmalloc(tbl_mtd->writesize, GFP_KERNEL);
	if(!pu8_DataBuf)
		return -ENOMEM;

	memset(pu8_DataBuf, 0xFF, tbl_mtd->writesize);
	blk_page_count = (tbl_mtd->erasesize/tbl_mtd->writesize);
	ubi->ebr->next_avail_tbl_pages += 1;

	if(ubi->ebr->next_avail_tbl_pages >= (tbl_mtd->size / tbl_mtd->writesize))
		ubi->ebr->next_avail_tbl_pages = 0;

	retry:
	if((ubi->ebr->next_avail_tbl_pages & (blk_page_count - 1)) == 0)
	{
		err = tbl_mtd->block_isbad(tbl_mtd, 
			ubi->ebr->next_avail_tbl_pages * tbl_mtd->writesize);
		if(err > 0)
		{
			eninit_msg("Skip bad block %X",ubi->ebr->next_avail_tbl_pages);
			if(ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count])
			{
				ubi->ebr->avail_tbl_blk_num --;
				ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count] = 0;
			}
			ubi->ebr->next_avail_tbl_pages += blk_page_count;
			if(ubi->ebr->next_avail_tbl_pages >= (tbl_mtd->size / tbl_mtd->writesize))
				ubi->ebr->next_avail_tbl_pages = 0;
			if(ubi->ebr->avail_tbl_blk_num)
				goto retry;	//infinite retry : need to refine
			else
			{
				err = ERR_TBL_RECORD_NOAVLBLK;
				goto end;
			}
		}
		else if(err < 0 )
		{
			err = ERR_CTRL_RECORD_INVALID;
			goto end;
		}
	}
		
	err = tbl_mtd->read(tbl_mtd,
		ubi->ebr->next_avail_tbl_pages * tbl_mtd->writesize, tbl_mtd->writesize, &read,
		pu8_DataBuf);

	/*
	if(err < 0)
	{
		if(err != -EUCLEAN)
		{
			err = ERR_CTRL_RECORD_INVALID;
			goto end;
		}
		else
		{
			//handle Bitflip
		}
	}
	*/
		
	if(!check_buf_all0xff(pu8_DataBuf, tbl_mtd->writesize))
	{
		struct erase_info ei;
		if(ubi->ebr->next_avail_tbl_pages & (blk_page_count - 1) 
			|| ubi->ebr->avail_tbl_blk_num == 1)
		{
			int pnum;
			//Next page is not empty -> power cut during update table record
			// invalid all table group
			eninit_msg("power cut, NTP %X, blk_page_count %X",ubi->ebr->next_avail_tbl_pages, blk_page_count );
			ubi->ebr->next_avail_tbl_pages = (ubi->ebr->next_avail_tbl_pages / blk_page_count) * blk_page_count;
			powercut = 1;
			//Next page is not empty -> power cut during update table record
			// invalid all table group
			eninit_msg("invalid all table group");
			memset(ubi->tsm->valid_groups, 0, ubi->tsm->groups_num);
			memset(ubi->ebr->bitmap, 0, ctrl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));
			for(pnum =0; pnum < ubi->peb_count; pnum ++)
			{
				ubi->trn[pnum].rcd_page_idx = -1;
			}
			err = sync_bitmap_storage(ubi);
			if(err)
				goto end;
			//	goto end;
		}
		else
		/*check whether there is a vaild page location in next block for erasure.*/
		{
			int pnum, rcd_page_idx, erase_page_idx, need_sync;
			need_sync = 0;
			erase_page_idx = (ubi->ebr->next_avail_tbl_pages / blk_page_count) * blk_page_count;
			for(pnum =0; pnum < ubi->peb_count; pnum ++)
			{
				rcd_page_idx = ubi->trn[pnum].rcd_page_idx;
				if(erase_page_idx <= rcd_page_idx && 
					(erase_page_idx + blk_page_count) > rcd_page_idx
					)
				{
					need_sync = 1;
					update_ctrl_content(ubi, rcd_page_idx, -1);
				}					
			}
			if(need_sync)
			{
				err = sync_bitmap_storage(ubi);
				if(err)
					goto end;
				powercut = 1;
			}
		}
			
		memset(&ei, 0, sizeof(struct erase_info));
		ei.mtd = tbl_mtd;
		ei.addr = (ubi->ebr->next_avail_tbl_pages / blk_page_count) 
			* tbl_mtd->erasesize;
		ei.len = tbl_mtd->erasesize;
		ei.callback = NULL;

		err = tbl_mtd->erase(tbl_mtd, &ei);

		eninit_msg("avail : %d", ubi->ebr->avail_tbl_blk_num);
		if(err == -EIO)
		{
			err = tbl_mtd->block_markbad(tbl_mtd, 
				(ubi->ebr->next_avail_tbl_pages / blk_page_count) 
				* tbl_mtd->erasesize);
			if(err)
			{
				eninit_msg("mark bad error %d\n", err);
				err = ERR_CTRL_RECORD_INVALID;
				goto end;
			}
			if(ubi->ebr->avail_tbl_blk_num)
			{
				ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count] = 0;
				ubi->ebr->avail_tbl_blk_num --;
				ubi->ebr->next_avail_tbl_pages += blk_page_count;
				if(ubi->ebr->next_avail_tbl_pages >= (tbl_mtd->size / tbl_mtd->writesize))
					ubi->ebr->next_avail_tbl_pages = 0;
				goto retry;
			}
			else
			{
				err = ERR_TBL_RECORD_NOAVLBLK;
				goto end;
			}
		}
		else if(err != -EIO && err < 0)
		{
			err = ERR_CTRL_RECORD_INVALID;
			goto end;
		}
	}


	err = 0;
	if(powercut)
		err = ERR_TBL_RECORD_POWERCUT;
end:
	kfree(pu8_DataBuf);
	return (int)err;
}

/*
=====================================================
find_first_empty_page
=====================================================
find first empty page in blk_idx-th block by linear search
*/

int find_first_empty_page(struct ubi_device * ubi, int blk_idx, int blk_page_count)
{
	int pn, err;
	size_t read;
	
	__u8 * buf = kmalloc(ctrl_mtd->writesize, GFP_KERNEL);
	pn = blk_idx + blk_page_count;
	while(--pn >= blk_idx)
	{
		//read pn
		//addr = (loff_t)pn << ubi->mtd->page_shift;
		//ubi->mtd->read(ubi->mtd, addr, ubi->mtd->writesize, &read, buf);
		err = ctrl_mtd->read(ctrl_mtd, pn / ctrl_mtd->writesize, 
		ctrl_mtd->writesize, &read, buf);
		if(err)
		{
			if(err != -EUCLEAN)
			{
				kfree(buf);
				return -1;
			}
			else
			{
				//handle bitflip
			}
		}
		if(!check_buf_all0xff(buf, ctrl_mtd->writesize))
		{
			kfree(buf);
			return pn+1;
		}
	}
	kfree(buf);
	return blk_idx;
}

int erase_ctrl_blocks(void)
{
	int blk_page_count, err;
	__u32 u32_i, cb_count;
	struct erase_info ei;
	blk_page_count = (ctrl_mtd->erasesize/ctrl_mtd->writesize);
	cb_count = ctrl_mtd->size / ctrl_mtd->writesize;

	for(u32_i = 0; u32_i < cb_count; u32_i += blk_page_count)
	{
		err = ctrl_mtd->block_isbad(ctrl_mtd, u32_i / ctrl_mtd->writesize);
		if(err > 0)
		{
			eninit_msg("Skip bad block %X", u32_i);
			continue;
		}
		else if (err < 0)
		{
			return ERR_CTRL_RECORD_FAIL;
		}
		
		memset(&ei, 0, sizeof(struct erase_info));
		ei.mtd = ctrl_mtd;
		ei.addr = (u32_i / blk_page_count) / ctrl_mtd->erasesize;
		ei.len = ctrl_mtd->erasesize;
		ei.callback = NULL;

		err = ctrl_mtd->erase(ctrl_mtd, &ei);
		if(err == -EIO)
		{
			err = ctrl_mtd->block_markbad(ctrl_mtd, 
					(u32_i / blk_page_count) / ctrl_mtd->erasesize);
			if(err < 0)
				return err;
		}
		else if(err < 0 && err != -EIO)
		{
			return err;
		}

	}
	return 0;	
}

int erase_all_blocks(void)
{
	int blk_page_count, err;
	__u32 u32_i, cb_count;
	struct erase_info ei;

	blk_page_count = (tbl_mtd->erasesize/tbl_mtd->writesize);
	cb_count = tbl_mtd->size / tbl_mtd->writesize;

	for(u32_i = 0; u32_i < cb_count; u32_i += blk_page_count)
	{
		err = tbl_mtd->block_isbad(tbl_mtd, u32_i * tbl_mtd->writesize);
		if(err > 0)
		{
			eninit_msg("Skip bad block %X", u32_i);
			continue;
		}
		else if (err < 0)
		{
			return ERR_CTRL_RECORD_FAIL;
		}
		
		memset(&ei, 0, sizeof(struct erase_info));
		ei.mtd = tbl_mtd;
		ei.addr = (u32_i / blk_page_count) * tbl_mtd->erasesize;
		ei.len = tbl_mtd->erasesize;
		ei.callback = NULL;

		err = tbl_mtd->erase(tbl_mtd, &ei);
		if(err == -EIO)
		{
			err = tbl_mtd->block_markbad(tbl_mtd, 
					(u32_i / blk_page_count) * tbl_mtd->erasesize);
			if(err < 0)
				return err;
		}
		else if(err < 0 && err != -EIO)
		{
			return err;
		}
	}

	blk_page_count = (ctrl_mtd->erasesize/ctrl_mtd->writesize);
	cb_count = ctrl_mtd->size / ctrl_mtd->writesize;

	for(u32_i = 0; u32_i < cb_count; u32_i += blk_page_count)
	{
		err = ctrl_mtd->block_isbad(ctrl_mtd, u32_i * ctrl_mtd->writesize);
		if(err > 0)
		{
			eninit_msg("Skip bad block %X", u32_i);
			continue;
		}
		else if (err < 0)
		{
			return ERR_CTRL_RECORD_FAIL;
		}
		
		memset(&ei, 0, sizeof(struct erase_info));
		ei.mtd = ctrl_mtd;
		ei.addr = (u32_i / blk_page_count) * ctrl_mtd->erasesize;
		ei.len = ctrl_mtd->erasesize;
		ei.callback = NULL;

		err = ctrl_mtd->erase(ctrl_mtd, &ei);
		if(err == -EIO)
		{
			err = ctrl_mtd->block_markbad(ctrl_mtd, 
					(u32_i / blk_page_count) * ctrl_mtd->erasesize);
			if(err < 0)
				return err;
		}
		else if(err < 0 && err != -EIO)
		{
			return err;
		}
			
	}
	return 0;
}

/*
=====================================================
process_ctrl_record
=====================================================
find newest ctrl records in ctrl storage
*/

int process_ctrl_record(struct ubi_device *ubi, __u8 * pu8_DataBuf)
{
	int  bitmap_block = -1, blk_page_count, is_valid = 0;
	size_t read;
	__u64 seq = 0;
	__u32 cb_count, err = 0, first_empty, bitmap_page = 0, i, next_tbl_page = 0;
	struct ubi_en_bitmap_hdr *bh = 0;
	struct ubi_en_bitmap_record * ebr = ubi->ebr;

	blk_page_count = (tbl_mtd->erasesize/tbl_mtd->writesize);
	cb_count = tbl_mtd->size / tbl_mtd->writesize;
	ebr->avail_tbl_blk_num = cb_count / blk_page_count;
	
	blk_page_count = (ctrl_mtd->erasesize/ctrl_mtd->writesize);
	cb_count = ctrl_mtd->size / ctrl_mtd->writesize;
	ebr->avail_ctrl_blk_num = cb_count /blk_page_count;
	
	memset(pu8_DataBuf, 0xFF, ctrl_mtd->writesize);

	for(i = 0; i < cb_count; i += blk_page_count)
	{
		err = ctrl_mtd->block_isbad(ctrl_mtd, i * ctrl_mtd->writesize);
		if(err > 0)
		{
			eninit_msg("Skip bad block %X", i);
			ebr->avail_ctrl_blk_num --;
			continue;
		}
		else if (err < 0)
		{
			memset(pu8_DataBuf, 0, ctrl_mtd->writesize);
			ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
			ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
			ebr->bh->sqnum =  cpu_to_be64(seq + 1);
			ebr->next_avail_bit_pages = -1;
			update_next_avail_ctrl_page(ubi);
			ebr->next_avail_tbl_pages = -1;
			update_next_avail_tbl_page(ubi);
			return ERR_CTRL_RECORD_FAIL;
		}

		first_empty = bfind_first_empty_page(ubi, i, blk_page_count);
		//eninit_msg("first_empty: %X\n",first_empty);
		if((int)first_empty < 0)	// ecc fail
		{
			erase_all_blocks();
			//err = ctrl_mtd->block_markbad(ctrl_mtd, 
			//		(i / blk_page_count) << ctrl_mtd->erasesize_shift);
			memset(pu8_DataBuf, 0, ctrl_mtd->writesize);
			ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
			ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
			ebr->bh->sqnum =  cpu_to_be64(seq + 1);
			ebr->next_avail_bit_pages = -1;
			update_next_avail_ctrl_page(ubi);
			ebr->next_avail_tbl_pages = -1;
			update_next_avail_tbl_page(ubi);

			return ERR_CTRL_RECORD_FAIL;
		}
		if( first_empty == i)
			continue;
		//read first_empty -1;
		err = ctrl_mtd->read(ctrl_mtd, (first_empty - 1) * ctrl_mtd->writesize, 
			ctrl_mtd->writesize, &read, pu8_DataBuf);
		if(err)
		{
			if(err != -EUCLEAN)	//ecc fail
			{
				erase_all_blocks();
				//err = ctrl_mtd->block_markbad(ctrl_mtd, 
				//	((first_empty - 1) / blk_page_count) << ctrl_mtd->erasesize_shift);
				eninit_msg("read fail at %X",(first_empty - 1) * ctrl_mtd->writesize);
				memset(pu8_DataBuf, 0, ctrl_mtd->writesize);
				ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
				ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
				ebr->bh->sqnum =  cpu_to_be64(seq + 1);
				ebr->next_avail_bit_pages = -1;
				update_next_avail_ctrl_page(ubi);
				ebr->next_avail_tbl_pages = -1;
				update_next_avail_tbl_page(ubi);

				return ERR_CTRL_RECORD_FAIL;
			}
			else
			{
				//handle bit flip
			}
		}
		
		
		bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
		if(be32_to_cpu(bh->magic) != UEBH)
		{
			erase_all_blocks();
			//err = ctrl_mtd->block_markbad(ctrl_mtd, 
			//		(i / blk_page_count) << ctrl_mtd->erasesize_shift);
			memset(pu8_DataBuf, 0, ctrl_mtd->writesize);
			ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
			ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
			ebr->bh->sqnum =  cpu_to_be64(seq + 1);
			ebr->next_avail_bit_pages = -1;
			update_next_avail_ctrl_page(ubi);
			ebr->next_avail_tbl_pages = -1;
			update_next_avail_tbl_page(ubi);
			return ERR_CTRL_RECORD_FAIL;
		}

		if(bitmap_block == -1 || seq < be64_to_cpu(bh->sqnum))
		{
			bitmap_block = i;
			bitmap_page = first_empty - 1;
			seq = be64_to_cpu(bh->sqnum);
			//parse next_tbl_page to next_tbl_page
			next_tbl_page = be32_to_cpu(bh->next_tbl_page);
			is_valid = 1;
		}
	}

	if(ebr->avail_ctrl_blk_num == 0)
	{
		eninit_msg("No available ctrl block, disable speed up ubi initial");
		ubi->tsm->disable_flag = 1;
		return ERR_CTRL_RECORD_NOAVLBLK;
	}
	
	if(bitmap_block != -1)
	{
		eninit_msg("Have Bitmap\n");
		err = ctrl_mtd->read(ctrl_mtd, (bitmap_page) * ctrl_mtd->writesize, 
			ctrl_mtd->writesize, &read, pu8_DataBuf);
		//print_buf(pu8_DataBuf, ctrl_mtd->writesize);
		if(err)
		{
			if(err != -EUCLEAN)
			{
				erase_all_blocks();
				//err = ctrl_mtd->block_markbad(ctrl_mtd, 
				//	((bitmap_page) / blk_page_count) << ctrl_mtd->erasesize_shift);
				memset(pu8_DataBuf, 0, ctrl_mtd->writesize);
				ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
				ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
				ebr->bh->sqnum =  cpu_to_be64(seq + 1);
				ebr->next_avail_bit_pages = -1;
				update_next_avail_ctrl_page(ubi);
				ebr->next_avail_tbl_pages = -1;
				update_next_avail_tbl_page(ubi);

			return ERR_CTRL_RECORD_FAIL;
		}
			else
			{
				//handle bit flip
			}
		}
		
		ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
		ebr->bh->sqnum =  cpu_to_be64(seq + 1);
		ebr->next_avail_bit_pages = bitmap_page;
		update_next_avail_ctrl_page(ubi);
		ebr->next_avail_tbl_pages = next_tbl_page - 1;
		ebr->is_valid = is_valid;
		ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
		//print_buf(pu8_DataBuf, ctrl_mtd->writesize);
		eninit_msg("seq:%lld NTP:%X\n", be64_to_cpu(ebr->bh->sqnum), be32_to_cpu(ebr->bh->next_tbl_page));
		if(is_valid)
			return ERR_CTRL_RECORD_FOUND;
		return ERR_CTRL_RECORD_INVALID;
	}
	else
	{
		eninit_msg("Have no Bitmap\n");
		memset(pu8_DataBuf, 0, ctrl_mtd->writesize);
		ebr->bh = (struct ubi_en_bitmap_hdr*) pu8_DataBuf;
		ebr->bitmap = (__u8*) (pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr));
		ebr->bh->sqnum =  cpu_to_be64(seq + 1);
		ebr->next_avail_bit_pages = -1;
		update_next_avail_ctrl_page(ubi);
		ebr->next_avail_tbl_pages = -1;
		update_next_avail_tbl_page(ubi);
		ebr->is_valid = 0;
	}
	return ERR_CTRL_RECORD_NOFOUND;
}

/*
=====================================================
process_valid_tbl_record
=====================================================
parse ctrl record for valid table record index
pass the record content to process_tbl_page function
*/

int process_valid_tbl_record(struct ubi_device *ubi, struct ubi_scan_info *si, struct ubi_en_bitmap_record *ebr)
{
	int i, j, v, pagecount, total_tbl_page, blk_page_count;
	__u8 tmp, *pu8_DataBuf;
	size_t read;
	__u32 err= 0, err2 = 0, page_idx;
	total_tbl_page = tbl_mtd->size / tbl_mtd->writesize;
	blk_page_count = tbl_mtd->erasesize/tbl_mtd->writesize;
	pagecount = 0;

	pu8_DataBuf = kmalloc(tbl_mtd->writesize, GFP_KERNEL);
	if(!pu8_DataBuf)
	{
		return -ENOMEM;
	}
	for(i = 0; i < tbl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr); i ++)
	{
		//according to the bitmap
		tmp = ebr->bitmap[i];
		for(j = 7; j >= 0 ; j --)
		{
			if(pagecount > total_tbl_page)
				goto end;
			v = ((tmp >> j) & 1);
			if(v)
			{
				page_idx = (i*8) + 7 - j;

				eninit_msg("read table page %X\n",page_idx);
				//read the valid page from nand
				//if read ecc fail -> return to original ubi scan				
				err = tbl_mtd->read(tbl_mtd, page_idx * tbl_mtd->writesize, 
					tbl_mtd->writesize, &read, pu8_DataBuf);
				if((int)err < 0)
				{
					if((int)err != -EUCLEAN)	//ecc fail
					{
						erase_all_blocks();
						memset(ubi->ebr->bitmap, 0, ctrl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));
						ebr->next_avail_bit_pages = -1;
						update_next_avail_ctrl_page(ubi);
						ebr->next_avail_tbl_pages = -1;
						eninit_err("read page ecc fail idx: %X\n", page_idx);
						err = ERR_CTRL_RECORD_FAIL;
						goto end;
					}
					else
					{
						err = 0;
						//handle bitflip
					}
				}
				
				//read page
				//if(ecc fail)
				//	return -1;
				
				//transfer buffer to process_record_page
				
				err = process_tbl_page(ubi, si, pu8_DataBuf, page_idx);
				if((int) err < 0)
				{
					erase_all_blocks();
					memset(ubi->ebr->bitmap, 0, ctrl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));
					ebr->next_avail_bit_pages = -1;
					update_next_avail_ctrl_page(ubi);
					ebr->next_avail_tbl_pages = -1;
					err = ERR_CTRL_RECORD_FAIL;
					goto end;
				}
			}
			pagecount ++;
		}
	}
end:
	err2 = update_next_avail_tbl_page(ubi);
	if(err2 == ERR_TBL_RECORD_POWERCUT)
	{
		eninit_err("Power Cut\n");
		err2 = 0;
	}
	eninit_msg("NTP : %X", ubi->ebr->next_avail_tbl_pages);
	kfree(pu8_DataBuf);
	return (err | err2);

}

/*
=====================================================
update_ctrl_content
=====================================================
update the ctrl record content 
unset prv_idx bit and set nxt_idx bit
*/

int update_ctrl_content(struct ubi_device *ubi, __u32 prv_idx, __u32 nxt_idx)
{
	struct ubi_en_bitmap_record*ebr;
	int prv_shift, nxt_shift;
	ebr = ubi->ebr;
	
	if(prv_idx != 0xffffffff)
	{
		prv_shift = prv_idx & 0x7;
		ubi_assert(prv_idx >= 0 && prv_idx < (tbl_mtd->size / tbl_mtd->writesize));
		prv_idx -= 0;
		ebr->bitmap[prv_idx/8]&= ~(1 << (7 - prv_shift));
	}
	if(nxt_idx != 0xffffffff)
	{
		nxt_shift = nxt_idx & 0x7;
		ubi_assert(nxt_idx >= 0 && nxt_idx < (tbl_mtd->size / tbl_mtd->writesize));
		nxt_idx -= 0;
		ebr->bitmap[nxt_idx/8]|= (1 << (7 - nxt_shift));
	}
	return 0;
}

/*
=====================================================
sync_dirty_tbl_storage
=====================================================
sync dirty table to nand, if all sync is set, all table records should be sync to nand 
*/
int sync_dirty_tbl_storage(struct ubi_device *ubi, int all_sync)
{
	//update all table records
	int j, i, k, n, off1, off2, end_idx, blk_page_count;
	__u32 err = 0, pre_page_idx = 0;
	size_t written;
	__u16 pnum;
	__u8 * pu8_DataBuf;
	struct tbl_storage_manager *tsm = ubi->tsm;
	pu8_DataBuf = kzalloc(tbl_mtd->writesize, GFP_KERNEL);
	if(!pu8_DataBuf)
		return -ENOMEM;

	blk_page_count = tbl_mtd->erasesize / tbl_mtd->writesize;
	n = tbl_mtd->writesize / (sizeof(struct ubi_en_tbl_record) + 2);

retry:
	
	for(j = 0; j < tsm->groups_num; j ++)
	{
		if(!tsm->valid_groups[j] || all_sync)
		{
			eninit_msg("write group %d",j);
			//sync dirty table storage
			off1 = 0;
			off2 = n *2;
			memset(pu8_DataBuf + n * 2, 0, tbl_mtd->writesize - (n * 2));
			memset(pu8_DataBuf, 0xFF, n * 2);
			end_idx = ((j + 1) * n >= ubi->peb_count)? ubi->peb_count : (j + 1) * n;
			for(i = j * n ; i < end_idx ; i ++)
			{
				pnum = (__u16)i;
				memcpy(pu8_DataBuf + off1, (__u8*) &pnum , 2);
				memcpy(pu8_DataBuf + off2, (__u8*) &ubi->trn[i].etr , sizeof(struct ubi_en_tbl_record));
				pre_page_idx = ubi->trn[i].rcd_page_idx;
				off1 += 2;
				off2 += sizeof(struct ubi_en_tbl_record);
				if(off2 >= tbl_mtd->writesize  || off1 >= n *2)
				{
					err = tbl_mtd->write(tbl_mtd, ubi->ebr->next_avail_tbl_pages * tbl_mtd->writesize, 
						tbl_mtd->writesize, &written, pu8_DataBuf);
					if(err)
					{
						tbl_mtd->block_markbad(tbl_mtd, (ubi->ebr->next_avail_tbl_pages/blk_page_count) 
							* tbl_mtd->erasesize);
						if(ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count])
						{
							ubi->ebr->avail_tbl_blk_num --;
							ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count] = 0;
						}
						if(!ubi->ebr->avail_tbl_blk_num)
						{
							eninit_msg("Run out of available block");
							kfree(pu8_DataBuf);
							err = ERR_TBL_RECORD_NOAVLBLK;
							return (int)err;
						}
						ubi->ebr->next_avail_tbl_pages = (ubi->ebr->next_avail_tbl_pages/blk_page_count + 1) * blk_page_count - 1; 
						err = update_next_avail_tbl_page(ubi);
						if(err)
						{
							if(err == ERR_TBL_RECORD_POWERCUT)
								goto retry;
							else
							{
								eninit_msg("Update table page fail");
								kfree(pu8_DataBuf);
								return (int)err;
							}
						}
						memset(tsm->valid_groups, 0, ubi->tsm->groups_num);
						memset(ubi->ebr->bitmap, 0, ctrl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));					
						goto retry;
					}
					for(k = j * n ; k < end_idx ; k ++)
						ubi->trn[k].rcd_page_idx = ubi->ebr->next_avail_tbl_pages;
					
					memset(pu8_DataBuf + n * 2, 0, tbl_mtd->writesize - (n * 2));
					memset(pu8_DataBuf, 0xFF, n * 2);
					//update bitmap records
					update_ctrl_content(ubi, pre_page_idx, ubi->ebr->next_avail_tbl_pages);
					err = update_next_avail_tbl_page(ubi);
					if(err)
					{
						if(err == ERR_TBL_RECORD_POWERCUT)
							goto retry;
						else
						{
							eninit_msg("Update table page fail");
							kfree(pu8_DataBuf);
							return (int)err;
						}
					}
					off1 = 0;
					off2 = n *2;
				}				
			}

			if(off1)
			{
				//write pu8_Databuf to nand				
				err = tbl_mtd->write(tbl_mtd, ubi->ebr->next_avail_tbl_pages * tbl_mtd->writesize, 
						tbl_mtd->writesize, &written, pu8_DataBuf);
				if(err)
				{
					tbl_mtd->block_markbad(tbl_mtd, (ubi->ebr->next_avail_tbl_pages/blk_page_count) 
							* tbl_mtd->erasesize);
					//point to the end of current block
					if(ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count])
					{
						ubi->ebr->avail_tbl_blk_num --;
						ubi->tsm->val_tbl_blk[(ubi->ebr->next_avail_tbl_pages) / blk_page_count] = 0;
					}
					if(!ubi->ebr->avail_tbl_blk_num)
					{
						eninit_msg("Run out of available block");
						err = ERR_TBL_RECORD_NOAVLBLK;
						kfree(pu8_DataBuf);
						return (int)err;
					}
					ubi->ebr->next_avail_tbl_pages = (ubi->ebr->next_avail_tbl_pages/blk_page_count + 1) * blk_page_count - 1; 
					err = update_next_avail_tbl_page(ubi);
					if(err)
					{
						if(err == ERR_TBL_RECORD_POWERCUT)
							goto retry;
						else
						{
							eninit_msg("Update table page fail");
							kfree(pu8_DataBuf);
							return (int)err;
						}
					}
					memset(tsm->valid_groups, 0, ubi->tsm->groups_num);
					memset(ubi->ebr->bitmap, 0, ctrl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));					
					goto retry;
				}
				//update bitmap records
				for(k = j * n ; k < end_idx ; k ++)
					ubi->trn[k].rcd_page_idx = ubi->ebr->next_avail_tbl_pages;
				
				update_ctrl_content(ubi, pre_page_idx, ubi->ebr->next_avail_tbl_pages);
				//ubi->ebr->next_avail_tbl_pages ++;
				err = update_next_avail_tbl_page(ubi);
				if(err)
				{
					if(err == ERR_TBL_RECORD_POWERCUT)
						goto retry;
					else
					{
						eninit_msg("Update table page fail");
						kfree(pu8_DataBuf);
						return (int)err;
					}
				}
			}
			//while(1);  //test for power cut
		}
	}

	for(j = 0; j < tsm->groups_num; j ++)
	{
		if(!tsm->valid_groups[j] || all_sync)
		{
			tsm->valid_groups[j]= 1;
			tsm->dirty_pages[j] = 0;
		}
	}
	kfree(pu8_DataBuf);
	return 0;
}

/*
=====================================================
sync_bitmap_storage
=====================================================
sync bitmap(ctrl record) to nand
*/
int sync_bitmap_storage(struct ubi_device *ubi)
{
	//write back newest bitmap records
	int blk_page_count;
	__u8* pu8_DataBuf;
	size_t written;
	__u32 err = 0, page_idx;
	//struct ubi_en_bitmap_hdr *ebh;
	
	pu8_DataBuf = kzalloc(ctrl_mtd->writesize, GFP_KERNEL);
	if(!pu8_DataBuf)
		return -ENOMEM;

	blk_page_count = ctrl_mtd->erasesize/ctrl_mtd->writesize;
retry:	
	page_idx = ubi->ebr->next_avail_bit_pages;
	
	ubi->ebr->bh->next_tbl_page = cpu_to_be32(ubi->ebr->next_avail_tbl_pages);
	ubi->ebr->bh->magic = cpu_to_be32(UEBH);

	eninit_msg("Magic %X, Seq %lld NTP %X", cpu_to_be32(ubi->ebr->bh->magic),cpu_to_be64(ubi->ebr->bh->sqnum), cpu_to_be32(ubi->ebr->bh->next_tbl_page));
	memcpy(pu8_DataBuf, (__u8*) &(ubi->ebr->bh->magic), sizeof(__be32));
	memcpy(pu8_DataBuf + sizeof(__be32), (__u8*) &(ubi->ebr->bh->sqnum), sizeof(__be64));
	memcpy(pu8_DataBuf + sizeof(__be32) +  sizeof(__be64), (__u8*) &(ubi->ebr->bh->next_tbl_page), sizeof(__be32));
	memcpy(pu8_DataBuf + sizeof(struct ubi_en_bitmap_hdr), ubi->ebr->bitmap, ctrl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));
	err = ctrl_mtd->write(ctrl_mtd, page_idx * ctrl_mtd->writesize, ctrl_mtd->writesize, &written, pu8_DataBuf);
	if(err)
	{
		ctrl_mtd->block_markbad(ctrl_mtd, (page_idx/blk_page_count) * ctrl_mtd->erasesize);
		ubi->ebr->avail_ctrl_blk_num --;
		ubi->ebr->next_avail_bit_pages = (ubi->ebr->next_avail_bit_pages/blk_page_count + 1) * blk_page_count - 1; 
		err = update_next_avail_ctrl_page(ubi);
		if(err)
		{
			eninit_err("update ctrl page fail err: %X", err);
			kfree(pu8_DataBuf);
			return err;
		}
		else
			goto retry;
	}
	//print_buf(pu8_DataBuf, ubi->mtd->writesize);

	err = update_next_avail_ctrl_page(ubi);
	if(err)
	{
		eninit_err("update ctrl page fail err: %X", err);
		kfree(pu8_DataBuf);
		return err;
	}
	spin_lock(&ubi->tsm->ctrl_lock);
	ubi->ebr->bh->sqnum =  cpu_to_be64(be64_to_cpu(ubi->ebr->bh->sqnum) + 1);
	spin_unlock(&ubi->tsm->ctrl_lock);
	//check if sqnum is overflow
	if(be64_to_cpu(ubi->ebr->bh->sqnum) >= ENINIT_MAX_SQNUM)
	{
		printk("UBI EN_INIT WARNING: CTRL storage Sqnum is overflow\n");
		spin_lock(&ubi->tsm->ctrl_lock);
		ubi->ebr->bh->sqnum =  cpu_to_be64(1);
		spin_unlock(&ubi->tsm->ctrl_lock);
		erase_all_blocks();
		ubi->ebr->next_avail_bit_pages = -1;
		err = update_next_avail_ctrl_page(ubi);
		if(err)
		{
			eninit_err("update ctrl page fail err: %X", err);
			kfree(pu8_DataBuf);
			return err;
		}
		ubi->ebr->next_avail_tbl_pages = -1;
		err = update_next_avail_tbl_page(ubi);
		if(err)
		{
			eninit_err("update tbl page fail err: %X", err);
			kfree(pu8_DataBuf);
			return err;
		}
		eninit_msg("invalid all table group");
		memset(ubi->tsm->valid_groups, 0, ubi->tsm->groups_num);
		memset(ubi->ebr->bitmap, 0, tbl_mtd->writesize - sizeof(struct ubi_en_bitmap_hdr));
		goto retry;
	}
	
	//ebh = (struct ubi_en_bitmap_hdr* )pu8_DataBuf;

	//eninit_msg("Seq %lld NTP %X", cpu_to_be64(ebh->sqnum), cpu_to_be32(ebh->next_tbl_page));

	kfree(pu8_DataBuf);
	return 0;
}

/*
=====================================================
check_set_dirty_group
=====================================================
check or set the group, which pnum belongs to, dirty.
*/
int check_set_dirty_group(struct ubi_device *ubi, int pnum)
{
	struct tbl_storage_manager *tsm = ubi->tsm;
	int group, err = 0;
	__u32 prv_idx = 0;

	group = pnum / tsm->tbl_rcds_num;

	mutex_lock(&tsm->tbl_work_sem);

	prv_idx = ubi->trn[pnum].rcd_page_idx;

	if(tsm->valid_groups[group])
	{
		tsm->valid_groups[group] = 0;
		eninit_msg("group %d is mark dirty, prv_idx: %x", group, prv_idx);
		
		update_ctrl_content(ubi, prv_idx, -1);
		if(prv_idx != -1)
		{
			err = sync_bitmap_storage(ubi);
			if(err)
			{
				erase_all_blocks();
				tsm->disable_flag = 1;
				goto end;
			}
		}
	}
	else
	{
		tsm->dirty_pages[group] ++;

		update_ctrl_content(ubi, prv_idx, -1);
		
		if(tsm->dirty_pages[group] > tsm->tbl_rcds_num)
		{
			eninit_msg("trigger dirty write back");
			ubi_dirty_write_back(ubi);
		}
		eninit_msg("group %d is already dirty, dirty pages num is %d",group, tsm->dirty_pages[group]); 
	}
end:
	mutex_unlock(&tsm->tbl_work_sem);
	return err;
	
}

extern struct mtd_info * __init open_mtd_device(const char *mtd_dev);
int en_init(void)
{
	int err = 0;
	u8_Partfound = 0;
	ctrl_mtd = open_mtd_device("CTRL");
	if(IS_ERR(ctrl_mtd))
	{
		printk("Can't find \"CTRL\" partition\n");
		err = PTR_ERR(ctrl_mtd);
		return err;
	}
	tbl_mtd = open_mtd_device("TBL");
	if(IS_ERR(tbl_mtd))
	{
		printk("Can't find \"TBL\" partition\n");
		err = PTR_ERR(tbl_mtd);
		put_mtd_device(ctrl_mtd);
		return err;
	}
	u8_Partfound = 1;
	return err;
}

int en_exit(void)
{
	if(u8_Partfound)
	{
		put_mtd_device(ctrl_mtd);
		put_mtd_device(tbl_mtd);
	}
return 0;
}

