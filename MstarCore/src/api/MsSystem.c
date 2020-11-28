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
#include <drvWDT.h>
#include <MsMath.h>
#include <MsSystem.h>
#include <MsUtility.h>
#include <MsDebug.h>
#include <exports.h>
#include <drvGPIO.h>
#include <MsOS.h>
#include <MsRawIO.h>
#include <ShareType.h>
#include <drvUART.h>
#include <MsUboot.h>
#include <drvMBX.h>
#include <msAPI_Power.h>
#include <drvSYS.h>
#include <miu/MsDrvMiu.h>

extern int snprintf(char *str, size_t size, const char *fmt, ...);
extern unsigned int GetRealOffset(unsigned int);

#define BRICK_TMP_PATCH 0

int do_wdt_enable (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int u32Timer = 0;

    if (argc < 2) {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }

    u32Timer = simple_strtoul(argv[1], NULL, 10);

    MDrv_WDT_Init(E_WDT_DBGLV_ALL);
    MDrv_WDT_SetTimer(E_WDT_DBGLV_ALL, u32Timer);

    return 0;
}

extern U8 MDrv_MIU_SelectMIU_UBoot(U8 bMIU1, U16 *au16SelMiu, U8 u8GpNum);
extern U8 MDrv_MIU_SetGroupPriority_UBoot(U8 bMIU1, U8 *au8GpPriority, U8 u8GpNum);

static void set_miu_group_priority(U8 u8MiuIdx, const char* cStr)
{
    if (cStr)
    {
        int i = 0;
        int j = 0;
        int length = 0;
        U8 au8GpPriority[MIU_MAX_GP_NUM] = {0};

        for (;;)
        {
            if (cStr[i] != ':')
            {
                au8GpPriority[j++] = cStr[i] - 0x30;
            }
            else
            {
                ++length; // length is ':' number and priority number need add one more.
            }

            if ('\0' == cStr[i])
            {
                ++length;
                break;
            }

            ++i;
        }
        MDrv_MIU_SetGroupPriority_UBoot(u8MiuIdx, au8GpPriority, length);
    }
}

static void select_miu(U8 u8MiuIdx, const char* cStr)
{
    if (cStr)
    {
        int i = 0;
        int j = 0;
        int length = 0;

        for (;;)
        {
            if (':' == cStr[i])
            {
                ++length;
            }

            if ('\0' == cStr[i])
            {
                ++length; // length is ':' number and priority number need add one more.
                break;
            }

            ++i;
        }

        i = 0;
        j = 0;
        U16 au16SelMiu[MIU_MAX_GP_NUM] = {0};

        for (;;)
        {
            au16SelMiu[j++] = ascii_to_hex(&cStr[i], 4);
            i += 5;

            if (length == j)
            {
                break;
            }
        }

        MDrv_MIU_SelectMIU_UBoot (u8MiuIdx, au16SelMiu, length);
    }
}

static void set_miu(void)
{
#if(CONFIG_VESTEL_MB100 == 1)
    char *sMIUSettings = NULL;

    //PRIORITY
    sMIUSettings = getenv("MIU0_GROUP_PRIORITY");
    if(NULL == sMIUSettings)
    {
        //use default miu settings 
        UBOOT_DEBUG("Setting DEFAULT_MIU0_GROUP_PRIORITY=%s\n", DEFAULT_MIU0_GROUP_PRIORITY);
        set_miu_group_priority(0, DEFAULT_MIU0_GROUP_PRIORITY);
    }
    else
    {
        UBOOT_DEBUG("Setting MIU0_GROUP_PRIORITY=%s\n", sMIUSettings);        
        set_miu_group_priority(0, sMIUSettings);
    }
    sMIUSettings = getenv("MIU1_GROUP_PRIORITY");
    if(NULL == sMIUSettings)
    {
        //use default miu settings 
        UBOOT_DEBUG("Setting DEFAULT_MIU1_GROUP_PRIORITY=%s\n", DEFAULT_MIU1_GROUP_PRIORITY);
        set_miu_group_priority(1, DEFAULT_MIU1_GROUP_PRIORITY);
    }
    else
    {
        UBOOT_DEBUG("Setting MIU1_GROUP_PRIORITY=%s\n", sMIUSettings);
        set_miu_group_priority(1, sMIUSettings);
    }
#if 0 // (ENABLE_MSTAR_MONACO==1) 
    set_miu_group_priority(2, getenv("MIU2_GROUP_PRIORITY"));
#endif


    //SELMIU
    sMIUSettings = getenv("MIU0_GROUP_SELMIU");
    if(NULL == sMIUSettings)
    {
        //use default miu settings 
        UBOOT_DEBUG("Setting DEFAULT_MIU0_GROUP_SELMIU=%s\n", DEFAULT_MIU0_GROUP_SELMIU);
        select_miu(0, DEFAULT_MIU0_GROUP_SELMIU);
    }
    else
    {
        UBOOT_DEBUG("Setting MIU0_GROUP_SELMIU=%s\n", sMIUSettings);
        select_miu(0, sMIUSettings);
    }
    sMIUSettings = getenv("MIU1_GROUP_SELMIU");
    if(NULL == sMIUSettings)
    {
        //use default miu settings 
        UBOOT_DEBUG("Setting DEFAULT_MIU1_GROUP_SELMIU=%s\n", DEFAULT_MIU1_GROUP_SELMIU);
        select_miu(1, DEFAULT_MIU1_GROUP_SELMIU);
    }
    else
    {
        UBOOT_DEBUG("Setting MIU1_GROUP_SELMIU=%s\n", sMIUSettings);
        select_miu(1, sMIUSettings);
    }
    sMIUSettings = getenv("MIU2_GROUP_SELMIU");
    if(NULL == sMIUSettings)
    {
        //use default miu settings 
        UBOOT_DEBUG("Setting DEFAULT_MIU2_GROUP_SELMIU=%s\n", DEFAULT_MIU2_GROUP_SELMIU);
        select_miu(2, DEFAULT_MIU2_GROUP_SELMIU);
    }
    else
    {
        UBOOT_DEBUG("Setting MIU2_GROUP_SELMIU=%s\n", sMIUSettings);
        select_miu(2, sMIUSettings);
    }


#else
    set_miu_group_priority(0, getenv("MIU0_GROUP_PRIORITY"));
    set_miu_group_priority(1, getenv("MIU1_GROUP_PRIORITY"));
    
#if 0 // (ENABLE_MSTAR_MONACO==1) 
    set_miu_group_priority(2, getenv("MIU2_GROUP_PRIORITY"));
#endif
    select_miu(0, getenv("MIU0_GROUP_SELMIU"));
    select_miu(1, getenv("MIU1_GROUP_SELMIU"));
    
#if (ENABLE_MSTAR_MONACO==1)
    select_miu(2, getenv("MIU2_GROUP_SELMIU"));
#endif

#endif
}

int do_set_miu(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    set_miu();
    return 0;
}

int do_disable_uart ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    volatile u32 *ptr;

    printf("Disable UART\n");

    ptr = (u32 *)(MS_RIU_MAP + (0x0E12<<1));
    *ptr &= ~0x1800;
    //mdrv_uart_connect(E_UART_PORT0,E_UART_OFF);
    return 0;
}

static U32 gu32ChunkHeader[CH_ITEM_LAST+1];
static BOOLEAN ChunkHeaderReady = FALSE;
int MsApiChunkHeader_Init(void)
{
    U32 u32ChunkHeaderOffset = 0;
    int ret = -1;

    UBOOT_TRACE("IN\n");
    raw_io_config_push();
    ret = mboot_raw_io_Config();
    if(ret != 0)
    {
        UBOOT_ERROR("raw_io_config setting fail!\n");
        raw_io_config_pop();
        return ret;
    }

    if(get_raw_status()==E_RAW_DATA_IN_SPI)
    {
        if(IsHouseKeepingBootingMode()==FALSE){
             u32ChunkHeaderOffset = 0x30000;
        }
        else
        {
            #if(CONFIG_MSTAR_RT_PM_IN_SPI==1)
                u32ChunkHeaderOffset = 0x30000;
            #else
#if defined(CONFIG_PM_SIZE_KB_FORCED) && (0!=CONFIG_PM_SIZE_KB_FORCED)
                u32ChunkHeaderOffset = 0x10000+(CONFIG_PM_SIZE_KB_FORCED*0x400);
#else
                u32ChunkHeaderOffset = 0x20000;
#endif
            #endif
        }

        #if(ENABLE_MSTAR_PUMABOOT)
        u32ChunkHeaderOffset = u32ChunkHeaderOffset + CONFIG_PUMABOOT_SIZE;
        #endif
    }
    else
    {
         u32ChunkHeaderOffset = 0;
    }
    #ifdef CONFIG_DOUBLE_MBOOT
	if (mbootbak_raw_io_Config() == 1)
	{
		ret = raw_read((U32)0x45000000,0,0x300000);
		ret = raw_read((U32)gu32ChunkHeader,u32ChunkHeaderOffset,(CH_ITEM_LAST+1)*4);
		raw_io_config(E_RAW_DATA_IN_MMC,UNNECESSARY_PARTITION,"MBOOT");
		raw_write((U32)0x45000000,0,0x300000);
	}
	else
    #endif
		ret = raw_read((U32)gu32ChunkHeader,u32ChunkHeaderOffset,(CH_ITEM_LAST+1)*4);
    raw_io_config_pop();
 
    if(ret != 0)
    {
         UBOOT_ERROR("raw_read gu8ChunkHeader fail\n");
         return -1;
    }
    
    ChunkHeaderReady = TRUE; 
    UBOOT_TRACE("OK\n");
    return 0;    
}

int MsApiChunkHeader_GetValue(EN_CHUNK_HEADER_ITEM enItem,unsigned int *puValue)
{
    UBOOT_TRACE("IN\n");
    
    //UBOOT_DUMP(gu8ChunkHeader,CH_ITEM_LAST);
    if(puValue==NULL)
    {
        UBOOT_ERROR("puValue is a null pointer\n");
        return -1;
    }
    
    if(ChunkHeaderReady != TRUE)
    {
        if(MsApiChunkHeader_Init() !=0)
        {
            UBOOT_ERROR("MsApiChunkHeader_Init fail\n");
            return -1;
        }
    }


    if((enItem>=CH_ITEM_FIRST) && (enItem<=CH_ITEM_LAST))
    {
        *puValue = gu32ChunkHeader[enItem];
        UBOOT_DEBUG("ChunkHeaderOffset(0x%x): 0x%x\n",enItem,*puValue);
    }
    else
    {
        UBOOT_ERROR("ERROR: Out of chunk header bound : %d \n",enItem);
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;    
}


extern U32 __heap;
extern U32 __heap_end;
void console_init(void)
{
#if 0//(CONFIG_R2_BRINGUP)
    //don't reinit uart
    return;
#endif	// CONFIG_R2_BRINGUP

    //bit 12 UART Enable, bit 11 UART RX Enable
    *(volatile U32*)(MS_RIU_MAP+(0x0E12<<1)) &= ~0x1800;    //don't enable uart (decided by mboot env)

    // Switch UART0 to PIU UART 0
    // Clear UART_SEL0
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) &= ~0x000F;
#if (EARLY_DISABLE_UART)
#else
    // bit 11 UART RX Enable
    *(volatile U32*)(MS_RIU_MAP+(0x0E12<<1)) |= 0x0800;

    // UART_SEL0 --> PIU UART0
#if (ENABLE_MSTAR_BD_MST147B_D01A_S_AGATE)
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x5004;

#elif (ENABLE_MSTAR_BD_MST036B_EDISON || ENABLE_MSTAR_BD_MST036B_EDISON_CUS18_ATSC)
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0xFFFF;
	#if defined (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)|| defined (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
		*(volatile U32*)(MS_RIU_MAP+(0x100B28<<1)) = 0x0c0c; //set piu_uart1/piu_uart2 clock
		
		*(volatile U32*)(MS_RIU_MAP+(0x220c98)) |= 0x0080;
		*(volatile U32*)(MS_RIU_MAP+(0x220c80)) = 0x0042;
		*(volatile U32*)(MS_RIU_MAP+(0x220c88)) = 0x0000;
		*(volatile U32*)(MS_RIU_MAP+(0x220c98)) &= ~(0x0080);

		*(volatile U32*)(MS_RIU_MAP+(0x101E04<<1)) = 0x0800; //set uart pad mux
	#endif
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x0654;
#else
	#if defined(CONFIG_MSTAR_NUGGET)
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x0504;
	#if defined (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)|| defined (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
		*(volatile U32*)(MS_RIU_MAP+(0x100B28<<1)) = 0x0c0c; //set piu_uart1/piu_uart2 clock
		*(volatile U32*)(MS_RIU_MAP+(0x11060C<<1)) = 0x0093;
		*(volatile U32*)(MS_RIU_MAP+(0x110600<<1)) = 0x0042;
		*(volatile U32*)(MS_RIU_MAP+(0x110610<<1)) = 0x000F;
		*(volatile U32*)(MS_RIU_MAP+(0x11060A<<1)) = 0x00C1;
		*(volatile U32*)(MS_RIU_MAP+(0x11060C<<1)) &= ~(0x0080);
	#endif
	#elif defined(CONFIG_MSTAR_NIKON)
	*(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x0004;
	#if defined (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)|| defined (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
		*(volatile U32*)(MS_RIU_MAP+(0x100B28<<1)) = 0x0c0c; //set piu_uart1/piu_uart2 clock
		*(volatile U32*)(MS_RIU_MAP+(0x11060C<<1)) = 0x0093;
		*(volatile U32*)(MS_RIU_MAP+(0x110600<<1)) = 0x0042;
		*(volatile U32*)(MS_RIU_MAP+(0x110610<<1)) = 0x000F;
		*(volatile U32*)(MS_RIU_MAP+(0x11060A<<1)) = 0x00C1;
		*(volatile U32*)(MS_RIU_MAP+(0x11060C<<1)) &= ~(0x0080);
	#endif
	#elif defined(CONFIG_MSTAR_MILAN)
	*(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x0004;
	#if defined (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)|| defined (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
		*(volatile U32*)(MS_RIU_MAP+(0x100B28<<1)) = 0x0c0c; //set piu_uart1/piu_uart2 clock
		*(volatile U32*)(MS_RIU_MAP+(0x11060C<<1)) = 0x0093;
		*(volatile U32*)(MS_RIU_MAP+(0x110600<<1)) = 0x0042;
		*(volatile U32*)(MS_RIU_MAP+(0x110610<<1)) = 0x000F;
		*(volatile U32*)(MS_RIU_MAP+(0x11060A<<1)) = 0x00C1;
		*(volatile U32*)(MS_RIU_MAP+(0x11060C<<1)) &= ~(0x0080);
	#endif
	#elif defined(CONFIG_MSTAR_KAISERIN)
	*(volatile U32*)(MS_RIU_MAP+(0x100B2E<<1)) = 0x010C;

	*(volatile U32*)(MS_RIU_MAP+(0x11068C<<1)) = 0x0093;
	*(volatile U32*)(MS_RIU_MAP+(0x110680<<1)) = 0x0014; //for fast uart clcok:12M , buadrate:38400
	*(volatile U32*)(MS_RIU_MAP+(0x110690<<1)) = 0x000F;
	*(volatile U32*)(MS_RIU_MAP+(0x11068A<<1)) = 0x00C1;
	*(volatile U32*)(MS_RIU_MAP+(0x11068C<<1)) &= ~(0x0080);

	*(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x0074;
	#else
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) = 0x0654;
	#endif
#endif
    *(volatile U32*)(MS_RIU_MAP+(0x101EA8<<1)) = 0x0000;
#endif
    // <-------

    // UART mode

    //enable reg_uart_rx_enable;
    *(volatile U32*)(MS_RIU_MAP+(0x101EA2<<1)) |= (1<<10);

//    MDrv_UART_Init(E_UART_PIU_UART0, 115200);

}

void console_disable(void)
{
    *(volatile U32*)(MS_RIU_MAP+(0x101EA6<<1)) |= 0x000F;
    //*(volatile U32*)(MS_RIU_MAP+(0x0E12<<1)) &= ~0x800;    //don't enable uart (decided by mboot env)
                                             
    // Switch UART0 to PIU UART 0
	//mdrv_uart_connect(E_UART_PORT0,E_UART_OFF);
}

MS_BOOL IsHouseKeepingBootingMode(void)
{
    UBOOT_TRACE("IN\n");
    #if defined (CONFIG_BOOTING_FROM_OTP_WITH_PM51)|| defined (CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)
    UBOOT_DEBUG("Host keeping is not the booting CPU\n");
    UBOOT_TRACE("OK\n");
    return FALSE;
    #else
    UBOOT_DEBUG("Host keeping is the booting CPU\n");
    UBOOT_TRACE("OK\n");
    return TRUE;
    #endif
}

MS_BOOL IsBootingFromMaskRom(void)
{
    UBOOT_TRACE("IN\n");
    #if defined (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)|| defined (CONFIG_MSTAR_ROM_BOOT_WITH_EMMC_FLASH)
    UBOOT_DEBUG("Boot from mask rom\n");
    UBOOT_TRACE("OK\n");
    return TRUE;
    #else
    UBOOT_DEBUG("Doesn't boot from mask rom\n");
    UBOOT_TRACE("OK\n");
    return FALSE;
    #endif
}

MS_BOOL MsApi_MBX_Init(void)
{
    MBX_CPU_ID eHKCPU;
    MS_U32 u32TimeoutMillSecs = 1500;

    eHKCPU = E_MBX_CPU_MIPS;
    if( E_MBX_SUCCESS != MDrv_MBX_Init(eHKCPU, E_MBX_ROLE_HK, u32TimeoutMillSecs))
    {
        printf("Error> MBX init failed !!\n");
        while(1);
    }
    else
    {
        MDrv_MBX_Enable(TRUE);
        return TRUE;
    }
}

void MsSystemReset(void)
{
   if((IsHouseKeepingBootingMode()==FALSE)&&(ENABLE_MODULE_SECURITY_BOOT==1))
   {
    msAPI_PM_MBX_Init();
    msAPI_PM_Reset();
   }
   else
   {
    MDrv_Sys_WholeChipReset();
   }
   hang();
}

unsigned long MsSystemGetBootTime()
{
#if defined(CONFIG_MIPS32)
    unsigned int PiuTick = *(volatile unsigned int *)(0xBF006090);
    PiuTick |= (*(volatile unsigned int *)(0xBF006094)) << 16;
#elif defined(CONFIG_ARMV7)
    unsigned int PiuTick = *(volatile unsigned int *)(0x1f006090);
    PiuTick |= (*(volatile unsigned int *)(0x1f006094)) << 16;
#else
#error "Please Specify Your CHIP type (MIPS32/ARMV7) in the chip config(include/configs/$(CHIP).h)."
#endif
    unsigned long PiuTime = PiuTick / 12000;
    return PiuTime;
}

#if CONFIG_RESCUE_ENV
#include <MsVfs.h>
#include <drvSERFLASH.h>
#include <MsEnvironment.h>
#include <environment.h>
static int _MsApi_BrickTerminator_Recover_Reserve (void);
static int _MsApi_BrickTerminator_Recover_NonReserve (void);
static int _MsApi_BrickTerminator_CheckRecover (unsigned char u8Count);
static int _MsApi_BrickTerminator_BackupEnv (void);
static int _MsApi_BrickTerminator_RestoreEnv (void);
static int _MsApi_BrickTerminator_ForceRecover (unsigned char u8Status);
static int _MsApi_BrickTerminator_Add2BootArgs (void);
extern int env_reload(void);
extern int restoreenv_from_rescue(void);
extern unsigned int cfg_env_offset;

#if 1 //From Kenny
#define BRICK_TERMINATOR_SPI_STATUS_OFFSET_STRING	"BRICK_TERMINATOR_SPI_STATUS_OFFSET"
#define BRICK_TERMINATOR_SPI_WP_GPIO_NUM_STRING	"SPI_WP"
#define STATUS_SIZE		8
#define SIZE_OF_BLOCK sizeof(Brick_Block)

typedef struct
{
    MS_U32 index;
    MS_U8 value[32];

} Brick_Block;

#if (ENABLE_MODULE_ENV_IN_SERIAL)
static int _MsApi_BrickTerminatorInfo_test_read_SPI(MS_U8 *value);
static int _MsApi_BrickTerminatorInfo_test_write_SPI(MS_U8 value);

static const SERFLASH_Info *pSpiflashinfo = NULL;
static int _MsApi_BrickTerminatorInfo_test_write_SPI(MS_U8 value)
{
    int ret = 0;
    const SERFLASH_Info *spiflashinfo = NULL;
    MS_U32 block_num = 0;

#if 1
    if(NULL == pSpiflashinfo)
    {
        pSpiflashinfo = MDrv_SERFLASH_GetInfo();
        if(pSpiflashinfo == NULL)
        {
            ret = -1;    
            return ret;
        }
        spiflashinfo = pSpiflashinfo;
    }
#else
    spiflashinfo = MDrv_SERFLASH_GetInfo();
    if(spiflashinfo == NULL)
    {
        ret = -1;
        return ret;
    }
#endif
    UBOOT_DEBUG("spiflashinfo.u32SecNum:%ld, spiflashinfo.u32SecSize:%ld, spiflashinfo.u32TotalSize:%ld\n", spiflashinfo->u32SecNum, spiflashinfo->u32SecSize, spiflashinfo->u32TotalSize);

    block_num = (spiflashinfo->u32SecSize / 16) / SIZE_OF_BLOCK;//16 is self define
    UBOOT_DEBUG("block_num: %ld\n", block_num);

    //write
    MS_U32 status_addr = 0;
    status_addr = CONFIG_SPI_STATUS_ADDR;
    UBOOT_DEBUG("status_addr: %lX\n", status_addr);
#if 0
    MDrv_FLASH_WriteProtect(0);
    MDrv_SERFLASH_SectorErase(status_addr, status_addr + (spiflashinfo->u32SecSize / 16) - 1);
    MDrv_FLASH_WriteProtect(1);
#endif
    int count = 1;
    Brick_Block block;
    memset(&block, 0, sizeof(block));

    //while
    while(1)
    {
        MDrv_SERFLASH_Read(status_addr, sizeof(block.index), (MS_U8 *)&block);
        //printf("block.index: %lX, sizeof(block.index): %d\n", block.index, sizeof(block.index));

        if(block.index == 0)
        {
            //jump to next index
            count++;
            if(count > block_num)
            {
                UBOOT_DEBUG("block.index: %lX, sizeof(block.index): %d\n", block.index, sizeof(block.index));

                count = 1;
                status_addr = CONFIG_SPI_STATUS_ADDR;

                //erase 
                MDrv_FLASH_WriteProtect(0);
                MDrv_SERFLASH_SectorErase(status_addr, status_addr + (spiflashinfo->u32SecSize / 16) - 1);
                MDrv_SERFLASH_WriteProtect(1);
                break;
            }
            else
            {
                status_addr += (SIZE_OF_BLOCK);
            }

            block.index = 0;       
            continue;
        }
        else
        {
            UBOOT_DEBUG("block.index: %lX, sizeof(block.index): %d\n", block.index, sizeof(block.index));

            //read value
            break;
        }
    }
    //end while

    UBOOT_DEBUG("status_addr: %lX\n", status_addr);
    MDrv_SERFLASH_Read(status_addr, SIZE_OF_BLOCK, (MS_U8 *)&block);

    block.index = ntohl(block.index);
    MS_U32 temp_index = block.index;

    int bit = 0;
    while(1)
    {
        if(temp_index & (0x00000001 << bit))
        {
            block.index &= ~(0x00000001 << bit);
            block.value[bit] = value;//write value
            UBOOT_DEBUG("bit %d, write_value %X\n", bit, value);
            break;
        }
        else
        {
            bit++;    
        }
    }

    block.index = htonl(block.index);

    MDrv_FLASH_WriteProtect(0);
    MDrv_SERFLASH_Write(status_addr, SIZE_OF_BLOCK, (MS_U8 *)&block);
    MDrv_FLASH_WriteProtect(1);

#if 0//print spi
    MS_U8 print_array[SIZE_OF_BLOCK] = {0};
    MDrv_SERFLASH_Read(status_addr, SIZE_OF_BLOCK, print_array);

    int x;
    for(x=0; x<SIZE_OF_BLOCK; x++)
    {
        printf("%d %X\n", x, print_array[x]);
    }
#endif
    //end write

    return ret;      
}

int _MsApi_BrickTerminatorInfo_test_read_SPI(MS_U8 *value)
{
    int ret = 0;
    const SERFLASH_Info *spiflashinfo = NULL;
    MS_U32 block_num = 0;
    MS_U32 start_addr = 0;

#if 1
    if(NULL == pSpiflashinfo)
    {
        pSpiflashinfo = MDrv_SERFLASH_GetInfo();
        if(pSpiflashinfo == NULL)
        {
            ret = -1;    
            return ret;
        }
        spiflashinfo = pSpiflashinfo;
    }
#else
    spiflashinfo = MDrv_SERFLASH_GetInfo();
    if(spiflashinfo == NULL)
    {
        ret = -1;    
        return ret;
    }
#endif
    UBOOT_DEBUG("spiflashinfo.u32SecNum:%ld, spiflashinfo.u32SecSize:%ld, spiflashinfo.u32TotalSize:%ld\n", spiflashinfo->u32SecNum, spiflashinfo->u32SecSize, spiflashinfo->u32TotalSize);

    block_num = (spiflashinfo->u32SecSize / 16) / SIZE_OF_BLOCK;//16 is self define
    UBOOT_DEBUG("block_num: %ld\n", block_num);

    //read
    MS_U32 status_addr = 0;
    status_addr = CONFIG_SPI_STATUS_ADDR;
    start_addr = status_addr;
    UBOOT_DEBUG("status_addr: %lX\n", status_addr);

/*
    MDrv_FLASH_WriteProtect(0);
    MDrv_SERFLASH_SectorErase(status_addr, status_addr + (spiflashinfo->u32SecSize / 16) - 1);
    MDrv_FLASH_WriteProtect(1);
*/
    int count = 1;
    Brick_Block block;
    memset(&block, 0, sizeof(block));

    //while
    while(1)
    {
        MDrv_SERFLASH_Read(status_addr, sizeof(block.index), (MS_U8 *)&block);
        //printf("block.index: %lX, sizeof(block.index): %d\n", block.index, sizeof(block.index));

        if(block.index == 0)
        {
            //jump to next index
            count++;
            if(count > block_num)
            {
                UBOOT_DEBUG("block.index: %lX, sizeof(block.index): %d\n", block.index, sizeof(block.index));

                //last             
                break;
            }
            else
            {
                status_addr += (SIZE_OF_BLOCK);
            }

            block.index = 0;       
            continue;
        }
        else
        {
            UBOOT_DEBUG("block.index: %lX, sizeof(block.index): %d\n", block.index, sizeof(block.index));

            //read value
            if(block.index == 0xFFFFFFFF)
            {
                if(status_addr == start_addr)
                {
                    MS_U8 u8Value_array = 0xFE;
                    MDrv_SERFLASH_WriteProtect(0);
                    MDrv_SERFLASH_Write(status_addr+sizeof(block.index)-1, 1, &u8Value_array);
                    MDrv_SERFLASH_WriteProtect(1);
                    break;
                }
                status_addr -= (SIZE_OF_BLOCK);    
            }
            break;
        }
    }
    //end while

    UBOOT_DEBUG("status_addr: %lX\n", status_addr);
    MDrv_SERFLASH_Read(status_addr, SIZE_OF_BLOCK, (MS_U8 *)&block);

#if 0 //print spi
    MS_U8 *byte_of_block = (MS_U8 *)&block;
    int x;
    for(x=0; x<SIZE_OF_BLOCK; x++)
    {
        printf("%d %X\n", x, *byte_of_block);
        byte_of_block++;
    }
#endif

    block.index = ntohl(block.index);
    MS_U32 temp_index = block.index;

    int bit = 0;
    while(1)
    {
        if(temp_index & (0x00000001 << bit))
        {    
            *value = block.value[bit-1];
            break;
        }
        else
        {
            bit++;
            if(bit >= 32)
            {
                *value = block.value[bit-1];
                break;
            }
        }
    }

    UBOOT_DEBUG("bit %d, return_value %X\n", bit-1, *value);

    return ret;      
}
#endif 
#endif//if 0

#if 0
static int MsApi_BrickTerminator_read_flash(MS_U32 u32Addr, MS_U8* pu8Dst, MS_U32 u32Size)
{
    int ret = -1;
#if 1
    ret=MDrv_SERFLASH_Read(u32Addr, u32Size, pu8Dst);
#else
    printf("Write addr=0x%08x, size=0x%08x\n", (unsigned int)u32Addr, (unsigned int)u32Size);

    MDrv_SERFLASH_WriteProtect(FALSE);
    if(u32Size>0x1000) // a sector size is 4KBytes
    {
        printf("block erase\n");
        ret=MDrv_SERFLASH_AddressErase(u32Addr, u32Size, TRUE);
    }
    else
    {
        printf("sector erase\n");
        ret=MDrv_SERFLASH_SectorErase(u32Addr, u32Addr+u32Size-1);
    }
    if (ret!=-1)
    {
        if (MDrv_SERFLASH_Write(u32Addr, u32Size, (MS_U8*)pu8Src))
        {
            ret = 0;
        }
    }
    MDrv_SERFLASH_WriteProtect(TRUE);
#endif

    return ret;
}

static int MsApi_BrickTerminator_write_flash(MS_U32 u32Addr, const MS_U8* pu8Src, MS_U32 u32Size)
{
    int ret = -1;
    printf("Write addr=0x%08x, size=0x%08x\n", (unsigned int)u32Addr, (unsigned int)u32Size);

    MDrv_SERFLASH_WriteProtect(FALSE);
    if(u32Size>0x1000) // a sector size is 4KBytes
    {
        printf("block erase\n");
        ret=MDrv_SERFLASH_AddressErase(u32Addr, u32Size, TRUE);
    }
    else
    {
        printf("sector erase\n");
        ret=MDrv_SERFLASH_SectorErase(u32Addr, u32Addr+u32Size-1);
    }
    if (ret!=-1)
    {
        if (MDrv_SERFLASH_Write(u32Addr, u32Size, (MS_U8*)pu8Src))
        {
            ret = 0;
        }
    }
    MDrv_SERFLASH_WriteProtect(TRUE);

    return ret;
}
#endif

#define BRICKTERMINATOR_STATUS_LENGTH 8
#define SPI_ADDR CONFIG_SPI_STATUS_ADDR
MS_BOOL MsApi_BrickTerminator_GetStatus(unsigned char *status)
{
    *status = MDrv_SYS_ReadBrickTerminatorStatus();
    return TRUE;
}

MS_BOOL MsApi_BrickTerminator_SetStatus(unsigned char status)
{
    MDrv_SYS_WriteBrickTerminatorStatus((unsigned int)status);
    return TRUE;
}

#define BOOT_RECOVER_CNT_DEFAULT 0xF
#define BOOT_RECOVER_MAX_RETRY_COUNT 3
#define BOOT_RECOVER_THRESHOLD (BOOT_RECOVER_CNT_DEFAULT-BOOT_RECOVER_MAX_RETRY_COUNT) //0xC
#define BOOT_RECOVER_PHASE2_MAX_RETRY_COUNT 1
#define BOOT_RECOVER_PHASE2_THRESHOLD (BOOT_RECOVER_CNT_DEFAULT-BOOT_RECOVER_MAX_RETRY_COUNT-BOOT_RECOVER_PHASE2_MAX_RETRY_COUNT) //0xB
#define BOOT_STATUS(x) (x&0xF)
#define BOOT_COUNT(x) (x>>4)
#define BOOT_MERGE(cnt,status) ((cnt<<4)|(BOOT_STATUS(status)))

char *BOOT_RECOVER_ENV_LIST[] = 
{
    "bootargs",
    "bootcmd",
    "info_exchange",
    "mtdparts",
    "verify",
    "MIU0_GROUP_PRIORITY",
    "MIU0_GROUP_SELMIU",
    "MIU1_GROUP_PRIORITY",
    "MIU1_GROUP_SELMIU",
    "UBI_SPEED_UP",
    NULL
};
extern char *CUS_BOOT_RECOVER_ENV_LIST[];

typedef enum _E_BRICK_TERMINATOR_STATUS
{
    E_BRICK_TERMINATOR_STATUS_START_RECOVER=0x0, // for type 4 file backup
    E_BRICK_TERMINATOR_STATUS_START_MBOOT=0x1,
    E_BRICK_TERMINATOR_STATUS_START_KERNEL=0x2,
    E_BRICK_TERMINATOR_STATUS_START_RESTORE=0xE, // for type 4 file restore
    E_BRICK_TERMINATOR_STATUS_CLEAR=0xF,
} E_BRICK_TERMINATOR_STATUS;

typedef enum _E_BRICK_TERMINATOR_CHECKSTATUS
{
    E_BRICK_TERMINATOR_CHECKSTATUS_UNDEFINED=-2,
    E_BRICK_TERMINATOR_CHECKSTATUS_ERROR=-1,
    E_BRICK_TERMINATOR_CHECKSTATUS_DONE=0x0,
    E_BRICK_TERMINATOR_CHECKSTATUS_NOUPDATE=0x1,
    E_BRICK_TERMINATOR_CHECKSTATUS_GOPHASE2=0x2,
} E_BRICK_TERMINATOR_CHECKSTATUS;

int do_BrickTerminator_Main (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    const char *BRICK_TERMINATOR_SPI_STATUS_OFFSET = BRICK_TERMINATOR_SPI_STATUS_OFFSET_STRING;
#if(PIN_FLASH_WP0) 
    const char *BRICK_TERMINATOR_SPI_WP = BRICK_TERMINATOR_SPI_WP_GPIO_NUM_STRING;
#endif
    unsigned char bClearStatusAndSkipCheck = 0;;
    unsigned char u8Status = 0, u8Count=0;
    char *pSwitch = getenv((char *)BRICK_TERMINATOR_SWITCH_STR);
//    uint u32Tmp=0;

    UBOOT_DEBUG("%s: at %d\n", __func__, __LINE__);
#if (ENABLE_MODULE_SPI_NAND_FLASH == 1)
    MDrv_SYS_Init();
#endif
    //NOTE: check if function switch is off
    {
        unsigned int u32Switch = 1;
        if(NULL!=pSwitch)
        {
            u32Switch = (unsigned int)simple_strtoul(pSwitch, NULL, 10);
        }
        if(0 == u32Switch)
        {
            UBOOT_DEBUG("%s: BYPASS, '%s': %u, at %d\n", __func__, BRICK_TERMINATOR_SWITCH_STR, u32Switch, __LINE__);
            if(0 != del_bootargs_cfg((char*)BRICK_TERMINATOR_SPI_STATUS_OFFSET))
            {
                UBOOT_ERROR("%s: Error! del_bootargs_cfg failed, at %d\n", __func__, __LINE__);
            }
#if(PIN_FLASH_WP0) 
            if(0 != del_bootargs_cfg((char*)BRICK_TERMINATOR_SPI_WP))
            {
                UBOOT_ERROR("%s: Error! del_bootargs_cfg failed, at %d\n", __func__, __LINE__);
            }
#endif
            return 0;
        }
    }

    if (argc > 2)
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        return 1;
    }
    else if(argc==2)
    {
        if(0==strcmp(argv[1], "recover_reserve"))
        {
            return _MsApi_BrickTerminator_Recover_Reserve();
        }
        else if(0==strcmp(argv[1], "recover_nonreserve"))
        {
            return _MsApi_BrickTerminator_Recover_NonReserve();
        }
        else if(0==strcmp(argv[1], "backup_env"))
        {
            return _MsApi_BrickTerminator_BackupEnv();
        }
        else if(0==strcmp(argv[1], "restore_env"))
        {
            return _MsApi_BrickTerminator_RestoreEnv();
        }
        else if(0==strcmp(argv[1], "force_recover"))
        {
            u8Status = BOOT_MERGE(BOOT_RECOVER_THRESHOLD, E_BRICK_TERMINATOR_STATUS_CLEAR); //0xCF
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
            if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
            {
                UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_SetStatus failed! at %d\n", __func__, __LINE__);
                return 1;
            }
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
            if(TRUE != MsApi_BrickTerminator_GetStatus(&u8Status))
            {
                UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_GetStatus failed! at %d\n", __func__, __LINE__);
                return 1;
            }
#if BRICK_TMP_PATCH
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
            _MsApi_BrickTerminator_ForceRecover(u8Status);

            {
                if(0 != _MsApi_BrickTerminator_Recover_NonReserve())
                {
                    UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_Recover_NonReserve failed! at %d\n", __func__, __LINE__);
                    return 1;
                }
                u8Status = BOOT_MERGE(BOOT_RECOVER_CNT_DEFAULT, E_BRICK_TERMINATOR_STATUS_CLEAR);
                if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
                {
                    UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_SetStatus failed! at %d\n", __func__, __LINE__);
                    return 1;
                }
            }
            goto BRICK_PATCH_EXIT;
#else
            return _MsApi_BrickTerminator_ForceRecover(u8Status);
#endif
        }
        else if(0==strcmp(argv[1], "add2bootargs"))
        {
            return _MsApi_BrickTerminator_Add2BootArgs();
        }
    }

    if(0 != _MsApi_BrickTerminator_Add2BootArgs())
    {
        UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_Add2BootArgs failed, at %d\n", __func__, __LINE__);
        //return 1; //NOTE: no need to return, for the case the main env is damaged
    }

    // NOTE: MMIO should be initialized first
    //    MDrv_MMIO_Init();
    //    MDrv_MMIO_GetBASE((MS_U32 *)&MS_RIU_MAP, (MS_U32 *)&u32Tmp, MS_MODULE_PM);

    if(TRUE != MsApi_BrickTerminator_GetStatus(&u8Status))
    {
        UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_GetStatus failed! at %d\n", __func__, __LINE__);
        return 1;
    }
    UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG

    u8Count = BOOT_COUNT(u8Status);

    //FLOW: 1. check if enter start restore status (0xE)
    if((unsigned char)E_BRICK_TERMINATOR_STATUS_START_RESTORE == BOOT_STATUS(u8Status))
    {
        if(0 != _MsApi_BrickTerminator_Recover_NonReserve())
        {
            UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_Recover_NonReserve failed! at %d\n", __func__, __LINE__);
            return 1;
        }
    }
    else
    {
        {
#if ((CONFIG_RESCUE_ENV_IR_TRIGGER) && (1 != CONFIG_RESCUE_ENV_AUTO_TRIGGER))
            //NOTE: if IR triggered recover done (PHASE2 done), end all
            if(((unsigned char)E_BRICK_TERMINATOR_STATUS_CLEAR == BOOT_STATUS(u8Status)) && ((unsigned char)BOOT_RECOVER_CNT_DEFAULT == BOOT_COUNT(u8Status)))
            {
                unsigned int u32Value = 0;
                char *pEnv = getenv(BRICK_TERMINATOR_IR_TRIGGERED_STRING);
                if(NULL != pEnv)
                {
                    u32Value = (unsigned int)simple_strtoul(pEnv, NULL, 10);
                    if(1 == u32Value)
                    {
#if BRICK_TMP_PATCH
BRICK_PATCH_EXIT:
                ;
#endif
                        if(0 != del_bootargs_cfg((char*)BRICK_TERMINATOR_SPI_STATUS_OFFSET))
                        {
                            UBOOT_ERROR("%s: Error! del_bootargs_cfg failed, at %d\n", __func__, __LINE__);
                        }
#if(PIN_FLASH_WP0) 
                        if(0 != del_bootargs_cfg((char*)BRICK_TERMINATOR_SPI_WP))
                        {
                            UBOOT_ERROR("%s: Error! del_bootargs_cfg failed, at %d\n", __func__, __LINE__);
                        }
#endif
                        //NOTE: clean env after job done
                        setenv(BRICK_TERMINATOR_IR_TRIGGERED_STRING, NULL);
                        saveenv();
                        UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
#if BRICK_TMP_PATCH
                        run_command("reset", 0);
#endif
                        return 0;
                    }
                }
            }
#endif //CONFIG_RESCUE_ENV_IR_TRIGGER

            //NOTE: check if needed to leave
            //RULE: if non-WDT, then should leave
            MDrv_WDT_Init(E_WDT_DBGLV_ALL);
            if(E_WDT_OK != MDrv_WDT_IsReset())
            {
                UBOOT_DEBUG("%s: NON WDT at %d\n", __func__, __LINE__);
                bClearStatusAndSkipCheck = 1;
            }
            else
            {
                UBOOT_DEBUG("%s: WDT on at %d\n", __func__, __LINE__);
                if(E_WDT_OK != MDrv_WDT_ClearRstFlag())
                {
                    UBOOT_ERROR("%s: Error! MDrv_WDT_ClearRstFlag() failed at %d\n", __func__, __LINE__);
                    return 1;
                }
            }

            //NOTE: if no need to run BrickTerminator
            if(1 == bClearStatusAndSkipCheck)
            {
                u8Status = BOOT_MERGE(BOOT_RECOVER_CNT_DEFAULT, E_BRICK_TERMINATOR_STATUS_START_MBOOT);
                if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
                {
                    UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_SetStatus failed! at %d\n", __func__, __LINE__);
                    return 1;
                }
                UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
                return 0;
            }
        }

        //FLOW: 2. check if enter clear status (0xF)
        if((unsigned char)E_BRICK_TERMINATOR_STATUS_CLEAR == BOOT_STATUS(u8Status))
        {
            if(0 != _MsApi_BrickTerminator_ForceRecover(u8Status))
            {
                UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_ForceRecover failed! at %d\n", __func__, __LINE__);
                return 1;
            }
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
            if(TRUE != MsApi_BrickTerminator_GetStatus(&u8Status))
            {
                UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_GetStatus failed! at %d\n", __func__, __LINE__);
                return 1;
            }
        }
        //FLOW: 3. other status
        else
        {
            //NOTE: 1. CNT += 1
            u8Count -= 1;
            u8Status = BOOT_MERGE(u8Count, u8Status);
            if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
            {
                UBOOT_ERROR("%s: MsApi_BrickTerminator_SetStatus errs! at %d\n", __func__, __LINE__);
                return 1;
            }
            //NOTE: 2. continue normal boot
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
            if(TRUE != MsApi_BrickTerminator_GetStatus(&u8Status))
            {
                UBOOT_ERROR("%s: MsApi_BrickTerminator_GetStatus errs! at %d\n", __func__, __LINE__);
                return 1;
            }
            UBOOT_DEBUG("%s: u8Count: 0x%02x, at %d\n", __func__, u8Count, __LINE__); //DBG
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG

            if(0 != _MsApi_BrickTerminator_ForceRecover(u8Status))
            {
                UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_ForceRecover failed! at %d\n", __func__, __LINE__);
                return 1;
            }
            UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
            if(TRUE != MsApi_BrickTerminator_GetStatus(&u8Status))
            {
                UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_GetStatus failed! at %d\n", __func__, __LINE__);
                return 1;
            }
        }
    }

    UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG

    return 0;
}


static int _MsApi_BrickTerminator_CheckRecover (unsigned char u8Count)
{
    unsigned char u8Status = 0;
    if(BOOT_RECOVER_THRESHOLD >= u8Count)
    {
        if(BOOT_RECOVER_PHASE2_THRESHOLD >= u8Count) //NOTE: AP failed to recover, go phase2 straight
        {
            return E_BRICK_TERMINATOR_CHECKSTATUS_GOPHASE2;
        }
        UBOOT_DEBUG("%s: START RECOVERY, u8Count: 0x%02x, at %d\n", __func__, u8Count, __LINE__); //DBG
        //NOTE: 0. DO env RECOVERY
        if(0 != _MsApi_BrickTerminator_RestoreEnv())
        {
            UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_RestoreEnv failed! at %d\n", __func__, __LINE__);
            //return 1; //TODO: consider of need to return
        }
        if(0 != _MsApi_BrickTerminator_Add2BootArgs())
        {
            UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_Add2BootArgs failed, at %d\n", __func__, __LINE__);
            return 1;
        }
        //NOTE: 1. DO reserve part RECOVERY
#if 1
        {
            if(0 != _MsApi_BrickTerminator_Recover_Reserve())
            {
                UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_Recover_Reserve failed! at %d\n", __func__, __LINE__);
                return E_BRICK_TERMINATOR_CHECKSTATUS_ERROR;
            }
        }
#endif
        //NOTE: 2. FLAGS = 0x0
        u8Status = (unsigned char)E_BRICK_TERMINATOR_STATUS_START_RECOVER;

        u8Status = BOOT_MERGE(u8Count, u8Status);
        if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
        {
            UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_SetStatus failed! at %d\n", __func__, __LINE__);
            return E_BRICK_TERMINATOR_CHECKSTATUS_ERROR;
        }
        UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
        if(TRUE != MsApi_BrickTerminator_GetStatus(&u8Status))
        {
            UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_GetStatus failed! at %d\n", __func__, __LINE__);
            return E_BRICK_TERMINATOR_CHECKSTATUS_ERROR;
        }
        //NOTE: 4. continue normal boot
        return E_BRICK_TERMINATOR_CHECKSTATUS_DONE; // NOTE: done
    }
    return E_BRICK_TERMINATOR_CHECKSTATUS_NOUPDATE; // NOTE: no need to update
}

static int _MsApi_BrickTerminator_BackupEnv ()
{
#if 1 // NOTE: backup env to rescue
    int idx=0;
    MS_BOOL bUpdate = FALSE;
    char *pEnv = NULL, *pBuf=NULL;

    UBOOT_DEBUG("%s: at %d\n", __func__, __LINE__); // DBG
    //NOTE: 1. backup the required env from current
    for(idx=0; NULL!=BOOT_RECOVER_ENV_LIST[idx]; idx++)
    {
        pEnv = getenv(BOOT_RECOVER_ENV_LIST[idx]);
        if(NULL != pEnv)
        {
            pBuf = malloc(strlen(pEnv)+1);
            if(NULL == pBuf)
            {
                UBOOT_ERROR("%s: Error! malloc(%d) failed, at %d\n", __func__, strlen(pEnv)+1, __LINE__); //DBG
                continue;
            }
            memset(pBuf, 0, strlen(pEnv)+1);
            snprintf(pBuf, strlen(pEnv), "%s", pEnv);
            setenv_rescue(BOOT_RECOVER_ENV_LIST[idx], pBuf);
            if(bUpdate != TRUE)
            {
                bUpdate = TRUE;
            }
            UBOOT_DEBUG("%s: update env: '%s', at %d\n", __func__, BOOT_RECOVER_ENV_LIST[idx], __LINE__); //DBG
            free(pBuf);
        }
    }
    //NOTE: 1.1 backup the customer required env from current
    for(idx=0; NULL!=CUS_BOOT_RECOVER_ENV_LIST[idx]; idx++)
    {
        pEnv = getenv(CUS_BOOT_RECOVER_ENV_LIST[idx]);
        if(NULL != pEnv)
        {
            pBuf = malloc(strlen(pEnv)+1);
            if(NULL == pBuf)
            {
                UBOOT_ERROR("%s: Error! malloc(%d) failed, at %d\n", __func__, strlen(pEnv)+1, __LINE__); //DBG
                continue;
            }
            memset(pBuf, 0, strlen(pEnv)+1);
            snprintf(pBuf, strlen(pEnv), "%s", pEnv);
            setenv_rescue(CUS_BOOT_RECOVER_ENV_LIST[idx], pBuf);
            if(bUpdate != TRUE)
            {
                bUpdate = TRUE;
            }
            UBOOT_DEBUG("%s: update env: '%s', at %d\n", __func__, CUS_BOOT_RECOVER_ENV_LIST[idx], __LINE__); //DBG
            free(pBuf);
        }
    }
    if(TRUE == bUpdate)
    {
        if(0!=saveenv_rescue())
        {
            UBOOT_ERROR("%s: ERROR: saveenv_rescue failed, at %d\n", __func__, __LINE__);
            return 1;
        }
    }
#endif
    UBOOT_DEBUG("%s: at %d\n", __func__, __LINE__); // DBG
    return 0;
}

static int _MsApi_BrickTerminator_RestoreEnv ()
{
    UBOOT_DEBUG("%s: at %d\n", __func__, __LINE__); // DBG
    if(0 != restoreenv_from_rescue()) // IF FINISH RECOVERY
    {
        UBOOT_ERROR("%s: Error! restoreenv_from_rescue failed! at %d\n", __func__, __LINE__);
        return 1;
    }
    //NOTE: reload env
    if(0!=env_reload())
    {
        UBOOT_ERROR("%s: Error! env_reload failed! at %d\n", __func__, __LINE__);
        return 1;
    }
#if !(CONFIG_LOGO_STORE_IN_MBOOT)
    run_command("dbtable_init", 0); //TODO: refine it
#endif
    run_command("updatemiureg", 0); //TODO: refine it
    return 0;
}

static int _MsApi_BrickTerminator_Recover_Reserve ()
{
    MS_BOOL bNeedReburn = TRUE;
    U32 u32PathSize = 0;
    const char* BOOT_RECOVER_BRICK_RESERVE_VOLUME = "brickreserve";
    const char* BOOT_RECOVER_BRICK_BACKUP_VOLUME = "brickbackup";
    const char* BOOT_RECOVER_BRICK_RESERVE_FILE = "/.ready";
    const char* BOOT_RECOVER_BRICK_BACKUP_FILE = "/MstarUpgrade_reserve.bin";
    if(0 == vfs_mount((char*)BOOT_RECOVER_BRICK_RESERVE_VOLUME))
    {
        u32PathSize = vfs_getsize((char*)BOOT_RECOVER_BRICK_RESERVE_FILE);
        if(0 < u32PathSize)
        {
            bNeedReburn = FALSE;
            UBOOT_DEBUG("%s: u32PathSize: %u, at %d\n", __func__, u32PathSize, __LINE__); // DBG
        }
        else // TODO: remove after debug
        {
            UBOOT_ERROR("%s: ERROR: vfs_getsize failed, at %d\n", __func__, __LINE__);
        }
    }
    if(TRUE == bNeedReburn)
    {
        char cmd[CMD_BUF] = {};
        vfs_umount();
        if(0 == vfs_mount((char*)BOOT_RECOVER_BRICK_BACKUP_VOLUME))
        {
            sprintf(cmd, "bstar %s", BOOT_RECOVER_BRICK_BACKUP_FILE);
            UBOOT_ERROR("%s: ERROR: VFS failed, at %d\n", __func__, __LINE__);
            UBOOT_DEBUG("%s: DO BRICK RESERVE RECOVER, at %d\n", __func__, __LINE__);
            //NOTE: do partition recover
            run_command(cmd, 0);
            vfs_umount();
        }
    }
    else
    {
        UBOOT_DEBUG("%s: '%s' is ok, no need to re-burn, at %d\n", __func__, BOOT_RECOVER_BRICK_RESERVE_VOLUME, __LINE__);
        vfs_umount();
    }
    return 0;
}

static int _MsApi_BrickTerminator_Recover_NonReserve ()
{
    char cmd[CMD_BUF] = {};
    const char* BOOT_RECOVER_BRICK_BACKUP_VOLUME = "brickbackup";
    const char* BOOT_RECOVER_BRICK_BACKUP_FILE = "/MstarUpgrade_backup.bin";

    vfs_umount();
    if(0 == vfs_mount((char*)BOOT_RECOVER_BRICK_BACKUP_VOLUME))
    {
        sprintf(cmd, "bstar %s", BOOT_RECOVER_BRICK_BACKUP_FILE);
        UBOOT_ERROR("%s: ERROR: VFS failed, at %d\n", __func__, __LINE__);
        UBOOT_DEBUG("%s: DO BRICK RESERVE RECOVER, at %d\n", __func__, __LINE__);
        //NOTE: do partition recover
        run_command(cmd, 0);
        vfs_umount();
    }
    return 0;
}

static int _MsApi_BrickTerminator_ForceRecover (unsigned char status)
{
    E_BRICK_TERMINATOR_CHECKSTATUS u8RetStatus=E_BRICK_TERMINATOR_CHECKSTATUS_UNDEFINED;
    unsigned char u8Status = 0, u8Count=0;
 
    UBOOT_DEBUG("%s: at %d\n", __func__, __LINE__); // DBG
    u8Count = BOOT_COUNT(status);
    u8Status = BOOT_STATUS(status);

    u8RetStatus = _MsApi_BrickTerminator_CheckRecover (u8Count);
    UBOOT_DEBUG("%s: u8RetStatus: 0x%02x, at %d\n", __func__, u8RetStatus, __LINE__); //DBG
    if(E_BRICK_TERMINATOR_CHECKSTATUS_ERROR == u8RetStatus)
    {
        UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_CheckRecover failed! at %d\n", __func__, __LINE__);
        return 1;
    }
    else if(E_BRICK_TERMINATOR_CHECKSTATUS_NOUPDATE == u8RetStatus) // no need to update
    {
        UBOOT_DEBUG("%s: status: 0x%02x, at %d\n", __func__, u8Status, __LINE__); //DBG
        //NOTE: 2. FLAGS = 0x1
        u8Status = (unsigned char)E_BRICK_TERMINATOR_STATUS_START_MBOOT;
        u8Status = BOOT_MERGE(u8Count, u8Status);
        if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
        {
            UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_SetStatus failed! at %d\n", __func__, __LINE__);
            return 1;
        }
    }
    else if(E_BRICK_TERMINATOR_CHECKSTATUS_GOPHASE2 == u8RetStatus)
    {
        if(0 != _MsApi_BrickTerminator_Recover_NonReserve())
        {
            UBOOT_ERROR("%s: Error! _MsApi_BrickTerminator_Recover_NonReserve failed! at %d\n", __func__, __LINE__);
            return 1;
        }
        u8Status = BOOT_MERGE(BOOT_RECOVER_CNT_DEFAULT, E_BRICK_TERMINATOR_STATUS_CLEAR);
        if(TRUE != MsApi_BrickTerminator_SetStatus(u8Status))
        {
            UBOOT_ERROR("%s: Error! MsApi_BrickTerminator_SetStatus failed! at %d\n", __func__, __LINE__);
            return 1;
        }
    }
    return 0;
}

static int _MsApi_BrickTerminator_Add2BootArgs (void)
{
    const char *BRICK_TERMINATOR_SPI_STATUS_OFFSET = BRICK_TERMINATOR_SPI_STATUS_OFFSET_STRING;
    unsigned int u32RescueStatusOffset =0;
    char buf[CMD_BUF] = "\0";    
    int ret=0;    
    // set BRICK_TERMINATOR_SPI_STATUS_OFFSET to bootargs
    MsApiChunkHeader_GetValue(CH_RESCURE_STATUS_ROM_OFFSET,&u32RescueStatusOffset);    
    u32RescueStatusOffset = GetRealOffset(u32RescueStatusOffset);
    sprintf(buf, "%s=%08X", BRICK_TERMINATOR_SPI_STATUS_OFFSET, u32RescueStatusOffset);
    if(0 != set_bootargs_cfg((char*)BRICK_TERMINATOR_SPI_STATUS_OFFSET, buf, 0))
    {
        UBOOT_ERROR("Error! set_bootargs_cfg failed\n");
        ret = -1;
    }

#if (PIN_FLASH_WP0&&ENABLE_MODULE_ENV_IN_SERIAL)    
    {   // set Write Protect GPIO to bootargs
        const char *BRICK_TERMINATOR_SPI_WP = BRICK_TERMINATOR_SPI_WP_GPIO_NUM_STRING;
        memset(buf,0,sizeof(buf));
        sprintf(buf, "%s=%X", BRICK_TERMINATOR_SPI_WP, PIN_FLASH_WP0);
        if(0 != set_bootargs_cfg((char*)BRICK_TERMINATOR_SPI_WP, buf, 0))
        {
            UBOOT_ERROR("%s: Error! set_bootargs_cfg failed, at %d\n", __func__, __LINE__);
            ret = -1;
        }
    }
#endif
    return ret;
}

#endif

#if (ENABLE_MSTAR_PUMABOOT)
MS_U32 MSys_GetBootTimeMs(void)
{
#if defined(CONFIG_MIPS32)
    unsigned int PiuTick = *(volatile unsigned int *)(0xBF006090);
    PiuTick |= (*(volatile unsigned int *)(0xBF006094)) << 16;
#elif defined(CONFIG_ARMV7)
    unsigned int PiuTick = *(volatile unsigned int *)(0x1f006090);
    PiuTick |= (*(volatile unsigned int *)(0x1f006094)) << 16;
#else
#error "Please Specify Your CHIP type (MIPS32/ARMV7) in the chip config(include/configs/$(CHIP).h)."
#endif
    unsigned long PiuTime = PiuTick / 12000;
    return PiuTime;
}

MS_U16 MSys_Read2Byte(MS_U32 u32Reg)
{
#if defined(CONFIG_MIPS32)
    return (MS_U16)(*(volatile unsigned int *)(0xBF000000+(u32Reg<<1)));
#elif defined(CONFIG_ARMV7)
    return (MS_U16)(*(volatile unsigned int *)(0x1F000000+(u32Reg<<1)));
#else
    #error "Please Specify Your CHIP type (MIPS32/ARMV7) in the chip config(include/configs/$(CHIP).h)."
#endif
}

#endif

