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
#include <MsTypes.h>
#include <version.h>
#include <MsEnvironment.h>

#define MB_VER_STR                                  "MB_mboot_ver"
#define DO_BOOTM_STR                             "MB_do_bootm"
#define INFO_EN_CHECKPOINTS_CFG          "en_chk_p"
#define CMD_BUF                                       128
#define MAX_SAVING_FILE_NUMBERS          16
extern char aPrePoints[CMD_BUF];
extern unsigned int start_ub_time;
extern int del_bootargs_cfg(char *);
extern int set_bootargs_cfg(char *,char *,MS_BOOL);

void do_points_handle(void)
{
    char* pInfo = getenv(INFO_EN_CHECKPOINTS_CFG);

    //printf("\n...[%s, %d] pInfo=%s, val=%d...\n", __FUNCTION__, __LINE__, pInfo, val);
    if (pInfo != NULL)
    {
        int val = 0;

        val = atoi(pInfo);

        //printf("\n...[%s, %d] pInfo=%s, val=%d...\n", __FUNCTION__, __LINE__, pInfo, val);
        if (val > 0 && val < MAX_SAVING_FILE_NUMBERS)
        {
            char _buf[10] = "";

            sprintf(_buf, "%s=%d", INFO_EN_CHECKPOINTS_CFG, val++);
            set_bootargs_cfg(INFO_EN_CHECKPOINTS_CFG, _buf, 0);

            sprintf(_buf, "%d", val);
            setenv(INFO_EN_CHECKPOINTS_CFG, _buf);
            saveenv();

            //printf("\n...[%s, %d] set %s to val=%d ok...\n", __FUNCTION__, __LINE__, INFO_EN_CHECKPOINTS_CFG, val);
        }
        else
        {
            int ret =0;

            setenv(INFO_EN_CHECKPOINTS_CFG, "");
            saveenv();

            ret = del_bootargs_cfg(INFO_EN_CHECKPOINTS_CFG);
            if(ret == 0)
            {
                if(val == MAX_SAVING_FILE_NUMBERS)
                {
                    printf("\n\n <<<<< customer performance index is done >>>>>\n");
                    printf(" <<<<< customer performance index is done >>>>>\n");
                    printf(" <<<<< customer performance index is done >>>>>\n\n");
                }
                //printf("\n...[%s, %d] del %s ok (after catch %d times)...\n", __FUNCTION__, __LINE__, INFO_EN_CHECKPOINTS_CFG, MAX_SAVING_FILE_NUMBERS-1);
            }
            else
            {
                printf("\n...[%s, %d] %s del failed...\n", __FUNCTION__, __LINE__, INFO_EN_CHECKPOINTS_CFG);
            }
        }
    }
}

void Points_Write(MS_U32 val)
{
    extern int snprintf(char *str, size_t size, const char *fmt, ...);
    char strEnv[CMD_BUF];

    // "start_ub" to bootargs
    if(0 != del_bootargs_cfg(aPrePoints))
    {
        printf("\n...[%s, %d] del failed for  %s ...\n", __FUNCTION__, __LINE__, aPrePoints);
    }

    memset(strEnv , 0, CMD_BUF);
    snprintf(strEnv , CMD_BUF-1, "%s=%lu", aPrePoints, start_ub_time);
    if(0 != set_bootargs_cfg((char*)aPrePoints, strEnv, 0))
    {
        printf("\n%s: Error: set_bootargs_cfg failed at %d\n", __func__, __LINE__);
    }

    // "do_bootm" to bootargs
    if(0 != del_bootargs_cfg(DO_BOOTM_STR))
    {
        printf("\n...[%s, %d] del failed for  %s ...\n", __FUNCTION__, __LINE__, DO_BOOTM_STR);
    }

    memset(strEnv , 0, CMD_BUF);
    snprintf(strEnv , CMD_BUF-1, "%s=%lu", DO_BOOTM_STR, val);

    if(0 != set_bootargs_cfg((char*)DO_BOOTM_STR, strEnv, 0))
    {
        printf("\n%s: Error: set_bootargs_cfg failed at %d\n", __func__, __LINE__);
    }

    // "mboot changelist version" to bootargs
    if(0 != del_bootargs_cfg(MB_VER_STR))
    {
        printf("\n...[%s, %d] del failed for  %s ...\n", __FUNCTION__, __LINE__, MB_VER_STR);
    }

    memset(strEnv , 0, CMD_BUF);
    snprintf(strEnv , CMD_BUF-1, "%s=%s", MB_VER_STR,  (char *)CHANGELIST_STRING);

    if(0 != set_bootargs_cfg((char*)MB_VER_STR, strEnv, 0))
    {
        printf("\n%s: Error: set_bootargs_cfg failed at %d\n", __func__, __LINE__);
    }

    // add the count value
    do_points_handle();

    return;
}







