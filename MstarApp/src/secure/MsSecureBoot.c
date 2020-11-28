//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (¡§MStar Software¡¨) are intellectual property of MStar Semiconductor, Inc. (¡§MStar¡¨) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar.
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (¡§Terms¡¨) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party¡¦s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party¡¦s software.
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar¡¦s confidential information and you agree to keep MStar¡¦s confidential information in strictest confidence and not disclose to any third party.
//4. MStar Software is provided on an ¡§AS IS¡¨ basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.
//   In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer¡¦s product (¡§Services¡¨).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an ¡§AS IS¡¨ basis and the warranty disclaimer set forth in Section 4 above shall apply.
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.
//   The arbitration award shall be final and binding to both parties.
//***********************************************************************************
//<MStar Software>

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    cmd_secure.c
/// @brief  SCS Main Function
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <common.h>
#include <exports.h>
#include <command.h>
#include <MsSystem.h>

#include <secure/MsSecureBoot.h>
#include <secure/MsSignature.h>
#include <secure/MsSecureCommon.h>
#include <secure/crypto_rsa.h>
#include <secure/crypto_sha.h>
#include <secure/crypto_func.h>
#include <secure/crypto_aes.h>
#include <secure/crypto_auth.h>
#include <secure/apiSecureBoot.h>
#include <MsTypes.h>
#include <MsSystem.h>
#include <ShareType.h>
#include <MsSystem.h>
#include <MsDebug.h>
#include <MsUtility.h>
#include <MsRawIO.h>
#include <MsMmap.h>
#include <MsBoot.h>
#include <drvMBX.h>
#include <drvAESDMA.h>
#include <CusConfig.h>
//-------------------------------------------------------------------------------------------------
//  Debug
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#if defined (CONFIG_MBOOT_IN_SPI_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_SPI
#define FLASH_DEFAULT_PARTITION SPI_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME SPI_DEFAULT_VOLUME
#define SECTOR_SIZE   0x10000
#elif defined (CONFIG_MBOOT_IN_NAND_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_NAND
#define FLASH_DEFAULT_PARTITION NAND_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME NAND_DEFAULT_VOLUME
#define SECTOR_SIZE   126976
#elif defined  (CONFIG_MBOOT_IN_MMC_FLASH)
#define FLASH_DEFAULT_TARGET  E_RAW_DATA_IN_MMC
#define FLASH_DEFAULT_PARTITION MMC_DEFAULT_PARTITION
#define FLASH_DEFAULT_VOLUME MMC_DEFAULT_VOLUME
#define SECTOR_SIZE   0x200
#else
#error "please set the correct security storage!!\n"
#endif
#define CUSTOMER_KEY_BANK_LEN 0x1000


#define SEC_INFOR_BIN_ADDR_OFFSET   0x120000
#define SEC_INFOR_BIN_ADDR_BACKUP_OFFSET   0x80000
#define SPI_FLASH_BASE_ADDR         0xBFC00000
#define CUSTOMER_KEY_BANK_ADDR_IN_SPI (0x20000)


#define ENV_BOOT_CMD "bootcmd"
#define ENV_PROTECTION_KEY "PROTECTION_KEY"
#define ENV_PARTAIL_AUTHENTICATION "partial_partition"
#define DID_LEN 16

#if defined(__ARM__)
#define CONFIG_SRAM_BASE_ADDRESS    0x1FC00000
#else
#define CONFIG_SRAM_BASE_ADDRESS    0xBF400000
#endif
#define POR_STATUS_BASE_ADDR (0x100500)

extern unsigned long MS_RIU_MAP;
#define RIU     ((unsigned short volatile *) MS_RIU_MAP)

//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------
#define ENV_KEYBANK_DONE "keybank_done"

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static SECURITY_INFO stSecureInfo;
static CUSTOMER_KEY_BANK stCusKey;
static U8 const u8MstarDefRSAImagePublicKey[RSA_PUBLIC_KEY_LEN]={
    0x84 ,0x62 ,0x76 ,0xCC ,0xBD ,0x5A ,0x5A ,0x40 ,0x30 ,0xC0 ,0x96 ,0x40 ,0x87 ,0x28 ,0xDB ,0x85 ,
    0xED ,0xED ,0x9F ,0x3E ,0xDE ,0x4E ,0x65 ,0xE6 ,0x7B ,0x1B ,0x78 ,0x17 ,0x87 ,0x9D ,0xF6 ,0x16 ,
    0xC3 ,0xD3 ,0x27 ,0xBC ,0xB4 ,0x5A ,0x3  ,0x13 ,0x35 ,0xB0 ,0x96 ,0x5A ,0x96 ,0x41 ,0x74 ,0x4E ,
    0xB9 ,0xD1 ,0x77 ,0x96 ,0xF7 ,0x8D ,0xE2 ,0xE7 ,0x15 ,0x9  ,0x65 ,0x9C ,0x46 ,0x79 ,0xEA ,0xF0 ,
    0x91 ,0x67 ,0x35 ,0xFA ,0x69 ,0x4C ,0x83 ,0xF7 ,0xDC ,0xCF ,0x97 ,0x20 ,0xF2 ,0xA5 ,0xBA ,0x72 ,
    0x80 ,0x9D ,0x55 ,0x79 ,0x17 ,0xDC ,0x6E ,0x60 ,0xA5 ,0xE7 ,0xE  ,0x9E ,0x89 ,0x9B ,0x46 ,0x6  ,
    0x52 ,0xFC ,0x64 ,0x56 ,0x2  ,0x8  ,0x9A ,0x96 ,0x41 ,0xE2 ,0x4F ,0xDB ,0xB6 ,0x60 ,0xC3 ,0x38 ,
    0xDF ,0xF4 ,0x97 ,0x81 ,0x5D ,0x12 ,0x2  ,0xAE ,0x2B ,0x9F ,0x9  ,0x29 ,0xB9 ,0x9D ,0x51 ,0x45 ,
    0xD2 ,0x9E ,0x2B ,0xAF ,0x64 ,0xCA ,0x9A ,0x6  ,0x4E ,0x94 ,0x35 ,0x67 ,0xF7 ,0x8E ,0x4  ,0x7B ,
    0x24 ,0x38 ,0xA0 ,0xDF ,0xE7 ,0x5F ,0x1E ,0x6D ,0x29 ,0x8E ,0x30 ,0xD7 ,0x83 ,0x8C ,0xB4 ,0x41 ,
    0xD2 ,0xFD ,0xBF ,0x5B ,0x18 ,0xCA ,0x50 ,0xD1 ,0x27 ,0xD1 ,0xF6 ,0x7D ,0x54 ,0x3E ,0x80 ,0x5F ,
    0x20 ,0xDC ,0x88 ,0x82 ,0xCF ,0xBE ,0xE1 ,0x46 ,0x2A ,0xD6 ,0x63 ,0xB9 ,0xB9 ,0x9D ,0xA3 ,0xC7 ,
    0x68 ,0x3E ,0x48 ,0xCE ,0x6A ,0x62 ,0x6F ,0xD1 ,0x6A ,0xC3 ,0xB6 ,0xDE ,0xF3 ,0x39 ,0x25 ,0xEC ,
    0xF6 ,0x79 ,0x20 ,0xB5 ,0xF2 ,0x30 ,0x25 ,0x6E ,0x99 ,0xAE ,0x39 ,0x56 ,0xDA ,0xAF ,0x83 ,0xD6 ,
    0xB8 ,0x49 ,0x15 ,0x78 ,0x81 ,0xCC ,0x3C ,0x4F ,0x66 ,0x5D ,0x95 ,0x7E ,0x31 ,0xD4 ,0x37 ,0x2A ,
    0xBE ,0xFC ,0xB4 ,0x66 ,0xF8 ,0x91 ,0x1  ,0xA  ,0x53 ,0x3C ,0x3C ,0xAB ,0x86 ,0xB9 ,0x80 ,0xB7 ,
    0x0  ,0x1  ,0x0  ,0x1};
static char idForContinueMode[]={'S','E','C','U','R','I','T','Y'};
static char idForInterleaveMode[]={'I','N','T','E','R','L','V','E'};

#if(ENABLE_MODULE_ANDROID_BOOT == 1)
static char* RawData_partition[]={"boot","recovery",TEE_PARTITION,NULL};
static char* filesystem_partition[]={NULL};
#else

static char* RawData_partition[]={"KL",TEE_PARTITION,NULL};
static char* filesystem_partition[]={"RFS","MSLIB","APP",NULL};
#endif

static U8 u8MagicID[16]={0x4D,0x73,0x74,0x61,0x72,0x2E,0x4B,0x65,0x79,0x2E,0x42,0x61,0x6E,0x6B,0x2E,0x2E};
//-------------------------------------------------------------------------------------------------
//  extern function
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);
extern int strcmp(const char * cs,const char * ct);
extern int ubi_get_leb_size(void);
//-------------------------------------------------------------------------------------------------
//  inline
//-------------------------------------------------------------------------------------------------

void Secure_HaltCPU(void)
{
    //show error UI
    run_command("destroy_logo",0);
    run_command("bootlogo 0 0 1 1 boot_error.jpg", 0);
    run_command("panel_post_init",0);
    //halt cpu
    while(1){;}
}


//-------------------------------------------------------------------------------------------------
//  Local function
//-------------------------------------------------------------------------------------------------
int ImageIOInit(char *partition);
int _ImageIOInitForEMMC(char *partition);
int _ImageIOInitForNand(char *partition);
int ImageRead(char *volume, unsigned int addr, unsigned int offset, unsigned len);
int _ImageRead(char *volume, unsigned int addr, unsigned int offset, unsigned len);
int ImageWrite(char *volume, unsigned int addr, unsigned int offset, unsigned len);
U32 GetBlockSize(void);
int GetSubImageNum(char *volume, U32 *num);
int GetImageFromStorage(char *volume, unsigned int addr, unsigned int number);
int _GetImageFromStorage(char *volume, unsigned int addr, unsigned int number, BOOLEAN bIsInterleaveMode);
int DecryptKernelImageByHouseKeeping(char *dataBuf, unsigned int len);
int DecryptKernelImageBySecureProcessor(char *dataBuf, unsigned int len);
int EnablePartialAuthentication(void);
int DisablePartialAuthentication(void);
BOOLEAN IsDoingPartialAuthentication(void);
int CancelBootCmd(void);
int _RawData_Authentication(char *KLName,unsigned int u32kernelAddr);

int do_Authenticate_RawData(char *KLName, int CacheBufAddr);
int do_Authenticate_FileSystem(char *fileSystemName);

int IsImageRight(char *volume);
int CheckSignature(SECURITY_INFO *sign);
int _LoadCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeySize,U32 u32HwAesVABufAddr);
int RestoreCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeySize,U32 tempDRAMAddr);
BOOLEAN isCustomerKeyBankCipher(U32 keyBankOffset,U32 keyBankSize,U32 tempDRAMAddr);
void EnableAESDAMClock(void);

int Secure_Drv_Init(void);
int LoadSignature(void);
int LoadCustomerKeyBank(void);

void PopUpProtectedKey(void);
#if defined(CONFIG_SECURE_SPI_PROTECT)
void spi_write_protect_process_init(void);
#endif
BOOLEAN IsInterleaveMode(void);
int _EncryptCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeySize,U32 tempDRAMAddr);

int EncryptCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeyBackUpOffset, U32 u32CusKeySize,U32 tempDRAMAddr);
int copyKeyBank(U32 destOffset, U32 srcOffset, U32 size, U32 tempDRAMAddr);
int setKeyBankProcessStatusDone(void);
int clearKeyBankProcessStatus(void);
int _setKeyBankProcessStatus(char value);

int IsKeyBankProcessDone(char *env, BOOLEAN*pDone);
int IsRawDataPartition(char* partition);
int IsFileSystemPartition(char* partition);
_SUB_SECURE_INFO*  getSubSecureInfo(SECURITY_INFO *pBufferAddr,char* partition,BOOLEAN bIsInterleaveMode);
void getSecIdentify(char* pSecIdentify,SECURITY_INFO *pBufferAddr,BOOLEAN bIsInterleaveMode);
U32 *getHash0PublicKeyN(void);
U32 *getHash0PublicKeyE(void);
BOOLEAN isCustomerKeyBankValid(CUSTOMER_KEY_BANK *pCusKey);

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

int IsRawDataPartition(char* partition)
{
    UBOOT_TRACE("IN\n");
    int ret = -1;
    int i;
    for(i = 0;RawData_partition[i] != NULL;i++)
    {
        if(0 == strcmp(partition,RawData_partition[i]))
        {
            ret = 0;
            break;
        }
    }
    if(0 == ret)
    {
        UBOOT_DEBUG("%s is RawData Partition\n",partition);
    }
    else
    {
        UBOOT_DEBUG("%s is not RawData Partition\n",partition);
    }
    UBOOT_TRACE("OK\n");
    return ret;
}

int IsFileSystemPartition(char* partition)
{
    UBOOT_TRACE("IN\n");
    int ret = -1;
    int i;
    for(i = 0;filesystem_partition[i] != NULL;i++)
    {
        if(0 == strcmp(partition,filesystem_partition[i]))
        {
            ret = 0;
            break;
        }
    }
    if(0 == ret)
    {
        UBOOT_DEBUG("%s is FileSystem Partition\n",partition);
    }
    else
    {
        UBOOT_DEBUG("%s is not FileSystem Partition\n",partition);
    }
    UBOOT_TRACE("OK\n");
    return ret;
}

_SUB_SECURE_INFO* getSubSecureInfo(SECURITY_INFO *pBufferAddr,char* partition,BOOLEAN bIsInterleaveMode)
{
    UBOOT_TRACE("IN\n");
    if(NULL == pBufferAddr || NULL == partition)
    {
        UBOOT_ERROR("args error\n");
        return NULL;
    }
    _SUB_SECURE_INFO *pSubAddr = NULL;
    #if (ENABLE_MODULE_ANDROID_BOOT == 1)
    if(0 == strcmp("boot",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.Boot);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.Boot);
        }

    }
    else if(0 == strcmp("recovery",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.Recovery);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.Recovery);
        }
    }
	else if(0 == strcmp(TEE_PARTITION,partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.tee);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.tee);
        }
    }
    #if defined (CONFIG_SecureStorage)
    else if(0 == strcmp("chunk",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.Chunk);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.Chunk);
        }
    }
    else if(0 == strcmp("chunkbackup",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.Chunk_backup);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.Chunk_backup);
        }
    }
    #endif
    #else
    if(0 == strcmp("KL",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.Kernel);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.Kernel);
        }
    }
    else if(0 == strcmp("RFS",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.RootFs[0]);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.RootFs[0]);
        }
    }
    else if(0 == strcmp("MSLIB",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.MsLib[0]);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.MsLib[0]);
        }
    }
    else if(0 == strcmp("APP",partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.App[0]);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.App[0]);
        }
    }
    else if(0 == strcmp(TEE_PARTITION,partition))
    {
        if(TRUE == bIsInterleaveMode)
        {
            pSubAddr = &(pBufferAddr->data_interleave.tee);
        }
        else
        {
            pSubAddr = &(pBufferAddr->data.tee);
        }
    }
    #endif
    else
    {
        UBOOT_ERROR("invalid partiton name:%s\n",partition);
        return NULL;
    }
    UBOOT_TRACE("OK\n");
    return pSubAddr;
}

void getSecIdentify(char* pSecIdentify,SECURITY_INFO *pBufferAddr,BOOLEAN bIsInterleaveMode)
{
    UBOOT_TRACE("IN\n");
    #if (ENABLE_MODULE_ANDROID_BOOT == 1)
    if(TRUE == bIsInterleaveMode)
    {
        memcpy(pSecIdentify,pBufferAddr->data_interleave.Boot.u8SecIdentify,sizeof(pBufferAddr->data_interleave.Boot.u8SecIdentify));
    }
    else
    {
        memcpy(pSecIdentify,pBufferAddr->data.Boot.u8SecIdentify,sizeof(pBufferAddr->data.Boot.u8SecIdentify));
    }
    #else
    if(TRUE == bIsInterleaveMode)
    {
        memcpy(pSecIdentify,pBufferAddr->data_interleave.Kernel.u8SecIdentify,sizeof(pBufferAddr->data_interleave.Kernel.u8SecIdentify));
    }
    else
    {
        memcpy(pSecIdentify,pBufferAddr->data.Kernel.u8SecIdentify,sizeof(pBufferAddr->data.Kernel.u8SecIdentify));
    }
    #endif
    UBOOT_TRACE("OK\n");
    return;
}

int FileSystem_Authentication(void)
{
    int ret=0;
    UBOOT_TRACE("IN\n");

    ret=ImageIOInit("UBI");
    if(ret==-1)
    {
        UBOOT_ERROR("Image IO init fail\n");
        Secure_HaltCPU();
    }
    int i;
	for(i = 0;filesystem_partition[i] != NULL;i++){
		ret=IsImageRight(filesystem_partition[i]);
		if(-1 == ret)
		{
			UBOOT_ERROR("Authentication is fail in %s\n",filesystem_partition[i]);
			Secure_HaltCPU();
		}
	}

    EnablePartialAuthentication();

    UBOOT_TRACE("OK\n");
    return 0;
}

int IsImageRight(char *volume)
{
    UBOOT_TRACE("IN\n");
    U32 numOfSubImage=0;
    U32 size=0;
    U8 i=0;
    U8 u8ImagePublicKeyN[RSA_PUBLIC_KEY_N_LEN];
    U8 u8ImagePublicKeyE[RSA_PUBLIC_KEY_E_LEN];
    U8 u8ImageSignature[SIGNATURE_LEN];
    U32 partition_num;
    int ret=-1;
    MS_BOOL skipPartialAuthen=FALSE;
    UBOOT_TRACE("IN\n");
    if(volume==0)
    {
        UBOOT_ERROR("The input of parameter is a null pointer\n");
        return ret;
    }
    ret=GetSubImageNum(volume,&numOfSubImage);
    if(ret!=0)
    {
        UBOOT_ERROR("get sub image number fail\n");
        return -1;
    }
    partition_num=getRandNum();
    partition_num=(partition_num)%numOfSubImage;
    UBOOT_INFO("partition_num=%d\n",partition_num);
    skipPartialAuthen=IsDoingPartialAuthentication();

    for(i=0;i<numOfSubImage;i++){

        if(skipPartialAuthen==TRUE){
            if(i!=partition_num){
                continue;
            }
        }
        ret=GetImageSize(volume,i, &size);
        if(ret!=0)
        {
            UBOOT_ERROR("Get image size fail\n");
            return ret;
        }
        ret=GetImageFromStorage(volume,FILESYSTEM_AUTHENTICATION_BUFFER_ADDR,i);
        if(ret!=0)
        {
            UBOOT_ERROR("Get image fail\n");
            return ret;
        }
        ret=GetPublicKeyN(E_RSA_IMAGE_PUBLIC_KEY, u8ImagePublicKeyN, sizeof(u8ImagePublicKeyN));
        if(ret!=0)
        {
            UBOOT_ERROR("Get public key N fail\n");
            return ret;
        }
        ret=GetPublicKeyE(E_RSA_IMAGE_PUBLIC_KEY, u8ImagePublicKeyE, sizeof(u8ImagePublicKeyE));
        if(ret!=0)
        {
            UBOOT_ERROR("Get public key E fail\n");
            return ret;
        }
        ret=GetSignature(volume, i, u8ImageSignature, sizeof(u8ImageSignature));
        if(ret!=0)
        {
            UBOOT_ERROR("Get signature fail\n");
            return ret;
        }
        if (-1 == Secure_doAuthentication(u8ImagePublicKeyN, u8ImagePublicKeyE,u8ImageSignature, (U8 *)FILESYSTEM_AUTHENTICATION_BUFFER_ADDR, (U32)size))
        {
            UBOOT_ERROR("Auth. %s FAIL\n",volume);
            DisablePartialAuthentication();

            UBOOT_DEBUG("\033[0;31m Image public-N key=\033[0m\n");
            UBOOT_DUMP((U32)u8ImagePublicKeyN, RSA_PUBLIC_KEY_N_LEN);

            UBOOT_DEBUG("\033[0;31m Image public-E key=\033[0m\n");
            UBOOT_DUMP((U32)u8ImagePublicKeyE, RSA_PUBLIC_KEY_E_LEN);

            UBOOT_DEBUG("\033[0;31m %s[%d] signature=\033[0m\n",volume, i);
            UBOOT_DUMP((U32)u8ImageSignature, SIGNATURE_LEN);

            UBOOT_DEBUG("\033[0;31m %s[%d] image=\033[0m\n",volume, i);
            UBOOT_DUMP((U32)FILESYSTEM_AUTHENTICATION_BUFFER_ADDR, 0x100);
            return -1;

        }
        else
        {
            #if defined(CONFIG_SECURE_DEBUG_MESSAGE)
            UBOOT_INFO("\033[0;34m*****************************\033[0m\n");
            UBOOT_INFO("\033[0;34m* %s Authentication SUCCESS !! *\033[0m\n",volume);
            UBOOT_INFO("\033[0;34m*****************************\033[0m\n");
            #endif
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

int do_AN_Authenticate(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
		int ret = -1;
		U32 addr=0;
    UBOOT_TRACE("IN\n");

    if(argc!=2)
    {
        cmd_usage(cmdtp);
        return -1;
    }

    addr=simple_strtoul(argv[1], NULL, 16);
    if(isBootToRecovery())
	{
		ret=RawData_Authentication("recovery",addr);
    }
	else
	{
        ret=RawData_Authentication("boot",addr);
    }

    if(-1 == ret)
    {
        UBOOT_ERROR("authenticate %s fail\n",argv[1]);
        return -1;
    }
    else
    {
        #if defined (CONFIG_SecureStorage)
        char cmd[128];
        memset(cmd, 0, 128);
        if (-1 == Chunk_Authentication("chunk",0x5E900000)){
            if (-1 == Chunk_Authentication("chunkbackup",0x5E900000))
			{
                Secure_HaltCPU();
            }
			else
			{
                snprintf(cmd , sizeof(cmd) - 1, "mmc read.p 0x5E900000 chunkbackup 0x00100000");
                run_command(cmd, 0);
                snprintf(cmd , sizeof(cmd) - 1, "mmc write.p 0x5E900000 chunk 0x00100000");
                run_command(cmd, 0);
            }
    }
    #endif
        UBOOT_TRACE("OK\n");
        return 0;
    }

}


int do_Authenticate(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");

    if((argc<2)||(argc>3))
    {
        cmd_usage(cmdtp);
        return -1;
    }

    int CacheBufAddr =0;
    if(argc==3)
    {
        CacheBufAddr=simple_strtoul(argv[2], NULL, 16);
    }

    int ret = -1;
    if(0 == IsRawDataPartition(argv[1]))
    {
        ret = do_Authenticate_RawData(argv[1],CacheBufAddr);
    }
    else if(0 == IsFileSystemPartition(argv[1]))
    {
        ret = do_Authenticate_FileSystem(argv[1]);
    }
    else
    {
         UBOOT_ERROR("Invalid volume name:%s.\n",argv[1]);
         return -1;
    }
    if(-1 == ret)
    {
        UBOOT_ERROR("authenticate %s fail\n",argv[1]);
        Secure_HaltCPU();
        return -1;
    }
    else
    {
        UBOOT_TRACE("OK\n");
        return 0;
    }

}

int do_Authenticate_RawData(char* KLName, int CacheBufAddr)
{
    UBOOT_TRACE("IN\n");
    U32 kernelSize = 0;
    int ret=0;
    int VirtWorkBuf=0;
	char *cmd = malloc(CMD_BUF);
    if(cmd == NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(cmd,0,CMD_BUF);
    ret = GetImageSize(KLName,0, &kernelSize);
    if (0 != ret)
    {
        UBOOT_ERROR("get %s size fail\n",KLName);
        return -1;
    }

    if(CacheBufAddr==0){
        VirtWorkBuf =FILESYSTEM_AUTHENTICATION_BUFFER_ADDR;
    }
    else{
        VirtWorkBuf=CacheBufAddr;
    }

    #if (ENABLE_MODULE_NAND_FLASH==1) || (ENABLE_MODULE_SPI_NAND_FLASH==1)
    snprintf(cmd,CMD_BUF,"nand read.e %x %s %x",(unsigned int)VirtWorkBuf,KLName,kernelSize);
    #endif
    #if(ENABLE_MODULE_MMC==1)
    snprintf(cmd,CMD_BUF,"mmc read.p %x %s %x",(unsigned int)VirtWorkBuf,KLName,kernelSize);
    #endif
    UBOOT_DEBUG("cmd=%s\n",cmd);
    ret = run_command(cmd,0);
    if(-1 == ret)
    {
        free(cmd);
        UBOOT_ERROR("read kernel fail\n");
        return -1;
    }
    ret = _RawData_Authentication(KLName,(unsigned int)VirtWorkBuf);
    if(-1 == ret)
    {
        free(cmd);
        UBOOT_ERROR("Authenticate %s fail\n",KLName);
        Secure_HaltCPU();
        return -1;
    }
    free(cmd);
    UBOOT_TRACE("OK\n");
    return 0;
}

int do_Authenticate_FileSystem(char *fileSystemName)
{
    int ret=0;
    UBOOT_TRACE("IN\n");

    if(fileSystemName==NULL)
    {
        UBOOT_ERROR("The input parameter is a null pointer\n");
        return -1;
    }

    ret=ImageIOInit("UBI");
    if(ret==-1)
    {
        UBOOT_ERROR("Image IO init fail\n");
        return -1;
    }

    ret=IsImageRight(fileSystemName);
    if(ret==-1)
    {
        UBOOT_ERROR("Authenticate %s fail\n",fileSystemName);
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}



int do_verify_sha256(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int intAddr;
    unsigned int intLen;
    unsigned int outAddr;
    unsigned int count;
    unsigned int i,j;
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(argc<5) {
        cmd_usage(cmdtp);
        return -1;
    }

    intAddr=simple_strtoul(argv[1], NULL, 16);
    outAddr=simple_strtoul(argv[2], NULL, 16);
    intLen=simple_strtoul(argv[3], NULL, 16);
    count=simple_strtoul(argv[4], NULL, 16);
    UBOOT_DEBUG("intAddr=0x%x,outAddr=0x%x,intLen=0x%x,count=0x%x\n",intAddr,outAddr,intLen,count);

    j=1;
    while(count--)
    {
        intAddr=simple_strtoul(argv[1], NULL, 16);
        outAddr=simple_strtoul(argv[2], NULL, 16);
        intLen=simple_strtoul(argv[3], NULL, 16);

        ret=CommonSHA(intAddr, outAddr, intLen);
        UBOOT_INFO("count=%d\n",j);
        for(i=0;i<32;i++,outAddr++){
            UBOOT_INFO("0x%x ",*(unsigned char *)outAddr);
        }

        UBOOT_INFO("\n");
        j++;
        if(ret!=0)
        {
            break;
        }
    }

    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("verify fail\n");
    }
    return 0;
}


int do_sha256(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int intAddr;
    unsigned int intLen;
    unsigned int outAddr;
    unsigned int i;
    UBOOT_TRACE("IN\n");
    if(argc<4) {
        cmd_usage(cmdtp);
        return -1;
    }
    intAddr=simple_strtoul(argv[1], NULL, 16);
    outAddr=simple_strtoul(argv[2], NULL, 16);
    intLen=simple_strtoul(argv[3], NULL, 16);

    CommonSHA(intAddr, outAddr, intLen);

    for(i=0;i<32;i++,outAddr++){
        UBOOT_INFO("0x%x ",*(unsigned char *)outAddr);
    }

    UBOOT_INFO("\n");
    UBOOT_TRACE("OK\n");
    return 0;
}


int do_rsa(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    unsigned int signAddr;
    unsigned int keyAddr;
    unsigned int outputAddr;
    unsigned int i;
    UBOOT_TRACE("IN\n");
    if(argc<4) {
        cmd_usage(cmdtp);
        return -1;
    }
    UBOOT_INFO("\n---- rsa 256 cacluate -----\n");
    signAddr=simple_strtoul(argv[1], NULL, 16);
    keyAddr=simple_strtoul(argv[2], NULL, 16);
    outputAddr=simple_strtoul(argv[3], NULL, 16);

    rsa_main((unsigned char *)signAddr, (unsigned char *)keyAddr, (unsigned char *)(keyAddr+256), (unsigned char *)outputAddr);
    for(i=0;i<32;i++,outputAddr++){
        UBOOT_INFO("0x%x ",*(unsigned char *)outputAddr);
    }
    UBOOT_INFO("\n");
    UBOOT_TRACE("OK\n");
    return 0;

}

U32 *getHash0PublicKeyN(void)
{
    UBOOT_TRACE("IN\n");
#if (ENABLE_MSTAR_MONACO == 1)
    #define RSA_PUBLIC_ADDR_N 0x20010000
    UBOOT_DEBUG("FROM DRAM:0x%x\n",RSA_PUBLIC_ADDR_N);
    UBOOT_TRACE("OK\n");
    return (U32*)RSA_PUBLIC_ADDR_N;
#else    
    UBOOT_DEBUG("MS_RIU_MAP is 0x%x\n",(U32)MS_RIU_MAP);    
    UBOOT_DEBUG("(U32)RIU[(POR_STATUS_BASE_ADDR+(0xB<<1))]=0x%x\n",((U32)RIU[(POR_STATUS_BASE_ADDR+(0xB<<1))]));
    UBOOT_TRACE("OK\n");
    return (U32 *)(CONFIG_SRAM_BASE_ADDRESS+((U32)RIU[(POR_STATUS_BASE_ADDR+(0xB<<1))]));
#endif
}

U32 *getHash0PublicKeyE(void)
{
    UBOOT_TRACE("IN\n");

#if (ENABLE_MSTAR_MONACO == 1)
    #define RSA_PUBLIC_ADDR_E 0x20010100
    UBOOT_DEBUG("FROM DRAM:0x%x\n",RSA_PUBLIC_ADDR_E);
    UBOOT_TRACE("OK\n");
    return (U32*)RSA_PUBLIC_ADDR_E;
#else    
    UBOOT_DEBUG("MS_RIU_MAP is 0x%x\n",(U32)MS_RIU_MAP);    
    UBOOT_DEBUG("(U32)RIU[(POR_STATUS_BASE_ADDR+(0xA<<1))]=0x%x\n",((U32)RIU[(POR_STATUS_BASE_ADDR+(0xA<<1))]));    
    UBOOT_TRACE("OK\n");
    return (U32 *)(CONFIG_SRAM_BASE_ADDRESS+((U32)RIU[(POR_STATUS_BASE_ADDR+(0xA<<1))]));
#endif
}

BOOLEAN isCustomerKeyBankValid(CUSTOMER_KEY_BANK *pCusKey)
{
    #define SIZE (sizeof(CUSTOMER_KEY_BANK)-sizeof(_SUB_SECURE_INFO))

    UBOOT_TRACE("IN\n");

    U32  *pHash0E=NULL;
    U32  *pHash0N=NULL;
    U32 publicKeyN[(RSA_PUBLIC_KEY_N_LEN/4)];
    U32 publicKeyE[(RSA_PUBLIC_KEY_E_LEN/4)];
    U32 idx=0;
    if(pCusKey==NULL)
	{
		UBOOT_ERROR("pCusKey is a null pointer\n");
		return FALSE;
	}
    pHash0E = getHash0PublicKeyE();
    pHash0N = getHash0PublicKeyN();
    UBOOT_DEBUG("pHash0E is at 0x%x\n",(U32)pHash0E);
    UBOOT_DEBUG("pHash0N is at 0x%x\n",(U32)pHash0N);
    for(idx=0;idx<(RSA_PUBLIC_KEY_N_LEN/4);idx++)
    {
        #if (ENABLE_MSTAR_MONACO == 1)
            publicKeyN[idx]=*pHash0N;
        #else
            publicKeyN[(RSA_PUBLIC_KEY_N_LEN/4)-1-idx]=*pHash0N;
        #endif
		
        pHash0N++;
    }

    for(idx=0;idx<(RSA_PUBLIC_KEY_E_LEN/4);idx++)
    {
        publicKeyE[(RSA_PUBLIC_KEY_E_LEN/4)-1-idx]=*pHash0E;
        pHash0E++;
    }
    UBOOT_DUMP((U32)publicKeyE,0x100);
    UBOOT_DUMP((U32)publicKeyN,0x100);

	if (-1 == Secure_doAuthentication((U8 *)publicKeyN, (U8 *)publicKeyE, pCusKey->customer.u8Signature, (U8 *)pCusKey->u8RSABootPublicKey, SIZE))
	{
	    UBOOT_DUMP((U32)pCusKey->u8RSABootPublicKey,SIZE);
	    //jump_to_console();
	    return FALSE;
	}
	UBOOT_DEBUG("Customer keybank is valid\n");
	UBOOT_TRACE("OK\n");
	return TRUE;

    #undef SIZE
}
BOOLEAN isCustomerKeyBankCipher(U32 keyBankOffset,U32 keyBankSize,U32 tempDRAMAddr)
{
    CUSTOMER_KEY_BANK *pCusKey = NULL;
    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("keyBankOffset=0x%x\n",keyBankOffset);
    UBOOT_DEBUG("keyBankSize=0x%x\n",keyBankSize);
    pCusKey = (CUSTOMER_KEY_BANK *)tempDRAMAddr;
	#ifdef CONFIG_DOUBLE_MBOOT
	mbootbak_raw_io_Config();
	#endif
    raw_read(tempDRAMAddr,keyBankOffset,keyBankSize);
    if(0 != memcmp(u8MagicID,pCusKey->u8MagicID,sizeof(u8MagicID)))
    {
         UBOOT_DEBUG("Customer KeyBank is cipher text \n");
         UBOOT_TRACE("OK\n");
         return TRUE;
    }

    UBOOT_DEBUG("Customer KeyBank is plain text \n");
    UBOOT_TRACE("OK\n");
    return FALSE;
}

int _EncryptCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeySize,U32 tempDRAMAddr)
{
    UBOOT_TRACE("IN\n");
    //Encrpt the Customer key bank, and
    //isCustomerKeyBankCipher had already loaded the CustomerKeyBank into stCusKey
    if(IsHouseKeepingBootingMode()==TRUE)
    {
        // use Efuse Key
        Secure_AES_ECB_Encrypt(tempDRAMAddr,u32CusKeySize,NULL);
    }
    else
    {
        #if !defined(CONFIG_MSTAR_CLEANBOOT)
        //In this case, customer keybank is encrypted by secure processor(8051),
        //and secure processor encrypt 64KBytes data one time.
        u32CusKeySize=CUSTOMER_KEY_BANK_LEN;
        SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
        raw_read(tempDRAMAddr,u32CusKeyOffset,u32CusKeySize);
        flush_cache(tempDRAMAddr,u32CusKeySize);
        Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct, E_AES_EFUSE_KEY, AES_KEY_LEN,E_KEY_NO_SWAP);
        Secure_MailBox_AESEncode(&SecureBootMbxRetStruct, VA2PA(tempDRAMAddr),u32CusKeySize , SECURE_ENG_AES_MODE_ECB);
        #endif
    }

    UBOOT_TRACE("IN\n");
    return 0;
}

int EncryptCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeyBackUpOffset, U32 u32CusKeySize,U32 tempDRAMAddr)
{
    UBOOT_TRACE("IN\n");
    if(_EncryptCustomerKeyBank(u32CusKeyBackUpOffset,u32CusKeySize,tempDRAMAddr)==-1)
    {
        UBOOT_ERROR("encrypt key bank fail\n");
        return  -1;
    }

    #ifdef CONFIG_DOUBLE_MBOOT
	mbootbak_raw_io_Config();
	#endif
	if(raw_write(tempDRAMAddr,u32CusKeyOffset,u32CusKeySize)!=0)
		{
			UBOOT_ERROR("fail\n");
			return -1;
		}

    if(raw_write(tempDRAMAddr,u32CusKeyBackUpOffset,u32CusKeySize)!=0)
    {
         UBOOT_ERROR("encrypt key bank backup fail\n");
         return  -1;
    }

#if defined (CONFIG_MSTAR_ROM_BOOT_WITH_NAND_FLASH)
    // Because system has double mboot in rom boot with nand,
    // so we mustdecrypt another keybank, too.
        raw_io_config_push();

        raw_io_config(E_RAW_DATA_IN_NAND,"MBOOTBAK",UNNECESSARY_VOLUME);
        if(raw_write(tempDRAMAddr,u32CusKeyOffset,u32CusKeySize)!=0)
        {
            UBOOT_ERROR("encrypt key bank backup fail in MBOOTBAK\n");
            return -1;
        }

        if(raw_write(tempDRAMAddr,u32CusKeyBackUpOffset,u32CusKeySize)!=0)
        {
             UBOOT_ERROR("encrypt key bank backup fail in MBOOTBAK\n");
             return  -1;
        }

        raw_io_config_pop();
#endif

    UBOOT_TRACE("OK\n");
    return 0;
}

int copyKeyBank(U32 destOffset, U32 srcOffset, U32 size, U32 tempDRAMAddr)
{
    UBOOT_TRACE("IN\n");
    if(raw_read(tempDRAMAddr,srcOffset,size)!=0)
    {
        UBOOT_ERROR("fail\n");
        return -1;
    }

    if(raw_write(tempDRAMAddr,destOffset,size)!=0)
    {
        UBOOT_ERROR("fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int setKeyBankProcessStatusDone(void)
{
    UBOOT_TRACE("IN\n");

    if(_setKeyBankProcessStatus(1)!=0)
    {
         UBOOT_ERROR("sete down\n");
         return -1;
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

int clearKeyBankProcessStatus(void)
{
    UBOOT_TRACE("IN\n");

    if(_setKeyBankProcessStatus(0)!=0)
    {
         UBOOT_ERROR("sete down\n");
         return -1;
    }
    UBOOT_TRACE("OK\n");
    return 0;
}


int _setKeyBankProcessStatus(char value)
{
    UBOOT_TRACE("IN\n");
    char buf[CMD_BUF];

    raw_io_config_push();
    snprintf(buf,CMD_BUF,"setenv %s %x;saveenv",ENV_KEYBANK_DONE,value);
    if(run_command(buf,0)!=0)
    {
         UBOOT_ERROR("setenv fail\n");
         return -1;
    }
    raw_io_config_pop();
    UBOOT_TRACE("OK\n");
    return 0;
}

int IsKeyBankProcessDone(char *env, BOOLEAN *pDone)
{
    UBOOT_TRACE("IN\n");
    char *ptr=NULL;
    if(env==NULL)
    {
        *pDone=FALSE;
        UBOOT_ERROR("env is a null pointer\n");
        return -1;
    }
    if(pDone==NULL)
    {
        *pDone=FALSE;
        UBOOT_ERROR("pDone is a null pointer\n");
        return -1;
    }
    ptr=getenv(env);
    if(ptr==NULL)
    {
       *pDone=FALSE;

    }
    else
    {
        if(strcmp(ptr,"1")==0)
        {
            *pDone=TRUE;
        }
        else
        {
            *pDone=FALSE;
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;

}


int RestoreCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeySize,U32 tempDRAMAddr)
{
// Here,there are 3 cases  that will be happened on customer keybank.
// case 1: KeyBank, and KeyBankBackup are both plaintext.
// case 2: keyBank is not plaintext, and KeyBankBackup is plaintext
// case 3: keyBank and KeyBankBackup aren't both plaintext, but env doesn't appear that the status is done.
// In case 1, uboot will encrypt these two keybanks, and setup the status on env.
// In case 2, uboot asssumes that something happened during writting keyBank, and uboot recover keyBank by keyBankBackup.
// In case 3, uboot asssumes that something happened during writting keyBankBackup, and uboot recover keyBankBackup by KeyBank.
#define KEY_BANK_OFFSET u32CusKeyOffset
#define KEY_BANK_BACKUP_OFFSET (u32CusKeyOffset+CUSTOMER_KEY_BANK_LEN)
    U8 u8Encrypt=0;
    U8 u8Restore=0;
    BOOLEAN IsKeyBankDone=FALSE;

    UBOOT_TRACE("IN\n");
    UBOOT_DEBUG("u32CusKeyOffset=0x%x\n",u32CusKeyOffset);

    if(isCustomerKeyBankCipher(KEY_BANK_OFFSET,u32CusKeySize,tempDRAMAddr)== FALSE)
    {
        u8Encrypt++;
        UBOOT_DEBUG("Keybank doesn't encrypt\n");
    }

    if(isCustomerKeyBankCipher(KEY_BANK_BACKUP_OFFSET,u32CusKeySize,tempDRAMAddr)== FALSE)
    {
        u8Encrypt++;
        UBOOT_DEBUG("KeybankBackup doesn't encrypt\n");
    }
    //"IsKeyBankProcessDone" must be behind of "isCustomerKeyBankCipher"
    if(IsKeyBankProcessDone(ENV_KEYBANK_DONE,&IsKeyBankDone)==-1)
    {
        UBOOT_ERROR("fail\n");
        return -1;
    }

    if(IsKeyBankDone==FALSE)
    {
        u8Restore++;
    }



    if(u8Encrypt>0)
    {
       UBOOT_INFO("Customer key bank is not encrypted\n");
       clearKeyBankProcessStatus();
       if(EncryptCustomerKeyBank(KEY_BANK_OFFSET,KEY_BANK_BACKUP_OFFSET,u32CusKeySize,tempDRAMAddr)==-1)
        {
            UBOOT_ERROR("Encrypt key bank fail\n");
            return  -1;
       }
        IsKeyBankDone = FALSE;
    }
    else
    {
        if(u8Restore>0)
        {
            if(copyKeyBank(KEY_BANK_BACKUP_OFFSET, KEY_BANK_OFFSET, u32CusKeySize, tempDRAMAddr)==-1)
            {
                UBOOT_ERROR("copy key bank fail\n");
                return -1;
            }
        }
    }

    if(FALSE == IsKeyBankDone)
    {
        if(setKeyBankProcessStatusDone()==-1)
        {
            UBOOT_ERROR("fail\n");
            return -1;
        }
    }
#if ( CONFIG_VESTEL_MB97 == 1 )    //ENHANCE_BOOTING_TIME
    run_command("updatemiureg",0);
#else
    if((u8Encrypt>0)||(u8Restore>0))
    {
        if(run_command("reset",0)!=0)
        {
          UBOOT_ERROR("reset cmd fail\n");
          return -1;
        }
    }

#endif

    UBOOT_TRACE("OK\n");
    return 0;
}



int Secure_Drv_Init(void)
{
    BOOLEAN ret=TRUE;
    UBOOT_TRACE("IN\n");

    #if defined(CONFIG_MSTAR_CLEANBOOT)
    ret = Secure_MailBox_Init();
    #else
    if(IsHouseKeepingBootingMode()==FALSE)
    {
        ret=Secure_MailBox_Init();
    }
    #endif

    EnableAESDAMClock();

    if(ret==FALSE)
    {
        UBOOT_ERROR("Secure_Drv_Init fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int LoadSignature(void)
{
    UBOOT_TRACE("IN\n");
    if(SignatureLoad((SECURITY_INFO *)&stSecureInfo)!=EN_SUCCESS)
    {
        UBOOT_ERROR("Load signature fail\n");
        return -1;
    }

    if(CheckSignature((SECURITY_INFO *)&stSecureInfo) == -1)
    {
        UBOOT_ERROR("Check signature fail\n");
        return -1;
    }
    UBOOT_TRACE("OK\n");
    return 0;
    }
int CopyCustomerKeyBank(U32 u32DramAddr)
{

	UBOOT_TRACE("IN\n");
    if(0 != memcmp(u8MagicID,stCusKey.u8MagicID,sizeof(u8MagicID)))
	{
		UBOOT_ERROR("Customer keybank is not ready");
		return -1;
	}
    UBOOT_DEBUG("u32DramAddr =%x\n",u32DramAddr);
	memcpy((void *)u32DramAddr,&stCusKey,sizeof(CUSTOMER_KEY_BANK));
	flush_cache(u32DramAddr,(U32)sizeof(CUSTOMER_KEY_BANK));

	UBOOT_TRACE("OK\n");
	return 0;
}

int LoadCustomerKeyBank(void)
{
    U32 u32CusKeyOffset = 0;
    U32 u32HwAesPABufAddr=0;
    U32 u32HwAesVABufAddr=0;
    U32 u32HwAesBufLen=0;

    UBOOT_TRACE("IN\n");
    raw_io_config_push();
    if(mboot_raw_io_Config() != 0)
    {
        UBOOT_ERROR("raw_io_config setting fail!\n");
        return -1;
    }

    get_addr_from_mmap("MMAP_HW_AES_BUF", &u32HwAesPABufAddr);	//MB100_BRINGUP
    get_length_from_mmap("MMAP_HW_AES_BUF", &u32HwAesBufLen);	//MB100_BRINGUP
    u32HwAesVABufAddr=(AES_DECRYPTED_ADDR|u32HwAesPABufAddr);

    UBOOT_DEBUG("u32HwAesPABufAddr=%x \n",u32HwAesPABufAddr);
    UBOOT_DEBUG("u32HwAesBufLen=%x \n",u32HwAesBufLen);
    UBOOT_DEBUG("u32HwAesVABufAddr=%x \n",u32HwAesVABufAddr);

    if(MsApiChunkHeader_GetValue(CH_CUSTOMER_KEY_BANK_ROM_OFFSET,&u32CusKeyOffset)== -1)
    {
        UBOOT_ERROR("Secure_Drv_Init fail\n");
        return -1;
    }

    if(RestoreCustomerKeyBank(u32CusKeyOffset,sizeof(stCusKey),u32HwAesVABufAddr)==-1)
    {
        UBOOT_ERROR("restore key bank fail\n");
        return -1;
    }

    ///Warning: "_LoadCustomerKeyBank" must behind of "SignatureLoad".
    ///why??
    ///Becase we have a simple secure booting solution on MIPS booting mode.
    ///In this case, we store both the sensitive keys and signatures in "SECURITY_INFO" in SPI.
    ///So, we have to do "SignatureLoad" first, and then copy the sensitive keys from stSecureInfo.
    if(_LoadCustomerKeyBank(u32CusKeyOffset,sizeof(stCusKey),u32HwAesVABufAddr) == -1)
    {
       UBOOT_ERROR("Load rsa public key fail\n");
       return -1;
    }

    PopUpProtectedKey();
    raw_io_config_pop();
    UBOOT_TRACE("OK\n");
    return 0;
    }


int do_Secure_Init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret1=0,ret2=0;
    UBOOT_TRACE("IN\n");

    #if defined(CONFIG_MSTAR_CLEANBOOT)
    UBOOT_DEBUG("Secure Boot with CleanBoot\n");
    #endif

	if(Secure_Drv_Init()==-1)
    {
        UBOOT_ERROR("Secure_drv_Init fail\n");
        //jump_to_console();
        return 0;
    }

    ret1=LoadSignature();
    ret2=LoadCustomerKeyBank();

    if((ret1!=0)||(ret2!=0))
    {
       //jump_to_console();
       return 0;
    }

#if defined(CONFIG_SECURE_SPI_PROTECT)
    spi_write_protect_process_init();
#endif

   UBOOT_TRACE("OK\n");
   return 0;
}

//WARNING: This function shoule be revomed from MstarApp.This kind of behavior must be in MstarCore
#if defined(__ARM__)
#define TSPCLK_MAP  0x1F2016A8
#else
#define TSPCLK_MAP  0xBF2016A8
#endif
#define TSP      ((unsigned char volatile *) TSPCLK_MAP)
void EnableAESDAMClock(void)
{
    TSP[0]=0x0;
}

int do_DumpSignature(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");

    if(argc!=2)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    UBOOT_INFO("data.%s\n",argv[1]);
    _SUB_SECURE_INFO * pSubAddr = getSubSecureInfo(&stSecureInfo,argv[1],FALSE);
    if( NULL == pSubAddr)
    {
        UBOOT_ERROR("get _SUB_SECURE_INFO error\n");
        return -1;
    }
    if(0 == IsFileSystemPartition(argv[1]))
    {
        _dump((unsigned int)pSubAddr,sizeof(_SUB_SECURE_INFO)*FRAGMENT_NUM);
    }
    else
    {
        _dump((unsigned int)pSubAddr,sizeof(_SUB_SECURE_INFO));
    }
    if(TRUE == IsInterleaveMode())
    {
        UBOOT_INFO("data_interleave.%s\n",argv[1]);
        pSubAddr = getSubSecureInfo(&stSecureInfo,argv[1],TRUE);
        if( NULL == pSubAddr)
        {
            UBOOT_ERROR("get _SUB_SECURE_INFO error\n");
            return -1;
        }
        if(0 == IsFileSystemPartition(argv[1]))
        {
            _dump((unsigned int)pSubAddr,sizeof(_SUB_SECURE_INFO)*FRAGMENT_NUM);
        }
        else
        {
            _dump((unsigned int)pSubAddr,sizeof(_SUB_SECURE_INFO));
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;

}

int CheckSignature(SECURITY_INFO *sign)
{
    unsigned int i;

    UBOOT_TRACE("IN\n");
    if(sign==NULL)
    {
        UBOOT_ERROR("The input parameter 'sign' is a null pointer\n");
        return -1;
    }
    char u8SecIdentify[8] = "\0";
    getSecIdentify(u8SecIdentify,sign,FALSE);
    if(0 != memcmp((const void *)u8SecIdentify,(const void *)idForContinueMode, sizeof(idForContinueMode)))
    {
        UBOOT_ERROR("\033[0;31m********************************\033[0m\n");
        UBOOT_ERROR("\033[0;31m !!SecureInfo ID compare fail   \033[0m\n");
        UBOOT_ERROR("\033[0;31m Please do sw upgrade           \033[0m\n");
        UBOOT_ERROR("\033[0;31m********************************\033[0m\n");
        return -1;
    }

    if(IsHouseKeepingBootingMode()==FALSE)
    {
        for(i=0;i<RSA_PUBLIC_KEY_E_LEN;i++)
        {
            if(sign->data.Key.u8RSAKernelPublicKey[RSA_PUBLIC_KEY_N_LEN+i]!=0xFF)
                break;
        }

        if(i!=RSA_PUBLIC_KEY_E_LEN){
            UBOOT_ERROR("\x1b[37;41m ===== [%s:%s:%d] Wrong Data in Secure Info !!! ===== \x1b[0m\n",__FILE__,__FUNCTION__,__LINE__);
            return -1;
        }
    }
    UBOOT_TRACE("OK\n");
    return 0;
}


int RawData_Authentication(char *KLName,unsigned int u32kernelAddr)
{
    UBOOT_TRACE("IN\n");
    if(-1 == _RawData_Authentication(KLName,u32kernelAddr))
    {
        Secure_HaltCPU();
    }
    UBOOT_TRACE("OK\n");
    return 0;
}
int _RawData_Authentication(char* KLName,unsigned int u32kernelAddr)
{
    U32 kernelSize=0;
    U8 u8ImagePublicKeyN[RSA_PUBLIC_KEY_N_LEN];
    U8 u8ImagePublicKeyE[RSA_PUBLIC_KEY_E_LEN];
    U8 u8ImageSignature[SIGNATURE_LEN];
    int ret=0;
    UBOOT_TRACE("IN\n");
    ret = IsRawDataPartition(KLName);
    if( 0 != ret)
    {
        UBOOT_ERROR("Invalid KLName :%s\n",KLName);
        return -1;
    }
    ret = GetImageSize(KLName,0,&kernelSize);
    if (0 != ret)
    {
        UBOOT_ERROR("get %s image size fail\n",KLName);
        return -1;
    }
    #if defined(CONFIG_SECURE_ENCRYPT_RAWDATA)
    ret = DecryptKernelImage((char *)u32kernelAddr,kernelSize);
    if(-1 == ret)
    {
        UBOOT_ERROR("\033[0;31m Dercypt %s FAIL\033[0m\n",KLName);
        return -1;
    }
    #endif//#if defined(CONFIG_SECURE_ENCRYPT_RAWDATA)
    flush_cache(u32kernelAddr,(U32)kernelSize);
    GetPublicKeyN(E_RSA_IMAGE_PUBLIC_KEY, u8ImagePublicKeyN, sizeof(u8ImagePublicKeyN));
    GetPublicKeyE(E_RSA_IMAGE_PUBLIC_KEY, u8ImagePublicKeyE, sizeof(u8ImagePublicKeyE));
    GetSignature(KLName, 0, u8ImageSignature, sizeof(u8ImageSignature));
    if (-1 == Secure_doAuthentication(u8ImagePublicKeyN, u8ImagePublicKeyE, u8ImageSignature, (U8 *)u32kernelAddr, kernelSize))
    {
        UBOOT_ERROR("\033[0;31m Auth  %s FAIL\033[0m\n",KLName);
        UBOOT_DEBUG("\033[0;31m RSA image public-N key=\033[0m\n");
        UBOOT_DUMP((U32)u8ImagePublicKeyN, RSA_PUBLIC_KEY_N_LEN);

        UBOOT_DEBUG("\033[0;31m RSA image public-E key=\033[0m\n");
        UBOOT_DUMP((U32)u8ImagePublicKeyE, RSA_PUBLIC_KEY_E_LEN);

        UBOOT_DEBUG("\033[0;31m %s signature=\033[0m\n",KLName);
        UBOOT_DUMP((U32)u8ImageSignature, SIGNATURE_LEN);

        UBOOT_DEBUG("\033[0;31m clear %s image=\033[0m\n",KLName);
        UBOOT_DUMP((U32)u32kernelAddr, 0x100);
        return -1;
    }
    else
    {
        #if defined(CONFIG_SECURE_DEBUG_MESSAGE)
        UBOOT_INFO("\033[0;34m*******************************\033[0m\n");
        UBOOT_INFO("\033[0;34m* %s Authentication SUCCESS !! *\033[0m\n",KLName);
        UBOOT_INFO("\033[0;34m*******************************\033[0m\n");
        #endif
        UBOOT_TRACE("OK\n");
        return 0;
    }
}


int ImageIOInit(char *partition)
{
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(partition==NULL)
    {
        UBOOT_ERROR("partition is a null pointer\n");
        return -1;
    }

    #if (ENABLE_MODULE_NAND_FLASH==1) || (ENABLE_MODULE_SPI_NAND_FLASH==1)
    ret=_ImageIOInitForNand(partition);
    #endif

    #if(ENABLE_MODULE_MMC==1)
    ret=_ImageIOInitForEMMC(partition);
    #endif

    UBOOT_TRACE("OK\n");
    return ret;
}

int _ImageIOInitForEMMC(char *partition)
{
    UBOOT_TRACE("IN\n");
    UBOOT_TRACE("OK\n");
    return 0;
}

int _ImageIOInitForNand(char *partition)
{
    char *buffer=NULL;
    int ret=0;

    UBOOT_TRACE("IN\n");

    if(partition==NULL)
    {
        UBOOT_ERROR("partition is a null pointer\n");
        return -1;
    }

    buffer=(char *)malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(buffer,0,CMD_BUF);

    UBOOT_DEBUG("partition=%s\n",partition);

    snprintf(buffer,CMD_BUF,"ubi part %s",partition);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        free(buffer);
        UBOOT_ERROR("ubi part %s fail\n",partition);
        return -1;
    }


    free(buffer);
    UBOOT_TRACE("OK\n");
    return 0;
}

int ImageRead(char *volume, unsigned int addr, unsigned int offset, unsigned len)
{
    int ret=0;
    UBOOT_TRACE("IN\n");
    ret=_ImageRead(volume, addr, offset, len);
    UBOOT_TRACE("OK\n");
    return 0;
}
int _ImageRead(char *volume, unsigned int addr, unsigned int offset, unsigned len)
{
    char *buffer=NULL;
    int ret=0;

    UBOOT_TRACE("IN\n");

    if(volume==NULL)
    {
        UBOOT_ERROR("volume is a null pointer\n");
        return -1;
    }
    buffer=(char *)malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(buffer,0,CMD_BUF);

    UBOOT_DEBUG("volume=%s\n",volume);
    UBOOT_DEBUG("addr=0x%x\n",(unsigned int)addr);
    UBOOT_DEBUG("offset=0x%x\n",(unsigned int)offset);
    UBOOT_DEBUG("len=0x%x\n",(unsigned int)len);

    flush_cache(addr,(U32)len);
    memset(buffer,0,CMD_BUF);

    #if (ENABLE_MODULE_NAND_FLASH==1) || (ENABLE_MODULE_SPI_NAND_FLASH==1)
    snprintf(buffer,CMD_BUF,"ubi partial_read %x %s %x %x",addr ,volume ,len, offset);
    #endif
    #if(ENABLE_MODULE_MMC==1)
    snprintf(buffer,CMD_BUF,"mmc read.p.continue %x %s %x %x", addr, volume,offset>>9, len);
    #endif

    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        free(buffer);
        UBOOT_ERROR("ubi read %s fail\n",volume);
        return -1;
    }
    flush_cache(addr,(U32)len);
    free(buffer);
    UBOOT_TRACE("OK\n");
    return 0;
}

int ImageWrite(char *volume, unsigned int addr, unsigned int offset, unsigned len)
{
    UBOOT_TRACE("IN\n");
    UBOOT_ERROR("This function is not implement\n");
    UBOOT_TRACE("OK\n");
    return -1;
}

BOOLEAN IsDoingPartialAuthentication(void)
{
    char *ptr=NULL;
    UBOOT_TRACE("IN\n");
    ptr=getenv(ENV_PARTAIL_AUTHENTICATION);
    if(ptr!=NULL){
       if(0==strcmp((const char *)ptr,"OFF"))
       {
         UBOOT_DEBUG("env '%s' is OFF\n",ENV_PARTAIL_AUTHENTICATION);
         UBOOT_TRACE("OK\n");
         return FALSE;
       }
    }
    else
    {
        UBOOT_DEBUG("No env '%s'\n",ENV_PARTAIL_AUTHENTICATION);
        UBOOT_TRACE("OK\n");
        return FALSE;
    }
    UBOOT_TRACE("OK\n");
    return TRUE;
}

int DisablePartialAuthentication(void)
{
    int ret=0;
    char *pEnv=0;
    UBOOT_TRACE("IN\n");
    pEnv=getenv(ENV_PARTAIL_AUTHENTICATION);
    if(pEnv!=NULL)
    {
        if(strstr(pEnv,"OFF")!=0)
        {
            UBOOT_DEBUG("This function is already disable\n");
            UBOOT_TRACE("OK\n");
            return 0;
        }
    }
    ret=setenv(ENV_PARTAIL_AUTHENTICATION, "OFF");
    if(ret==0)
    {
        ret=saveenv();
        if(ret==0)
        {
            UBOOT_TRACE("OK\n");
        }
        else
        {
           UBOOT_ERROR("DisablePartialAuthentication executes saveenv fail\n");
        }
    }
    else
    {
        UBOOT_ERROR("DisablePartialAuthentication executes setenv fail\n");
    }

    return ret;
}

int EnablePartialAuthentication(void)
{
    int ret=0;
    char *pEnv=NULL;
    UBOOT_TRACE("IN\n");

    pEnv=getenv(ENV_PARTAIL_AUTHENTICATION);
    if(pEnv!=NULL)
    {
        if(strstr(pEnv,"ON")!=0)
        {
            UBOOT_DEBUG("This function is already enable\n");
            UBOOT_TRACE("OK\n");
            return 0;
        }
    }
    ret=setenv(ENV_PARTAIL_AUTHENTICATION, "ON");
    if(ret==0)
    {
        ret=saveenv();
        if(ret==0)
        {
            UBOOT_TRACE("OK\n");
        }
        else
        {
           UBOOT_ERROR("EnablePartialAuthentication executes saveenv fail\n");
        }
    }
    else
    {
        UBOOT_ERROR("EnablePartialAuthentication executes setenv fail\n");
    }
    return ret;
}

int CancelBootCmd(void)
{
    int ret=0;
    char *buffer=NULL;
    UBOOT_TRACE("IN\n");
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(buffer,0,CMD_BUF);
    snprintf(buffer,CMD_BUF,"setenv %s",ENV_BOOT_CMD);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        free(buffer);
        UBOOT_ERROR("CancelBootCmd executes setenv fail\n");
        return -1;
    }

    memset(buffer,0,CMD_BUF);
    snprintf(buffer,CMD_BUF,"saveenv");
    UBOOT_DEBUG("cmd=%s\n",buffer);
    ret=run_command(buffer,0);
    if(ret==-1)
    {
        free(buffer);
        UBOOT_ERROR("CancelBootCmd executes saveenv fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return ret;
}

int GetAESKey(KEY_INDEX enKey,U8 *keyBuf)
{
    UBOOT_TRACE("IN\n");
    if(keyBuf==NULL)
    {
        UBOOT_ERROR("The input parameter 'keyBuf' is a null pointer\n");
        return -1;
    }
    if(enKey == E_AES_BOOT_KEY)
    {
        #if defined(CONFIG_SECURE_HW_IP)
        //if call AESDMA ,need to reverse AES key
        int i;
        for(i=0;i<AES_KEY_LEN;i++)
        {
            keyBuf[AES_KEY_LEN-1-i]=stCusKey.u8AESBootKey[i];
        }
        #else
        memcpy(keyBuf,stCusKey.u8AESBootKey,AES_KEY_LEN);
        #endif
    }
    else if(enKey == E_AES_UPGRADE_KEY)
    {
        #if defined(CONFIG_SECURE_HW_IP)
        int i;
        for(i=0;i<AES_KEY_LEN;i++)
        {
            keyBuf[AES_KEY_LEN-1-i]=stCusKey.u8AESUpgradeKey[i];
        }
        #else
        memcpy(keyBuf,stCusKey.u8AESUpgradeKey,AES_KEY_LEN);
        #endif
    }
    else
    {
        UBOOT_ERROR("Wrong AES Key Index !!\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int GetPublicKeyN(KEY_INDEX enKey, U8 *buffer, U32 len)
{
    UBOOT_TRACE("IN\n");
    if(buffer==NULL)
    {
        UBOOT_ERROR("The input parameter 'buffer' is a null pointer\n");
        return -1;
    }

    if(len<RSA_PUBLIC_KEY_N_LEN)
    {
        UBOOT_ERROR("The len is smaller than the lenght of public-N(%d bytes).\n",RSA_PUBLIC_KEY_N_LEN);
        return -1;
    }

    if(enKey == E_RSA_IMAGE_PUBLIC_KEY)
    {
        memcpy(buffer,stCusKey.u8RSAImagePublicKey,RSA_PUBLIC_KEY_N_LEN);
    }
    else if(enKey == E_RSA_UPGRADE_PUBLIC_KEY)
    {
        memcpy(buffer,stCusKey.u8RSAUpgradePublicKey,RSA_PUBLIC_KEY_N_LEN);
    }
    else if(enKey == E_RSA_BOOT_PUBLIC_KEY)
    {
        memcpy(buffer,stCusKey.u8RSABootPublicKey,RSA_PUBLIC_KEY_N_LEN);
    }
    else
    {
        UBOOT_ERROR("Wrong RSA Key Index !!\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int GetPublicKeyE(KEY_INDEX enKey, U8 *buffer, U32 len)
{
    UBOOT_TRACE("IN\n");

    if(buffer==NULL)
    {
        UBOOT_ERROR("The input parameter 'buffer' is a null pointer\n");
        return -1;
    }

    if(len<RSA_PUBLIC_KEY_E_LEN)
    {
        UBOOT_ERROR("The len is smaller than the lenght of public-E(%d bytes).\n",RSA_PUBLIC_KEY_E_LEN);
        return -1;
    }

    if(enKey == E_RSA_IMAGE_PUBLIC_KEY)
    {
        memcpy(buffer,&stCusKey.u8RSAImagePublicKey[RSA_PUBLIC_KEY_N_LEN],RSA_PUBLIC_KEY_E_LEN);
    }
    else if(enKey == E_RSA_UPGRADE_PUBLIC_KEY)
    {
        memcpy(buffer,&stCusKey.u8RSAUpgradePublicKey[RSA_PUBLIC_KEY_N_LEN],RSA_PUBLIC_KEY_E_LEN);
    }
    else if(enKey == E_RSA_BOOT_PUBLIC_KEY)
    {
        memcpy(buffer,&stCusKey.u8RSABootPublicKey[RSA_PUBLIC_KEY_N_LEN],RSA_PUBLIC_KEY_E_LEN);

    }
    else
    {
        UBOOT_ERROR("Wrong Key Index !!\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int GetSignature(char *volume, U8 num, U8 *buffer, U32 len)
{
    UBOOT_TRACE("IN\n");
    if(volume==NULL)
    {
        UBOOT_ERROR("The input parameter 'volume' is a null pointer\n");
        return -1;
    }

    if(buffer==NULL)
    {
        UBOOT_ERROR("The input parameter 'buffer' is a null pointer\n");
        return -1;
    }

    if(len<SIGNATURE_LEN)
    {
        UBOOT_ERROR("The len is smaller than the lenght of signature(%d bytes).\n",SIGNATURE_LEN);
        return -1;
    }
    UBOOT_DEBUG("get %s[%d] signature\n",volume,num);
    _SUB_SECURE_INFO * pSubAddr = getSubSecureInfo(&stSecureInfo,volume,IsInterleaveMode());
    if( NULL == pSubAddr)
    {
        UBOOT_ERROR("get _SUB_SECURE_INFO error\n");
        return -1;
    }
    if(0 == IsFileSystemPartition(volume))
    {
        pSubAddr += num;
    }
    memcpy(buffer,pSubAddr->u8Signature,SIGNATURE_LEN);
    UBOOT_TRACE("OK\n");
    return 0;
}

int GetImageSize(char *volume, U8 num, U32 *size)
{

    UBOOT_TRACE("IN\n");
    if(volume==NULL)
    {
        UBOOT_ERROR("The input parameter 'volume' is a null pointer\n");
        return -1;
    }

    if(size==NULL)
    {
        UBOOT_ERROR("The input parameter 'size' is a null pointer\n");
        return -1;
    }
    UBOOT_DEBUG("get %s[%d] size\n",volume,num);
    _SUB_SECURE_INFO * pSubAddr = getSubSecureInfo(&stSecureInfo,volume,IsInterleaveMode());
    if( NULL == pSubAddr)
    {
        UBOOT_ERROR("get _SUB_SECURE_INFO error\n");
        return -1;
    }
    if(0 == IsFileSystemPartition(volume))
    {
        pSubAddr += num;
    }
    *size = pSubAddr->info.u32Size;
    UBOOT_DEBUG("size=0x%x\n",*size);
    if(*size==0)
    {
        UBOOT_ERROR("wrong image size\n");
        return -1;
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

int GetSubImageNum(char *volume, U32 *num)
{
    UBOOT_TRACE("IN\n");
    if(volume==NULL)
    {
        UBOOT_ERROR("The input parameter 'volume' is a null pointer\n");
        return -1;
    }

    if(num==NULL)
    {
        UBOOT_ERROR("The input parameter 'num' is a null pointer\n");
        return -1;
    }

    UBOOT_DEBUG("get the sub image number of %s\n",volume);
    _SUB_SECURE_INFO * pSubAddr = getSubSecureInfo(&stSecureInfo,volume,IsInterleaveMode());
    if( NULL == pSubAddr)
    {
        UBOOT_ERROR("get _SUB_SECURE_INFO error\n");
        return -1;
    }
    *num = pSubAddr->info.u32Num;
    UBOOT_DEBUG("num=0x%x\n",*num);
    if(*num > FRAGMENT_NUM)
    {
        UBOOT_ERROR("wrong sub image num,larger than FRAGMENT_NUM(%d)\n",FRAGMENT_NUM);
        return -1;
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

int DecryptKernelImage(char *dataBuf, unsigned int len)
{
    int ret=-1;

    UBOOT_TRACE("IN\n");

    if(IsHouseKeepingBootingMode()==FALSE)
    {
        ret=DecryptKernelImageBySecureProcessor(dataBuf, len);
    }
    else
    {
        ret=DecryptKernelImageByHouseKeeping(dataBuf, len);
    }

    if(ret==-1)
    {
        UBOOT_ERROR("Decrypte kernel image fail\n");
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return ret;
}

int DecryptKernelImageBySecureProcessor(char *dataBuf, unsigned int len)
{
    #if !defined(CONFIG_MSTAR_CLEANBOOT)
    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
    SECUREBOOT_Result Result;
    int ret=-1;
    UBOOT_TRACE("IN\n");

    flush_cache((U32)dataBuf,(U32)len);
    Chip_Flush_Memory();

    Result=Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct,E_AES_BOOT_KEY,AES_KEY_LEN,E_KEY_SWAP);
    if(Result==E_SECUREBOOT_OK)
    {
        Result=Secure_MailBox_AESDecode(&SecureBootMbxRetStruct, VA2PA((U32)dataBuf), len, SECURE_ENG_AES_MODE_ECB);
        if(Result==E_SECUREBOOT_OK)
        {
            ret=0;
        }
        else
        {
            UBOOT_DEBUG("aes decrypte fail\n");
            ret=-1;
        }
    }
    else
    {
        UBOOT_DEBUG("Assign aes decrypted key fail\n");
        ret=-1;
    }


    if(ret==-1)
    {
        UBOOT_ERROR("Decrypte kernel image by secure processor fail\n");
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return ret;

    #else  //#if !defined(CONFIG_MSTAR_CLEANBOOT)
    return 0;
    #endif
}

int DecryptKernelImageByHouseKeeping(char *dataBuf, unsigned int len)
{
    int ret=-1;
    UBOOT_TRACE("IN\n");
    flush_cache((U32)dataBuf,(U32)len);
    Chip_Flush_Memory();
    U8 u8Key[AES_KEY_LEN]="\0";
    GetAESKey(E_AES_BOOT_KEY,u8Key);
    UBOOT_DUMP((unsigned int)u8Key,AES_KEY_LEN);
    ret=Secure_AES_ECB_Decrypt((U32)(dataBuf), len, (U8 *)u8Key);
    if(-1 == ret)
    {
        UBOOT_ERROR("Decrypte kernel image by hostkeeping fail\n");
    }
    else
    {
        UBOOT_TRACE("OK\n");
    }

    return ret;
}


int _LoadCustomerKeyBank(U32 u32CusKeyOffset,U32 u32CusKeySize,U32 u32HwAesVABufAddr)
{
    UBOOT_TRACE("IN\n");
    if(IsHouseKeepingBootingMode()==FALSE)
    {
        #if !defined(CONFIG_MSTAR_CLEANBOOT)
        //In this case, secure processor holds all clean customer's key. And it only allow us to get the rsa public key.
        SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
        UBOOT_DEBUG("flush memory\n");
        flush_cache((U32)u32HwAesVABufAddr,RSA_PUBLIC_KEY_LEN); //Chip_Flush_Memory();
        // get RSA_IMAGE_PUBLIC_KEY
        if(E_SECUREBOOT_OK!=Secure_MailBox_GetKey(&SecureBootMbxRetStruct,(U32)u32HwAesVABufAddr,E_RSA_IMAGE_PUBLIC_KEY,RSA_PUBLIC_KEY_LEN))
        {
            return -1;
        }
        memcpy((void *)stCusKey.u8RSAImagePublicKey,(void *)u32HwAesVABufAddr,RSA_PUBLIC_KEY_LEN);

        // get RSA_UPGRADE_PUBLIC_KEY
        flush_cache((U32)u32HwAesVABufAddr,RSA_PUBLIC_KEY_LEN); //Chip_Flush_Memory();
        if(E_SECUREBOOT_OK!=Secure_MailBox_GetKey(&SecureBootMbxRetStruct,(U32)u32HwAesVABufAddr,E_RSA_UPGRADE_PUBLIC_KEY,RSA_PUBLIC_KEY_LEN))
        {
            return -1;
        }
        memcpy((void *)stCusKey.u8RSAUpgradePublicKey,(void *)u32HwAesVABufAddr,RSA_PUBLIC_KEY_LEN);
        #endif
    }
    else
    {
        if(IsBootingFromMaskRom()==TRUE)
        {
            #ifdef CONFIG_DOUBLE_MBOOT
			mbootbak_raw_io_Config();
			#endif
            if(raw_read(u32HwAesVABufAddr,u32CusKeyOffset,u32CusKeySize)!= 0)
            {
                UBOOT_ERROR("Read CustomerKeyBank Fail\n");
            }
            //use Efuse key
            Secure_AES_ECB_Decrypt(u32HwAesVABufAddr,u32CusKeySize,NULL);
            memcpy(&stCusKey,(void*)u32HwAesVABufAddr,u32CusKeySize);
            #if defined(CONFIG_MSTAR_AUTHEN_ENABLE)
            isCustomerKeyBankValid((CUSTOMER_KEY_BANK *)u32HwAesVABufAddr);
            #endif
        }
        else
        {
            #if defined(CONFIG_MSTAR_KAISER)
			if(raw_read((U32)&stCusKey,u32CusKeyOffset,u32CusKeySize)!= 0)
            {
                UBOOT_ERROR("Read CustomerKeyBank Fail\n");
            }
            //use Efuse key
            Secure_AES_ECB_Decrypt((U32)&stCusKey,u32CusKeySize,NULL);
			#else
            //In MIPS based chip, we still have a simple secure booting solution on MIPS booting mode.
            ///In this case, we store both the sensitive keys and signatures in "SECURITY_INFO" in SPI.
            memcpy((void *)stCusKey.u8RSAImagePublicKey,(const void *)stSecureInfo.data.Key.u8RSAKernelPublicKey,RSA_PUBLIC_KEY_LEN);
            memcpy((void *)stCusKey.u8AESBootKey,(const void *)stSecureInfo.data.Key.u8AESKernelKey,AES_KEY_LEN);
            #endif
        }
    }

    if(memcmp(stCusKey.u8RSAImagePublicKey,u8MstarDefRSAImagePublicKey,RSA_PUBLIC_KEY_LEN)==0)
    {
        UBOOT_DEBUG("\033[0;36m Mstar's default keys inside\033[0m\n");
    }
    else
    {
        UBOOT_DEBUG("\033[0;36m Customer's keys inside\033[0m\n");
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

#if defined(CONFIG_BOOTING_FROM_EXT_SPI_WITH_PM51)
void _DoSecureEngUnitTestCase1(void)
{
   /*
      *  Test encoding and decodeing basically.
      */
    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;

    U8 u8Plaintext[] = {0x4E,0x43,0x43,0x50,0x32,0x2F,0x63,0x54,0x69,0x63,0x6B,0x65,0x74,0x45,0x78,0x70,
                        0x69,0x72,0x61,0x74,0x69,0x6F,0x6E,0x0A,0x31,0x32,0x38,0x31,0x39,0x35,0x35,0x34};



    const U8 u8PlaintextBackup[] = {0x4E,0x43,0x43,0x50,0x32,0x2F,0x63,0x54,0x69,0x63,0x6B,0x65,0x74,0x45,0x78,0x70,
                                   0x69,0x72,0x61,0x74,0x69,0x6F,0x6E,0x0A,0x31,0x32,0x38,0x31,0x39,0x35,0x35,0x34};

    UBOOT_TRACE("IN\n");
    if(IsHouseKeepingBootingMode()==TRUE)
    {
        UBOOT_INFO("This function only supports in secure processer booting mode\n");
        return;
    }
    Secure_Drv_Init();
    Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct,E_AES_EFUSE_KEY,AES_KEY_LEN,E_KEY_SWAP);


    memcpy((void *)SECURITY_COMMON_BUFFER_ADDR,u8Plaintext,sizeof(u8Plaintext));
    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u8Plaintext));
    Chip_Flush_Memory();
    Secure_MailBox_AESEncode(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u8Plaintext),SECURE_ENG_AES_MODE_ECB);
    UBOOT_DUMP(SECURITY_COMMON_BUFFER_ADDR,sizeof(u8Plaintext));


    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u8Plaintext));
    Chip_Flush_Memory();
    Secure_MailBox_AESDecode(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u8Plaintext),SECURE_ENG_AES_MODE_ECB);
    UBOOT_DUMP(SECURITY_COMMON_BUFFER_ADDR,sizeof(u8Plaintext));

    if(0!=memcmp((void *)SECURITY_COMMON_BUFFER_ADDR,(void *)u8PlaintextBackup,sizeof(u8PlaintextBackup))){
        UBOOT_INFO("\033[0;31m %s fail \033[0m\n",__FUNCTION__);

    }
    else{
        UBOOT_INFO("\033[0;31m %s pass \033[0m\n",__FUNCTION__);
    }
    UBOOT_TRACE("OK\n");

}

void _DoSecureEngUnitTestCase2(void)
{
    /*
       *  We use a cipher key to decrypt u8ENCRYPTED. So we have to command PM51 to decrypte u8cipherKey first.
       *  PS: This cipher key has 32 bytes, but only first 16 bytes is for aes decryption. (Here, key offset is o)
       */

    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;

    //u8ENCRYPTED comes from using u8cleanKey to encrypte u8DECRYPTED.
    U8 u8ENCRYPTED[] = {0x76,0x1F,0x47,0x1B,0x3B,0x93,0x21,0x46,0x90,0xB5,0xD5,0x6F,0x2C,0x67,0x77,0xFE,
                        0x79,0x05,0x06,0xB5,0xAE,0xF8,0xAB,0xDF,0x29,0x27,0xE0,0x43,0x2E,0x1E,0x00,0x37};

    const U8 u8DECRYPTED[] = {0x4E,0x43,0x43,0x50,0x32,0x2F,0x63,0x54,0x69,0x63,0x6B,0x65,0x74,0x45,0x78,0x70,
                                       0x36,0x2B,0x2D,0xDF,0x0C,0xDF,0xED,0x4D,0x96,0xBF,0xA7,0x0C,0x00,0x2E,0x7E,0x9C};

    //U8 u8cleanKey[]={0x02,0x44,0xB7,0x16,0x7F,0x65,0x98,0x04,0xC5,0x75,0xC4,0x9A,0x81,0xDF,0xE0,0x00};
    // u8ChiperKey comes from using efse key to encrypte u8cleanKey.(Here, efuse key are all zero)
    U8 u8cipherKey[]={0xDE,0x5D,0x16,0x31,0x48,0xA8,0x12,0x47,0xCB,0x64,0x7A,0x18,0x60,0x24,0x8D,0xAC, //Key
                      0xDE,0x5D,0x16,0x31,0x48,0xA8,0x12,0x47,0xCB,0x64,0x7A,0x18,0x60,0x24,0x8D,0xAC}; //Data
    UBOOT_TRACE("IN\n");
    if(IsHouseKeepingBootingMode()==TRUE)
    {
        UBOOT_INFO("This function only supports in secure processer booting mode\n");
        return;
    }
    Secure_Drv_Init();
    Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct,E_AES_EFUSE_KEY,AES_KEY_LEN,E_KEY_SWAP);
    memcpy((void *)SECURITY_COMMON_BUFFER_ADDR,u8cipherKey,sizeof(u8cipherKey));
    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u8cipherKey));
    Chip_Flush_Memory();
    Secure_MailBox_SET_KEY_WITH_DECRYPTION(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u8cipherKey),0,SECURE_ENG_AES_MODE_ECB);


    memcpy((void *)SECURITY_COMMON_BUFFER_ADDR,u8ENCRYPTED,sizeof(u8ENCRYPTED));
    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u8ENCRYPTED));
    Chip_Flush_Memory();
    Secure_MailBox_AESDecode(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u8ENCRYPTED),SECURE_ENG_AES_MODE_ECB);
    UBOOT_DUMP(SECURITY_COMMON_BUFFER_ADDR,sizeof(u8ENCRYPTED));

    if(0!=memcmp((void *)SECURITY_COMMON_BUFFER_ADDR,(void *)u8DECRYPTED,sizeof(u8DECRYPTED)))
    {
        UBOOT_INFO("\033[0;31m %s fail \033[0m\n",__FUNCTION__);

    }
    else{
        UBOOT_INFO("\033[0;31m %s pass \033[0m\n",__FUNCTION__);
    }
    UBOOT_TRACE("OK\n");
}


void _DoSecureEngUnitTestCase3(void)
{
    /*
       *  This cipher key has 48 bytes, but only  16 bytes is for aes decryption. (Here, key offset is 21)
       *   The cipher keys encrypte in ECB mode
       */

    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;

    // u8ChiperKey comes from using efse key to encrypte u8cleanKey.(Here, efuse key are all zero)
    U8 u8cipherKey[]={0xDE,0x5D,0x16,0x31,0x48,0xA8,0x12,0x47,0xCB,0x64,0x7A,0x18,0x60,0x24,0x8D,0xAC,
                      0xDE,0x5D,0x16,0x31,0x48,//Data
                      0xA8,0x12,0x47,0xCB,0x64,0x7A,0x18,0x60,0x24,0x8D,0xAC,0xDE,0x5D,0x16,0x31,0x48, //Key
                      0xA8,0x12,0x47,0xCB,0x64,0x7A,0x18,0x60,0x24,0x8D,0xAC}; //Data

    const U8 u8plaintKey[]={0x02,0x44,0xB7,0x16,0x7F,0x65,0x98,0x04,0xC5,0x75,0xC4,0x9A,0x81,0xDF,0xE0,0x00,
                      0x02,0x44,0xB7,0x16,0x7F, // Data
                      0xA8,0x12,0x47,0xCB,0x64,0x7A,0x18,0x60,0x24,0x8D,0xAC,0xDE,0x5D,0x16,0x31,0x48, //Key
                      0x65,0x98,0x04,0xC5,0x75,0xC4,0x9A,0x81,0xDF,0xE0,0x00}; //Data

    UBOOT_TRACE("IN\n");
    if(IsHouseKeepingBootingMode()==TRUE)
    {
        UBOOT_INFO("This function only supports in secure processer booting mode\n");
        return;
    }
    Secure_Drv_Init();
    Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct,E_AES_EFUSE_KEY,AES_KEY_LEN,E_KEY_SWAP);
    memcpy((void *)SECURITY_COMMON_BUFFER_ADDR,u8cipherKey,sizeof(u8cipherKey));
    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u8cipherKey));
    Chip_Flush_Memory();
    Secure_MailBox_SET_KEY_WITH_DECRYPTION(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u8cipherKey),21,SECURE_ENG_AES_MODE_ECB);
    UBOOT_DUMP(SECURITY_COMMON_BUFFER_ADDR,sizeof(u8cipherKey));

    if(0!=memcmp((void *)(0xA0000000|(SECURITY_COMMON_BUFFER_ADDR)),(void *)u8plaintKey,sizeof(u8plaintKey)))
    {
        UBOOT_INFO("\033[0;31m %s fail \033[0m\n",__FUNCTION__);

    }
    else{
        UBOOT_INFO("\033[0;31m %s pass \033[0m\n",__FUNCTION__);
    }
    UBOOT_TRACE("OK\n");
}


void _DoSecureEngUnitTestCase4(void)
{
    /*
       *  This u82thChiphertext has 36 bytes, but only  16 bytes is for aes decryption. (Here, key offset is 5)
       *   The cipher keys encrypte in CBC mode
       */

    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;

    //--> u82thCiphertext is encrypted by u81thPlaintKey in CBC mode
    U8 u82thChiphertext[]={0x2c,0x82,0x9f,0xbe, //Data
                           0xa9,0x83,0x0d,0x64,0x31,0xd2,0x1d,0x50,0x5f,0x58,0x38,0x79,0xcb,0xa0,0x35,0x49, //Key
                           0x64,0x5c,0x20,0x9c,0xfc,0x7e,0xa0,0xd8,0xb7,0x25,0xec,0xfe}; //Data

    // --> u82thPlaintext is real plaintext
    //U8 u82thPlaintext[]={0x62,0x27,0xdc,0xd1, //Data
    //                             0x5e,0x59,0x79,0x97,0x4e,0xd7,0x2a,0x8a,0x24,0x0a,0x05,0xb0, 0x97,0x96,0xa8,0x7e, //Key
    //                             0x4f,0x0b,0x33,0xb5,0x6a,0x89,0xac,0x33,0x7f,0xab,0xe8,0x9a}; //Data
    // --> u82thOutputtext is output data, becuase the part of key will be stored in RIU only.
    const U8 u82thOutputtext[]={0x62,0x27,0xdc,0xd1, //Data
                          0xa9,0x83,0x0d,0x64,0x31,0xd2,0x1d,0x50,0x5f,0x58,0x38,0x79,0xcb,0xa0,0x35,0x49, //Key
                          0x4f,0x0b,0x33,0xb5,0x6a,0x89,0xac,0x33,0x7f,0xab,0xe8,0x9a}; //Data

    // --> u81thCiphertKey comes from using efse key to encrypte u81thPlaintKey.(Here, efuse key are all zero)
    //U8 u81thPlaintKey[]={0x23,0xb2,0xdb,0xea,0xb4,0x0b,0x8c,0xc0,0xd1,0xca,0xaa,0xe9,0xe8,0x65,0xca,0x3c};
    U8 u81thCiphertKey[]={0x56,0xa5,0xc2,0x1b,0x30,0xd4,0x3c,0xc6,0x10,0x1f,0x93,0xe3,0xb5,0x78,0xc9,0xa9};

    UBOOT_TRACE("IN\n");
    if(IsHouseKeepingBootingMode()==TRUE)
    {
        UBOOT_INFO("This function only supports in secure processer booting mode\n");
        return;
    }
    Secure_Drv_Init();
    Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct,E_AES_EFUSE_KEY,AES_KEY_LEN,E_KEY_SWAP);

    memcpy((void *)SECURITY_COMMON_BUFFER_ADDR,u81thCiphertKey,sizeof(u81thCiphertKey));
    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u81thCiphertKey));
    Chip_Flush_Memory();
    Secure_MailBox_SET_KEY_WITH_DECRYPTION(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u81thCiphertKey),0,SECURE_ENG_AES_MODE_ECB);
    UBOOT_DUMP(SECURITY_COMMON_BUFFER_ADDR,sizeof(u81thCiphertKey));

    memcpy((void *)SECURITY_COMMON_BUFFER_ADDR,u82thChiphertext,sizeof(u82thChiphertext));

    flush_cache((U32)SECURITY_COMMON_BUFFER_ADDR,sizeof(u82thChiphertext));
    Chip_Flush_Memory();
    Secure_MailBox_SET_KEY_WITH_DECRYPTION(&SecureBootMbxRetStruct,VA2PA((U32)SECURITY_COMMON_BUFFER_ADDR),sizeof(u82thChiphertext),4,SECURE_ENG_AES_MODE_CBC);

    UBOOT_DUMP(SECURITY_COMMON_BUFFER_ADDR,sizeof(u82thChiphertext));

    if(0!=memcmp((void *)SECURITY_COMMON_BUFFER_ADDR,(void *)u82thOutputtext,sizeof(u82thOutputtext)))
    {
        UBOOT_INFO("\033[0;31m %s fail \033[0m\n",__FUNCTION__);

    }
    else{
        UBOOT_INFO("\033[0;31m %s pass \033[0m\n",__FUNCTION__);
    }
    UBOOT_TRACE("OK\n");


}

void _DoSecureEngUnitTestCase5(void)
{
    SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
    U8 DID[DID_LEN];
    U8 i=0;
    UBOOT_TRACE("IN\n");
    if(IsHouseKeepingBootingMode()==TRUE)
    {
        UBOOT_INFO("This function only supports in secure processer booting mode\n");
        return;
    }

    memset((void *)DID,0,DID_LEN);
    flush_cache((U32)DID,DID_LEN);
    Secure_MailBox_GETDID(&SecureBootMbxRetStruct,(U32)DID,DID_LEN);
    UBOOT_INFO("DID[]={");
    for(i=0;i<DID_LEN;i++)
    {
        UBOOT_INFO("0x%02x ",DID[i]);
    }
    UBOOT_INFO("}\n");
    UBOOT_TRACE("OK\n");
}

int do_DoSecureEngUnitTestCase1(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    _DoSecureEngUnitTestCase1();
    UBOOT_TRACE("OK\n");
    return 0;

}
int do_DoSecureEngUnitTestCase2(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    _DoSecureEngUnitTestCase2();
    UBOOT_TRACE("OK\n");
    return 0;

}
int do_DoSecureEngUnitTestCase3(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    _DoSecureEngUnitTestCase3();
    UBOOT_TRACE("OK\n");
    return 0;

}
int do_DoSecureEngUnitTestCase4(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    _DoSecureEngUnitTestCase4();
    UBOOT_TRACE("OK\n");
    return 0;

}

int do_DoSecureEngUnitTestCase5(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    UBOOT_TRACE("IN\n");
    _DoSecureEngUnitTestCase5();
    UBOOT_TRACE("OK\n");
    return 0;

}
#endif

void PopUpProtectedKey(void)
{
    char *pEnv=NULL;
    UBOOT_TRACE("IN\n");
    pEnv=getenv(ENV_PROTECTION_KEY);
    if(pEnv!=NULL)
    {
        if(0==strcmp((const char *)pEnv,"MSTAR"))
        {
            UBOOT_DEBUG("\033[0;34m The application bins are protected by MSTAR default key \033[0m\n");
        }
        else
        {
            UBOOT_DEBUG("\033[0;34m The application bins are protected by Customer key \033[0m\n");
        }
    }
    else
    {
        UBOOT_DEBUG("\033[0;34m The application bins are protected by MSTAR default key \033[0m\n");
    }
    UBOOT_TRACE("OK\n");
}

#if defined(CONFIG_SECURE_SPI_PROTECT)

#if defined(CONFIG_DISPLAY_LOGO)
#define INTERNAL_SPI_NON_PROTECT_SPACE (CONFIG_ENV_SIZE+CONFIG_ENV_SIZE+SECURITY_BOOT_SIGNATURE_SIZE+CONFIG_DISPLAY_LOGO_SPACE)
#else
#define INTERNAL_SPI_NON_PROTECT_SPACE (CONFIG_ENV_SIZE+CONFIG_ENV_SIZE+SECURITY_BOOT_SIGNATURE_SIZE)
#endif


void spi_write_protect_process_init(void)
{
    char *p_active = getenv("active_spi_wp");
    UBOOT_INFO("IN\n");

    if(p_active && (0 == strncmp(p_active,"on",2)))
    {
        int ret = 1;
        char spi_wp_active[256];
        UBOOT_DEBUG("active_spi_wp=on\n");
        memset(spi_wp_active, 0 , 256);
        snprintf(spi_wp_active, sizeof(spi_wp_active), "spi_in");
        UBOOT_DEBUG("cmd=%s\n",spi_wp_active);
        ret = run_command(spi_wp_active, 0);
        ASSERT((0 == ret));
#if defined(CONFIG_SECURE_SPI_PARTIAL_PROTECT)//partial protect
        uint ProtectLength      = CONFIG_SECURE_SPI_PROTECT_SPACE;
        uint NonProtectLength   = CONFIG_SECURE_SPI_NON_PROTECT_SPACE + INTERNAL_SPI_NON_PROTECT_SPACE;
        snprintf(spi_wp_active, sizeof(spi_wp_active), "spi_bwp 0x%x 0x%x", ProtectLength, NonProtectLength);
#elif defined(CONFIG_SECURE_SPI_FULL_PROTECT)//full protect
        snprintf(spi_wp_active, sizeof(spi_wp_active), "spi_wp %u", 1);
#else
        ASSERT(0);
#endif
        UBOOT_DEBUG("cmd=%s\n",spi_wp_active);
        ret = run_command(spi_wp_active, 0);
        ASSERT((0 == ret));
        snprintf(spi_wp_active, sizeof(spi_wp_active), "setenv active_spi_wp done");
        UBOOT_DEBUG("cmd=%s\n",spi_wp_active);
        ret = run_command(spi_wp_active, 0);
        ASSERT((0 == ret));
        snprintf(spi_wp_active, sizeof(spi_wp_active), "saveenv");
        UBOOT_DEBUG("cmd=%s\n",spi_wp_active);
        ret = run_command(spi_wp_active, 0);
        ASSERT((0 == ret));
    }
    UBOOT_INFO("OK\n");
}
#endif

BOOLEAN IsInterleaveMode(void)
{
    UBOOT_TRACE("IN\n");
    char u8SecIdentify[8] = "\0";
    getSecIdentify(u8SecIdentify,&stSecureInfo,TRUE);
    if(0 == memcmp((const void *)u8SecIdentify,(const void *)idForInterleaveMode,sizeof(idForInterleaveMode)))
    {
        UBOOT_DEBUG("Interleave mode\n");
        UBOOT_TRACE("OK\n");
        return TRUE;
    }
    else
    {
        UBOOT_DEBUG("Continue mode\n");
        UBOOT_TRACE("OK\n");
        return FALSE;
    }
}

int GetImageFromStorage(char *volume, unsigned int addr, unsigned int number)
{
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(volume==NULL)
    {
        UBOOT_ERROR("The volume is a null pointer\n");
        return -1;
    }
    ret=_GetImageFromStorage(volume,addr,number,IsInterleaveMode());

    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("read image fail\n");
    }

    return ret;

}

int _GetImageFromStorage(char *volume, unsigned int addr, unsigned int number, BOOLEAN bIsInterleaveMode)
{
    int ret=0;
    unsigned int i=0;
    unsigned int size=0;
    unsigned int rsize=0;
    unsigned int offset=0;
    unsigned int blockSize=0;
    UBOOT_TRACE("IN\n");
    if(volume==NULL)
    {
        UBOOT_ERROR("The volume is a null pointer\n");
        return -1;
    }
    blockSize=GetBlockSize();
    ret=GetImageSize(volume, number, &size);
    if(ret!=0)
    {
        UBOOT_ERROR("get image %s size fail\n",volume);
        return -1;
    }
    if(bIsInterleaveMode==TRUE)
    {
        UBOOT_DEBUG("Read by interleave mode\n");
        while(size>0)
        {
            rsize=(size>blockSize)?blockSize:size;
            ret=ImageRead(volume,addr, blockSize*(i*FRAGMENT_NUM+number),rsize);
            size-=rsize;
            addr=addr+rsize;
            i++;
            if(ret==-1)
            {
                break;
            }
        }
    }
    else
    {
        UBOOT_DEBUG("Read by continue mode\n");
        //Get 0th size as unit.
        ret=GetImageSize(volume, 0, &offset);
        if(ret!=0)
        {
            UBOOT_ERROR("Get 0th of %s size fail\n",volume);
            return -1;
        }
        offset=offset*number;
        ret=ImageRead(volume,addr,offset,(U32)size);
    }

    if(ret==0)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("Get image fail\n");
    }
    return ret;

}



extern void wait_tee_ready(void);

int do_SecureBootCmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //#define KERNEL_SIZE 0x600000
    char buffer[CMD_BUF]="\0";
    unsigned int *KL_buffer=NULL;
    int ret = 0;
    UBOOT_TRACE("IN\n");
    KL_buffer=(unsigned int *)(BOOT_MODE_TMP_BUF_ADDR);
    if(KL_buffer==NULL)
    {
        UBOOT_ERROR("malloc buffer fail\n");
        return -1;
    }

    #if (CONFIG_VESTEL_MB97 == 1)
    ret = run_command("readNuttx", 0);
    // disable black pattern in MOD layer to avoid issue SENTOR-4164
    Write2Byte(0x103202, 0x0000);
    ret = run_command("panel_post_init", 0);
    ret = run_command("bootNuttx", 0);
    #else
    ret = run_command("readNuttx;panel_post_init;bootNuttx;", 0);
    #endif

    if(ret==-1)
    {
       UBOOT_ERROR("verify tee fail\n");
        return -1;
    }

#if (ENABLE_MODULE_ANDROID_BOOT == 1 )
    do_Authenticate_RawData("boot",(int)KL_buffer);
#else
    do_Authenticate_RawData("KL",(int)KL_buffer);
#endif

    wait_tee_ready();

    snprintf(buffer, CMD_BUF, "bootm 0x%x",(int)KL_buffer);
    printf("[AT][MBoot][Boot Nuttx][%lu]\n", MsSystemGetBootTime());
    ret = run_command(buffer, 0);
    if(ret==-1)
    {
        UBOOT_ERROR("do_SecureKLBoot fail\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return ret;
}


int do_performance_test (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(argc!=3)
    {
        cmd_usage(cmdtp);
        return -1;
    }
    if((argv[1]==NULL)||(argv[2]==NULL))
    {
        UBOOT_ERROR("One of the parameters is a null pointer\n");
        return -1;
    }

    ret=ImageIOInit("UBI");



    if(ret!=-1)
    {
        if(strncmp(argv[1], "-c", 2) == 0)
        {
            UBOOT_INFO("==>start\n");
            ret=_GetImageFromStorage(argv[2],UPGRADE_BUFFER_ADDR,0,FALSE);
            UBOOT_INFO("==>end\n");
        }
        else if(strncmp(argv[1], "-i", 2) == 0)
        {
            UBOOT_INFO("==>start\n");
            ret=_GetImageFromStorage(argv[2],UPGRADE_BUFFER_ADDR,0,TRUE);
            UBOOT_INFO("==>end\n");
        }
        else
        {
            cmd_usage(cmdtp);
            return -1;
        }
    }

    if(ret!=-1)
    {
        UBOOT_TRACE("OK\n");
    }
    else
    {
        UBOOT_ERROR("Image IO init fail\n");

    }

    return 0;
}

U32 GetBlockSize(void)
{
    #define EMMC_READ_LEN_OF_CMD18 (512*4096) //CM18 can read 4096 blocks in one time.
    unsigned int size=0;
    UBOOT_TRACE("IN\n");
#if (ENABLE_MODULE_NAND_FLASH==1) || (ENABLE_MODULE_SPI_NAND_FLASH==1)
    size=ubi_get_leb_size();
#endif
#if(ENABLE_MODULE_MMC==1)
    size=EMMC_READ_LEN_OF_CMD18;
#endif

    UBOOT_DEBUG("block size=0x%x\n",size);
    UBOOT_TRACE("OK\n");
    return size;

}

#if defined (CONFIG_SecureStorage)
int Chunk_Authentication(char* KLName, unsigned u32kernelAddr)
{
    U32 kernelSize=0;
    char cmd[128];
    U8 u8ImagePublicKeyN[RSA_PUBLIC_KEY_N_LEN];
    U8 u8ImagePublicKeyE[RSA_PUBLIC_KEY_E_LEN];
    U8 u8ImageSignature[SIGNATURE_LEN];
    int ret=0;
    UBOOT_TRACE("IN\n");

    ret = GetImageSize(KLName,0,&kernelSize);
    if (0 != ret)
    {
        UBOOT_ERROR("get %s image size fail\n",KLName);
        return -1;
    }
    memset(cmd, 0, 128);
    snprintf(cmd , sizeof(cmd) - 1, "mmc read.p %x %s 0x0010000", u32kernelAddr, KLName);
    run_command(cmd, 0);
    flush_cache(u32kernelAddr,(U32)kernelSize);
    GetPublicKeyN(E_RSA_IMAGE_PUBLIC_KEY, u8ImagePublicKeyN, sizeof(u8ImagePublicKeyN));
    GetPublicKeyE(E_RSA_IMAGE_PUBLIC_KEY, u8ImagePublicKeyE, sizeof(u8ImagePublicKeyE));
    GetSignature(KLName, 0, u8ImageSignature, sizeof(u8ImageSignature));
    if (-1 == Secure_doAuthentication(u8ImagePublicKeyN, u8ImagePublicKeyE, u8ImageSignature, (U8*)u32kernelAddr, kernelSize))
    {
        UBOOT_ERROR("\033[0;31m Auth  %s FAIL\033[0m\n",KLName);
        UBOOT_DEBUG("\033[0;31m RSA image public-N key=\033[0m\n");
        UBOOT_DUMP((U32)u8ImagePublicKeyN, RSA_PUBLIC_KEY_N_LEN);

        UBOOT_DEBUG("\033[0;31m RSA image public-E key=\033[0m\n");
        UBOOT_DUMP((U32)u8ImagePublicKeyE, RSA_PUBLIC_KEY_E_LEN);

        UBOOT_DEBUG("\033[0;31m %s signature=\033[0m\n",KLName);
        UBOOT_DUMP((U32)u8ImageSignature, SIGNATURE_LEN);

        UBOOT_DEBUG("\033[0;31m clear %s image=\033[0m\n",KLName);
        UBOOT_DUMP(u32kernelAddr, 0x100);
        return -1;
    }
    else
    {
        UBOOT_INFO("\033[0;34m********************************\033[0m\n");
        UBOOT_INFO("\033[0;34m* %s Authentication SUCCESS !! *\033[0m\n",KLName);
        UBOOT_INFO("\033[0;34m********************************\033[0m\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
}

int do_write_rsa_key(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned char *buffer = NULL;
	char *p1, *p2, p[32 * 1024];
	int ret = -1, i = 0;
	char cmd[256];
	char buf1[17 * 512], buf2[32 * 1024];
	rawdata_header head_part[32];

	void *addr = (void *)simple_strtoul(argv[1], NULL, 16);
	s32 blk = simple_strtoul(argv[2], NULL, 16);
	u32 cnt = simple_strtoul(argv[3], NULL, 16);

	memset(&head_part, 0, 32 * sizeof(rawdata_header));
	memset(buf1, 0, 17 * 512);
	memset(p, 0, 32 * 1024);
	memset(buf2, 0, 32 * 1024);

	buffer = (unsigned char*)addr;
	memcpy(buf1, buffer, 17 * 512);
	p1 = strtok(buf1,"\n");
	while(NULL != p1)
	{
		if (-1 != ret)
		{
			if (NULL == (p1 = strtok(NULL, "\n")))
			{
				ret = -1;
				break;
			}
		}
		if (NULL == (p2 = strchr(p1, '=')))
		{
			ret = -1;
			break;
		}
		head_part[i].size = strlen(p2) - 3;
		strncpy(head_part[i].name, p1, p2 - p1);
		head_part[i].offset = 32 * sizeof(rawdata_header) + i * 1024;
		ret = 0;
		Secure_AES_ECB_Encrypt((MS_U32 *)(p2 + 2), head_part[i].size, NULL);
		memcpy(p + 1024 * i, p2 + 2, head_part[i].size);
		i++;
	}
	memcpy(buf2, &head_part, 32 * sizeof(rawdata_header));
	memcpy(buf2 + 32 * sizeof(rawdata_header), p, 1024 * i);
	memcpy(buffer, buf2, (i + 4) * 1024);
	memset(cmd, 0, 256);
	snprintf(cmd, 256, "mmc write.boot 2 %x %d %x 1", addr, blk, cnt);
	run_command(cmd, 0);
}
#endif

