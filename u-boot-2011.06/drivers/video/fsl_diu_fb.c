/*
 * Copyright 2007, 2010-2011 Freescale Semiconductor, Inc.
 * Authors: York Sun <yorksun@freescale.com>
 *          Timur Tabi <timur@freescale.com>
 *
 * FSL DIU Framebuffer driver
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

#include <common.h>
#include <malloc.h>
#include <asm/io.h>

#include "videomodes.h"
#include <video_fb.h>
#include <fsl_diu_fb.h>

struct fb_var_screeninfo {
	unsigned int xres;		/* visible resolution		*/
	unsigned int yres;

	unsigned int bits_per_pixel;	/* guess what			*/

	/* Timing: All values in pixclocks, except pixclock (of course) */
	unsigned int pixclock;		/* pixel clock in ps (pico seconds) */
	unsigned int left_margin;	/* time from sync to picture	*/
	unsigned int right_margin;	/* time from picture to sync	*/
	unsigned int upper_margin;	/* time from sync to picture	*/
	unsigned int lower_margin;
	unsigned int hsync_len;		/* length of horizontal sync	*/
	unsigned int vsync_len;		/* length of vertical sync	*/
	unsigned int sync;		/* see FB_SYNC_*		*/
	unsigned int vmode;		/* see FB_VMODE_*		*/
	unsigned int rotate;		/* angle we rotate counter clockwise */
};

struct fb_info {
	struct fb_var_screeninfo var;	/* Current var */
	unsigned int smem_len;		/* Length of frame buffer mem */
	unsigned int type;		/* see FB_TYPE_*		*/
	unsigned int line_length;	/* length of a line in bytes    */

	void *screen_base;
	unsigned long screen_size;
};

struct fb_videomode {
	const char *name;	/* optional */
	unsigned int refresh;		/* optional */
	unsigned int xres;
	unsigned int yres;
	unsigned int pixclock;
	unsigned int left_margin;
	unsigned int right_margin;
	unsigned int upper_margin;
	unsigned int lower_margin;
	unsigned int hsync_len;
	unsigned int vsync_len;
	unsigned int sync;
	unsigned int vmode;
	unsigned int flag;
};

#define FB_SYNC_VERT_HIGH_ACT	2	/* vertical sync high active	*/
#define FB_SYNC_COMP_HIGH_ACT	8	/* composite sync high active   */
#define FB_VMODE_NONINTERLACED  0	/* non interlaced */

/* This setting is used for the ifm pdm360ng with PRIMEVIEW PM070WL3 */
static struct fb_videomode fsl_diu_mode_800 = {
	.name		= "800x600-60",
	.refresh	= 60,
	.xres		= 800,
	.yres		= 480,
	.pixclock	= 31250,
	.left_margin	= 86,
	.right_margin	= 42,
	.upper_margin	= 33,
	.lower_margin	= 10,
	.hsync_len	= 128,
	.vsync_len	= 2,
	.sync		= 0,
	.vmode		= FB_VMODE_NONINTERLACED
};

/*
 * These parameters give default parameters
 * for video output 1024x768,
 * FIXME - change timing to proper amounts
 * hsync 31.5kHz, vsync 60Hz
 */
static struct fb_videomode fsl_diu_mode_1024 = {
	.name		= "1024x768-60",
	.refresh	= 60,
	.xres		= 1024,
	.yres		= 768,
	.pixclock	= 15385,
	.left_margin	= 160,
	.right_margin	= 24,
	.upper_margin	= 29,
	.lower_margin	= 3,
	.hsync_len	= 136,
	.vsync_len	= 6,
	.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.vmode		= FB_VMODE_NONINTERLACED
};

static struct fb_videomode fsl_diu_mode_1280 = {
	.name		= "1280x1024-60",
	.refresh	= 60,
	.xres		= 1280,
	.yres		= 1024,
	.pixclock	= 9375,
	.left_margin	= 38,
	.right_margin	= 128,
	.upper_margin	= 2,
	.lower_margin	= 7,
	.hsync_len	= 216,
	.vsync_len	= 37,
	.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.vmode		= FB_VMODE_NONINTERLACED
};

/*
 * These are the fields of area descriptor(in DDR memory) for every plane
 */
struct diu_ad {
	/* Word 0(32-bit) in DDR memory */
	__le32 pix_fmt; /* hard coding pixel format */
	/* Word 1(32-bit) in DDR memory */
	__le32 addr;
	/* Word 2(32-bit) in DDR memory */
	__le32 src_size_g_alpha;
	/* Word 3(32-bit) in DDR memory */
	__le32 aoi_size;
	/* Word 4(32-bit) in DDR memory */
	__le32 offset_xyi;
	/* Word 5(32-bit) in DDR memory */
	__le32 offset_xyd;
	/* Word 6(32-bit) in DDR memory */
	__le32 ckmax_r:8;
	__le32 ckmax_g:8;
	__le32 ckmax_b:8;
	__le32 res9:8;
	/* Word 7(32-bit) in DDR memory */
	__le32 ckmin_r:8;
	__le32 ckmin_g:8;
	__le32 ckmin_b:8;
	__le32 res10:8;
	/* Word 8(32-bit) in DDR memory */
	__le32 next_ad;
	/* Word 9(32-bit) in DDR memory, just for 64-bit aligned */
	__le32 res[3];
} __attribute__ ((packed));

/*
 * DIU register map
 */
struct diu {
	__be32 desc[3];
	__be32 gamma;
	__be32 pallete;
	__be32 cursor;
	__be32 curs_pos;
	__be32 diu_mode;
	__be32 bgnd;
	__be32 bgnd_wb;
	__be32 disp_size;
	__be32 wb_size;
	__be32 wb_mem_addr;
	__be32 hsyn_para;
	__be32 vsyn_para;
	__be32 syn_pol;
	__be32 thresholds;
	__be32 int_status;
	__be32 int_mask;
	__be32 colorbar[8];
	__be32 filling;
	__be32 plut;
} __attribute__ ((packed));

struct diu_addr {
	void *vaddr;		/* Virtual address */
	u32 paddr;		/* 32-bit physical address */
	unsigned int offset;	/* Alignment offset */
};

static struct fb_info info;

/*
 * Align to 64-bit(8-byte), 32-byte, etc.
 */
static int allocate_buf(struct diu_addr *buf, u32 size, u32 bytes_align)
{
	u32 offset, ssize;
	u32 mask;

	ssize = size + bytes_align;
	buf->vaddr = malloc(ssize);
	if (!buf->vaddr)
		return -1;

	memset(buf->vaddr, 0, ssize);
	mask = bytes_align - 1;
	offset = (u32)buf->vaddr & mask;
	if (offset) {
		buf->offset = bytes_align - offset;
		buf->vaddr += offset;
	} else
		buf->offset = 0;

	buf->paddr = virt_to_phys(buf->vaddr);
	return 0;
}

/*
 * Allocate a framebuffer and an Area Descriptor that points to it.  Both
 * are created in the same memory block.  The Area Descriptor is updated to
 * point to the framebuffer memory. Memory is aligned as needed.
 */
static struct diu_ad *allocate_fb(unsigned int xres, unsigned int yres,
				  unsigned int depth, void **fb)
{
	unsigned long size = xres * yres * depth;
	struct diu_addr addr;
	struct diu_ad *ad;
	size_t ad_size = roundup(sizeof(struct diu_ad), 32);

	/*
	 * Allocate a memory block that holds the Area Descriptor and the
	 * frame buffer right behind it.  To keep the code simple, everything
	 * is aligned on a 32-byte address.
	 */
	if (allocate_buf(&addr, ad_size + size, 32) < 0)
		return NULL;

	ad = addr.vaddr;
	ad->addr = cpu_to_le32(addr.paddr + ad_size);
	ad->aoi_size = cpu_to_le32((yres << 16) | xres);
	ad->src_size_g_alpha = cpu_to_le32((yres << 12) | xres);
	ad->offset_xyi = 0;
	ad->offset_xyd = 0;

	if (fb)
		*fb = addr.vaddr + ad_size;

	return ad;
}

int fsl_diu_init(int xres, u32 pixel_format, int gamma_fix)
{
	struct fb_videomode *fsl_diu_mode_db;
	struct diu_ad *ad;
	struct diu *hw = (struct diu *)CONFIG_SYS_DIU_ADDR;
	u8 *gamma_table_base;
	unsigned int i, j;
	struct diu_ad *dummy_ad;
	struct diu_addr gamma;
	struct diu_addr cursor;

	switch (xres) {
	case 800:
		fsl_diu_mode_db = &fsl_diu_mode_800;
		break;
	case 1280:
		fsl_diu_mode_db = &fsl_diu_mode_1280;
		break;
	default:
		fsl_diu_mode_db = &fsl_diu_mode_1024;
	}

	/* The AD struct for the dummy framebuffer and the FB itself */
	dummy_ad = allocate_fb(2, 4, 4, NULL);
	if (!dummy_ad) {
		printf("DIU:   Out of memory\n");
		return -1;
	}
	dummy_ad->pix_fmt = 0x88883316;

	/* read mode info */
	info.var.xres = fsl_diu_mode_db->xres;
	info.var.yres = fsl_diu_mode_db->yres;
	info.var.bits_per_pixel = 32;
	info.var.pixclock = fsl_diu_mode_db->pixclock;
	info.var.left_margin = fsl_diu_mode_db->left_margin;
	info.var.right_margin = fsl_diu_mode_db->right_margin;
	info.var.upper_margin = fsl_diu_mode_db->upper_margin;
	info.var.lower_margin = fsl_diu_mode_db->lower_margin;
	info.var.hsync_len = fsl_diu_mode_db->hsync_len;
	info.var.vsync_len = fsl_diu_mode_db->vsync_len;
	info.var.sync = fsl_diu_mode_db->sync;
	info.var.vmode = fsl_diu_mode_db->vmode;
	info.line_length = info.var.xres * info.var.bits_per_pixel / 8;

	/* Memory allocation for framebuffer */
	info.smem_len =
		info.var.xres * info.var.yres * (info.var.bits_per_pixel / 8);
	ad = allocate_fb(info.var.xres, info.var.yres,
			 info.var.bits_per_pixel / 8, &info.screen_base);
	if (!ad) {
		printf("DIU:   Out of memory\n");
		return -1;
	}

	ad->pix_fmt = pixel_format;

	/* Disable chroma keying function */
	ad->ckmax_r = 0;
	ad->ckmax_g = 0;
	ad->ckmax_b = 0;

	ad->ckmin_r = 255;
	ad->ckmin_g = 255;
	ad->ckmin_b = 255;

	/* Initialize the gamma table */
	if (allocate_buf(&gamma, 256 * 3, 32) < 0) {
		printf("DIU:   Out of memory\n");
		return -1;
	}
	gamma_table_base = gamma.vaddr;
	for (i = 0; i <= 2; i++)
		for (j = 0; j < 256; j++)
			*gamma_table_base++ = j;

	if (gamma_fix == 1) {	/* fix the gamma */
		gamma_table_base = gamma.vaddr;
		for (i = 0; i < 256 * 3; i++) {
			gamma_table_base[i] = (gamma_table_base[i] << 2)
				| ((gamma_table_base[i] >> 6) & 0x03);
		}
	}

	/* Initialize the cursor */
	if (allocate_buf(&cursor, 32 * 32 * 2, 32) < 0) {
		printf("DIU:   Can't alloc cursor data\n");
		return -1;
	}

	/* Program DIU registers */
	out_be32(&hw->diu_mode, 0);	/* Temporarily disable the DIU */

	out_be32(&hw->gamma, gamma.paddr);
	out_be32(&hw->cursor, cursor.paddr);
	out_be32(&hw->bgnd, 0x007F7F7F);
	out_be32(&hw->bgnd_wb, 0);
	out_be32(&hw->disp_size, info.var.yres << 16 | info.var.xres);
	out_be32(&hw->wb_size, 0);
	out_be32(&hw->wb_mem_addr, 0);
	out_be32(&hw->hsyn_para, info.var.left_margin << 22 |
			info.var.hsync_len << 11 |
			info.var.right_margin);

	out_be32(&hw->vsyn_para, info.var.upper_margin << 22 |
			info.var.vsync_len << 11 |
			info.var.lower_margin);

	out_be32(&hw->syn_pol, 0);
	out_be32(&hw->thresholds, 0x00037800);
	out_be32(&hw->int_status, 0);
	out_be32(&hw->int_mask, 0);
	out_be32(&hw->plut, 0x01F5F666);
	/* Pixel Clock configuration */
	diu_set_pixel_clock(info.var.pixclock);

	/* Set the frame buffers */
	out_be32(&hw->desc[0], virt_to_phys(ad));
	out_be32(&hw->desc[1], virt_to_phys(dummy_ad));
	out_be32(&hw->desc[2], virt_to_phys(dummy_ad));

	/* Enable the DIU, set display to all three planes */
	out_be32(&hw->diu_mode, 1);

	return 0;
}

void *video_hw_init(void)
{
	static GraphicDevice ctfb;
	const char *options;
	unsigned int depth = 0, freq = 0;

	if (!video_get_video_mode(&ctfb.winSizeX, &ctfb.winSizeY, &depth, &freq,
				  &options))
		return NULL;

	/* Find the monitor port, which is a required option */
	if (!options)
		return NULL;
	if (strncmp(options, "monitor=", 8) != 0)
		return NULL;

	if (platform_diu_init(ctfb.winSizeX, ctfb.winSizeY, options + 8) < 0)
		return NULL;

	/* fill in Graphic device struct */
	sprintf(ctfb.modeIdent, "%ix%ix%i %ikHz %iHz",
		ctfb.winSizeX, ctfb.winSizeY, depth, 64, freq);

	ctfb.frameAdrs = (unsigned int)info.screen_base;
	ctfb.plnSizeX = ctfb.winSizeX;
	ctfb.plnSizeY = ctfb.winSizeY;

	ctfb.gdfBytesPP = 4;
	ctfb.gdfIndex = GDF_32BIT_X888RGB;

	ctfb.isaBase = 0;
	ctfb.pciBase = 0;
	ctfb.memSize = info.screen_size;

	/* Cursor Start Address */
	ctfb.dprBase = 0;
	ctfb.vprBase = 0;
	ctfb.cprBase = 0;

	return &ctfb;
}
