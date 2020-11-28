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

#include <MsTypes.h>
#include <common.h>
#include <command.h>
#include <config.h>
#include "../../stdio.h"
#include <gop/MsDrvGop.h>
#include <apiGOP.h>
#include <MsOS.h>
#include "MsApiGEGOP.h"
#include <MsApiPanel.h>
#include <MsSystem.h>
#include "uboot_mmap.h"
#include "LoaderCharset.h"
#include "LoaderCharset_Eng.h"
#include <MsDebug.h>

#define ASC_CHAR_TABLE      LoaderEngCharacterset
#define ASC_FONT_TABLE      LoaderEngFont
#define CHAR_WIDTH_TABLE    LoaderEngWidthData

#define UNI_CHAR_TABLE      LoaderCharacterset
#define UNI_FONT_TABLE      LoaderChineseFont

#define ASC_CHAR_ARRAY      EngFont24X32
#define UNI_CHAR_ARRAY      Font24X24

#define ONE_CHAR_WIDTH      24
#define ONE_CHAR_HEIGHT     24
#define EACH_CHAR_INTERVAL  2
#define SPACE_WIDTH         20
#define PROGRESS_NUM        32
#define PROGRESS_WIDTH      10
#define PROGRESS_INTERVAL   4
#define CANVAS_WIDTH        720
#define CANVAS_HEIGHT       576
#define ENABLE_FRC_OSD 0

extern U8 u8FbId,u8GwinId;
extern U8 u8OsdLayerFbId,u8OsdLayerGwinId;
extern U16 u16OsdW,u16OsdH;

static MS_U32 u32FontBitMask[] =
{
    0x80000000, 0x40000000, 0x20000000, 0x10000000,
    0x08000000, 0x04000000, 0x02000000, 0x01000000,
    0x00800000, 0x00400000, 0x00200000, 0x00100000,
    0x00080000, 0x00040000, 0x00020000, 0x00010000,
    0x00008000, 0x00004000, 0x00002000, 0x00001000,
    0x00000800, 0x00000400, 0x00000200, 0x00000100
};
//for new font small and large
static MS_U8 u8FontBitMask[] =
{
	0x80,
	0x40,
	0x20,
	0x10,
	0x08,
	0x04,
	0x02,
	0x01
};
static MS_U8 font_size_table[8][4] =
{
	{32,32,32,2},
	{16,16,16,2}
};
const unsigned char *CharTable[8]=
	{
		LoaderEngFont,
		LoaderEngFont_small
	};
const unsigned char *FontWidthTable[8] =
	{
		LoaderEngWidthData,
		LoaderEngWidthData_small
	};
MS_U8 using_font = font32X32;
FontInfo font_info= {0};
static unsigned char Font16X16[32] = {0};//16X16
static unsigned char Font32X32[128] = {0};//32X32
static unsigned char Font24X24[72] = {0};//24X24
//static unsigned int EngFont24X32[24] = {0};//24X32

static MS_BOOL GetFontInfo(FontInfo *pFontInfo,MS_U8 using_font )
{
	if(using_font > font_max || font_max < 0 )
		{
			printf("Error: This font is out of range !\n");
			return false;
		}
	if(pFontInfo == NULL)
		{
			printf("Error: NULL Pointer \n");
			return false;
		}

	pFontInfo->font_width= font_size_table[using_font][0];
	pFontInfo->font_height= font_size_table[using_font][1];
	pFontInfo->space_width= font_size_table[using_font][2];
	pFontInfo->interval_width= font_size_table[using_font][3];
	pFontInfo->pCharTable = (unsigned char *)CharTable[using_font];
	pFontInfo->pFontWidthTable = (unsigned char *)FontWidthTable[using_font];

	return true;


}
void MsApiSelectFont(MS_U8 font_choose)
{
	using_font = font_choose;
	return ;
}


#if (ENABLE_DISPLAY_LOGO) // GEGOP

void MsApiDisplay_Logo(GFX_DrawRect *rect,GFX_BufferInfo *src_info,GFX_BufferInfo *dst_info, MS_BOOL bHorStretch, MS_BOOL bVerStretch,MS_U16 u16DispX,MS_U16 u16DispY)
{
	
    UBOOT_TRACE("IN\n");
    U16* u16TempAddr = (U16*)MsOS_PA2KSEG1(dst_info->u32Addr);

    if(u16TempAddr == NULL)
    {
        printf("%s: Error: NULL pointer, at %d\n", __func__, __LINE__);
        return;
    }
    MsDrvGFX_Init();
    MsDrvGOP_Init();
    #if 0 //by jh
    U32 i=0;
    for (i=0;i<((dst_info->u32Pitch)*(rect->srcblk.height));i++)
    {
        *u16TempAddr = 0x8000;
        u16TempAddr++;
    }
    #endif

    Chip_Flush_Memory();
	MsDrvGFX_Blt(rect,src_info,dst_info);
	src_info->u32Pitch =src_info->u32Pitch>>1;
	dst_info->u32Pitch =dst_info->u32Pitch>>1;

	char * p_str = getenv ("MIRROR_ON");
    if(p_str != NULL)
    {
        if((int)simple_strtol(p_str, NULL, 10))
        {
            printf("<<set_mirror ON!!>>");
            MApi_GOP_GWIN_SetVMirror(TRUE);
            MApi_GOP_GWIN_SetHMirror(TRUE);
        }
    }
	MsDrvGOP_Show(dst_info,bHorStretch,bVerStretch,u16DispX,u16DispY);
    printf("[AT][MB][Show Logo][%lu]\n", MsSystemGetBootTime());
    UBOOT_TRACE("OK\n");

}

#endif
void MsApiDrawJPG(GFX_BufferInfo src_info,GFX_Block Blk)
{
	GFX_BufferInfo dst_info;
	GFX_DrawRect gfxBitbltInfo;
	GFX_Point v0;
    GFX_Point v1;

    if (0xFF == u8OsdLayerFbId)
    {
        return;
    }

	v0.x = Blk.x;
	v0.y = Blk.y;
	v1.x = Blk.x + Blk.width;
	v1.y = Blk.y + Blk.height;
	MApi_GFX_SetClip(&v0, &v1);
	MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_PC, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);

	dst_info.u32ColorFmt = (GFX_Buffer_Format)E_MS_FMT_YUV422;
    dst_info.u32Addr = CANVAS_BUFFER_ADDR;
    dst_info.u32Width = CANVAS_WIDTH;
    dst_info.u32Height = CANVAS_HEIGHT;
    dst_info.u32Pitch = CANVAS_WIDTH << 1;

	MApi_GFX_SetDstBufferInfo(&dst_info, 0);
    MApi_GFX_SetSrcBufferInfo(&src_info, 0);

    gfxBitbltInfo.dstblk.height = Blk.height;
    gfxBitbltInfo.dstblk.width = Blk.width;
    gfxBitbltInfo.dstblk.x = Blk.x;
    gfxBitbltInfo.dstblk.y = Blk.y;

    gfxBitbltInfo.srcblk.height = src_info.u32Height;
    gfxBitbltInfo.srcblk.width = src_info.u32Width;
    gfxBitbltInfo.srcblk.x = 0;
    gfxBitbltInfo.srcblk.y = 0;

    MApi_GFX_BitBlt(&gfxBitbltInfo, GFXDRAW_FLAG_SCALE);
    MApi_GFX_FlushQueue();
    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_PC, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YVYU);
}

void MsApiDrawRect(GFX_Block* pBlk, GFX_RgbColor color)
{
    GFX_Point v0 = {0, 0};
    GFX_Point v1 = {CANVAS_WIDTH, CANVAS_HEIGHT};
    MApi_GFX_SetClip(&v0, &v1);
    GFX_RgbColor tmpcolor;

    GFX_BufferInfo gfxDstBuf;
    gfxDstBuf.u32ColorFmt = (GFX_Buffer_Format)E_MS_FMT_YUV422;
    gfxDstBuf.u32Addr = CANVAS_BUFFER_ADDR;
    gfxDstBuf.u32Width = CANVAS_WIDTH;
    gfxDstBuf.u32Height = CANVAS_HEIGHT;
    gfxDstBuf.u32Pitch = CANVAS_WIDTH << 1;
    MApi_GFX_SetDstBufferInfo(&gfxDstBuf, 0);

    GFX_RectFillInfo gfxFillBlock;
    gfxFillBlock.dstBlock.x = pBlk->x;
    gfxFillBlock.dstBlock.y = pBlk->y;
    gfxFillBlock.dstBlock.height = pBlk->height;
    gfxFillBlock.dstBlock.width = pBlk->width;

    gfxFillBlock.fmt = (GFX_Buffer_Format)E_MS_FMT_YUV422;

    if(gfxDstBuf.u32ColorFmt == GFX_FMT_YUV422)
    {
        tmpcolor.r = (MS_U8)( 0.439*color.r-0.368*color.g-0.071*color.b+128);
        tmpcolor.g = (MS_U8)( 0.257*color.r+0.504*color.g+0.098*color.b+16);
        tmpcolor.b = (MS_U8)(-0.148*color.r-0.291*color.g+0.439*color.b+128);
		tmpcolor.a = 0xFF;
    }
    else
    {
        tmpcolor.r = color.r;
        tmpcolor.g = color.g;
        tmpcolor.b = color.b;
		tmpcolor.a = 0xFF;
    }

    memcpy(&gfxFillBlock.colorRange.color_s,&tmpcolor,sizeof(tmpcolor));
    memcpy(&gfxFillBlock.colorRange.color_e,&tmpcolor,sizeof(tmpcolor));

    gfxFillBlock.flag = GFXRECT_FLAG_COLOR_CONSTANT;

    MApi_GFX_BeginDraw();
    MApi_GFX_RectFill(&gfxFillBlock);
    MApi_GFX_EndDraw();

    return;
}
void MsApiDrawPixel(GFX_Point p, GFX_RgbColor color)
{
    GFX_Block dstBlk = {p.x, p.y, 1, 1};
    MsApiDrawRect(&dstBlk, color);
    return ;
}
static MS_BOOL drawASCChar(MS_U16 X, MS_U16 Y, MS_U16 W, GFX_RgbColor color)
{
    MS_U16 h = 0;
    MS_U16 i = 0;
    unsigned char castFont[8]={0};
    for (; h < font_info.font_height; ++h)
    {

        GFX_Point point;
        point.y = h + Y;

        MS_U16 w = 0;
		for(i=0;i<font_info.font_height/8;i++)
		{
			if(using_font == font32X32)
				{
					castFont[i] = Font32X32[h*4+i];
				}
			if(using_font  ==font16X16)
				{
					castFont[i] = Font16X16[h*2+i];
				}
		}
	     i=0;
        for (; w < W; ++w)
        {
            //Draw one ponit
            i = w/8;
	        castFont[0] = castFont[i];
            if (castFont[0]  & u8FontBitMask[w-i*8])
            {
                point.x = w + X;
                MsApiDrawPixel(point, color);
            }
        }
    }

    return TRUE;
}
static MS_BOOL drawUniChar(MS_U16 X, MS_U16 Y, MS_U16 W, GFX_RgbColor color)
{
    MS_U16 h = 0;
    for (; h < ONE_CHAR_HEIGHT; ++h)
    {
        MS_U16 u16Idx = 3 * h;
        MS_U32 u32Line = (UNI_CHAR_ARRAY[u16Idx] << 24) | (UNI_CHAR_ARRAY[u16Idx + 1] << 16) | (UNI_CHAR_ARRAY[u16Idx + 2] << 8);

        if (0 == u32Line)
        {
            continue;
        }

        GFX_Point point;
        point.y = h + Y;

        MS_U16 w = 0;
        for (; w < W; ++w)
        {
            //Draw one ponit
            if (u32Line & u32FontBitMask[w])
            {
                point.x = w + X;
                MsApiDrawPixel(point, color);
            }
        }
    }

    return TRUE;
}

static MS_S16 findASCCharIndex(const char* pStrText)
{
    MS_U16 u16Len = strlen(ASC_CHAR_TABLE);
    MS_S16 idx = 0;
    for (; idx < u16Len; ++idx)
    {
        if (ASC_CHAR_TABLE[idx] == pStrText[0])
        {
            return idx;
        }
    }

    return -1;
}

static MS_S16 findUniCharIndex(const char* pStrText)
{
    MS_U16 u16Len = strlen(UNI_CHAR_TABLE);
    MS_S16 idx = 0;
    for (; idx < u16Len; ++idx)
    {
        if (UNI_CHAR_TABLE[idx++] == pStrText[0] && UNI_CHAR_TABLE[idx] == pStrText[1])
        {
            return idx >> 1;
        }
    }

    return -1;
}

static MS_U16 getASCStrTextTotalWidth(const char* pStrText)
{
    MS_U16 u16Total = 0;
    MS_U16 u16Len = strlen(pStrText);
    MS_U16 i = 0;
    for (; i < u16Len; ++i)
    {
        MS_S16 s16Idx = findASCCharIndex(&pStrText[i]);
        if(s16Idx>=0)
        {
            u16Total += ((s16Idx < 0) ? font_info.space_width: (font_info.pFontWidthTable[s16Idx] + font_info.interval_width));
        }
    }

    return (u16Total > font_info.interval_width)?(u16Total - font_info.interval_width):0;
}

static MS_U16 getUniStrTextTotalWidth(const char* pStrText)
{
    MS_U16 u16Total = 0;
    MS_U16 u16Len = strlen(pStrText) >> 1;
    MS_U16 i = 0;
    for (; i < u16Len; ++i)
    {
        u16Total += (ONE_CHAR_WIDTH + EACH_CHAR_INTERVAL);
    }

    return (u16Total > EACH_CHAR_INTERVAL)?(u16Total - EACH_CHAR_INTERVAL):0;
}

static MS_BOOL drawOneASCCharByIdx(MS_S16 s16Idx, MS_U16 X, MS_U16 Y, GFX_RgbColor color)
{
    if (s16Idx < 0)
    {
        return FALSE;
    }
    if(using_font == 0)
    	{
    	 	memcpy(Font32X32, &(font_info.pCharTable[s16Idx * 128]), 128);
    		drawASCChar(X, Y, font_info.pFontWidthTable[s16Idx], color);
    	}
   if(using_font == 1)
   	{
   		 memcpy(Font16X16, &(font_info.pCharTable[s16Idx * 32]), 32);
   	 	drawASCChar(X, Y,font_info.pFontWidthTable[s16Idx], color);
   	}
    return TRUE;
}
static MS_BOOL drawOneUniCharByIdx(MS_S16 s16Idx, MS_U16 X, MS_U16 Y, GFX_RgbColor color)
{
    if (s16Idx < 0)
    {
        return FALSE;
    }

    memcpy(UNI_CHAR_ARRAY, &UNI_FONT_TABLE[s16Idx * 72], 72);
    drawUniChar(X, Y, ONE_CHAR_WIDTH, color);
    return TRUE;
}

static MS_BOOL drawASCStrText(const char* pStrText, MS_U16 X, MS_U16 Y, GFX_RgbColor color, TextAttrib eTextAttrib)
{

    GetFontInfo(&font_info,  using_font);
    switch (eTextAttrib)
    {
        case eTextAlignMiddle:
        {
            GOP_GwinFBAttr sFBInfo;
            MApi_GOP_GWIN_GetFBInfo(u8OsdLayerFbId, &sFBInfo);
            X = (sFBInfo.width - getASCStrTextTotalWidth(pStrText)) >> 1;
            break;
        }

        case eTextAlignRight:
            X -= getASCStrTextTotalWidth(pStrText);
            break;

        case eTextAlignLeft:
        default:
            break;
    }

    MS_U16 u16Offset = 0;
    MS_U16 u16Len = strlen(pStrText);
    MS_U16 i = 0;

    for(; i < u16Len; ++i)
    {
        X += u16Offset;
        MS_S16 s16Idx = findASCCharIndex(&pStrText[i]);
        if(s16Idx>=0)
        {
            drawOneASCCharByIdx(s16Idx, X, Y, color);

	    u16Offset = (s16Idx < 0) ? font_info.space_width: (font_info.pFontWidthTable[s16Idx] + font_info.interval_width);
        }
        
    }

    return TRUE;
}

static MS_BOOL drawUniStrText(const char* pStrText, MS_U16 X, MS_U16 Y, GFX_RgbColor color, TextAttrib eTextAttrib)
{
    switch (eTextAttrib)
    {
        case eTextAlignMiddle:
        {
            GOP_GwinFBAttr sFBInfo;
            MApi_GOP_GWIN_GetFBInfo(u8OsdLayerFbId, &sFBInfo);
            X = (sFBInfo.width - getUniStrTextTotalWidth(pStrText)) >> 1;
            break;
        }

        case eTextAlignRight:
            X -= getUniStrTextTotalWidth(pStrText);
            break;

        case eTextAlignLeft:
        default:
            break;
    }

    MS_U16 u16Offset = 0;
    MS_U16 u16Len = strlen(pStrText);
    MS_U16 i = 0;

    for(; i < u16Len; i += 2)
    {
        X += u16Offset;
        MS_S16 s16Idx = findUniCharIndex(&pStrText[i]);
        drawOneUniCharByIdx(s16Idx, X, Y, color);
        u16Offset = (s16Idx < 0) ? SPACE_WIDTH : (ONE_CHAR_WIDTH + EACH_CHAR_INTERVAL);
    }

    return TRUE;
}

void MsApiDrawStrText(const char* pStrText, MS_U16 X, MS_U16 Y, GFX_RgbColor color, TextAttrib eTextAttrib)
{
    ((MS_U8)pStrText[0] < 0xA0) ? drawASCStrText(pStrText, X, Y, color, eTextAttrib) : drawUniStrText(pStrText, X, Y, color, eTextAttrib);
	return ;
}
void MsApiFlushCanvas2Screen(void)
{
    if (0xFF == u8OsdLayerFbId)
    {
        return;
    }

    GOP_GwinFBAttr sFBInfo;
    MApi_GOP_GWIN_GetFBInfo(u8OsdLayerFbId, &sFBInfo);

    GFX_Point v0 = {sFBInfo.x0, sFBInfo.y0};
    GFX_Point v1 = {sFBInfo.x1, sFBInfo.y1};
    MApi_GFX_SetClip(&v0, &v1);

    GFX_BufferInfo gfxDstBuf;
    gfxDstBuf.u32ColorFmt = (GFX_Buffer_Format)(sFBInfo.fbFmt & 0xFF);
    gfxDstBuf.u32Addr = sFBInfo.addr;
    gfxDstBuf.u32Width = sFBInfo.width;
    gfxDstBuf.u32Height = sFBInfo.height;
    gfxDstBuf.u32Pitch = sFBInfo.pitch;
    MApi_GFX_SetDstBufferInfo(&gfxDstBuf, 0);

    GFX_BufferInfo gfxSrcBuf;
    gfxSrcBuf.u32ColorFmt = (GFX_Buffer_Format)E_MS_FMT_YUV422;
    gfxSrcBuf.u32Addr = CANVAS_BUFFER_ADDR;
    gfxSrcBuf.u32Width = CANVAS_WIDTH;
    gfxSrcBuf.u32Height = CANVAS_HEIGHT;
    gfxSrcBuf.u32Pitch = CANVAS_WIDTH << 1;
    MApi_GFX_SetSrcBufferInfo(&gfxSrcBuf, 0);

    GFX_DrawRect gfxBitbltInfo;
    gfxBitbltInfo.dstblk.height = sFBInfo.height;
    gfxBitbltInfo.dstblk.width = sFBInfo.width;
    gfxBitbltInfo.dstblk.x = 0;
    gfxBitbltInfo.dstblk.y = 0;

    gfxBitbltInfo.srcblk.height = CANVAS_HEIGHT;
    gfxBitbltInfo.srcblk.width = CANVAS_WIDTH;
    gfxBitbltInfo.srcblk.x = 0;
    gfxBitbltInfo.srcblk.y = 0;

    MApi_GFX_BitBlt(&gfxBitbltInfo, GFXDRAW_FLAG_SCALE);
    MApi_GFX_FlushQueue();

}

void MsApiOsdCreate(GFX_Block* pBlk, U32 u32GopBuffer)
{
	U32 i=0;
    U16* u16TempAddr = (U16*)MsOS_PA2KSEG1(u32GopBuffer);
    U16* u16TempAddr1 = (U16*)MsOS_PA2KSEG1(CANVAS_BUFFER_ADDR);
    GFX_BufferInfo dst_info;

    if(u16TempAddr == NULL)
    {
        printf("%s: Error: NULL pointer, at %d\n", __func__, __LINE__);
        return;
    }
    if(u16TempAddr1 == NULL)
    {
        printf("%s: Error: NULL pointer, at %d\n", __func__, __LINE__);
        return;
    }
    MsDrvGFX_Init();
    MsDrvGOP_Init();

    for (i=0;i<((pBlk->width)*(g_IPanel.Height()));i++)
    {
            *u16TempAddr = 0x8000;
            u16TempAddr++;
    }
    for (i = 0; i < CANVAS_WIDTH * CANVAS_HEIGHT; ++i)
    {
        *(u16TempAddr1++) = 0x8000;
    }
    Chip_Flush_Memory();

    dst_info.u32Addr = u32GopBuffer;
    dst_info.u32Width = pBlk->width;
    dst_info.u32Height = g_IPanel.Height();
    dst_info.u32ColorFmt = GFX_FMT_YUV422;
    dst_info.u32Pitch = (pBlk->width<<1);

	u16OsdW = pBlk->width;
    u16OsdH = pBlk->height;
    MsDrvGOP_Show(&dst_info,TRUE,TRUE,pBlk->x,pBlk->y);
    char * p_str = getenv ("MIRROR_ON");
    if(p_str != NULL)
    {
        if((int)simple_strtol(p_str, NULL, 10))
        {
            printf("<<set_mirror ON!!>>");
            MApi_GOP_GWIN_SetVMirror(TRUE);
            MApi_GOP_GWIN_SetHMirror(TRUE);
        }
    }
}

void MsApiOsdDestroy(void)
{
    //Set OSD to black before destroy
    if (u16OsdW != 0 && u16OsdH != 0)
    {
        GFX_RgbColor color = {0, 0, 0, 0};
        GFX_Block dstBlk = {0, 0, u16OsdW, u16OsdH};
        MsApiDrawRect(&dstBlk, color);
        MsApiFlushCanvas2Screen();
        u16OsdW = 0;
        u16OsdH = 0;
    }

    if (u8OsdLayerGwinId != 0xFF)
    {
        MApi_GOP_GWIN_Enable(u8OsdLayerGwinId, FALSE);
        u8OsdLayerGwinId = 0xFF;
    }

    if (u8OsdLayerFbId != 0xFF)
    {
        MApi_GOP_GWIN_DestroyFB(u8OsdLayerFbId);
        u8OsdLayerFbId = 0xFF;
    }
}
void MsApiDrawProgress(MS_U16 X, MS_U16 Y, GFX_RgbColor fcolor, MS_U8 per)
{
    if (per > 100)
    {
        per = 100;
    }

    MS_U16 u16StartX = X;
    MS_U16 u16Total = (PROGRESS_NUM * PROGRESS_WIDTH) * per / 100;
    MS_U16 u16Count = u16Total / PROGRESS_WIDTH;

    //memset(ASC_CHAR_ARRAY, 0xFF, 96);
	memset(Font32X32, 0xFF, 128);

    MS_U16 i = 0;
    for (; i < u16Count; ++i)
    {
        drawASCChar(u16StartX, Y, PROGRESS_WIDTH, fcolor);
        u16StartX += (PROGRESS_WIDTH + PROGRESS_INTERVAL);
    }

    MS_U16 u16Left = u16Total % PROGRESS_WIDTH;
    if (u16Left != 0)
    {
        drawASCChar(u16StartX, Y, u16Left, fcolor);
        u16StartX += (u16Left + PROGRESS_INTERVAL);
    }

    char cStr[5] = {0};
    memset(cStr, 0, sizeof(cStr));
    snprintf(cStr, sizeof(cStr), "%d%%", per);
    drawASCStrText(cStr, X + PROGRESS_NUM * (PROGRESS_WIDTH + PROGRESS_INTERVAL), Y, fcolor, eTextAlignLeft);

}

