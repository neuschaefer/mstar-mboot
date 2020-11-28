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
#include <command.h>
#include <common.h>
#include <exports.h>
#include <lzmadec.h>
#include <MsTypes.h>
#include <ShareType.h>
#include <MsVfs.h>
#include <MsDebug.h>
#include <MsUtility.h>
#include <MsOS.h>
#include <MsSystem.h>

#if (ENABLE_MODULE_USB == 1)
#include <usb.h>
#endif

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define SCRIPT_FILE_COMMENT         '#'                 // symbol for comment
#define SCRIPT_FILE_END             '%'                 // symbol for file end
#define IS_COMMENT(x)       (SCRIPT_FILE_COMMENT == (x))
#define IS_FILE_END(x)      (SCRIPT_FILE_END == (x))
#define IS_LINE_END(x)      ('\r' == (x)|| '\n' == (x))
#define IS_IGNORED_CHAR(x)  ('\r' == (x)|| '\n' == (x) || '\t' == (x) || ' ' == (x))
#define SCRIPT_BUFSIZE       	64*1024                 //max script is 64

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------

void *SzAlloc(void *p, size_t size) { p = p; return malloc(size);}
void SzFree(void *p, void *address) { p = p; free(address); }
ISzAlloc g_Alloc = { SzAlloc, SzFree };

int do_mdelay(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
  int delaytime = 0;
  delaytime = simple_strtol(argv[1],NULL,10);
  MsOS_DelayTask(delaytime);
  return 0;
}

U8 MsDecompress7(U8 *pSrc, U8 *pDst, U32 srclen)
{
    U32 OriginalFileLength = 0;
    int result = SZ_OK;
    U8 i;
    ELzmaStatus estatus = NULL;
    SizeT destLen, srcLen;
    char buf [12], filesize[12];

    #define LZMA_PROPS_SIZE 5

	/* header: 5 bytes of LZMA properties and 8 bytes of uncompressed size */
    srclen -= (LZMA_PROPS_SIZE + 8);

	// It seems that in our system, we never have a chance to have a compressed data which needs to use U64 integer to store its file size
	// So we use just U32 here to instead of U64
	/* Read and parse header */
    for (i = 0; i < 8; i++)
        OriginalFileLength += ( (U32)pSrc[LZMA_PROPS_SIZE + i] << (i << 3) );

	destLen = OriginalFileLength;
	srcLen = srclen;

    result = LzmaDecode(pDst, &destLen, pSrc + (LZMA_PROPS_SIZE + 8), &srcLen, pSrc, LZMA_PROPS_SIZE, LZMA_FINISH_ANY, &estatus, &g_Alloc);

    switch( estatus )
    {
    case LZMA_STATUS_FINISHED_WITH_MARK:
    case LZMA_STATUS_NOT_FINISHED:
    case LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK:
        break;
    default:
    //LZMA_STATUS_NOT_SPECIFIED,               /* use main error code instead */
    //LZMA_STATUS_NEEDS_MORE_INPUT,            /* you must provide more input bytes */
        //printf("ELzmaStatus = %d\n", estatus);
        //Decompression fail!
        return FALSE;
    }

    if (result != SZ_OK)
    {
    //  SZ_ERROR_DATA - Data error
    //  SZ_ERROR_MEM  - Memory allocation error
    //  SZ_ERROR_UNSUPPORTED - Unsupported properties
    //  SZ_ERROR_INPUT_EOF - It needs more bytes in input buffer (src).
    //#define SZ_ERROR_DATA 1
    //#define SZ_ERROR_MEM 2
    //#define SZ_ERROR_CRC 3
    //#define SZ_ERROR_UNSUPPORTED 4
    //#define SZ_ERROR_PARAM 5
    //#define SZ_ERROR_INPUT_EOF 6
    //#define SZ_ERROR_OUTPUT_EOF 7
    //#define SZ_ERROR_READ 8
    //#define SZ_ERROR_WRITE 9
    //#define SZ_ERROR_PROGRESS 10
    //#define SZ_ERROR_FAIL 11
    //#define SZ_ERROR_THREAD 12
    //#define SZ_ERROR_ARCHIVE 16
    //#define SZ_ERROR_NO_ARCHIVE 17
        //printf("error code:%d\n", result);
        //Decompression fail!
		return FALSE;
    }

	if ( destLen != OriginalFileLength )
	{
        //Decompression fail!
		return FALSE;
	}

	if ( srcLen != srclen )
	{
        //Decompression fail!
// Skip this check temporarily		return FALSE;
	}

    memset(buf, 0 , sizeof(buf));
    memset(filesize, 0 , sizeof(filesize));
    snprintf(buf, sizeof(buf), "%lX", destLen);
    strcpy(filesize, "filesize");
    setenv(filesize, buf);

#if((ENABLE_MSTAR_KENYA == 1) || (ENABLE_MSTAR_KERES == 1) || (ENABLE_MSTAR_CLIPPERS==1))
    // flush cache after read
    flush_cache((ulong)pDst, destLen);

    //Decompression OK!
    printf("Decompression OK!\n");
#endif
	return TRUE;
}


int do_mscompress7 (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int i;
    long AddrSrc=0, LengthSrc=0, AddrDst=0;

    if (argc < 6) {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    for (i=1; i<argc; ++i) {
        switch(i)
        {
            case 1:
                if(argv[i][0] != 'd')
                {
                    return 1;
                }
                break;
            case 2:
                if(simple_strtol(argv[i], NULL, 10) != 0)
                {
                    return 1;
                }
                break;
            case 3:
                AddrSrc = simple_strtol(argv[i], NULL, 16);
                break;
            case 4:
                LengthSrc = simple_strtol(argv[i], NULL, 16);
                break;
            case 5:
                AddrDst = simple_strtol(argv[i], NULL, 16);
                break;
            default:
                break;
        }
    }
    if(TRUE != MsDecompress7((U8*)AddrSrc, (U8*)AddrDst, LengthSrc))
    {
        printf("%s: MsDecompress7() failed, at %d\n", __func__, __LINE__);
        return 1;
    }
    return 0;
}

extern int readline (const char *const prompt);
extern char console_buffer[CONFIG_SYS_CBSIZE + 1];
void jump_to_console(void)
{

	static char lastcommand[CONFIG_SYS_CBSIZE +1] = { 0, };//Fix Coverity CID:148928
	int len;
	int rc = 1;
	int aflag;
    printf("jump_to_console start!!\n");
    for (;;)
    {
        len = readline (CONFIG_SYS_PROMPT);

        aflag = 0;   /* assume no special flags for now */
        if (len > 0)
            strcpy (lastcommand, console_buffer);
        else if (len == 0)
            aflag |= CMD_FLAG_REPEAT;

        if (len == -1)
            puts ("<INTERRUPT>\n");
        else
            rc = run_command (lastcommand, aflag);

        if (rc <= 0) {
            /* invalid command or not repeatable, forget it */
            lastcommand[0] = 0;
        }
    }
     printf("jump_to_console end!!\n");
}

#if (ENABLE_MODULE_USB == 1)
int appInitUsbDisk(void)
{
    char idx=0;

#if   defined(ENABLE_FIFTH_EHC)
    const char u8UsbPortCount = 5;
#elif defined(ENABLE_FOURTH_EHC)
    const char u8UsbPortCount = 4;
#elif defined(ENABLE_THIRD_EHC)
    const char u8UsbPortCount = 3;
#elif defined(ENABLE_SECOND_EHC)
    const char u8UsbPortCount = 2;
#else
    const char u8UsbPortCount = 1;
#endif
    UBOOT_TRACE("IN\n");

    for(idx=0; idx<u8UsbPortCount; idx++)
    {
#if defined (CONFIG_USB_PREINIT)
        usb_stop(idx);
        if (usb_post_init(idx) == 0)
#else
        if (usb_init(idx) == 0)
#endif
        {
            if (usb_stor_scan(1) == 0)
            {
                UBOOT_TRACE("OK\n");
                return 0 ;
            }
        }
    }
    UBOOT_TRACE("OK\n");
    return -1;
}
#endif



#if ((ENABLE_MODULE_USB == 1)&&(ENABLE_MODULE_FAT==1))
int do_spi2usb ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    ulong u32SPIAddr=0;
    ulong u32Len=0;
    char *fileName;
    int ret=0;
    char buffer[CMD_BUF] = "\0";
    U8 *temp=NULL;

    UBOOT_TRACE("IN\n");
    if(argc!=4)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if((argv[1]==NULL)||(argv[2]==NULL)||(argv[3]==NULL))
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(appInitUsbDisk()!=0)
    {
        UBOOT_ERROR("no usb disk plug-in \n");
        return -1;
    }


    memset(buffer, 0, CMD_BUF);
    snprintf(buffer,CMD_BUF,"spi init");
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("spi init fail\n");
        free(temp);
        return -1;
    }


    u32SPIAddr= simple_strtol(argv[1], NULL, 16);
    u32Len= simple_strtol(argv[2], NULL, 16);
    fileName=argv[3];

    temp=(U8 *)malloc(u32Len);
    if(temp==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(temp,0,u32Len);
    memset(buffer, 0, CMD_BUF);
    snprintf(buffer,CMD_BUF,"spi rdc %x %x %x",(unsigned int)temp,(unsigned int)u32SPIAddr,(unsigned int)(u32Len));
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("spi2usb fail\n");
        free(temp);
        return -1;
    }

    memset(buffer, 0, CMD_BUF);
    snprintf(buffer,CMD_BUF,"fatwrite usb 0 0x%x %s %x",(unsigned int)temp,fileName,(unsigned int)u32Len);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("spi2usb fail\n");
        free(temp);
        return -1;
    }
    free(temp);

    UBOOT_TRACE("OK\n");
    return 0;
}

int do_usb2spi ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    MS_U32 u32SPIAddr=0;
    MS_U32 u32Len=0;
    char *fileName;
    int ret=0;
    char buffer[CMD_BUF] = "\0";
    MS_U8 *temp=NULL;
    char *pfileSize=NULL;
    MS_U32 u32FileSize=0;

    UBOOT_TRACE("IN\n");

    if(argc!=4)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if((argv[1]==NULL)||(argv[2]==NULL)||(argv[3]==NULL))
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(appInitUsbDisk()!=0)
    {
        UBOOT_ERROR("no usb disk plug-in \n");
        return -1;
    }


    u32SPIAddr= simple_strtol(argv[1], NULL, 16);
    u32Len= simple_strtol(argv[2], NULL, 16);
    fileName=argv[3];

    memset(buffer, 0, CMD_BUF);
    snprintf(buffer,CMD_BUF,"fatfilesize usb 0 %s",fileName);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("get file size fail\n");
        return -1;
    }

    pfileSize=getenv("filesize");
    if(pfileSize==NULL)
    {
        UBOOT_ERROR("get file size fail\n");
        return -1;
    }
    u32FileSize=simple_strtoul(pfileSize, 0, 16);

    if(u32FileSize<u32Len)
    {
        UBOOT_ERROR("The file size is smaller than input length, file size=0x%x(bytes), lenght=0x%x(bytes)\n",(unsigned int)u32FileSize,(unsigned int)u32Len);
        return -1;
    }

    temp=(MS_U8 *)malloc(u32Len);
    if(temp==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }

    memset(temp,0,u32Len);
    memset(buffer, 0, CMD_BUF);
    snprintf(buffer,CMD_BUF,"fatload usb 0 0x%x %s %x",(unsigned int)temp,fileName,(unsigned int)u32Len);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("fatload usb fail\n");
        free(temp);
        return -1;
    }

    memset(buffer, 0, CMD_BUF);
    snprintf(buffer,CMD_BUF,"spi wrc %x %x %x",(unsigned int)temp,u32SPIAddr,(unsigned int)(u32Len));
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("spi wrc fail \n");
        free(temp);
        return -1;
    }

    free(temp);

    UBOOT_TRACE("OK\n");
    return 0;
}

#endif

#if ((ENABLE_MODULE_USB == 1)&&(ENABLE_MODULE_EEPROM==1))
int do_eeprom2usb ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    ulong u32Off=0;
    ulong u32Len=0;
    char *fileName;
    int ret=0;
    char cmd[CMD_BUF];
    U8 *temp=NULL;
    UBOOT_TRACE("IN\n");
    if(argc!=4)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if((argv[1]==NULL)||(argv[2]==NULL)||(argv[3]==NULL))
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(appInitUsbDisk()!=0)
    {
        UBOOT_ERROR("no usb disk plug-in \n");
        return -1;
    }


    u32Off= simple_strtol(argv[1], NULL, 16);
    u32Len= simple_strtol(argv[2], NULL, 16);
    fileName=argv[3];



    temp=(U8 *)malloc(u32Len);
    if(temp==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(temp,0,u32Len);
    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd,sizeof(cmd),"eeprom read %x %x %x",(unsigned int)temp,(unsigned int)u32Off,(unsigned int)u32Len);
    UBOOT_DEBUG("cmd=%s\n",cmd);
    ret=run_command(cmd,0);
    if(ret!=0)
    {
        UBOOT_ERROR("read from eeprom fail\n");
        free(temp);
        return -1;
    }

    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd,sizeof(cmd),"fatwrite usb 0 0x%x %s %x",(unsigned int)temp,fileName,(unsigned int)u32Len);
    UBOOT_DEBUG("cmd=%s\n",cmd);
    ret=run_command(cmd,0);
    if(ret!=0)
    {
        UBOOT_ERROR("write to usb disk fail\n");
        free(temp);
        return -1;
    }
    free(temp);
    UBOOT_TRACE("OK\n");
    return 0;
}


int do_usb2eeprom ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    ulong u32Off=0;
    ulong u32Len=0;
    char *fileName;
    int ret=0;
    char cmd[CMD_BUF];
    U8 *temp=NULL;
    UBOOT_TRACE("IN\n");

    if(argc!=4)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if((argv[1]==NULL)||(argv[2]==NULL)||(argv[3]==NULL))
    {
        cmd_usage(cmdtp);
        return -1;
    }

    if(appInitUsbDisk()!=0)
    {
        UBOOT_ERROR("no usb disk plug-in \n");
        return -1;
    }


    u32Off= simple_strtol(argv[1], NULL, 16);
    u32Len= simple_strtol(argv[2], NULL, 16);
    fileName=argv[3];

    temp=(U8 *)malloc(u32Len);
    if(temp==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }



    memset(temp,0,u32Len);
    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd,sizeof(cmd),"fatload usb 0 0x%x %s %x",(unsigned int)temp,fileName,(unsigned int)u32Len);
    UBOOT_DEBUG("cmd=%s\n",cmd);
    ret=run_command(cmd,0);
    if(ret!=0)
    {
        UBOOT_ERROR("read from usb disk fail\n");
        free(temp);
        return -1;
    }

    memset(cmd, 0, sizeof(cmd));
    snprintf(cmd,sizeof(cmd),"eeprom write %x %x %x",(unsigned int)temp,(unsigned int)u32Off,(unsigned int)u32Len);
    UBOOT_DEBUG("cmd=%s\n",cmd);
    ret=run_command(cmd,0);
    if(ret!=0)
    {
        UBOOT_ERROR("write to eeprom fail\n");
        free(temp);
        return -1;
    }
    free(temp);
    UBOOT_TRACE("OK\n");
    return 0;
}
#endif

char *get_script_next_line(char **line_buf_ptr)
{
    char *line_buf;
    char *next_line;
    int i;
    UBOOT_TRACE("IN\n");

    line_buf = (*line_buf_ptr);

    // strip '\r', '\n' and comment
    while (1)
    {
        // strip '\r' & '\n' & ' ' & '\t'
        if (IS_IGNORED_CHAR(line_buf[0]))
        {
            line_buf++;
        }
        // strip comment
        else if (IS_COMMENT(line_buf[0]))
        {
            for (i = 0; !IS_LINE_END(line_buf[0]) && i <= MAX_LINE_SIZE; i++)
            {
                line_buf++;
            }

            if (i > MAX_LINE_SIZE)
            {
                line_buf[0] = SCRIPT_FILE_END;

                UBOOT_ERROR("Error: the max size of one line is %d!!!\n", MAX_LINE_SIZE); // <-@@@

                break;
            }
        }
        else
        {
            break;
        }
    }

    // get next line
    if (IS_FILE_END(line_buf[0]))
    {
        next_line = NULL;
    }
    else
    {
        next_line = line_buf;

        for (i = 0; !IS_LINE_END(line_buf[0]) && i <= MAX_LINE_SIZE; i++)
        {
            line_buf++;
        }

        if (i > MAX_LINE_SIZE)
        {
            next_line = NULL;

            UBOOT_ERROR("Error: the max size of one line is %d!!!\n", MAX_LINE_SIZE); // <-@@@
        }
        else
        {
            line_buf[0] = '\0';
            *line_buf_ptr = line_buf + 1;
        }
    }
    UBOOT_TRACE("OK\n");

    return next_line;
}

char* loadscript(char *filedir,U32 *filesize)
{
	char *script = NULL;
	UBOOT_TRACE("IN\n");

	*filesize = vfs_getsize(filedir);
	if( (*filesize > SCRIPT_BUFSIZE) || (*filesize == 0) )
	{
		UBOOT_ERROR("No enough buffer or path fail(%s) :\n[%s] [%s]\n",filedir,__FILE__,__FUNCTION__);
		return NULL;
	}

	script = (char *)malloc(*filesize);
	if(script == NULL)
	{
		UBOOT_ERROR("No enough buffer %s %s\n",__FILE__,__FUNCTION__);
		return NULL;
	}
    if(vfs_read((void *)script,filedir,0,(unsigned int)(*filesize))==-1)
    {
        free(script);
        UBOOT_ERROR("Error: vfs_read Fail \n");
		return NULL;
    }
    UBOOT_TRACE("OK\n");
	return script;
}

void runscript_linebyline(char *scriptdir)
{
    char *script = NULL;
    char *TmpScrtip = NULL;
    char *next_line;
	U32 filesize = 0;
    UBOOT_TRACE("IN\n");
	script = loadscript(scriptdir,&filesize);
    TmpScrtip = script;
	if(script != NULL)
	{
        while ((next_line = get_script_next_line(&script)) != NULL)
        {
            UBOOT_INFO("\n>> %s \n", next_line);
            run_command(next_line, 0);
        }
	}
	if(TmpScrtip != NULL)
    {
		free(TmpScrtip);
    }
    UBOOT_TRACE("OK\n");
}

char *pattern_search(char *buf, unsigned int buf_size, char *pattern)
{
    char *ptr=NULL;
    UBOOT_TRACE("IN\n");
    if((buf==NULL)||(pattern==NULL))
    {
        UBOOT_ERROR("One of the parameters is null pointer\n");
        return NULL;
    }
    if(buf_size==0)
    {
        UBOOT_ERROR("The buf_size is 0\n");
        return NULL;
    }

    ptr=buf;
    UBOOT_DEBUG("target=%s,len=0x%x\n",pattern,strlen(pattern));
    while(buf_size)
    {
        if(memcmp(ptr,pattern,strlen(pattern))==0)
        {
            break;
        }
        ptr++;

        if(buf_size==strlen(pattern))
        {
            buf_size=0;
        }
        else
        {
            buf_size--;
        }
    }
    if(buf_size==0)
    {
        UBOOT_DEBUG("Can't find the %s \n",pattern);
        return NULL;
    }
    else
    {
        UBOOT_TRACE("OK\n");
        return ptr;
    }
}

#if defined(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN) && defined (CONFIG_MSTAR_TOOL_PROGRAM)
int do_nandprogramforrom ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	char ciscmd[128];
	int filelength = 0;
	U32 dbgAddress=0;
	//console_disable();
	//write register status Begin

	#if defined(CONFIG_ARM)
	(*(volatile unsigned short*)(0x1F206700)) = 0x2454;
	(*(volatile unsigned short*)(0x1F206704)) = 0x3697;
	(*(volatile unsigned short*)(0x1F206700)) = 0x0000;
	(*(volatile unsigned short*)(0x1F206704)) = 0x0000;
	dbgAddress=0x1F002140;
	#elif defined(CONFIG_MIPS32)
	(*(volatile unsigned short*)(0xBF206700)) = 0x2454;
	(*(volatile unsigned short*)(0xBF206704)) = 0x3697;
	(*(volatile unsigned short*)(0xBF206700)) = 0x0000;
	(*(volatile unsigned short*)(0xBF206704)) = 0x0000;
	dbgAddress=0xBF206720;
	#endif

	(*(volatile unsigned short*)(dbgAddress)) = 0x003A;// jh.huang

	#if defined(CONFIG_ENV_IS_IN_NANDUBI)
	run_command("nand erase.force" , 0);
	#else
	run_command("nand erase.chip" , 0);
	#endif
 	//get file length for register
	(*(volatile unsigned short*)(dbgAddress)) = 0x003b;// jh.huang

	#if defined(CONFIG_ARM)
	filelength = *(volatile unsigned short*)(0x1F206710);
	filelength |= (*(volatile unsigned short*)(0x1F20670C)) << 16;
	#elif defined(CONFIG_MIPS32)
	filelength = *(volatile unsigned short*)(0xBF206710);
	filelength |= (*(volatile unsigned short*)(0xBF20670C)) << 16;
	#endif
	(*(volatile unsigned short*)(dbgAddress)) = 0x003c;// jh.huang
	printf("file length = %d\n", filelength);
	filelength -= 65536*3;
	#if (ENABLE_EAGLE)
	sprintf(ciscmd,"ncisbl 0x44000000 0x44010000 0x44020000 0x44030000 0x%X", filelength);
    #elif (ENABLE_KRITI)
	sprintf(ciscmd,"ncisbl 0x82000000 0x82010000 0x82020000 0x82030000 0x%X", filelength);
	#elif (ENABLE_EMERALD) || (ENABLE_NIKON) || (ENABLE_MILAN) || (ENABLE_KENYA)
	sprintf(ciscmd,"ncisbl 0x84000000 0x84010000 0x84020000 0x84030000 0x%X", filelength);
	#elif (ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_MADISON)  || (ENABLE_CLIPPERS) || (ENABLE_MIAMI) || (ENABLE_NADAL) || (ENABLE_EINSTEIN || ENABLE_NAPOLI)
	filelength -= 0x2800;
	sprintf(ciscmd,"ncishash 0x24000000 0x24010000 0x24020000 0x24030000 0x2800 0x24032800 0x%X", filelength);
	#elif (ENABLE_MONACO)
	filelength -= 0x3800;
	sprintf(ciscmd,"ncishash 0x24000000 0x24010000 0x24020000 0x24030000 0x3800 0x24033800 0x%X", filelength);
	#elif (ENABLE_MUJI)
	filelength -= 0x3800;
	sprintf(ciscmd,"ncishash 0x24000000 0x24010000 0x24020000 0x24030000 0x3800 0x24033800 0x%X", filelength);
	#elif (ENABLE_CELTICS)
	filelength -= 0x3800;
	sprintf(ciscmd,"ncishash 0x24000000 0x24010000 0x24020000 0x24030000 0x3800 0x24033800 0x%X", filelength);
	#elif (ENABLE_NUGGET)
	filelength -= 0x3800;
	(*(volatile unsigned short*)(dbgAddress)) = 0x003d;// jh.huang
	sprintf(ciscmd,"ncishash 0x84000000 0x84010000 0x84020000 0x84030000 0x3800 0x84033800 0x%X 0x3200", filelength);
	(*(volatile unsigned short*)(dbgAddress)) = 0x003e;// jh.huang
	#endif
	printf("CIS Cmd = %s\n", ciscmd);
	(*(volatile unsigned short*)(dbgAddress)) = 0x003d;// jh.huang
	run_command(ciscmd, 0);
	(*(volatile unsigned short*)(dbgAddress)) = 0x003f;// jh.huang
	printf("done\n");
	#if defined(CONFIG_ARM)
	while((*(volatile unsigned short*)(0x1F206700)) != 0x0000);
	#elif defined(CONFIG_MIPS32)
	while((*(volatile unsigned short*)(0xBF206700)) != 0x0000);
	#endif
	(*(volatile unsigned short*)(dbgAddress)) = 0x0040;// jh.huang
	run_command("reset", 0);
	return 0;
}
#endif

#if defined(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN) && defined (CONFIG_MSTAR_TOOL_CMDLINE)
int do_skipnandprogramforrom ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	console_disable();

	run_command("setprogramok", 0);
	udelay(5000000);

	console_init_r();
	return 0;
}
#endif
