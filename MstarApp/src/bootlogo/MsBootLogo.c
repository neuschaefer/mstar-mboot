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
#include <malloc.h>
#include <ShareType.h>
#include <bootlogo/MsBootLogo.h>
#include <bootlogo/MsPoolDB.h>
#include <MsApiJpd.h>
#include <MsApiGEGOP.h>
#include <MsVfs.h>
#include <MsSystem.h>
#include <MsApiPanel.h>
#include <MsUboot.h>
#include <MsDebug.h>
#include <MsRawIO.h>
#include <CusConfig.h>
#include <MsMmap.h>
#include <drvGPIO.h>
#include <MsBoot.h>
#ifdef CONFIG_MSTAR_CLEANBOOT
#include <drvMBX.h>
#include <drvMBXMsgPool.h>
#endif

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#if defined (CONFIG_LOGO_STORE_IN_SPI_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_SPI
#define FLASH_DEFAULT_PARTITION SPI_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME SPI_DEFAULT_VOLUME
#elif defined (CONFIG_LOGO_STORE_IN_NAND_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_NAND
#define FLASH_DEFAULT_PARTITION NAND_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME NAND_DEFAULT_VOLUME
#elif defined  (CONFIG_LOGO_STORE_IN_EMMC_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_MMC
#define FLASH_DEFAULT_PARTITION MMC_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME MMC_DEFAULT_VOLUME
#endif

#define BOOTLOGO_BUFFER_SIZE 0x400000

#if (ENABLE_MSTAR_CLEANBOOT==1)
typedef struct
{
    GFX_DrawRect stRect;
    GFX_BufferInfo stSrcInfo;
    GFX_BufferInfo stDstInfo;
    LogoDispConfigParams stConfig;
} ST_LOGO_CONFIG_PARAMS;
#endif
//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
extern db_struct db_table;

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if CONFIG_MINIUBOOT && (1==CONFIG_LOGO_STORE_IN_MBOOT)
#else
static BOOLEAN bdbtableReady=FALSE;
#endif

#if (ENABLE_MSTAR_CLEANBOOT==1)
static MBX_Result gLogoMBXResult;
#endif

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//ENHANCE_BOOTING_TIME
#if ( CONFIG_VESTEL_MB97 == 1 )
MS_U8 get_cmd_flag(void)
{
    MS_U8 u8OriCmdflag;
    /* read from flash to dram */
#if 0
    static unsigned int spi_size=0;
    MS_BOOL ret =0;

    ret = MDrv_SERFLASH_DetectSize((MS_U32 *)&spi_size);
    if(ret != TRUE)
    {
       printf("detect SPI size fail\n");
       return -1;
    }

    printf("spi_size=0x%x\n",spi_size);

    printf("SPI_MAP_BASE_ADDR=0x%x\n",SPI_MAP_BASE_ADDR);
    printf("SPI_MAP_CMD_ADDR=0x%x\n",SPI_MAP_CMD_ADDR);
#endif

    if (MDrv_SERFLASH_Read((SPI_MAP_BASE_ADDR + SPI_MAP_CMD_ADDR), SPI_MAP_CMD_SIZE, &u8OriCmdflag))
    {
        printf("[CMDFLAG] : get_cmd_flag : %d\n",u8OriCmdflag);
        return u8OriCmdflag;
    }
    else
    {
        printf("[CMDFLAG] : ERROR: SPI DMA fail !!!\n");
        return E_NewSPI; //default 0xFF
    }
}

void set_cmd_flag(MS_U8 u8SetFlag)
{
    u8SetFlag = u8SetFlag;

    MS_U8 cmd_flag;
    MS_U8 *pData;

    if (u8SetFlag == E_NewSPI)
    {
        printf("[CMDFLAG] : Clear CMD Flag \n");
    }
    else
    {
        #if 0
        cmd_flag = get_cmd_flag();

        if(cmd_flag!=0xFF)
        {
            u8SetFlag = u8SetFlag|cmd_flag;
        }
        #endif
        printf("[CMDFLAG] : Set CMD Flag : %d\n", u8SetFlag);
    }
    pData = malloc(SPI_BLOCK_SIZE);
    MDrv_SERFLASH_Read(SPI_MAP_BASE_ADDR, SPI_BLOCK_SIZE, pData);
    memcpy(pData + SPI_MAP_CMD_ADDR, &u8SetFlag, 1);//??
    MDrv_SERFLASH_WriteProtect(0);
    //MDrv_SERFLASH_BlockErase(SPI_OAD_BASE_ADDR, SPI_OAD_BASE_ADDR, TRUE);
    MDrv_SERFLASH_AddressErase(SPI_MAP_BASE_ADDR, SPI_BLOCK_SIZE, TRUE);
    MDrv_SERFLASH_Write(SPI_MAP_BASE_ADDR, SPI_BLOCK_SIZE, pData);
    MDrv_SERFLASH_WriteProtect(1);
    free(pData);
}
#endif

////////////////////////////////////////////////////////////////////////////////
// @brief \b Function Name \b dbtable_init
// @brief \b Description   \b prepare the logo/music/panel/ursa information & data
// @return                 \b dbtable_init_Result
////////////////////////////////////////////////////////////////////////////////

#if !(CONFIG_LOGO_STORE_IN_MBOOT) && !(CONFIG_MINIUBOOT)  && !(CONFIG_MSTAR_TOOL_ROM_PROGRAM_NAND_BIN)
int do_dbtable_init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret =-1;
    int dbtable = 0;
    U32 u32LogoOffset = 0;
    char * p_str = NULL;

//ENHANCE_BOOTING_TIME
#if ( CONFIG_VESTEL_MB97 == 1 )
    MS_U8 u8CmdFlag=0xFF;
#endif

    UBOOT_TRACE("IN\n");

    ret = raw_io_config(FLASH_DEFAULT_TARGET,FLASH_DEFAULT_PARTITION,FLASH_DEFAULT_VOLUME);

    if(ret != 0)
    {
        bdbtableReady=FALSE;
        UBOOT_ERROR("raw_io_config setting fail!\n");
        return -1;
    }

    ret=MsApiChunkHeader_GetValue(CH_UBOOT_POOL_ROM_OFFSET,&u32LogoOffset);
    if(ret != 0)
    {
        bdbtableReady=FALSE;
        UBOOT_ERROR("get logo offset fail!\n");
        return -1;
    }

    UBOOT_DEBUG("u32LogoOffset=0x%x\n",(unsigned int)u32LogoOffset);
    if( (argc > 1) && (strcmp(argv[1],"1")==0))
    {
        UBOOT_DEBUG("sikp db_table\n");

        ret = write_dbtable(u32LogoOffset);
    }
    else
    {
#if (CONFIG_VESTEL_MB97 == 1)   //ENHANCE_BOOTING_TIME
        u8CmdFlag = get_cmd_flag();
        if ( u8CmdFlag != E_NewSPI)
        {
            if ( u8CmdFlag & E_PanelFileUpdate )
            {
                vfs_mount(CONF);
                char as8PanelFilePath[CMD_BUF];
                memset(as8PanelFilePath,0,CMD_BUF);
                U32 filesize = 0;
                snprintf(as8PanelFilePath, sizeof(as8PanelFilePath),"/panel_file_updated.txt");
                filesize = vfs_getsize(as8PanelFilePath);
                if(filesize == 4)
                {
                    setenv("db_table","0");
                    printf("[CMDFLAG] : panel_file_updated.txt, Do db_table 0\n");
                    saveenv();
                }
                vfs_umount();
                set_cmd_flag(u8CmdFlag&(~E_PanelFileUpdate));
            }

            if ( u8CmdFlag & E_LogoUpdated )
            {
                setenv("db_table","0");
                printf("[CMDFLAG] : BootLogo, Do db_table 0\n");
                saveenv();
                set_cmd_flag(u8CmdFlag&(~E_LogoUpdated));
            }
        }
#elif ( CONFIG_VESTEL_MB100 == 1)
        vfs_mount(CONF);
        char as8PanelFilePath[CMD_BUF];
        memset(as8PanelFilePath,0,CMD_BUF);
        U32 filesize = 0;
        snprintf(as8PanelFilePath, sizeof(as8PanelFilePath),"/panel_file_updated.txt");
        filesize = vfs_getsize(as8PanelFilePath);
        if(filesize == 4)
        {
            setenv("db_table","0");
            saveenv();
        }
        vfs_umount();
    #endif
        UBOOT_DEBUG("get db_table\n");
        p_str = getenv ("db_table");
        if(p_str != NULL)
        {

            dbtable = (int)simple_strtol(p_str, NULL, 10);
            UBOOT_DEBUG("db_table=%d\n",dbtable);
            if(dbtable == 0)
            {
                ret =  write_dbtable(u32LogoOffset);

            }
            else
            {
                ret =  read_dbtable(u32LogoOffset);
            }
        }
        else
        {
            UBOOT_DEBUG("No db_table\n");
            ret =  write_dbtable(u32LogoOffset);
        }
    }
    if(ret!=0)
    {
        bdbtableReady=FALSE;
        UBOOT_ERROR("dbtable init fail\n");
    }
    else
    {
        bdbtableReady=TRUE;
        UBOOT_TRACE("OK\n");
    }
    return ret;
}
#endif

#if (CONFIG_LOGO_STORE_IN_MBOOT)
static int LogoInMboot2Dram(U32 Dram_Addr)
{
    int ret = -1;
    U32 u32LogoSize = 0;
    U32 u32LogoOffset = 0;
    UBOOT_TRACE("IN\n");

    ret = mboot_raw_io_Config();
    if(ret != 0)
    {
        UBOOT_ERROR("raw_io_config setting fail!\n");
        return -1;
    }

    ret=MsApiChunkHeader_GetValue(CH_LOGO_ROM_OFFSET,&u32LogoOffset);
    if(ret!=0)
    {
        UBOOT_ERROR("get u32LogoOffset fail\n");
        return -1;
    }
    ret=MsApiChunkHeader_GetValue(CH_LOGO_ROM_SIZE,&u32LogoSize);
    if(ret!=0)
    {
        UBOOT_ERROR("get u32LogoSize fail\n");
        return -1;
    }

    if(raw_read(Dram_Addr,u32LogoOffset,u32LogoSize)!=0)
    {
        UBOOT_ERROR("LogoInMboot2Dram Fail!!\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return u32LogoSize;
}
#else
static unsigned int Load_Photo2Dram(char *SrcPath,U32 Dram_Addr)
{
    U32 u32LogoSize=0;
    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("Dram_Addr=0x%x\n",(unsigned int)Dram_Addr);

    if(SrcPath==NULL)
    {
        if(bdbtableReady!=TRUE)
        {
            UBOOT_ERROR("dbtable is not ready\n");
            return -1;
        }

        UBOOT_DEBUG("No SrcPath\n");
        if(-1 == Read_LogoToDisplayAddr(Dram_Addr)) //read logo from spi/emmc to dram
        {
            UBOOT_ERROR("Error: Read_LogoToDisplayAddr Fail\n");
            return 0;
        }
        u32LogoSize = db_table.logo_size;
        UBOOT_DEBUG("u32LogoSize=0x%x\n",(unsigned int)u32LogoSize);
    }
    else // from nand/emmc directly
    {
        char PathBuf[128] = "\0";


        #if 0
        vfs_mount(CUSTOMER);
        snprintf(PathBuf, sizeof(PathBuf), "%s/%s",CUSTOMER_PATH,SrcPath);
        #else
        vfs_mount(CONF);
        snprintf(PathBuf, sizeof(PathBuf), "%s/%s",CUSTOMER_LOGO_PATH,SrcPath);
        #endif
        UBOOT_DEBUG("PathBuf=%s\n",PathBuf);
        u32LogoSize = vfs_getsize(PathBuf);
        UBOOT_DEBUG("u32LogoSize=0x%x\n",(unsigned int)u32LogoSize);
        vfs_read((void *)Dram_Addr,PathBuf,0,u32LogoSize);

    }
    UBOOT_TRACE("OK\n");
    return u32LogoSize;
}
#endif

#if (ENABLE_MSTAR_CLEANBOOT==1)
MS_BOOL MApi_Logo_MailBox_Init(void)
{
    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_CB_LOGO_NOWAIT, 8))
    {
        UBOOT_ERROR("MApi_Logo_MailBox_Init - MBX register msg E_MBX_CLASS_CB_LOGO_NOWAIT error\n");
        return FALSE;
    }
    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_CB_CHECK_NOWAIT, 8))
    {
        UBOOT_ERROR("MApi_Logo_MailBox_Init - MBX register msg E_MBX_CLASS_CB_CHECK_NOWAIT error\n");
        return FALSE;
    }

    UBOOT_DEBUG("MApi_Logo_MailBox_Init - MBX register msg success\n");
    return TRUE;
}

MS_BOOL MApi_Logo_MailBox_Deinit(void)
{
    if( E_MBX_SUCCESS != MDrv_MBX_UnRegisterMSG(E_MBX_CLASS_CB_LOGO_NOWAIT, TRUE))
    {
        printf("@@ E_MBX_CLASS_CB_LOGO_NOWAIT - MBX unregister msg error\n");
    }
    return TRUE;
}

static void MApi_Logo_MailBox_Handler(MBX_Class eMsgClass)
{
    MBX_Msg MB_Command;

    if(eMsgClass != E_MBX_CLASS_CB_LOGO_NOWAIT)
    {
        printf("Invalid Message Class!\n");
        return;
    }

    gLogoMBXResult = MDrv_MBX_RecvMsg(eMsgClass, &MB_Command, 3000, MBX_CHECK_INSTANT_MSG);//MBX_CHECK_NORMAL_MSG);

    if (gLogoMBXResult == E_MBX_ERR_TIME_OUT)
    {
        UBOOT_DEBUG("Handler Timeout!\n");
        return;
    }

    if (gLogoMBXResult == E_MBX_SUCCESS)
    {
        MS_U8 i;
        if ((MB_Command.u8Ctrl != 0) && (MB_Command.u8Ctrl != 1))
        {
            UBOOT_DEBUG("Not Implemented!\n");
            return;
        }

        //printf("Get  command: 0x%02x, 0x%02x\n", MB_Command.u8Index, MB_Command.u8ParameterCount);
        for(i=0; i<MB_Command.u8ParameterCount; i++)
        {
            UBOOT_DEBUG("Parameter[%d]=0x%02x\n", i, MB_Command.u8Parameters[i]);
        }
    }

    return;
}

MS_BOOL MApi_Logo_MailBox_SendMsg(U32 u32Addr,  MS_U8 u8Mirr)
{
    MBX_Msg MB_Command;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));

    //(1) send to CB
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_CB_LOGO_NOWAIT;
    MB_Command.u8Index = 0;
    MB_Command.u8ParameterCount = 5;
    MB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32Addr&0xFF);
    MB_Command.u8Parameters[4] =  u8Mirr;
    printf(" -MDrv_MBX_SendMsg u8Parameters[0]:0x%x, MDrv_MBX_SendMsg u8Parameters[1]:0x%x\n",MB_Command.u8Parameters[0],MB_Command.u8Parameters[1]);
    printf(" -MDrv_MBX_SendMsg u8Parameters[2]:0x%x, MDrv_MBX_SendMsg u8Parameters[3]:0x%x\n",MB_Command.u8Parameters[2],MB_Command.u8Parameters[3]);
//    Change2R2();

    MDrv_MBX_SendMsg(&MB_Command);

    //(2) Waiting for message done
    do
    {
        MApi_Logo_MailBox_Handler(E_MBX_CLASS_CB_LOGO_NOWAIT);
    }while((gLogoMBXResult != E_MBX_SUCCESS) && (gLogoMBXResult != E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(gLogoMBXResult == E_MBX_ERR_TIME_OUT)
    {
        UBOOT_ERROR("MApi_Logo_MailBox_SendMsg Fail\n");
    }
    else
    {
        UBOOT_DEBUG("OK\n");
    }

    return gLogoMBXResult;
}

MS_U16 BootLogo_MailBox_Check_Panel_Init(void)
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));

    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_CB_CHECK_NOWAIT;
    stMB_Command.u8Index = 0;
    stMB_Command.u8ParameterCount = 1;
    stMB_Command.u8Parameters[0] =  (U8)(E_MSGQ_R2TASK_PNL);
    MDrv_MBX_SendMsg(&stMB_Command);
//    printf("BootLogo_MailBox_Check_Panel_Init - MDrv_MBX_SendMsg line:%d \n",__LINE__);

    //(2) Waiting for message done
    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    do{
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_CB_CHECK_NOWAIT, &stMB_Command, 5000, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("Test_Check_Panel Fail\n");
    }
    else
    {
        enMbxResult = stMB_Command.u8Parameters[0];
        //      printf("Test_Check_Panel OK enMbxResult:%d, count::%d \n",enMbxResult, stMB_Command.u8ParameterCount);
    }

    return enMbxResult;
}
#endif //(ENABLE_MSTAR_CLEANBOOT==1)

int showLogo(LogoDispConfigParams stConfig,U32 JPD_OUTADDR)
{
    GFX_BufferInfo src_info, dst_info;
    GFX_DrawRect rect;
    MS_BOOL bHorStretch=stConfig.bHorStretch;
    MS_BOOL bVerStretch=stConfig.bVerStretch;
    U32 u32Addr=0;
    extern U8 g_logoMiuIdx;
    extern U8 bDelayLogo;
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


#if (CONFIG_MINIUBOOT || ENABLE_BOOT_SPI_ECOS)
    u32Addr = MMAP_E_DFB_FRAMEBUFFER_ADDR;
#else

    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &u32Addr)!=0)
    {
        //UBOOT_ERROR("get E_DFB_FRAMEBUFFER_ADR mmap fail\n");
        return -1;
    }



    char *cmdline = getenv ("bootargs");
    if (cmdline)
    {
        if (strstr(cmdline, "delaylogo=true") != NULL && (!isBootToRecovery()))
        {
            // use the PVR buffer to store bootlogo,
            // because the DFB buffer will be cleared during booting up
            MMapInfo_s mmapinfo = {0};
            char bootlogo_buffer[32] = "E_MMAP_ID_PVR_DOWNLOAD";
            char *p_str = NULL;

            // check if users define another buffer to store the bootlogo
            if ((p_str = getenv("bootlogo_buffer")) != NULL)
            {
                    memset(bootlogo_buffer, 0, 32);
                    strncpy(bootlogo_buffer, p_str ,sizeof(bootlogo_buffer)-1);
            }

            if (get_mmap(bootlogo_buffer, &mmapinfo) == 0)
            {
                if (mmapinfo.u32Size > BOOTLOGO_BUFFER_SIZE)
                {
                    if (get_addr_from_mmap(bootlogo_buffer, &u32Addr) != 0)
                    {
                        UBOOT_ERROR("fail to delay bootlogo because cannot get the size of %s\n", bootlogo_buffer);
                        return -1;
                    }

                    g_logoMiuIdx = mmapinfo.u32miuID;
                    bDelayLogo = TRUE;
                }
                else
                {
                    UBOOT_ERROR("fail to delay bootlogo because the size of buffer is less than 4MB (1366*768 *ARGB)");
                    return -1;
                }
            }
            else
            {
                UBOOT_ERROR("fail to delay bootlogo because cannot get the mmapinfo of %s\n", bootlogo_buffer);
                return -1;
            }
        }
    }

    if(u32Addr==0xFFFF)
    {
        UBOOT_ERROR("Get Mmap for GOP Failed !!! \n");
        return -1;
    }

#endif
    dst_info.u32Addr = (MS_PHYADDR) u32Addr;

    UBOOT_DEBUG("dst_info.u32Addr=0x%x\n",(unsigned int)dst_info.u32Addr);

    dst_info.u32ColorFmt = GFX_FMT_YUV422;
    UBOOT_DEBUG("dst_info.u32ColorFmt=0x%x\n",(unsigned int)dst_info.u32ColorFmt);

    rect.srcblk.x = 0;
    UBOOT_DEBUG("rect.srcblk.x=0x%x\n",(unsigned int)rect.srcblk.x);

    rect.srcblk.y = 0;
    UBOOT_DEBUG("rect.srcblk.y=0x%x\n",(unsigned int)rect.srcblk.y);

    rect.srcblk.width = JPG_GetAlignmentWidth()/*u16Pitch*/;
    UBOOT_DEBUG("rect.srcblk.width=0x%x\n",(unsigned int)rect.srcblk.width);


    rect.srcblk.height = JPG_GetAlignmentHeight();
    UBOOT_DEBUG("rect.srcblk.height=0x%x\n",(unsigned int)rect.srcblk.height);

    rect.dstblk.x = 0;
    UBOOT_DEBUG("rect.dstblk.x=0x%x\n",(unsigned int)rect.dstblk.x);

    rect.dstblk.y = 0;
    UBOOT_DEBUG("rect.dstblk.y=0x%x\n",(unsigned int)rect.dstblk.y);

    #if (ENABLE_MSTAR_KENYA == 1||ENABLE_MSTAR_KERES==1)
        rect.dstblk.width  = ((g_IPanel.Width()+15)&0xFFFFF0)/*u16Pitch*/;
        rect.dstblk.height = g_IPanel.Height();

        dst_info.u32Width  = (U32)((g_IPanel.Width()+15)&0xFFFFF0);
        dst_info.u32Pitch  = (U32)(((g_IPanel.Width()+15)&0xFFFFF0)<<1);
        dst_info.u32Height = g_IPanel.Height();
    #else
    if( JPG_GetAlignmentWidth() > g_IPanel.Width())
    {
        rect.dstblk.width = ((g_IPanel.Width()+15)&0xFFFFF0)/*u16Pitch*/;
        dst_info.u32Width = (U32)((g_IPanel.Width()+15)&0xFFFFF0);
        dst_info.u32Pitch = (U32)(((g_IPanel.Width()+15)&0xFFFFF0)<<1);
    }
    else
    {
        rect.dstblk.width = ((JPG_GetAlignmentWidth()+15)&0xFFFFF0)/*u16Pitch*/;
        dst_info.u32Width = (U32)((JPG_GetAlignmentWidth()+15)&0xFFFFF0);
        dst_info.u32Pitch = (U32)(((JPG_GetAlignmentPitch()+15)&0xFFFFF0)<<1);
    }
    UBOOT_DEBUG("rect.dstblk.width=0x%x\n",(unsigned int)rect.dstblk.width);
    UBOOT_DEBUG("dst_info.u32Width=0x%x\n",(unsigned int)dst_info.u32Width);
    UBOOT_DEBUG("dst_info.u32Pitch=0x%x\n",(unsigned int)dst_info.u32Pitch);

    if( JPG_GetAlignmentHeight() > g_IPanel.Height())
    {
        rect.dstblk.height = g_IPanel.Height();
        dst_info.u32Height = g_IPanel.Height();
    }
    else
    {
        rect.dstblk.height = JPG_GetAlignmentHeight();
        dst_info.u32Height = (U32)JPG_GetAlignmentHeight();
    }
    UBOOT_DEBUG("rect.dstblk.height=0x%x\n",(unsigned int)rect.dstblk.height);
    UBOOT_DEBUG("dst_info.u32Height=0x%x\n",(unsigned int)dst_info.u32Height);
    #endif


#if (ENABLE_MSTAR_CLEANBOOT==1)
    UBOOT_TRACE("Show logo by CleanBoot in R2\n");
    if (TRUE == MApi_Logo_MailBox_Init())
    {
        static ST_LOGO_CONFIG_PARAMS stLogoParams;
        MS_U8 u8Mirror = 0;

        char * p_str = getenv ("MIRROR_ON");
        if(p_str != NULL)
        {
            u8Mirror = simple_strtol(p_str, NULL, 10);
        }
        memset(&stLogoParams, 0x00, sizeof(stLogoParams));
        memcpy(&stLogoParams.stRect, &rect, sizeof(rect));
        memcpy(&stLogoParams.stSrcInfo, &src_info, sizeof(src_info));
        memcpy(&stLogoParams.stDstInfo, &dst_info, sizeof(dst_info));
        memcpy(&stLogoParams.stConfig, &stConfig, sizeof(stConfig));
        flush_cache((MS_U32)(&stLogoParams), sizeof(stLogoParams));
        MApi_Logo_MailBox_SendMsg(MsOS_VA2PA((MS_U32)(&stLogoParams)), u8Mirror);
    }
#else //(ENABLE_MSTAR_CLEANBOOT==1)
    MsApiDisplay_Logo(&rect,&src_info,&dst_info,bHorStretch,bVerStretch,stConfig.u16DispX,stConfig.u16DispY);
#endif //(ENABLE_MSTAR_CLEANBOOT==1)
    UBOOT_TRACE("OK\n");
    return 1;
}

int do_bootlogo (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    U32 u32LogoSize=0;
    U32 JPD_InputADDR=0;
    U32 JPD_OUTADDR=0;
    char *PhotoPath=NULL;
    LogoDispConfigParams stConfig;
    UBOOT_TRACE("IN\n");

#if (CONFIG_MINIUBOOT || ENABLE_BOOT_SPI_ECOS)
    JPD_InputADDR = MMAP_E_MMAP_ID_JPD_READ_ADDR;
    JPD_OUTADDR = MMAP_E_MMAP_ID_JPD_WRITE_ADDR;
#else

    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &JPD_InputADDR)!=0)
    {
        UBOOT_ERROR("get E_DFB_FRAMEBUFFER_ADR mmap fail\n");
    }
#if (CONFIG_VESTEL_MB100 == 1)
    if(get_addr_from_mmap("E_MMAP_ID_JPD_WRITE", &JPD_OUTADDR)!=0)  //MB100_BRINGUP
    {
        UBOOT_ERROR("get E_MMAP_ID_JPD_WRITE mmap fail\n");

    }
#else
    if(get_addr_from_mmap("E_MMAP_MAD_JPEG_DISPLAY_ADR", &JPD_OUTADDR)!=0)
    {
        UBOOT_ERROR("get E_MMAP_MAD_JPEG_DISPLAY_ADR mmap fail\n");

    }
#endif

#endif
    JPD_InputADDR=PA2NVA(JPD_InputADDR);//PA2NVA

    if(JPD_InputADDR==0xFFFF || JPD_OUTADDR==0xFFFF )
    {
        UBOOT_ERROR("Get Mmap for JPD Failed Skip BootLogo !!! \n");
        return -1;
    }

    if(argc > 4)
    {
        stConfig.u16DispX = simple_strtoul(argv[1], NULL, 10);
        stConfig.u16DispY = simple_strtoul(argv[2], NULL, 10);
        stConfig.bHorStretch = simple_strtoul(argv[3], NULL, 10);
        stConfig.bVerStretch = simple_strtoul(argv[4], NULL, 10);
    }
    else
    {
        stConfig.u16DispX = 0;
        stConfig.u16DispY = 0;
        stConfig.bHorStretch = 1;
        stConfig.bVerStretch = 1;
    }

    if(IsPanelReady()!=0)
    {
        UBOOT_ERROR("Panle is not ready\n");
        return -1;
    }
    UBOOT_DEBUG("u16DispX=0x%x,u16DispY=0x%x,bHorStretch=0x%x,bVerStretch=0x%x\n",stConfig.u16DispX,stConfig.u16DispY,stConfig.bHorStretch,stConfig.bVerStretch);
    if(argc > 5)
    {
        PhotoPath = argv[5];
        UBOOT_DEBUG("PhotoPath=%s\n",PhotoPath);
    }
#if (CONFIG_LOGO_STORE_IN_MBOOT)
    u32LogoSize = LogoInMboot2Dram(JPD_InputADDR);
#else
    u32LogoSize = Load_Photo2Dram(PhotoPath,JPD_InputADDR);
#endif

    UBOOT_DEBUG("u32LogoSize : 0x%x \n",u32LogoSize);
    if(u32LogoSize == 0)
    {
        UBOOT_ERROR("Fail: Load_Photo2Dram return size is 0 !!\n");
        return -1;
    }

    MsApi_JPD_Decode(JPD_InputADDR, u32LogoSize);
    showLogo(stConfig,JPD_OUTADDR);

    UBOOT_TRACE("OK\n");
    return 0;
}

#if (ENABLE_MODULE_POWER_MUSIC == 1)
#include <MsApiAudio.h>
#include <audio/MsDrvAudio.h>

int Load_Music2Dram(char *MusicPath,U32 Dram_Addr)
{
    U32 musicSize=0;
    UBOOT_TRACE("IN\n");

    if(MusicPath == NULL)
    {
        UBOOT_DEBUG("MusicPath is a null pointer\n");
        UBOOT_DEBUG("Dram_Addr=0x%x\n",Dram_Addr);
        //read music from spi/emmc to dram defalut logo
        if(Read_MusicToPlayAddr(Dram_Addr)!=0)
        {
            UBOOT_ERROR("Read_MusicToPlayAddr() failed\n");
            return -1;
        }
    }
    else // from nand/emmc directly
    {
        char PathBuf[128] = "\0";
        vfs_mount(CUSTOMER);
        snprintf(PathBuf, sizeof(PathBuf), "%s/%s",CUSTOMER_PATH,MusicPath);
        UBOOT_DEBUG("PathBuf=%s\n",PathBuf);
        musicSize = vfs_getsize(PathBuf);
        UBOOT_DEBUG("musicSize=0x%x,Dram_Addr=0x%x\n",(unsigned int)musicSize,(unsigned int)Dram_Addr);
        if(vfs_read((void *)(PA2NVA(Dram_Addr)),PathBuf,0,musicSize)==-1)
        {
            UBOOT_ERROR("vfs_read fail\n");
            return -1;
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

#if (ENABLE_MSTAR_CLEANBOOT==1)
static MBX_Result gMusicMBXResult;

MS_BOOL MApi_Music_MailBox_Init(void)
{
    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_CB_MUSIC_NOWAIT, 8))
    {
        UBOOT_ERROR("MApi_Music_MailBox_Init - MBX register msg error\n");
        return FALSE;
    }
    UBOOT_DEBUG("MApi_Music_MailBox_Init - MBX register msg success\n");
    return TRUE;
}

MS_BOOL MApi_Music_MailBox_Deinit(void)
{
    if( E_MBX_SUCCESS != MDrv_MBX_UnRegisterMSG(E_MBX_CLASS_CB_MUSIC_NOWAIT, TRUE))
    {
        UBOOT_ERROR("@@ E_MBX_CLASS_CB_MUSIC_NOWAIT - MBX unregister msg error\n");
    }
    return TRUE;
}

static void MApi_Music_MailBox_Handler(MBX_Class eMsgClass)
{
    MBX_Msg MB_Command;

    if(eMsgClass != E_MBX_CLASS_CB_MUSIC_NOWAIT)
    {
        printf("Invalid Message Class!\n");
        return;
    }

    gMusicMBXResult = MDrv_MBX_RecvMsg(eMsgClass, &MB_Command, 3000, MBX_CHECK_INSTANT_MSG);

    if (gMusicMBXResult == E_MBX_ERR_TIME_OUT)
    {
        UBOOT_DEBUG("Handler Timeout!\n");
        return;
    }

    if (gMusicMBXResult == E_MBX_SUCCESS)
    {
        MS_U8 i;
        if ((MB_Command.u8Ctrl != 0) && (MB_Command.u8Ctrl != 1))
        {
            UBOOT_DEBUG("Not Implemented!\n");
            return;
        }

        //printf("Get  command: 0x%02x, 0x%02x\n", MB_Command.u8Index, MB_Command.u8ParameterCount);
        for(i=0; i<MB_Command.u8ParameterCount; i++)
        {
            UBOOT_DEBUG("Parameter[%d]=0x%02x\n", i, MB_Command.u8Parameters[i]);
        }
    }

    return;
}

MS_BOOL MApi_Music_MailBox_SendMsg(MS_U8 u8Vol)
{
    MBX_Msg MB_Command;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));

    //(1) send to CB
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_CB_MUSIC_NOWAIT;
    MB_Command.u8Index = 0;
    /*
        MB_Command.u8ParameterCount = 8;
        MB_Command.u8Parameters[0] =  (U8)(u32Addr0>>24);
        MB_Command.u8Parameters[1] =  (U8)(u32Addr0>>16);
        MB_Command.u8Parameters[2] =  (U8)(u32Addr0>>8);
        MB_Command.u8Parameters[3] =  (U8)(u32Addr0&0xFF);
        MB_Command.u8Parameters[4] =  (U8)(u32Addr1>>24);
        MB_Command.u8Parameters[5] =  (U8)(u32Addr1>>16);
        MB_Command.u8Parameters[6] =  (U8)(u32Addr1>>8);
        MB_Command.u8Parameters[7] =  (U8)(u32Addr1&0xFF);
    */
    MB_Command.u8ParameterCount = 1;
    MB_Command.u8Parameters[0] =  u8Vol;
//    Change2R2();
    MDrv_MBX_SendMsg(&MB_Command);

    //(2) Waiting for message done
    do
    {
        MApi_Music_MailBox_Handler(E_MBX_CLASS_CB_MUSIC_NOWAIT);
    }
    while((gMusicMBXResult != E_MBX_SUCCESS) && (gMusicMBXResult != E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(gMusicMBXResult == E_MBX_ERR_TIME_OUT)
    {
        UBOOT_ERROR("MApi_Music_MailBox_SendMsg Fail\n");
    }
    else
    {
        UBOOT_DEBUG("OK\n");
    }

    return gMusicMBXResult;
}

#endif //(ENABLE_MSTAR_CLEANBOOT==1)


int do_bootmusic (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = 0;
    char *MusicPath = NULL;
    U32 u32EsStartAddr = 0;

    UBOOT_TRACE("IN\n");
    if(argc > 1)
    {
        MusicPath = argv[1];
    }

    if(bdbtableReady!=TRUE)
    {
        UBOOT_ERROR("dbtable is not ready\n");
        return -1;
    }

    Adj_Volume_Off();      //
    Audio_Amplifier_OFF(); //
    ret =MsDrv_AudioPreInit();

    if(ret==-1)
    {
        UBOOT_ERROR("Get Mmap for Audio Fail Skip Power Music !!! \n");
        return -1;
    }

    u32EsStartAddr = MsDrv_GetEsStartAddr();

    ret = Load_Music2Dram(MusicPath, u32EsStartAddr);
    if(ret==-1)
    {
        UBOOT_ERROR("load music to dram fail\n");
    }
    else
    {
#if (ENABLE_MSTAR_CLEANBOOT==1)
        UBOOT_TRACE("Play music by CleanBoot in R2\n");
#if (!CONFIG_SIM_Amplifier)
        drvAudio_AMP_Init();
#endif

        if (TRUE == MApi_Music_MailBox_Init())
        {
            MS_U8 u8Volum = 0;
            char * p_vol = NULL;
            if((p_vol =getenv ("music_vol"))!=NULL)
            {
                u8Volum = (MS_U8)simple_strtol(p_vol, NULL, 10);
            }

            MApi_Music_MailBox_SendMsg(u8Volum);
        }
#else //(ENABLE_MSTAR_CLEANBOOT==1)
        //   MsOS_DelayTask(2000);
        play_powermusic_main();
#endif //(ENABLE_MSTAR_CLEANBOOT==1)

        UBOOT_TRACE("OK\n");
    }
    return ret;
}
#endif


