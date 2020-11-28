//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
#ifndef DRVGPD_H
#define DRVGPD_H

#include "gpd.h"

#define DEFAULT_ALPHA 0xFF


#define FALSE  0
#define TRUE   1

#if 1
extern U32 READBITBASE;
#define read_bits_reg(n) 	(*((volatile unsigned short*)(READBITBASE+((0x10|(n-1))<<2))))
#define show_bits_reg(n) 	(*((volatile unsigned short*)(READBITBASE+((0x20|(n-1))<<2))))
#else
#define READBITBASE1 0xA000543C
#define READBITBASE2 0xA000547C
#define read_bits_reg(n) 	(*((volatile unsigned int*)(READBITBASE1+(n<<2))))
#define show_bits_reg(n) 	(*((volatile unsigned int*)(READBITBASE2+(n<<2))))
#endif

void drv_gpd_set_scaling(unsigned int enable, unsigned int mode);
unsigned int drv_gpd_get_scaling_mode(void);

#if (defined(__arm__))
void drv_eng_always_active(unsigned int value);
#endif

void drv_gpd_png_en(void);
void drv_gpd_gif_en(void);
unsigned short read_bits(int n);
unsigned short show_bits(int n);

unsigned int drv_reg_iofifo_state(void);
void drv_gpd_eco_enable(unsigned int enable);

void drv_gpd_set_zbuf_bas(unsigned int base);
void drv_gpd_set_cbuf_bas(unsigned int base);

void set_nop_cmd(U32 num);

unsigned int drv_gpd_png_state(void);
unsigned int drv_gpd_bitpos(void);
unsigned int drv_gpd_ififo_radr(void);
unsigned int drv_gpd_ififo_empty(void);
unsigned int drv_gpd_ififo_full(void);
unsigned int drv_gpd_ofifo_done(void);
unsigned int drv_gpd_bsadr_full(void);
unsigned int drv_gpd_png_blk_done(void);
unsigned int drv_gpd_png_eob(void);

void drv_gpd_Init(void);
void drv_gpd_set_bstart_end(unsigned int bstart, unsigned int bend);
void drv_gpd_set_ocolor(int ocolor_typ);
void drv_gpd_write_cmap(unsigned int num, unsigned char *ptr, int trans_idx);
//void drv_gpd_write_cmap(unsigned int num, unsigned int *ptr);

void drv_gpd_set_pitch(unsigned int pitch);
void drv_gpd_set_gif_swidth_sheight(unsigned int width ,unsigned int height);
void drv_gpd_set_iwidth_height(unsigned int iwidth, unsigned int iheight);
void drv_gpd_set_istart(unsigned int istart);
void drv_gpd_set_ROI(U32 enable, U32 hstart, U32 vstart, U32 width, U32 height);
void drv_gpd_set_interlace(unsigned char interlace);
void drv_gpd_set_gif_local_map_size(int bpp);

void drv_gpd_set_gif_go(void);
unsigned int drv_gpd_gif_done(void);
void drv_gpd_set_trans(unsigned short r, unsigned short g, unsigned short b, unsigned char enable);
void drv_gpd_set_palette(unsigned char *palette, unsigned short palette_num, unsigned char *trans, unsigned short num_trans);
void drv_gpd_set_pgend(unsigned char pgend);

void drv_gpd_set_frun_cnt(unsigned int frun_cnt);
void drv_gpd_set_iccp_dtsize(unsigned char iccp, unsigned char dtsize);
void drv_gpd_set_type(unsigned char color_type, unsigned char interlace, unsigned char color_depth);
void drv_gpd_set_default_alpha(unsigned char alpha);
void drv_gpd_set_sca_dfa(unsigned char sca, unsigned char dfa);
void drv_gpd_set_ltsize(unsigned short ltsize);

void drv_gpd_set_scline_width_progressive(unsigned int width, unsigned char bpp);
void drv_gpd_set_scline_height_progressive(unsigned int height);
void drv_gpd_set_scline_width_interlace(unsigned int width, unsigned char bpp);
void drv_gpd_set_scline_height_interlace(unsigned int height);

void drv_gpd_set_png_go(void);
void drv_gpd_set_blk_go(void);
void drv_gpd_set_png_done(unsigned int value);
void drv_gpd_set_cmp_type(unsigned char type);

void drv_gpd_set_lbase(unsigned short *lbase);
void drv_gpd_set_dbase(unsigned short *dbase);
void drv_gpd_set_lmincode_valid(unsigned short lmin_valid);
void drv_gpd_set_dmincode_valid(unsigned short dmin_valid);
void drv_gpd_set_lmincode(unsigned short *lmin);
void drv_gpd_set_dmincode(unsigned short *dmin);

void drv_gpd_set_fixed_ldata(void);
void drv_gpd_set_dynamic_ldata(unsigned short num, unsigned short *ldata);
void drv_gpd_set_dynamic_ddata(unsigned short num, unsigned short *ddata);
int drv_gpd_check_engine(void);
void drv_gpd_set_hipri(unsigned short hipri);
void drv_gpd_set_access_region(U32 start, U32 end);
unsigned int drv_gpd_get_clkbase(void);
unsigned int drv_gpd_get_clkoffset(void);
unsigned int is_stb(void);
void drv_gpd_init_outside_reg(U32 BankBaseAddr);
void drv_gpd_init_chip_specific_reg(void);
U8 MDrv_GPD_MIU_Select(U32 u32Addr);
void MDrv_GPD_Reg_Base(U32* u32RIUBase, U32* u32XIUBase);
void MDrv_GPD_MIU_Client(U8* u8Offset, U16* u16BitMask);

// GPD Interrupt Register Function
typedef void (*GPD_IsrFuncCb)(void);

U8 MDrv_GPD_EnableISR(GPD_IsrFuncCb IsrCb);
U8 MDrv_GPD_DisableISR(void);
void MDrv_GPD_SetISRMask(void);
void MDrv_GPD_PrintGPDBuf(void);
void drv_gpd_dbg_dump(void);

#endif

