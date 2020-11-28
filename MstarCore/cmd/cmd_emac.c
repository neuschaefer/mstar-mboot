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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   cmd_emac.c
/// @brief  u-boot EMAC Driver
/// @author MStar Semiconductor Inc.
///
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//  Include files
//-------------------------------------------------------------------------------------------------#include "e1000.h"

/*
 * EMAC Read/Write Utilities
 */
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <net.h>

//#include <mdrv_emac.h>
/*-----------------------------------------------------------------------
 * Definitions
 */
#define EMAC_INPUT_LEN                  2
#define EMAC_ADDR_INPUT_LEN                  7

#define MAX_EMAC_BYTES 0x1000	/* Maximum number of bytes we can handle */

extern int MDrv_EMAC_initialize(bd_t * bis);
void MDrv_EMAC_PowerMode(u8 mode);
extern void MDrv_EMAC_WaveTest(u8 mode);

extern u8 MY_MAC[6];
/*
 * emac init
 *
 * Syntax:
 *   estart
 */
#define MACADDR_ENV    "macaddr"
#define MACADDR_FORMAT "XX:XX:XX:XX:XX:XX"

int do_emac (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    bd_t * bis=NULL;
    char * macaddr;

    if (   NULL != (macaddr = getenv(MACADDR_ENV))
        && strlen(macaddr) == strlen(MACADDR_FORMAT)
        && ':' == macaddr[2]
        && ':' == macaddr[5]
        && ':' == macaddr[8]
        && ':' == macaddr[11]
        && ':' == macaddr[14]
        )
    {
        macaddr[2]  = '\0';
        macaddr[5]  = '\0';
        macaddr[8]  = '\0';
        macaddr[11] = '\0';
        macaddr[14] = '\0';

        MY_MAC[0]   = (u8)simple_strtoul(&(macaddr[0]),  NULL, 16);
        MY_MAC[1]   = (u8)simple_strtoul(&(macaddr[3]),  NULL, 16);
        MY_MAC[2]   = (u8)simple_strtoul(&(macaddr[6]),  NULL, 16);
        MY_MAC[3]   = (u8)simple_strtoul(&(macaddr[9]),  NULL, 16);
        MY_MAC[4]   = (u8)simple_strtoul(&(macaddr[12]), NULL, 16);
        MY_MAC[5]   = (u8)simple_strtoul(&(macaddr[15]), NULL, 16);

        /* set back to ':' or the environment variable would be destoried */ // REVIEW: this coding style is dangerous
        macaddr[2]  = ':';
        macaddr[5]  = ':';
        macaddr[8]  = ':';
        macaddr[11] = ':';
        macaddr[14] = ':';
    }

    MDrv_EMAC_initialize(bis);
	printf("(Re)start EMAC...\n");

	return 0;
}

int do_ewavetest (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u8 mode = simple_strtoul(argv[1], NULL, 16);

    printf("start EMAC ewavetest mode:%d...\n", mode);
    MDrv_EMAC_WaveTest(mode);
    printf("finish EMAC ewavetest mode:%d...\n", mode);
    
return 0;
}

int do_setMac(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char *cmdline_buf = NULL;
    if ((argc < EMAC_ADDR_INPUT_LEN) || (argc > EMAC_ADDR_INPUT_LEN))
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    MY_MAC[0]    = simple_strtoul(argv[1], NULL, 16);
    MY_MAC[1]    = simple_strtoul(argv[2], NULL, 16);
    MY_MAC[2]    = simple_strtoul(argv[3], NULL, 16);
    MY_MAC[3]    = simple_strtoul(argv[4], NULL, 16);
    MY_MAC[4]    = simple_strtoul(argv[5], NULL, 16);
    MY_MAC[5]    = simple_strtoul(argv[6], NULL, 16);

    cmdline_buf = malloc(64);
    if(cmdline_buf == NULL)
    {
        printf("%s: malloc() failed, at %d\n", __func__, __LINE__); //cyber
        return -1;
    }
    sprintf(cmdline_buf, "setenv "MACADDR_ENV" %02X:%02X:%02X:%02X:%02X:%02X", MY_MAC[0], MY_MAC[1], MY_MAC[2], MY_MAC[3], MY_MAC[4], MY_MAC[5]);

    run_command(cmdline_buf, 0);
    run_command("saveenv", 0);
    free(cmdline_buf);

    printf("New MAC Address is %02X:%02X:%02X:%02X:%02X:%02X\n", MY_MAC[0], MY_MAC[1], MY_MAC[2], MY_MAC[3], MY_MAC[4], MY_MAC[5]);

    // Set MAC address ------------------------------------------------------
    //MHal_EMAC_Write_SA1_MAC_Address(sa1[0],sa1[1],sa1[2],sa1[3],sa1[4],sa1[5]);

    return 0;
}

extern int emac_init;
extern void MDrv_EMAC_DumpReg(void);
int do_dumpMac(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (!emac_init)
    {
        printf("Please start emac first!\n");
        return 0;
    }
   	printf("Dump EMAC Register\n");
    MDrv_EMAC_DumpReg();
    return 0;
}

extern u8 MDrv_EMAC_Bist(u8 bEnable);
extern int NetLoop(proto_t protocol);
int do_bistMac(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    u8 count = simple_strtoul(argv[1], NULL, 16);

    if (!emac_init)
    {
        printf("Please start emac first!\n");
        return 0;
    }

    if (0 == count)
        printf("Usage:\n ebist count (count:0~255 times)\n Ex: ebist 10\n");
    else
    {
        u8 idx= 0;
        char buffer[256], ip_addr[][15] =
            {
                "10.0.0.253",
                "127.0.0.1",
                "172.16.90.254",
                "192.168.0.1",
                "224.30.0.253",
                "0"
            };

        if (MDrv_EMAC_Bist(1))
        {
            for (; idx < count; idx++)
            {
                memset(buffer, 0 , sizeof(buffer));
                sprintf(buffer, "ping %s", ip_addr[idx%5]);
                printf("\n=========>  %s for PHY Loopback test.....\n", buffer);
                run_command(buffer, 0);
            }
        }
        MDrv_EMAC_Bist(0);
    }
    return 0;
}

int do_Loopback(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (!emac_init)
    {
        printf("Please start emac first!\n");
        return 0;
    }

    MDrv_EMAC_Bist(2);
    return 0;
}

int do_loadspi (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    ulong ram_start;
    ulong spi_start;
    ulong len,i;
	if (argc != 4) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return 1;
	}

	spi_start = simple_strtoul(argv[1], NULL, 10);
	ram_start = simple_strtoul(argv[2], NULL, 10);
	len       = simple_strtoul(argv[3], NULL, 10);
    printf("copy from spi(%lux) to ram(%lux) with len=%lux\n",spi_start,ram_start,len);

    for(i=0;i<len;i+=4)
    {
        if(0==i%1024)printf(".");
        *((ulong*)(ram_start+i))=*((ulong*)(spi_start+i));
        //printf("[%x]=%x,[%x]=%x\n",ram_start+i,*((ulong*)(ram_start+i)),spi_start+i,*((ulong*)(spi_start+i)));
    }

	return 0;
}

int do_emacpowerdown (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    MDrv_EMAC_PowerMode(0);
    return 0;
}

/***************************************************/

U_BOOT_CMD(
	estart, EMAC_INPUT_LEN,	1,	do_emac,
	"EMAC start",
	"reset  - reset EMAC controller\n"
	"start  - start EMAC controller\n"
);

U_BOOT_CMD(
	macaddr, EMAC_ADDR_INPUT_LEN,	1,	do_setMac,
	"setup EMAC MAC addr",
    "XX XX XX XX XX XX"
);

U_BOOT_CMD(
	ewavetest, EMAC_INPUT_LEN, 1,	do_ewavetest,
	"EMAC wave test",
	"1  - 100M\n"
	"2  - 10M\n"
);

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
	ebist, EMAC_INPUT_LEN,	1,	do_bistMac,
	"PHY loopback test",
	"ebist - PHY loopback test\n"
);

U_BOOT_CMD(
	edump, EMAC_INPUT_LEN,	1,	do_dumpMac,
	"EMAC Register settings dump",
    "edump - EMAC Register settings dump\n"
);

U_BOOT_CMD(
	eloopback, EMAC_INPUT_LEN,	1,	do_Loopback,
	"Long loopback test",
    "eloopback - Long loopback test\n"
);

U_BOOT_CMD(
	loadspi, 4,	4,	do_loadspi,
	"load data from SPI",
    "XX XX XX XX XX XX"
);

U_BOOT_CMD(
	epd, 4,	4,	do_emacpowerdown,
	"emac power down",
    "XX XX XX XX XX XX"
);
#endif

