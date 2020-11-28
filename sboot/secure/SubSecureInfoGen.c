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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------
#define ERROR(msg...) \
	do{\
		printf("\033[0;31m[ERROR] %s:%d: \033[0m",__FUNCTION__,__LINE__);\
		printf(msg);\
	}while(0);
	
#define DEBUG(msg...) \
	do{\
		if(enDebugInfo==1)\
		{	\
			printf("\033[0;34m[DEBUG] %s:%d: \033[0m",__FUNCTION__,__LINE__);\
			printf(msg);\
		}	\
	}while(0);	
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define SIGNATURE_LEN               256
#define RSA_PUBLIC_KEY_LEN          (256+4)
#define SEGMENT_NUM 8
#define CMD_BUF 1024
#define TEMP_FILE "tempfile"
typedef unsigned char U8;
typedef unsigned short int U16;
typedef unsigned int U32;

typedef struct
{
    U32 u32Num;
    U32 u32Size;
}IMAGE_INFOR;


typedef struct
{
  U8 u8SecIdentify[8]; 	
  IMAGE_INFOR info;
  U8 u8Signature[SIGNATURE_LEN];
}SUB_SECURE_INFO;


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
char idForContinueMode[]={'S','E','C','U','R','I','T','Y'};
char idForInterleaveMode[]={'I','N','T','E','R','L','V','E'};
U8 enDebugInfo=0;
//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
unsigned int  _atoi(char *str);
int _genSubSecureInfo(U8 *utilityPath, U8 *outFileName, U8 *intFileName, U32 u32Num, U8 *private_key, U8 *public_key,U8 enInterleaveMode);
int getFileSize(char *file, U32 *size);
int createSubFile(char *intFileName, char *outFileName, U32 offset, U32 size, U8 IsInterleaveMode, U32 blockSize);
int getFileImage(char *file, U8* outBuf, U32 offset, U32 size, U8 IsInterleaveMode, U32 blockSize);
int genSecureInfo(char *intFileName, char *outFileName, U32 segmentNum, char *utilityPath, char *privKeyPath, char *pubKeyPath, U8 enInterleaveMode, U32 blockSize);
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
int readFileToBuffer(char *file, unsigned int offset, char *buffer, unsigned int len)
{
    FILE *fr=NULL;

    if(file==NULL)
    {
        printf("[ERROR] file is a null pointer\n");
        return -1;
    }
    
    if(buffer==NULL)
    {
        printf("[ERROR] buffer is a null pointer\n");
        return -1;
    }  

    fr=fopen(file,"rb");
    if(fr==NULL)
    {
        printf("[ERROR] open %s fail\n",file);
        return -1;
    }
    
    fseek(fr,offset,SEEK_CUR);

    if(len!=fread(buffer,1,len,fr))
    {
        fclose(fr);
        printf("[ERROR] read file fail\n");
        return -1;
    }
    
    fclose(fr);
    return 0;
}

int saveFileFromBuffer(char *file, char *buffer, unsigned int len)
{
    FILE *fw=NULL;
    unsigned int retLen=0;

    if(file==NULL)
    {
        printf("[ERROR] The file is a null pointer\n");        
        return -1;
    }

    if(buffer==NULL)
    {
        printf("[ERROR]The buffer is a null pointer\n");
        return -1;
    }

    fw=fopen(file,"wb");
    if(fw==NULL)
    {
        printf("[ERROR] open %s fail\n",file);
        return -1;
    }

    retLen=fwrite(buffer, 1 , len, fw);
    if(retLen!=len)
    {
        fclose(fw);
        printf("[ERROR] write file fail\n");
        return -1;
    }
    fclose(fw);
    fsync();
    return 0;
}

int _cat(char *source, char *target)
{
	unsigned int source_size=0, target_size=0, total_size=0;
	char *pBuf=NULL;
	DEBUG("source=%s\n",source);
	DEBUG("target=%s\n",target);
	getFileSize(source,&source_size);
	getFileSize(target,&target_size);
	total_size=source_size+target_size;
	pBuf=malloc(total_size);
	if(pBuf==NULL)
	{
		ERROR("[ERROR]malloc fail\n");
		return -1;
	}
	memset(pBuf,0,total_size);
 	if(target_size==0)
	{
		readFileToBuffer(source,0,pBuf,source_size);
	}
	else
	{
		readFileToBuffer(target,0,pBuf,target_size);
		readFileToBuffer(source,0,pBuf+target_size,source_size);
	}
	saveFileFromBuffer(target,pBuf,total_size);
	free(pBuf);
	return 0;
}				
unsigned int  _atoi(char *str)
{
	
	unsigned int  value=0;

       if(*str=='\0') return  value;

	if((str[0]=='0')&&((str[1]=='x')||(str[1]=='X'))){   
	// 16Hex
		str+=2;
		while(1){

		   if(*str>=0x61)
		   	*str-=0x27;
		   else if(*str>=0x41)
		   	*str-=0x07;
		   
		   value|=(*str-'0');
		   str++;
		   //i++;
	          if(*str=='\0') break;
		   value=value<<4;	  
	      }
	}
	else{
	// 10 Dec

	       unsigned int  len,tmp=1;;	
		len=strlen(str);
		while(len){
			if(*str>'9') return 0;
			
			value+=((str[len-1]-'0')*tmp);

			len--;
			tmp=tmp*10;
	       }
	}
	return value;
	
}
int _genSubSecureInfo(U8 *utilityPath, U8 *outFileName, U8 *intFileName, U32 u32Num, U8 *private_key, U8 *public_key,U8 enInterleaveMode)
{
    FILE *fr=NULL;
	FILE *fw=NULL;
	U32 fileSize=0;
	SUB_SECURE_INFO subSecureInfo;
	U8 cmdBuf[CMD_BUF];
	U8 tempBuf1[CMD_BUF];
	U8 tempBuf2[CMD_BUF];
	DEBUG("utilityPath=%s\n",utilityPath);
	DEBUG("outFileName=%s\n",outFileName);
	DEBUG("intFileName=%s\n",intFileName);
	DEBUG("private_key=%s\n",private_key);
	DEBUG("public_key=%s\n",public_key);
	DEBUG("u32Num=0x%x\n",(unsigned int)u32Num);
	DEBUG("enInterleaveMode=0x%x\n",(unsigned int)enInterleaveMode);
	fr=fopen(intFileName,"r");
	if(fr==NULL){
		ERROR("[ERROR] open %s fail\n",intFileName);
		return -1;
	}
	
	fseek(fr, 0, SEEK_END);
	fileSize=ftell(fr);
	fseek(fr, 0, SEEK_SET);
	fclose(fr);
	
	if(enInterleaveMode==0)
	{
		DEBUG("use the non-interleave mode\n");
		memcpy((void *)subSecureInfo.u8SecIdentify,(void *)idForContinueMode, sizeof(idForContinueMode));
	}
	else
	{
		DEBUG("use the interleave mode\n");
		memcpy((void *)subSecureInfo.u8SecIdentify,(void *)idForInterleaveMode, sizeof(idForInterleaveMode));
	}
	
	subSecureInfo.info.u32Num=u32Num;
	subSecureInfo.info.u32Size=fileSize;
	
	sprintf(cmdBuf,"%s/rsa_sign %s %s ",utilityPath, intFileName,private_key);
	DEBUG("cmd=%s\n",cmdBuf);
    system(cmdBuf);
	memset(tempBuf1,0,sizeof(tempBuf1));
	strcat(strcpy(tempBuf1, intFileName),".sig");
	memset(tempBuf2,0,sizeof(tempBuf2));
	strcat(strcpy(tempBuf2, intFileName),".sig.bin");
	
	fr=fopen(tempBuf2,"r");
	if(fr==NULL){
		ERROR("[ERROR] open %s fail\n",tempBuf2);
		return -1;
	}
	
	fseek(fr, 0, SEEK_END);
	fileSize=ftell(fr);
	fseek(fr, 0, SEEK_SET);
	fread(subSecureInfo.u8Signature, SIGNATURE_LEN,sizeof(U8),fr);
	fclose(fr);
	
	
	DEBUG("tempBuf1=%s\n",tempBuf1);
	if(remove(tempBuf1)!=0){
		ERROR("[ERROR] remove %s fail\n",tempBuf1);
		return -1;
    }
	
	DEBUG("tempBuf2=%s\n",tempBuf2);
	if(remove(tempBuf2)!=0){
		ERROR("[ERROR] remove %s fail\n",tempBuf2);
		return -1;
    }
	
	DEBUG("fileFileName %s\n",outFileName);
	fw=fopen(outFileName,"w");
	if(fw==NULL){
		ERROR("[ERROR] open %s fail\n",outFileName);
		return -1;
	}
	
	fwrite(&subSecureInfo, sizeof(SUB_SECURE_INFO),sizeof(U8),fw);
	fclose(fw);
	return 0;
}


int getFileImage(char *file, U8* outBuf, U32 offset, U32 size, U8 IsInterleaveMode, U32 blockSize)
{
	FILE *fr=NULL;
	U32 read_size=0;
	U32 return_size=0;
	U32 i=0;
	if((file==NULL)||(outBuf==NULL))
	{
		ERROR("[ERROR] The input parameter is a null pointer\n");
		return -1;
	}
	DEBUG("file=%s\n",file);
	DEBUG("offset=0x%x\n",(unsigned int)offset);
	DEBUG("size=0x%x\n",(unsigned int)size);
	DEBUG("IsInterleaveMode=0x%x\n",(unsigned int)IsInterleaveMode);
	fr=fopen(file,"r");
	if(fr==NULL)
	{
		ERROR("[ERROR] open %s fail\n",file);
		return -1;
	}
	read_size=size;
	if(IsInterleaveMode==0)
	{
		fseek(fr, offset, SEEK_SET);
		return_size=fread(outBuf,sizeof(U8),read_size,fr);
		if(return_size!=read_size)
		{
			ERROR("Return size is not enough, return size=0x%x, read size=0x%x\n",(unsigned int)return_size,(unsigned int)read_size);
			fclose(fr);
			return -1;
		}
	}
	else
	{
		while(size>0)
        {
            read_size=(size>blockSize)?blockSize:size;
			DEBUG("i=%d, offset=0x%x, size=0x%x\n",(unsigned int)i,(unsigned int)(blockSize*i*SEGMENT_NUM+offset),(unsigned int)size);
			fseek(fr, 0, SEEK_SET);
			fseek(fr, blockSize*i*SEGMENT_NUM+offset, SEEK_CUR);
            return_size=fread(outBuf, sizeof(U8),read_size,fr);
            if(return_size!=read_size)
			{
				ERROR("Return size is not enough, return size=0x%x, read size=0x%x, size=0x%x\n",(unsigned int)return_size,(unsigned int)read_size,(unsigned int)size);
				fclose(fr);
				return -1;
			}
			size-=read_size;
			outBuf+=read_size;
			i++;
        }
	}
	fclose(fr);
	return 0;
}
int getFileSize(char *file, U32 *size)
{
	FILE *fr=NULL;
	if((file==NULL)||(size==NULL))
	{
		ERROR("The input parameter is a null pointer\n");
		return -1;
	}
	fr=fopen(file,"r");
	if(fr==NULL){
        DEBUG("The file size is 0\n");
		*size=0;
		return 0;
	}

	fseek(fr, 0, SEEK_END);
	*size=ftell(fr);
	fseek(fr, 0, SEEK_SET);
	fclose(fr);
	return 0;
}

int createSubFile(char *intFileName, char *outFileName, U32 offset, U32 size, U8 IsInterleaveMode, U32 blockSize)
{
	U8 *dataBuf=NULL;
	FILE *fw=NULL;
	U32 wsize=0;
	if((intFileName==NULL)||(outFileName==NULL))
	{
		ERROR("The input parameter is a null pointer\n");
		return -1;
	}
	DEBUG("intFileName=%s\n",intFileName);
	DEBUG("outFileName=%s\n",outFileName);
	DEBUG("offset=0x%x\n",(unsigned int)offset);
	DEBUG("size=0x%x\n",(unsigned int)size);
	DEBUG("IsInterleaveMode=0x%x\n",(unsigned int)IsInterleaveMode);
	dataBuf=(U8 *)malloc(size);
	if(dataBuf==NULL)
	{
		ERROR("[ERROR] malloc fail in %s\n",__FUNCTION__);
		return -1;
	}
	memset(dataBuf,0, size);
	if(getFileImage(intFileName,dataBuf,offset,size,IsInterleaveMode,blockSize)==-1)
	{
		ERROR("[ERROR] get file from %s fail\n",intFileName);
		free((void *)dataBuf);
		return -1;
	}
	fw=fopen(outFileName,"w");
	wsize=fwrite(dataBuf,sizeof(U8),size,fw);
	if(wsize!=size)
	{
		printf("Return size is not enough,wsize=0x%x, size=0x%x\n",(unsigned int)wsize,(unsigned int)size);
		free((void *)dataBuf);
		fclose(fw);
		return -1;
	}
	free((void *)dataBuf);
	fclose(fw);
	return 0;
}

int genSecureInfo(char *intFileName, char *outFileName, U32 segmentNum, char *utilityPath, char *privKeyPath, char *pubKeyPath,  U8 enInterleaveMode, U32 blockSize)
{
	U32 fileSize=0;
	U32 segmentSize=0;
	U32 offset=0;
	U32 size=0;
	U32 m=0,n=0;
	U8 cmdBuf[CMD_BUF];
	U8 nameBuf[CMD_BUF];
	U8 tempBuf[CMD_BUF];
	U32 origin_segmentNum;
	U32 i=0,j=0;
	int ret=0;
	
	if((intFileName==NULL)||(outFileName==NULL)||(privKeyPath==NULL)||(pubKeyPath==NULL))
	{
		ERROR("The input parameter is a null pointer\n");
		return -1;
	}
	origin_segmentNum=segmentNum;
	ret=getFileSize(intFileName,&fileSize);
	if(ret==-1)
	{
		ERROR("[ERROR] get %s size fail\n",intFileName);
		return -1;
	}
	DEBUG("The size of %s is 0x%x\n",intFileName,(unsigned int)fileSize);
    if((fileSize/blockSize)<segmentNum)
	{
		DEBUG("This image size is smaller than 0x%x\n",(unsigned int)(blockSize*segmentNum));
		segmentNum=(fileSize/blockSize)+1;
	}
	
	
	offset=0;
	for(i=0;i<segmentNum;i++)
	{
		if(enInterleaveMode==1)
		{
			DEBUG("fileSize=0x%x\n",(unsigned int)fileSize);
			DEBUG("blockSize=0x%x\n",(unsigned int)blockSize);
			DEBUG("segmentNum=%x\n",(unsigned int)segmentNum);
			if(origin_segmentNum>=segmentNum)
			{	
				size=(fileSize>blockSize)?blockSize:fileSize;
				fileSize-=blockSize;
			}
			else
			{
				m=(fileSize/blockSize)/segmentNum;
				n=(fileSize/blockSize)%segmentNum;
				DEBUG("m=%x\n",(unsigned int)m);
				DEBUG("n=%x\n",(unsigned int)n);
				size=m*blockSize;
				if(i<n)
				{
					size+=blockSize;
				}
			}
		}
		else
		{
			segmentSize=(fileSize/segmentNum);
			segmentSize+=(fileSize%segmentNum);
			size=fileSize>segmentSize?segmentSize:fileSize;
		}
		
		DEBUG("segment number=%x,size=%x,offset=%x\n",(unsigned int)i,(unsigned int)size,(unsigned int)offset);
		memset(tempBuf,0,sizeof(tempBuf));
		sprintf(tempBuf,  "%s.%d", intFileName,(unsigned int)i);
		DEBUG("tempBuf=%s\n",tempBuf);
		if(createSubFile(intFileName,tempBuf,offset,size,enInterleaveMode,blockSize)==-1)
		{
			ERROR("[ERROR] create sub file fail\n");
			return -1;
		}
		
		if(enInterleaveMode==1)
		{
			offset+=blockSize;
			DEBUG("blockSize=%x\n",(unsigned int)blockSize);
		}
		else
		{
			offset+=size;
		}
		
		memset(nameBuf,0,sizeof(nameBuf));
		sprintf(nameBuf,  "%s.%d", outFileName,(unsigned int)i);
		DEBUG("nameBuf=%s\n",nameBuf);
		ret=_genSubSecureInfo(utilityPath,nameBuf,tempBuf,segmentNum,privKeyPath,pubKeyPath,enInterleaveMode);
		if(ret<0)
		{
			printf("[ERROR]Generate sub secure info fail\n");
			return -1;
		}
		_cat(nameBuf,outFileName);
		if(remove(tempBuf)!=0)
		{
			ERROR("[ERROR] remove %s fail\n",tempBuf);
			return -1;
		}
		
	}
	//This part is for padding.
	while(segmentNum!=(origin_segmentNum))
	{
		_cat(nameBuf,outFileName);
		segmentNum++;
	}
	
	for(j=0;j<i;j++)
	{
		memset(nameBuf,0,sizeof(nameBuf));
		sprintf(nameBuf,  "%s.%d", outFileName,(unsigned int)j);
		DEBUG("nameBuf=%s\n",nameBuf);
		if(remove(nameBuf)!=0)
		{
			ERROR("[ERROR] remove %s fail\n",nameBuf);
			return -1;
		}
	}
	
	return 0;
	
}

int main(char argc, char *argv[])
{
	#define OUTPUT_FILE_NAME argv[1]
	#define INPUT_FILE_NAME  argv[2]
	#define PRIVATE_KEY argv[3]
	#define PUBLIC_KEY argv[4]
	#define ENABLE_PARTIAL_AUTHENTICATION argv[5]
	#define NUMBER_FOR_PARTIAL_AUTHENTICATION argv[6]
	#define ENABLE_INTERLEAVE_MODE argv[7]
	#define BLOCK_SIZE_FOR_INTERLEAVE argv[8]
	#define DISPLAY_DEBUGGING_INFO argv[9]
	#define UTILITY_PATH argv[10]
	U8 enPartialAuth=0;
	U8 enInterleaveMode=0;
	U32 segmentNum=0;
	FILE *fr=NULL;
	U32 blockSize=0;
	int ret1=0;
	int ret2=0;
	U8 cmdBuf[CMD_BUF];
	U8 tempBuf[CMD_BUF];
	
	if(argc<11){
		printf("argv[1] The output file name \n");
		printf("argv[2] The input file name \n");
		printf("argv[3] The path of private key \n");
		printf("argv[4] The path of public key \n");
		printf("argv[5] '1':Enable partial authentication. '0':Disable partial authentication \n");
		printf("argv[6] number for partial authentication\n");
		printf("argv[7] '1':Enable interleave mode. '0':Disable interleave mode \n");
		printf("argv[8] The Block size for interleave mode(unit:bytes) \n");
		printf("argv[9] '1'Enable debugging info.'0':Disable debugging info \n");
		printf("argv[10] externel utility tool path \n");
		return -1;
	}
	
	enDebugInfo=_atoi(DISPLAY_DEBUGGING_INFO);
	
	DEBUG("Enable displaying debugging info\n");
	DEBUG("OUTPUT_FILE_NAME=%s\n",OUTPUT_FILE_NAME);
	DEBUG("INPUT_FILE_NAME=%s\n",INPUT_FILE_NAME);
	DEBUG("PRIVATE_KEY=%s\n",PRIVATE_KEY);
	DEBUG("PUBLIC_KEY=%s\n",PUBLIC_KEY);
	DEBUG("ENABLE_PARTIAL_AUTHENTICATION=%s\n",ENABLE_PARTIAL_AUTHENTICATION);
	DEBUG("NUMBER_FOR_PARTIAL_AUTHENTICATION=%s\n",NUMBER_FOR_PARTIAL_AUTHENTICATION);
	DEBUG("UTILITY_PATH=%s\n",UTILITY_PATH);
	DEBUG("ENABLE_INTERLEAVE_MODE=%s\n",ENABLE_INTERLEAVE_MODE);
	DEBUG("BLOCK_SIZE_FOR_INTERLEAVE=%s\n",BLOCK_SIZE_FOR_INTERLEAVE);
	DEBUG("DISPLAY_DEBUGGING_INFO=%s\n",DISPLAY_DEBUGGING_INFO);
	
	enPartialAuth=_atoi(ENABLE_PARTIAL_AUTHENTICATION);
	enInterleaveMode=_atoi(ENABLE_INTERLEAVE_MODE);
	blockSize=_atoi(BLOCK_SIZE_FOR_INTERLEAVE);
	segmentNum=_atoi(NUMBER_FOR_PARTIAL_AUTHENTICATION);
	
	DEBUG("enPartialAuth=%d,segmentNum=%d\n",(unsigned int)enPartialAuth,(unsigned int)segmentNum);
	
	//Check if output file exist or not, if it exist, delete it.
	fr=fopen(OUTPUT_FILE_NAME,"r");
	if(fr!=NULL)
	{
		fclose(fr);
		if(remove(OUTPUT_FILE_NAME)!=0)
		{
			ERROR("[ERROR] remove %s fail\n",OUTPUT_FILE_NAME);
			return -1;
		}
	}
	
	if(enPartialAuth==0)
	{
		ret1=_genSubSecureInfo(UTILITY_PATH,OUTPUT_FILE_NAME,INPUT_FILE_NAME,1,PRIVATE_KEY,PUBLIC_KEY,0);
	        
		if(enInterleaveMode==1)
		{
			
			memset(tempBuf,0,sizeof(tempBuf));
			sprintf(tempBuf,  "%s.sig", INPUT_FILE_NAME);
			DEBUG("tempBuf=%s\n",tempBuf);
			if(-1!=_genSubSecureInfo(UTILITY_PATH,tempBuf,INPUT_FILE_NAME,1,PRIVATE_KEY,PUBLIC_KEY,1))
			{
				_cat(tempBuf,OUTPUT_FILE_NAME);
			    if(remove(tempBuf)!=0)
				{
					ERROR("[ERROR] remove %s fail\n",tempBuf);
					return -1;
				}
				
			}
			else
			{
				ret2=-1;
			}
		}
		
		if((ret1==-1)||(ret2==-1))
		{
			ERROR("create sub secure info for interleave mode fail\n");
			return -1;
		}
		
	}
	else
	{
		ret1=genSecureInfo(INPUT_FILE_NAME, OUTPUT_FILE_NAME,segmentNum, UTILITY_PATH, PRIVATE_KEY, PUBLIC_KEY, 0, blockSize);
		if(enInterleaveMode==1)
		{
			ret2=genSecureInfo(INPUT_FILE_NAME, OUTPUT_FILE_NAME,segmentNum, UTILITY_PATH, PRIVATE_KEY, PUBLIC_KEY, 1, blockSize);
		}
	}
	
	if((ret1==-1)||(ret2==-1))
	{
		ERROR("Create secure info fail\n");
	}
	
	return ((ret1==-1)||(ret2==-1));
}
