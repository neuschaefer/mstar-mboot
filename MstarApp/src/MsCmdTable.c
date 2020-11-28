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

#include <common.h>
#include <command.h>
#include <MsCmdTable.h>
#include <MsDebug.h>
#include <exports.h>


static struct list_head cmd_list;


void Table_Init(void)
{
    UBOOT_TRACE("IN\n");

    INIT_LIST_HEAD(&cmd_list);

    UBOOT_TRACE("OK\n");    
}

void Add_Command_Table(char * cmd, int flag, int stage)
{

    ST_CMD_RECORED *pcmd=NULL;
    UBOOT_TRACE("IN\n");    
    pcmd=malloc(sizeof(ST_CMD_RECORED));
    if(pcmd==NULL)
    {
        UBOOT_ERROR("malloc for pcmd fail==========\n");
        return;
    }
    memset(pcmd,0,sizeof(ST_CMD_RECORED));
    INIT_LIST_HEAD(&pcmd->list);
    pcmd->cmd=malloc(strlen(cmd)+1);
    if(pcmd->cmd==NULL)
    {
        UBOOT_ERROR("malloc for cmd fail\n");
        free(pcmd);
        return;
    }
    memset(pcmd->cmd,0,strlen(cmd)+1);
    strcpy (pcmd->cmd, cmd);

    pcmd->flag = flag;
    pcmd->stage = stage;    
    list_add_tail(&pcmd->list,&cmd_list);
    
    UBOOT_TRACE("OK\n");    
    return;
}

ST_CMD_RECORED *getFirstCmd(void)
{

    ST_CMD_RECORED *pcmd=NULL;
    UBOOT_TRACE("IN\n");


    if(list_empty(&cmd_list)==1)
    {
        UBOOT_DEBUG("This is an empty list\n");
        return NULL;
    }

    pcmd=list_entry((cmd_list.next),ST_CMD_RECORED,list);
    UBOOT_TRACE("OK\n");    

    return pcmd; 
}

ST_CMD_RECORED *getNextCmd(ST_CMD_RECORED *pCmd)
{
    ST_CMD_RECORED *pcmd=NULL;
    UBOOT_TRACE("IN\n");
    if(pCmd==NULL)
    {
        UBOOT_ERROR("The input parameter 'pCmd' is a numm pointer\n");
        return NULL;
    }
    if(list_is_last(&pCmd->list,&cmd_list)==1)
    {
        UBOOT_DEBUG("This is the last cmd\n");
        return NULL;
    }

    pcmd=list_entry((pCmd->list.next),ST_CMD_RECORED,list);
    UBOOT_TRACE("OK\n");

    return pcmd;
}


int Show_Command_Table(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{    
    int index=0;
    int ShowStage=0;
    ST_CMD_RECORED *pCmd=NULL;

    UBOOT_TRACE("IN\n");
    if (argc < 2)
    {
       return cmd_usage(cmdtp);
    }
    ShowStage= (int)argv[1][0]-'0';
    
    UBOOT_INFO("No.  CmdName    Stage\n");

    pCmd=getFirstCmd();
    if(pCmd==NULL)
    {
        UBOOT_DEBUG("There are no any cmds in table\n");
        return 0;
    }
    
    while(1)
    {
        if((pCmd->stage == STAGE_MSINIT) && (ShowStage == 0 ||  ShowStage == 1))
        {
           UBOOT_INFO("%d  %s  STAGE_MSINIT\n",(index+1),pCmd->cmd);
        }
        if ((pCmd->stage == STAGE_PROCESS) && (ShowStage == 0 ||  ShowStage == 2))
        {
           UBOOT_INFO("%d  %s  STAGE_PROCESS\n",(index+1),pCmd->cmd);        
        }
        if ((pCmd->stage == STAGE_TOKERNEL) && (ShowStage == 0 ||  ShowStage == 3))
        {
           UBOOT_INFO("%d  %s  STAGE_TOKERNEL\n",(index+1),pCmd->cmd);        
        }
        pCmd=getNextCmd(pCmd);
        if(pCmd==NULL)
        {
            UBOOT_DEBUG("It's the last cmd\n");
            break;
        }
        index++;
    }
    return 0;
}

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
    showtb,    3,    1,     Show_Command_Table,
    "Show register command table."
    "    -  showtb [stage]\n",
    "0:ALL , 1:MsInit , 2:MsProcess , 3:MsToKernel\n"
);
#endif

