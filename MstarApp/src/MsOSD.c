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


//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <stdio.h>
#include <MsTypes.h>
#include <ShareType.h>
#include <MsOSD.h>
#include <MsApiGEGOP.h>
#include <MsDebug.h>
#include <MsUboot.h>
#include <MsVfs.h>
#include <MsApiJpd.h>
#include <MsApiPanel.h>
#include <MsRawIO.h>
#include <MsSystem.h>
#include <CusConfig.h>
#include <MsMmap.h>



//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
typedef struct
{
    U16 u16DispX;
    U16 u16DispY;
    U16 u16DispW;
    U16 u16DispH;
}BltConfigParams;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
int do_create_osdlayer(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    U32 u32GopBuffer;
    MS_U16 w, h;

    if (argc < 3)
    {
#if (CONFIG_BINARY_RELEASE == 1)
        w = DEFAULT_OSD_LAYER_WIDTH;
        h = DEFAULT_OSD_LAYER_HEIGHT;
#else
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
#endif
    }
    else
    {
       w = simple_strtoul(argv[1], NULL, 10);
       h = simple_strtoul(argv[2], NULL, 10);
    }

    MS_U32 size = w * h;

    if (0 == size)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    if(IsPanelReady()!= 0)
    {
        if(run_command("panel_init",0)!=0)
        {
            printf("Error : panel_init fail!!\n");
            return -1;
        }
    }

#if defined(CONFIG_ENABLE_4K2K_PANEL)
#if defined(CONFIG_INX_NOVA_VB1)
	run_command("inx_panel_set_init", 0);
#endif
#endif

#if(ENABLE_HDMI_TX == 1)
    if(run_command("hdmi init",0)!=0)
    {
        printf("Error : hdmi init fail!!\n");
        return -1;
    }

#endif

#if(ENABLE_CVBS_OUT == 1)
    run_command("cvbs",0);
#endif

#if (CONFIG_ENABLE_RTPM)
	run_command ("runtime_pm" , 0);
#endif

#if defined(CONFIG_INX_VB1) && defined(CONFIG_BOOTLOGO_4K2K)
	run_command("panel_inx_vb1_init", 0);
#endif

#if ENABLE_BOOT_SPI_ECOS
    u32GopBuffer = GOP_BUFFER_ADDR;
#else

    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &u32GopBuffer)!=0)
    {
        UBOOT_ERROR("get E_DFB_FRAMEBUFFER_ADR mmap fail\n");
        return -1;
    }
#endif
    if(u32GopBuffer==0xFFFF)
    {
        UBOOT_ERROR("Get Mmap for GOP Failed !!! \n");
        return -1;
    }

    GFX_Block dstBlk = {0, 0, w, h};
    MsApiOsdCreate(&dstBlk,u32GopBuffer);
    return 0;
}
int do_destroy_osdlayer(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MsApiOsdDestroy();
    return 0;
}
int do_flush2screen_osdlayer(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MsApiFlushCanvas2Screen();
    return 0;
}

static unsigned int LoadJpg2Dram(char *SrcPath,U32 Dram_Addr)
{
    char PathBuf[128] = "\0";
    U32 u32LogoSize=0;
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("PA2NVA(Dram_Addr)=0x%x\n",(unsigned int)Dram_Addr);

    vfs_mount(CUSTOMER);
    snprintf(PathBuf, sizeof(PathBuf), "%s/%s",CUSTOMER_PATH,SrcPath);
    UBOOT_DEBUG("PathBuf=%s\n",PathBuf);
    u32LogoSize = vfs_getsize(PathBuf);
    UBOOT_DEBUG("u32LogoSize=0x%x\n",(unsigned int)u32LogoSize);
    vfs_read((void *)Dram_Addr,PathBuf,0,u32LogoSize);

    UBOOT_TRACE("OK\n");
    return u32LogoSize;
}

void draw_jpg(BltConfigParams stConfig,U32 JPD_OUTADDR)
{

    GFX_BufferInfo src_info;
    GFX_Block Blk;

    UBOOT_TRACE("IN\n");

    src_info.u32Addr = JPD_OUTADDR;
    UBOOT_DEBUG("src_info.u32Addr=0x%x\n",(unsigned int)src_info.u32Addr);

    src_info.u32ColorFmt = GFX_FMT_YUV422;
    UBOOT_DEBUG("src_info.u32ColorFmt=0x%x\n",(unsigned int)src_info.u32ColorFmt);

    src_info.u32Width = (U32)JPG_GetAlignmentWidth();
    UBOOT_DEBUG("src_info.u32Width=0x%x\n",(unsigned int)src_info.u32Width);

    src_info.u32Height = (U32)JPG_GetAlignmentHeight();
    UBOOT_DEBUG("src_info.u32Height=0x%x\n",(unsigned int)src_info.u32Height);

    src_info.u32Pitch = (U32)JPG_GetAlignmentPitch()<<1;
    UBOOT_DEBUG("src_info.u32Pitch=0x%x\n",(unsigned int)src_info.u32Pitch);

    Blk.x = (U16)((stConfig.u16DispX+15)&0xFFFFF0);
    Blk.y = stConfig.u16DispY;
    Blk.width = (U16)((stConfig.u16DispW+15)&0xFFFFF0);;
    Blk.height = stConfig.u16DispH;
    MsApiDrawJPG(src_info,Blk);
    UBOOT_TRACE("OK\n");
}

int do_draw_jpg (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    U32 u32LogoAddr=0;
    U32 u32LogoSize=0;
    U32 JPD_InputADDR=0;
    U32 JPD_OUTADDR=0;
    char *PhotoPath=NULL;
    BltConfigParams stConfig;
    UBOOT_TRACE("IN\n");


    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &JPD_InputADDR)!=0)
    {
        UBOOT_ERROR("get E_DFB_FRAMEBUFFER mmap fail\n");
        return -1;
    }

#if (CONFIG_VESTEL_MB100 == 1)
    if(get_addr_from_mmap("E_MMAP_ID_JPD_WRITE", &JPD_OUTADDR)!=0)	//MB100_BRINGUP
    {
        UBOOT_ERROR("get E_MMAP_ID_JPD_WRITE mmap fail\n");
        return -1;
    }
#else
    if(get_addr_from_mmap("E_MMAP_MAD_JPEG_DISPLAY_ADR", &JPD_OUTADDR)!=0)	//MB100_BRINGUP
    {
        UBOOT_ERROR("get E_MMAP_MAD_JPEG_DISPLAY_ADR mmap fail\n");
        return -1;
    }
#endif
    JPD_InputADDR=PA2NVA(JPD_InputADDR);
	if(JPD_InputADDR==0xFFFF || JPD_OUTADDR==0xFFFF)
	{
		UBOOT_ERROR("Get Mmap for JPD Fail Skip JPD Decode !!! \n");
		return -1;

	}
    if(argc < 6)
    {
#if (CONFIG_BINARY_RELEASE == 1)
    stConfig.u16DispX = DEFAULT_OSD_STRING_X;
    stConfig.u16DispY = DEFAULT_OSD_STRING_Y;
    stConfig.u16DispW = DEFAULT_OSD_LAYER_WIDTH;
    stConfig.u16DispH = DEFAULT_OSD_LAYER_HEIGHT;
#else
        cmd_usage(cmdtp);
        return 1;
#endif
    }
    else
    {
        stConfig.u16DispX = simple_strtoul(argv[2], NULL, 10);
        stConfig.u16DispY = simple_strtoul(argv[3], NULL, 10);
        stConfig.u16DispW = simple_strtoul(argv[4], NULL, 10);
        stConfig.u16DispH = simple_strtoul(argv[5], NULL, 10);
    }
    if(IsPanelReady()!=0)
    {
         UBOOT_ERROR("Panle is not ready\n");
        return -1;
    }


    UBOOT_DEBUG("u16DispX=0x%x,u16DispY=0x%x,u16DispW=0x%x,u16DispH=0x%x\n",stConfig.u16DispX,stConfig.u16DispY,stConfig.u16DispW,stConfig.u16DispH);

    if(strncmp(argv[1], "-fs", 3)==0) // jpd from filesystem
    {
        PhotoPath = argv[6];
        UBOOT_DEBUG("PhotoPath=%s\n",PhotoPath);
        u32LogoSize = LoadJpg2Dram(PhotoPath, JPD_InputADDR);
        UBOOT_DEBUG("u32LogoSize : 0x%x \n",u32LogoSize);
        if(u32LogoSize == 0)
        {
            UBOOT_ERROR("Fail: Load_Photo2Dram return size is 0 !!\n");
            return -1;
        }
    }
    else if(strncmp(argv[1], "-s", 2)==0)
    {
        mboot_raw_io_Config();
        u32LogoAddr= simple_strtoul(argv[6],NULL,16);
        u32LogoSize= simple_strtoul(argv[7],NULL,16);;
        raw_read(PA2NVA(JPD_InputADDR),u32LogoAddr,u32LogoSize);
    }
    else
    {
#if (CONFIG_BINARY_RELEASE == 1)
        PhotoPath = DEFAULT_OSD_BACKGROUND_PATH;
        UBOOT_DEBUG("PhotoPath=%s\n",PhotoPath);
        u32LogoSize = LoadJpg2Dram(PhotoPath,LOGO_JPG_DRAM_ADDR);
        UBOOT_DEBUG("u32LogoSize : 0x%x \n",u32LogoSize);
        if(u32LogoSize == 0)
        {
            UBOOT_ERROR("Fail: Load_Photo2Dram return size is 0 !!\n");
            return -1;
        }
#else
        cmd_usage(cmdtp);
        return -1;
#endif
    }
    MsApi_JPD_Decode(JPD_InputADDR, u32LogoSize);
    draw_jpg(stConfig,JPD_OUTADDR);
    UBOOT_TRACE("OK\n");
    return 0;
}

int do_draw_rect(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc < 6)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }
    MS_U16 x = simple_strtoul(argv[1], NULL, 10);
    MS_U16 y = simple_strtoul(argv[2], NULL, 10);
    MS_U16 w = simple_strtoul(argv[3], NULL, 10);
    MS_U16 h = simple_strtoul(argv[4], NULL, 10);
    MS_U32 tColor = simple_strtoul(argv[5], NULL, 16);

    GFX_RgbColor color;
    color.a = tColor >> 24;
    color.r = (tColor >> 16) & 0xFF;
    color.g = (tColor >> 8) & 0xFF;
    color.b = tColor & 0xFF;
    GFX_Block dstBlk = {x, y, w, h};
    MsApiDrawRect(&dstBlk, color);
    return 0;
}

int do_draw_pixel(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc < 4)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    MS_U16 x = simple_strtoul(argv[1], NULL, 10);
    MS_U16 y = simple_strtoul(argv[2], NULL, 10);
    MS_U32 tColor = simple_strtoul(argv[3], NULL, 16);

    GFX_RgbColor color;
    color.a = tColor >> 24;
    color.r = (tColor >> 16) & 0xFF;
    color.g = (tColor >> 8) & 0xFF;
    color.b = tColor & 0xFF;
    GFX_Point p = {x, y};
    MsApiDrawPixel(p, color);
    return 0;
}
int do_draw_string(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MS_U8 font;
    MS_U16 x, y, attrib;
    MS_U32 tColor;
    GFX_RgbColor color;

    if (argc < 6)
    {
#if (CONFIG_BINARY_RELEASE == 1)
          x    = DEFAULT_OSD_STRING_X;
          y    = DEFAULT_OSD_STRING_Y;
        tColor = DEFAULT_OSD_COLOR;
        attrib = (DEFAULT_OSD_ATTRIB)%10;
        font   = (DEFAULT_OSD_ATTRIB)/10;
#else
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
#endif
    }
    else
    {
        x = simple_strtoul(argv[1], NULL, 10);
        y = simple_strtoul(argv[2], NULL, 10);
        tColor = simple_strtoul(argv[3], NULL, 16);
        attrib = simple_strtoul(argv[4], NULL, 10)%10;
        font = simple_strtoul(argv[4], NULL, 10)/10;
    }

    color.a = tColor >> 24;
    color.r = (tColor >> 16) & 0xFF;
    color.g = (tColor >> 8) & 0xFF;
    color.b = tColor & 0xFF;


	MsApiSelectFont(font);
    char cStr[202] = {0};
    MS_U16 u16Total = 0;
    MS_S16 i = 5;

    for (; i < argc; ++i)
    {
        MS_U16 u16Len = strlen(argv[i]);
        if (u16Total + u16Len > 200)
        {
            break;
        }

        memset(cStr + u16Total, 0 , (sizeof(cStr)-u16Total));
        snprintf(cStr + u16Total, (sizeof(cStr)-u16Total), "%s", argv[i]);
        u16Total += u16Len;
        cStr[u16Total++] = ' ';
    }

    cStr[u16Total] = 0;

    MsApiDrawStrText(cStr, x, y, color, (TextAttrib)attrib);
    return 0;
}
int do_draw_Progress(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc < 5)
    {
        printf("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    MS_U16 x = simple_strtoul(argv[1], NULL, 10);
    MS_U16 y = simple_strtoul(argv[2], NULL, 10);
    MS_U8 per = simple_strtoul(argv[4], NULL, 10);
    MS_U32 tColor = simple_strtoul(argv[3], NULL, 16);

    GFX_RgbColor color;
    color.a = tColor >> 24;
    color.r = (tColor >> 16) & 0xFF;
    color.g = (tColor >> 8) & 0xFF;
    color.b = tColor & 0xFF;
    MsApiDrawProgress(x, y, color, per);
    return 0;
}
