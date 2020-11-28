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
#include <exports.h>
#include <MsTypes.h>
#include <ShareType.h>
#include <MsBoot.h>
#include <MsUpgrade.h>
#include <uboot_mmap.h>
#include <MsDebug.h>
#if defined (CONFIG_URSA_6M40) && defined(CONFIG_SET_4K2K_MODE)
#include <CusSystem.h>
#endif

#include <MsRawIO.h>
#include <secure/MsSecureBoot.h>
#include <MsSystem.h>
#include <MsMmap.h>
#include <MsApiSpi.h>
#if defined (CONFIG_R2_BRINGUP)
#if defined (CONFIG_SECURITY_BOOT)
#if defined (CONFIG_NCONFIG_STORE_IN_SPI_FLASH)
#include <MsApiSpi.h>
#elif defined (CONFIG_NCONFIG_STORE_IN_NAND_FLASH)
//wait for implement
#elif defined (CONFIG_NCONFIG_STORE_IN_EMMC_FLASH)
#include <MsMmc.h>
#else
#error "please set the correct security storage!!\n"
#endif //#if defined (CONFIG_NCONFIG_STORE_IN_SPI_FLASH)
#endif //#if defined (CONFIG_SECURITY_BOOT)
#endif //#if (CONFIG_R2_BRINGUP)

#if defined (CONFIG_SECURITY_BOOT)
#include <MsSecureBoot.h>
#include <crypto_auth.h>
#endif

#if CONFIG_RESCUE_ENV  && CONFIG_RESCUE_ENV_IR_TRIGGER
#include <MsSystem.h>
#endif

#if CONFIG_AUTO_USB_UPGRADE
#include <msAPI_Power.h>
#endif
#include <MsUtility.h>
#include <CusConfig.h>
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define ENV_UPGRADE_COMPLETE        "MstarUpgrade_complete"
#define ENV_UPGRADE_MODE            "upgrade_mode"
#define ENV_FORCE_UPGRADE           "force_upgrade"
#define ENV_TEE_DEBUG_LEVEL          "teeDebugLevel"

#if defined (CONFIG_R2_BRINGUP)
#if defined (CONFIG_NCONFIG_STORE_IN_SPI_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_SPI
#define FLASH_DEFAULT_PARTITION SPI_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME SPI_DEFAULT_VOLUME
#define SECTOR_SIZE   0x10000 //64KBytes
#elif defined (CONFIG_NCONFIG_STORE_IN_NAND_FLASH)
extern  int ubi_get_volume_size(char *, size_t* );
extern int ubi_get_leb_size(void);
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_NAND
#define FLASH_DEFAULT_PARTITION NAND_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME NAND_DEFAULT_VOLUME
#define SECTOR_SIZE   ubi_get_leb_size()
#define SECURE_INFOR_BACK_OFFSET 1 // unit is sectore, so the total offset is 128*512=64KBytes
#elif defined  (CONFIG_NCONFIG_STORE_IN_EMMC_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_MMC
#define FLASH_DEFAULT_PARTITION MMC_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME MMC_DEFAULT_VOLUME
#define SECTOR_SIZE   0x200 //512Bytes
#define SECURE_INFOR_BACK_OFFSET 128 // unit is sectore, so the total offset is 128*512=64KBytes
#else
#error "please set the correct security storage!!\n"
#endif
#endif //#if defined (CONFIG_R2_BRINGUP)

#define NUTTX_HEADER_LEN 0x80
#define ALIGN_BYTES 16
#define FOUR_BIT_SHIFT 4
#define HW_AES_ADDR "E_MMAP_ID_HW_AES_BUF"
#define NUTTX_ADDR "E_MMAP_ID_NUTTX_MEM"


typedef struct
{
    U32 Length;
    U32 Offset;
}ST_HEADER_INFO;

typedef struct
{
    ST_HEADER_INFO stSignature;
    ST_HEADER_INFO stConfig;
}ST_SIGN_CONFIG;

typedef enum
{
    EN_TEE_DEBUG_LEVEL_DISABLE=0,
    EN_TEE_DEBUG_LEVEL_ERROR=0x01,
    EN_TEE_DEBUG_LEVEL_INFO=0x02,
    EN_TEE_DEBUG_LEVEL_TRACE=0x04,
    EN_TEE_DEBUG_LEVEL_DEBUG=0x08,
    EN_TEE_DEBUG_LEVEL_DEBUG_L2=0x10,
    EN_TEE_DEBUG_LEVEL_INVALID,
    EN_TEE_DEBUG_LEVEL_MAX=EN_TEE_DEBUG_LEVEL_INVALID
}EN_TEE_DEBUG_LEVEL;

#define NUTTX_BOOT_CONFIG_SIZE 0x1000
#define TEE_BOOT_CONFIG_ID "TEE_BOOT_CONFIG"
typedef struct
{
    U8  u8BootConfigID[16];
    EN_TEE_DEBUG_LEVEL  enDebugLevel;
    U8  u8FastBootMode;
    U8  u8Reserved[64];
}ST_TEE_BOOT_CONFIG;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
U32 gu32TeeBootConfigAddr=0;
U32 gu32TeeHandShakeAddr=0;

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if defined (CONFIG_R2_BRINGUP)
static char* pNuttxAlignMallocAddr=NULL;
static char* pNuttxOriMallocAddr=NULL;
static int NuttxAlignSize=0;

#endif
static EN_BOOT_MODE stBootMode = EN_BOOT_MODE_UNKNOWN;


#define _PA2VA(x)   (MS_U32)MsOS_PA2KSEG0((x))
#define _PA2NVA(x)  (MS_U32)MsOS_PA2KSEG1((x))
#define _VA2PA(x)   (MS_U32)MsOS_VA2PA((x))

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);
extern void Chip_Flush_Memory(void);
//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
int get_nconfig_offset(unsigned int *u32NConfigOffset,unsigned int *u32NConfigBakOffset);
int NConfigSave(U8* pBufferAddr, U32 u32NConfigLen);
int NConfigLoad(U32 u32HwAesVABufAddr);
int LoadNConfig(U32 u32HwAesVABufAddr);
int get_nconfig_size(unsigned int *u32NConfigSize);

//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------

int boot_mode_recovery(void)
{
    int ret = -1;
    char *s = NULL;
    char cmd[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
    s = getenv("recoverycmd");
    if ((s == NULL) || (strncmp(s, BOOT_COMMAND, 4) != 0))
    {
        snprintf(cmd, sizeof(cmd)-1, BOOT_COMMAND);
    }
    else
    {
        snprintf(cmd, sizeof(cmd)-1, s);
    }

#if defined (CONFIG_URSA_6M40) && defined(CONFIG_SET_4K2K_MODE)
    Set_4K2K_OP0();
#endif
    ret = run_command(cmd, 0);
    if(ret!=0)
    {
        UBOOT_ERROR("recovery command fail!!\n");
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }
    return ret;
}

#define ENABLE_MODULE_ENV_BOOT 1
#if (ENABLE_MODULE_ENV_BOOT == 1)
EN_BOOT_MODE get_boot_mode_from_env(void)
{
    char *buffer = NULL;
    char ret = EN_BOOT_MODE_NORMAL;
    char *cUpgradeComplete = getenv(ENV_UPGRADE_COMPLETE);
    char *cUpgradeMode = getenv(ENV_UPGRADE_MODE);
    ulong ulComplete = 0;
    UBOOT_TRACE("IN\n");

    buffer = (char*) malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }

    if(cUpgradeMode == NULL)
    {
        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "setenv %s null;saveenv", ENV_UPGRADE_MODE);
        if(run_command(buffer, 0)!=0)
        {
          UBOOT_ERROR("cmd[%s] fail!!\n",buffer);
        }
    }

    if(cUpgradeComplete == NULL)
    {
        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "setenv %s 0;saveenv", ENV_UPGRADE_COMPLETE);
        if(run_command(buffer, 0)!=0)
        {
          UBOOT_ERROR("cmd[%s] fail!!\n",buffer);
        }
    }

    if(cUpgradeComplete != NULL)
    ulComplete = simple_strtoul (cUpgradeComplete, NULL, 10);

    if(ulComplete == 0)
    {
        if(strncmp(cUpgradeMode, "usb",3) == 0)
        {
            ret = EN_BOOT_MODE_USB_UPGRADE;
        }
#if CONFIG_MINIUBOOT
#else
        else if(strncmp(cUpgradeMode, "oad",3) == 0)
        {
            ret = EN_BOOT_MODE_OAD_UPGRADE;
        }
        else if(strncmp(cUpgradeMode, "net",3) == 0)
        {
            ret = EN_BOOT_MODE_NET_UPGRADE;
        }
#endif
#if (ENABLE_MODULE_ENV_UPGRADE_FROM_BANK == 1)
        else if(strncmp(cUpgradeMode, "env",3) == 0)
        {
            ret = EN_BOOT_MODE_ENV_UPGRADE;
        }
#endif
    }
    else
    {
        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "setenv %s 0", ENV_UPGRADE_COMPLETE);
        run_command(buffer, 0);  // run_command("setenv MstarUpgrade_complete 0");
        run_command("saveenv", 0);
        UBOOT_DEBUG("last upgrade complete\n");
    }
    free(buffer);
    UBOOT_TRACE("OK\n");
    return ret;
}
#endif

#if (ENABLE_MODULE_BOOT_IR == 1)
EN_BOOT_MODE get_boot_mode_from_ir(void)
{
    U8 IRKey=0xFF;
    U8 IRFlag;
#if CONFIG_RESCUE_ENV && CONFIG_RESCUE_ENV_IR_TRIGGER
    U8 u8IRKeyPrev=0, u8KeyCheckCnt=0;
    U32 u32FirstTime = 0;
    const U32 BRICK_TERMINATOR_IR_TIMEOUT = 3000;
    const U8 BRICK_TERMINATOR_IR_CHECK_CNT = IR_BRICK_TERMINATOR_RECOVERY_KEY_REPEAT_REQUIRED;
#endif
    EN_BOOT_MODE mode = EN_BOOT_MODE_UNKNOWN;
    UBOOT_TRACE("IN\n");
    //IRKey = MDrv_ReadByte(0x3DA9); // get IR code
    extern BOOLEAN msIR_GetIRKeyCode(U8 *pkey, U8 *pu8flag);
    msIR_GetIRKeyCode(&IRKey,&IRFlag);
#if CONFIG_RESCUE_ENV && CONFIG_RESCUE_ENV_IR_TRIGGER
    u8IRKeyPrev = IRKey;
    u32FirstTime = MsOS_GetSystemTime();
#endif
    printf("fore uup IRKey [0x%x]\n",IRKey);
    switch(IRKey) // NOTE: read IR Key to decide what boot mode to go
    {
#if CONFIG_RESCUE_ENV && CONFIG_RESCUE_ENV_IR_TRIGGER
        case IR_BRICK_TERMINATOR_RECOVERY_KEY1:
        case IR_BRICK_TERMINATOR_RECOVERY_KEY2:
            {
                while(1)
                {
                    u32FirstTime = MsOS_GetSystemTime();
                    msIR_GetIRKeyCode(&IRKey,&IRFlag);
                    if((0xFF!=IRKey) && (u8IRKeyPrev!=IRKey))
                    {
                        printf("fore uup IRKey [0x%x] cnt: %u, at %d\n", IRKey, u8KeyCheckCnt, __LINE__);
                        u8KeyCheckCnt+=1;
                        if(BRICK_TERMINATOR_IR_CHECK_CNT <= u8KeyCheckCnt)
                        {
                            mode = EN_BOOT_MODE_BRICK_TERMINATOR;
                            break;
                        }
                        u8IRKeyPrev = IRKey;
                    }
                    if(BRICK_TERMINATOR_IR_TIMEOUT < MsOS_Timer_DiffTimeFromNow(u32FirstTime))
                    {
                        printf("%s: TIMEOUT, at %d\n", __func__, __LINE__);
                        break;
                    }
                    udelay(5000);
                }
            }
            break;
#endif
        case IR_RECOVERY_KEY:
            mode = EN_BOOT_MODE_RECOVERY;
            break;
        case IR_UPGRADEUSBOTA_KEY:
            mode = EN_BOOT_MODE_OTA_UPGRADE;
            break;
        case IR_FORCEUGRADE_KEY:
            mode = EN_BOOT_MODE_USB_UPGRADE;
            break;
        case IR_UPGRADEBOOTLOADER_KEY:
            mode = EN_BOOT_MODE_USB_RECOVRY_UPGRADE;
            break;
        case IR_RECOVERYWIPEDATA_KEY:
            mode = EN_BOOT_MODE_RECOVRY_WIPE_DATA;
            break;
        case IR_RECOVERYWIPECACHE_KEY:
            mode = EN_BOOT_MODE_RECOVRY_WIPE_CACHE;
            break;
        default:
            mode = EN_BOOT_MODE_UNKNOWN;
            break;
    }
    UBOOT_TRACE("OK\n");
    return mode;
}
#endif

#if (ENABLE_MODULE_ANDROID_BOOT == 1 )

EN_BOOT_MODE get_boot_mode_from_mtd0(void)
{
    EN_BOOT_MODE mode = EN_BOOT_MODE_UNKNOWN;
    struct bootloader_message *p_msg = NULL;
    p_msg = (struct bootloader_message*)BOOT_MODE_TMP_BUF_ADDR;
    char cmd[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
#if (ENABLE_MODULE_MMC == 1)
    snprintf(cmd, sizeof(cmd)-1, "mmc read.p 0x%08lX misc 32", (unsigned long)BOOT_MODE_TMP_BUF_ADDR);
#else
    snprintf(cmd, sizeof(cmd)-1, "nand read.e 0x%08lX misc 32", (unsigned long)BOOT_MODE_TMP_BUF_ADDR);
#endif
    if(-1 != run_command(cmd, 0))
    {

        if((strlen(p_msg->command) == strlen(BOOT_MODE_RECOVERY_STR)) && (0==strncmp(p_msg->command, BOOT_MODE_RECOVERY_STR, strlen(BOOT_MODE_RECOVERY_STR))))
        {
            mode = EN_BOOT_MODE_RECOVERY;
        }
        /*else {do nothing;}*/
    }
    else
    {
        printf("%s: '%s' fails, at %d\n", __func__, cmd, __LINE__);
    }
    UBOOT_TRACE("OK\n");
    return mode;
}

#endif


#if (ENABLE_MODULE_BOOT_KEYPAD == 1)
#include <MsUboot.h>
extern BOOLEAN msKeypad_GetKey(U8 *pkey, U8 *pflag);

EN_BOOT_MODE get_boot_mode_from_keypad(void)
{
     U8 u8KeyPad_KeyVal=0xFF;
	 U8 u8KeyPad_RepFlag = 0;
     EN_BOOT_MODE mode = EN_BOOT_MODE_UNKNOWN;
     UBOOT_TRACE("IN\n");
     #if (ENABLE_MODULE_BOOT_COMBINE_RECOVERY_KEYPAD == 1)
     // check combination key to enter recovery mode
     // REG_SAR3 : SAR3 register,0x141D
     U8 u8adcValue = MDrv_ReadByte(REG_SAR3);
     UBOOT_DEBUG("adc value :0x%x\n",u8adcValue);
     if(u8adcValue >= COMBINATION_KEY_RECOVERY_ADC_LOW && \
        u8adcValue <= COMBINATION_KEY_RECOVERY_ADC_HIGH)
     {
         UBOOT_DEBUG("adc is in section ,enter recovery mode\n");
         mode = EN_BOOT_MODE_RECOVERY;
         UBOOT_TRACE("OK\n");
         return mode;
     }
     #endif
     msKeypad_GetKey(&u8KeyPad_KeyVal,&u8KeyPad_RepFlag);
     UBOOT_DEBUG("fore uup u8KeyPad_KeyVal [0x%x]\n",u8KeyPad_KeyVal);
     switch(u8KeyPad_KeyVal) // NOTE: read IR Key to decide what boot mode to go
    {
        #if (ENABLE_MODULE_BOOT_COMBINE_RECOVERY_KEYPAD == 0)
        case KEYPAD_RECOVERY_KEY:
            mode =EN_BOOT_MODE_RECOVERY;
            break;
        #endif
        case KEYPAD_FORCEUGRADE_KEY:
            mode =EN_BOOT_MODE_USB_UPGRADE;
            break;
		case KEYPAD_UART_DEBUG_KEY:
			mode = EN_BOOT_MODE_UART_DEBUG;
			break;
        #if (ENABLE_MODULE_SYSTEM_RESTORE == 1)
        case KEYPAD_SYSTEM_RESTORE_KEY:
            mode = EN_BOOT_MODE_SYSTEM_RESTORE;
            break;
        #endif
        default:
            mode = EN_BOOT_MODE_UNKNOWN;
            break;
    }
     UBOOT_TRACE("OK\n");
     return mode;
}
#endif

#if CONFIG_MINIUBOOT
extern int appInitUsbDisk(void);
#endif

#if (ENABLE_MODULE_ANDROID_BOOT == 1 )
// set boot to Recovery mode flag
static void setBootToRecovery(void)
{
    stBootMode = EN_BOOT_MODE_RECOVERY;
}
#endif

// check if boot to Recovery mode
// must call it after bootcheck command
int isBootToRecovery(void)
{
    if(EN_BOOT_MODE_RECOVERY == stBootMode)
    {
	    UBOOT_DEBUG("boot to recovery mode\n");
        return 1;
    }
	else
	{
	    UBOOT_DEBUG("boot to normal mode\n");
	    return 0;
	}
}

#if ENABLE_BOOT_SPI_ECOS
#define STB_UBOOT_INFO_ADDR     0x20000
#define STB_INFO_SIZE           0x400//1024B//0x20000

void Big2LittleEndian(U8* addr,U8* data)
{

    U8 * tmp = NULL;
	tmp = (U8 *)(data);
    *tmp = *(addr+3);
	*(tmp+1) = *(addr+2);
	*(tmp+2) = *(addr+1);
	*(tmp+3) = *(addr);
    UBOOT_DEBUG("\n*(addr) 0x%x\n",*addr);
}

int do_read_boot_info(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char buffer[256];
    U8 *pTemp;
    U32 u32AppMagicFlag;
    U32 u32AppFileLen;
    U32 u32AppDramAddr;
    U32 u32AppRestAddr;
    U32 u32AppSPIAddr;
    U32 u32LzmaBufAddr;
    U32 u32LzmaDecBufAddr;
    U32 u32UbootInfoAddr = 0;
    int ret;
    int ch = 0;

    if (tstc())
    {   /* we got a key press   */
        ch = getc();  /* consume input  */
        puts ("\b\b\b 0");
        if (ch == 0x1B)//when esc,upgrade flash_usb_auto.bin
        {
            if (-1 == appInitUsbDisk())
            {
               UBOOT_ERROR("FAIL : can not init usb!! \n");
               return -1;
            }

            sprintf(buffer, "ustar /flash_usb_auto.bin");
            UBOOT_DEBUG("cmd=%s\n", buffer);
            if(-1 == run_command(buffer, 0))
            {
                UBOOT_ERROR("USB auto upgrade fail!\n");
                return -1;
            }

            run_command("reset",0);
        }
    }

    memset(buffer, 0 , 256);
    sprintf(buffer,"spi_rdc 0x80B00000 0x%x 0x%x", STB_UBOOT_INFO_ADDR, STB_INFO_SIZE);
    UBOOT_INFO("%s\n", buffer);

    ret = run_command(buffer, 0);
    if (ret!=0)
    {
        UBOOT_ERROR("cmd %s failed\n", buffer);
        return FALSE;
    }
    else
    {
        UBOOT_DEBUG("cmd %s success\n", buffer);
    }

#if (CONFIG_DISPLAY_LOGO == 1)
    pTemp = (U8 *)((U32)0x80B00000);
    pTemp += 0x20;//uboot rom end addr stored here
	u32UbootInfoAddr = *((U32 *) pTemp);

    UBOOT_DEBUG("u32UbootInfoAddr: 0x%x\n", u32UbootInfoAddr);
	pTemp += 0x4;
	u32UbootInfoAddr +=*((U32 *) pTemp);

    UBOOT_DEBUG("u32UbootInfoAddr1: 0x%x\n", u32UbootInfoAddr);
#else
    pTemp = (U8 *)((U32)0x80B00000);
    pTemp += 0xc;//uboot rom end addr stored here

    UBOOT_DEBUG("u32UbootInfoAddr: 0x%x\n", u32UbootInfoAddr);
	u32UbootInfoAddr = *((U32 *) pTemp);
    UBOOT_DEBUG("u32UbootInfoAddr1: 0x%x\n", u32UbootInfoAddr);
    u32UbootInfoAddr &= 0x000fffff;//get offest of 0xBFCxxxxx
    UBOOT_DEBUG("u32UbootInfoAddr: 0x%x\n", u32UbootInfoAddr);
#endif

    u32UbootInfoAddr = u32UbootInfoAddr + 65536;
    u32UbootInfoAddr = u32UbootInfoAddr/65536;
	u32UbootInfoAddr = u32UbootInfoAddr*65536;

    UBOOT_DEBUG("BOOT_INFO_ADDR: 0x%x\n", u32UbootInfoAddr);

    memset(buffer, 0 , 256);
    sprintf(buffer,"spi_rdc 0x80B00000 0x%x 0x%x", u32UbootInfoAddr, STB_INFO_SIZE);
    UBOOT_INFO("%s\n", buffer);

    ret = run_command(buffer, 0);

    if (ret!=0)
    {
        UBOOT_ERROR("cmd %s failed\n", buffer);
        return FALSE;
    }
    else
    {
        UBOOT_DEBUG("cmd %s success\n", buffer);
    }

    pTemp = (U8 *)((U32)0x80B00000);

    if (*((U32*)pTemp) == 0xefbeadde)
    {
       u32AppMagicFlag = 0xDEADBEEF;
    }
    Big2LittleEndian(pTemp,(U8*)(&u32AppMagicFlag));

    if (u32AppMagicFlag != 0xDEADBEEF)
    {
        UBOOT_ERROR("AppMagicFlag ERROR !!\n");
        return FALSE;
    }
	else
	{
        UBOOT_DEBUG("AppMagicFlag Correct !!\n");

	}
    UBOOT_DEBUG("\n*(pTemp +4) 0x%x\n",*(U32*)(pTemp +4));//printf just print 4 bytes in order
    Big2LittleEndian((U8 *)(pTemp +4),(U8 *) &u32AppFileLen);
    UBOOT_DEBUG("\nu32AppFileLen 0x%x\n", u32AppFileLen);

    // u32AppRestAddr
    Big2LittleEndian((U8 * )(pTemp +12),(U8 *) &u32AppRestAddr);
	Big2LittleEndian((U8 * )(pTemp +8),(U8 *) &u32AppDramAddr);
	UBOOT_DEBUG("\nu32AppDramAddr 0x%x\n",u32AppDramAddr);

    // u32AppSPIAddr
    u32AppSPIAddr = 0;
    Big2LittleEndian((U8 *)(pTemp +16),(U8 *) &u32AppSPIAddr);
	UBOOT_DEBUG("\nu32AppSPIAddr 0x%x\n", u32AppSPIAddr);

    // u32LzmaBufAddr
    u32LzmaBufAddr = 0;
	Big2LittleEndian((U8 *)(pTemp +20),(U8 *) &u32LzmaBufAddr);
	UBOOT_DEBUG("\nu32AppFileLen 0x%x\n", u32LzmaBufAddr);

    // u32LzmaDecBufAddr
    u32LzmaDecBufAddr = 0;
    Big2LittleEndian((U8 *)(pTemp +24),(U8 *) &u32LzmaDecBufAddr);
	UBOOT_DEBUG("\nu32AppFileLen 0x%x\n", u32LzmaDecBufAddr);

    memset(buffer, 0 , 256);

    //u32AppFileLen = 0x300000;
    sprintf(buffer, "setenv bootcmd ' usb exit;spi_rdc 0x%x 0x%x 0x%x; LzmaDec 0x%x 0x%x 0x%x 0x%x; go 0x%x;",u32LzmaBufAddr,u32AppSPIAddr,u32AppFileLen,u32LzmaBufAddr,u32AppFileLen,u32AppDramAddr,u32LzmaDecBufAddr,u32AppRestAddr);
    UBOOT_INFO("%s\n", buffer);

    ret = run_command (buffer, 0);
    if (ret != 0)
    {
        UBOOT_ERROR("cmd %s failed\n", buffer);
        return FALSE;
    }
    else
    {
        UBOOT_DEBUG("cmd %s success\n", buffer);
    }

    memset(buffer, 0 , 256);
    sprintf(buffer, "saveenv");

    ret = run_command (buffer, 0);
    if (ret!=0)
    {
        UBOOT_ERROR("cmd %s failed\n", buffer);
        return FALSE;
    }
    else
    {
        UBOOT_DEBUG("cmd %s success\n", buffer);
    }

    return TRUE;
}
#endif

int do_bootcheck (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
     int ret=0;
     EN_BOOT_MODE BootMode;
     BOOLEAN BootFlag;
     BootMode = EN_BOOT_MODE_UNKNOWN;
     BootFlag=0; // decide the boot mode

    UBOOT_TRACE("IN\n");

#if (ENABLE_AUTO_USB_UPGRADE == 1)
    #if (ENABLE_AUTO_USB_UPGRADE_AC == 1)
        if (msAPI_Power_QueryPowerOnMode() == EN_POWER_AC_BOOT)
    #endif
        {
            char *cUpgradeComplete = getenv(ENV_UPGRADE_COMPLETE);
            if((cUpgradeComplete == NULL) || (0 == strcmp(cUpgradeComplete, "0")))
            {
                //bootmode via AC ON
                run_command("custar", 0);
            }
        }
#endif

#if (ENABLE_MODULE_BOOT_IR == 1)
     if(BootFlag == 0)
     {
        BootMode =get_boot_mode_from_ir();
        if(BootMode!=EN_BOOT_MODE_UNKNOWN)
        {
            //bootmode via IR
            BootFlag=1;
        }
     }
#endif

#if (ENABLE_MODULE_BOOT_KEYPAD == 1)
     if(BootFlag == 0)
     {
        BootMode =get_boot_mode_from_keypad();
        if(BootMode!=EN_BOOT_MODE_UNKNOWN)
        {
            //BootMode via KEYPAD
            BootFlag=1;
        }
     }
#endif

#if (ENABLE_MODULE_ANDROID_BOOT == 1)
    // NOTE: read BCB in mtd0 (misc) to decide what boot mode to go
    if(BootFlag == 0)
    {
        BootMode=get_boot_mode_from_mtd0();
        if(BootMode!=EN_BOOT_MODE_UNKNOWN)
        {
            //BootMode via MTD
            BootFlag=1;
        }
    }
#endif

#if (ENABLE_MODULE_ENV_BOOT == 1)
    if(BootFlag == 0)
    {
        BootMode=get_boot_mode_from_env();
    }

    char* force_upgrade = getenv(ENV_FORCE_UPGRADE);
    if(force_upgrade)
    {
        int force_flag = simple_strtoul(force_upgrade,NULL,16);
        if((force_flag <= 0x0F)&&(force_flag > 0x00))
        {
           //last time force upgrade not finish,so continue upgrading
            BootMode = EN_BOOT_MODE_USB_UPGRADE;
        }
    }
#endif
#if (ENABLE_MODULE_ANDROID_BOOT == 1 ) || (ENABLE_MODULE_BOOT_IR == 1)
    int recovery_mode = 0;
#if CONFIG_RESCUE_ENV && CONFIG_RESCUE_ENV_IR_TRIGGER
    int brick_terminator_recover_mode = 0;
#endif
#endif
    switch(BootMode)
    {
#if CONFIG_RESCUE_ENV && CONFIG_RESCUE_ENV_IR_TRIGGER
        case EN_BOOT_MODE_BRICK_TERMINATOR:
            brick_terminator_recover_mode = 1;
            break;
#endif
#if (ENABLE_MODULE_ANDROID_BOOT == 1 )
        case EN_BOOT_MODE_RECOVERY:
            recovery_mode = 1;
            break;
        case EN_BOOT_MODE_RECOVRY_WIPE_DATA:
            run_command("recovery_wipe_partition data",0);
            recovery_mode = 1;
            break;
        case EN_BOOT_MODE_RECOVRY_WIPE_CACHE:
            run_command("recovery_wipe_partition cache",0);
            recovery_mode = 1;
            break;
        #if (ENABLE_MODULE_SYSTEM_RESTORE == 1)
        case EN_BOOT_MODE_SYSTEM_RESTORE:
            ret = run_command("SystemRestore",0);
            recovery_mode = 1;
            break;
        #endif
#endif
        #if (ENABLE_MODULE_USB == 1)
        case EN_BOOT_MODE_USB_UPGRADE:
			#ifdef CONFIG_MSTAR_NUGGET
			console_init();   //Open Uart when upgrade
			#endif
#if CONFIG_MINIUBOOT
            appInitUsbDisk();
            ret = run_command("ustar",0);//usb upgrade
#else
            ret = run_command("custar",0);//usb upgrade
#endif
            break;
#if CONFIG_MINIUBOOT
#else
#if (ENABLE_MODULE_BOOT_IR == 1)
        case EN_BOOT_MODE_OTA_UPGRADE:
            ret = run_command("ota_zip_check",0);//ota upgrade
            if (ret != -1)
            {
                recovery_mode = 1;
            }
            break;
        case EN_BOOT_MODE_USB_RECOVRY_UPGRADE:
            ret = run_command("usb_bin_check",0);//usb upgrade
            if(ret == 0)
            {
                break;
            }
            ret = run_command("ota_zip_check",0);//ota upgrade
            if (ret != -1)
            {
                recovery_mode = 1;
            }
            break;
#endif
#endif
        #endif
        #if (ENABLE_MODULE_OAD == 1)
        case EN_BOOT_MODE_OAD_UPGRADE:
            ret = run_command("costar",0);//oad upgrade
            break;
        #endif
        #if (ENABLE_MODULE_ENV_UPGRADE_FROM_BANK == 1)
        case EN_BOOT_MODE_ENV_UPGRADE:
            ret = run_command("rstar",0);
        #endif
        #if (ENABLE_MODULE_NETUPDATE == 1)
        case EN_BOOT_MODE_NET_UPGRADE:
            ret = run_command("cnstar",0);//net upgrade
            break;
        #endif
		case EN_BOOT_MODE_UART_DEBUG:
			ret = run_command("setenv UARTOnOff on", 0);
			ret = run_command("saveenv", 0);
			printf("Opening UART now\n");
			break;
        case EN_BOOT_MODE_NORMAL:
            break;
        default:
            //normal booting according bootcmd in main.c
            UBOOT_DEBUG("non available case\n");
            break;
    }
#if (ENABLE_MODULE_ANDROID_BOOT == 1 )
    if( 1 == recovery_mode ){
        setBootToRecovery();
        run_command("panel_pre_init",0);
		#if defined(CONFIG_ENABLE_4K2K_PANEL)
        #if defined(CONFIG_INX_NOVA_VB1)
        run_command("inx_panel_set_init", 0);
        #endif
        #endif
        #if(ENABLE_CVBS_OUT==1)
            run_command ("cvbs" , 0);
        #endif
        #if(ENABLE_HDMI_TX == 1)
        run_command("hdmi init",0);
        #endif
        #if (CONFIG_ENABLE_RTPM)
        run_command ("runtime_pm" , 0);
        #endif
		#if defined (CONFIG_URSA_6M40)
        run_command("ursa_lvds_on", 0);
        #endif
        #if defined (CONFIG_URSA_8)
        run_command("ursa8_lvds_on", 0);
        #endif
        #if defined (CONFIG_URSA6_VB1)
        run_command("send_I2C_cmd_to_ursa6", 0);
        #endif
        run_command("bootlogo 0 0 1 1 boot_recovery.jpg", 0);
        #if defined(CONFIG_INX_VB1) && defined(CONFIG_BOOTLOGO_4K2K)
        run_command("panel_inx_vb1_init", 0);
        #endif
        ret = boot_mode_recovery();
    }
#endif
#if CONFIG_RESCUE_ENV && CONFIG_RESCUE_ENV_IR_TRIGGER
    if(1 == brick_terminator_recover_mode)
    {
        run_command("BrickTerminator force_recover",0);
#if ((CONFIG_RESCUE_ENV_IR_TRIGGER) && (1 != CONFIG_RESCUE_ENV_AUTO_TRIGGER))
        setenv(BRICK_TERMINATOR_IR_TRIGGERED_STRING, "1");
        saveenv();
#endif
    }
#endif
    UBOOT_TRACE("OK\n");
    return ret;
}

#if defined (CONFIG_R2_BRINGUP)
#include "drvSERFLASH.h" //for flash copy fw from flash to dram
#include "drvBDMA.h" //for bdma copy fw from flash to dram

#if defined(__ARM__)
static MS_U32 _gMIO_MapBase = 0x1F000000;
#else
static MS_U32 _gMIO_MapBase = 0xBF000000;
#endif

#define UART_DBG_FRCR2  0x00 //A5
#define UART_DBG_UART0  0x04
#if defined(CONFIG_MSTAR_KAISER)
#define UART_DBG_SECR2  0x00
#else
#define UART_DBG_SECR2  0x0D
#endif
#define UART_DBG_OTHER  UART_DBG_UART0

#define UART_DBG_SRC    UART_DBG_SECR2
#if defined(CONFIG_MSTAR_KAISER)
#define REG_R2_BASE                     0x103500
#define REG_PM_SLEEP		0x000E00
#else
#define REG_R2_BASE			0x122A00
#endif
#if defined(CONFIG_MSTAR_CLIPPERS ) || defined(CONFIG_MSTAR_MONACO ) || defined(CONFIG_MSTAR_MADISON )|| defined(CONFIG_MSTAR_EDISON )|| defined(CONFIG_MSTAR_EIFFEL) || defined(CONFIG_MSTAR_NUGGET) || defined(CONFIG_MSTAR_EINSTEIN)|| defined(CONFIG_MSTAR_NAPOLI)
#define REG_R2_MAU0 			0x122B00
#elif defined(CONFIG_MSTAR_KAISER)
#define REG_R2_MAU0 			0x103600
#endif

#if defined(CONFIG_MSTAR_MONACO )
#define REG_R2_MAU1     0x163900

#endif

MS_U8 _ReadByte(MS_U32 u32RegAddr)
{
    return ((volatile MS_U8*)(_gMIO_MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)];
}

MS_U16 _Read2Byte(MS_U32 u32RegAddr)
{
    return ((volatile MS_U16*)(_gMIO_MapBase))[u32RegAddr];
}

MS_U32 _Read4Byte(MS_U32 u32RegAddr)
{
    return (_Read2Byte(u32RegAddr) | _Read2Byte(u32RegAddr+2) << 16);
}

MS_BOOL _WriteByte(MS_U32 u32RegAddr, MS_U8 u8Val)
{
    if (!u32RegAddr)
    {
        return FALSE;
    }
    ((volatile MS_U8*)(_gMIO_MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)] = u8Val;
    return TRUE;
}

MS_BOOL _Write2Byte(MS_U32 u32RegAddr, MS_U16 u16Val)
{
    if (!u32RegAddr)
    {
        return FALSE;
    }

    ((volatile MS_U16*)(_gMIO_MapBase))[u32RegAddr] = u16Val;
    return TRUE;
}

MS_BOOL _Write4Byte(MS_U32 u32RegAddr, MS_U32 u32Val)
{
    if (!u32RegAddr)
    {
        return FALSE;
    }

    _Write2Byte(u32RegAddr, u32Val & 0x0000FFFF);
    _Write2Byte(u32RegAddr+2, u32Val >> 16);
    return TRUE;
}

MS_BOOL _WriteRegBit(MS_U32 u32RegAddr, MS_U8 u8Mask, MS_BOOL bEnable)
{
    MS_U8 u8Val = _ReadByte(u32RegAddr);
    if (!u32RegAddr)
    {
        return FALSE;
    }

    u8Val = _ReadByte(u32RegAddr);
    u8Val = (bEnable) ? (u8Val | u8Mask) : (u8Val & ~u8Mask);
    _WriteByte(u32RegAddr, u8Val);
    return TRUE;
}


void MApi_R2_FwCopy(MS_U32 u32FlashAddr, MS_U32 u32DramAddr, MS_U32 u32Len)
{
	printf("Copy R2 Fw from Flash 0x%08x to Ram 0x%08x, len = 0x%08x ... ",
		(unsigned int)u32FlashAddr, (unsigned int)u32DramAddr, (unsigned int)u32Len);

	MDrv_BDMA_SetDbgLevel(E_BDMA_DBGLV_ALL);

	MDrv_BDMA_Init(0x20000000);

	MDrv_BDMA_FlashCopy2Dram((MS_PHYADDR)u32FlashAddr, (MS_PHYADDR)u32DramAddr, u32Len);

	printf("Done!\n");
}

#define SWITCH_UART_TO_R2 "uart2R2"

void MApi_Disable_R2(void)
{
	UBOOT_TRACE("IN\n");

	_WriteByte(REG_R2_BASE+0x40*2, 0x00); //disable R2

	UBOOT_TRACE("OK\n");
}

void MApi_R2_StartFrDRAM(MS_U32 addr)
{
	MS_U32 AeonBufAdr=addr;
	MS_U16 value;
    char *pEnv=NULL;
    UBOOT_TRACE("IN\n");
	UBOOT_DEBUG("R2 Boot from 0x%08x\n", (unsigned int)AeonBufAdr);

	// select UART source
	//_WriteByte(0x101EA6, UART_DBG_SRC);

    pEnv=getenv("uart2R2");
    if(pEnv!=NULL)
    {
        if(strcmp(pEnv,"1")==0)
        {
            UBOOT_DEBUG("switch uart message to uart\n");
            _WriteByte(0x101EA6, UART_DBG_SRC);
        }
    }

#if defined(CONFIG_MSTAR_KAISER)
    _Write2Byte(REG_PM_SLEEP+0x29*2, 0x2002);
#endif

//	_Write2Byte(0x101E04, 0x0400);
//	_Write2Byte(0x101EA6, 0x0D04);

	//switch UART to dig_mux (instead of MCU51)
	value = _Read2Byte(0x0E12);
#if 1//HK message
	value &= (~BIT12); //0: dig_mux (reg_uart_sel0)
	value |= BIT11; //1: enable uart rx via  PAD_DDCA for dig_mux (reg_uart_sel0)
#else //PM message
	value |= (BIT12); //1: HK MCU51 uart0
	value |= BIT11; //1: enable uart rx via  PAD_DDCA for dig_mux (reg_uart_sel0)
#endif
	_Write2Byte(0x0E12,value);


	//(1) Disable R2 -> Stop
	//_WriteByte(REG_R2_BASE+0x40*2, 0x00); //disable R2
	MApi_Disable_R2();


	//(2) Set R2 clock
	// [1:0] = 2'b00
	// [3:2] = 2'b00: 240MHz,  2'b01: 192HMz, 2'b10: 172MHz, 2'b11: 144MHz
	// Set to 240 MHz
#if defined(CONFIG_MSTAR_EDISON) || defined(CONFIG_MSTAR_EIFFEL) || defined(CONFIG_MSTAR_EINSTEIN)|| defined(CONFIG_MSTAR_NAPOLI) || defined(CONFIG_MSTAR_MONACO) || defined(CONFIG_MSTAR_CLIPPERS) || defined(CONFIG_MSTAR_MADISON)
	_WriteByte(0x10337A, 0x00);
#elif defined(CONFIG_MSTAR_NUGGET)
	_WriteByte(0x100B94, 0x00);
#elif defined(CONFIG_MSTAR_KAISER)
    _WriteByte(0x100B00+(0x2F*2), 0x1C);
    /*instaed of write bit mask*/
    _WriteByte(0x100B00+(0x7E*2), _ReadByte(0x100B00+(0x7E*2)) | BIT2);
    /*end*/
#endif

	// check MIU memory mapping
#if 0
	//(3) Set CPU SDR base
	_Write2Byte(REG_R2_BASE+0x41*2, (AeonBufAdr&0x0000FFFF)); //I Fetch Offset - Low
	_Write2Byte(REG_R2_BASE+0x42*2, (AeonBufAdr>>16)); //I Fetch Offset - High
	_Write2Byte(REG_R2_BASE+0x43*2, (AeonBufAdr&0x0000FFFF)); //D Fetch Offset - Low
	_Write2Byte(REG_R2_BASE+0x44*2, (AeonBufAdr>>16)); //D Fetch Offset - High
#else
	//(3) Set CPU reset base(vector)
        #if defined (CONFIG_NUTTX_BRINGUP_TEST)
        _Write2Byte(REG_R2_BASE+0x5A*2, 0xa20);
        #else
	_Write2Byte(REG_R2_BASE+0x5A*2, ((AeonBufAdr|R2_CACHE_ADDR)>>16)); //CPU reset base (vector)  // reset vector address 0x0(64K alignment)
        #endif
#endif


	//(4) Set UART base
	_Write2Byte(REG_R2_BASE+0x55*2, 0x9000); // UART base address
#if defined(CONFIG_MSTAR_KAISER) || defined(CONFIG_MSTAR_EDISON) || defined(CONFIG_MSTAR_EIFFEL) || defined(CONFIG_MSTAR_NUGGET)|| defined(CONFIG_MSTAR_EINSTEIN)
          //Set the size of MIU0/MIU1 (512/512)
          _Write2Byte(REG_R2_MAU0+0x01*2, 0x8300);
#elif defined(CONFIG_MSTAR_NAPOLI) || defined(CONFIG_MSTAR_MADISON)
          _Write2Byte(REG_R2_MAU0+0x01*2, 0x8500);
#elif defined(CONFIG_MSTAR_MONACO)
          _Write2Byte(REG_R2_MAU0+0x01*2, 0x8800);
          _Write2Byte(REG_R2_MAU1+0x01*2, 0x8500);
#endif



	//(5) Set IO space enable (UART, RIU) with QMEM space disabled
	_Write2Byte(REG_R2_BASE+0x58*2, 0x0003); // io_space_en[3:0]: UART,RIU, qmem_space_en[4] : disable


	//(6) CPU SW reset R2
	_Write2Byte(0x2E52, _Read2Byte(0x2E52) &(~BIT13));
	_Write2Byte(0x2E52, _Read2Byte(0x2E52) |(BIT13));

	//(7) Without QMEM
#if 0
	_Write2Byte(REG_R2_BASE+0x4E*2, 0xB000); // QMEM base address = 0x80000000
	_Write2Byte(REG_R2_BASE+0x50*2, 0xF000); // QMEM less, set DCU Decoding..
#endif


	//(8) Enable R2 -> Start
	_WriteByte(REG_R2_BASE+0x40*2, 0x24); // miu_sw_rst and sdram_boot = 1
	_WriteByte(REG_R2_BASE+0x40*2, 0x27); // sdram_boot and (miu/r2/r2_rst) =1
	UBOOT_TRACE("OK\n");
}
void SetHKtoGo(U32 address)
{
    char str[]="HK is going";
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("address=0x%x\n",address);
    memset((void *)address,0 , sizeof(str)+1);
    memcpy((void *)address,str,sizeof(str));
    UBOOT_DEBUG("Mboot Starts to go\n");

    UBOOT_TRACE("OK\n");

    return;
}

int IsSecureMemDone(U32 address)
{
	char str[]="Secure memory is done";
	char *s=NULL;
	U32 timeOut=0;
	U32 count=0;
	UBOOT_TRACE("IN\n");
	UBOOT_DEBUG("address=0x%x\n",address);
	s = getenv("timeOut");
	if(s==NULL)
	{
		timeOut=60000;//60s
	}
	else
	{
		timeOut=simple_strtoul(s, NULL, 16);
	}
	UBOOT_DEBUG("timeOut=%d(ms)\n",timeOut);


	while(1){
	        Chip_Flush_Memory();
		if(memcmp((void *)address,str,sizeof(str))==0)
		{
			UBOOT_TRACE("OK\n");
			return 0;
		}

	    //MsOS_DelayTaskUs(100);
	    MsOS_DelayTask(1);
		count++;
		if(count==timeOut){
			UBOOT_DEBUG("Time out\n");
			break;
		}
	}

	UBOOT_ERROR("fail\n");
	return -1;
}

void* AllocateNuttxbuffer(int BufSize)
{
    UBOOT_TRACE("IN\n");
    U8* pu8R2MallocAddr=NULL;
    UBOOT_DEBUG("BufSize =%x \n",BufSize);
    pu8R2MallocAddr=malloc(BufSize);
    //pu8R2MallocAddr=(U8*)((U32)((U32)pu8R2MallocAddr+16))>>4<<4;

    if(pu8R2MallocAddr==NULL)
    {
        UBOOT_ERROR("\033[0;31m malloc FAIL\033[0m\n");
        return NULL;
    }
    memset(pu8R2MallocAddr, 0, BufSize);

    UBOOT_DEBUG("pu8R2MallocAddr =%x \n",(U32)pu8R2MallocAddr);
    UBOOT_TRACE("OK\n");

    return pu8R2MallocAddr;
}

void DeAllocateNuttxbuffer(void* BufAddr)
{
    UBOOT_TRACE("IN\n");

    if(BufAddr!=NULL)
    {
        free(BufAddr);
        BufAddr=NULL;
    }

    UBOOT_TRACE("OK\n");
    return;
}

int CalculateNuttxAlignSize(char* pu8R2HeaderAddr)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    U32 NuttxSize=0;

    UBOOT_TRACE("IN\n");

    pstTeeHd=(ST_TEE_HEADER*)pu8R2HeaderAddr;
    if(memcmp(pstTeeHd->ucMagicID,TeeMagicID,strlen(TeeMagicID))==0)
    {
        UBOOT_DEBUG("pstTeeHd->_sthd.uitee_image_size =%x \n",pstTeeHd->_sthd.uitee_image_size);

        if(pstTeeHd->_sthd.uitee_image_size==0){
            UBOOT_ERROR(" error size\n");
            return 0;
        }


        if(pstTeeHd->_sthd.uitee_image_size%ALIGN_BYTES){
            NuttxSize=(((pstTeeHd->_sthd.uitee_image_size+ALIGN_BYTES)>>FOUR_BIT_SHIFT)<<FOUR_BIT_SHIFT)+NUTTX_HEADER_LEN;
        }
        else{
            NuttxSize=pstTeeHd->_sthd.uitee_image_size+NUTTX_HEADER_LEN;
        }
    }

    UBOOT_TRACE("OK\n");

    return NuttxSize;
}

U32 MoveNuttx2Dest(U32 NuttxVirtMallocAddr, U32 NuttxSize)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    unsigned long ulTempAddr = 0;
    unsigned long ulImageSize = 0;
    unsigned long ulHeaderLen = 0;
    U32 u32NuttxPhyAddr = 0;
    U32 NuttxPhyMallocAddr=0;
    UBOOT_TRACE("IN\n");

    UBOOT_DUMP(_PA2NVA(_VA2PA(NuttxVirtMallocAddr)), 0x100);

    pstTeeHd=(ST_TEE_HEADER*)NuttxVirtMallocAddr;
    UBOOT_DEBUG("NuttxVirtMallocAddr=0x%x\n",(U32)NuttxVirtMallocAddr);
    UBOOT_DEBUG("pstTeeHd->ucMagicID=%s\n",pstTeeHd->ucMagicID);

    UBOOT_DEBUG("*****compare magic id*****\n");
    if(memcmp(pstTeeHd->ucMagicID,TeeMagicID,strlen(TeeMagicID))==0)
    {
        UBOOT_DEBUG("pstTeeHd->uitee_header_len=%x\n",pstTeeHd->_sthd.uitee_header_len);
        UBOOT_DEBUG("pstTeeHd->uitee_start_paddr=0x%x\n",pstTeeHd->_sthd.uitee_start_paddr);
        UBOOT_DEBUG("pstTeeHd->uitee_start_vaddr=0x%x\n",pstTeeHd->_sthd.uitee_start_vaddr);
        UBOOT_DEBUG("pstTeeHd->uitee_image_size=0x%x\n",pstTeeHd->_sthd.uitee_image_size);
        UBOOT_DEBUG("pstTeeHd->ulltime=%llx\n",pstTeeHd->_sthd.ulltime);
        UBOOT_DEBUG("pstTeeHd->ullTeeBinVersion=%llx\n",pstTeeHd->_sthd.ullTeeBinVersion);
        UBOOT_DEBUG("pstTeeHd->uiHeaderVersion=%d\n",pstTeeHd->_sthd.uiHeaderVersion);
        UBOOT_DEBUG("pstTeeHd->uicrc_value=%d\n",pstTeeHd->_sthd.uicrc_value);

        if((pstTeeHd->_sthd.uitee_start_paddr==0)&&(pstTeeHd->_sthd.uitee_start_vaddr==0)&&(pstTeeHd->_sthd.uitee_image_size==0))
        {
            UBOOT_ERROR("header info in wrong, please check again");
            return 0;
        }

        ulTempAddr = pstTeeHd->_sthd.uitee_start_paddr;
        ulImageSize = pstTeeHd->_sthd.uitee_image_size;
        ulHeaderLen = pstTeeHd->_sthd.uitee_header_len;
        u32NuttxPhyAddr = _VA2PA(NuttxVirtMallocAddr);
        UBOOT_DEBUG("u32NuttxPhyAddr=%x\n",u32NuttxPhyAddr);

        UBOOT_DUMP(_PA2NVA(_VA2PA(NuttxVirtMallocAddr)), 0x100);
        //UBOOT_DUMP((unsigned long)((u32R2BaseAddr|CONFIG_MIU0_BUSADDR|0x20000000)+ulImageSize+0x80-0x200), 0x200);

        UBOOT_DEBUG("*****MDrv_BDMA_MemCopy*****\n");
        MDrv_BDMA_MemCopy((U32)u32NuttxPhyAddr+ulHeaderLen, ulTempAddr, ulImageSize);

        u32NuttxPhyAddr=ulTempAddr;
        UBOOT_DEBUG("phdinfo->ultee_start_paddr=%x\n",pstTeeHd->_sthd.uitee_start_paddr);
        UBOOT_DEBUG("u32R2PhyAddr=%x\n",u32NuttxPhyAddr);
        UBOOT_DEBUG("_PA2NVA(u32R2PhyAddr)=%lx\n",_PA2NVA(u32NuttxPhyAddr));

        UBOOT_DEBUG("*****_PA2VA(u32NuttxPhyAddr) =%lx*****\n",_PA2VA(u32NuttxPhyAddr));
        UBOOT_DUMP((_PA2VA(u32NuttxPhyAddr+0x100)), 0x110);
        UBOOT_DEBUG("*****_PA2NVA(u32NuttxPhyAddr) =%lx*****\n",_PA2NVA(u32NuttxPhyAddr));
        UBOOT_DUMP((_PA2NVA(u32NuttxPhyAddr+0x100)), 0x110);
        //UBOOT_DUMP((unsigned long)((u32NuttxPhyAddr|CONFIG_MIU0_BUSADDR|0x20000000)+ulImageSize-0x100), 0x100);
    }
    else
    {
        UBOOT_DEBUG("*****Without Header*****\n");
        u32NuttxPhyAddr = _VA2PA(NuttxVirtMallocAddr);
        UBOOT_DEBUG("TempPhyAddr=%x\n",NuttxPhyMallocAddr);

        get_addr_from_mmap(NUTTX_ADDR, &u32NuttxPhyAddr);
        //get_length_from_mmap(NUTTX_ADDR, &u32NuttxBufSize);
        MDrv_BDMA_MemCopy(NuttxPhyMallocAddr, u32NuttxPhyAddr, NuttxSize);
    }

    UBOOT_TRACE("OK\n");
    return u32NuttxPhyAddr;
}

U32 get_hw_aes_addr_from_tee_hd(U32 u32NuttxVirtAddr)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    UBOOT_TRACE("IN\n");

    pstTeeHd=(ST_TEE_HEADER*)u32NuttxVirtAddr;

    UBOOT_TRACE("OK\n");
    return pstTeeHd->_sthd.uihw_aes_paddr;
}

U32 get_hw_aes_len_from_tee_hd(U32 u32NuttxVirtAddr)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    UBOOT_TRACE("IN\n");
    pstTeeHd=(ST_TEE_HEADER*)u32NuttxVirtAddr;

    UBOOT_TRACE("OK\n");

    return pstTeeHd->_sthd.uihw_aes_buffer_len;
}

int do_set_tee_debug_level (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret=0;
    char buffer[CMD_BUF];
    if(argc!=2)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    UBOOT_TRACE("IN\n");
    memset(buffer,0,CMD_BUF);
    snprintf((char *)buffer,CMD_BUF,"setenv %s %s",ENV_TEE_DEBUG_LEVEL,argv[1]);
    UBOOT_DEBUG("%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("set %s to env fail.\n",ENV_TEE_DEBUG_LEVEL);
        return -1;
    }

    snprintf((char *)buffer,CMD_BUF,"saveenv");
    UBOOT_DEBUG("%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        UBOOT_ERROR("save %s to env fail\n",ENV_TEE_DEBUG_LEVEL);
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

void _set_tee_debug_mode(ST_TEE_BOOT_CONFIG *pstTeeBootConfig)
{
    EN_TEE_DEBUG_LEVEL dbgLevel=(EN_TEE_DEBUG_LEVEL_ERROR+EN_TEE_DEBUG_LEVEL_INFO);
    char *pEnv=NULL;
    UBOOT_TRACE("IN\n");

    pEnv=getenv(ENV_TEE_DEBUG_LEVEL);
    if(pEnv==NULL)
    {
        dbgLevel=EN_TEE_DEBUG_LEVEL_INFO;
        UBOOT_DEBUG("tee debug leve: DEFAULT\n");
    }

    if(strcmp(pEnv,"ERROR")==0)
    {
        dbgLevel=EN_TEE_DEBUG_LEVEL_ERROR;
        UBOOT_DEBUG("tee debug leve: ERROR\n");
    }
    else if(strcmp(pEnv,"INFO")==0)
    {
        //dbgLevel=(EN_TEE_DEBUG_LEVEL_INFO+EN_TEE_DEBUG_LEVEL_ERROR);
        dbgLevel=EN_TEE_DEBUG_LEVEL_INFO;
        UBOOT_DEBUG("tee debug leve: INFO\n");
    }
    else if(strcmp(pEnv,"TRACE")==0)
    {
        //dbgLevel=(EN_TEE_DEBUG_LEVEL_INFO+EN_TEE_DEBUG_LEVEL_ERROR+EN_TEE_DEBUG_LEVEL_TRACE);
        dbgLevel=EN_TEE_DEBUG_LEVEL_TRACE;
        UBOOT_DEBUG("tee debug leve: TRACE\n");
    }
    else if(strcmp(pEnv,"DEBUG")==0)
    {
        //dbgLevel=(EN_TEE_DEBUG_LEVEL_INFO+EN_TEE_DEBUG_LEVEL_ERROR+EN_TEE_DEBUG_LEVEL_TRACE+EN_TEE_DEBUG_LEVEL_DEBUG);
        dbgLevel=EN_TEE_DEBUG_LEVEL_DEBUG;
        UBOOT_DEBUG("tee debug leve: DEBUG\n");
    }
    else if(strcmp(pEnv,"DEBUG_L2")==0)
    {
        //dbgLevel=(EN_TEE_DEBUG_LEVEL_INFO+EN_TEE_DEBUG_LEVEL_ERROR+EN_TEE_DEBUG_LEVEL_TRACE+EN_TEE_DEBUG_LEVEL_DEBUG+EN_TEE_DEBUG_LEVEL_DEBUG_L2);
        dbgLevel=EN_TEE_DEBUG_LEVEL_DEBUG_L2;
        UBOOT_DEBUG("tee debug leve: DEBUG_L2\n");
    }
    else
    {
        dbgLevel=EN_TEE_DEBUG_LEVEL_INFO;
        UBOOT_DEBUG("tee debug leve: DEFAULT\n");
    }

    pstTeeBootConfig->enDebugLevel=dbgLevel;
    UBOOT_TRACE("OK\n");
}

void _set_tee_boot_mode(ST_TEE_BOOT_CONFIG *pstTeeBootConfig)
{
    pstTeeBootConfig->u8FastBootMode=1;
}

void set_tee_boot_config(U32 u32BootConfigAddr)
{
  ST_TEE_BOOT_CONFIG stTeeBootConfig;

  memset(&stTeeBootConfig,0,sizeof(stTeeBootConfig));

  strncpy((void *)stTeeBootConfig.u8BootConfigID,TEE_BOOT_CONFIG_ID,strlen(TEE_BOOT_CONFIG_ID));

  _set_tee_debug_mode(&stTeeBootConfig);

  _set_tee_boot_mode(&stTeeBootConfig);

  memcpy((void *)u32BootConfigAddr,&stTeeBootConfig,sizeof(ST_TEE_BOOT_CONFIG));
  flush_cache(u32BootConfigAddr,(U32)sizeof(ST_TEE_BOOT_CONFIG));

  UBOOT_DEBUG("Dump boot config\n");
  UBOOT_DUMP(u32BootConfigAddr,sizeof(ST_TEE_BOOT_CONFIG));
}

int supportTeeBootConfig(U32 u32NuttxVirtAddr)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("u32NuttxVirtAddr : %x \n",u32NuttxVirtAddr);
    UBOOT_DUMP(u32NuttxVirtAddr, sizeof(ST_TEE_HEADER));
    pstTeeHd=(ST_TEE_HEADER*)u32NuttxVirtAddr;

    if(pstTeeHd->bootConfigFlag[0]==0x11)
    {
        UBOOT_DEBUG("The tee.bin support the boot config function \n");
        UBOOT_TRACE("OK\n");
    	  return 0;
    }
    else
    {
    	 UBOOT_ERROR("The tee.bin doesn't support the boot config function\n");
    	 return -1;
    }
}
int show_tee_version(U32 u32NuttxVirtAddr)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    U8 v0[3]={0};
    U8 v1[3]={0};
    U8 v2[3]={0};
    U8 v3[3]={0};
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("u32NuttxVirtAddr : %x \n",u32NuttxVirtAddr);
    UBOOT_DUMP(u32NuttxVirtAddr, sizeof(ST_TEE_HEADER));
    pstTeeHd=(ST_TEE_HEADER*)u32NuttxVirtAddr;
    memcpy(v0,&(((char *)&pstTeeHd->_sthd.ullTeeBinVersion)[0]),2);
    memcpy(v1,&(((char *)&pstTeeHd->_sthd.ullTeeBinVersion)[2]),2);
    memcpy(v2,&(((char *)&pstTeeHd->_sthd.ullTeeBinVersion)[4]),2);
    memcpy(v3,&(((char *)&pstTeeHd->_sthd.ullTeeBinVersion)[6]),2);
    UBOOT_INFO("\033[0;33mThe version of tee.bin is %s:%s:%s:%s\n\033[0m",v0,v1,v2,v3);
    UBOOT_TRACE("OK\n");
    return 0;
}


int support_tee_1g1g_miu_interval(U32 u32NuttxVirtAddr)
{
    ST_TEE_HEADER* pstTeeHd=NULL;
    UBOOT_TRACE("IN\n");

    UBOOT_DEBUG("u32NuttxVirtAddr : %x \n",u32NuttxVirtAddr);
    UBOOT_DUMP(u32NuttxVirtAddr, sizeof(ST_TEE_HEADER));
    pstTeeHd=(ST_TEE_HEADER*)u32NuttxVirtAddr;

    if((pstTeeHd->one_g_miu_interval[0]==0x1)&&(R2_CACHE_ADDR==0))
    {
        UBOOT_DEBUG("The tee.bin supports 1G1G Miu Interval \n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
    else if((pstTeeHd->one_g_miu_interval[0]==0xff)&&(R2_CACHE_ADDR==0x40000000))
    {
        UBOOT_DEBUG(" The tee.bin does ''NOT'' support 1G1G Miu Interval \n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
    else
    {
        UBOOT_ERROR("Please check the version of tee.bin and mboot \n");
        return -1;
    }
}


int do_readNuttx (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char buffer[CMD_BUF]={0};
    char* pu8NuttxHeaderAddr=NULL;
    int ret = 0;

    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("TOTAL_MALLOC_LEN=%x \n",TOTAL_MALLOC_LEN);

    pu8NuttxHeaderAddr=malloc(NUTTX_HEADER_LEN);
    if(pu8NuttxHeaderAddr==NULL){
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(pu8NuttxHeaderAddr, 0, NUTTX_HEADER_LEN);

    memset(buffer,0,CMD_BUF);
	#if(ENABLE_MMC==1)
    snprintf(buffer,CMD_BUF, "mmc read.p %x %s %x",pu8NuttxHeaderAddr,TEE_PARTITION,NUTTX_HEADER_LEN);
	#elif (ENABLE_NAND_FLASH==1)
    snprintf(buffer,CMD_BUF, "nand read.e %x %s %x",pu8NuttxHeaderAddr,TEE_PARTITION,NUTTX_HEADER_LEN);
	#else
		#error
	#endif
    UBOOT_DEBUG("cmd: %s \n",buffer);
    run_command(buffer,0);

    UBOOT_DUMP((U32)pu8NuttxHeaderAddr, NUTTX_HEADER_LEN);

#if defined (CONFIG_SECURITY_BOOT)
    ret = DecryptKernelImage((char *)pu8NuttxHeaderAddr,NUTTX_HEADER_LEN);
    if(-1 == ret){
        free(pu8NuttxHeaderAddr);
        UBOOT_ERROR("\033[0;31m Dercypt FAIL\033[0m\n");
        return -1;
    }
#endif

    UBOOT_DUMP((U32)pu8NuttxHeaderAddr, NUTTX_HEADER_LEN);

    NuttxAlignSize=CalculateNuttxAlignSize(pu8NuttxHeaderAddr);
    UBOOT_DEBUG("NuttxAlignSize =%x \n",NuttxAlignSize);
    if(NuttxAlignSize!=0)
    {
        pNuttxOriMallocAddr=AllocateNuttxbuffer(NuttxAlignSize+16);
        if(pNuttxOriMallocAddr==NULL)
        {
            free(pu8NuttxHeaderAddr);
            UBOOT_ERROR("malloc fail\n");
            return -1;
        }
        pNuttxAlignMallocAddr=(char*)((((U32)(((U32)pNuttxOriMallocAddr)+16))>>4)<<4);
        UBOOT_DEBUG("pNuttxAlignMallocAddr =%x \n",(U32)pNuttxAlignMallocAddr);
        memset(buffer,0,CMD_BUF);
		#if(ENABLE_MMC==1)
        snprintf(buffer,CMD_BUF, "mmc read.p %x %s %x",pNuttxAlignMallocAddr,TEE_PARTITION,NuttxAlignSize);
		#elif(ENABLE_NAND_FLASH==1)
        snprintf(buffer,CMD_BUF, "nand read.e %x %s %x",pNuttxAlignMallocAddr,TEE_PARTITION,NuttxAlignSize);
		#else
			#error
		#endif
        UBOOT_DEBUG("cmd: %s \n",buffer);
        run_command(buffer,0);
    }
    else
    {
        #define TEE_PART_SIZE 0x600000
        pNuttxAlignMallocAddr=AllocateNuttxbuffer(TEE_PART_SIZE);
        if(pNuttxAlignMallocAddr==NULL)
        {
            free(pu8NuttxHeaderAddr);
            UBOOT_ERROR("malloc fail\n");
            return -1;
        }
        UBOOT_DEBUG("pNuttxAlignMallocAddr =%x \n",(U32)pNuttxAlignMallocAddr);
        memset(buffer,0,CMD_BUF);
		#if(ENABLE_MMC==1)
        snprintf(buffer,CMD_BUF, "mmc read.p %x %s %x",pNuttxAlignMallocAddr,TEE_PARTITION,TEE_PART_SIZE);
		#elif(ENABLE_NAND_FLASH==1)
		snprintf(buffer,CMD_BUF, "nand read.e %x %s %x",pNuttxAlignMallocAddr,TEE_PARTITION,TEE_PART_SIZE);
		#else
			#error
		#endif
        UBOOT_DEBUG("cmd: %s \n",buffer);
        run_command(buffer,0);
        NuttxAlignSize=TEE_PART_SIZE;
    }

    free(pu8NuttxHeaderAddr);
    return ret;
}

int do_bootNuttx (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
 #if defined (CONFIG_R2_BRINGUP)
    //I marked 'nand erad' behavior here, and add this behavior in script '[[nuttx'
    //ret = run_command ("nand read.e 0x58000000 NUTTX 0x200000", 0 );
    int ret = 0;
    U32 u32NuttxPhyAddr = 0;
    U32 u32NuttxVirtAddr = 0;
    U32 u32HwAesPABufAddr=0;
    U32 u32HwAesBufSize=0;
    U32 u32CustomerKeyBankAddr=0;
    U32 u32NConfigAddr=0;
    U32 u32NConfigSize=0;

    UBOOT_TRACE("IN\n");

    if(argc==2)
    {
        UBOOT_DEBUG("physical working buffer is from external parameter \n");
        u32NuttxPhyAddr  = simple_strtoul(argv[1], NULL, 16);
        u32NuttxVirtAddr = _PA2VA(u32NuttxPhyAddr);
    }
    else
    {
        u32NuttxVirtAddr = (U32)pNuttxAlignMallocAddr;
    }
#if defined (CONFIG_SECURITY_BOOT)
    if(-1==RawData_Authentication(TEE_PARTITION,u32NuttxVirtAddr))
    {
		UBOOT_ERROR("TEE Authentication fail\n");
		return -1;
	}
#endif


    UBOOT_DEBUG("u32NuttxVirtAddr =%x \n",u32NuttxVirtAddr);
    UBOOT_DUMP(_PA2NVA(_VA2PA(u32NuttxVirtAddr)), 0x100);
    u32NuttxPhyAddr=MoveNuttx2Dest(u32NuttxVirtAddr, NuttxAlignSize);
    if(u32NuttxPhyAddr==0)
    {
        UBOOT_ERROR("MoveNuttx2Dest fail\n");
        DeAllocateNuttxbuffer(pNuttxOriMallocAddr);
        return -1;
    }
#if !defined (CONFIG_NUTTX_BRINGUP_TEST)
    if(-1==supportTeeBootConfig(u32NuttxVirtAddr))
    {
            jump_to_console();
    		return -1;
    }

    if(-1==support_tee_1g1g_miu_interval(u32NuttxVirtAddr))
    {
            jump_to_console();
    		return -1;
    }

    show_tee_version(u32NuttxVirtAddr);
#endif

    u32HwAesPABufAddr=get_hw_aes_addr_from_tee_hd(u32NuttxVirtAddr);
    u32HwAesBufSize=get_hw_aes_len_from_tee_hd(u32NuttxVirtAddr);
    if((u32HwAesPABufAddr==0)||(u32HwAesPABufAddr==0xffffffff)||(u32HwAesBufSize==0)||(u32HwAesBufSize==0xffffffff))
    {
        UBOOT_DEBUG("tee header doesn't have hw aes info, using hw aes info in mmap\n");
        get_addr_from_mmap(HW_AES_ADDR, &u32HwAesPABufAddr);
        get_length_from_mmap(HW_AES_ADDR, &u32HwAesBufSize);
    }

    u32CustomerKeyBankAddr=_PA2NVA(u32HwAesPABufAddr);
    u32NConfigAddr=u32CustomerKeyBankAddr+sizeof(CUSTOMER_KEY_BANK);
    gu32TeeBootConfigAddr=_PA2NVA(u32HwAesPABufAddr)-NUTTX_BOOT_CONFIG_SIZE;
    gu32TeeHandShakeAddr=gu32TeeBootConfigAddr+sizeof(ST_TEE_BOOT_CONFIG);

    get_nconfig_size(&u32NConfigSize);

    UBOOT_DEBUG("u32HwAesPABufAddr=%x \n",u32HwAesPABufAddr);
    UBOOT_DEBUG("u32HwAesBufSize=%x \n",u32HwAesBufSize);
    UBOOT_DEBUG("u32NConfigSize =%x \n",u32NConfigSize);

#if defined (CONFIG_SECURITY_BOOT)
    UBOOT_DEBUG("u32CustomerKeyBankAddr=%x \n",u32CustomerKeyBankAddr);
    UBOOT_DEBUG("sizeof(CUSTOMER_KEY_BANK)=%x \n",sizeof(CUSTOMER_KEY_BANK));
    if((sizeof(CUSTOMER_KEY_BANK)+u32NConfigSize)> u32HwAesBufSize )
    {
        UBOOT_ERROR("Data is too big\n");
        UBOOT_ERROR("sizeof(CUSTOMER_KEY_BANK) : %x , u32NConfigSize : %x \n",sizeof(CUSTOMER_KEY_BANK),u32NConfigSize);
        UBOOT_ERROR("u32HwAesBufSize %x \n",u32HwAesBufSize);
        DeAllocateNuttxbuffer(pNuttxOriMallocAddr);
        return -1;
    }

    if(-1==CopyCustomerKeyBank(u32CustomerKeyBankAddr))
    {
        UBOOT_ERROR("Load NConfig fail\n");
        DeAllocateNuttxbuffer(pNuttxOriMallocAddr);
        return -1;
    }
#endif

    LoadNConfig(u32NConfigAddr);

    UBOOT_DUMP(u32CustomerKeyBankAddr, 0x100);
    UBOOT_DUMP(u32NConfigAddr, 0x100);

    set_tee_boot_config(gu32TeeBootConfigAddr);

    #if defined (CONFIG_NUTTX_BRINGUP_TEST)
    MApi_R2_StartFrDRAM(simple_strtoul(argv[1], NULL, 16));
    #else
    MApi_R2_StartFrDRAM(u32NuttxPhyAddr);
    #endif

    DeAllocateNuttxbuffer(pNuttxOriMallocAddr);
 #endif	// CONFIG_R2_BRINGUP

    UBOOT_TRACE("OK\n");
    return ret;
}

void wait_tee_ready(void)
{
    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("Wait for secure memory done\n");
    if(-1==IsSecureMemDone(gu32TeeHandShakeAddr))
    {
        UBOOT_ERROR("SecureOS is dead\n");
        UBOOT_ERROR("SecureOS is dead\n");
        MApi_Disable_R2();
    }
	else
	{
    	UBOOT_DEBUG("secure memory setting is done\n");
    	SetHKtoGo(gu32TeeHandShakeAddr);
	}
    UBOOT_TRACE("OK\n");
}

int do_load_nconfig(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    U32 u32HwAesPABufAddr=0;
    U32 u32HwAesVABufAddr=0;
    U32 u32HwAesBufLen=0;
    U32 u32NConfigAddr=0;
	if(argc!=1){
         cmd_usage(cmdtp);
         return -1;
     }

	UBOOT_TRACE("IN\n");
    get_addr_from_mmap(HW_AES_ADDR, &u32HwAesPABufAddr);
    get_length_from_mmap(HW_AES_ADDR, &u32HwAesBufLen);
    u32HwAesVABufAddr=_PA2NVA(u32HwAesPABufAddr);
    u32NConfigAddr=u32HwAesVABufAddr+sizeof(CUSTOMER_KEY_BANK);

    UBOOT_DEBUG("u32HwAesPABufAddr=%x \n",u32HwAesPABufAddr);
    UBOOT_DEBUG("u32HwAesBufLen=%x \n",u32HwAesBufLen);
    UBOOT_DEBUG("u32HwAesVABufAddr=%x \n",u32HwAesVABufAddr);
    UBOOT_DEBUG("u32NConfigAddr=%x \n",u32NConfigAddr);

    if(NConfigLoad(u32NConfigAddr)!=0)
	{
		UBOOT_ERROR("Load NConfig fail\n");
		return -1;
	}

	UBOOT_TRACE("OK\n");
	return 0;

}
int do_save_nconfig(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    #define OBJECT_NAME argv[1]
    #define OBJECT_DRAM_ADDR argv[2]
    int ret=0;

    if(argc<3){
         cmd_usage(cmdtp);
         return -1;
     }

    if(strcmp(OBJECT_NAME,"NuttxConfig")!=0){
        return -1;
    }

    ST_SIGN_CONFIG* pstHeaderInfo = NULL;
    U32 u32SignConfigPhyAddr=simple_strtoul(OBJECT_DRAM_ADDR, NULL, 16);;
    U32 u32SignConfigLen=0;
    U32 u32SigPhyAddr=0;
    U32 u32ConfigPhyAddr=0;
    U32 u32SigLen=256;
    U32 u32ConfigLen=0;
    UBOOT_DEBUG("OBJECT_NAME : %s \n",OBJECT_NAME);
    UBOOT_DEBUG("u32SignConfigPhyAddr =%x \n",u32SignConfigPhyAddr);

    pstHeaderInfo=(ST_SIGN_CONFIG*)u32SignConfigPhyAddr;
    u32SigPhyAddr=u32SignConfigPhyAddr+pstHeaderInfo->stSignature.Offset;
    u32SigLen=pstHeaderInfo->stSignature.Length;
    u32ConfigPhyAddr=u32SignConfigPhyAddr+pstHeaderInfo->stConfig.Offset;
    u32ConfigLen=pstHeaderInfo->stConfig.Length;
    #define HEADER_LEN 256
    u32SignConfigLen=HEADER_LEN+u32SigLen+u32ConfigLen;

    UBOOT_DEBUG("****u32SignConfigPhyAddr : %x \n",u32SignConfigPhyAddr);
    UBOOT_DEBUG("****u32SigPhyAddr : %x \n",u32SigPhyAddr);
    UBOOT_DEBUG("****u32SigLen : %x \n",u32SigLen);
    UBOOT_DEBUG("****u32ConfigPhyAddr : %x \n",u32ConfigPhyAddr);
    UBOOT_DEBUG("****u32ConfigLen : %x \n",u32ConfigLen);

    ret = NConfigSave((U8*)u32SignConfigPhyAddr, u32SignConfigLen);
    if(EN_SUCCESS != ret){
        UBOOT_ERROR("NConfig Save fail\n");
        return -1;
    }

     UBOOT_TRACE("OK\n");

     return 0;
}
int get_nconfig_size(unsigned int *u32NConfigSize)
{
    int ret = 0;
    UBOOT_DEBUG("IN\n");

    ret = MsApiChunkHeader_GetValue(CH_NUTTX_CONFIG_SIZE,u32NConfigSize);
    if(ret != 0){
        UBOOT_ERROR("MsApiChunkHeader_GetValue fail!\n");
        return -1;
    }
    *u32NConfigSize=(*u32NConfigSize)*((unsigned int)SECTOR_SIZE);
    UBOOT_DEBUG("*u32NConfigSize = %x\n",*u32NConfigSize);

    UBOOT_DEBUG("OK\n");
    return ret;
}

int get_nconfig_offset(unsigned int *u32NConfigOffset,unsigned int *u32NConfigBakOffset)
{
    int ret = 0;
	U32 u32Size=0;

    UBOOT_DEBUG("IN\n");

    ret = MsApiChunkHeader_GetValue(CH_NUTTX_CONFIG_OFFSET,u32NConfigOffset);
    if(ret != 0){
        UBOOT_ERROR("MsApiChunkHeader_GetValue fail!\n");
        return -1;
    }
    UBOOT_DEBUG("*u32NConfigOffset = %x\n",*u32NConfigOffset);
    #if defined (CONFIG_NCONFIG_STORE_IN_SPI_FLASH)
    ret = getSpiSize(&u32Size);
    *u32NConfigOffset = u32Size - ((*u32NConfigOffset)*SECTOR_SIZE);
    *u32NConfigBakOffset=*u32NConfigOffset+SECTOR_SIZE;
    UBOOT_DEBUG("u32NConfigOffset : 0x%x\n",*u32NConfigOffset);
    UBOOT_DEBUG("u32NConfigBkOffset : 0x%x\n",*u32NConfigBakOffset);

	#elif defined (CONFIG_NCONFIG_STORE_IN_NAND_FLASH)
    check_ubi_partition(NAND_DEFAULT_VOLUME,NAND_DEFAULT_PARTITION);
    ubi_get_volume_size(NAND_DEFAULT_VOLUME,&u32Size);
    UBOOT_DEBUG("u32Size : 0x%x\n",u32Size);
    UBOOT_DEBUG("ubi_get_leb_size : 0x%x\n",SECTOR_SIZE);
    *u32NConfigOffset = u32Size - ((*u32NConfigOffset)*SECTOR_SIZE);
   	*u32NConfigBakOffset=*u32NConfigOffset+SECURE_INFOR_BACK_OFFSET*SECTOR_SIZE;
    UBOOT_DEBUG("u32NConfigOffset : 0x%x\n",*u32NConfigOffset);
    UBOOT_DEBUG("u32NConfigBkOffset : 0x%x\n",*u32NConfigBakOffset);

	#elif defined (CONFIG_NCONFIG_STORE_IN_EMMC_FLASH)
    ret = get_mmc_partsize(FLASH_DEFAULT_VOLUME,&u32Size);
    *u32NConfigOffset = u32Size - ((*u32NConfigOffset)*SECTOR_SIZE);
    *u32NConfigBakOffset=*u32NConfigOffset+SECURE_INFOR_BACK_OFFSET*SECTOR_SIZE;
    UBOOT_DEBUG("u32NConfigOffset : 0x%x\n",*u32NConfigOffset);
    UBOOT_DEBUG("u32NConfigBkOffset : 0x%x\n",*u32NConfigBakOffset);
	#else
	#error "error"
    #endif

    if(EN_SUCCESS == ret){
        ret=0;
        UBOOT_DEBUG("OK\n");
    }
    else{
        ret=-1;
        UBOOT_DEBUG("get_NConfig_offset fail\n");
    }

    UBOOT_DEBUG("OK\n");

    return ret;
}

int NConfigSave(U8* pBufferAddr, U32 u32NConfigLen)
{
   int ret=-1;
   int ret_bk =-1;
   unsigned int u32NConfigOffset = 0;
   unsigned int u32NConfigBkOffset = 0;
   unsigned int u32NConfigSize=0;
    UBOOT_DEBUG("IN\n");

   if(pBufferAddr==NULL)
   {
      UBOOT_ERROR("The input parameter pBufferAddr' is a null pointer\n");
      return -1;
   }

   ret = raw_io_config(FLASH_DEFAULT_TARGET,FLASH_DEFAULT_PARTITION,FLASH_DEFAULT_VOLUME);
   if(ret != 0)
   {
       UBOOT_ERROR("raw_io_config setting fail!\n");
       return -1;
   }

   ret = get_nconfig_offset(&u32NConfigOffset,&u32NConfigBkOffset);
   if(ret != 0)
   {
       UBOOT_ERROR("get_NConfig_offset fail!\n");
       return -1;
   }

   UBOOT_DEBUG("u32NConfigOffset : 0x%x\n",u32NConfigOffset);
   UBOOT_DEBUG("u32NConfigBkOffset : 0x%x\n",u32NConfigBkOffset);

   ret = get_nconfig_size(&u32NConfigSize);
   if(ret != 0)
   {
       UBOOT_ERROR("get_nconfig_max_size fail!\n");
       return -1;
   }

   #define NCONFIG_RAW_DATA_SIZE (u32NConfigSize-4)

   UBOOT_DEBUG("u32NConfigLen =%x\n",u32NConfigLen);
   if(u32NConfigLen>=NCONFIG_RAW_DATA_SIZE)
   {
        UBOOT_ERROR("NCofngi length is larger than %x\n",NCONFIG_RAW_DATA_SIZE);
        return -1;
   }

    unsigned long Crc32=0;
    // update CRC
    Crc32=crc32(0, pBufferAddr,NCONFIG_RAW_DATA_SIZE);
    UBOOT_DEBUG("Crc32 =%lx\n",Crc32);
    memcpy(pBufferAddr+NCONFIG_RAW_DATA_SIZE, &Crc32, sizeof(Crc32));
    UBOOT_DEBUG("Burn NConfig to blcok\n");
    ret = raw_write((unsigned int)pBufferAddr,u32NConfigOffset,u32NConfigSize);
    UBOOT_DEBUG("Burn NConfig to  backup blcok\n");
    ret_bk = raw_write((unsigned int)pBufferAddr,u32NConfigBkOffset,u32NConfigSize);

    if(EN_SUCCESS == ret || EN_SUCCESS == ret_bk){
        UBOOT_DEBUG("ret : %d , ret_bk : %d \n",ret,ret_bk);
        UBOOT_TRACE("OK\n");
        ret = 0;
    }
    else{
        ret= -1;
        UBOOT_ERROR("NConfig Save fail\n");
    }

    UBOOT_DEBUG("OK\n");
    return ret;
    #undef NCONFIG_RAW_DATA_SIZE
}

int LoadNConfig(U32 u32NConfigBufAddr)
{
    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("u32HwAesVABufAddr =%x\n",u32NConfigBufAddr);
    if(NConfigLoad(u32NConfigBufAddr)!=EN_SUCCESS){
        UBOOT_ERROR("Load signature fail\n");
        return -1;
    }

    UBOOT_DEBUG("OK\n");
    return 0;
}

int NConfigLoad(U32 u32NConfigBufAddr)
{
    int ret = -1;

    unsigned int u32NConfigOffset = 0;
    unsigned int u32NConfigBakOffset = 0;
	unsigned int u32NConfigSize=0;
    UBOOT_DEBUG("IN\n");
#define NCONFIG_RAW_DATA_SIZE (u32NConfigSize-4)


    ret = raw_io_config(FLASH_DEFAULT_TARGET,FLASH_DEFAULT_PARTITION,FLASH_DEFAULT_VOLUME);
    if(ret != 0){
        UBOOT_ERROR("raw_io_config setting fail!\n");
        return -1;
    }

    ret = get_nconfig_offset(&u32NConfigOffset,&u32NConfigBakOffset);
    if(ret != 0){
        UBOOT_ERROR("get_signature_offset fail!\n");
        return -1;
    }
    UBOOT_DEBUG("u32NConfigOffset =%x \n",u32NConfigOffset);
    UBOOT_DEBUG("u32NConfigBakOffset =%x \n",u32NConfigBakOffset);


    U8* pBufferAddr= NULL;
    int flag1=0, flag2=0;
    unsigned long Crc32=0;

	get_nconfig_size(&u32NConfigSize);
    pBufferAddr=malloc(u32NConfigSize);
    if(pBufferAddr==NULL){
        return -1;
    }
    memset(pBufferAddr ,0 ,u32NConfigSize);

    UBOOT_DEBUG("u32NConfigSize =%x \n",u32NConfigSize);



    ret = raw_read((unsigned int)pBufferAddr,u32NConfigOffset,u32NConfigSize);
    memcpy(&Crc32, (pBufferAddr+NCONFIG_RAW_DATA_SIZE), sizeof(Crc32));
    UBOOT_DEBUG("Crc32 =%lx \n",Crc32);
    if( (EN_SUCCESS == ret) && (Crc32 == crc32(0, pBufferAddr,NCONFIG_RAW_DATA_SIZE)) ){
        UBOOT_DEBUG("NConfig data is ok \n");
        flag1=1;
    }

    ret = raw_read((unsigned int)pBufferAddr,u32NConfigBakOffset,u32NConfigSize);
    memcpy(&Crc32, (pBufferAddr+NCONFIG_RAW_DATA_SIZE), sizeof(Crc32));
    UBOOT_DEBUG("Crc32 =%lx \n",Crc32);
    if( (EN_SUCCESS == ret) && (Crc32== crc32(0, pBufferAddr,NCONFIG_RAW_DATA_SIZE)) ){
        UBOOT_DEBUG("Backup NConfig data is ok \n");
        flag2=1;
    }

    if( (flag2==0) && (flag1!=0) ){
        ret = raw_read((unsigned int)pBufferAddr,u32NConfigOffset,u32NConfigSize);
        memcpy(&Crc32, (pBufferAddr+NCONFIG_RAW_DATA_SIZE), sizeof(Crc32));
        if( (EN_SUCCESS == ret) && (Crc32 == crc32(0, pBufferAddr,NCONFIG_RAW_DATA_SIZE))){
            UBOOT_DEBUG("Backup NConfig data is fail, re-write backup NConfig \n");
            UBOOT_DEBUG("Crc32 =%lx \n",Crc32);

            ret = raw_write((unsigned int)pBufferAddr,u32NConfigBakOffset,u32NConfigSize);
        }
        else{
            free(pBufferAddr);
            UBOOT_ERROR("raw_read fail or caculate crc fail!\n");
            return -1;
        }
    }

    if((flag1==0)&&(flag2!=0)){
        UBOOT_DEBUG("SigNConfig data is fail, re write backup SigNConfig \n");
        ret = raw_write((unsigned int)pBufferAddr,u32NConfigOffset,sizeof(SECURITY_INFO));
    }

   if(EN_SUCCESS != ret){
       free(pBufferAddr);
       UBOOT_ERROR("Load NConfig fail\n");
        return -1;
    }
	flush_cache(u32NConfigBufAddr,u32NConfigSize);
    ret = raw_read((unsigned int)u32NConfigBufAddr,u32NConfigOffset,u32NConfigSize);
    if(EN_SUCCESS != ret){
       free(pBufferAddr);
       UBOOT_ERROR("Load NConfig fail\n");
       return -1;
    }

    free(pBufferAddr);
    UBOOT_DEBUG("OK\n");
    return ret;
#undef NCONFIG_RAW_DATA_SIZE
}

#endif	// CONFIG_R2_BRINGUP


#if defined(CONFIG_TRUSTZONE_ENABLE)
static void do_setup_normal_world(void)
{

    __asm__ volatile(

    /*Setup */
    "ldr     r1, =0x73fff\n"
    "mrc     p15, 0, r0, c1, c1, 2\n"
    "orr     r0,  r0, r1\n"
    "mcr     p15, 0, r0, c1, c1, 2\n"

    /*Setup IRQ and local tiemr and SPI63 as Group1 for non secure world usage */
    "ldr    r0, =0xA000ffff\n"
    "mov    r1, #0x16000000\n"
    "add    r1, r1, #0x1080\n"
    "str    r0, [r1]\n"
    "ldr    r0, =0x80000000\n"
    "add    r1, r1, #0x4\n"
    "str    r0, [r1]\n"

    /*Setup SNAC that kernel can R/W private/local timer */
    "ldr    r0, =0xfff\n"
    "mov    r1, #0x16000000\n"
    "add    r1, r1, #0x54\n"
    "str    r0, [r1]\n"

    "ldr    r0, =0xf0\n"
    "mov    r1, #0x16000000\n"
    "add    r1, r1, #0x104\n"
    "str    r0, [r1]\n"

    "mrc     15, 0, r0, cr1, cr0, 1\n"
    "orr     r0, r0, #1\n"
    "mcr     15, 0, r0, cr1, cr0, 1\n"

    "dmb\n"
    "dsb\n"

   );

}

static void do_enter_to_normal_world(void)
{
    //Enter to normal world
    printf("enter normal world\n");

    __asm__ volatile(
    "mrc  p15, 0, r0, c1, c1, 0\n"
    "orr  r0, #0x1\n"
    "mcr  p15, 0, r0, c1, c1, 0\n"
    );

}

static void do_prepare_normal_world(void)
{

    do_setup_normal_world();

    Chip_Flush_Memory();

    do_enter_to_normal_world();
}

/*
static void do_trigger_core1(void)
{
    __asm__ volatile(
       "ldr r0, =0x53484954\n"
       "ldr r1, =0x57fffffc\n"
       "str r0, [r1]\n"
    );

}
*/
//int do_bootNuttx (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
void do_bootNuttx (void)
{
   // int ret = 0;

    // Load Nuttx.
/*
    if(argc==2)
    {
        UBOOT_DEBUG("physical working buffer is from external parameter \n");
        UBOOT_DEBUG("physical working buffer is from external parameter \n");
        UBOOT_DEBUG("physical working buffer is from external parameter \n");

        u32NuttxPhyAddr=simple_strtoul(argv[1], NULL, 16);
    }
*/
    //ret = run_command ("nand read.e 98008000 NUTTX 0x200000", 0 );
    //ret = run_command ("mmc read.p 58008000 NUTTX 0x400000", 0 );

    //Set Nuttx address then fill magic number 0xaaaa to core1
#if defined(CONFIG_MSTAR_NAPOLI_BD_MST189A_D01A_S) || defined(CONFIG_MSTAR_NAPOLI_BD_MST069D_10AWVS)
    *((volatile unsigned int *)(0x20208000)) = 0x0000aaaa;
#else
	*((volatile unsigned int *)(0x60208000)) = 0x0000aaaa;
#endif

    //Set ready and going to normal world, then wfi
    do_prepare_normal_world();

    Chip_Flush_Memory();

    //do_trigger_core1();

/*
    U32 boot_address=CONFIG_KERNEL_START_ADDRESS+0x8000 ;
    printf("Core boot address = %x\n",boot_address);

    *(volatile unsigned int *)(boot_address) = 0xbabe;
    *(volatile unsigned int *)(boot_address+4) = 0x58008000;
    flush_cache(boot_address,8);
    Chip_Flush_Memory();

    *(volatile unsigned int *)(0x16001f00) = 0x00020001;

    __asm__ volatile ("wfi");
*/

    //return ret;
}
#endif //CONFIG_TRUSTZONE_ENABLE
