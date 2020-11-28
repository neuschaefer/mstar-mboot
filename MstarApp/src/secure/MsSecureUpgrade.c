//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (“MStar Software”) are intellectual property of MStar Semiconductor, Inc. (“MStar”) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar. 
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (“Terms”) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party’s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party’s software. 
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar’s confidential information and you agree to keep MStar’s confidential information in strictest confidence and not disclose to any third party.  
//4. MStar Software is provided on an “AS IS” basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.  
//   In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer’s product (“Services”).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an “AS IS” basis and the warranty disclaimer set forth in Section 4 above shall apply.  
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.  
//   The arbitration award shall be final and binding to both parties.
//
//本處所有軟體、韌體及相關文檔(下稱「MStar Software」)均為MStar Semiconductor, Inc. (下稱「MStar」)之智慧財產權並為相關法律(包括但不限於著作權法及國際條約)所保護，任何未經MStar事前書面野i之使用、修改、重製、傳送或公開均為禁止的。
//一旦您進入、瀏覽或使用MStar Software，您即聲明您已詳讀、了解並同意為下列條款（下稱「本條款」）所拘束並將遵守相關法規之規定：
//
//1.	MStar仍保有MStar Software及其修改物／衍生物之任何與全部的權利、所有權及利益，您並未因本條款而取得關於MStar Software及其修改物／衍生物之任何與全部的權利、所有權及利益。
//2.	您了解MStar Software可能含有或結合有屬於第三人之軟體或係與第三人之軟體一併提供，而使用MStar Software可能需另行向第三人取得授權，因此您同意您將自行負責向此等第三人取得授權以合法使用MStar Software。
//3.	MStar Software及其修改物／衍生物應被視為MStar的機密資訊，您同意將以最機密保存MStar的機密資訊且不將之揭露予任何第三人。
//4.	MStar Software係「依現狀」所提供而無任何擔保。MStar於此否認對MStar Software提供任何擔保，包括但不限於可商品化、不侵權、符合特定使用目的、無瑕疵及符合任何國際標準之擔保。您同意將不會對MStar主張您因使用MStar Software所生之任何損失、損害、費用或支出。於任何情況下，MStar對於直接的、間接的、附帶的或必然的損害均不負責任，包括但不限於利潤營收損失、資料之毀損遺失及系統被未經授權使用。您並同意，除雙方另有書面協議外，即使MStar曾依您的要求或指示而修改MStar Software，本第4條之規定仍繼續適用而不受影響。
//5.	如經要求，MStar不時將提供技術支援或服務予您，以利您的產品可以與MStar Software一同使用(下稱「服務」)，您了解並同意，除雙方另有書面協議外，所有服務均係「以現狀」提供，第4條之不提供擔保相關規定亦應適用之。
//6.	本條款之任何條款不得被解釋為(無論依默示、禁反言原則或其它)：(a) 授予任何權利以使用MStar之名稱、商標、服務標章、符號或其它識別圖像；(b)課予MStar或其關係企業提供予任何人(包括但不限於您及您的客戶)任何形式的協助或資訊的義務；或(c) 授予任何智慧財產權。
//7.	本條款應依中華民國法律為準據法(不含其衝突法則)。任何基於本條款所生或與本條款相關之爭議最終應依中華民國仲裁法及該協會之仲裁規則解決，仲裁應由3名仲裁人以英文在台灣台北進行，仲裁人應依中華民國仲裁協會之仲裁規則選出，仲裁判斷應為終局的且對雙方均有拘束力。
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
#include <command.h>
#include <secure/MsSecureBoot.h>
#include <secure/MsSecureCommon.h>
#include <secure/crypto_rsa.h>
#include <secure/crypto_sha.h>
#include <secure/crypto_func.h>
#include <secure/crypto_aes.h>
#include <secure/crypto_auth.h>
#include <secure/apiSecureBoot.h>
#include <MsTypes.h>
#include <MsVfs.h>
#include <MsSystem.h>
#include <exports.h>
#include <ShareType.h>
#include <MsDebug.h>
#include <MsUtility.h>
#include <MsUpgradeUtility.h>


//-------------------------------------------------------------------------------------------------
//  Debug
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define DEFAULT_SEGMENT_SIZE 8192
#define CERTIFICATE_LOCATION        "certificate"
#define RSA_PUBLIC_KEY_PATH "/RSAPublicKeyAPP.bin"
#define AES_KEY_PATH "/Kcust.bin"





//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static unsigned char aesKey[0x10];
static unsigned int segmentSize=0;
static unsigned char fileSizeReady=FALSE;
static unsigned int gfileSize=0;

//-------------------------------------------------------------------------------------------------
//  extern function
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  inline
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local function
//-------------------------------------------------------------------------------------------------
U32 Secure_SegmentSize (void);
int GetfileSizeforAESUsbUpgrade(const char *Interface,const char *device,char *file);



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------




int do_file_segment_rsa_authendication(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //"filSegRSA usb %d:%d %s",device, partition, upgradeFile);
    #define TARGET_INTERFACE argv[1]
    #define TARGET_DEVICE  argv[2]
    #define TARGET_FILE  argv[3]
    /// chunk file size in all-in-one segment rsa mode
    #define SEGMENT_RSA_CHUNK_FILE_SIZE 128
    /// CHUNK file's start signature
    #define CHUNK_ID "MSTAR..."
    /// CHUNK file's end signature
    #define CHUNK_END "...mstar"
    #define RSA_PUBLIC_KEN_N_LEN 256
    #define RSA_PUBLIC_KEN_E_LEN 4
    #undef RSA_PUBLIC_KEY_LEN
    #define RSA_PUBLIC_KEY_LEN          (RSA_PUBLIC_KEN_N_LEN+RSA_PUBLIC_KEN_E_LEN)
    #define SHA256_DIGEST_SIZE ( 256 / 8)
    #define BUF_SIZE 4096
    
    unsigned int i=0;
    unsigned int fileDataOffset=0;
    unsigned int fileDataLen=0;
    unsigned int fileHashOffset=0;
    unsigned int fileHashLen=0;
    unsigned int fileSignatureOffset=0;
    unsigned int fileSignatureLen=0;
    unsigned int *pReadChunk=NULL;
    char *buffer=NULL;
    int ret=0;
    unsigned int readLen=0;
    unsigned char rsaOutBuf[RSA_KEY_DIGI_LEN*4];
    unsigned char rsaPublicKeyN[RSA_PUBLIC_KEN_N_LEN];
    unsigned char rsaPublicKeyE[RSA_PUBLIC_KEN_E_LEN];
    unsigned char hashOutBuf[SHA256_DIGEST_SIZE];
    unsigned char *pt=NULL;
    UBOOT_TRACE("IN\n");
    if(argc<4)
        return -1;

    buffer=(char *)malloc(BUF_SIZE);
    if(buffer==0)
    {
        UBOOT_ERROR("[ERROR]memroy allocate fail\n");
        return -1;
    }

    ret=GetfileSizeforAESUsbUpgrade(TARGET_INTERFACE,TARGET_DEVICE,TARGET_FILE);
    if(ret<0)
    {
        free(buffer);
        return -1;
    }
    
    //Read last segment , because we want to get chunk file.
    memset(buffer,0,BUF_SIZE);
    snprintf(buffer, BUF_SIZE, "filepartloadSegAES %s %s %x %s %x %x", TARGET_INTERFACE, TARGET_DEVICE, RSA_AUTHENTICATION_ADDR, TARGET_FILE, gfileSize-SEGMENT_RSA_CHUNK_FILE_SIZE, SEGMENT_RSA_CHUNK_FILE_SIZE);
    ret=run_command(buffer, 0);
    if(ret<0)
    {
        free(buffer);
        return -1;
    }
    
    if(memcmp((const void *)(RSA_AUTHENTICATION_ADDR),CHUNK_ID,sizeof(CHUNK_ID))!=0){
        UBOOT_ERROR("[ERROR] CHUNK_ID compare fail\n");
        free(buffer);
        return -1;
    }

    if(memcmp((const void *)(RSA_AUTHENTICATION_ADDR+SEGMENT_RSA_CHUNK_FILE_SIZE-strlen(CHUNK_END)),CHUNK_END,strlen(CHUNK_END))!=0){
        UBOOT_ERROR("[ERROR] CHUNK_END compare fail\n");
        free(buffer);
        return -1;
    }

    //Get hash, signature infor from chunk data
    pReadChunk=(unsigned int *)(RSA_AUTHENTICATION_ADDR);
    pReadChunk+=2;
    segmentSize=*pReadChunk;
    pReadChunk+=1;
    fileDataOffset=*pReadChunk;
    pReadChunk++;
    fileDataLen=*pReadChunk;
    pReadChunk++;

    fileHashOffset=*pReadChunk;
    pReadChunk++;
    fileHashLen=*pReadChunk;
    pReadChunk++;
    fileSignatureOffset=*pReadChunk;
    pReadChunk++;
    fileSignatureLen=*pReadChunk;
    pReadChunk++;
    
    UBOOT_DEBUG("segment size=0x%x\n",segmentSize);
    UBOOT_DEBUG("fileDataOffset=0x%x\n",fileDataOffset);
    UBOOT_DEBUG("fileDataLen=0x%x\n",fileDataLen);
    UBOOT_DEBUG("fileHashOffset=0x%x\n",fileHashOffset);
    UBOOT_DEBUG("fileHashLen=0x%x\n",fileHashLen);
    UBOOT_DEBUG("fileSignatureOffset=0x%x\n",fileSignatureOffset);
    UBOOT_DEBUG("fileSignatureLen=0x%x\n",fileSignatureLen);


    //Get rsa upgrade public key
    ret = GetPublicKeyN(E_RSA_UPGRADE_PUBLIC_KEY,rsaPublicKeyN,RSA_PUBLIC_KEN_N_LEN);
    if(ret!=0)
    {
        UBOOT_ERROR("Get public key N fail\n");
        free(buffer);
        return -1;
    }
    ret = GetPublicKeyE(E_RSA_UPGRADE_PUBLIC_KEY,rsaPublicKeyE,RSA_PUBLIC_KEN_E_LEN);
    if(ret!=0)
    {
        UBOOT_ERROR("Get public key E fail\n");
        free(buffer);
        return -1;
    }

     
    //Read ***.hash.signature, and then do rsa decod
    memset(buffer,0,BUF_SIZE);
    snprintf(buffer, BUF_SIZE, "filepartloadSegAES %s %s %x %s %x %x", TARGET_INTERFACE,TARGET_DEVICE,RSA_AUTHENTICATION_ADDR, TARGET_FILE, fileSignatureOffset, fileSignatureLen);
    ret=run_command(buffer, 0);
    if(ret<0)
    {          
        free(buffer);
        return -1;
    }
    
    rsa_main((unsigned char *)RSA_AUTHENTICATION_ADDR,rsaPublicKeyN,rsaPublicKeyE,rsaOutBuf);
    
    // Do rsa authentication for ***.hash
    if( buffer != NULL )
    {
        memset(buffer,0,BUF_SIZE);
        
        snprintf(buffer, BUF_SIZE, "filepartloadSegAES %s %s %x %s %x %x", TARGET_INTERFACE,TARGET_DEVICE,RSA_AUTHENTICATION_ADDR, TARGET_FILE, fileHashOffset, fileHashLen);

        ret=run_command(buffer, 0);
        if(ret<0)
        {
            free(buffer);
            return -1;
        }
    }
    
    if(CommonSHA(RSA_AUTHENTICATION_ADDR,(MS_U32)hashOutBuf,(MS_U32)fileHashLen)!=0)
    {
        free(buffer);
        return -1;
    }
    #if 1
    for(i = 0; i<SHA256_DIGEST_SIZE; i++)
    {

        if(hashOutBuf[i] != rsaOutBuf[i])
        {
           UBOOT_ERROR("hashOutBuf[%d]=0x%x, rsaOutBuf[%d]=0x%x \n",i,hashOutBuf[i],i,rsaOutBuf[i]);
           free(buffer);
           return -1;
        }
    }
    #endif

    // Do rsa authentication for ***.hash
    UBOOT_INFO("Segment RSA Authentication ....\n");
    while(fileDataLen)
    {
        UBOOT_INFO("*");
        readLen=(fileDataLen>=segmentSize)?segmentSize:fileDataLen;

        memset(buffer,0,BUF_SIZE);
        snprintf(buffer, BUF_SIZE, "filepartloadSegAES %s %s %x %s %x %x", TARGET_INTERFACE,TARGET_DEVICE,RSA_AUTHENTICATION_ADDR, TARGET_FILE, fileDataOffset, readLen);
        ret=run_command(buffer, 0);
        if(ret<0)
        {
            free(buffer);
            return -1;
        }
        if(CommonSHA(RSA_AUTHENTICATION_ADDR,(MS_U32)hashOutBuf,(MS_U32)readLen)!=0)
        {
            free(buffer);
            return -1;
        }

        memset(buffer,0,BUF_SIZE);
        snprintf(buffer, BUF_SIZE, "filepartloadSegAES %s %s %x %s %x %x", TARGET_INTERFACE,TARGET_DEVICE,RSA_AUTHENTICATION_ADDR, TARGET_FILE, fileHashOffset, SHA256_DIGEST_SIZE*2);
        ret=run_command(buffer, 0);
        if(ret<0)
        {
             free(buffer);
             return -1;
        }

        pt=(unsigned char *)(RSA_AUTHENTICATION_ADDR);//+SHA256_DIGEST_SIZE-1);
        for(i = 0; i<SHA256_DIGEST_SIZE; i++)
        {
             if(hashOutBuf[SHA256_DIGEST_SIZE-1-i] != *pt){
                UBOOT_ERROR("hashOutBuf[%d]=0x%x, *pt=0x%x \n",SHA256_DIGEST_SIZE-1-i,hashOutBuf[SHA256_DIGEST_SIZE-1-i],*pt);
                free(buffer);
                return -1;
             }
             pt++;
        }
        fileDataLen-=readLen;
        fileDataOffset+=readLen;
        fileHashOffset+=SHA256_DIGEST_SIZE;

        UBOOT_DEBUG("readLen=0x%x\n",readLen);
        UBOOT_DEBUG("fileDataLen=0x%x\n",fileDataLen);
        UBOOT_DEBUG("fileDataOffset=0x%x\n",fileDataOffset);
        UBOOT_DEBUG("fileHashOffset=0x%x\n",fileHashOffset);

    }
    free(buffer);
    UBOOT_TRACE("OK\n");
    return 0;             
}

int do_file_part_load_with_segment_aes_decrypted(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
     #define DOWNLOAD_INTERFACE argv[1]
     #define DOWNLOAD_DEVICE argv[2]
     #define DOWNLOAD_ADDR argv[3]
     #define DOWNLOAD_FILE argv[4]
     #define DOWNLOAD_OFFSET argv[5]
     #define DOWNLOAD_LENGTH argv[6]
            
     unsigned int downloadOffset=0;
     unsigned int downloadLen=0;
     unsigned int pdownloadAddr=0;

     unsigned int readSegmentAddr=0;
     unsigned int readOffsetInSeg=0;
     unsigned int readLen=0;
     unsigned int aesDecodeLen=0;
     unsigned int segmentNum=0;
     unsigned int _segmentSize=0;
     char* buffer=NULL;
     int ret=0;
     SECUREBOOT_MbxRetStruct SecureBootMbxRetStruct;
     UBOOT_TRACE("IN\n");
    
     if(argc<7){
        return -1;
     }
     buffer=(char *)malloc(BUF_SIZE);
     if(buffer == NULL)
     {
        UBOOT_ERROR("%s: Error: out of memory, at %d\n", __func__, __LINE__);
        return -1;
      }
     else
      memset(buffer, 0, BUF_SIZE);


      downloadOffset = (unsigned int)simple_strtoul(DOWNLOAD_OFFSET, NULL, 16);
      downloadLen = (unsigned int)simple_strtoul(DOWNLOAD_LENGTH, NULL, 16);
      pdownloadAddr = (unsigned int)simple_strtoul(DOWNLOAD_ADDR, NULL, 16);

      //Get total file size
     ret=GetfileSizeforAESUsbUpgrade(DOWNLOAD_INTERFACE,DOWNLOAD_DEVICE,DOWNLOAD_FILE);
     if(ret<0)
     {
        free(buffer);
        return -1;
     }

      //Get AES decode key
      if(segmentSize==0)
        _segmentSize=DEFAULT_SEGMENT_SIZE;
      else
        _segmentSize=segmentSize;
      //Read data and do aes decoder.
      segmentNum=downloadOffset/_segmentSize;

      if(IsHouseKeepingBootingMode()==FALSE)
      {
          Secure_MailBox_ASSIGN_DECRYPTED_KEY(&SecureBootMbxRetStruct,E_AES_UPGRADE_KEY,AES_KEY_LEN,E_KEY_SWAP);
      }
      else
      {
          GetAESKey(E_AES_UPGRADE_KEY,aesKey);
      }
      
      while(downloadLen)
      {
        readSegmentAddr=segmentNum*_segmentSize;
        if(downloadOffset%_segmentSize){ //Only first time
            readOffsetInSeg=downloadOffset-readSegmentAddr;
            readLen=((readOffsetInSeg+downloadLen)>=_segmentSize)?(_segmentSize-readOffsetInSeg):downloadLen;

        }
        else{
            readOffsetInSeg=0;
            readLen=(downloadLen>=_segmentSize)?_segmentSize:downloadLen;

        }
        aesDecodeLen=((readSegmentAddr+_segmentSize)>=gfileSize)?gfileSize-readSegmentAddr:_segmentSize;

        UBOOT_DEBUG("downloadOffset=0x%x\n",downloadOffset);
        UBOOT_DEBUG("downloadLen=0x%x\n",downloadLen);
        UBOOT_DEBUG("pdownloadAddr=0x%x\n",pdownloadAddr);
        UBOOT_DEBUG("readSegmentAddr=0x%x\n",readSegmentAddr);
        UBOOT_DEBUG("readOffsetInSeg=0x%x\n",readOffsetInSeg);
        UBOOT_DEBUG("readLen=0x%x\n",readLen);
        UBOOT_DEBUG("aesDecodeLen=0x%x\n",aesDecodeLen);
        UBOOT_DEBUG("segmentNum=0x%x\n",segmentNum);

        if(getUpgradeMode()==EN_UPDATE_MODE_NET_WITH_SEG_DECRYPTED)
        {
            ret = vfs_read((void*)AES_DECRYPTED_ADDR,DOWNLOAD_FILE,readSegmentAddr,aesDecodeLen);
            if(ret<0)
            {
              free(buffer);
              return -1;
            }
        }
        else if(getUpgradeMode()==EN_UPDATE_MODE_USB_WITH_SEG_DECRYPTED)
        {
            snprintf(buffer, BUF_SIZE, "fatpartload %s %s %x %s %x %x", DOWNLOAD_INTERFACE,DOWNLOAD_DEVICE,AES_DECRYPTED_ADDR, DOWNLOAD_FILE, readSegmentAddr, aesDecodeLen);
            ret = run_command(buffer, 0);
            if(ret<0)
            {
              free(buffer);
              return -1;
            }
        }
        else
        {
            UBOOT_ERROR("Wrong Upgrade Mode!!\n");
            free(buffer);        
            return -1;
        }

        // AES decode
        if(IsHouseKeepingBootingMode()==FALSE)
        {
            flush_cache((U32)AES_DECRYPTED_ADDR,aesDecodeLen);
            Chip_Flush_Memory();
            Secure_MailBox_AESDecode(&SecureBootMbxRetStruct, MsOS_VA2PA(AES_DECRYPTED_ADDR), aesDecodeLen, SECURE_ENG_AES_MODE_ECB);
        }
        else
        {
            Secure_AES_ECB_Decrypt(AES_DECRYPTED_ADDR, aesDecodeLen, (U8 *)aesKey);
        }

        // copy to target address
        memcpy((void*)pdownloadAddr,(char *)(AES_DECRYPTED_ADDR+readOffsetInSeg),readLen);


        downloadLen-=readLen;

        pdownloadAddr+=readLen;
        downloadOffset+=readLen;
        segmentNum++;
     }
     free(buffer);
     UBOOT_TRACE("OK\n");
     return 0;
}

U32 Secure_SegmentSize (void)
{
    UBOOT_TRACE("IN\n");
    UBOOT_TRACE("OK\n");
    return DEFAULT_SEGMENT_SIZE;
}

int GetfileSizeforAESUsbUpgrade(const char *Interface,const char *device,char *file)
{
    char* buffer=NULL;
    int ret=0;
    UBOOT_TRACE("IN\n");
    if(fileSizeReady==TRUE)
    {
        UBOOT_TRACE("OK\n");
        return ret;
    }

    buffer=(char *)malloc(BUF_SIZE);
    if(buffer == NULL)
    {
       UBOOT_ERROR("Error: out of memory\n");
       return -1;
    }
    //Get total file size
    memset(buffer,0,BUF_SIZE);
    if(getUpgradeMode()==EN_UPDATE_MODE_NET_WITH_SEG_DECRYPTED)
    {
        gfileSize=vfs_getsize(file);

    }
    else if(getUpgradeMode()==EN_UPDATE_MODE_USB_WITH_SEG_DECRYPTED)
    {
        snprintf(buffer, BUF_SIZE, "fatfilesize %s %s %s 0x%08x",Interface,device, file, &gfileSize);
        UBOOT_DEBUG("cmd:%s\n",buffer);
        ret=run_command(buffer, 0);
        if(ret<0)
        {
            free(buffer);
            return -1;
        }
    }
    else
    {
        UBOOT_ERROR("Wrong Upgrade Mode!!\n");
        free(buffer);        
        return -1;        
    }


    free(buffer);
    fileSizeReady=TRUE;
    UBOOT_TRACE("OK\n");
    return ret;
}



