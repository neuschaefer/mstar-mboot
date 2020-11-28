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
#include <MsTypes.h>

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <drvBDMA.h>
#include <bootlogo/MsPoolDB.h>
#include <MsVfs.h>
#include <MsUtility.h>
#include <MsDebug.h>
#include <MsSystem.h>
#include <MsRawIO.h>
#include <drvSERFLASH.h>
#include <CusConfig.h>
#include <MsMmap.h>

#include <uboot_mmap.h>
#include <bootlogo/iniparser.h>
#include <bootlogo/MsBootLogo.h>



#if (CONFIG_URSA_6M30)
#include <../drivers/mstar/ursa/ursa_6m30.h>
#endif

#if (ENABLE_URSA_8 ==1 )
#include <../drivers/mstar/ursa/ursa_8.h>
#endif

#if (ENABLE_URSA_6M40==1 )
#include <../drivers/mstar/ursa/ursa_6m40.h>
#endif

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
db_struct db_table;
static char gPnlPath[BUFFER_SIZE];
static char gBoardPath[BUFFER_SIZE];
static char gLogoPath[BUFFER_SIZE];
static char gMusicPath[BUFFER_SIZE];
static char gKeypadPath[BUFFER_SIZE];
//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern char * strncpy(char * dest,const char *src,size_t count);
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
int Load_LogoToFlash(void);
int Load_PanelSetting_ToFlash(void);
int Load_BoardSetting_ToFlash(void);
int Load_KeypadSetting_ToFlash(void);
int Load_MusicToFlash(void);



void count_data_crc32_setenv(U32 addr,int size,char *name);
int count_data_crc32_getenv(U32 addr,int size,char *name);
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

int parse_sys_ini(char* path,char* ModelPath)
{
    int ret = -1;
    char *script = NULL;
    char str[BUFFER_SIZE];
    U32 filesize = 0;
    UBOOT_TRACE("IN\n");

    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        goto exit;
    }
    UBOOT_INFO("sizeof( sys ini script ) --------> %u bytes\n",filesize);
    Profile_Init((char *)script,filesize);

    // select mode via project id
    if(Profile_GetBoolean("select_model_via_project_id", "bEnabled",0) == TRUE)
    {
        U16 u16MaxProjectID  = 0xffff;
        char cTempBuffer[BUFFER_SIZE]= {0};
        U32 u32ProjectIdAddr = 0;
        U32 u32ProjectIdBackupAddr = 0;
        U32 u32ProjectId;

        u16MaxProjectID = Profile_GetInteger("select_model_via_project_id", "MAX_MODEL_INDEX", 1);
        u32ProjectIdAddr = Profile_GetInteger("select_model_via_project_id", "project_id_spi_addr", 0);
        flush_cache((MS_PHYADDR)&u32ProjectId, sizeof(u32ProjectId));
        
        if(0 != raw_read((U32)(&u32ProjectId), u32ProjectIdAddr, sizeof(u32ProjectId)))
        {
            UBOOT_ERROR("ERROR: read project id fail...>>>\n");
            goto exit;
        }
        else
        {
            UBOOT_DEBUG("read project id success...\n");
            UBOOT_DEBUG("project id is [0x%08x]\n", u32ProjectId);

            // Read Data from backup
            if((u32ProjectId > u16MaxProjectID) || (u32ProjectId == 0x0000))
            {
                u32ProjectIdBackupAddr = Profile_GetInteger("select_model_via_project_id", "project_id_backup_spi_addr", 0);
                if(0 != raw_read((U32)(&u32ProjectId), u32ProjectIdBackupAddr, sizeof(u32ProjectId)))
                {
                    UBOOT_ERROR("ERROR: read backup project id fail...>>>\n");
                    goto exit;
                }
                else
                {
                    if((u32ProjectId > u16MaxProjectID) || (u32ProjectId == 0x0000)) //set to default project ID
                    {
                        u32ProjectId = 1;
                    }
                }
            }
        }
        flush_cache((U32)&u32ProjectId, sizeof(u32ProjectId));
        Chip_Flush_Memory();

        snprintf(cTempBuffer, BUFFER_SIZE, "Model_%d", u32ProjectId);

        if(Profile_GetString("select_model_via_project_id", cTempBuffer, "", str, sizearray(str)))
        {
            UBOOT_INFO("Half model.ini path --> %s\n",str);
            snprintf(ModelPath, BUFFER_SIZE, "%s",str);
            UBOOT_INFO("Full model.ini  path --> %s\n",ModelPath);
            ret = 0;
        }
        else////Can't find the Model, use the default Model.
        {
            snprintf(cTempBuffer, BUFFER_SIZE, "Model_1");
            if(Profile_GetString("select_model_via_project_id", cTempBuffer, "", str, sizearray(str)))
            {
                printf("Half model.ini path --> %s\n",str);
                snprintf(ModelPath, BUFFER_SIZE, "%s",str);
                printf("Full model.ini  path --> %s\n",ModelPath);
                ret = 0;
            }
            else
            {
                printf("Please check the sys ini, thers is no Model_1 on it!\n");
            }
        }
    }
    else
    {
        if(Profile_GetString("model", "gModelName", "", str, sizearray(str)))
        {
            UBOOT_INFO("Half model.ini path --> %s\n",str);
            snprintf(ModelPath, BUFFER_SIZE, "%s",str);
            UBOOT_INFO("Full model.ini  path --> %s\n",ModelPath);
            ret = 0;
        }
    }

exit:
    if(script)
        free(script);
    UBOOT_TRACE("OK\n");
    return ret;
}

int parse_model_ini(char* path, char* PnlPath, char* BoardPath)
{
    int ret = -1;//
    char *script = NULL;
    char *panel_name = NULL;
    char str[BUFFER_SIZE];
    U32 filesize = 0;
    UBOOT_TRACE("IN\n");
    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        while (*path== '/') path++;
        path=strstr(path,"/");
        UBOOT_INFO("filter /config, and find file again!!\n");
        script = loadscript(path,&filesize);
        if(script == NULL)
        {
            goto exit;
        }
    }
    UBOOT_INFO("sizeof( model ini script ) --------> %u bytes\n",filesize);

    panel_name = "m_pPanelName";

    Profile_Init((char *)script,filesize);
    if(Profile_GetString("panel", panel_name,"", str, sizearray(str)))
    {
        UBOOT_INFO("Half panel.ini path --> %s\n",str);
        snprintf(PnlPath,BUFFER_SIZE,"%s",str);
        UBOOT_INFO("Full panel.ini  path --> %s\n",PnlPath);
        ret = 0;
    }
    else
    {
        goto exit;
    }

    if(Profile_GetString("board", "m_pBoardName","", str, sizearray(str)))
    {
        UBOOT_INFO("Half board.ini path --> %s\n",str);
        snprintf(BoardPath,BUFFER_SIZE,"%s",str);
        UBOOT_INFO("Full board.ini  path --> %s\n",BoardPath);
        ret = 0;
    }
    else
    {
        goto exit;
    }

#if (CONFIG_PANEL_INIT == 1)
    memset(str,0,sizeof(str));
    int n = Profile_GetInteger("PANEL_SWING_LEVEL", "SWING_LEVEL", -1);

    if (n >= 0)
    {
        snprintf(str,sizeof(str),"%u",n);
        UBOOT_INFO("swing_level -> [%s]\n",str);
        setenv("swing_level",str);
    }
    else
    {
        setenv("swing_level","250");
    }
#endif
#if (ENABLE_MSTAR_BD_MST036B_EDISON_CUS19 == 1)
    memset(str,0,sizeof(str));
    if(Profile_GetString("force_upgrade", "force_upgrade_path","", str, sizearray(str)))
        setenv(Force_Upgrade_Path,str);
    else
        printf("Set force_upgrade_path fail!\n");
#endif

    if(Profile_GetString("MISC_MIRROR_CFG", "MIRROR_OSD","", str, sizearray(str)))
    {
        UBOOT_INFO("MIRROR_OSD is  --> %s\n",str);
        if((strcmp(str, "True") == 0)||(strcmp(str, "1") == 0))
        {
            setenv(MIRROR_ON,"1");
        }
        else if((strcmp(str, "False") == 0)||(strcmp(str, "0") == 0))
        {
            setenv(MIRROR_ON,"0");
        }
        else
        {

            UBOOT_INFO("MIRROR_OSD is  [True] or [False], other value can not be parsed\n");
        }
    }
    else
    {
        goto exit;
    }
exit:
    if(script)
        free(script);
    UBOOT_TRACE("OK\n");
    return ret;
}

int parse_boot_ini(char* path)
{
    int ret = 0;//
    int n = 0;
    char *script = NULL;
    char str[BUFFER_SIZE];
    U32 filesize = 0;
    char *tmp;
    UBOOT_TRACE("IN\n");
    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        ret = -1;
        goto exit;
    }
    UBOOT_INFO("sizeof( boot ini script ) --------> %u bytes\n",filesize);
    Profile_Init((char *)script,filesize);

    //Music
    #if (CONFIG_BINARY_RELEASE)
    snprintf(gMusicPath,sizeof(gMusicPath),"%s/%s",CUSTOMER_PATH, MUSIC_FILE);
    #else
    if(Profile_GetString("MUSIC_CFG", "MUSIC_NAME","", str, sizearray(str)))
    {
        snprintf(gMusicPath,sizeof(gMusicPath),"%s/%s",CUSTOMER_PATH,str);
    }
    else
    {
        // use default music file
        UBOOT_DEBUG("no MUSIC_NAME in %s, use default music file\n",path);
        snprintf(gMusicPath,sizeof(gMusicPath),"%s/boot0.mp3",CUSTOMER_PATH);
    }
    UBOOT_INFO("gMusicPath --> %s\n",gMusicPath);
    #endif

    //Logo
    #if (CONFIG_BINARY_RELEASE)
    snprintf(gLogoPath, sizeof(gLogoPath), "%s/%s", CUSTOMER_PATH, LOGO_FILE);
    #else
    if(Profile_GetString("LOGO_CFG", "LOGO_NAME","", str, sizearray(str)))
    {
        //snprintf(gLogoPath,sizeof(gLogoPath),"%s/%s",CUSTOMER_PATH,str);
        snprintf(gLogoPath,sizeof(gLogoPath),"%s/%s",CUSTOMER_LOGO_PATH,str);
    }
    else
    {
        // use default logo file
        UBOOT_DEBUG("no LOGO_NAME in %s, use default logo file\n",path);
        //snprintf(gLogoPath,sizeof(gLogoPath),"%s/boot0.jpg",CUSTOMER_PATH);
        snprintf(gLogoPath,sizeof(gLogoPath),"%s/boot0.jpg",CUSTOMER_LOGO_PATH); 
    }


    UBOOT_INFO("gLogoPath --> %s\n",gLogoPath);
    #endif

    //Music volume
    memset(str,0 ,sizeof(str));
    tmp = getenv("music_vol");
    if (tmp != NULL)
    {
        n = (int)simple_strtol(tmp, NULL, 10);
    }
    else
    {
        n = Profile_GetInteger("MUSIC_VOL_CFG", "MUSIC_VOL", 0);
    }

    if((n >= 0)&&(n <= 0x7F))
    {
        snprintf(str,sizeof(str),"0x%x",n);
        UBOOT_INFO("music_vol -> [%s]\n",str);
        setenv("music_vol",str);
    }
    else
    {
        setenv("music_vol","30");
    }

exit:
    if(script)
        free(script);
    UBOOT_TRACE("OK\n");
    return ret;
}


int parse_ini(void)
{
    int ret = -1;//
    char InPath[BUFFER_SIZE];
    char OutPath[BUFFER_SIZE];
    memset(gPnlPath,0,sizeof(gPnlPath));
    memset(gBoardPath,0,sizeof(gBoardPath));     
    memset(gMusicPath,0,sizeof(gMusicPath));     
    memset(gLogoPath,0,sizeof(gLogoPath));
    memset(gKeypadPath,0,sizeof(gKeypadPath));   
    UBOOT_TRACE("IN\n");
    vfs_mount(CONFIG);
    memset(InPath,0,sizeof(InPath));
    snprintf(InPath,sizeof(InPath),"%s/sys.ini",CONFIG_PATH);
    ret = parse_sys_ini(InPath,OutPath);
    if(ret)
    {
        goto exit;
    }

    memset(InPath,0,sizeof(InPath));
    memcpy(InPath,OutPath,sizeof(OutPath));
    //set keypad init setting
    memcpy(gKeypadPath,OutPath,sizeof(OutPath));
    UBOOT_INFO("Full Customer.ini for keypad path --> %s\n",gKeypadPath);

    ret = parse_model_ini(InPath, gPnlPath, gBoardPath);
    if(ret)
    {
        goto exit;
    }

    vfs_mount(CUSTOMER);
    memset(InPath,0,sizeof(InPath));
    snprintf(InPath,sizeof(InPath),"%s/boot.ini",CUSTOMER_PATH);
    ret = parse_boot_ini(InPath);
    if(ret)
    {
        goto exit;
    }
exit:
    UBOOT_TRACE("OK\n");
    return ret;
}

int prepare_nand_dbtable(U32 u32LogoOffset)
{
    int ret = -1;
    UBOOT_TRACE("IN\n");
    // U32 u32FlashSize;
    memset((void*)&db_table,0,sizeof(db_table));
    //vfs_mount(CUSTOMER);
    vfs_mount(CONF);

#if(ENABLE_DISPLAY_LOGO)
    db_table.logo_size = vfs_getsize(gLogoPath);
    UBOOT_DEBUG("gLogoPath=%s\n",gLogoPath);
    UBOOT_DEBUG("db_table.logo_size=0x%x\n",db_table.logo_size);


    if(db_table.logo_size > 0)
    {
        UBOOT_DEBUG("%s size =:0x%08x \n",gLogoPath,db_table.logo_size);
    }
    else
    {
        UBOOT_ERROR(" get logo_size fail...>>>:%d\n",db_table.logo_size);
        return ret;
    }
#endif

    vfs_mount(CUSTOMER);
#if ENABLE_POWER_MUSIC
    //get music_size
    db_table.music_size = vfs_getsize(gMusicPath);
    UBOOT_DEBUG("gMusicPath=%s\n",gMusicPath);
    UBOOT_DEBUG("db_table.music_size=0x%x\n",db_table.music_size);
    if( db_table.music_size > 0)
    {
        UBOOT_DEBUG("%s size =:0x%08x \n",gMusicPath,db_table.music_size);
    }
    else
    {
        UBOOT_ERROR(" get music_size fail...>>>:%d\n",db_table.music_size);
        return ret; //althought music is set off, logo can be showed if it is set on
    }
#endif


#if (CONFIG_PANEL_INIT)
    db_table.panelpara_size = sizeof(PanelType);
    db_table.boardpara_size = sizeof(st_board_para);
#endif

#if(ENABLE_ENABLE_URSA == 1)
#if(ENABLE_URSA_6M30 == 1)
    db_table.ursa_6m30_size = sizeof(ursa_6m30_cmd_table);
#elif (ENABLE_URSA_8 == 1)|| (ENABLE_URSA_6M40 == 1)
    db_table.ursa_size = sizeof(ursa_cmd_table);
#endif
#endif

#if defined(PCB_WITH_MFC) && (CONFIG_VESTEL_MB97 == 1)
    db_table.ursa_6m30_size = sizeof(ursa5_cmd_table); 
    //printf("\033[0;36m db_table.ursa_6m30_size = 0x%lx\n\033[m",db_table.ursa_6m30_size);
#endif
#if(ENABLE_KEYPAD_CUST == 1)
    db_table.keypad_size= sizeof(st_keypad_para);
#endif

#if 1	//ENHANCE_BOOTING_TIME
    #if (CONFIG_BOOTLOGO_4K2K)
        db_table.logo_size = 0x0;//bootlogo data not in spi
    #endif
#else
#if (CONFIG_BOOTLOGO_4K2K)  || (CONFIG_VESTEL_MB97 == 1)
    db_table.logo_size = 0x0;//bootlogo data not in spi
#endif
#endif
    db_table.logo_offset  = u32LogoOffset+sizeof(db_table);
    db_table.music_offset = db_table.logo_offset + db_table.logo_size;
    db_table.panelpara_offset = db_table.music_offset + db_table.music_size;
    db_table.boardpara_offset = db_table.panelpara_offset + db_table.panelpara_size;
    db_table.ursa_6m30_offset = db_table.boardpara_offset + db_table.boardpara_size;
    db_table.ursa_offset = db_table.ursa_6m30_offset + db_table.ursa_6m30_size;
    db_table.keypad_offset = db_table.ursa_offset + db_table.ursa_size;

    UBOOT_DEBUG("logo  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.logo_offset,db_table.logo_size,(db_table.logo_offset+db_table.logo_size));
    UBOOT_DEBUG("music offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.music_offset,db_table.music_size,(db_table.music_offset+db_table.music_size));
    UBOOT_DEBUG("panel offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.panelpara_offset,db_table.panelpara_size,(db_table.panelpara_offset+db_table.panelpara_size));
    UBOOT_DEBUG("board offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.boardpara_offset,db_table.boardpara_size,(db_table.boardpara_offset+db_table.boardpara_size));
    UBOOT_DEBUG("ursa 6m30  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.ursa_6m30_offset,db_table.ursa_6m30_size,(db_table.ursa_6m30_offset+db_table.ursa_6m30_size));
    UBOOT_DEBUG("ursa  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.ursa_offset,db_table.ursa_size,(db_table.ursa_offset+db_table.ursa_size));
    UBOOT_DEBUG("keypad  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.keypad_offset,db_table.keypad_size,(db_table.keypad_offset+db_table.keypad_size));

    {
        U32 db_size = 0;
        db_size = (sizeof(db_table)+db_table.logo_size+db_table.music_size+db_table.panelpara_size+db_table.ursa_6m30_size+db_table.keypad_size+env_sector_size+u32LogoOffset);
        UBOOT_DEBUG("u32LogoOffset  =: 0x%x \n",u32LogoOffset);
        UBOOT_DEBUG("db size        =: 0x%x \n",db_size);
    }
    count_data_crc32_setenv((U32)&db_table,sizeof(db_struct),"db_crc");
    ret = raw_write((U32)&db_table,u32LogoOffset,sizeof(db_table));
    UBOOT_TRACE("OK\n");
    return ret;
}

int write_dbtable(U32 u32LogoOffset)
{
    int ret = -1;
    UBOOT_TRACE("IN\n");
    parse_ini();
    if(prepare_nand_dbtable(u32LogoOffset)==-1)
    {
        UBOOT_ERROR("flash database not ready...>>>\n");
        return ret;
    }
    else
    {

#if ENABLE_DISPLAY_LOGO
#if 1    //ENHANCE_BOOTING_TIME
    #if  (!(CONFIG_BOOTLOGO_4K2K))
        Load_LogoToFlash();
    #endif
#else
#if  (!(CONFIG_BOOTLOGO_4K2K)) && (CONFIG_VESTEL_MB97 == 0) 
        Load_LogoToFlash();
#endif
#endif
#endif
#if ENABLE_POWER_MUSIC
        Load_MusicToFlash();
#endif
#if (CONFIG_PANEL_INIT)
        Load_PanelSetting_ToFlash();
        Load_BoardSetting_ToFlash();
        #if defined(PCB_WITH_MFC) && (CONFIG_VESTEL_MB97 == 1)
        Load_Ursa5Setting_ToFlash();
        #endif
#endif
#if ENABLE_ENABLE_URSA
#if ENABLE_URSA_6M30
        //Load_Ursa6m30Para_ToFlash();
#elif (ENABLE_URSA_8 == 1) || (ENABLE_URSA_6M40 == 1)
        Load_UrsaPara_ToFlash();
#endif
#endif

#if ENABLE_KEYPAD_CUST
        //Load_KeypadSetting_ToFlash();
#endif

        setenv("db_table","1");
        saveenv();
        ret = 0;
    }
    UBOOT_TRACE("OK\n");
    return ret;
}

int read_dbtable(U32 u32LogoOffset)
{
    if(-1 == raw_read((U32)&db_table,u32LogoOffset,sizeof(db_table)))
    {
        UBOOT_ERROR("ERROR: read_mmc_dbtable fail...>>>\n");
        return -1;
    }
    else
    {
        UBOOT_DEBUG("read_dbtable success...>>>\n");
        UBOOT_DEBUG("read table >>> \n");
        UBOOT_DEBUG("logo  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.logo_offset,db_table.logo_size,(db_table.logo_offset+db_table.logo_size));
        UBOOT_DEBUG("music offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.music_offset,db_table.music_size,(db_table.music_offset+db_table.music_size));
        UBOOT_DEBUG("panel offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.panelpara_offset,db_table.panelpara_size,(db_table.panelpara_offset+db_table.panelpara_size));
        UBOOT_DEBUG("ursa  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.ursa_6m30_offset,db_table.ursa_6m30_size,(db_table.ursa_6m30_offset+db_table.ursa_6m30_size));
        UBOOT_DEBUG("keypad  offset[0x%08x] size[0x%08x] end[0x%08x]\n",db_table.keypad_offset,db_table.keypad_size,(db_table.keypad_offset+db_table.keypad_size));
    }
    ulong checksum = 0,savesum = 0;
    char *p_str = NULL;
    checksum = crc32(0,(unsigned char *)&db_table,sizeof(db_struct));
    p_str = getenv("db_crc");
    if(p_str == NULL)
    {
        savesum = 0;
    }
    else
    {
        savesum = simple_strtoul(p_str, NULL, 16);
    }
    if(checksum != savesum)
    {
        UBOOT_ERROR("Error : savesum =%ld , checksum= %ld \n",savesum,checksum);
        UBOOT_ERROR("Reload the dbtable from AP !!!\n");
        return write_dbtable(u32LogoOffset);
    }
    return 0;
}
void count_data_crc32_setenv(U32 addr,int size,char *name)
{
    char buf[32] = "\0";
    ulong checksum = 0;
    checksum = crc32(0,(unsigned char *)addr,size);
    snprintf(buf,sizeof(buf),"%lx",checksum);
    setenv(name,buf);
    UBOOT_DEBUG("%s checksum =: 0x%lx ... %s \n",name,checksum,buf);
}
int count_data_crc32_getenv(U32 addr,int size,char *name)
{
    int ret = -1;
    U32 checksum,savesum;
    char * p_str = NULL;
    checksum = crc32(0,(unsigned char *)addr,size);
    p_str = getenv(name);
    if(p_str == NULL)
    {
        savesum = 0;
    }
    else
    {
        savesum = simple_strtoul(p_str,NULL,16);
    }
    if(checksum == savesum)
    {
        UBOOT_DEBUG("## CRC check done, %s\n", name);
        ret = 0;
    }
    else
    {
        UBOOT_ERROR("checksum :0X%x ; savesum :0X%x\n",checksum,savesum);
        UBOOT_ERROR("## CRC check Error, %s\n", name);
        setenv("db_table","0");
        saveenv();
    }
    return ret;
}
#if ENABLE_DISPLAY_LOGO
int Load_LogoToFlash(void)
{
    int ret = -1;
    U32 JPD_InputADDR=0;
    UBOOT_TRACE("IN\n");

#if (CONFIG_VESTEL_MB100 == 1)
    if(get_addr_from_mmap("E_MMAP_ID_JPD_READ", &JPD_InputADDR)!=0) //MB100_BRINGUP
    {
        UBOOT_ERROR("get E_MMAP_ID_JPD_READ mmap fail\n");
        return -1;
    }
#else  
    if(get_addr_from_mmap("E_MMAP_MAD_JPEG_OUT_ADR", &JPD_InputADDR)!=0)
    {
        UBOOT_ERROR("get E_MMAP_MAD_JPEG_OUT_ADR mmap fail\n");
        return -1;
    }
#endif

    U32 u32BinAddr = (U32)(PA2NVA(JPD_InputADDR));
    U32 u32fileSize=0;
    UBOOT_TRACE("IN\n");
    if(JPD_InputADDR==0xFFFF)
    {
        UBOOT_ERROR("Get JPD Mmap fail...>>>\n");
        return ret;
    }

    //vfs_mount(CUSTOMER);
    vfs_mount(CONF);
    u32fileSize=vfs_getsize(gLogoPath);
    UBOOT_DEBUG("u32fileSize=0x%x\n",u32fileSize);
    UBOOT_DEBUG("db_table.logo_size=0x%x\n",db_table.logo_size);

    if (vfs_read((void *)u32BinAddr,gLogoPath,0,u32fileSize) == 0)
    {
        count_data_crc32_setenv(u32BinAddr,db_table.logo_size,"logo_crc");
        ret = raw_write(u32BinAddr,db_table.logo_offset,db_table.logo_size);
        if(ret == -1)
        {
            UBOOT_ERROR("write data to flash fail...>>>\n");
        }
        else
        {
            UBOOT_TRACE("OK\n");
        }
    }
    else
    {
        UBOOT_ERROR("ubifsload data fail ...>>>\n");
    }
    UBOOT_TRACE("OK\n");
    return ret;
}
int Read_LogoToDisplayAddr(U32 u32LogoAddr)
{
    int ret = -1;
    UBOOT_DEBUG("db_table.logo_offset =:0x%x ... db_table.logo_size=: 0x%x\n",db_table.logo_offset,db_table.logo_size);
    if(-1 == raw_read(u32LogoAddr,db_table.logo_offset,db_table.logo_size))
    {
        UBOOT_ERROR("ERROR: Read_LogoToDisplayAddr fail...>>>\n");
    }
    else
    {
        UBOOT_DEBUG("Read_LogoToDisplayAddr success...>>>\n");
        //crc check
        if(count_data_crc32_getenv(u32LogoAddr,db_table.logo_size,"logo_crc")==-1)
        {
            UBOOT_ERROR("check LogoToDisplayAddr fail...>>>\n");
            return ret;
        }
        else
        {
            ret = 0;
        }
    }
    return ret;
}
#endif

#if ENABLE_POWER_MUSIC
int Load_MusicToFlash(void)
{
    int ret = -1;
    U32 u32MusicAddr = 0, u32Addr = 0;
    U32 u32fileSize=0;

    UBOOT_TRACE("IN\n");
    vfs_mount(CUSTOMER);
    u32fileSize=vfs_getsize(gMusicPath);
    UBOOT_DEBUG("u32fileSize=0x%x\n",u32fileSize);
    UBOOT_DEBUG("db_table.music_size=0x%x\n",db_table.music_size);

    if(get_addr_from_mmap("E_DFB_FRAMEBUFFER", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_DFB_FRAMEBUFFER_ADR mmap fail\n");
    }
    if(u32Addr==0xFFFF)
    {
        UBOOT_ERROR("Get Audio Mmap fail...>>>\n");
        return ret;
    }
    u32MusicAddr = (U32)(PA2NVA(u32Addr));
    UBOOT_DEBUG("Music address PA[0x%x]VA[0x%x]>>>\n",u32Addr,u32MusicAddr);
    if (vfs_read((void *)u32MusicAddr,gMusicPath,0,u32fileSize) == 0)
    {
        count_data_crc32_setenv(u32MusicAddr,db_table.music_size,"music_crc");
        UBOOT_INFO("music_offset = 0x%x music_size = 0x%x\n",db_table.music_offset,db_table.music_size);
        ret = raw_write(u32MusicAddr,db_table.music_offset,db_table.music_size);
        if(ret == -1)
        {
            UBOOT_ERROR("write data to flash fail...>>>\n");
        }
        else
        {
            UBOOT_TRACE("OK\n");
        }
    }
    else
    {
        UBOOT_ERROR("load mp3 file faile>>>>>>>>>>\n");
    }
    return ret;
}

int Read_MusicToPlayAddr(MS_U32 u32MusicDramAddr)
{
    int ret = -1;
    U32 u32MusicAddr = (U32)(PA2NVA(u32MusicDramAddr));
    // Clear ES1 buffer = 64K
    memset((void*)(u32MusicAddr), 0, 65536);

    UBOOT_DEBUG("Read_>>>\n");
    if(-1 == raw_read(u32MusicAddr,db_table.music_offset,db_table.music_size))
    {
        UBOOT_ERROR("ERROR: Read_MusicToPlayAddr fail...>>>\n");
    }
    else
    {
        UBOOT_DEBUG("Read_MusicToPlayAddr success...>>>\n");
        UBOOT_DEBUG("Read_MusicToPlayAddr success...>>> 2\n");
        //crc check
        if(count_data_crc32_getenv(u32MusicAddr,db_table.music_size,"music_crc")==-1)
        {
            return ret;
        }
        else
        {
            ret = 0;
        }
    }
    return ret;
}

#endif

#if (CONFIG_PANEL_INIT)

#if ((CONFIG_VESTEL_MB97 == 1) || (CONFIG_VESTEL_MB100 == 1))	//MB100_BRINGUP

char *script = NULL;
char *TmpScrtip = NULL;


char* fgets(char *str, int n, int fp)
{
    int i=0;
    char *next_line;

    next_line = get_script_next_line(&script);
    //printf(">>>next_line=%s\n",next_line);
	
    if(next_line==NULL) return NULL;

    for(i=0;i<256;i++)
    if(next_line[i]=='\n' || next_line[i]=='\r' )
    {  
       strncpy(str,next_line,i);
       str[i]=0;
	//printf(">>>str=%s\n",str);
	break;
    }

    return next_line;

}



//MB100_BRINGUP
int parse_pnl_ini(char *path,PanelType *p_data)
{
    char str[1024];
    int len, n, i, j;
    char *next_line;
    int fp=0;
    MS_U8 bEnable_Filp_Function = 0;
    U32 filesize = 0;

    printf("vestel panel bin file: %s \n", path);

    script = loadscript(path,&filesize);
    TmpScrtip = script;
    if(script == NULL)
                return -1;
    	
    
	//-----------------------Panel Timing---------------------------------------------
#if 1
        while(fgets(str,sizeof(str),fp) != NULL)
        {

            // strip trailing '\n' if it exists
        #if 0
            len = strlen(str)-1;
            if(str[len] == '\n')
                str[len] = 0;
            if(str[len-1] == '\r')
                str[len-1] = 0;
        #else
            len = strlen(str)-2;
            if(str[len] == '\r')
                str[len] = 0;
        #endif
            //printf("\n%s", str);
            if (strncmp(str,"Customer Field",14)==0)
            {
                //printf("\n\033[33mFound Customer Field\033[m\n");
                break;
            }
        }

    while(fgets(str,sizeof(str),fp) != NULL)
    {    	
	
        // strip trailing '\n' if it exists
        #if 0
        len = strlen(str)-1;
        if(str[len] == '\n')
            str[len] = 0;
        if(str[len-1] == '\r')
            str[len-1] = 0;
        #else
        len = strlen(str)-2;
        if(str[len] == '\r')
            str[len] = 0;
        #endif
        //printf("\n%s", str);
        if (strncmp(str,"Timing",6)==0)
        {
                //printf("\n\033[33mFound Timing\033[m\n");
                break;
            }
        }


            fgets(str,sizeof(str),fp);
            len = strlen(str)-2;
            if(str[len] == '\r')
                str[len] = 0;
            //strcpy(pPanelName, str);
            setenv("panel_name",str);
            //printf(">>>>>>>>>>debug %s_%d str=%s\n",__FUNCTION__,__LINE__, str);

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelDither = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ePanelLinkType = (APIPNL_LINK_TYPE)n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelDualPort = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapPort = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapOdd_ML  = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapEven_ML = n;

            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapOdd_RB = n;
            fgets(str,sizeof(str),fp);

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapEven_RB = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapLVDS_POL = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapLVDS_CH = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelPDP10BIT = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelLVDS_TI_MODE = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelDCLKDelay = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelInvDCLK = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelInvDE = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelInvHSync = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelInvVSync = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelDCKLCurrent = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelDECurrent = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelODDDataCurrent = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelEvenDataCurrent = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelOnTiming1 = n;
            //printf(">>>>>>>>>>debug %s_%d m_wPanelOnTiming1=%d\n",__FUNCTION__,__LINE__, n); 

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelOnTiming2 = n;
            //printf(">>>>>>>>>>debug %s_%d m_wPanelOnTiming2=%d\n",__FUNCTION__,__LINE__, n); 

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelOffTiming1 = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelOffTiming2 = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelHSyncWidth = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelHSyncBackPorch = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelVSyncWidth = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelVBackPorch = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelHStart = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelVStart = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelWidth = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelHeight = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelMaxHTotal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelHTotal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelMinHTotal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelMaxVTotal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelVTotal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wPanelMinVTotal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_dwPanelMaxDCLK = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_dwPanelDCLK = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_dwPanelMinDCLK = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wSpreadSpectrumStep = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_wSpreadSpectrumSpan = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucDimmingCtl = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucMaxPWMVal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucMinPWMVal = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelDeinterMode = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucPanelAspectRatio = (E_PNL_ASPECT_RATIO)n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_u16LVDSTxSwapValue = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucTiBitMode = (APIPNL_TIBITMODE)n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_ucOutputFormatBitMode = (APIPNL_OUTPUTFORMAT_BITMODE)n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapOdd_RG = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapEven_RG = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapOdd_GB = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelSwapEven_GB = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_bPanelDoubleClk = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_dwPanelMaxSET = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);
            p_data->m_dwPanelMinSET = n;

            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n); // ucOutTimingMode
            //printf(">>>>>>>>>>debug %s_%d ucOutTimingMode=%d\n",__FUNCTION__,__LINE__, n); 
            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n); // bPanelNoiseDith
            //printf(">>>>>>>>>>debug %s_%d bPanelNoiseDith=%d\n",__FUNCTION__,__LINE__, n); 
            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n); // ucBacklightCrop
            //printf(">>>>>>>>>>debug %s_%d ucBacklightCrop=%d\n",__FUNCTION__,__LINE__, n); 
            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);// PWM_Period
            //printf(">>>>>>>>>>debug %s_%d PWM_Period=%d\n",__FUNCTION__,__LINE__, n); 
  		    snprintf(str,sizeof(str),"0x%x",n);
		    setenv(PWM_PERIOD,str);
            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);// PWM_DIVPWM
            //printf(">>>>>>>>>>debug %s_%d PWM_DIVPWM=%d\n",__FUNCTION__,__LINE__, n);
            snprintf(str,sizeof(str),"0x%x",n);
            setenv(PWM_DIVPWM,str);
            fgets(str,sizeof(str),fp);
            sscanf(str, "%d", &n);// Enable_Filp_Function
            //printf(">>>>>>>>>>debug %s_%d Enable_Filp_Function=%d\n",__FUNCTION__,__LINE__, n); 
            bEnable_Filp_Function = n;
            if(bEnable_Filp_Function)
                setenv(MIRROR_ON,"1");
            else
                setenv(MIRROR_ON,"0");
            setenv(PWM_POLPWM,"0");  //tmp solution, for Nugget MB97(since no ursa case), force to set PWM POL = 0, or there will be blank screen problem
            saveenv();

            if(TmpScrtip != NULL)
            {
                //printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
                free(TmpScrtip);
                TmpScrtip=NULL;
            }

            //printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
            return 0;
#else

    while(fgets(str,sizeof(str),fp) != NULL)
    {

        // strip trailing '\n' if it exists
        #if 0
        len = strlen(str)-1;
        if(str[len] == '\n')
            str[len] = 0;
        if(str[len-1] == '\r')
            str[len-1] = 0;
        #else
        len = strlen(str)-2;
        if(str[len] == '\r')
            str[len] = 0;
        #endif
        //printf("\n%s", str);
        if (strncmp(str,"Timing",6)==0)
        {
            printf("\n\033[33mFound Panel Timing\033[m\n");
            break;
        }
    }

		fgets(str,sizeof(str),fp);
		len = strlen(str)-2;
		if(str[len] == '\r')
		    str[len] = 0;
	
		//strcpy(pPanelName, str);    
		setenv("panel_name",str);
		printf(">>>>>>>>>>debug %s_%d str=%s\n",__FUNCTION__,__LINE__, str);

		

		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelDither = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ePanelLinkType = (APIPNL_LINK_TYPE)n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelDualPort = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapPort = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapOdd_ML  = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapEven_ML = n;
		
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapOdd_RB = n;
		fgets(str,sizeof(str),fp);
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapEven_RB = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapLVDS_POL = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapLVDS_CH = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelPDP10BIT = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelLVDS_TI_MODE = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelDCLKDelay = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelInvDCLK = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelInvDE = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelInvHSync = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelInvVSync = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelDCKLCurrent = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelDECurrent = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelODDDataCurrent = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelEvenDataCurrent = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelOnTiming1 = n;
		printf(">>>>>>>>>>debug %s_%d m_wPanelOnTiming1=%d\n",__FUNCTION__,__LINE__, n);
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelOnTiming2 = n;
		printf(">>>>>>>>>>debug %s_%d m_wPanelOnTiming2=%d\n",__FUNCTION__,__LINE__, n);
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelOffTiming1 = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelOffTiming2 = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelHSyncWidth = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelHSyncBackPorch = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelVSyncWidth = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelVBackPorch = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelHStart = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelVStart = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelWidth = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelHeight = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelMaxHTotal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelHTotal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelMinHTotal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelMaxVTotal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelVTotal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wPanelMinVTotal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_dwPanelMaxDCLK = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_dwPanelDCLK = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_dwPanelMinDCLK = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wSpreadSpectrumStep = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_wSpreadSpectrumSpan = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucDimmingCtl = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucMaxPWMVal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucMinPWMVal = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelDeinterMode = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucPanelAspectRatio = (E_PNL_ASPECT_RATIO)n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_u16LVDSTxSwapValue = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucTiBitMode = (APIPNL_TIBITMODE)n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_ucOutputFormatBitMode = (APIPNL_OUTPUTFORMAT_BITMODE)n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapOdd_RG = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapEven_RG = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapOdd_GB = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelSwapEven_GB = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_bPanelDoubleClk = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_dwPanelMaxSET = n;
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		p_data->m_dwPanelMinSET = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		//panel_params->BacklightCrop = n;
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		snprintf(str,sizeof(str),"0x%x",n);
		setenv(PWM_PERIOD,str);
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		snprintf(str,sizeof(str),"0x%x",n);
		//panel_params->PWMClockDiv= n;    
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		snprintf(str,sizeof(str),"0x%x",n);
		setenv(PWM_DIVPWM,str);

		printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
		
		fgets(str,sizeof(str),fp);
		sscanf(str, "%d", &n);
		snprintf(str,sizeof(str),"0x%x",n);
		//panel_params->Enable_Flip_Function= n;

		printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
		
		if(TmpScrtip != NULL)
	    {
    		printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
			free(TmpScrtip);
			TmpScrtip=NULL;
	    }

		printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
		return 0;
#endif
}
#if(MS_BOARD_TYPE_SEL == BD_MST180F_D01A_S)
int parse_ursa5_ini(char *path,ursa5_cmd_table *p_data) 
{
    char str[1024];
    int len, n, i, j;
    char *next_line;
    int fp=0;
    MS_U8 bEnable_Filp_Function = 0;
    U32 filesize = 0;

    printf("vestel one bin file: %s \n", path);

    script = loadscript(path,&filesize);
    TmpScrtip = script;
    if(script == NULL)
                return -1;
    while(fgets(str,sizeof(str),fp) != NULL)
    {
        // strip trailing '\n' if it exists
    #if 0
        len = strlen(str)-1;
        if(str[len] == '\n')
            str[len] = 0;
        if(str[len-1] == '\r')
            str[len-1] = 0;
    #else
        len = strlen(str)-2;
        if(str[len] == '\r')
            str[len] = 0;
    #endif
        //printf("\n%s", str);
        if (strncmp(str,"MFC_OneBin",10)==0)
        {
            printf("\n\033[33mFound MFC_OneBin\033[m\n");
            break;
        }
    }

    for(j = 0; j <= 44; j++) 
    {
        fgets(str,sizeof(str),fp);
        sscanf(str, "%d", &n);
    }
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_PANEL_TYPE = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_MASK_HS = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_MASK_VS = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_MASK_DE = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_PANEL_INV_HSYNC = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_PANEL_INV_VSYNC = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_PANEL_INV_DE = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_DITHER_8BITS = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_DITHER_EN = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_A = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_A %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_B = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_B %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_C = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_C %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_D = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_CHANNEL_SWAP_CHANNEL_D %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_CHANNEL_NUMBER = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_BIT_NUMBER = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_SWAP_PAIR = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_SWAP_POL = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_INCREASE_VTOTAL_FOR_50HZ = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_DITHER_TAIL_CUT = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_CUS_PANEL_SWING_DATA = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_HTOTAL = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_HTOTAL %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_VTOTAL = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_VTOTAL %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_HSTART = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_VSTART = n;
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_WIDTH = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_WIDTH %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_HEIGHT = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_HEIGHT %s_%d \n",__FUNCTION__,n);
    for(j = 0; j < 7; j++)
    {
        fgets(str,sizeof(str),fp);
        sscanf(str, "%d", &n);
    }

    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_SHIFT_PAIR = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_SHIFT_PAIR %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_TX_TI_MODE = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_TX_TI_MODE %s_%d \n",__FUNCTION__,n);

    for(j = 0; j < 6; j++) 
    {
        fgets(str,sizeof(str),fp);
        sscanf(str, "%d", &n);
    }

    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_ENABLE_MST_MIRROR_FUNC = n;

    for(j = 0; j < 21; j++)
    {
        fgets(str,sizeof(str),fp);
        sscanf(str, "%d", &n);
    }

    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_RX_CHCONNECT = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_RX_CHCONNECT %s_%d \n",__FUNCTION__,n);

    for(j = 0; j < 6; j++)
    {
        fgets(str,sizeof(str),fp);
        sscanf(str, "%d", &n);
    }
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_RX_BIT_NUM = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_RX_BIT_NUM %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_RX_TI_MODE = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_RX_TI_MODE %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_LVDS_RX_SWAP_ODD_EVEN = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_LVDS_RX_SWAP_ODD_EVEN %s_%d \n",__FUNCTION__,n);
    for(j = 0; j < 17; j++) 
    {
        fgets(str,sizeof(str),fp);
        sscanf(str, "%d", &n);
    }
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_CUS_LVDS_RX_SWAP_MSB_LSB = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_CUS_LVDS_RX_SWAP_MSB_LSB %s_%d \n",__FUNCTION__,n);
    fgets(str,sizeof(str),fp);
    sscanf(str, "%d", &n);
    p_data->URSA5_CUS_LVDS_RX_SWAP_P_N = n;
    //printf(">>>>>>>>>>E_MFC_ONEBIN_CUS_LVDS_RX_SWAP_P_N %s_%d \n",__FUNCTION__,n);
    if(TmpScrtip != NULL)
    {
        //printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
        free(TmpScrtip);
        TmpScrtip=NULL;
    }

    //printf(">>>>>>>>>>debug %s_%d \n",__FUNCTION__,__LINE__);
    return 0;

}

#endif

#else


//maintrunk

int parse_pnl_ini(char *path,PanelType *p_data)
{
    long n;
    char *script = NULL;
    char str[BUFFER_SIZE];
    char buf [12];	
    U32 filesize = 0;
    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        while (*path== '/') path++;
        path=strstr(path,"/");
        UBOOT_INFO("filter /config, and find file again!!\n");
        script = loadscript(path,&filesize);
        if(script == NULL)
        {
            return -1;
        }
    }
    UBOOT_INFO("sizeof( panel ini script ) --------> %u bytes\n",filesize);
    Profile_Init((char *)script,filesize); 
    n = Profile_GetInteger("panel", "m_bPanelDither", 0);
    UBOOT_DEBUG("m_bPanelDither = %ld \n",n);
    p_data->m_bPanelDither = n;
    memset(str,0,sizeof(str));
    Profile_GetString("panel", "m_pPanelName","", str, sizearray(str));
    setenv("panel_name",str);
    n = Profile_GetInteger("panel", "m_ePanelLinkType", 0);
    UBOOT_DEBUG("m_ePanelLinkType = %ld \n",n);
    p_data->m_ePanelLinkType = (APIPNL_LINK_TYPE)n;
    Profile_GetString("panel", "m_ePanelLinkExtType","", str, sizearray(str));        
    UBOOT_DEBUG("m_ePanelLinkExtType = %s \n",str);
    setenv("panel_ext_type", str);
	Profile_GetString("panel", "m_u16PANEL_LVDS_CONNECT_TYPE","", str, sizearray(str));        
    UBOOT_DEBUG("m_u16PANEL_LVDS_CONNECT_TYPE = %s \n",str);
    setenv("PANEL_LVDS_CONNECT_TYPE", str);
    saveenv();
        
    n = Profile_GetInteger("panel", "m_bPanelDualPort", 0);
    UBOOT_DEBUG("m_bPanelDualPort = %ld \n",n);
    p_data->m_bPanelDualPort = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapPort", 0);
    UBOOT_DEBUG("m_bPanelSwapPort  = %ld \n",n);
    p_data->m_bPanelSwapPort = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapOdd_ML", 0);
    UBOOT_DEBUG("m_bPanelSwapOdd_ML = %ld \n",n);
    p_data->m_bPanelSwapOdd_ML  = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapEven_ML", 0);
    UBOOT_DEBUG("m_bPanelSwapEven_ML = %ld \n",n);
    p_data->m_bPanelSwapEven_ML = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapOdd_RB", 0);
    UBOOT_DEBUG("m_bPanelSwapOdd_RB = %ld \n",n);
    p_data->m_bPanelSwapOdd_RB = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapEven_RB", 0);
    UBOOT_DEBUG("m_bPanelSwapEven_RB = %ld \n",n);
    p_data->m_bPanelSwapEven_RB = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapLVDS_POL", 0);
    UBOOT_DEBUG("m_bPanelSwapLVDS_POL = %ld \n",n);
    p_data->m_bPanelSwapLVDS_POL = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapLVDS_CH", 0);
    UBOOT_DEBUG("m_bPanelSwapLVDS_CH = %ld \n",n);
    p_data->m_bPanelSwapLVDS_CH = n;
    n = Profile_GetInteger("panel", "m_bPanelPDP10BIT", 0);
    UBOOT_DEBUG("m_bPanelPDP10BIT = %ld \n",n);
    p_data->m_bPanelPDP10BIT = n;
    n = Profile_GetInteger("panel", "m_bPanelLVDS_TI_MODE", 0);
    UBOOT_DEBUG("m_bPanelLVDS_TI_MODE = %ld \n",n);
    p_data->m_bPanelLVDS_TI_MODE = n;
    n = Profile_GetInteger("panel", "m_ucPanelDCLKDelay", 0);
    UBOOT_DEBUG("m_ucPanelDCLKDelay = %ld \n",n);
    p_data->m_ucPanelDCLKDelay = n;
    n = Profile_GetInteger("panel", "m_bPanelInvDCLK", 0);
    UBOOT_DEBUG("m_bPanelInvDCLK = %ld \n",n);
    p_data->m_bPanelInvDCLK = n;
    n = Profile_GetInteger("panel", "m_bPanelInvDE", 0);
    UBOOT_DEBUG("m_bPanelInvDE = %ld \n",n);
    p_data->m_bPanelInvDE = n;
    n = Profile_GetInteger("panel", "m_bPanelInvHSync", 0);
    UBOOT_DEBUG("m_bPanelInvHSync = %ld \n",n);
    p_data->m_bPanelInvHSync = n;
    n = Profile_GetInteger("panel", "m_bPanelInvVSync", 0);
    UBOOT_DEBUG("m_bPanelInvVSync = %ld \n",n);
    p_data->m_bPanelInvVSync = n;
    n = Profile_GetInteger("panel", "m_ucPanelDCKLCurrent", 0);
    UBOOT_DEBUG("m_ucPanelDCKLCurrent = %ld \n",n);
    p_data->m_ucPanelDCKLCurrent = n;
    n = Profile_GetInteger("panel", "m_ucPanelDECurrent", 0);
    UBOOT_DEBUG("m_ucPanelDECurrent = %ld \n",n);
    p_data->m_ucPanelDECurrent = n;
    n = Profile_GetInteger("panel", "m_ucPanelODDDataCurrent", 0);
    UBOOT_DEBUG("m_ucPanelODDDataCurrent = %ld \n",n);
    p_data->m_ucPanelODDDataCurrent = n;
    n = Profile_GetInteger("panel", "m_ucPanelEvenDataCurrent", 0);
    UBOOT_DEBUG("m_ucPanelEvenDataCurrent = %ld \n",n);
    p_data->m_ucPanelEvenDataCurrent = n;
    n = Profile_GetInteger("panel", "m_wPanelOnTiming1", 0);
    UBOOT_DEBUG("m_wPanelOnTiming1 = %ld \n",n);
    p_data->m_wPanelOnTiming1 = n;
    n = Profile_GetInteger("panel", "m_wPanelOnTiming2", 0);
    UBOOT_DEBUG("m_wPanelOnTiming2 = %ld \n",n);
    p_data->m_wPanelOnTiming2 = n;
    n = Profile_GetInteger("panel", "m_wPanelOffTiming1", 0);
    UBOOT_DEBUG("m_wPanelOffTiming1 = %ld \n",n);
    p_data->m_wPanelOffTiming1 = n;
    n = Profile_GetInteger("panel", "m_wPanelOffTiming2", 0);
    UBOOT_DEBUG("m_wPanelOffTiming2 = %ld \n",n);
    p_data->m_wPanelOffTiming2 = n;
    n = Profile_GetInteger("panel", "m_ucPanelHSyncWidth", 0);
    UBOOT_DEBUG("m_ucPanelHSyncWidth  = %ld \n",n);
    p_data->m_ucPanelHSyncWidth = n;
    n = Profile_GetInteger("panel", "m_ucPanelHSyncBackPorch", 0);
    UBOOT_DEBUG("m_ucPanelHSyncBackPorch  = %ld \n",n);
    p_data->m_ucPanelHSyncBackPorch = n;

    n = Profile_GetInteger("panel", "m_ucPanelVSyncWidth", 0);
    UBOOT_DEBUG("m_ucPanelVSyncWidth = %ld \n",n);
    p_data->m_ucPanelVSyncWidth = n;
    n = Profile_GetInteger("panel", "m_ucPanelVBackPorch", 0);
    UBOOT_DEBUG("m_ucPanelVBackPorch = %ld \n",n);
    p_data->m_ucPanelVBackPorch = n;

    n = Profile_GetInteger("panel", "m_wPanelHStart", 0);
    UBOOT_DEBUG("m_wPanelHStart = %ld \n",n);
    p_data->m_wPanelHStart = n;
    n = Profile_GetInteger("panel", "m_wPanelVStart", 0);
    UBOOT_DEBUG("m_wPanelVStart = %ld \n",n);
    p_data->m_wPanelVStart = n;
    n = Profile_GetInteger("panel", "m_wPanelWidth", 0);
    UBOOT_DEBUG("m_wPanelWidth = %ld \n",n);
    p_data->m_wPanelWidth = n;
    n = Profile_GetInteger("panel", "m_wPanelHeight", 0);
    UBOOT_DEBUG("m_wPanelHeight = %ld \n",n);
    p_data->m_wPanelHeight = n;

    n = Profile_GetInteger("panel", "m_wPanelMaxHTotal", 0);
    UBOOT_DEBUG("m_wPanelMaxHTotal = %ld \n",n);
    p_data->m_wPanelMaxHTotal = n;
    n = Profile_GetInteger("panel", "m_wPanelHTotal", 0);
    UBOOT_DEBUG("m_wPanelHTotal = %ld \n",n);
    p_data->m_wPanelHTotal = n;
    n = Profile_GetInteger("panel", "m_wPanelMinHTotal", 0);
    UBOOT_DEBUG("m_wPanelMinHTotal = %ld \n",n);
    p_data->m_wPanelMinHTotal = n;
    n = Profile_GetInteger("panel", "m_wPanelMaxVTotal", 0);
    UBOOT_DEBUG("m_wPanelMaxVTotal = %ld \n",n);
    p_data->m_wPanelMaxVTotal = n;
    n = Profile_GetInteger("panel", "m_wPanelVTotal", 0);
    UBOOT_DEBUG("m_wPanelVTotal = %ld \n",n);
    p_data->m_wPanelVTotal = n;

    n = Profile_GetInteger("panel", "m_wPanelMinVTotal", 0);
    UBOOT_DEBUG("m_wPanelMinVTotal = %ld \n",n);
    p_data->m_wPanelMinVTotal = n;
    n = Profile_GetInteger("panel", "m_dwPanelMaxDCLK", 0);
    UBOOT_DEBUG("m_dwPanelMaxDCLK = %ld \n",n);
    p_data->m_dwPanelMaxDCLK = n;
    n = Profile_GetInteger("panel", "m_dwPanelDCLK", 0);
    UBOOT_DEBUG("m_dwPanelDCLK = %ld \n",n);
    p_data->m_dwPanelDCLK = n;
	
    memset(buf, 0 , sizeof(buf));
    snprintf(buf, sizeof(buf), "%ld", n);
    setenv("u16PanelDCLK", buf);
	saveenv();

    n = Profile_GetInteger("panel", "m_dwPanelMinDCLK", 0);
    UBOOT_DEBUG("m_dwPanelMinDCLK = %ld \n",n);
    p_data->m_dwPanelMinDCLK = n;
    n = Profile_GetInteger("panel", "m_wSpreadSpectrumStep", 0);
    UBOOT_DEBUG("m_wSpreadSpectrumStep = %ld \n",n);
    p_data->m_wSpreadSpectrumStep = n;
    n = Profile_GetInteger("panel", "m_wSpreadSpectrumSpan", 0);
    UBOOT_DEBUG("m_wSpreadSpectrumSpan = %ld \n",n);
    p_data->m_wSpreadSpectrumSpan = n;
    n = Profile_GetInteger("panel", "m_ucDimmingCtl", 0);
    UBOOT_DEBUG("m_ucDimmingCtl = %ld \n",n);
    p_data->m_ucDimmingCtl = n;
    n = Profile_GetInteger("panel", "m_ucMaxPWMVal", 0);
    UBOOT_DEBUG("m_ucMaxPWMVal = %ld \n",n);
    p_data->m_ucMaxPWMVal = n;
    n = Profile_GetInteger("panel", "m_ucMinPWMVal", 0);
    UBOOT_DEBUG("m_ucMinPWMVal = %ld \n",n);
    p_data->m_ucMinPWMVal = n;
    n = Profile_GetInteger("panel", "m_bPanelDeinterMode", 0);
    UBOOT_DEBUG("m_bPanelDeinterMode = %ld \n",n);
    p_data->m_bPanelDeinterMode = n;
    n = Profile_GetInteger("panel", "m_ucPanelAspectRatio", 0);
    UBOOT_DEBUG("m_ucPanelAspectRatio = %ld \n",n);
    p_data->m_ucPanelAspectRatio = (E_PNL_ASPECT_RATIO)n;

    n = Profile_GetInteger("panel", "m_u16LVDSTxSwapValue", 0);
    UBOOT_DEBUG("m_u16LVDSTxSwapValue = %ld \n",n);
    p_data->m_u16LVDSTxSwapValue = n;
    n = Profile_GetInteger("panel", "m_ucTiBitMode", 0);
    UBOOT_DEBUG("m_ucTiBitMode = %ld \n",n);
    p_data->m_ucTiBitMode = (APIPNL_TIBITMODE)n;

    n = Profile_GetInteger("panel", "m_ucOutputFormatBitMode", 0);
    UBOOT_DEBUG("m_ucOutputFormatBitMode = %ld \n",n);
    p_data->m_ucOutputFormatBitMode = (APIPNL_OUTPUTFORMAT_BITMODE)n;

    n = Profile_GetInteger("panel", "m_bPanelSwapOdd_RG", 0);
    UBOOT_DEBUG("m_bPanelSwapOdd_RG = %ld \n",n);
    p_data->m_bPanelSwapOdd_RG = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapEven_RG", 0);
    UBOOT_DEBUG("m_bPanelSwapEven_RG = %ld \n",n);
    p_data->m_bPanelSwapEven_RG = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapOdd_GB", 0);
    UBOOT_DEBUG("m_bPanelSwapOdd_GB = %ld \n",n);
    p_data->m_bPanelSwapOdd_GB = n;
    n = Profile_GetInteger("panel", "m_bPanelSwapEven_GB", 0);
    UBOOT_DEBUG("m_bPanelSwapEven_GB = %ld \n",n);
    p_data->m_bPanelSwapEven_GB = n;
    n = Profile_GetInteger("panel", "m_bPanelDoubleClk", 0);
    UBOOT_DEBUG("m_bPanelDoubleClk = %ld \n",n);
    p_data->m_bPanelDoubleClk = n;
    n = Profile_GetInteger("panel", "m_dwPanelMaxSET", 0);
    UBOOT_DEBUG("m_dwPanelMaxSET = %ld \n",n);
    p_data->m_dwPanelMaxSET = n;
    n = Profile_GetInteger("panel", "m_dwPanelMinSET", 0);
    UBOOT_DEBUG("m_dwPanelMinSET = %ld \n",n);
    p_data->m_dwPanelMinSET = n;
    n = Profile_GetInteger("panel", "m_ucOutTimingMode", 0);
    UBOOT_DEBUG("m_ucOutTimingMode = %ld \n",n);
    p_data->m_ucOutTimingMode = (APIPNL_OUT_TIMING_MODE)n;
#if 1//use pwm setting in panel.ini and save it to env
    memset(str,0,sizeof(str));
    n = Profile_GetInteger("panel", "u32PeriodPWM", 0);
    snprintf(str,sizeof(str),"0x%x",n);
    UBOOT_INFO("u32PeriodPWM = %ld \n",n);
    setenv(PWM_PERIOD,str);

    memset(str,0,sizeof(str));
    n = Profile_GetInteger("panel", "u16DivPWM", 0);
    snprintf(str,sizeof(str),"0x%x",n);
    UBOOT_DEBUG("u16DivPWM = %ld \n",n);
    setenv(PWM_DIVPWM,str);

    memset(str,0,sizeof(str));
    n = Profile_GetInteger("panel", "u32DutyPWM", 0);// Duty use Div value,fix it later
    snprintf(str,sizeof(str),"0x%x",n);
    UBOOT_INFO("u32DutyPWM = %s\n",str);
    setenv(PWM_DUTY,str);

    memset(str,0,sizeof(str));
    n = Profile_GetInteger("panel", "bPolPWM", 0);// Duty use polpwm value,fix it later
    snprintf(str,sizeof(str),"0x%x",n);
    UBOOT_DEBUG("bPolPWM = %s\n",str);
    setenv(PWM_POLPWM,str);

    memset(str,0,sizeof(str));
    n = Profile_GetInteger("panel", "u16MaxPWMvalue", 0);// Duty use u16MaxPWMvalue value,fix it later
    snprintf(str,sizeof(str),"0x%x",n);
    UBOOT_DEBUG("u16MaxPWMvalue = %s\n",str);
    setenv(PWM_MAXPWM,str);

    memset(str,0,sizeof(str));
    n = Profile_GetInteger("panel", "u16MinPWMvalue", 0);// Duty use u16MinPWMvalue value,fix it later
    snprintf(str,sizeof(str),"0x%x",n);
    UBOOT_DEBUG("u16MinPWMvalue = %s\n",str);
    setenv(PWM_MINPWM,str);
    memset(str,0,sizeof(str));

#endif
    if(script)
        free(script);
    return 0;
}

#endif

int Load_PanelSetting_ToFlash(void)
{
    int ret = -1;
    PanelType pnl;
    char *p_str = NULL;

    memset(&pnl,0,sizeof(pnl));
    #if ((CONFIG_VESTEL_MB100 == 1)||(CONFIG_VESTEL_MB97 == 1)) 
    vfs_mount(CONF);
    char as8PanelFilePath[50] = "\0";
    snprintf(as8PanelFilePath, sizeof(as8PanelFilePath),"/VESTEL_D1_Plus_TMG.bin");
    setenv("panel_path", as8PanelFilePath);
    saveenv();
    #else
    vfs_mount(CONFIG);
    #endif

    p_str = getenv ("panel_path");
    //printf("Load_PanelSetting_ToFlash,line:%dgPnlPath:%s, p_str:%s\n",__LINE__,gPnlPath,p_str);
    if(NULL != p_str)
    {
        memcpy(gPnlPath, p_str, sizeof(gPnlPath));
        //setenv("panel_path",NULL);
        //saveenv();
    }
    //printf("Load_PanelSetting_ToFlash,line:%dgPnlPath:%s, p_str:%s\n",__LINE__,gPnlPath,p_str);

    if(parse_pnl_ini(gPnlPath,&pnl)!=0)
    {
        UBOOT_ERROR("parse_pnl_ini fail !!\n");
        return ret;
    }

    UBOOT_DEBUG("panel para size =: 0x%08x \n",sizeof(pnl));
    count_data_crc32_setenv((U32)&pnl,sizeof(pnl),"panel_crc");

    ret = raw_write((U32)&pnl,db_table.panelpara_offset,sizeof(pnl));
    if(ret == -1)
    {
        UBOOT_ERROR("write data to spiflash fail...>>>\n");
    }
    return ret;
}
#if defined(PCB_WITH_MFC) && (CONFIG_VESTEL_MB97 == 1)
int Load_Ursa5Setting_ToFlash(void) 
{
    int ret = -1;
    char *p_str = NULL;
    ursa5_cmd_table u5cmd;
    memset(&u5cmd,0,sizeof(u5cmd));

    #if ((CONFIG_VESTEL_MB100 == 1)||(CONFIG_VESTEL_MB97 == 1))
    vfs_mount(CONF);
    char as8PanelFilePath[50] = "\0";
    snprintf(as8PanelFilePath, sizeof(as8PanelFilePath),"/VESTEL_D1_Plus_TMG.bin");
    setenv("panel_path", as8PanelFilePath);
    saveenv();
    #else
    vfs_mount(CONFIG);
    #endif

    p_str = getenv ("panel_path");
    //printf("Load_PanelSetting_ToFlash,line:%dgPnlPath:%s, p_str:%s\n",__LINE__,gPnlPath,p_str);
    if(NULL != p_str)
    {
        memcpy(gPnlPath, p_str, sizeof(gPnlPath));
        //setenv("panel_path",NULL);
        //saveenv();
    }
    //printf("Load_PanelSetting_ToFlash,line:%dgPnlPath:%s, p_str:%s\n",__LINE__,gPnlPath,p_str);

    if(parse_ursa5_ini(gPnlPath,&u5cmd)!=0)
    {
        UBOOT_ERROR("parse_ursa5_ini fail !!\n");
        return ret;
    }

    //UBOOT_DEBUG("ursa5 para size =: 0x%08x \n",sizeof(u5cmd));
    printf("\033[0;35m ursa5 para size =: 0x%08x \n\033[m",sizeof(u5cmd));
    count_data_crc32_setenv((U32)&u5cmd,sizeof(u5cmd),"ursa5_crc");

    ret = raw_write((U32)&u5cmd,db_table.ursa_6m30_offset,sizeof(u5cmd));
    if(ret == -1)
    {
        UBOOT_ERROR("write data to spiflash fail...>>>\n");
    }
    return ret;
}
#endif

int Read_PanelParaFromflash(PanelType * panel_data)
{
    int ret = -1;
    UBOOT_DEBUG("db_table.panelpara_offset =:0x%x...db_table.panelpara_size=:0x%x\n",db_table.panelpara_offset,db_table.panelpara_size);
    if(-1 == raw_read((U32)panel_data,db_table.panelpara_offset,db_table.panelpara_size))
    {
        UBOOT_ERROR("ERROR: Read_PanelParaFromflash fail...>>>\n");
    }
    else
    {
        UBOOT_DEBUG("Read_PanelParaFromflash success...>>>\n");
        if(count_data_crc32_getenv((U32)panel_data,db_table.panelpara_size,"panel_crc")==-1)
        {
            return ret;
        }
        else
        {
            ret = 0;
        }
    }
    UBOOT_DEBUG("panel_data.m_wPanelVStart=: 0x%x\n",panel_data->m_wPanelVStart);
    UBOOT_DEBUG("panel_data.m_wPanelWidth=: 0x%x\n",panel_data->m_wPanelWidth);
    UBOOT_DEBUG("panel_data.m_wPanelHeight=: 0x%x\n",panel_data->m_wPanelHeight);
    return ret;
}
#if defined(PCB_WITH_MFC) && (CONFIG_VESTEL_MB97 == 1)
int Read_Ursa5ParaFromflash(ursa5_cmd_table * ursa5_data)
{
    int ret = -1;
    UBOOT_DEBUG("db_table.ursa_6m30_offset =:0x%x...db_table.ursa_6m30_size=:0x%x\n",db_table.ursa_6m30_offset,db_table.ursa_6m30_size);
    if(-1 == raw_read((U32)ursa5_data,db_table.ursa_6m30_offset,db_table.ursa_6m30_size))
    {
        UBOOT_ERROR("ERROR: Read_Ursa5ParaFromflash fail...>>>\n");
    }
    else
    {
        UBOOT_DEBUG("Read_Ursa5ParaFromflash success...>>>\n");
        if(count_data_crc32_getenv((U32)ursa5_data,db_table.ursa_6m30_size,"ursa5_crc")==-1)
        {
            return ret;
        }
        else
        {
            ret = 0;
        }
    }
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_PANEL_TYPE =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_PANEL_TYPE);
    UBOOT_DEBUG("ursa5_data->URSA5_MASK_HS =: 0x%x\n",ursa5_data->URSA5_MASK_HS);
    UBOOT_DEBUG("ursa5_data->URSA5_MASK_VS =: 0x%x\n",ursa5_data->URSA5_MASK_VS);
    UBOOT_DEBUG("ursa5_data->URSA5_MASK_DE =: 0x%x\n",ursa5_data->URSA5_MASK_DE);
    UBOOT_DEBUG("ursa5_data->URSA5_PANEL_INV_HSYNC =: 0x%x\n",ursa5_data->URSA5_PANEL_INV_HSYNC);
    UBOOT_DEBUG("ursa5_data->URSA5_PANEL_INV_VSYNC =: 0x%x\n",ursa5_data->URSA5_PANEL_INV_VSYNC);
    UBOOT_DEBUG("ursa5_data->URSA5_PANEL_INV_DE =: 0x%x\n",ursa5_data->URSA5_PANEL_INV_DE);
    UBOOT_DEBUG("ursa5_data->URSA5_DITHER_8BITS =: 0x%x\n",ursa5_data->URSA5_DITHER_8BITS);
    UBOOT_DEBUG("ursa5_data->URSA5_DITHER_EN =: 0x%x\n",ursa5_data->URSA5_DITHER_EN);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_A =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_A);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_B =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_B);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_C =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_C);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_D =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_CHANNEL_SWAP_CHANNEL_D);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_CHANNEL_NUMBER =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_CHANNEL_NUMBER);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_BIT_NUMBER =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_BIT_NUMBER);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_SWAP_PAIR =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_SWAP_PAIR);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_SWAP_POL =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_SWAP_POL);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_INCREASE_VTOTAL_FOR_50HZ =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_INCREASE_VTOTAL_FOR_50HZ);
    UBOOT_DEBUG("ursa5_data->URSA5_DITHER_TAIL_CUT =: 0x%x\n",ursa5_data->URSA5_DITHER_TAIL_CUT);
    UBOOT_DEBUG("ursa5_data->URSA5_CUS_PANEL_SWING_DATA =: 0x%x\n",ursa5_data->URSA5_CUS_PANEL_SWING_DATA);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_HTOTAL =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_HTOTAL);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_VTOTAL =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_VTOTAL);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_HSTART =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_HSTART);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_VSTART =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_VSTART);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_WIDTH =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_WIDTH);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_HEIGHT =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_HEIGHT);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_SHIFT_PAIR =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_SHIFT_PAIR);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_TX_TI_MODE =: 0x%x\n",ursa5_data->URSA5_LVDS_TX_TI_MODE);
    UBOOT_DEBUG("ursa5_data->URSA5_ENABLE_MST_MIRROR_FUNC =: 0x%x\n",ursa5_data->URSA5_ENABLE_MST_MIRROR_FUNC);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_RX_CHCONNECT =: 0x%x\n",ursa5_data->URSA5_LVDS_RX_CHCONNECT);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_RX_BIT_NUM =: 0x%x\n",ursa5_data->URSA5_LVDS_RX_BIT_NUM);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_RX_TI_MODE =: 0x%x\n",ursa5_data->URSA5_LVDS_RX_TI_MODE);
    UBOOT_DEBUG("ursa5_data->URSA5_LVDS_RX_SWAP_ODD_EVEN =: 0x%x\n",ursa5_data->URSA5_LVDS_RX_SWAP_ODD_EVEN);
    UBOOT_DEBUG("ursa5_data->URSA5_CUS_LVDS_RX_SWAP_MSB_LSB =: 0x%x\n",ursa5_data->URSA5_CUS_LVDS_RX_SWAP_MSB_LSB);
    UBOOT_DEBUG("ursa5_data->URSA5_CUS_LVDS_RX_SWAP_P_N =: 0x%x\n",ursa5_data->URSA5_CUS_LVDS_RX_SWAP_P_N);
    return ret;
}
#endif

int parse_board_ini(char *path, st_board_para *p_data)
{
    long n;
    char *script = NULL;
    U32 filesize = 0;
    char str[BUFFER_SIZE];
    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        while (*path== '/') path++;
        path=strstr(path,"/");
        UBOOT_INFO("filter /config, and find file again!!\n");
        script = loadscript(path,&filesize);
        if(script == NULL)
        {
            return -1;
        }
    }

    memset(str,0,sizeof(str));
    UBOOT_INFO("sizeof( board ini script ) --------> %u bytes\n",filesize);
    Profile_Init((char *)script,filesize);

    n = Profile_GetInteger("PanelRelativeSetting", "m_u8BOARD_PWM_PORT", 2);
    UBOOT_DEBUG("m_u8BOARD_PWM_PORT = %ld \n",n);
    p_data->m_u8BOARD_PWM_PORT = n;
    snprintf(str,sizeof(str),"%d",n);
    setenv(PWM_CH,str);
    saveenv();

    n = Profile_GetInteger("PanelRelativeSetting", "m_u16BOARD_LVDS_CONNECT_TYPE", 0);
    UBOOT_DEBUG("m_u16BOARD_LVDS_CONNECT_TYPE = %ld \n",n);
    p_data->m_u16BOARD_LVDS_CONNECT_TYPE = n;

    n = Profile_GetInteger("PanelRelativeSetting", "m_bPANEL_PDP_10BIT", 0);
    UBOOT_DEBUG("m_bPANEL_PDP_10BIT = %ld \n",n);
    p_data->m_bPANEL_PDP_10BIT = n;

    n = Profile_GetInteger("PanelRelativeSetting", "m_bPANEL_SWAP_LVDS_POL", 0);
    UBOOT_DEBUG("m_bPANEL_SWAP_LVDS_POL = %ld \n",n);
    p_data->m_bPANEL_SWAP_LVDS_POL = n;

    n = Profile_GetInteger("PanelRelativeSetting", "m_bPANEL_SWAP_LVDS_CH", 0);
    UBOOT_DEBUG("m_bPANEL_SWAP_LVDS_CH = %ld \n",n);
    p_data->m_bPANEL_SWAP_LVDS_CH = n;

    n = Profile_GetInteger("PanelRelativeSetting", "m_bPANEL_CONNECTOR_SWAP_PORT", 0);
    UBOOT_DEBUG("m_bPANEL_CONNECTOR_SWAP_PORT = %ld \n",n);
    p_data->m_bPANEL_CONNECTOR_SWAP_PORT = n;

    n = Profile_GetInteger("PanelRelativeSetting", "m_u16LVDS_PN_SWAP_L", 0);
    UBOOT_DEBUG("m_u16LVDS_PN_SWAP_L = %ld \n",n);
    p_data->m_u16LVDS_PN_SWAP_L = n;

    n = Profile_GetInteger("PanelRelativeSetting", "m_u16LVDS_PN_SWAP_H", 0);
    UBOOT_DEBUG("m_u16LVDS_PN_SWAP_H = %ld \n",n);
    p_data->m_u16LVDS_PN_SWAP_H = n;

    if(script)
        free(script);
    return 0;
}

int Load_BoardSetting_ToFlash(void)
{
    int ret = -1;
    st_board_para stBoard;
    memset(&stBoard,0,sizeof(stBoard));
    vfs_mount(CONFIG);
    if(parse_board_ini(gBoardPath, &stBoard)!=0)
    {
        UBOOT_ERROR("parse_board_ini fail !!\n");
        return ret;
    }

    UBOOT_DEBUG("board para size =: 0x%08x \n",sizeof(stBoard));
    count_data_crc32_setenv((U32)&stBoard, sizeof(stBoard), "board_crc");

    ret = raw_write((U32)&stBoard, db_table.boardpara_offset, sizeof(stBoard));
    if(ret == -1)
    {
        UBOOT_ERROR("write data to spiflash fail...>>>\n");
    }
    return ret;
}

int Read_BoardParaFromflash(st_board_para * board_data)
{
    int ret = -1;
    UBOOT_DEBUG("db_table.boardpara_offset =:0x%x...db_table.boardpara_size=:0x%x\n",db_table.boardpara_offset,db_table.boardpara_size);
    if(-1 == raw_read((U32)board_data,db_table.boardpara_offset,db_table.boardpara_size))
    {
        UBOOT_ERROR("ERROR: Read_BoardParaFromflash fail...>>>\n");
    }
    else
    {
        UBOOT_DEBUG("Read_BoardParaFromflash success...>>>\n");
        if(count_data_crc32_getenv((U32)board_data,db_table.boardpara_size,"board_crc")==-1)
        {
            return ret;
        }
        else
        {
            ret = 0;
        }
    }
    return ret;
}

#endif

#if ENABLE_KEYPAD_CUST
static U8 parse_strhex_2_int(char *strhex)
{
    char *hexptr;
    U8 u8Result = 0;
    U8 u8Offset = 0;

    if (strlen(strhex) < 2)
        return 0;

    hexptr = strhex + 2; //ignore  "0x"

    u8Offset = 0;
    while (*hexptr != '\0')
    {
        u8Result = u8Result << u8Offset;
        if (*hexptr >= '0' && *hexptr <= '9')
            u8Result = u8Result + (*hexptr - '0');
        else if (*hexptr >= 'A' && *hexptr <= 'F')
            u8Result = u8Result + (*hexptr - 'A') + 10;
        else if (*hexptr >= 'a' && *hexptr <= 'f')
            u8Result = u8Result + (*hexptr - 'a') + 10;

        hexptr++;
        u8Offset += 4;
    }

    return u8Result;
}

static void parse_keypad_threshold(char *str, SAR_RegCfg *pdata)
{
    U8 u8Index = 0;
    char *sptr;
    char *pch;

    if (strlen(str) < 3)
        return ;

    sptr = str + 1; //ignore "{"
    sptr[strlen(sptr) - 2] = 0;
    pch = strtok(sptr, ", ");
    u8Index = 0;
    while (pch != NULL)
    {
        pdata->u8KeyThreshold[u8Index] = parse_strhex_2_int(pch);
        UBOOT_DEBUG("[parse_keypad_threshold] %s to 0x%x\n", pch, pdata->u8KeyThreshold[u8Index]);
        pch = strtok(NULL, ", ");
        u8Index++;
    }
}

static void parse_keypad_keycode(char *str, SAR_RegCfg *pdata)
{
    U8 u8Index;
    char *sptr;
    char *pch;

    if (strlen(str) < 3)
        return ;

    sptr = str + 1; //ignore "{"
    sptr[strlen(sptr) - 2] = 0;
    pch = strtok(sptr, ", ");
    u8Index = 0;
    while (pch != NULL)
    {
        pdata->u8KeyCode[u8Index] = parse_strhex_2_int(pch);
        UBOOT_DEBUG("[parse_keypad_keycode] %s to 0x%x\n", pch, pdata->u8KeyCode[u8Index]);
        pch = strtok(NULL, ", ");
        u8Index++;
    }
}


int parse_keypad_ini(char *path, st_keypad_para *kpdpdata, int *pcount)
{
#define SAR_CH_NUM 4

#define PARSE_TITLE "Keypad_Ext"

#define PARSE_ENABLE "bEnable"
#define PARSE_CHID "u8SARChID"
#define PARSE_UPBND "u8SARChUpBnd"
#define PARSE_LOWBND "u8SARChLoBnd"
#define PARSE_LEVELNUM "u8KeyLevelNum"
#define PARSE_THRESHOLD "u8KeyThreshold"
#define PARSE_KEYCODE "u8KeyCode"


    long n;
    char str[BUFFER_SIZE];
    char *script = NULL;
    U32 filesize = 0;
    SAR_RegCfg *pdata = kpdpdata->kpdCfg;

    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        while (*path== '/') path++;
        path=strstr(path,"/");
        UBOOT_INFO("filter /config, and find file again!!\n");
        script = loadscript(path,&filesize);
        if(script == NULL)
        {
            return -1;
        }
    }
    UBOOT_INFO("sizeof( keypad ini script ) --------> %u bytes path=%s\n",filesize, path);
    Profile_Init((char *)script,filesize);

    //set keypad select
    U8 u8KeypadSelect = 1;
    U8 u8Ch = 0;
    char title[BUFFER_SIZE];
    char parse[BUFFER_SIZE];
    u8KeypadSelect = Profile_GetInteger("KEYPAD", "keypadSelect", 0);

    if (u8KeypadSelect > 0)
    {
        title[0] = 0;
        UBOOT_INFO(title, "%s_%d", PARSE_TITLE, u8KeypadSelect);

        for (u8Ch = 1; u8Ch <= SAR_CH_NUM; u8Ch++)
        {
            U8 u8ChID_Offset = 0;

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_ENABLE, u8Ch);
            n=Profile_GetBoolean(title, parse,0);
            UBOOT_DEBUG("[KEYPAD PARSE] %s => %ld\n", parse, n);
            if (n == 0)
                u8ChID_Offset = Kpd_ChID_Offset;

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_CHID, u8Ch);
            n=Profile_GetInteger(title, parse,0) + u8ChID_Offset;
            UBOOT_DEBUG("[KEYPAD PARSE] %s => 0x%lx\n", parse, n);
            pdata[*pcount].u8SARChID = (U8) n;

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_UPBND, u8Ch);
            n=Profile_GetInteger(title, parse,0);
            UBOOT_DEBUG("[KEYPAD PARSE] %s => 0x%lx\n", parse, n);
            pdata[*pcount].u8UpBnd = (U8) n;

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_LOWBND, u8Ch);
            n=Profile_GetInteger(title, parse,0);
            UBOOT_DEBUG("[KEYPAD PARSE] %s => 0x%lx\n", parse, n);
            pdata[*pcount].u8LoBnd = (U8) n;

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_LEVELNUM, u8Ch);
            n=Profile_GetInteger(title, parse,0);
            UBOOT_DEBUG("[KEYPAD PARSE] %s => 0x%lx\n", parse, n);
            pdata[*pcount].u8KeyLevelNum = (U8) n;

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_THRESHOLD, u8Ch);
            Profile_GetString(title, parse,"", str, sizearray(str));
            UBOOT_DEBUG("[KEYPAD PARSE] %s => %s\n", parse, str);
            parse_keypad_threshold(str, &pdata[*pcount]);

            parse[0] = 0;
            UBOOT_INFO(parse, "%s_%d", PARSE_KEYCODE, u8Ch);
            Profile_GetString(title, parse,"", str, sizearray(str));
            UBOOT_DEBUG("[KEYPAD PARSE] %s => %s\n", parse, str);
            parse_keypad_keycode(str, &pdata[*pcount]);

            *pcount = *pcount+1;
        }
    }

    //saveenv keypad select for 0: default setting, 1 ~ :setting for customer
    UBOOT_INFO("[KEYPAD Init] u8KeypadSelect=%d\n", u8KeypadSelect);

    kpdpdata->u8KeypadSelect = u8KeypadSelect;

    if(script)
        free(script);

    return 0;
}

int Load_KeypadSetting_ToFlash(void)
{
    int ret = -1;
    st_keypad_para kpadPara;
    int kpdCount = 0;
    memset(&kpadPara,0,sizeof(kpadPara));
    vfs_mount(CONFIG);
    if(parse_keypad_ini(gKeypadPath, &kpadPara, &kpdCount)!=0)
    {
        UBOOT_ERROR("parse_pnl_ini fail !!\n");
        return ret;
    }

    UBOOT_DEBUG("keypad para size =: 0x%08x \n",sizeof(kpadPara));

    ret = raw_write((U32)&kpadPara, db_table.keypad_offset, sizeof(kpadPara));
    if(ret == -1)
    {
        UBOOT_ERROR("write data to spiflash fail...>>>\n");
    }
    return ret;
}

int Read_KeypadParaFromflash(st_keypad_para *keypad_data)
{
    UBOOT_DEBUG("db_table.keypad_offset =:0x%x...db_table.keypad_size=:0x%x\n",db_table.keypad_offset,db_table.keypad_size);
    if ((db_table.keypad_offset==0) || (db_table.keypad_size==0)) return -1;
    if(-1 == raw_read((U32)keypad_data,db_table.keypad_offset,db_table.keypad_size))
    {
        UBOOT_ERROR("ERROR: Read_KeypadParaFromflash fail...>>>\n");
        return -1;
    }
    else
    {
        UBOOT_DEBUG("Read_PanelParaFromflash success...>>>\n");
    }

    return 1;
}
#endif

#if (ENABLE_ENABLE_URSA == 1)
#if (ENABLE_URSA_6M30 == 1)
int iniparser_6m30_cmd(ursa_6m30_cmd_table * cmd_table)
{
    int ret = -1;
    char * script = NULL;
    char InPath[BUFFER_SIZE]= {0};
    U32 filesize = 0;
    vfs_mount(CONFIG);
    snprintf(InPath,sizeof(InPath),"%s/6m30_mode.ini",CONFIG_PATH);
    script = loadscript(InPath,&filesize);
    if(script != NULL)
    {
        Profile_Init(script,filesize);
        cmd_table->URSA_6M30_LVDS_CHANNEL_SWAP_MODE = Profile_GetInteger("MISC_6M30_CFG", "6M30_LVDS_CHANNEL_SWAP_MODE", 0);
        cmd_table->URSA_6M30_IN_LVDS_TIMODE = Profile_GetInteger("MISC_6M30_CFG", "6M30_IN_LVDS_TIMODE", 0);
        cmd_table->URSA_6M30_IN_LVDS_TI_BITNUM = Profile_GetInteger("MISC_6M30_CFG", "6M30_IN_LVDS_TI_BITNUM", 0);
        cmd_table->URSA_6M30_OUT_LVDS_TIMODE = Profile_GetInteger("MISC_6M30_CFG", "6M30_OUT_LVDS_TIMODE", 0);
        cmd_table->URSA_6M30_OUT_LVDS_TI_BITNUM = Profile_GetInteger("MISC_6M30_CFG", "6M30_OUT_LVDS_TI_BITNUM", 0);

        cmd_table->URSA_6M30_SSC_SEL = Profile_GetInteger("MISC_6M30_CFG", "6M30_SSC_SEL", 0);
        cmd_table->URSA_6M30_SSC_ENABLE = Profile_GetInteger("MISC_6M30_CFG", "6M30_SSC_ENABLE", 0);
        cmd_table->URSA_6M30_SSC_FREQ = Profile_GetInteger("MISC_6M30_CFG", "6M30_SSC_FREQ", 0);
        cmd_table->URSA_6M30_SSC_PERCENT = Profile_GetInteger("MISC_6M30_CFG", "6M30_SSC_PERCENT", 0);

        UBOOT_DEBUG(" --->>> 6M30_LVDS_CHANNEL_SWAP_MODE is %x \n",cmd_table->URSA_6M30_LVDS_CHANNEL_SWAP_MODE);
        UBOOT_DEBUG(" --->>> 6M30_IN_LVDS_TIMODE is %x \n",cmd_table->URSA_6M30_IN_LVDS_TIMODE);
        UBOOT_DEBUG(" --->>> 6M30_IN_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_6M30_IN_LVDS_TI_BITNUM);
        UBOOT_DEBUG(" --->>> 6M30_OUT_LVDS_TIMODE is %x \n",cmd_table->URSA_6M30_OUT_LVDS_TIMODE);
        UBOOT_DEBUG(" --->>> 6M30_OUT_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_6M30_OUT_LVDS_TI_BITNUM);

        UBOOT_DEBUG(" --->>> 6M30_SSC_SEL is %x \n",cmd_table->URSA_6M30_SSC_SEL);
        UBOOT_DEBUG(" --->>> 6M30_SSC_ENABLE is %x \n",cmd_table->URSA_6M30_SSC_ENABLE);
        UBOOT_DEBUG(" --->>> 6M30_SSC_FREQ is %x \n",cmd_table->URSA_6M30_SSC_FREQ);
        UBOOT_DEBUG(" --->>> 6M30_SSC_PERCENT is %x \n",cmd_table->URSA_6M30_SSC_PERCENT);
        ret = 0;
    }
    else
    {
        UBOOT_ERROR("ubifsload 6m30.ini fail...>>>\n");
    }
    free(script);
    return ret;
}
int Read_Ursa_6m30_Para(ursa_6m30_cmd_table * cmd_table)
{
    int ret = -1;
    UBOOT_INFO("db_table.ursa_6m30_offset =:0x%x...db_table.ursa_6m30_size=:0x%x\n",db_table.ursa_6m30_offset,db_table.ursa_6m30_size);

    if(-1 == raw_read((U32)cmd_table,db_table.ursa_6m30_offset,db_table.ursa_6m30_size))
    {
        UBOOT_ERROR("ERROR: Read_UrsaParaFromflash fail...>>>\n");
    }
    else
    {
        if(count_data_crc32_getenv((U32)cmd_table,db_table.ursa_6m30_size,"ursa_crc")==-1)
        {
            return ret;
        }
        else
        {
            ret = 0;
        }
    }

    UBOOT_DEBUG(" cmd_table.6M30_LVDS_CHANNEL_SWAP_MODE is %x \n",cmd_table->URSA_6M30_LVDS_CHANNEL_SWAP_MODE);
    UBOOT_DEBUG(" cmd_table.6M30_IN_LVDS_TIMODE is %x \n",cmd_table->URSA_6M30_IN_LVDS_TIMODE);
    UBOOT_DEBUG(" cmd_table.6M30_IN_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_6M30_IN_LVDS_TI_BITNUM);
    UBOOT_DEBUG(" cmd_table.6M30_OUT_LVDS_TIMODE is %x \n",cmd_table->URSA_6M30_OUT_LVDS_TIMODE);
    UBOOT_DEBUG(" cmd_table.6M30_OUT_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_6M30_OUT_LVDS_TI_BITNUM);

    UBOOT_DEBUG(" cmd_table.6M30_SSC_SEL is %x \n",cmd_table->URSA_6M30_SSC_SEL);
    UBOOT_DEBUG(" cmd_table.6M30_SSC_ENABLE is %x \n",cmd_table->URSA_6M30_SSC_ENABLE);
    UBOOT_DEBUG(" cmd_table.6M30_SSC_FREQ is %x \n",cmd_table->URSA_6M30_SSC_FREQ);
    UBOOT_DEBUG(" cmd_table.6M30_SSC_PERCENT is %x \n",cmd_table->URSA_6M30_SSC_PERCENT);
    return ret;
}
int Load_Ursa6m30Para_ToFlash(void)
{
    int ret = -1;
    ursa_6m30_cmd_table cmd_table= {0};
    if(iniparser_6m30_cmd(&cmd_table)==0)
    {
        UBOOT_DEBUG("6m30 para size =: 0x%08x \n",sizeof(cmd_table));
        UBOOT_DEBUG("db_table.ursa_6m30_offset =: 0x%x\n",db_table.ursa_6m30_offset);
        count_data_crc32_setenv((U32)&cmd_table,sizeof(cmd_table),"ursa_crc");

        ret = raw_write((U32)&cmd_table,db_table.ursa_6m30_offset,sizeof(cmd_table));
        if(ret == -1)
        {
            UBOOT_ERROR("write ursa_6m30 data to spiflash fail...>>>\n");
        }
    }
    else
    {
        UBOOT_ERROR("parser_6m30_cmd fail ...>>>\n");
    }

    return ret;
}

int Ursa_6M30_Setting(ursa_6m30_cmd_table * cmd_table)
{
    int ret = -1;
    MDrv_Ursa_6M30_ChanelSwap_Mode(cmd_table->URSA_6M30_LVDS_CHANNEL_SWAP_MODE);
    g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode = cmd_table->URSA_6M30_IN_LVDS_TIMODE;
    g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = cmd_table->URSA_6M30_IN_LVDS_TI_BITNUM;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode = cmd_table->URSA_6M30_OUT_LVDS_TIMODE;
    g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = cmd_table->URSA_6M30_OUT_LVDS_TI_BITNUM;

    MDrv_Ursa_6M30_Data_Init();

    g_UrsaCMDGenSetting.g_SscFreqPercent.SscSel = cmd_table->URSA_6M30_SSC_SEL;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscEN = cmd_table->URSA_6M30_SSC_ENABLE;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscFreq = cmd_table->URSA_6M30_SSC_FREQ;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscPercent = cmd_table->URSA_6M30_SSC_PERCENT;

    if(MDrv_Ursa_6M30_3D_Cmd(UC_SET_SSC_FREQ_PERCENT)>0)
    {
        ret = 0;
    }

    return ret;
}

#elif (ENABLE_URSA_8 == 1) || (ENABLE_URSA_6M40 == 1)

int parse_model_ini_ForUrsa(char* path, char* UrsaInIPath)
{
    int ret = -1;//
    char *script = NULL;
    char str[BUFFER_SIZE]= {0};
    U32 filesize = 0;
    script = loadscript(path,&filesize);
    if(script == NULL)
    {
        while (*path== '/') path++;
        path=strstr(path,"/");
        UBOOT_INFO("filter /config, and find file again!!\n");
        script = loadscript(path,&filesize);
        if(script == NULL)
        {
            goto exit;
        }
    }
    UBOOT_INFO("sizeof( model ini script ) --------> %u bytes\n",filesize);

    Profile_Init((char *)script,filesize);
    if(Profile_GetString("Ursa", "m_pUrsaName","", str, sizearray(str)))
    {
        UBOOT_INFO("Half Ursa.ini path --> %s\n",str);
        snprintf(UrsaInIPath,BUFFER_SIZE,"%s",str);
        UBOOT_INFO("Full Ursa.ini  path --> %s\n",UrsaInIPath);
        ret = 0;
    }
    else
    {
        goto exit;
    }

exit:
    if(script)
        free(script);
    return ret;
}

int Parser_Ursa_Ini(ursa_cmd_table * cmd_table)
{
    int ret = -1;
    char * script = NULL;
    char InPath[BUFFER_SIZE]= {0};
    char OutPath[BUFFER_SIZE]= {0};
    char UrsaBinName[BUFFER_SIZE]= {0};
    U32 filesize = 0;
    vfs_mount(CONFIG);
    memset(InPath,0,sizeof(InPath));
    snprintf(InPath,sizeof(InPath),"%s/sys.ini",CONFIG_PATH);
    ret = parse_sys_ini(InPath,OutPath);
    if(ret)
    {
        goto Ursa_exit;
    }

    memset(InPath,0,sizeof(InPath));
    memcpy(InPath,OutPath,sizeof(OutPath));
    ret = parse_model_ini_ForUrsa(InPath,OutPath);
    if(ret)
    {
        goto Ursa_exit;
    }
    UBOOT_INFO("Full Ursa.ini path --> %s\n",OutPath);

    memset(InPath,0,sizeof(InPath));
    memcpy(InPath,OutPath,sizeof(OutPath));
    script = loadscript(InPath,&filesize);
    if(script != NULL)
    {
        Profile_Init(script,filesize);
        cmd_table->URSA_EXTERNAL = Profile_GetBoolean("URSA_PARA_CFG", "URSA_EXTERNAL", 1);
        cmd_table->URSA_MEMC_ENABLE = Profile_GetInteger("URSA_PARA_CFG", "URSA_MEMC_ENABLE", 0);
        cmd_table->URSA_LVDS_CHANNEL_SWAP_MODE = Profile_GetInteger("URSA_PARA_CFG", "URSA_LVDS_CHANNEL_SWAP_MODE", 0);
        cmd_table->URSA_LVDS_SWAP_POL = Profile_GetInteger("URSA_PARA_CFG", "URSA_LVDS_SWAP_POL", 0);
        cmd_table->URSA_IN_LVDS_TIMODE = Profile_GetInteger("URSA_PARA_CFG", "URSA_IN_LVDS_TIMODE", 0);
        cmd_table->URSA_IN_LVDS_TI_BITNUM = Profile_GetInteger("URSA_PARA_CFG", "URSA_IN_LVDS_TI_BITNUM", 0);
        cmd_table->URSA_OUT_LVDS_TIMODE = Profile_GetInteger("URSA_PARA_CFG", "URSA_OUT_LVDS_TIMODE", 0);
        cmd_table->URSA_OUT_LVDS_TI_BITNUM = Profile_GetInteger("URSA_PARA_CFG", "URSA_OUT_LVDS_TI_BITNUM", 0);

        cmd_table->URSA_SSC_SEL = Profile_GetInteger("URSA_PARA_CFG", "URSA_SSC_SEL", 0);
        cmd_table->URSA_SSC_ENABLE = Profile_GetInteger("URSA_PARA_CFG", "URSA_SSC_ENABLE", 0);
        cmd_table->URSA_SSC_FREQ = Profile_GetInteger("URSA_PARA_CFG", "URSA_SSC_FREQ", 0);
        cmd_table->URSA_SSC_PERCENT = Profile_GetInteger("URSA_PARA_CFG", "URSA_SSC_PERCENT", 0);
        cmd_table->URSA_OSD_PROTECT_MODE = Profile_GetInteger("URSA_PARA_CFG", "URSA_OSD_PROTECT_MODE", 0);

        UBOOT_DEBUG(" --->>> URSA_EXTERNAL is %x \n",cmd_table->URSA_EXTERNAL);
        UBOOT_DEBUG(" --->>> URSA_MEMC_ENABLE is %x \n",cmd_table->URSA_MEMC_ENABLE);
        UBOOT_DEBUG(" --->>> URSA_LVDS_CHANNEL_SWAP_MODE is %x \n",cmd_table->URSA_LVDS_CHANNEL_SWAP_MODE);
        UBOOT_DEBUG(" --->>> URSA_LVDS_SWAP_POL is %x \n",cmd_table->URSA_LVDS_SWAP_POL);
        UBOOT_DEBUG(" --->>> URSA_IN_LVDS_TIMODE is %x \n",cmd_table->URSA_IN_LVDS_TIMODE);
        UBOOT_DEBUG(" --->>> URSA_IN_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_IN_LVDS_TI_BITNUM);
        UBOOT_DEBUG(" --->>> URSA_OUT_LVDS_TIMODE is %x \n",cmd_table->URSA_OUT_LVDS_TIMODE);
        UBOOT_DEBUG(" --->>> URSA_OUT_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_OUT_LVDS_TI_BITNUM);

        UBOOT_DEBUG(" --->>> URSA_SSC_SEL is %x \n",cmd_table->URSA_SSC_SEL);
        UBOOT_DEBUG(" --->>> URSA_SSC_ENABLE is %x \n",cmd_table->URSA_SSC_ENABLE);
        UBOOT_DEBUG(" --->>> URSA_SSC_FREQ is %x \n",cmd_table->URSA_SSC_FREQ);
        UBOOT_DEBUG(" --->>> URSA_SSC_PERCENT is %x \n",cmd_table->URSA_SSC_PERCENT);
        UBOOT_DEBUG(" --->>> URSA_OSD_PROTECT_MODE is %x \n",cmd_table->URSA_OSD_PROTECT_MODE);

        if(cmd_table->URSA_EXTERNAL == FALSE)
        {
            if(Profile_GetString("URSA_FILE_CFG", "m_pUrsaBinName","", UrsaBinName, sizearray(UrsaBinName)))
            {
                UBOOT_INFO("Full Ursa Bin Name --> %s\n",UrsaBinName);
                ret = 0;
                setenv("ursa_bin_name",UrsaBinName);
                saveenv();
            }
            else
            {
                goto Ursa_exit;
            }
        }
        ret = 0;
    }
    else
    {
        UBOOT_ERROR("ubifsload 6m30.ini fail...>>>\n");
    }

Ursa_exit:
    if(script)
        free(script);
    return ret;
}
int Read_Ursa_Para(ursa_cmd_table * cmd_table)
{
    int ret = -1;
    UBOOT_INFO("db_table.ursa_offset =:0x%x...db_table.ursa_size=:0x%x\n",db_table.ursa_offset,db_table.ursa_size);

    if(-1 == raw_read((U32)cmd_table,db_table.ursa_offset,db_table.ursa_size))
    {
        UBOOT_ERROR("ERROR: Read_UrsaParaFromflash fail...>>>\n");
    }
    else
    {
        if(count_data_crc32_getenv((U32)cmd_table,db_table.ursa_size,"ursa_crc")==-1)
        {
            return ret;
        }
        else
        {
            ret = 0;
        }
    }

    UBOOT_DEBUG(" cmd_table.URSA_EXTERNAL is %x \n",cmd_table->URSA_EXTERNAL);
    UBOOT_DEBUG(" cmd_table.URSA_MEMC_ENABLE is %x \n",cmd_table->URSA_MEMC_ENABLE);
    UBOOT_DEBUG(" cmd_table.URSA_LVDS_CHANNEL_SWAP_MODE is %x \n",cmd_table->URSA_LVDS_CHANNEL_SWAP_MODE);
    UBOOT_DEBUG(" cmd_table.URSA_LVDS_SWAP_POL is %x \n",cmd_table->URSA_LVDS_SWAP_POL);
    UBOOT_DEBUG(" cmd_table.URSA_IN_LVDS_TIMODE is %x \n",cmd_table->URSA_IN_LVDS_TIMODE);
    UBOOT_DEBUG(" cmd_table.URSA_IN_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_IN_LVDS_TI_BITNUM);
    UBOOT_DEBUG(" cmd_table.URSA_OUT_LVDS_TIMODE is %x \n",cmd_table->URSA_OUT_LVDS_TIMODE);
    UBOOT_DEBUG(" cmd_table.URSA_OUT_LVDS_TI_BITNUM is %x \n",cmd_table->URSA_OUT_LVDS_TI_BITNUM);

    UBOOT_DEBUG(" cmd_table.URSA_SSC_SEL is %x \n",cmd_table->URSA_SSC_SEL);
    UBOOT_DEBUG(" cmd_table.URSA_SSC_ENABLE is %x \n",cmd_table->URSA_SSC_ENABLE);
    UBOOT_DEBUG(" cmd_table.URSA_SSC_FREQ is %x \n",cmd_table->URSA_SSC_FREQ);
    UBOOT_DEBUG(" cmd_table.URSA_SSC_PERCENT is %x \n",cmd_table->URSA_SSC_PERCENT);
	
	UBOOT_DEBUG(" cmd_table.URSA_OSD_PROTECT_MODE is %x \n",cmd_table->URSA_OSD_PROTECT_MODE);
    return ret;
}
int Load_UrsaPara_ToFlash(void)
{
    int ret = -1;
    ursa_cmd_table cmd_table= {0};
    if(Parser_Ursa_Ini(&cmd_table)==0)
    {
        UBOOT_DEBUG("Ursa para size =: 0x%08x \n",sizeof(cmd_table));
        UBOOT_DEBUG("db_table.ursa_offset =: 0x%x\n",db_table.ursa_offset);
        count_data_crc32_setenv((U32)&cmd_table,sizeof(cmd_table),"ursa_crc");

        ret = raw_write((U32)&cmd_table,db_table.ursa_offset,sizeof(cmd_table));
        if(ret == -1)
        {
            UBOOT_ERROR("write ursa_6m30 data to spiflash fail...>>>\n");
        }
    }
    else
    {
        UBOOT_ERROR("parser_cmd fail ...>>>\n");
    }

    return ret;
}

#if (ENABLE_URSA_8 == 1)
int Ursa_8_Setting(ursa_cmd_table * cmd_table)
{
    int ret = -1;
    MDrv_Ursa_8_ChanelSwap_Mode(cmd_table->URSA_LVDS_CHANNEL_SWAP_MODE);
    //g_UrsaCMDGenSetting.g_InitInLvdsAll.bTIMode = cmd_table->URSA_6M30_IN_LVDS_TIMODE;
    //g_UrsaCMDGenSetting.g_InitInLvdsAll.BitNums = cmd_table->URSA_6M30_IN_LVDS_TI_BITNUM;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bLvdsSwapPol = cmd_table->URSA_LVDS_SWAP_POL;
    g_UrsaCMDGenSetting.g_OutLvdsMode.bTIMode = cmd_table->URSA_OUT_LVDS_TIMODE;
    g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = cmd_table->URSA_OUT_LVDS_TI_BITNUM;

    g_UrsaCMDGenSetting.g_OsdMode.protect_mode = cmd_table->URSA_OSD_PROTECT_MODE;
    //MDrv_Ursa_6M30_Data_Init();
    udelay(50*1000);
    MDrv_Ursa_8_3D_Cmd ( UC_SET_OUT_LVDS_MODE);

    g_UrsaCMDGenSetting.g_SscFreqPercent.SscSel = cmd_table->URSA_SSC_SEL;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscEN = cmd_table->URSA_SSC_ENABLE;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscFreq = cmd_table->URSA_SSC_FREQ;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscPercent = cmd_table->URSA_SSC_PERCENT;
    udelay(50*1000);
    if(MDrv_Ursa_8_3D_Cmd(UC_SET_SSC_FREQ_PERCENT)>0)
    {
        ret = 0;
    }

    return ret;
}
#elif (ENABLE_URSA_6M40 == 1)
int Ursa_6M40_Syetting(ursa_cmd_table * cmd_table)
{
    int ret = -1;
    g_UrsaCMDGenSetting.g_OutLvdsMode.PanelBitNums = cmd_table->URSA_OUT_LVDS_TI_BITNUM;
    g_UrsaCMDGenSetting.g_OsdMode.protect_mode = cmd_table->URSA_OSD_PROTECT_MODE;
	UBOOT_INFO("g_UrsaCMDGenSetting.g_OsdMode.protect_mode=%d\n",g_UrsaCMDGenSetting.g_OsdMode.protect_mode);

    g_UrsaCMDGenSetting.g_SscFreqPercent.SscSel = cmd_table->URSA_SSC_SEL;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscEN = cmd_table->URSA_SSC_ENABLE;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscFreq = cmd_table->URSA_SSC_FREQ;
    g_UrsaCMDGenSetting.g_SscFreqPercent.SscPercent = cmd_table->URSA_SSC_PERCENT;

    return ret;
}
#endif

#endif

#endif

