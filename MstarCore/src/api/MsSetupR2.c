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

#include <command.h>
#include <common.h>
#include <drvCPU.h>
#include <MsUtility.h>
#include <MsDebug.h>
#include <MsUboot.h>
#include <drvMBX.h>
#include <MsCommon.h>
#include <MsSystem.h>
#if (ENABLE_MSTAR_PUMABOOT)
#include <MsMmap.h>
#include <drvBDMA.h>
#include <MsEnvironment.h>

extern char mmapID[][MAX_MMAP_ID_LEN];
extern void *malloc(unsigned int);
extern void free(void*);

#endif

////////////////////////////////////////////////////////////////////////////////
// Global Function
////////////////////////////////////////////////////////////////////////////////


//#define DEBUG_MBX_R2
#ifdef DEBUG_MBX_R2
#define TEST_MBX_QUEUESIZE        8
#define TEST_MBX_TIMEOUT          5000

static MBX_Result gMBXResult;

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: Test_MailBox_Init
/// @brief \b Function  \b Description: Test case to register mailbox test class
/// @param <IN>         \b None :
/// @param <OUT>        \b None :
/// @param <RET>        \b MS_BOOL : TRUE: success; FALSE: failed
////////////////////////////////////////////////////////////////////////////////
MS_BOOL Test_MailBox_Init(void)
{
    //MDrv_MBX_SetDbgLevel(MBX_DBG_LEVEL_ALL);

    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_TEST, TEST_MBX_QUEUESIZE))
    {
        printf("E_MBX_CLASS_TEST - MBX register msg error\n");
        return FALSE;
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: Test_MailBoxHandler
/// @brief \b Function  \b Description: Test case for receiving mailbox message.
/// @param <IN>         \b MBX_Class : message class
/// @param <OUT>        \b None :
/// @param <RET>        \b int : 0: success; -1: failed
////////////////////////////////////////////////////////////////////////////////
static int Test_MailBoxHandler(MBX_Class eMsgClass)
{
    MBX_Msg MB_Command;

    if(eMsgClass != E_MBX_CLASS_TEST)
    {
        printf("Invalid Message Class!\n");
        return -1;
    }

    printf("Receive response from R2\n");
    gMBXResult = MDrv_MBX_RecvMsg(eMsgClass, &MB_Command, TEST_MBX_TIMEOUT/*ms*/, MBX_CHECK_INSTANT_MSG);

    if (gMBXResult == E_MBX_SUCCESS)
    {
        MS_U8 i;
        //printf("Get SECURE command: 0x%02x, 0x%02x\n", MB_Command.u8Index, MB_Command.u8ParameterCount);
        for(i=0; i<MB_Command.u8ParameterCount; i++)
        {
            printf("    Parameter[%d]=0x%02x\n", i, MB_Command.u8Parameters[i]);
        }
        return 0;
    } else {
        printf("    ==> Error: %d\n", gMBXResult);
        return -1;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: Test_MailBox_SendMsg
/// @brief \b Function  \b Description: Test case for sending mailbox message.
/// @param <IN>         \b u32Addr : memory address to storage data
/// @param <IN>         \b u32Len : data length
/// @param <OUT>        \b None :
/// @param <RET>        \b MS_BOOL : 0: success; 1: error
////////////////////////////////////////////////////////////////////////////////
MS_BOOL Test_MailBox_SendMsg(U32 u32Addr, U32 u32Len)
{
    MBX_Msg MB_Command;
    memset((void*)&MB_Command, 0, sizeof(MBX_Msg));

    //(1) send to R2
    MB_Command.eRoleID = E_MBX_ROLE_CP;
    MB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    MB_Command.u8Ctrl = 0;
    MB_Command.u8MsgClass = E_MBX_CLASS_TEST;
    MB_Command.u8Index = 0;
    MB_Command.u8ParameterCount = 8;
    MB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    MB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    MB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    MB_Command.u8Parameters[3] =  (U8)(u32Addr&0x000000FF);

    MB_Command.u8Parameters[4] =  (U8)(u32Len>>24);
    MB_Command.u8Parameters[5] =  (U8)(u32Len>>16);
    MB_Command.u8Parameters[6] =  (U8)(u32Len>>8);
    MB_Command.u8Parameters[7] =  (U8)(u32Len&0x000000FF);

    printf("Test_MailBox_SendMsg!\n");

    MDrv_MBX_SendMsg(&MB_Command);
    printf("Test_MailBox_SendMsg!finish\n");

    //(2) Waiting for SECURE BOOT message done
    do
    {
        if (0 == Test_MailBoxHandler(E_MBX_CLASS_TEST)) {
            break;
        }
    }
    while((gMBXResult  !=  E_MBX_SUCCESS) || (gMBXResult  !=  E_MBX_ERR_TIME_OUT));

    printf("gMBXResult:%d\n",gMBXResult);
    //(3) check result
    if(gMBXResult  !=  E_MBX_SUCCESS)
    {
        printf("Test_MailBox_SendMsg Fail, error %d\n", gMBXResult);
        return 1;
    }
    printf("Test_MailBox_SendMsg finish, Success %d\n", gMBXResult);

    return 0;
}

// Test message transmission between ARM and R2
MS_S8 test_r2_mbx(void)
{
    char *test_string = "hello world!";
    int test_string_len = (strlen(test_string) + 1) * sizeof(char);
    int testaddr = 0x75000000;
    memset((void *)testaddr, 0, 16);
    memcpy((char *)testaddr, test_string, 13);
//    flush_cache(testaddr, test_string_len);
    int loop=0;
    for(loop=0;loop<12;loop++)
        printf("%c ", ((char *)testaddr)[loop]);
    if(FALSE == Test_MailBox_Init()){
       return -1;
    }
    printf("==> ARM Mailbox Initialized\n");

    udelay(10000000);
    MDrv_WriteByte(0x101ea6, 0x0d);
//    Change2R2();
    MS_BOOL ret =Test_MailBox_SendMsg(MsOS_VA2PA(test_string), test_string_len);
//    MS_BOOL ret =Test_MailBox_SendMsg(MsOS_VA2PA(testaddr), test_string_len);
    printf("==> ARM Mailbox Finish:%d\n",ret);

    return 0;
}
#endif //DEBUG_MBX_R2

// Macro definition for loading cleanboot.bin. The max size of cleanboot.bin is 512KB (0x80000),offset 0x20000
// CPU SDR base address
//#define IFETCH_SDR_BASE           0x00000000
//#define DFETCH_SDR_BASE           0x00000000
#if (ENABLE_MSTAR_PUMABOOT)
// for R2 binary
#define R2_BOOT_BASE           CONFIG_PUMABOOT_ADDR
#define R2_IMAGE_SIZE           CONFIG_PUMABOOT_SIZE
// for BootVideo Image binary
#define BOOT_VIDEO_MAGIC_BUFFER_LEN 24
#define BOOT_VIDEO_RESERVED_BUFFER_LEN 188*300
#define BOOT_VIDEO_BASE_ADDR (R2_BOOT_BASE+R2_IMAGE_SIZE)
#define BOOT_VIDEO_BASE_LEN 0x1400000
#define BOOT_VIDEO_DATA_ADDR  (BOOT_VIDEO_BASE_ADDR + BOOT_VIDEO_MAGIC_BUFFER_LEN +BOOT_VIDEO_RESERVED_BUFFER_LEN)
#define BOOT_VIDEO_LOAD_SIZE 0x600000
#define BOOT_VIDEO_TOTAL_SIZE 0x2245DA8
#else
#define R2_BOOT_BASE           0x00000000
#endif
// Implement UBoot command: r2_init
// Bring up R2 from ARM.
int do_r2_run(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char LOAD_CLEANBOOT_BIN[100] = "\0";
    #if defined(CONFIG_MBOOT_IN_MMC_FLASH)
    unsigned int offset = 0;
    unsigned int size = 0;
    if(-1 == MsApiChunkHeader_GetValue(CH_CLEANBOOT_ROM_OFFSET,&offset))
    {
        return -1;
    }
    if(-1 == MsApiChunkHeader_GetValue(CH_CLEANBOOT_SIZE,&size))
    {
        return -1;
    }
    if(-1 == run_command("config_raw_io MMC MBOOT",0))
    {
        return -1;
    }
    snprintf(LOAD_CLEANBOOT_BIN,100,"raw_read 0x60000000 0x%x 0x%x",offset,size);
    #else
    snprintf(LOAD_CLEANBOOT_BIN,100,"spi rdc 0x60000000 0x14020000 0x80000");
    #endif
    if(-1 == run_command(LOAD_CLEANBOOT_BIN, 0))
    {
        return -1;
    }
    //UBOOT_DUMP(0x60000000,0x30);

    //1.  Get & Set Secure base address
    MDrv_COPRO_GetBase();

    //2. Enable R2 -> Start
    MDrv_COPRO_Enable(R2_BOOT_BASE);

    if(FALSE == MsApi_MBX_Init()) {
        printf("do_r2_run: setup R2 ok, mbx init fail!!!\n");
    }

#ifdef DEBUG_MBX_R2
    test_r2_mbx();
#endif

//    MDrv_WriteByte(0x101ea6, 0x0d);

    return 0;
}

#if (ENABLE_MSTAR_PUMABOOT)
//-------------------------------------------------------------------------------------------------
//  Definitions
//-------------------------------------------------------------------------------------------------
#define R2_PBMBX_QUEUESIZE      8
#define R2_PBMBX_TIMEOUT          5000

//-------------------------------------------------------------------------------------------------
//  External Functions
//-------------------------------------------------------------------------------------------------
extern int r2_pbpnlinit(void);

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
static MS_BOOL R2_PBMBX_IsReady(void)
{
    static MS_BOOL bR2Ready=FALSE;

    if(bR2Ready==TRUE) return TRUE;
    while(1)
    {
        if(MSys_Read2Byte(0x1033D0)==0x3697) 
        {
            bR2Ready = TRUE;
            return TRUE;
        }
    }
    printf("@@ R2_PBMBX_IsReady - NOT Ready !!\n");
    return FALSE;
}

static MS_BOOL R2_PBMBX_Init(void)
{
    MBX_CPU_ID eHKCPU;
    MS_U32 u32TimeoutMillSecs = 1500;

    //Initialize Mailbox
    eHKCPU = E_MBX_CPU_MIPS;
    if( E_MBX_SUCCESS != MDrv_MBX_Init(eHKCPU, E_MBX_ROLE_HK, u32TimeoutMillSecs))
    {
        printf("@@ R2_PBMBX_Init - MBX init failed !!\n");
        while(1);
    }
    else
    {
        MDrv_MBX_Enable(TRUE);
    }

    //Register class for R2
    if( E_MBX_SUCCESS != MDrv_MBX_RegisterMSG(E_MBX_CLASS_INPUT, R2_PBMBX_QUEUESIZE))
    {
        printf("@@ R2_PBMBX_Init - MBX register msg error\n");
        return FALSE;
    }

    return TRUE;
}

static MS_BOOL R2_PBMBX_SendMsgDatabase(U8 u8CmdIdx, U32 u32Addr ,U32 u32Size)
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;

    if(R2_PBMBX_IsReady()==FALSE) return FALSE; 

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_INPUT;
    stMB_Command.u8Index = u8CmdIdx;
    stMB_Command.u8ParameterCount = 8;
    stMB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    stMB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    stMB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    stMB_Command.u8Parameters[3] =  (U8)(u32Addr&0xFF);
    stMB_Command.u8Parameters[4] =  (U8)(u32Size>>24);
    stMB_Command.u8Parameters[5] =  (U8)(u32Size>>16);
    stMB_Command.u8Parameters[6] =  (U8)(u32Size>>8);
    stMB_Command.u8Parameters[7] =  (U8)(u32Size&0xFF);
    MDrv_MBX_SendMsg(&stMB_Command);

    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_INPUT, &stMB_Command, R2_PBMBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("R2_PBMBX_SendMsgDatabase : Fail\n");
    }
    return enMbxResult;
}

static MS_BOOL R2_PBMBX_SendMsgInput(U8 u8CmdIdx, U8 u8InputIdx ,U8 u8OutIdx)
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;

    if(R2_PBMBX_IsReady()==FALSE) return FALSE; 

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_INPUT;
    stMB_Command.u8Index = u8CmdIdx;
    stMB_Command.u8ParameterCount = 2;
    stMB_Command.u8Parameters[0] =  u8InputIdx;
    stMB_Command.u8Parameters[1] =  u8OutIdx;
    MDrv_MBX_SendMsg(&stMB_Command);

    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_INPUT, &stMB_Command, R2_PBMBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("R2_PBMBX_SendMsgInput : Fail\n");
    }
    return enMbxResult;
}

MS_BOOL MApi_PBMBX_SendMsgPanel(U32 u32Addr, U16 u16Level, U16 u16Type)
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;

    if(R2_PBMBX_IsReady()==FALSE) return FALSE; 

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_INPUT;
    stMB_Command.u8Index = E_MBX_PB_CMD_PANEL;
    stMB_Command.u8ParameterCount = 9;
    stMB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    stMB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    stMB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    stMB_Command.u8Parameters[3] =  (U8)(u32Addr&0xFF);
    stMB_Command.u8Parameters[4] =  (U8)(u16Level>>8);
    stMB_Command.u8Parameters[5] =  (U8)(u16Level&0xFF);
    stMB_Command.u8Parameters[6] =  (U8)(u16Type>>8);
    stMB_Command.u8Parameters[7] =  (U8)(u16Type&0xFF);
    stMB_Command.u8Parameters[8] =  0;//panel init order
    MDrv_MBX_SendMsg(&stMB_Command);

    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_INPUT, &stMB_Command, R2_PBMBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("MApi_PBMBX_SendMsgPanel Fail\n");
    }
    return enMbxResult;
}

static MS_BOOL R2_PBMBX_SendMsgBootVideo(U32 u32Addr ,U32 u32Size)
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;
    U8 *pu8VirAdrr = (U8 *)PA2NVA(u32Addr);
    if(R2_PBMBX_IsReady()==FALSE) return FALSE;

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    /*
    pu8VirAdrr[0] = 0;
    pu8VirAdrr[1] = BOOT_VIDEO_BASE_LEN;
    pu8VirAdrr[2] = BOOT_VIDEO_LOAD_SIZE;
    pu8VirAdrr[3] = BOOT_VIDEO_TOTAL_SIZE;
    */
    pu8VirAdrr[0] = 0;
    pu8VirAdrr[1] = 0;
    pu8VirAdrr[2] = 0;
    pu8VirAdrr[3] = 0;

    pu8VirAdrr[4] = (U8)(BOOT_VIDEO_BASE_LEN >>24);
    pu8VirAdrr[5] = (U8)(BOOT_VIDEO_BASE_LEN >>16);
    pu8VirAdrr[6] = (U8)(BOOT_VIDEO_BASE_LEN >>8);
    pu8VirAdrr[7] = (U8)(BOOT_VIDEO_BASE_LEN &0xFF);
    
    pu8VirAdrr[8] = (U8)(BOOT_VIDEO_LOAD_SIZE >>24);
    pu8VirAdrr[9] = (U8)(BOOT_VIDEO_LOAD_SIZE >>16);
    pu8VirAdrr[10] = (U8)(BOOT_VIDEO_LOAD_SIZE >>8);
    pu8VirAdrr[11] = (U8)(BOOT_VIDEO_LOAD_SIZE &0xFF);
    
    pu8VirAdrr[12] = (U8)(BOOT_VIDEO_TOTAL_SIZE >>24);
    pu8VirAdrr[13] = (U8)(BOOT_VIDEO_TOTAL_SIZE >>16);
    pu8VirAdrr[14] = (U8)(BOOT_VIDEO_TOTAL_SIZE >>8);
    pu8VirAdrr[15] = (U8)(BOOT_VIDEO_TOTAL_SIZE &0xFF);
    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_INPUT;
    stMB_Command.u8Index = E_MBX_PB_CMD_BVIDEO;
    stMB_Command.u8ParameterCount = 8;
    stMB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    stMB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    stMB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    stMB_Command.u8Parameters[3] =  (U8)(u32Addr&0xFF);
    stMB_Command.u8Parameters[4] =  (U8)(u32Size>>24);
    stMB_Command.u8Parameters[5] =  (U8)(u32Size>>16);
    stMB_Command.u8Parameters[6] =  (U8)(u32Size>>8);
    stMB_Command.u8Parameters[7] =  (U8)(u32Size&0xFF);
    MDrv_MBX_SendMsg(&stMB_Command);

    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_INPUT, &stMB_Command, R2_PBMBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("R2_PBMBX_SendMsgBootVideo : Fail\n");
    }
    return enMbxResult;
}
#if 0
int do_load_video_file(void)
{
    char cmd[CMD_BUF] = "\0";
    char *env =NULL;
    int partition = 0;
    int device = 0;
    int ret = -1;
    unsigned  int u32FileSize = 0;

    if (-1 == appInitUsbDisk())
    {
        printf("FAIL : can not init usb!! \n");
        return ret;
    }

    ret = check_file_partition(VIDEO_FILE_PATH, &device, &partition);
     if(0 == ret)
     {
        printf("Find video file in USB disk\n");
        printf("Geting file size\n");
        snprintf(cmd, CMD_BUF, "fatfilesize usb %d:%d %s", device, partition, VIDEO_FILE_PATH);
        printf("cmd=%s\n",cmd);
        ret = run_command(cmd, 0);
        if(-1 == ret)
        {
            printf("Get video file's size failed\n");
            return ret;
        }
        else
        {
            env=getenv("filesize");
            if(NULL == env)
            {
                printf("Get env 'filesize' failed\n");
            }
            u32FileSize = simple_strtol(env, NULL, 16);
            printf("Size=0x%x \n",u32FileSize);
        }

        snprintf(cmd, CMD_BUF, "fatload usb %d:%d  %X %s %X", device, partition, VIDEO_BUFFER_ADDR, VIDEO_FILE_PATH, u32FileSize);
        UBOOT_INFO("cmd=%s\n",cmd);
        ret = run_command(cmd, 0);
        if(-1 == ret)
        {
            printf("Load video file failed!\n");
            return ret;
        }
        else
        {
            printf("Send Message to CP!\n");
            R2_PBMBX_SendMsgBootVideo(MsOS_VA2PA((MS_U32)(VIDEO_BUFFER_ADDR)), u32FileSize);
            printf("Load video file OK!~\n");
        }
    }
    else
    {
        printf("Not found %s in USB disk\n", VIDEO_FILE_PATH);
    }

    return ret;
}

#endif

////////////////////////////////////////////////////////////////////////////////
// Global Function
////////////////////////////////////////////////////////////////////////////////
int do_r2_pbrun(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    printf("\n================================================================do_r2_pbrun\n");

    #if ENABLE_BOOTING_FROM_EXT_SPI_WITH_CPU
    //MDrv_BDMA_SetDbgLevel(E_BDMA_DBGLV_ALL);
    //MDrv_BDMA_Init(0x20000000);
    //MDrv_MMIO_Init();
    //MDrv_BDMA_Init(MIU_INTERVAL);
    MDrv_BDMA_FlashCopy2Dram((MS_PHYADDR)0x20000, (MS_PHYADDR)R2_BOOT_BASE,(MS_U32)R2_IMAGE_SIZE);
    #endif

   #if (ENABLE_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    char ts[128];
	
    memset(ts, 0, sizeof(ts));
    snprintf(ts, sizeof(ts)-1, "mmc read.p 0x%08lX bootvideo 0x600000", (U32)(PA2NVA(BOOT_VIDEO_DATA_ADDR)));    
	
    if(-1 != run_command(ts, 0))
    {
        printf("\n[%s: %d] read the TS partion data:\n",__func__,__LINE__);
    }
    else
    {
        UBOOT_ERROR("%s: '%s' fails, at %d\n", __func__, ts, __LINE__);
        return -1;
    }    
    
    char cmd[128];
    
    memset(cmd, 0, sizeof(cmd));
    
    //snprintf(cmd, sizeof(cmd)-1, "mmc read.p 0x%08lX PUMABOOT 0x400000", (U32)(PA2NVA(R2_BOOT_BASE)));    
    snprintf(cmd, sizeof(cmd)-1, "mmc read.p 0x%08lX PUMABOOT 0x600000", (U32)(PA2NVA(R2_BOOT_BASE)));    
    
    if(-1 != run_command(cmd, 0))
    {
        printf("\n[%s: %d] read the PUMABOOT partion data@%x:\n",__func__,__LINE__,R2_BOOT_BASE);
    }
    else
    {
        UBOOT_ERROR("%s: '%s' fails, at %d\n", __func__, cmd, __LINE__);
        return -1;
    }    
    #endif

    //Initialize mailbox for Co-processor(R2)
    R2_PBMBX_Init();
    //Disable Co-processor(R2)
    MDrv_COPRO_Init_Front();
    //Enable Co-processor(R2)
    MDrv_COPRO_Init_End(R2_BOOT_BASE);

    return 0;
}

static PBChanDB gChanBatabase[5]=
{
        {45, 1, 101, 102, 101},
        {45, 2, 201, 202, 201},
        {45, 3, 301, 302, 301},
        {45, 4, 401, 402, 401},
        {45, 5, 501, 502, 501},
};

int do_r2_pbdbchan(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    U32 u32PAChanDBAddr;
    flush_cache((MS_U32)gChanBatabase,sizeof(gChanBatabase));
    u32PAChanDBAddr = VA2PA((MS_U32)gChanBatabase);
    
    
    printf("do_r2_pbdbchan : start\n");
    R2_PBMBX_SendMsgDatabase((U8)E_MBX_PB_CMD_DBCHAN,u32PAChanDBAddr,sizeof(gChanBatabase));
    printf("do_r2_pbdbchan : end\n");
    return 0;
}

static U8 gUserDatabase[512] =
{
    0xEF,0x7B,0x02,0x60,0x04,0x7D,0x00,0x80,0x02,0x7D,0x01,0x7E,0x24,0x7F,0x06,0x12,
    0x91,0x60,0x22,0x0D,0x0A,0x45,0x6E,0x74,0x65,0x72,0x20,0x6D,0x61,0x69,0x6E,0x20,
    0x6C,0x6F,0x6F,0x70,0x00,0xE4,0xFF,0x90,0x43,0x55,0xE0,0x54,0x03,0x60,0x01,0xE4,
    0xEF,0x60,0x03,0x12,0x49,0xAE,0x22,0xED,0xF4,0x5F,0xFE,0xEF,0x4D,0x54,0x07,0xFB,
    0xAD,0x06,0x7E,0x21,0x7F,0x02,0x02,0x95,0x8E,0xED,0xF4,0x5F,0xFE,0xEF,0x4D,0x54,
    0x03,0xFB,0xAD,0x06,0x7E,0x21,0x7F,0x03,0x02,0x95,0x8E,0xED,0xF4,0x5F,0xFE,0xED,
    0x4F,0x54,0x07,0xFB,0xAD,0x06,0x7E,0x20,0x7F,0x52,0x02,0x95,0x8E,0xED,0xF4,0x5F,
    0xFE,0xEF,0x4D,0x54,0x82,0xFB,0xAD,0x06,0x7E,0x23,0x7F,0x00,0x02,0x95,0x8E,0xED,
    0xF4,0x5F,0xFE,0xEF,0x4D,0x54,0xD0,0xFB,0xAD,0x06,0x7E,0x23,0x7F,0x28,0x02,0x95,
    0x8E,0xED,0xF4,0x5F,0xFE,0xEF,0x4D,0x54,0x2C,0xFB,0xAD,0x06,0x7E,0x22,0x7F,0x14,
    0x02,0x95,0x8E,0xED,0xF4,0x5F,0xFE,0xEF,0x4D,0x54,0xE0,0xFB,0xAD,0x06,0x7E,0x30,
    0x7F,0xBF,0x02,0x95,0x8E,0xEF,0xF4,0x5D,0xFE,0xEF,0x4D,0x54,0x1F,0xFB,0xAD,0x06,
    0x7E,0x1E,0x7F,0x27,0x02,0x95,0x8E,0x12,0xAE,0xE3,0x8F,0x34,0x12,0x96,0xCA,0x7F,
    0x3C,0x12,0x84,0x3F,0xAF,0x34,0x02,0x9C,0x87,0x12,0xAE,0xE3,0x8F,0x34,0x12,0x96,
    0xB6,0x7F,0x26,0x12,0x84,0x3F,0xAF,0x34,0x02,0x9C,0x87,0x12,0xAE,0xE3,0x8F,0x34,
    0xAE,0xE3,0x8F,0x34,0x12,0x96,0xB6,0x7F,0x2A,0x12,0x84,0x3F,0xAF,0x34,0x02,0x9C,
    0x02,0x77,0x84,0x02,0x8A,0xC6,0xE4,0xFF,0x02,0xA3,0x0D,0x02,0x9A,0x89,0xE4,0xFF,
    0x02,0xAE,0x34,0x02,0x8F,0xB2,0x12,0x80,0x14,0x7A,0x03,0x12,0x7C,0xE4,0x7F,0x38,
    0x02,0x84,0x3F,0x02,0x73,0x7D,0x02,0xAF,0xEB,0x32,0x22,0x02,0x00,0x29,0x90,0x41,
    0x30,0xE0,0xFC,0xA3,0xE0,0xFD,0x90,0x41,0x26,0xE0,0xFB,0x7F,0x06,0xED,0xAE,0x04,
    0xA8,0x07,0x08,0x80,0x05,0xCE,0xC3,0x13,0xCE,0x13,0xD8,0xF9,0x90,0x41,0xC4,0xF0,
    0xED,0xAE,0x04,0x78,0x06,0xCE,0xC3,0x13,0xCE,0x13,0xD8,0xF9,0x90,0x41,0xC5,0xF0,
    0xEB,0x7F,0x05,0x12,0x0F,0x64,0x80,0x05,0xCE,0xC3,0x13,0xCE,0x13,0xD8,0xF9,0x90,
    0x41,0xC6,0xF0,0x90,0x41,0x26,0xE0,0xFD,0x7F,0x04,0xA8,0x07,0x12,0x0E,0x1D,0x80,
    0x05,0xCE,0xC3,0x13,0xCE,0x13,0xD8,0xF9,0x90,0x41,0xC7,0xF0,0x90,0x41,0x4C,0xE0,
    0xED,0xAE,0x04,0x78,0x06,0xCE,0xC3,0x13,0xCE,0x13,0xD8,0xF9,0x90,0x41,0xC5,0xF0,
    0xFE,0xEF,0x4D,0x54,0x82,0xFB,0xAD,0x06,0x7E,0x23,0x7F,0x00,0x02,0x95,0x8E,0xED,
    0x41,0xC6,0xF0,0x90,0x41,0x26,0xE0,0xFD,0x7F,0x04,0xA8,0x07,0x12,0x0E,0x1D,0x80,
    0x7E,0x1E,0x7F,0x27,0x02,0x95,0x8E,0x12,0xAE,0xE3,0x8F,0x34,0x12,0x96,0xCA,0x7F,
    0x4A,0x60,0x10,0xED,0x1D,0xAA,0x04,0x70,0x01,0x1C,0x4A,0x70,0xF6,0x7C,0x03,0x7D,
    0xE8,0x80,0xE6,0x22,0xED,0xF4,0xFB,0xEC,0xF4,0x5E,0xFA,0xEB,0x5F,0xF5,0x82,0x8A,
    0x7F,0xE8,0x02,0x2D,0x6C,0xC2,0x0A,0x12,0x33,0x43,0x12,0x3B,0x60,0xC2,0x0A,0x12,
};

int do_r2_pbdbuser(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    U32 u32PAUserDBAddr;
    flush_cache((MS_U32)gUserDatabase,sizeof(gUserDatabase));
    u32PAUserDBAddr = VA2PA((MS_U32)gUserDatabase);
    printf("do_r2_pbdbuser : start\n");
    R2_PBMBX_SendMsgDatabase((U8)E_MBX_PB_CMD_DBUSER,u32PAUserDBAddr,sizeof(gUserDatabase));
    printf("do_r2_pbdbuser : end\n");
    return 0;
}

int do_r2_pbpnlinit(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret = 0;
    
    printf("do_r2_pbpnlinit : start\n");
    ret = r2_pbpnlinit();
    printf("do_r2_pbpnlinit : end\n");
    return ret;
}

int do_r2_pbinput(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //Set input source as DMX/VDEC
    printf("do_r2_pbinput : start\n");
    R2_PBMBX_SendMsgBootVideo(BOOT_VIDEO_BASE_ADDR, BOOT_VIDEO_BASE_LEN);
    printf("do_r2_pbinput : end\n");
    return 0;
}

#if 1//speed up boot time
char pbMmapID[][MAX_MMAP_ID_LEN]={
        "E_MMAP_ID_MAD_R2",
        "E_MMAP_ID_MAD_SE",
        "E_MMAP_ID_MAD_DEC",
        "E_MMAP_ID_VDEC_CPU", // VDEC_AEON
        "E_MMAP_ID_VDEC_FRAMEBUFFER", // VDEC_FRAMEBUFFER
        "E_MMAP_ID_VDEC_BITSTREAM", // VDEC_BITSTREAM
        "E_MMAP_ID_XC_MAIN_FB", // SCALER_DNR
        "E_MMAP_ID_XC_MLOAD", // MENULOAD_BUFFER
        ""
};
typedef enum
{
    E_MMAP_ID_MAD_R2=0,
    E_MMAP_ID_MAD_SE,
    E_MMAP_ID_MAD_DEC,
    E_MMAP_ID_VDEC_CPU, 
    E_MMAP_ID_VDEC_FRAMEBUFFER,
    E_MMAP_ID_VDEC_BITSTREAM,
    E_MMAP_ID_XC_MAIN_FB,
    E_MMAP_ID_XC_MLOAD,
    E_MMAP_ID_END,
} E_MMAP_ID;

static MS_BOOL dump_to_pumaboot_mmap_info(MMAP_PUMABOOT_ADDRESS_LAYOUT *pMailBox_MMAP_Layout)
{
    U32 i=0;
    U32 u32Addr=0, u32Len=0;
    char *pChar;

    // fill pMailBox_MMAP_Info
    while(1)
    {
        pChar=pbMmapID[i++];
        // calculate the element neumber in mmapID
        // there is no other way to make sure the number of element in mmapID (no lease element reserved in enum)
        // mmapID ended with a ""
        if(strcmp(pChar,"")==0)
        {
            UBOOT_TRACE("OK\n");
            break;
        }
        // get address offset and legnth
        if(get_addr_from_mmap(pChar, &u32Addr)!=0)
        {
            UBOOT_ERROR("get %s fail\n",pChar);
            u32Addr = 0;
        }
        if(u32Addr==0xFFFF)
        {
            UBOOT_ERROR("Get %s Failed Skip! \n",pChar);
            return FALSE;
        }
        if(get_length_from_mmap(pChar, &u32Len)!=0)
        {
            UBOOT_ERROR("get length %s fail\n",pChar);
            u32Len = 0;
        }

        if(strcmp(pChar,"E_MMAP_ID_MAD_R2")==0)
        {
            pMailBox_MMAP_Layout->MAD_R2_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MAD_R2_BUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_MAD_SE")==0)
        {
            pMailBox_MMAP_Layout->MAD_SE_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MAD_SE_BUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_MAD_DEC")==0)
        {
            pMailBox_MMAP_Layout->MAD_DEC_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MAD_DEC_BUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_VDEC_CPU")==0)
        {
            pMailBox_MMAP_Layout->VDEC_AEON.u32Address = u32Addr;
            pMailBox_MMAP_Layout->VDEC_AEON.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_VDEC_FRAMEBUFFER")==0)
        {
            pMailBox_MMAP_Layout->VDEC_FRAMEBUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->VDEC_FRAMEBUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_VDEC_BITSTREAM")==0)
        {
            pMailBox_MMAP_Layout->VDEC_BITSTREAM.u32Address = u32Addr;
            pMailBox_MMAP_Layout->VDEC_BITSTREAM.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_XC_MAIN_FB")==0)
        {
            pMailBox_MMAP_Layout->SCALER_DNR.u32Address = u32Addr;
            pMailBox_MMAP_Layout->SCALER_DNR.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_XC_MLOAD")==0)
        {
            pMailBox_MMAP_Layout->MENULOAD_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MENULOAD_BUFFER.u32Length = u32Len;
        }
        else
        {
            // something Pumaboot do not care...
            // do nothing
        }
    } // while(1)
    return TRUE;
}
#else
static MS_BOOL dump_to_pumaboot_mmap_info(MMAP_PUMABOOT_ADDRESS_LAYOUT *pMailBox_MMAP_Layout)
{
    U32 i=0;
    U32 u32Addr=0, u32Len=0;
    char *pChar;

    // fill pMailBox_MMAP_Info
    while(1)
    {
        pChar=mmapID[i++];
        // calculate the element neumber in mmapID
        // there is no other way to make sure the number of element in mmapID (no lease element reserved in enum)
        // mmapID ended with a ""
        if(strcmp(pChar,"")==0)
        {
            UBOOT_TRACE("OK\n");
            break;
        }
        // get address offset and legnth
        if(get_addr_from_mmap(pChar, &u32Addr)!=0)
        {
            UBOOT_ERROR("get %s fail\n",pChar);
            u32Addr = 0;
        }
        if(u32Addr==0xFFFF)
        {
            UBOOT_ERROR("Get %s Failed Skip! \n",pChar);
            return FALSE;
        }
        if(get_length_from_mmap(pChar, &u32Len)!=0)
        {
            UBOOT_ERROR("get length %s fail\n",pChar);
            u32Len = 0;
        }

        if(strcmp(pChar,"E_MMAP_ID_MAD_R2")==0)
        {
            pMailBox_MMAP_Layout->MAD_R2_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MAD_R2_BUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_MAD_SE")==0)
        {
            pMailBox_MMAP_Layout->MAD_SE_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MAD_SE_BUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_MAD_DEC")==0)
        {
            pMailBox_MMAP_Layout->MAD_DEC_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MAD_DEC_BUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_VDEC_CPU")==0)
        {
            pMailBox_MMAP_Layout->VDEC_AEON.u32Address = u32Addr;
            pMailBox_MMAP_Layout->VDEC_AEON.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_VDEC_FRAMEBUFFER")==0)
        {
            pMailBox_MMAP_Layout->VDEC_FRAMEBUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->VDEC_FRAMEBUFFER.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_VDEC_BITSTREAM")==0)
        {
            pMailBox_MMAP_Layout->VDEC_BITSTREAM.u32Address = u32Addr;
            pMailBox_MMAP_Layout->VDEC_BITSTREAM.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_XC_MAIN_FB")==0)
        {
            pMailBox_MMAP_Layout->SCALER_DNR.u32Address = u32Addr;
            pMailBox_MMAP_Layout->SCALER_DNR.u32Length = u32Len;
        }
        else if(strcmp(pChar,"E_MMAP_ID_XC_MLOAD")==0)
        {
            pMailBox_MMAP_Layout->MENULOAD_BUFFER.u32Address = u32Addr;
            pMailBox_MMAP_Layout->MENULOAD_BUFFER.u32Length = u32Len;
        }
        else
        {
            // something Pumaboot do not care...
            // do nothing
        }
    } // while(1)
    return TRUE;
}
#endif

// return 32 bit Pumaboot global mmap address (read only), mmap data are first written by do_r2_pbmmap
const MMAP_PUMABOOT_ADDRESS_LAYOUT* const get_Pumaboot_mmap(void)
{
    // global field
    static MMAP_PUMABOOT_ADDRESS_LAYOUT gPumaboot_mmap_Info;
    return &gPumaboot_mmap_Info;
}

int do_r2_pbmmap(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;
    U32 u32Addr=0;
    const MMAP_PUMABOOT_ADDRESS_LAYOUT* pPumaboot_mmap_Info = NULL;

    pPumaboot_mmap_Info = get_Pumaboot_mmap();
    memset((void *)pPumaboot_mmap_Info,0,sizeof(MMAP_PUMABOOT_ADDRESS_LAYOUT));
    // put mmap data to Pumaboot MMAP
    if(dump_to_pumaboot_mmap_info((MMAP_PUMABOOT_ADDRESS_LAYOUT*) pPumaboot_mmap_Info) == FALSE)
    {
        return -1;
    }
    if(R2_PBMBX_IsReady()==FALSE) 
    {   
        return FALSE; 
    }

    // send physical address of pMailBox_MMAP_Info to R2
    flush_cache((MS_U32)pPumaboot_mmap_Info,sizeof(MMAP_PUMABOOT_ADDRESS_LAYOUT));
    u32Addr = VA2PA((MS_U32)(pPumaboot_mmap_Info));
    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_INPUT;
    stMB_Command.u8Index = E_MBX_PB_CMD_MMAP;
    stMB_Command.u8ParameterCount = 8;
    stMB_Command.u8Parameters[0] =  (U8)(u32Addr>>24);
    stMB_Command.u8Parameters[1] =  (U8)(u32Addr>>16);
    stMB_Command.u8Parameters[2] =  (U8)(u32Addr>>8);
    stMB_Command.u8Parameters[3] =  (U8)(u32Addr&0xFF);
    stMB_Command.u8Parameters[4] =  0x0;
    stMB_Command.u8Parameters[5] =  0x0;
    stMB_Command.u8Parameters[6] =  0x0;
    stMB_Command.u8Parameters[7] =  0x0;
    stMB_Command.u8Parameters[8] =  0;
    MDrv_MBX_SendMsg(&stMB_Command);
    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_INPUT, &stMB_Command, R2_PBMBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("MApi_PBMBX_SendMsgPanel Fail\n");
    }
    printf("do_r2_pbmmap : end\n");
    // do not reserve that memory for co-processor, co-process should store those information
    return 0;
}

int do_r2_pbtuneatv(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]) //may be removed later
{
    U8 u8ChannelNum;

    printf("\ndo_r2_pbatv : ===================================\n");

    if(argc<1)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    u8ChannelNum=(U8)atoi(argv[1]);  

    printf("do_r2_pbtuneatv : set channel number : %d\n",u8ChannelNum);

    {
    MBX_Msg stMB_Command;
    MBX_Result enMbxResult = 0;

    if(R2_PBMBX_IsReady()==FALSE) return FALSE; 

    memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
    //(1) send to CB
    stMB_Command.eRoleID = E_MBX_ROLE_CP;
    stMB_Command.eMsgType = E_MBX_MSG_TYPE_INSTANT;
    stMB_Command.u8Ctrl = 0;
    stMB_Command.u8MsgClass = E_MBX_CLASS_INPUT;
    stMB_Command.u8Index = E_MBX_PB_CMD_TUNEATV;
    stMB_Command.u8ParameterCount = 1;
    stMB_Command.u8Parameters[0] =  u8ChannelNum;
    MDrv_MBX_SendMsg(&stMB_Command);
    
    //(2) Waiting for message done
    do
    {
        memset((void*)&stMB_Command, 0x00, sizeof(MBX_Msg));
        enMbxResult = MDrv_MBX_RecvMsg(E_MBX_CLASS_INPUT, &stMB_Command, R2_PBMBX_TIMEOUT, MBX_CHECK_INSTANT_MSG);
    }while((enMbxResult  !=  E_MBX_SUCCESS) && (enMbxResult  !=  E_MBX_ERR_TIME_OUT));

    //(3) check result
    if(enMbxResult == E_MBX_ERR_TIME_OUT)
    {
        printf("R2_PBMBX_SendMsg : atv index : fail\n");
    }
    }
    printf("do_r2_pbtuneatv : set index end\n");

    return 0;    
}

#endif

